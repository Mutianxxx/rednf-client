// ============================================================
// 【40JP逆向源代码工程】src/nengine/gfx_texture.cpp
// 模块: 引擎核心 0x41 区 —— D3D 纹理绘制 / CNImagePackEx 图像包(IMG) / NeopleFontFile+Arial Narrow 字体 / WAV / 模块切换
// 来源: work/dump_engine.txt  区块: 0x410000-0x420000
// 层级: L2 转写层（Hex-Rays 逐字对应）+【L1 精修层】
//
// 【L1 精修内容】（注释级，函数体与 L2 逐字一致，零改动）:
//   ① 文件头重写 + 29 个 SECTION 分区横幅（29 段生效）+ SECTION 索引表
//   ② 34 个关键函数【解读】注释块（CNImagePackEx::Load/Destroy、IMG 解码族、
//      字体构建、onChangeModule、界面 IMG 预载等）
//   ③ 10 个函数标记行追加 [串: "..."] 字符串证据尾注（逐函数覆盖）
//
// ★★ IMG（Neople Image File）格式推断（0x418CD0/0x418E20/0x419550 直证）:
//   [文件头] 0x20(32) 字节魔数 = "Neople Image File"（strcmp 校验，不足补齐到 32B）
//   [记录流] 顺序记录，每条:
//     · 4B 记录头 = 图像 ID（0x419550 读出后交设备 vt+8 CreateImage）
//       └ 特例 ID == 0x11(17): 别名条目 —— 再读 4B 源索引，与已建图像共享指针（flag=1）
//     · 图像数据块 = zlib 压缩流（★ 解码族 0x4116A0/0x411B30/0x412150/0x412700
//       均调 zlib_inflate.cpp 0x652E00 = uncompress），块长自描述:
//       图像对象 vt+116(FILE*) 装载并返回消费字节数 → fseek 定位下一记录
//   [运行时目录] 12 字节/项矢量（this+52..60 三指针）: [数据偏移 4B | 图像对象 4B | 别名标志 1B]
//     —— 由 Load 构建；0x418E20 据此做延迟加载（fseek(offset) + 图像 vt+108 装载）
//   [包根决策] 0x420190（0x42 区）: _access("_ImagePacks") 开发目录 → 缺省 "ImagePacks2/"；
//     路径拼装 "%s%c%s%c%s"（0x419D40）
//   [自证字符串] CND3DTexture32/16::CalcuatePersistSize（二进制串证据，本区纹理持久尺寸计算）
//
// 其它要点:
//   - CNImagePackEx::Load（0x419550）/Destroy（0x419320）函数名自证；CreateImage 失败/
//     SetImagePackEx 失败/open_file failed 三类错误日志（off_77F3FC）。
//   - SetImagePackEx（0x410750）把图像包绑到 CND3DBaseTexture（+32/33），重复绑定报错。
//   - 字体: NeopleFontFile 自有字体容器（0x416F40/0x417030 魔数校验）+ Arial Narrow
//     GDI 栅格化（0x4176E0/0x417B60 CreateFontA+CreateDIBSection+TextOutA）。
//   - onChangeModule（0x41CC80）: MODULE_TYPE_PVP/WARROOM/MAIN_GAME/SELECT_DUNGEON 切换时
//     "@@UDP STOP/START" 广播 + LADDER_DOWN + STOP SOUND + MAP_APPEAR（seatIndex 直证）。
//   - 界面 IMG 预载八件套（0x41F2C0）: Sprite/Interface/{SelectCharacter,CreateCharacter,
//     CharacterIllust,Base,ItemInventoryWindow,AvatarInventoryWindow,ItemTradeWindow,
//     EquipmentShopWindow}.img。
//
// 函数数: 370（L1 覆盖 370：解读 34 / 串证据 10 / 分区 29）
// ============================================================

#include "../../common/arad_types.h"
// ============================================================
// SECTION 索引（按 VA 升序）
// ============================================================
//   0x410000 — CND3DBaseTexture 绘制族：NiProfile 包裹 + IntersectRect 裁剪 + 浮点变换的块绘制（0x410030/0x410140/0x410300/0x4105A0 变体）
//   0x410750 — 纹理↔ImagePackEx 绑定（SetImagePackEx）+ 块传输族
//   0x4111E0 — 屏幕矩形/视口辅助
//   0x4116A0 — ★ IMG 图像块解码族（0x4116A0/0x411B30/0x412150/0x412700 —— 均调 0x652E00 zlib uncompress：IMG 内嵌图像数据为 zlib 压缩流）
//   0x412AE0 — 图像属性 getter/setter（宽高/矩形/标志，HIWORD/LOWORD 打包）
//   0x413B80 — 图像对象构造/克隆（SetRect + 容器分配）
//   0x413EE0 — 窗口尺寸调整族（GetWindowLong/GetSystemMetrics/AdjustWindowRectEx/SetWindowPos）
//   0x414200 — 引擎日志格式化转发（vsprintf → 0x404B30 缓冲）
//   0x4143A0 — 对象销毁/容器壳
//   0x414570 — 声音对象/WAV 缓冲族（0x4149E0 mmio WAV→DirectSound 装载）
//   0x414D60 — COM/宽字符工具（CoCreateInstance / MultiByteToWideChar）
//   0x415020 — 键盘输入族（GetAsyncKeyState 轮询）
//   0x415B10 — 输入映射 vector 管理（按键状态容器）
//   0x4164C0 — string/vector 容器工具
//   0x416890 — 字形/文本对象容器（大函数，字体缓存管理）
//   0x416CD0 — GDI 资源清理（DeleteObject 族）
//   0x416F40 — ★ NeopleFontFile 自有字体文件校验（fopen + 魔数 "NeopleFontFile"）
//   0x4176E0 — ★ Arial Narrow GDI 位图字体构建（CreateFontA + CreateDIBSection + TextOutA 栅格化缓存）
//   0x4185B0 — GDI 文本渲染三件套（DIB/TextOut/宽度表，0x4185B0/0x4186C0/0x418AA0）
//   0x418CB0 — ★★ CNImagePackEx：IMG 打开/魔数校验/延迟加载/别名/销毁 + 路径拼装
//   0x4199A0 — mmio WAV 读取族（mmioOpenA/Descend/Read/Ascend → 声音缓冲）
//   0x419D40 — 路径拼装（"%s%c%s%c%s"）/ 图像项容器 / 时间节流
//   0x41A7C0 — STL 容器模板实例族（vector/list/deque 诊断与操作）
//   0x41C0C0 — 应用状态/模块管理（场景查询、退出、事件分发、消息发送）
//   0x41CC80 — ★★ onChangeModule 模块切换总控（UDP STOP/START 广播、LADDER_DOWN、STOP SOUND、MAP_APPEAR）
//   0x41D5A0 — 模块切换辅助（map 容器/观察者清理/资源卸载链）
//   0x41E4F0 — 服务器连接 UI 状态（"Connect to Server..."/"Connection Failed"）
//   0x41F2C0 — ★ 界面 IMG 预载清单（Sprite/Interface/*.img 八件）+ DllMain
//   0x41F930 — 引擎聚合初始化/事件路由/杂项
// ============================================================

// ============================================================
// SECTION 0x410000 — CND3DBaseTexture 绘制族：NiProfile 包裹 + IntersectRect 裁剪 + 浮点变换的块绘制（0x410030/0x410140/0x410300/0x4105A0 变体）
// ============================================================
// ------------------------------------------------------------
// 0x410000 sub_410000
// ------------------------------------------------------------
// 【解读】
//   纹理设备丢失复位: this+44 就绪标志检查 → 设备 vt+68(0) 复位 → 标志清 0；失败返回 0x80000005（E_FAIL 族）。
// ------------------------------------------------------------
int /*thiscall*/ sub_410000(int this)
{
  int result; // eax

  if ( *(uint8_t *)(this + 44) == 0 )
    return -2147483641;
  result = (*(int (/*stdcall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(this + 112) + 68))(*(uint32_t *)(this + 112), 0);
  if ( result >= 0 )
  {
    *(uint8_t *)(this + 44) = 0;
    return 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x410030 sub_410030
// ------------------------------------------------------------
// 【解读】
//   纹理块绘制入口（userpurge）: sub_404F40(a1,4) = NiProfile 计时作用域开启 →
//     源矩形平移（a3+a2[7]）→ IntersectRect 裁剪 → 浮点坐标变换 → sub_404F80 计时结束。
// ------------------------------------------------------------
void /*userpurge*/ sub_410030(int nArg1@<eax>, uint32_t *pArg2@<ecx>, int nArg3, int nArg4, const RECT *pArg5, int nArg6, int nArg7)
{
  LONG v8; // edi
  LONG v9; // ebx
  LONG v10; // ecx
  int v11; // edx
  double left; // st7
  double v13; // st7
  int v14; // eax
  double v15; // st7
  int pObj; // eax
  int v17; // eax
  struct tagRECT rcDst; // [esp+Ch] [ebp-28h] BYREF
  uint32_t v19[2]; // [esp+1Ch] [ebp-18h] BYREF
  float v20[2]; // [esp+24h] [ebp-10h] BYREF
  float v21[2]; // [esp+2Ch] [ebp-8h] BYREF

  sub_404F40(nArg1, 4u);
  v8 = nArg3 + pArg2[7];
  v9 = nArg4 + pArg2[8];
  v10 = v9 + pArg2[6];
  rcDst.right = v8 + pArg2[5];
  rcDst.bottom = v10;
  rcDst.left = v8;
  rcDst.top = v9;
  if ( IntersectRect(&rcDst, &rcDst, pArg5 + 3) )
  {
    v11 = pArg2[5];
    left = (double)rcDst.left;
    rcDst.left -= v8;
    v21[0] = left;
    rcDst.right -= v8;
    v21[1] = (float)rcDst.top;
    v13 = (double)(int)pArg2[5];
    rcDst.top -= v9;
    rcDst.bottom -= v9;
    v19[0] = 1065353216;
    v19[1] = 1065353216;
    if ( v11 < 0 )
      v13 = v13 + 4294967300.0;
    v14 = pArg2[6];
    v20[0] = v13 * 0.5;
    v15 = (double)(int)pArg2[6];
    if ( v14 < 0 )
      v15 = v15 + 4294967300.0;
    pObj = pArg2[31];
    v20[1] = v15 * 0.5;
    v17 = (*(int (/*stdcall*/ **)(int, uint32_t, struct tagRECT *, uint32_t *, float *, int, float *, int))(*(uint32_t *)pObj + 20))(
            pObj,
            pArg2[28],
            &rcDst,
            v19,
            v20,
            nArg7,
            v21,
            nArg6);
    sub_404F80(v17, 4u, 0);
  }
}



// ------------------------------------------------------------
// 0x410140 sub_410140 —— 缩放纹理绘制（反算 UV）
//   计时作用域 sub_404F40(4) 内：this+20/24 宽高乘 fArg8/fArg9 得缩放尺寸，与目标矩形求交后
//   按 1/缩放 反算贴图 UV 写入全局 dword_8A76E8 族四角，交设备 vt+20 绘制。
// ------------------------------------------------------------
void /*userpurge*/ sub_410140(int nArg1@<eax>, int pArg2@<ecx>, int nArg3, int nArg4, int *pDwArg5, int nArg6, int nArg7, float fArg8, float fArg9)
{
  double v10; // st7
  int v11; // ecx
  double v12; // st7
  int v14; // edx
  double v15; // st7
  double v16; // st6
  double v17; // st7
  double v18; // st6
  double v19; // st5
  double v20; // st5
  int v21; // eax
  float v22; // [esp+8h] [ebp-40h] BYREF
  float v23; // [esp+Ch] [ebp-3Ch]
  float v24; // [esp+10h] [ebp-38h]
  float v25; // [esp+14h] [ebp-34h]
  float v26; // [esp+18h] [ebp-30h] BYREF
  float v27; // [esp+1Ch] [ebp-2Ch]
  float pNext; // [esp+20h] [ebp-28h]
  float pNext2; // [esp+24h] [ebp-24h]
  uint32_t fArg82[2]; // [esp+28h] [ebp-20h] BYREF
  float v31[2]; // [esp+30h] [ebp-18h] BYREF
  float v32[2]; // [esp+38h] [ebp-10h] BYREF
  float v33; // [esp+40h] [ebp-8h]
  float v34; // [esp+44h] [ebp-4h]
  int v35; // [esp+50h] [ebp+8h]
  float v36; // [esp+50h] [ebp+8h]
  int v37; // [esp+58h] [ebp+10h]
  float v38; // [esp+58h] [ebp+10h]

  sub_404F40(nArg1, 4u);
  v10 = (double)*(unsigned int *)(pArg2 + 20);
  v26 = 0.0;
  v11 = *(uint32_t *)(pArg2 + 24);
  v27 = 0.0;
  v34 = v10 * fArg8;
  pNext = v34;
  v12 = (double)*(int *)(pArg2 + 24);
  if ( v11 < 0 )
    v12 = v12 + 4294967300.0;
  v14 = *(uint32_t *)(pArg2 + 28);
  v33 = v12 * fArg9;
  pNext2 = v33;
  v15 = (double)pDwArg5[12];
  v37 = nArg3 + v14;
  v16 = (double)pDwArg5[14];
  v23 = (float)pDwArg5[13];
  v35 = nArg4 + *(uint32_t *)(pArg2 + 32);
  v25 = (float)pDwArg5[15];
  v38 = (float)v37;
  v22 = v15 - v38;
  v24 = v16 - v38;
  v36 = (float)v35;
  v23 = v23 - v36;
  v25 = v25 - v36;
  if ( sub_40FCB0(&v26, &v26, &v22) )
  {
    v17 = v38 + v26;
    v18 = v36 + v27;
    *(float *)fArg82 = fArg8;
    *(float *)&fArg82[1] = fArg9;
    v19 = 1.0 / fArg8;
    v26 = v26 * v19;
    pNext = v19 * pNext;
    v20 = 1.0 / fArg9;
    v27 = v27 * v20;
    pNext2 = v20 * pNext2;
    v32[0] = v17;
    v32[1] = v18;
    v31[0] = v34 * 0.5;
    v31[1] = v33 * 0.5;
    dword_8A76E8 = (uint64_t)v26;
    dword_8A76F0 = (uint64_t)pNext;
    dword_8A76EC = (uint64_t)v27;
    dword_8A76F4 = (uint64_t)pNext2;
    v21 = (*(int (/*stdcall*/ **)(uint32_t, uint32_t, int *, uint32_t *, float *, int, float *, unsigned int))(**(uint32_t **)(pArg2 + 124) + 20))(
            *(uint32_t *)(pArg2 + 124),
            *(uint32_t *)(pArg2 + 112),
            &dword_8A76E8,
            fArg82,
            v31,
            nArg7,
            v32,
            nArg6 & 0xFF00FF00 | ((uint8_t)nArg6 << 16) | BYTE2(nArg6));
    sub_404F80(v21, 4u, 0);
  }
}



// ------------------------------------------------------------
// 0x410300 sub_410300 —— 缩放与镜像纹理绘制（正负分支）
//   与 ·sub_410140 同族：fArg7/fArg8 为负时走镜像分支（UV 端点互换、偏移取反），
//   颜色 nArg5 经 FF00FF00 通道重排后交设备 vt+20 绘制。
// ------------------------------------------------------------
int /*thiscall*/ sub_410300(int this, int nArg2, int nArg3, int *pDwArg4, int nArg5, int nArg6, float fArg7, float fArg8, float fArg9, float fArg10)
{
  int fld_142; // eax
  double fld_143; // st7
  double fld_1C2; // st7
  int fld_182; // edx
  double fld_183; // st7
  double fld_202; // st7
  double v17; // st7
  double v18; // st6
  int result; // eax
  double v21; // st7
  uint8_t v22; // c0
  uint8_t v23; // c3
  double v24; // st7
  double v26; // st6
  uint8_t v27; // c0
  uint8_t v28; // c3
  double v29; // st6
  double v31; // st5
  uint8_t v32; // c0
  uint8_t v33; // c3
  double v34; // st4
  double v35; // st5
  double v37; // st5
  uint8_t v38; // c0
  uint8_t v39; // c3
  double v40; // st4
  double v41; // st5
  float v42; // [esp+4h] [ebp-44h] BYREF
  float v43; // [esp+8h] [ebp-40h]
  float v44; // [esp+Ch] [ebp-3Ch]
  float v45; // [esp+10h] [ebp-38h]
  float fld_14; // [esp+14h] [ebp-34h] BYREF
  float fld_18; // [esp+18h] [ebp-30h]
  float v48; // [esp+1Ch] [ebp-2Ch]
  float v49; // [esp+20h] [ebp-28h]
  uint32_t fArg72[2]; // [esp+24h] [ebp-24h] BYREF
  float v51[2]; // [esp+2Ch] [ebp-1Ch] BYREF
  float v52[3]; // [esp+34h] [ebp-14h] BYREF
  float fld_20; // [esp+40h] [ebp-8h]
  float fld_1C; // [esp+44h] [ebp-4h]
  float v55; // [esp+6Ch] [ebp+24h]
  float v56; // [esp+70h] [ebp+28h]

  sub_404F40(4);
  fld_1C = (double)*(int *)(this + 28) - fArg9;
  fld_20 = (double)*(int *)(this + 32) - fArg10;
  if ( fArg7 <= 0.0 )
  {
    fld_14 = ((double)*(unsigned int *)(this + 20) + fld_1C) * fArg7;
    fld_1C2 = fld_1C;
  }
  else
  {
    fld_142 = *(uint32_t *)(this + 20);
    fld_14 = fld_1C * fArg7;
    fld_143 = (double)*(int *)(this + 20);
    if ( fld_142 < 0 )
      fld_143 = fld_143 + 4294967300.0;
    fld_1C2 = fld_143 + fld_1C;
  }
  v48 = fld_1C2 * fArg7;
  if ( fArg8 <= 0.0 )
  {
    fld_18 = ((double)*(unsigned int *)(this + 24) + fld_20) * fArg8;
    fld_202 = fld_20;
  }
  else
  {
    fld_182 = *(uint32_t *)(this + 24);
    fld_18 = fld_20 * fArg8;
    fld_183 = (double)*(int *)(this + 24);
    if ( fld_182 < 0 )
      fld_183 = fld_183 + 4294967300.0;
    fld_202 = fld_183 + fld_20;
  }
  v49 = fld_202 * fArg8;
  v17 = (double)pDwArg4[12];
  v18 = (double)pDwArg4[14];
  v43 = (float)pDwArg4[13];
  v45 = (float)pDwArg4[15];
  v55 = (double)nArg2 + fArg9;
  v56 = (double)nArg3 + fArg10;
  v42 = v17 - v55;
  v44 = v18 - v55;
  v43 = v43 - v56;
  v45 = v45 - v56;
  result = sub_40FCB0(&fld_14, &fld_14, &v42);
  if ( (uint8_t)result != 0 )
  {
    v21 = v55;
    if ( (v22 | v23) != 0 )
      v24 = v21 + v48;
    else
      v24 = v21 + fld_14;
    v26 = v56;
    if ( (v27 | v28) != 0 )
      v29 = v26 + v49;
    else
      v29 = v26 + fld_18;
    v31 = 1.0 / fArg7;
    if ( (v32 | v33) != 0 )
    {
      v34 = v31;
      v35 = v48 * v31 - fld_1C;
      v48 = v34 * fld_14 - fld_1C;
      fld_14 = v35;
    }
    else
    {
      fld_14 = fld_14 * v31 - fld_1C;
      v48 = v31 * v48 - fld_1C;
    }
    v37 = 1.0 / fArg8;
    if ( (v38 | v39) != 0 )
    {
      v40 = v37;
      v41 = v49 * v37 - fld_20;
      v49 = v40 * fld_18 - fld_20;
      fld_18 = v41;
    }
    else
    {
      fld_18 = fld_18 * v37 - fld_20;
      v49 = v37 * v49 - fld_20;
    }
    v52[0] = v24;
    v52[1] = v29;
    *(float *)fArg72 = fArg7;
    *(float *)&fArg72[1] = fArg8;
    v51[0] = -fld_1C;
    v51[1] = -fld_20;
    dword_8A76E8 = (uint64_t)fld_14;
    dword_8A76F0 = (uint64_t)v48;
    dword_8A76EC = (uint64_t)fld_18;
    dword_8A76F4 = (uint64_t)v49;
    (*(void (/*stdcall*/ **)(uint32_t, uint32_t, int *, uint32_t *, float *, int, float *, unsigned int))(**(uint32_t **)(this + 124)
                                                                                                + 20))(
      *(uint32_t *)(this + 124),
      *(uint32_t *)(this + 112),
      &dword_8A76E8,
      fArg72,
      v51,
      nArg6,
      v52,
      nArg5 & 0xFF00FF00 | ((uint8_t)nArg5 << 16) | BYTE2(nArg5));
    return sub_404F80(4, 0);
  }
  return result;
}


// ------------------------------------------------------------
// 0x4105A0 sub_4105A0 —— 矩阵变换绘制（0x67 区矩阵链）
//   调 0x67 区矩阵库拼四角变换（sub_67CF8F/sub_67D13A/sub_67CEFF/sub_67C632 链，反复相乘后交设备），
//   结果交设备 vt+24 绘制（矩阵版语义【推断】）。
// ------------------------------------------------------------
void /*userpurge*/ sub_4105A0(
        int a1@<eax>,
        int a2@<ecx>,
        int a3,
        int a4,
        int a5,
        int a6,
        float a7,
        float a8,
        float a9,
        float a10,
        float a11)
{
  int v12; // eax
  float v13; // [esp+Ch] [ebp-358h]
  float v14; // [esp+Ch] [ebp-358h]
  float v15; // [esp+10h] [ebp-354h]
  float v16; // [esp+10h] [ebp-354h]
  float v17; // [esp+14h] [ebp-350h]
  uint8_t v18[64]; // [esp+24h] [ebp-340h] BYREF
  uint8_t v19[64]; // [esp+64h] [ebp-300h] BYREF
  uint8_t v20[64]; // [esp+A4h] [ebp-2C0h] BYREF
  uint8_t v21[64]; // [esp+E4h] [ebp-280h] BYREF
  uint8_t v22[64]; // [esp+124h] [ebp-240h] BYREF
  int v23[16]; // [esp+164h] [ebp-200h] BYREF
  int v24[16]; // [esp+1A4h] [ebp-1C0h] BYREF
  uint8_t v25[64]; // [esp+1E4h] [ebp-180h] BYREF
  uint8_t v26[64]; // [esp+224h] [ebp-140h] BYREF
  uint8_t v27[64]; // [esp+264h] [ebp-100h] BYREF
  uint8_t v28[64]; // [esp+2A4h] [ebp-C0h] BYREF
  uint8_t v29[64]; // [esp+2E4h] [ebp-80h] BYREF
  int v30[16]; // [esp+324h] [ebp-40h] BYREF

  sub_404F40(a1, 4u);
  v15 = a11 - (double)*(int *)(a2 + 32);
  v13 = a10 - (double)*(int *)(a2 + 28);
  sub_67CF8F((int)v30, v13, v15, 0.0);
  sub_67CB3E(v27, 0, v30);
  v17 = -a7;
  sub_67D13A((int)v23, v17);
  sub_67CEFF((int)v25, a8, a9, 1.0);
  v16 = (float)(a4 + *(uint32_t *)(a2 + 32));
  v14 = (float)(a3 + *(uint32_t *)(a2 + 28));
  sub_67CF8F((int)v24, v14, v16, 1.0);
  sub_67C632(v19, v27, v23);
  qmemcpy(v21, v19, sizeof(v21));
  sub_67C632(v29, v21, v25);
  qmemcpy(v28, v29, sizeof(v28));
  sub_67C632(v26, v28, v30);
  qmemcpy(v22, v26, sizeof(v22));
  sub_67C632(v20, v22, v24);
  qmemcpy(v18, v20, sizeof(v18));
  v12 = (*(int (/*stdcall*/ **)(uint32_t, uint32_t, uint32_t, uint8_t *, unsigned int))(**(uint32_t **)(a2 + 124) + 24))(
          *(uint32_t *)(a2 + 124),
          *(uint32_t *)(a2 + 112),
          0,
          v18,
          a6 & 0xFF00FF00 | ((uint8_t)a6 << 16) | BYTE2(a6));
  sub_404F80(v12, 4u, 0);
}



// ============================================================
// SECTION 0x410750 — 纹理↔ImagePackEx 绑定（SetImagePackEx）+ 块传输族
// ============================================================
// ------------------------------------------------------------
// 0x410750 sub_410750
// ------------------------------------------------------------
// 【解读】
//   SetImagePackEx: 把 CNImagePackEx(+索引) 绑到 CND3DBaseTexture（this+32/33）；
//   重复绑定报 "CND3DBaseTexture : ImagePackEx already exists"（0x80000005）。
//   0x419550（PackEx::Load）对每个新图像调用 —— 纹理回指图像包的通路。
// ------------------------------------------------------------
int /*thiscall*/ sub_410750(uint32_t *this, int nArg2, int nArg3)  // 【纹理↔ImagePackEx 绑定（SetImagePackEx）+ 块传输族】
{
  if ( *(this + 32) != 0 )
  {
    off_77F3FC("CND3DBaseTexture : ImagePackEx already exists");
    return 0x80000000;
  }
  else
  {
    *(this + 32) = nArg2;
    *(this + 33) = nArg3;
    return 1;
  }
}



// ------------------------------------------------------------
// 0x410790 sub_410790 —— 整数快速幂（含负指数）
//   二进制快速幂 nArg1^nArg2；负指数取整数倒数 1/v4【推断：用于缩放/采样比例换算】。
// ------------------------------------------------------------
int /*cdecl*/ sub_410790(int nArg1, int nArg2)
{
  unsigned int nArg22; // eax
  int v4; // ecx

  nArg22 = nArg2;
  if ( nArg2 < 0 )
    nArg22 = -nArg2;
  v4 = 1;
  while ( 1 )
  {
    if ( (nArg22 & 1) != 0 )
      v4 *= nArg1;
    nArg22 >>= 1;
    if ( nArg22 == 0 )
      break;
    nArg1 *= nArg1;
  }
  if ( nArg2 >= 0 )
    return v4;
  else
    return 1 / v4;
}



// ------------------------------------------------------------
// 0x4107D0 sub_4107D0 —— 块传输分派（纹理块 / 位图 Blt）
//   守卫：this+128 无外部位图或 sub_418E20 对图像包 this+132 延迟加载成功，且 this+4 就绪。
//   格式 7 交纹理块绘制 sub_410030；8/16/14/15 先 CopyRect+IntersectRect 裁剪再交对象 vt+112 blit。
// ------------------------------------------------------------
void /*thiscall*/ sub_4107D0(int this, int nArg2, int dy, const RECT *pArg4)
{
  int fld_14; // ecx
  int right; // eax
  int fld_20; // ecx
  int fld_78; // eax
  struct tagRECT rcDst; // [esp+4h] [ebp-18h] BYREF
  int fld_1C; // [esp+14h] [ebp-8h] BYREF
  int v11; // [esp+18h] [ebp-4h]

  if ( (*(uint32_t *)(this + 128) == 0 || sub_418E20(*(uint32_t *)(this + 132)) != 0) && *(uint8_t *)(this + 4) != 0 )
  {
    fld_14 = *(uint32_t *)(this + 20);
    if ( fld_14 != 1 || *(uint32_t *)(this + 24) != 1 )
    {
      right = pArg4->right;
      if ( right == 7 )
      {
        if ( fld_14 != 1 || *(uint32_t *)(this + 24) != 1 )
          sub_410030(7, (uint32_t *)this, nArg2, dy, pArg4, -1, 0);
      }
      else if ( right == 8 || right == 16 || right == 14 || right == 15 )
      {
        sub_404F40(right, 4u);
        fld_20 = *(uint32_t *)(this + 32);
        fld_1C = nArg2 + *(uint32_t *)(this + 28);
        v11 = dy + fld_20;
        CopyRect(&rcDst, (const RECT *)(this + 48));
        OffsetRect(&rcDst, nArg2, dy);
        if ( IntersectRect(&rcDst, &rcDst, pArg4 + 3) )
        {
          OffsetRect(&rcDst, -nArg2, -dy);
          if ( nArg2 < 0 )
            fld_1C = 0;
          if ( dy < 0 )
            v11 = 0;
          fld_78 = (*(int (/*stdcall*/ **)(uint32_t, uint32_t, struct tagRECT *, int, LONG, int *))(**(uint32_t **)(this + 120) + 112))(
                 *(uint32_t *)(this + 120),
                 *(uint32_t *)(this + 116),
                 &rcDst,
                 1,
                 pArg4[7].top,
                 &fld_1C);
          sub_404F80(fld_78, 4u, 0);
        }
      }
    }
  }
}



// ------------------------------------------------------------
// 0x410910 sub_410910 —— 块绘制分派（直绘 / 逐像素透明检测）
//   格式 7 直接交 vt+20 单块绘制；14/15 且源目同表面时逐像素读回（vt+64）比对键值 0x7F070707，
//   非键值像素经 vt+32 改写为 -1（键值像素保留）【推断：颜色键处理】；跨表面则交 vt+112 blit。
// ------------------------------------------------------------
void /*userpurge*/ sub_410910(int nArg1@<eax>, int pArg2@<ecx>, int nArg3, int nArg4, int pArg5, uint32_t *pArg6, int nArg7)
{
  uint32_t *pArg62; // eax
  int pObj; // eax
  int v10; // eax
  int v11; // ecx
  int v12; // ecx
  unsigned int v13; // edx
  unsigned int i; // ebx
  unsigned int v15; // edi
  int v16; // [esp-1Ch] [ebp-30h]
  int v17; // [esp-10h] [ebp-24h]
  int nArg32; // [esp+4h] [ebp-10h] BYREF
  int nArg42; // [esp+8h] [ebp-Ch]
  float v20[2]; // [esp+Ch] [ebp-8h] BYREF
  unsigned int v21; // [esp+24h] [ebp+10h]
  unsigned int v22; // [esp+2Ch] [ebp+18h]

  sub_404F40(nArg1, 4u);
  if ( (*(uint32_t *)(pArg2 + 128) == 0 || sub_418E20(*(uint32_t *)(pArg2 + 132)) != 0)
    && *(uint8_t *)(pArg2 + 4) != 0
    && (*(uint32_t *)(pArg2 + 20) != 1 || *(uint32_t *)(pArg2 + 24) != 1) )
  {
    pArg62 = *(uint32_t **)(pArg5 + 8);
    if ( pArg62 == (uint32_t *)7 )
    {
      pObj = *(uint32_t *)(pArg2 + 124);
      v20[0] = (float)nArg3;
      v20[1] = (float)nArg4;
      v16 = *(uint32_t *)(pArg2 + 112);
      nArg32 = 1065353216;
      nArg42 = 1065353216;
      v10 = (*(int (/*stdcall*/ **)(int, int, uint32_t *, int *, uint32_t, uint32_t, float *, int))(*(uint32_t *)pObj + 20))(
              pObj,
              v16,
              pArg6,
              &nArg32,
              0,
              0,
              v20,
              nArg7);
      sub_404F80(v10, 4u, 0);
    }
    else
    {
      if ( pArg62 == (uint32_t *)14 || pArg62 == (uint32_t *)15 )
      {
        if ( pArg5 == pArg2 )
        {
          pArg62 = pArg6;
          v12 = pArg6[2] - *pArg6;
          v13 = pArg6[3] - pArg6[1];
          v21 = v12;
          v22 = v13;
          for ( i = 0; i < v13; ++i )
          {
            v15 = 0;
            if ( v12 != 0 )
            {
              do
              {
                if ( (*(int (/*thiscall*/ **)(int, unsigned int, unsigned int))(*(uint32_t *)pArg2 + 64))(
                       pArg2,
                       v15 + *pArg62,
                       i + pArg62[1]) != 2131166983 )
                  (*(void (/*thiscall*/ **)(int, unsigned int, unsigned int, int))(*(uint32_t *)pArg2 + 32))(
                    pArg2,
                    v15 + nArg3,
                    i + nArg4,
                    -1);
                ++v15;
                pArg62 = pArg6;
              }
              while ( v15 < v21 );
              v12 = v21;
              v13 = v22;
            }
          }
        }
        else
        {
          v17 = *(uint32_t *)(pArg5 + 116);
          v11 = *(uint32_t *)(pArg2 + 116);
          nArg32 = nArg3;
          nArg42 = nArg4;
          pArg62 = (uint32_t *)(*(int (/*stdcall*/ **)(uint32_t, int, uint32_t *, int, int, int *))(**(uint32_t **)(pArg2 + 120) + 112))(
                           *(uint32_t *)(pArg2 + 120),
                           v11,
                           pArg6,
                           1,
                           v17,
                           &nArg32);
        }
      }
      sub_404F80((int)pArg62, 4u, 0);
    }
  }
}



// ------------------------------------------------------------
// 0x410A80 sub_410A80 —— 绘制入口（按缩放 1 分派）
//   缩放均为 1.0 时直绘 sub_410030；否则（fArg5/fArg6 大于 0）走缩放绘制 sub_410140。
// ------------------------------------------------------------
void /*thiscall*/ sub_410A80(int this, int nArg2, int nArg3, RECT *uArg4, float fArg5, float fArg6, int nArg7, int nArg8, int nArg9, int nArg10)
{
  if ( (*(uint32_t *)(this + 128) == 0 || sub_418E20(*(uint32_t *)(this + 132)) != 0)
    && *(uint8_t *)(this + 4) != 0
    && (*(uint32_t *)(this + 20) != 1 || *(uint32_t *)(this + 24) != 1)
    && uArg4->right == 7 )
  {
    if ( fArg5 == 1.0 && fArg6 == 1.0 )
    {
      sub_410030(nArg8, (uint32_t *)this, nArg2, nArg3, uArg4, nArg8, nArg7);
    }
    else if ( fArg5 > 0.0 && fArg6 > 0.0 )
    {
      sub_410140(nArg3, this, nArg2, nArg3, &uArg4->left, nArg8, nArg7, fArg5, fArg6);
    }
  }
}



// ------------------------------------------------------------
// 0x410B60 sub_410B60 —— 绘制入口（按旋转角分派）
//   旋转角 nArg7 为 0 走几何版 sub_410300，否则走矩阵版 sub_4105A0；
//   fArg9/fArg10 为哨兵值（Hex-Rays 记 4294967300.0）时以宽高一半为旋转中心【推断】。
// ------------------------------------------------------------
void /*thiscall*/ sub_410B60(int this, int nArg2, int nArg3, int *pDwArg4, float fArg5, float fArg6, int nArg7, int nArg8, float fArg9, float fArg10)
{
  unsigned int fld_14; // ecx

  if ( (*(uint32_t *)(this + 128) == 0 || sub_418E20(*(uint32_t *)(this + 132)) != 0) && *(uint8_t *)(this + 4) != 0 )
  {
    fld_14 = *(uint32_t *)(this + 20);
    if ( (fld_14 != 1 || *(uint32_t *)(this + 24) != 1) && pDwArg4[2] == 7 && (fld_14 != 1 || *(uint32_t *)(this + 24) != 1) )
    {
      if ( fArg9 == 4294967300.0 )
        fArg9 = (double)fld_14 * 0.5;
      if ( fArg10 == 4294967300.0 )
        fArg10 = (double)*(unsigned int *)(this + 24) * 0.5;
      if ( *(float *)&nArg7 == 0.0 )
        sub_410300(nArg2, this, nArg2, nArg3, pDwArg4, nArg8, nArg7, fArg5, fArg6, fArg9, fArg10);
      else
        sub_4105A0(nArg8, this, nArg2, nArg3, (int)pDwArg4, nArg8, *(float *)&nArg7, fArg5, fArg6, fArg9, fArg10);
    }
  }
}



// ------------------------------------------------------------
// 0x410C80 sub_410C80 —— 缩放块传输（7 号缩放 / 逐行拷贝）
//   格式 7 按目标矩形与源矩形之比（中心取源矩形半宽高）交 vt+20 缩放绘制；
//   8/16/14/15 且目标非本对象原表面时用 this+16 行表逐行 qmemcpy，否则裁剪后交 vt+112。
// ------------------------------------------------------------
void /*thiscall*/ sub_410C80(int this, int *pDwArg2, RECT *lprcSrc, const RECT *pArg4)
{
  int right; // eax
  int v6; // ebx
  int v7; // ecx
  int v8; // edx
  LONG v9; // eax
  double v10; // st7
  LONG bottom; // ecx
  int v12; // edx
  double v13; // st7
  int fld_1C; // eax
  double v15; // st7
  int v16; // eax
  int fld_20; // ecx
  int fld_7C; // eax
  int fld_1C2; // eax
  float v20; // ecx
  int fld_78; // eax
  int v23; // edi
  bool v24; // zf
  uint32_t *v25; // eax
  int v26; // edx
  struct tagRECT rcDst; // [esp+4h] [ebp-24h] BYREF
  float v28[2]; // [esp+14h] [ebp-14h] BYREF
  float v29; // [esp+1Ch] [ebp-Ch] BYREF
  float v30; // [esp+20h] [ebp-8h]
  int i; // [esp+24h] [ebp-4h]
  int v32; // [esp+30h] [ebp+8h]
  RECT *lprcSrca; // [esp+34h] [ebp+Ch]
  int v34; // [esp+38h] [ebp+10h]
  int v35; // [esp+38h] [ebp+10h]
  int v36; // [esp+38h] [ebp+10h]

  if ( (*(uint32_t *)(this + 128) == 0 || sub_418E20(*(uint32_t *)(this + 132)) != 0)
    && *(uint8_t *)(this + 4) != 0
    && (*(uint32_t *)(this + 20) != 1 || *(uint32_t *)(this + 24) != 1) )
  {
    right = pArg4->right;
    if ( right == 7 )
    {
      v6 = *pDwArg2;
      v7 = pDwArg2[2];
      i = *pDwArg2;
      if ( i != v7 )
      {
        v8 = pDwArg2[3];
        v32 = pDwArg2[1];
        if ( v32 != v8 )
        {
          v9 = lprcSrc->right;
          v10 = (double)(v7 - v6) / (double)(v9 - lprcSrc->left);
          bottom = lprcSrc->bottom;
          v34 = v8 - v32;
          v12 = bottom - lprcSrc->top;
          *(float *)&rcDst.right = v10;
          v13 = (double)v34;
          v35 = v9 >> 1;
          fld_1C = *(uint32_t *)(this + 28);
          *(float *)&rcDst.bottom = v13 / (double)v12;
          v15 = (double)v35;
          v36 = bottom >> 1;
          v16 = i + fld_1C;
          fld_20 = *(uint32_t *)(this + 32);
          v28[0] = v15;
          v28[1] = (float)v36;
          v29 = (float)v16;
          v30 = (float)(v32 + fld_20);
          sub_404F40(v16, 4u);
          fld_7C = (*(int (/*stdcall*/ **)(uint32_t, uint32_t, RECT *, LONG *, float *, uint32_t, float *, int))(**(uint32_t **)(this + 124) + 20))(
                  *(uint32_t *)(this + 124),
                  *(uint32_t *)(this + 112),
                  lprcSrc,
                  &rcDst.right,
                  v28,
                  0,
                  &v29,
                  -1);
LABEL_26:
          sub_404F80(fld_7C, 4u, 0);
        }
      }
    }
    else if ( right == 8 || right == 16 || right == 14 || right == 15 )
    {
      if ( pArg4[7].right != *(uint32_t *)(this + 120) )
      {
        sub_404F40(right, 4u);
        v23 = lprcSrc->right - lprcSrc->left;
        v24 = lprcSrc->bottom == lprcSrc->top;
        LODWORD(v30) = lprcSrc->bottom - lprcSrc->top;
        fld_7C = 0;
        lprcSrca = nullptr;
        if ( !v24 )
        {
          do
          {
            i = *(uint32_t *)(*(uint32_t *)(this + 16) + 4 * (fld_7C + lprcSrc->top)) + 4 * lprcSrc->left;
            v25 = (uint32_t *)(*(uint32_t *)(pArg4[1].left + 4 * ((uint32_t)lprcSrca + pDwArg2[1])) + 4 * *pDwArg2);
            if ( v23 != 0 )
            {
              v26 = i - (uint32_t)v25;
              for ( i = v23; i != 0; --i )
              {
                *v25 = *(uint32_t *)((char *)v25 + v26);
                ++v25;
              }
            }
            fld_7C = (int)&lprcSrca->left + 1;
            lprcSrca = (RECT *)((char *)lprcSrca + 1);
          }
          while ( (unsigned int)lprcSrca < LODWORD(v30) );
        }
        goto LABEL_26;
      }
      CopyRect(&rcDst, lprcSrc);
      IntersectRect(&rcDst, &rcDst, (const RECT *)(this + 48));
      OffsetRect(&rcDst, *pDwArg2 - lprcSrc->left, pDwArg2[1] - lprcSrc->top);
      if ( IntersectRect(&rcDst, &rcDst, pArg4 + 3) )
      {
        OffsetRect(&rcDst, lprcSrc->left - *pDwArg2, lprcSrc->top - pDwArg2[1]);
        fld_1C2 = *pDwArg2 + *(uint32_t *)(this + 28);
        LODWORD(v20) = pDwArg2[1] + *(uint32_t *)(this + 32);
        v29 = *(float *)&fld_1C2;
        v30 = v20;
        if ( fld_1C2 < 0 )
          v29 = 0.0;
        if ( v20 < 0.0 )
          v30 = 0.0;
        sub_404F40(fld_1C2, 4u);
        fld_78 = (*(int (/*stdcall*/ **)(uint32_t, uint32_t, struct tagRECT *, int, LONG, float *))(**(uint32_t **)(this + 120)
                                                                                         + 112))(
                *(uint32_t *)(this + 120),
                *(uint32_t *)(this + 116),
                &rcDst,
                1,
                pArg4[7].top,
                &v29);
        sub_404F80(fld_78, 4u, 0);
      }
    }
  }
}


// ------------------------------------------------------------
// 0x410F30 sub_410F30 —— 缩放绘制（中心取 this+96.100 半值）
//   格式 7 专属：缩放比 = 目标/源矩形之比，中心 = (this+96>>1, this+100>>1)，交 vt+20；
//   nArg6 颜色同经 FF00FF00 通道重排。
// ------------------------------------------------------------
void /*thiscall*/ sub_410F30(int this, int *pDwArg2, uint32_t *pArg3, int pArg4, int nArg5, int nArg6)
{
  int v7; // eax
  int v8; // ecx
  int v9; // edx
  int v10; // edi
  double v11; // st7
  int fld_64; // edi
  double v13; // st7
  int fld_1C; // edi
  int fld_20; // ecx
  int fld_7C; // ecx
  int fld_70; // eax
  float v18[2]; // [esp+4h] [ebp-18h] BYREF
  float v19[2]; // [esp+Ch] [ebp-10h] BYREF
  float v20[2]; // [esp+14h] [ebp-8h] BYREF
  int v21; // [esp+2Ch] [ebp+10h]
  int fld_60; // [esp+2Ch] [ebp+10h]
  int fld_642; // [esp+2Ch] [ebp+10h]
  int v24; // [esp+2Ch] [ebp+10h]

  if ( (*(uint32_t *)(this + 128) == 0 || sub_418E20(*(uint32_t *)(this + 132)) != 0)
    && *(uint8_t *)(this + 4) != 0
    && (*(uint32_t *)(this + 20) != 1 || *(uint32_t *)(this + 24) != 1)
    && *(uint32_t *)(pArg4 + 8) == 7
    && *pDwArg2 != pDwArg2[2] )
  {
    v7 = pDwArg2[1];
    if ( v7 != pDwArg2[3] )
    {
      sub_404F40(v7, 4u);
      v8 = *pDwArg2;
      v9 = pDwArg2[1];
      v21 = pDwArg2[3] - v9;
      v10 = pArg3[3] - pArg3[1];
      v18[0] = (double)(pDwArg2[2] - *pDwArg2) / (double)(pArg3[2] - *pArg3);
      v11 = (double)v21 / (double)v10;
      fld_60 = *(int *)(this + 96) >> 1;
      fld_64 = *(int *)(this + 100) >> 1;
      v18[1] = v11;
      v13 = (double)fld_60;
      fld_642 = fld_64;
      fld_1C = v8 + *(uint32_t *)(this + 28);
      fld_20 = *(uint32_t *)(this + 32);
      v19[0] = v13;
      v19[1] = (float)fld_642;
      v24 = v9 + fld_20;
      fld_7C = *(uint32_t *)(this + 124);
      v20[0] = (float)fld_1C;
      v20[1] = (float)v24;
      fld_70 = (*(int (/*stdcall*/ **)(int, uint32_t, uint32_t *, float *, float *, int, float *, unsigned int))(*(uint32_t *)fld_7C + 20))(
              fld_7C,
              *(uint32_t *)(this + 112),
              pArg3,
              v18,
              v19,
              nArg5,
              v20,
              nArg6 & 0xFF00FF00 | ((uint8_t)nArg6 << 16) | BYTE2(nArg6));
      sub_404F80(fld_70, 4u, 0);
    }
  }
}



// ------------------------------------------------------------
// 0x411080 sub_411080 —— 缩放绘制（动态 alpha 掩码变体）
//   与 ·sub_410F30 同构（差异：pszArg7 非零时颜色掩码取 0x8000FF00，即动态 alpha 开关）【推断】。
// ------------------------------------------------------------
void /*thiscall*/ sub_411080(int this, int *pDwArg2, uint32_t *pArg3, int pArg4, int nArg5, int nArg6, char pszArg7)
{
  int v8; // ecx
  int v9; // ebx
  int v10; // edx
  int v11; // eax
  double v12; // st7
  int v13; // eax
  int fld_60; // ecx
  double v15; // st7
  int fld_64; // eax
  double v17; // st7
  int fld_1C; // ecx
  double v19; // st7
  int fld_20; // eax
  unsigned int v21; // eax
  int v22; // ebx
  int fld_7C; // eax
  float v24[2]; // [esp+4h] [ebp-18h] BYREF
  float v25[2]; // [esp+Ch] [ebp-10h] BYREF
  float v26[2]; // [esp+14h] [ebp-8h] BYREF
  int v27; // [esp+2Ch] [ebp+10h]
  int v28; // [esp+2Ch] [ebp+10h]
  int fld_602; // [esp+2Ch] [ebp+10h]
  int fld_642; // [esp+2Ch] [ebp+10h]

  if ( (*(uint32_t *)(this + 128) == 0 || sub_418E20(*(uint32_t *)(this + 132)) != 0)
    && *(uint8_t *)(this + 4) != 0
    && (*(uint32_t *)(this + 20) != 1 || *(uint32_t *)(this + 24) != 1)
    && *(uint32_t *)(pArg4 + 8) == 7 )
  {
    v8 = pDwArg2[2];
    v9 = *pDwArg2;
    if ( *pDwArg2 != v8 )
    {
      v10 = pDwArg2[1];
      v11 = pDwArg2[3];
      if ( v10 != v11 )
      {
        v12 = (double)(v8 - v9) / (double)(pArg3[2] - *pArg3);
        v27 = v11 - v10;
        v13 = pArg3[3] - pArg3[1];
        fld_60 = *(int *)(this + 96) >> 1;
        v24[0] = v12;
        v15 = (double)v27;
        v28 = v13;
        fld_64 = *(int *)(this + 100) >> 1;
        v17 = v15 / (double)v28;
        fld_602 = fld_60;
        fld_1C = v9 + *(uint32_t *)(this + 28);
        v24[1] = v17;
        v19 = (double)fld_602;
        fld_642 = fld_64;
        fld_20 = v10 + *(uint32_t *)(this + 32);
        v25[0] = v19;
        v25[1] = (float)fld_642;
        v26[0] = (float)fld_1C;
        v26[1] = (float)fld_20;
        if ( pszArg7 != 0 )
          v21 = nArg6 & 0x8000FF00;
        else
          v21 = nArg6 & 0xFF00FF00;
        v22 = v21 | ((uint8_t)nArg6 << 16) | BYTE2(nArg6);
        sub_404F40(v21, 4u);
        fld_7C = (*(int (/*stdcall*/ **)(uint32_t, uint32_t, uint32_t *, float *, float *, int, float *, int))(**(uint32_t **)(this + 124)
                                                                                                  + 20))(
                *(uint32_t *)(this + 124),
                *(uint32_t *)(this + 112),
                pArg3,
                v24,
                v25,
                nArg5,
                v26,
                v22);
        sub_404F80(fld_7C, 4u, 0);
      }
    }
  }
}



// ============================================================
// SECTION 0x4111E0 — 屏幕矩形/视口辅助
// ============================================================
// ------------------------------------------------------------
// 0x4111E0 sub_4111E0 —— 向上取 2 的幂（纹理对齐）
//   求不小于 nArg1 的最小 2 的幂（倍增 2^v1）；v1 达 100 仍不足返回 -1。
//   供 ·sub_411240 做表面尺寸 pow2 对齐【推断】。
// ------------------------------------------------------------
int /*stdcall*/ sub_4111E0(int nArg1)  // 【屏幕矩形/视口辅助】
{
  int v1; // esi
  int v2; // edx
  unsigned int v3; // eax
  int v4; // ecx
  int result; // eax

  v1 = 0;
  while ( 1 )
  {
    v2 = 2;
    v3 = v1;
    if ( v1 < 0 )
      v3 = -v1;
    v4 = 1;
    while ( 1 )
    {
      if ( (v3 & 1) != 0 )
        v4 *= v2;
      v3 >>= 1;
      if ( v3 == 0 )
        break;
      v2 *= v2;
    }
    result = v1 >= 0 ? v4 : 1 / v4;
    if ( result >= nArg1 )
      break;
    if ( ++v1 >= 100 )
      return -1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x411240 sub_411240 —— D3D 表面创建与行表建立
//   置尺寸 this+20/24 并 SetRect；查表面能力（v18[60]&2 / v18[61]&1 或 nArg6==26）决定是否向上取 2 的幂。
//   建表面 vt+80 → 取 DC vt+60 → 取像素 vt+64 → 释放 DC vt+68 → 建行表 vt+172，
//   sub_405060(1, 尺寸, 0) 计入内存统计【推断】；任一步失败调 vt+20 销毁重来。
// ------------------------------------------------------------
int /*userpurge*/ sub_411240@<eax>(int *pDwArg1@<ecx>, int nArg2@<ebx>, int nArg3@<edi>, int xRight, int yBottom, int nArg6)
{
  int v8; // edx
  int v9; // eax
  int v10; // ebx
  int v11; // eax
  uint32_t *v12; // edi
  int v13; // ebx
  int v14; // ecx
  int v15; // eax
  int v16; // edi
  uint8_t v18[212]; // [esp+4h] [ebp-D4h] BYREF
  int xRighta; // [esp+E0h] [ebp+8h]

  if ( *((uint8_t *)pDwArg1 + 4) != 0 )
    return -2147483646;
  v8 = pDwArg1[9];
  *((uint8_t *)pDwArg1 + 4) = 1;
  pDwArg1[5] = xRight;
  pDwArg1[6] = yBottom;
  if ( v8 == 0 )
    pDwArg1[9] = xRight;
  if ( pDwArg1[10] == 0 )
    pDwArg1[10] = yBottom;
  SetRect((LPRECT)(pDwArg1 + 22), 0, 0, xRight, yBottom);
  SetRect((LPRECT)pDwArg1 + 3, 0, 0, pDwArg1[5] + pDwArg1[7], pDwArg1[6] + pDwArg1[8]);
  v9 = pDwArg1[5];
  *((uint8_t *)pDwArg1 + 76) = 0;
  if ( v9 == 0 )
    pDwArg1[5] = 1;
  if ( pDwArg1[6] == 0 )
    pDwArg1[6] = 1;
  v10 = pDwArg1[5];
  xRighta = pDwArg1[6];
  (*(void (/*stdcall*/ **)(int, uint8_t *, int, int))(*(uint32_t *)pDwArg1[30] + 28))(pDwArg1[30], v18, nArg3, nArg2);
  if ( (v18[60] & 2) != 0 && (v18[61] & 1) == 0 || nArg6 == 26 )
  {
    v10 = sub_4111E0(pDwArg1[5]);  // 【屏幕矩形/视口辅助】
    v11 = sub_4111E0(pDwArg1[6]);  // 【屏幕矩形/视口辅助】
  }
  else
  {
    if ( (v10 & 1) != 0 )
      ++v10;
    if ( (xRighta & 1) == 0 )
      goto LABEL_20;
    v11 = xRighta + 1;
  }
  xRighta = v11;
LABEL_20:
  v12 = pDwArg1 + 28;
  v13 = (*(int (/*stdcall*/ **)(int, int, int, int, uint32_t, int))(*(uint32_t *)pDwArg1[30] + 80))(pDwArg1[30], v10, xRighta, 1, 0, nArg6);
  if ( v13 >= 0 && (v13 = (*(int (/*stdcall*/ **)(uint32_t, uint32_t, int *))(*(uint32_t *)*v12 + 60))(*v12, 0, pDwArg1 + 29)) >= 0 )
  {
    (*(void (/*stdcall*/ **)(uint32_t, uint32_t, int *, uint32_t, uint32_t))(*(uint32_t *)*v12 + 64))(*v12, 0, pDwArg1 + 26, 0, 0);
    (*(void (/*stdcall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*v12 + 68))(*v12, 0);
    v14 = pDwArg1[26];
    pDwArg1[3] = pDwArg1[27];
    v15 = *pDwArg1;
    pDwArg1[20] = v14;
    pDwArg1[21] = xRighta;
    v16 = (*(int (/*thiscall*/ **)(int *))(v15 + 172))(pDwArg1);
    if ( v16 >= 0 )
    {
      sub_405060(1u, pDwArg1[20] * pDwArg1[21] + 4 * pDwArg1[6], 0);
      return 1;
    }
    else
    {
      (*(void (/*thiscall*/ **)(int *))(*pDwArg1 + 20))(pDwArg1);
      return v16;
    }
  }
  else
  {
    (*(void (/*thiscall*/ **)(int *))(*pDwArg1 + 20))(pDwArg1);
    return v13;
  }
}



// ------------------------------------------------------------
// 0x4113F0 sub_4113F0 —— 指定色转透明（32bpp）
//   vt+84/88 锁定内逐像素：匹配重排色（FF00FF00）者清 0；记录 this+17 = nArg2 为当前透明色。
// ------------------------------------------------------------
int /*thiscall*/ sub_4113F0(uint32_t *this, int nArg2)
{
  unsigned int i; // edi
  int fld_e4; // ecx
  unsigned int j; // eax
  int result; // eax

  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 84))(this);
  for ( i = 0; i < *(this + 6); ++i )
  {
    fld_e4 = *(uint32_t *)(*(this + 4) + 4 * i);
    for ( j = 0; j < *(this + 5); ++j )
    {
      if ( *(uint32_t *)(fld_e4 + 4 * j) == (nArg2 & 0xFF00FF00 | ((uint8_t)nArg2 << 16) | BYTE2(nArg2)) )
        *(uint32_t *)(fld_e4 + 4 * j) = 0;
    }
  }
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 88))(this);
  *(this + 17) = nArg2;
  return result;
}



// ------------------------------------------------------------
// 0x411460 sub_411460 —— 整幅填充（32bpp）
//   与 ·sub_4113F0 同族（差异：不做匹配判定，整幅写为重排色 nArg2），同样记录 this+17。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_411460(unsigned int *this, int nArg2)
{
  unsigned int result; // eax
  unsigned int v3; // ebx
  unsigned int fld_e5; // edx
  int fld_e4; // esi
  unsigned int i; // eax

  result = *(this + 3);
  if ( result != 0 )
  {
    result = *(this + 6);
    v3 = 0;
    if ( result != 0 )
    {
      fld_e5 = *(this + 5);
      do
      {
        fld_e4 = *(uint32_t *)(*(this + 4) + 4 * v3);
        for ( i = 0; i < fld_e5; ++i )
        {
          *(uint32_t *)(fld_e4 + 4 * i) = nArg2 & 0xFF00FF00 | ((uint8_t)nArg2 << 16) | BYTE2(nArg2);
          fld_e5 = *(this + 5);
        }
        result = *(this + 6);
        ++v3;
      }
      while ( v3 < result );
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4114C0 sub_4114C0 —— 单像素取色（32bpp）
//   越界由 sub_40F530 判定返回 0；否则读该像素按 FF00FF00 通道重排返回。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4114C0(uint32_t *this, int nArg2, int nArg3)
{
  int fld_e4; // edx

  if ( sub_40F530(nArg2, nArg3, this + 12) )
    return 0;
  fld_e4 = *(uint32_t *)(*(this + 4) + 4 * nArg3) + 4 * nArg2;
  return *(uint32_t *)fld_e4 & 0xFF00FF00 | *(uint8_t *)(fld_e4 + 2) | ((uint8_t)*(uint32_t *)fld_e4 << 16);
}



// ------------------------------------------------------------
// 0x411510 sub_411510 —— 水平线段填充（32bpp）
//   nArg3 为行（限 this[13..15]），起 x = nArg2、宽 nArg4；负起点与右越界裁剪后 memset32 写入。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_411510(int *this, int nArg2, signed int nArg3, signed int nArg4, int nArg5)
{
  unsigned int result; // eax
  signed int nArg42; // ecx
  int fld_e14; // eax
  void *fld_e4; // edi
  int nArg22; // [esp+4h] [ebp-4h]

  result = nArg3;
  if ( nArg3 >= *(this + 13) && nArg3 < *(this + 15) )
  {
    nArg22 = 0;
    nArg42 = nArg4;
    if ( nArg2 < 0 )
      nArg42 = nArg2 + nArg4;
    else
      nArg22 = nArg2;
    fld_e14 = *(this + 14);
    if ( nArg2 + nArg4 >= fld_e14 )
      nArg42 += fld_e14 - nArg2 - nArg4;
    result = nArg5 & 0xFF00FF00 | ((uint8_t)nArg5 << 16) | BYTE2(nArg5);
    fld_e4 = (void *)(*(uint32_t *)(*(this + 4) + 4 * nArg3) + 4 * nArg22);
    if ( nArg42 > 0 )
      memset32(fld_e4, result, nArg42);
  }
  return result;
}



// ------------------------------------------------------------
// 0x411590 sub_411590 —— 图像存盘（32bpp 序列化）
//   fwrite 封装 sub_66BC25：写标志 5、宽高 this+5/6、字节数 4*w*h、this+7..10 四字段，再逐行写 4*w。
// ------------------------------------------------------------
int /*thiscall*/ sub_411590(uint32_t *this, FILE *Stream)
{
  int fld_e6; // eax
  uint32_t *pThis_6; // ebx
  size_t fld_e5; // eax
  size_t fld_e52; // [esp+8h] [ebp-Ch]
  int v9; // [esp+Ch] [ebp-8h] BYREF
  int Buffer; // [esp+10h] [ebp-4h] BYREF
  FILE *Streama; // [esp+1Ch] [ebp+8h]

  if ( Stream == nullptr )
    return 0x80000000;
  fld_e6 = *(this + 6) * *(this + 5);
  pThis_6 = this + 6;
  Buffer = 5;
  v9 = 4 * fld_e6;
  sub_66BC25(&Buffer, 4u, 1u, Stream);
  sub_66BC25(this + 5, 4u, 1u, Stream);
  sub_66BC25(this + 6, 4u, 1u, Stream);
  sub_66BC25(&v9, 4u, 1u, Stream);
  sub_66BC25(this + 7, 4u, 1u, Stream);
  sub_66BC25(this + 8, 4u, 1u, Stream);
  sub_66BC25(this + 9, 4u, 1u, Stream);
  sub_66BC25(this + 10, 4u, 1u, Stream);
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 84))(this);
  fld_e5 = 4 * *(this + 5);
  fld_e52 = fld_e5;
  Streama = nullptr;
  if ( *pThis_6 != 0 )
  {
    while ( 1 )
    {
      sub_66BC25(*(void **)(*(this + 4) + 4 * (uint32_t)Streama), fld_e5, 1u, Stream);
      Streama = (FILE *)((char *)Streama + 1);
      if ( (unsigned int)Streama >= *pThis_6 )
        break;
      fld_e5 = fld_e52;
    }
  }
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 88))(this);
  return 1;
}



// ============================================================
// SECTION 0x4116A0 — ★ IMG 图像块解码族（0x4116A0/0x411B30/0x412150/0x412700 —— 均调 0x652E00 zlib uncompress：IMG 内嵌图像数据为 zlib 压缩流）
// ============================================================
// ------------------------------------------------------------
// 0x4116A0 sub_4116A0
// ------------------------------------------------------------
// 【解读】
//   ★ IMG 图像块解码（202 行）: 读块头（sub_66BD5A fread）→
//     sub_652E00 = zlib uncompress（★ IMG 内嵌图像数据是 zlib 压缩流，zlib_inflate.cpp 0x65 区）→
//     解码结果建图像对象（new + sub_652E00 失败路径 j_j__free）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4116A0(int *this, FILE *Stream)
{
  FILE *v2; // edi
  unsigned int v3; // ebx
  int result; // eax
  int fld_e6; // ecx
  size_t fld_e5; // eax
  int fld_e66; // ecx
  size_t fld_e53; // eax
  void *pMem; // ebx
  int fld_e62; // eax
  int fld_e20; // eax
  size_t fld_e63; // ecx
  int v14; // edx
  int *pThis; // ecx
  void *pMem2; // eax
  int fld_e3; // eax
  int fld_e65; // ecx
  size_t fld_e52; // eax
  int fld_e64; // [esp+Ch] [ebp-18h] BYREF
  int Buffer; // [esp+10h] [ebp-14h] BYREF
  size_t fld_e54; // [esp+14h] [ebp-10h]
  size_t ElementSize; // [esp+18h] [ebp-Ch] BYREF
  int v24; // [esp+1Ch] [ebp-8h] BYREF
  int v25; // [esp+20h] [ebp-4h] BYREF

  v2 = Stream;
  v3 = 0;
  if ( Stream == nullptr )
    return 0x80000000;
  Buffer = 0;
  v25 = 0;
  Stream = nullptr;
  v24 = 0;
  sub_66BD5A(&Buffer, 4u, 1u, v2);  // 【fread封装】
  if ( Buffer == 1 )
  {
    sub_66BD5A(&v25, 4u, 1u, v2);  // 【fread封装】
    sub_66BD5A(&Stream, 4u, 1u, v2);  // 【fread封装】
    sub_66BD5A(&v24, 4u, 1u, v2);  // 【fread封装】
    result = (*(int (/*thiscall*/ **)(int *, int, FILE *))(*this + 12))(this, v25, Stream);
    if ( result >= 0 )
    {
      (*(void (/*thiscall*/ **)(int *))(*this + 84))(this);
      fld_e6 = *(this + 6);
      fld_e5 = 4 * *(this + 5);
      fld_e54 = fld_e5;
      if ( fld_e6 != 0 )
      {
        while ( 1 )
        {
          sub_66BD5A(*(void **)(*(this + 4) + 4 * v3++), fld_e5, 1u, v2);  // 【fread封装】
          if ( v3 >= *(this + 6) )
            break;
          fld_e5 = fld_e54;
        }
      }
LABEL_40:
      (*(void (/*thiscall*/ **)(int *))(*this + 88))(this);
      return 1;
    }
    return result;
  }
  if ( Buffer != 2 )
  {
    switch ( Buffer )
    {
      case 3:
        sub_66BD5A(&v25, 4u, 1u, v2);  // 【fread封装】
        sub_66BD5A(&Stream, 4u, 1u, v2);  // 【fread封装】
        sub_66BD5A(&v24, 4u, 1u, v2);  // 【fread封装】
        sub_66BD5A(this + 7, 4u, 1u, v2);  // 【fread封装】
        sub_66BD5A(this + 8, 4u, 1u, v2);  // 【fread封装】
        result = (*(int (/*thiscall*/ **)(int *, int, FILE *))(*this + 12))(this, v25, Stream);
        if ( result < 0 )
          return result;
        pMem = operator new(2 * *(this + 20) + 12);
        if ( pMem != nullptr )
        {
          (*(void (/*thiscall*/ **)(int *))(*this + 84))(this);
          fld_e62 = *(this + 6);
          fld_e54 = 0;
          if ( fld_e62 != 0 )
          {
            while ( 1 )
            {
              fld_e20 = *(this + 20);
              ElementSize = 0;
              fld_e64 = fld_e20;
              sub_66BD5A(&ElementSize, 4u, 1u, v2);  // 【fread封装】
              sub_66BD5A(pMem, ElementSize, 1u, v2);  // 【fread封装】
              if ( sub_652E00(*(uint32_t *)(*(this + 4) + 4 * fld_e54), &fld_e64, pMem, ElementSize) != 0 )
                break;
              fld_e63 = *(this + 6);
              if ( ++fld_e54 >= fld_e63 )
                goto LABEL_22;
            }
            v14 = *this;
            pThis = this;
            goto LABEL_24;
          }
          goto LABEL_22;
        }
        break;
      case 4:
        sub_66BD5A(&v25, 4u, 1u, v2);  // 【fread封装】
        sub_66BD5A(&Stream, 4u, 1u, v2);  // 【fread封装】
        sub_66BD5A(&v24, 4u, 1u, v2);  // 【fread封装】
        sub_66BD5A(this + 7, 4u, 1u, v2);  // 【fread封装】
        sub_66BD5A(this + 8, 4u, 1u, v2);  // 【fread封装】
        result = (*(int (/*thiscall*/ **)(int *, int, FILE *))(*this + 12))(this, v25, Stream);
        if ( result < 0 )
          return result;
        ElementSize = 0;
        sub_66BD5A(&ElementSize, 4u, 1u, v2);  // 【fread封装】
        pMem2 = operator new(ElementSize);
        pMem = pMem2;
        if ( pMem2 != nullptr )
        {
          sub_66BD5A(pMem2, ElementSize, 1u, v2);  // 【fread封装】
          (*(void (/*thiscall*/ **)(int *))(*this + 84))(this);
          fld_e64 = *(this + 6) * *(this + 20);
          fld_e3 = sub_652E00(*(this + 3), &fld_e64, pMem, ElementSize);
          pThis = this;
          if ( fld_e3 != 0 )
          {
            v14 = *this;
LABEL_24:
            (*(void (/*fastcall*/ **)(int *))(v14 + 88))(pThis);
            j_j__free(pMem);
            return 0x80000000;
          }
LABEL_22:
          (*(void (/*thiscall*/ **)(int *))(*this + 88))(this);
          j_j__free(pMem);
          return 1;
        }
        break;
      case 5:
        sub_66BD5A(&v25, 4u, 1u, v2);  // 【fread封装】
        sub_66BD5A(&Stream, 4u, 1u, v2);  // 【fread封装】
        sub_66BD5A(&v24, 4u, 1u, v2);  // 【fread封装】
        sub_66BD5A(this + 7, 4u, 1u, v2);  // 【fread封装】
        sub_66BD5A(this + 8, 4u, 1u, v2);  // 【fread封装】
        sub_66BD5A(this + 9, 4u, 1u, v2);  // 【fread封装】
        sub_66BD5A(this + 10, 4u, 1u, v2);  // 【fread封装】
        result = (*(int (/*thiscall*/ **)(int *, int, FILE *))(*this + 12))(this, v25, Stream);
        if ( result >= 0 )
        {
          (*(void (/*thiscall*/ **)(int *))(*this + 84))(this);
          fld_e65 = *(this + 6);
          fld_e52 = 4 * *(this + 5);
          fld_e64 = fld_e52;
          if ( fld_e65 != 0 )
          {
            while ( 1 )
            {
              sub_66BD5A(*(void **)(*(this + 4) + 4 * v3++), fld_e52, 1u, v2);  // 【fread封装】
              if ( v3 >= *(this + 6) )
                break;
              fld_e52 = fld_e64;
            }
          }
          goto LABEL_40;
        }
        return result;
      default:
        return 0x80000000;
    }
    return -2147483640;
  }
  sub_66BD5A(&v25, 4u, 1u, v2);  // 【fread封装】
  sub_66BD5A(&Stream, 4u, 1u, v2);  // 【fread封装】
  sub_66BD5A(&v24, 4u, 1u, v2);  // 【fread封装】
  sub_66BD5A(this + 7, 4u, 1u, v2);  // 【fread封装】
  sub_66BD5A(this + 8, 4u, 1u, v2);  // 【fread封装】
  result = (*(int (/*thiscall*/ **)(int *, int, FILE *))(*this + 12))(this, v25, Stream);
  if ( result >= 0 )
  {
    (*(void (/*thiscall*/ **)(int *))(*this + 84))(this);
    fld_e66 = *(this + 6);
    fld_e53 = 4 * *(this + 5);
    fld_e54 = fld_e53;
    if ( fld_e66 != 0 )
    {
      while ( 1 )
      {
        sub_66BD5A(*(void **)(*(this + 4) + 4 * v3++), fld_e53, 1u, v2);  // 【fread封装】
        if ( v3 >= *(this + 6) )
          break;
        fld_e53 = fld_e54;
      }
    }
    goto LABEL_40;
  }
  return result;
}


// ------------------------------------------------------------
// 0x411B30 sub_411B30
// ------------------------------------------------------------
// 【解读】
//   ★ 同族解码变体（279 行，同样调 0x652E00 uncompress）—— 不同位深/格式分支【推断】。
// ------------------------------------------------------------
int /*thiscall*/ sub_411B30(uint32_t *this, int **pDwArg2)
{
  int v2; // eax
  uint32_t *pThis; // edi
  uint32_t *v4; // ebx
  int v5; // eax
  int v6; // ecx
  char *v7; // ebx
  int result; // eax
  int v9; // edx
  void *Block2; // ecx
  unsigned int v11; // eax
  int v12; // eax
  int v13; // ecx
  uint32_t *v14; // ebx
  int v15; // edx
  int v16; // edx
  void *Block4; // ecx
  unsigned int v18; // eax
  int v19; // eax
  int v20; // ecx
  uint32_t *v21; // ebx
  int v22; // edx
  int *v23; // ebx
  void *pMem; // esi
  int v25; // eax
  size_t v26; // ecx
  char *v27; // edi
  int v28; // eax
  int v29; // edx
  unsigned int v30; // ecx
  char *v31; // ebx
  char *v32; // edi
  char *v33; // esi
  int v34; // edx
  void *Block3; // edi
  uint32_t *pThis22; // esi
  bool v37; // cf
  int v38; // eax
  int v39; // ecx
  uint32_t *v40; // ebx
  int v41; // edx
  size_t *v42; // ebx
  char *v43; // ebx
  char *pMem2; // eax
  uint32_t *pThis23; // esi
  int *v46; // ebx
  int v47; // eax
  int v48; // ecx
  uint32_t *v49; // ebx
  int v50; // edx
  int v51; // edx
  int v52; // edx
  int v53; // edx
  unsigned int v54; // ecx
  unsigned int v55; // eax
  int v56; // [esp-10h] [ebp-2Ch]
  size_t v57; // [esp+Ch] [ebp-10h] BYREF
  void *Block; // [esp+10h] [ebp-Ch]
  int v59; // [esp+14h] [ebp-8h] BYREF
  uint32_t *pThis2; // [esp+18h] [ebp-4h]

  v2 = **pDwArg2;
  pThis = this;
  v4 = *pDwArg2 + 1;
  pThis2 = this;
  if ( v2 == 1 )
  {
    v5 = *v4;
    v6 = v4[1];
    v7 = (char *)(v4 + 3);
    result = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*pThis + 12))(pThis, v5, v6);
    if ( result >= 0 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *))(*pThis + 84))(pThis);
      v9 = pThis[6];
      Block2 = (void *)(4 * pThis[5]);
      v11 = 0;
      Block = Block2;
      if ( v9 != 0 )
      {
        do
        {
          qmemcpy(*(void **)(pThis[4] + 4 * v11), v7, (unsigned int)Block2);
          Block2 = Block;
          v7 = &v7[(uint32_t)Block];
          ++v11;
          pThis = pThis2;
        }
        while ( v11 < pThis2[6] );
      }
LABEL_34:
      (*(void (/*thiscall*/ **)(uint32_t *))(*pThis + 88))(pThis);
      *pDwArg2 = (int *)v7;
      return 1;
    }
    return result;
  }
  if ( v2 != 2 )
  {
    switch ( v2 )
    {
      case 3:
        v19 = *v4;
        v20 = v4[1];
        v21 = v4 + 1;
        v22 = v21[2];
        v21 += 2;
        pThis[7] = v22;
        pThis[8] = v21[1];
        v23 = v21 + 2;
        result = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*pThis + 12))(pThis, v19, v20);
        if ( result < 0 )
          return result;
        pMem = operator new(2 * pThis[20] + 12);
        Block = pMem;
        if ( pMem != nullptr )
        {
          (*(void (/*thiscall*/ **)(uint32_t *))(*pThis + 84))(pThis);
          v25 = pThis[6];
          v59 = 0;
          if ( v25 == 0 )
          {
LABEL_18:
            (*(void (/*thiscall*/ **)(uint32_t *))(*pThis + 88))(pThis);
            j_j__free(pMem);
            *pDwArg2 = v23;
            return 1;
          }
          while ( 1 )
          {
            v26 = pThis[20];
            v27 = (char *)Block;
            v57 = v26;
            v28 = *v23;
            v29 = *v23;
            v30 = (unsigned int)*v23 >> 2;
            v31 = (char *)(v23 + 1);
            qmemcpy(Block, v31, 4 * v30);
            v33 = &v31[4 * v30];
            v32 = &v27[4 * v30];
            LOBYTE(v30) = v29;
            v34 = v59;
            qmemcpy(v32, v33, v30 & 3);
            Block3 = Block;
            pThis22 = pThis2;
            v23 = (int *)&v31[v28];
            if ( sub_652E00(*(uint32_t *)(pThis2[4] + 4 * v34), (int *)&v57, (uint8_t *)Block, v28) != 0 )
              break;
            v37 = (unsigned int)++v59 < pThis22[6];
            pThis = pThis22;
            if ( !v37 )
            {
              pMem = Block;
              goto LABEL_18;
            }
          }
          (*(void (/*thiscall*/ **)(uint32_t *))(*pThis22 + 88))(pThis22);
LABEL_20:
          j_j__free(Block3);
          return 0x80000000;
        }
        break;
      case 4:
        v38 = *v4;
        v39 = v4[1];
        v40 = v4 + 1;
        v41 = v40[2];
        v40 += 2;
        pThis[7] = v41;
        pThis[8] = v40[1];
        v42 = v40 + 2;
        result = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*pThis + 12))(pThis, v38, v39);
        if ( result < 0 )
          return result;
        v57 = *v42;
        v43 = (char *)(v42 + 1);
        pMem2 = (char *)operator new(v57);
        Block = pMem2;
        if ( pMem2 != nullptr )
        {
          qmemcpy(pMem2, v43, v57);
          pThis23 = pThis2;
          v46 = (int *)&v43[v57];
          (*(void (/*thiscall*/ **)(uint32_t *))(*pThis2 + 84))(pThis2);
          Block3 = Block;
          v56 = pThis2[3];
          v59 = pThis23[6] * pThis23[20];
          if ( sub_652E00(v56, &v59, (uint8_t *)Block, v57) == 0 )
          {
            (*(void (/*thiscall*/ **)(uint32_t *))(*pThis23 + 88))(pThis23);
            j_j__free(Block);
            *pDwArg2 = v46;
            return 1;
          }
          (*(void (/*thiscall*/ **)(uint32_t *))(*pThis23 + 88))(pThis23);
          goto LABEL_20;
        }
        break;
      case 5:
        v47 = *v4;
        v48 = v4[1];
        v49 = v4 + 1;
        v50 = v49[2];
        v49 += 2;
        pThis[7] = v50;
        v51 = v49[1];
        ++v49;
        pThis[8] = v51;
        v52 = v49[1];
        ++v49;
        pThis[9] = v52;
        pThis[10] = v49[1];
        v7 = (char *)(v49 + 2);
        result = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*pThis + 12))(pThis, v47, v48);
        if ( result >= 0 )
        {
          (*(void (/*thiscall*/ **)(uint32_t *))(*pThis + 84))(pThis);
          v53 = pThis[6];
          v54 = 4 * pThis[5];
          v55 = 0;
          v57 = v54;
          if ( v53 != 0 )
          {
            do
            {
              qmemcpy(*(void **)(pThis[4] + 4 * v55), v7, v54);
              v54 = v57;
              v7 += v57;
              ++v55;
              pThis = pThis2;
            }
            while ( v55 < pThis2[6] );
          }
          goto LABEL_34;
        }
        return result;
      default:
        return 0x80000000;
    }
    return -2147483640;
  }
  v12 = *v4;
  v13 = v4[1];
  v14 = v4 + 1;
  v15 = v14[2];
  v14 += 2;
  pThis[7] = v15;
  pThis[8] = v14[1];
  v7 = (char *)(v14 + 2);
  result = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*pThis + 12))(pThis, v12, v13);
  if ( result >= 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*pThis + 84))(pThis);
    v16 = pThis[6];
    Block4 = (void *)(4 * pThis[5]);
    v18 = 0;
    Block = Block4;
    if ( v16 != 0 )
    {
      do
      {
        qmemcpy(*(void **)(pThis[4] + 4 * v18), v7, (unsigned int)Block4);
        Block4 = Block;
        v7 = &v7[(uint32_t)Block];
        ++v18;
        pThis = pThis2;
      }
      while ( v18 < pThis2[6] );
    }
    goto LABEL_34;
  }
  return result;
}


// ------------------------------------------------------------
// 0x411EB0 sub_411EB0 —— 尺寸头预读与内存需求估算
//   fread 4B 格式号：1..4 打印失败日志（off_77F3FC 的 aFailedCnd3dtex 族）并返回 4；
//   5 → 读 0x1C 字节 7 字段存 this+5..10，返回 4*w*h+32（载入缓冲需要量）。
// ------------------------------------------------------------
int /*thiscall*/ sub_411EB0(uint32_t *this, FILE *Stream)
{
  FILE *pFile; // edi
  int v5; // ebx
  int fld_e5; // ebx
  int fld_e6; // ebx

  pFile = Stream;
  if ( Stream == nullptr )
    return 0x80000000;
  Stream = nullptr;
  ftell(pFile);
  sub_66BD5A(&Stream, 4u, 1u, pFile);  // 【fread封装】
  ftell(pFile);
  v5 = 4;
  if ( Stream == (FILE *)1 )
  {
    off_77F3FC(aFailedCnd3dtex);
    return 4;
  }
  else if ( Stream == (FILE *)2 )
  {
    off_77F3FC(aFailedCnd3dtex_0);
    return 4;
  }
  else if ( Stream == (FILE *)3 )
  {
    off_77F3FC(aFailedCnd3dtex_1);
    return 4;
  }
  else if ( Stream == (FILE *)4 )
  {
    off_77F3FC(aFailedCnd3dtex_2);
    return 4;
  }
  else
  {
    if ( Stream == (FILE *)5 )
    {
      sub_66BD5A(&dword_8A76F8, 0x1Cu, 1u, pFile);  // 【fread封装】
      *(this + 5) = dword_8A76F8;
      fld_e5 = *(this + 5);
      *(this + 6) = dword_8A76FC;
      fld_e6 = *(this + 6) * fld_e5;
      *(this + 7) = dword_8A7704;
      *(this + 8) = dword_8A7708;
      *(this + 9) = dword_8A770C;
      *(this + 10) = dword_8A7710;
      return 4 * fld_e6 + 32;
    }
    return v5;
  }
}



// ------------------------------------------------------------
// 0x411FD0 sub_411FD0 —— 行指针表重建（步长 this+80）
//   释放旧表 this+16 后 new 4*this+24，行 = this+12 + 行号*this+80；this+12 为空返回 0x80000001，内存失败 0x80000008。
// ------------------------------------------------------------
int /*thiscall*/ sub_411FD0(int this)
{
  uint32_t *pMem; // eax
  int fld_182; // ebx
  unsigned int v5; // ecx
  int v6; // edx
  int fld_C; // edi
  size_t fld_18; // [esp-4h] [ebp-8h]

  if ( *(uint32_t *)(this + 12) == 0 )
    return -2147483647;
  if ( *(uint32_t *)(this + 16) != 0 )
    j_j__free(*(void **)(this + 16));
  fld_18 = 4 * *(uint32_t *)(this + 24);
  *(uint32_t *)(this + 16) = 0;
  pMem = operator new(fld_18);
  if ( pMem == nullptr )
    return -2147483640;
  fld_182 = *(uint32_t *)(this + 24);
  v5 = 0;
  v6 = 0;
  fld_C = *(uint32_t *)(this + 12);
  *(uint32_t *)(this + 16) = pMem;
  if ( fld_182 != 0 )
  {
    do
    {
      pMem[v5] = v6 + fld_C;
      v6 += *(uint32_t *)(this + 80);
      ++v5;
    }
    while ( v5 < *(uint32_t *)(this + 24) );
  }
  return 1;
}



// ------------------------------------------------------------
// 0x412040 sub_412040 —— 图像存盘（16bpp 行宽变体）
//   —— 与 ·sub_411590 同构（差异：逐行写 2*w 字节，16bpp 序列化）。
// ------------------------------------------------------------
int /*thiscall*/ sub_412040(uint32_t *this, FILE *Stream)
{
  int fld_e6; // eax
  uint32_t *pThis_6; // ebx
  size_t fld_e5; // eax
  size_t fld_e52; // [esp+8h] [ebp-Ch]
  int v9; // [esp+Ch] [ebp-8h] BYREF
  int Buffer; // [esp+10h] [ebp-4h] BYREF
  FILE *Streama; // [esp+1Ch] [ebp+8h]

  if ( Stream == nullptr )
    return 0x80000000;
  fld_e6 = *(this + 6) * *(this + 5);
  pThis_6 = this + 6;
  Buffer = 5;
  v9 = 4 * fld_e6;
  sub_66BC25(&Buffer, 4u, 1u, Stream);
  sub_66BC25(this + 5, 4u, 1u, Stream);
  sub_66BC25(this + 6, 4u, 1u, Stream);
  sub_66BC25(&v9, 4u, 1u, Stream);
  sub_66BC25(this + 7, 4u, 1u, Stream);
  sub_66BC25(this + 8, 4u, 1u, Stream);
  sub_66BC25(this + 9, 4u, 1u, Stream);
  sub_66BC25(this + 10, 4u, 1u, Stream);
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 84))(this);
  fld_e5 = 2 * *(this + 5);
  fld_e52 = fld_e5;
  Streama = nullptr;
  if ( *pThis_6 != 0 )
  {
    while ( 1 )
    {
      sub_66BC25(*(void **)(*(this + 4) + 4 * (uint32_t)Streama), fld_e5, 1u, Stream);
      Streama = (FILE *)((char *)Streama + 1);
      if ( (unsigned int)Streama >= *pThis_6 )
        break;
      fld_e5 = fld_e52;
    }
  }
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 88))(this);
  return 1;
}



// ------------------------------------------------------------
// 0x412150 sub_412150
// ------------------------------------------------------------
// 【解读】
//   ★ 同族解码变体（232 行，调 0x652E00 uncompress）。
// ------------------------------------------------------------
int /*thiscall*/ sub_412150(uint32_t *this, FILE *Stream)
{
  FILE *v2; // ebx
  unsigned int v3; // edi
  int result; // eax
  unsigned int i; // edi
  int fld_e5; // eax
  size_t v8; // eax
  int dword_8A77243; // ecx
  int dword_8A77203; // eax
  void *pMem; // edi
  void *pMem2; // eax
  int fld_e63; // eax
  int fld_e54; // eax
  int v15; // edi
  unsigned int fld_e64; // ecx
  int dword_8A77242; // ecx
  int dword_8A77202; // eax
  int fld_e6; // eax
  int v20; // edi
  unsigned int fld_e62; // ecx
  size_t fld_e52; // eax
  size_t fld_e53; // [esp-8h] [ebp-2Ch]
  int fld_e542; // [esp+Ch] [ebp-18h] BYREF
  void *pMem3; // [esp+10h] [ebp-14h]
  int Buffer; // [esp+14h] [ebp-10h] BYREF
  unsigned int v27; // [esp+18h] [ebp-Ch]
  size_t ElementSize; // [esp+1Ch] [ebp-8h] BYREF
  void *Block; // [esp+20h] [ebp-4h]
  FILE *Streama; // [esp+2Ch] [ebp+8h]
  FILE *Streamb; // [esp+2Ch] [ebp+8h]
  FILE *Streamc; // [esp+2Ch] [ebp+8h]

  v2 = Stream;
  v3 = 0;
  if ( Stream == nullptr )
    return 0x80000000;
  Buffer = 1;
  sub_66BD5A(&Buffer, 4u, 1u, Stream);  // 【fread封装】
  if ( Buffer == 1 )
  {
    sub_66BD5A(&dword_8A7720, 0xCu, 1u, Stream);  // 【fread封装】
    result = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*this + 12))(this, dword_8A7720, dword_8A7724);
    if ( result >= 0 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 84))(this);
      if ( *((uint8_t *)this + 136) != 0 )
      {
        Block = operator new(4 * *(this + 5));
        for ( Streama = nullptr; (unsigned int)Streama < *(this + 6); Streama = (FILE *)((char *)Streama + 1) )
        {
          sub_66BD5A(Block, 4 * *(this + 5), 1u, v2);  // 【fread封装】
          for ( i = 0; i < *(this + 5); ++i )
            (*(void (/*thiscall*/ **)(uint32_t *, unsigned int, FILE *, uint32_t))(*this + 32))(
              this,
              i,
              Streama,
              *((uint32_t *)Block + i));
        }
        j_j__free(Block);
        (*(void (/*thiscall*/ **)(uint32_t *))(*this + 88))(this);
        return 1;
      }
      else
      {
        sub_66BD5A(&dword_8A7720, 8u, 1u, Stream);  // 【fread封装】
        *(this + 7) = dword_8A7720;
        fld_e5 = *(this + 5);
        *(this + 8) = dword_8A7724;
        v8 = 2 * fld_e5;
        Streamb = (FILE *)v8;
        if ( *(this + 6) != 0 )
        {
          while ( 1 )
          {
            sub_66BD5A(*(void **)(*(this + 4) + 4 * v3++), v8, 1u, v2);  // 【fread封装】
            if ( v3 >= *(this + 6) )
              break;
            v8 = (size_t)Streamb;
          }
        }
        (*(void (/*thiscall*/ **)(uint32_t *))(*this + 88))(this);
        return 1;
      }
    }
    return result;
  }
  if ( Buffer != 3 )
  {
    if ( Buffer == 5 )
    {
      sub_66BD5A(&dword_8A7720, 0x1Cu, 1u, Stream);  // 【fread封装】
      dword_8A77242 = dword_8A7724;
      dword_8A77202 = dword_8A7720;
      *(this + 7) = dword_8A772C;
      *(this + 8) = dword_8A7730;
      *(this + 9) = dword_8A7734;
      *(this + 10) = dword_8A7738;
      result = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*this + 12))(this, dword_8A77202, dword_8A77242);
      if ( result < 0 )
        return result;
      if ( *((uint8_t *)this + 136) != 0 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *))(*this + 84))(this);
        ElementSize = (size_t)operator new(4 * *(this + 5));
        fld_e6 = *(this + 6);
        v27 = 0;
        if ( fld_e6 != 0 )
        {
          do
          {
            sub_66BD5A((void *)ElementSize, 4 * *(this + 5), 1u, v2);  // 【fread封装】
            v20 = 0;
            if ( (int)*(this + 5) > 0 )
            {
              do
              {
                (*(void (/*thiscall*/ **)(uint32_t *, int, unsigned int, unsigned int))(*this + 32))(
                  this,
                  v20,
                  v27,
                  *(uint32_t *)(ElementSize + 4 * v20) & 0xFF00FF00
                | ((uint8_t)*(uint32_t *)(ElementSize + 4 * v20) << 16)
                | *(uint8_t *)(ElementSize + 4 * v20 + 2));
                ++v20;
              }
              while ( v20 < *(this + 5) );
              v2 = Stream;
            }
            fld_e62 = *(this + 6);
            ++v27;
          }
          while ( v27 < fld_e62 );
        }
        j_j__free((void *)ElementSize);
        (*(void (/*thiscall*/ **)(uint32_t *))(*this + 88))(this);
        return 1;
      }
      fld_e52 = 2 * *(this + 5);
      Streamc = (FILE *)fld_e52;
      if ( *(this + 6) != 0 )
      {
        while ( 1 )
        {
          sub_66BD5A(*(void **)(*(this + 4) + 4 * v3++), fld_e52, 1u, v2);  // 【fread封装】
          if ( v3 >= *(this + 6) )
            break;
          fld_e52 = (size_t)Streamc;
        }
      }
      return 1;
    }
    return 0x80000000;
  }
  sub_66BD5A(&dword_8A7720, 0x14u, 1u, Stream);  // 【fread封装】
  dword_8A77243 = dword_8A7724;
  dword_8A77203 = dword_8A7720;
  *(this + 7) = dword_8A772C;
  *(this + 8) = dword_8A7730;
  result = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*this + 12))(this, dword_8A77203, dword_8A77243);
  if ( result < 0 )
    return result;
  if ( *((uint8_t *)this + 136) == 0 )
    return 1;
  pMem = operator new(2 * *(this + 20) + 12);
  fld_e53 = 4 * *(this + 5);
  pMem3 = pMem;
  pMem2 = operator new(fld_e53);
  Block = pMem2;
  if ( pMem != nullptr )
  {
    if ( pMem2 == nullptr )
    {
      j_j__free(pMem);
      return -2147483640;
    }
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 84))(this);
    fld_e63 = *(this + 6);
    v27 = 0;
    if ( fld_e63 == 0 )
    {
LABEL_26:
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 88))(this);
      j_j__free(Block);
      j_j__free(pMem);
      return 1;
    }
    while ( 1 )
    {
      fld_e54 = 4 * *(this + 5);
      ElementSize = 0;
      fld_e542 = fld_e54;
      sub_66BD5A(&ElementSize, 4u, 1u, v2);  // 【fread封装】
      sub_66BD5A(pMem, ElementSize, 1u, v2);  // 【fread封装】
      if ( sub_652E00(Block, &fld_e542, pMem, ElementSize) != 0 )
        break;
      v15 = 0;
      if ( (int)*(this + 5) > 0 )
      {
        do
        {
          (*(void (/*thiscall*/ **)(uint32_t *, int, unsigned int, unsigned int))(*this + 32))(
            this,
            v15,
            v27,
            *((uint32_t *)Block + v15) & 0xFF00FF00
          | ((uint8_t)*((uint32_t *)Block + v15) << 16)
          | *((uint8_t *)Block + 4 * v15 + 2));
          ++v15;
        }
        while ( v15 < *(this + 5) );
        v2 = Stream;
      }
      fld_e64 = *(this + 6);
      pMem = pMem3;
      if ( ++v27 >= fld_e64 )
        goto LABEL_26;
    }
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 88))(this);
    j_j__free(Block);
    j_j__free(pMem);
    return 0x80000000;
  }
  if ( pMem2 != nullptr )
    j_j__free(pMem2);
  return -2147483640;
}


// ------------------------------------------------------------
// 0x4125D0 sub_4125D0 —— 尺寸头预读（bpp 由 this+136 决定）
//   格式 1 → 读 12B 填 this+20..40，返回 2*w*h*((this+136==1)+1) 再 +16（this+136 为 0 时 +24）；
//   格式 3 打失败日志 aFailedCnd3dtex_3；格式 5 → 读 0x1C 字节返回 2*w*h*((this+136==1)+1)+32。
// ------------------------------------------------------------
int /*thiscall*/ sub_4125D0(int this, FILE *Buffer)
{
  FILE *v2; // edi
  int v5; // ebx
  int dword_8A77202; // eax
  int dword_8A77242; // edx
  char fld_88; // cl
  char fld_882; // cl

  v2 = Buffer;
  if ( Buffer == nullptr )
    return 0x80000000;
  Buffer = nullptr;
  sub_66BD5A(&Buffer, 4u, 1u, v2);  // 【fread封装】
  v5 = 4;
  if ( Buffer == (FILE *)1 )
  {
    sub_66BD5A(&dword_8A7720, 0xCu, 1u, v2);  // 【fread封装】
    dword_8A77202 = dword_8A7720;
    *(uint32_t *)(this + 20) = dword_8A7720;
    dword_8A77242 = dword_8A7724;
    *(uint32_t *)(this + 28) = 0;
    *(uint32_t *)(this + 32) = 0;
    fld_88 = *(uint8_t *)(this + 136);
    *(uint32_t *)(this + 24) = dword_8A77242;
    *(uint32_t *)(this + 36) = dword_8A77202;
    *(uint32_t *)(this + 40) = dword_8A77242;
    v5 = 2 * dword_8A77202 * dword_8A77242 * ((fld_88 == 1) + 1) + 16;
    if ( fld_88 == 0 )
      return 2 * dword_8A77202 * dword_8A77242 * ((fld_88 == 1) + 1) + 24;
  }
  else
  {
    if ( Buffer == (FILE *)3 )
    {
      off_77F3FC(aFailedCnd3dtex_3);
      return 4;
    }
    if ( Buffer == (FILE *)5 )
    {
      sub_66BD5A(&dword_8A7720, 0x1Cu, 1u, v2);  // 【fread封装】
      *(uint32_t *)(this + 20) = dword_8A7720;
      *(uint32_t *)(this + 24) = dword_8A7724;
      *(uint32_t *)(this + 28) = dword_8A772C;
      *(uint32_t *)(this + 32) = dword_8A7730;
      *(uint32_t *)(this + 36) = dword_8A7734;
      fld_882 = *(uint8_t *)(this + 136);
      *(uint32_t *)(this + 40) = dword_8A7738;
      return 2 * *(uint32_t *)(this + 24) * *(uint32_t *)(this + 20) * ((fld_882 == 1) + 1) + 32;
    }
  }
  return v5;
}



// ------------------------------------------------------------
// 0x412700 sub_412700
// ------------------------------------------------------------
// 【解读】
//   ★ 同族解码变体（282 行，调 0x652E00 uncompress + BYTE2 分支）。
// ------------------------------------------------------------
int /*thiscall*/ sub_412700(unsigned int *this, int **pDwArg2)
{
  int v2; // eax
  int *v3; // esi
  int *v5; // esi
  int result; // eax
  int fld_e6; // eax
  unsigned int i; // edi
  unsigned int fld_e62; // ecx
  int v10; // ecx
  int fld_e5; // eax
  uint32_t *v12; // esi
  int fld_e63; // ecx
  unsigned int v14; // edx
  unsigned int v15; // eax
  unsigned int fld_e64; // ecx
  int v17; // eax
  int v18; // ecx
  uint32_t *v19; // esi
  int *pMem; // edi
  void *pMem2; // eax
  int fld_e65; // eax
  int v23; // eax
  unsigned int v24; // edx
  void *pMem32; // esi
  uint32_t *Block2; // edi
  int v27; // esi
  unsigned int fld_e66; // ecx
  int v29; // eax
  int v30; // ecx
  uint32_t *v31; // esi
  unsigned int v32; // edx
  unsigned int v33; // edx
  unsigned int v34; // edx
  int fld_e67; // eax
  int fld_e54; // eax
  unsigned int v37; // edx
  int v38; // ecx
  int v39; // edi
  int fld_e55; // eax
  unsigned int fld_e68; // ecx
  int fld_e69; // edx
  unsigned int fld_e56; // ecx
  unsigned int v44; // eax
  unsigned int fld_e610; // edx
  int v46; // [esp-8h] [ebp-28h]
  size_t fld_e52; // [esp-8h] [ebp-28h]
  int v48; // [esp-4h] [ebp-24h]
  int fld_e53; // [esp+Ch] [ebp-14h] BYREF
  void *Block; // [esp+10h] [ebp-10h]
  void *pMem3; // [esp+14h] [ebp-Ch]
  int v52; // [esp+18h] [ebp-8h]
  int *v53; // [esp+1Ch] [ebp-4h]

  v2 = **pDwArg2;
  v3 = *pDwArg2 + 1;
  if ( v2 == 1 )
  {
    v46 = *v3;
    v5 = *pDwArg2 + 4;
    result = (*(int (/*thiscall*/ **)(unsigned int *, int, int))(*this + 12))(this, v46, (*pDwArg2)[2]);
    if ( result >= 0 )
    {
      (*(void (/*thiscall*/ **)(unsigned int *))(*this + 84))(this);
      if ( *((uint8_t *)this + 136) != 0 )
      {
        fld_e6 = *(this + 6);
        v53 = nullptr;
        if ( fld_e6 != 0 )
        {
          do
          {
            for ( i = 0; i < *(this + 5); ++i )
            {
              v48 = *v5++;
              (*(void (/*thiscall*/ **)(unsigned int *, unsigned int, int *, int))(*this + 32))(this, i, v53, v48);
            }
            fld_e62 = *(this + 6);
            v53 = (int *)((char *)v53 + 1);
          }
          while ( (unsigned int)v53 < fld_e62 );
        }
      }
      else
      {
        v10 = *v5;
        fld_e5 = *(this + 5);
        v12 = v5 + 1;
        *(this + 7) = v10;
        fld_e63 = *(this + 6);
        *(this + 8) = *v12;
        v5 = v12 + 1;
        v14 = 0;
        v15 = 2 * fld_e5;
        v53 = v5;
        Block = nullptr;
        if ( fld_e63 != 0 )
        {
          do
          {
            qmemcpy(*(void **)(*(this + 4) + 4 * v14), v5, v15);
            fld_e64 = *(this + 6);
            v14 = (unsigned int)Block + 1;
            v53 = (int *)((char *)v53 + v15);
            Block = (void *)v14;
            v5 = v53;
          }
          while ( v14 < fld_e64 );
        }
      }
LABEL_42:
      (*(void (/*thiscall*/ **)(unsigned int *))(*this + 88))(this);
      goto LABEL_43;
    }
    return result;
  }
  if ( v2 == 3 )
  {
    v17 = *v3;
    v18 = (*pDwArg2)[2];
    v19 = *pDwArg2 + 4;
    *(this + 7) = *v19;
    *(this + 8) = v19[1];
    v5 = v19 + 2;
    result = (*(int (/*thiscall*/ **)(unsigned int *, int, int))(*this + 12))(this, v17, v18);
    if ( result < 0 )
      return result;
    if ( *((uint8_t *)this + 136) == 0 )
    {
LABEL_43:
      *pDwArg2 = v5;
      return 1;
    }
    pMem = (int *)operator new(2 * *(this + 20) + 12);
    fld_e52 = 4 * *(this + 5);
    pMem3 = pMem;
    pMem2 = operator new(fld_e52);
    Block = pMem2;
    if ( pMem == nullptr )
    {
      if ( pMem2 != nullptr )
        j_j__free(pMem2);
      return -2147483640;
    }
    if ( pMem2 == nullptr )
    {
      j_j__free(pMem);
      return -2147483640;
    }
    (*(void (/*thiscall*/ **)(unsigned int *))(*this + 84))(this);
    fld_e65 = *(this + 6);
    v52 = 0;
    if ( fld_e65 == 0 )
    {
LABEL_24:
      (*(void (/*thiscall*/ **)(unsigned int *))(*this + 88))(this);
      j_j__free(Block);
      j_j__free(pMem);
      *pDwArg2 = v5;
      return 1;
    }
    while ( 1 )
    {
      fld_e53 = 4 * *(this + 5);
      v23 = *v5;
      v24 = *v5;
      v53 = v5 + 1;
      qmemcpy(pMem, v5 + 1, v24);
      pMem32 = pMem3;
      v53 = (int *)((char *)v53 + v23);
      Block2 = Block;
      if ( sub_652E00(Block, &fld_e53, pMem3, v23) != 0 )
        break;
      v27 = 0;
      if ( (int)*(this + 5) > 0 )
      {
        while ( 1 )
        {
          (*(void (/*thiscall*/ **)(unsigned int *, int, int, unsigned int))(*this + 32))(
            this,
            v27,
            v52,
            Block2[v27] & 0xFF00FF00 | ((uint8_t)Block2[v27] << 16) | BYTE2(Block2[v27]));
          if ( ++v27 >= (int)*(this + 5) )
            break;
          Block2 = Block;
        }
      }
      fld_e66 = *(this + 6);
      v5 = v53;
      pMem = (int *)pMem3;
      if ( ++v52 >= fld_e66 )
        goto LABEL_24;
    }
    (*(void (/*thiscall*/ **)(unsigned int *))(*this + 88))(this);
    j_j__free(Block2);
    j_j__free(pMem32);
    return 0x80000000;
  }
  if ( v2 != 5 )
    return 0x80000000;
  v29 = *v3;
  v30 = (*pDwArg2)[2];
  v31 = *pDwArg2 + 4;
  *(this + 7) = *v31;
  v32 = v31[1];
  ++v31;
  *(this + 8) = v32;
  v33 = v31[1];
  ++v31;
  *(this + 9) = v33;
  *(this + 10) = v31[1];
  v34 = *this;
  v5 = v31 + 2;
  v53 = v5;
  result = (*(int (/*thiscall*/ **)(unsigned int *, int, int))(v34 + 12))(this, v29, v30);
  if ( result >= 0 )
  {
    (*(void (/*thiscall*/ **)(unsigned int *))(*this + 84))(this);
    if ( *((uint8_t *)this + 136) != 0 )
    {
      fld_e67 = *(this + 6);
      Block = nullptr;
      if ( fld_e67 != 0 )
      {
        do
        {
          fld_e54 = *(this + 5);
          pMem3 = nullptr;
          if ( fld_e54 > 0 )
          {
            do
            {
              v37 = *this;
              v38 = (uint8_t)BYTE2(*v5);
              v39 = (uint8_t)*v5;
              fld_e53 = *v5++;
              (*(void (/*thiscall*/ **)(unsigned int *, void *, void *, unsigned int))(v37 + 32))(
                this,
                pMem3,
                Block,
                fld_e53 & 0xFF00FF00 | (v39 << 16) | v38);
              fld_e55 = *(this + 5);
              pMem3 = (char *)pMem3 + 1;
            }
            while ( (int)pMem3 < fld_e55 );
          }
          fld_e68 = *(this + 6);
          Block = (char *)Block + 1;
        }
        while ( (unsigned int)Block < fld_e68 );
      }
    }
    else
    {
      fld_e69 = *(this + 6);
      fld_e56 = 2 * *(this + 5);
      v44 = 0;
      fld_e53 = fld_e56;
      if ( fld_e69 != 0 )
      {
        do
        {
          qmemcpy(*(void **)(*(this + 4) + 4 * v44), v5, fld_e56);
          fld_e56 = fld_e53;
          fld_e610 = *(this + 6);
          ++v44;
          v53 = (int *)((char *)v53 + fld_e53);
          v5 = v53;
        }
        while ( v44 < fld_e610 );
      }
    }
    goto LABEL_42;
  }
  return result;
}


// ============================================================
// SECTION 0x412AE0 — 图像属性 getter/setter（宽高/矩形/标志，HIWORD/LOWORD 打包）
// ============================================================
// ------------------------------------------------------------
// 0x412AE0 sub_412AE0 —— 指定色转透明（16bpp A1R5G5B5）
//   vt+84/88 锁定内逐像素匹配 A1R5G5B5 折叠色者清 0；记录 this+17 = uArg2。
//   A1R5G5B5 即 IMG 定案像素格式（0x418CD0 族解码产物）。
// ------------------------------------------------------------
int /*thiscall*/ sub_412AE0(uint32_t *this, unsigned int uArg2)  // 【图像属性 getter/setter（宽高/矩形/标志，HIWORD/LOWORD…】
{
  unsigned int i; // edi
  int fld_e4; // edx
  unsigned int j; // eax
  int result; // eax

  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 84))(this);
  for ( i = 0; i < *(this + 6); ++i )
  {
    fld_e4 = *(uint32_t *)(*(this + 4) + 4 * i);
    for ( j = 0; j < *(this + 5); ++j )
    {
      if ( *(uint16_t *)(fld_e4 + 2 * j) == ((uint16_t)(16 * (uArg2 & 0xF0))
                                    | (uArg2 >> 20) & 0xF
                                    | (uArg2 >> 8) & 0xF0
                                    | HIWORD(uArg2) & 0xF000) )
        *(uint16_t *)(fld_e4 + 2 * j) = 0;
    }
  }
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 88))(this);
  *(this + 17) = uArg2;
  return result;
}



// ------------------------------------------------------------
// 0x412B70 sub_412B70 —— 整幅填充（16bpp 批量）
//   与 ·sub_412AE0 同族（差异：整幅填充为折叠色，按 32 位 memset32 双像素写、奇数宽补 1 像素）。
// ------------------------------------------------------------
int /*thiscall*/ sub_412B70(uint32_t *this, unsigned int uArg2)
{
  int result; // eax
  int16_t uArg22; // bx
  int fld_e6; // edi
  unsigned int fld_e5; // esi
  unsigned int v7; // ecx
  uint16_t *v8; // edi
  int fld_e4; // [esp+0h] [ebp-4h]
  int v10; // [esp+Ch] [ebp+8h]

  result = *(this + 3);
  if ( result != 0 )
  {
    fld_e4 = *(this + 4);
    uArg22 = uArg2;
    fld_e6 = *(this + 6);
    fld_e5 = *(this + 5) >> 1;
    result = (((uint16_t)(16 * (uArg2 & 0xF0)) | (uArg2 >> 20) & 0xF | (uArg2 >> 8) & 0xF0 | HIWORD(uArg2) & 0xF000) << 16)
           | (uint16_t)(16 * (uArg2 & 0xF0))
           | (uArg2 >> 20) & 0xF
           | (uArg2 >> 8) & 0xF0
           | HIWORD(uArg2) & 0xF000;
    v7 = 0;
    v10 = 0;
    if ( fld_e6 != 0 )
    {
      do
      {
        v8 = *(uint16_t **)(fld_e4 + 4 * v7);
        if ( (*(uint8_t *)(this + 5) & 1) != 0 )
          *v8++ = uArg22;
        if ( fld_e5 != 0 )
        {
          memset32(v8, result, fld_e5);
          v7 = v10;
        }
        v10 = ++v7;
      }
      while ( v7 < *(this + 6) );
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x412C20 sub_412C20 —— 单像素置色（16bpp）
//   越界由 sub_40F530 判定；否则写 A1R5G5B5 折叠色（与 ·sub_412C80 取色互逆）。
// ------------------------------------------------------------
char /*thiscall*/ sub_412C20(uint32_t *this, int nArg2, int nArg3, unsigned int uArg4)
{
  int fld_e4; // eax

  LOBYTE(fld_e4) = sub_40F530(nArg2, nArg3, this + 12);
  if ( (uint8_t)fld_e4 == 0 )
  {
    fld_e4 = *(this + 4);
    *(uint16_t *)(*(uint32_t *)(fld_e4 + 4 * nArg3) + 2 * nArg2) = (16 * (uArg4 & 0xF0))
                                                  | (uArg4 >> 20) & 0xF
                                                  | (uArg4 >> 8) & 0xF0
                                                  | HIWORD(uArg4) & 0xF000;
  }
  return fld_e4;
}



// ------------------------------------------------------------
// 0x412C80 sub_412C80 —— 单像素取色（16bpp 反折叠）
//   越界返回 0；否则读 16bpp 像素按位展开回 ARGB。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_412C80(uint32_t *this, int nArg2, int nArg3)
{
  int fld_e4; // esi
  int v6; // ecx

  if ( sub_40F530(nArg2, nArg3, this + 12) )
    return 0;
  fld_e4 = *(this + 4);
  v6 = *(uint16_t *)(*(uint32_t *)(fld_e4 + 4 * nArg3) + 2 * nArg2);
  return ((v6 & 0xF00 | 0xF0F0F0FF) >> 4)
       | ((*(uint16_t *)(*(uint32_t *)(fld_e4 + 4 * nArg3) + 2 * nArg2) & 0xF0
         | ((v6 ^ ((uint8_t)v6 ^ (uint8_t)(16 * *(uint16_t *)(*(uint32_t *)(fld_e4 + 4 * nArg3) + 2 * nArg2))) & 0xF0) << 8)) << 8);
}



// ------------------------------------------------------------
// 0x412CF0 sub_412CF0 —— 水平线段填充（16bpp）
//   nArg3 为行界 this[13..15]，起 x/宽 nArg2/nArg4 裁剪后 memset32 双像素写、奇数补 1。
// ------------------------------------------------------------
int /*thiscall*/ sub_412CF0(int *this, int nArg2, int nArg3, int nArg4, unsigned int uArg5)
{
  int result; // eax
  int nArg42; // ecx
  int fld_e14; // eax
  int fld_e4; // edx
  char *v10; // edi
  int v11; // edx
  char v12; // cf
  unsigned int v13; // ecx
  char *v14; // edi
  int i; // ecx
  int nArg22; // [esp+4h] [ebp-4h]

  result = nArg3;
  if ( nArg3 >= *(this + 13) && nArg3 < *(this + 15) )
  {
    nArg22 = 0;
    nArg42 = nArg4;
    if ( nArg2 < 0 )
      nArg42 = nArg2 + nArg4;
    else
      nArg22 = nArg2;
    fld_e14 = *(this + 14);
    if ( nArg2 + nArg4 >= fld_e14 )
      nArg42 += fld_e14 - nArg2 - nArg4;
    result = (16 * (uArg5 & 0xF0)) | (uArg5 >> 20) & 0xF | (uArg5 >> 8) & 0xF0 | HIWORD(uArg5) & 0xF000;
    fld_e4 = *(uint32_t *)(*(this + 4) + 4 * nArg3);
    v10 = (char *)(fld_e4 + 2 * nArg22);
    if ( nArg42 > 0 )
    {
      LOWORD(fld_e4) = (16 * (uArg5 & 0xF0)) | (uArg5 >> 20) & 0xF | (uArg5 >> 8) & 0xF0 | HIWORD(uArg5) & 0xF000;
      v11 = fld_e4 << 16;
      LOWORD(v11) = (16 * (uArg5 & 0xF0)) | (uArg5 >> 20) & 0xF | (uArg5 >> 8) & 0xF0 | HIWORD(uArg5) & 0xF000;
      v12 = nArg42 & 1;
      v13 = (unsigned int)nArg42 >> 1;
      result = v11;
      memset32(v10, v11, v13);
      v14 = &v10[4 * v13];
      for ( i = v12; i != 0; --i )
      {
        *(uint16_t *)v14 = v11;
        v14 += 2;
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x412DA0 sub_412DA0 —— 垂直线段填充（16bpp）
//   nArg2 为列（界 this[12..14]），自 nArg3 起高 nArg4，经 this[4] 行表逐行写同列。
// ------------------------------------------------------------
int /*thiscall*/ sub_412DA0(int *this, int nArg2, int nArg3, int nArg4, unsigned int uArg5)
{
  int result; // eax
  int nArg32; // ebx
  int nArg33; // esi
  int nArg42; // edi
  int v9; // edx
  int v10; // esi
  int fld_e4; // ecx
  int fld_e15; // [esp+14h] [ebp+10h]

  result = nArg2;
  if ( nArg2 >= *(this + 12) && nArg2 < *(this + 14) )
  {
    nArg32 = nArg3;
    nArg33 = 0;
    nArg42 = nArg4;
    if ( nArg3 < 0 )
      nArg42 = nArg3 + nArg4;
    else
      nArg33 = nArg3;
    fld_e15 = *(this + 15);
    result = (16 * (uArg5 & 0xF0)) | (uArg5 >> 20) & 0xF | (uArg5 >> 8) & 0xF0 | HIWORD(uArg5) & 0xF000;
    v9 = 0;
    if ( nArg42 > 0 )
    {
      v10 = 4 * nArg33;
      while ( v9 + nArg32 < fld_e15 )
      {
        fld_e4 = *(uint32_t *)(*(this + 4) + v10);
        ++v9;
        v10 += 4;
        *(uint16_t *)(fld_e4 + 2 * nArg2) = result;
        if ( v9 >= nArg42 )
          break;
        nArg32 = nArg3;
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x412E40 sub_412E40 —— 指定色转透明（16bpp R5G6B5 变体）
//   —— 与 ·sub_412AE0 同构（差异：16bpp R5G6B5 打包）。
// ------------------------------------------------------------
int /*thiscall*/ sub_412E40(uint32_t *this, unsigned int uArg2)
{
  unsigned int i; // edi
  int fld_e4; // ecx
  unsigned int j; // eax
  int result; // eax

  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 84))(this);
  for ( i = 0; i < *(this + 6); ++i )
  {
    fld_e4 = *(uint32_t *)(*(this + 4) + 4 * i);
    for ( j = 0; j < *(this + 5); ++j )
    {
      if ( *(uint16_t *)(fld_e4 + 2 * j) == (((uArg2 & 0xF8) << 7) | HIWORD(uArg2) & 0x8000 | (uArg2 >> 19) & 0x1F | (uArg2 >> 6) & 0x3E0) )
        *(uint16_t *)(fld_e4 + 2 * j) = 0;
    }
  }
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 88))(this);
  *(this + 17) = uArg2;
  return result;
}



// ------------------------------------------------------------
// 0x412ED0 sub_412ED0 —— 整幅填充（16bpp R5G6B5 变体）
//   —— 与 ·sub_412B70 同构（差异：R5G6B5 打包）。
// ------------------------------------------------------------
int /*thiscall*/ sub_412ED0(uint32_t *this, unsigned int uArg2)
{
  int result; // eax
  int16_t uArg22; // bx
  int fld_e6; // edi
  unsigned int fld_e5; // esi
  unsigned int v7; // ecx
  uint16_t *v8; // edi
  int fld_e4; // [esp+0h] [ebp-4h]
  int v10; // [esp+Ch] [ebp+8h]

  result = *(this + 3);
  if ( result != 0 )
  {
    fld_e4 = *(this + 4);
    uArg22 = uArg2;
    fld_e6 = *(this + 6);
    fld_e5 = *(this + 5) >> 1;
    result = ((((uArg2 & 0xF8) << 7) | HIWORD(uArg2) & 0x8000 | (uArg2 >> 19) & 0x1F | (uArg2 >> 6) & 0x3E0) << 16)
           | ((uArg2 & 0xF8) << 7)
           | HIWORD(uArg2) & 0x8000
           | (uArg2 >> 19) & 0x1F
           | (uArg2 >> 6) & 0x3E0;
    v7 = 0;
    v10 = 0;
    if ( fld_e6 != 0 )
    {
      do
      {
        v8 = *(uint16_t **)(fld_e4 + 4 * v7);
        if ( (*(uint8_t *)(this + 5) & 1) != 0 )
          *v8++ = uArg22;
        if ( fld_e5 != 0 )
        {
          memset32(v8, result, fld_e5);
          v7 = v10;
        }
        v10 = ++v7;
      }
      while ( v7 < *(this + 6) );
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x412F80 sub_412F80 —— 矩形区域填充（16bpp R5G6B5）
//   区域取 pDwArg2（x1/y1/x2/y2），逐行对 [x1, x2] 段 memset32 写 R5G6B5，奇数宽补 1。
// ------------------------------------------------------------
int /*thiscall*/ sub_412F80(int this, unsigned int *pDwArg2, unsigned int uArg3)
{
  int result; // eax
  signed int v5; // esi
  unsigned int v6; // edx
  signed int v7; // ecx
  uint16_t *uArg32; // edi
  int fld_10; // [esp+4h] [ebp-4h]
  signed int v11; // [esp+10h] [ebp+8h]

  result = *(uint32_t *)(this + 12);
  if ( result != 0 )
  {
    fld_10 = *(uint32_t *)(this + 16);
    v5 = pDwArg2[3];
    v6 = (int)(pDwArg2[2] - *pDwArg2) >> 1;
    result = ((((uArg3 & 0xF8) << 7) | HIWORD(uArg3) & 0x8000 | (uArg3 >> 19) & 0x1F | (uArg3 >> 6) & 0x3E0) << 16)
           | ((uArg3 & 0xF8) << 7)
           | HIWORD(uArg3) & 0x8000
           | (uArg3 >> 19) & 0x1F
           | (uArg3 >> 6) & 0x3E0;
    v11 = pDwArg2[1];
    v7 = v11;
    if ( v11 < v5 )
    {
      do
      {
        uArg32 = *(uint16_t **)(fld_10 + 4 * v7);
        if ( (*(uint8_t *)(this + 20) & 1) != 0 )
        {
          *uArg32 = uArg3;
          v7 = v11;
          ++uArg32;
        }
        if ( *pDwArg2 <= v6 )
        {
          memset32(&uArg32[2 * *pDwArg2], result, v6 - *pDwArg2 + 1);
          v7 = v11;
        }
        v11 = ++v7;
      }
      while ( v7 < (int)pDwArg2[3] );
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x413040 sub_413040 —— 单像素置色（16bpp R5G6B5 变体）
//   —— 与 ·sub_412C20 同构（差异：R5G6B5 打包）。
// ------------------------------------------------------------
char /*thiscall*/ sub_413040(uint32_t *this, int nArg2, int nArg3, unsigned int uArg4)
{
  int fld_e4; // eax

  LOBYTE(fld_e4) = sub_40F530(nArg2, nArg3, this + 12);
  if ( (uint8_t)fld_e4 == 0 )
  {
    fld_e4 = *(this + 4);
    *(uint16_t *)(*(uint32_t *)(fld_e4 + 4 * nArg3) + 2 * nArg2) = ((uArg4 & 0xF8) << 7)
                                                  | HIWORD(uArg4) & 0x8000
                                                  | (uArg4 >> 19) & 0x1F
                                                  | (uArg4 >> 6) & 0x3E0;
  }
  return fld_e4;
}



// ------------------------------------------------------------
// 0x4130A0 sub_4130A0 —— 单像素取色（16bpp R5G6B5 变体）
//   与 ·sub_412C80 同构（差异：R5G6B5 展开并或上 0x7F070707 常量位）【推断：常量位为引擎标记】。
// ------------------------------------------------------------
int /*thiscall*/ sub_4130A0(uint32_t *this, int nArg2, int nArg3)
{
  int fld_e4; // esi
  unsigned int v6; // ecx

  if ( sub_40F530(nArg2, nArg3, this + 12) )
    return 0;
  fld_e4 = *(this + 4);
  v6 = *(uint16_t *)(*(uint32_t *)(fld_e4 + 4 * nArg3) + 2 * nArg2);
  return (v6 >> 7) & 0xF8
       | ((*(uint16_t *)(*(uint32_t *)(fld_e4 + 4 * nArg3) + 2 * nArg2) & 0x3E0
         | ((v6 ^ ((uint8_t)v6 ^ (uint8_t)(8 * v6)) & 0xF8) << 10)) << 6)
       | 0x7F070707;
}



// ------------------------------------------------------------
// 0x413110 sub_413110 —— 水平线段填充（16bpp R5G6B5 变体）
//   —— 与 ·sub_412CF0 同构（差异：R5G6B5 打包）。
// ------------------------------------------------------------
int /*thiscall*/ sub_413110(int *this, int nArg2, int nArg3, int nArg4, unsigned int uArg5)
{
  int result; // eax
  int nArg42; // ecx
  int fld_e14; // eax
  int fld_e4; // edx
  char *v10; // edi
  int v11; // edx
  char v12; // cf
  unsigned int v13; // ecx
  char *v14; // edi
  int i; // ecx
  int nArg22; // [esp+4h] [ebp-4h]

  result = nArg3;
  if ( nArg3 >= *(this + 13) && nArg3 < *(this + 15) )
  {
    nArg22 = 0;
    nArg42 = nArg4;
    if ( nArg2 < 0 )
      nArg42 = nArg2 + nArg4;
    else
      nArg22 = nArg2;
    fld_e14 = *(this + 14);
    if ( nArg2 + nArg4 >= fld_e14 )
      nArg42 += fld_e14 - nArg2 - nArg4;
    result = ((uArg5 & 0xF8) << 7) | HIWORD(uArg5) & 0x8000 | (uArg5 >> 19) & 0x1F | (uArg5 >> 6) & 0x3E0;
    fld_e4 = *(uint32_t *)(*(this + 4) + 4 * nArg3);
    v10 = (char *)(fld_e4 + 2 * nArg22);
    if ( nArg42 > 0 )
    {
      LOWORD(fld_e4) = ((uArg5 & 0xF8) << 7) | HIWORD(uArg5) & 0x8000 | (uArg5 >> 19) & 0x1F | (uArg5 >> 6) & 0x3E0;
      v11 = fld_e4 << 16;
      LOWORD(v11) = ((uArg5 & 0xF8) << 7) | HIWORD(uArg5) & 0x8000 | (uArg5 >> 19) & 0x1F | (uArg5 >> 6) & 0x3E0;
      v12 = nArg42 & 1;
      v13 = (unsigned int)nArg42 >> 1;
      result = v11;
      memset32(v10, v11, v13);
      v14 = &v10[4 * v13];
      for ( i = v12; i != 0; --i )
      {
        *(uint16_t *)v14 = v11;
        v14 += 2;
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4131C0 sub_4131C0 —— 垂直线段填充（16bpp R5G6B5 变体）
//   —— 与 ·sub_412DA0 同构（差异：R5G6B5 打包）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4131C0(int *this, int nArg2, int nArg3, int nArg4, unsigned int uArg5)
{
  int result; // eax
  int nArg32; // ebx
  int nArg33; // esi
  int nArg42; // edi
  int v9; // edx
  int v10; // esi
  int fld_e4; // ecx
  int fld_e15; // [esp+14h] [ebp+10h]

  result = nArg2;
  if ( nArg2 >= *(this + 12) && nArg2 < *(this + 14) )
  {
    nArg32 = nArg3;
    nArg33 = 0;
    nArg42 = nArg4;
    if ( nArg3 < 0 )
      nArg42 = nArg3 + nArg4;
    else
      nArg33 = nArg3;
    fld_e15 = *(this + 15);
    result = ((uArg5 & 0xF8) << 7) | HIWORD(uArg5) & 0x8000 | (uArg5 >> 19) & 0x1F | (uArg5 >> 6) & 0x3E0;
    v9 = 0;
    if ( nArg42 > 0 )
    {
      v10 = 4 * nArg33;
      while ( v9 + nArg32 < fld_e15 )
      {
        fld_e4 = *(uint32_t *)(*(this + 4) + v10);
        ++v9;
        v10 += 4;
        *(uint16_t *)(fld_e4 + 2 * nArg2) = result;
        if ( v9 >= nArg42 )
          break;
        nArg32 = nArg3;
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x413260 sub_413260 —— 图像复用与克隆挂接
//   vt+12 设尺寸、vt+28 复位；源格式 8 → 直接 vt+152(0, 0, this) 共享挂接；
//   其余格式先 vt+84/88 锁定源与本对象，再 vt+152 挂接后解锁。
// ------------------------------------------------------------
int /*thiscall*/ sub_413260(void *this, uint32_t *pArg2)
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(void *, uint32_t, uint32_t))(*(uint32_t *)this + 12))(this, pArg2[5], pArg2[6]);
  if ( result >= 0 )
  {
    (*(void (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 28))(this, 0);
    if ( pArg2[2] == 8 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, void *))(*pArg2 + 152))(pArg2, 0, 0, this);
    }
    else
    {
      (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 84))(this);
      (*(void (/*thiscall*/ **)(uint32_t *))(*pArg2 + 84))(pArg2);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, void *))(*pArg2 + 152))(pArg2, 0, 0, this);
      (*(void (/*thiscall*/ **)(uint32_t *))(*pArg2 + 88))(pArg2);
      (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 88))(this);
    }
    return 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4132E0 sub_4132E0 —— 行指针表重建（步长 4*this+20）
//   —— 与 ·sub_411FD0 同构（差异：行 = this+12 + 行号*(4*this+20)）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4132E0(int this)
{
  uint32_t *pMem; // eax
  int fld_182; // ebx
  int fld_14; // edx
  unsigned int v6; // ecx
  int fld_C; // edi
  size_t fld_18; // [esp-4h] [ebp-8h]

  if ( *(uint32_t *)(this + 12) == 0 )
    return -2147483647;
  if ( *(uint32_t *)(this + 16) != 0 )
    j_j__free(*(void **)(this + 16));
  fld_18 = 4 * *(uint32_t *)(this + 24);
  *(uint32_t *)(this + 16) = 0;
  pMem = operator new(fld_18);
  if ( pMem == nullptr )
    return -2147483640;
  fld_182 = *(uint32_t *)(this + 24);
  fld_14 = 4 * *(uint32_t *)(this + 20);
  v6 = 0;
  fld_C = *(uint32_t *)(this + 12);
  *(uint32_t *)(this + 16) = pMem;
  if ( fld_182 != 0 )
  {
    do
    {
      pMem[v6++] = fld_C;
      fld_C += fld_14;
    }
    while ( v6 < *(uint32_t *)(this + 24) );
  }
  return 1;
}



// ------------------------------------------------------------
// 0x413360 sub_413360 —— 指定色 alpha 清 0（32bpp）
//   与 ·sub_4113F0 同族（差异：不清整值，仅把匹配像素第 4 字节清 0 而保留 RGB）；记录 this+17。
// ------------------------------------------------------------
int /*thiscall*/ sub_413360(uint32_t *this, int nArg2)
{
  unsigned int i; // edi
  int fld_e4; // ecx
  unsigned int j; // eax

  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 84))(this);
  for ( i = 0; i < *(this + 6); ++i )
  {
    fld_e4 = *(uint32_t *)(*(this + 4) + 4 * i);
    for ( j = 0; j < *(this + 5); ++j )
    {
      if ( *(uint32_t *)(fld_e4 + 4 * j) == (nArg2 & 0xFF00FF00 | ((uint8_t)nArg2 << 16) | BYTE2(nArg2)) )
        *(uint8_t *)(fld_e4 + 4 * j + 3) = 0;
    }
  }
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 88))(this);
  *(this + 17) = nArg2;
  return nArg2;
}



// ------------------------------------------------------------
// 0x4133D0 sub_4133D0 —— 单像素置色（32bpp）
//   —— 与 ·sub_412C20 同构（差异：32bpp 整字写 + FF00FF00 重排）。
// ------------------------------------------------------------
char /*thiscall*/ sub_4133D0(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  int fld_e4; // eax

  LOBYTE(fld_e4) = sub_40F530(nArg2, nArg3, this + 12);
  if ( (uint8_t)fld_e4 == 0 )
  {
    fld_e4 = *(this + 4);
    *(uint32_t *)(*(uint32_t *)(fld_e4 + 4 * nArg3) + 4 * nArg2) = nArg4 & 0xFF00FF00 | ((uint8_t)nArg4 << 16) | BYTE2(nArg4);
  }
  return fld_e4;
}



// ------------------------------------------------------------
// 0x413420 sub_413420 —— 垂直线段填充（32bpp）
//   —— 与 ·sub_412DA0 同构（差异：32bpp 整字写）。
// ------------------------------------------------------------
int /*thiscall*/ sub_413420(int *this, int nArg2, int nArg3, int nArg4, int nArg5)
{
  int result; // eax
  int nArg32; // ebx
  int nArg33; // esi
  int nArg42; // edi
  int v9; // esi
  int fld_e4; // ecx
  int fld_e15; // [esp+14h] [ebp+10h]

  result = nArg2;
  if ( nArg2 >= *(this + 12) && nArg2 < *(this + 14) )
  {
    nArg32 = nArg3;
    nArg33 = 0;
    nArg42 = nArg4;
    if ( nArg3 < 0 )
      nArg42 = nArg3 + nArg4;
    else
      nArg33 = nArg3;
    fld_e15 = *(this + 15);
    result = 0;
    if ( nArg42 > 0 )
    {
      v9 = 4 * nArg33;
      while ( result + nArg32 < fld_e15 )
      {
        fld_e4 = *(uint32_t *)(*(this + 4) + v9);
        ++result;
        v9 += 4;
        *(uint32_t *)(fld_e4 + 4 * nArg2) = nArg5 & 0xFF00FF00 | ((uint8_t)nArg5 << 16) | BYTE2(nArg5);
        if ( result >= nArg42 )
          break;
        nArg32 = nArg3;
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4134B0 sub_4134B0 —— 图像存盘（标志 1 / 32bpp）
//   —— 与 ·sub_411590 同构（差异：头部仅写标志 1 与 4 个字段，无 this+7..10；逐行 4*w）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4134B0(uint32_t *this, FILE *Stream)
{
  int fld_e6; // eax
  uint32_t *pThis_6; // ebx
  size_t fld_e5; // eax
  size_t fld_e52; // [esp+8h] [ebp-Ch]
  int v9; // [esp+Ch] [ebp-8h] BYREF
  int Buffer; // [esp+10h] [ebp-4h] BYREF
  FILE *Streama; // [esp+1Ch] [ebp+8h]

  if ( Stream == nullptr )
    return 0x80000000;
  fld_e6 = *(this + 6) * *(this + 5);
  pThis_6 = this + 6;
  Buffer = 1;
  v9 = 4 * fld_e6;
  sub_66BC25(&Buffer, 4u, 1u, Stream);
  sub_66BC25(this + 5, 4u, 1u, Stream);
  sub_66BC25(this + 6, 4u, 1u, Stream);
  sub_66BC25(&v9, 4u, 1u, Stream);
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 84))(this);
  fld_e5 = 4 * *(this + 5);
  fld_e52 = fld_e5;
  Streama = nullptr;
  if ( *pThis_6 != 0 )
  {
    while ( 1 )
    {
      sub_66BC25(*(void **)(*(this + 4) + 4 * (uint32_t)Streama), fld_e5, 1u, Stream);
      Streama = (FILE *)((char *)Streama + 1);
      if ( (unsigned int)Streama >= *pThis_6 )
        break;
      fld_e5 = fld_e52;
    }
  }
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 88))(this);
  return 1;
}



// ------------------------------------------------------------
// 0x413580 sub_413580 —— 图像读入（标志 1 / 32bpp）
//   读 4B 标志须为 1 → 收宽高与字节数 → vt+12 建图 → 逐行 fread 4*w 字节（与 ·sub_4134B0 互逆）。
// ------------------------------------------------------------
int /*thiscall*/ sub_413580(uint32_t *this, FILE *Buffer)
{
  FILE *v2; // ebx
  unsigned int v3; // edi
  int result; // eax
  size_t fld_e5; // eax
  FILE *v7; // [esp-4h] [ebp-20h]
  size_t fld_e52; // [esp+Ch] [ebp-10h]
  int v9; // [esp+10h] [ebp-Ch] BYREF
  int v10; // [esp+14h] [ebp-8h] BYREF
  int v11; // [esp+18h] [ebp-4h] BYREF

  v2 = Buffer;
  v3 = 0;
  if ( Buffer == nullptr )
    return 0x80000000;
  v7 = Buffer;
  Buffer = nullptr;
  v10 = 0;
  v11 = 0;
  v9 = 0;
  sub_66BD5A(&Buffer, 4u, 1u, v7);  // 【fread封装】
  if ( Buffer != (FILE *)1 )
    return 0x80000000;
  sub_66BD5A(&v10, 4u, 1u, v2);  // 【fread封装】
  sub_66BD5A(&v11, 4u, 1u, v2);  // 【fread封装】
  sub_66BD5A(&v9, 4u, 1u, v2);  // 【fread封装】
  result = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*this + 12))(this, v10, v11);
  if ( result >= 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 84))(this);
    fld_e5 = 4 * *(this + 5);
    fld_e52 = fld_e5;
    if ( *(this + 6) != 0 )
    {
      while ( 1 )
      {
        sub_66BD5A(*(void **)(*(this + 4) + 4 * v3++), fld_e5, 1u, v2);  // 【fread封装】
        if ( v3 >= *(this + 6) )
          break;
        fld_e5 = fld_e52;
      }
    }
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 88))(this);
    return 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x413670 sub_413670 —— 由外部表面对象绑定尺寸与行表
//   nArg2 虚表 +32 查询表面信息（第 4 槽为格式标志）→ 置 this[5]/[6] 并 SetRect，this+4 置就绪；
//   标志为 1 时 vt+84/88 锁定解锁、this[3] = this[25] 复制行表，再 vt+172 建表。
// ------------------------------------------------------------
int /*thiscall*/ sub_413670(int *this, int nArg2)
{
  int v4; // ecx
  bool v5; // zf
  int v6; // edx
  int v7; // edi
  int v8; // [esp-Ch] [ebp-30h]
  int v9; // [esp-8h] [ebp-2Ch]
  uint32_t pBuf[3]; // [esp+4h] [ebp-20h] BYREF
  int v11; // [esp+10h] [ebp-14h]
  int v12; // [esp+14h] [ebp-10h]
  int v13; // [esp+18h] [ebp-Ch]
  int xRight; // [esp+1Ch] [ebp-8h]
  int yBottom; // [esp+20h] [ebp-4h]

  if ( *((uint8_t *)this + 4) != 0 )
    return -2147483646;
  memset(pBuf, 0, sizeof(pBuf));
  v11 = 0;
  v12 = 0;
  v13 = 0;
  xRight = 0;
  yBottom = 0;
  *((uint8_t *)this + 4) = 1;
  (*(void (/*stdcall*/ **)(int, uint32_t *))(*(uint32_t *)nArg2 + 32))(nArg2, pBuf);
  v4 = yBottom;
  v9 = yBottom;
  v8 = xRight;
  *(this + 5) = xRight;
  *(this + 6) = v4;
  SetRect((LPRECT)this + 5, 0, 0, v8, v9);
  SetRect((LPRECT)this + 3, 0, 0, *(this + 5), *(this + 6));
  v5 = v11 == 1;
  *((uint8_t *)this + 76) = 1;
  if ( !v5 )
    return 1;
  (*(void (/*thiscall*/ **)(int *))(*this + 84))(this);
  (*(void (/*thiscall*/ **)(int *))(*this + 88))(this);
  v6 = *this;
  *(this + 3) = *(this + 25);
  v7 = (*(int (/*thiscall*/ **)(int *))(v6 + 172))(this);
  if ( v7 >= 0 )
    return 1;
  (*(void (/*thiscall*/ **)(int *))(*this + 20))(this);
  return v7;
}



// ------------------------------------------------------------
// 0x413740 sub_413740 —— 按宽高创建设备图像（vt+108）
//   与 ·sub_413670 互补：取 this[27] 设备对象（偏移 108）虚表 +108（参数 21）出图存 this[26]（偏移 104），
//   随后自身 vt+84/88 锁定解锁、this[3] = this[25]，vt+172 建行表；失败调 vt+20 销毁。
// ------------------------------------------------------------
int /*thiscall*/ sub_413740(int *this, int xRight, int yBottom)
{
  int fld_e27; // eax
  int pThis_1A; // edi
  int v7; // edx

  if ( *((uint8_t *)this + 4) != 0 )
    return -2147483646;
  *((uint8_t *)this + 4) = 1;
  *(this + 5) = xRight;
  *(this + 6) = yBottom;
  SetRect((LPRECT)this + 5, 0, 0, xRight, yBottom);
  SetRect((LPRECT)this + 3, 0, 0, *(this + 5), *(this + 6));
  fld_e27 = *(this + 27);
  *((uint8_t *)this + 76) = 0;
  pThis_1A = (*(int (/*stdcall*/ **)(int, int, int, int, int *))(*(uint32_t *)fld_e27 + 108))(fld_e27, xRight, yBottom, 21, this + 26);
  if ( pThis_1A >= 0 )
  {
    (*(void (/*thiscall*/ **)(int *))(*this + 84))(this);
    (*(void (/*thiscall*/ **)(int *))(*this + 88))(this);
    v7 = *this;
    *(this + 3) = *(this + 25);
    pThis_1A = (*(int (/*thiscall*/ **)(int *))(v7 + 172))(this);
    if ( pThis_1A >= 0 )
      return 1;
  }
  (*(void (/*thiscall*/ **)(int *))(*this + 20))(this);
  return pThis_1A;
}



// ------------------------------------------------------------
// 0x413800 sub_413800 —— 图像状态复位
//   非共享（this+76 == 0）时释放 this+104 对象（vt+8）；清尺寸表与标志 this+12/16/96/100 与 4/76。
// ------------------------------------------------------------
int /*thiscall*/ sub_413800(int this)
{
  int fld_68; // eax
  uint32_t *pThis_60; // esi

  if ( *(uint8_t *)(this + 76) == 0 )
  {
    fld_68 = *(uint32_t *)(this + 104);
    if ( fld_68 != 0 )
      (*(void (/*stdcall*/ **)(uint32_t))(*(uint32_t *)fld_68 + 8))(*(uint32_t *)(this + 104));
    *(uint32_t *)(this + 104) = 0;
  }
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint8_t *)(this + 76) = 0;
  *(uint8_t *)(this + 4) = 0;
  pThis_60 = (uint32_t *)(this + 96);
  *pThis_60 = 0;
  pThis_60[1] = 0;
  return 1;
}



// ------------------------------------------------------------
// 0x413840 sub_413840 —— 图像加锁（vt+36）
//   this+44 防重入检查后调 this+104 对象 vt+36(this+96, 0, 0)，置 this+44 = 1。
// ------------------------------------------------------------
int /*thiscall*/ sub_413840(int this)
{
  if ( *(uint8_t *)(this + 44) != 0 )
    return -2147483642;
  (*(void (/*stdcall*/ **)(uint32_t, int, uint32_t, uint32_t))(**(uint32_t **)(this + 104) + 36))(
    *(uint32_t *)(this + 104),
    this + 96,
    0,
    0);
  *(uint8_t *)(this + 44) = 1;
  return 1;
}



// ------------------------------------------------------------
// 0x413870 sub_413870 —— 图像解锁（vt+40）
//   —— 与 ·sub_413840 同构（差异：调 vt+40 解锁并清 this+44；未加锁返回 0x80000007）。
// ------------------------------------------------------------
int /*thiscall*/ sub_413870(int this)
{
  if ( *(uint8_t *)(this + 44) == 0 )
    return -2147483641;
  (*(void (/*stdcall*/ **)(uint32_t))(**(uint32_t **)(this + 104) + 40))(*(uint32_t *)(this + 104));
  *(uint8_t *)(this + 44) = 0;
  return 1;
}



// ------------------------------------------------------------
// 0x4138A0 sub_4138A0 —— 格式分派 Blt（3 / 7）
//   pArg4[2] 为 3 时把 this+80 区域交对象 vt+112（源取 pArg4[26]）；为 7 时源取 pArg4[32]。
// ------------------------------------------------------------
int /*thiscall*/ sub_4138A0(int this, int nArg2, int nArg3, uint32_t *pArg4)
{
  int result; // eax
  int fld_68; // [esp-8h] [ebp-18h]
  int fld_682; // [esp-8h] [ebp-18h]
  int nArg22; // [esp+8h] [ebp-8h] BYREF
  int nArg32; // [esp+Ch] [ebp-4h]

  result = pArg4[2];
  if ( result == 3 )
  {
    nArg22 = nArg2;
    fld_68 = *(uint32_t *)(this + 104);
    nArg32 = nArg3;
    return (*(int (/*stdcall*/ **)(uint32_t, uint32_t, int, int, int, int *))(**(uint32_t **)(this + 108) + 112))(
             *(uint32_t *)(this + 108),
             pArg4[26],
             this + 80,
             1,
             fld_68,
             &nArg22);
  }
  else if ( result == 7 )
  {
    nArg22 = nArg2;
    fld_682 = *(uint32_t *)(this + 104);
    nArg32 = nArg3;
    return (*(int (/*stdcall*/ **)(uint32_t, uint32_t, int, int, int, int *))(**(uint32_t **)(this + 108) + 112))(
             *(uint32_t *)(this + 108),
             pArg4[32],
             this + 80,
             1,
             fld_682,
             &nArg22);
  }
  return result;
}



// ------------------------------------------------------------
// 0x413920 sub_413920 —— 存盘为 1 字节/像素（8bpp 模板）
//   写 4B 标志 0、宽高，再写 256 项 4B 调色板（全 0），逐像素按 R5G6B5 非零输出 0xFF/0x00【推断：模板存盘】。
// ------------------------------------------------------------
int /*thiscall*/ sub_413920(unsigned int *this, FILE *Stream)
{
  int i; // ebx
  int fld_e6; // eax
  unsigned int v5; // ebx
  unsigned int fld_e5; // eax
  unsigned int j; // edi
  unsigned int fld_e62; // ecx
  unsigned int v10; // [esp+Ch] [ebp-14h]
  unsigned int v11; // [esp+Ch] [ebp-14h]
  unsigned int v12; // [esp+Ch] [ebp-14h]
  int v13; // [esp+10h] [ebp-10h] BYREF
  int Buffer; // [esp+14h] [ebp-Ch] BYREF
  int v15; // [esp+18h] [ebp-8h]
  char v16; // [esp+1Fh] [ebp-1h] BYREF

  Buffer = 0;
  sub_66BC25(&Buffer, 4u, 1u, Stream);
  v13 = 0;
  sub_66BC25(this + 5, 4u, 1u, Stream);
  sub_66BC25(this + 6, 4u, 1u, Stream);
  for ( i = 256; i != 0; --i )
    sub_66BC25(&v13, 4u, 1u, Stream);
  fld_e6 = *(this + 6);
  v5 = 0;
  v15 = 0;
  if ( fld_e6 != 0 )
  {
    fld_e5 = *(this + 5);
    do
    {
      for ( j = 0; j < fld_e5; ++j )
      {
        v10 = ((unsigned int)(*(int (/*thiscall*/ **)(unsigned int *, unsigned int, unsigned int))(*this + 64))(
                               this,
                               j,
                               v5) >> 6)
            & 0x3E0;
        v11 = ((unsigned int)(*(int (/*thiscall*/ **)(unsigned int *, unsigned int, unsigned int))(*this + 64))(
                               this,
                               j,
                               v5) >> 19)
            & 0x1F
            | v10;
        v12 = ((unsigned int)(*(int (/*thiscall*/ **)(unsigned int *, unsigned int, int))(*this + 64))(this, j, v15) >> 16)
            & 0x8000
            | v11;
        v16 = -(((((*(int (/*thiscall*/ **)(unsigned int *, unsigned int, int))(*this + 64))(this, j, v15) & 0xF8) << 7)
               | (uint16_t)v12) != 0);
        sub_66BC25(&v16, 1u, 1u, Stream);
        fld_e5 = *(this + 5);
        v5 = v15;
      }
      fld_e62 = *(this + 6);
      v15 = ++v5;
    }
    while ( v5 < fld_e62 );
  }
  (*(void (/*thiscall*/ **)(unsigned int *))(*this + 88))(this);
  return 1;
}



// ------------------------------------------------------------
// 0x413A60 sub_413A60 —— 读入 1 字节/像素并展开 ARGB
//   与 ·sub_413920 对称：标志须为 0，读宽高、跳过 256 项调色板，逐行读 w 字节；
//   每字节按 b|b<<8|b<<16|b<<24 展开为灰阶 ARGB 交 vt+32 写入。
// ------------------------------------------------------------
int /*thiscall*/ sub_413A60(size_t *this, FILE *Stream)
{
  FILE *v3; // esi
  size_t *pThis_5; // ebx
  int fld_e6; // eax
  size_t v6; // eax
  size_t j; // esi
  unsigned int fld_e62; // edx
  int v10; // [esp+Ch] [ebp-10h] BYREF
  int Buffer; // [esp+10h] [ebp-Ch] BYREF
  void *Block; // [esp+14h] [ebp-8h]
  int i; // [esp+18h] [ebp-4h]

  (*(void (/*thiscall*/ **)(size_t *))(*this + 84))(this);
  (*(void (/*thiscall*/ **)(size_t *, uint32_t))(*this + 28))(this, 0);
  v3 = Stream;
  Buffer = 0;
  sub_66BD5A(&Buffer, 4u, 1u, Stream);  // 【fread封装】
  if ( Buffer == 0 )
  {
    v10 = 0;
    pThis_5 = this + 5;
    sub_66BD5A(this + 5, 4u, 1u, Stream);  // 【fread封装】
    sub_66BD5A(this + 6, 4u, 1u, Stream);  // 【fread封装】
    Block = operator new(*(this + 5));
    for ( i = 256; i != 0; --i )
      sub_66BD5A(&v10, 4u, 1u, Stream);  // 【fread封装】
    fld_e6 = *(this + 6);
    i = 0;
    if ( fld_e6 != 0 )
    {
      v6 = *pThis_5;
      while ( 1 )
      {
        sub_66BD5A(Block, v6, 1u, v3);  // 【fread封装】
        v6 = *pThis_5;
        for ( j = 0; j < *pThis_5; ++j )
        {
          (*(void (/*thiscall*/ **)(size_t *, size_t, int, int))(*this + 32))(
            this,
            j,
            i,
            *((uint8_t *)Block + j)
          | ((*((uint8_t *)Block + j)
            | ((*((uint8_t *)Block + j) | (*((uint8_t *)Block + j) << 8)) << 8)) << 8));
          v6 = *pThis_5;
        }
        fld_e62 = *(this + 6);
        if ( ++i >= fld_e62 )
          break;
        v3 = Stream;
      }
    }
    if ( Block != nullptr )
      j_j__free(Block);
  }
  (*(void (/*thiscall*/ **)(size_t *))(*this + 88))(this);
  return 1;
}



// ============================================================
// SECTION 0x413B80 — 图像对象构造/克隆（SetRect + 容器分配）
// ============================================================
// ------------------------------------------------------------
// 0x413B80 sub_413B80 —— 由源表面构造图像对象
//   源 Block 虚表 +64 建图到 this+128，源指针存 this+120 并置共享标志 this+76 = 1；查询尺寸 SetRect；
//   new 0x70 容器经 sub_4089B0(容器, 3, Block) 包装，再 sub_413670 绑定尺寸行表 → this+27。
// ------------------------------------------------------------
int /*thiscall*/ sub_413B80(char *this, void *Block)  // 【图像对象构造/克隆（SetRect + 容器分配）】
{
  int result; // eax
  int *pThis_80; // edi
  int v6; // ecx
  void *pMem; // eax
  int *v8; // ebx
  int v9; // [esp-10h] [ebp-40h]
  int v10; // [esp-Ch] [ebp-3Ch]
  int pBuf[6]; // [esp+4h] [ebp-2Ch] BYREF
  int xRight; // [esp+1Ch] [ebp-14h]
  int yBottom; // [esp+20h] [ebp-10h]
  int v14; // [esp+2Ch] [ebp-4h]
  void *Blocka; // [esp+38h] [ebp+8h]

  if ( *(this + 4) != 0 )
    return -2147483646;
  pThis_80 = (int *)(this + 128);
  *(this + 4) = 1;
  *((uint32_t *)this + 30) = Block;
  *(this + 76) = 1;
  Blocka = (void *)(*(int (/*stdcall*/ **)(void *, uint32_t, uint32_t, char *))(*(uint32_t *)Block + 64))(
                     Block,
                     0,
                     0,
                     this + 128);
  if ( (int)Blocka >= 0 )
  {
    memset(pBuf, 0, sizeof(pBuf));
    xRight = 0;
    yBottom = 0;
    (*(void (/*stdcall*/ **)(int, int *))(*(uint32_t *)*pThis_80 + 32))(*pThis_80, pBuf);
    v6 = yBottom;
    v10 = yBottom;
    v9 = xRight;
    *((uint32_t *)this + 5) = xRight;
    *((uint32_t *)this + 6) = v6;
    SetRect((LPRECT)(this + 84), 0, 0, v9, v10);
    SetRect((LPRECT)this + 3, 0, 0, *((uint32_t *)this + 5), *((uint32_t *)this + 6));
    pMem = operator new(0x70u);
    v14 = 0;
    if ( pMem != nullptr )
      v8 = (int *)sub_4089B0((int)pMem, 3, (int)Block);
    else
      v8 = nullptr;
    v14 = -1;
    if ( v8 != nullptr )
    {
      result = sub_413670(v8, *pThis_80);
      if ( result >= 0 )
      {
        *((uint32_t *)this + 27) = v8;
        return 1;
      }
    }
    else
    {
      (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)this + 20))(this);
      return -2147483640;
    }
  }
  else
  {
    (*(void (/*thiscall*/ **)(char *))(*(uint32_t *)this + 20))(this);
    return (int)Blocka;
  }
  return result;
}



// ------------------------------------------------------------
// 0x413CE0 sub_413CE0 —— 图像对象析构（三对象释放）
//   释放 this+128 图（vt+8）与 this+108 容器（虚表首槽(self, 1)）；非共享（this+76 == 0）再释放 this+120；
//   清 this+12/16/128 与就绪位 this+4。
// ------------------------------------------------------------
int /*thiscall*/ sub_413CE0(int this)
{
  int fld_80; // eax
  void (/*thiscall*/ ***pThis_6C)(uint32_t, int); // ecx
  bool fld_4C; // zf
  int fld_78; // eax

  fld_80 = *(uint32_t *)(this + 128);
  if ( fld_80 != 0 )
    (*(void (/*stdcall*/ **)(int))(*(uint32_t *)fld_80 + 8))(fld_80);
  pThis_6C = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 108);
  *(uint32_t *)(this + 128) = 0;
  if ( pThis_6C != nullptr )
    (**pThis_6C)(pThis_6C, 1);
  fld_4C = *(uint8_t *)(this + 76) == 0;
  *(uint32_t *)(this + 108) = 0;
  if ( fld_4C )
  {
    fld_78 = *(uint32_t *)(this + 120);
    if ( fld_78 != 0 )
      (*(void (/*stdcall*/ **)(uint32_t))(*(uint32_t *)fld_78 + 8))(*(uint32_t *)(this + 120));
    *(uint32_t *)(this + 120) = 0;
  }
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 128) = 0;
  *(uint8_t *)(this + 4) = 0;
  return 1;
}



// ------------------------------------------------------------
// 0x413D40 sub_413D40 —— 行指针表重建（像素步长变体）
//   —— 与 ·sub_411FD0 同构（差异：行 = this+12 + 4*行号*this+80）。
// ------------------------------------------------------------
int /*thiscall*/ sub_413D40(int this)
{
  uint32_t *pMem; // eax
  int fld_182; // ebx
  unsigned int v5; // ecx
  int v6; // edx
  int fld_C; // edi
  size_t fld_18; // [esp-4h] [ebp-8h]

  if ( *(uint32_t *)(this + 12) == 0 )
    return -2147483647;
  if ( *(uint32_t *)(this + 16) != 0 )
    j_j__free(*(void **)(this + 16));
  fld_18 = 4 * *(uint32_t *)(this + 24);
  *(uint32_t *)(this + 16) = 0;
  pMem = operator new(fld_18);
  if ( pMem == nullptr )
    return -2147483640;
  fld_182 = *(uint32_t *)(this + 24);
  v5 = 0;
  v6 = 0;
  fld_C = *(uint32_t *)(this + 12);
  *(uint32_t *)(this + 16) = pMem;
  if ( fld_182 != 0 )
  {
    do
    {
      pMem[v5] = fld_C + 4 * v6;
      v6 += *(uint32_t *)(this + 80);
      ++v5;
    }
    while ( v5 < *(uint32_t *)(this + 24) );
  }
  return 1;
}



// ------------------------------------------------------------
// 0x413DB0 sub_413DB0 —— 设置透明色键（vt+144）
//   交 this+120 对象 vt+144(0, 0, 模式, 重排色 nArg2, 0, 0)；模式由 this+112+8268 标志取 1 或 3。
// ------------------------------------------------------------
int /*thiscall*/ sub_413DB0(int this, int nArg2)
{
  int v2; // edx

  v2 = 1;
  if ( *(uint8_t *)(*(uint32_t *)(this + 112) + 8268) != 0 )
    v2 = 3;
  return (*(int (/*stdcall*/ **)(uint32_t, uint32_t, uint32_t, int, unsigned int, uint32_t, uint32_t))(**(uint32_t **)(this + 120)
                                                                                         + 144))(
           *(uint32_t *)(this + 120),
           0,
           0,
           v2,
           nArg2 & 0xFF00FF00 | ((uint8_t)nArg2 << 16) | BYTE2(nArg2),
           0,
           0);
}



// ------------------------------------------------------------
// 0x413E10 sub_413E10 —— 显示资源加锁
//   this+77 防重入；this+120 vt+136 与 this+124 vt+16 加锁，置 this+77 = 1。
// ------------------------------------------------------------
int /*thiscall*/ sub_413E10(int this)
{
  if ( *(uint8_t *)(this + 77) != 0 )
    return -2147483642;
  (*(void (/*stdcall*/ **)(uint32_t))(**(uint32_t **)(this + 120) + 136))(*(uint32_t *)(this + 120));
  (*(void (/*stdcall*/ **)(uint32_t))(**(uint32_t **)(this + 124) + 16))(*(uint32_t *)(this + 124));
  *(uint8_t *)(this + 77) = 1;
  return 1;
}



// ------------------------------------------------------------
// 0x413E40 sub_413E40 —— 显示资源解锁
//   —— 与 ·sub_413E10 同构（差异：this+124 vt+28 与 this+120 vt+140 解锁，清 this+77）。
// ------------------------------------------------------------
int /*thiscall*/ sub_413E40(int this)
{
  if ( *(uint8_t *)(this + 77) == 0 )
    return -2147483641;
  (*(void (/*stdcall*/ **)(uint32_t))(**(uint32_t **)(this + 124) + 28))(*(uint32_t *)(this + 124));
  (*(void (/*stdcall*/ **)(uint32_t))(**(uint32_t **)(this + 120) + 140))(*(uint32_t *)(this + 120));
  *(uint8_t *)(this + 77) = 0;
  return 1;
}



// ------------------------------------------------------------
// 0x413E80 sub_413E80 —— 3 号格式共享挂接
//   pArg4[2] == 3 时把 (nArg2, nArg3, this+27 容器) 交 pArg4 vt+152 挂接。
// ------------------------------------------------------------
int /*thiscall*/ sub_413E80(uint32_t *this, int nArg2, int nArg3, uint32_t *pArg4)
{
  int result; // eax

  result = (int)pArg4;
  if ( pArg4[2] == 3 )
    return (*(int (/*thiscall*/ **)(uint32_t *, int, int, uint32_t))(*pArg4 + 152))(pArg4, nArg2, nArg3, *(this + 27));
  return result;
}



// ------------------------------------------------------------
// 0x413EB0 sub_413EB0 —— 绑定日志输出接口
//   一次性把 this+64 设为 nArg2 并置 this+45（·sub_414200 日志转发即读 this+45/64 直证）。
// ------------------------------------------------------------
char /*thiscall*/ sub_413EB0(int this, int nArg2)
{
  char result; // al

  result = *(uint8_t *)(this + 45);
  if ( result == 0 )
  {
    *(uint32_t *)(this + 64) = nArg2;
    *(uint8_t *)(this + 45) = 1;
    return nArg2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x413ED0 sub_413ED0 —— 解除日志输出接口绑定
//   —— 与 ·sub_413EB0 配对（差异：清 this+64 与 this+45）。
// ------------------------------------------------------------
int /*thiscall*/ sub_413ED0(int this)
{
  int result; // eax

  result = 0;
  if ( *(uint8_t *)(this + 45) != 0 )
  {
    *(uint32_t *)(this + 64) = 0;
    *(uint8_t *)(this + 45) = 0;
  }
  return result;
}



// ============================================================
// SECTION 0x413EE0 — 窗口尺寸调整族（GetWindowLong/GetSystemMetrics/AdjustWindowRectEx/SetWindowPos）
// ============================================================
// ------------------------------------------------------------
// 0x413EE0 sub_413EE0
// ------------------------------------------------------------
// 【解读】
//   主窗口尺寸调整（客户区→窗口矩形）: GetWindowLongA 风格 + GetSystemMetrics + AdjustWindowRectEx + SetWindowPos。0x414090 为带边框变体。
// ------------------------------------------------------------
int /*thiscall*/ sub_413EE0(int this, DWORD dwExStyle, char pszArg3)  // 【窗口尺寸调整族（GetWindowLong/GetSystemMetrics/Adj…】
{
  int result; // eax
  int fld_80; // eax
  int *pThis_80; // edi
  int fld_78; // eax
  int fld_6C; // edi
  int fld_84; // ecx
  int fld_14; // edi
  int SystemMetrics; // eax
  LONG fld_142; // edx
  int v13; // ebx
  struct tagRECT Rect; // [esp+8h] [ebp-18h] BYREF
  int fld_6C2; // [esp+18h] [ebp-8h]
  DWORD dwStyle; // [esp+1Ch] [ebp-4h]
  LONG dwExStylea; // [esp+28h] [ebp+8h]
  unsigned int fld_18; // [esp+2Ch] [ebp+Ch]

  if ( (*(int (/*stdcall*/ **)(uint32_t))(**(uint32_t **)(this + 120) + 12))(*(uint32_t *)(this + 120)) != -2005530519 )
  {
    if ( pszArg3 == 0 )
      return -2147483645;
  }
  else if ( pszArg3 == 0 )
  {
    fld_80 = *(uint32_t *)(this + 128);
    pThis_80 = (int *)(this + 128);
    if ( fld_80 != 0 )
      (*(void (/*stdcall*/ **)(uint32_t))(*(uint32_t *)fld_80 + 8))(*(uint32_t *)(this + 128));
    fld_78 = *(uint32_t *)(this + 120);
    *pThis_80 = 0;
    result = (*(int (/*stdcall*/ **)(int, DWORD))(*(uint32_t *)fld_78 + 56))(fld_78, dwExStyle);
    if ( result >= 0 )
    {
      result = (*(int (/*stdcall*/ **)(uint32_t, uint32_t, uint32_t, int))(**(uint32_t **)(this + 120) + 64))(
                 *(uint32_t *)(this + 120),
                 0,
                 0,
                 this + 128);
      if ( result >= 0 )
      {
        (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 108) + 20))(*(uint32_t *)(this + 108));
        fld_6C = sub_413670(*(int **)(this + 108), *pThis_80);
        fld_6C2 = fld_6C;
        if ( fld_6C >= 0 )
        {
          (*(void (/*stdcall*/ **)(uint32_t))(**(uint32_t **)(this + 124) + 36))(*(uint32_t *)(this + 124));
          fld_84 = *(uint32_t *)(this + 132);
          if ( *(uint32_t *)(dwExStyle + 28) != 0 )
          {
            sub_404590((uint32_t *)fld_84, -1, -1);
            dwStyle = GetWindowLongA(*(HWND *)(*(uint32_t *)(this + 132) + 16), -16);
            dwExStylea = GetWindowLongA(*(HWND *)(*(uint32_t *)(this + 132) + 16), -20);
            fld_14 = (GetSystemMetrics(0) >> 1) - (*(uint32_t *)(this + 20) >> 1);
            fld_18 = *(uint32_t *)(this + 24);
            SystemMetrics = GetSystemMetrics(1);
            fld_142 = *(uint32_t *)(this + 20);
            Rect.bottom = fld_18;
            v13 = (SystemMetrics >> 1) - (fld_18 >> 1);
            Rect.left = 0;
            Rect.top = 0;
            Rect.right = fld_142;
            AdjustWindowRectEx(&Rect, dwStyle, false, dwExStylea);
            SetWindowPos(
              *(HWND *)(*(uint32_t *)(this + 132) + 16),
              (HWND)0xFFFFFFFE,
              fld_14,
              v13,
              Rect.right - Rect.left,
              Rect.bottom - Rect.top,
              0x40u);
            return fld_6C2;
          }
          SetWindowPos(*(HWND *)(fld_84 + 16), HWND_MESSAGE|0x2, 0, 0, 0, 0, 3u);
        }
        return fld_6C;
      }
    }
    return result;
  }
  (*(void (/*stdcall*/ **)(uint32_t, DWORD))(**(uint32_t **)(this + 120) + 56))(*(uint32_t *)(this + 120), dwExStyle);
  return (*(int (/*stdcall*/ **)(uint32_t, DWORD))(**(uint32_t **)(this + 120) + 56))(*(uint32_t *)(this + 120), dwExStyle);
}



// ------------------------------------------------------------
// 0x414090 sub_414090 —— 窗口尺寸调整（带边框变体）
//   既有解读定为带边框变体；与 ·sub_413EE0 同构，略去设备状态前置判断、pszArg3 参数与尾部双调用。
//   vt+56 换显示模式 → vt+64 重建 → sub_413670 重绑 → 依 pArg2+28 隐藏（SetWindowPos 3）或居中（AdjustWindowRectEx）。
// ------------------------------------------------------------
int /*thiscall*/ sub_414090(int this, int pArg2)
{
  int fld_80; // eax
  int *pThis_80; // edi
  int fld_78; // eax
  int result; // eax
  int fld_84; // ecx
  int fld_14; // edi
  int SystemMetrics; // eax
  LONG fld_142; // edx
  int v11; // ebx
  struct tagRECT Rect; // [esp+Ch] [ebp-18h] BYREF
  DWORD dwStyle; // [esp+1Ch] [ebp-8h]
  DWORD dwExStyle; // [esp+20h] [ebp-4h]
  unsigned int fld_18; // [esp+2Ch] [ebp+8h]

  (*(void (/*stdcall*/ **)(uint32_t))(**(uint32_t **)(this + 120) + 12))(*(uint32_t *)(this + 120));
  fld_80 = *(uint32_t *)(this + 128);
  pThis_80 = (int *)(this + 128);
  if ( fld_80 != 0 )
    (*(void (/*stdcall*/ **)(uint32_t))(*(uint32_t *)fld_80 + 8))(*(uint32_t *)(this + 128));
  fld_78 = *(uint32_t *)(this + 120);
  *pThis_80 = 0;
  result = (*(int (/*stdcall*/ **)(int, int))(*(uint32_t *)fld_78 + 56))(fld_78, pArg2);
  if ( result >= 0 )
  {
    result = (*(int (/*stdcall*/ **)(uint32_t, uint32_t, uint32_t, int))(**(uint32_t **)(this + 120) + 64))(
               *(uint32_t *)(this + 120),
               0,
               0,
               this + 128);
    if ( result >= 0 )
    {
      (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 108) + 20))(*(uint32_t *)(this + 108));
      result = sub_413670(*(int **)(this + 108), *pThis_80);
      if ( result >= 0 )
      {
        (*(void (/*stdcall*/ **)(uint32_t))(**(uint32_t **)(this + 124) + 36))(*(uint32_t *)(this + 124));
        fld_84 = *(uint32_t *)(this + 132);
        if ( *(uint32_t *)(pArg2 + 28) != 0 )
        {
          sub_404590((uint32_t *)fld_84, -1, -1);
          dwStyle = GetWindowLongA(*(HWND *)(*(uint32_t *)(this + 132) + 16), -16);
          dwExStyle = GetWindowLongA(*(HWND *)(*(uint32_t *)(this + 132) + 16), -20);
          fld_14 = (GetSystemMetrics(0) >> 1) - (*(uint32_t *)(this + 20) >> 1);
          fld_18 = *(uint32_t *)(this + 24);
          SystemMetrics = GetSystemMetrics(1);
          fld_142 = *(uint32_t *)(this + 20);
          Rect.bottom = fld_18;
          v11 = (SystemMetrics >> 1) - (fld_18 >> 1);
          Rect.left = 0;
          Rect.top = 0;
          Rect.right = fld_142;
          AdjustWindowRectEx(&Rect, dwStyle, false, dwExStyle);
          SetWindowPos(
            *(HWND *)(*(uint32_t *)(this + 132) + 16),
            (HWND)0xFFFFFFFE,
            fld_14,
            v11,
            Rect.right - Rect.left,
            Rect.bottom - Rect.top,
            0x40u);
        }
        else
        {
          SetWindowPos(*(HWND *)(fld_84 + 16), HWND_MESSAGE|0x2, 0, 0, 0, 0, 3u);
        }
        return 1;
      }
    }
  }
  return result;
}



// ============================================================
// SECTION 0x414200 — 引擎日志格式化转发（vsprintf → 0x404B30 缓冲）
// ============================================================
// ------------------------------------------------------------
// 0x414200 sub_414200
// ------------------------------------------------------------
// 【解读】
//   引擎格式化日志转发: vsprintf → sub_404B30（安全拷贝）→ sub_404E30 —— off_77F3FC 日志指针的落地实现之一【推断】。
// ------------------------------------------------------------
char sub_414200(int pArg1, int nArg2, int nArg3, int nArg4, char *Format, ...)
{
  int v5; // eax
  int v6; // esi
  int v7; // eax
  int v8; // ecx
  int nLen; // ebx
  int v10; // edi
  uint8_t v12[204800]; // [esp+4h] [ebp-33014h] BYREF
  int v13; // [esp+32004h] [ebp-1014h]
  const char *psz; // [esp+32008h] [ebp-1010h]
  int v15; // [esp+3200Ch] [ebp-100Ch]
  int i; // [esp+32010h] [ebp-1008h]
  char Buffer[4096]; // [esp+32014h] [ebp-1004h] BYREF
  int dword_796E502; // [esp+33014h] [ebp-4h]
  va_list va; // [esp+33034h] [ebp+1Ch] BYREF

  va_start(va, Format);
  dword_796E502 = dword_796E50;
  LOBYTE(v5) = *(uint8_t *)(pArg1 + 45);
  if ( (uint8_t)v5 != 0 )
  {
    v5 = *(uint32_t *)(pArg1 + 64);
    if ( v5 != 0 )
    {
      vsprintf(Buffer, Format, va);
      v6 = *(uint32_t *)(pArg1 + 64);
      v15 = sub_404B30(v12, Buffer, v6);
      v7 = *(uint32_t *)(pArg1 + 64);
      v8 = *(uint32_t *)(v7 + 32);
      v13 = *(uint32_t *)(v7 + 48);
      if ( v8 != 0 )
        v15 = *(uint32_t *)(v7 + 32);
      LOBYTE(v5) = v15;
      for ( i = 0; i < v15; ++i )
      {
        psz = &v12[1024 * (i + *(uint32_t *)(v6 + 24))];
        nLen = nArg2 + sub_404E30(v6, strlen(psz));
        v10 = nArg3 + i * (*(uint32_t *)(v6 + 20) + *(uint32_t *)(v6 + 36) + 2);
        unknown_libname_3(
          v13,
          pArg1,
          nLen,
          v10,
          nArg4,
          *(uint8_t *)(v6 + 2),
          *(uint8_t *)(v6 + 1),
          *(uint32_t *)(v6 + 4),
          *(uint32_t *)(v6 + 8),
          1065353216,
          1065353216,
          psz);
        if ( *(uint8_t *)v6 != 0 )
          unknown_libname_3(
            v13,
            pArg1,
            nLen + 1,
            v10,
            nArg4,
            *(uint8_t *)(v6 + 2),
            *(uint8_t *)(v6 + 1),
            *(uint32_t *)(v6 + 4),
            *(uint32_t *)(v6 + 8),
            1065353216,
            1065353216,
            psz);
        LOBYTE(v5) = i + 1;
      }
    }
  }
  return v5;
}



// ============================================================
// SECTION 0x4143A0 — 对象销毁/容器壳
// ============================================================
// ------------------------------------------------------------
// 0x4143A0 sub_4143A0 —— 图像对象构造（设备指针族绑定）
//   vftable 依次挂 off_6C1BE8 → off_6C28D8，经 sub_40F360 初始化；
//   this+112 存引擎对象 pArg3，this+116/120/124 取 pArg3[2062..2064]（设备接口三件套）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4143A0(int this, int nArg2, uint32_t *pArg3)  // 【对象销毁/容器壳】
{
  *(uint8_t *)(this + 4) = 0;
  *(uint32_t *)this = &off_6C1BE8;
  *(uint32_t *)(this + 8) = nArg2;
  sub_40F360((uint32_t *)this);
  *(uint32_t *)(this + 120) = 0;
  *(uint32_t *)(this + 112) = pArg3;
  *(uint8_t *)(this + 76) = 0;
  *(uint8_t *)(this + 77) = 0;
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 128) = 0;
  *(uint32_t *)this = &off_6C28D8;
  *(uint32_t *)(this + 84) = 0;
  *(uint32_t *)(this + 88) = 0;
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  *(uint32_t *)(this + 100) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint32_t *)(this + 108) = 0;
  *(uint32_t *)(this + 116) = pArg3[2062];
  *(uint32_t *)(this + 120) = pArg3[2063];
  *(uint32_t *)(this + 124) = pArg3[2064];
  return this;
}



// ------------------------------------------------------------
// 0x414450 sub_414450 —— 空桩（恒返 0x80000002）
//   恒返回 0x80000002（未实现/禁用占位）【推断】。
// ------------------------------------------------------------
int /*stdcall*/ sub_414450(int nArg1, int nArg2)
{
  return -2147483646;
}



// ------------------------------------------------------------
// 0x414460 sub_414460 —— 析构加释放壳
//   —— 与 ·sub_414C40 同构（差异：析构体为 ·sub_414490）；pszArg2 位 0 置位时 free。
// ------------------------------------------------------------
void */*thiscall*/ sub_414460(void *Block, char pszArg2)
{
  sub_414490();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x414490 sub_414490 —— 图像对象析构链
//   vftable 6C28D8 → sub_413CE0（释放三对象）→ 6C1BE8 → sub_40F3B0 → IObject 基类并清 this+4。
// ------------------------------------------------------------
int /*thiscall*/ sub_414490(uint8_t *this)
{
  int result; // eax

  *(uint32_t *)this = &off_6C28D8;
  sub_413CE0((int)this);
  *(uint32_t *)this = &off_6C1BE8;
  result = sub_40F3B0(this);
  *(uint32_t *)this = &nengine::IObject::`vftable';
  *(this + 4) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x4144F0 sub_4144F0 —— 状态清零（this+12..48）
//   清 this+12/13/14/16/20/48 六字段并返回 0（构造前置零）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4144F0(int this)
{
  *(uint8_t *)(this + 12) = 0;
  *(uint8_t *)(this + 13) = 0;
  *(uint8_t *)(this + 14) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 48) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x414510 sub_414510 —— 释放日志接口容器
//   this+48 非空则虚表首槽(self, 1) 释放，清 this+48 与 this+4。
// ------------------------------------------------------------
int /*thiscall*/ sub_414510(int this)
{
  int (/*thiscall*/ ***pThis_30)(uint32_t, int); // ecx
  int result; // eax

  pThis_30 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 48);
  if ( pThis_30 != nullptr )
    result = (**pThis_30)(pThis_30, 1);
  *(uint32_t *)(this + 48) = 0;
  *(uint8_t *)(this + 4) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x414530 sub_414530 —— 注册到 this+44 管理器
//   就绪检查后 sub_4081C0(this+44, this) 注册，置 this+13 标志位。
// ------------------------------------------------------------
int /*thiscall*/ sub_414530(int this)
{
  if ( *(uint8_t *)(this + 4) == 0 )
    return -2147483647;
  sub_4081C0(*(uint32_t *)(this + 44), this);
  *(uint16_t *)(this + 13) = 1;
  return 1;
}



// ------------------------------------------------------------
// 0x414560 sub_414560 —— 清 13.14.15 三字段
//   清 this[13]/[14]/[15] 并返回 0。
// ------------------------------------------------------------
int /*thiscall*/ sub_414560(uint32_t *this)
{
  *(this + 13) = 0;
  *(this + 14) = 0;
  *(this + 15) = 0;
  return 0;
}



// ============================================================
// SECTION 0x414570 — 声音对象/WAV 缓冲族（0x4149E0 mmio WAV→DirectSound 装载）
// ============================================================
// ------------------------------------------------------------
// 0x414570 sub_414570 —— 声音槽位表分配
//   this+4 防重入；new 4*n 指针表存 this+52 并清零，this+20 = n 槽位数。
// ------------------------------------------------------------
int /*thiscall*/ sub_414570(int this, int nArg2)
{
  void *pMem; // eax
  unsigned int i; // eax

  if ( *(uint8_t *)(this + 4) != 0 )
    return -2147483646;
  *(uint32_t *)(this + 20) = nArg2;
  pMem = operator new(4 * nArg2);
  *(uint32_t *)(this + 52) = pMem;
  if ( pMem == nullptr )
    return -2147483640;
  for ( i = 0; i < *(uint32_t *)(this + 20); ++i )
    *(uint32_t *)(*(uint32_t *)(this + 52) + 4 * i) = 0;
  *(uint8_t *)(this + 4) = 1;
  return 1;
}



// ------------------------------------------------------------
// 0x4145E0 sub_4145E0 —— 声音槽位表释放
//   逐槽对象 vt+8 释放后 free 槽表，清 this+52/56/60 与 this+4。
// ------------------------------------------------------------
int /*thiscall*/ sub_4145E0(int this)
{
  unsigned int i; // edi
  int fld_34; // ecx

  for ( i = 0; i < *(uint32_t *)(this + 20); ++i )
  {
    fld_34 = *(uint32_t *)(*(uint32_t *)(this + 52) + 4 * i);
    if ( fld_34 != 0 )
      (*(void (/*stdcall*/ **)(int))(*(uint32_t *)fld_34 + 8))(fld_34);
    *(uint32_t *)(*(uint32_t *)(this + 52) + 4 * i) = 0;
  }
  if ( *(uint32_t *)(this + 52) != 0 )
    j_j__free(*(void **)(this + 52));
  *(uint32_t *)(this + 52) = 0;
  *(uint32_t *)(this + 56) = 0;
  *(uint32_t *)(this + 60) = 0;
  *(uint8_t *)(this + 4) = 0;
  return 1;
}



// ------------------------------------------------------------
// 0x414640 sub_414640 —— 选取空闲缓冲并播放（轮转）
//   遍历缓冲槽位表（this+52，count this+20）经虚表 +36 取状态（bit0 = 播放中）【推断：DirectSound 缓冲虚表】；
//   找到未在播槽位后交 +48（Play 槽位）以 (0, 0, 0) 启动；无空闲时 this+12 非 0 直接返回，否则自身 vt+32(0) 后播首槽。
// ------------------------------------------------------------
int /*thiscall*/ sub_414640(uint8_t *this)
{
  int pThis_5; // eax
  int v4; // edi
  int pThis_D; // [esp-14h] [ebp-1Ch]
  int v6; // [esp+4h] [ebp-4h] BYREF

  if ( *(this + 4) == 0 )
    return -2147483647;
  pThis_5 = *((uint32_t *)this + 5);
  v4 = 0;
  v6 = 0;
  if ( pThis_5 == 0 )
  {
LABEL_8:
    if ( *(this + 12) != 0 )
    {
      if ( (*(int (/*stdcall*/ **)(uint32_t, int *))(***((uint32_t ***)this + 13) + 36))(**((uint32_t **)this + 13), &v6) < 0
        || (v6 & 1) != 0 && v6 != 0 )
      {
        return 1;
      }
    }
    else
    {
      (*(void (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 32))(this, 0);
    }
    (*(void (/*stdcall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t))(***((uint32_t ***)this + 13) + 48))(
      **((uint32_t **)this + 13),
      0,
      0,
      0);
    return 1;
  }
  while ( (*(int (/*stdcall*/ **)(uint32_t, int *))(**(uint32_t **)(*((uint32_t *)this + 13) + 4 * v4) + 36))(
            *(uint32_t *)(*((uint32_t *)this + 13) + 4 * v4),
            &v6) < 0
       || (v6 & 1) != 0 && v6 != 0 )
  {
    if ( (unsigned int)++v4 >= *((uint32_t *)this + 5) )
      goto LABEL_8;
  }
  pThis_D = *(uint32_t *)(*((uint32_t *)this + 13) + 4 * v4);
  (*(void (/*stdcall*/ **)(int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)pThis_D + 48))(pThis_D, 0, 0, 0);
  return 1;
}



// ------------------------------------------------------------
// 0x414700 sub_414700 —— 全部停止并复位
//   遍历槽位表（this+52，count this+20）逐个交 vt+72（Stop 槽位）停止；自身 vt+32(0)，置标志 13 = 0、14 = 1。
// ------------------------------------------------------------
int /*thiscall*/ sub_414700(uint8_t *this)
{
  unsigned int i; // edi

  if ( *(this + 4) == 0 )
    return -2147483647;
  for ( i = 0; i < *((uint32_t *)this + 5); ++i )
    (*(void (/*stdcall*/ **)(uint32_t))(**(uint32_t **)(*((uint32_t *)this + 13) + 4 * i) + 72))(*(uint32_t *)(*((uint32_t *)this + 13) + 4 * i));
  (*(void (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 32))(this, 0);
  *(this + 13) = 0;
  *(this + 14) = 1;
  return 1;
}



// ------------------------------------------------------------
// 0x414750 sub_414750 —— 全部停止（无自身调用变体）
//   —— 与 ·sub_414700 同构（差异：不调自身 vt+32(0)）。
// ------------------------------------------------------------
int /*thiscall*/ sub_414750(int this)
{
  unsigned int i; // edi

  if ( *(uint8_t *)(this + 4) == 0 )
    return -2147483647;
  for ( i = 0; i < *(uint32_t *)(this + 20); ++i )
    (*(void (/*stdcall*/ **)(uint32_t))(**(uint32_t **)(*(uint32_t *)(this + 52) + 4 * i) + 72))(*(uint32_t *)(*(uint32_t *)(this + 52) + 4 * i));
  *(uint8_t *)(this + 13) = 0;
  *(uint8_t *)(this + 14) = 1;
  return 1;
}



// ------------------------------------------------------------
// 0x4147A0 sub_4147A0 —— 设置播放位置（vt+52）
//   逐槽交 vt+52(nArg2)（SetCurrentPosition 槽位）【推断】。
// ------------------------------------------------------------
int /*thiscall*/ sub_4147A0(int this, int nArg2)
{
  unsigned int i; // esi

  if ( *(uint8_t *)(this + 4) == 0 )
    return -2147483647;
  for ( i = 0; i < *(uint32_t *)(this + 20); ++i )
    (*(void (/*stdcall*/ **)(uint32_t, int))(**(uint32_t **)(*(uint32_t *)(this + 52) + 4 * i) + 52))(
      *(uint32_t *)(*(uint32_t *)(this + 52) + 4 * i),
      nArg2);
  return 1;
}



// ------------------------------------------------------------
// 0x4147F0 sub_4147F0 —— 设置音量（百分比 → 毫贝）
//   this+16 = 100*(uArg2-100)，逐槽交 vt+60（SetVolume 槽位）【推断：百分音量转毫贝】。
// ------------------------------------------------------------
int /*thiscall*/ sub_4147F0(int this, uint16_t uArg2)
{
  unsigned int i; // edi

  if ( *(uint8_t *)(this + 4) == 0 )
    return -2147483647;
  *(uint32_t *)(this + 16) = 100 * (uArg2 - 100);
  for ( i = 0; i < *(uint32_t *)(this + 20); ++i )
    (*(void (/*stdcall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(*(uint32_t *)(this + 52) + 4 * i) + 60))(
      *(uint32_t *)(*(uint32_t *)(this + 52) + 4 * i),
      *(uint32_t *)(this + 16));
  return 1;
}



// ------------------------------------------------------------
// 0x414850 sub_414850 —— 声音缓冲创建（描述结构 → vt+12）
//   this[16]（偏移 64）为 0 返回 0x80000000；否则填 36 字节描述（首字段 36、标志 nArg4 = 0x40082、字节数 nArg2）
//   交其虚表 +12（CreateSoundBuffer 槽位）建缓冲；失败返回 0x80000021。
// ------------------------------------------------------------
int /*thiscall*/ sub_414850(uint32_t *this, int nArg2, int nArg3, int nArg4)
{
  int fld_e16; // eax
  int fld_e13; // [esp-8h] [ebp-30h]
  int v7; // [esp+0h] [ebp-28h] BYREF
  int nArg42; // [esp+4h] [ebp-24h]
  int nArg22; // [esp+8h] [ebp-20h]
  int v10; // [esp+Ch] [ebp-1Ch]
  int nArg32; // [esp+10h] [ebp-18h]
  int v12; // [esp+14h] [ebp-14h]
  int v13; // [esp+18h] [ebp-10h]
  int v14; // [esp+1Ch] [ebp-Ch]
  int v15; // [esp+20h] [ebp-8h]
  int dword_796E502; // [esp+24h] [ebp-4h]

  dword_796E502 = dword_796E50;
  if ( *(this + 16) == 0 )
    return 0x80000000;
  v7 = 0;
  nArg42 = 0;
  nArg22 = 0;
  v10 = 0;
  v12 = 0;
  v13 = 0;
  v14 = 0;
  v15 = 0;
  nArg32 = nArg3;
  fld_e16 = *(this + 16);
  fld_e13 = *(this + 13);
  nArg42 = nArg4;
  v7 = 36;
  nArg22 = nArg2;
  return (*(int (/*stdcall*/ **)(int, int *, int, uint32_t))(*(uint32_t *)fld_e16 + 12))(fld_e16, &v7, fld_e13, 0) >= 0 ? 1 : -2147483615;
}



// ------------------------------------------------------------
// 0x4148E0 sub_4148E0 —— 多缓冲循环链接
//   this+64 为 0 返回 0x80000000；槽位 1..n-1 逐个交 this+64 虚表 +20（首槽缓冲 + 槽位地址为参数）建立关联【推断】。
// ------------------------------------------------------------
int /*thiscall*/ sub_4148E0(int this)
{
  int v3; // edi

  if ( *(uint32_t *)(this + 64) == 0 )
    return 0x80000000;
  v3 = 1;
  if ( *(uint32_t *)(this + 20) <= 1u )
    return 1;
  while ( (*(int (/*stdcall*/ **)(uint32_t, uint32_t, int))(**(uint32_t **)(this + 64) + 20))(
            *(uint32_t *)(this + 64),
            **(uint32_t **)(this + 52),
            *(uint32_t *)(this + 52) + 4 * v3) >= 0 )
  {
    if ( (unsigned int)++v3 >= *(uint32_t *)(this + 20) )
      return 1;
  }
  return 0x80000000;
}



// ------------------------------------------------------------
// 0x414940 sub_414940 —— 取缓冲写指针（Lock）
//   缓冲对象（this[13]）虚表 +44 取写指针（Lock 槽位）【推断：DirectSound 缓冲虚表】，出参写 this[15]/this[14]，末参 2 = DSBLOCK_FROMWRITECURSOR；
//   返回 0x88780096（DSERR_BUFFERLOST）时虚表 +80 恢复（Restore）。
// ------------------------------------------------------------
int /*thiscall*/ sub_414940(uint32_t *this)
{
  uint32_t *fld_e13; // eax

  if ( *(this + 16) == 0 )
    return 0x80000000;
  fld_e13 = (uint32_t *)*(this + 13);
  if ( *fld_e13 == 0 )
    return 0x80000000;
  if ( (*(int (/*stdcall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t *, uint32_t *, uint32_t, uint32_t, int))(*(uint32_t *)*fld_e13 + 44))(
         *fld_e13,
         0,
         0,
         this + 15,
         this + 14,
         0,
         0,
         2) == -2005401450 )
    (*(void (/*stdcall*/ **)(uint32_t))(**(uint32_t **)*(this + 13) + 80))(*(uint32_t *)*(this + 13));
  return 1;
}



// ------------------------------------------------------------
// 0x414990 sub_414990 —— 解锁缓冲（Unlock）
//   缓冲对象（this[13]）虚表 +76 以 this[15]/this[14] 解锁（Unlock 槽位）【推断同 ·sub_414940】；
//   返回 0x88780096（DSERR_BUFFERLOST）时虚表 +8 释放。
// ------------------------------------------------------------
int /*thiscall*/ sub_414990(uint32_t *this)
{
  uint32_t *fld_e13; // eax

  if ( *(this + 16) == 0 )
    return 0x80000000;
  fld_e13 = (uint32_t *)*(this + 13);
  if ( *fld_e13 == 0 )
    return 0x80000000;
  if ( (*(int (/*stdcall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)*fld_e13 + 76))(
         *fld_e13,
         *(this + 15),
         *(this + 14),
         0,
         0) == -2005401450 )
    (*(void (/*stdcall*/ **)(uint32_t))(**(uint32_t **)*(this + 13) + 8))(*(uint32_t *)*(this + 13));
  return 1;
}



// ------------------------------------------------------------
// 0x4149E0 sub_4149E0
// ------------------------------------------------------------
// 【解读】
//   WAV→声音对象装载: sub_4199A0(mmioOpenA/Descend/Read 全量) + sub_419B40(Seek/Descend fmt 块)
//    + sub_419B80(mmioGetInfo/Advance 数据流) → sub_414850/0x414940 建缓冲 → 挂声音管理器。
// ------------------------------------------------------------
int /*thiscall*/ sub_4149E0(int *this, LPSTR pszFileName, HMMIO hmmio)
{
  int v5; // eax
  int *pThis; // ecx
  int fld_e14; // eax
  struct _MMCKINFO pmmcki; // [esp+4h] [ebp-30h] BYREF
  struct _MMCKINFO v9; // [esp+18h] [ebp-1Ch] BYREF
  int v10; // [esp+2Ch] [ebp-8h] BYREF
  int v11; // [esp+30h] [ebp-4h] BYREF

  if ( *((uint8_t *)this + 4) != 0 )
    return -2147483646;
  if ( (*(int (/*thiscall*/ **)(int *, HMMIO))(*this + 4))(this, hmmio) < 0 )
  {
    (*(void (/*thiscall*/ **)(int *))(*this + 8))(this);
    return 0x80000000;
  }
  if ( sub_4199A0(pszFileName, (int)&hmmio, (int)&v11, &pmmcki) != 0 )  // 【mmio WAV 读取族（mmioOpenA/Descend/Read/Ascend…】
  {
    (*(void (/*thiscall*/ **)(int *))(*this + 8))(this);
    return -2147483643;
  }
  if ( sub_419B40((int)&hmmio, &v9, &pmmcki) != 0 )
  {
    (*(void (/*thiscall*/ **)(int *))(*this + 8))(this);
    sub_419C40(&hmmio, &v11);
    return -2147483644;
  }
  v5 = sub_414850(this, v9.cksize, v11, 262274);
  pThis = this;
  if ( v5 < 0 )
    goto LABEL_10;
  if ( sub_414940(this) < 0 )
  {
    pThis = this;
LABEL_10:
    (*(void (/*thiscall*/ **)(int *))(*this + 8))(pThis);
    sub_419C40(&hmmio, &v11);
    return 0x80000000;
  }
  fld_e14 = sub_419B80(hmmio, *(this + 14), *(this + 15), (int)&v9, (int)&v10);
  pThis = this;
  if ( fld_e14 != 0 )
    goto LABEL_10;
  sub_414990(this);
  sub_419C40(&hmmio, &v11);
  sub_402AE0((int)(this + 6), pszFileName);
  if ( (unsigned int)*(this + 5) > 1 )
    sub_4148E0((int)this);
  *((uint8_t *)this + 4) = 1;
  return 1;
}



// ------------------------------------------------------------
// 0x414B30 sub_414B30 —— 构造（双字符串参数包）
//   vftable off_6C298C；this+2/this+7 两个字符串参数包（6C38F4 + sub_402A50）；this+32 清 0；sub_419C80 收尾。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_414B30(uint8_t *this)
{
  *(this + 4) = 0;
  *(uint32_t *)this = &off_6C298C;
  *(this + 12) = 0;
  *((uint32_t *)this + 2) = &off_6C38F4;
  sub_402A50((uint32_t *)this + 2);  // 【字符串参数包 / CString 数组 / vsprintf 格式化打包工具】
  *(this + 32) = 0;
  *((uint32_t *)this + 7) = &off_6C38F4;
  sub_402A50((uint32_t *)this + 7);  // 【字符串参数包 / CString 数组 / vsprintf 格式化打包工具】
  sub_419C80(this);
  return this;
}



// ------------------------------------------------------------
// 0x414BB0 sub_414BB0 —— 析构链（双参数包）
//   6C298C → sub_419CD0 → this+7/this+2 两包 sub_402A60 → IObject 基类（与 ·sub_414490 同型）。
// ------------------------------------------------------------
int /*thiscall*/ sub_414BB0(uint32_t *this)
{
  int result; // eax

  *this = &off_6C298C;
  sub_419CD0();
  *(this + 7) = &off_6C38F4;
  sub_402A60((int)(this + 7));
  *(this + 7) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 32) = 0;
  *(this + 2) = &off_6C38F4;
  result = sub_402A60((int)(this + 2));
  *(this + 2) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 12) = 0;
  *this = &nengine::IObject::`vftable';
  *((uint8_t *)this + 4) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x414C40 sub_414C40 —— 析构加释放壳
//   —— 与 ·sub_414460 同构（差异：析构体为 ·sub_414BB0）。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_414C40(uint32_t *Block, char pszArg2)
{
  sub_414BB0(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x414C70 sub_414C70 —— 构造（414B30 + 6C299C）
//   在 ·sub_414B30 基础上换 vftable off_6C299C 并调 nullsub_3。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_414C70(uint8_t *this)
{
  sub_414B30(this);
  *(uint32_t *)this = &off_6C299C;
  nullsub_3(this);
  return this;
}



// ------------------------------------------------------------
// 0x414CC0 sub_414CC0 —— 析构加释放壳
//   —— 与 ·sub_414C40 同构（差异：析构体为 ·sub_414CF0）。
// ------------------------------------------------------------
void */*thiscall*/ sub_414CC0(void *Block, char pszArg2)
{
  sub_414CF0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x414CF0 sub_414CF0 —— 析构（6C299C → 419CD0 → 414BB0）
//   先挂 off_6C299C，交 sub_419CD0 清理，再走 ·sub_414BB0 析构链。
// ------------------------------------------------------------
int /*thiscall*/ sub_414CF0(uint32_t *this)
{
  *this = &off_6C299C;
  sub_419CD0();
  return sub_414BB0(this);
}



// ------------------------------------------------------------
// 0x414D40 sub_414D40 —— 清 13..17 五字段
//   清 this[13..17]（偏移 52..68，与 ·sub_414E00 释放的五个接口同址）。
// ------------------------------------------------------------
int /*thiscall*/ sub_414D40(uint32_t *this)
{
  *(this + 17) = 0;
  *(this + 15) = 0;
  *(this + 16) = 0;
  *(this + 14) = 0;
  *(this + 13) = 0;
  return 0;
}



// ============================================================
// SECTION 0x414D60 — COM/宽字符工具（CoCreateInstance / MultiByteToWideChar）
// ============================================================
// ------------------------------------------------------------
// 0x414D60 sub_414D60
// ------------------------------------------------------------
// 【解读】
//   CoCreateInstance —— COM 对象创建（0x414D40/0x414E00 伴随）【推断：声音/滤镜类组件】。
// ------------------------------------------------------------
int /*thiscall*/ sub_414D60(int this, int nArg2)  // 【COM/宽字符工具（CoCreateInstance / MultiByteToWi…】
{
  uint32_t *pThis_34; // edi

  if ( *(uint8_t *)(this + 4) != 0 )
    return -2147483646;
  pThis_34 = (uint32_t *)(this + 52);
  if ( CoCreateInstance(&stru_749D4C, nullptr, 1u, &stru_749CFC, (LPVOID *)(this + 52)) < 0
    || (**(int (/*stdcall*/ ***)(uint32_t, void *, int))*pThis_34)(*pThis_34, &unk_749D3C, this + 56) < 0
    || (**(int (/*stdcall*/ ***)(uint32_t, void *, int))*pThis_34)(*pThis_34, &unk_749D2C, this + 64) < 0
    || (**(int (/*stdcall*/ ***)(uint32_t, void *, int))*pThis_34)(*pThis_34, &unk_749D0C, this + 60) < 0
    || (**(int (/*stdcall*/ ***)(uint32_t, void *, int))*pThis_34)(*pThis_34, &unk_749D1C, this + 68) < 0 )
  {
    return -2147483600;
  }
  *(uint8_t *)(this + 4) = 1;
  return 1;
}



// ------------------------------------------------------------
// 0x414E00 sub_414E00 —— COM 接口释放（五个）
//   依次释放 this+68/60/64/56/52 五接口（虚表 +8 Release），清 this+4。
// ------------------------------------------------------------
int /*thiscall*/ sub_414E00(int this)
{
  int fld_44; // eax
  int fld_3C; // eax
  int fld_40; // eax
  int fld_38; // eax
  int fld_34; // eax

  fld_44 = *(uint32_t *)(this + 68);
  if ( fld_44 != 0 )
    (*(void (/*stdcall*/ **)(int))(*(uint32_t *)fld_44 + 8))(fld_44);
  fld_3C = *(uint32_t *)(this + 60);
  *(uint32_t *)(this + 68) = 0;
  if ( fld_3C != 0 )
    (*(void (/*stdcall*/ **)(int))(*(uint32_t *)fld_3C + 8))(fld_3C);
  fld_40 = *(uint32_t *)(this + 64);
  *(uint32_t *)(this + 60) = 0;
  if ( fld_40 != 0 )
    (*(void (/*stdcall*/ **)(int))(*(uint32_t *)fld_40 + 8))(fld_40);
  fld_38 = *(uint32_t *)(this + 56);
  *(uint32_t *)(this + 64) = 0;
  if ( fld_38 != 0 )
    (*(void (/*stdcall*/ **)(int))(*(uint32_t *)fld_38 + 8))(fld_38);
  fld_34 = *(uint32_t *)(this + 52);
  *(uint32_t *)(this + 56) = 0;
  if ( fld_34 != 0 )
    (*(void (/*stdcall*/ **)(int))(*(uint32_t *)fld_34 + 8))(fld_34);
  *(uint32_t *)(this + 52) = 0;
  *(uint8_t *)(this + 4) = 0;
  return 1;
}



// ------------------------------------------------------------
// 0x414E70 sub_414E70 —— 播放状态收尾（+32/+48）
//   this+12 非 0 且 this+64 对象虚表 +32 取三出参成功时调 +48(v5, v3, v4)，v5 == 1 则清 this+13；
//   随后自身 vt+32(0)，this+56 对象虚表 +28 并按返回值给出 1 或 0x80000000。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_414E70(uint8_t *this)
{
  int v3; // [esp+4h] [ebp-Ch] BYREF
  int v4; // [esp+8h] [ebp-8h] BYREF
  int v5; // [esp+Ch] [ebp-4h] BYREF

  if ( *(this + 4) == 0 )
    return -2147483647;
  if ( *(this + 12) != 0
    && (*(int (/*stdcall*/ **)(uint32_t, int *, int *, int *, uint32_t))(**((uint32_t **)this + 16) + 32))(
         *((uint32_t *)this + 16),
         &v5,
         &v3,
         &v4,
         0) >= 0 )
  {
    (*(void (/*stdcall*/ **)(uint32_t, int, int, int))(**((uint32_t **)this + 16) + 48))(*((uint32_t *)this + 16), v5, v3, v4);
    if ( v5 == 1 )
      *(this + 13) = 0;
  }
  (*(void (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 32))(this, 0);
  return (*(int (/*stdcall*/ **)(uint32_t))(**((uint32_t **)this + 14) + 28))(*((uint32_t *)this + 14)) >= 0 ? 1 : 0x80000000;
}



// ------------------------------------------------------------
// 0x414F00 sub_414F00 —— 控制序列（+60/+36）并复位
//   自身 vt+32(0) 后对 this+56 对象依序调虚表 +60、+36；任一失败返回 0x80000000，成功置 this+13 = 0、this+14 = 1。
// ------------------------------------------------------------
int /*thiscall*/ sub_414F00(uint8_t *this)
{
  if ( *(this + 4) == 0 )
    return -2147483647;
  (*(void (/*thiscall*/ **)(uint8_t *, uint32_t))(*(uint32_t *)this + 32))(this, 0);
  if ( (*(int (/*stdcall*/ **)(uint32_t))(**((uint32_t **)this + 14) + 60))(*((uint32_t *)this + 14)) < 0
    || (*(int (/*stdcall*/ **)(uint32_t))(**((uint32_t **)this + 14) + 36))(*((uint32_t *)this + 14)) < 0 )
  {
    return 0x80000000;
  }
  *(this + 13) = 0;
  *(this + 14) = 1;
  return 1;
}



// ------------------------------------------------------------
// 0x414F50 sub_414F50 —— 控制序列（无自身调用变体）
//   —— 与 ·sub_414F00 同构（差异：不调自身 vt+32(0)）。
// ------------------------------------------------------------
int /*thiscall*/ sub_414F50(int this)
{
  if ( *(uint8_t *)(this + 4) == 0 )
    return -2147483647;
  if ( (*(int (/*stdcall*/ **)(uint32_t))(**(uint32_t **)(this + 56) + 60))(*(uint32_t *)(this + 56)) < 0
    || (*(int (/*stdcall*/ **)(uint32_t))(**(uint32_t **)(this + 56) + 36))(*(uint32_t *)(this + 56)) < 0 )
  {
    return 0x80000000;
  }
  *(uint8_t *)(this + 13) = 0;
  *(uint8_t *)(this + 14) = 1;
  return 1;
}



// ------------------------------------------------------------
// 0x414F90 sub_414F90 —— 参数对下发（+56）
//   把 {nArg2, 0} 参数对交 this+60 对象虚表 +56（count 1）；失败返回 0x80000000。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_414F90(int this, int nArg2)
{
  int fld_3C; // eax
  uint32_t v4[2]; // [esp+0h] [ebp-8h] BYREF

  if ( *(uint8_t *)(this + 4) == 0 )
    return -2147483647;
  v4[0] = nArg2;
  fld_3C = *(uint32_t *)(this + 60);
  v4[1] = 0;
  return (*(int (/*stdcall*/ **)(int, uint32_t *, int, uint32_t, uint32_t))(*(uint32_t *)fld_3C + 56))(fld_3C, v4, 1, 0, 0) >= 0
       ? 1
       : 0x80000000;
}



// ------------------------------------------------------------
// 0x414FE0 sub_414FE0 —— 音量下发（+28）
//   this+16 = 100*(uArg2-100)，交 this+68 对象虚表 +28；失败返回 0x80000000。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_414FE0(int this, uint16_t uArg2)
{
  if ( *(uint8_t *)(this + 4) == 0 )
    return -2147483647;
  *(uint32_t *)(this + 16) = 100 * (uArg2 - 100);
  return (*(int (/*stdcall*/ **)(uint32_t, int))(**(uint32_t **)(this + 68) + 28))(*(uint32_t *)(this + 68), 100 * (uArg2 - 100)) >= 0
       ? 1
       : 0x80000000;
}



// ============================================================
// SECTION 0x415020 — 键盘输入族（GetAsyncKeyState 轮询）
// ============================================================
// ------------------------------------------------------------
// 0x415020 sub_415020 —— 宽字符路径换绑资源
//   MultiByteToWideChar 转宽路径；现场经 vt+40 保存、vt+8 释放旧、vt+4(1) 重建，
//   this+52 对象虚表 +52 装载宽路径，成功后 vt+36 恢复现场并置 this+4。
// ------------------------------------------------------------
int /*thiscall*/ sub_415020(uint8_t *this, LPCCH lpMultiByteStr, int nArg3)  // 【键盘输入族（GetAsyncKeyState 轮询）】
{
  int result; // eax
  int pThis_28; // edi
  WCHAR WideCharStr[256]; // [esp+4h] [ebp-204h] BYREF
  int dword_796E502; // [esp+204h] [ebp-4h]

  dword_796E502 = dword_796E50;
  if ( *(this + 4) != 0 )
    return -2147483646;
  MultiByteToWideChar(0, 1u, lpMultiByteStr, -1, WideCharStr, 256);
  pThis_28 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 40))(this);
  (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 8))(this);
  result = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 4))(this, 1);
  if ( result >= 0 )
  {
    if ( (*(int (/*stdcall*/ **)(uint32_t, WCHAR *, uint32_t))(**((uint32_t **)this + 13) + 52))(
           *((uint32_t *)this + 13),
           WideCharStr,
           0) >= 0 )
    {
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 36))(this, pThis_28);
      *(this + 4) = 1;
      return 1;
    }
    else
    {
      *(this + 4) = 0;
      return 0x80000000;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4150E0 sub_4150E0 —— 惰性创建字符串参数包
//   this+48 为空则 new 0x34 经 sub_414C70 构造，sub_419C90 初始化后回写；再输出给 uArg2。
// ------------------------------------------------------------
int /*thiscall*/ sub_4150E0(int this, uint32_t *uArg2)
{
  int fld_30; // eax
  uint8_t *pMem; // eax
  uint8_t *v6; // eax

  if ( *(uint8_t *)(this + 4) == 0 )
    return -2147483647;
  fld_30 = *(uint32_t *)(this + 48);
  if ( fld_30 == 0 )
  {
    pMem = operator new(0x34u);
    v6 = pMem != nullptr ? sub_414C70(pMem) : nullptr;
    *(uint32_t *)(this + 48) = v6;
    sub_419C90(this);
    fld_30 = *(uint32_t *)(this + 48);
    if ( fld_30 == 0 )
      return -2147483640;
  }
  *uArg2 = fld_30;
  return 1;
}



// ------------------------------------------------------------
// 0x415190 sub_415190 —— 输入映射表重置（六段 memset）
//   置 this+12 = 1；memset 六张表（this+13/269/525 各 0x100、+784 0x400、+1808 0x100、+2064 0x400），
//   再调自身 vt+32。
// ------------------------------------------------------------
int /*thiscall*/ sub_415190(uint8_t *this)
{
  *(this + 12) = 1;
  memset(this + 13, 0, 0x100u);
  memset(this + 269, 0, 0x100u);
  memset(this + 525, 0, 0x100u);
  memset(this + 784, 0, 0x400u);
  memset(this + 1808, 0, 0x100u);
  memset(this + 2064, 0, 0x400u);
  return (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 32))(this);
}



// ------------------------------------------------------------
// 0x415200 sub_415200 —— 当前帧按键边沿判定（映射表 + 键态双表
//   状态位(this+12) 非 0 且 映射键码(this[784+4n]) 键态表(this+269) 已按下 而上帧表(this+525) 未按下 —— 本帧新按下。
// ------------------------------------------------------------
bool /*thiscall*/ sub_415200(uint8_t *this, int nArg2)
{
  uint8_t *v2; // eax

  return *(this + 12) != 0 && (v2 = this + *((uint32_t *)this + nArg2 + 196))[269] != 0 && v2[525] == 0;
}



// ------------------------------------------------------------
// 0x415240 sub_415240 —— 键盘映射表初始化（第一套: DirectInput DIK 扫描码）
//   写 dword 索引 196..302 共 107 项 逻辑动作 → DIK 键码（203/205/200/208 = 左右上下，57 = 空格）；返回 9。
//   与 ·0x4161A0 的 VK 套共用同一表区（两套互为镜像，后初始化者生效）。
// ------------------------------------------------------------
int /*thiscall*/ sub_415240(uint32_t *this)
{
  *(this + 200) = 29;
  *(this + 201) = 29;
  *(this + 203) = 42;
  *(this + 204) = 42;
  *(this + 206) = 56;
  *(this + 208) = 56;
  *(this + 196) = 203;
  *(this + 197) = 205;
  *(this + 198) = 200;
  *(this + 199) = 208;
  *(this + 202) = 157;
  *(this + 205) = 54;
  *(this + 207) = 184;
  *(this + 209) = 57;
  *(this + 210) = 13;
  *(this + 211) = 14;
  *(this + 212) = 28;
  *(this + 213) = 210;
  *(this + 214) = 211;
  *(this + 215) = 201;
  *(this + 216) = 209;
  *(this + 217) = 199;
  *(this + 218) = 207;
  *(this + 219) = 78;
  *(this + 220) = 12;
  *(this + 221) = 55;
  *(this + 222) = 1;
  *(this + 223) = 39;
  *(this + 224) = 52;
  *(this + 225) = 51;
  *(this + 226) = 181;
  *(this + 227) = 15;
  *(this + 228) = 58;
  *(this + 229) = 74;
  *(this + 230) = 53;
  *(this + 231) = 82;
  *(this + 232) = 79;
  *(this + 233) = 80;
  *(this + 234) = 81;
  *(this + 235) = 75;
  *(this + 236) = 76;
  *(this + 237) = 77;
  *(this + 238) = 71;
  *(this + 239) = 72;
  *(this + 240) = 73;
  *(this + 241) = 11;
  *(this + 242) = 2;
  *(this + 243) = 3;
  *(this + 244) = 4;
  *(this + 245) = 5;
  *(this + 246) = 6;
  *(this + 247) = 7;
  *(this + 248) = 8;
  *(this + 249) = 9;
  *(this + 250) = 10;
  *(this + 251) = 30;
  *(this + 252) = 48;
  *(this + 253) = 46;
  *(this + 254) = 32;
  *(this + 255) = 18;
  *(this + 256) = 33;
  *(this + 257) = 34;
  *(this + 258) = 35;
  *(this + 259) = 23;
  *(this + 260) = 36;
  *(this + 261) = 37;
  *(this + 262) = 38;
  *(this + 263) = 50;
  *(this + 264) = 49;
  *(this + 265) = 24;
  *(this + 266) = 25;
  *(this + 267) = 16;
  *(this + 268) = 19;
  *(this + 269) = 31;
  *(this + 270) = 20;
  *(this + 271) = 22;
  *(this + 272) = 47;
  *(this + 273) = 17;
  *(this + 274) = 45;
  *(this + 275) = 21;
  *(this + 276) = 44;
  *(this + 277) = 59;
  *(this + 278) = 60;
  *(this + 279) = 61;
  *(this + 280) = 62;
  *(this + 281) = 63;
  *(this + 282) = 64;
  *(this + 283) = 65;
  *(this + 284) = 66;
  *(this + 285) = 67;
  *(this + 286) = 68;
  *(this + 287) = 87;
  *(this + 288) = 88;
  *(this + 289) = 183;
  *(this + 290) = 0;
  *(this + 291) = 1;
  *(this + 292) = 2;
  *(this + 293) = 3;
  *(this + 294) = 4;
  *(this + 295) = 5;
  *(this + 296) = 6;
  *(this + 297) = 7;
  *(this + 298) = 8;
  *(this + 299) = 9;
  *(this + 300) = 26;
  *(this + 301) = 27;
  *(this + 302) = 40;
  return 9;
}


// ------------------------------------------------------------
// 0x415660 sub_415660 —— GetAsyncKeyState 边沿锁存（按下置位 / 释放返回 1）
//   uArg2 为空返回 0；状态 0 且键按下 → 置 1（返回 0）；状态 1 且键释放 → 清 0 并返回 1。
// ------------------------------------------------------------
char /*stdcall*/ sub_415660(int vKey, uint8_t *uArg2)
{
  if ( uArg2 == nullptr )
    return 0;
  if ( *uArg2 == 0 )
  {
    if ( (GetAsyncKeyState(vKey) & 0x80000) != 0 )
      *uArg2 = 1;
    return 0;
  }
  if ( *uArg2 != 1 || (GetAsyncKeyState(vKey) & 0x80000) != 0 )
    return 0;
  *uArg2 = 0;
  return 1;
}



// ------------------------------------------------------------
// 0x4156C0 sub_4156C0 —— 键态查询（this+1808 表 + 状态位门控）
//   状态位(this+12) 为 0 时恒返回 0。
// ------------------------------------------------------------
char /*thiscall*/ sub_4156C0(uint8_t *this, int pArg2)
{
  if ( *(this + 12) != 0 )
    return *(this + pArg2 + 1808);
  else
    return 0;
}



// ------------------------------------------------------------
// 0x4156E0 sub_4156E0 —— DirectInput 设备创建（CreateDevice + 数据格式 + 协作级别）
//   守卫: 已初始化(this+4) → 0x80000002；this+3092 对象空 → 0x80000000；
//   vt+12 建设备到 this+3088（GUID unk_743EF0）→ vt+44 数据格式 unk_749ADC → vt+52 协作级别 6（hwnd 取 this+3096 对象 +16）→ 置状态位。【推断】
// ------------------------------------------------------------
int /*thiscall*/ sub_4156E0(int this, int nArg2)
{
  int fld_C14; // eax
  uint32_t *pThis_C10; // edi

  if ( *(uint8_t *)(this + 4) != 0 )
    return -2147483646;
  fld_C14 = *(uint32_t *)(this + 3092);
  if ( fld_C14 == 0 )
    return 0x80000000;
  pThis_C10 = (uint32_t *)(this + 3088);
  if ( (*(int (/*stdcall*/ **)(int, void *, int, uint32_t))(*(uint32_t *)fld_C14 + 12))(fld_C14, &unk_743EF0, this + 3088, 0) < 0 )
    return -2147483583;
  if ( (*(int (/*stdcall*/ **)(uint32_t, void *))(*(uint32_t *)*pThis_C10 + 44))(*pThis_C10, &unk_749ADC) < 0
    || (*(int (/*stdcall*/ **)(uint32_t, uint32_t, int))(*(uint32_t *)*pThis_C10 + 52))(
         *pThis_C10,
         *(uint32_t *)(*(uint32_t *)(this + 3096) + 16),
         6) < 0 )
  {
    return 0x80000000;
  }
  *(uint8_t *)(this + 4) = 1;
  return 1;
}



// ------------------------------------------------------------
// 0x415770 sub_415770 —— 设备 Acquire + 键态读取（256 字节）
//   状态位(this+4) 门控；先把旧键态 this+525 ← this+269（256B），再 vt+28 / vt+100 均成功后 vt+36(256, this+269)。
//   vt+36 写入 256 字节 DIK 全键表（GetDeviceState 位）。【推断】
// ------------------------------------------------------------
char /*thiscall*/ sub_415770(int this)
{
  int fld_C102; // eax
  int fld_C10; // eax

  LOBYTE(fld_C102) = *(uint8_t *)(this + 4);
  if ( (uint8_t)fld_C102 != 0 )
  {
    fld_C10 = *(uint32_t *)(this + 3088);
    qmemcpy((void *)(this + 525), (const void *)(this + 269), 0x100u);
    fld_C102 = (*(int (/*stdcall*/ **)(int))(*(uint32_t *)fld_C10 + 28))(fld_C10);
    if ( fld_C102 >= 0 )
    {
      fld_C102 = (*(int (/*stdcall*/ **)(uint32_t))(**(uint32_t **)(this + 3088) + 100))(*(uint32_t *)(this + 3088));
      if ( fld_C102 >= 0 )
        LOBYTE(fld_C102) = (*(int (/*stdcall*/ **)(uint32_t, int, int))(**(uint32_t **)(this + 3088) + 36))(
                       *(uint32_t *)(this + 3088),
                       256,
                       this + 269);
    }
  }
  return fld_C102;
}



// ------------------------------------------------------------
// 0x4157E0 sub_4157E0 —— 设备槽清零（this+3088 = 0）
//   仅清设备槽 this+3088（无释放动作）—— 错误回退路径用。【推断】
// ------------------------------------------------------------
void /*thiscall*/ sub_4157E0(uint32_t *this)
{
  *(this + 772) = 0;
}



// ------------------------------------------------------------
// 0x4157F0 sub_4157F0 —— 设备释放（vt+32 + vt+8，槽与状态位清零）
//   vt+32 后经 vt+8 释放 this+3088 并置 0，this+4 = 0，返回 1。
// ------------------------------------------------------------
int /*thiscall*/ sub_4157F0(int this)
{
  int fld_C10; // eax
  int fld_C102; // eax

  fld_C10 = *(uint32_t *)(this + 3088);
  if ( fld_C10 != 0 )
  {
    (*(void (/*stdcall*/ **)(int))(*(uint32_t *)fld_C10 + 32))(fld_C10);
    fld_C102 = *(uint32_t *)(this + 3088);
    if ( fld_C102 != 0 )
      (*(void (/*stdcall*/ **)(uint32_t))(*(uint32_t *)fld_C102 + 8))(*(uint32_t *)(this + 3088));
    *(uint32_t *)(this + 3088) = 0;
  }
  *(uint8_t *)(this + 4) = 0;
  *(uint32_t *)(this + 3088) = 0;
  return 1;
}



// ------------------------------------------------------------
// 0x415840 sub_415840 —— 第二输入设备状态同步（272B 状态 → 键态表回填）
//   状态位门控；vt+36(272, this+3092) 读状态，经 this+2064 索引表把 107 项键态回填 this+1808；
//   轴值 this+3092/this+3096 超 ±500 阈值时合成 4 个方向键（映射项 this+784/788/792/796），旧键态搬 this+525 并清 this+269。【推断】
// ------------------------------------------------------------
char /*thiscall*/ sub_415840(int this)
{
  int fld_C10; // eax
  int v3; // eax
  int *pThis_810; // esi
  int v5; // edx
  bool v6; // cl

  LOBYTE(fld_C10) = *(uint8_t *)(this + 4);
  if ( (uint8_t)fld_C10 != 0 )
  {
    LOBYTE(fld_C10) = *(uint8_t *)(this + 12);
    if ( (uint8_t)fld_C10 != 0 )
    {
      fld_C10 = *(uint32_t *)(this + 3088);
      if ( fld_C10 != 0 )
      {
        fld_C10 = (*(int (/*stdcall*/ **)(uint32_t))(*(uint32_t *)fld_C10 + 28))(*(uint32_t *)(this + 3088));
        if ( fld_C10 >= 0 )
        {
          fld_C10 = (*(int (/*stdcall*/ **)(uint32_t))(**(uint32_t **)(this + 3088) + 100))(*(uint32_t *)(this + 3088));
          if ( fld_C10 >= 0 )
          {
            (*(void (/*stdcall*/ **)(uint32_t, int, int))(**(uint32_t **)(this + 3088) + 36))(
              *(uint32_t *)(this + 3088),
              272,
              this + 3092);
            qmemcpy((void *)(this + 525), (const void *)(this + 269), 0x100u);
            v3 = 0;
            memset((void *)(this + 269), 0, 0x100u);
            pThis_810 = (int *)(this + 2064);
            do
            {
              v5 = *pThis_810;
              v6 = *(uint8_t *)(this + v3++ + 3140) != 0;
              ++pThis_810;
              *(uint8_t *)(this + v5 + 1808) = v6;
            }
            while ( v3 < 107 );
            LOBYTE(fld_C10) = 1;
            if ( *(int *)(this + 3092) < -500 )
              *(uint8_t *)(*(uint32_t *)(this + 784) + this + 269) = 1;
            if ( *(int *)(this + 3092) > 500 )
              *(uint8_t *)(*(uint32_t *)(this + 788) + this + 269) = 1;
            if ( *(int *)(this + 3096) < -500 )
              *(uint8_t *)(*(uint32_t *)(this + 792) + this + 269) = 1;
            if ( *(int *)(this + 3096) > 500 )
              *(uint8_t *)(*(uint32_t *)(this + 796) + this + 269) = 1;
          }
        }
      }
    }
  }
  return fld_C10;
}



// ------------------------------------------------------------
// 0x415960 sub_415960 —— 输入轴向范围属性设置（±1000）
//   请求块 = {24, 16, 轴对象 pArg1+24, 2, -1000, 1000} 经设备 this[772](=this+3088) vt+24(4, 块) 下发。【推断】
// ------------------------------------------------------------
int /*stdcall*/ sub_415960(int pArg1, int pArg2)
{
  int v2; // ecx
  int pObj; // eax
  uint32_t v5[6]; // [esp+0h] [ebp-18h] BYREF

  v2 = *(uint32_t *)(pArg1 + 24);
  pObj = *(uint32_t *)(pArg2 + 3088);
  v5[0] = 24;
  v5[1] = 16;
  v5[3] = 2;
  v5[2] = v2;
  v5[5] = 1000;
  v5[4] = -1000;
  (*(void (/*stdcall*/ **)(int, int, uint32_t *))(*(uint32_t *)pObj + 24))(pObj, 4, v5);
  return 1;
}



// ------------------------------------------------------------
// 0x4159C0 sub_4159C0 —— 580B 记录矢量计数
//   返回 (end - begin) / 580；580 = 0x244 为键映射记录步长。
// ------------------------------------------------------------
int /*thiscall*/ sub_4159C0(int *this)
{
  int result; // eax

  result = *(this + 1);
  if ( result != 0 )
    return (*(this + 2) - result) / 580;
  return result;
}



// ------------------------------------------------------------
// 0x4159F0 sub_4159F0 —— 未初始化区间正向填充（580B 元素）
//   [pszArg1, pszArg2) 每条 580B 拷贝 pArg3 一份（MSVC uninitialized_fill 实例）。
// ------------------------------------------------------------
char */*cdecl*/ sub_4159F0(char *pszArg1, char *pszArg2, const void *pArg3)
{
  char *result; // eax
  void *v4; // edi

  for ( result = pszArg1; result != pszArg2; result += 580 )
  {
    v4 = result;
    qmemcpy(v4, pArg3, 0x244u);
  }
  return result;
}



// ------------------------------------------------------------
// 0x415A20 sub_415A20 —— 反向搬移（580B 元素，尾 → 头）
//   逐条 580B qmemcpy 从尾到头，返回目标起点 —— 插入时把尾部整体后移。
// ------------------------------------------------------------
char */*cdecl*/ sub_415A20(char *pszArg1, char *pszArg2, char *pszArg3)
{
  char *pszArg22; // edx
  char *result; // eax

  pszArg22 = pszArg2;
  result = pszArg3;
  while ( pszArg22 != pszArg1 )
  {
    pszArg22 -= 580;
    result -= 580;
    qmemcpy(result, pszArg22, 0x244u);
  }
  return result;
}



// ------------------------------------------------------------
// 0x415A60 sub_415A60 —— 正向拷贝（580B 元素）
//   [pszArg1, pszArg2) 逐条拷贝到 pszArg3 起，含空目标保护；返回目标尾。
// ------------------------------------------------------------
char */*cdecl*/ sub_415A60(char *pszArg1, char *pszArg2, char *pszArg3)
{
  char *pszArg12; // edx
  char *result; // eax

  pszArg12 = pszArg1;
  for ( result = pszArg3; pszArg12 != pszArg2; result += 580 )
  {
    if ( result != nullptr )
      qmemcpy(result, pszArg12, 0x244u);
    pszArg12 += 580;
  }
  return result;
}



// ------------------------------------------------------------
// 0x415AA0 sub_415AA0 —— 重复填充（n 份 580B 元素）
//   供插入路径做尾部批量构造（目标为空时只推进指针）。
// ------------------------------------------------------------
char */*cdecl*/ sub_415AA0(char *pszArg1, char *pszArg2, const void *pArg3)
{
  char *result; // eax
  char *pszArg22; // edx

  result = pszArg2;
  if ( pszArg2 != nullptr )
  {
    pszArg22 = pszArg2;
    result = pszArg1;
    do
    {
      if ( result != nullptr )
        qmemcpy(result, pArg3, 0x244u);
      result += 580;
      --pszArg22;
    }
    while ( pszArg22 != nullptr );
  }
  return result;
}



// ------------------------------------------------------------
// 0x415AE0 sub_415AE0 —— 填充 + 返回尾指针
//   调 ·0x415AA0 后返回 &pszArg1[580 * n]。
// ------------------------------------------------------------
char */*stdcall*/ sub_415AE0(char *pszArg1, char *pszArg2, const void *pArg3)
{
  sub_415AA0(pszArg1, pszArg2, pArg3);
  return &pszArg1[580 * (uint32_t)pszArg2];
}



// ============================================================
// SECTION 0x415B10 — 输入映射 vector 管理（按键状态容器）
// ============================================================
// ------------------------------------------------------------
// 0x415B10 sub_415B10 [串: "vector<T> too long"]
// ------------------------------------------------------------
void /*noreturn*/ sub_415B10()  // 【输入映射 vector 管理（按键状态容器）】
{
  uint32_t pExceptionObject[10]; // [esp+0h] [ebp-50h] BYREF
  size_t v1; // [esp+28h] [ebp-28h] BYREF
  char v2; // [esp+2Ch] [ebp-24h]
  int v3; // [esp+3Ch] [ebp-14h]
  int v4; // [esp+40h] [ebp-10h]
  int v5; // [esp+4Ch] [ebp-4h]

  v4 = 15;
  v3 = 0;
  v2 = 0;
  sub_4015C0(&v1, "vector<T> too long", 0x12u);  // 【std::string构造赋值】
  v5 = 0;
  sub_401740(pExceptionObject, &v1);
  pExceptionObject[0] = &std::length_error::`vftable';
  _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x415B80 sub_415B80 —— 580B 记录矢量插入（MSVC vector 实例）
//   容量三分支: 原地尾部后移 / 尾部直接构造 / 扩容重建；元素步长 580B(0x244)，上限 off_70FE3C。
//   溢出调 ·0x415B10 抛 length_error; 辅助件 ·0x4159C0/·0x415A20/·0x415A60/·0x415AA0/·0x4159F0。
// ------------------------------------------------------------
int /*thiscall*/ sub_415B80(int this, char *pszArg2, char *pszArg3, const void *pArg4)
{
  int result; // eax
  int fld_4; // edi
  unsigned int fld_C; // ecx
  int fld_8; // eax
  int fld_82; // eax
  unsigned int v10; // ecx
  int fld_87; // eax
  int v12; // edi
  void *pMem; // eax
  char *fld_42; // ecx
  int fld_43; // eax
  char *v16; // esi
  char *v17; // esi
  char *fld_83; // ecx
  int fld_86; // edx
  char *fld_85; // [esp-Ch] [ebp-278h]
  char *fld_84; // [esp-8h] [ebp-274h]
  int v23; // [esp+0h] [ebp-26Ch] BYREF
  char *v24; // [esp+Ch] [ebp-260h]
  void *Block; // [esp+10h] [ebp-25Ch]
  uint32_t v26[147]; // [esp+14h] [ebp-258h] BYREF
  int v27; // [esp+268h] [ebp-4h]
  char *v28; // [esp+274h] [ebp+8h]
  char *fld_832; // [esp+27Ch] [ebp+10h]

  result = dword_796E50;
  qmemcpy(v26, pArg4, 0x244u);
  fld_4 = *(uint32_t *)(this + 4);
  v26[145] = dword_796E50;
  v26[146] = &v23;
  if ( fld_4 != 0 )
  {
    result = -503547889 * (*(uint32_t *)(this + 12) - fld_4);
    fld_C = (*(uint32_t *)(this + 12) - fld_4) / 580;
  }
  else
  {
    fld_C = 0;
  }
  if ( pszArg3 != nullptr )
  {
    if ( fld_4 != 0 )
      fld_8 = (*(uint32_t *)(this + 8) - *(uint32_t *)(this + 4)) / 580;
    else
      fld_8 = 0;
    if ( (char *)&off_70FE3C - fld_8 < pszArg3 )
      sub_415B10(this);  // 【输入映射 vector 管理（按键状态容器）】
    if ( *(uint32_t *)(this + 4) != 0 )
      fld_82 = (*(uint32_t *)(this + 8) - *(uint32_t *)(this + 4)) / 580;
    else
      fld_82 = 0;
    if ( fld_C >= (unsigned int)&pszArg3[fld_82] )
    {
      fld_83 = *(char **)(this + 8);
      fld_832 = fld_83;
      if ( (fld_83 - pszArg2) / 580 >= (unsigned int)pszArg3 )
      {
        v28 = &fld_83[-580 * (uint32_t)pszArg3];
        *(uint32_t *)(this + 8) = sub_415A60(v28, fld_83, fld_83);
        sub_415A20(pszArg2, v28, fld_832);
        return (int)sub_4159F0(pszArg2, &pszArg2[580 * (uint32_t)pszArg3], v26);
      }
      else
      {
        sub_415A60(pszArg2, fld_83, &pszArg2[580 * (uint32_t)pszArg3]);
        fld_84 = &pszArg3[-((*(uint32_t *)(this + 8) - (int)pszArg2) / 580)];
        fld_85 = *(char **)(this + 8);
        v27 = 2;
        sub_415AE0(fld_85, fld_84, v26);
        fld_86 = 580 * (uint32_t)pszArg3 + *(uint32_t *)(this + 8);
        *(uint32_t *)(this + 8) = fld_86;
        return (int)sub_4159F0(pszArg2, (char *)(fld_86 - 580 * (uint32_t)pszArg3), v26);
      }
    }
    else
    {
      if ( (unsigned int)&off_70FE3C - (fld_C >> 1) >= fld_C )
        v10 = (fld_C >> 1) + fld_C;
      else
        v10 = 0;
      if ( *(uint32_t *)(this + 4) != 0 )
        fld_87 = (*(uint32_t *)(this + 8) - *(uint32_t *)(this + 4)) / 580;
      else
        fld_87 = 0;
      if ( v10 < (unsigned int)&pszArg3[fld_87] )
        v10 = (unsigned int)&pszArg3[sub_4159C0((int *)this)];
      v12 = 580 * v10;
      pMem = operator new(580 * v10);
      fld_42 = *(char **)(this + 4);
      Block = pMem;
      v27 = 0;
      v24 = sub_415A60(fld_42, pszArg2, (char *)pMem);
      sub_415AA0(v24, pszArg3, v26);
      sub_415A60(pszArg2, *(char **)(this + 8), &v24[580 * (uint32_t)pszArg3]);
      fld_43 = *(uint32_t *)(this + 4);
      if ( fld_43 != 0 )
        fld_43 = (*(uint32_t *)(this + 8) - fld_43) / 580;
      v16 = &pszArg3[fld_43];
      if ( *(uint32_t *)(this + 4) != 0 )
        j__free(*(void **)(this + 4));
      result = (int)Block;
      v17 = (char *)Block + 580 * (uint32_t)v16;
      *(uint32_t *)(this + 12) = (char *)Block + v12;
      *(uint32_t *)(this + 8) = v17;
      *(uint32_t *)(this + 4) = result;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x415E70 sub_415E70 —— 指定位置插入一条 580B 记录（返回新元素）
//   先算旧位置序号，再经 ·0x415B80 插入 1 条，出参 = this[1] + 580 * 序号。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_415E70(uint32_t *this, uint32_t *uArg2, char *pszArg3, const void *pArg4)
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 580 != 0 )
    v6 = (int)&pszArg3[-fld_e1] / 580;
  else
    v6 = 0;
  sub_415B80((int)this, pszArg3, (char *)1, pArg4);
  *uArg2 = *(this + 1) + 580 * v6;
  return uArg2;
}



// ------------------------------------------------------------
// 0x415EE0 sub_415EE0 —— 尾插一条 580B 记录（满则走插入路径）
//   容量足时尾部直接填充并推进 this+8，否则转 ·0x415E70。
// ------------------------------------------------------------
char */*thiscall*/ sub_415EE0(int this, const void *pArg2)
{
  int fld_4; // ebx
  unsigned int fld_8; // esi
  char *fld_82; // esi
  char *result; // eax

  fld_4 = *(uint32_t *)(this + 4);
  if ( fld_4 != 0 )
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) / 580;
  else
    fld_8 = 0;
  if ( fld_4 == 0 || fld_8 >= (*(uint32_t *)(this + 12) - fld_4) / 580 )
    return (char *)sub_415E70((uint32_t *)this, &pArg2, *(char **)(this + 8), pArg2);
  fld_82 = *(char **)(this + 8);
  result = sub_415AA0(fld_82, (char *)1, pArg2);
  *(uint32_t *)(this + 8) = fld_82 + 580;
  return result;
}



// ------------------------------------------------------------
// 0x415F70 sub_415F70 —— 设备枚举回调（推入全局设备矢量）
//   把 pArg1（580B 设备记录）追加到全局矢量 dword_8A7748，返回 1 = 继续枚举。
// ------------------------------------------------------------
int /*stdcall*/ sub_415F70(const void *pArg1, int nArg2)
{
  sub_415EE0((int)&unk_8A7748, pArg1);
  return 1;
}



// ------------------------------------------------------------
// 0x415F90 sub_415F90 —— 按索引创建设备（枚举 + CreateDevice + 协作级别 + 轴范围回调）
//   全局设备矢量为空时先经 this+3364 对象 vt+16 = EnumDevices(4, ·0x415F70, this, 1) 枚举游戏控制器；
//   取第 nArg2 条记录(+4 = 设备 GUID) → vt+12 建设备到 this+3088 → vt+44 数据格式 unk_749CE4 → vt+52 协作级别 5（hwnd 取 this+3368+16）→ vt+16 轴范围回调 ·0x415960。
// ------------------------------------------------------------
int /*thiscall*/ sub_415F90(int this, int nArg2)
{
  int dword_8A774C2; // ebx
  int dword_8A77502; // ecx
  int v6; // eax
  uint32_t *pThis_C10; // esi

  if ( *(uint8_t *)(this + 4) != 0 )
    return -2147483646;
  dword_8A774C2 = dword_8A774C;
  if ( dword_8A774C == 0 || (dword_8A77502 = dword_8A7750, (dword_8A7750 - dword_8A774C) / 580 == 0) )
  {
    (*(void (/*stdcall*/ **)(uint32_t, int, int (/*stdcall*/ *)(const void *, int), int, int))(**(uint32_t **)(this + 3364) + 16))(
      *(uint32_t *)(this + 3364),
      4,
      sub_415F70,
      this,
      1);
    dword_8A77502 = dword_8A7750;
    dword_8A774C2 = dword_8A774C;
  }
  if ( dword_8A774C2 == 0 )
    return 0x80000000;
  v6 = (dword_8A77502 - dword_8A774C2) / 580;
  if ( v6 == 0 || v6 <= nArg2 )
    return 0x80000000;
  pThis_C10 = (uint32_t *)(this + 3088);
  if ( (*(int (/*stdcall*/ **)(uint32_t, int, int, uint32_t))(**(uint32_t **)(this + 3364) + 12))(
         *(uint32_t *)(this + 3364),
         dword_8A774C2 + 580 * nArg2 + 4,
         this + 3088,
         0) < 0 )
    return -2147483647;
  (*(void (/*stdcall*/ **)(uint32_t, void *))(*(uint32_t *)*pThis_C10 + 44))(*pThis_C10, &unk_749CE4);
  (*(void (/*stdcall*/ **)(uint32_t, uint32_t, int))(*(uint32_t *)*pThis_C10 + 52))(*pThis_C10, *(uint32_t *)(*(uint32_t *)(this + 3368) + 16), 5);
  (*(void (/*stdcall*/ **)(uint32_t))(*(uint32_t *)*pThis_C10 + 32))(*pThis_C10);
  (*(void (/*stdcall*/ **)(uint32_t, int (/*stdcall*/ *)(int, int), int, int))(*(uint32_t *)*pThis_C10 + 16))(*pThis_C10, sub_415960, this, 3);
  *(uint8_t *)(this + 4) = 1;
  return 1;
}



// ------------------------------------------------------------
// 0x4160B0 sub_4160B0 —— 初启壳（vt+32 + 状态位）
//   已初始化返回 0x80000002；否则调 vt+32 后置状态位(this+4) = 1，返回 1。
// ------------------------------------------------------------
int /*thiscall*/ sub_4160B0(uint8_t *this, int nArg2)
{
  if ( *(this + 4) != 0 )
    return -2147483646;
  (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 32))(this);
  *(this + 4) = 1;
  return 1;
}



// ------------------------------------------------------------
// 0x4160E0 sub_4160E0 —— 状态位复位（this+4 = 0，返回 1）
//   清状态位 this+4 的复位壳，无 vt 调用。
// ------------------------------------------------------------
int /*thiscall*/ sub_4160E0(uint8_t *this)
{
  *(this + 4) = 0;
  return 1;
}



// ------------------------------------------------------------
// 0x4160F0 sub_4160F0 —— VK 键按下置位（GetAsyncKeyState → 键态表）
//   状态位门控；VK 码 = this[784+4n]，按下则把键态表 this+269[码] 置 1 并返回 1。
// ------------------------------------------------------------
char /*thiscall*/ sub_4160F0(uint8_t *this, int nArg2)
{
  if ( *(this + 12) == 0 )
    return 0;
  if ( GetAsyncKeyState(*((uint32_t *)this + nArg2 + 196)) == 0 )
    return 0;
  *(this + *((uint32_t *)this + nArg2 + 196) + 269) = 1;
  return 1;
}



// ------------------------------------------------------------
// 0x416140 sub_416140 —— VK 键按下查询（GetAsyncKeyState 非 0）
//   与 ·0x416170（键抬起）配对 —— 本函数判按下。
// ------------------------------------------------------------
bool /*thiscall*/ sub_416140(uint8_t *this, int nArg2)
{
  return *(this + 12) != 0 && GetAsyncKeyState(*((uint32_t *)this + nArg2 + 196)) != 0;
}



// ------------------------------------------------------------
// 0x416170 sub_416170 —— VK 键抬起查询（GetAsyncKeyState == 0）
//   与 ·0x416140 同构（差异: 判定为非 0 的补集，即键抬起）。
// ------------------------------------------------------------
bool /*thiscall*/ sub_416170(uint8_t *this, int nArg2)
{
  return *(this + 12) != 0 && GetAsyncKeyState(*((uint32_t *)this + nArg2 + 196)) == 0;
}



// ------------------------------------------------------------
// 0x4161A0 sub_4161A0 —— 键盘映射表初始化（第二套: VK 虚拟键码）
//   写 107 项 VK 码（37/38/39/40 = 方向键，160..163 = 左右 Shift/Ctrl，112..123 = F1..F12，96..105 = 小键盘）；返回 160（默认键）。
//   与 ·0x415240 的 DIK 套共用表区（dword 索引 196..302）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4161A0(uint32_t *this)
{
  *(this + 200) = 162;
  *(this + 201) = 162;
  *(this + 196) = 37;
  *(this + 197) = 39;
  *(this + 198) = 38;
  *(this + 199) = 40;
  *(this + 206) = 18;
  *(this + 202) = 163;
  *(this + 203) = 160;
  *(this + 204) = 160;
  *(this + 205) = 161;
  *(this + 209) = 32;
  *(this + 211) = 8;
  *(this + 212) = 13;
  *(this + 213) = 45;
  *(this + 214) = 46;
  *(this + 217) = 36;
  *(this + 218) = 35;
  *(this + 219) = 107;
  *(this + 221) = 106;
  *(this + 222) = 27;
  *(this + 226) = 111;
  *(this + 227) = 9;
  *(this + 228) = 20;
  *(this + 229) = 109;
  *(this + 231) = 96;
  *(this + 232) = 97;
  *(this + 233) = 98;
  *(this + 234) = 99;
  *(this + 235) = 100;
  *(this + 236) = 101;
  *(this + 237) = 102;
  *(this + 238) = 103;
  *(this + 239) = 104;
  *(this + 240) = 105;
  *(this + 277) = 112;
  *(this + 278) = 113;
  *(this + 279) = 114;
  *(this + 280) = 115;
  *(this + 281) = 116;
  *(this + 282) = 117;
  *(this + 283) = 118;
  *(this + 284) = 119;
  *(this + 285) = 120;
  *(this + 286) = 121;
  *(this + 287) = 122;
  *(this + 288) = 123;
  *(this + 289) = 42;
  *(this + 300) = 219;
  *(this + 301) = 221;
  *(this + 302) = 222;
  return 160;
}



// ------------------------------------------------------------
// 0x4163A0 sub_4163A0 —— 缓冲按 32 位波形填充（memset32 + 余数 memset）
//   uArg3 >> 2 个 dword 写 4 倍复制值 + 尾 uArg3 & 3 字节 memset；返回原缓冲。
// ------------------------------------------------------------
char */*usercall*/ sub_4163A0@<eax>(int nArg1@<ebx>, char *pszArg2, unsigned int uArg3, char pszArg4)
{
  int v4; // eax

  LOBYTE(nArg1) = pszArg4;
  BYTE1(nArg1) = pszArg4;
  v4 = nArg1 << 16;
  LOWORD(v4) = nArg1;
  memset32(pszArg2, v4, uArg3 >> 2);
  memset(&pszArg2[4 * (uArg3 >> 2)], pszArg4, uArg3 & 3);
  return pszArg2;
}



// ------------------------------------------------------------
// 0x4163E0 sub_4163E0 —— 转发 vt+32（无守卫）
//   无状态位守卫的 vt+32 直通（薄转发壳）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4163E0(void *this)
{
  return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 32))(this);
}



// ------------------------------------------------------------
// 0x4163F0 sub_4163F0 —— 初启（vt+32 结果透传 + 状态位）
//   已初始化返回 0x80000002；vt+32 失败原样返回，成功置状态位(this+4) = 1。
// ------------------------------------------------------------
int /*thiscall*/ sub_4163F0(uint8_t *this)
{
  int result; // eax

  if ( *(this + 4) != 0 )
    return -2147483646;
  result = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 32))(this);
  if ( result >= 0 )
  {
    *(this + 4) = 1;
    return 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x416420 sub_416420 —— 复位（vt+36 + 状态位清 0）
//   先调 vt+36 再清 this+4，返回 vt+36 结果。
// ------------------------------------------------------------
int /*thiscall*/ sub_416420(uint8_t *this)
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 36))(this);
  *(this + 4) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x416430 sub_416430 —— 绘制转发（vt+48 + 默认参数）
//   补默认参数 0, 0, -1, -1 与 1.0f / 1.0f（1065353216 = 浮点 1.0）后调 vt+48。
// ------------------------------------------------------------
int /*thiscall*/ sub_416430(void *this, int nArg2, int nArg3, int nArg4, int nArg5, int nArg6)
{
  return (*(int (/*thiscall*/ **)(void *, int, int, int, int, uint32_t, uint32_t, int, int, int, int, int))(*(uint32_t *)this + 48))(
           this,
           nArg2,
           nArg3,
           nArg4,
           nArg5,
           0,
           0,
           -1,
           -1,
           1065353216,
           1065353216,
           nArg6);
}



// ------------------------------------------------------------
// 0x416470 unknown_libname_3
// ------------------------------------------------------------
// Microsoft VisualC 2-14/net runtime
int /*thiscall*/ unknown_libname_3(void *this)
{
  return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 48))(this);
}



// ------------------------------------------------------------
// 0x416480 sub_416480 —— std::string 析构（容量 ≥16 释放 + 复位）
//   容量 ≥16 释放堆缓冲，长度清零、容量复位 15；pszArg2 位 1 时连对象一起释放。
// ------------------------------------------------------------
void **/*thiscall*/ sub_416480(void **Block, char pszArg2)
{
  if ( (unsigned int)*(Block + 6) >= 0x10 )
    j__free(*(Block + 1));
  *(Block + 5) = nullptr;
  *(Block + 6) = (void *)15;
  *((uint8_t *)Block + 4) = 0;
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ============================================================
// SECTION 0x4164C0 — string/vector 容器工具
// ============================================================
// ------------------------------------------------------------
// 0x4164C0 sub_4164C0 —— std::string 追加填充 n 个字符
//   _Xlen 溢出校验 → ·0x4012B0 缓冲重分配 → memset32 按 4 倍复制填充 → 更新长度并补 0。
//   （MSVC append(n, ch) 实例 —— 带 _String_base 指针与容量字段 this[5]/this[6]。）
// ------------------------------------------------------------
size_t */*thiscall*/ sub_4164C0(size_t *this, unsigned int uArg2, char pszArg3)  // 【string/vector 容器工具】
{
  unsigned int uArg22; // ebx
  unsigned int fld_e6; // eax
  bool v6; // zf
  char *pThis_1; // edx
  unsigned int pBuf; // ecx
  char *fld_e52; // edi
  char pBuf2; // dl
  int v12; // eax
  bool fld_e62; // cf
  unsigned int fld_e5; // [esp+10h] [ebp+8h]

  uArg22 = uArg2;
  if ( -1 - *(this + 5) <= uArg2 )
    std::_String_base::_Xlen((std::_String_base *)this);
  if ( uArg2 == 0 )
    return this;
  fld_e5 = uArg2 + *(this + 5);
  if ( fld_e5 == -1 )
    std::_String_base::_Xlen((std::_String_base *)this);
  fld_e6 = *(this + 6);
  if ( fld_e6 < fld_e5 )
  {
    sub_4012B0(this, fld_e5, *(this + 5));
    v6 = fld_e5 == 0;
    goto LABEL_8;
  }
  v6 = fld_e5 == 0;
  if ( fld_e5 != 0 )
  {
LABEL_8:
    if ( !v6 )
    {
      if ( *(this + 6) < 0x10 )
        pThis_1 = (char *)(this + 1);
      else
        pThis_1 = (char *)*(this + 1);
      pBuf = uArg22;
      LOBYTE(uArg22) = pszArg3;
      BYTE1(uArg22) = pszArg3;
      fld_e52 = &pThis_1[*(this + 5)];
      pBuf2 = pBuf;
      pBuf >>= 2;
      v12 = uArg22 << 16;
      LOWORD(v12) = uArg22;
      memset32(fld_e52, v12, pBuf);
      memset(&fld_e52[4 * pBuf], pszArg3, pBuf2 & 3);
      fld_e62 = *(this + 6) < 0x10;
      *(this + 5) = fld_e5;
      if ( !fld_e62 )
      {
        *(uint8_t *)(*(this + 1) + fld_e5) = 0;
        return this;
      }
      *((uint8_t *)this + fld_e5 + 4) = 0;
    }
    return this;
  }
  *(this + 5) = 0;
  if ( fld_e6 < 0x10 )
    *((uint8_t *)this + 4) = 0;
  else
    *(uint8_t *)*(this + 1) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x4165A0 sub_4165A0 —— string 对象区间反向赋值拷贝（28B/个）
//   从 pArg2 到 pArg1 逆序对 28B 元素调 ·0x4014D0（assign）构造到 pArg3 起，返回目标起点。
// ------------------------------------------------------------
size_t */*cdecl*/ sub_4165A0(size_t *pArg1, size_t *pArg2, size_t *pArg3)
{
  size_t *pArg22; // esi
  size_t *pArg32; // edi

  pArg22 = pArg2;
  if ( pArg1 == pArg2 )
    return pArg3;
  pArg32 = pArg3;
  do
  {
    pArg22 -= 7;
    pArg32 -= 7;
    sub_4014D0(pArg32, pArg22, 0, 0xFFFFFFFF);
  }
  while ( pArg22 != pArg1 );
  return pArg32;
}



// ------------------------------------------------------------
// 0x4165E0 sub_4165E0 —— std::string 析构（单对象，固定返回 0）
//   与 ·0x416480 同构（差异: 不做对象自身的条件释放）。
// ------------------------------------------------------------
int /*stdcall*/ sub_4165E0(int pArg1)
{
  if ( *(uint32_t *)(pArg1 + 24) >= 0x10u )
    j__free(*(void **)(pArg1 + 4));
  *(uint32_t *)(pArg1 + 24) = 15;
  *(uint32_t *)(pArg1 + 20) = 0;
  *(uint8_t *)(pArg1 + 4) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x416610 sub_416610 [串: "vector<T> too long"]
// ------------------------------------------------------------
void /*noreturn*/ sub_416610()
{
  uint32_t pExceptionObject[10]; // [esp+0h] [ebp-50h] BYREF
  size_t v1; // [esp+28h] [ebp-28h] BYREF
  char v2; // [esp+2Ch] [ebp-24h]
  int v3; // [esp+3Ch] [ebp-14h]
  int v4; // [esp+40h] [ebp-10h]
  int v5; // [esp+4Ch] [ebp-4h]

  v4 = 15;
  v3 = 0;
  v2 = 0;
  sub_4015C0(&v1, "vector<T> too long", 0x12u);  // 【std::string构造赋值】
  v5 = 0;
  sub_401740(pExceptionObject, &v1);
  pExceptionObject[0] = &std::length_error::`vftable';
  _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x416680 sub_416680 —— 转发 ·0x4165A0（区间拷贝构造）
//   区间对象拷贝构造适配（MSVC _Uninit_copy 命名实例）。
// ------------------------------------------------------------
size_t */*cdecl*/ sub_416680(size_t *pArg1, size_t *pArg2, size_t *pArg3)
{
  return sub_4165A0(pArg1, pArg2, pArg3);
}



// ------------------------------------------------------------
// 0x4166A0 sub_4166A0 —— 析构区间内 28B string 元素
//   [nArg1, nArg2) 每 28B 释放堆缓冲并复位（长度 0 / 容量 15）。
// ------------------------------------------------------------
void /*cdecl*/ sub_4166A0(int nArg1, int nArg2)
{
  int i; // esi

  for ( i = nArg1; i != nArg2; i += 28 )
  {
    if ( *(uint32_t *)(i + 24) >= 0x10u )
      j__free(*(void **)(i + 4));
    *(uint32_t *)(i + 24) = 15;
    *(uint32_t *)(i + 20) = 0;
    *(uint8_t *)(i + 4) = 0;
  }
}



// ------------------------------------------------------------
// 0x4166E0 sub_4166E0 —— 区间拷贝构造（28B string 元素）
//   [pArg1, pArg2) 逐个拷到 nArg3 起（先置空串再 ·0x4014D0 assign），返回目标尾。
// ------------------------------------------------------------
int /*cdecl*/ sub_4166E0(size_t *pArg1, size_t *pArg2, int nArg3)
{
  int nArg32; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  nArg32 = nArg3;
  v6[4] = v6;
  v6[3] = nArg3;
  v7 = 0;
  while ( pArg1 != pArg2 )
  {
    LOBYTE(v7) = 1;
    if ( nArg32 != 0 )
    {
      *(uint32_t *)(nArg32 + 24) = 15;
      *(uint32_t *)(nArg32 + 20) = 0;
      *(uint8_t *)(nArg32 + 4) = 0;
      sub_4014D0((size_t *)nArg32, pArg1, 0, 0xFFFFFFFF);
    }
    nArg32 += 28;
    LOBYTE(v7) = 0;
    pArg1 += 7;
  }
  return nArg32;
}



// ------------------------------------------------------------
// 0x416780 sub_416780 —— 重复填充 n 份 28B string 元素
//   循环 n 次向 nArg1 起逐条 assign 复制 pArg3；返回尾指针。
// ------------------------------------------------------------
size_t */*cdecl*/ sub_416780(int nArg1, int nArg2, size_t *pArg3)
{
  int nArg12; // esi
  size_t *result; // eax
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  nArg12 = nArg1;
  v6[4] = v6;
  v6[3] = nArg1;
  v7 = 0;
  while ( nArg2 != 0 )
  {
    LOBYTE(v7) = 1;
    if ( nArg12 != 0 )
    {
      *(uint32_t *)(nArg12 + 24) = 15;
      *(uint32_t *)(nArg12 + 20) = 0;
      *(uint8_t *)(nArg12 + 4) = 0;
      result = sub_4014D0((size_t *)nArg12, pArg3, 0, 0xFFFFFFFF);
    }
    --nArg2;
    nArg12 += 28;
    LOBYTE(v7) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x416820 sub_416820 —— 转发 ·0x4166A0（区间析构）
//   区间析构适配（MSVC _Destroy_range 命名实例）。
// ------------------------------------------------------------
void /*stdcall*/ sub_416820(int nArg1, int nArg2)
{
  sub_4166A0(nArg1, nArg2);
}



// ------------------------------------------------------------
// 0x416840 sub_416840 —— 转发 ·0x4166E0（区间拷贝构造）
//   区间拷贝构造适配（MSVC _Uninit_copy 命名实例）。
// ------------------------------------------------------------
int /*stdcall*/ sub_416840(size_t *pArg1, size_t *pArg2, int nArg3)
{
  return sub_4166E0(pArg1, pArg2, nArg3);
}



// ------------------------------------------------------------
// 0x416860 sub_416860 —— 填充 + 返回尾指针（nArg1 + 28 * nArg2）
//   填充后返回尾指针 —— 供插入路径计算新尾。
// ------------------------------------------------------------
int /*stdcall*/ sub_416860(int nArg1, int nArg2, size_t *pArg3)
{
  sub_416780(nArg1, nArg2, pArg3);
  return nArg1 + 28 * nArg2;
}



// ============================================================
// SECTION 0x416890 — 字形/文本对象容器（大函数，字体缓存管理）
// ============================================================
// ------------------------------------------------------------
// 0x416890 sub_416890 —— 28B string 矢量插入（MSVC vector 实例）
//   容量三分支与 ·0x415B80 同族，元素步长 28B（std::string），上限 153391689；调 ·0x416680/·0x416860/·0x52C080。
//   溢出调 ·0x416610 抛 length_error。
// ------------------------------------------------------------
void /*thiscall*/ sub_416890(int *this, int pArg2, unsigned int uArg3, int nArg4)  // 【字形/文本对象容器（大函数，字体缓存管理）】
{
  int fld_e1; // ebx
  unsigned int fld_e3; // ecx
  int fld_e2; // eax
  int fld_e22; // eax
  unsigned int v10; // ecx
  int fld_e27; // eax
  char *pMem; // ebx
  int fld_e13; // eax
  unsigned int v14; // edi
  int fld_e14; // eax
  void *fld_e23; // ecx
  int fld_e26; // edx
  int fld_e12; // [esp-18h] [ebp-60h]
  int fld_e28; // [esp-10h] [ebp-58h]
  int fld_e25; // [esp-Ch] [ebp-54h]
  unsigned int fld_e24; // [esp-8h] [ebp-50h]
  uint32_t v23[4]; // [esp+0h] [ebp-48h] BYREF
  void *Block; // [esp+10h] [ebp-38h]
  char *pMem2; // [esp+14h] [ebp-34h]
  char v26[4]; // [esp+18h] [ebp-30h] BYREF
  void *v27; // [esp+1Ch] [ebp-2Ch]
  int v28; // [esp+2Ch] [ebp-1Ch]
  unsigned int v29; // [esp+30h] [ebp-18h]
  int dword_796E502; // [esp+34h] [ebp-14h]
  uint32_t *v31; // [esp+38h] [ebp-10h]
  int v32; // [esp+44h] [ebp-4h]
  int v33; // [esp+50h] [ebp+8h]
  int v34; // [esp+54h] [ebp+Ch]

  v31 = v23;
  dword_796E502 = dword_796E50;
  v23[3] = this;
  v29 = 15;
  v28 = 0;
  LOBYTE(v27) = 0;
  sub_4014D0((std::_String_base *)v26, nArg4, 0, -1);
  fld_e1 = *(this + 1);
  v32 = 0;
  if ( fld_e1 != 0 )
    fld_e3 = (*(this + 3) - fld_e1) / 28;
  else
    fld_e3 = 0;
  if ( uArg3 != 0 )
  {
    if ( fld_e1 != 0 )
      fld_e2 = (*(this + 2) - *(this + 1)) / 28;
    else
      fld_e2 = 0;
    if ( 153391689 - fld_e2 < uArg3 )
      sub_416610(this);
    if ( *(this + 1) != 0 )
      fld_e22 = (*(this + 2) - *(this + 1)) / 28;
    else
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )
    {
      fld_e23 = (void *)*(this + 2);
      Block = fld_e23;
      if ( ((int)fld_e23 - pArg2) / 28 >= uArg3 )
      {
        v33 = (int)fld_e23 - 28 * uArg3;
        *(this + 2) = sub_4166E0(v33, (int)fld_e23, (int)fld_e23);
        sub_416680(pArg2, v33, Block);
        sub_52C080(pArg2, pArg2 + 28 * uArg3, v26);
      }
      else
      {
        sub_4166E0(pArg2, (int)fld_e23, pArg2 + 28 * uArg3);
        fld_e24 = uArg3 - (*(this + 2) - pArg2) / 28;
        fld_e25 = *(this + 2);
        LOBYTE(v32) = 3;
        sub_416860(fld_e25, fld_e24, v26);
        fld_e26 = 28 * uArg3 + *(this + 2);
        *(this + 2) = fld_e26;
        v32 = 0;
        sub_52C080(pArg2, fld_e26 - 28 * uArg3, v26);
      }
    }
    else
    {
      if ( 153391689 - (fld_e3 >> 1) >= fld_e3 )
        v10 = (fld_e3 >> 1) + fld_e3;
      else
        v10 = 0;
      if ( *(this + 1) != 0 )
        fld_e27 = (*(this + 2) - *(this + 1)) / 28;
      else
        fld_e27 = 0;
      if ( v10 < uArg3 + fld_e27 )
        v10 = uArg3 + sub_52AEF0(this);
      v34 = 28 * v10;
      pMem = (char *)operator new(28 * v10);
      fld_e12 = *(this + 1);
      Block = pMem;
      pMem2 = pMem;
      LOBYTE(v32) = 1;
      pMem2 = (char *)sub_4166E0(fld_e12, pArg2, (int)pMem);
      sub_416780((int)pMem2, uArg3, (int)v26);
      fld_e28 = *(this + 2);
      pMem2 += 28 * uArg3;
      sub_4166E0(pArg2, fld_e28, (int)pMem2);
      fld_e13 = *(this + 1);
      if ( fld_e13 != 0 )
        fld_e13 = (*(this + 2) - fld_e13) / 28;
      v14 = fld_e13 + uArg3;
      fld_e14 = *(this + 1);
      if ( fld_e14 != 0 )
      {
        sub_4166A0(fld_e14, *(this + 2));
        j__free((void *)*(this + 1));
      }
      *(this + 3) = (int)&pMem[v34];
      *(this + 2) = (int)&pMem[28 * v14];
      *(this + 1) = (int)pMem;
    }
  }
  if ( v29 >= 0x10 )
    j__free(v27);
}


// ------------------------------------------------------------
// 0x416BD0 sub_416BD0 —— 指定位置插入一条 28B 记录（返回新元素）
//   先算旧位置序号，再经 ·0x416890 插入 1 条，出参 = this[1] + 28 * 序号。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_416BD0(uint32_t *this, uint32_t *uArg2, size_t *pArg3, size_t *pArg4)
{
  int fld_e1; // esi
  int v6; // esi

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 && (*(this + 2) - fld_e1) / 28 != 0 )
    v6 = ((int)pArg3 - fld_e1) / 28;
  else
    v6 = 0;
  sub_416890((int)this, pArg3, 1u, pArg4);  // 【字形/文本对象容器（大函数，字体缓存管理）】
  *uArg2 = *(this + 1) + 28 * v6;
  return uArg2;
}



// ------------------------------------------------------------
// 0x416C40 sub_416C40 —— 尾插一条 28B 记录（满则走插入路径）
//   与 ·0x415EE0 同构（差异: 元素步长 28B，配套 ·0x416BD0 / ·0x416780）。
// ------------------------------------------------------------
size_t */*thiscall*/ sub_416C40(int this, size_t *pArg2)
{
  int fld_4; // ebx
  unsigned int fld_8; // esi
  int fld_82; // esi
  size_t *result; // eax

  fld_4 = *(uint32_t *)(this + 4);
  if ( fld_4 != 0 )
    fld_8 = (*(uint32_t *)(this + 8) - fld_4) / 28;
  else
    fld_8 = 0;
  if ( fld_4 == 0 || fld_8 >= (*(uint32_t *)(this + 12) - fld_4) / 28 )
    return sub_416BD0((uint32_t *)this, &pArg2, *(size_t **)(this + 8), pArg2);
  fld_82 = *(uint32_t *)(this + 8);
  result = sub_416780(fld_82, 1, pArg2);
  *(uint32_t *)(this + 8) = fld_82 + 28;
  return result;
}



// ============================================================
// SECTION 0x416CD0 — GDI 资源清理（DeleteObject 族）
// ============================================================
// ------------------------------------------------------------
// 0x416CD0 sub_416CD0 —— 绘制状态结构初始化（返回 0）
//   13 个 dword: 清零后置 +16 = 6、+20 = 12、+28 = 1600 —— 与 ·0x416DA0 的局部结构同型（绘制状态模板）。
// ------------------------------------------------------------
int /*thiscall*/ sub_416CD0(uint8_t *this)  // 【GDI 资源清理（DeleteObject 族）】
{
  *this = 0;
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  *((uint32_t *)this + 3) = 0;
  *((uint32_t *)this + 4) = 6;
  *((uint32_t *)this + 5) = 12;
  *((uint32_t *)this + 6) = 0;
  *((uint32_t *)this + 7) = 1600;
  *((uint32_t *)this + 8) = 0;
  *((uint32_t *)this + 9) = 0;
  *((uint32_t *)this + 10) = 0;
  *((uint32_t *)this + 11) = 0;
  *((uint32_t *)this + 12) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x416D10 sub_416D10 —— 绘制状态结构初始化（void 版）
//   与 ·0x416CD0 同构（差异: 无返回值）。
// ------------------------------------------------------------
void /*thiscall*/ sub_416D10(uint8_t *this)
{
  *this = 0;
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  *((uint32_t *)this + 3) = 0;
  *((uint32_t *)this + 4) = 6;
  *((uint32_t *)this + 5) = 12;
  *((uint32_t *)this + 6) = 0;
  *((uint32_t *)this + 7) = 1600;
  *((uint32_t *)this + 8) = 0;
  *((uint32_t *)this + 9) = 0;
  *((uint32_t *)this + 10) = 0;
  *((uint32_t *)this + 11) = 0;
  *((uint32_t *)this + 12) = 0;
}



// ------------------------------------------------------------
// 0x416D50 sub_416D50 —— GDI 句柄释放 + 结构清零
//   先 DeleteObject(this[11] = 偏移 +44 的 HGDIOBJ) 再 13 个字段全零。
// ------------------------------------------------------------
void /*thiscall*/ sub_416D50(HGDIOBJ *this)
{
  if ( *(this + 11) != nullptr )
  {
    DeleteObject(*(this + 11));
    *(this + 11) = nullptr;
  }
  *(uint8_t *)this = 0;
  *((uint8_t *)this + 1) = 0;
  *((uint8_t *)this + 2) = 0;
  *((uint8_t *)this + 3) = 0;
  *(this + 3) = nullptr;
  *(this + 4) = nullptr;
  *(this + 5) = nullptr;
  *(this + 6) = nullptr;
  *(this + 7) = nullptr;
  *(this + 8) = nullptr;
  *(this + 9) = nullptr;
  *(this + 10) = nullptr;
  *(this + 11) = nullptr;
  *(this + 12) = nullptr;
}



// ------------------------------------------------------------
// 0x416DA0 sub_416DA0 —— 绘制提交封装（状态分支 + 临时对象释放）
//   局部状态结构 = 0,0,0,0,6,12,0,1600,...（同 ·0x416CD0）；按 a1+44 选 a1 对象 vt+68 或 vt+72 开始；
//   vt+80(a2, a3, a4, a11) 提交绘制 → 需要时 vt+76 收尾 → 局部 HGDIOBJ 交 DeleteObject 释放。
// ------------------------------------------------------------
HGDIOBJ /*stdcall*/ sub_416DA0(
        uint8_t *a1,
        int a2,
        int a3,
        int a4,
        char a5,
        char a6,
        int a7,
        int a8,
        int a9,
        int a10,
        int a11)
{
  bool v11; // zf
  int v12; // edx
  HGDIOBJ result; // eax
  uint8_t v14[4]; // [esp+8h] [ebp-44h] BYREF
  int v15; // [esp+Ch] [ebp-40h]
  int v16; // [esp+10h] [ebp-3Ch]
  int v17; // [esp+14h] [ebp-38h]
  int v18; // [esp+18h] [ebp-34h]
  int v19; // [esp+1Ch] [ebp-30h]
  int v20; // [esp+20h] [ebp-2Ch]
  int v21; // [esp+24h] [ebp-28h]
  int v22; // [esp+28h] [ebp-24h]
  int v23; // [esp+2Ch] [ebp-20h]
  int v24; // [esp+30h] [ebp-1Ch]
  HGDIOBJ ho; // [esp+34h] [ebp-18h]
  int v26; // [esp+38h] [ebp-14h]
  char v27; // [esp+3Fh] [ebp-Dh]
  int v28; // [esp+48h] [ebp-4h]

  v27 = 0;
  v14[2] = a5;
  v16 = a8;
  v11 = a1[44] == 0;
  v15 = a7;
  v14[3] = a6;
  v12 = *(uint32_t *)a1;
  v28 = 0;
  v14[0] = 0;
  v14[1] = 0;
  v17 = 0;
  v18 = 6;
  v19 = 12;
  v20 = 0;
  v21 = 1600;
  v22 = 0;
  v23 = 0;
  v24 = 0;
  ho = nullptr;
  v26 = 0;
  if ( v11 )
  {
    (*(void (/*thiscall*/ **)(uint8_t *, uint8_t *))(v12 + 68))(a1, v14);
  }
  else
  {
    v27 = 1;
    (*(void (/*thiscall*/ **)(uint8_t *, uint8_t *))(v12 + 72))(a1, v14);
  }
  (*(void (/*cdecl*/ **)(uint8_t *, int, int, int, int))(*(uint32_t *)a1 + 80))(a1, a2, a3, a4, a11);
  if ( v27 != 0 )
    (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)a1 + 76))(a1);
  result = ho;
  if ( ho != nullptr )
    return (HGDIOBJ)DeleteObject(ho);
  return result;
}



// ------------------------------------------------------------
// 0x416E70 sub_416E70 —— 字体对象 + 全局字形缓存复位
//   清 this+4 起 0x3C、this+19 与 this+25..32；再清三张全局表 word_8D77D8 / word_8B77D8（各 0x1FFFC）与 word_8A7798 / word_8A7758（各 0x40）。
// ------------------------------------------------------------
int /*thiscall*/ sub_416E70(uint32_t *this)
{
  *(this + 19) = 0;
  memset(this + 4, 0, 0x3Cu);
  *(this + 25) = 0;
  *(this + 26) = 0;
  *(this + 27) = 0;
  *(this + 28) = 0;
  *(this + 29) = 0;
  *(this + 30) = 0;
  *(this + 31) = 0;
  *(this + 32) = 0;
  memset(&word_8D77D8, 0, 0x1FFFCu);
  unk_8F77D4 = 0;
  memset(&word_8B77D8, 0, 0x1FFFCu);
  unk_8D77D4 = 0;
  memset(&word_8A7798, 0, 0x40u);
  memset(&word_8A7758, 0, 0x40u);
  return 0;
}



// ------------------------------------------------------------
// 0x416EE0 sub_416EE0 —— 字形位图对象释放（this+29 个）+ 字段复位
//   逐个经 this+3 管理器 vt+12 归还 this[19] 数组中对象（4B 数组项），再清计数与结构体。
// ------------------------------------------------------------
int /*thiscall*/ sub_416EE0(uint32_t *this)
{
  unsigned int i; // edi

  for ( i = 0; i < *(this + 29); ++i )
    (*(void (/*thiscall*/ **)(uint32_t, unsigned int))(**(uint32_t **)(*(this + 3) + 12) + 12))(
      *(uint32_t *)(*(this + 3) + 12),
      *(this + 19) + 4 * i);
  *(this + 28) = 0;
  *(this + 29) = 0;
  *(this + 30) = 0;
  *(this + 31) = 0;
  *(this + 32) = 0;
  memset(this + 4, 0, 0x3Cu);
  *(this + 25) = 0;
  *(this + 26) = 0;
  *(this + 27) = 0;
  return 0;
}



// ============================================================
// SECTION 0x416F40 — ★ NeopleFontFile 自有字体文件校验（fopen + 魔数 "NeopleFontFile"）
// ============================================================
// ------------------------------------------------------------
// 0x416F40 sub_416F40
// ------------------------------------------------------------
// 【解读】
//   NeopleFontFile 校验（写向）: fopen + wsprintfA 生成字体文件名 → 写魔数 "NeopleFontFile" → fclose。
//   Neople 自有字体容器格式（与 0x417030 读校验成对）。
// ------------------------------------------------------------
int /*thiscall*/ sub_416F40(char *this, char *FileName)  // 【NeopleFontFile 自有字体文件校验（fopen + 魔数 NeopleF…】
{
  int result; // eax
  FILE *pFile; // ebx
  int pThis_3; // edx
  int pThis_2; // ecx
  int pThis_28; // esi
  CHAR Buffer[48]; // [esp+4h] [ebp-34h] BYREF
  int dword_796E502; // [esp+34h] [ebp-4h]

  dword_796E502 = dword_796E50;
  if ( *(this + 4) == 0 )
    return -2147483647;
  pFile = fopen(FileName, "wb");
  if ( pFile == nullptr )
    return -2147483644;
  memset(Buffer, 0, sizeof(Buffer));
  wsprintfA(Buffer, "NeopleFontFile");
  pThis_3 = *((uint32_t *)this + 3);
  pThis_2 = *((uint32_t *)this + 2);
  memset(&Buffer[36], 255, 12);
  *(uint32_t *)&Buffer[32] = 1;
  *(uint32_t *)&Buffer[36] = *(uint32_t *)(pThis_3 + 8);
  *(uint32_t *)&Buffer[40] = pThis_2;
  *(uint32_t *)&Buffer[44] = 1;
  sub_66BC25(Buffer, 0x30u, 1u, pFile);
  sub_66BC25(this + 16, 0x3Cu, 1u, pFile);
  pThis_28 = (*(int (/*thiscall*/ **)(char *, FILE *))(*(uint32_t *)this + 40))(this, pFile);
  fclose(pFile);
  result = pThis_28;
  if ( pThis_28 >= 0 )
    return 1;
  return result;
}



// ------------------------------------------------------------
// 0x417030 sub_417030
// ------------------------------------------------------------
// 【解读】
//   NeopleFontFile 读校验: fopen + sub_66BD5A 读头 + strcmp("NeopleFontFile") + sub_402AE0 登记文件名。
// ------------------------------------------------------------
int /*thiscall*/ sub_417030(uint32_t *this, char *FileName)
{
  FILE *pFile; // eax
  int fld_e5; // eax
  int fld_e4; // ecx
  int v7; // esi
  FILE *Stream; // [esp+4h] [ebp-38h]
  char Buffer[32]; // [esp+8h] [ebp-34h] BYREF
  int v10; // [esp+28h] [ebp-14h]
  int v11; // [esp+30h] [ebp-Ch]
  int dword_796E502; // [esp+38h] [ebp-4h]

  dword_796E502 = dword_796E50;
  if ( *((uint8_t *)this + 4) == 0 )
    return -2147483647;
  pFile = fopen(FileName, "rb");
  Stream = pFile;
  if ( pFile == nullptr )
    return -2147483644;
  sub_66BD5A(Buffer, 0x30u, 1u, pFile);  // 【fread封装】
  if ( strcmp(Buffer, "NeopleFontFile") == 0 && v10 == 1 && v11 == *(this + 2) )
  {
    sub_66BD5A(this + 4, 0x3Cu, 1u, Stream);  // 【fread封装】
    fld_e5 = *(this + 5);
    fld_e4 = *(this + 4);
    *(this + 26) = fld_e5;
    *(this + 27) = fld_e4;
    *(this + 25) = 2 * fld_e5;
    sub_402AE0((int)(this + 20), (const char *)this + 44);
    v7 = (*(int (/*thiscall*/ **)(uint32_t *, FILE *))(*this + 44))(this, Stream);
    fclose(Stream);
    if ( v7 >= 0 )
      return 1;
    else
      return v7;
  }
  else
  {
    fclose(Stream);
    return 0x80000000;
  }
}



// ------------------------------------------------------------
// 0x417150 sub_417150 —— 文本绘制核心（查字形块 + 裁剪 + 块位图提交）
//   GBK 解码（首字节 >= 0 单字节，否则双字节）→ word_8B77D8 查字形序号 → 拆 (块号, 块内行, 块内列)；
//   块位图 = *(this+19) 矢量第 (序号/每块字数) 项，经该对象 vt+132(源矩形, 字库矩形, 目标表面, 0, 参数) 提交；
//   目标表面裁剪域 a2+20 / a2+24 越界即止；推进 5 像素/ASCII、10 像素/双字节。
// ------------------------------------------------------------
int /*thiscall*/ sub_417150(unsigned int *this, int pArg2, int nArg3, int nArg4, int nArg5, const char *pArg6, int nArg7)
{
  const char *pArg62; // edi
  int result; // eax
  int v10; // esi
  char v11; // al
  uint16_t v12; // ax
  unsigned int fld_e30; // esi
  int v14; // ecx
  unsigned int v15; // eax
  unsigned int v16; // ecx
  unsigned int fld_e31; // esi
  int v18; // eax
  int v19; // edx
  int nArg322; // esi
  int v21; // edi
  int fld_e27; // edx
  int v23; // edx
  bool v24; // cc
  int fld_e19; // ecx
  int v26; // esi
  uint32_t v27[4]; // [esp+8h] [ebp-38h] BYREF
  int v28; // [esp+18h] [ebp-28h] BYREF
  int v29; // [esp+1Ch] [ebp-24h]
  int v30; // [esp+20h] [ebp-20h]
  int v31; // [esp+24h] [ebp-1Ch]
  unsigned int v32; // [esp+28h] [ebp-18h]
  unsigned int v33; // [esp+2Ch] [ebp-14h]
  int fld_e25; // [esp+30h] [ebp-10h]
  int nArg32; // [esp+34h] [ebp-Ch]
  int v36; // [esp+38h] [ebp-8h]
  int v37; // [esp+3Ch] [ebp-4h]
  int v38; // [esp+50h] [ebp+10h]

  pArg62 = pArg6;
  v38 = nArg4 - 1;
  result = strlen(pArg6);
  v32 = result;
  if ( result != 0 )
  {
    v10 = 0;
    v36 = 0;
    v37 = 0;
    nArg32 = nArg3;
    while ( 1 )
    {
      v11 = pArg62[v10];
      v12 = v11 >= 0 ? word_8B77D8[v11] : word_8B77D8[*(uint16_t *)&pArg62[v10]];
      fld_e30 = *(this + 30);
      v14 = v12;
      v15 = v12 / fld_e30;
      fld_e25 = *(this + 25);
      v16 = v14 - v15 * fld_e30;
      fld_e31 = *(this + 31);
      v33 = v15;
      v18 = v16 / fld_e31;
      v19 = v16 % fld_e31;
      nArg322 = nArg32;
      v27[0] = nArg32;
      v21 = v19 * fld_e25;
      fld_e27 = *(this + 27);
      v28 = v21;
      v30 = fld_e25 + v21;
      v29 = v18 * fld_e27;
      result = nArg3 + v37 + fld_e25;
      v31 = fld_e27 + v29;
      v23 = v38 + fld_e27;
      v24 = nArg32 <= *(uint32_t *)(pArg2 + 20);
      v27[1] = v38;
      v27[2] = result;
      v27[3] = v23;
      if ( !v24 || v38 > *(uint32_t *)(pArg2 + 24) || v23 < 0 )
        break;
      if ( result > 0 )
      {
        fld_e19 = *(uint32_t *)(*(this + 19) + 4 * v33);
        if ( fld_e19 != 0 )
          (*(void (/*thiscall*/ **)(int, uint32_t *, int *, int, uint32_t, int, int))(*(uint32_t *)fld_e19 + 132))(
            fld_e19,
            v27,
            &v28,
            pArg2,
            0,
            nArg5,
            nArg7);
      }
      if ( pArg6[v36] >= 0 )
      {
        v26 = nArg322 + 5;
        v37 += 5;
        result = v36 + 1;
      }
      else
      {
        result = v36 + 2;
        v37 += 10;
        v26 = nArg322 + 10;
      }
      nArg32 = v26;
      v36 = result;
      if ( result >= v32 )
        break;
      pArg62 = pArg6;
      v10 = v36;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4172B0 sub_4172B0 —— 描边 / 阴影文本绘制封装
//   a7 非 0 时按 8 邻域 ±1/±2 共 12 次 ·0x417150 描边再画本体；a8 且无描边时左上单次偏移阴影；
//   前后 ·0x404F40 / ·0x404F80（类别 5）为计时包裹。
// ------------------------------------------------------------
void /*userpurge*/ sub_4172B0(
        int a1@<eax>,
        unsigned int *a2@<ecx>,
        int a3,
        int a4,
        int a5,
        int a6,
        char a7,
        char a8,
        int a9,
        int a10,
        int a11,
        int a12,
        const char *a13)
{
  int v14; // eax

  sub_404F40(a1, 5u);
  if ( a7 != 0 )
  {
    sub_417150(a2, a3, a4 + 1, a5 + 1, a9, a13, 1);
    sub_417150(a2, a3, a4 - 1, a5 - 1, a9, a13, 1);
    sub_417150(a2, a3, a4 + 1, a5 - 1, a9, a13, 1);
    sub_417150(a2, a3, a4 - 1, a5 + 1, a9, a13, 1);
    sub_417150(a2, a3, a4 - 1, a5, a9, a13, 1);
    sub_417150(a2, a3, a4 + 1, a5, a9, a13, 1);
    sub_417150(a2, a3, a4, a5 + 1, a9, a13, 1);
    sub_417150(a2, a3, a4, a5 - 1, a9, a13, 1);
    sub_417150(a2, a3, a4 + 2, a5, a9, a13, 1);
    sub_417150(a2, a3, a4 - 2, a5, a9, a13, 1);
    sub_417150(a2, a3, a4, a5 + 2, a9, a13, 1);
    sub_417150(a2, a3, a4, a5 - 2, a9, a13, 1);
  }
  if ( a8 != 0 && a7 == 0 )
    sub_417150(a2, a3, a4 + 1, a5 + 1, a10, a13, 1);
  v14 = sub_417150(a2, a3, a4, a5, a6, a13, 0);
  sub_404F80(v14, 5u, 0);
}



// ------------------------------------------------------------
// 0x417450 sub_417450 —— 字体写盘（5 字段 + 宽度表 + 各字形 vt+104）
//   ·0x66BC25（fwrite）依次写 this+28..32 五个 4B 字段与宽度表 byte_8A77D8(0xFFFF)；
//   再按 this+29 逐个字形对象 vt+104(FILE*) 写位图数据。
// ------------------------------------------------------------
int /*thiscall*/ sub_417450(uint32_t *this, FILE *Stream)
{
  unsigned int i; // ebx
  int fld_e19; // ecx

  sub_66BC25(this + 28, 4u, 1u, Stream);
  sub_66BC25(this + 29, 4u, 1u, Stream);
  sub_66BC25(this + 30, 4u, 1u, Stream);
  sub_66BC25(this + 31, 4u, 1u, Stream);
  sub_66BC25(this + 32, 4u, 1u, Stream);
  sub_66BC25(&byte_8A77D8, 0xFFFFu, 1u, Stream);
  for ( i = 0; i < *(this + 29); ++i )
  {
    fld_e19 = *(uint32_t *)(*(this + 19) + 4 * i);
    (*(void (/*thiscall*/ **)(int, FILE *))(*(uint32_t *)fld_e19 + 104))(fld_e19, Stream);
  }
  return 1;
}



// ------------------------------------------------------------
// 0x4174F0 sub_4174F0 —— 字体读盘（5 字段 + 分配字形矢量 + 重建）
//   读 this+28..32 五字段 → operator new 字形矢量 → 每项经 this+3 管理器 vt+8 分配 12B 对象；
//   逐字形 vt+20 复位 → vt+12(1024,1024) 建面 → vt+108(FILE*) 装载位图。
// ------------------------------------------------------------
int /*thiscall*/ sub_4174F0(unsigned int *this, FILE *Stream)
{
  unsigned int *pThis_1D; // ebx
  int v4; // edi
  int result; // eax
  unsigned int i; // edi
  int fld_e19; // ecx
  int fld_e192; // ecx
  int fld_e193; // ecx

  sub_66BD5A(this + 28, 4u, 1u, Stream);  // 【fread封装】
  pThis_1D = this + 29;
  sub_66BD5A(this + 29, 4u, 1u, Stream);  // 【fread封装】
  sub_66BD5A(this + 30, 4u, 1u, Stream);  // 【fread封装】
  sub_66BD5A(this + 31, 4u, 1u, Stream);  // 【fread封装】
  sub_66BD5A(this + 32, 4u, 1u, Stream);  // 【fread封装】
  *(this + 19) = (unsigned int)operator new(4 * *(this + 29));
  v4 = 0;
  if ( *(this + 29) != 0 )
  {
    while ( 1 )
    {
      result = (*(int (/*thiscall*/ **)(uint32_t, int, unsigned int))(**(uint32_t **)(*(this + 3) + 12) + 8))(
                 *(uint32_t *)(*(this + 3) + 12),
                 12,
                 *(this + 19) + 4 * v4);
      if ( result < 0 )
        break;
      if ( ++v4 >= *pThis_1D )
        goto LABEL_4;
    }
  }
  else
  {
LABEL_4:
    for ( i = 0; i < *pThis_1D; ++i )
    {
      fld_e19 = *(uint32_t *)(*(this + 19) + 4 * i);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)fld_e19 + 20))(fld_e19);
      fld_e192 = *(uint32_t *)(*(this + 19) + 4 * i);
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)fld_e192 + 12))(fld_e192, 1024, 1024);
      fld_e193 = *(uint32_t *)(*(this + 19) + 4 * i);
      (*(void (/*thiscall*/ **)(int, FILE *))(*(uint32_t *)fld_e193 + 108))(fld_e193, Stream);
    }
    return 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4175D0 sub_4175D0 —— 字符 ↔ 字形序号双向表构建（12 段 Unicode 区间）
//   对 12 段 dword_77F458[i] .. dword_77F428[i] 逐码位 WideCharToMultiByte 转本地编码（缺省字符 = 空格）；
//   产出 word_8D77D8[序号] = 本地码 与 word_8B77D8[本地码] = 序号 双向表 + word_8A7798/word_8A7758 段起点表；返回总字形数。
// ------------------------------------------------------------
int sub_4175D0()
{
  int v0; // eax
  int v1; // esi
  unsigned int i; // ebx
  unsigned int v3; // edi
  bool v4; // cf
  int16_t v5; // dx
  uint16_t v6; // ax
  WCHAR WideCharStr[2]; // [esp+Ch] [ebp-10h] BYREF
  BOOL UsedDefaultChar; // [esp+10h] [ebp-Ch] BYREF
  int v10; // [esp+14h] [ebp-8h]
  CHAR MultiByteStr[4]; // [esp+18h] [ebp-4h] BYREF

  memset(word_8D77D8, 0, sizeof(word_8D77D8));
  unk_8F77D4 = 0;
  memset(word_8B77D8, 0, sizeof(word_8B77D8));
  unk_8D77D4 = 0;
  v0 = 0;
  v1 = 0;
  v10 = 0;
  for ( i = 0; i < 12; ++i )
  {
    v3 = dword_77F458[i];
    v4 = v3 < dword_77F428[i];
    *(int16_t *)((char *)&word_8A7798 + v0) = v1;
    if ( v4 )
    {
      do
      {
        *(uint32_t *)WideCharStr = v3;
        *(uint16_t *)MultiByteStr = 0;
        UsedDefaultChar = true;
        WideCharToMultiByte(0, 0, WideCharStr, 1, MultiByteStr, 2, " ", &UsedDefaultChar);
        LOBYTE(v5) = 0;
        HIBYTE(v5) = MultiByteStr[1];
        v6 = v5 | (uint8_t)MultiByteStr[0];
        word_8D77D8[v1] = v6;
        word_8B77D8[v6] = v1;
        ++v3;
        ++v1;
      }
      while ( v3 < dword_77F428[i] );
      v0 = v10;
    }
    *(int16_t *)((char *)&word_8A7758 + v0) = v1;
    v0 += 2;
    v10 = v0;
  }
  return v1;
}



// ------------------------------------------------------------
// 0x4176A0 sub_4176A0 —— 文本像素宽估算（5 × 字符数）
//   与 ·0x417150 的 5 像素/ASCII 步进一致。
// ------------------------------------------------------------
unsigned int /*cdecl*/ sub_4176A0(const char *pArg1)
{
  return 5 * strlen(pArg1);
}



// ------------------------------------------------------------
// 0x4176C0 sub_4176C0 —— 字形数缓存（this+28 = ·0x4175D0 结果，返回 1）
//   字形数 = ·0x4175D0 双向表构建结果（写入 this+28）。
// ------------------------------------------------------------
int /*thiscall*/ sub_4176C0(uint32_t *this)
{
  *(this + 28) = sub_4175D0();
  return 1;
}



// ============================================================
// SECTION 0x4176E0 — ★ Arial Narrow GDI 位图字体构建（CreateFontA + CreateDIBSection + TextOutA 栅格化缓存）
// ============================================================
// ------------------------------------------------------------
// 0x4176E0 sub_4176E0
// ------------------------------------------------------------
// 【解读】
//   ★ Arial Narrow 位图字体构建器（253 行）: strcmp 选族 → CreateFontA → GetDC/CreateCompatibleDC
//    → CreateDIBSection 栅格缓存 → SetTextColor/SetBkMode + TextOutA 逐字符绘制 →
//    GetTextExtentPoint32A 宽度表。"Arial Narrow" 为默认 UI 字体。
// ------------------------------------------------------------
int /*thiscall*/ sub_4176E0(  // 【Arial Narrow GDI 位图字体构建（CreateFontA + Crea…】
        LONG *this,
        int a2,
        int *a3,
        int a4,
        int a5,
        LPCSTR pszFaceName,
        int a7,
        unsigned int a8,
        unsigned int a9)
{
  HFONT FontA; // eax
  DWORD v11; // ecx
  DWORD v12; // edx
  HFONT v13; // eax
  int v14; // edx
  int v15; // eax
  HDC DC; // edx
  LONG v17; // ecx
  LONG v18; // eax
  HDC CompatibleDC; // edi
  unsigned int v20; // edx
  unsigned int v21; // ecx
  unsigned int k; // eax
  unsigned int v23; // eax
  unsigned int v24; // esi
  char v25; // cl
  unsigned int v26; // eax
  unsigned int m; // edi
  unsigned int v28; // esi
  unsigned int v29; // eax
  unsigned int n; // edi
  HGDIOBJ v31; // esi
  BITMAPINFO pbmi; // [esp+Ch] [ebp-ACh] BYREF
  char v34; // [esp+38h] [ebp-80h]
  char v35; // [esp+39h] [ebp-7Fh]
  char v36; // [esp+3Ah] [ebp-7Eh]
  char v37; // [esp+3Bh] [ebp-7Dh]
  int v38; // [esp+44h] [ebp-74h]
  int v39; // [esp+48h] [ebp-70h]
  int v40; // [esp+4Ch] [ebp-6Ch]
  int v41; // [esp+50h] [ebp-68h]
  int v42; // [esp+54h] [ebp-64h]
  int v43; // [esp+58h] [ebp-60h]
  int v44; // [esp+5Ch] [ebp-5Ch]
  int v45; // [esp+60h] [ebp-58h]
  HGDIOBJ v46; // [esp+64h] [ebp-54h]
  int v47; // [esp+68h] [ebp-50h]
  HGDIOBJ ho; // [esp+6Ch] [ebp-4Ch]
  HGDIOBJ v49; // [esp+70h] [ebp-48h]
  struct tagSIZE psizl; // [esp+74h] [ebp-44h] BYREF
  HGDIOBJ v51; // [esp+7Ch] [ebp-3Ch]
  HDC hDC; // [esp+80h] [ebp-38h]
  HGDIOBJ v53; // [esp+84h] [ebp-34h]
  HGDIOBJ v54; // [esp+88h] [ebp-30h]
  HGDIOBJ v55; // [esp+8Ch] [ebp-2Ch]
  int v56; // [esp+90h] [ebp-28h]
  int v57; // [esp+94h] [ebp-24h]
  int y; // [esp+98h] [ebp-20h]
  int x; // [esp+9Ch] [ebp-1Ch]
  HDC v60; // [esp+A0h] [ebp-18h]
  HGDIOBJ h; // [esp+A4h] [ebp-14h]
  void *ppvBits[4]; // [esp+A8h] [ebp-10h] BYREF
  unsigned int j; // [esp+C4h] [ebp+Ch]
  unsigned int i; // [esp+C8h] [ebp+10h]

  x = 0;
  y = 0;
  if ( strcmp("Arial Narrow", pszFaceName) == 0 )
  {
    x = 0;
    y = -2;
  }
  else if ( memcmp(&byte_6C29C8, pszFaceName, 7u) == 0 )
  {
    x = -1;
  }
  FontA = CreateFontA(
            -a4,
            0,
            a3[2],
            a3[3],
            a3[4],
            *((uint8_t *)a3 + 20),
            *((uint8_t *)a3 + 21),
            *((uint8_t *)a3 + 22),
            *((uint8_t *)a3 + 23),
            *((uint8_t *)a3 + 24),
            *((uint8_t *)a3 + 25),
            *((uint8_t *)a3 + 26),
            *((uint8_t *)a3 + 27),
            pszFaceName);
  v11 = *((uint8_t *)a3 + 26);
  v12 = *((uint8_t *)a3 + 25);
  h = FontA;
  v13 = CreateFontA(
          11,
          0,
          a3[2],
          a3[3],
          a3[4],
          *((uint8_t *)a3 + 20),
          *((uint8_t *)a3 + 21),
          *((uint8_t *)a3 + 22),
          *((uint8_t *)a3 + 23),
          *((uint8_t *)a3 + 24),
          v12,
          v11,
          *((uint8_t *)a3 + 27),
          &byte_6C29C0);
  v55 = v13;
  if ( h == nullptr || v13 == nullptr )
    return 0x80000000;
  v14 = a3[1];
  v15 = *a3;
  ppvBits[3] = nullptr;
  v34 = 0;
  v35 = 0;
  v36 = 0;
  v37 = 0;
  v38 = 0;
  v41 = 0;
  v42 = 1600;
  v43 = 0;
  v44 = 0;
  v47 = 0;
  v46 = h;
  v45 = 1;
  v39 = v14;
  v40 = v15;
  DC = GetDC(nullptr);
  memset(&pbmi, 0, sizeof(pbmi));
  v17 = *(this + 25);
  v18 = -*(this + 27);
  hDC = DC;
  ppvBits[0] = nullptr;
  pbmi.bmiHeader.biSize = 40;
  pbmi.bmiHeader.biBitCount = 16;
  pbmi.bmiHeader.biCompression = 0;
  pbmi.bmiHeader.biWidth = v17;
  pbmi.bmiHeader.biHeight = v18;
  pbmi.bmiHeader.biSizeImage = 0;
  pbmi.bmiHeader.biPlanes = 1;
  CompatibleDC = CreateCompatibleDC(DC);
  v60 = CompatibleDC;
  v53 = CreateDIBSection(CompatibleDC, &pbmi, 0, ppvBits, nullptr, 0);
  v51 = SelectObject(CompatibleDC, v53);
  SetTextColor(CompatibleDC, 0xFFFFFFu);
  SetBkMode(CompatibleDC, 1);
  v49 = SelectObject(CompatibleDC, h);
  ho = CreateSolidBrush(0);
  for ( i = 0; i < *(this + 32); ++i )
  {
    for ( j = 0; j < *(this + 31); ++j )
    {
      v20 = 0;
      if ( *(this + 27) != 0 )
      {
        v21 = *(this + 25);
        do
        {
          for ( k = 0; k < v21; ++k )
          {
            *((uint16_t *)ppvBits[0] + k + v20 * v21) = 0;
            v21 = *(this + 25);
          }
          ++v20;
        }
        while ( v20 < *(this + 27) );
      }
      LOWORD(pszFaceName) = word_8D77D8[j + i * *(this + 31) + a7 * *(this + 30)];
      TextOutA(CompatibleDC, x, y, (LPCSTR)&pszFaceName, 3);
      v57 = j * *(this + 25);
      v56 = i * *(this + 27);
      psizl.cx = 0;
      psizl.cy = 0;
      GetTextExtentPoint32A(CompatibleDC, (LPCSTR)&pszFaceName, strlen((const char *)&pszFaceName), &psizl);
      v23 = (uint16_t)word_8B77D8[(uint16_t)word_8D77D8[j + i * *(this + 31) + a7 * *(this + 30)]];
      if ( v23 >= a8 && v23 < a9 )
      {
        byte_8A77D8[v23] = psizl.cx;
        v24 = 0;
        v25 = 1;
        if ( *(this + 27) == 0 )
          goto LABEL_23;
        do
        {
          v26 = *(this + 25);
          for ( m = 0; m < v26; ++m )
          {
            if ( *((uint16_t *)ppvBits[0] + m + v24 * v26) != 0 )
            {
              (*(void (/*thiscall*/ **)(int, unsigned int, unsigned int, int))(*(uint32_t *)a2 + 32))(
                a2,
                m + v57,
                v24 + v56,
                -1);
              v25 = 0;
            }
            v26 = *(this + 25);
          }
          ++v24;
        }
        while ( v24 < *(this + 27) );
        CompatibleDC = v60;
        if ( v25 == 1 )
        {
LABEL_23:
          v54 = SelectObject(CompatibleDC, v55);
          TextOutA(CompatibleDC, -1, 1, (LPCSTR)&pszFaceName, 3);
          v28 = 0;
          if ( *(this + 27) != 0 )
          {
            do
            {
              v29 = *(this + 25);
              for ( n = 0; n < v29; ++n )
              {
                if ( *((uint16_t *)ppvBits[0] + n + v28 * v29) != 0 )
                  (*(void (/*thiscall*/ **)(int, unsigned int, unsigned int, int))(*(uint32_t *)a2 + 32))(
                    a2,
                    n + v57,
                    v28 + v56,
                    -1);
                v29 = *(this + 25);
              }
              ++v28;
            }
            while ( v28 < *(this + 27) );
            CompatibleDC = v60;
          }
          SelectObject(CompatibleDC, v54);
        }
      }
    }
  }
  SelectObject(CompatibleDC, v49);
  SelectObject(CompatibleDC, v51);
  DeleteObject(ho);
  DeleteObject(v53);
  DeleteDC(CompatibleDC);
  ReleaseDC(nullptr, hDC);
  v31 = h;
  DeleteObject(h);
  DeleteObject(v55);
  DeleteObject(v31);
  return 1;
}


// ------------------------------------------------------------
// 0x417B60 sub_417B60
// ------------------------------------------------------------
// 【解读】
//   Arial Narrow 字体族管理（199 行）: sub_402AE0 登记 + new 字体对象 + 复用 0x4176E0 构建器。
// ------------------------------------------------------------
int /*thiscall*/ sub_417B60(LONG *this, int pArg2, int nArg3, int nArg4)
{
  int fld_e26; // eax
  unsigned int fld_e25; // esi
  unsigned int fld_e27; // eax
  int v8; // ecx
  unsigned int fld_e28; // eax
  int v10; // esi
  int result; // eax
  int fld_e3; // ecx
  unsigned int i; // esi
  int fld_e19; // ecx
  int fld_e192; // ecx
  int pObj; // [esp+Ch] [ebp-4h] BYREF

  *(this + 25) = 2 * *(uint32_t *)(pArg2 + 4);
  *(this + 26) = *(uint32_t *)(pArg2 + 4);
  *(this + 27) = *(uint32_t *)pArg2;
  sub_402AE0((int)(this + 20), (const char *)(pArg2 + 28));
  fld_e26 = *(this + 26);
  qmemcpy(this + 4, (const void *)pArg2, 0x3Cu);
  if ( fld_e26 == 0 && nArg4 != 0 )
    *(this + 26) = nArg4;
  if ( nArg3 == 0 )
    nArg3 = -*(this + 27);
  fld_e25 = 0x400u / *(this + 25);
  fld_e27 = 0x400u / *(this + 27);
  *(this + 31) = fld_e25;
  v8 = fld_e25 * fld_e27;
  *(this + 32) = fld_e27;
  fld_e28 = *(this + 28) / (fld_e25 * fld_e27);
  *(this + 30) = v8;
  *(this + 29) = ++fld_e28;
  *(this + 19) = (LONG)operator new(4 * fld_e28);
  v10 = 0;
  if ( *(this + 29) != 0 )
  {
    while ( 1 )
    {
      result = (*(int (/*thiscall*/ **)(uint32_t, int, int))(**(uint32_t **)(*(this + 3) + 12) + 8))(
                 *(uint32_t *)(*(this + 3) + 12),
                 12,
                 *(this + 19) + 4 * v10);
      if ( result < 0 )
        break;
      if ( ++v10 >= (unsigned int)*(this + 29) )
        goto LABEL_9;
    }
  }
  else
  {
LABEL_9:
    fld_e3 = *(this + 3);
    pObj = 0;
    (*(void (/*thiscall*/ **)(uint32_t, int, int *))(**(uint32_t **)(fld_e3 + 12) + 8))(*(uint32_t *)(fld_e3 + 12), 12, &pObj);
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)pObj + 12))(pObj, 1024, 1024);
    for ( i = 0; i < *(this + 29); ++i )
    {
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)pObj + 28))(pObj, 0);
      *(uint32_t *)pArg2 = 12;
      sub_4176E0(  // 【Arial Narrow GDI 位图字体构建（CreateFontA + Crea…】
        this,
        pObj,
        (int *)pArg2,
        nArg3,
        nArg4,
        (LPCSTR)(pArg2 + 28),
        i,
        (uint16_t)word_8A779E,
        (uint16_t)word_8A775E);
      sub_4176E0(  // 【Arial Narrow GDI 位图字体构建（CreateFontA + Crea…】
        this,
        pObj,
        (int *)pArg2,
        nArg3,
        nArg4,
        (LPCSTR)(pArg2 + 28),
        i,
        (uint16_t)word_8A77A6,
        (uint16_t)word_8A7766);
      sub_4176E0(  // 【Arial Narrow GDI 位图字体构建（CreateFontA + Crea…】
        this,
        pObj,
        (int *)pArg2,
        nArg3,
        nArg4,
        (LPCSTR)(pArg2 + 28),
        i,
        (uint16_t)word_8A77AA,
        (uint16_t)word_8A776A);
      *(uint32_t *)pArg2 = 15;
      *(uint8_t *)(pArg2 + 23) = 0;
      sub_4176E0(  // 【Arial Narrow GDI 位图字体构建（CreateFontA + Crea…】
        this,
        pObj,
        (int *)pArg2,
        nArg3 - 3,
        nArg4,
        "Arial Narrow",
        i,
        (uint16_t)word_8A7798,
        (uint16_t)word_8A7758);
      sub_4176E0(  // 【Arial Narrow GDI 位图字体构建（CreateFontA + Crea…】
        this,
        pObj,
        (int *)pArg2,
        nArg3 - 3,
        nArg4,
        "Arial Narrow",
        i,
        (uint16_t)word_8A77A0,
        (uint16_t)word_8A7760);
      sub_4176E0(  // 【Arial Narrow GDI 位图字体构建（CreateFontA + Crea…】
        this,
        pObj,
        (int *)pArg2,
        nArg3 - 3,
        nArg4,
        "Arial Narrow",
        i,
        (uint16_t)word_8A77A2,
        (uint16_t)word_8A7762);
      sub_4176E0(  // 【Arial Narrow GDI 位图字体构建（CreateFontA + Crea…】
        this,
        pObj,
        (int *)pArg2,
        nArg3 - 3,
        nArg4,
        "Arial Narrow",
        i,
        (uint16_t)word_8A77A4,
        (uint16_t)word_8A7764);
      sub_4176E0(  // 【Arial Narrow GDI 位图字体构建（CreateFontA + Crea…】
        this,
        pObj,
        (int *)pArg2,
        nArg3 - 3,
        nArg4,
        "Arial Narrow",
        i,
        (uint16_t)word_8A77AE,
        (uint16_t)word_8A776E);
      *(uint32_t *)pArg2 = 11;
      *(uint8_t *)(pArg2 + 23) = -127;
      sub_4176E0(  // 【Arial Narrow GDI 位图字体构建（CreateFontA + Crea…】
        this,
        pObj,
        (int *)pArg2,
        nArg3 + 1,
        nArg4,
        &byte_6C29C8,
        i,
        (uint16_t)word_8A77A8,
        (uint16_t)word_8A7768);
      sub_4176E0(  // 【Arial Narrow GDI 位图字体构建（CreateFontA + Crea…】
        this,
        pObj,
        (int *)pArg2,
        nArg3 + 1,
        nArg4,
        &byte_6C29C8,
        i,
        (uint16_t)word_8A77AC,
        (uint16_t)word_8A776C);
      sub_4176E0(  // 【Arial Narrow GDI 位图字体构建（CreateFontA + Crea…】
        this,
        pObj,
        (int *)pArg2,
        nArg3 + 1,
        nArg4,
        &byte_6C29C8,
        i,
        (uint16_t)word_8A779A,
        (uint16_t)word_8A775A);
      sub_4176E0(  // 【Arial Narrow GDI 位图字体构建（CreateFontA + Crea…】
        this,
        pObj,
        (int *)pArg2,
        nArg3 + 1,
        nArg4,
        &byte_6C29C8,
        i,
        (uint16_t)word_8A779C,
        (uint16_t)word_8A775C);
      fld_e19 = *(uint32_t *)(*(this + 19) + 4 * i);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)fld_e19 + 20))(fld_e19);
      fld_e192 = *(uint32_t *)(*(this + 19) + 4 * i);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)fld_e192 + 16))(fld_e192, pObj);
    }
    (*(void (/*thiscall*/ **)(uint32_t, int *))(**(uint32_t **)(*(this + 3) + 12) + 12))(*(uint32_t *)(*(this + 3) + 12), &pObj);
    return 1;
  }
  return result;
}


// ------------------------------------------------------------
// 0x417EE0 sub_417EE0 —— 字体对象 D3D 路径读盘（表面重建）
//   读 this+28..32 与宽度表 byte_8A77D8(0xFFFF) → operator new 字形矢量（管理器 vt+8）→ 每项 vt+20 复位；
//   与 ·0x4174F0 的差异: 改调 ·0x411240(1024,1024,25) 建 D3D 表面与行表，再 vt+108 读入。
// ------------------------------------------------------------
int /*thiscall*/ sub_417EE0(uint32_t *this, FILE *Stream)
{
  FILE *v4; // edi
  int result; // eax
  unsigned int i; // edi
  int fld_e19; // ecx
  int fld_e192; // ecx
  FILE *Streama; // [esp+14h] [ebp+8h]

  sub_66BD5A(this + 28, 4u, 1u, Stream);  // 【fread封装】
  sub_66BD5A(this + 29, 4u, 1u, Stream);  // 【fread封装】
  sub_66BD5A(this + 30, 4u, 1u, Stream);  // 【fread封装】
  sub_66BD5A(this + 31, 4u, 1u, Stream);  // 【fread封装】
  sub_66BD5A(this + 32, 4u, 1u, Stream);  // 【fread封装】
  sub_66BD5A(byte_8A77D8, 0xFFFFu, 1u, Stream);  // 【fread封装】
  *(this + 19) = operator new(4 * *(this + 29));
  Streama = nullptr;
  if ( *(this + 29) != 0 )
  {
    while ( 1 )
    {
      v4 = Streama;
      result = (*(int (/*thiscall*/ **)(uint32_t, int, int))(**(uint32_t **)(*(this + 3) + 12) + 8))(
                 *(uint32_t *)(*(this + 3) + 12),
                 12,
                 *(this + 19) + 4 * (uint32_t)Streama);
      if ( result < 0 )
        break;
      Streama = (FILE *)((char *)Streama + 1);
      if ( (unsigned int)&v4->_ptr + 1 >= *(this + 29) )
        goto LABEL_4;
    }
  }
  else
  {
LABEL_4:
    for ( i = 0; i < *(this + 29); ++i )
    {
      fld_e19 = *(uint32_t *)(*(this + 19) + 4 * i);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)fld_e19 + 20))(fld_e19);
      sub_411240(*(int **)(*(this + 19) + 4 * i), (int)Stream, i, 1024, 1024, 25);
      fld_e192 = *(uint32_t *)(*(this + 19) + 4 * i);
      (*(void (/*thiscall*/ **)(int, FILE *))(*(uint32_t *)fld_e192 + 108))(fld_e192, Stream);
    }
    return 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x417FE0 sub_417FE0 —— 三套 GDI 字体创建（charset 0x81）
//   CreateFontA(-11, 0,0,0, 100, ..., charset 0x81, 字体名 byte_6C29C0 / byte_6C29C8) → this+24/28/32；
//   对应 ·0x4186C0 选字体的三槽位（含中文字体位）。
// ------------------------------------------------------------
int /*thiscall*/ sub_417FE0(uint32_t *this, int nArg2)
{
  *(this + 6) = CreateFontA(-11, 0, 0, 0, 100, 0, 0, 0, 0x81u, 0, 0, 0, 0, &byte_6C29C0);
  *(this + 7) = CreateFontA(-11, 0, 0, 0, 100, 0, 0, 0, 0x81u, 0, 0, 0, 0, &byte_6C29C8);
  *(this + 8) = CreateFontA(-11, 0, 0, 0, 100, 0, 0, 0, 0x81u, 0, 0, 0, 0, &byte_6C29C0);
  return 1;
}



// ------------------------------------------------------------
// 0x418070 sub_418070 —— 50 个字块对象释放 + 全局字形表复位
//   释放 this+131116 起 50 个对象（管理器 vt+12）→ 清 this+42/44 计数 → memset(this+46, 0xFF, 0x1FFFC) 全表置未缓存；
//   this+131114 = -1，返回 ·0x405060(2, 0, 1)。
// ------------------------------------------------------------
int /*thiscall*/ sub_418070(int this)
{
  uint32_t *pThis_2002C; // edi
  int i; // ebx

  pThis_2002C = (uint32_t *)(this + 131116);
  for ( i = 50; i != 0; --i )
  {
    if ( *pThis_2002C != 0 )
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t *))(**(uint32_t **)(*(uint32_t *)(this + 12) + 12) + 12))(
        *(uint32_t *)(*(uint32_t *)(this + 12) + 12),
        pThis_2002C);
    ++pThis_2002C;
  }
  *(uint16_t *)(this + 42) = 0;
  *(uint16_t *)(this + 44) = 0;
  memset((void *)(this + 131116), 0, 0xC8u);
  memset((void *)(this + 46), 0xFFu, 0x1FFFCu);
  *(uint16_t *)(this + 131114) = -1;
  return sub_405060(2u, 0, 1);
}



// ------------------------------------------------------------
// 0x4180D0 sub_4180D0 —— 8B 元素矢量区间删除搬移
//   把 [uArg3, uArg4) 从尾端起逐对 (8B) 搬到 uArg3 起，收尾改 this[2] 新尾指针；出参返回 uArg3。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4180D0(uint32_t *this, uint32_t *uArg2, uint32_t *uArg3, uint32_t *uArg4)
{
  uint32_t *uArg42; // eax
  uint32_t *fld_e2; // esi
  uint32_t *uArg32; // edx

  uArg42 = uArg4;
  if ( uArg3 != uArg4 )
  {
    fld_e2 = (uint32_t *)*(this + 2);
    uArg32 = uArg3;
    if ( uArg4 != fld_e2 )
    {
      do
      {
        *uArg32 = *uArg42;
        uArg32[1] = uArg42[1];
        uArg42 += 2;
        uArg32 += 2;
      }
      while ( uArg42 != fld_e2 );
    }
    *(this + 2) = uArg32;
  }
  *uArg2 = uArg3;
  return uArg2;
}



// ------------------------------------------------------------
// 0x418120 sub_418120
// ------------------------------------------------------------
// 【解读】
//   std::out_of_range("invalid vector<T> subscript") 抛出器（MSVC vector::operator[] 检查版）。
// ------------------------------------------------------------
void /*noreturn*/ sub_418120()
{
  uint32_t pExceptionObject[10]; // [esp+0h] [ebp-50h] BYREF
  size_t v1; // [esp+28h] [ebp-28h] BYREF
  char v2; // [esp+2Ch] [ebp-24h]
  int v3; // [esp+3Ch] [ebp-14h]
  int v4; // [esp+40h] [ebp-10h]
  int v5; // [esp+4Ch] [ebp-4h]

  v4 = 15;
  v3 = 0;
  v2 = 0;
  sub_4015C0(&v1, "invalid vector<T> subscript", 0x1Bu);  // 【std::string构造赋值】
  v5 = 0;
  sub_401740(pExceptionObject, &v1);
  pExceptionObject[0] = &std::out_of_range::`vftable';
  _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
}



// ------------------------------------------------------------
// 0x418190 sub_418190
// ------------------------------------------------------------
// 【解读】
//   std::length_error("vector<T> too long") 抛出器。
// ------------------------------------------------------------
void /*noreturn*/ sub_418190()
{
  uint32_t pExceptionObject[10]; // [esp+0h] [ebp-50h] BYREF
  size_t v1; // [esp+28h] [ebp-28h] BYREF
  char v2; // [esp+2Ch] [ebp-24h]
  int v3; // [esp+3Ch] [ebp-14h]
  int v4; // [esp+40h] [ebp-10h]
  int v5; // [esp+4Ch] [ebp-4h]

  v4 = 15;
  v3 = 0;
  v2 = 0;
  sub_4015C0(&v1, "vector<T> too long", 0x12u);  // 【std::string构造赋值】
  v5 = 0;
  sub_401740(pExceptionObject, &v1);
  pExceptionObject[0] = &std::length_error::`vftable';
  _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x418200 sub_418200 —— 文本渲染对象析构
//   vftable 重写 → DeleteObject(+24/+28/+32/+20)、DeleteDC(+16)、free(+131320 字形块矢量)；
//   vftable 降级 off_6C25B8 → ·0x416420 收尾 → 复位 nengine::IObject vftable。
// ------------------------------------------------------------
int /*thiscall*/ sub_418200(int this)
{
  void *fld_18; // eax
  int result; // eax

  fld_18 = *(void **)(this + 24);
  *(uint32_t *)this = &off_6C29FC;
  if ( fld_18 != nullptr )
    DeleteObject(fld_18);
  if ( *(uint32_t *)(this + 28) != 0 )
    DeleteObject(*(HGDIOBJ *)(this + 28));
  if ( *(uint32_t *)(this + 32) != 0 )
    DeleteObject(*(HGDIOBJ *)(this + 32));
  DeleteObject(*(HGDIOBJ *)(this + 20));
  DeleteDC(*(HDC *)(this + 16));
  if ( *(uint32_t *)(this + 131320) != 0 )
    j__free(*(void **)(this + 131320));
  *(uint32_t *)(this + 131320) = 0;
  *(uint32_t *)(this + 131324) = 0;
  *(uint32_t *)(this + 131328) = 0;
  *(uint32_t *)this = &off_6C25B8;
  result = sub_416420((uint8_t *)this);
  *(uint8_t *)(this + 4) = 0;
  *(uint32_t *)this = &nengine::IObject::`vftable';
  return result;
}



// ------------------------------------------------------------
// 0x4182C0 sub_4182C0 —— 8B 元素矢量插入（MSVC _Insert_n 实例）
//   上限 0x1FFFFFFF；三分支: 原地后移（·0x44BD30 / ·0x44BD00）、尾部填充（·0x5E51F0）、扩容重建（·0x63A7C0 构造 + ·0x41FEB0）。
// ------------------------------------------------------------
void /*thiscall*/ sub_4182C0(int this, int nArg2, unsigned int uArg3, int pArg4)
{
  void *v4; // edx
  int fld_4; // ecx
  unsigned int fld_C; // eax
  int fld_8; // edx
  int fld_82; // edx
  unsigned int v11; // eax
  int fld_87; // edx
  int fld_88; // eax
  char *pMem; // edi
  int fld_43; // ecx
  int fld_89; // eax
  unsigned int v17; // ebx
  int fld_83; // eax
  bool v20; // cf
  int v21; // ecx
  int fld_86; // ebx
  int v23; // ebx
  int fld_42; // [esp-18h] [ebp-40h]
  int fld_85; // [esp-Ch] [ebp-34h]
  unsigned int fld_84; // [esp-8h] [ebp-30h]
  int v27; // [esp+0h] [ebp-28h] BYREF
  void *v28[4]; // [esp+Ch] [ebp-1Ch] BYREF
  int v29; // [esp+24h] [ebp-4h]
  int v30; // [esp+30h] [ebp+8h]
  int v31; // [esp+34h] [ebp+Ch]
  int v32; // [esp+38h] [ebp+10h]
  int fld_832; // [esp+38h] [ebp+10h]

  v4 = *(void **)(pArg4 + 4);
  v28[0] = *(void **)pArg4;
  fld_4 = *(uint32_t *)(this + 4);
  v28[3] = &v27;
  v28[1] = v4;
  if ( fld_4 != 0 )
    fld_C = (*(uint32_t *)(this + 12) - fld_4) >> 3;
  else
    fld_C = 0;
  if ( uArg3 != 0 )
  {
    if ( fld_4 != 0 )
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 3;
    else
      fld_8 = 0;
    if ( 0x1FFFFFFF - fld_8 < uArg3 )
      sub_418190(this);
    if ( fld_4 != 0 )
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 3;
    else
      fld_82 = 0;
    if ( fld_C >= uArg3 + fld_82 )
    {
      fld_83 = *(uint32_t *)(this + 8);
      v20 = (fld_83 - nArg2) >> 3 < uArg3;
      v21 = 8 * uArg3;
      v30 = 8 * uArg3;
      fld_832 = fld_83;
      if ( v20 )
      {
        sub_44BD30(nArg2, fld_83, nArg2 + v21);
        fld_84 = uArg3 - ((*(uint32_t *)(this + 8) - nArg2) >> 3);
        fld_85 = *(uint32_t *)(this + 8);
        v29 = 2;
        sub_5E51F0(fld_85, fld_84, v28);
        fld_86 = v30 + *(uint32_t *)(this + 8);
        *(uint32_t *)(this + 8) = fld_86;
        sub_41FEB0(nArg2, fld_86 - v30, v28);
      }
      else
      {
        v23 = fld_83 - v21;
        *(uint32_t *)(this + 8) = sub_44BD30(fld_83 - v21, fld_83, fld_83);
        sub_44BD00(nArg2, v23, fld_832);
        sub_41FEB0(nArg2, nArg2 + v30, v28);
      }
    }
    else
    {
      if ( 0x1FFFFFFF - (fld_C >> 1) >= fld_C )
        v11 = (fld_C >> 1) + fld_C;
      else
        v11 = 0;
      if ( fld_4 != 0 )
        fld_87 = (*(uint32_t *)(this + 8) - fld_4) >> 3;
      else
        fld_87 = 0;
      if ( v11 < uArg3 + fld_87 )
      {
        if ( fld_4 != 0 )
          fld_88 = (*(uint32_t *)(this + 8) - fld_4) >> 3;
        else
          fld_88 = 0;
        v11 = uArg3 + fld_88;
      }
      v31 = 8 * v11;
      pMem = (char *)operator new(8 * v11);
      fld_42 = *(uint32_t *)(this + 4);
      v28[2] = pMem;
      v29 = 0;
      v32 = sub_44BD30(fld_42, nArg2, pMem);
      sub_63A7C0(v32, uArg3, v28);
      sub_44BD30(nArg2, *(uint32_t *)(this + 8), v32 + 8 * uArg3);
      fld_43 = *(uint32_t *)(this + 4);
      if ( fld_43 != 0 )
        fld_89 = (*(uint32_t *)(this + 8) - fld_43) >> 3;
      else
        fld_89 = 0;
      v17 = fld_89 + uArg3;
      if ( fld_43 != 0 )
        j__free(*(void **)(this + 4));
      *(uint32_t *)(this + 12) = &pMem[v31];
      *(uint32_t *)(this + 8) = &pMem[8 * v17];
      *(uint32_t *)(this + 4) = pMem;
    }
  }
}


// ------------------------------------------------------------
// 0x418510 sub_418510 —— 删除壳（析构 ·0x418200 + 条件释放）
//   pszArg2 位 1 时释放对象内存。
// ------------------------------------------------------------
void */*thiscall*/ sub_418510(void *Block, char pszArg2)
{
  sub_418200((int)Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x418540 sub_418540 —— 8B 元素矢量 resize
//   uArg2 小于当前 size → ·0x4180D0 删尾；大于 → ·0x4182C0 补 (uArg2 - size) 项。
// ------------------------------------------------------------
void /*thiscall*/ sub_418540(int *this, unsigned int uArg2, char pszArg3, int nArg4)
{
  int fld_e1; // edx
  unsigned int fld_e2; // eax
  int fld_e22; // eax

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 )
    fld_e2 = (*(this + 2) - fld_e1) >> 3;
  else
    fld_e2 = 0;
  if ( fld_e2 >= uArg2 )
  {
    if ( fld_e1 != 0 && uArg2 < (*(this + 2) - fld_e1) >> 3 )
      sub_4180D0(this, &uArg2, (uint32_t *)(fld_e1 + 8 * uArg2), (uint32_t *)*(this + 2));
  }
  else
  {
    if ( fld_e1 != 0 )
      fld_e22 = (*(this + 2) - fld_e1) >> 3;
    else
      fld_e22 = 0;
    sub_4182C0((int)this, *(this + 2), uArg2 - fld_e22, (int)&pszArg3);
  }
}



// ============================================================
// SECTION 0x4185B0 — GDI 文本渲染三件套（DIB/TextOut/宽度表，0x4185B0/0x4186C0/0x418AA0）
// ============================================================
// ------------------------------------------------------------
// 0x4185B0 sub_4185B0 —— 文本渲染器构造（32x32 DIB + 兼容 DC）
//   ·0x40B530 基类 → vftable off_6C29FC → 字宽 this+40 = 10、行高 this+41 = 12 → ·0x418070 复位字形表；
//   CreateDIBSection(32x32, 16bpp, 位指针 → this+36) + CreateCompatibleDC(hWnd) → this+16/20/24 = DC / 位图 / 字体槽。
// ------------------------------------------------------------
int /*thiscall*/ sub_4185B0(int this, HWND hWnd, int nArg3, int nArg4)
{
  HDC DC; // edi
  HDC CompatibleDC; // eax
  void *fld_14; // [esp-4h] [ebp-48h]
  BITMAPINFO pbmi; // [esp+Ch] [ebp-38h] BYREF
  int v10; // [esp+40h] [ebp-4h]

  pbmi.bmiColors[0] = (RGBQUAD)this;
  sub_40B530((uint8_t *)this, nArg3, nArg4);
  *(uint32_t *)this = &off_6C29FC;
  v10 = 0;
  *(uint32_t *)(this + 131320) = 0;
  *(uint32_t *)(this + 131324) = 0;
  *(uint32_t *)(this + 131328) = 0;
  *(uint8_t *)(this + 40) = 10;
  *(uint8_t *)(this + 41) = 12;
  memset((void *)(this + 131116), 0, 0xC8u);
  LOBYTE(v10) = 1;
  sub_418070(this);
  pbmi.bmiHeader.biSize = 40;
  pbmi.bmiHeader.biWidth = 32;
  pbmi.bmiHeader.biHeight = -32;
  pbmi.bmiHeader.biPlanes = 1;
  pbmi.bmiHeader.biBitCount = 16;
  memset(&pbmi.bmiHeader.biCompression, 0, 24);
  *(uint32_t *)(this + 20) = CreateDIBSection(nullptr, &pbmi, 0, (void **)(this + 36), nullptr, 0);
  DC = GetDC(hWnd);
  CompatibleDC = CreateCompatibleDC(DC);
  fld_14 = *(void **)(this + 20);
  *(uint32_t *)(this + 16) = CompatibleDC;
  SelectObject(CompatibleDC, fld_14);
  ReleaseDC(hWnd, DC);
  *(uint32_t *)(this + 24) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x4186C0 sub_4186C0 —— 单字形栅格化与缓存（50 块轮转）
//   this+2*ch+46 查缓存（0xFFFF = 未缓存）→ 满 162 项轮转下一块（this+131116 起 50 块，9 列/块，每字形 6B 记录）；
//   清 32x32 DIB(0x800 字节) + 选字体（0xCAA1..0xF9FE 用 this+28 中文字体，其余按 +24/+32）+ SetBkMode/SetTextColor + TextOutA；
//   扫 12x12 网格逐点 vt+32 打点 → 8 次 vt+148 描边提交 → this+42 计数++ 并回写块号 → 返回记录 (块号, 行, 列)。
// ------------------------------------------------------------
uint16_t */*thiscall*/ sub_4186C0(int this, uint16_t pArg2)
{
  int fld_200F8; // ecx
  int pThis_200F4; // ebx
  int fld_200FC; // eax
  int fld_2C; // ecx
  uint16_t fld_2C2; // dx
  uint16_t fld_2A; // ax
  int *pThis_4; // esi
  int fld_200F82; // ecx
  uint16_t *v12; // ebx
  int pThis2; // edi
  int v14; // eax
  int v15; // edi
  int v16; // ecx
  bool v17; // zf
  int v18; // ecx
  int v19; // edx
  int v20; // eax
  int v21; // edi
  int v22; // edx
  int v23; // edx
  int v24; // edx
  int v25; // edx
  unsigned int fld_2A22; // edi
  int pThis3; // eax
  uint32_t v28[4]; // [esp+Ch] [ebp-30h] BYREF
  int c; // [esp+1Ch] [ebp-20h]
  unsigned int fld_2A2; // [esp+20h] [ebp-1Ch]
  int i; // [esp+28h] [ebp-14h]
  int v32; // [esp+2Ch] [ebp-10h]
  int pThis; // [esp+30h] [ebp-Ch]
  CHAR String; // [esp+34h] [ebp-8h] BYREF
  char pArg22; // [esp+35h] [ebp-7h]
  char v36; // [esp+36h] [ebp-6h]
  bool v37; // [esp+3Bh] [ebp-1h]

  pThis = this;
  v37 = pArg2 >= 0x80u;
  if ( pArg2 < 0x80u )
  {
    String = pArg2;
    pArg22 = 0;
  }
  else
  {
    String = HIBYTE(pArg2);
    pArg22 = pArg2;
    v36 = 0;
  }
  fld_200F8 = *(uint32_t *)(this + 131320);
  pThis_200F4 = this + 131316;
  c = this + 131316;
  if ( fld_200F8 != 0 )
    fld_200FC = (*(uint32_t *)(this + 131324) - fld_200F8) >> 3;
  else
    fld_200FC = 0;
  if ( *(uint16_t *)(this + 42) == fld_200FC )
  {
    if ( *(uint16_t *)(this + 44) == 50 )
      sub_418070(this);
    if ( (*(int (/*thiscall*/ **)(uint32_t, int, int))(**(uint32_t **)(*(uint32_t *)(this + 12) + 12) + 8))(
           *(uint32_t *)(*(uint32_t *)(this + 12) + 12),
           14,
           this + 4 * *(uint16_t *)(this + 44) + 131116) != 1 )
      return nullptr;
    fld_2C = *(uint32_t *)(this + 4 * *(uint16_t *)(this + 44) + 131116);
    if ( (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)fld_2C + 12))(fld_2C, 256, 256) != 1 )
      return nullptr;
    sub_418540(162 * (uint16_t)++*(uint16_t *)(this + 44), 0, 0);
  }
  fld_2C2 = *(uint16_t *)(this + 44);
  fld_2A = *(uint16_t *)(this + 42);
  pThis_4 = *(int **)(this + 4 * fld_2C2 + 131112);
  fld_2A2 = fld_2A;
  fld_200F82 = *(uint32_t *)(this + 131320);
  if ( fld_200F82 == 0 )
LABEL_17:
    sub_418120(pThis_200F4);
  if ( (*(uint32_t *)(this + 131324) - fld_200F82) >> 3 <= fld_2A2 )
  {
    pThis_200F4 = c;
    goto LABEL_17;
  }
  v12 = (uint16_t *)(fld_200F82 + 8 * fld_2A2);
  *v12 = fld_2C2 - 1;
  v12[1] = (uint16_t)(fld_2A - 162 * (fld_2C2 - 1)) / 9;
  v12[2] = 2 * ((uint16_t)(fld_2A - 162 * (fld_2C2 - 1)) % 9);
  memset(*(void **)(this + 36), 1u, 0x800u);
  if ( pArg2 < 0xCAA1u || pArg2 > 0xF9FEu )
  {
    if ( v37 )
      SelectObject(*(HDC *)(pThis + 16), *(HGDIOBJ *)(pThis + 24));
    else
      SelectObject(*(HDC *)(pThis + 16), *(HGDIOBJ *)(pThis + 32));
    pThis2 = pThis;
  }
  else
  {
    pThis2 = pThis;
    SelectObject(*(HDC *)(pThis + 16), *(HGDIOBJ *)(pThis + 28));
  }
  SetBkMode(*(HDC *)(pThis2 + 16), 1);
  SetTextColor(*(HDC *)(pThis2 + 16), 0xFFFFFFFF);
  c = v37 + 1;
  TextOutA(*(HDC *)(pThis2 + 16), -1, 1, &String, c);
  (*(void (/*thiscall*/ **)(int *))(*pThis_4 + 84))(pThis_4);
  fld_2A2 = 2;
  do
  {
    --fld_2A2;
    v14 = 0;
    v15 = 0;
    v16 = 0;
    v37 = false;
    v32 = 0;
    for ( i = 0; ; i = v32 << 6 )
    {
      while ( 1 )
      {
        v17 = *(uint16_t *)(v16 + *(uint32_t *)(pThis + 36)) == 257;
        v18 = (uint16_t)v12[1];
        v19 = *pThis_4;
        if ( v17 )
        {
          (*(void (/*thiscall*/ **)(int *, int, int, uint32_t))(v19 + 32))(
            pThis_4,
            14 * (uint16_t)v12[2] + v15 + 1,
            14 * v18 + v14 + 1,
            0);
        }
        else
        {
          (*(void (/*thiscall*/ **)(int *, int, int, int))(v19 + 32))(
            pThis_4,
            14 * (uint16_t)v12[2] + v15 + 1,
            14 * v18 + v14 + 1,
            -1);
          v37 = true;
        }
        v14 = v32;
        ++v15;
        i += 2;
        if ( v15 >= 12 )
          break;
        v16 = i;
      }
      if ( ++v32 >= 12 )
        break;
      v14 = v32;
      v15 = 0;
      v16 = v32 << 6;
    }
    if ( v37 )
      break;
    SelectObject(*(HDC *)(pThis + 16), *(HGDIOBJ *)(pThis + 32));
    TextOutA(*(HDC *)(pThis + 16), -1, 1, &String, c);
  }
  while ( fld_2A2 != 0 );
  v28[0] = 14 * (uint16_t)v12[2] + 1;
  v28[2] = v28[0] + 12;
  v20 = 14 * (uint16_t)v12[1] + 1;
  v28[3] = 14 * (uint16_t)v12[1] + 13;
  v28[1] = v20;
  v21 = 14 * (uint16_t)v12[2] + 15;
  fld_2A2 = v21 + 1;
  v22 = *pThis_4;
  i = v20;
  (*(void (/*thiscall*/ **)(int *, int, int, int *, uint32_t *, int))(v22 + 148))(pThis_4, v21 + 1, v20, pThis_4, v28, -1);
  v23 = *pThis_4;
  c = v21 - 1;
  (*(void (/*thiscall*/ **)(int *, int, int, int *, uint32_t *, int))(v23 + 148))(pThis_4, v21 - 1, i, pThis_4, v28, -1);
  v24 = *pThis_4;
  v32 = i + 1;
  (*(void (/*thiscall*/ **)(int *, int, int, int *, uint32_t *, int))(v24 + 148))(pThis_4, v21, i + 1, pThis_4, v28, -1);
  v25 = *pThis_4;
  (*(void (/*thiscall*/ **)(int *, int, int, int *, uint32_t *, int))(v25 + 148))(pThis_4, v21, --i, pThis_4, v28, -1);
  fld_2A22 = fld_2A2;
  (*(void (/*thiscall*/ **)(int *, unsigned int, int, int *, uint32_t *, int))(*pThis_4 + 148))(pThis_4, fld_2A2, v32, pThis_4, v28, -1);
  (*(void (/*thiscall*/ **)(int *, int, int, int *, uint32_t *, int))(*pThis_4 + 148))(pThis_4, c, i, pThis_4, v28, -1);
  (*(void (/*thiscall*/ **)(int *, unsigned int, int, int *, uint32_t *, int))(*pThis_4 + 148))(pThis_4, fld_2A22, i, pThis_4, v28, -1);
  (*(void (/*thiscall*/ **)(int *, int, int, int *, uint32_t *, int))(*pThis_4 + 148))(pThis_4, c, v32, pThis_4, v28, -1);
  (*(void (/*thiscall*/ **)(int *))(*pThis_4 + 88))(pThis_4);
  pThis3 = pThis;
  *(uint16_t *)(pThis + 2 * pArg2 + 46) = *(uint16_t *)(pThis + 42);
  ++*(uint16_t *)(pThis3 + 42);
  sub_405060(2, 1, 0);
  return v12;
}


// ------------------------------------------------------------
// 0x418AA0 sub_418AA0 —— 文本串绘制（字形缓存查建 + 逐字形提交）
//   逐字符 GBK 判定 → this+2*ch+46 查缓存，未命中调 ·0x4186C0 生成 → 块对象 vt+148(源矩形, 目标表面, 颜色) 绘制；
//   a6 描边模式取偏移 (x-1, y-2) 与 0xC8000000 半透明色；裁剪域 a2+48/+52 .. +56/+60 判据越界跳过；推进 this+40 = 10 / ASCII 折半。
// ------------------------------------------------------------
void /*thiscall*/ sub_418AA0(
        int this,
        uint32_t *a2,
        int a3,
        int a4,
        int a5,
        char a6,
        int a7,
        int a8,
        int a9,
        int a10,
        int a11,
        const char *a12)
{
  unsigned int v13; // eax
  int v14; // eax
  int v15; // esi
  int v16; // ecx
  char v17; // al
  bool v18; // bl
  uint16_t v19; // cx
  uint16_t v20; // ax
  uint16_t *v21; // eax
  int v22; // edx
  int v23; // ecx
  int v24; // ecx
  int v25; // ecx
  bool v26; // cf
  int v27; // [esp+8h] [ebp-1Ch] BYREF
  int v28; // [esp+Ch] [ebp-18h]
  int v29; // [esp+10h] [ebp-14h]
  int v30; // [esp+14h] [ebp-10h]
  int v31; // [esp+18h] [ebp-Ch]
  unsigned int v32; // [esp+1Ch] [ebp-8h]
  int v33; // [esp+20h] [ebp-4h]
  unsigned int v34; // [esp+38h] [ebp+14h]
  int v35; // [esp+3Ch] [ebp+18h]

  v32 = strlen(a12);
  v13 = a5 & 0xFF00FF00;
  v34 = a5 & 0xFF00FF00 | ((uint8_t)a5 << 16) | BYTE2(a5);
  sub_404F40(v13, 5u);
  if ( a4 + *(uint8_t *)(this + 41) >= a2[13] && a4 < a2[15] )
  {
    v14 = (a6 != 0) + 1;
    do
    {
      v15 = a3;
      v31 = v14 - 1;
      v16 = 0;
      v33 = a3;
      v35 = 0;
      if ( v32 != 0 )
      {
        while ( v15 < a2[14] )
        {
          v17 = a12[v16];
          v18 = (uint8_t)v17 >= 0x80u;
          if ( (uint8_t)v17 >= 0x80u )
          {
            LOBYTE(v19) = a12[v16 + 1];
            HIBYTE(v19) = v17;
          }
          else
          {
            v19 = v17;
          }
          if ( v15 + *(uint8_t *)(this + 40) >= a2[12] )
          {
            v20 = *(uint16_t *)(this + 2 * v19 + 46);
            if ( v20 == 0xFFFF )
            {
              v21 = sub_4186C0(this, v19);
            }
            else
            {
              v22 = *(uint32_t *)(this + 131320);
              if ( v22 == 0 || (*(uint32_t *)(this + 131324) - v22) >> 3 <= (unsigned int)v20 )
                sub_418120(this + 131316);
              v21 = (uint16_t *)(v22 + 8 * v20);
              v15 = v33;
            }
            if ( v21 == nullptr )
              break;
            v23 = (uint16_t)v21[2];
            if ( v31 != 0 )
            {
              v27 = 14 * (v23 + 1);
              v29 = v27 + 14;
              v28 = 14 * (uint16_t)v21[1];
              v30 = v28 + 14;
              v25 = *(uint32_t *)(this + 4 * (uint16_t)*v21 + 131116);
              if ( v25 != 0 )
                (*(void (/*thiscall*/ **)(int, int, int, uint32_t *, int *, int))(*(uint32_t *)v25 + 148))(
                  v25,
                  v15 - 1,
                  a4 - 2,
                  a2,
                  &v27,
                  -939524096);
            }
            else
            {
              v27 = 14 * v23 + 1;
              v29 = 14 * v23 + 13;
              v28 = 14 * (uint16_t)v21[1] + 1;
              v30 = v28 + 12;
              v24 = *(uint32_t *)(this + 4 * (uint16_t)*v21 + 131116);
              if ( v24 != 0 )
                (*(void (/*thiscall*/ **)(int, int, int, uint32_t *, int *, unsigned int))(*(uint32_t *)v24 + 148))(
                  v24,
                  v15,
                  a4 - 1,
                  a2,
                  &v27,
                  v34);
            }
          }
          if ( v18 )
          {
            ++v35;
            v15 += *(uint8_t *)(this + 40);
          }
          else
          {
            v15 += *(uint8_t *)(this + 40) >> 1;
          }
          v26 = v35 + 1 < v32;
          v33 = v15;
          ++v35;
          if ( !v26 )
            break;
          v16 = v35;
        }
      }
      v14 = v31;
    }
    while ( v31 != 0 );
    sub_404F80(0, 5u, 0);
  }
}


// ============================================================
// SECTION 0x418CB0 — ★★ CNImagePackEx：IMG 打开/魔数校验/延迟加载/别名/销毁 + 路径拼装
// ============================================================
// ------------------------------------------------------------
// 0x418CB0 sub_418CB0 —— IMG 目录项计数（12B/项）
//   返回 (this[14] - this[13]) / 12 —— CNImagePackEx 运行时目录矢量条目数。
// ------------------------------------------------------------
int /*thiscall*/ sub_418CB0(int *this)  // 【CNImagePackEx：IMG 打开/魔数校验/延迟加载/别名/销毁 + 路径拼装】
{
  int result; // eax

  result = *(this + 13);
  if ( result != 0 )
    return (*(this + 14) - result) / 12;
  return result;
}



// ------------------------------------------------------------
// 0x418CD0 sub_418CD0
// ------------------------------------------------------------
// 【解读】
//   ★ IMG 文件打开+魔数校验:
//     this+100 == 0（包态）→ sub_40E3E0 从 NPK 包流打开；否则 fopen(磁盘态)；
//     读 0x20(32) 字节头 → strcmp "Neople Image File" —— IMG 格式魔数；
//     this+21(84) 非 0 = 已加载守卫；成功返回 FILE*（由 0x418E20/0x419550 续用）。
// ------------------------------------------------------------
FILE */*thiscall*/ sub_418CD0(uint8_t *this, int pArg2)  // 【IMG文件头打开校验】
{
  bool fld_e100; // zf
  unsigned int v4; // ecx
  FILE *pFile; // eax
  char *v6; // eax
  FILE *pFile2; // ebx
  void *pThis_40; // esi
  int v10; // [esp+8h] [ebp-8h] BYREF
  uint8_t *pThis; // [esp+Ch] [ebp-4h]

  fld_e100 = *(this + 100) == 0;
  v4 = *(uint32_t *)(pArg2 + 24);
  pThis = this;
  if ( fld_e100 )
  {
    if ( v4 < 0x10 )
      pFile = fopen((const char *)(pArg2 + 4), "rb");
    else
      pFile = fopen(*(const char **)(pArg2 + 4), "rb");
  }
  else
  {
    if ( v4 < 0x10 )
      v6 = (char *)(pArg2 + 4);
    else
      v6 = *(char **)(pArg2 + 4);
    pFile = sub_40E3E0(&v10, &pArg2, v6, 0);  // 【NPK按名取数据流】
  }
  pFile2 = pFile;
  if ( pFile == nullptr )
    return nullptr;
  pThis_40 = this + 64;
  sub_66BD5A(pThis_40, 0x20u, 1u, pFile);  // 【fread封装】
  if ( strcmp((const char *)pThis_40, "Neople Image File") != 0 || *((uint32_t *)pThis + 21) != 0 )
  {
    if ( pThis[100] == 0 )
      fclose(pFile2);
    return nullptr;
  }
  return pFile2;
}



// ------------------------------------------------------------
// 0x418DD0 sub_418DD0
// ------------------------------------------------------------
// 【解读】
//   按索引取图像对象: 12B 目录项（this+13 起 12*i）[+4] = 图像对象指针；越界/未建 → sub_419F00（全局占位图像）。
// ------------------------------------------------------------
int /*thiscall*/ sub_418DD0(uint32_t *this, unsigned int uArg2)
{
  int fld_e13; // eax
  int fld_e132; // eax

  fld_e13 = *(this + 13);
  if ( fld_e13 != 0 && uArg2 < (*(this + 14) - fld_e13) / 12 && *(uint32_t *)((fld_e132 = *(this + 13) + 12 * uArg2) + 4) != 0 )
    return *(uint32_t *)(fld_e132 + 4);
  else
    return sub_419F00();
}



// ------------------------------------------------------------
// 0x418E20 sub_418E20
// ------------------------------------------------------------
// 【解读】
//   ★ IMG 延迟加载驱动: 遍历 12B 目录矢量（this+52 起，12 字节/项）→
//     对未加载项（图像+4 == 0）且 this+88 == 1（允许流式）: fseek(FILE*, entry.offset) →
//     图像对象 vt+108(FILE*) 从包流装载；dword_77F488 控制逐个/跳过策略（v14 = a2+1 或 0x418CB0 计数）。
// ------------------------------------------------------------
int /*thiscall*/ sub_418E20(int this, unsigned int pArg2)
{
  unsigned int pArg22; // edi
  int fld_34; // ecx
  int v5; // ebx
  int pThis_8; // eax
  FILE *pThis_14; // eax
  FILE *pFile3; // ebx
  int v10; // edi
  int *fld_342; // eax
  unsigned int pArg222; // [esp+Ch] [ebp-8h]
  FILE *pFile; // [esp+10h] [ebp-4h]
  FILE *pFile2; // [esp+1Ch] [ebp+8h]

  pArg22 = pArg2;
  fld_34 = *(uint32_t *)(this + 52);
  v5 = *(uint32_t *)(fld_34 + 12 * pArg2 + 4);
  pFile = (FILE *)v5;
  if ( fld_34 == 0 || pArg2 >= (*(uint32_t *)(this + 56) - fld_34) / 12 || v5 == 0 )
    return sub_419F00();
  pThis_8 = sub_41A510(this + 8);
  LOBYTE(pThis_8) = *(uint8_t *)(v5 + 4);
  if ( (uint8_t)pThis_8 != 1 )
  {
    sub_404F40(pThis_8, 0);
    pThis_14 = sub_418CD0((uint8_t *)this, this + 20);  // 【IMG文件头打开校验】
    pFile3 = pThis_14;
    if ( pThis_14 == nullptr )
      return sub_419F00();
    if ( dword_77F488 == 1 )
    {
      pFile2 = (FILE *)(pArg2 + 1);
    }
    else
    {
      pArg22 = 0;
      pThis_14 = (FILE *)sub_418CB0((int *)this);  // 【CNImagePackEx：IMG 打开/魔数校验/延迟加载/别名/销毁 + 路径拼装】
      pFile2 = pThis_14;
    }
    pArg222 = pArg22;
    if ( pArg22 < (unsigned int)pFile2 )
    {
      v10 = 12 * pArg22;
      while ( 1 )
      {
        fld_342 = (int *)(v10 + *(uint32_t *)(this + 52));
        if ( *(uint8_t *)(fld_342[1] + 4) == 0 && *(uint32_t *)(this + 88) == 1 )
        {
          fseek(pFile3, *fld_342, 0);
          if ( (*(int (/*thiscall*/ **)(uint32_t, FILE *))(**(uint32_t **)(v10 + *(uint32_t *)(this + 52) + 4) + 108))(
                 *(uint32_t *)(v10 + *(uint32_t *)(this + 52) + 4),
                 pFile3) < 0 )
            break;
        }
        pThis_14 = (FILE *)(pArg222 + 1);
        v10 += 12;
        if ( ++pArg222 >= (unsigned int)pFile2 )
          goto LABEL_19;
      }
      pThis_14 = (FILE *)sub_419F00();
      pFile = pThis_14;
    }
LABEL_19:
    sub_404F80((int)pThis_14, 0, 0);
    if ( *(uint8_t *)(this + 100) == 0 )
      fclose(pFile3);
  }
  return (int)pFile;
}



// ------------------------------------------------------------
// 0x418F60 sub_418F60 [串: "vector<T> too long"]
// ------------------------------------------------------------
void /*noreturn*/ sub_418F60()
{
  uint32_t pExceptionObject[10]; // [esp+0h] [ebp-50h] BYREF
  size_t v1; // [esp+28h] [ebp-28h] BYREF
  char v2; // [esp+2Ch] [ebp-24h]
  int v3; // [esp+3Ch] [ebp-14h]
  int v4; // [esp+40h] [ebp-10h]
  int v5; // [esp+4Ch] [ebp-4h]

  v4 = 15;
  v3 = 0;
  v2 = 0;
  sub_4015C0(&v1, "vector<T> too long", 0x12u);  // 【std::string构造赋值】
  v5 = 0;
  sub_401740(pExceptionObject, &v1);
  pExceptionObject[0] = &std::length_error::`vftable';
  _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x418FD0 sub_418FD0 —— CNImagePackEx 资源释放（目录归还 + 名字串清理）
//   遍历 12B 目录: 非别名项(+8 == 0)且对象非空 → 经 this+96 管理器 vt+12 归还；再 free 目录矢量；
//   名字串 erase（·0x401230）后经 ·0x41A260 从全局延迟加载 deque 注销 this+8 子对象。
// ------------------------------------------------------------
int /*thiscall*/ sub_418FD0(int this)
{
  int i; // esi
  unsigned int fld_2C; // esi
  char *pThis_18; // edx
  char *pThis_182; // ebx
  unsigned int fld_28; // eax
  char *pThis_183; // ebx
  unsigned int v8; // esi

  for ( i = *(uint32_t *)(this + 52); i != *(uint32_t *)(this + 56); i += 12 )
  {
    if ( *(uint8_t *)(i + 8) == 0 && *(uint32_t *)(i + 4) != 0 )
      (*(void (/*thiscall*/ **)(uint32_t, int))(**(uint32_t **)(this + 96) + 12))(*(uint32_t *)(this + 96), i + 4);
  }
  if ( *(uint32_t *)(this + 52) != 0 )
    j__free(*(void **)(this + 52));
  *(uint32_t *)(this + 52) = 0;
  *(uint32_t *)(this + 56) = 0;
  *(uint32_t *)(this + 60) = 0;
  fld_2C = *(uint32_t *)(this + 44);
  pThis_18 = (char *)(this + 24);
  if ( fld_2C < 0x10 )
    pThis_182 = (char *)(this + 24);
  else
    pThis_182 = *(char **)pThis_18;
  fld_28 = (unsigned int)&pThis_182[*(uint32_t *)(this + 40)];
  if ( fld_2C < 0x10 )
    pThis_183 = (char *)(this + 24);
  else
    pThis_183 = *(char **)pThis_18;
  if ( fld_2C >= 0x10 )
    pThis_18 = *(char **)pThis_18;
  if ( pThis_183 != nullptr )
    v8 = pThis_183 - pThis_18;
  else
    v8 = 0;
  if ( fld_28 != 0 )
    fld_28 -= (unsigned int)pThis_183;
  sub_401230((uint32_t *)(this + 20), v8, fld_28);
  return sub_41A260(this + 8);
}



// ------------------------------------------------------------
// 0x419070 sub_419070
// ------------------------------------------------------------
// 【解读】
//   图像目录矢量中段插入（MSVC vector 模板实例，12B 元素: 偏移/对象/标志；0x357913941 = 12B 元素容量上限）。
// ------------------------------------------------------------
int /*thiscall*/ sub_419070(int *this, int pArg2, unsigned int uArg3, int *Block)
{
  int v5; // ecx
  int v6; // edx
  int fld_e1; // ebx
  int result; // eax
  unsigned int fld_e3; // ecx
  int fld_e2; // eax
  int fld_e22; // eax
  unsigned int v13; // ecx
  int fld_e27; // eax
  int v15; // ebx
  int fld_e13; // eax
  unsigned int v17; // edi
  void *fld_e23; // ecx
  int fld_e26; // edi
  int fld_e12; // [esp-18h] [ebp-40h]
  int fld_e25; // [esp-Ch] [ebp-34h]
  unsigned int fld_e24; // [esp-8h] [ebp-30h]
  int v24; // [esp+0h] [ebp-28h] BYREF
  uint32_t v25[4]; // [esp+Ch] [ebp-1Ch] BYREF
  int v26; // [esp+24h] [ebp-4h]
  int v27; // [esp+30h] [ebp+8h]
  int v28; // [esp+34h] [ebp+Ch]
  char *Blocka; // [esp+38h] [ebp+10h]
  void *Blockb; // [esp+38h] [ebp+10h]

  v5 = *Block;
  v6 = Block[1];
  fld_e1 = *(this + 1);
  result = Block[2];
  v25[3] = &v24;
  v25[0] = v5;
  v25[1] = v6;
  v25[2] = result;
  if ( fld_e1 != 0 )
  {
    result = 715827883 * (*(this + 3) - fld_e1);
    fld_e3 = (*(this + 3) - fld_e1) / 12;
  }
  else
  {
    fld_e3 = 0;
  }
  if ( uArg3 != 0 )
  {
    if ( fld_e1 != 0 )
      fld_e2 = (*(this + 2) - fld_e1) / 12;
    else
      fld_e2 = 0;
    if ( 357913941 - fld_e2 < uArg3 )
      sub_418F60(this);
    if ( fld_e1 != 0 )
      fld_e22 = (*(this + 2) - fld_e1) / 12;
    else
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )
    {
      fld_e23 = (void *)*(this + 2);
      Blockb = fld_e23;
      if ( ((int)fld_e23 - pArg2) / 12 >= uArg3 )
      {
        v27 = (int)fld_e23 - 12 * uArg3;
        *(this + 2) = sub_59EE30(v27, fld_e23, fld_e23);
        sub_504450(pArg2, v27, Blockb);
        return sub_5043B0(pArg2, pArg2 + 12 * uArg3, v25);
      }
      else
      {
        sub_59EE30(pArg2, fld_e23, pArg2 + 12 * uArg3);
        fld_e24 = uArg3 - (*(this + 2) - pArg2) / 12;
        fld_e25 = *(this + 2);
        v26 = 2;
        sub_5E51C0(fld_e25, fld_e24, v25);
        fld_e26 = 12 * uArg3 + *(this + 2);
        *(this + 2) = fld_e26;
        return sub_5043B0(pArg2, fld_e26 - 12 * uArg3, v25);
      }
    }
    else
    {
      if ( 357913941 - (fld_e3 >> 1) >= fld_e3 )
        v13 = (fld_e3 >> 1) + fld_e3;
      else
        v13 = 0;
      if ( fld_e1 != 0 )
        fld_e27 = (*(this + 2) - fld_e1) / 12;
      else
        fld_e27 = 0;
      if ( v13 < uArg3 + fld_e27 )
        v13 = uArg3 + sub_4DA030(this);
      v15 = 12 * v13;
      Blocka = (char *)operator new(12 * v13);
      fld_e12 = *(this + 1);
      v26 = 0;
      v28 = sub_59EE30(fld_e12, pArg2, Blocka);
      sub_623C10(v28, uArg3, v25);
      sub_59EE30(pArg2, *(this + 2), v28 + 12 * uArg3);
      fld_e13 = *(this + 1);
      if ( fld_e13 != 0 )
        fld_e13 = (*(this + 2) - fld_e13) / 12;
      v17 = fld_e13 + uArg3;
      if ( *(this + 1) != 0 )
        j__free((void *)*(this + 1));
      *(this + 3) = (int)&Blocka[v15];
      *(this + 2) = (int)&Blocka[12 * v17];
      *(this + 1) = (int)Blocka;
      return (int)Blocka;
    }
  }
  return result;
}


// ------------------------------------------------------------
// 0x419320 sub_419320
// ------------------------------------------------------------
// 【解读】
//   CNImagePackEx::Destroy: off_77F3FC 日志（函数名自证字符串）→ sub_418FD0 释放目录/图像 → 名字串复位 → IObject vftable 复位。
// ------------------------------------------------------------
void /*thiscall*/ sub_419320(char *this)
{
  const char *pThis_18; // eax

  *(uint32_t *)this = &off_6C2A64;
  *((uint32_t *)this + 2) = &off_6C2A60;
  if ( *((uint32_t *)this + 11) < 0x10u )
    pThis_18 = this + 24;
  else
    pThis_18 = *((const char **)this + 6);
  off_77F3FC("CNImagePackEx::Destroy - %s", pThis_18);
  sub_418FD0((int)this);
  if ( *((uint32_t *)this + 13) != 0 )
    j__free(*((void **)this + 13));
  *((uint32_t *)this + 13) = 0;
  *((uint32_t *)this + 14) = 0;
  *((uint32_t *)this + 15) = 0;
  if ( *((uint32_t *)this + 11) >= 0x10u )
    j__free(*((void **)this + 6));
  *((uint32_t *)this + 10) = 0;
  *((uint32_t *)this + 11) = 15;
  *(this + 24) = 0;
  *(this + 4) = 0;
  *(uint32_t *)this = &nengine::IObject::`vftable';
}



// ------------------------------------------------------------
// 0x4193D0 sub_4193D0 —— 12B 目录矢量 resize
//   收缩 → ·0x47DDD0 中段删除搬移并改尾指针；增长 → ·0x419070 补插 (uArg2 - size) 项。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4193D0(int *this, unsigned int uArg2, int Block, int nArg4, int nArg5)
{
  int fld_e1; // ecx
  unsigned int result; // eax
  int fld_e22; // eax
  int fld_e2; // edi

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 )
    result = (*(this + 2) - fld_e1) / 12;
  else
    result = 0;
  if ( result >= uArg2 )
  {
    if ( fld_e1 != 0 )
    {
      fld_e2 = *(this + 2);
      result = (fld_e2 - fld_e1) / 12;
      if ( uArg2 < result )
      {
        result = fld_e1 + 12 * uArg2;
        if ( result != fld_e2 )
        {
          result = sub_47DDD0(fld_e2, fld_e2, result);
          *(this + 2) = result;
        }
      }
    }
  }
  else
  {
    if ( fld_e1 != 0 )
      fld_e22 = (*(this + 2) - fld_e1) / 12;
    else
      fld_e22 = 0;
    return sub_419070(this, *(this + 2), uArg2 - fld_e22, &Block);
  }
  return result;
}



// ------------------------------------------------------------
// 0x419480 sub_419480
// ------------------------------------------------------------
// 【解读】
//   CNImagePackEx 构造: IObject 头 → off_6C2A64 vftable → 名字串(this+24, 容量15) →
//     目录矢量(this+52..60 三指针) → 标志组: +88 加载模式、+92/96 设备/管理器、
//     +84 独立文件标志(this+21)、+22(this+88?) 就绪位、this+100 磁盘态标志；+96(24) = a2 类型。
// ------------------------------------------------------------
char */*thiscall*/ sub_419480(char *this, int nArg2)
{
  uint32_t *pThis_8; // edi

  *(uint32_t *)this = &nengine::IObject::`vftable';
  *(this + 4) = 0;
  pThis_8 = this + 8;
  sub_419E90(this + 8);
  *(uint32_t *)this = &off_6C2A64;
  *pThis_8 = &off_6C2A60;
  *((uint32_t *)this + 11) = 15;
  *((uint32_t *)this + 10) = 0;
  *(this + 24) = 0;
  *((uint32_t *)this + 13) = 0;
  *((uint32_t *)this + 14) = 0;
  *((uint32_t *)this + 15) = 0;
  *((uint32_t *)this + 21) = 0;
  *((uint32_t *)this + 23) = 0;
  *((uint32_t *)this + 22) = 1;
  *((uint32_t *)this + 16) = 0;
  *((uint32_t *)this + 17) = 0;
  *((uint32_t *)this + 18) = 0;
  *((uint32_t *)this + 19) = 0;
  *((uint16_t *)this + 40) = 0;
  *(this + 4) = 1;
  *(this + 100) = 0;
  *((uint32_t *)this + 24) = nArg2;
  return this;
}



// ------------------------------------------------------------
// 0x419520 sub_419520 —— CNImagePackEx 删除壳（析构 ·0x419320 + 条件释放）
//   析构 ·0x419320 + pszArg2 位 1 时 free（堆对象删除语义）。
// ------------------------------------------------------------
char */*thiscall*/ sub_419520(char *Block, char pszArg2)
{
  sub_419320(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x419550 sub_419550
// ------------------------------------------------------------
// 【解读】
//   ★★ CNImagePackEx::Load —— IMG 装载主流程（132 行，函数名直证）:
//     ① sub_419D40 拼路径（"%s%c%s%c%s"，ImagePacks2 包根由 0x420190 决策）+ _access 探测；
//     ② sub_418CD0 打开 IMG（32B 魔数 "Neople Image File" 校验）；
//     ③ this+88 == 1 时逐目录项处理: 读 4B 记录头 ——
//        == 0x11(17) → 别名条目: 再读 4B 源索引，图像指针共享已建项，flag(+8)=1；
//        否则 → 设备 vt+8 CreateImage(ID) 建图 + sub_410750 SetImagePackEx 绑定 +
//               entry.offset = ftell（数据起点）→ 图像 vt+116(FILE*) 自描述装载
//               （返回消费字节数 → fseek(v15+offset) 定位下一记录）；
//     ④ 失败报 "CreateImage(%d) failed" / "SetImagePackEx(%d) failed" / "open_file failed %s"。
//     【推断】IMG 结构 = 32B 魔数 + 顺序记录流（4B 图像ID + 自定长 zlib 压缩块，见文件头）。
// ------------------------------------------------------------
char /*thiscall*/ sub_419550(int this, int *Block, unsigned int ArgList)
{
  char fld_60; // cl
  bool v5; // al
  int *Block2; // edi
  char *v7; // eax
  FILE *pFile; // ebx
  const char *v9; // edi
  int v10; // edi
  int fld_34; // eax
  unsigned int v12; // ecx
  int fld_602; // ecx
  int nPos; // eax
  int pFile2; // eax
  const char *pThis_18; // eax
  const char *pThis_182; // eax
  int v19; // [esp+14h] [ebp-11Ch]
  int Buffer; // [esp+1Ch] [ebp-114h] BYREF
  int pObj; // [esp+20h] [ebp-110h] BYREF
  char v22; // [esp+27h] [ebp-109h]
  char FileName[260]; // [esp+28h] [ebp-108h] BYREF
  int dword_796E502; // [esp+12Ch] [ebp-4h]

  dword_796E502 = dword_796E50;
  sub_404F40(0);
  fld_60 = *(uint8_t *)(*(uint32_t *)(this + 96) + 12);
  v22 = 1;
  v5 = fld_60 == 1 && (uint8_t)ArgList == 0;
  Block2 = Block;
  *(uint8_t *)(this + 100) = v5;
  if ( byte_8F77DC != 0 )
  {
    if ( (unsigned int)Block2[6] < 0x10 )
      v7 = (char *)(Block2 + 1);
    else
      v7 = (char *)Block2[1];
    sub_419D40(FileName, v7, 0x104u, 1);  // 【路径拼装（%s%c%s%c%s）/ 图像项容器 / 时间节流】
    if ( *(uint8_t *)(this + 100) == 1 )
    {
      if ( sub_40E3E0((int)&Block, (int)&ArgList, FileName, 0) != 0 )  // 【NPK按名取数据流】
        sub_4015C0(FileName, strlen(FileName));  // 【std::string构造赋值】
    }
    else if ( _access(FileName, 0) == 0 )
    {
      sub_4015C0(FileName, strlen(FileName));  // 【std::string构造赋值】
    }
  }
  sub_4014D0((std::_String_base *)(this + 20), Block2, 0, -1);
  pFile = (FILE *)sub_418CD0(Block2);  // 【IMG文件头打开校验】
  if ( pFile != nullptr )
  {
    if ( *(uint32_t *)(this + 88) == 1 )
    {
      LOBYTE(v19) = 0;
      sub_4193D0(*(uint32_t *)(this + 92), 0, 0, v19);
      v10 = 0;
      ArgList = 0;
      while ( 1 )
      {
        fld_34 = *(uint32_t *)(this + 52);
        if ( fld_34 == 0 || ArgList >= (*(uint32_t *)(this + 56) - fld_34) / 12 )
          break;
        Buffer = 0;
        sub_66BD5A(&Buffer, 4u, 1u, pFile);  // 【fread封装】
        if ( Buffer == 17 )
        {
          Block = nullptr;
          sub_66BD5A(&Block, 4u, 1u, pFile);  // 【fread封装】
          *(uint32_t *)(v10 + *(uint32_t *)(this + 52) + 4) = *(uint32_t *)(*(uint32_t *)(this + 52) + 12 * (uint32_t)Block + 4);
          *(uint8_t *)(v10 + *(uint32_t *)(this + 52) + 8) = 1;
          v12 = ArgList + 1;
          *(uint32_t *)(v10 + *(uint32_t *)(this + 52)) = *(uint32_t *)(*(uint32_t *)(this + 52) + 12 * (uint32_t)Block);
          ArgList = v12;
          v10 += 12;
        }
        else
        {
          fld_602 = *(uint32_t *)(this + 96);
          pObj = 0;
          if ( (*(int (/*thiscall*/ **)(int, int, int *))(*(uint32_t *)fld_602 + 8))(fld_602, Buffer, &pObj) < 0 )
          {
            if ( *(uint32_t *)(this + 44) < 0x10u )
              pThis_18 = (const char *)(this + 24);
            else
              pThis_18 = *(const char **)(this + 24);
            off_77F3FC("CNImagePackEx::Load - %s, CreateImage(%d) failed", pThis_18, ArgList);
            v22 = 0;
            goto LABEL_38;
          }
          if ( sub_410750(pObj, this, ArgList) < 0 )  // 【纹理↔ImagePackEx 绑定（SetImagePackEx）+ 块传输族】
          {
            off_77F3FC("CNImagePackEx::Load - SetImagePackEx(%d) failed", ArgList);
            v22 = 0;
            goto LABEL_38;
          }
          *(uint32_t *)(v10 + *(uint32_t *)(this + 52) + 4) = pObj;
          Block = (int *)(v10 + *(uint32_t *)(this + 52));
          nPos = ftell(pFile);
          *Block = nPos;
          pFile2 = (*(int (/*thiscall*/ **)(int, FILE *))(*(uint32_t *)pObj + 116))(pObj, pFile);
          fseek(pFile, pFile2 + *(uint32_t *)(v10 + *(uint32_t *)(this + 52)), 0);
          ++ArgList;
          v10 += 12;
        }
      }
    }
    if ( *(uint32_t *)(this + 44) < 0x10u )
      pThis_182 = (const char *)(this + 24);
    else
      pThis_182 = *(const char **)(this + 24);
    off_77F3FC("CNImagePackEx::Load - %s", pThis_182);
    if ( *(uint8_t *)(this + 100) == 0 )
      fclose(pFile);
  }
  else
  {
    if ( (unsigned int)Block2[6] < 0x10 )
      v9 = (const char *)(Block2 + 1);
    else
      v9 = (const char *)Block2[1];
    off_77F3FC("CNImagePackEx::Load - open_file failed %s", v9);
    v22 = 0;
  }
LABEL_38:
  sub_404F80(0, 0);
  return v22;
}


// ------------------------------------------------------------
// 0x4198A0 sub_4198A0
// ------------------------------------------------------------
// 【解读】
//   Load 外壳: sub_419D40 拼完整路径 + sub_4015C0 登记 → 转 0x419550。
// ------------------------------------------------------------
char */*thiscall*/ sub_4198A0(char *this, int nArg2, char *Src)
{
  uint32_t *pThis_8; // edi
  size_t v6; // [esp+10h] [ebp-2Ch] BYREF
  void *Block; // [esp+14h] [ebp-28h]
  int v8; // [esp+24h] [ebp-18h]
  unsigned int v9; // [esp+28h] [ebp-14h]
  int dword_796E502; // [esp+2Ch] [ebp-10h]
  int v11; // [esp+38h] [ebp-4h]

  dword_796E502 = dword_796E50;
  *(uint32_t *)this = &nengine::IObject::`vftable';
  *(this + 4) = 0;
  pThis_8 = this + 8;
  v11 = 0;
  sub_419E90(this + 8);
  *(uint32_t *)this = &off_6C2A64;
  *pThis_8 = &off_6C2A60;
  *((uint32_t *)this + 11) = 15;
  *((uint32_t *)this + 10) = 0;
  *(this + 24) = 0;
  *((uint32_t *)this + 13) = 0;
  *((uint32_t *)this + 14) = 0;
  *((uint32_t *)this + 15) = 0;
  *((uint32_t *)this + 21) = 0;
  *((uint32_t *)this + 22) = 1;
  *((uint32_t *)this + 23) = 0;
  *((uint32_t *)this + 16) = 0;
  *((uint32_t *)this + 17) = 0;
  *((uint32_t *)this + 18) = 0;
  *((uint32_t *)this + 19) = 0;
  v9 = 15;
  *((uint16_t *)this + 40) = 0;
  LOBYTE(v11) = 2;
  *((uint32_t *)this + 24) = nArg2;
  v8 = 0;
  LOBYTE(Block) = 0;
  sub_4015C0(&v6, Src, strlen(Src));  // 【std::string构造赋值】
  LOBYTE(v11) = 3;
  *(this + 100) = 0;
  *(this + 4) = 1;
  sub_419550((int)this, &v6, 0);
  if ( v9 >= 0x10 )
    j__free(Block);
  return this;
}



// ============================================================
// SECTION 0x4199A0 — mmio WAV 读取族（mmioOpenA/Descend/Read/Ascend → 声音缓冲）
// ============================================================
// ------------------------------------------------------------
// 0x4199A0 sub_4199A0
// ------------------------------------------------------------
// 【解读】
//   mmio WAV 装载: mmioOpenA → mmioDescend(RIFF/WAVE) → mmioRead 全量 → GlobalAlloc 拷出 → mmioAscend/Close。
// ------------------------------------------------------------
MMRESULT /*cdecl*/ sub_4199A0(LPSTR pszFileName, HMMIO *uArg2, HGLOBAL *uArg3, LPMMCKINFO pmmcki)  // 【mmio WAV 读取族（mmioOpenA/Descend/Read/Ascend…】
{
  HMMIO v4; // eax
  HMMIO v5; // edi
  MMRESULT v6; // esi
  uint64_t *v7; // eax
  LONG v8; // eax
  MMRESULT result; // eax
  struct _MMCKINFO v10; // [esp+Ch] [ebp-28h] BYREF
  int64_t pch; // [esp+20h] [ebp-14h] BYREF
  int v12; // [esp+28h] [ebp-Ch]
  int v13; // [esp+2Ch] [ebp-8h]
  char v14[4]; // [esp+30h] [ebp-4h] BYREF

  *uArg3 = nullptr;
  v4 = mmioOpenA(pszFileName, nullptr, 0x10000u);
  v5 = v4;
  if ( v4 != nullptr )
  {
    v6 = mmioDescend(v4, pmmcki, nullptr, 0);
    if ( v6 == 0 )
    {
      if ( pmmcki->ckid != 1179011410 || pmmcki->fccType != 1163280727 )
        goto LABEL_20;
      v10.ckid = 544501094;
      v6 = mmioDescend(v5, &v10, pmmcki, 0x10u);
      if ( v6 != 0 )
        goto LABEL_21;
      if ( v10.cksize < 0x10 )
        goto LABEL_20;
      if ( mmioRead(v5, (HPSTR)&pch, 16) != 16 )
      {
        v6 = 57602;
        goto LABEL_21;
      }
      if ( (uint16_t)pch == 1 )
      {
        *(uint32_t *)v14 = 0;
      }
      else if ( mmioRead(v5, v14, 2) != 2 )
      {
        v6 = 57602;
        goto LABEL_21;
      }
      v7 = GlobalAlloc(0, *(uint16_t *)v14 + 18);
      *uArg3 = v7;
      if ( v7 == nullptr )
      {
        v6 = 57344;
        goto LABEL_21;
      }
      *v7 = pch;
      *((uint32_t *)v7 + 2) = v12;
      *((uint32_t *)v7 + 3) = v13;
      *((uint16_t *)*uArg3 + 8) = *(uint16_t *)v14;
      if ( *(uint16_t *)v14 != 0 )
      {
        v8 = mmioRead(v5, (HPSTR)*uArg3 + 18, *(uint16_t *)v14);
        if ( v8 != *(uint16_t *)v14 )
        {
LABEL_20:
          v6 = 57601;
          goto LABEL_21;
        }
      }
      result = mmioAscend(v5, &v10, 0);
      v6 = result;
      if ( result == 0 )
      {
        *uArg2 = v5;
        return result;
      }
    }
  }
  else
  {
    v6 = 57600;
  }
LABEL_21:
  if ( *uArg3 != nullptr )
  {
    GlobalFree(*uArg3);
    *uArg3 = nullptr;
  }
  if ( v5 != nullptr )
    mmioClose(v5, 0);
  *uArg2 = nullptr;
  return v6;
}



// ------------------------------------------------------------
// 0x419B40 sub_419B40 —— WAV data 块定位
//   mmioSeek 到 pmmckiParent->dwDataOffset + 4 后以 ckid = 1635017060 (0x61746164 = RIFF 四字符码 data) 做 mmioDescend(0x10)。
// ------------------------------------------------------------
MMRESULT /*cdecl*/ sub_419B40(HMMIO *uArg1, LPMMCKINFO pmmcki, MMCKINFO *pmmckiParent)
{
  mmioSeek(*uArg1, pmmckiParent->dwDataOffset + 4, 0);
  pmmcki->ckid = 1635017060;
  return mmioDescend(*uArg1, pmmcki, pmmckiParent, 0x10u);
}



// ------------------------------------------------------------
// 0x419B80 sub_419B80 —— mmio 流式读取 n 字节
//   mmioGetInfo 后逐字节从 MMIOINFO 缓冲搬到 nArg3（耗尽则 mmioAdvance 续读），mmioSetInfo 提交；
//   pDwArg5 出参实读字节数；读空返回 57603，其余失败返回错误码并置 0。
// ------------------------------------------------------------
int /*cdecl*/ sub_419B80(HMMIO hmmio, unsigned int uArg2, int nArg3, int pArg4, unsigned int *pDwArg5)
{
  int result; // eax
  unsigned int uArg22; // edi
  unsigned int v7; // eax
  unsigned int v8; // esi
  HPSTR pchEndRead; // ecx
  char *pchNext; // eax
  char v11; // dl
  struct _MMIOINFO pmmioinfo; // [esp+Ch] [ebp-48h] BYREF

  result = mmioGetInfo(hmmio, &pmmioinfo, 0) != 0;
  if ( result != 0 )
    goto LABEL_11;
  uArg22 = uArg2;
  v7 = *(uint32_t *)(pArg4 + 4);
  if ( uArg2 > v7 )
    uArg22 = *(uint32_t *)(pArg4 + 4);
  v8 = 0;
  *(uint32_t *)(pArg4 + 4) = v7 - uArg22;
  if ( uArg22 == 0 )
  {
LABEL_10:
    result = mmioSetInfo(hmmio, &pmmioinfo, 0);
    if ( result == 0 )
    {
      *pDwArg5 = uArg22;
      return result;
    }
LABEL_11:
    *pDwArg5 = 0;
    return result;
  }
  pchEndRead = pmmioinfo.pchEndRead;
  pchNext = pmmioinfo.pchNext;
  while ( 1 )
  {
    if ( pchNext == pchEndRead )
    {
      result = mmioAdvance(hmmio, &pmmioinfo, 0);
      if ( result != 0 )
        goto LABEL_11;
      pchNext = pmmioinfo.pchNext;
      pchEndRead = pmmioinfo.pchEndRead;
      if ( pmmioinfo.pchNext == pmmioinfo.pchEndRead )
        break;
    }
    v11 = *pchNext++;
    *(uint8_t *)(v8 + nArg3) = v11;
    ++v8;
    pmmioinfo.pchNext = pchNext;
    if ( v8 >= uArg22 )
      goto LABEL_10;
  }
  *pDwArg5 = 0;
  return 57603;
}



// ------------------------------------------------------------
// 0x419C40 sub_419C40 —— mmio 资源释放（GlobalFree + mmioClose + 置空）
//   两个出参都置空，返回 0。
// ------------------------------------------------------------
int /*cdecl*/ sub_419C40(HMMIO *uArg1, HGLOBAL *uArg2)
{
  if ( *uArg2 != nullptr )
  {
    GlobalFree(*uArg2);
    *uArg2 = nullptr;
  }
  if ( *uArg1 != nullptr )
  {
    mmioClose(*uArg1, 0);
    *uArg1 = nullptr;
  }
  return 0;
}



// ------------------------------------------------------------
// 0x419C90 sub_419C90 —— 声音对象挂接与初启（this+48 = 新对象）
//   已初始化返回 0x80000002；先写 this+48 = nArg2 再调 vt+8 初启，成功置状态位(this+4) = 1。
// ------------------------------------------------------------
int /*thiscall*/ sub_419C90(uint8_t *this, int nArg2)
{
  int result; // eax
  int v4; // edx

  if ( *(this + 4) != 0 )
    return -2147483646;
  v4 = *(uint32_t *)this;
  *((uint32_t *)this + 12) = nArg2;
  result = (*(int (/*thiscall*/ **)(uint8_t *))(v4 + 8))(this);
  if ( result >= 0 )
  {
    *(this + 4) = 1;
    return 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x419CD0 sub_419CD0 —— 停止 / 重启转发（vt+12 + vt+4）
//   调 vt+12 后调 vt+4，置状态位(this+4) = 1 并返回 vt+4 结果。
// ------------------------------------------------------------
int /*thiscall*/ sub_419CD0(uint8_t *this)
{
  int result; // eax

  (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 12))(this);
  result = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 4))(this);
  *(this + 4) = 1;
  return result;
}



// ------------------------------------------------------------
// 0x419CF0 sub_419CF0 —— 路径包裹符设置（2 字符）
//   仅长度 2 的串可设（否则 0x80000000）；写入 byte_8F77DC / byte_8F77DD，供 ·0x419D40 的 nArg4 = 1 分支包裹路径。【推断】
// ------------------------------------------------------------
int /*cdecl*/ sub_419CF0(int pArg1)
{
  char v1; // cl

  if ( strlen((const char *)pArg1) == 2 )
  {
    byte_8F77DC = *(uint8_t *)pArg1;
    byte_8F77DD = *(uint8_t *)(pArg1 + 1);
    return 1;
  }
  else
  {
    byte_8F77DC = v1;
    return 0x80000000;
  }
}



// ============================================================
// SECTION 0x419D40 — 路径拼装（"%s%c%s%c%s"）/ 图像项容器 / 时间节流
// ============================================================
// ------------------------------------------------------------
// 0x419D40 sub_419D40
// ------------------------------------------------------------
// 【解读】
//   路径拼装器 "%s%c%s%c%s" / "%c%s%c%s"（根/分隔符/文件名/分隔符/扩展名，strncpy 截断保护）。
// ------------------------------------------------------------
int /*cdecl*/ sub_419D40(char *Buffer, char *Source, size_t Count, int nArg4)  // 【路径拼装（%s%c%s%c%s）/ 图像项容器 / 时间节流】
{
  unsigned int nLen; // eax
  char *v5; // esi
  char v6; // bl
  char v8; // cl
  char v9[260]; // [esp+10h] [ebp-108h] BYREF
  int dword_796E502; // [esp+114h] [ebp-4h]
  char v11; // [esp+12Fh] [ebp+17h]

  dword_796E502 = dword_796E50;
  nLen = strlen(Source);
  if ( nArg4 != 0 )
  {
    if ( nArg4 != 1 )
      return 0x80000000;
    v5 = &byte_8F77DC;
    v6 = 40;
    v11 = 41;
  }
  else
  {
    v5 = (char *)&unk_8F77D8;
    v6 = 91;
    v11 = 93;
  }
  if ( *v5 == 0 )
  {
    strncpy(Buffer, Source, Count);
    return 0x80000000;
  }
  if ( Count <= nLen + 5 )
    return 0x80000000;
  if ( nLen != 0 )
  {
    while ( 1 )
    {
      v8 = Source[nLen];
      if ( v8 == 47 || v8 == 92 )
        break;
      if ( --nLen == 0 )
        goto LABEL_16;
    }
    qmemcpy(v9, Source, nLen + 1);
    v9[nLen + 1] = 0;
    sprintf(Buffer, "%s%c%s%c%s", v9, v6, v5, v11, &Source[nLen + 1]);
    return 1;
  }
  else
  {
LABEL_16:
    sprintf(Buffer, "%c%s%c%s", v6, v5, v11, Source);
    return 1;
  }
}



// ------------------------------------------------------------
// 0x419E90 sub_419E90 —— 延迟加载计时子对象构造
//   vftable off_6C2B2C；+4 时间戳 = -1、+8/+10 计数 = 0；被 ·0x419480 / ·0x4198A0 内嵌到 this+8（其 vftable 随后被覆盖为 off_6C2A60）。
// ------------------------------------------------------------
uint16_t */*thiscall*/ sub_419E90(uint16_t *this)
{
  *(uint32_t *)this = &off_6C2B2C;
  *(this + 4) = 0;
  *(this + 5) = 0;
  *((uint32_t *)this + 1) = -1;
  return this;
}



// ------------------------------------------------------------
// 0x419EB0 sub_419EB0 —— 全局延迟加载对象参数写（+28/+32）
//   写 dword_8F77E0 +28/+32；+28 为超时阈值（默认 300000ms，见 ·0x41A110 / ·0x41A510）。
// ------------------------------------------------------------
int /*cdecl*/ sub_419EB0(uint32_t *pArg1)
{
  *(uint32_t *)(dword_8F77E0 + 28) = *pArg1;
  *(uint32_t *)(dword_8F77E0 + 32) = pArg1[1];
  return 1;
}



// ------------------------------------------------------------
// 0x419EE0 sub_419EE0 —— 全局延迟加载对象参数读（+28/+32）
//   与 ·0x419EB0 成对（读回超时阈值等参数）。
// ------------------------------------------------------------
int /*cdecl*/ sub_419EE0(uint32_t *pArg1)
{
  int dword_8F77E02; // ecx

  dword_8F77E02 = dword_8F77E0;
  *pArg1 = *(uint32_t *)(dword_8F77E0 + 28);
  pArg1[1] = *(uint32_t *)(dword_8F77E02 + 32);
  return 1;
}



// ------------------------------------------------------------
// 0x419F10 sub_419F10 —— deque 区间反向搬移（两级页表索引重算）
//   从区间尾端倒退逐元素搬移（--nArg7 并重算 (页索引, 页内偏移)）；出参写 (pArg6, nArg7)。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_419F10(uint32_t *pArg1, int nArg2, int nArg3, int pArg4, unsigned int uArg5, int pArg6, int nArg7)
{
  unsigned int v8; // eax
  unsigned int v9; // ecx
  unsigned int v10; // eax
  int v11; // edx
  unsigned int v12; // edi

  while ( nArg2 != pArg4 || nArg3 != uArg5 )
  {
    v8 = *(uint32_t *)(pArg4 + 8);
    v9 = --uArg5 >> 2;
    if ( v8 <= uArg5 >> 2 )
      v9 -= v8;
    v10 = (unsigned int)--nArg7 >> 2;
    v11 = nArg7 - 4 * v10;
    v12 = *(uint32_t *)(pArg6 + 8);
    if ( v12 <= v10 )
      v10 -= v12;
    *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(pArg6 + 4) + 4 * v10) + 4 * v11) = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(pArg4 + 4)
                                                                                              + 4 * v9)
                                                                                  + 4 * (uArg5 - 4 * (uArg5 >> 2)));
  }
  *pArg1 = pArg6;
  pArg1[1] = nArg7;
  return pArg1;
}



// ------------------------------------------------------------
// 0x419FA0 sub_419FA0 —— deque 区间正向搬移（两级页表索引重算）
//   与 ·0x419F10 互为反向（本函数从前往后并递增 uArg7）；出参写到 pArg1。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_419FA0(uint32_t *pArg1, int pArg2, unsigned int uArg3, int nArg4, int nArg5, int pArg6, unsigned int uArg7)
{
  unsigned int uArg72; // edx
  unsigned int v9; // eax
  unsigned int v10; // ecx
  unsigned int v11; // eax
  unsigned int v12; // edx
  unsigned int v13; // ebx

  uArg72 = uArg7;
  while ( pArg2 != nArg4 || uArg3 != nArg5 )
  {
    v9 = *(uint32_t *)(pArg2 + 8);
    v10 = uArg3 >> 2;
    if ( v9 <= uArg3 >> 2 )
      v10 -= v9;
    v11 = uArg72 >> 2;
    v12 = uArg72 - 4 * (uArg72 >> 2);
    v13 = *(uint32_t *)(pArg6 + 8);
    if ( v13 <= v11 )
      v11 -= v13;
    *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(pArg6 + 4) + 4 * v11) + 4 * v12) = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(pArg2 + 4)
                                                                                              + 4 * v10)
                                                                                  + 4 * (uArg3 - 4 * (uArg3 >> 2)));
    uArg72 = ++uArg7;
    ++uArg3;
  }
  *pArg1 = pArg6;
  pArg1[1] = uArg72;
  return pArg1;
}



// ------------------------------------------------------------
// 0x41A020 sub_41A020 —— deque 中段删除（erase 区间）
//   头段距 >= 尾段距时用 ·0x419FA0 向前搬，否则用 ·0x419F10 向后搬，再递减长度(this+4)；
//   出参 = (容器, this+3 起点 + 头段长度)。
// ------------------------------------------------------------
int **/*thiscall*/ sub_41A020(int *this, int **pDwArg2, int nArg3, unsigned int uArg4, int nArg5, unsigned int uArg6)
{
  int fld_e3; // ebx
  unsigned int v8; // edi
  int fld_e43; // ecx
  unsigned int fld_e32; // eax
  unsigned int fld_e2; // ebx
  int fld_e42; // eax
  int fld_e33; // ecx
  int fld_e4; // [esp+18h] [ebp-8h]
  int v16; // [esp+1Ch] [ebp-4h]

  fld_e3 = *(this + 3);
  v16 = uArg4 - fld_e3;
  v8 = uArg6 - uArg4;
  fld_e4 = fld_e3 + *(this + 4);
  if ( uArg4 - fld_e3 >= fld_e4 - uArg6 )
  {
    sub_419FA0(&nArg3, nArg5, uArg6, (int)this, fld_e4, nArg3, uArg4);
    if ( v8 != 0 )
    {
      fld_e42 = *(this + 4);
      do
      {
        if ( fld_e42 != 0 && --fld_e42 == 0 )
          *(this + 3) = 0;
        --v8;
      }
      while ( v8 != 0 );
      *(this + 4) = fld_e42;
    }
  }
  else
  {
    sub_419F10(&nArg3, (int)this, *(this + 3), nArg3, uArg4, nArg5, uArg6);
    if ( v8 != 0 )
    {
      fld_e43 = *(this + 4);
      do
      {
        if ( fld_e43 != 0 )
        {
          fld_e32 = *(this + 3) + 1;
          fld_e2 = 4 * *(this + 2);
          *(this + 3) = fld_e32;
          if ( fld_e2 <= fld_e32 )
            *(this + 3) = 0;
          if ( --fld_e43 == 0 )
            *(this + 3) = 0;
        }
        --v8;
      }
      while ( v8 != 0 );
      *(this + 4) = fld_e43;
    }
  }
  fld_e33 = *(this + 3);
  *pDwArg2 = this;
  pDwArg2[1] = (int *)(v16 + fld_e33);
  return pDwArg2;
}



// ------------------------------------------------------------
// 0x41A110 sub_41A110 —— 全局延迟加载登记表构造（单例注册）
//   vftable off_6C2B30 → 内嵌 deque(this+8: 块表 this+12 / 块数 this+16 / 起点 this+20 / 长度 this+24)；
//   dword_8F77E0 为空则登记单例；this+28 = 300000（毫秒阈值）、this+32 = 0。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_41A110(uint8_t *this)
{
  uint8_t *result; // eax

  result = this;
  *(this + 4) = 0;
  *(uint32_t *)this = &off_6C2B30;
  *((uint32_t *)this + 3) = 0;
  *((uint32_t *)this + 4) = 0;
  *((uint32_t *)this + 5) = 0;
  *((uint32_t *)this + 6) = 0;
  if ( dword_8F77E0 == 0 )
    dword_8F77E0 = (int)this;
  *(this + 4) = 1;
  *((uint32_t *)this + 8) = 0;
  *((uint32_t *)this + 7) = 300000;
  return result;
}



// ------------------------------------------------------------
// 0x41A150 sub_41A150 —— 登记表析构（·0x406E40 清 deque + vftable 复位）
//   ·0x406E40 清内嵌 deque 后把 vftable 降级为 nengine::IObject。
// ------------------------------------------------------------
void /*thiscall*/ sub_41A150(uint8_t *this)
{
  *(uint32_t *)this = &off_6C2B30;
  sub_406E40((int)(this + 8));
  *(uint32_t *)this = &nengine::IObject::`vftable';
  *(this + 4) = 0;
}



// ------------------------------------------------------------
// 0x41A170 sub_41A170 —— 登记表整体重置（遍历元素 + 清空 deque）
//   遍历 deque 全部元素: 元素 +10 置 0、+4 = -1、调元素自身虚函数 → 再 ·0x406E40 清 deque；返回 1。
// ------------------------------------------------------------
int sub_41A170()
{
  int dword_8F77E02; // edx
  int v1; // esi
  unsigned int i; // edi
  unsigned int v3; // edx
  unsigned int v4; // eax
  unsigned int v5; // ebx
  unsigned int v6; // eax
  unsigned int v7; // ebx
  int v8; // ecx
  unsigned int v9; // eax
  unsigned int v10; // ecx
  unsigned int v11; // edx
  void (/*thiscall*/ ***v12)(uint32_t); // ecx

  dword_8F77E02 = dword_8F77E0;
  v1 = dword_8F77E0 + 8;
  for ( i = *(uint32_t *)(dword_8F77E0 + 20); v1 != dword_8F77E02 + 8 || i != *(uint32_t *)(dword_8F77E02 + 20) + *(uint32_t *)(dword_8F77E02 + 24); ++i )
  {
    v3 = i >> 2;
    v4 = i >> 2;
    v5 = *(uint32_t *)(v1 + 8);
    if ( v5 <= i >> 2 )
      v4 -= v5;
    *(uint16_t *)(*(uint32_t *)(*(uint32_t *)(*(uint32_t *)(v1 + 4) + 4 * v4) + 4 * (i - 4 * (i >> 2))) + 10) = 0;
    v6 = i >> 2;
    v7 = *(uint32_t *)(v1 + 8);
    if ( v7 <= v3 )
      v6 = v3 - v7;
    v8 = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(v1 + 4) + 4 * v6) + 4 * (i - 4 * v3));
    v9 = i >> 2;
    *(uint32_t *)(v8 + 4) = -1;
    v10 = i - 4 * v3;
    v11 = *(uint32_t *)(v1 + 8);
    if ( v11 <= i >> 2 )
      v9 -= v11;
    v12 = *(void (/*thiscall*/ ****)(uint32_t))(*(uint32_t *)(*(uint32_t *)(v1 + 4) + 4 * v9) + 4 * v10);
    (**v12)(v12);
    dword_8F77E02 = dword_8F77E0;
  }
  sub_406E40(dword_8F77E02 + 8);
  return 1;
}



// ------------------------------------------------------------
// 0x41A230 sub_41A230 —— 删除壳（析构 ·0x41A150 + 条件释放）
//   析构 ·0x41A150 + 可选 free —— 与 ·0x418510 / ·0x419520 同族。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_41A230(uint8_t *Block, char pszArg2)
{
  sub_41A150(Block);
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x41A260 sub_41A260 —— 按对象指针在 deque 中查找并删除
//   遍历（两级页表索引）逐项比较首个 dword == nArg1，命中即经 ·0x41A020 删除该位；未命中返回尾迭代器。
//   —— 图像包销毁时注销延迟加载登记。【推断】
// ------------------------------------------------------------
int **/*cdecl*/ sub_41A260(int nArg1)
{
  unsigned int v1; // esi
  int **result; // eax
  unsigned int v3; // eax
  unsigned int v4; // edi
  int *v5; // [esp+8h] [ebp-8h] BYREF
  int **v6; // [esp+Ch] [ebp-4h]

  v1 = *(uint32_t *)(dword_8F77E0 + 20);
  result = (int **)(v1 + *(uint32_t *)(dword_8F77E0 + 24));
  v6 = result;
  while ( (int **)v1 != result )
  {
    v3 = v1 >> 2;
    v4 = *(uint32_t *)(dword_8F77E0 + 16);
    if ( v4 <= v1 >> 2 )
      v3 -= v4;
    if ( *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(dword_8F77E0 + 12) + 4 * v3) + 4 * (v1 - 4 * (v1 >> 2))) == nArg1 )
      return sub_41A020((int *)(dword_8F77E0 + 8), &v5, dword_8F77E0 + 8, v1, dword_8F77E0 + 8, v1 + 1);
    result = v6;
    ++v1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x41A2D0 sub_41A2D0 [串: "deque<T> too long"]
// ------------------------------------------------------------
void /*noreturn*/ sub_41A2D0()
{
  uint32_t pExceptionObject[10]; // [esp+0h] [ebp-50h] BYREF
  size_t v1; // [esp+28h] [ebp-28h] BYREF
  char v2; // [esp+2Ch] [ebp-24h]
  int v3; // [esp+3Ch] [ebp-14h]
  int v4; // [esp+40h] [ebp-10h]
  int v5; // [esp+4Ch] [ebp-4h]

  v4 = 15;
  v3 = 0;
  v2 = 0;
  sub_4015C0(&v1, "deque<T> too long", 0x11u);  // 【std::string构造赋值】
  v5 = 0;
  sub_401740(pExceptionObject, &v1);
  pExceptionObject[0] = &std::length_error::`vftable';
  _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x41A340 sub_41A340 —— deque 块表扩容（4B 元素页表）
//   上限 0xFFFFFFF 校验；operator new(4 * (新增 + 现块数)) 后按当前起点偏移两段 memcpy 重排块指针数组，尾部清零；
//   返回新块数 (uArg2 + this+8)。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_41A340(int this, unsigned int uArg2)
{
  unsigned int uArg22; // edx
  unsigned int fld_8; // eax
  unsigned int v5; // ecx
  unsigned int fld_C; // edi
  int v7; // esi
  char *fld_4; // eax
  const void *fld_42; // ecx
  char *v10; // eax
  char *pBuf3; // edx
  unsigned int pBuf; // ecx
  char *pBuf2; // edi
  size_t v14; // esi
  char *fld_43; // eax
  unsigned int result; // eax
  size_t fld_82; // [esp+8h] [ebp-Ch]
  char *pMem; // [esp+10h] [ebp-4h]

  uArg22 = uArg2;
  fld_8 = *(uint32_t *)(this + 8);
  if ( 0xFFFFFFF - fld_8 < uArg2 )
    sub_41A2D0(this);
  v5 = fld_8 >> 1;
  if ( fld_8 >> 1 < 8 )
    v5 = 8;
  if ( uArg2 < v5 && fld_8 <= 0xFFFFFFF - v5 )
  {
    uArg2 = v5;
    uArg22 = v5;
  }
  fld_C = *(uint32_t *)(this + 12) >> 2;
  v7 = 4 * fld_C;
  pMem = (char *)operator new(4 * (uArg22 + fld_8));
  fld_82 = 4 * ((int)(4 * *(uint32_t *)(this + 8) - 4 * fld_C) >> 2);
  fld_4 = (char *)memcpy_0(&pMem[4 * fld_C], (const void *)(4 * fld_C + *(uint32_t *)(this + 4)), fld_82);
  fld_42 = *(const void **)(this + 4);
  v10 = &fld_4[fld_82];
  if ( fld_C > uArg2 )
  {
    memcpy_0(v10, fld_42, 4 * ((int)(4 * uArg2) >> 2));
    v14 = 4 * ((int)(v7 - 4 * uArg2) >> 2);
    fld_43 = (char *)memcpy_0(pMem, (const void *)(4 * uArg2 + *(uint32_t *)(this + 4)), v14);
    pBuf = uArg2;
    pBuf2 = &fld_43[v14];
    if ( uArg2 == 0 )
      goto LABEL_15;
    goto LABEL_14;
  }
  pBuf3 = (char *)memcpy_0(v10, fld_42, 4 * (v7 >> 2)) + 4 * (v7 >> 2);
  if ( uArg2 != fld_C )
    memset(pBuf3, 0, 4 * (uArg2 - fld_C));
  if ( fld_C != 0 )
  {
    pBuf = fld_C;
    pBuf2 = pMem;
LABEL_14:
    memset(pBuf2, 0, 4 * pBuf);
  }
LABEL_15:
  if ( *(uint32_t *)(this + 4) != 0 )
    j__free(*(void **)(this + 4));
  result = uArg2 + *(uint32_t *)(this + 8);
  *(uint32_t *)(this + 4) = pMem;
  *(uint32_t *)(this + 8) = result;
  return result;
}



// ------------------------------------------------------------
// 0x41A490 sub_41A490 —— deque 尾插（惰性页分配）
//   起点 + 长度 达到 4 * 块数 边界时先经 ·0x41A340 扩容；目标页为空则 operator new(0x10)（4 元素页）；
//   写值后 ++this+16 长度，返回新长度。
// ------------------------------------------------------------
int /*thiscall*/ sub_41A490(int this, uint32_t *uArg2)
{
  int fld_10; // eax
  unsigned int fld_8; // eax
  unsigned int fld_102; // edi
  unsigned int v6; // ebx
  uint32_t *fld_4; // edi
  int result; // eax

  fld_10 = *(uint32_t *)(this + 16);
  if ( (((uint8_t)fld_10 + *(uint8_t *)(this + 12)) & 3) == 0 && *(uint32_t *)(this + 8) <= (unsigned int)(fld_10 + 4) >> 2 )
    sub_41A340(this, 1u);
  fld_8 = *(uint32_t *)(this + 8);
  fld_102 = *(uint32_t *)(this + 16) + *(uint32_t *)(this + 12);
  v6 = fld_102 >> 2;
  if ( fld_8 <= fld_102 >> 2 )
    v6 -= fld_8;
  if ( *(uint32_t *)(*(uint32_t *)(this + 4) + 4 * v6) == 0 )
    *(uint32_t *)(*(uint32_t *)(this + 4) + 4 * v6) = operator new(0x10u);
  fld_4 = (uint32_t *)(*(uint32_t *)(*(uint32_t *)(this + 4) + 4 * v6) + 4 * (fld_102 & 3));
  if ( fld_4 != nullptr )
    *fld_4 = *uArg2;
  result = *(uint32_t *)(this + 16) + 1;
  *(uint32_t *)(this + 16) = result;
  return result;
}



// ------------------------------------------------------------
// 0x41A510 sub_41A510
// ------------------------------------------------------------
// 【解读】
//   timeGetTime 缓存（+0x41A490 容器）—— 图像/资源延迟加载的时间节流。
// ------------------------------------------------------------
DWORD /*cdecl*/ sub_41A510(int pArg1)
{
  DWORD result; // eax
  int pArg12; // esi
  int v3; // ecx

  result = timeGetTime();
  pArg12 = pArg1;
  if ( *(uint16_t *)(pArg1 + 10) != 0 )
  {
    ++*(uint16_t *)(pArg1 + 8);
  }
  else
  {
    *(uint16_t *)(pArg1 + 8) = 0;
    v3 = *(uint32_t *)(pArg12 + 4);
    if ( v3 == -1 || v3 + *(uint32_t *)(dword_8F77E0 + 28) <= result )
      *(uint16_t *)(pArg12 + 10) = 1;
    else
      *(uint16_t *)(pArg12 + 10) = 2;
    *(uint32_t *)(pArg12 + 4) = timeGetTime();
    return sub_41A490(dword_8F77E0 + 8, &pArg1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x41A580 sub_41A580 —— crypt4byte 析构（vftable 复位 + 实例计数递减）
//   写 crypt4byte vftable 后 --dword_8F7A08。
// ------------------------------------------------------------
void /*thiscall*/ sub_41A580(uint32_t *this)
{
  *this = &crypt4byte::`vftable';
  --dword_8F7A08;
}



// ------------------------------------------------------------
// 0x41A590 sub_41A590 —— crypt4byte 加密初始化（随机密钥 + 双校验字）
//   rand() & 0x7F 取密钥表 dword_8F7808 项，与 pArg1 高低 16 位及 nArg3 混合生成 +5/+9 两个 4B 校验字（与 ·0x41A5E0 成对）。
// ------------------------------------------------------------
int /*fastcall*/ sub_41A590(unsigned int pArg1, int nArg2, int nArg3)
{
  uint8_t nRand; // al
  int v5; // edx
  int result; // eax
  int v7; // ecx

  nRand = rand() & 0x7F;
  *(uint8_t *)(pArg1 + 4) = nRand;
  *(uint8_t *)(pArg1 + 13) = nRand;
  v5 = dword_8F7808[nRand];
  result = v5 + HIWORD(pArg1);
  v7 = v5 + (uint16_t)pArg1;
  *(uint32_t *)(pArg1 + 5) = v7 ^ (result + nArg3);
  *(uint32_t *)(pArg1 + 9) = result ^ (nArg3 - v7);
  return result;
}



// ------------------------------------------------------------
// 0x41A5E0 sub_41A5E0 —— crypt4byte 解密校验（·0x41A590 逆运算）
//   由 +4/+13 查 dword_8F7808 密钥表，与 +5/+9 两校验字对 pArg1 高低 16 位重构明文；双式相等 → ++dword_8F7A10 返回明文，
//   否则 byte_77F48C=0 并返回 0（篡改/调试检测）。
// ------------------------------------------------------------
int /*fastcall*/ sub_41A5E0(unsigned int pArg1)
{
  int v1; // edx
  int v2; // esi
  int result; // eax

  v1 = dword_8F7808[*(uint8_t *)(pArg1 + 4)] + HIWORD(pArg1);
  v2 = dword_8F7808[*(uint8_t *)(pArg1 + 13)] + (uint16_t)pArg1;
  result = (v2 ^ *(uint32_t *)(pArg1 + 5)) - v1;
  if ( result == v2 + (v1 ^ *(uint32_t *)(pArg1 + 9)) )
  {
    ++dword_8F7A10;
  }
  else
  {
    byte_77F48C = 0;
    return 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x41A630 sub_41A630
// ------------------------------------------------------------
// 【解读】
//   随机源初始化: time 播种 srand + rand 工具（全引擎随机基元之一）。
// ------------------------------------------------------------
unsigned int /*fastcall*/ sub_41A630(unsigned int pArg1)
{
  bool v1; // zf
  __time32_t v3; // eax
  int *dword_8F78082; // edi
  int nRand; // ebx
  int nRand2; // ebx
  int nRand3; // ebx
  int nRand4; // edi
  uint8_t nRand5; // al
  int v10; // edx
  int v11; // eax
  int v12; // ecx
  int v13; // edx
  int v14; // edi
  int v15; // eax

  v1 = dword_8F7A08 == 0;
  *(uint32_t *)pArg1 = &crypt4byte::`vftable';
  if ( v1 )
  {
    v3 = time(nullptr);
    srand(v3);
    dword_8F78082 = dword_8F7808;
    do
    {
      nRand = (uint8_t)rand();
      nRand2 = ((rand() << 8) | nRand) << 8;
      nRand3 = ((uint8_t)rand() | nRand2) << 8;
      *dword_8F78082++ = (uint8_t)rand() | nRand3;
    }
    while ( (int)dword_8F78082 < (int)&dword_8F7A08 );
  }
  nRand4 = rand();
  nRand5 = rand() & 0x7F;
  *(uint8_t *)(pArg1 + 4) = nRand5;
  *(uint8_t *)(pArg1 + 13) = nRand5;
  v10 = dword_8F7808[nRand5];
  v11 = v10 + HIWORD(pArg1);
  v12 = v10 + (uint16_t)pArg1;
  v13 = v11 + nRand4;
  v14 = v11 ^ (nRand4 - v12);
  v15 = dword_8F7A08 + 1;
  *(uint32_t *)(pArg1 + 9) = v14;
  dword_8F7A08 = v15;
  *(uint32_t *)(pArg1 + 5) = v12 ^ v13;
  return pArg1;
}



// ------------------------------------------------------------
// 0x41A6F0 sub_41A6F0 —— crypt4byte 标量删除析构（vftable 复位 + 全局计数 --）
//   全局实例计数 dword_8F7A08 减 1；pszArg2 最低位（scalar deleting 标志）置位时 j__free 本体。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_41A6F0(uint32_t *Block, char pszArg2)
{
  int v3; // ecx

  v3 = dword_8F7A08 - 1;
  *Block = &crypt4byte::`vftable';
  dword_8F7A08 = v3;
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x41A720 sub_41A720 —— bitset 位测试（位容量 this[0] + 位数组 this[1]）
//   uArg2 >= *this 越界返回 false；否则取 (1 << (uArg2&7)) 与字节做与后右移，等于 1 为真。
// ------------------------------------------------------------
bool /*thiscall*/ sub_41A720(unsigned int *this, unsigned int uArg2)
{
  return uArg2 < *this
      && (uint8_t)(((1 << (uArg2 & 7)) & *(uint8_t *)((uArg2 >> 3) + *(this + 1))) >> (uArg2 & 7)) == 1;
}



// ------------------------------------------------------------
// 0x41A760 sub_41A760 —— bitset 位清零（·0x41A720 的写侧配对）
//   越界直接返回；否则按 uArg2 定位字节与位并 &= ~(1 << bit)。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_41A760(unsigned int *this, unsigned int uArg2)
{
  uint8_t *result; // eax

  if ( uArg2 < *this )
  {
    result = (uint8_t *)(*(this + 1) + (uArg2 >> 3));
    *result &= ~(1 << (uArg2 & 7));
  }
  return result;
}



// ------------------------------------------------------------
// 0x41A790 sub_41A790 —— 位集容器析构壳
//   0x6569D0 元素析构（0x65 库区）+ free(this+4) 位数组并置 0。【推断】
// ------------------------------------------------------------
void /*stdcall*/ sub_41A790(int pArg1)
{
  sub_6569D0(pArg1);
  j__free(*(void **)(pArg1 + 4));
  *(uint32_t *)(pArg1 + 4) = 0;
}



// ============================================================
// SECTION 0x41A7C0 — STL 容器模板实例族（vector/list/deque 诊断与操作）
// ============================================================
// ------------------------------------------------------------
// 0x41A7C0 sub_41A7C0 [串: "invalid vector<T> subscript"]
// ------------------------------------------------------------
void /*noreturn*/ sub_41A7C0()  // 【STL 容器模板实例族（vector/list/deque 诊断与操作）】
{
  uint32_t pExceptionObject[10]; // [esp+0h] [ebp-50h] BYREF
  size_t v1; // [esp+28h] [ebp-28h] BYREF
  char v2; // [esp+2Ch] [ebp-24h]
  int v3; // [esp+3Ch] [ebp-14h]
  int v4; // [esp+40h] [ebp-10h]
  int v5; // [esp+4Ch] [ebp-4h]

  v4 = 15;
  v3 = 0;
  v2 = 0;
  sub_4015C0(&v1, "invalid vector<T> subscript", 0x1Bu);  // 【std::string构造赋值】
  v5 = 0;
  sub_401740(pExceptionObject, &v1);
  pExceptionObject[0] = &std::out_of_range::`vftable';
  _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
}



// ------------------------------------------------------------
// 0x41A830 sub_41A830 [串: "list<T> too long"]
// ------------------------------------------------------------
int /*thiscall*/ sub_41A830(uint32_t *this, unsigned int uArg2)
{
  int fld_e2; // eax
  int result; // eax
  uint32_t pExceptionObject[10]; // [esp+4h] [ebp-50h] BYREF
  size_t v5; // [esp+2Ch] [ebp-28h] BYREF
  char v6; // [esp+30h] [ebp-24h]
  int v7; // [esp+40h] [ebp-14h]
  int v8; // [esp+44h] [ebp-10h]
  int v9; // [esp+50h] [ebp-4h]

  fld_e2 = *(this + 2);
  if ( 0x3FFFFFFF - fld_e2 < uArg2 )
  {
    v8 = 15;
    v7 = 0;
    v6 = 0;
    sub_4015C0(&v5, "list<T> too long", 0x10u);  // 【std::string构造赋值】
    v9 = 0;
    sub_401740(pExceptionObject, &v5);
    pExceptionObject[0] = &std::length_error::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
  }
  result = uArg2 + fld_e2;
  *(this + 2) = result;
  return result;
}



// ------------------------------------------------------------
// 0x41A8C0 sub_41A8C0 [串: "vector<T> too long"]
// ------------------------------------------------------------
void /*noreturn*/ sub_41A8C0()
{
  uint32_t pExceptionObject[10]; // [esp+0h] [ebp-50h] BYREF
  size_t v1; // [esp+28h] [ebp-28h] BYREF
  char v2; // [esp+2Ch] [ebp-24h]
  int v3; // [esp+3Ch] [ebp-14h]
  int v4; // [esp+40h] [ebp-10h]
  int v5; // [esp+4Ch] [ebp-4h]

  v4 = 15;
  v3 = 0;
  v2 = 0;
  sub_4015C0(&v1, "vector<T> too long", 0x12u);  // 【std::string构造赋值】
  v5 = 0;
  sub_401740(pExceptionObject, &v1);
  pExceptionObject[0] = &std::length_error::`vftable';
  _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x41A930 sub_41A930 —— 12B 单元区间销毁（每单元内含小链表）
//   步长 12B：哨兵(+4) 先断开自环、沿旧链逐节点 free，再释放哨兵本体，+4/+8 清零；
//   vector<T 12B> 的区间 _Destroy 实例（4B 元素版本见 ·0x41AD50）。
// ------------------------------------------------------------
int /*cdecl*/ sub_41A930(int nArg1, int nArg2)
{
  int result; // eax
  int i; // esi
  uint32_t **v4; // ecx
  uint32_t *v5; // eax
  bool v6; // zf
  uint32_t *v7; // edi

  result = nArg2;
  for ( i = nArg1; i != nArg2; i += 12 )
  {
    v4 = *(uint32_t ***)(i + 4);
    v5 = *v4;
    *v4 = v4;
    *(uint32_t *)(*(uint32_t *)(i + 4) + 4) = *(uint32_t *)(i + 4);
    v6 = v5 == *(uint32_t **)(i + 4);
    *(uint32_t *)(i + 8) = 0;
    if ( !v6 )
    {
      do
      {
        v7 = (uint32_t *)*v5;
        j__free(v5);
        v5 = v7;
      }
      while ( v7 != *(uint32_t **)(i + 4) );
    }
    j__free(*(void **)(i + 4));
    result = nArg2;
    *(uint32_t *)(i + 4) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x41A990 sub_41A990 —— vector<T 4B> 下标取值（越界抛）
//   空或 (止-起)>>2 <= uArg2 → 抛 0x41A7C0（invalid vector<T> subscript）；否则返回 &elem[uArg2]。
// ------------------------------------------------------------
int /*thiscall*/ sub_41A990(uint32_t *this, unsigned int uArg2)
{
  int fld_e1; // edx

  fld_e1 = *(this + 1);
  if ( fld_e1 == 0 || (*(this + 2) - fld_e1) >> 2 <= uArg2 )
    sub_41A7C0();  // 【STL 容器模板实例族（vector/list/deque 诊断与操作）】
  return fld_e1 + 4 * uArg2;
}



// ------------------------------------------------------------
// 0x41A9C0 sub_41A9C0 —— vector<T 12B> 下标取值（越界抛）
//   判据 (止-起)/12 <= uArg2 → 抛 0x41A7C0；返回首址 + 12*idx —— 槽位链表单元（9 级池）寻址。
// ------------------------------------------------------------
int /*thiscall*/ sub_41A9C0(uint32_t *this, unsigned int uArg2)
{
  int fld_e1; // esi

  fld_e1 = *(this + 1);
  if ( fld_e1 == 0 || (*(this + 2) - fld_e1) / 12 <= uArg2 )
    sub_41A7C0();  // 【STL 容器模板实例族（vector/list/deque 诊断与操作）】
  return fld_e1 + 12 * uArg2;
}



// ------------------------------------------------------------
// 0x41AA00 sub_41AA00 —— vector<T 4B> 批量插入（insert(pos, n, val) 实例）
//   容量足且尾距足 → 后移 0x55E7F0 后逐元素填充 0x49A9D0；尾距不足 → 搬尾后补填 0x523700；
//   容量不足 → new 2 倍缓冲 memcpy 三段搬迁；4B 指针元素（如位图对象数组）插入均走本例。
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_41AA00(int this, int Src, unsigned int uArg3, int *pDwArg4)
{
  int fld_4; // edx
  unsigned int result; // eax
  int fld_8; // ecx
  int fld_82; // ecx
  unsigned int v10; // eax
  int fld_85; // ecx
  int fld_86; // eax
  char *fld_42; // eax
  void *v15; // eax
  int fld_43; // eax
  int fld_87; // ecx
  unsigned int v18; // edi
  uint8_t *fld_83; // eax
  unsigned int v21; // edx
  int v22; // ecx
  char *fld_84; // edi
  int v24; // edi
  char *pMem; // [esp+8h] [ebp-4h]
  int Srcb; // [esp+14h] [ebp+8h]
  char *Srca; // [esp+14h] [ebp+8h]
  int v28; // [esp+18h] [ebp+Ch]
  int v29; // [esp+18h] [ebp+Ch]

  fld_4 = *(uint32_t *)(this + 4);
  pDwArg4 = (int *)*pDwArg4;
  if ( fld_4 != 0 )
    result = (*(uint32_t *)(this + 12) - fld_4) >> 2;
  else
    result = 0;
  if ( uArg3 != 0 )
  {
    if ( fld_4 != 0 )
      fld_8 = (*(uint32_t *)(this + 8) - fld_4) >> 2;
    else
      fld_8 = 0;
    if ( 0x3FFFFFFF - fld_8 < uArg3 )
      sub_41A8C0(this);
    if ( fld_4 != 0 )
      fld_82 = (*(uint32_t *)(this + 8) - fld_4) >> 2;
    else
      fld_82 = 0;
    if ( result >= uArg3 + fld_82 )
    {
      fld_83 = *(uint8_t **)(this + 8);
      v21 = (int)&fld_83[-Src] >> 2;
      v22 = 4 * uArg3;
      v29 = (int)fld_83;
      Srca = (char *)(4 * uArg3);
      if ( v21 >= uArg3 )
      {
        v24 = (int)&fld_83[-v22];
        *(uint32_t *)(this + 8) = sub_55E7F0(&fld_83[-v22], (int)fld_83, fld_83);
        sub_5DAF70((void *)Src, v24, v29);
        return sub_49A9D0(Src, &Srca[Src], &pDwArg4);
      }
      else
      {
        sub_55E7F0((void *)Src, (int)fld_83, (void *)(Src + v22));
        sub_523700(*(uint32_t *)(this + 8), uArg3 - ((*(uint32_t *)(this + 8) - Src) >> 2), &pDwArg4);
        fld_84 = &Srca[*(uint32_t *)(this + 8)];
        *(uint32_t *)(this + 8) = fld_84;
        return sub_49A9D0(Src, fld_84 - Srca, &pDwArg4);
      }
    }
    else
    {
      if ( 0x3FFFFFFF - (result >> 1) >= result )
        v10 = (result >> 1) + result;
      else
        v10 = 0;
      if ( fld_4 != 0 )
        fld_85 = (*(uint32_t *)(this + 8) - fld_4) >> 2;
      else
        fld_85 = 0;
      if ( v10 < uArg3 + fld_85 )
      {
        if ( fld_4 != 0 )
          fld_86 = (*(uint32_t *)(this + 8) - fld_4) >> 2;
        else
          fld_86 = 0;
        v10 = uArg3 + fld_86;
      }
      v28 = 4 * v10;
      pMem = (char *)operator new(4 * v10);
      Srcb = 4 * ((Src - *(uint32_t *)(this + 4)) >> 2);
      fld_42 = (char *)memcpy_0(pMem, *(const void **)(this + 4), Srcb);
      v15 = (void *)sub_523700(&fld_42[Srcb], uArg3, &pDwArg4);
      memcpy_0(v15, (const void *)Src, 4 * ((*(uint32_t *)(this + 8) - Src) >> 2));
      fld_43 = *(uint32_t *)(this + 4);
      if ( fld_43 != 0 )
        fld_87 = (*(uint32_t *)(this + 8) - fld_43) >> 2;
      else
        fld_87 = 0;
      v18 = fld_87 + uArg3;
      if ( fld_43 != 0 )
        j__free(*(void **)(this + 4));
      *(uint32_t *)(this + 12) = &pMem[v28];
      *(uint32_t *)(this + 8) = &pMem[4 * v18];
      *(uint32_t *)(this + 4) = pMem;
      return (unsigned int)pMem;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x41ABE0 sub_41ABE0 —— 12B 单元链表区间复制插入
//   从 [nArg3, uArg4) 逐节点 new（0x40C0F0）取 (节点+8) 载荷挂入 pArg2 哨兵，计数 +1（0x41A830）。
// ------------------------------------------------------------
void /*thiscall*/ sub_41ABE0(uint32_t *this, int pArg2, int nArg3, uint32_t *uArg4, int nArg5)
{
  uint32_t *v5; // esi
  uint32_t *v6; // edi
  uint32_t v7[4]; // [esp+0h] [ebp-24h] BYREF
  uint32_t *pThis; // [esp+10h] [ebp-14h]
  uint32_t *v9; // [esp+14h] [ebp-10h]
  int v10; // [esp+20h] [ebp-4h]

  v5 = (uint32_t *)nArg3;
  v9 = v7;
  pThis = this;
  v7[3] = nArg3;
  v10 = 0;
  while ( v5 != uArg4 )
  {
    v6 = sub_40C0F0(pArg2, *(uint32_t *)(pArg2 + 4), v5 + 2);
    sub_41A830(pThis, 1u);
    *(uint32_t *)(pArg2 + 4) = v6;
    *(uint32_t *)v6[1] = v6;
    v5 = (uint32_t *)*v5;
  }
}



// ------------------------------------------------------------
// 0x41AC90 sub_41AC90 —— 槽位数据寻址（HIWORD 选单元 + LOWORD 选项）
//   12B 单元表按 HIWORD 取指针，再返回 +16*(项+2) 处的数据区（驻留串本体）；越界返回 0。
// ------------------------------------------------------------
int /*thiscall*/ sub_41AC90(uint32_t *this, unsigned int uArg2)
{
  int fld_e1; // esi
  unsigned int v3; // edx

  fld_e1 = *(this + 1);
  v3 = HIWORD(uArg2);
  if ( fld_e1 != 0 && v3 < (*(this + 2) - fld_e1) >> 2 )
    return *(uint32_t *)(fld_e1 + 4 * v3) + 16 * ((uint16_t)uArg2 + 2);
  else
    return 0;
}



// ------------------------------------------------------------
// 0x41ACF0 sub_41ACF0 —— 驻留串句柄 → 字符串指针
//   句柄或全局池 dword_8F7A14 寻址失败 → 返回空串 szPassword；否则返回 0x41AC90(池, 槽码) 的串指针。
// ------------------------------------------------------------
const CHAR */*thiscall*/ sub_41ACF0(unsigned int **this)
{
  const CHAR *result; // eax

  if ( *this == nullptr )
    return szPassword;
  result = (const CHAR *)sub_41AC90(dword_8F7A14, **this);
  if ( result == nullptr )
    return szPassword;
  return result;
}



// ------------------------------------------------------------
// 0x41AD10 sub_41AD10 —— 12B 单元链表尾插（写入槽索引）
//   new 节点写入 uArg2 并挂哨兵、计数 +1（0x41A830）。【推断】
// ------------------------------------------------------------
int /*thiscall*/ sub_41AD10(int *this, uint32_t *uArg2)
{
  int fld_e1; // edi
  uint32_t *v4; // ebx
  int result; // eax

  fld_e1 = *(this + 1);
  v4 = sub_40C0F0(fld_e1, *(uint32_t *)(fld_e1 + 4), uArg2);
  result = sub_41A830(this, 1u);
  *(uint32_t *)(fld_e1 + 4) = v4;
  *(uint32_t *)v4[1] = v4;
  return result;
}



// ------------------------------------------------------------
// 0x41AD50 sub_41AD50 —— 0x41A930 区间销毁 thunk（stdcall 包装）
// ------------------------------------------------------------
int /*stdcall*/ sub_41AD50(int nArg1, int nArg2)
{
  return sub_41A930(nArg1, nArg2);
}



// ------------------------------------------------------------
// 0x41AD70 sub_41AD70 —— 槽位池分配 allocate（级 4..12 位图 + 上级传播）【推断】
//   pArg2 < 4 或 > 12 拒绝，级 4 且 nArg3==1 亦拒绝；本级链表非空取头槽，否则递归上一级取；
//   置位本级位图；nArg3!=1 返回 槽 << (pArg2-4)，否则把 2*槽 与 2*槽+1 记入上一级链表。
// ------------------------------------------------------------
int /*thiscall*/ sub_41AD70(uint32_t *this, uint8_t pArg2, int nArg3)
{
  unsigned int v4; // esi
  uint32_t *pThis_4; // edi
  unsigned int v6; // ebx
  int v7; // eax
  int pObj; // eax
  uint8_t *v9; // eax
  unsigned int v10; // esi
  int *v11; // eax
  int v12; // ebx
  int *v13; // eax

  if ( pArg2 < 4u || pArg2 > 0xCu )
    return -1;
  if ( (uint8_t)nArg3 == 1 && pArg2 == 4 )
    return -1;
  v4 = (uint8_t)(pArg2 - 4);
  pThis_4 = this + 4;
  if ( *(uint32_t *)(sub_41A9C0(this + 4, v4) + 8) != 0 )
    v6 = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(sub_41A9C0(pThis_4, (uint8_t)(pArg2 - 4)) + 4) + 4) + 8);
  else
    v6 = sub_41AD70(pArg2 + 1, 1);
  if ( v6 == -1 )
    return -1;
  v7 = sub_41A9C0(pThis_4, v4);
  sub_5D2440(v7);
  pObj = sub_41A990(this, v4);
  if ( v6 < **(uint32_t **)pObj )
  {
    v9 = (uint8_t *)(*(uint32_t *)(*(uint32_t *)pObj + 4) + (v6 >> 3));
    *v9 |= 1 << (v6 & 7);
  }
  if ( (uint8_t)nArg3 != 1 )
    return v6 << (pArg2 - 4);
  v10 = v4 - 1;
  nArg3 = 2 * v6;
  v11 = (int *)sub_41A9C0(pThis_4, v10);
  sub_41AD10(v11, &nArg3);
  v12 = 2 * v6 + 1;
  nArg3 = v12;
  v13 = (int *)sub_41A9C0(pThis_4, v10);
  sub_41AD10(v13, &nArg3);
  return v12;
}



// ------------------------------------------------------------
// 0x41AE90 sub_41AE90 —— 槽位池释放（位图回收 + 父级链表摘除）【推断】
//   uArg2 < 0x10000，自 nArg3 级向下递归判位；采该级位、兄弟槽(^1) 亦空闲或已到顶级 12 时，
//   从上一级链表摘除该子项（0x4371E0 双向链表节点摘除）—— 与 ·0x41AD70 互为逆操作。
// ------------------------------------------------------------
char /*thiscall*/ sub_41AE90(uint32_t *this, unsigned int uArg2, int nArg3)
{
  uint8_t v5; // cl
  unsigned int v6; // edi
  unsigned int v7; // esi
  int fld_e1; // eax
  unsigned int **v9; // eax
  unsigned int v10; // edi
  unsigned int **v11; // eax
  uint32_t *pThis_42; // ebx
  uint32_t *v13; // eax
  int *pThis_4; // eax
  void *v15; // [esp-8h] [ebp-14h]
  unsigned int v16; // [esp+8h] [ebp-4h] BYREF

  if ( uArg2 < 0x10000 )
  {
    if ( (uint8_t)nArg3 < 4u )
      return 1;
    if ( (uint8_t)nArg3 <= 0xCu )
    {
      v5 = nArg3 - 4;
      v6 = uArg2 >> (nArg3 - 4);
      v7 = (uint8_t)(nArg3 - 4);
      fld_e1 = *(this + 1);
      v16 = v6;
      if ( fld_e1 == 0 || (*(this + 2) - fld_e1) >> 2 <= (unsigned int)v5 )
        sub_41A7C0(this);  // 【STL 容器模板实例族（vector/list/deque 诊断与操作）】
      if ( !sub_41A720(*(unsigned int **)(fld_e1 + 4 * v5), v6) )
        return 1;
      if ( (uint8_t)sub_41AE90(uArg2, (uint8_t)(nArg3 - 1)) != 1 )
        return 0;
      v9 = (unsigned int **)sub_41A990(this, v7);
      sub_41A760(*v9, v6);
      v10 = v6 ^ 1;
      v11 = (unsigned int **)sub_41A990(this, v7);
      if ( sub_41A720(*v11, v10) || (uint8_t)nArg3 == 12 )
      {
        pThis_4 = (int *)sub_41A9C0(this + 4, v7);
        sub_41AD10(pThis_4, &v16);
        return 0;
      }
      pThis_42 = this + 4;
      nArg3 = *(uint32_t *)(sub_41A9C0(pThis_42, v7) + 4);
      v13 = **(uint32_t ***)(sub_41A9C0(pThis_42, v7) + 4);
      if ( v13 == (uint32_t *)nArg3 )
        return 1;
      while ( v13[2] != v10 )
      {
        v13 = (uint32_t *)*v13;
        if ( v13 == (uint32_t *)nArg3 )
          return 1;
      }
      v15 = v13;
      sub_41A9C0(pThis_42, v7);
      sub_4371E0((int)&nArg3, v15);
      return 1;
    }
  }
  return 0;
}



// ------------------------------------------------------------
// 0x41AFC0 sub_41AFC0 —— 池句柄释放入口（HIWORD 选级 → 0x41AE90）
//   表空或 HIWORD 越界返回 0；否则以 LOWORD 与顶级 12 调 0x41AE90 回收槽位。
// ------------------------------------------------------------
char /*thiscall*/ sub_41AFC0(uint32_t *this, unsigned int uArg2)
{
  int fld_e1; // esi
  unsigned int v3; // eax

  fld_e1 = *(this + 1);
  v3 = HIWORD(uArg2);
  if ( fld_e1 != 0 && v3 < (*(this + 2) - fld_e1) >> 2 )
    LOBYTE(v3) = sub_41AE90(*(uint32_t **)(fld_e1 + 4 * v3), (uint16_t)uArg2, 12);
  return v3;
}



// ------------------------------------------------------------
// 0x41B010 sub_41B010 —— 驻留句柄析构（引用计数减到 0 释放）
//   --refcount（句柄+8）为 0 → 0x41AFC0 池还槽 + free 句柄；*this 置空。
// ------------------------------------------------------------
void /*thiscall*/ sub_41B010(void **this)
{
  if ( *this != nullptr )
  {
    if ( --*((uint32_t *)*this + 2) == 0 )
    {
      sub_41AFC0(*(uint32_t *)*this);
      j__free(*this);
    }
    *this = nullptr;
  }
}



// ------------------------------------------------------------
// 0x41B050 sub_41B050 —— 12B 单元链表拷贝构造
//   0x425940 建哨兵（+4）、计数 0（+8）；随后 0x41ABE0 从 pArg2 源链逐节点复制。
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_41B050(uint32_t *this, int pArg2)
{
  int *v3; // eax
  int v5; // [esp-10h] [ebp-30h]
  int v6; // [esp-Ch] [ebp-2Ch]
  int *v7; // [esp-8h] [ebp-28h]
  int v8; // [esp+0h] [ebp-20h] BYREF
  void *pThis; // [esp+Ch] [ebp-14h]
  int *v10; // [esp+10h] [ebp-10h]
  int v11; // [esp+1Ch] [ebp-4h]

  v10 = &v8;
  pThis = this;
  v3 = (int *)sub_425940(this);
  *(this + 1) = v3;
  *(this + 2) = 0;
  v7 = *(int **)(pArg2 + 4);
  v6 = *v7;
  v5 = *v3;
  v11 = 0;
  sub_41ABE0(this, v5, v6, v7, pArg2);
  return this;
}



// ------------------------------------------------------------
// 0x41B0D0 sub_41B0D0 —— 驻留句柄赋值（旧引用释放 + 新引用 ++）
//   旧句柄 refcount-- 归零 → 0x41AFC0(dword_8F7A14, 槽码) + free；随后 *this = *pDwArg2 且 ++refcount。
// ------------------------------------------------------------
unsigned int */*thiscall*/ sub_41B0D0(unsigned int **this, unsigned int **pDwArg2)
{
  unsigned int *result; // eax

  if ( *this != nullptr )
  {
    if ( --(*this)[2] == 0 )
    {
      sub_41AFC0(dword_8F7A14, **this);
      j__free(*this);
    }
    *this = nullptr;
  }
  result = *pDwArg2;
  if ( *pDwArg2 != nullptr )
  {
    *this = result;
    ++result[2];
  }
  return result;
}



// ------------------------------------------------------------
// 0x41B120 sub_41B120 —— 12B 单元 vector 析构（区间销毁 + 释放缓冲）
//   调 0x41A930(起, 止) 后 free 缓冲，起/止/容量三字段清零。
// ------------------------------------------------------------
void /*thiscall*/ sub_41B120(int *this)
{
  int fld_e1; // eax

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 )
  {
    sub_41A930(fld_e1, *(this + 2));
    j__free((void *)*(this + 1));
  }
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
}



// ------------------------------------------------------------
// 0x41B170 sub_41B170 —— 12B 单元前向区间拷贝构造（uninitialized_copy 实例）
//   逐单元（步长 12B）：目标若已有内容先断链释放，再 0x41ABE0 从对应源单元拷入；返回目标末地址。
//   insert 后移与 erase 前移共用本例。
// ------------------------------------------------------------
int /*cdecl*/ sub_41B170(int nArg1, int nArg2, int nArg3)
{
  int nArg12; // edi
  int nArg32; // esi
  int *v5; // ebx
  uint32_t **v6; // ecx
  uint32_t *v7; // eax
  bool v8; // zf
  uint32_t *v9; // edi
  int v11; // [esp+14h] [ebp+10h]

  nArg12 = nArg1;
  if ( nArg1 == nArg2 )
    return nArg3;
  nArg32 = nArg3;
  do
  {
    if ( nArg32 != nArg12 )
    {
      v5 = *(int **)(nArg12 + 4);
      v6 = *(uint32_t ***)(nArg32 + 4);
      v11 = *v5;
      v7 = *v6;
      *v6 = v6;
      *(uint32_t *)(*(uint32_t *)(nArg32 + 4) + 4) = *(uint32_t *)(nArg32 + 4);
      v8 = v7 == *(uint32_t **)(nArg32 + 4);
      *(uint32_t *)(nArg32 + 8) = 0;
      if ( !v8 )
      {
        do
        {
          v9 = (uint32_t *)*v7;
          j__free(v7);
          v7 = v9;
        }
        while ( v9 != *(uint32_t **)(nArg32 + 4) );
        nArg12 = nArg1;
      }
      sub_41ABE0((uint32_t *)nArg32, **(uint32_t **)(nArg32 + 4), v11, v5, nArg1);
    }
    nArg12 += 12;
    nArg32 += 12;
    nArg1 = nArg12;
  }
  while ( nArg12 != nArg2 );
  return nArg32;
}



// ------------------------------------------------------------
// 0x41B200 sub_41B200 —— 12B 单元倒序区间拷贝构造（源在后，倒着搬防重叠）
//   自区间尾向前逐单元先断链释放再复制（0x41ABE0），供 insert 尾部搬移复用。
// ------------------------------------------------------------
int /*cdecl*/ sub_41B200(int nArg1, int nArg2, int nArg3)
{
  int nArg22; // edi
  int nArg32; // esi
  int *v5; // ebx
  uint32_t **v6; // ecx
  uint32_t *v7; // eax
  bool v8; // zf
  uint32_t *v9; // edi
  int nArg222; // [esp+10h] [ebp+Ch]
  int v12; // [esp+14h] [ebp+10h]

  nArg22 = nArg2;
  if ( nArg1 == nArg2 )
    return nArg3;
  nArg32 = nArg3;
  do
  {
    nArg22 -= 12;
    nArg32 -= 12;
    nArg222 = nArg22;
    if ( nArg32 != nArg22 )
    {
      v5 = *(int **)(nArg22 + 4);
      v6 = *(uint32_t ***)(nArg32 + 4);
      v12 = *v5;
      v7 = *v6;
      *v6 = v6;
      *(uint32_t *)(*(uint32_t *)(nArg32 + 4) + 4) = *(uint32_t *)(nArg32 + 4);
      v8 = v7 == *(uint32_t **)(nArg32 + 4);
      *(uint32_t *)(nArg32 + 8) = 0;
      if ( !v8 )
      {
        do
        {
          v9 = (uint32_t *)*v7;
          j__free(v7);
          v7 = v9;
        }
        while ( v9 != *(uint32_t **)(nArg32 + 4) );
        nArg22 = nArg222;
      }
      sub_41ABE0((uint32_t *)nArg32, **(uint32_t **)(nArg32 + 4), v12, v5, nArg222);
    }
  }
  while ( nArg22 != nArg1 );
  return nArg32;
}



// ------------------------------------------------------------
// 0x41B280 sub_41B280 —— 区间拷贝构造到独立缓冲（copy(first, last, dest)）
//   dest（uArg3）起逐元素 0x41B050 拷贝构造，返回写入末地址 —— 扩容搬迁用。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_41B280(int nArg1, int nArg2, uint32_t *uArg3)
{
  uint32_t *uArg32; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  uArg32 = uArg3;
  v6[4] = v6;
  v6[3] = uArg3;
  v7 = 0;
  while ( nArg1 != nArg2 )
  {
    LOBYTE(v7) = 1;
    if ( uArg32 != nullptr )
      sub_41B050(uArg32, nArg1);
    uArg32 += 3;
    LOBYTE(v7) = 0;
    nArg1 += 12;
  }
  return uArg32;
}



// ------------------------------------------------------------
// 0x41B310 sub_41B310 —— 槽位池析构（位图数组 + 9 级槽链表）
//   this+4 数组逐项 free(项[1]) + free(项)：8B 位图对象（容量 + malloc 位缓冲）；
//   随后释放 this+4 与 this+20（12B 单元 vector 走 0x41A930）并把六字段清零。
// ------------------------------------------------------------
void /*thiscall*/ sub_41B310(int this)
{
  unsigned int i; // ebx
  int fld_4; // ecx
  void **v4; // esi
  int fld_14; // eax

  for ( i = 0; ; ++i )
  {
    fld_4 = *(uint32_t *)(this + 4);
    if ( fld_4 == 0 || (*(uint32_t *)(this + 8) - fld_4) >> 2 <= i )
      break;
    v4 = *(void ***)(fld_4 + 4 * i);
    if ( v4 != nullptr )
    {
      if ( v4[1] != nullptr )
        free(v4[1]);
      j__free(v4);
    }
  }
  if ( *(uint32_t *)(this + 4) != 0 )
    j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
  fld_14 = *(uint32_t *)(this + 20);
  if ( fld_14 != 0 )
  {
    sub_41A930(fld_14, *(uint32_t *)(this + 24));
    j__free(*(void **)(this + 20));
  }
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 0;
  *(uint32_t *)(this + 28) = 0;
  if ( *(uint32_t *)(this + 4) != 0 )
    j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
}



// ------------------------------------------------------------
// 0x41B420 sub_41B420 —— 区间赋固定值（各单元内容重置为 pArg3）
//   逐单元（12B）先断链释放旧内容再 0x41ABE0 拷入固定源；insert 后移段的清位赋值。【推断】
// ------------------------------------------------------------
int /*cdecl*/ sub_41B420(int nArg1, int nArg2, int pArg3)
{
  int result; // eax
  int i; // esi
  int *v5; // ebx
  uint32_t **v6; // ecx
  uint32_t *v7; // eax
  bool v8; // zf
  uint32_t *v9; // edi
  int v10; // [esp+Ch] [ebp+8h]

  result = nArg2;
  for ( i = nArg1; i != nArg2; i += 12 )
  {
    if ( i != pArg3 )
    {
      v5 = *(int **)(pArg3 + 4);
      v6 = *(uint32_t ***)(i + 4);
      v10 = *v5;
      v7 = *v6;
      *v6 = v6;
      *(uint32_t *)(*(uint32_t *)(i + 4) + 4) = *(uint32_t *)(i + 4);
      v8 = v7 == *(uint32_t **)(i + 4);
      *(uint32_t *)(i + 8) = 0;
      if ( !v8 )
      {
        do
        {
          v9 = (uint32_t *)*v7;
          j__free(v7);
          v7 = v9;
        }
        while ( v9 != *(uint32_t **)(i + 4) );
      }
      sub_41ABE0((uint32_t *)i, **(uint32_t **)(i + 4), v10, v5, nArg2);
    }
    result = nArg2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x41B4A0 sub_41B4A0 —— 0x41B200 倒序拷贝 thunk（insert/erase 内部用）
// ------------------------------------------------------------
int /*cdecl*/ sub_41B4A0(int nArg1, int nArg2, int nArg3)
{
  return sub_41B200(nArg1, nArg2, nArg3);
}



// ------------------------------------------------------------
// 0x41B4C0 sub_41B4C0 —— 填充 nArg2 个拷贝单元（fill_n → uArg1）
//   逐元素 0x41B050(uArg12, nArg3) 从模板拷贝构造，返回末地址 —— resize/insert 的填充段。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_41B4C0(uint32_t *uArg1, int nArg2, int nArg3)
{
  uint32_t *uArg12; // esi
  uint32_t *result; // eax
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  uArg12 = uArg1;
  v6[4] = v6;
  v6[3] = uArg1;
  v7 = 0;
  while ( nArg2 != 0 )
  {
    LOBYTE(v7) = 1;
    if ( uArg12 != nullptr )
      result = sub_41B050(uArg12, nArg3);
    --nArg2;
    uArg12 += 3;
    LOBYTE(v7) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x41B550 sub_41B550 —— 外层池数组析构（vector<T*> → 逐项 0x41B310 + free）
//   遍历 this+4 指针数组，每项调 0x41B310 析构池再 free；最后释放数组并清零三字段。
// ------------------------------------------------------------
void /*thiscall*/ sub_41B550(int this)
{
  unsigned int i; // esi
  int fld_4; // ecx
  void *v4; // edi

  for ( i = 0; ; ++i )
  {
    fld_4 = *(uint32_t *)(this + 4);
    if ( fld_4 == 0 || (*(uint32_t *)(this + 8) - fld_4) >> 2 <= i )
      break;
    v4 = *(void **)(fld_4 + 4 * i);
    if ( v4 != nullptr )
    {
      sub_41B310(*(uint32_t *)(fld_4 + 4 * i));
      j__free(v4);
    }
  }
  if ( *(uint32_t *)(this + 4) != 0 )
    j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  *(uint32_t *)(this + 12) = 0;
}



// ------------------------------------------------------------
// 0x41B5E0 sub_41B5E0 —— 12B 单元 erase(first, last)（前移 + 尾部销毁）
//   0x41B170 把 [nArg4, end) 前移到 nArg3，0x41A930 销毁残留尾部并收回止指针，*pDwArg2 写回新位置。
// ------------------------------------------------------------
int */*thiscall*/ sub_41B5E0(int *this, int *pDwArg2, int nArg3, int nArg4)
{
  int fld_e2; // edi

  if ( nArg3 != nArg4 )
  {
    fld_e2 = sub_41B170(nArg4, *(this + 2), nArg3);
    sub_41A930(fld_e2, *(this + 2));
    *(this + 2) = fld_e2;
  }
  *pDwArg2 = nArg3;
  return pDwArg2;
}



// ------------------------------------------------------------
// 0x41B630 sub_41B630 —— 12B 单元 fill_n 区间填充（返回 pArg1 + 3*nArg2 末地址）
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_41B630(uint32_t *pArg1, int nArg2, int nArg3)
{
  sub_41B4C0(pArg1, nArg2, nArg3);
  return &pArg1[3 * nArg2];
}



// ------------------------------------------------------------
// 0x41B660 sub_41B660 —— 12B 单元 insert(pos, n, val) 核心
//   容量足且尾距足 → 后移（0x41B280/0x41B4A0）+ 清位赋值（0x41B420）；尾距不足 → 搬尾 + 填充（0x41B630）+ 尾部复位；
//   容量不足 → new 12*2n 缓冲三段拼接（0x41B280 / 0x41B4C0 / 0x41B280）后整体替换；末尾释放临时模板元素。
// ------------------------------------------------------------
void /*thiscall*/ sub_41B660(int *this, int pArg2, unsigned int uArg3, int nArg4)
{
  int fld_e1; // ebx
  unsigned int fld_e3; // ecx
  int fld_e2; // eax
  int fld_e22; // eax
  unsigned int v10; // ecx
  int fld_e27; // eax
  char *pMem; // ebx
  int fld_e13; // eax
  unsigned int v14; // edi
  int fld_e14; // eax
  uint32_t *fld_e23; // ecx
  int fld_e26; // edi
  uint32_t *v19; // esi
  uint32_t *v20; // eax
  bool v21; // zf
  uint32_t *v22; // edi
  int fld_e12; // [esp-18h] [ebp-48h]
  uint32_t *fld_e25; // [esp-Ch] [ebp-3Ch]
  int fld_e24; // [esp-8h] [ebp-38h]
  int v26; // [esp+0h] [ebp-30h] BYREF
  int v27; // [esp+Ch] [ebp-24h] BYREF
  void *v28; // [esp+10h] [ebp-20h]
  void *Block; // [esp+18h] [ebp-18h]
  int *pThis; // [esp+1Ch] [ebp-14h]
  int *v31; // [esp+20h] [ebp-10h]
  int v32; // [esp+2Ch] [ebp-4h]
  int v33; // [esp+38h] [ebp+8h]
  uint32_t *v34; // [esp+3Ch] [ebp+Ch]
  int v35; // [esp+40h] [ebp+10h]
  int v36; // [esp+40h] [ebp+10h]

  v31 = &v26;
  pThis = this;
  sub_41B050(&v27, nArg4);
  fld_e1 = *(this + 1);
  fld_e3 = 0;
  v32 = 0;
  if ( fld_e1 != 0 )
    fld_e3 = (*(this + 3) - fld_e1) / 12;
  if ( uArg3 != 0 )
  {
    if ( fld_e1 != 0 )
      fld_e2 = (*(this + 2) - fld_e1) / 12;
    else
      fld_e2 = 0;
    if ( 357913941 - fld_e2 < uArg3 )
      sub_41A8C0(this);
    if ( fld_e1 != 0 )
      fld_e22 = (*(this + 2) - fld_e1) / 12;
    else
      fld_e22 = 0;
    if ( fld_e3 >= uArg3 + fld_e22 )
    {
      fld_e23 = (uint32_t *)*(this + 2);
      v36 = (int)fld_e23;
      if ( ((int)fld_e23 - pArg2) / 12 >= uArg3 )
      {
        v33 = (int)&fld_e23[-3 * uArg3];
        *(this + 2) = (int)sub_41B280(v33, (int)fld_e23, fld_e23);
        sub_41B4A0(pArg2, v33, v36);
        sub_41B420(pArg2, pArg2 + 12 * uArg3, (int)&v27);
      }
      else
      {
        sub_41B280(pArg2, (int)fld_e23, (uint32_t *)(pArg2 + 12 * uArg3));
        fld_e24 = uArg3 - (*(this + 2) - pArg2) / 12;
        fld_e25 = (uint32_t *)*(this + 2);
        LOBYTE(v32) = 3;
        sub_41B630(fld_e25, fld_e24, (int)&v27);
        fld_e26 = 12 * uArg3 + *(this + 2);
        *(this + 2) = fld_e26;
        v32 = 0;
        sub_41B420(pArg2, fld_e26 - 12 * uArg3, (int)&v27);
      }
    }
    else
    {
      if ( 357913941 - (fld_e3 >> 1) >= fld_e3 )
        v10 = (fld_e3 >> 1) + fld_e3;
      else
        v10 = 0;
      if ( fld_e1 != 0 )
        fld_e27 = (*(this + 2) - fld_e1) / 12;
      else
        fld_e27 = 0;
      if ( v10 < uArg3 + fld_e27 )
        v10 = uArg3 + sub_4DA030(this);
      v35 = 12 * v10;
      pMem = (char *)operator new(12 * v10);
      fld_e12 = *(this + 1);
      Block = pMem;
      LOBYTE(v32) = 1;
      v34 = sub_41B280(fld_e12, pArg2, pMem);
      sub_41B4C0(v34, uArg3, (int)&v27);
      sub_41B280(pArg2, *(this + 2), &v34[3 * uArg3]);
      fld_e13 = *(this + 1);
      if ( fld_e13 != 0 )
        fld_e13 = (*(this + 2) - fld_e13) / 12;
      v14 = fld_e13 + uArg3;
      fld_e14 = *(this + 1);
      if ( fld_e14 != 0 )
      {
        sub_41A930(fld_e14, *(this + 2));
        j__free((void *)*(this + 1));
      }
      *(this + 3) = (int)&pMem[v35];
      *(this + 2) = (int)&pMem[12 * v14];
      *(this + 1) = (int)pMem;
    }
  }
  v19 = v28;
  v20 = *(uint32_t **)v28;
  v21 = *(uint32_t *)v28 == (uint32_t)v28;
  *(uint32_t *)v28 = v28;
  v19[1] = v19;
  if ( !v21 )
  {
    do
    {
      v22 = (uint32_t *)*v20;
      j__free(v20);
      v20 = v22;
    }
    while ( v22 != v19 );
  }
  j__free(v19);
}


// ------------------------------------------------------------
// 0x41B970 sub_41B970 —— 12B 单元 vector resize（模板元素 pszArg3）
//   需扩 → 0x41B660 追加差额；需缩 → 0x41B5E0 擦除尾部；末尾释放临时模板元素副本（Block 链）。
// ------------------------------------------------------------
void /*thiscall*/ sub_41B970(int *this, unsigned int uArg2, char pszArg3, uint32_t **Block, int nArg5)
{
  int fld_e1; // esi
  unsigned int fld_e2; // eax
  int fld_e22; // eax
  uint32_t *Block2; // esi
  uint32_t *v9; // eax
  bool v10; // zf
  uint32_t *v11; // edi

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 )
    fld_e2 = (*(this + 2) - fld_e1) / 12;
  else
    fld_e2 = 0;
  if ( fld_e2 >= uArg2 )
  {
    if ( fld_e1 != 0 && uArg2 < (*(this + 2) - fld_e1) / 12 )
      sub_41B5E0(this, (int *)&uArg2, fld_e1 + 12 * uArg2, *(this + 2));
  }
  else
  {
    if ( fld_e1 != 0 )
      fld_e22 = (*(this + 2) - fld_e1) / 12;
    else
      fld_e22 = 0;
    sub_41B660(this, *(this + 2), uArg2 - fld_e22, (int)&pszArg3);
  }
  Block2 = Block;
  v9 = *Block;
  v10 = *Block == Block;
  *Block = Block;
  Block2[1] = Block2;
  if ( !v10 )
  {
    do
    {
      v11 = (uint32_t *)*v9;
      j__free(v9);
      v9 = v11;
    }
    while ( v11 != Block2 );
  }
  j__free(Block2);
}



// ------------------------------------------------------------
// 0x41BA60 sub_41BA60 —— ★ 槽位池构造（9 级位图 2^16..2^8 + 9 槽链表 + 预置 0..255）
//   建 9 个位图对象（容量 ((1<<i)+7)&~7，i=16..8，malloc 位数组清零）推入 this+4 vector；
//   再把槽链表数组 resize 为 9（0x41B970 用空链模板），最后把 0..255 逐个挂进末级（2^8）链表。
// ------------------------------------------------------------
int */*thiscall*/ sub_41BA60(int *this)
{
  unsigned int *pMem; // esi
  unsigned int v3; // eax
  void *pMem2; // eax
  unsigned int v5; // edx
  unsigned int pBuf; // ecx
  int fld_e1; // edx
  unsigned int fld_e2; // ecx
  unsigned int **fld_e22; // eax
  bool v10; // zf
  uint32_t **v11; // eax
  int fld_e6; // esi
  int v13; // edi
  int v14; // eax
  char v16[24]; // [esp-Ch] [ebp-34h] BYREF
  void *pThis; // [esp+Ch] [ebp-1Ch]
  int v18; // [esp+10h] [ebp-18h] BYREF
  int v19; // [esp+14h] [ebp-14h]
  unsigned int i; // [esp+18h] [ebp-10h] BYREF
  int v21; // [esp+24h] [ebp-4h]

  pThis = this;
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  v21 = 0;
  *(this + 5) = 0;
  *(this + 6) = 0;
  *(this + 7) = 0;
  LOBYTE(v21) = 1;
  i = 16;
  v19 = 9;
  do
  {
    pMem = (unsigned int *)operator new(8u);
    if ( pMem != nullptr )
    {
      v3 = ((1 << i) + 7) & 0xFFFFFFF8;
      *pMem = v3;
      pMem2 = malloc(v3 >> 3);
      v5 = *pMem >> 3;
      pBuf = *pMem >> 5;
      pMem[1] = (unsigned int)pMem2;
      memset(pMem2, 0, 4 * pBuf + (v5 & 3));
    }
    else
    {
      pMem = nullptr;
    }
    fld_e1 = *(this + 1);
    v18 = (int)pMem;
    if ( fld_e1 != 0 )
      fld_e2 = (*(this + 2) - fld_e1) >> 2;
    else
      fld_e2 = 0;
    if ( fld_e1 != 0 && fld_e2 < (*(this + 3) - fld_e1) >> 2 )
    {
      fld_e22 = (unsigned int **)*(this + 2);
      *fld_e22 = pMem;
      *(this + 2) = (int)(fld_e22 + 1);
    }
    else
    {
      sub_41AA00((int)this, *(this + 2), 1u, &v18);
    }
    v10 = v19 == 1;
    --i;
    --v19;
  }
  while ( !v10 );
  v18 = (int)v16;
  v11 = (uint32_t **)sub_425940(v16);
  sub_41B970(this + 4, 9u, v16[0], v11, 0);
  for ( i = 0; i < 0x100; ++i )
  {
    fld_e6 = *(this + 6);
    v13 = *(uint32_t *)(fld_e6 - 8);
    v18 = (int)sub_40C0F0(v13, *(uint32_t *)(v13 + 4), &i);
    sub_41A830((uint32_t *)(fld_e6 - 12), 1u);
    v14 = v18;
    *(uint32_t *)(v13 + 4) = v18;
    **(uint32_t **)(v14 + 4) = v14;
  }
  return this;
}



// ------------------------------------------------------------
// 0x41BBE0 sub_41BBE0 —— ★ 槽位分配 allocate(len ≤ 0x1000)【推断】
//   按 len 取级（ceil(log2(len)) - 4，即 1<<(级+4) 逐级比较）后遍历各级池：命中空闲槽即置位并返回 级<<16 | 槽；
//   未命中则 new 0x100020 建新池（0x41BA60）挂入 this 再在该池中取；返回码高 16 位为池/级索引，低 16 位为槽。
// ------------------------------------------------------------
int /*thiscall*/ sub_41BBE0(void *this, unsigned int uArg2)
{
  void *pThis; // esi
  int result; // eax
  int v4; // edi
  unsigned int v5; // ebx
  int v6; // edx
  uint32_t *v7; // ecx
  int v8; // ebx
  uint32_t *v9; // edi
  unsigned int v10; // esi
  unsigned int v11; // ebx
  int v12; // ebx
  int v13; // ecx
  int v14; // edi
  int v15; // ecx
  uint32_t **v16; // eax
  void *Block2; // ecx
  int v18; // edx
  unsigned int *v19; // esi
  unsigned int uArg22; // eax
  void *pMem; // eax
  void *v22; // eax
  int v23; // edx
  unsigned int v24; // edi
  uint32_t *v25; // ecx
  uint32_t *v26; // edi
  int v27; // ebx
  unsigned int v28; // esi
  unsigned int v29; // ebx
  int v30; // ebx
  char *v31; // edi
  int v32; // ecx
  uint32_t **v33; // eax
  int v34; // edx
  unsigned int *v35; // esi
  int v36; // eax
  int v37; // esi
  void *Block; // [esp+8h] [ebp-18h] BYREF
  uint32_t *v39; // [esp+Ch] [ebp-14h]
  void *pThis2; // [esp+10h] [ebp-10h]
  int v41; // [esp+1Ch] [ebp-4h]

  pThis = this;
  result = 0;
  pThis2 = this;
  if ( uArg2 <= 0x1000 )
  {
    while ( uArg2 >= 1 << (result + 4) )
    {
      if ( (unsigned int)++result >= 9 )
        goto LABEL_6;
    }
    HIBYTE(uArg2) = result + 4;
LABEL_6:
    v4 = -1;
    v5 = 0;
    while ( 1 )
    {
      v6 = *((uint32_t *)pThis + 1);
      v39 = (uint32_t *)v5;
      if ( v6 == 0 || (*((uint32_t *)pThis + 2) - v6) >> 2 <= v5 )
        break;
      v7 = *(uint32_t **)(v6 + 4 * v5);
      Block = v7;
      if ( HIBYTE(uArg2) < 4u || HIBYTE(uArg2) > 0xCu )
      {
        v4 = -1;
        ++v5;
      }
      else
      {
        v8 = v7[5];
        v9 = v7 + 4;
        v10 = (uint8_t)(HIBYTE(uArg2) - 4);
        if ( v8 == 0 || (v7[6] - v8) / 12 <= v10 )
          goto LABEL_58;
        if ( *(uint32_t *)(v8 + 12 * v10 + 8) != 0 )
        {
          v12 = v7[5];
          if ( v12 == 0 || (v7[6] - v12) / 12 <= v10 )
            goto LABEL_58;
          v11 = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(v12 + 12 * v10 + 4) + 4) + 8);
        }
        else
        {
          v11 = sub_41AD70(HIBYTE(uArg2) + 1, 1);
        }
        if ( v11 == -1 )
        {
          pThis = pThis2;
          v4 = -1;
          v5 = (unsigned int)v39 + 1;
        }
        else
        {
          v13 = v9[1];
          if ( v13 == 0 || (v9[2] - v13) / 12 <= v10 )
            goto LABEL_58;
          v14 = v13 + 12 * v10;
          v15 = *(uint32_t *)(v14 + 4);
          v16 = *(uint32_t ***)(v15 + 4);
          if ( v16 != (uint32_t **)v15 )
          {
            *v16[1] = *v16;
            (*v16)[1] = v16[1];
            j__free(v16);
            --*(uint32_t *)(v14 + 8);
          }
          Block2 = Block;
          v18 = *((uint32_t *)Block + 1);
          if ( v18 == 0 || (*((uint32_t *)Block + 2) - v18) >> 2 <= v10 )
            goto LABEL_63;
          v19 = *(unsigned int **)(v18 + 4 * v10);
          if ( v11 < *v19 )
            *(uint8_t *)(v19[1] + (v11 >> 3)) |= 1 << (v11 & 7);
          v4 = v11 << (HIBYTE(uArg2) - 4);
          if ( v4 != -1 )
          {
            uArg22 = (unsigned int)v39;
            pThis = pThis2;
            goto LABEL_33;
          }
          pThis = pThis2;
          v5 = (unsigned int)v39 + 1;
        }
      }
    }
    uArg22 = uArg2;
LABEL_33:
    if ( v4 != -1 )
      return v4 + (uArg22 << 16);
    pMem = operator new(0x100020u);
    Block = pMem;
    v41 = 0;
    if ( pMem != nullptr )
      v22 = (void *)sub_41BA60((int)pMem);
    else
      v22 = nullptr;
    v23 = *((uint32_t *)pThis + 1);
    v41 = -1;
    Block = v22;
    if ( v23 != 0 )
      v24 = (*((uint32_t *)pThis + 2) - v23) >> 2;
    else
      v24 = 0;
    if ( v23 != 0 && v24 < (*((uint32_t *)pThis + 3) - v23) >> 2 )
    {
      v25 = *((uint32_t **)pThis + 2);
      *v25 = v22;
      *((uint32_t *)pThis + 2) = v25 + 1;
    }
    else
    {
      sub_41AA00(*((void **)pThis + 2), 1, (int)&Block);
    }
    v26 = *(uint32_t **)(*((uint32_t *)pThis + 2) - 4);
    v39 = v26;
    if ( HIBYTE(uArg2) >= 4u && HIBYTE(uArg2) <= 0xCu )
    {
      v27 = v26[5];
      v9 = v26 + 4;
      v28 = (uint8_t)(HIBYTE(uArg2) - 4);
      if ( v27 == 0 || (v9[2] - v27) / 12 <= v28 )
        sub_41A7C0(v9);  // 【STL 容器模板实例族（vector/list/deque 诊断与操作）】
      if ( *(uint32_t *)(v27 + 12 * v28 + 8) != 0 )
      {
        v30 = v9[1];
        if ( v30 == 0 || (v9[2] - v30) / 12 <= v28 )
          sub_41A7C0(v9);  // 【STL 容器模板实例族（vector/list/deque 诊断与操作）】
        v29 = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(v30 + 12 * v28 + 4) + 4) + 8);
      }
      else
      {
        v29 = sub_41AD70(HIBYTE(uArg2) + 1, 1);
      }
      if ( v29 != -1 )
      {
        Block = (void *)v9[1];
        if ( Block == nullptr || (v9[2] - (int)Block) / 12 <= v28 )
LABEL_58:
          sub_41A7C0(v9);  // 【STL 容器模板实例族（vector/list/deque 诊断与操作）】
        v31 = (char *)Block + 12 * v28;
        v32 = *((uint32_t *)v31 + 1);
        v33 = *(uint32_t ***)(v32 + 4);
        if ( v33 != (uint32_t **)v32 )
        {
          *v33[1] = *v33;
          (*v33)[1] = v33[1];
          j__free(v33);
          --*((uint32_t *)v31 + 2);
        }
        Block2 = v39;
        v34 = v39[1];
        if ( v34 == 0 || (v39[2] - v34) >> 2 <= v28 )
LABEL_63:
          sub_41A7C0(Block2);  // 【STL 容器模板实例族（vector/list/deque 诊断与操作）】
        v35 = *(unsigned int **)(v34 + 4 * v28);
        if ( v29 < *v35 )
          *(uint8_t *)(v35[1] + (v29 >> 3)) |= 1 << (v29 & 7);
        pThis = pThis2;
        v4 = v29 << (HIBYTE(uArg2) - 4);
        goto LABEL_69;
      }
      pThis = pThis2;
    }
    v4 = -1;
LABEL_69:
    v36 = *((uint32_t *)pThis + 1);
    if ( v36 != 0 )
      v37 = (*((uint32_t *)pThis + 2) - v36) >> 2;
    else
      v37 = 0;
    uArg22 = v37 - 1;
    return v4 + (uArg22 << 16);
  }
  return result;
}


// ------------------------------------------------------------
// 0x41BFE0 sub_41BFE0 —— ★ 驻留字符串设置（set(const char*)）
//   先释放旧句柄（递减/还槽）；新串为 null 或 len ≥ 0x1000 → 置空；否则 new 12B 句柄：
//   槽码 = 0x41BBE0(len+1)，失败 free 置空；成功写 [槽码, 原长, refcount=1] 并把串（含终止符）拷入 0x41AC90 槽址。
// ------------------------------------------------------------
void /*thiscall*/ sub_41BFE0(void **this, const char *pArg2)
{
  unsigned int nLen; // eax
  unsigned int nLen2; // esi
  unsigned int v5; // ebx
  int v6; // eax

  if ( *this != nullptr )
  {
    if ( --*((uint32_t *)*this + 2) == 0 )
    {
      sub_41AFC0(*(uint32_t *)*this);
      j__free(*this);
    }
    *this = nullptr;
  }
  if ( pArg2 != nullptr )
  {
    nLen = strlen(pArg2);
    nLen2 = nLen;
    if ( nLen < 0x1000 )
    {
      if ( nLen != 0 )
      {
        v5 = nLen + 1;
        *this = operator new(0xCu);
        v6 = sub_41BBE0(nLen2 + 1);
        if ( v6 == -1 )
        {
          j__free(*this);
          *this = nullptr;
        }
        else
        {
          *(uint32_t *)*this = v6;
          *((uint32_t *)*this + 1) = nLen2;
          *((uint32_t *)*this + 2) = 1;
          qmemcpy((void *)sub_41AC90(*(uint32_t *)*this), pArg2, v5);
        }
      }
      else
      {
        *this = nullptr;
      }
    }
  }
}



// ============================================================
// SECTION 0x41C0C0 — 应用状态/模块管理（场景查询、退出、事件分发、消息发送）
// ============================================================
// ------------------------------------------------------------
// 0x41C0C0 sub_41C0C0 —— 发送缓冲写入单字节（长度 1 的极短消息封装）【推断】
//   转发 0x423290(&pszArg1, 1)；姊妹 ·0x41C0E0 为长度 2 版本。
// ------------------------------------------------------------
int /*stdcall*/ sub_41C0C0(char pszArg1)  // 【应用状态/模块管理（场景查询、退出、事件分发、消息发送）】
{
  return sub_423290(&pszArg1, 1);
}



// ------------------------------------------------------------
// 0x41C0E0 sub_41C0E0 —— 发送缓冲写入（长度 2 版本）【推断】
//   转发 0x423290(&pszArg1, 2) —— 与 ·0x41C0C0 构成同一包字段的写入原语对。
// ------------------------------------------------------------
int /*stdcall*/ sub_41C0E0(char pszArg1)
{
  return sub_423290(&pszArg1, 2);
}



// ------------------------------------------------------------
// 0x41C100 sub_41C100 —— 写字符串到发送缓冲（4B 长度 + 内容）
//   入参 null 返回 0x80000000；否则先写 strlen 长度（4B）再写内容，返回第二次写入结果。
// ------------------------------------------------------------
unsigned int /*stdcall*/ sub_41C100(const char *pArg1)
{
  const char *pArg12; // esi

  pArg12 = pArg1;
  if ( pArg1 == nullptr )
    return 0x80000000;
  pArg1 = (const char *)strlen(pArg1);
  sub_423290(&pArg1, 4);
  return sub_423290(pArg12, pArg1);
}



// ------------------------------------------------------------
// 0x41C150 sub_41C150 —— crypt4byte 初始化转发（0x41A590）
//   直接转发 0x41A590(uArg1, nArg2, nArg3) 并返回 nArg3，便于调用点链式使用。
// ------------------------------------------------------------
int /*fastcall*/ sub_41C150(unsigned int uArg1, int nArg2, int nArg3)
{
  sub_41A590(uArg1, nArg2, nArg3);
  return nArg3;
}



// ------------------------------------------------------------
// 0x41C170 sub_41C170 —— 驻留句柄拷贝构造（置空 + 0x41B0D0 赋值）
//   *this = 0 后引用计数 ++（拷贝语义），返回 this。
// ------------------------------------------------------------
unsigned int **/*thiscall*/ sub_41C170(unsigned int **this, unsigned int **pDwArg2)
{
  *this = nullptr;
  sub_41B0D0(this, pDwArg2);
  return this;
}



// ------------------------------------------------------------
// 0x41C190 sub_41C190 —— 级联通知转发（this+44 / this+104 作上下文）【推断】
//   以 (nArg2, *(this+44), *(this+104)) 调 0x425960（播放/暂停级联广播）。
// ------------------------------------------------------------
int /*thiscall*/ sub_41C190(uint32_t *this, int nArg2)
{
  return sub_425960(nArg2, *(this + 11), *(this + 26));
}



// ------------------------------------------------------------
// 0x41C1B0 sub_41C1B0 —— 按全局键 word_77F804 查表取对象
//   0x429830 表按键查找（uint16）；返回 0 表示当前无对应管理器/界面实例。【推断】
// ------------------------------------------------------------
int sub_41C1B0()
{
  return sub_429830((uint16_t)word_77F804);
}



// ------------------------------------------------------------
// 0x41C1C0 sub_41C1C0 —— 字段 setter（this+112 = pszArg2）
//   恒返回 1（成功）。
// ------------------------------------------------------------
int /*thiscall*/ sub_41C1C0(uint8_t *this, char pszArg2)
{
  *(this + 112) = pszArg2;
  return 1;
}



// ------------------------------------------------------------
// 0x41C1E0 sub_41C1E0
// ------------------------------------------------------------
void /*noreturn*/ sub_41C1E0()
{
  sub_65DC70(lpCriticalSection);
  sub_6989F0(dword_8F7B08);
  PostQuitMessage(0);
  sub_41FD50();
  exit(0);
}



// ------------------------------------------------------------
// 0x41C210 sub_41C210 —— 状态判定（三路或）【推断】
//   模块态 this+12 == 3 → 1；== 4 且 *(*(this+32)+36) == 3 → 1；== 6 且 0x42B510(this+40)（场景类别 +32 属 2/3/4）非 0 → 1。
// ------------------------------------------------------------
char /*thiscall*/ sub_41C210(uint32_t *this)
{
  if ( *(this + 3) == 3 )
    return 1;
  if ( *(this + 3) == 4 )
  {
    if ( *(uint32_t *)(*(this + 8) + 36) == 3 )
      return 1;
  }
  else if ( *(this + 3) == 6 && (uint8_t)sub_42B510(*(this + 10)) != 0 )
  {
    return 1;
  }
  return 0;
}



// ------------------------------------------------------------
// 0x41C240 sub_41C240 —— 8 个控件/对象指针就地析构并清零
//   this+16 起 8 个指针：非空则调 vtbl 首项(对象, 1) 释放，槽位写 0；返回 1。【推断】
// ------------------------------------------------------------
int /*thiscall*/ sub_41C240(uint32_t *this)
{
  uint32_t *pThis_4; // esi
  int i; // edi

  pThis_4 = this + 4;
  for ( i = 8; i != 0; --i )
  {
    if ( *pThis_4 != 0 )
      (**(void (/*thiscall*/ ***)(uint32_t, int))*pThis_4)(*pThis_4, 1);
    *pThis_4++ = 0;
  }
  return 1;
}



// ------------------------------------------------------------
// 0x41C270 sub_41C270 —— 对 this+248 子对象做 crypt4byte 初始化
//   转发 0x41A590(pArg1 + 248, nArg2, uArg3)。
// ------------------------------------------------------------
int /*fastcall*/ sub_41C270(int pArg1, int nArg2, uint8_t uArg3)
{
  return sub_41A590(pArg1 + 248, nArg2, uArg3);
}



// ------------------------------------------------------------
// 0x41C290 sub_41C290 —— this+248 子对象完整性校验
//   0x41A5E0(this + 248) != 0 —— 加密字段校验点位（反篡改检查）。【推断】
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_41C290(void *this)
{
  return sub_41A5E0((unsigned int)this + 248) != 0;
}



// ------------------------------------------------------------
// 0x41C2B0 sub_41C2B0 —— ★ 进入频道请求组包
//   调试日志 off_77F3FC(byte_6C2B70, this+113)；0x423200(…, 1) 开包 → 写串 this+113、串 this+177（各 64B 级，长度+内容）、
//   写 4B（this+262..）与 16B（nArg2）→ 0x423380 发包；随后置 this+92=1（等待应答）、93/94=0、0x698F90(this+80) 归零计时、this+76=0。
// ------------------------------------------------------------
char /*thiscall*/ sub_41C2B0(int this, int nArg2)
{
  const char *pThis_71; // esi
  int i; // esi
  char result; // al
  unsigned int nLen; // [esp+Ch] [ebp-8h] BYREF
  uint8_t v7[4]; // [esp+10h] [ebp-4h] BYREF

  pThis_71 = (const char *)(this + 113);
  off_77F3FC((char *)&byte_6C2B70, this + 113);
  sub_423200(dword_8F7B08, 1);  // 【发送网络包API】
  if ( pThis_71 != nullptr )
  {
    nLen = strlen(pThis_71);
    sub_423290(&nLen, 4);
    sub_423290(pThis_71, nLen);
  }
  if ( this != -177 )
  {
    nLen = strlen((const char *)(this + 177));
    sub_423290(&nLen, 4);
    sub_423290(this + 177, nLen);
  }
  for ( i = 0; i < 4; ++i )
  {
    v7[0] = *(uint8_t *)(this + i + 262);
    sub_423290(v7, 1);
  }
  sub_423290(nArg2, 16);
  sub_423380(dword_8F7B08);
  *(uint8_t *)(this + 92) = 1;
  *(uint8_t *)(this + 93) = 0;
  *(uint8_t *)(this + 94) = 0;
  result = sub_698F90(this + 80, 0, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
  *(uint8_t *)(this + 76) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x41C3C0 sub_41C3C0 —— 字段 setter（this+292 = nArg2）
// ------------------------------------------------------------
int /*thiscall*/ sub_41C3C0(uint32_t *this, int nArg2)
{
  *(this + 73) = nArg2;
  return nArg2;
}



// ------------------------------------------------------------
// 0x41C3D0 sub_41C3D0 —— 状态提示刷新（资源 843/844 文本 + 条件触发）
//   this+292 == 1 时按 pszArg2 取文本 843/844，经 0x43BEE0(文本, 颜色 -6567706(0xFF9BE5E6), 0, -1) 建提示控件；
//   若 dword_8F8500 与查表项 +192 非空 → 0x431820(pszArg2)（雪花/特效触发条件包装）。
// ------------------------------------------------------------
int /*thiscall*/ sub_41C3D0(uint32_t *this, char pszArg2)
{
  int result; // eax
  uint32_t *v3; // esi
  int v4; // eax

  result = *(this + 73) - 1;
  if ( *(this + 73) == 1 )
  {
    v3 = *((uint32_t **)dword_8F8528 + 7);
    if ( pszArg2 != 0 )
      v4 = sub_422E70(843);
    else
      v4 = sub_422E70(844);
    result = sub_43BEE0(v3, v4, -6567706, 0, -1);
  }
  if ( dword_8F8500 != 0 )
  {
    result = sub_429830((uint16_t)word_77F804);
    if ( result != 0 )
    {
      result = sub_429830((uint16_t)word_77F804);
      if ( *(uint32_t *)(result + 192) != 0 )
        return sub_431820(pszArg2);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x41C470 sub_41C470 —— 字节数组 setter（this + pArg2 + 297 = pszArg3）
// ------------------------------------------------------------
char /*thiscall*/ sub_41C470(uint8_t *this, int pArg2, char pszArg3)
{
  *(this + pArg2 + 297) = pszArg3;
  return pszArg3;
}



// ------------------------------------------------------------
// 0x41C490 sub_41C490 —— dword 数组 setter（this + pArg2 + 77 = nArg3）
// ------------------------------------------------------------
int /*thiscall*/ sub_41C490(uint32_t *this, int pArg2, int nArg3)
{
  *(this + pArg2 + 77) = nArg3;
  return nArg3;
}



// ------------------------------------------------------------
// 0x41C4B0 sub_41C4B0 —— 索引取字符串资源（文本表）【推断】
//   1..5 → 资源 845..849；7/8 → 1950/1951；其余返回空串 szPassword —— 等级/名号等固定文本。
// ------------------------------------------------------------
const CHAR */*stdcall*/ sub_41C4B0(int nArg1)
{
  const CHAR *result; // eax

  switch ( nArg1 )
  {
    case 1:
      result = (const CHAR *)sub_422E70(845);
      break;
    case 2:
      result = (const CHAR *)sub_422E70(846);
      break;
    case 3:
      result = (const CHAR *)sub_422E70(847);
      break;
    case 4:
      result = (const CHAR *)sub_422E70(848);
      break;
    case 5:
      result = (const CHAR *)sub_422E70(849);
      break;
    case 7:
      result = (const CHAR *)sub_422E70(1950);
      break;
    case 8:
      result = (const CHAR *)sub_422E70(1951);
      break;
    default:
      result = szPassword;
      break;
  }
  return result;
}



// ------------------------------------------------------------
// 0x41C570 sub_41C570 —— 字段 setter（this+352 = nArg2）并同步全局 dword_78FF38
// ------------------------------------------------------------
int /*thiscall*/ sub_41C570(uint32_t *this, int nArg2)
{
  *(this + 88) = nArg2;
  dword_78FF38 = nArg2;
  return nArg2;
}



// ------------------------------------------------------------
// 0x41C590 sub_41C590 —— 状态查询（this+348 == 4）
// ------------------------------------------------------------
bool /*thiscall*/ sub_41C590(uint32_t *this)
{
  return *(this + 87) == 4;
}



// ------------------------------------------------------------
// 0x41C5A0 sub_41C5A0 —— vector<T 4B> 大小查询（空返回 0）
// ------------------------------------------------------------
int /*thiscall*/ sub_41C5A0(uint32_t *this)
{
  int fld_e1; // edx

  fld_e1 = *(this + 1);
  if ( fld_e1 != 0 )
    return (*(this + 2) - fld_e1) >> 2;
  else
    return 0;
}



// ------------------------------------------------------------
// 0x41C5C0 sub_41C5C0 —— 红黑树最左节点查找（_Min 实例，nil 标志 +33）
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_41C5C0(uint32_t *pArg1)
{
  uint32_t *result; // eax
  int *v2; // ecx

  result = pArg1;
  v2 = (int *)*pArg1;
  if ( *(uint8_t *)(*pArg1 + 33) == 0 )
  {
    do
    {
      result = v2;
      v2 = (int *)*v2;
    }
    while ( *((uint8_t *)v2 + 33) == 0 );
  }
  return result;
}



// ------------------------------------------------------------
// 0x41C5E0 sub_41C5E0 —— 红黑树迭代器自增（_Inc 实例，nil 标志 +21）
//   右子树非空 → 取右子树最左；否则沿父链上溯（含根/表头判定）；返回自增后的迭代器。
// ------------------------------------------------------------
int */*thiscall*/ sub_41C5E0(int *this)
{
  int *result; // eax
  int *v2; // edx

  result = (int *)*this;
  if ( *(uint8_t *)(*this + 21) == 0 )
  {
    v2 = (int *)result[2];
    if ( *((uint8_t *)v2 + 21) != 0 )
    {
      for ( result = (int *)result[1]; *((uint8_t *)result + 21) == 0; result = (int *)result[1] )
      {
        if ( *this != result[2] )
          break;
        *this = (int)result;
      }
      *this = (int)result;
    }
    else
    {
      result = (int *)*v2;
      if ( *(uint8_t *)(*v2 + 21) == 0 )
      {
        do
        {
          v2 = result;
          result = (int *)*result;
        }
        while ( *((uint8_t *)result + 21) == 0 );
      }
      *this = (int)v2;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x41C640 sub_41C640 —— 红黑树迭代器自增（_Inc 实例二，nil 标志 +33）
// ------------------------------------------------------------
int */*thiscall*/ sub_41C640(int *this)
{
  int *result; // eax
  int *v2; // edx

  result = (int *)*this;
  if ( *(uint8_t *)(*this + 33) == 0 )
  {
    v2 = (int *)result[2];
    if ( *((uint8_t *)v2 + 33) != 0 )
    {
      for ( result = (int *)result[1]; *((uint8_t *)result + 33) == 0; result = (int *)result[1] )
      {
        if ( *this != result[2] )
          break;
        *this = (int)result;
      }
      *this = (int)result;
    }
    else
    {
      result = (int *)*v2;
      if ( *(uint8_t *)(*v2 + 33) == 0 )
      {
        do
        {
          v2 = result;
          result = (int *)*result;
        }
        while ( *((uint8_t *)result + 33) == 0 );
      }
      *this = (int)v2;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x41C6A0 sub_41C6A0 —— 驻留句柄区间赋值（逐元素 0x41B0D0 = 引用计数 ++）
//   返回目标末地址。
// ------------------------------------------------------------
unsigned int **/*cdecl*/ sub_41C6A0(unsigned int **pDwArg1, unsigned int **pDwArg2, unsigned int **pDwArg3)
{
  unsigned int **pDwArg12; // esi
  unsigned int **pDwArg32; // edi

  pDwArg12 = pDwArg1;
  if ( pDwArg1 == pDwArg2 )
    return pDwArg3;
  pDwArg32 = pDwArg3;
  do
    sub_41B0D0(pDwArg32++, pDwArg12++);
  while ( pDwArg12 != pDwArg2 );
  return pDwArg32;
}



// ------------------------------------------------------------
// 0x41C6E0 sub_41C6E0 —— 超时判定（clock_now(clk) >= this+24 截止时刻）
// ------------------------------------------------------------
bool /*thiscall*/ sub_41C6E0(int *this)
{
  int fld_e6; // esi

  fld_e6 = *(this + 6);
  return sub_699000((int)this) >= fld_e6;  // 【clock_now(clk)】
}



// ------------------------------------------------------------
// 0x41C700 sub_41C700 —— ★ CNMainGameModule 构造
//   装 CNMainGameModule vftable（this[0]/this[2] + IAppendDraw 多重继承）；初始化四组 12B 子容器（off_6C2B88 同型块）；
//   子域使能标志（this+36/+76/+104）置 1；末尾 0x444B60 未激活态字段复位 + 0x444F60 激活初始化（控件 + 场景）。返回 this。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_41C700(uint8_t *this)
{
  *(this + 4) = 0;
  *((uint32_t *)this + 2) = &nengine::IAppendDraw::`vftable';
  *(uint32_t *)this = &CNMainGameModule::`vftable';
  *((uint32_t *)this + 2) = &CNMainGameModule::`vftable';
  *(this + 28) = 0;
  *((uint32_t *)this + 6) = &off_6C2B88;
  *((uint32_t *)this + 8) = 0;
  *(this + 36) = 1;
  *(this + 38) = 0;
  *(this + 37) = 0;
  *((uint32_t *)this + 12) = 0;
  *((uint32_t *)this + 11) = 0;
  *((uint32_t *)this + 10) = 0;
  *(this + 68) = 0;
  *((uint32_t *)this + 16) = &off_6C2B88;
  *((uint32_t *)this + 18) = 0;
  *(this + 76) = 1;
  *(this + 78) = 0;
  *(this + 77) = 0;
  *((uint32_t *)this + 22) = 0;
  *((uint32_t *)this + 21) = 0;
  *((uint32_t *)this + 20) = 0;
  *(this + 96) = 0;
  *((uint32_t *)this + 23) = &off_6C2B88;
  *((uint32_t *)this + 25) = 0;
  *(this + 104) = 1;
  *(this + 106) = 0;
  *(this + 105) = 0;
  *((uint32_t *)this + 29) = 0;
  *((uint32_t *)this + 28) = 0;
  *((uint32_t *)this + 27) = 0;
  sub_444B60((int)this);
  sub_444F60(this);
  return this;
}



// ------------------------------------------------------------
// 0x41C7C0 sub_41C7C0 —— CNMainGameModule 标量删除析构（0x41C7F0 + flag&1 free）
// ------------------------------------------------------------
void */*thiscall*/ sub_41C7C0(void *Block, char pszArg2)
{
  sub_41C7F0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x41C7F0 sub_41C7F0 —— CNMainGameModule 析构体
//   vftable 复位 → 0x444F10 释放激活对象 → 四个子对象 vftable 依次回落 nengine::IObject 并清标志 → 返回 0。
// ------------------------------------------------------------
char /*thiscall*/ sub_41C7F0(uint32_t *this)
{
  *this = &CNMainGameModule::`vftable';
  *(this + 2) = &CNMainGameModule::`vftable';
  sub_444F10();
  *(this + 23) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 96) = 0;
  *(this + 16) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 68) = 0;
  *(this + 6) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 28) = 0;
  *this = &nengine::IObject::`vftable';
  *((uint8_t *)this + 4) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x41C860 sub_41C860 —— 断线/超时退出判定（重试上限 5）
//   0x4461F0(dword_8F8520) 上报（PVP ping/SNAT 日志，包 105）；若未连接（8F7B08+8 == 0）或重试计数 this+108 > 5 →
//   0x41C1E0 退出清理（__noreturn）；否则 ++this+108 并发包 3 后 flush。
// ------------------------------------------------------------
int /*thiscall*/ sub_41C860(uint32_t *this)
{
  int fld_e27; // eax

  sub_4461F0(dword_8F8520);
  if ( *(uint8_t *)(dword_8F7B08 + 8) == 0 || (fld_e27 = *(this + 27)) > 5 )
    sub_41C1E0();
  *(this + 27) = fld_e27 + 1;
  sub_423200(dword_8F7B08, 3);  // 【发送网络包API】
  return sub_423380(dword_8F7B08);
}



// ------------------------------------------------------------
// 0x41C8B0 sub_41C8B0 —— ★ 帧更新主循环（CNMainGameModule::Update）
//   未就绪(this+4)==0 → 0x80000001；驱动 dword_79C0B4/79C0B8 两设备（vt+12）；未聚焦且鼠标在顶栏（pt.y < 24）→
//   SendMessageA(0xA1/0xA2, HTCAPTION=2) 实现窗口拖拽；模块态 != 8 → 旧模块 vt+8(卸载) + 新模块 vt+4(激活)；
//   到期提示（this+60 / clock_now >= this+72）与 10 分钟提示（this+92 / clock_now(this+80) >= 600000）各借对象池 0x44E8D0（池 0x1B，文本 841/842）。
// ------------------------------------------------------------
int /*thiscall*/ sub_41C8B0(int this)
{
  int fld_C; // eax
  int fld_C2; // ecx
  int fld_48; // edi
  int v6; // eax
  int v7; // eax

  if ( *(uint8_t *)(this + 4) == 0 )
    return -2147483647;
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B4 + 12))(dword_79C0B4);
  if ( dword_79C0B8 != 0 )
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0B8 + 12))(dword_79C0B8);
  if ( *(uint8_t *)(this + 112) == 0 && *(uint32_t *)(dword_8F7A24 + 12) != 0 && pt.y < 24 )
  {
    if ( byte_89D274 == 0 || (SendMessageA(*(HWND *)(dword_79C0A0 + 16), 0xA1u, 2u, 0), byte_89D274 == 0) )
      SendMessageA(*(HWND *)(dword_79C0A0 + 16), 0xA2u, 2u, 0);
  }
  fld_C = *(uint32_t *)(this + 12);
  if ( fld_C != 8 )
  {
    (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4 * fld_C + 16) + 8))(*(uint32_t *)(this + 4 * fld_C + 16));
    fld_C2 = *(uint32_t *)(this + 4 * *(uint32_t *)(this + 12) + 16);
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)fld_C2 + 4))(fld_C2);
  }
  if ( *(uint8_t *)(this + 60) != 0 )
  {
    fld_48 = *(uint32_t *)(this + 72);
    if ( sub_699000(this + 48) >= fld_48 )  // 【clock_now(clk)】
    {
      if ( *(uint8_t *)(dword_8F7B08 + 8) == 0 )
      {
        v6 = sub_422E70(841);
        sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v6, 1);
      }
      *(uint8_t *)(this + 60) = 0;
    }
  }
  if ( *(uint8_t *)(this + 92) != 0 && sub_699000(this + 80) >= 600000 )  // 【clock_now(clk)】
  {
    v7 = sub_422E70(842);
    sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v7, 1);
    *(uint8_t *)(this + 92) = 0;
  }
  return 1;
}



// ------------------------------------------------------------
// 0x41C9E0 sub_41C9E0 —— 字段 setter（this+296），变更时 0x41C3D0 刷新提示
// ------------------------------------------------------------
int /*thiscall*/ sub_41C9E0(int this, int nArg2)
{
  int result; // eax

  result = nArg2;
  if ( *(uint8_t *)(this + 296) != (uint8_t)nArg2 )
  {
    *(uint8_t *)(this + 296) = nArg2;
    return sub_41C3D0((uint32_t *)this, nArg2);
  }
  return result;
}



// ------------------------------------------------------------
// 0x41CA00 sub_41CA00 —— 0x41C6A0 区间赋值 thunk
// ------------------------------------------------------------
unsigned int **/*cdecl*/ sub_41CA00(unsigned int **pDwArg1, unsigned int **pDwArg2, unsigned int **pDwArg3)
{
  return sub_41C6A0(pDwArg1, pDwArg2, pDwArg3);
}



// ------------------------------------------------------------
// 0x41CA20 sub_41CA20 —— 红黑树节点递归释放（后序 free；nil 标志 +21）实例一
// ------------------------------------------------------------
char /*stdcall*/ sub_41CA20(void **Block)
{
  void **Block2; // edi
  char result; // al
  void **i; // esi

  Block2 = Block;
  result = *((uint8_t *)Block + 21);
  for ( i = Block; result == 0; Block2 = i )
  {
    sub_41CA20(i[2]);
    i = (void **)*i;
    j__free(Block2);
    result = *((uint8_t *)i + 21);
  }
  return result;
}



// ------------------------------------------------------------
// 0x41CA60 sub_41CA60 —— 同构实例二（另 map 元素）
// ------------------------------------------------------------
char /*stdcall*/ sub_41CA60(void **Block)
{
  void **Block2; // edi
  char result; // al
  void **i; // esi

  Block2 = Block;
  result = *((uint8_t *)Block + 21);
  for ( i = Block; result == 0; Block2 = i )
  {
    sub_41CA60(i[2]);
    i = (void **)*i;
    j__free(Block2);
    result = *((uint8_t *)i + 21);
  }
  return result;
}



// ------------------------------------------------------------
// 0x41CAA0 sub_41CAA0 —— 同构实例三
// ------------------------------------------------------------
char /*stdcall*/ sub_41CAA0(void **Block)
{
  void **Block2; // edi
  char result; // al
  void **i; // esi

  Block2 = Block;
  result = *((uint8_t *)Block + 21);
  for ( i = Block; result == 0; Block2 = i )
  {
    sub_41CAA0(i[2]);
    i = (void **)*i;
    j__free(Block2);
    result = *((uint8_t *)i + 21);
  }
  return result;
}



// ------------------------------------------------------------
// 0x41CAE0 sub_41CAE0 —— 同构实例四
// ------------------------------------------------------------
char /*stdcall*/ sub_41CAE0(void **Block)
{
  void **Block2; // edi
  char result; // al
  void **i; // esi

  Block2 = Block;
  result = *((uint8_t *)Block + 21);
  for ( i = Block; result == 0; Block2 = i )
  {
    sub_41CAE0(i[2]);
    i = (void **)*i;
    j__free(Block2);
    result = *((uint8_t *)i + 21);
  }
  return result;
}



// ------------------------------------------------------------
// 0x41CB20 sub_41CB20 —— 同构实例五
// ------------------------------------------------------------
char /*stdcall*/ sub_41CB20(void **Block)
{
  void **Block2; // edi
  char result; // al
  void **i; // esi

  Block2 = Block;
  result = *((uint8_t *)Block + 21);
  for ( i = Block; result == 0; Block2 = i )
  {
    sub_41CB20(i[2]);
    i = (void **)*i;
    j__free(Block2);
    result = *((uint8_t *)i + 21);
  }
  return result;
}



// ------------------------------------------------------------
// 0x41CB60 sub_41CB60 —— 驻留句柄区间拷贝构造（置 0 后 0x41B0D0 引用 ++）
//   返回目标末地址。
// ------------------------------------------------------------
unsigned int **/*cdecl*/ sub_41CB60(unsigned int **pDwArg1, unsigned int **pDwArg2, unsigned int **pDwArg3)
{
  unsigned int **pDwArg32; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  pDwArg32 = pDwArg3;
  v6[4] = v6;
  v6[3] = pDwArg3;
  v7 = 0;
  while ( pDwArg1 != pDwArg2 )
  {
    LOBYTE(v7) = 1;
    if ( pDwArg32 != nullptr )
    {
      *pDwArg32 = nullptr;
      sub_41B0D0(pDwArg32, pDwArg1);
    }
    ++pDwArg32;
    LOBYTE(v7) = 0;
    ++pDwArg1;
  }
  return pDwArg32;
}



// ------------------------------------------------------------
// 0x41CBF0 sub_41CBF0 —— 成员析构（两个 std::string + crypt4byte 子对象）
//   this+140 串（容量 ≥ 16 走堆 free）复位；0x41A580 复位 crypt4byte(this+37)；this+24 串释放并置空。
// ------------------------------------------------------------
void /*thiscall*/ sub_41CBF0(int this)
{
  if ( *(uint32_t *)(this + 140) >= 0x10u )
    j__free(*(void **)(this + 120));
  *(uint32_t *)(this + 140) = 15;
  *(uint32_t *)(this + 136) = 0;
  *(uint8_t *)(this + 120) = 0;
  sub_41A580((uint32_t *)(this + 37));
  if ( *(uint32_t *)(this + 24) >= 0x10u )
    j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 20) = 0;
  *(uint32_t *)(this + 24) = 15;
  *(uint8_t *)(this + 4) = 0;
}



// ============================================================
// SECTION 0x41CC80 — ★★ onChangeModule 模块切换总控（UDP STOP/START 广播、LADDER_DOWN、STOP SOUND、MAP_APPEAR）
// ============================================================
// ------------------------------------------------------------
// 0x41CC80 sub_41CC80
// ------------------------------------------------------------
// 【解读】
//   ★★ onChangeModule 模块切换总控（252 行，函数名直证于 CALL 表）:
//     按目标模块 switch: MODULE_TYPE_PVP / WARROOM / MAIN_GAME||SELECT_DUNGEON →
//       "@@UDP STOP - onChangeModule(), MODULE_TYPE_XXX" 广播（语音/UDP 停止）；
//     SELECT_DUNGEON → "@@UDP START - onChangeModule(), MODULE_TYPE_SELECT_DUNGEON : seatIndex %d"；
//     case 4 → sub_432EA0("LADDER_DOWN")（天梯离场提示/音效）；
//     另见 "STOP SOUND" / "MAP_APPEAR" 关键串 —— 场景声音停播与地图出场事件。
// ------------------------------------------------------------
void /*thiscall*/ sub_41CC80(int this, int ArgList, int nArg3)  // 【onChangeModule 模块切换总控（UDP STOP/START 广播、LA…】
{
  int nArg32; // ebx
  int v4; // edi
  int fld_1C; // ebx
  int v7; // eax
  int fld_14; // eax
  int fld_10; // ecx
  uint32_t *v10; // ebx
  int v11; // eax
  int i; // ebx
  int v13; // eax
  int pObj2; // eax
  int j; // ebx
  int v16; // eax
  int pObj; // edi
  int v18; // eax
  int v19; // ebx
  int v20; // eax
  int k; // esi
  int v22; // eax
  int v23; // eax
  int v24; // [esp+Ch] [ebp-4h]

  nArg32 = nArg3;
  v4 = ArgList;
  if ( ArgList == nArg3 )
    return;
  off_77F3FC((char *)&byte_6C2CE8, ArgList, nArg3);
  sub_41A170();
  if ( nArg3 == 3 || nArg3 == 4 || (dword_77F488 = 1, nArg3 == 6) )
    dword_77F488 = 0;
  switch ( ArgList )
  {
    case 1:
      fld_14 = *(uint32_t *)(this + 20);
      if ( *(uint32_t *)(fld_14 + 216) == 1 )
        *(uint32_t *)(fld_14 + 216) = -1;
      goto LABEL_11;
    case 3:
      sub_4772A0(0);
      sub_45A420(0);
      fld_1C = *(uint32_t *)(*(uint32_t *)(this + 28) + 16);
      if ( fld_1C != 0 )
      {
        sub_425500(0);
        sub_424100(0);
        sub_475760();
        *(uint32_t *)(fld_1C + 108) = 0;
        sub_472AF0();
      }
      nArg32 = nArg3;
      goto LABEL_11;
    case 4:
      *((uint32_t *)dword_8F8528 + 621) = 0;
      off_77F3FC("@@UDP STOP - onChangeModule(), MODULE_TYPE_PVP 1");
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 152))(dword_8F8520);
      goto LABEL_11;
    case 5:
      sub_44E850(dword_8F8528, 27);
      sub_46E3B0(*(uint32_t *)(this + 36));
      goto LABEL_11;
    case 6:
      *((uint32_t *)dword_8F8528 + 621) = 0;
      off_77F3FC("@@UDP STOP - onChangeModule(), MODULE_TYPE_WARROOM 1");
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 152))(dword_8F8520);
      if ( *(uint32_t *)(*(uint32_t *)(this + 40) + 188) == 1 )
      {
        v7 = sub_422E70(1925);
      }
      else
      {
        if ( *(uint32_t *)(*(uint32_t *)(this + 40) + 188) != 2 )
          goto LABEL_11;
        v7 = sub_422E70(1926);
      }
      sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v7, 0);
LABEL_11:
      switch ( nArg32 )
      {
        case 0:
          fld_10 = *(uint32_t *)(this + 16);
          *(uint32_t *)(this + 284) = *(uint32_t *)(*(uint32_t *)(this + 36) + 12);
          sub_46D300(fld_10);
          break;
        case 1:
          sub_45B250(*(uint32_t *)(this + 20));
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 124))(
            dword_8F8520,
            *(uint32_t *)(*(uint32_t *)(this + 20) + 44));
          sub_445830(0);
          (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 112))(dword_8F8520);
          sub_461110(0);
          if ( *(uint32_t *)(this + 348) == 4 )
          {
            sub_44E8D0((char *)dword_8F8528, (void *)2, 0, 0);
            v10 = *((uint32_t **)dword_8F8528 + 7);
            v11 = sub_422E70(1249);
            sub_43BEE0(v10, v11, -6567706, 0, -1);
            nArg32 = nArg3;
          }
          if ( ArgList != 0 )
          {
            switch ( ArgList )
            {
              case 3:
              case 2:
                sub_65DC70(lpCriticalSection);
                dword_79D0C4 = 100;
                for ( i = 16; i < 32; i += 4 )
                {
                  v13 = *(uint32_t *)(i + dword_8F850C);
                  if ( v13 != 0 )
                  {
                    pObj2 = *(uint32_t *)(v13 + 196);
                    if ( pObj2 != 0 )
                      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj2 + 1020))(pObj2);
                  }
                }
                if ( *(uint32_t *)(sub_429830((uint16_t)word_77F804) + 184) == 0 )
                {
                  off_77F3FC("@@UDP STOP - onChangeModule(), MODULE_TYPE_MAIN_GAME || MODULE_TYPE_SELECT_DUNGEON 1");
                  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 152))(dword_8F8520);
                }
                sub_657230(*(uint32_t *)(dword_8F8520 + 1049988));
                sub_45DF90(dword_8F8524);
                sub_4461F0(dword_8F8520);
                sub_45B0A0(*(uint32_t *)(this + 20));
                sub_425960(
                  0,
                  *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(this + 20) + 44) + 44),
                  *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(this + 20) + 44) + 104));
                (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 164))(dword_8F8520);
                sub_458400(*((uint32_t *)dword_8F8528 + 609));
                nArg32 = nArg3;
                break;
              case 4:
                sub_45F4D0(273);
                (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 1056))(dword_8F7C04, 1);
                sub_432EA0("LADDER_DOWN", -1, 0, 0);
                break;
              case 6:
                sub_45F4D0(273);
                (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)dword_8F7C04 + 1056))(dword_8F7C04, 1);
                break;
              default:
                break;
            }
          }
          if ( dword_8F7C08 != 0 )
            sub_42FC50();
          sub_41C3D0(*(uint8_t *)(this + 296));
          break;
        case 2:
          sub_453A60(*(uint32_t *)(this + 24));
          sub_65DC70(lpCriticalSection);
          off_77F3FC("STOP SOUND");
          sub_432EA0("MAP_APPEAR", -1, 0, 0);
          v24 = 0;
          for ( j = 16; j < 32; j += 4 )
          {
            v16 = *(uint32_t *)(j + dword_8F850C);
            if ( v16 != 0 )
            {
              pObj = *(uint32_t *)(v16 + 196);
              if ( pObj != 0 )
              {
                (*(void (/*thiscall*/ **)(int))(*(uint32_t *)pObj + 1020))(pObj);
                (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 1200))(pObj, 1);
                (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)pObj + 1212))(pObj, v24);
              }
              v4 = ArgList;
            }
            ++v24;
          }
          if ( (*(uint8_t (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 156))(dword_8F8520) == 0 )
          {
            v18 = sub_456420(dword_8F850C);
            off_77F3FC("@@UDP START - onChangeModule(), MODULE_TYPE_SELECT_DUNGEON : seatIndex %d /// 1", v18);
            v19 = *(uint32_t *)dword_8F8520;
            v20 = sub_456420(dword_8F850C);
            (*(void (/*thiscall*/ **)(int, int))(v19 + 148))(dword_8F8520, v20);
          }
          sub_453AC0(*(uint32_t *)(*(uint32_t *)(this + 20) + 44));
          sub_425960(
            1,
            *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(this + 24) + 68) + 44),
            *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(this + 24) + 68) + 104));
          sub_456210(**(uint32_t **)(*(uint32_t *)(*(uint32_t *)(this + 20) + 104) + 40));
          sub_4461F0(dword_8F8520);
          sub_445960(dword_8F8520);
          sub_6560A0(dword_8F8548);
          for ( k = 0; k < 8; ++k )
          {
            if ( *(uint32_t *)(sub_656710() + 4 * k) != -1 )
              sub_656630(k);
          }
          v22 = sub_656710();
          v23 = sub_656840(v22);  // 【定时器/调度容器（GetTickCount / timeGetTime 节流链表）】
          sub_656630(v23);
          sub_656090(dword_8F8548);
          nArg32 = nArg3;
          break;
        case 3:
          sub_444BE0(*(uint32_t *)(this + 28));
          sub_461110(0);
          sub_44E850(dword_8F8528, 55);
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 124))(
            dword_8F8520,
            *(uint32_t *)(*(uint32_t *)(this + 28) + 16));
          if ( ArgList == 2 )
          {
            sub_425460(*(uint32_t *)(*(uint32_t *)(this + 28) + 16));
            sub_41C190(0);
            *((uint32_t *)dword_8F8528 + 621) = 0;
            (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 160))(dword_8F8520);
          }
          break;
        case 4:
          sub_461110(1);
          sub_453230(*(uint32_t *)(this + 32));
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 124))(
            dword_8F8520,
            *(uint32_t *)(*(uint32_t *)(this + 32) + 16));
          sub_432EA0("LADDER_DOWN", -1, 0, 0);
          break;
        case 5:
          *(uint8_t *)(this + 60) = 0;
          dword_978998 = 0;
          sub_46EF40(*(uint32_t *)(this + 36));
          break;
        case 6:
          sub_461110(1);
          sub_42EE80(*(uint32_t *)(this + 40));
          (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)dword_8F8520 + 124))(
            dword_8F8520,
            *(uint32_t *)(*(uint32_t *)(this + 40) + 16));
          break;
        default:
          break;
      }
      sub_44EA20(v4, nArg32);  // 【模块切换收尾（docs/13 §3 末行定案调用）】
      return;
    default:
      goto LABEL_11;
  }
}


// ------------------------------------------------------------
// 0x41D300 sub_41D300 —— 模块切换 setter → 0x41CC80(onChangeModule) 转发
//   先存旧模块号 this+12，写新值后以 (旧, 新) 触发切换总控。
// ------------------------------------------------------------
void /*thiscall*/ sub_41D300(int *this, int nArg2)
{
  int fld_e3; // [esp-8h] [ebp-8h]

  fld_e3 = *(this + 3);
  *(this + 3) = nArg2;
  sub_41CC80((int)this, fld_e3, nArg2);  // 【onChangeModule 模块切换总控（UDP STOP/START 广播、LA…】
}



// ------------------------------------------------------------
// 0x41D320 sub_41D320 —— ★ 登出/回主界面资源卸载链
//   进临界区；旧模块 != 5 → this+12 = 0 且 onChangeModule(旧→0)；清 STL map(0x4297A0) 与红黑树(0x4878B0)，
//   NPC 容器 +164 置 0 并清链(0x41CA60)、重建归属(0x45C400)、锚定对象换绑(0x425500/0x424100)；
//   批量全局管理器卸载 + 观察者树清空(0x41CA20)；自身字段 +297..+348 复位；切到 0 态时发包 8（0xFFFF + 0x02）并 flush。
// ------------------------------------------------------------
int /*thiscall*/ sub_41D320(int this)
{
  int fld_C; // eax
  uint32_t *fld_14; // edi
  void **v4; // edx
  int v5; // ecx
  uint32_t *v6; // eax
  int fld_142; // eax
  uint32_t *fld_1C; // edi
  int result; // eax
  int v10; // [esp+Ch] [ebp-8h] BYREF
  char v11[4]; // [esp+10h] [ebp-4h] BYREF

  sub_65DC70(lpCriticalSection);
  fld_C = *(uint32_t *)(this + 12);
  if ( fld_C != 5 )
  {
    *(uint32_t *)(this + 12) = 0;
    sub_41CC80(this, fld_C, 0);  // 【onChangeModule 模块切换总控（UDP STOP/START 广播、LA…】
  }
  sub_4297A0(dword_8F8500);
  sub_4878B0(dword_8F8504);
  *(uint32_t *)(*(uint32_t *)(this + 20) + 164) = 0;
  fld_14 = *(uint32_t **)(this + 20);
  v4 = *(void ***)(fld_14[23] + 4);
  v10 = (int)fld_14;
  fld_14 += 22;
  sub_41CA60(v4);
  v5 = v10;
  *(uint32_t *)(fld_14[1] + 4) = fld_14[1];
  v6 = (uint32_t *)fld_14[1];
  fld_14[2] = 0;
  *v6 = v6;
  *(uint32_t *)(fld_14[1] + 8) = fld_14[1];
  sub_45C400(v5);
  fld_142 = *(uint32_t *)(this + 20);
  *(uint32_t *)(fld_142 + 104) = 0;
  *(uint32_t *)(fld_142 + 108) = 0;
  fld_1C = *(uint32_t **)(*(uint32_t *)(this + 28) + 16);
  if ( fld_1C != nullptr )
  {
    sub_425500(0);
    sub_424100(fld_1C, 0);
    sub_475760();
    fld_1C[27] = 0;
    sub_472AF0();
  }
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8520 + 152))(dword_8F8520);
  sub_485020(dword_8F852C);
  sub_485020(dword_8F8530);
  sub_485020(dword_8F8534);
  sub_4844B0(dword_8F8538);
  sub_483E30(dword_8F853C);
  sub_47E2B0();
  sub_47CC00(dword_8F8540);
  sub_41CA20(*(void ***)(dword_99FBA8 + 4));
  *(uint32_t *)(dword_99FBA8 + 4) = dword_99FBA8;
  dword_99FBAC = 0;
  *(uint32_t *)dword_99FBA8 = dword_99FBA8;
  *(uint32_t *)(dword_99FBA8 + 8) = dword_99FBA8;
  sub_456950(dword_8F850C);
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8510 + 12))(dword_8F8510);
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8514 + 12))(dword_8F8514);
  (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_8F8518 + 12))(dword_8F8518);
  sub_47A380();
  sub_43ECC0(*((uint32_t *)dword_8F8528 + 7));
  *(uint32_t *)(this + 297) = 0;
  *(uint32_t *)(this + 301) = 0;
  *(uint8_t *)(this + 305) = 0;
  *(uint32_t *)(this + 308) = 0;
  *(uint32_t *)(this + 312) = 0;
  *(uint32_t *)(this + 316) = 0;
  *(uint32_t *)(this + 320) = 0;
  *(uint32_t *)(this + 324) = 0;
  *(uint32_t *)(this + 328) = 0;
  *(uint32_t *)(this + 332) = 0;
  *(uint32_t *)(this + 336) = 0;
  *(uint32_t *)(this + 340) = 0;
  result = *(uint32_t *)(this + 12);
  *(uint32_t *)(this + 348) = 0;
  if ( result == 0 )
  {
    sub_423200(dword_8F7B08, 8);  // 【发送网络包API】
    v10 = 0xFFFF;
    sub_423290(&v10, 2);
    v11[0] = 2;
    sub_423290(v11, 1);
    return sub_423380(dword_8F7B08);
  }
  return result;
}



// ------------------------------------------------------------
// 0x41D520 sub_41D520 —— 切换到模块 5 的切换流程
//   0x44AB50 页签切换 ×2；子对象 *(this+16)+48 标志清零；this+12 = 5 后 onChangeModule(旧→5)；发包 3 + flush。
// ------------------------------------------------------------
int /*thiscall*/ sub_41D520(int *this)
{
  int fld_e3; // [esp-8h] [ebp-Ch]

  sub_44AB50(1, 12);
  sub_44AB50(0, 12);
  *(uint8_t *)(*(this + 4) + 48) = 0;
  fld_e3 = *(this + 3);
  *(this + 3) = 5;
  sub_41CC80((int)this, fld_e3, 5);  // 【onChangeModule 模块切换总控（UDP STOP/START 广播、LA…】
  sub_423200(dword_8F7B08, 3);  // 【发送网络包API】
  return sub_423380(dword_8F7B08);
}



// ------------------------------------------------------------
// 0x41D580 sub_41D580 —— 0x41CB60 区间拷贝构造 thunk（stdcall）
// ------------------------------------------------------------
unsigned int **/*stdcall*/ sub_41D580(unsigned int **pDwArg1, unsigned int **pDwArg2, unsigned int **pDwArg3)
{
  return sub_41CB60(pDwArg1, pDwArg2, pDwArg3);
}



// ============================================================
// SECTION 0x41D5A0 — 模块切换辅助（map 容器/观察者清理/资源卸载链）
// ============================================================
// ------------------------------------------------------------
// 0x41D5A0 sub_41D5A0 [串: "vector<T> too long"]
// ------------------------------------------------------------
void /*noreturn*/ sub_41D5A0()  // 【模块切换辅助（map 容器/观察者清理/资源卸载链）】
{
  uint32_t pExceptionObject[10]; // [esp+0h] [ebp-50h] BYREF
  size_t v1; // [esp+28h] [ebp-28h] BYREF
  char v2; // [esp+2Ch] [ebp-24h]
  int v3; // [esp+3Ch] [ebp-14h]
  int v4; // [esp+40h] [ebp-10h]
  int v5; // [esp+4Ch] [ebp-4h]

  v4 = 15;
  v3 = 0;
  v2 = 0;
  sub_4015C0(&v1, "vector<T> too long", 0x12u);  // 【std::string构造赋值】
  v5 = 0;
  sub_401740(pExceptionObject, &v1);
  pExceptionObject[0] = &std::length_error::`vftable';
  _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x41D610 sub_41D610 [串: "invalid map/set<T> iterator"]
// ------------------------------------------------------------
int ***/*thiscall*/ sub_41D610(uint32_t *this, int ***uArg2, int **pDwArg3)
{
  int **pDwArg32; // ebx
  int *v4; // edi
  int *v5; // ecx
  int *v6; // esi
  uint32_t *pThis2; // ecx
  int v8; // eax
  int *v9; // eax
  int v10; // ecx
  bool v11; // zf
  int v12; // eax
  int **v13; // eax
  char v14; // al
  uint32_t *pThis3; // ecx
  uint32_t *v16; // eax
  int v17; // eax
  uint32_t pExceptionObject[10]; // [esp+Ch] [ebp-5Ch] BYREF
  size_t v20; // [esp+34h] [ebp-34h] BYREF
  char v21; // [esp+38h] [ebp-30h]
  int v22; // [esp+48h] [ebp-20h]
  int v23; // [esp+4Ch] [ebp-1Ch]
  int v24; // [esp+50h] [ebp-18h]
  void *Block; // [esp+54h] [ebp-14h]
  uint32_t *pThis; // [esp+58h] [ebp-10h]
  int v27; // [esp+64h] [ebp-4h]

  pThis = this;
  if ( *((uint8_t *)pDwArg3 + 21) != 0 )
  {
    v23 = 15;
    v22 = 0;
    v21 = 0;
    sub_4015C0(&v20, "invalid map/set<T> iterator", 0x1Bu);  // 【std::string构造赋值】
    v27 = 0;
    sub_401740(pExceptionObject, &v20);
    pExceptionObject[0] = &std::out_of_range::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
  }
  pDwArg32 = pDwArg3;
  Block = pDwArg3;
  sub_41C5E0((int *)&pDwArg3);
  if ( *((uint8_t *)*pDwArg32 + 21) != 0 )
  {
    v4 = pDwArg32[2];
LABEL_8:
    v6 = pDwArg32[1];
    if ( *((uint8_t *)v4 + 21) == 0 )
      v4[1] = (int)v6;
    pThis2 = pThis;
    v8 = pThis[1];
    if ( *(int ***)(v8 + 4) == pDwArg32 )
    {
      *(uint32_t *)(v8 + 4) = v4;
    }
    else if ( (int **)*v6 == pDwArg32 )
    {
      *v6 = (int)v4;
    }
    else
    {
      v6[2] = (int)v4;
    }
    if ( *(int ***)pThis2[1] == pDwArg32 )
    {
      if ( *((uint8_t *)v4 + 21) != 0 )
      {
        v9 = v6;
      }
      else
      {
        v9 = (int *)sub_52E300(v4);
        pThis2 = pThis;
      }
      *(uint32_t *)pThis2[1] = v9;
    }
    v10 = pThis2[1];
    v11 = *(uint32_t *)(v10 + 8) == (uint32_t)pDwArg32;
    v24 = v10;
    if ( v11 )
    {
      if ( *((uint8_t *)v4 + 21) != 0 )
        *(uint32_t *)(v10 + 8) = v6;
      else
        *(uint32_t *)(v24 + 8) = sub_542490(v4);
    }
    goto LABEL_35;
  }
  if ( *((uint8_t *)pDwArg32[2] + 21) != 0 )
  {
    v4 = *pDwArg32;
    goto LABEL_8;
  }
  v5 = (int *)pDwArg3;
  v4 = pDwArg3[2];
  if ( pDwArg3 == pDwArg32 )
    goto LABEL_8;
  (*pDwArg32)[1] = (int)pDwArg3;
  *v5 = (int)*pDwArg32;
  if ( v5 == pDwArg32[2] )
  {
    v6 = v5;
  }
  else
  {
    v6 = (int *)v5[1];
    if ( *((uint8_t *)v4 + 21) == 0 )
      v4[1] = (int)v6;
    *v6 = (int)v4;
    v5[2] = (int)pDwArg32[2];
    pDwArg32[2][1] = (int)v5;
  }
  v12 = pThis[1];
  if ( *(int ***)(v12 + 4) == pDwArg32 )
  {
    *(uint32_t *)(v12 + 4) = v5;
  }
  else
  {
    v13 = (int **)pDwArg32[1];
    if ( *v13 == (int *)pDwArg32 )
      *v13 = v5;
    else
      v13[2] = v5;
  }
  v5[1] = (int)pDwArg32[1];
  v14 = *((uint8_t *)v5 + 20);
  *((uint8_t *)v5 + 20) = *((uint8_t *)pDwArg32 + 20);
  *((uint8_t *)pDwArg32 + 20) = v14;
LABEL_35:
  if ( *((uint8_t *)Block + 20) == 1 )
  {
    pThis3 = pThis;
    if ( v4 != *(int **)(pThis[1] + 4) )
    {
      do
      {
        if ( *((uint8_t *)v4 + 20) != 1 )
          break;
        v16 = (uint32_t *)*v6;
        if ( v4 == (int *)*v6 )
        {
          v16 = (uint32_t *)v6[2];
          if ( *((uint8_t *)v16 + 20) == 0 )
          {
            *((uint8_t *)v16 + 20) = 1;
            *((uint8_t *)v6 + 20) = 0;
            sub_433130(v6);
            v16 = (uint32_t *)v6[2];
            pThis3 = pThis;
          }
          if ( *((uint8_t *)v16 + 21) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(*v16 + 20) != 1 || *(uint8_t *)(v16[2] + 20) != 1 )
          {
            if ( *(uint8_t *)(v16[2] + 20) == 1 )
            {
              *(uint8_t *)(*v16 + 20) = 1;
              *((uint8_t *)v16 + 20) = 0;
              sub_4296E0(v16);
              v16 = (uint32_t *)v6[2];
            }
            *((uint8_t *)v16 + 20) = *((uint8_t *)v6 + 20);
            *((uint8_t *)v6 + 20) = 1;
            *(uint8_t *)(v16[2] + 20) = 1;
            sub_433130(v6);
            break;
          }
        }
        else
        {
          if ( *((uint8_t *)v16 + 20) == 0 )
          {
            *((uint8_t *)v16 + 20) = 1;
            *((uint8_t *)v6 + 20) = 0;
            sub_4296E0(v6);
            v16 = (uint32_t *)*v6;
            pThis3 = pThis;
          }
          if ( *((uint8_t *)v16 + 21) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(v16[2] + 20) != 1 || *(uint8_t *)(*v16 + 20) != 1 )
          {
            if ( *(uint8_t *)(*v16 + 20) == 1 )
            {
              *(uint8_t *)(v16[2] + 20) = 1;
              *((uint8_t *)v16 + 20) = 0;
              sub_433130(v16);
              v16 = (uint32_t *)*v6;
            }
            *((uint8_t *)v16 + 20) = *((uint8_t *)v6 + 20);
            *((uint8_t *)v6 + 20) = 1;
            *(uint8_t *)(*v16 + 20) = 1;
            sub_4296E0(v6);
            break;
          }
        }
        *((uint8_t *)v16 + 20) = 0;
LABEL_53:
        v4 = v6;
        v11 = v6 == *(int **)(pThis3[1] + 4);
        v6 = (int *)v6[1];
      }
      while ( !v11 );
    }
    *((uint8_t *)v4 + 20) = 1;
  }
  j__free(Block);
  v17 = pThis[2];
  if ( v17 != 0 )
    pThis[2] = v17 - 1;
  *uArg2 = pDwArg3;
  return uArg2;
}


// ------------------------------------------------------------
// 0x41D8D0 sub_41D8D0 —— 结构复位（5 个 16B 桶）
//   首字节与 +52/+56 清零；this+64 起 5 个 16B 桶逐个 free 缓冲并把三字段清零。
// ------------------------------------------------------------
void /*thiscall*/ sub_41D8D0(uint32_t *this)
{
  char *pThis_10; // esi
  int i; // edi

  *(uint8_t *)this = 0;
  *(this + 13) = 0;
  *(this + 14) = 0;
  pThis_10 = (char *)(this + 16);
  for ( i = 5; i != 0; --i )
  {
    if ( *(uint32_t *)pThis_10 != 0 )
      j__free(*(void **)pThis_10);
    *(uint32_t *)pThis_10 = 0;
    *((uint32_t *)pThis_10 + 1) = 0;
    *((uint32_t *)pThis_10 + 2) = 0;
    pThis_10 += 16;
  }
}



// ------------------------------------------------------------
// 0x41D910 sub_41D910 —— 数组析构迭代器（this+60 起 5 个 16B 元素 → 0x5E5260）
// ------------------------------------------------------------
void /*thiscall*/ sub_41D910(char *this)
{
  `eh vector destructor iterator'(this + 60, 0x10u, 5, (void (/*thiscall*/ *)(void *))sub_5E5260);
}



// ------------------------------------------------------------
// 0x41D930 sub_41D930 —— vector<T 28B> reserve(n)
//   三字段清零；n == 0 返回 0；n > 0x9249249 抛 0x416610（vector<T> too long）；否则 new 28*n 并写起/止/容量。
// ------------------------------------------------------------
char /*thiscall*/ sub_41D930(uint32_t *this, unsigned int uArg2)
{
  char *pMem; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( uArg2 == 0 )
    return 0;
  if ( uArg2 > 0x9249249 )
    sub_416610(this);
  pMem = (char *)operator new(28 * uArg2);
  *(this + 3) = &pMem[28 * uArg2];
  *(this + 1) = pMem;
  *(this + 2) = pMem;
  return 1;
}



// ------------------------------------------------------------
// 0x41D980 sub_41D980 —— 红黑树 erase(first, last) 实例一
//   覆盖整树（first==begin 且 last==end）→ 0x41CA60 递归清除并把表头三指针自环复位、计数 0；
//   否则按 _Inc 迭代逐个 0x41D610 摘除；*pDwArg2 写回删除后的迭代器。
// ------------------------------------------------------------
int **/*thiscall*/ sub_41D980(int ***this, int **pDwArg2, int *pDwArg3, int *pDwArg4)
{
  int *pDwArg42; // ebx
  int *pDwArg32; // esi
  int fld_e1; // eax
  uint32_t *fld_e12; // eax
  int **v10; // ecx
  int **v11; // eax
  int *j; // eax
  int *i; // eax

  pDwArg42 = pDwArg4;
  pDwArg32 = pDwArg3;
  fld_e1 = (int)*(this + 1);
  if ( pDwArg3 == *(int **)fld_e1 && pDwArg4 == (int *)fld_e1 )
  {
    sub_41CA60(*(void ***)(fld_e1 + 4));
    (*(this + 1))[1] = (int *)*(this + 1);
    fld_e12 = *(this + 1);
    *(this + 2) = nullptr;
    *fld_e12 = fld_e12;
    (*(this + 1))[2] = (int *)*(this + 1);
    *pDwArg2 = **(this + 1);
    return pDwArg2;
  }
  else
  {
    if ( pDwArg3 != pDwArg4 )
    {
      do
      {
        v10 = (int **)pDwArg32;
        if ( *((uint8_t *)pDwArg32 + 21) == 0 )
        {
          v11 = (int **)pDwArg32[2];
          if ( *((uint8_t *)v11 + 21) != 0 )
          {
            for ( i = (int *)pDwArg32[1]; *((uint8_t *)i + 21) == 0; i = (int *)i[1] )
            {
              if ( pDwArg32 != (int *)i[2] )
                break;
              pDwArg32 = i;
            }
            pDwArg32 = i;
          }
          else
          {
            pDwArg32 = (int *)pDwArg32[2];
            for ( j = *v11; *((uint8_t *)j + 21) == 0; j = (int *)*j )
              pDwArg32 = j;
          }
        }
        sub_41D610(this, (int ***)&pDwArg3, v10);
      }
      while ( pDwArg32 != pDwArg42 );
    }
    *pDwArg2 = pDwArg32;
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x41DA40 sub_41DA40 —— 同族实例二（回调 0x41CAA0）
// ------------------------------------------------------------
int **/*thiscall*/ sub_41DA40(int ***this, int **pDwArg2, int *pDwArg3, int *pDwArg4)
{
  int *pDwArg42; // ebx
  int *pDwArg32; // esi
  int fld_e1; // eax
  uint32_t *fld_e12; // eax
  int **v10; // ecx
  int **v11; // eax
  int *j; // eax
  int *i; // eax

  pDwArg42 = pDwArg4;
  pDwArg32 = pDwArg3;
  fld_e1 = (int)*(this + 1);
  if ( pDwArg3 == *(int **)fld_e1 && pDwArg4 == (int *)fld_e1 )
  {
    sub_41CAA0(*(void ***)(fld_e1 + 4));
    (*(this + 1))[1] = (int *)*(this + 1);
    fld_e12 = *(this + 1);
    *(this + 2) = nullptr;
    *fld_e12 = fld_e12;
    (*(this + 1))[2] = (int *)*(this + 1);
    *pDwArg2 = **(this + 1);
    return pDwArg2;
  }
  else
  {
    if ( pDwArg3 != pDwArg4 )
    {
      do
      {
        v10 = (int **)pDwArg32;
        if ( *((uint8_t *)pDwArg32 + 21) == 0 )
        {
          v11 = (int **)pDwArg32[2];
          if ( *((uint8_t *)v11 + 21) != 0 )
          {
            for ( i = (int *)pDwArg32[1]; *((uint8_t *)i + 21) == 0; i = (int *)i[1] )
            {
              if ( pDwArg32 != (int *)i[2] )
                break;
              pDwArg32 = i;
            }
            pDwArg32 = i;
          }
          else
          {
            pDwArg32 = (int *)pDwArg32[2];
            for ( j = *v11; *((uint8_t *)j + 21) == 0; j = (int *)*j )
              pDwArg32 = j;
          }
        }
        sub_41D610(this, (int ***)&pDwArg3, v10);
      }
      while ( pDwArg32 != pDwArg42 );
    }
    *pDwArg2 = pDwArg32;
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x41DB00 sub_41DB00 —— 同族实例三（回调 0x41CAE0）
// ------------------------------------------------------------
int **/*thiscall*/ sub_41DB00(int ***this, int **pDwArg2, int *pDwArg3, int *pDwArg4)
{
  int *pDwArg42; // ebx
  int *pDwArg32; // esi
  int fld_e1; // eax
  uint32_t *fld_e12; // eax
  int **v10; // ecx
  int **v11; // eax
  int *j; // eax
  int *i; // eax

  pDwArg42 = pDwArg4;
  pDwArg32 = pDwArg3;
  fld_e1 = (int)*(this + 1);
  if ( pDwArg3 == *(int **)fld_e1 && pDwArg4 == (int *)fld_e1 )
  {
    sub_41CAE0(*(void ***)(fld_e1 + 4));
    (*(this + 1))[1] = (int *)*(this + 1);
    fld_e12 = *(this + 1);
    *(this + 2) = nullptr;
    *fld_e12 = fld_e12;
    (*(this + 1))[2] = (int *)*(this + 1);
    *pDwArg2 = **(this + 1);
    return pDwArg2;
  }
  else
  {
    if ( pDwArg3 != pDwArg4 )
    {
      do
      {
        v10 = (int **)pDwArg32;
        if ( *((uint8_t *)pDwArg32 + 21) == 0 )
        {
          v11 = (int **)pDwArg32[2];
          if ( *((uint8_t *)v11 + 21) != 0 )
          {
            for ( i = (int *)pDwArg32[1]; *((uint8_t *)i + 21) == 0; i = (int *)i[1] )
            {
              if ( pDwArg32 != (int *)i[2] )
                break;
              pDwArg32 = i;
            }
            pDwArg32 = i;
          }
          else
          {
            pDwArg32 = (int *)pDwArg32[2];
            for ( j = *v11; *((uint8_t *)j + 21) == 0; j = (int *)*j )
              pDwArg32 = j;
          }
        }
        sub_41D610(this, (int ***)&pDwArg3, v10);
      }
      while ( pDwArg32 != pDwArg42 );
    }
    *pDwArg2 = pDwArg32;
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x41DBC0 sub_41DBC0 —— 同族实例四（回调 0x41CB20）
// ------------------------------------------------------------
int **/*thiscall*/ sub_41DBC0(int ***this, int **pDwArg2, int *pDwArg3, int *pDwArg4)
{
  int *pDwArg42; // ebx
  int *pDwArg32; // esi
  int fld_e1; // eax
  uint32_t *fld_e12; // eax
  int **v10; // ecx
  int **v11; // eax
  int *j; // eax
  int *i; // eax

  pDwArg42 = pDwArg4;
  pDwArg32 = pDwArg3;
  fld_e1 = (int)*(this + 1);
  if ( pDwArg3 == *(int **)fld_e1 && pDwArg4 == (int *)fld_e1 )
  {
    sub_41CB20(*(void ***)(fld_e1 + 4));
    (*(this + 1))[1] = (int *)*(this + 1);
    fld_e12 = *(this + 1);
    *(this + 2) = nullptr;
    *fld_e12 = fld_e12;
    (*(this + 1))[2] = (int *)*(this + 1);
    *pDwArg2 = **(this + 1);
    return pDwArg2;
  }
  else
  {
    if ( pDwArg3 != pDwArg4 )
    {
      do
      {
        v10 = (int **)pDwArg32;
        if ( *((uint8_t *)pDwArg32 + 21) == 0 )
        {
          v11 = (int **)pDwArg32[2];
          if ( *((uint8_t *)v11 + 21) != 0 )
          {
            for ( i = (int *)pDwArg32[1]; *((uint8_t *)i + 21) == 0; i = (int *)i[1] )
            {
              if ( pDwArg32 != (int *)i[2] )
                break;
              pDwArg32 = i;
            }
            pDwArg32 = i;
          }
          else
          {
            pDwArg32 = (int *)pDwArg32[2];
            for ( j = *v11; *((uint8_t *)j + 21) == 0; j = (int *)*j )
              pDwArg32 = j;
          }
        }
        sub_41D610(this, (int ***)&pDwArg3, v10);
      }
      while ( pDwArg32 != pDwArg42 );
    }
    *pDwArg2 = pDwArg32;
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x41DC80 sub_41DC80 —— vector<T 4B 驻留句柄> 拷贝赋值 operator=
//   自赋/空源 → 0x4017E0 清空；容量足 → 区间赋值(0x41C6A0) + 销毁多余(0x4016E0)；
//   容量不足 → 全销毁 + reserve(0x401950) + 拷贝构造(0x41D580)；夹层 → 覆盖前段(0x41CA00) + 追加(0x41CB60)。
// ------------------------------------------------------------
int /*thiscall*/ sub_41DC80(int this, int pArg2)
{
  unsigned int **v3; // ebx
  unsigned int v4; // ecx
  unsigned int **fld_4; // eax
  unsigned int fld_8; // edx
  void **v8; // eax
  int v9; // eax
  int fld_42; // ecx
  unsigned int fld_C; // edx
  int fld_82; // edx
  unsigned int **v13; // ebx
  int v14; // ecx
  unsigned int v15; // eax

  if ( this == pArg2 )
    return this;
  v3 = *(unsigned int ***)(pArg2 + 4);
  if ( v3 == nullptr || (v4 = (*(uint32_t *)(pArg2 + 8) - (int)v3) >> 2) == 0 )
  {
    sub_4017E0(this);
    return this;
  }
  fld_4 = *(unsigned int ***)(this + 4);
  if ( fld_4 != nullptr )
    fld_8 = (*(uint32_t *)(this + 8) - (int)fld_4) >> 2;
  else
    fld_8 = 0;
  if ( v4 <= fld_8 )
  {
    v8 = (void **)sub_41C6A0(v3, *(unsigned int ***)(pArg2 + 8), fld_4);
    sub_4016E0(v8, *(void ***)(this + 8));
    v9 = *(uint32_t *)(pArg2 + 4);
    if ( v9 != 0 )
      fld_42 = *(uint32_t *)(this + 4) + 4 * ((*(uint32_t *)(pArg2 + 8) - v9) >> 2);
    else
      fld_42 = *(uint32_t *)(this + 4);
    *(uint32_t *)(this + 8) = fld_42;
    return this;
  }
  if ( fld_4 != nullptr )
    fld_C = (*(uint32_t *)(this + 12) - (int)fld_4) >> 2;
  else
    fld_C = 0;
  if ( v4 > fld_C )
  {
    if ( fld_4 != nullptr )
    {
      sub_4016E0((void **)fld_4, *(void ***)(this + 8));
      j__free(*(void **)(this + 4));
    }
    v14 = *(uint32_t *)(pArg2 + 4);
    if ( v14 != 0 )
      v15 = (*(uint32_t *)(pArg2 + 8) - v14) >> 2;
    else
      v15 = 0;
    if ( sub_401950((uint32_t *)this, v15) != 0 )
      *(uint32_t *)(this + 8) = sub_41D580(
                                *(unsigned int ***)(pArg2 + 4),
                                *(unsigned int ***)(pArg2 + 8),
                                *(unsigned int ***)(this + 4));
    return this;
  }
  if ( fld_4 != nullptr )
    fld_82 = (*(uint32_t *)(this + 8) - (int)fld_4) >> 2;
  else
    fld_82 = 0;
  v13 = (unsigned int **)(*(uint32_t *)(pArg2 + 4) + 4 * fld_82);
  sub_41CA00(*(unsigned int ***)(pArg2 + 4), v13, *(unsigned int ***)(this + 4));
  *(uint32_t *)(this + 8) = sub_41CB60(v13, *(unsigned int ***)(pArg2 + 8), *(unsigned int ***)(this + 8));
  return this;
}



// ------------------------------------------------------------
// 0x41DDD0 sub_41DDD0 —— 区间析构（步长 144B 逐元素 0x41CBF0）
// ------------------------------------------------------------
void /*stdcall*/ sub_41DDD0(int nArg1, int nArg2)
{
  int i; // esi

  for ( i = nArg1; i != nArg2; i += 144 )
    sub_41CBF0(i);
}



// ------------------------------------------------------------
// 0x41DE00 sub_41DE00 —— 子数组构造（this+60 起 5 个 16B：构造 0x4019A0 / 析构 0x5E5260）
//   末尾 0x41D8D0 复位。
// ------------------------------------------------------------
void /*thiscall*/ sub_41DE00(char *this)
{
  `eh vector constructor iterator'(
    this + 60,
    0x10u,
    5,
    (void (/*thiscall*/ *)(void *))sub_4019A0,
    (void (/*thiscall*/ *)(void *))sub_5E5260);
  sub_41D8D0(this);
}



// ------------------------------------------------------------
// 0x41DE30 sub_41DE30 —— ★ CNEntranceChannel 构造
//   vftable CNEntranceChannel（+ IAppendDraw / off_6C2D00）；两大同型字段块（+196 与 +244，各含 {0, 6, 12, 0, 1600…} 面板参数）；
//   this+440 建 6 个 28B 定时器（0x401170）；this+616 建 6 个 140B 子对象（0x41DE00）；
//   +1744..+1748 四个索引初值 -1；挂接 0x46DE70 / 0x46F990。
// ------------------------------------------------------------
char */*thiscall*/ sub_41DE30(char *this)
{
  *(this + 4) = 0;
  *((uint32_t *)this + 2) = &nengine::IAppendDraw::`vftable';
  *(uint32_t *)this = &CNEntranceChannel::`vftable';
  *((uint32_t *)this + 2) = &off_6C2D00;
  *(this + 184) = 0;
  *(this + 185) = 0;
  *(this + 186) = 0;
  *(this + 187) = 0;
  *((uint32_t *)this + 49) = 0;
  *((uint32_t *)this + 50) = 6;
  *((uint32_t *)this + 51) = 12;
  *((uint32_t *)this + 52) = 0;
  *((uint32_t *)this + 53) = 1600;
  *((uint32_t *)this + 54) = 0;
  *((uint32_t *)this + 55) = 0;
  *((uint32_t *)this + 56) = 0;
  *((uint32_t *)this + 57) = 0;
  *((uint32_t *)this + 58) = 0;
  *(this + 236) = 0;
  *(this + 237) = 0;
  *(this + 238) = 0;
  *(this + 239) = 0;
  *((uint32_t *)this + 62) = 0;
  *((uint32_t *)this + 63) = 6;
  *((uint32_t *)this + 64) = 12;
  *((uint32_t *)this + 65) = 0;
  *((uint32_t *)this + 66) = 1600;
  *((uint32_t *)this + 67) = 0;
  *((uint32_t *)this + 68) = 0;
  *((uint32_t *)this + 69) = 0;
  *((uint32_t *)this + 70) = 0;
  *((uint32_t *)this + 71) = 0;
  *(this + 324) = 0;
  *((uint32_t *)this + 80) = &off_6C2B88;
  *((uint32_t *)this + 82) = 0;
  *(this + 332) = 1;
  *(this + 334) = 0;
  *(this + 333) = 0;
  *((uint32_t *)this + 86) = 0;
  *((uint32_t *)this + 85) = 0;
  *((uint32_t *)this + 84) = 0;
  *(this + 352) = 0;
  *((uint32_t *)this + 87) = &off_6C2B88;
  *((uint32_t *)this + 89) = 0;
  *(this + 360) = 1;
  *(this + 362) = 0;
  *(this + 361) = 0;
  *((uint32_t *)this + 93) = 0;
  *((uint32_t *)this + 92) = 0;
  *((uint32_t *)this + 91) = 0;
  *(this + 380) = 0;
  *((uint32_t *)this + 94) = &off_6C2B88;
  *((uint32_t *)this + 96) = 0;
  *(this + 388) = 1;
  *(this + 390) = 0;
  *(this + 389) = 0;
  *((uint32_t *)this + 100) = 0;
  *((uint32_t *)this + 99) = 0;
  *((uint32_t *)this + 98) = 0;
  *(this + 408) = 0;
  *((uint32_t *)this + 101) = &off_6C2B88;
  *((uint32_t *)this + 103) = 0;
  *(this + 416) = 1;
  *(this + 418) = 0;
  *(this + 417) = 0;
  *((uint32_t *)this + 107) = 0;
  *((uint32_t *)this + 106) = 0;
  *((uint32_t *)this + 105) = 0;
  `eh vector constructor iterator'(
    this + 440,
    0x1Cu,
    6,
    (void (/*thiscall*/ *)(void *))sub_401170,
    (void (/*thiscall*/ *)(void *))sub_401000);
  `eh vector constructor iterator'(
    this + 616,
    0x8Cu,
    6,
    (void (/*thiscall*/ *)(void *))sub_41DE00,
    (void (/*thiscall*/ *)(void *))sub_41D910);
  *((uint32_t *)this + 436) = 0;
  *((uint32_t *)this + 432) = -1;
  *((uint32_t *)this + 433) = -1;
  *((uint32_t *)this + 434) = -1;
  *((uint32_t *)this + 435) = -1;
  sub_46DE70(this);
  sub_46F990((int)this);
  return this;
}



// ------------------------------------------------------------
// 0x41E090 sub_41E090 —— CNEntranceChannel 标量删除析构（0x41E0C0 + flag&1 free）
// ------------------------------------------------------------
void */*thiscall*/ sub_41E090(void *Block, char pszArg2)
{
  sub_41E0C0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x41E0C0 sub_41E0C0 —— CNEntranceChannel 析构
//   vftable 复位 + 0x46DF70 频道对象析构（含临界区释放）；6 子对象(0x41D910) 与 6 定时器(0x401000) 析构；
//   四个子模块 vftable 回落 nengine::IObject；DeleteObject 释放两个 GDI 对象（+228/+280）；
//   随后大段字段清零并自身回落 IObject。
// ------------------------------------------------------------
int /*thiscall*/ sub_41E0C0(char *this)
{
  int result; // eax

  *(uint32_t *)this = &CNEntranceChannel::`vftable';
  *((uint32_t *)this + 2) = &off_6C2D00;
  sub_46DF70();
  `eh vector destructor iterator'(this + 616, 0x8Cu, 6, (void (/*thiscall*/ *)(void *))sub_41D910);
  `eh vector destructor iterator'(this + 440, 0x1Cu, 6, (void (/*thiscall*/ *)(void *))sub_401000);
  *(this + 408) = 0;
  *((uint32_t *)this + 101) = &nengine::IObject::`vftable';
  *((uint32_t *)this + 94) = &nengine::IObject::`vftable';
  *(this + 380) = 0;
  *((uint32_t *)this + 87) = &nengine::IObject::`vftable';
  *(this + 352) = 0;
  *((uint32_t *)this + 80) = &nengine::IObject::`vftable';
  *(this + 324) = 0;
  if ( *((uint32_t *)this + 70) != 0 )
  {
    DeleteObject(*((HGDIOBJ *)this + 70));
    *((uint32_t *)this + 70) = 0;
  }
  *(this + 236) = 0;
  *(this + 237) = 0;
  *(this + 238) = 0;
  *(this + 239) = 0;
  *((uint32_t *)this + 62) = 0;
  *((uint32_t *)this + 63) = 0;
  *((uint32_t *)this + 64) = 0;
  *((uint32_t *)this + 65) = 0;
  *((uint32_t *)this + 66) = 0;
  *((uint32_t *)this + 67) = 0;
  *((uint32_t *)this + 68) = 0;
  *((uint32_t *)this + 69) = 0;
  *((uint32_t *)this + 70) = 0;
  *((uint32_t *)this + 71) = 0;
  result = *((uint32_t *)this + 57);
  if ( result != 0 )
  {
    result = DeleteObject(*((HGDIOBJ *)this + 57));
    *((uint32_t *)this + 57) = 0;
  }
  *(this + 184) = 0;
  *(this + 185) = 0;
  *(this + 186) = 0;
  *(this + 187) = 0;
  *((uint32_t *)this + 49) = 0;
  *((uint32_t *)this + 50) = 0;
  *((uint32_t *)this + 51) = 0;
  *((uint32_t *)this + 52) = 0;
  *((uint32_t *)this + 53) = 0;
  *((uint32_t *)this + 54) = 0;
  *((uint32_t *)this + 55) = 0;
  *((uint32_t *)this + 56) = 0;
  *((uint32_t *)this + 57) = 0;
  *((uint32_t *)this + 58) = 0;
  *(uint32_t *)this = &nengine::IObject::`vftable';
  *(this + 4) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x41E260 sub_41E260 —— map 清空（全区间擦除 + free 表头）
//   0x41D980 擦除 [begin, end) 后 free 表头结点并把三字段清零，返回 0。
// ------------------------------------------------------------
int /*thiscall*/ sub_41E260(int this)
{
  int *v3; // [esp+4h] [ebp-4h] BYREF

  sub_41D980((int ***)this, &v3, **(int ***)(this + 4), *(int **)(this + 4));
  j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x41E2A0 sub_41E2A0 —— ★ CNSelectDungeonModule 构造
//   vftable × 2（CNSelectDungeonModule）+ IAppendDraw；四组 12B 子容器（off_6C2B88 同型块）；
//   this+84 建 2 个 28B 定时器；末尾 0x454BC0 副本界面状态复位 + 0x454360 副本选择界面构造。
// ------------------------------------------------------------
char */*thiscall*/ sub_41E2A0(char *this)
{
  *(this + 4) = 0;
  *((uint32_t *)this + 2) = &nengine::IAppendDraw::`vftable';
  *(uint32_t *)this = &CNSelectDungeonModule::`vftable';
  *((uint32_t *)this + 2) = &CNSelectDungeonModule::`vftable';
  *(this + 44) = 0;
  *((uint32_t *)this + 10) = &off_6C2B88;
  *((uint32_t *)this + 12) = 0;
  *(this + 52) = 1;
  *(this + 54) = 0;
  *(this + 53) = 0;
  *((uint32_t *)this + 16) = 0;
  *((uint32_t *)this + 15) = 0;
  *((uint32_t *)this + 14) = 0;
  `eh vector constructor iterator'(
    this + 84,
    0x1Cu,
    2,
    (void (/*thiscall*/ *)(void *))sub_401170,
    (void (/*thiscall*/ *)(void *))sub_401000);
  *(this + 156) = 0;
  *((uint32_t *)this + 38) = &off_6C2B88;
  *((uint32_t *)this + 40) = 0;
  *(this + 164) = 1;
  *(this + 166) = 0;
  *(this + 165) = 0;
  *((uint32_t *)this + 44) = 0;
  *((uint32_t *)this + 43) = 0;
  *((uint32_t *)this + 42) = 0;
  *(this + 188) = 0;
  *((uint32_t *)this + 46) = &off_6C2B88;
  *((uint32_t *)this + 48) = 0;
  *(this + 196) = 1;
  *(this + 198) = 0;
  *(this + 197) = 0;
  *((uint32_t *)this + 52) = 0;
  *((uint32_t *)this + 51) = 0;
  *((uint32_t *)this + 50) = 0;
  *(this + 244) = 0;
  *((uint32_t *)this + 60) = &off_6C2B88;
  *((uint32_t *)this + 62) = 0;
  *(this + 252) = 1;
  *(this + 254) = 0;
  *(this + 253) = 0;
  *((uint32_t *)this + 66) = 0;
  *((uint32_t *)this + 65) = 0;
  *((uint32_t *)this + 64) = 0;
  *((uint32_t *)this + 69) = 0;
  *((uint32_t *)this + 70) = 0;
  *((uint32_t *)this + 71) = 0;
  sub_454BC0((int)this);
  sub_454360(this);
  return this;
}



// ------------------------------------------------------------
// 0x41E400 sub_41E400 —— CNSelectDungeonModule 删除析构（thunk 尾 free）
//   先调 0x41E430 析构本体；pszArg2 & 1 时 j__free 释放对象自身（标量删除析构器惯用形）。
// ------------------------------------------------------------
void */*thiscall*/ sub_41E400(void *Block, char pszArg2)
{
  sub_41E430();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x41E430 sub_41E430 —— CNSelectDungeonModule 析构
//   双 vftable 归位 + 0x4539D0 界面对象析构；释放 this+69 矢量字段；三级 IObject 子对象
//   （this+240/+184/+152）复位；this+84 起 2 个 28B 子项区间析构（0x401000）。
// ------------------------------------------------------------
void /*thiscall*/ sub_41E430(char *this)
{
  *(uint32_t *)this = &CNSelectDungeonModule::`vftable';
  *((uint32_t *)this + 2) = &CNSelectDungeonModule::`vftable';
  sub_4539D0();
  if ( *((uint32_t *)this + 69) != 0 )
    j__free(*((void **)this + 69));
  *((uint32_t *)this + 69) = 0;
  *((uint32_t *)this + 70) = 0;
  *((uint32_t *)this + 71) = 0;
  *((uint32_t *)this + 60) = &nengine::IObject::`vftable';
  *(this + 244) = 0;
  *((uint32_t *)this + 46) = &nengine::IObject::`vftable';
  *(this + 188) = 0;
  *((uint32_t *)this + 38) = &nengine::IObject::`vftable';
  *(this + 156) = 0;
  `eh vector destructor iterator'(this + 84, 0x1Cu, 2, (void (/*thiscall*/ *)(void *))sub_401000);
  *((uint32_t *)this + 10) = &nengine::IObject::`vftable';
  *(this + 44) = 0;
  *(uint32_t *)this = &nengine::IObject::`vftable';
  *(this + 4) = 0;
}



// ============================================================
// SECTION 0x41E4F0 — 服务器连接 UI 状态（"Connect to Server..."/"Connection Failed"）
// ============================================================
// ------------------------------------------------------------
// 0x41E4F0 sub_41E4F0
// ------------------------------------------------------------
// 【解读】
//   服务器连接 UI 状态机: "Connect to Server..." → j__atol 端口解析 + sub_4231B0 连接发起 +
//     sub_698F90 超时时钟；失败路径 "Connection Failed"（off_77F3FC 日志）。
// ------------------------------------------------------------
int /*thiscall*/ sub_41E4F0(uint8_t *this, int pArg2)  // 【服务器连接 UI 状态（Connect to Server.../Connectio…】
{
  const char *psz; // edi
  const char *v4; // eax
  int v5; // esi
  char v7; // cl
  char v8; // cl

  sub_41DC80((int)(this + 268), pArg2);
  psz = sub_41ACF0((unsigned int **)(*(uint32_t *)(pArg2 + 4) + 4));
  v4 = sub_41ACF0((unsigned int **)(*(uint32_t *)(pArg2 + 4) + 8));
  v5 = j__atol(v4);
  if ( strlen(psz) <= 0xF )
  {
    off_77F3FC((char *)&byte_6C2D68, psz, v5);
    *(uint32_t *)(dword_79C0A0 + 128) = dword_8F7B08;
    if ( sub_4231B0((char)psz, v5) >= 0 )
    {
      sub_4052D0();  // 【tick_domains_step】
      *(this + 60) = 1;
      *(this + 61) = 0;
      *(this + 62) = 0;
      sub_698F90((int)(this + 48), 600000, 0);  // 【clock_set_countdown(clk, duration=a2, star…】
      off_77F3F8(v8, "Connect to Server...");
      return 1;
    }
    else
    {
      off_77F3F8(v7, "Connection Failed");
      *(uint32_t *)(dword_79C0A0 + 128) = 0;
      return -2147483564;
    }
  }
  else
  {
    off_77F3FC((char *)&byte_6C2D88, strlen(psz), psz);
    return 0x80000000;
  }
}



// ------------------------------------------------------------
// 0x41E600 sub_41E600 —— 矢量清空（步长 144B 逐元素 0x41CBF0 成员析构）
//   遍历 [begin,end) 逐元素调 0x41CBF0，再 free 表头结点并把三字段归零。
// ------------------------------------------------------------
int /*thiscall*/ sub_41E600(int *this)
{
  int fld_e1; // esi
  int result; // eax
  int i; // edi

  fld_e1 = *(this + 1);
  result = 0;
  if ( fld_e1 != 0 )
  {
    for ( i = *(this + 2); fld_e1 != i; fld_e1 += 144 )
      sub_41CBF0(fld_e1);
    j__free((void *)*(this + 1));
    result = 0;
  }
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x41E650 sub_41E650 —— map 清空（0x41DA40 全区间擦除）
//   0x41DA40 为树 erase 同族实例二（节点回调 0x41CAA0）；随后 free 表头、三字段归零。
// ------------------------------------------------------------
int /*thiscall*/ sub_41E650(int this)
{
  int *v3; // [esp+4h] [ebp-4h] BYREF

  sub_41DA40((int ***)this, &v3, **(int ***)(this + 4), *(int **)(this + 4));
  j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x41E690 sub_41E690 —— map 清空（0x41DB00 全区间擦除）
//   0x41DB00 为树 erase 同族实例三（节点回调 0x41CAE0）；随后 free 表头、三字段归零。
// ------------------------------------------------------------
int /*thiscall*/ sub_41E690(int this)
{
  int *v3; // [esp+4h] [ebp-4h] BYREF

  sub_41DB00((int ***)this, &v3, **(int ***)(this + 4), *(int **)(this + 4));
  j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x41E6D0 sub_41E6D0 —— map 清空（0x41DBC0 全区间擦除）
//   0x41DBC0 为树 erase 同族实例四（节点回调 0x41CB20）；随后 free 表头、三字段归零。
// ------------------------------------------------------------
int /*thiscall*/ sub_41E6D0(int this)
{
  int *v3; // [esp+4h] [ebp-4h] BYREF

  sub_41DBC0((int ***)this, &v3, **(int ***)(this + 4), *(int **)(this + 4));
  j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x41E710 sub_41E710
// ------------------------------------------------------------
// attributes: thunk
int /*thiscall*/ sub_41E710(int *this)
{
  return sub_41E600(this);
}



// ------------------------------------------------------------
// 0x41E720 sub_41E720 [串: "invalid map/set<T> iterator"]
// ------------------------------------------------------------
int ***/*thiscall*/ sub_41E720(uint32_t *this, int ***uArg2, int **pDwArg3)
{
  int **pDwArg32; // ebx
  int *v4; // edi
  int *v5; // ecx
  int *v6; // esi
  uint32_t *pThis2; // ecx
  int v8; // eax
  int *v9; // eax
  int v10; // ecx
  bool v11; // zf
  int v12; // eax
  int **v13; // eax
  char v14; // al
  uint32_t *pThis3; // ecx
  uint32_t *v16; // eax
  uint32_t *Block2; // eax
  int v18; // eax
  void *Block3; // [esp-4h] [ebp-64h]
  uint32_t pExceptionObject[10]; // [esp+4h] [ebp-5Ch] BYREF
  uint8_t v22[20]; // [esp+2Ch] [ebp-34h] BYREF
  int v23; // [esp+40h] [ebp-20h]
  int v24; // [esp+44h] [ebp-1Ch]
  int v25; // [esp+48h] [ebp-18h]
  void *Block; // [esp+4Ch] [ebp-14h]
  uint32_t *pThis; // [esp+50h] [ebp-10h]
  int v28; // [esp+5Ch] [ebp-4h]

  pThis = this;
  if ( *((uint8_t *)pDwArg3 + 33) != 0 )
  {
    v24 = 15;
    v23 = 0;
    v22[4] = 0;
    sub_4015C0("invalid map/set<T> iterator", 0x1Bu);  // 【std::string构造赋值】
    v28 = 0;
    sub_401740(pExceptionObject, (int)v22);
    pExceptionObject[0] = &std::out_of_range::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
  }
  pDwArg32 = pDwArg3;
  Block = pDwArg3;
  sub_41C640(&pDwArg3);
  if ( *((uint8_t *)*pDwArg32 + 33) != 0 )
  {
    v4 = pDwArg32[2];
LABEL_8:
    v6 = pDwArg32[1];
    if ( *((uint8_t *)v4 + 33) == 0 )
      v4[1] = (int)v6;
    pThis2 = pThis;
    v8 = pThis[1];
    if ( *(int ***)(v8 + 4) == pDwArg32 )
    {
      *(uint32_t *)(v8 + 4) = v4;
    }
    else if ( (int **)*v6 == pDwArg32 )
    {
      *v6 = (int)v4;
    }
    else
    {
      v6[2] = (int)v4;
    }
    if ( *(int ***)pThis2[1] == pDwArg32 )
    {
      if ( *((uint8_t *)v4 + 33) != 0 )
      {
        v9 = v6;
      }
      else
      {
        v9 = (int *)sub_41C5C0(v4);
        pThis2 = pThis;
      }
      *(uint32_t *)pThis2[1] = v9;
    }
    v10 = pThis2[1];
    v11 = *(uint32_t *)(v10 + 8) == (uint32_t)pDwArg32;
    v25 = v10;
    if ( v11 )
    {
      if ( *((uint8_t *)v4 + 33) != 0 )
        *(uint32_t *)(v10 + 8) = v6;
      else
        *(uint32_t *)(v25 + 8) = sub_433210(v4);
    }
    goto LABEL_35;
  }
  if ( *((uint8_t *)pDwArg32[2] + 33) != 0 )
  {
    v4 = *pDwArg32;
    goto LABEL_8;
  }
  v5 = (int *)pDwArg3;
  v4 = pDwArg3[2];
  if ( pDwArg3 == pDwArg32 )
    goto LABEL_8;
  (*pDwArg32)[1] = (int)pDwArg3;
  *v5 = (int)*pDwArg32;
  if ( v5 == pDwArg32[2] )
  {
    v6 = v5;
  }
  else
  {
    v6 = (int *)v5[1];
    if ( *((uint8_t *)v4 + 33) == 0 )
      v4[1] = (int)v6;
    *v6 = (int)v4;
    v5[2] = (int)pDwArg32[2];
    pDwArg32[2][1] = (int)v5;
  }
  v12 = pThis[1];
  if ( *(int ***)(v12 + 4) == pDwArg32 )
  {
    *(uint32_t *)(v12 + 4) = v5;
  }
  else
  {
    v13 = (int **)pDwArg32[1];
    if ( *v13 == (int *)pDwArg32 )
      *v13 = v5;
    else
      v13[2] = v5;
  }
  v5[1] = (int)pDwArg32[1];
  v14 = *((uint8_t *)v5 + 32);
  *((uint8_t *)v5 + 32) = *((uint8_t *)pDwArg32 + 32);
  *((uint8_t *)pDwArg32 + 32) = v14;
LABEL_35:
  if ( *((uint8_t *)Block + 32) == 1 )
  {
    pThis3 = pThis;
    if ( v4 != *(int **)(pThis[1] + 4) )
    {
      do
      {
        if ( *((uint8_t *)v4 + 32) != 1 )
          break;
        v16 = (uint32_t *)*v6;
        if ( v4 == (int *)*v6 )
        {
          v16 = (uint32_t *)v6[2];
          if ( *((uint8_t *)v16 + 32) == 0 )
          {
            *((uint8_t *)v16 + 32) = 1;
            *((uint8_t *)v6 + 32) = 0;
            sub_4331B0(v6);
            v16 = (uint32_t *)v6[2];
            pThis3 = pThis;
          }
          if ( *((uint8_t *)v16 + 33) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(*v16 + 32) != 1 || *(uint8_t *)(v16[2] + 32) != 1 )
          {
            if ( *(uint8_t *)(v16[2] + 32) == 1 )
            {
              *(uint8_t *)(*v16 + 32) = 1;
              *((uint8_t *)v16 + 32) = 0;
              sub_433230(v16);
              v16 = (uint32_t *)v6[2];
            }
            *((uint8_t *)v16 + 32) = *((uint8_t *)v6 + 32);
            *((uint8_t *)v6 + 32) = 1;
            *(uint8_t *)(v16[2] + 32) = 1;
            sub_4331B0(v6);
            break;
          }
        }
        else
        {
          if ( *((uint8_t *)v16 + 32) == 0 )
          {
            *((uint8_t *)v16 + 32) = 1;
            *((uint8_t *)v6 + 32) = 0;
            sub_433230(v6);
            v16 = (uint32_t *)*v6;
            pThis3 = pThis;
          }
          if ( *((uint8_t *)v16 + 33) != 0 )
            goto LABEL_53;
          if ( *(uint8_t *)(v16[2] + 32) != 1 || *(uint8_t *)(*v16 + 32) != 1 )
          {
            if ( *(uint8_t *)(*v16 + 32) == 1 )
            {
              *(uint8_t *)(v16[2] + 32) = 1;
              *((uint8_t *)v16 + 32) = 0;
              sub_4331B0(v16);
              v16 = (uint32_t *)*v6;
            }
            *((uint8_t *)v16 + 32) = *((uint8_t *)v6 + 32);
            *((uint8_t *)v6 + 32) = 1;
            *(uint8_t *)(*v16 + 32) = 1;
            sub_433230(v6);
            break;
          }
        }
        *((uint8_t *)v16 + 32) = 0;
LABEL_53:
        v4 = v6;
        v11 = v6 == *(int **)(pThis3[1] + 4);
        v6 = (int *)v6[1];
      }
      while ( !v11 );
    }
    *((uint8_t *)v4 + 32) = 1;
  }
  if ( *((uint32_t *)Block + 5) != 0 )
    j__free(*((void **)Block + 5));
  Block2 = Block;
  Block3 = Block;
  *((uint32_t *)Block + 5) = 0;
  Block2[6] = 0;
  Block2[7] = 0;
  j__free(Block3);
  v18 = pThis[2];
  if ( v18 != 0 )
    pThis[2] = v18 - 1;
  *uArg2 = pDwArg3;
  return uArg2;
}


// ------------------------------------------------------------
// 0x41EA00 sub_41EA00 —— 红黑树整树递归析构
//   节点非哨兵（+33 为 0）时后序遍历：先递归右子树，再 0x4CEB50 成员清理【推断】，最后 free 本节点。
// ------------------------------------------------------------
char /*stdcall*/ sub_41EA00(void **Block)
{
  void **Block2; // edi
  char result; // al
  void **i; // esi

  Block2 = Block;
  result = *((uint8_t *)Block + 33);
  for ( i = Block; result == 0; Block2 = i )
  {
    sub_41EA00(i[2]);
    i = (void **)*i;
    sub_4CEB50(Block2);
    j__free(Block2);
    result = *((uint8_t *)i + 33);
  }
  return result;
}



// ------------------------------------------------------------
// 0x41EA50 sub_41EA50 —— CNPVPModule 构造
//   vftable 双基 + off_6C2DB4/off_6C2B88 头；this+68 建哨兵 map（0x18 节点）；
//   0x4525D0 槽表状态复位 + 0x452C50 后续初始化，返回 this。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_41EA50(uint8_t *this)
{
  char *pThis_44; // edi
  int pThis_442; // eax

  *(this + 4) = 0;
  *((uint32_t *)this + 2) = &nengine::IAppendDraw::`vftable';
  *(uint32_t *)this = &CNPVPModule::`vftable';
  *((uint32_t *)this + 2) = &off_6C2DB4;
  *(this + 44) = 0;
  *((uint32_t *)this + 10) = &off_6C2B88;
  *((uint32_t *)this + 12) = 0;
  *(this + 52) = 1;
  *(this + 54) = 0;
  *(this + 53) = 0;
  *((uint32_t *)this + 16) = 0;
  *((uint32_t *)this + 15) = 0;
  *((uint32_t *)this + 14) = 0;
  pThis_44 = this + 68;
  pThis_442 = sub_433AC0(this + 68);
  *((uint32_t *)pThis_44 + 1) = pThis_442;
  *(uint8_t *)(pThis_442 + 21) = 1;
  *(uint32_t *)(*((uint32_t *)pThis_44 + 1) + 4) = *((uint32_t *)pThis_44 + 1);
  **((uint32_t **)pThis_44 + 1) = *((uint32_t *)pThis_44 + 1);
  *(uint32_t *)(*((uint32_t *)pThis_44 + 1) + 8) = *((uint32_t *)pThis_44 + 1);
  *((uint32_t *)pThis_44 + 2) = 0;
  sub_4525D0(this);
  sub_452C50(this);
  return this;
}



// ------------------------------------------------------------
// 0x41EB00 sub_41EB00 —— CNPVPModule 删除析构（thunk 尾 free）
//   先调 0x41EB30 析构本体；pszArg2 & 1 时 j__free 释放对象自身。
// ------------------------------------------------------------
void */*thiscall*/ sub_41EB00(void *Block, char pszArg2)
{
  sub_41EB30();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x41EB30 sub_41EB30 —— CNPVPModule 析构
//   0x452FA0 场景容器析构；this+68 map 经 0x41DA40 全区间擦除 + free 表头；
//   this+40/this+0 依次归位 IObject vftable，返回 0。
// ------------------------------------------------------------
int /*thiscall*/ sub_41EB30(int this)
{
  int *v3; // [esp-8h] [ebp-24h]
  int *fld_48; // [esp-4h] [ebp-20h]
  int *v5[2]; // [esp+8h] [ebp-14h] BYREF
  int v6; // [esp+18h] [ebp-4h]

  v5[1] = (int *)this;
  *(uint32_t *)this = &CNPVPModule::`vftable';
  *(uint32_t *)(this + 8) = &off_6C2DB4;
  v6 = 2;
  sub_452FA0();
  v4 = *(int **)(this + 72);
  v3 = (int *)*v4;
  LOBYTE(v6) = 1;
  sub_41DA40((int ***)(this + 68), v5, v3, v4);
  j__free(*(void **)(this + 72));
  *(uint32_t *)(this + 72) = 0;
  *(uint32_t *)(this + 76) = 0;
  *(uint32_t *)(this + 40) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 44) = 0;
  *(uint32_t *)this = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 4) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x41EBC0 sub_41EBC0 —— CNEntranceModule 构造
//   vftable + 面板参数块（+34=6 / +35=12 / +37=1600）；0x46AE70 管理器状态批量复位；
//   0x46D4A0 选角界面控件构建。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_41EBC0(uint8_t *this)
{
  *(this + 4) = 0;
  *((uint32_t *)this + 2) = &nengine::IAppendDraw::`vftable';
  *(uint32_t *)this = &CNEntranceModule::`vftable';
  *((uint32_t *)this + 2) = &CNEntranceModule::`vftable';
  *(this + 20) = 0;
  *((uint32_t *)this + 4) = &off_6C2B88;
  *((uint32_t *)this + 6) = 0;
  *(this + 28) = 1;
  *(this + 30) = 0;
  *(this + 29) = 0;
  *((uint32_t *)this + 10) = 0;
  *((uint32_t *)this + 9) = 0;
  *((uint32_t *)this + 8) = 0;
  *((uint32_t *)this + 16) = 0;
  *((uint32_t *)this + 17) = 0;
  *((uint32_t *)this + 18) = 0;
  *((uint32_t *)this + 20) = 0;
  *((uint32_t *)this + 21) = 0;
  *((uint32_t *)this + 22) = 0;
  *(this + 120) = 0;
  *(this + 121) = 0;
  *(this + 122) = 0;
  *(this + 123) = 0;
  *((uint32_t *)this + 33) = 0;
  *((uint32_t *)this + 34) = 6;
  *((uint32_t *)this + 35) = 12;
  *((uint32_t *)this + 36) = 0;
  *((uint32_t *)this + 37) = 1600;
  *((uint32_t *)this + 38) = 0;
  *((uint32_t *)this + 39) = 0;
  *((uint32_t *)this + 40) = 0;
  *((uint32_t *)this + 41) = 0;
  *((uint32_t *)this + 42) = 0;
  sub_46AE70();
  sub_46D4A0((int)this);
  return this;
}



// ------------------------------------------------------------
// 0x41ECB0 sub_41ECB0 —— CNEntranceModule 删除析构（thunk 尾 free）
//   先调 0x41ECE0 析构本体；pszArg2 & 1 时 j__free 释放对象自身。
// ------------------------------------------------------------
void */*thiscall*/ sub_41ECB0(void *Block, char pszArg2)
{
  sub_41ECE0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x41ECE0 sub_41ECE0 —— CNEntranceModule 析构
//   0x46BED0 控件逐槽析构 + DeleteObject 释放 this+164 GDI 句柄；字段批量清空；
//   this+76 矢量经 0x41E600 清空（步长 144B）。
// ------------------------------------------------------------
void /*thiscall*/ sub_41ECE0(void *this)
{
  *(uint32_t *)this = &CNEntranceModule::`vftable';
  *((uint32_t *)this + 2) = &CNEntranceModule::`vftable';
  sub_46BED0();
  if ( *((uint32_t *)this + 41) != 0 )
  {
    DeleteObject(*((HGDIOBJ *)this + 41));
    *((uint32_t *)this + 41) = 0;
  }
  *((uint8_t *)this + 120) = 0;
  *((uint8_t *)this + 121) = 0;
  *((uint8_t *)this + 122) = 0;
  *((uint8_t *)this + 123) = 0;
  *((uint32_t *)this + 33) = 0;
  *((uint32_t *)this + 34) = 0;
  *((uint32_t *)this + 35) = 0;
  *((uint32_t *)this + 36) = 0;
  *((uint32_t *)this + 37) = 0;
  *((uint32_t *)this + 38) = 0;
  *((uint32_t *)this + 39) = 0;
  *((uint32_t *)this + 40) = 0;
  *((uint32_t *)this + 41) = 0;
  *((uint32_t *)this + 42) = 0;
  sub_41E600((int *)this + 19);
  if ( *((uint32_t *)this + 16) != 0 )
    j__free(*((void **)this + 16));
  *((uint32_t *)this + 16) = 0;
  *((uint32_t *)this + 17) = 0;
  *((uint32_t *)this + 18) = 0;
  *((uint8_t *)this + 20) = 0;
  *((uint32_t *)this + 4) = &nengine::IObject::`vftable';
  *((uint8_t *)this + 4) = 0;
  *(uint32_t *)this = &nengine::IObject::`vftable';
}



// ------------------------------------------------------------
// 0x41EDD0 sub_41EDD0 —— CNWarRoomModule 构造
//   vftable + this+64 哨兵 map；两组同型控件块（+96 与 +156 的 off_6C2B88 头/可见标志/矢量）；
//   0x42B4C0 玩家实体字段复位 + 0x42EBD0 惰性初始化。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_41EDD0(uint8_t *this)
{
  char *pThis_40; // edi
  int pThis_402; // eax

  *(this + 4) = 0;
  *((uint32_t *)this + 2) = &nengine::IAppendDraw::`vftable';
  *(uint32_t *)this = &CNWarRoomModule::`vftable';
  *((uint32_t *)this + 2) = &CNWarRoomModule::`vftable';
  *(this + 40) = 0;
  *((uint32_t *)this + 9) = &off_6C2B88;
  *((uint32_t *)this + 11) = 0;
  *(this + 48) = 1;
  *(this + 50) = 0;
  *(this + 49) = 0;
  *((uint32_t *)this + 15) = 0;
  *((uint32_t *)this + 14) = 0;
  *((uint32_t *)this + 13) = 0;
  pThis_40 = this + 64;
  pThis_402 = sub_433AC0(this + 64);
  *((uint32_t *)pThis_40 + 1) = pThis_402;
  *(uint8_t *)(pThis_402 + 21) = 1;
  *(uint32_t *)(*((uint32_t *)pThis_40 + 1) + 4) = *((uint32_t *)pThis_40 + 1);
  **((uint32_t **)pThis_40 + 1) = *((uint32_t *)pThis_40 + 1);
  *(uint32_t *)(*((uint32_t *)pThis_40 + 1) + 8) = *((uint32_t *)pThis_40 + 1);
  *((uint32_t *)pThis_40 + 2) = 0;
  *(this + 100) = 0;
  *((uint32_t *)this + 24) = &off_6C2B88;
  *((uint32_t *)this + 26) = 0;
  *(this + 108) = 1;
  *(this + 110) = 0;
  *(this + 109) = 0;
  *((uint32_t *)this + 30) = 0;
  *((uint32_t *)this + 29) = 0;
  *((uint32_t *)this + 28) = 0;
  *((uint32_t *)this + 35) = 0;
  *((uint32_t *)this + 36) = 0;
  *((uint32_t *)this + 37) = 0;
  *(this + 160) = 0;
  *((uint32_t *)this + 39) = &off_6C2B88;
  *((uint32_t *)this + 41) = 0;
  *(this + 168) = 1;
  *(this + 170) = 0;
  *(this + 169) = 0;
  *((uint32_t *)this + 45) = 0;
  *((uint32_t *)this + 44) = 0;
  *((uint32_t *)this + 43) = 0;
  sub_42B4C0(this);
  sub_42EBD0(this);
  return this;
}



// ------------------------------------------------------------
// 0x41EEF0 sub_41EEF0 —— CNWarRoomModule 删除析构（thunk 尾 free）
//   先调 0x41EF20 析构本体；pszArg2 & 1 时 j__free 释放对象自身。
// ------------------------------------------------------------
void */*thiscall*/ sub_41EEF0(void *Block, char pszArg2)
{
  sub_41EF20();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x41EF20 sub_41EF20 —— CNWarRoomModule 析构
//   0x42F0D0 模块销毁；释放 this+140 矢量；this+64 map 经 0x41DA40 擦除 + free 表头；
//   this+156/this+96 归位 IObject vftable。
// ------------------------------------------------------------
void /*thiscall*/ sub_41EF20(int this)
{
  int *v2; // [esp-8h] [ebp-28h]
  int *fld_44; // [esp-4h] [ebp-24h]
  int *v4[2]; // [esp+Ch] [ebp-14h] BYREF
  int v5; // [esp+1Ch] [ebp-4h]

  v4[1] = (int *)this;
  *(uint32_t *)this = &CNWarRoomModule::`vftable';
  *(uint32_t *)(this + 8) = &CNWarRoomModule::`vftable';
  v5 = 5;
  sub_42F0D0();
  *(uint32_t *)(this + 156) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 160) = 0;
  if ( *(uint32_t *)(this + 140) != 0 )
    j__free(*(void **)(this + 140));
  *(uint32_t *)(this + 140) = 0;
  *(uint32_t *)(this + 144) = 0;
  *(uint32_t *)(this + 148) = 0;
  *(uint32_t *)(this + 96) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 100) = 0;
  fld_44 = *(int **)(this + 68);
  v2 = (int *)*fld_44;
  LOBYTE(v5) = 1;
  sub_41DA40((int ***)(this + 64), v4, v2, fld_44);
  j__free(*(void **)(this + 68));
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 72) = 0;
  *(uint8_t *)(this + 40) = 0;
  *(uint32_t *)(this + 36) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 4) = 0;
  *(uint32_t *)this = &nengine::IObject::`vftable';
}



// ------------------------------------------------------------
// 0x41EFF0 sub_41EFF0 —— CNChaosModule 构造
//   vftable + this+76 哨兵 map；两组同型控件块（+48 与 +100 的 off_6C2B88 头）；
//   0x487AB0 CNChaosModule 状态块初始化 + 0x488160 战场模块延迟初始化。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_41EFF0(uint8_t *this)
{
  char *pThis_4C; // edi
  int pThis_4C2; // eax

  *(this + 4) = 0;
  *((uint32_t *)this + 2) = &nengine::IAppendDraw::`vftable';
  *(uint32_t *)this = &CNChaosModule::`vftable';
  *((uint32_t *)this + 2) = &CNChaosModule::`vftable';
  *(this + 52) = 0;
  *((uint32_t *)this + 12) = &off_6C2B88;
  *((uint32_t *)this + 14) = 0;
  *(this + 60) = 1;
  *(this + 62) = 0;
  *(this + 61) = 0;
  *((uint32_t *)this + 18) = 0;
  *((uint32_t *)this + 17) = 0;
  *((uint32_t *)this + 16) = 0;
  pThis_4C = this + 76;
  pThis_4C2 = sub_433AC0(this + 76);
  *((uint32_t *)pThis_4C + 1) = pThis_4C2;
  *(uint8_t *)(pThis_4C2 + 21) = 1;
  *(uint32_t *)(*((uint32_t *)pThis_4C + 1) + 4) = *((uint32_t *)pThis_4C + 1);
  **((uint32_t **)pThis_4C + 1) = *((uint32_t *)pThis_4C + 1);
  *(uint32_t *)(*((uint32_t *)pThis_4C + 1) + 8) = *((uint32_t *)pThis_4C + 1);
  *((uint32_t *)pThis_4C + 2) = 0;
  *(this + 104) = 0;
  *((uint32_t *)this + 25) = &off_6C2B88;
  *((uint32_t *)this + 27) = 0;
  *(this + 112) = 1;
  *(this + 114) = 0;
  *(this + 113) = 0;
  *((uint32_t *)this + 31) = 0;
  *((uint32_t *)this + 30) = 0;
  *((uint32_t *)this + 29) = 0;
  sub_487AB0(this);
  sub_488160(this);
  return this;
}



// ------------------------------------------------------------
// 0x41F0C0 sub_41F0C0 —— CNChaosModule 删除析构（thunk 尾 free）
//   先调 0x41F0F0 析构本体；pszArg2 & 1 时 j__free 释放对象自身。
// ------------------------------------------------------------
void */*thiscall*/ sub_41F0C0(void *Block, char pszArg2)
{
  sub_41F0F0();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x41F0F0 sub_41F0F0 —— CNChaosModule 析构
//   0x488300 战场模块卸载；this+100 归位 IObject vftable；this+76 map 经 0x41DA40
//   擦除 + free 表头。
// ------------------------------------------------------------
void /*thiscall*/ sub_41F0F0(int this)
{
  int *v2; // [esp-8h] [ebp-28h]
  int *fld_50; // [esp-4h] [ebp-24h]
  int *v4[2]; // [esp+Ch] [ebp-14h] BYREF
  int v5; // [esp+1Ch] [ebp-4h]

  v4[1] = (int *)this;
  *(uint32_t *)this = &CNChaosModule::`vftable';
  *(uint32_t *)(this + 8) = &CNChaosModule::`vftable';
  v5 = 3;
  sub_488300();
  *(uint32_t *)(this + 100) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 104) = 0;
  v3 = *(int **)(this + 80);
  v2 = (int *)*v3;
  LOBYTE(v5) = 1;
  sub_41DA40((int ***)(this + 76), v4, v2, v3);
  j__free(*(void **)(this + 80));
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  *(uint8_t *)(this + 52) = 0;
  *(uint32_t *)(this + 48) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 4) = 0;
  *(uint32_t *)this = &nengine::IObject::`vftable';
}



// ------------------------------------------------------------
// 0x41F190 sub_41F190 —— CNImagePackList 构造
//   vftable nengine::CNImagePackList；+20/+24/+28 与 +36/+40/+44 两族字段清零；
//   0x6991D0 接入管理器【推断：与析构侧 0x699230 配对】。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_41F190(uint8_t *this)
{
  *(this + 4) = 0;
  *(uint32_t *)this = &nengine::CNImagePackList::`vftable';
  *((uint32_t *)this + 5) = 0;
  *((uint32_t *)this + 6) = 0;
  *((uint32_t *)this + 7) = 0;
  *((uint32_t *)this + 9) = 0;
  *((uint32_t *)this + 10) = 0;
  *((uint32_t *)this + 11) = 0;
  sub_6991D0();
  return this;
}



// ------------------------------------------------------------
// 0x41F1F0 sub_41F1F0 —— CNImagePackList 删除析构（thunk 尾 free）
//   先调 0x41F220 析构本体；pszArg2 & 1 时 j__free 释放对象自身。
// ------------------------------------------------------------
void */*thiscall*/ sub_41F1F0(void *Block, char pszArg2)
{
  sub_41F220();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x41F220 sub_41F220 —— CNImagePackList 析构
//   0x699230 脱管【推断：与 0x6991D0 配对】；this+36 矢量经 0x4166A0 逐元素（28B）析构后 free；
//   释放 this+20 矢量；vftable 归位 nengine::IObject。
// ------------------------------------------------------------
void /*thiscall*/ sub_41F220(void *this)
{
  int pThis_9; // eax

  *(uint32_t *)this = &nengine::CNImagePackList::`vftable';
  sub_699230();
  v2 = *((uint32_t *)this + 9);
  if ( v2 != 0 )
  {
    sub_4166A0(v2, *((uint32_t *)this + 10));
    j__free(*((void **)this + 9));
  }
  *((uint32_t *)this + 9) = 0;
  *((uint32_t *)this + 10) = 0;
  *((uint32_t *)this + 11) = 0;
  if ( *((uint32_t *)this + 5) != 0 )
    j__free(*((void **)this + 5));
  *((uint32_t *)this + 5) = 0;
  *((uint32_t *)this + 6) = 0;
  *((uint32_t *)this + 7) = 0;
  *((uint8_t *)this + 4) = 0;
  *(uint32_t *)this = &nengine::IObject::`vftable';
}



// ============================================================
// SECTION 0x41F2C0 — ★ 界面 IMG 预载清单（Sprite/Interface/*.img 八件）+ DllMain
// ============================================================
// ------------------------------------------------------------
// 0x41F2C0 sub_41F2C0
// ------------------------------------------------------------
// 【解读】
//   ★ 界面 IMG 预载清单（new + sub_41F190/0x6990D0/0x6992C0/0x699100 挂管理器）:
//     Sprite/Interface/{SelectCharacter, CreateCharacter, CharacterIllust, Base,
//     ItemInventoryWindow, AvatarInventoryWindow, ItemTradeWindow, EquipmentShopWindow}.img
//     —— 角色选择/创建/仓库/交易/商店八大界面包。
// ------------------------------------------------------------
int sub_41F2C0()  // 【界面 IMG 预载清单（Sprite/Interface/*.img 八件）+ Dl…】
{
  uint8_t *pMem; // eax
  uint8_t *v1; // eax
  void *Block; // [esp+0h] [ebp-10h]

  pMem = operator new(0x30u);
  Block = pMem;
  if ( pMem != nullptr )
    v1 = sub_41F190(pMem);
  else
    v1 = nullptr;
  dword_99FCC8 = (int)v1;
  sub_6990D0(dword_79C0A4);
  sub_6992C0("Sprite/Interface/SelectCharacter.img");
  sub_6992C0("Sprite/Interface/CreateCharacter.img");
  sub_6992C0("Sprite/Interface/CharacterIllust.img");
  sub_6992C0("Sprite/Interface/Base.img");
  sub_6992C0("Sprite/Interface/ItemInventoryWindow.img");
  sub_6992C0("Sprite/Interface/AvatarInventoryWindow.img");
  sub_6992C0("Sprite/Interface/ItemTradeWindow.img");
  sub_6992C0("Sprite/Interface/EquipmentShopWindow.img");
  sub_6992C0("Sprite/Interface/StackableShopWindow.img");
  sub_6992C0("Sprite/Interface/DisjointShopWindow.img");
  sub_6992C0("Sprite/Interface/QuestWindow.img");
  sub_6992C0("Sprite/Interface/SkillBuyWindow.img");
  sub_6992C0("Sprite/Interface/SkillInventoryWindow.img");
  sub_6992C0("Sprite/Interface/StatusWindow.img");
  sub_6992C0("Sprite/Interface/StatusIllust.img");
  sub_6992C0("Sprite/Interface/Popup.img");
  sub_6992C0("Sprite/Interface/NewResult/Result.img");
  sub_6992C0("Sprite/Interface/CountDown.img");
  sub_6992C0("Sprite/Interface/Option.img");
  sub_6992C0("Sprite/Interface/SelectDungeon.img");
  sub_6992C0("Sprite/Interface/SelectDungeonWarning.img");
  sub_6992C0("Sprite/Interface/MiniMap.img");
  sub_6992C0("Sprite/Interface/ClearReward.img");
  sub_6992C0("Sprite/Interface/Chatting.img");
  sub_6992C0("Sprite/Interface/Compound.img");
  sub_6992C0("Sprite/Interface/PVP.img");
  sub_6992C0("Sprite/Interface/PVPTimeCount.img");
  sub_6992C0("Sprite/Interface/ClassChange.img");
  sub_6992C0("Sprite/Interface/Tutorial.img");
  sub_6992C0("Sprite/Interface/Community.img");
  sub_6992C0("Sprite/Common/Etc/Combo.img");
  sub_6992C0("Sprite/Common/Etc/CoolTimeEnd.img");
  sub_6992C0("Sprite/Interface/NewResult/Reward.img");
  sub_6992C0("Sprite/Interface/PVP_Result.img");
  sub_6992C0("Sprite/Interface/PVP_NormalizeEffect.img");
  sub_6992C0("Sprite/Interface/PVP_RankSmall.img");
  sub_6992C0("Sprite/Interface/PVP_RankSmallGlow.img");
  sub_6992C0("Sprite/Common/Etc/CastingGage.img");
  sub_6992C0("Sprite/Interface/ChampKeyFX.img");
  sub_6992C0("Sprite/Interface/CashShop/CashShopImg.img");
  sub_6992C0("Sprite/Interface/CashShop/CashShopBtn.img");
  sub_6992C0("Sprite/Interface/CashShop/CashShopBuyWindow.img");
  sub_6992C0("Sprite/Interface/CashShop/InformCashShop.img");
  sub_6992C0("Sprite/Interface/PVP_OnGameNet.img");
  sub_6992C0("Sprite/Interface/Channel_base.img");
  sub_6992C0("Sprite/Interface/Channel_monster.img");
  sub_6992C0("Sprite/Interface/EPLP.img");
  sub_6992C0("Sprite/Interface/Storage.img");
  sub_6992C0("Sprite/Interface/DungeonInfo/dungeoninfo.img");
  sub_6992C0("Sprite/interface/battledungeon/battledungeon.img");
  sub_6992C0("Sprite/interface/ItemProductWindow.img");
  sub_6992C0("Sprite/Interface/PrivateStoreWindow.img");
  sub_6992C0("Sprite/interface/battledungeon/battledungeon_result.img");
  sub_6992C0("Sprite/interface/MailWindow.img");
  return sub_699100(dword_99FCC8, Block);
}



// ------------------------------------------------------------
// 0x41F690 sub_41F690 —— map 区间擦除 [pDwArg3, pDwArg4)
//   全区间（first==begin 且 last==根）走 0x41EA00 整树递归析构并复位空表；否则按中序
//   后继推进，逐节点交 0x41E720 删除（含 invalid map/set 迭代器校验）。
// ------------------------------------------------------------
int **/*thiscall*/ sub_41F690(int ***this, int **pDwArg2, int *pDwArg3, int *pDwArg4)
{
  int *pDwArg42; // ebx
  int *pDwArg32; // esi
  int fld_e1; // eax
  uint32_t *fld_e12; // eax
  int **v10; // ecx
  int **v11; // eax
  int *j; // eax
  int *i; // eax

  pDwArg42 = pDwArg4;
  pDwArg32 = pDwArg3;
  fld_e1 = (int)*(this + 1);
  if ( pDwArg3 == *(int **)fld_e1 && pDwArg4 == (int *)fld_e1 )
  {
    sub_41EA00(*(void ***)(fld_e1 + 4));
    (*(this + 1))[1] = (int *)*(this + 1);
    fld_e12 = *(this + 1);
    *(this + 2) = nullptr;
    *fld_e12 = fld_e12;
    (*(this + 1))[2] = (int *)*(this + 1);
    *pDwArg2 = **(this + 1);
    return pDwArg2;
  }
  else
  {
    if ( pDwArg3 != pDwArg4 )
    {
      do
      {
        v10 = (int **)pDwArg32;
        if ( *((uint8_t *)pDwArg32 + 33) == 0 )
        {
          v11 = (int **)pDwArg32[2];
          if ( *((uint8_t *)v11 + 33) != 0 )
          {
            for ( i = (int *)pDwArg32[1]; *((uint8_t *)i + 33) == 0; i = (int *)i[1] )
            {
              if ( pDwArg32 != (int *)i[2] )
                break;
              pDwArg32 = i;
            }
            pDwArg32 = i;
          }
          else
          {
            pDwArg32 = (int *)pDwArg32[2];
            for ( j = *v11; *((uint8_t *)j + 33) == 0; j = (int *)*j )
              pDwArg32 = j;
          }
        }
        sub_41E720(this, (int ***)&pDwArg3, v10);
      }
      while ( pDwArg32 != pDwArg42 );
    }
    *pDwArg2 = pDwArg32;
    return pDwArg2;
  }
}



// ------------------------------------------------------------
// 0x41F750 sub_41F750 —— map 清空（0x41F690 全区间擦除）
//   0x41F690 擦除 [begin,end) 后 free 表头结点，三字段归零，返回 0。
// ------------------------------------------------------------
int /*thiscall*/ sub_41F750(int this)
{
  int *v3; // [esp+4h] [ebp-4h] BYREF

  sub_41F690((int ***)this, &v3, **(int ***)(this + 4), *(int **)(this + 4));
  j__free(*(void **)(this + 4));
  *(uint32_t *)(this + 4) = 0;
  *(uint32_t *)(this + 8) = 0;
  return 0;
}



// ------------------------------------------------------------
// 0x41F790 sub_41F790 —— CNRoomListModule 构造
//   vftable + 四组哨兵 map（this+52/+64/+76/+88，this+76 为 0x24 节点族）；
//   三组控件块（+16/+124/+176）；0x45AFF0 未激活字段清空 + 0x45C640 延迟构造。
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_41F790(uint8_t *this)
{
  char *pThis_34; // edi
  int pThis_342; // eax
  int pThis_40; // eax
  int pThis_4C; // eax
  int pThis_58; // eax

  *(this + 4) = 0;
  *((uint32_t *)this + 2) = &nengine::IAppendDraw::`vftable';
  *(uint32_t *)this = &CNRoomListModule::`vftable';
  *((uint32_t *)this + 2) = &CNRoomListModule::`vftable';
  *(this + 20) = 0;
  *((uint32_t *)this + 4) = &off_6C2B88;
  *((uint32_t *)this + 6) = 0;
  *(this + 28) = 1;
  *(this + 30) = 0;
  *(this + 29) = 0;
  *((uint32_t *)this + 10) = 0;
  *((uint32_t *)this + 9) = 0;
  *((uint32_t *)this + 8) = 0;
  pThis_34 = this + 52;
  pThis_342 = sub_433AC0(this + 52);
  *((uint32_t *)pThis_34 + 1) = pThis_342;
  *(uint8_t *)(pThis_342 + 21) = 1;
  *(uint32_t *)(*((uint32_t *)pThis_34 + 1) + 4) = *((uint32_t *)pThis_34 + 1);
  **((uint32_t **)pThis_34 + 1) = *((uint32_t *)pThis_34 + 1);
  *(uint32_t *)(*((uint32_t *)pThis_34 + 1) + 8) = *((uint32_t *)pThis_34 + 1);
  *((uint32_t *)pThis_34 + 2) = 0;
  pThis_40 = sub_433AC0(this + 64);
  *((uint32_t *)this + 17) = pThis_40;
  *(uint8_t *)(pThis_40 + 21) = 1;
  *(uint32_t *)(*((uint32_t *)this + 17) + 4) = *((uint32_t *)this + 17);
  **((uint32_t **)this + 17) = *((uint32_t *)this + 17);
  *(uint32_t *)(*((uint32_t *)this + 17) + 8) = *((uint32_t *)this + 17);
  *((uint32_t *)this + 18) = 0;
  pThis_4C = sub_433B40(this + 76);
  *((uint32_t *)this + 20) = pThis_4C;
  *(uint8_t *)(pThis_4C + 33) = 1;
  *(uint32_t *)(*((uint32_t *)this + 20) + 4) = *((uint32_t *)this + 20);
  **((uint32_t **)this + 20) = *((uint32_t *)this + 20);
  *(uint32_t *)(*((uint32_t *)this + 20) + 8) = *((uint32_t *)this + 20);
  *((uint32_t *)this + 21) = 0;
  pThis_58 = sub_433AC0(this + 88);
  *((uint32_t *)this + 23) = pThis_58;
  *(uint8_t *)(pThis_58 + 21) = 1;
  *(uint32_t *)(*((uint32_t *)this + 23) + 4) = *((uint32_t *)this + 23);
  **((uint32_t **)this + 23) = *((uint32_t *)this + 23);
  *(uint32_t *)(*((uint32_t *)this + 23) + 8) = *((uint32_t *)this + 23);
  *((uint32_t *)this + 24) = 0;
  *(this + 128) = 0;
  *((uint32_t *)this + 31) = &off_6C2B88;
  *((uint32_t *)this + 33) = 0;
  *(this + 136) = 1;
  *(this + 138) = 0;
  *(this + 137) = 0;
  *((uint32_t *)this + 37) = 0;
  *((uint32_t *)this + 36) = 0;
  *((uint32_t *)this + 35) = 0;
  *(this + 180) = 0;
  *((uint32_t *)this + 44) = &off_6C2B88;
  *((uint32_t *)this + 46) = 0;
  *(this + 188) = 1;
  *(this + 190) = 0;
  *(this + 189) = 0;
  *((uint32_t *)this + 50) = 0;
  *((uint32_t *)this + 49) = 0;
  *((uint32_t *)this + 48) = 0;
  sub_45AFF0(this);
  sub_45C640(this);
  return this;
}



// ============================================================
// SECTION 0x41F930 — 引擎聚合初始化/事件路由/杂项
// ============================================================
// ------------------------------------------------------------
// 0x41F930 _DllMain@12
// ------------------------------------------------------------
// 【解读】
//   DllMain 桩（DLL_PROCESS_ATTACH 无附加处理）。
// ------------------------------------------------------------
BOOL /*stdcall*/ DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
  return true;
}



// ------------------------------------------------------------
// 0x41F940 sub_41F940 —— CNRoomListModule 删除析构（thunk 尾 free）
//   先调 0x41F970 析构本体；pszArg2 & 1 时 j__free 释放对象自身。
// ------------------------------------------------------------
void */*thiscall*/ sub_41F940(void *Block, char pszArg2)
{
  sub_41F970();
  if ( (pszArg2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x41F970 sub_41F970 —— CNRoomListModule 析构
//   0x45C9A0 关停/析构；this+176/+124 归位 IObject；四组 map 依次清空
//   （0x41D980 / 0x41F690 / 0x41DBC0 / 0x41DB00）并 free 表头。
// ------------------------------------------------------------
void /*thiscall*/ sub_41F970(int this)
{
  int *v2; // [esp-8h] [ebp-28h]
  int *v3; // [esp-8h] [ebp-28h]
  int *v4; // [esp-8h] [ebp-28h]
  int *v5; // [esp-8h] [ebp-28h]
  int *fld_5C; // [esp-4h] [ebp-24h]
  int *fld_50; // [esp-4h] [ebp-24h]
  int *fld_44; // [esp-4h] [ebp-24h]
  int *fld_38; // [esp-4h] [ebp-24h]
  int *v10[2]; // [esp+Ch] [ebp-14h] BYREF
  int v11; // [esp+1Ch] [ebp-4h]

  v10[1] = (int *)this;
  *(uint32_t *)this = &CNRoomListModule::`vftable';
  *(uint32_t *)(this + 8) = &CNRoomListModule::`vftable';
  v11 = 7;
  sub_45C9A0();
  *(uint32_t *)(this + 176) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 180) = 0;
  *(uint32_t *)(this + 124) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 128) = 0;
  fld_5C = *(int **)(this + 92);
  v2 = (int *)*fld_5C;
  LOBYTE(v11) = 4;
  sub_41D980((int ***)(this + 88), v10, v2, fld_5C);
  j__free(*(void **)(this + 92));
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  fld_50 = *(int **)(this + 80);
  v3 = (int *)*fld_50;
  LOBYTE(v11) = 3;
  sub_41F690((int ***)(this + 76), v10, v3, fld_50);
  j__free(*(void **)(this + 80));
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  fld_44 = *(int **)(this + 68);
  v4 = (int *)*fld_44;
  LOBYTE(v11) = 2;
  sub_41DBC0((int ***)(this + 64), v10, v4, fld_44);
  j__free(*(void **)(this + 68));
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 72) = 0;
  fld_38 = *(int **)(this + 56);
  v5 = (int *)*fld_38;
  LOBYTE(v11) = 1;
  sub_41DB00((int ***)(this + 52), v10, v5, fld_38);
  j__free(*(void **)(this + 56));
  *(uint32_t *)(this + 56) = 0;
  *(uint32_t *)(this + 60) = 0;
  *(uint8_t *)(this + 20) = 0;
  *(uint32_t *)(this + 16) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 4) = 0;
  *(uint32_t *)this = &nengine::IObject::`vftable';
}



// ------------------------------------------------------------
// 0x41FAA0 sub_41FAA0
// ------------------------------------------------------------
// 【解读】
//   引擎事件路由聚合构造（83 行）: new 事件总线 + 注册 8 个回调
//     （sub_41DE30/41EBC0/41F790/41E2A0/41C700/41EA50/41EDD0/41EFF0 —— 模块生命周期钩子）。
// ------------------------------------------------------------
int /*thiscall*/ sub_41FAA0(uint32_t *this)
{
  char *pMem; // eax
  char *v3; // eax
  uint8_t *pMem2; // eax
  uint8_t *v5; // eax
  uint8_t *pMem3; // eax
  uint8_t *v7; // eax
  char *pMem4; // eax
  char *v9; // eax
  uint8_t *pMem5; // eax
  uint8_t *v11; // eax
  uint8_t *pMem6; // eax
  uint8_t *v13; // eax
  uint8_t *pMem7; // eax
  uint8_t *v15; // eax
  uint8_t *pMem8; // eax
  uint8_t *v17; // eax

  *(this + 4) = 0;
  *(this + 5) = 0;
  *(this + 6) = 0;
  *(this + 7) = 0;
  *(this + 8) = 0;
  *(this + 9) = 0;
  *(this + 10) = 0;
  *(this + 11) = 0;
  pMem = (char *)operator new(0x6D4u);
  if ( pMem != nullptr )
    v3 = sub_41DE30(pMem);
  else
    v3 = nullptr;
  *(this + 9) = v3;
  pMem2 = operator new(0x118u);
  if ( pMem2 != nullptr )
    v5 = sub_41EBC0(pMem2);
  else
    v5 = nullptr;
  *(this + 4) = v5;
  pMem3 = operator new(0xDCu);
  if ( pMem3 != nullptr )
    v7 = sub_41F790(pMem3);
  else
    v7 = nullptr;
  *(this + 5) = v7;
  pMem4 = (char *)operator new(0x134u);
  if ( pMem4 != nullptr )
    v9 = sub_41E2A0(pMem4);
  else
    v9 = nullptr;
  *(this + 6) = v9;
  pMem5 = operator new(0x7Cu);
  if ( pMem5 != nullptr )
    v11 = sub_41C700(pMem5);
  else
    v11 = nullptr;
  *(this + 7) = v11;
  pMem6 = operator new(0x8Cu);
  if ( pMem6 != nullptr )
    v13 = sub_41EA50(pMem6);
  else
    v13 = nullptr;
  *(this + 8) = v13;
  pMem7 = operator new(0xC0u);
  if ( pMem7 != nullptr )
    v15 = sub_41EDD0(pMem7);
  else
    v15 = nullptr;
  *(this + 10) = v15;
  pMem8 = operator new(0x84u);
  if ( pMem8 != nullptr )
    v17 = sub_41EFF0(pMem8);
  else
    v17 = nullptr;
  *(this + 11) = v17;
  return 1;
}



// ------------------------------------------------------------
// 0x41FC50 sub_41FC50 —— 全局单例惰性构造（dword_8F7B08）
//   dword_8F7B08 已存在返回 -2147483646；否则 new 0x1D4 + 0x4230A0 构造存全局；
//   分配或构造失败返回 -2147483640，成功返回 1。
// ------------------------------------------------------------
int sub_41FC50()
{
  void *pMem; // eax
  int v2; // eax

  if ( dword_8F7B08 != 0 )
    return -2147483646;
  pMem = operator new(0x1D4u);
  if ( pMem == nullptr )
    return -2147483640;
  v2 = sub_4230A0(pMem, pMem);
  if ( v2 == 0 )
    return -2147483640;
  dword_8F7B08 = v2;
  return 1;
}



// ------------------------------------------------------------
// 0x41FCE0 sub_41FCE0 —— 全局 dword_9D3BC8 赋值 setter
//   写入 nArg1 并原样返回。
// ------------------------------------------------------------
int /*stdcall*/ sub_41FCE0(int nArg1)
{
  dword_9D3BC8 = nArg1;
  return nArg1;
}



// ------------------------------------------------------------
// 0x41FCF0 sub_41FCF0 —— COM 组件一次性初始化（CoCreateInstance）
//   CoInitialize → CoCreateInstance(rclsid, riid, 1) 成功后调对象 vt+164 与 vt+8；
//   任一步失败 CoUninitialize 返回 0，成功返回 1。
// ------------------------------------------------------------
char /*thiscall*/ sub_41FCF0(void *this)
{
  LPVOID ppv; // [esp+0h] [ebp-4h] BYREF

  ppv = this;
  if ( CoInitialize(nullptr) < 0 )
    return 0;
  ppv = nullptr;
  if ( CoCreateInstance(&rclsid, nullptr, 1u, &riid, &ppv) < 0 )
  {
    CoUninitialize();
    return 0;
  }
  (*(void (/*stdcall*/ **)(LPVOID, LPVOID))(*(uint32_t *)ppv + 164))(ppv, ppv);
  (*(void (/*stdcall*/ **)(LPVOID))(*(uint32_t *)ppv + 8))(ppv);
  CoUninitialize();
  return 1;
}



// ------------------------------------------------------------
// 0x41FD50 sub_41FD50 —— 引擎管理器群关停/反初始化
//   0x699580 收尾；dword_79C0AC 经 0x407BD0 批量析构子项，dword_79C0A8/79C0A4 调虚表槽
//   24/16；最后 0x404490 释放三全局槽位，返回 1。
// ------------------------------------------------------------
int sub_41FD50()
{
  sub_699580();
  if ( dword_79C0AC != 0 )
    sub_407BD0(dword_79C0AC);
  if ( dword_79C0A8 != 0 )
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0A8 + 24))(dword_79C0A8);
  if ( dword_79C0A4 != 0 )
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)dword_79C0A4 + 16))(dword_79C0A4);
  sub_404490(&dword_79C0AC);
  sub_404490(&dword_79C0A8);
  sub_404490(&dword_79C0A4);
  return 1;
}



// ------------------------------------------------------------
// 0x41FDC0 sub_41FDC0 —— 全局引擎状态块惰性初始化
//   this+4 为 0 时批量置初值（+12=8、dword_99FCC8=0、+284/288=-1、+292..348 清零）；
//   0x41A590(0) crypt4byte 加密初始化；返回 this+52，已初始化则回原字节值。
// ------------------------------------------------------------
char /*thiscall*/ sub_41FDC0(int this)
{
  char result; // al

  result = *(uint8_t *)(this + 4);
  if ( result == 0 )
  {
    *(uint32_t *)(this + 8) = 0;
    *(uint32_t *)(this + 12) = 8;
    *(uint32_t *)(this + 16) = 0;
    *(uint32_t *)(this + 20) = 0;
    *(uint32_t *)(this + 24) = 0;
    *(uint32_t *)(this + 28) = 0;
    *(uint32_t *)(this + 32) = 0;
    *(uint32_t *)(this + 36) = 0;
    *(uint32_t *)(this + 40) = 0;
    *(uint32_t *)(this + 44) = 0;
    *(uint8_t *)(this + 76) = 0;
    *(uint32_t *)(this + 108) = 0;
    dword_99FCC8 = 0;
    *(uint8_t *)(this + 112) = 0;
    *(uint32_t *)(this + 244) = 0;
    sub_41A590(0);
    *(uint32_t *)(this + 284) = -1;
    *(uint32_t *)(this + 288) = -1;
    *(uint32_t *)(this + 292) = 0;
    *(uint8_t *)(this + 296) = 0;
    *(uint8_t *)(this + 113) = 0;
    *(uint8_t *)(this + 177) = 0;
    *(uint32_t *)(this + 297) = 0;
    *(uint32_t *)(this + 301) = 0;
    *(uint8_t *)(this + 305) = 0;
    *(uint32_t *)(this + 308) = 0;
    *(uint32_t *)(this + 312) = 0;
    *(uint32_t *)(this + 316) = 0;
    *(uint32_t *)(this + 320) = 0;
    *(uint32_t *)(this + 324) = 0;
    *(uint32_t *)(this + 328) = 0;
    *(uint32_t *)(this + 332) = 0;
    *(uint32_t *)(this + 336) = 0;
    *(uint32_t *)(this + 340) = 0;
    *(uint8_t *)(this + 344) = 0;
    *(uint32_t *)(this + 348) = 0;
    return this + 52;
  }
  return result;
}



// ------------------------------------------------------------
// 0x41FE80 sub_41FE80 —— 驻留句柄区间正向填充
//   [pDwArg1, pDwArg2) 逐元素 0x41B0D0 赋值（旧引用释放 + 新引用自增）。
// ------------------------------------------------------------
unsigned int */*cdecl*/ sub_41FE80(unsigned int **pDwArg1, unsigned int **pDwArg2, unsigned int **pDwArg3)
{
  unsigned int **i; // esi
  unsigned int *result; // eax

  for ( i = pDwArg1; i != pDwArg2; ++i )
    result = sub_41B0D0(i, pDwArg3);
  return result;
}



// ------------------------------------------------------------
// 0x41FEB0 sub_41FEB0 —— 8B 元素区间拷贝
//   步长 2 dword 逐元素复制 pArg3 的 [0]/[1] 两字段，返回末地址。
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_41FEB0(uint32_t *uArg1, uint32_t *uArg2, uint32_t *pArg3)
{
  uint32_t *result; // eax

  for ( result = uArg1; result != uArg2; result += 2 )
  {
    *result = *pArg3;
    result[1] = pArg3[1];
  }
  return result;
}



// ------------------------------------------------------------
// 0x41FEE0 sub_41FEE0 —— 驻留句柄区间逆序填充
//   自尾向前逐元素 0x41B0D0 赋值，返回目的区间首地址。
// ------------------------------------------------------------
unsigned int **/*cdecl*/ sub_41FEE0(unsigned int **pDwArg1, unsigned int **pDwArg2, unsigned int **pDwArg3)
{
  unsigned int **pDwArg22; // esi
  unsigned int **pDwArg32; // edi

  pDwArg22 = pDwArg2;
  if ( pDwArg1 == pDwArg2 )
    return pDwArg3;
  pDwArg32 = pDwArg3;
  do
    sub_41B0D0(--pDwArg32, --pDwArg22);
  while ( pDwArg22 != pDwArg1 );
  return pDwArg32;
}



// ------------------------------------------------------------
// 0x41FF20 sub_41FF20 —— 转发 thunk → 0x41FEE0（区间逆序填充）
//   无独立语义：直接尾转发到 0x41FEE0（驻留句柄区间逆序填充）。
// ------------------------------------------------------------
unsigned int **/*cdecl*/ sub_41FF20(unsigned int **pDwArg1, unsigned int **pDwArg2, unsigned int **pDwArg3)
{
  return sub_41FEE0(pDwArg1, pDwArg2, pDwArg3);
}



// ------------------------------------------------------------
// 0x41FF40 sub_41FF40 —— CNRDTutorialTip 析构
//   vftable 归位 + nullsub_3；三段 eh vector destructor iterator（this+8 与 this+7176 各 256
//   项、this+14344 为 64 项，步长 28B，元素析构 0x501490）。
// ------------------------------------------------------------
void /*thiscall*/ sub_41FF40(uint32_t *this)
{
  *this = &CNRDTutorialTip::`vftable';
  nullsub_3(this);
  `eh vector destructor iterator'(this + 3586, 0x1Cu, 64, sub_501490);
  `eh vector destructor iterator'(this + 1794, 0x1Cu, 256, sub_501490);
  `eh vector destructor iterator'(this + 2, 0x1Cu, 256, sub_501490);
}



// ------------------------------------------------------------
// 0x41FFE0 sub_41FFE0 —— 驻留句柄区间填充 nArg2 个元素
//   逐元素先置空再 0x41B0D0 赋值；v7 为部分构造区间的异常展开标志。
// ------------------------------------------------------------
unsigned int */*cdecl*/ sub_41FFE0(unsigned int **pDwArg1, int nArg2, unsigned int **pDwArg3)
{
  unsigned int **pDwArg12; // esi
  unsigned int *result; // eax
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  pDwArg12 = pDwArg1;
  v6[4] = v6;
  v6[3] = pDwArg1;
  v7 = 0;
  while ( nArg2 != 0 )
  {
    LOBYTE(v7) = 1;
    if ( pDwArg12 != nullptr )
    {
      *pDwArg12 = nullptr;
      result = sub_41B0D0(pDwArg12, pDwArg3);
    }
    --nArg2;
    ++pDwArg12;
    LOBYTE(v7) = 0;
  }
  return result;
}

