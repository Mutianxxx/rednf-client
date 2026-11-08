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
void /*userpurge*/ sub_410030(int a1@<eax>, uint32_t *a2@<ecx>, int a3, int a4, const RECT *a5, int a6, int a7)
{
  LONG v8; // edi
  LONG v9; // ebx
  LONG v10; // ecx
  int v11; // edx
  double left; // st7
  double v13; // st7
  int v14; // eax
  double v15; // st7
  int v16; // eax
  int v17; // eax
  struct tagRECT rcDst; // [esp+Ch] [ebp-28h] BYREF
  uint32_t v19[2]; // [esp+1Ch] [ebp-18h] BYREF
  float v20[2]; // [esp+24h] [ebp-10h] BYREF
  float v21[2]; // [esp+2Ch] [ebp-8h] BYREF

  sub_404F40(a1, 4u);
  v8 = a3 + a2[7];
  v9 = a4 + a2[8];
  v10 = v9 + a2[6];
  rcDst.right = v8 + a2[5];
  rcDst.bottom = v10;
  rcDst.left = v8;
  rcDst.top = v9;
  if ( IntersectRect(&rcDst, &rcDst, a5 + 3) )
  {
    v11 = a2[5];
    left = (double)rcDst.left;
    rcDst.left -= v8;
    v21[0] = left;
    rcDst.right -= v8;
    v21[1] = (float)rcDst.top;
    v13 = (double)(int)a2[5];
    rcDst.top -= v9;
    rcDst.bottom -= v9;
    v19[0] = 1065353216;
    v19[1] = 1065353216;
    if ( v11 < 0 )
      v13 = v13 + 4294967300.0;
    v14 = a2[6];
    v20[0] = v13 * 0.5;
    v15 = (double)(int)a2[6];
    if ( v14 < 0 )
      v15 = v15 + 4294967300.0;
    v16 = a2[31];
    v20[1] = v15 * 0.5;
    v17 = (*(int (/*stdcall*/ **)(int, uint32_t, struct tagRECT *, uint32_t *, float *, int, float *, int))(*(uint32_t *)v16 + 20))(
            v16,
            a2[28],
            &rcDst,
            v19,
            v20,
            a7,
            v21,
            a6);
    sub_404F80(v17, 4u, 0);
  }
}



// ------------------------------------------------------------
// 0x410140 sub_410140
// ------------------------------------------------------------
void /*userpurge*/ sub_410140(int a1@<eax>, int a2@<ecx>, int a3, int a4, int *a5, int a6, int a7, float a8, float a9)
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
  float v28; // [esp+20h] [ebp-28h]
  float v29; // [esp+24h] [ebp-24h]
  uint32_t v30[2]; // [esp+28h] [ebp-20h] BYREF
  float v31[2]; // [esp+30h] [ebp-18h] BYREF
  float v32[2]; // [esp+38h] [ebp-10h] BYREF
  float v33; // [esp+40h] [ebp-8h]
  float v34; // [esp+44h] [ebp-4h]
  int v35; // [esp+50h] [ebp+8h]
  float v36; // [esp+50h] [ebp+8h]
  int v37; // [esp+58h] [ebp+10h]
  float v38; // [esp+58h] [ebp+10h]

  sub_404F40(a1, 4u);
  v10 = (double)*(unsigned int *)(a2 + 20);
  v26 = 0.0;
  v11 = *(uint32_t *)(a2 + 24);
  v27 = 0.0;
  v34 = v10 * a8;
  v28 = v34;
  v12 = (double)*(int *)(a2 + 24);
  if ( v11 < 0 )
    v12 = v12 + 4294967300.0;
  v14 = *(uint32_t *)(a2 + 28);
  v33 = v12 * a9;
  v29 = v33;
  v15 = (double)a5[12];
  v37 = a3 + v14;
  v16 = (double)a5[14];
  v23 = (float)a5[13];
  v35 = a4 + *(uint32_t *)(a2 + 32);
  v25 = (float)a5[15];
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
    *(float *)v30 = a8;
    *(float *)&v30[1] = a9;
    v19 = 1.0 / a8;
    v26 = v26 * v19;
    v28 = v19 * v28;
    v20 = 1.0 / a9;
    v27 = v27 * v20;
    v29 = v20 * v29;
    v32[0] = v17;
    v32[1] = v18;
    v31[0] = v34 * 0.5;
    v31[1] = v33 * 0.5;
    dword_8A76E8 = (uint64_t)v26;
    dword_8A76F0 = (uint64_t)v28;
    dword_8A76EC = (uint64_t)v27;
    dword_8A76F4 = (uint64_t)v29;
    v21 = (*(int (/*stdcall*/ **)(uint32_t, uint32_t, int *, uint32_t *, float *, int, float *, unsigned int))(**(uint32_t **)(a2 + 124) + 20))(
            *(uint32_t *)(a2 + 124),
            *(uint32_t *)(a2 + 112),
            &dword_8A76E8,
            v30,
            v31,
            a7,
            v32,
            a6 & 0xFF00FF00 | ((uint8_t)a6 << 16) | BYTE2(a6));
    sub_404F80(v21, 4u, 0);
  }
}



// ------------------------------------------------------------
// 0x410300 sub_410300
// ------------------------------------------------------------
int /*thiscall*/ sub_410300(int this, int a2, int a3, int *a4, int a5, int a6, float a7, float a8, float a9, float a10)
{
  int v11; // eax
  double v12; // st7
  double v13; // st7
  int v14; // edx
  double v15; // st7
  double v16; // st7
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
  float v46; // [esp+14h] [ebp-34h] BYREF
  float v47; // [esp+18h] [ebp-30h]
  float v48; // [esp+1Ch] [ebp-2Ch]
  float v49; // [esp+20h] [ebp-28h]
  uint32_t v50[2]; // [esp+24h] [ebp-24h] BYREF
  float v51[2]; // [esp+2Ch] [ebp-1Ch] BYREF
  float v52[3]; // [esp+34h] [ebp-14h] BYREF
  float v53; // [esp+40h] [ebp-8h]
  float v54; // [esp+44h] [ebp-4h]
  float v55; // [esp+6Ch] [ebp+24h]
  float v56; // [esp+70h] [ebp+28h]

  sub_404F40(4);
  v54 = (double)*(int *)(this + 28) - a9;
  v53 = (double)*(int *)(this + 32) - a10;
  if ( a7 <= 0.0 )
  {
    v46 = ((double)*(unsigned int *)(this + 20) + v54) * a7;
    v13 = v54;
  }
  else
  {
    v11 = *(uint32_t *)(this + 20);
    v46 = v54 * a7;
    v12 = (double)*(int *)(this + 20);
    if ( v11 < 0 )
      v12 = v12 + 4294967300.0;
    v13 = v12 + v54;
  }
  v48 = v13 * a7;
  if ( a8 <= 0.0 )
  {
    v47 = ((double)*(unsigned int *)(this + 24) + v53) * a8;
    v16 = v53;
  }
  else
  {
    v14 = *(uint32_t *)(this + 24);
    v47 = v53 * a8;
    v15 = (double)*(int *)(this + 24);
    if ( v14 < 0 )
      v15 = v15 + 4294967300.0;
    v16 = v15 + v53;
  }
  v49 = v16 * a8;
  v17 = (double)a4[12];
  v18 = (double)a4[14];
  v43 = (float)a4[13];
  v45 = (float)a4[15];
  v55 = (double)a2 + a9;
  v56 = (double)a3 + a10;
  v42 = v17 - v55;
  v44 = v18 - v55;
  v43 = v43 - v56;
  v45 = v45 - v56;
  result = sub_40FCB0(&v46, &v46, &v42);
  if ( (uint8_t)result != 0 )
  {
    v21 = v55;
    if ( (v22 | v23) != 0 )
      v24 = v21 + v48;
    else
      v24 = v21 + v46;
    v26 = v56;
    if ( (v27 | v28) != 0 )
      v29 = v26 + v49;
    else
      v29 = v26 + v47;
    v31 = 1.0 / a7;
    if ( (v32 | v33) != 0 )
    {
      v34 = v31;
      v35 = v48 * v31 - v54;
      v48 = v34 * v46 - v54;
      v46 = v35;
    }
    else
    {
      v46 = v46 * v31 - v54;
      v48 = v31 * v48 - v54;
    }
    v37 = 1.0 / a8;
    if ( (v38 | v39) != 0 )
    {
      v40 = v37;
      v41 = v49 * v37 - v53;
      v49 = v40 * v47 - v53;
      v47 = v41;
    }
    else
    {
      v47 = v47 * v37 - v53;
      v49 = v37 * v49 - v53;
    }
    v52[0] = v24;
    v52[1] = v29;
    *(float *)v50 = a7;
    *(float *)&v50[1] = a8;
    v51[0] = -v54;
    v51[1] = -v53;
    dword_8A76E8 = (uint64_t)v46;
    dword_8A76F0 = (uint64_t)v48;
    dword_8A76EC = (uint64_t)v47;
    dword_8A76F4 = (uint64_t)v49;
    (*(void (/*stdcall*/ **)(uint32_t, uint32_t, int *, uint32_t *, float *, int, float *, unsigned int))(**(uint32_t **)(this + 124)
                                                                                                + 20))(
      *(uint32_t *)(this + 124),
      *(uint32_t *)(this + 112),
      &dword_8A76E8,
      v50,
      v51,
      a6,
      v52,
      a5 & 0xFF00FF00 | ((uint8_t)a5 << 16) | BYTE2(a5));
    return sub_404F80(4, 0);
  }
  return result;
}


// ------------------------------------------------------------
// 0x4105A0 sub_4105A0
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
int /*thiscall*/ sub_410750(uint32_t *this, int a2, int a3)
{
  if ( *(this + 32) != 0 )
  {
    off_77F3FC("CND3DBaseTexture : ImagePackEx already exists");
    return 0x80000000;
  }
  else
  {
    *(this + 32) = a2;
    *(this + 33) = a3;
    return 1;
  }
}



// ------------------------------------------------------------
// 0x410790 sub_410790
// ------------------------------------------------------------
int /*cdecl*/ sub_410790(int a1, int a2)
{
  unsigned int v2; // eax
  int v4; // ecx

  v2 = a2;
  if ( a2 < 0 )
    v2 = -a2;
  v4 = 1;
  while ( 1 )
  {
    if ( (v2 & 1) != 0 )
      v4 *= a1;
    v2 >>= 1;
    if ( v2 == 0 )
      break;
    a1 *= a1;
  }
  if ( a2 >= 0 )
    return v4;
  else
    return 1 / v4;
}



// ------------------------------------------------------------
// 0x4107D0 sub_4107D0
// ------------------------------------------------------------
void /*thiscall*/ sub_4107D0(int this, int a2, int dy, const RECT *a4)
{
  int v5; // ecx
  int right; // eax
  int v7; // ecx
  int v8; // eax
  struct tagRECT rcDst; // [esp+4h] [ebp-18h] BYREF
  int v10; // [esp+14h] [ebp-8h] BYREF
  int v11; // [esp+18h] [ebp-4h]

  if ( (*(uint32_t *)(this + 128) == 0 || sub_418E20(*(uint32_t *)(this + 132)) != 0) && *(uint8_t *)(this + 4) != 0 )
  {
    v5 = *(uint32_t *)(this + 20);
    if ( v5 != 1 || *(uint32_t *)(this + 24) != 1 )
    {
      right = a4->right;
      if ( right == 7 )
      {
        if ( v5 != 1 || *(uint32_t *)(this + 24) != 1 )
          sub_410030(7, (uint32_t *)this, a2, dy, a4, -1, 0);
      }
      else if ( right == 8 || right == 16 || right == 14 || right == 15 )
      {
        sub_404F40(right, 4u);
        v7 = *(uint32_t *)(this + 32);
        v10 = a2 + *(uint32_t *)(this + 28);
        v11 = dy + v7;
        CopyRect(&rcDst, (const RECT *)(this + 48));
        OffsetRect(&rcDst, a2, dy);
        if ( IntersectRect(&rcDst, &rcDst, a4 + 3) )
        {
          OffsetRect(&rcDst, -a2, -dy);
          if ( a2 < 0 )
            v10 = 0;
          if ( dy < 0 )
            v11 = 0;
          v8 = (*(int (/*stdcall*/ **)(uint32_t, uint32_t, struct tagRECT *, int, LONG, int *))(**(uint32_t **)(this + 120) + 112))(
                 *(uint32_t *)(this + 120),
                 *(uint32_t *)(this + 116),
                 &rcDst,
                 1,
                 a4[7].top,
                 &v10);
          sub_404F80(v8, 4u, 0);
        }
      }
    }
  }
}



// ------------------------------------------------------------
// 0x410910 sub_410910
// ------------------------------------------------------------
void /*userpurge*/ sub_410910(int a1@<eax>, int a2@<ecx>, int a3, int a4, int a5, uint32_t *a6, int a7)
{
  uint32_t *v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // ecx
  int v12; // ecx
  unsigned int v13; // edx
  unsigned int i; // ebx
  unsigned int v15; // edi
  int v16; // [esp-1Ch] [ebp-30h]
  int v17; // [esp-10h] [ebp-24h]
  int v18; // [esp+4h] [ebp-10h] BYREF
  int v19; // [esp+8h] [ebp-Ch]
  float v20[2]; // [esp+Ch] [ebp-8h] BYREF
  unsigned int v21; // [esp+24h] [ebp+10h]
  unsigned int v22; // [esp+2Ch] [ebp+18h]

  sub_404F40(a1, 4u);
  if ( (*(uint32_t *)(a2 + 128) == 0 || sub_418E20(*(uint32_t *)(a2 + 132)) != 0)
    && *(uint8_t *)(a2 + 4) != 0
    && (*(uint32_t *)(a2 + 20) != 1 || *(uint32_t *)(a2 + 24) != 1) )
  {
    v8 = *(uint32_t **)(a5 + 8);
    if ( v8 == (uint32_t *)7 )
    {
      v9 = *(uint32_t *)(a2 + 124);
      v20[0] = (float)a3;
      v20[1] = (float)a4;
      v16 = *(uint32_t *)(a2 + 112);
      v18 = 1065353216;
      v19 = 1065353216;
      v10 = (*(int (/*stdcall*/ **)(int, int, uint32_t *, int *, uint32_t, uint32_t, float *, int))(*(uint32_t *)v9 + 20))(
              v9,
              v16,
              a6,
              &v18,
              0,
              0,
              v20,
              a7);
      sub_404F80(v10, 4u, 0);
    }
    else
    {
      if ( v8 == (uint32_t *)14 || v8 == (uint32_t *)15 )
      {
        if ( a5 == a2 )
        {
          v8 = a6;
          v12 = a6[2] - *a6;
          v13 = a6[3] - a6[1];
          v21 = v12;
          v22 = v13;
          for ( i = 0; i < v13; ++i )
          {
            v15 = 0;
            if ( v12 != 0 )
            {
              do
              {
                if ( (*(int (/*thiscall*/ **)(int, unsigned int, unsigned int))(*(uint32_t *)a2 + 64))(
                       a2,
                       v15 + *v8,
                       i + v8[1]) != 2131166983 )
                  (*(void (/*thiscall*/ **)(int, unsigned int, unsigned int, int))(*(uint32_t *)a2 + 32))(
                    a2,
                    v15 + a3,
                    i + a4,
                    -1);
                ++v15;
                v8 = a6;
              }
              while ( v15 < v21 );
              v12 = v21;
              v13 = v22;
            }
          }
        }
        else
        {
          v17 = *(uint32_t *)(a5 + 116);
          v11 = *(uint32_t *)(a2 + 116);
          v18 = a3;
          v19 = a4;
          v8 = (uint32_t *)(*(int (/*stdcall*/ **)(uint32_t, int, uint32_t *, int, int, int *))(**(uint32_t **)(a2 + 120) + 112))(
                           *(uint32_t *)(a2 + 120),
                           v11,
                           a6,
                           1,
                           v17,
                           &v18);
        }
      }
      sub_404F80((int)v8, 4u, 0);
    }
  }
}



// ------------------------------------------------------------
// 0x410A80 sub_410A80
// ------------------------------------------------------------
void /*thiscall*/ sub_410A80(int this, int a2, int a3, RECT *a4, float a5, float a6, int a7, int a8, int a9, int a10)
{
  if ( (*(uint32_t *)(this + 128) == 0 || sub_418E20(*(uint32_t *)(this + 132)) != 0)
    && *(uint8_t *)(this + 4) != 0
    && (*(uint32_t *)(this + 20) != 1 || *(uint32_t *)(this + 24) != 1)
    && a4->right == 7 )
  {
    if ( a5 == 1.0 && a6 == 1.0 )
    {
      sub_410030(a8, (uint32_t *)this, a2, a3, a4, a8, a7);
    }
    else if ( a5 > 0.0 && a6 > 0.0 )
    {
      sub_410140(a3, this, a2, a3, &a4->left, a8, a7, a5, a6);
    }
  }
}



// ------------------------------------------------------------
// 0x410B60 sub_410B60
// ------------------------------------------------------------
void /*thiscall*/ sub_410B60(int this, int a2, int a3, int *a4, float a5, float a6, int a7, int a8, float a9, float a10)
{
  unsigned int v11; // ecx

  if ( (*(uint32_t *)(this + 128) == 0 || sub_418E20(*(uint32_t *)(this + 132)) != 0) && *(uint8_t *)(this + 4) != 0 )
  {
    v11 = *(uint32_t *)(this + 20);
    if ( (v11 != 1 || *(uint32_t *)(this + 24) != 1) && a4[2] == 7 && (v11 != 1 || *(uint32_t *)(this + 24) != 1) )
    {
      if ( a9 == 4294967300.0 )
        a9 = (double)v11 * 0.5;
      if ( a10 == 4294967300.0 )
        a10 = (double)*(unsigned int *)(this + 24) * 0.5;
      if ( *(float *)&a7 == 0.0 )
        sub_410300(a2, this, a2, a3, a4, a8, a7, a5, a6, a9, a10);
      else
        sub_4105A0(a8, this, a2, a3, (int)a4, a8, *(float *)&a7, a5, a6, a9, a10);
    }
  }
}



// ------------------------------------------------------------
// 0x410C80 sub_410C80
// ------------------------------------------------------------
void /*thiscall*/ sub_410C80(int this, int *a2, RECT *lprcSrc, const RECT *a4)
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
  int v14; // eax
  double v15; // st7
  int v16; // eax
  int v17; // ecx
  int v18; // eax
  int v19; // eax
  float v20; // ecx
  int v21; // eax
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
    right = a4->right;
    if ( right == 7 )
    {
      v6 = *a2;
      v7 = a2[2];
      i = *a2;
      if ( i != v7 )
      {
        v8 = a2[3];
        v32 = a2[1];
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
          v14 = *(uint32_t *)(this + 28);
          *(float *)&rcDst.bottom = v13 / (double)v12;
          v15 = (double)v35;
          v36 = bottom >> 1;
          v16 = i + v14;
          v17 = *(uint32_t *)(this + 32);
          v28[0] = v15;
          v28[1] = (float)v36;
          v29 = (float)v16;
          v30 = (float)(v32 + v17);
          sub_404F40(v16, 4u);
          v18 = (*(int (/*stdcall*/ **)(uint32_t, uint32_t, RECT *, LONG *, float *, uint32_t, float *, int))(**(uint32_t **)(this + 124) + 20))(
                  *(uint32_t *)(this + 124),
                  *(uint32_t *)(this + 112),
                  lprcSrc,
                  &rcDst.right,
                  v28,
                  0,
                  &v29,
                  -1);
LABEL_26:
          sub_404F80(v18, 4u, 0);
        }
      }
    }
    else if ( right == 8 || right == 16 || right == 14 || right == 15 )
    {
      if ( a4[7].right != *(uint32_t *)(this + 120) )
      {
        sub_404F40(right, 4u);
        v23 = lprcSrc->right - lprcSrc->left;
        v24 = lprcSrc->bottom == lprcSrc->top;
        LODWORD(v30) = lprcSrc->bottom - lprcSrc->top;
        v18 = 0;
        lprcSrca = nullptr;
        if ( !v24 )
        {
          do
          {
            i = *(uint32_t *)(*(uint32_t *)(this + 16) + 4 * (v18 + lprcSrc->top)) + 4 * lprcSrc->left;
            v25 = (uint32_t *)(*(uint32_t *)(a4[1].left + 4 * ((uint32_t)lprcSrca + a2[1])) + 4 * *a2);
            if ( v23 != 0 )
            {
              v26 = i - (uint32_t)v25;
              for ( i = v23; i != 0; --i )
              {
                *v25 = *(uint32_t *)((char *)v25 + v26);
                ++v25;
              }
            }
            v18 = (int)&lprcSrca->left + 1;
            lprcSrca = (RECT *)((char *)lprcSrca + 1);
          }
          while ( (unsigned int)lprcSrca < LODWORD(v30) );
        }
        goto LABEL_26;
      }
      CopyRect(&rcDst, lprcSrc);
      IntersectRect(&rcDst, &rcDst, (const RECT *)(this + 48));
      OffsetRect(&rcDst, *a2 - lprcSrc->left, a2[1] - lprcSrc->top);
      if ( IntersectRect(&rcDst, &rcDst, a4 + 3) )
      {
        OffsetRect(&rcDst, lprcSrc->left - *a2, lprcSrc->top - a2[1]);
        v19 = *a2 + *(uint32_t *)(this + 28);
        LODWORD(v20) = a2[1] + *(uint32_t *)(this + 32);
        v29 = *(float *)&v19;
        v30 = v20;
        if ( v19 < 0 )
          v29 = 0.0;
        if ( v20 < 0.0 )
          v30 = 0.0;
        sub_404F40(v19, 4u);
        v21 = (*(int (/*stdcall*/ **)(uint32_t, uint32_t, struct tagRECT *, int, LONG, float *))(**(uint32_t **)(this + 120)
                                                                                         + 112))(
                *(uint32_t *)(this + 120),
                *(uint32_t *)(this + 116),
                &rcDst,
                1,
                a4[7].top,
                &v29);
        sub_404F80(v21, 4u, 0);
      }
    }
  }
}


// ------------------------------------------------------------
// 0x410F30 sub_410F30
// ------------------------------------------------------------
void /*thiscall*/ sub_410F30(int this, int *a2, uint32_t *a3, int a4, int a5, int a6)
{
  int v7; // eax
  int v8; // ecx
  int v9; // edx
  int v10; // edi
  double v11; // st7
  int v12; // edi
  double v13; // st7
  int v14; // edi
  int v15; // ecx
  int v16; // ecx
  int v17; // eax
  float v18[2]; // [esp+4h] [ebp-18h] BYREF
  float v19[2]; // [esp+Ch] [ebp-10h] BYREF
  float v20[2]; // [esp+14h] [ebp-8h] BYREF
  int v21; // [esp+2Ch] [ebp+10h]
  int v22; // [esp+2Ch] [ebp+10h]
  int v23; // [esp+2Ch] [ebp+10h]
  int v24; // [esp+2Ch] [ebp+10h]

  if ( (*(uint32_t *)(this + 128) == 0 || sub_418E20(*(uint32_t *)(this + 132)) != 0)
    && *(uint8_t *)(this + 4) != 0
    && (*(uint32_t *)(this + 20) != 1 || *(uint32_t *)(this + 24) != 1)
    && *(uint32_t *)(a4 + 8) == 7
    && *a2 != a2[2] )
  {
    v7 = a2[1];
    if ( v7 != a2[3] )
    {
      sub_404F40(v7, 4u);
      v8 = *a2;
      v9 = a2[1];
      v21 = a2[3] - v9;
      v10 = a3[3] - a3[1];
      v18[0] = (double)(a2[2] - *a2) / (double)(a3[2] - *a3);
      v11 = (double)v21 / (double)v10;
      v22 = *(int *)(this + 96) >> 1;
      v12 = *(int *)(this + 100) >> 1;
      v18[1] = v11;
      v13 = (double)v22;
      v23 = v12;
      v14 = v8 + *(uint32_t *)(this + 28);
      v15 = *(uint32_t *)(this + 32);
      v19[0] = v13;
      v19[1] = (float)v23;
      v24 = v9 + v15;
      v16 = *(uint32_t *)(this + 124);
      v20[0] = (float)v14;
      v20[1] = (float)v24;
      v17 = (*(int (/*stdcall*/ **)(int, uint32_t, uint32_t *, float *, float *, int, float *, unsigned int))(*(uint32_t *)v16 + 20))(
              v16,
              *(uint32_t *)(this + 112),
              a3,
              v18,
              v19,
              a5,
              v20,
              a6 & 0xFF00FF00 | ((uint8_t)a6 << 16) | BYTE2(a6));
      sub_404F80(v17, 4u, 0);
    }
  }
}



// ------------------------------------------------------------
// 0x411080 sub_411080
// ------------------------------------------------------------
void /*thiscall*/ sub_411080(int this, int *a2, uint32_t *a3, int a4, int a5, int a6, char a7)
{
  int v8; // ecx
  int v9; // ebx
  int v10; // edx
  int v11; // eax
  double v12; // st7
  int v13; // eax
  int v14; // ecx
  double v15; // st7
  int v16; // eax
  double v17; // st7
  int v18; // ecx
  double v19; // st7
  int v20; // eax
  unsigned int v21; // eax
  int v22; // ebx
  int v23; // eax
  float v24[2]; // [esp+4h] [ebp-18h] BYREF
  float v25[2]; // [esp+Ch] [ebp-10h] BYREF
  float v26[2]; // [esp+14h] [ebp-8h] BYREF
  int v27; // [esp+2Ch] [ebp+10h]
  int v28; // [esp+2Ch] [ebp+10h]
  int v29; // [esp+2Ch] [ebp+10h]
  int v30; // [esp+2Ch] [ebp+10h]

  if ( (*(uint32_t *)(this + 128) == 0 || sub_418E20(*(uint32_t *)(this + 132)) != 0)
    && *(uint8_t *)(this + 4) != 0
    && (*(uint32_t *)(this + 20) != 1 || *(uint32_t *)(this + 24) != 1)
    && *(uint32_t *)(a4 + 8) == 7 )
  {
    v8 = a2[2];
    v9 = *a2;
    if ( *a2 != v8 )
    {
      v10 = a2[1];
      v11 = a2[3];
      if ( v10 != v11 )
      {
        v12 = (double)(v8 - v9) / (double)(a3[2] - *a3);
        v27 = v11 - v10;
        v13 = a3[3] - a3[1];
        v14 = *(int *)(this + 96) >> 1;
        v24[0] = v12;
        v15 = (double)v27;
        v28 = v13;
        v16 = *(int *)(this + 100) >> 1;
        v17 = v15 / (double)v28;
        v29 = v14;
        v18 = v9 + *(uint32_t *)(this + 28);
        v24[1] = v17;
        v19 = (double)v29;
        v30 = v16;
        v20 = v10 + *(uint32_t *)(this + 32);
        v25[0] = v19;
        v25[1] = (float)v30;
        v26[0] = (float)v18;
        v26[1] = (float)v20;
        if ( a7 != 0 )
          v21 = a6 & 0x8000FF00;
        else
          v21 = a6 & 0xFF00FF00;
        v22 = v21 | ((uint8_t)a6 << 16) | BYTE2(a6);
        sub_404F40(v21, 4u);
        v23 = (*(int (/*stdcall*/ **)(uint32_t, uint32_t, uint32_t *, float *, float *, int, float *, int))(**(uint32_t **)(this + 124)
                                                                                                  + 20))(
                *(uint32_t *)(this + 124),
                *(uint32_t *)(this + 112),
                a3,
                v24,
                v25,
                a5,
                v26,
                v22);
        sub_404F80(v23, 4u, 0);
      }
    }
  }
}



// ============================================================
// SECTION 0x4111E0 — 屏幕矩形/视口辅助
// ============================================================
// ------------------------------------------------------------
// 0x4111E0 sub_4111E0
// ------------------------------------------------------------
int /*stdcall*/ sub_4111E0(int a1)
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
    if ( result >= a1 )
      break;
    if ( ++v1 >= 100 )
      return -1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x411240 sub_411240
// ------------------------------------------------------------
int /*userpurge*/ sub_411240@<eax>(int *a1@<ecx>, int a2@<ebx>, int a3@<edi>, int xRight, int yBottom, int a6)
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

  if ( *((uint8_t *)a1 + 4) != 0 )
    return -2147483646;
  v8 = a1[9];
  *((uint8_t *)a1 + 4) = 1;
  a1[5] = xRight;
  a1[6] = yBottom;
  if ( v8 == 0 )
    a1[9] = xRight;
  if ( a1[10] == 0 )
    a1[10] = yBottom;
  SetRect((LPRECT)(a1 + 22), 0, 0, xRight, yBottom);
  SetRect((LPRECT)a1 + 3, 0, 0, a1[5] + a1[7], a1[6] + a1[8]);
  v9 = a1[5];
  *((uint8_t *)a1 + 76) = 0;
  if ( v9 == 0 )
    a1[5] = 1;
  if ( a1[6] == 0 )
    a1[6] = 1;
  v10 = a1[5];
  xRighta = a1[6];
  (*(void (/*stdcall*/ **)(int, uint8_t *, int, int))(*(uint32_t *)a1[30] + 28))(a1[30], v18, a3, a2);
  if ( (v18[60] & 2) != 0 && (v18[61] & 1) == 0 || a6 == 26 )
  {
    v10 = sub_4111E0(a1[5]);
    v11 = sub_4111E0(a1[6]);
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
  v12 = a1 + 28;
  v13 = (*(int (/*stdcall*/ **)(int, int, int, int, uint32_t, int))(*(uint32_t *)a1[30] + 80))(a1[30], v10, xRighta, 1, 0, a6);
  if ( v13 >= 0 && (v13 = (*(int (/*stdcall*/ **)(uint32_t, uint32_t, int *))(*(uint32_t *)*v12 + 60))(*v12, 0, a1 + 29)) >= 0 )
  {
    (*(void (/*stdcall*/ **)(uint32_t, uint32_t, int *, uint32_t, uint32_t))(*(uint32_t *)*v12 + 64))(*v12, 0, a1 + 26, 0, 0);
    (*(void (/*stdcall*/ **)(uint32_t, uint32_t))(*(uint32_t *)*v12 + 68))(*v12, 0);
    v14 = a1[26];
    a1[3] = a1[27];
    v15 = *a1;
    a1[20] = v14;
    a1[21] = xRighta;
    v16 = (*(int (/*thiscall*/ **)(int *))(v15 + 172))(a1);
    if ( v16 >= 0 )
    {
      sub_405060(1u, a1[20] * a1[21] + 4 * a1[6], 0);
      return 1;
    }
    else
    {
      (*(void (/*thiscall*/ **)(int *))(*a1 + 20))(a1);
      return v16;
    }
  }
  else
  {
    (*(void (/*thiscall*/ **)(int *))(*a1 + 20))(a1);
    return v13;
  }
}



// ------------------------------------------------------------
// 0x4113F0 sub_4113F0
// ------------------------------------------------------------
int /*thiscall*/ sub_4113F0(uint32_t *this, int a2)
{
  unsigned int i; // edi
  int v4; // ecx
  unsigned int j; // eax
  int result; // eax

  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 84))(this);
  for ( i = 0; i < *(this + 6); ++i )
  {
    v4 = *(uint32_t *)(*(this + 4) + 4 * i);
    for ( j = 0; j < *(this + 5); ++j )
    {
      if ( *(uint32_t *)(v4 + 4 * j) == (a2 & 0xFF00FF00 | ((uint8_t)a2 << 16) | BYTE2(a2)) )
        *(uint32_t *)(v4 + 4 * j) = 0;
    }
  }
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 88))(this);
  *(this + 17) = a2;
  return result;
}



// ------------------------------------------------------------
// 0x411460 sub_411460
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_411460(unsigned int *this, int a2)
{
  unsigned int result; // eax
  unsigned int v3; // ebx
  unsigned int v4; // edx
  int v5; // esi
  unsigned int i; // eax

  result = *(this + 3);
  if ( result != 0 )
  {
    result = *(this + 6);
    v3 = 0;
    if ( result != 0 )
    {
      v4 = *(this + 5);
      do
      {
        v5 = *(uint32_t *)(*(this + 4) + 4 * v3);
        for ( i = 0; i < v4; ++i )
        {
          *(uint32_t *)(v5 + 4 * i) = a2 & 0xFF00FF00 | ((uint8_t)a2 << 16) | BYTE2(a2);
          v4 = *(this + 5);
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
// 0x4114C0 sub_4114C0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4114C0(uint32_t *this, int a2, int a3)
{
  int v5; // edx

  if ( sub_40F530(a2, a3, this + 12) )
    return 0;
  v5 = *(uint32_t *)(*(this + 4) + 4 * a3) + 4 * a2;
  return *(uint32_t *)v5 & 0xFF00FF00 | *(uint8_t *)(v5 + 2) | ((uint8_t)*(uint32_t *)v5 << 16);
}



// ------------------------------------------------------------
// 0x411510 sub_411510
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_411510(int *this, int a2, signed int a3, signed int a4, int a5)
{
  unsigned int result; // eax
  signed int v7; // ecx
  int v8; // eax
  void *v9; // edi
  int v10; // [esp+4h] [ebp-4h]

  result = a3;
  if ( a3 >= *(this + 13) && a3 < *(this + 15) )
  {
    v10 = 0;
    v7 = a4;
    if ( a2 < 0 )
      v7 = a2 + a4;
    else
      v10 = a2;
    v8 = *(this + 14);
    if ( a2 + a4 >= v8 )
      v7 += v8 - a2 - a4;
    result = a5 & 0xFF00FF00 | ((uint8_t)a5 << 16) | BYTE2(a5);
    v9 = (void *)(*(uint32_t *)(*(this + 4) + 4 * a3) + 4 * v10);
    if ( v7 > 0 )
      memset32(v9, result, v7);
  }
  return result;
}



// ------------------------------------------------------------
// 0x411590 sub_411590
// ------------------------------------------------------------
int /*thiscall*/ sub_411590(uint32_t *this, FILE *Stream)
{
  int v5; // eax
  uint32_t *v6; // ebx
  size_t v7; // eax
  size_t v8; // [esp+8h] [ebp-Ch]
  int v9; // [esp+Ch] [ebp-8h] BYREF
  int Buffer; // [esp+10h] [ebp-4h] BYREF
  FILE *Streama; // [esp+1Ch] [ebp+8h]

  if ( Stream == nullptr )
    return 0x80000000;
  v5 = *(this + 6) * *(this + 5);
  v6 = this + 6;
  Buffer = 5;
  v9 = 4 * v5;
  sub_66BC25(&Buffer, 4u, 1u, Stream);
  sub_66BC25(this + 5, 4u, 1u, Stream);
  sub_66BC25(this + 6, 4u, 1u, Stream);
  sub_66BC25(&v9, 4u, 1u, Stream);
  sub_66BC25(this + 7, 4u, 1u, Stream);
  sub_66BC25(this + 8, 4u, 1u, Stream);
  sub_66BC25(this + 9, 4u, 1u, Stream);
  sub_66BC25(this + 10, 4u, 1u, Stream);
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 84))(this);
  v7 = 4 * *(this + 5);
  v8 = v7;
  Streama = nullptr;
  if ( *v6 != 0 )
  {
    while ( 1 )
    {
      sub_66BC25(*(void **)(*(this + 4) + 4 * (uint32_t)Streama), v7, 1u, Stream);
      Streama = (FILE *)((char *)Streama + 1);
      if ( (unsigned int)Streama >= *v6 )
        break;
      v7 = v8;
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
  int v6; // ecx
  size_t v7; // eax
  int v8; // ecx
  size_t v9; // eax
  void *v10; // ebx
  int v11; // eax
  int v12; // eax
  size_t v13; // ecx
  int v14; // edx
  int *v15; // ecx
  void *v16; // eax
  int v17; // eax
  int v18; // ecx
  size_t v19; // eax
  int v20; // [esp+Ch] [ebp-18h] BYREF
  int Buffer; // [esp+10h] [ebp-14h] BYREF
  size_t v22; // [esp+14h] [ebp-10h]
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
  sub_66BD5A(&Buffer, 4u, 1u, v2);
  if ( Buffer == 1 )
  {
    sub_66BD5A(&v25, 4u, 1u, v2);
    sub_66BD5A(&Stream, 4u, 1u, v2);
    sub_66BD5A(&v24, 4u, 1u, v2);
    result = (*(int (/*thiscall*/ **)(int *, int, FILE *))(*this + 12))(this, v25, Stream);
    if ( result >= 0 )
    {
      (*(void (/*thiscall*/ **)(int *))(*this + 84))(this);
      v6 = *(this + 6);
      v7 = 4 * *(this + 5);
      v22 = v7;
      if ( v6 != 0 )
      {
        while ( 1 )
        {
          sub_66BD5A(*(void **)(*(this + 4) + 4 * v3++), v7, 1u, v2);
          if ( v3 >= *(this + 6) )
            break;
          v7 = v22;
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
        sub_66BD5A(&v25, 4u, 1u, v2);
        sub_66BD5A(&Stream, 4u, 1u, v2);
        sub_66BD5A(&v24, 4u, 1u, v2);
        sub_66BD5A(this + 7, 4u, 1u, v2);
        sub_66BD5A(this + 8, 4u, 1u, v2);
        result = (*(int (/*thiscall*/ **)(int *, int, FILE *))(*this + 12))(this, v25, Stream);
        if ( result < 0 )
          return result;
        v10 = operator new(2 * *(this + 20) + 12);
        if ( v10 != nullptr )
        {
          (*(void (/*thiscall*/ **)(int *))(*this + 84))(this);
          v11 = *(this + 6);
          v22 = 0;
          if ( v11 != 0 )
          {
            while ( 1 )
            {
              v12 = *(this + 20);
              ElementSize = 0;
              v20 = v12;
              sub_66BD5A(&ElementSize, 4u, 1u, v2);
              sub_66BD5A(v10, ElementSize, 1u, v2);
              if ( sub_652E00(*(uint32_t *)(*(this + 4) + 4 * v22), &v20, v10, ElementSize) != 0 )
                break;
              v13 = *(this + 6);
              if ( ++v22 >= v13 )
                goto LABEL_22;
            }
            v14 = *this;
            v15 = this;
            goto LABEL_24;
          }
          goto LABEL_22;
        }
        break;
      case 4:
        sub_66BD5A(&v25, 4u, 1u, v2);
        sub_66BD5A(&Stream, 4u, 1u, v2);
        sub_66BD5A(&v24, 4u, 1u, v2);
        sub_66BD5A(this + 7, 4u, 1u, v2);
        sub_66BD5A(this + 8, 4u, 1u, v2);
        result = (*(int (/*thiscall*/ **)(int *, int, FILE *))(*this + 12))(this, v25, Stream);
        if ( result < 0 )
          return result;
        ElementSize = 0;
        sub_66BD5A(&ElementSize, 4u, 1u, v2);
        v16 = operator new(ElementSize);
        v10 = v16;
        if ( v16 != nullptr )
        {
          sub_66BD5A(v16, ElementSize, 1u, v2);
          (*(void (/*thiscall*/ **)(int *))(*this + 84))(this);
          v20 = *(this + 6) * *(this + 20);
          v17 = sub_652E00(*(this + 3), &v20, v10, ElementSize);
          v15 = this;
          if ( v17 != 0 )
          {
            v14 = *this;
LABEL_24:
            (*(void (/*fastcall*/ **)(int *))(v14 + 88))(v15);
            j_j__free(v10);
            return 0x80000000;
          }
LABEL_22:
          (*(void (/*thiscall*/ **)(int *))(*this + 88))(this);
          j_j__free(v10);
          return 1;
        }
        break;
      case 5:
        sub_66BD5A(&v25, 4u, 1u, v2);
        sub_66BD5A(&Stream, 4u, 1u, v2);
        sub_66BD5A(&v24, 4u, 1u, v2);
        sub_66BD5A(this + 7, 4u, 1u, v2);
        sub_66BD5A(this + 8, 4u, 1u, v2);
        sub_66BD5A(this + 9, 4u, 1u, v2);
        sub_66BD5A(this + 10, 4u, 1u, v2);
        result = (*(int (/*thiscall*/ **)(int *, int, FILE *))(*this + 12))(this, v25, Stream);
        if ( result >= 0 )
        {
          (*(void (/*thiscall*/ **)(int *))(*this + 84))(this);
          v18 = *(this + 6);
          v19 = 4 * *(this + 5);
          v20 = v19;
          if ( v18 != 0 )
          {
            while ( 1 )
            {
              sub_66BD5A(*(void **)(*(this + 4) + 4 * v3++), v19, 1u, v2);
              if ( v3 >= *(this + 6) )
                break;
              v19 = v20;
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
  sub_66BD5A(&v25, 4u, 1u, v2);
  sub_66BD5A(&Stream, 4u, 1u, v2);
  sub_66BD5A(&v24, 4u, 1u, v2);
  sub_66BD5A(this + 7, 4u, 1u, v2);
  sub_66BD5A(this + 8, 4u, 1u, v2);
  result = (*(int (/*thiscall*/ **)(int *, int, FILE *))(*this + 12))(this, v25, Stream);
  if ( result >= 0 )
  {
    (*(void (/*thiscall*/ **)(int *))(*this + 84))(this);
    v8 = *(this + 6);
    v9 = 4 * *(this + 5);
    v22 = v9;
    if ( v8 != 0 )
    {
      while ( 1 )
      {
        sub_66BD5A(*(void **)(*(this + 4) + 4 * v3++), v9, 1u, v2);
        if ( v3 >= *(this + 6) )
          break;
        v9 = v22;
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
int /*thiscall*/ sub_411B30(uint32_t *this, int **a2)
{
  int v2; // eax
  uint32_t *v3; // edi
  uint32_t *v4; // ebx
  int v5; // eax
  int v6; // ecx
  char *v7; // ebx
  int result; // eax
  int v9; // edx
  void *v10; // ecx
  unsigned int v11; // eax
  int v12; // eax
  int v13; // ecx
  uint32_t *v14; // ebx
  int v15; // edx
  int v16; // edx
  void *v17; // ecx
  unsigned int v18; // eax
  int v19; // eax
  int v20; // ecx
  uint32_t *v21; // ebx
  int v22; // edx
  int *v23; // ebx
  void *v24; // esi
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
  void *v35; // edi
  uint32_t *v36; // esi
  bool v37; // cf
  int v38; // eax
  int v39; // ecx
  uint32_t *v40; // ebx
  int v41; // edx
  size_t *v42; // ebx
  char *v43; // ebx
  char *v44; // eax
  uint32_t *v45; // esi
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
  uint32_t *v60; // [esp+18h] [ebp-4h]

  v2 = **a2;
  v3 = this;
  v4 = *a2 + 1;
  v60 = this;
  if ( v2 == 1 )
  {
    v5 = *v4;
    v6 = v4[1];
    v7 = (char *)(v4 + 3);
    result = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*v3 + 12))(v3, v5, v6);
    if ( result >= 0 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *))(*v3 + 84))(v3);
      v9 = v3[6];
      v10 = (void *)(4 * v3[5]);
      v11 = 0;
      Block = v10;
      if ( v9 != 0 )
      {
        do
        {
          qmemcpy(*(void **)(v3[4] + 4 * v11), v7, (unsigned int)v10);
          v10 = Block;
          v7 = &v7[(uint32_t)Block];
          ++v11;
          v3 = v60;
        }
        while ( v11 < v60[6] );
      }
LABEL_34:
      (*(void (/*thiscall*/ **)(uint32_t *))(*v3 + 88))(v3);
      *a2 = (int *)v7;
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
        v3[7] = v22;
        v3[8] = v21[1];
        v23 = v21 + 2;
        result = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*v3 + 12))(v3, v19, v20);
        if ( result < 0 )
          return result;
        v24 = operator new(2 * v3[20] + 12);
        Block = v24;
        if ( v24 != nullptr )
        {
          (*(void (/*thiscall*/ **)(uint32_t *))(*v3 + 84))(v3);
          v25 = v3[6];
          v59 = 0;
          if ( v25 == 0 )
          {
LABEL_18:
            (*(void (/*thiscall*/ **)(uint32_t *))(*v3 + 88))(v3);
            j_j__free(v24);
            *a2 = v23;
            return 1;
          }
          while ( 1 )
          {
            v26 = v3[20];
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
            v35 = Block;
            v36 = v60;
            v23 = (int *)&v31[v28];
            if ( sub_652E00(*(uint32_t *)(v60[4] + 4 * v34), (int *)&v57, (uint8_t *)Block, v28) != 0 )
              break;
            v37 = (unsigned int)++v59 < v36[6];
            v3 = v36;
            if ( !v37 )
            {
              v24 = Block;
              goto LABEL_18;
            }
          }
          (*(void (/*thiscall*/ **)(uint32_t *))(*v36 + 88))(v36);
LABEL_20:
          j_j__free(v35);
          return 0x80000000;
        }
        break;
      case 4:
        v38 = *v4;
        v39 = v4[1];
        v40 = v4 + 1;
        v41 = v40[2];
        v40 += 2;
        v3[7] = v41;
        v3[8] = v40[1];
        v42 = v40 + 2;
        result = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*v3 + 12))(v3, v38, v39);
        if ( result < 0 )
          return result;
        v57 = *v42;
        v43 = (char *)(v42 + 1);
        v44 = (char *)operator new(v57);
        Block = v44;
        if ( v44 != nullptr )
        {
          qmemcpy(v44, v43, v57);
          v45 = v60;
          v46 = (int *)&v43[v57];
          (*(void (/*thiscall*/ **)(uint32_t *))(*v60 + 84))(v60);
          v35 = Block;
          v56 = v60[3];
          v59 = v45[6] * v45[20];
          if ( sub_652E00(v56, &v59, (uint8_t *)Block, v57) == 0 )
          {
            (*(void (/*thiscall*/ **)(uint32_t *))(*v45 + 88))(v45);
            j_j__free(Block);
            *a2 = v46;
            return 1;
          }
          (*(void (/*thiscall*/ **)(uint32_t *))(*v45 + 88))(v45);
          goto LABEL_20;
        }
        break;
      case 5:
        v47 = *v4;
        v48 = v4[1];
        v49 = v4 + 1;
        v50 = v49[2];
        v49 += 2;
        v3[7] = v50;
        v51 = v49[1];
        ++v49;
        v3[8] = v51;
        v52 = v49[1];
        ++v49;
        v3[9] = v52;
        v3[10] = v49[1];
        v7 = (char *)(v49 + 2);
        result = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*v3 + 12))(v3, v47, v48);
        if ( result >= 0 )
        {
          (*(void (/*thiscall*/ **)(uint32_t *))(*v3 + 84))(v3);
          v53 = v3[6];
          v54 = 4 * v3[5];
          v55 = 0;
          v57 = v54;
          if ( v53 != 0 )
          {
            do
            {
              qmemcpy(*(void **)(v3[4] + 4 * v55), v7, v54);
              v54 = v57;
              v7 += v57;
              ++v55;
              v3 = v60;
            }
            while ( v55 < v60[6] );
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
  v3[7] = v15;
  v3[8] = v14[1];
  v7 = (char *)(v14 + 2);
  result = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*v3 + 12))(v3, v12, v13);
  if ( result >= 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*v3 + 84))(v3);
    v16 = v3[6];
    v17 = (void *)(4 * v3[5]);
    v18 = 0;
    Block = v17;
    if ( v16 != 0 )
    {
      do
      {
        qmemcpy(*(void **)(v3[4] + 4 * v18), v7, (unsigned int)v17);
        v17 = Block;
        v7 = &v7[(uint32_t)Block];
        ++v18;
        v3 = v60;
      }
      while ( v18 < v60[6] );
    }
    goto LABEL_34;
  }
  return result;
}


// ------------------------------------------------------------
// 0x411EB0 sub_411EB0
// ------------------------------------------------------------
int /*thiscall*/ sub_411EB0(uint32_t *this, FILE *Stream)
{
  FILE *v2; // edi
  int v5; // ebx
  int v6; // ebx
  int v7; // ebx

  v2 = Stream;
  if ( Stream == nullptr )
    return 0x80000000;
  Stream = nullptr;
  ftell(v2);
  sub_66BD5A(&Stream, 4u, 1u, v2);
  ftell(v2);
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
      sub_66BD5A(&dword_8A76F8, 0x1Cu, 1u, v2);
      *(this + 5) = dword_8A76F8;
      v6 = *(this + 5);
      *(this + 6) = dword_8A76FC;
      v7 = *(this + 6) * v6;
      *(this + 7) = dword_8A7704;
      *(this + 8) = dword_8A7708;
      *(this + 9) = dword_8A770C;
      *(this + 10) = dword_8A7710;
      return 4 * v7 + 32;
    }
    return v5;
  }
}



// ------------------------------------------------------------
// 0x411FD0 sub_411FD0
// ------------------------------------------------------------
int /*thiscall*/ sub_411FD0(int this)
{
  uint32_t *v3; // eax
  int v4; // ebx
  unsigned int v5; // ecx
  int v6; // edx
  int v7; // edi
  size_t v8; // [esp-4h] [ebp-8h]

  if ( *(uint32_t *)(this + 12) == 0 )
    return -2147483647;
  if ( *(uint32_t *)(this + 16) != 0 )
    j_j__free(*(void **)(this + 16));
  v8 = 4 * *(uint32_t *)(this + 24);
  *(uint32_t *)(this + 16) = 0;
  v3 = operator new(v8);
  if ( v3 == nullptr )
    return -2147483640;
  v4 = *(uint32_t *)(this + 24);
  v5 = 0;
  v6 = 0;
  v7 = *(uint32_t *)(this + 12);
  *(uint32_t *)(this + 16) = v3;
  if ( v4 != 0 )
  {
    do
    {
      v3[v5] = v6 + v7;
      v6 += *(uint32_t *)(this + 80);
      ++v5;
    }
    while ( v5 < *(uint32_t *)(this + 24) );
  }
  return 1;
}



// ------------------------------------------------------------
// 0x412040 sub_412040
// ------------------------------------------------------------
int /*thiscall*/ sub_412040(uint32_t *this, FILE *Stream)
{
  int v5; // eax
  uint32_t *v6; // ebx
  size_t v7; // eax
  size_t v8; // [esp+8h] [ebp-Ch]
  int v9; // [esp+Ch] [ebp-8h] BYREF
  int Buffer; // [esp+10h] [ebp-4h] BYREF
  FILE *Streama; // [esp+1Ch] [ebp+8h]

  if ( Stream == nullptr )
    return 0x80000000;
  v5 = *(this + 6) * *(this + 5);
  v6 = this + 6;
  Buffer = 5;
  v9 = 4 * v5;
  sub_66BC25(&Buffer, 4u, 1u, Stream);
  sub_66BC25(this + 5, 4u, 1u, Stream);
  sub_66BC25(this + 6, 4u, 1u, Stream);
  sub_66BC25(&v9, 4u, 1u, Stream);
  sub_66BC25(this + 7, 4u, 1u, Stream);
  sub_66BC25(this + 8, 4u, 1u, Stream);
  sub_66BC25(this + 9, 4u, 1u, Stream);
  sub_66BC25(this + 10, 4u, 1u, Stream);
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 84))(this);
  v7 = 2 * *(this + 5);
  v8 = v7;
  Streama = nullptr;
  if ( *v6 != 0 )
  {
    while ( 1 )
    {
      sub_66BC25(*(void **)(*(this + 4) + 4 * (uint32_t)Streama), v7, 1u, Stream);
      Streama = (FILE *)((char *)Streama + 1);
      if ( (unsigned int)Streama >= *v6 )
        break;
      v7 = v8;
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
  int v7; // eax
  size_t v8; // eax
  int v9; // ecx
  int v10; // eax
  void *v11; // edi
  void *v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // edi
  unsigned int v16; // ecx
  int v17; // ecx
  int v18; // eax
  int v19; // eax
  int v20; // edi
  unsigned int v21; // ecx
  size_t v22; // eax
  size_t v23; // [esp-8h] [ebp-2Ch]
  int v24; // [esp+Ch] [ebp-18h] BYREF
  void *v25; // [esp+10h] [ebp-14h]
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
  sub_66BD5A(&Buffer, 4u, 1u, Stream);
  if ( Buffer == 1 )
  {
    sub_66BD5A(&dword_8A7720, 0xCu, 1u, Stream);
    result = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*this + 12))(this, dword_8A7720, dword_8A7724);
    if ( result >= 0 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 84))(this);
      if ( *((uint8_t *)this + 136) != 0 )
      {
        Block = operator new(4 * *(this + 5));
        for ( Streama = nullptr; (unsigned int)Streama < *(this + 6); Streama = (FILE *)((char *)Streama + 1) )
        {
          sub_66BD5A(Block, 4 * *(this + 5), 1u, v2);
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
        sub_66BD5A(&dword_8A7720, 8u, 1u, Stream);
        *(this + 7) = dword_8A7720;
        v7 = *(this + 5);
        *(this + 8) = dword_8A7724;
        v8 = 2 * v7;
        Streamb = (FILE *)v8;
        if ( *(this + 6) != 0 )
        {
          while ( 1 )
          {
            sub_66BD5A(*(void **)(*(this + 4) + 4 * v3++), v8, 1u, v2);
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
      sub_66BD5A(&dword_8A7720, 0x1Cu, 1u, Stream);
      v17 = dword_8A7724;
      v18 = dword_8A7720;
      *(this + 7) = dword_8A772C;
      *(this + 8) = dword_8A7730;
      *(this + 9) = dword_8A7734;
      *(this + 10) = dword_8A7738;
      result = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*this + 12))(this, v18, v17);
      if ( result < 0 )
        return result;
      if ( *((uint8_t *)this + 136) != 0 )
      {
        (*(void (/*thiscall*/ **)(uint32_t *))(*this + 84))(this);
        ElementSize = (size_t)operator new(4 * *(this + 5));
        v19 = *(this + 6);
        v27 = 0;
        if ( v19 != 0 )
        {
          do
          {
            sub_66BD5A((void *)ElementSize, 4 * *(this + 5), 1u, v2);
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
            v21 = *(this + 6);
            ++v27;
          }
          while ( v27 < v21 );
        }
        j_j__free((void *)ElementSize);
        (*(void (/*thiscall*/ **)(uint32_t *))(*this + 88))(this);
        return 1;
      }
      v22 = 2 * *(this + 5);
      Streamc = (FILE *)v22;
      if ( *(this + 6) != 0 )
      {
        while ( 1 )
        {
          sub_66BD5A(*(void **)(*(this + 4) + 4 * v3++), v22, 1u, v2);
          if ( v3 >= *(this + 6) )
            break;
          v22 = (size_t)Streamc;
        }
      }
      return 1;
    }
    return 0x80000000;
  }
  sub_66BD5A(&dword_8A7720, 0x14u, 1u, Stream);
  v9 = dword_8A7724;
  v10 = dword_8A7720;
  *(this + 7) = dword_8A772C;
  *(this + 8) = dword_8A7730;
  result = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*this + 12))(this, v10, v9);
  if ( result < 0 )
    return result;
  if ( *((uint8_t *)this + 136) == 0 )
    return 1;
  v11 = operator new(2 * *(this + 20) + 12);
  v23 = 4 * *(this + 5);
  v25 = v11;
  v12 = operator new(v23);
  Block = v12;
  if ( v11 != nullptr )
  {
    if ( v12 == nullptr )
    {
      j_j__free(v11);
      return -2147483640;
    }
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 84))(this);
    v13 = *(this + 6);
    v27 = 0;
    if ( v13 == 0 )
    {
LABEL_26:
      (*(void (/*thiscall*/ **)(uint32_t *))(*this + 88))(this);
      j_j__free(Block);
      j_j__free(v11);
      return 1;
    }
    while ( 1 )
    {
      v14 = 4 * *(this + 5);
      ElementSize = 0;
      v24 = v14;
      sub_66BD5A(&ElementSize, 4u, 1u, v2);
      sub_66BD5A(v11, ElementSize, 1u, v2);
      if ( sub_652E00(Block, &v24, v11, ElementSize) != 0 )
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
      v16 = *(this + 6);
      v11 = v25;
      if ( ++v27 >= v16 )
        goto LABEL_26;
    }
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 88))(this);
    j_j__free(Block);
    j_j__free(v11);
    return 0x80000000;
  }
  if ( v12 != nullptr )
    j_j__free(v12);
  return -2147483640;
}


// ------------------------------------------------------------
// 0x4125D0 sub_4125D0
// ------------------------------------------------------------
int /*thiscall*/ sub_4125D0(int this, FILE *Buffer)
{
  FILE *v2; // edi
  int v5; // ebx
  int v6; // eax
  int v7; // edx
  char v8; // cl
  char v9; // cl

  v2 = Buffer;
  if ( Buffer == nullptr )
    return 0x80000000;
  Buffer = nullptr;
  sub_66BD5A(&Buffer, 4u, 1u, v2);
  v5 = 4;
  if ( Buffer == (FILE *)1 )
  {
    sub_66BD5A(&dword_8A7720, 0xCu, 1u, v2);
    v6 = dword_8A7720;
    *(uint32_t *)(this + 20) = dword_8A7720;
    v7 = dword_8A7724;
    *(uint32_t *)(this + 28) = 0;
    *(uint32_t *)(this + 32) = 0;
    v8 = *(uint8_t *)(this + 136);
    *(uint32_t *)(this + 24) = v7;
    *(uint32_t *)(this + 36) = v6;
    *(uint32_t *)(this + 40) = v7;
    v5 = 2 * v6 * v7 * ((v8 == 1) + 1) + 16;
    if ( v8 == 0 )
      return 2 * v6 * v7 * ((v8 == 1) + 1) + 24;
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
      sub_66BD5A(&dword_8A7720, 0x1Cu, 1u, v2);
      *(uint32_t *)(this + 20) = dword_8A7720;
      *(uint32_t *)(this + 24) = dword_8A7724;
      *(uint32_t *)(this + 28) = dword_8A772C;
      *(uint32_t *)(this + 32) = dword_8A7730;
      *(uint32_t *)(this + 36) = dword_8A7734;
      v9 = *(uint8_t *)(this + 136);
      *(uint32_t *)(this + 40) = dword_8A7738;
      return 2 * *(uint32_t *)(this + 24) * *(uint32_t *)(this + 20) * ((v9 == 1) + 1) + 32;
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
int /*thiscall*/ sub_412700(unsigned int *this, int **a2)
{
  int v2; // eax
  int *v3; // esi
  int *v5; // esi
  int result; // eax
  int v7; // eax
  unsigned int i; // edi
  unsigned int v9; // ecx
  int v10; // ecx
  int v11; // eax
  uint32_t *v12; // esi
  int v13; // ecx
  unsigned int v14; // edx
  unsigned int v15; // eax
  unsigned int v16; // ecx
  int v17; // eax
  int v18; // ecx
  uint32_t *v19; // esi
  int *v20; // edi
  void *v21; // eax
  int v22; // eax
  int v23; // eax
  unsigned int v24; // edx
  void *v25; // esi
  uint32_t *v26; // edi
  int v27; // esi
  unsigned int v28; // ecx
  int v29; // eax
  int v30; // ecx
  uint32_t *v31; // esi
  unsigned int v32; // edx
  unsigned int v33; // edx
  unsigned int v34; // edx
  int v35; // eax
  int v36; // eax
  unsigned int v37; // edx
  int v38; // ecx
  int v39; // edi
  int v40; // eax
  unsigned int v41; // ecx
  int v42; // edx
  unsigned int v43; // ecx
  unsigned int v44; // eax
  unsigned int v45; // edx
  int v46; // [esp-8h] [ebp-28h]
  size_t v47; // [esp-8h] [ebp-28h]
  int v48; // [esp-4h] [ebp-24h]
  int v49; // [esp+Ch] [ebp-14h] BYREF
  void *Block; // [esp+10h] [ebp-10h]
  void *v51; // [esp+14h] [ebp-Ch]
  int v52; // [esp+18h] [ebp-8h]
  int *v53; // [esp+1Ch] [ebp-4h]

  v2 = **a2;
  v3 = *a2 + 1;
  if ( v2 == 1 )
  {
    v46 = *v3;
    v5 = *a2 + 4;
    result = (*(int (/*thiscall*/ **)(unsigned int *, int, int))(*this + 12))(this, v46, (*a2)[2]);
    if ( result >= 0 )
    {
      (*(void (/*thiscall*/ **)(unsigned int *))(*this + 84))(this);
      if ( *((uint8_t *)this + 136) != 0 )
      {
        v7 = *(this + 6);
        v53 = nullptr;
        if ( v7 != 0 )
        {
          do
          {
            for ( i = 0; i < *(this + 5); ++i )
            {
              v48 = *v5++;
              (*(void (/*thiscall*/ **)(unsigned int *, unsigned int, int *, int))(*this + 32))(this, i, v53, v48);
            }
            v9 = *(this + 6);
            v53 = (int *)((char *)v53 + 1);
          }
          while ( (unsigned int)v53 < v9 );
        }
      }
      else
      {
        v10 = *v5;
        v11 = *(this + 5);
        v12 = v5 + 1;
        *(this + 7) = v10;
        v13 = *(this + 6);
        *(this + 8) = *v12;
        v5 = v12 + 1;
        v14 = 0;
        v15 = 2 * v11;
        v53 = v5;
        Block = nullptr;
        if ( v13 != 0 )
        {
          do
          {
            qmemcpy(*(void **)(*(this + 4) + 4 * v14), v5, v15);
            v16 = *(this + 6);
            v14 = (unsigned int)Block + 1;
            v53 = (int *)((char *)v53 + v15);
            Block = (void *)v14;
            v5 = v53;
          }
          while ( v14 < v16 );
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
    v18 = (*a2)[2];
    v19 = *a2 + 4;
    *(this + 7) = *v19;
    *(this + 8) = v19[1];
    v5 = v19 + 2;
    result = (*(int (/*thiscall*/ **)(unsigned int *, int, int))(*this + 12))(this, v17, v18);
    if ( result < 0 )
      return result;
    if ( *((uint8_t *)this + 136) == 0 )
    {
LABEL_43:
      *a2 = v5;
      return 1;
    }
    v20 = (int *)operator new(2 * *(this + 20) + 12);
    v47 = 4 * *(this + 5);
    v51 = v20;
    v21 = operator new(v47);
    Block = v21;
    if ( v20 == nullptr )
    {
      if ( v21 != nullptr )
        j_j__free(v21);
      return -2147483640;
    }
    if ( v21 == nullptr )
    {
      j_j__free(v20);
      return -2147483640;
    }
    (*(void (/*thiscall*/ **)(unsigned int *))(*this + 84))(this);
    v22 = *(this + 6);
    v52 = 0;
    if ( v22 == 0 )
    {
LABEL_24:
      (*(void (/*thiscall*/ **)(unsigned int *))(*this + 88))(this);
      j_j__free(Block);
      j_j__free(v20);
      *a2 = v5;
      return 1;
    }
    while ( 1 )
    {
      v49 = 4 * *(this + 5);
      v23 = *v5;
      v24 = *v5;
      v53 = v5 + 1;
      qmemcpy(v20, v5 + 1, v24);
      v25 = v51;
      v53 = (int *)((char *)v53 + v23);
      v26 = Block;
      if ( sub_652E00(Block, &v49, v51, v23) != 0 )
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
            v26[v27] & 0xFF00FF00 | ((uint8_t)v26[v27] << 16) | BYTE2(v26[v27]));
          if ( ++v27 >= (int)*(this + 5) )
            break;
          v26 = Block;
        }
      }
      v28 = *(this + 6);
      v5 = v53;
      v20 = (int *)v51;
      if ( ++v52 >= v28 )
        goto LABEL_24;
    }
    (*(void (/*thiscall*/ **)(unsigned int *))(*this + 88))(this);
    j_j__free(v26);
    j_j__free(v25);
    return 0x80000000;
  }
  if ( v2 != 5 )
    return 0x80000000;
  v29 = *v3;
  v30 = (*a2)[2];
  v31 = *a2 + 4;
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
      v35 = *(this + 6);
      Block = nullptr;
      if ( v35 != 0 )
      {
        do
        {
          v36 = *(this + 5);
          v51 = nullptr;
          if ( v36 > 0 )
          {
            do
            {
              v37 = *this;
              v38 = (uint8_t)BYTE2(*v5);
              v39 = (uint8_t)*v5;
              v49 = *v5++;
              (*(void (/*thiscall*/ **)(unsigned int *, void *, void *, unsigned int))(v37 + 32))(
                this,
                v51,
                Block,
                v49 & 0xFF00FF00 | (v39 << 16) | v38);
              v40 = *(this + 5);
              v51 = (char *)v51 + 1;
            }
            while ( (int)v51 < v40 );
          }
          v41 = *(this + 6);
          Block = (char *)Block + 1;
        }
        while ( (unsigned int)Block < v41 );
      }
    }
    else
    {
      v42 = *(this + 6);
      v43 = 2 * *(this + 5);
      v44 = 0;
      v49 = v43;
      if ( v42 != 0 )
      {
        do
        {
          qmemcpy(*(void **)(*(this + 4) + 4 * v44), v5, v43);
          v43 = v49;
          v45 = *(this + 6);
          ++v44;
          v53 = (int *)((char *)v53 + v49);
          v5 = v53;
        }
        while ( v44 < v45 );
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
// 0x412AE0 sub_412AE0
// ------------------------------------------------------------
int /*thiscall*/ sub_412AE0(uint32_t *this, unsigned int a2)
{
  unsigned int i; // edi
  int v4; // edx
  unsigned int j; // eax
  int result; // eax

  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 84))(this);
  for ( i = 0; i < *(this + 6); ++i )
  {
    v4 = *(uint32_t *)(*(this + 4) + 4 * i);
    for ( j = 0; j < *(this + 5); ++j )
    {
      if ( *(uint16_t *)(v4 + 2 * j) == ((uint16_t)(16 * (a2 & 0xF0))
                                    | (a2 >> 20) & 0xF
                                    | (a2 >> 8) & 0xF0
                                    | HIWORD(a2) & 0xF000) )
        *(uint16_t *)(v4 + 2 * j) = 0;
    }
  }
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 88))(this);
  *(this + 17) = a2;
  return result;
}



// ------------------------------------------------------------
// 0x412B70 sub_412B70
// ------------------------------------------------------------
int /*thiscall*/ sub_412B70(uint32_t *this, unsigned int a2)
{
  int result; // eax
  int16_t v4; // bx
  int v5; // edi
  unsigned int v6; // esi
  unsigned int v7; // ecx
  uint16_t *v8; // edi
  int v9; // [esp+0h] [ebp-4h]
  int v10; // [esp+Ch] [ebp+8h]

  result = *(this + 3);
  if ( result != 0 )
  {
    v9 = *(this + 4);
    v4 = a2;
    v5 = *(this + 6);
    v6 = *(this + 5) >> 1;
    result = (((uint16_t)(16 * (a2 & 0xF0)) | (a2 >> 20) & 0xF | (a2 >> 8) & 0xF0 | HIWORD(a2) & 0xF000) << 16)
           | (uint16_t)(16 * (a2 & 0xF0))
           | (a2 >> 20) & 0xF
           | (a2 >> 8) & 0xF0
           | HIWORD(a2) & 0xF000;
    v7 = 0;
    v10 = 0;
    if ( v5 != 0 )
    {
      do
      {
        v8 = *(uint16_t **)(v9 + 4 * v7);
        if ( (*(uint8_t *)(this + 5) & 1) != 0 )
          *v8++ = v4;
        if ( v6 != 0 )
        {
          memset32(v8, result, v6);
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
// 0x412C20 sub_412C20
// ------------------------------------------------------------
char /*thiscall*/ sub_412C20(uint32_t *this, int a2, int a3, unsigned int a4)
{
  int v5; // eax

  LOBYTE(v5) = sub_40F530(a2, a3, this + 12);
  if ( (uint8_t)v5 == 0 )
  {
    v5 = *(this + 4);
    *(uint16_t *)(*(uint32_t *)(v5 + 4 * a3) + 2 * a2) = (16 * (a4 & 0xF0))
                                                  | (a4 >> 20) & 0xF
                                                  | (a4 >> 8) & 0xF0
                                                  | HIWORD(a4) & 0xF000;
  }
  return v5;
}



// ------------------------------------------------------------
// 0x412C80 sub_412C80
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_412C80(uint32_t *this, int a2, int a3)
{
  int v5; // esi
  int v6; // ecx

  if ( sub_40F530(a2, a3, this + 12) )
    return 0;
  v5 = *(this + 4);
  v6 = *(uint16_t *)(*(uint32_t *)(v5 + 4 * a3) + 2 * a2);
  return ((v6 & 0xF00 | 0xF0F0F0FF) >> 4)
       | ((*(uint16_t *)(*(uint32_t *)(v5 + 4 * a3) + 2 * a2) & 0xF0
         | ((v6 ^ ((uint8_t)v6 ^ (uint8_t)(16 * *(uint16_t *)(*(uint32_t *)(v5 + 4 * a3) + 2 * a2))) & 0xF0) << 8)) << 8);
}



// ------------------------------------------------------------
// 0x412CF0 sub_412CF0
// ------------------------------------------------------------
int /*thiscall*/ sub_412CF0(int *this, int a2, int a3, int a4, unsigned int a5)
{
  int result; // eax
  int v7; // ecx
  int v8; // eax
  int v9; // edx
  char *v10; // edi
  int v11; // edx
  char v12; // cf
  unsigned int v13; // ecx
  char *v14; // edi
  int i; // ecx
  int v16; // [esp+4h] [ebp-4h]

  result = a3;
  if ( a3 >= *(this + 13) && a3 < *(this + 15) )
  {
    v16 = 0;
    v7 = a4;
    if ( a2 < 0 )
      v7 = a2 + a4;
    else
      v16 = a2;
    v8 = *(this + 14);
    if ( a2 + a4 >= v8 )
      v7 += v8 - a2 - a4;
    result = (16 * (a5 & 0xF0)) | (a5 >> 20) & 0xF | (a5 >> 8) & 0xF0 | HIWORD(a5) & 0xF000;
    v9 = *(uint32_t *)(*(this + 4) + 4 * a3);
    v10 = (char *)(v9 + 2 * v16);
    if ( v7 > 0 )
    {
      LOWORD(v9) = (16 * (a5 & 0xF0)) | (a5 >> 20) & 0xF | (a5 >> 8) & 0xF0 | HIWORD(a5) & 0xF000;
      v11 = v9 << 16;
      LOWORD(v11) = (16 * (a5 & 0xF0)) | (a5 >> 20) & 0xF | (a5 >> 8) & 0xF0 | HIWORD(a5) & 0xF000;
      v12 = v7 & 1;
      v13 = (unsigned int)v7 >> 1;
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
// 0x412DA0 sub_412DA0
// ------------------------------------------------------------
int /*thiscall*/ sub_412DA0(int *this, int a2, int a3, int a4, unsigned int a5)
{
  int result; // eax
  int v6; // ebx
  int v7; // esi
  int v8; // edi
  int v9; // edx
  int v10; // esi
  int v11; // ecx
  int v13; // [esp+14h] [ebp+10h]

  result = a2;
  if ( a2 >= *(this + 12) && a2 < *(this + 14) )
  {
    v6 = a3;
    v7 = 0;
    v8 = a4;
    if ( a3 < 0 )
      v8 = a3 + a4;
    else
      v7 = a3;
    v13 = *(this + 15);
    result = (16 * (a5 & 0xF0)) | (a5 >> 20) & 0xF | (a5 >> 8) & 0xF0 | HIWORD(a5) & 0xF000;
    v9 = 0;
    if ( v8 > 0 )
    {
      v10 = 4 * v7;
      while ( v9 + v6 < v13 )
      {
        v11 = *(uint32_t *)(*(this + 4) + v10);
        ++v9;
        v10 += 4;
        *(uint16_t *)(v11 + 2 * a2) = result;
        if ( v9 >= v8 )
          break;
        v6 = a3;
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x412E40 sub_412E40
// ------------------------------------------------------------
int /*thiscall*/ sub_412E40(uint32_t *this, unsigned int a2)
{
  unsigned int i; // edi
  int v4; // ecx
  unsigned int j; // eax
  int result; // eax

  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 84))(this);
  for ( i = 0; i < *(this + 6); ++i )
  {
    v4 = *(uint32_t *)(*(this + 4) + 4 * i);
    for ( j = 0; j < *(this + 5); ++j )
    {
      if ( *(uint16_t *)(v4 + 2 * j) == (((a2 & 0xF8) << 7) | HIWORD(a2) & 0x8000 | (a2 >> 19) & 0x1F | (a2 >> 6) & 0x3E0) )
        *(uint16_t *)(v4 + 2 * j) = 0;
    }
  }
  result = (*(int (/*thiscall*/ **)(uint32_t *))(*this + 88))(this);
  *(this + 17) = a2;
  return result;
}



// ------------------------------------------------------------
// 0x412ED0 sub_412ED0
// ------------------------------------------------------------
int /*thiscall*/ sub_412ED0(uint32_t *this, unsigned int a2)
{
  int result; // eax
  int16_t v4; // bx
  int v5; // edi
  unsigned int v6; // esi
  unsigned int v7; // ecx
  uint16_t *v8; // edi
  int v9; // [esp+0h] [ebp-4h]
  int v10; // [esp+Ch] [ebp+8h]

  result = *(this + 3);
  if ( result != 0 )
  {
    v9 = *(this + 4);
    v4 = a2;
    v5 = *(this + 6);
    v6 = *(this + 5) >> 1;
    result = ((((a2 & 0xF8) << 7) | HIWORD(a2) & 0x8000 | (a2 >> 19) & 0x1F | (a2 >> 6) & 0x3E0) << 16)
           | ((a2 & 0xF8) << 7)
           | HIWORD(a2) & 0x8000
           | (a2 >> 19) & 0x1F
           | (a2 >> 6) & 0x3E0;
    v7 = 0;
    v10 = 0;
    if ( v5 != 0 )
    {
      do
      {
        v8 = *(uint16_t **)(v9 + 4 * v7);
        if ( (*(uint8_t *)(this + 5) & 1) != 0 )
          *v8++ = v4;
        if ( v6 != 0 )
        {
          memset32(v8, result, v6);
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
// 0x412F80 sub_412F80
// ------------------------------------------------------------
int /*thiscall*/ sub_412F80(int this, unsigned int *a2, unsigned int a3)
{
  int result; // eax
  signed int v5; // esi
  unsigned int v6; // edx
  signed int v7; // ecx
  uint16_t *v8; // edi
  int v10; // [esp+4h] [ebp-4h]
  signed int v11; // [esp+10h] [ebp+8h]

  result = *(uint32_t *)(this + 12);
  if ( result != 0 )
  {
    v10 = *(uint32_t *)(this + 16);
    v5 = a2[3];
    v6 = (int)(a2[2] - *a2) >> 1;
    result = ((((a3 & 0xF8) << 7) | HIWORD(a3) & 0x8000 | (a3 >> 19) & 0x1F | (a3 >> 6) & 0x3E0) << 16)
           | ((a3 & 0xF8) << 7)
           | HIWORD(a3) & 0x8000
           | (a3 >> 19) & 0x1F
           | (a3 >> 6) & 0x3E0;
    v11 = a2[1];
    v7 = v11;
    if ( v11 < v5 )
    {
      do
      {
        v8 = *(uint16_t **)(v10 + 4 * v7);
        if ( (*(uint8_t *)(this + 20) & 1) != 0 )
        {
          *v8 = a3;
          v7 = v11;
          ++v8;
        }
        if ( *a2 <= v6 )
        {
          memset32(&v8[2 * *a2], result, v6 - *a2 + 1);
          v7 = v11;
        }
        v11 = ++v7;
      }
      while ( v7 < (int)a2[3] );
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x413040 sub_413040
// ------------------------------------------------------------
char /*thiscall*/ sub_413040(uint32_t *this, int a2, int a3, unsigned int a4)
{
  int v5; // eax

  LOBYTE(v5) = sub_40F530(a2, a3, this + 12);
  if ( (uint8_t)v5 == 0 )
  {
    v5 = *(this + 4);
    *(uint16_t *)(*(uint32_t *)(v5 + 4 * a3) + 2 * a2) = ((a4 & 0xF8) << 7)
                                                  | HIWORD(a4) & 0x8000
                                                  | (a4 >> 19) & 0x1F
                                                  | (a4 >> 6) & 0x3E0;
  }
  return v5;
}



// ------------------------------------------------------------
// 0x4130A0 sub_4130A0
// ------------------------------------------------------------
int /*thiscall*/ sub_4130A0(uint32_t *this, int a2, int a3)
{
  int v5; // esi
  unsigned int v6; // ecx

  if ( sub_40F530(a2, a3, this + 12) )
    return 0;
  v5 = *(this + 4);
  v6 = *(uint16_t *)(*(uint32_t *)(v5 + 4 * a3) + 2 * a2);
  return (v6 >> 7) & 0xF8
       | ((*(uint16_t *)(*(uint32_t *)(v5 + 4 * a3) + 2 * a2) & 0x3E0
         | ((v6 ^ ((uint8_t)v6 ^ (uint8_t)(8 * v6)) & 0xF8) << 10)) << 6)
       | 0x7F070707;
}



// ------------------------------------------------------------
// 0x413110 sub_413110
// ------------------------------------------------------------
int /*thiscall*/ sub_413110(int *this, int a2, int a3, int a4, unsigned int a5)
{
  int result; // eax
  int v7; // ecx
  int v8; // eax
  int v9; // edx
  char *v10; // edi
  int v11; // edx
  char v12; // cf
  unsigned int v13; // ecx
  char *v14; // edi
  int i; // ecx
  int v16; // [esp+4h] [ebp-4h]

  result = a3;
  if ( a3 >= *(this + 13) && a3 < *(this + 15) )
  {
    v16 = 0;
    v7 = a4;
    if ( a2 < 0 )
      v7 = a2 + a4;
    else
      v16 = a2;
    v8 = *(this + 14);
    if ( a2 + a4 >= v8 )
      v7 += v8 - a2 - a4;
    result = ((a5 & 0xF8) << 7) | HIWORD(a5) & 0x8000 | (a5 >> 19) & 0x1F | (a5 >> 6) & 0x3E0;
    v9 = *(uint32_t *)(*(this + 4) + 4 * a3);
    v10 = (char *)(v9 + 2 * v16);
    if ( v7 > 0 )
    {
      LOWORD(v9) = ((a5 & 0xF8) << 7) | HIWORD(a5) & 0x8000 | (a5 >> 19) & 0x1F | (a5 >> 6) & 0x3E0;
      v11 = v9 << 16;
      LOWORD(v11) = ((a5 & 0xF8) << 7) | HIWORD(a5) & 0x8000 | (a5 >> 19) & 0x1F | (a5 >> 6) & 0x3E0;
      v12 = v7 & 1;
      v13 = (unsigned int)v7 >> 1;
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
// 0x4131C0 sub_4131C0
// ------------------------------------------------------------
int /*thiscall*/ sub_4131C0(int *this, int a2, int a3, int a4, unsigned int a5)
{
  int result; // eax
  int v6; // ebx
  int v7; // esi
  int v8; // edi
  int v9; // edx
  int v10; // esi
  int v11; // ecx
  int v13; // [esp+14h] [ebp+10h]

  result = a2;
  if ( a2 >= *(this + 12) && a2 < *(this + 14) )
  {
    v6 = a3;
    v7 = 0;
    v8 = a4;
    if ( a3 < 0 )
      v8 = a3 + a4;
    else
      v7 = a3;
    v13 = *(this + 15);
    result = ((a5 & 0xF8) << 7) | HIWORD(a5) & 0x8000 | (a5 >> 19) & 0x1F | (a5 >> 6) & 0x3E0;
    v9 = 0;
    if ( v8 > 0 )
    {
      v10 = 4 * v7;
      while ( v9 + v6 < v13 )
      {
        v11 = *(uint32_t *)(*(this + 4) + v10);
        ++v9;
        v10 += 4;
        *(uint16_t *)(v11 + 2 * a2) = result;
        if ( v9 >= v8 )
          break;
        v6 = a3;
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x413260 sub_413260
// ------------------------------------------------------------
int /*thiscall*/ sub_413260(void *this, uint32_t *a2)
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(void *, uint32_t, uint32_t))(*(uint32_t *)this + 12))(this, a2[5], a2[6]);
  if ( result >= 0 )
  {
    (*(void (/*thiscall*/ **)(void *, uint32_t))(*(uint32_t *)this + 28))(this, 0);
    if ( a2[2] == 8 )
    {
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, void *))(*a2 + 152))(a2, 0, 0, this);
    }
    else
    {
      (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 84))(this);
      (*(void (/*thiscall*/ **)(uint32_t *))(*a2 + 84))(a2);
      (*(void (/*thiscall*/ **)(uint32_t *, uint32_t, uint32_t, void *))(*a2 + 152))(a2, 0, 0, this);
      (*(void (/*thiscall*/ **)(uint32_t *))(*a2 + 88))(a2);
      (*(void (/*thiscall*/ **)(void *))(*(uint32_t *)this + 88))(this);
    }
    return 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4132E0 sub_4132E0
// ------------------------------------------------------------
int /*thiscall*/ sub_4132E0(int this)
{
  uint32_t *v3; // eax
  int v4; // ebx
  int v5; // edx
  unsigned int v6; // ecx
  int v7; // edi
  size_t v8; // [esp-4h] [ebp-8h]

  if ( *(uint32_t *)(this + 12) == 0 )
    return -2147483647;
  if ( *(uint32_t *)(this + 16) != 0 )
    j_j__free(*(void **)(this + 16));
  v8 = 4 * *(uint32_t *)(this + 24);
  *(uint32_t *)(this + 16) = 0;
  v3 = operator new(v8);
  if ( v3 == nullptr )
    return -2147483640;
  v4 = *(uint32_t *)(this + 24);
  v5 = 4 * *(uint32_t *)(this + 20);
  v6 = 0;
  v7 = *(uint32_t *)(this + 12);
  *(uint32_t *)(this + 16) = v3;
  if ( v4 != 0 )
  {
    do
    {
      v3[v6++] = v7;
      v7 += v5;
    }
    while ( v6 < *(uint32_t *)(this + 24) );
  }
  return 1;
}



// ------------------------------------------------------------
// 0x413360 sub_413360
// ------------------------------------------------------------
int /*thiscall*/ sub_413360(uint32_t *this, int a2)
{
  unsigned int i; // edi
  int v4; // ecx
  unsigned int j; // eax

  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 84))(this);
  for ( i = 0; i < *(this + 6); ++i )
  {
    v4 = *(uint32_t *)(*(this + 4) + 4 * i);
    for ( j = 0; j < *(this + 5); ++j )
    {
      if ( *(uint32_t *)(v4 + 4 * j) == (a2 & 0xFF00FF00 | ((uint8_t)a2 << 16) | BYTE2(a2)) )
        *(uint8_t *)(v4 + 4 * j + 3) = 0;
    }
  }
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 88))(this);
  *(this + 17) = a2;
  return a2;
}



// ------------------------------------------------------------
// 0x4133D0 sub_4133D0
// ------------------------------------------------------------
char /*thiscall*/ sub_4133D0(uint32_t *this, int a2, int a3, int a4)
{
  int v5; // eax

  LOBYTE(v5) = sub_40F530(a2, a3, this + 12);
  if ( (uint8_t)v5 == 0 )
  {
    v5 = *(this + 4);
    *(uint32_t *)(*(uint32_t *)(v5 + 4 * a3) + 4 * a2) = a4 & 0xFF00FF00 | ((uint8_t)a4 << 16) | BYTE2(a4);
  }
  return v5;
}



// ------------------------------------------------------------
// 0x413420 sub_413420
// ------------------------------------------------------------
int /*thiscall*/ sub_413420(int *this, int a2, int a3, int a4, int a5)
{
  int result; // eax
  int v6; // ebx
  int v7; // esi
  int v8; // edi
  int v9; // esi
  int v10; // ecx
  int v12; // [esp+14h] [ebp+10h]

  result = a2;
  if ( a2 >= *(this + 12) && a2 < *(this + 14) )
  {
    v6 = a3;
    v7 = 0;
    v8 = a4;
    if ( a3 < 0 )
      v8 = a3 + a4;
    else
      v7 = a3;
    v12 = *(this + 15);
    result = 0;
    if ( v8 > 0 )
    {
      v9 = 4 * v7;
      while ( result + v6 < v12 )
      {
        v10 = *(uint32_t *)(*(this + 4) + v9);
        ++result;
        v9 += 4;
        *(uint32_t *)(v10 + 4 * a2) = a5 & 0xFF00FF00 | ((uint8_t)a5 << 16) | BYTE2(a5);
        if ( result >= v8 )
          break;
        v6 = a3;
      }
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4134B0 sub_4134B0
// ------------------------------------------------------------
int /*thiscall*/ sub_4134B0(uint32_t *this, FILE *Stream)
{
  int v5; // eax
  uint32_t *v6; // ebx
  size_t v7; // eax
  size_t v8; // [esp+8h] [ebp-Ch]
  int v9; // [esp+Ch] [ebp-8h] BYREF
  int Buffer; // [esp+10h] [ebp-4h] BYREF
  FILE *Streama; // [esp+1Ch] [ebp+8h]

  if ( Stream == nullptr )
    return 0x80000000;
  v5 = *(this + 6) * *(this + 5);
  v6 = this + 6;
  Buffer = 1;
  v9 = 4 * v5;
  sub_66BC25(&Buffer, 4u, 1u, Stream);
  sub_66BC25(this + 5, 4u, 1u, Stream);
  sub_66BC25(this + 6, 4u, 1u, Stream);
  sub_66BC25(&v9, 4u, 1u, Stream);
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 84))(this);
  v7 = 4 * *(this + 5);
  v8 = v7;
  Streama = nullptr;
  if ( *v6 != 0 )
  {
    while ( 1 )
    {
      sub_66BC25(*(void **)(*(this + 4) + 4 * (uint32_t)Streama), v7, 1u, Stream);
      Streama = (FILE *)((char *)Streama + 1);
      if ( (unsigned int)Streama >= *v6 )
        break;
      v7 = v8;
    }
  }
  (*(void (/*thiscall*/ **)(uint32_t *))(*this + 88))(this);
  return 1;
}



// ------------------------------------------------------------
// 0x413580 sub_413580
// ------------------------------------------------------------
int /*thiscall*/ sub_413580(uint32_t *this, FILE *Buffer)
{
  FILE *v2; // ebx
  unsigned int v3; // edi
  int result; // eax
  size_t v6; // eax
  FILE *v7; // [esp-4h] [ebp-20h]
  size_t v8; // [esp+Ch] [ebp-10h]
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
  sub_66BD5A(&Buffer, 4u, 1u, v7);
  if ( Buffer != (FILE *)1 )
    return 0x80000000;
  sub_66BD5A(&v10, 4u, 1u, v2);
  sub_66BD5A(&v11, 4u, 1u, v2);
  sub_66BD5A(&v9, 4u, 1u, v2);
  result = (*(int (/*thiscall*/ **)(uint32_t *, int, int))(*this + 12))(this, v10, v11);
  if ( result >= 0 )
  {
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 84))(this);
    v6 = 4 * *(this + 5);
    v8 = v6;
    if ( *(this + 6) != 0 )
    {
      while ( 1 )
      {
        sub_66BD5A(*(void **)(*(this + 4) + 4 * v3++), v6, 1u, v2);
        if ( v3 >= *(this + 6) )
          break;
        v6 = v8;
      }
    }
    (*(void (/*thiscall*/ **)(uint32_t *))(*this + 88))(this);
    return 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x413670 sub_413670
// ------------------------------------------------------------
int /*thiscall*/ sub_413670(int *this, int a2)
{
  int v4; // ecx
  bool v5; // zf
  int v6; // edx
  int v7; // edi
  int v8; // [esp-Ch] [ebp-30h]
  int v9; // [esp-8h] [ebp-2Ch]
  uint32_t v10[3]; // [esp+4h] [ebp-20h] BYREF
  int v11; // [esp+10h] [ebp-14h]
  int v12; // [esp+14h] [ebp-10h]
  int v13; // [esp+18h] [ebp-Ch]
  int xRight; // [esp+1Ch] [ebp-8h]
  int yBottom; // [esp+20h] [ebp-4h]

  if ( *((uint8_t *)this + 4) != 0 )
    return -2147483646;
  memset(v10, 0, sizeof(v10));
  v11 = 0;
  v12 = 0;
  v13 = 0;
  xRight = 0;
  yBottom = 0;
  *((uint8_t *)this + 4) = 1;
  (*(void (/*stdcall*/ **)(int, uint32_t *))(*(uint32_t *)a2 + 32))(a2, v10);
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
// 0x413740 sub_413740
// ------------------------------------------------------------
int /*thiscall*/ sub_413740(int *this, int xRight, int yBottom)
{
  int v5; // eax
  int v6; // edi
  int v7; // edx

  if ( *((uint8_t *)this + 4) != 0 )
    return -2147483646;
  *((uint8_t *)this + 4) = 1;
  *(this + 5) = xRight;
  *(this + 6) = yBottom;
  SetRect((LPRECT)this + 5, 0, 0, xRight, yBottom);
  SetRect((LPRECT)this + 3, 0, 0, *(this + 5), *(this + 6));
  v5 = *(this + 27);
  *((uint8_t *)this + 76) = 0;
  v6 = (*(int (/*stdcall*/ **)(int, int, int, int, int *))(*(uint32_t *)v5 + 108))(v5, xRight, yBottom, 21, this + 26);
  if ( v6 >= 0 )
  {
    (*(void (/*thiscall*/ **)(int *))(*this + 84))(this);
    (*(void (/*thiscall*/ **)(int *))(*this + 88))(this);
    v7 = *this;
    *(this + 3) = *(this + 25);
    v6 = (*(int (/*thiscall*/ **)(int *))(v7 + 172))(this);
    if ( v6 >= 0 )
      return 1;
  }
  (*(void (/*thiscall*/ **)(int *))(*this + 20))(this);
  return v6;
}



// ------------------------------------------------------------
// 0x413800 sub_413800
// ------------------------------------------------------------
int /*thiscall*/ sub_413800(int this)
{
  int v2; // eax
  uint32_t *v3; // esi

  if ( *(uint8_t *)(this + 76) == 0 )
  {
    v2 = *(uint32_t *)(this + 104);
    if ( v2 != 0 )
      (*(void (/*stdcall*/ **)(uint32_t))(*(uint32_t *)v2 + 8))(*(uint32_t *)(this + 104));
    *(uint32_t *)(this + 104) = 0;
  }
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 104) = 0;
  *(uint8_t *)(this + 76) = 0;
  *(uint8_t *)(this + 4) = 0;
  v3 = (uint32_t *)(this + 96);
  *v3 = 0;
  v3[1] = 0;
  return 1;
}



// ------------------------------------------------------------
// 0x413840 sub_413840
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
// 0x413870 sub_413870
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
// 0x4138A0 sub_4138A0
// ------------------------------------------------------------
int /*thiscall*/ sub_4138A0(int this, int a2, int a3, uint32_t *a4)
{
  int result; // eax
  int v5; // [esp-8h] [ebp-18h]
  int v6; // [esp-8h] [ebp-18h]
  int v7; // [esp+8h] [ebp-8h] BYREF
  int v8; // [esp+Ch] [ebp-4h]

  result = a4[2];
  if ( result == 3 )
  {
    v7 = a2;
    v5 = *(uint32_t *)(this + 104);
    v8 = a3;
    return (*(int (/*stdcall*/ **)(uint32_t, uint32_t, int, int, int, int *))(**(uint32_t **)(this + 108) + 112))(
             *(uint32_t *)(this + 108),
             a4[26],
             this + 80,
             1,
             v5,
             &v7);
  }
  else if ( result == 7 )
  {
    v7 = a2;
    v6 = *(uint32_t *)(this + 104);
    v8 = a3;
    return (*(int (/*stdcall*/ **)(uint32_t, uint32_t, int, int, int, int *))(**(uint32_t **)(this + 108) + 112))(
             *(uint32_t *)(this + 108),
             a4[32],
             this + 80,
             1,
             v6,
             &v7);
  }
  return result;
}



// ------------------------------------------------------------
// 0x413920 sub_413920
// ------------------------------------------------------------
int /*thiscall*/ sub_413920(unsigned int *this, FILE *Stream)
{
  int i; // ebx
  int v4; // eax
  unsigned int v5; // ebx
  unsigned int v6; // eax
  unsigned int j; // edi
  unsigned int v8; // ecx
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
  v4 = *(this + 6);
  v5 = 0;
  v15 = 0;
  if ( v4 != 0 )
  {
    v6 = *(this + 5);
    do
    {
      for ( j = 0; j < v6; ++j )
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
        v6 = *(this + 5);
        v5 = v15;
      }
      v8 = *(this + 6);
      v15 = ++v5;
    }
    while ( v5 < v8 );
  }
  (*(void (/*thiscall*/ **)(unsigned int *))(*this + 88))(this);
  return 1;
}



// ------------------------------------------------------------
// 0x413A60 sub_413A60
// ------------------------------------------------------------
int /*thiscall*/ sub_413A60(size_t *this, FILE *Stream)
{
  FILE *v3; // esi
  size_t *v4; // ebx
  int v5; // eax
  size_t v6; // eax
  size_t j; // esi
  unsigned int v8; // edx
  int v10; // [esp+Ch] [ebp-10h] BYREF
  int Buffer; // [esp+10h] [ebp-Ch] BYREF
  void *Block; // [esp+14h] [ebp-8h]
  int i; // [esp+18h] [ebp-4h]

  (*(void (/*thiscall*/ **)(size_t *))(*this + 84))(this);
  (*(void (/*thiscall*/ **)(size_t *, uint32_t))(*this + 28))(this, 0);
  v3 = Stream;
  Buffer = 0;
  sub_66BD5A(&Buffer, 4u, 1u, Stream);
  if ( Buffer == 0 )
  {
    v10 = 0;
    v4 = this + 5;
    sub_66BD5A(this + 5, 4u, 1u, Stream);
    sub_66BD5A(this + 6, 4u, 1u, Stream);
    Block = operator new(*(this + 5));
    for ( i = 256; i != 0; --i )
      sub_66BD5A(&v10, 4u, 1u, Stream);
    v5 = *(this + 6);
    i = 0;
    if ( v5 != 0 )
    {
      v6 = *v4;
      while ( 1 )
      {
        sub_66BD5A(Block, v6, 1u, v3);
        v6 = *v4;
        for ( j = 0; j < *v4; ++j )
        {
          (*(void (/*thiscall*/ **)(size_t *, size_t, int, int))(*this + 32))(
            this,
            j,
            i,
            *((uint8_t *)Block + j)
          | ((*((uint8_t *)Block + j)
            | ((*((uint8_t *)Block + j) | (*((uint8_t *)Block + j) << 8)) << 8)) << 8));
          v6 = *v4;
        }
        v8 = *(this + 6);
        if ( ++i >= v8 )
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
// 0x413B80 sub_413B80
// ------------------------------------------------------------
int /*thiscall*/ sub_413B80(char *this, void *Block)
{
  int result; // eax
  int *v5; // edi
  int v6; // ecx
  void *v7; // eax
  int *v8; // ebx
  int v9; // [esp-10h] [ebp-40h]
  int v10; // [esp-Ch] [ebp-3Ch]
  int v11[6]; // [esp+4h] [ebp-2Ch] BYREF
  int xRight; // [esp+1Ch] [ebp-14h]
  int yBottom; // [esp+20h] [ebp-10h]
  int v14; // [esp+2Ch] [ebp-4h]
  void *Blocka; // [esp+38h] [ebp+8h]

  if ( *(this + 4) != 0 )
    return -2147483646;
  v5 = (int *)(this + 128);
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
    memset(v11, 0, sizeof(v11));
    xRight = 0;
    yBottom = 0;
    (*(void (/*stdcall*/ **)(int, int *))(*(uint32_t *)*v5 + 32))(*v5, v11);
    v6 = yBottom;
    v10 = yBottom;
    v9 = xRight;
    *((uint32_t *)this + 5) = xRight;
    *((uint32_t *)this + 6) = v6;
    SetRect((LPRECT)(this + 84), 0, 0, v9, v10);
    SetRect((LPRECT)this + 3, 0, 0, *((uint32_t *)this + 5), *((uint32_t *)this + 6));
    v7 = operator new(0x70u);
    v14 = 0;
    if ( v7 != nullptr )
      v8 = (int *)sub_4089B0((int)v7, 3, (int)Block);
    else
      v8 = nullptr;
    v14 = -1;
    if ( v8 != nullptr )
    {
      result = sub_413670(v8, *v5);
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
// 0x413CE0 sub_413CE0
// ------------------------------------------------------------
int /*thiscall*/ sub_413CE0(int this)
{
  int v2; // eax
  void (/*thiscall*/ ***v3)(uint32_t, int); // ecx
  bool v4; // zf
  int v5; // eax

  v2 = *(uint32_t *)(this + 128);
  if ( v2 != 0 )
    (*(void (/*stdcall*/ **)(int))(*(uint32_t *)v2 + 8))(v2);
  v3 = *(void (/*thiscall*/ ****)(uint32_t, int))(this + 108);
  *(uint32_t *)(this + 128) = 0;
  if ( v3 != nullptr )
    (**v3)(v3, 1);
  v4 = *(uint8_t *)(this + 76) == 0;
  *(uint32_t *)(this + 108) = 0;
  if ( v4 )
  {
    v5 = *(uint32_t *)(this + 120);
    if ( v5 != 0 )
      (*(void (/*stdcall*/ **)(uint32_t))(*(uint32_t *)v5 + 8))(*(uint32_t *)(this + 120));
    *(uint32_t *)(this + 120) = 0;
  }
  *(uint32_t *)(this + 12) = 0;
  *(uint32_t *)(this + 16) = 0;
  *(uint32_t *)(this + 128) = 0;
  *(uint8_t *)(this + 4) = 0;
  return 1;
}



// ------------------------------------------------------------
// 0x413D40 sub_413D40
// ------------------------------------------------------------
int /*thiscall*/ sub_413D40(int this)
{
  uint32_t *v3; // eax
  int v4; // ebx
  unsigned int v5; // ecx
  int v6; // edx
  int v7; // edi
  size_t v8; // [esp-4h] [ebp-8h]

  if ( *(uint32_t *)(this + 12) == 0 )
    return -2147483647;
  if ( *(uint32_t *)(this + 16) != 0 )
    j_j__free(*(void **)(this + 16));
  v8 = 4 * *(uint32_t *)(this + 24);
  *(uint32_t *)(this + 16) = 0;
  v3 = operator new(v8);
  if ( v3 == nullptr )
    return -2147483640;
  v4 = *(uint32_t *)(this + 24);
  v5 = 0;
  v6 = 0;
  v7 = *(uint32_t *)(this + 12);
  *(uint32_t *)(this + 16) = v3;
  if ( v4 != 0 )
  {
    do
    {
      v3[v5] = v7 + 4 * v6;
      v6 += *(uint32_t *)(this + 80);
      ++v5;
    }
    while ( v5 < *(uint32_t *)(this + 24) );
  }
  return 1;
}



// ------------------------------------------------------------
// 0x413DB0 sub_413DB0
// ------------------------------------------------------------
int /*thiscall*/ sub_413DB0(int this, int a2)
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
           a2 & 0xFF00FF00 | ((uint8_t)a2 << 16) | BYTE2(a2),
           0,
           0);
}



// ------------------------------------------------------------
// 0x413E10 sub_413E10
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
// 0x413E40 sub_413E40
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
// 0x413E80 sub_413E80
// ------------------------------------------------------------
int /*thiscall*/ sub_413E80(uint32_t *this, int a2, int a3, uint32_t *a4)
{
  int result; // eax

  result = (int)a4;
  if ( a4[2] == 3 )
    return (*(int (/*thiscall*/ **)(uint32_t *, int, int, uint32_t))(*a4 + 152))(a4, a2, a3, *(this + 27));
  return result;
}



// ------------------------------------------------------------
// 0x413EB0 sub_413EB0
// ------------------------------------------------------------
char /*thiscall*/ sub_413EB0(int this, int a2)
{
  char result; // al

  result = *(uint8_t *)(this + 45);
  if ( result == 0 )
  {
    *(uint32_t *)(this + 64) = a2;
    *(uint8_t *)(this + 45) = 1;
    return a2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x413ED0 sub_413ED0
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
int /*thiscall*/ sub_413EE0(int this, DWORD dwExStyle, char a3)
{
  int result; // eax
  int v5; // eax
  int *v6; // edi
  int v7; // eax
  int v8; // edi
  int v9; // ecx
  int v10; // edi
  int SystemMetrics; // eax
  LONG v12; // edx
  int v13; // ebx
  struct tagRECT Rect; // [esp+8h] [ebp-18h] BYREF
  int v15; // [esp+18h] [ebp-8h]
  DWORD dwStyle; // [esp+1Ch] [ebp-4h]
  LONG dwExStylea; // [esp+28h] [ebp+8h]
  unsigned int v18; // [esp+2Ch] [ebp+Ch]

  if ( (*(int (/*stdcall*/ **)(uint32_t))(**(uint32_t **)(this + 120) + 12))(*(uint32_t *)(this + 120)) != -2005530519 )
  {
    if ( a3 == 0 )
      return -2147483645;
  }
  else if ( a3 == 0 )
  {
    v5 = *(uint32_t *)(this + 128);
    v6 = (int *)(this + 128);
    if ( v5 != 0 )
      (*(void (/*stdcall*/ **)(uint32_t))(*(uint32_t *)v5 + 8))(*(uint32_t *)(this + 128));
    v7 = *(uint32_t *)(this + 120);
    *v6 = 0;
    result = (*(int (/*stdcall*/ **)(int, DWORD))(*(uint32_t *)v7 + 56))(v7, dwExStyle);
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
        v8 = sub_413670(*(int **)(this + 108), *v6);
        v15 = v8;
        if ( v8 >= 0 )
        {
          (*(void (/*stdcall*/ **)(uint32_t))(**(uint32_t **)(this + 124) + 36))(*(uint32_t *)(this + 124));
          v9 = *(uint32_t *)(this + 132);
          if ( *(uint32_t *)(dwExStyle + 28) != 0 )
          {
            sub_404590((uint32_t *)v9, -1, -1);
            dwStyle = GetWindowLongA(*(HWND *)(*(uint32_t *)(this + 132) + 16), -16);
            dwExStylea = GetWindowLongA(*(HWND *)(*(uint32_t *)(this + 132) + 16), -20);
            v10 = (GetSystemMetrics(0) >> 1) - (*(uint32_t *)(this + 20) >> 1);
            v18 = *(uint32_t *)(this + 24);
            SystemMetrics = GetSystemMetrics(1);
            v12 = *(uint32_t *)(this + 20);
            Rect.bottom = v18;
            v13 = (SystemMetrics >> 1) - (v18 >> 1);
            Rect.left = 0;
            Rect.top = 0;
            Rect.right = v12;
            AdjustWindowRectEx(&Rect, dwStyle, false, dwExStylea);
            SetWindowPos(
              *(HWND *)(*(uint32_t *)(this + 132) + 16),
              (HWND)0xFFFFFFFE,
              v10,
              v13,
              Rect.right - Rect.left,
              Rect.bottom - Rect.top,
              0x40u);
            return v15;
          }
          SetWindowPos(*(HWND *)(v9 + 16), HWND_MESSAGE|0x2, 0, 0, 0, 0, 3u);
        }
        return v8;
      }
    }
    return result;
  }
  (*(void (/*stdcall*/ **)(uint32_t, DWORD))(**(uint32_t **)(this + 120) + 56))(*(uint32_t *)(this + 120), dwExStyle);
  return (*(int (/*stdcall*/ **)(uint32_t, DWORD))(**(uint32_t **)(this + 120) + 56))(*(uint32_t *)(this + 120), dwExStyle);
}



// ------------------------------------------------------------
// 0x414090 sub_414090
// ------------------------------------------------------------
int /*thiscall*/ sub_414090(int this, int a2)
{
  int v3; // eax
  int *v4; // edi
  int v5; // eax
  int result; // eax
  int v7; // ecx
  int v8; // edi
  int SystemMetrics; // eax
  LONG v10; // edx
  int v11; // ebx
  struct tagRECT Rect; // [esp+Ch] [ebp-18h] BYREF
  DWORD dwStyle; // [esp+1Ch] [ebp-8h]
  DWORD dwExStyle; // [esp+20h] [ebp-4h]
  unsigned int v15; // [esp+2Ch] [ebp+8h]

  (*(void (/*stdcall*/ **)(uint32_t))(**(uint32_t **)(this + 120) + 12))(*(uint32_t *)(this + 120));
  v3 = *(uint32_t *)(this + 128);
  v4 = (int *)(this + 128);
  if ( v3 != 0 )
    (*(void (/*stdcall*/ **)(uint32_t))(*(uint32_t *)v3 + 8))(*(uint32_t *)(this + 128));
  v5 = *(uint32_t *)(this + 120);
  *v4 = 0;
  result = (*(int (/*stdcall*/ **)(int, int))(*(uint32_t *)v5 + 56))(v5, a2);
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
      result = sub_413670(*(int **)(this + 108), *v4);
      if ( result >= 0 )
      {
        (*(void (/*stdcall*/ **)(uint32_t))(**(uint32_t **)(this + 124) + 36))(*(uint32_t *)(this + 124));
        v7 = *(uint32_t *)(this + 132);
        if ( *(uint32_t *)(a2 + 28) != 0 )
        {
          sub_404590((uint32_t *)v7, -1, -1);
          dwStyle = GetWindowLongA(*(HWND *)(*(uint32_t *)(this + 132) + 16), -16);
          dwExStyle = GetWindowLongA(*(HWND *)(*(uint32_t *)(this + 132) + 16), -20);
          v8 = (GetSystemMetrics(0) >> 1) - (*(uint32_t *)(this + 20) >> 1);
          v15 = *(uint32_t *)(this + 24);
          SystemMetrics = GetSystemMetrics(1);
          v10 = *(uint32_t *)(this + 20);
          Rect.bottom = v15;
          v11 = (SystemMetrics >> 1) - (v15 >> 1);
          Rect.left = 0;
          Rect.top = 0;
          Rect.right = v10;
          AdjustWindowRectEx(&Rect, dwStyle, false, dwExStyle);
          SetWindowPos(
            *(HWND *)(*(uint32_t *)(this + 132) + 16),
            (HWND)0xFFFFFFFE,
            v8,
            v11,
            Rect.right - Rect.left,
            Rect.bottom - Rect.top,
            0x40u);
        }
        else
        {
          SetWindowPos(*(HWND *)(v7 + 16), HWND_MESSAGE|0x2, 0, 0, 0, 0, 3u);
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
char sub_414200(int a1, int a2, int a3, int a4, char *Format, ...)
{
  int v5; // eax
  int v6; // esi
  int v7; // eax
  int v8; // ecx
  int v9; // ebx
  int v10; // edi
  uint8_t v12[204800]; // [esp+4h] [ebp-33014h] BYREF
  int v13; // [esp+32004h] [ebp-1014h]
  const char *v14; // [esp+32008h] [ebp-1010h]
  int v15; // [esp+3200Ch] [ebp-100Ch]
  int i; // [esp+32010h] [ebp-1008h]
  char Buffer[4096]; // [esp+32014h] [ebp-1004h] BYREF
  int v18; // [esp+33014h] [ebp-4h]
  va_list va; // [esp+33034h] [ebp+1Ch] BYREF

  va_start(va, Format);
  v18 = dword_796E50;
  LOBYTE(v5) = *(uint8_t *)(a1 + 45);
  if ( (uint8_t)v5 != 0 )
  {
    v5 = *(uint32_t *)(a1 + 64);
    if ( v5 != 0 )
    {
      vsprintf(Buffer, Format, va);
      v6 = *(uint32_t *)(a1 + 64);
      v15 = sub_404B30(v12, Buffer, v6);
      v7 = *(uint32_t *)(a1 + 64);
      v8 = *(uint32_t *)(v7 + 32);
      v13 = *(uint32_t *)(v7 + 48);
      if ( v8 != 0 )
        v15 = *(uint32_t *)(v7 + 32);
      LOBYTE(v5) = v15;
      for ( i = 0; i < v15; ++i )
      {
        v14 = &v12[1024 * (i + *(uint32_t *)(v6 + 24))];
        v9 = a2 + sub_404E30(v6, strlen(v14));
        v10 = a3 + i * (*(uint32_t *)(v6 + 20) + *(uint32_t *)(v6 + 36) + 2);
        unknown_libname_3(
          v13,
          a1,
          v9,
          v10,
          a4,
          *(uint8_t *)(v6 + 2),
          *(uint8_t *)(v6 + 1),
          *(uint32_t *)(v6 + 4),
          *(uint32_t *)(v6 + 8),
          1065353216,
          1065353216,
          v14);
        if ( *(uint8_t *)v6 != 0 )
          unknown_libname_3(
            v13,
            a1,
            v9 + 1,
            v10,
            a4,
            *(uint8_t *)(v6 + 2),
            *(uint8_t *)(v6 + 1),
            *(uint32_t *)(v6 + 4),
            *(uint32_t *)(v6 + 8),
            1065353216,
            1065353216,
            v14);
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
// 0x4143A0 sub_4143A0
// ------------------------------------------------------------
int /*thiscall*/ sub_4143A0(int this, int a2, uint32_t *a3)
{
  *(uint8_t *)(this + 4) = 0;
  *(uint32_t *)this = &off_6C1BE8;
  *(uint32_t *)(this + 8) = a2;
  sub_40F360((uint32_t *)this);
  *(uint32_t *)(this + 120) = 0;
  *(uint32_t *)(this + 112) = a3;
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
  *(uint32_t *)(this + 116) = a3[2062];
  *(uint32_t *)(this + 120) = a3[2063];
  *(uint32_t *)(this + 124) = a3[2064];
  return this;
}



// ------------------------------------------------------------
// 0x414450 sub_414450
// ------------------------------------------------------------
int /*stdcall*/ sub_414450(int a1, int a2)
{
  return -2147483646;
}



// ------------------------------------------------------------
// 0x414460 sub_414460
// ------------------------------------------------------------
void */*thiscall*/ sub_414460(void *Block, char a2)
{
  sub_414490();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x414490 sub_414490
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
// 0x4144F0 sub_4144F0
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
// 0x414510 sub_414510
// ------------------------------------------------------------
int /*thiscall*/ sub_414510(int this)
{
  int (/*thiscall*/ ***v2)(uint32_t, int); // ecx
  int result; // eax

  v2 = *(int (/*thiscall*/ ****)(uint32_t, int))(this + 48);
  if ( v2 != nullptr )
    result = (**v2)(v2, 1);
  *(uint32_t *)(this + 48) = 0;
  *(uint8_t *)(this + 4) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x414530 sub_414530
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
// 0x414560 sub_414560
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
// 0x414570 sub_414570
// ------------------------------------------------------------
int /*thiscall*/ sub_414570(int this, int a2)
{
  void *v4; // eax
  unsigned int i; // eax

  if ( *(uint8_t *)(this + 4) != 0 )
    return -2147483646;
  *(uint32_t *)(this + 20) = a2;
  v4 = operator new(4 * a2);
  *(uint32_t *)(this + 52) = v4;
  if ( v4 == nullptr )
    return -2147483640;
  for ( i = 0; i < *(uint32_t *)(this + 20); ++i )
    *(uint32_t *)(*(uint32_t *)(this + 52) + 4 * i) = 0;
  *(uint8_t *)(this + 4) = 1;
  return 1;
}



// ------------------------------------------------------------
// 0x4145E0 sub_4145E0
// ------------------------------------------------------------
int /*thiscall*/ sub_4145E0(int this)
{
  unsigned int i; // edi
  int v3; // ecx

  for ( i = 0; i < *(uint32_t *)(this + 20); ++i )
  {
    v3 = *(uint32_t *)(*(uint32_t *)(this + 52) + 4 * i);
    if ( v3 != 0 )
      (*(void (/*stdcall*/ **)(int))(*(uint32_t *)v3 + 8))(v3);
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
// 0x414640 sub_414640
// ------------------------------------------------------------
int /*thiscall*/ sub_414640(uint8_t *this)
{
  int v3; // eax
  int v4; // edi
  int v5; // [esp-14h] [ebp-1Ch]
  int v6; // [esp+4h] [ebp-4h] BYREF

  if ( *(this + 4) == 0 )
    return -2147483647;
  v3 = *((uint32_t *)this + 5);
  v4 = 0;
  v6 = 0;
  if ( v3 == 0 )
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
  v5 = *(uint32_t *)(*((uint32_t *)this + 13) + 4 * v4);
  (*(void (/*stdcall*/ **)(int, uint32_t, uint32_t, uint32_t))(*(uint32_t *)v5 + 48))(v5, 0, 0, 0);
  return 1;
}



// ------------------------------------------------------------
// 0x414700 sub_414700
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
// 0x414750 sub_414750
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
// 0x4147A0 sub_4147A0
// ------------------------------------------------------------
int /*thiscall*/ sub_4147A0(int this, int a2)
{
  unsigned int i; // esi

  if ( *(uint8_t *)(this + 4) == 0 )
    return -2147483647;
  for ( i = 0; i < *(uint32_t *)(this + 20); ++i )
    (*(void (/*stdcall*/ **)(uint32_t, int))(**(uint32_t **)(*(uint32_t *)(this + 52) + 4 * i) + 52))(
      *(uint32_t *)(*(uint32_t *)(this + 52) + 4 * i),
      a2);
  return 1;
}



// ------------------------------------------------------------
// 0x4147F0 sub_4147F0
// ------------------------------------------------------------
int /*thiscall*/ sub_4147F0(int this, uint16_t a2)
{
  unsigned int i; // edi

  if ( *(uint8_t *)(this + 4) == 0 )
    return -2147483647;
  *(uint32_t *)(this + 16) = 100 * (a2 - 100);
  for ( i = 0; i < *(uint32_t *)(this + 20); ++i )
    (*(void (/*stdcall*/ **)(uint32_t, uint32_t))(**(uint32_t **)(*(uint32_t *)(this + 52) + 4 * i) + 60))(
      *(uint32_t *)(*(uint32_t *)(this + 52) + 4 * i),
      *(uint32_t *)(this + 16));
  return 1;
}



// ------------------------------------------------------------
// 0x414850 sub_414850
// ------------------------------------------------------------
int /*thiscall*/ sub_414850(uint32_t *this, int a2, int a3, int a4)
{
  int v5; // eax
  int v6; // [esp-8h] [ebp-30h]
  int v7; // [esp+0h] [ebp-28h] BYREF
  int v8; // [esp+4h] [ebp-24h]
  int v9; // [esp+8h] [ebp-20h]
  int v10; // [esp+Ch] [ebp-1Ch]
  int v11; // [esp+10h] [ebp-18h]
  int v12; // [esp+14h] [ebp-14h]
  int v13; // [esp+18h] [ebp-10h]
  int v14; // [esp+1Ch] [ebp-Ch]
  int v15; // [esp+20h] [ebp-8h]
  int v16; // [esp+24h] [ebp-4h]

  v16 = dword_796E50;
  if ( *(this + 16) == 0 )
    return 0x80000000;
  v7 = 0;
  v8 = 0;
  v9 = 0;
  v10 = 0;
  v12 = 0;
  v13 = 0;
  v14 = 0;
  v15 = 0;
  v11 = a3;
  v5 = *(this + 16);
  v6 = *(this + 13);
  v8 = a4;
  v7 = 36;
  v9 = a2;
  return (*(int (/*stdcall*/ **)(int, int *, int, uint32_t))(*(uint32_t *)v5 + 12))(v5, &v7, v6, 0) >= 0 ? 1 : -2147483615;
}



// ------------------------------------------------------------
// 0x4148E0 sub_4148E0
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
// 0x414940 sub_414940
// ------------------------------------------------------------
int /*thiscall*/ sub_414940(uint32_t *this)
{
  uint32_t *v2; // eax

  if ( *(this + 16) == 0 )
    return 0x80000000;
  v2 = (uint32_t *)*(this + 13);
  if ( *v2 == 0 )
    return 0x80000000;
  if ( (*(int (/*stdcall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t *, uint32_t *, uint32_t, uint32_t, int))(*(uint32_t *)*v2 + 44))(
         *v2,
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
// 0x414990 sub_414990
// ------------------------------------------------------------
int /*thiscall*/ sub_414990(uint32_t *this)
{
  uint32_t *v2; // eax

  if ( *(this + 16) == 0 )
    return 0x80000000;
  v2 = (uint32_t *)*(this + 13);
  if ( *v2 == 0 )
    return 0x80000000;
  if ( (*(int (/*stdcall*/ **)(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))(*(uint32_t *)*v2 + 76))(
         *v2,
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
  int *v6; // ecx
  int v7; // eax
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
  if ( sub_4199A0(pszFileName, (int)&hmmio, (int)&v11, &pmmcki) != 0 )
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
  v6 = this;
  if ( v5 < 0 )
    goto LABEL_10;
  if ( sub_414940(this) < 0 )
  {
    v6 = this;
LABEL_10:
    (*(void (/*thiscall*/ **)(int *))(*this + 8))(v6);
    sub_419C40(&hmmio, &v11);
    return 0x80000000;
  }
  v7 = sub_419B80(hmmio, *(this + 14), *(this + 15), (int)&v9, (int)&v10);
  v6 = this;
  if ( v7 != 0 )
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
// 0x414B30 sub_414B30
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_414B30(uint8_t *this)
{
  *(this + 4) = 0;
  *(uint32_t *)this = &off_6C298C;
  *(this + 12) = 0;
  *((uint32_t *)this + 2) = &off_6C38F4;
  sub_402A50((uint32_t *)this + 2);
  *(this + 32) = 0;
  *((uint32_t *)this + 7) = &off_6C38F4;
  sub_402A50((uint32_t *)this + 7);
  sub_419C80(this);
  return this;
}



// ------------------------------------------------------------
// 0x414BB0 sub_414BB0
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
// 0x414C40 sub_414C40
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_414C40(uint32_t *Block, char a2)
{
  sub_414BB0(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x414C70 sub_414C70
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_414C70(uint8_t *this)
{
  sub_414B30(this);
  *(uint32_t *)this = &off_6C299C;
  nullsub_3(this);
  return this;
}



// ------------------------------------------------------------
// 0x414CC0 sub_414CC0
// ------------------------------------------------------------
void */*thiscall*/ sub_414CC0(void *Block, char a2)
{
  sub_414CF0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x414CF0 sub_414CF0
// ------------------------------------------------------------
int /*thiscall*/ sub_414CF0(uint32_t *this)
{
  *this = &off_6C299C;
  sub_419CD0();
  return sub_414BB0(this);
}



// ------------------------------------------------------------
// 0x414D40 sub_414D40
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
int /*thiscall*/ sub_414D60(int this, int a2)
{
  uint32_t *v4; // edi

  if ( *(uint8_t *)(this + 4) != 0 )
    return -2147483646;
  v4 = (uint32_t *)(this + 52);
  if ( CoCreateInstance(&stru_749D4C, nullptr, 1u, &stru_749CFC, (LPVOID *)(this + 52)) < 0
    || (**(int (/*stdcall*/ ***)(uint32_t, void *, int))*v4)(*v4, &unk_749D3C, this + 56) < 0
    || (**(int (/*stdcall*/ ***)(uint32_t, void *, int))*v4)(*v4, &unk_749D2C, this + 64) < 0
    || (**(int (/*stdcall*/ ***)(uint32_t, void *, int))*v4)(*v4, &unk_749D0C, this + 60) < 0
    || (**(int (/*stdcall*/ ***)(uint32_t, void *, int))*v4)(*v4, &unk_749D1C, this + 68) < 0 )
  {
    return -2147483600;
  }
  *(uint8_t *)(this + 4) = 1;
  return 1;
}



// ------------------------------------------------------------
// 0x414E00 sub_414E00
// ------------------------------------------------------------
int /*thiscall*/ sub_414E00(int this)
{
  int v2; // eax
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax

  v2 = *(uint32_t *)(this + 68);
  if ( v2 != 0 )
    (*(void (/*stdcall*/ **)(int))(*(uint32_t *)v2 + 8))(v2);
  v3 = *(uint32_t *)(this + 60);
  *(uint32_t *)(this + 68) = 0;
  if ( v3 != 0 )
    (*(void (/*stdcall*/ **)(int))(*(uint32_t *)v3 + 8))(v3);
  v4 = *(uint32_t *)(this + 64);
  *(uint32_t *)(this + 60) = 0;
  if ( v4 != 0 )
    (*(void (/*stdcall*/ **)(int))(*(uint32_t *)v4 + 8))(v4);
  v5 = *(uint32_t *)(this + 56);
  *(uint32_t *)(this + 64) = 0;
  if ( v5 != 0 )
    (*(void (/*stdcall*/ **)(int))(*(uint32_t *)v5 + 8))(v5);
  v6 = *(uint32_t *)(this + 52);
  *(uint32_t *)(this + 56) = 0;
  if ( v6 != 0 )
    (*(void (/*stdcall*/ **)(int))(*(uint32_t *)v6 + 8))(v6);
  *(uint32_t *)(this + 52) = 0;
  *(uint8_t *)(this + 4) = 0;
  return 1;
}



// ------------------------------------------------------------
// 0x414E70 sub_414E70
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
// 0x414F00 sub_414F00
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
// 0x414F50 sub_414F50
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
// 0x414F90 sub_414F90
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_414F90(int this, int a2)
{
  int v3; // eax
  uint32_t v4[2]; // [esp+0h] [ebp-8h] BYREF

  if ( *(uint8_t *)(this + 4) == 0 )
    return -2147483647;
  v4[0] = a2;
  v3 = *(uint32_t *)(this + 60);
  v4[1] = 0;
  return (*(int (/*stdcall*/ **)(int, uint32_t *, int, uint32_t, uint32_t))(*(uint32_t *)v3 + 56))(v3, v4, 1, 0, 0) >= 0
       ? 1
       : 0x80000000;
}



// ------------------------------------------------------------
// 0x414FE0 sub_414FE0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_414FE0(int this, uint16_t a2)
{
  if ( *(uint8_t *)(this + 4) == 0 )
    return -2147483647;
  *(uint32_t *)(this + 16) = 100 * (a2 - 100);
  return (*(int (/*stdcall*/ **)(uint32_t, int))(**(uint32_t **)(this + 68) + 28))(*(uint32_t *)(this + 68), 100 * (a2 - 100)) >= 0
       ? 1
       : 0x80000000;
}



// ============================================================
// SECTION 0x415020 — 键盘输入族（GetAsyncKeyState 轮询）
// ============================================================
// ------------------------------------------------------------
// 0x415020 sub_415020
// ------------------------------------------------------------
int /*thiscall*/ sub_415020(uint8_t *this, LPCCH lpMultiByteStr, int a3)
{
  int result; // eax
  int v5; // edi
  WCHAR WideCharStr[256]; // [esp+4h] [ebp-204h] BYREF
  int v7; // [esp+204h] [ebp-4h]

  v7 = dword_796E50;
  if ( *(this + 4) != 0 )
    return -2147483646;
  MultiByteToWideChar(0, 1u, lpMultiByteStr, -1, WideCharStr, 256);
  v5 = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 40))(this);
  (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 8))(this);
  result = (*(int (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 4))(this, 1);
  if ( result >= 0 )
  {
    if ( (*(int (/*stdcall*/ **)(uint32_t, WCHAR *, uint32_t))(**((uint32_t **)this + 13) + 52))(
           *((uint32_t *)this + 13),
           WideCharStr,
           0) >= 0 )
    {
      (*(void (/*thiscall*/ **)(uint8_t *, int))(*(uint32_t *)this + 36))(this, v5);
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
// 0x4150E0 sub_4150E0
// ------------------------------------------------------------
int /*thiscall*/ sub_4150E0(int this, uint32_t *a2)
{
  int v4; // eax
  uint8_t *v5; // eax
  uint8_t *v6; // eax

  if ( *(uint8_t *)(this + 4) == 0 )
    return -2147483647;
  v4 = *(uint32_t *)(this + 48);
  if ( v4 == 0 )
  {
    v5 = operator new(0x34u);
    v6 = v5 != nullptr ? sub_414C70(v5) : nullptr;
    *(uint32_t *)(this + 48) = v6;
    sub_419C90(this);
    v4 = *(uint32_t *)(this + 48);
    if ( v4 == 0 )
      return -2147483640;
  }
  *a2 = v4;
  return 1;
}



// ------------------------------------------------------------
// 0x415190 sub_415190
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
// 0x415200 sub_415200
// ------------------------------------------------------------
bool /*thiscall*/ sub_415200(uint8_t *this, int a2)
{
  uint8_t *v2; // eax

  return *(this + 12) != 0 && (v2 = this + *((uint32_t *)this + a2 + 196))[269] != 0 && v2[525] == 0;
}



// ------------------------------------------------------------
// 0x415240 sub_415240
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
// 0x415660 sub_415660
// ------------------------------------------------------------
char /*stdcall*/ sub_415660(int vKey, uint8_t *a2)
{
  if ( a2 == nullptr )
    return 0;
  if ( *a2 == 0 )
  {
    if ( (GetAsyncKeyState(vKey) & 0x80000) != 0 )
      *a2 = 1;
    return 0;
  }
  if ( *a2 != 1 || (GetAsyncKeyState(vKey) & 0x80000) != 0 )
    return 0;
  *a2 = 0;
  return 1;
}



// ------------------------------------------------------------
// 0x4156C0 sub_4156C0
// ------------------------------------------------------------
char /*thiscall*/ sub_4156C0(uint8_t *this, int a2)
{
  if ( *(this + 12) != 0 )
    return *(this + a2 + 1808);
  else
    return 0;
}



// ------------------------------------------------------------
// 0x4156E0 sub_4156E0
// ------------------------------------------------------------
int /*thiscall*/ sub_4156E0(int this, int a2)
{
  int v4; // eax
  uint32_t *v5; // edi

  if ( *(uint8_t *)(this + 4) != 0 )
    return -2147483646;
  v4 = *(uint32_t *)(this + 3092);
  if ( v4 == 0 )
    return 0x80000000;
  v5 = (uint32_t *)(this + 3088);
  if ( (*(int (/*stdcall*/ **)(int, void *, int, uint32_t))(*(uint32_t *)v4 + 12))(v4, &unk_743EF0, this + 3088, 0) < 0 )
    return -2147483583;
  if ( (*(int (/*stdcall*/ **)(uint32_t, void *))(*(uint32_t *)*v5 + 44))(*v5, &unk_749ADC) < 0
    || (*(int (/*stdcall*/ **)(uint32_t, uint32_t, int))(*(uint32_t *)*v5 + 52))(
         *v5,
         *(uint32_t *)(*(uint32_t *)(this + 3096) + 16),
         6) < 0 )
  {
    return 0x80000000;
  }
  *(uint8_t *)(this + 4) = 1;
  return 1;
}



// ------------------------------------------------------------
// 0x415770 sub_415770
// ------------------------------------------------------------
char /*thiscall*/ sub_415770(int this)
{
  int v2; // eax
  int v3; // eax

  LOBYTE(v2) = *(uint8_t *)(this + 4);
  if ( (uint8_t)v2 != 0 )
  {
    v3 = *(uint32_t *)(this + 3088);
    qmemcpy((void *)(this + 525), (const void *)(this + 269), 0x100u);
    v2 = (*(int (/*stdcall*/ **)(int))(*(uint32_t *)v3 + 28))(v3);
    if ( v2 >= 0 )
    {
      v2 = (*(int (/*stdcall*/ **)(uint32_t))(**(uint32_t **)(this + 3088) + 100))(*(uint32_t *)(this + 3088));
      if ( v2 >= 0 )
        LOBYTE(v2) = (*(int (/*stdcall*/ **)(uint32_t, int, int))(**(uint32_t **)(this + 3088) + 36))(
                       *(uint32_t *)(this + 3088),
                       256,
                       this + 269);
    }
  }
  return v2;
}



// ------------------------------------------------------------
// 0x4157E0 sub_4157E0
// ------------------------------------------------------------
void /*thiscall*/ sub_4157E0(uint32_t *this)
{
  *(this + 772) = 0;
}



// ------------------------------------------------------------
// 0x4157F0 sub_4157F0
// ------------------------------------------------------------
int /*thiscall*/ sub_4157F0(int this)
{
  int v2; // eax
  int v3; // eax

  v2 = *(uint32_t *)(this + 3088);
  if ( v2 != 0 )
  {
    (*(void (/*stdcall*/ **)(int))(*(uint32_t *)v2 + 32))(v2);
    v3 = *(uint32_t *)(this + 3088);
    if ( v3 != 0 )
      (*(void (/*stdcall*/ **)(uint32_t))(*(uint32_t *)v3 + 8))(*(uint32_t *)(this + 3088));
    *(uint32_t *)(this + 3088) = 0;
  }
  *(uint8_t *)(this + 4) = 0;
  *(uint32_t *)(this + 3088) = 0;
  return 1;
}



// ------------------------------------------------------------
// 0x415840 sub_415840
// ------------------------------------------------------------
char /*thiscall*/ sub_415840(int this)
{
  int v2; // eax
  int v3; // eax
  int *v4; // esi
  int v5; // edx
  bool v6; // cl

  LOBYTE(v2) = *(uint8_t *)(this + 4);
  if ( (uint8_t)v2 != 0 )
  {
    LOBYTE(v2) = *(uint8_t *)(this + 12);
    if ( (uint8_t)v2 != 0 )
    {
      v2 = *(uint32_t *)(this + 3088);
      if ( v2 != 0 )
      {
        v2 = (*(int (/*stdcall*/ **)(uint32_t))(*(uint32_t *)v2 + 28))(*(uint32_t *)(this + 3088));
        if ( v2 >= 0 )
        {
          v2 = (*(int (/*stdcall*/ **)(uint32_t))(**(uint32_t **)(this + 3088) + 100))(*(uint32_t *)(this + 3088));
          if ( v2 >= 0 )
          {
            (*(void (/*stdcall*/ **)(uint32_t, int, int))(**(uint32_t **)(this + 3088) + 36))(
              *(uint32_t *)(this + 3088),
              272,
              this + 3092);
            qmemcpy((void *)(this + 525), (const void *)(this + 269), 0x100u);
            v3 = 0;
            memset((void *)(this + 269), 0, 0x100u);
            v4 = (int *)(this + 2064);
            do
            {
              v5 = *v4;
              v6 = *(uint8_t *)(this + v3++ + 3140) != 0;
              ++v4;
              *(uint8_t *)(this + v5 + 1808) = v6;
            }
            while ( v3 < 107 );
            LOBYTE(v2) = 1;
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
  return v2;
}



// ------------------------------------------------------------
// 0x415960 sub_415960
// ------------------------------------------------------------
int /*stdcall*/ sub_415960(int a1, int a2)
{
  int v2; // ecx
  int v3; // eax
  uint32_t v5[6]; // [esp+0h] [ebp-18h] BYREF

  v2 = *(uint32_t *)(a1 + 24);
  v3 = *(uint32_t *)(a2 + 3088);
  v5[0] = 24;
  v5[1] = 16;
  v5[3] = 2;
  v5[2] = v2;
  v5[5] = 1000;
  v5[4] = -1000;
  (*(void (/*stdcall*/ **)(int, int, uint32_t *))(*(uint32_t *)v3 + 24))(v3, 4, v5);
  return 1;
}



// ------------------------------------------------------------
// 0x4159C0 sub_4159C0
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
// 0x4159F0 sub_4159F0
// ------------------------------------------------------------
char */*cdecl*/ sub_4159F0(char *a1, char *a2, const void *a3)
{
  char *result; // eax
  void *v4; // edi

  for ( result = a1; result != a2; result += 580 )
  {
    v4 = result;
    qmemcpy(v4, a3, 0x244u);
  }
  return result;
}



// ------------------------------------------------------------
// 0x415A20 sub_415A20
// ------------------------------------------------------------
char */*cdecl*/ sub_415A20(char *a1, char *a2, char *a3)
{
  char *v3; // edx
  char *result; // eax

  v3 = a2;
  result = a3;
  while ( v3 != a1 )
  {
    v3 -= 580;
    result -= 580;
    qmemcpy(result, v3, 0x244u);
  }
  return result;
}



// ------------------------------------------------------------
// 0x415A60 sub_415A60
// ------------------------------------------------------------
char */*cdecl*/ sub_415A60(char *a1, char *a2, char *a3)
{
  char *v3; // edx
  char *result; // eax

  v3 = a1;
  for ( result = a3; v3 != a2; result += 580 )
  {
    if ( result != nullptr )
      qmemcpy(result, v3, 0x244u);
    v3 += 580;
  }
  return result;
}



// ------------------------------------------------------------
// 0x415AA0 sub_415AA0
// ------------------------------------------------------------
char */*cdecl*/ sub_415AA0(char *a1, char *a2, const void *a3)
{
  char *result; // eax
  char *v4; // edx

  result = a2;
  if ( a2 != nullptr )
  {
    v4 = a2;
    result = a1;
    do
    {
      if ( result != nullptr )
        qmemcpy(result, a3, 0x244u);
      result += 580;
      --v4;
    }
    while ( v4 != nullptr );
  }
  return result;
}



// ------------------------------------------------------------
// 0x415AE0 sub_415AE0
// ------------------------------------------------------------
char */*stdcall*/ sub_415AE0(char *a1, char *a2, const void *a3)
{
  sub_415AA0(a1, a2, a3);
  return &a1[580 * (uint32_t)a2];
}



// ============================================================
// SECTION 0x415B10 — 输入映射 vector 管理（按键状态容器）
// ============================================================
// ------------------------------------------------------------
// 0x415B10 sub_415B10 [串: "vector<T> too long"]
// ------------------------------------------------------------
void /*noreturn*/ sub_415B10()
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
  sub_4015C0(&v1, "vector<T> too long", 0x12u);
  v5 = 0;
  sub_401740(pExceptionObject, &v1);
  pExceptionObject[0] = &std::length_error::`vftable';
  _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x415B80 sub_415B80
// ------------------------------------------------------------
int /*thiscall*/ sub_415B80(int this, char *a2, char *a3, const void *a4)
{
  int result; // eax
  int v6; // edi
  unsigned int v7; // ecx
  int v8; // eax
  int v9; // eax
  unsigned int v10; // ecx
  int v11; // eax
  int v12; // edi
  void *v13; // eax
  char *v14; // ecx
  int v15; // eax
  char *v16; // esi
  char *v17; // esi
  char *v18; // ecx
  int v20; // edx
  char *v21; // [esp-Ch] [ebp-278h]
  char *v22; // [esp-8h] [ebp-274h]
  int v23; // [esp+0h] [ebp-26Ch] BYREF
  char *v24; // [esp+Ch] [ebp-260h]
  void *Block; // [esp+10h] [ebp-25Ch]
  uint32_t v26[147]; // [esp+14h] [ebp-258h] BYREF
  int v27; // [esp+268h] [ebp-4h]
  char *v28; // [esp+274h] [ebp+8h]
  char *v29; // [esp+27Ch] [ebp+10h]

  result = dword_796E50;
  qmemcpy(v26, a4, 0x244u);
  v6 = *(uint32_t *)(this + 4);
  v26[145] = dword_796E50;
  v26[146] = &v23;
  if ( v6 != 0 )
  {
    result = -503547889 * (*(uint32_t *)(this + 12) - v6);
    v7 = (*(uint32_t *)(this + 12) - v6) / 580;
  }
  else
  {
    v7 = 0;
  }
  if ( a3 != nullptr )
  {
    if ( v6 != 0 )
      v8 = (*(uint32_t *)(this + 8) - *(uint32_t *)(this + 4)) / 580;
    else
      v8 = 0;
    if ( (char *)&off_70FE3C - v8 < a3 )
      sub_415B10(this);
    if ( *(uint32_t *)(this + 4) != 0 )
      v9 = (*(uint32_t *)(this + 8) - *(uint32_t *)(this + 4)) / 580;
    else
      v9 = 0;
    if ( v7 >= (unsigned int)&a3[v9] )
    {
      v18 = *(char **)(this + 8);
      v29 = v18;
      if ( (v18 - a2) / 580 >= (unsigned int)a3 )
      {
        v28 = &v18[-580 * (uint32_t)a3];
        *(uint32_t *)(this + 8) = sub_415A60(v28, v18, v18);
        sub_415A20(a2, v28, v29);
        return (int)sub_4159F0(a2, &a2[580 * (uint32_t)a3], v26);
      }
      else
      {
        sub_415A60(a2, v18, &a2[580 * (uint32_t)a3]);
        v22 = &a3[-((*(uint32_t *)(this + 8) - (int)a2) / 580)];
        v21 = *(char **)(this + 8);
        v27 = 2;
        sub_415AE0(v21, v22, v26);
        v20 = 580 * (uint32_t)a3 + *(uint32_t *)(this + 8);
        *(uint32_t *)(this + 8) = v20;
        return (int)sub_4159F0(a2, (char *)(v20 - 580 * (uint32_t)a3), v26);
      }
    }
    else
    {
      if ( (unsigned int)&off_70FE3C - (v7 >> 1) >= v7 )
        v10 = (v7 >> 1) + v7;
      else
        v10 = 0;
      if ( *(uint32_t *)(this + 4) != 0 )
        v11 = (*(uint32_t *)(this + 8) - *(uint32_t *)(this + 4)) / 580;
      else
        v11 = 0;
      if ( v10 < (unsigned int)&a3[v11] )
        v10 = (unsigned int)&a3[sub_4159C0((int *)this)];
      v12 = 580 * v10;
      v13 = operator new(580 * v10);
      v14 = *(char **)(this + 4);
      Block = v13;
      v27 = 0;
      v24 = sub_415A60(v14, a2, (char *)v13);
      sub_415AA0(v24, a3, v26);
      sub_415A60(a2, *(char **)(this + 8), &v24[580 * (uint32_t)a3]);
      v15 = *(uint32_t *)(this + 4);
      if ( v15 != 0 )
        v15 = (*(uint32_t *)(this + 8) - v15) / 580;
      v16 = &a3[v15];
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
// 0x415E70 sub_415E70
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_415E70(uint32_t *this, uint32_t *a2, char *a3, const void *a4)
{
  int v5; // esi
  int v6; // esi

  v5 = *(this + 1);
  if ( v5 != 0 && (*(this + 2) - v5) / 580 != 0 )
    v6 = (int)&a3[-v5] / 580;
  else
    v6 = 0;
  sub_415B80((int)this, a3, (char *)1, a4);
  *a2 = *(this + 1) + 580 * v6;
  return a2;
}



// ------------------------------------------------------------
// 0x415EE0 sub_415EE0
// ------------------------------------------------------------
char */*thiscall*/ sub_415EE0(int this, const void *a2)
{
  int v3; // ebx
  unsigned int v4; // esi
  char *v5; // esi
  char *result; // eax

  v3 = *(uint32_t *)(this + 4);
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(this + 8) - v3) / 580;
  else
    v4 = 0;
  if ( v3 == 0 || v4 >= (*(uint32_t *)(this + 12) - v3) / 580 )
    return (char *)sub_415E70((uint32_t *)this, &a2, *(char **)(this + 8), a2);
  v5 = *(char **)(this + 8);
  result = sub_415AA0(v5, (char *)1, a2);
  *(uint32_t *)(this + 8) = v5 + 580;
  return result;
}



// ------------------------------------------------------------
// 0x415F70 sub_415F70
// ------------------------------------------------------------
int /*stdcall*/ sub_415F70(const void *a1, int a2)
{
  sub_415EE0((int)&unk_8A7748, a1);
  return 1;
}



// ------------------------------------------------------------
// 0x415F90 sub_415F90
// ------------------------------------------------------------
int /*thiscall*/ sub_415F90(int this, int a2)
{
  int v4; // ebx
  int v5; // ecx
  int v6; // eax
  uint32_t *v7; // esi

  if ( *(uint8_t *)(this + 4) != 0 )
    return -2147483646;
  v4 = dword_8A774C;
  if ( dword_8A774C == 0 || (v5 = dword_8A7750, (dword_8A7750 - dword_8A774C) / 580 == 0) )
  {
    (*(void (/*stdcall*/ **)(uint32_t, int, int (/*stdcall*/ *)(const void *, int), int, int))(**(uint32_t **)(this + 3364) + 16))(
      *(uint32_t *)(this + 3364),
      4,
      sub_415F70,
      this,
      1);
    v5 = dword_8A7750;
    v4 = dword_8A774C;
  }
  if ( v4 == 0 )
    return 0x80000000;
  v6 = (v5 - v4) / 580;
  if ( v6 == 0 || v6 <= a2 )
    return 0x80000000;
  v7 = (uint32_t *)(this + 3088);
  if ( (*(int (/*stdcall*/ **)(uint32_t, int, int, uint32_t))(**(uint32_t **)(this + 3364) + 12))(
         *(uint32_t *)(this + 3364),
         v4 + 580 * a2 + 4,
         this + 3088,
         0) < 0 )
    return -2147483647;
  (*(void (/*stdcall*/ **)(uint32_t, void *))(*(uint32_t *)*v7 + 44))(*v7, &unk_749CE4);
  (*(void (/*stdcall*/ **)(uint32_t, uint32_t, int))(*(uint32_t *)*v7 + 52))(*v7, *(uint32_t *)(*(uint32_t *)(this + 3368) + 16), 5);
  (*(void (/*stdcall*/ **)(uint32_t))(*(uint32_t *)*v7 + 32))(*v7);
  (*(void (/*stdcall*/ **)(uint32_t, int (/*stdcall*/ *)(int, int), int, int))(*(uint32_t *)*v7 + 16))(*v7, sub_415960, this, 3);
  *(uint8_t *)(this + 4) = 1;
  return 1;
}



// ------------------------------------------------------------
// 0x4160B0 sub_4160B0
// ------------------------------------------------------------
int /*thiscall*/ sub_4160B0(uint8_t *this, int a2)
{
  if ( *(this + 4) != 0 )
    return -2147483646;
  (*(void (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 32))(this);
  *(this + 4) = 1;
  return 1;
}



// ------------------------------------------------------------
// 0x4160E0 sub_4160E0
// ------------------------------------------------------------
int /*thiscall*/ sub_4160E0(uint8_t *this)
{
  *(this + 4) = 0;
  return 1;
}



// ------------------------------------------------------------
// 0x4160F0 sub_4160F0
// ------------------------------------------------------------
char /*thiscall*/ sub_4160F0(uint8_t *this, int a2)
{
  if ( *(this + 12) == 0 )
    return 0;
  if ( GetAsyncKeyState(*((uint32_t *)this + a2 + 196)) == 0 )
    return 0;
  *(this + *((uint32_t *)this + a2 + 196) + 269) = 1;
  return 1;
}



// ------------------------------------------------------------
// 0x416140 sub_416140
// ------------------------------------------------------------
bool /*thiscall*/ sub_416140(uint8_t *this, int a2)
{
  return *(this + 12) != 0 && GetAsyncKeyState(*((uint32_t *)this + a2 + 196)) != 0;
}



// ------------------------------------------------------------
// 0x416170 sub_416170
// ------------------------------------------------------------
bool /*thiscall*/ sub_416170(uint8_t *this, int a2)
{
  return *(this + 12) != 0 && GetAsyncKeyState(*((uint32_t *)this + a2 + 196)) == 0;
}



// ------------------------------------------------------------
// 0x4161A0 sub_4161A0
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
// 0x4163A0 sub_4163A0
// ------------------------------------------------------------
char */*usercall*/ sub_4163A0@<eax>(int a1@<ebx>, char *a2, unsigned int a3, char a4)
{
  int v4; // eax

  LOBYTE(a1) = a4;
  BYTE1(a1) = a4;
  v4 = a1 << 16;
  LOWORD(v4) = a1;
  memset32(a2, v4, a3 >> 2);
  memset(&a2[4 * (a3 >> 2)], a4, a3 & 3);
  return a2;
}



// ------------------------------------------------------------
// 0x4163E0 sub_4163E0
// ------------------------------------------------------------
int /*thiscall*/ sub_4163E0(void *this)
{
  return (*(int (/*thiscall*/ **)(void *))(*(uint32_t *)this + 32))(this);
}



// ------------------------------------------------------------
// 0x4163F0 sub_4163F0
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
// 0x416420 sub_416420
// ------------------------------------------------------------
int /*thiscall*/ sub_416420(uint8_t *this)
{
  int result; // eax

  result = (*(int (/*thiscall*/ **)(uint8_t *))(*(uint32_t *)this + 36))(this);
  *(this + 4) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x416430 sub_416430
// ------------------------------------------------------------
int /*thiscall*/ sub_416430(void *this, int a2, int a3, int a4, int a5, int a6)
{
  return (*(int (/*thiscall*/ **)(void *, int, int, int, int, uint32_t, uint32_t, int, int, int, int, int))(*(uint32_t *)this + 48))(
           this,
           a2,
           a3,
           a4,
           a5,
           0,
           0,
           -1,
           -1,
           1065353216,
           1065353216,
           a6);
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
// 0x416480 sub_416480
// ------------------------------------------------------------
void **/*thiscall*/ sub_416480(void **Block, char a2)
{
  if ( (unsigned int)*(Block + 6) >= 0x10 )
    j__free(*(Block + 1));
  *(Block + 5) = nullptr;
  *(Block + 6) = (void *)15;
  *((uint8_t *)Block + 4) = 0;
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ============================================================
// SECTION 0x4164C0 — string/vector 容器工具
// ============================================================
// ------------------------------------------------------------
// 0x4164C0 sub_4164C0
// ------------------------------------------------------------
size_t */*thiscall*/ sub_4164C0(size_t *this, unsigned int a2, char a3)
{
  unsigned int v3; // ebx
  unsigned int v5; // eax
  bool v6; // zf
  char *v7; // edx
  unsigned int v9; // ecx
  char *v10; // edi
  char v11; // dl
  int v12; // eax
  bool v13; // cf
  unsigned int v14; // [esp+10h] [ebp+8h]

  v3 = a2;
  if ( -1 - *(this + 5) <= a2 )
    std::_String_base::_Xlen((std::_String_base *)this);
  if ( a2 == 0 )
    return this;
  v14 = a2 + *(this + 5);
  if ( v14 == -1 )
    std::_String_base::_Xlen((std::_String_base *)this);
  v5 = *(this + 6);
  if ( v5 < v14 )
  {
    sub_4012B0(this, v14, *(this + 5));
    v6 = v14 == 0;
    goto LABEL_8;
  }
  v6 = v14 == 0;
  if ( v14 != 0 )
  {
LABEL_8:
    if ( !v6 )
    {
      if ( *(this + 6) < 0x10 )
        v7 = (char *)(this + 1);
      else
        v7 = (char *)*(this + 1);
      v9 = v3;
      LOBYTE(v3) = a3;
      BYTE1(v3) = a3;
      v10 = &v7[*(this + 5)];
      v11 = v9;
      v9 >>= 2;
      v12 = v3 << 16;
      LOWORD(v12) = v3;
      memset32(v10, v12, v9);
      memset(&v10[4 * v9], a3, v11 & 3);
      v13 = *(this + 6) < 0x10;
      *(this + 5) = v14;
      if ( !v13 )
      {
        *(uint8_t *)(*(this + 1) + v14) = 0;
        return this;
      }
      *((uint8_t *)this + v14 + 4) = 0;
    }
    return this;
  }
  *(this + 5) = 0;
  if ( v5 < 0x10 )
    *((uint8_t *)this + 4) = 0;
  else
    *(uint8_t *)*(this + 1) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x4165A0 sub_4165A0
// ------------------------------------------------------------
size_t */*cdecl*/ sub_4165A0(size_t *a1, size_t *a2, size_t *a3)
{
  size_t *v3; // esi
  size_t *v4; // edi

  v3 = a2;
  if ( a1 == a2 )
    return a3;
  v4 = a3;
  do
  {
    v3 -= 7;
    v4 -= 7;
    sub_4014D0(v4, v3, 0, 0xFFFFFFFF);
  }
  while ( v3 != a1 );
  return v4;
}



// ------------------------------------------------------------
// 0x4165E0 sub_4165E0
// ------------------------------------------------------------
int /*stdcall*/ sub_4165E0(int a1)
{
  if ( *(uint32_t *)(a1 + 24) >= 0x10u )
    j__free(*(void **)(a1 + 4));
  *(uint32_t *)(a1 + 24) = 15;
  *(uint32_t *)(a1 + 20) = 0;
  *(uint8_t *)(a1 + 4) = 0;
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
  sub_4015C0(&v1, "vector<T> too long", 0x12u);
  v5 = 0;
  sub_401740(pExceptionObject, &v1);
  pExceptionObject[0] = &std::length_error::`vftable';
  _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x416680 sub_416680
// ------------------------------------------------------------
size_t */*cdecl*/ sub_416680(size_t *a1, size_t *a2, size_t *a3)
{
  return sub_4165A0(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x4166A0 sub_4166A0
// ------------------------------------------------------------
void /*cdecl*/ sub_4166A0(int a1, int a2)
{
  int i; // esi

  for ( i = a1; i != a2; i += 28 )
  {
    if ( *(uint32_t *)(i + 24) >= 0x10u )
      j__free(*(void **)(i + 4));
    *(uint32_t *)(i + 24) = 15;
    *(uint32_t *)(i + 20) = 0;
    *(uint8_t *)(i + 4) = 0;
  }
}



// ------------------------------------------------------------
// 0x4166E0 sub_4166E0
// ------------------------------------------------------------
int /*cdecl*/ sub_4166E0(size_t *a1, size_t *a2, int a3)
{
  int v3; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  v3 = a3;
  v6[4] = v6;
  v6[3] = a3;
  v7 = 0;
  while ( a1 != a2 )
  {
    LOBYTE(v7) = 1;
    if ( v3 != 0 )
    {
      *(uint32_t *)(v3 + 24) = 15;
      *(uint32_t *)(v3 + 20) = 0;
      *(uint8_t *)(v3 + 4) = 0;
      sub_4014D0((size_t *)v3, a1, 0, 0xFFFFFFFF);
    }
    v3 += 28;
    LOBYTE(v7) = 0;
    a1 += 7;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x416780 sub_416780
// ------------------------------------------------------------
size_t */*cdecl*/ sub_416780(int a1, int a2, size_t *a3)
{
  int v3; // esi
  size_t *result; // eax
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  v3 = a1;
  v6[4] = v6;
  v6[3] = a1;
  v7 = 0;
  while ( a2 != 0 )
  {
    LOBYTE(v7) = 1;
    if ( v3 != 0 )
    {
      *(uint32_t *)(v3 + 24) = 15;
      *(uint32_t *)(v3 + 20) = 0;
      *(uint8_t *)(v3 + 4) = 0;
      result = sub_4014D0((size_t *)v3, a3, 0, 0xFFFFFFFF);
    }
    --a2;
    v3 += 28;
    LOBYTE(v7) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x416820 sub_416820
// ------------------------------------------------------------
void /*stdcall*/ sub_416820(int a1, int a2)
{
  sub_4166A0(a1, a2);
}



// ------------------------------------------------------------
// 0x416840 sub_416840
// ------------------------------------------------------------
int /*stdcall*/ sub_416840(size_t *a1, size_t *a2, int a3)
{
  return sub_4166E0(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x416860 sub_416860
// ------------------------------------------------------------
int /*stdcall*/ sub_416860(int a1, int a2, size_t *a3)
{
  sub_416780(a1, a2, a3);
  return a1 + 28 * a2;
}



// ============================================================
// SECTION 0x416890 — 字形/文本对象容器（大函数，字体缓存管理）
// ============================================================
// ------------------------------------------------------------
// 0x416890 sub_416890
// ------------------------------------------------------------
void /*thiscall*/ sub_416890(int *this, int a2, unsigned int a3, int a4)
{
  int v5; // ebx
  unsigned int v6; // ecx
  int v8; // eax
  int v9; // eax
  unsigned int v10; // ecx
  int v11; // eax
  char *v12; // ebx
  int v13; // eax
  unsigned int v14; // edi
  int v15; // eax
  void *v16; // ecx
  int v18; // edx
  int v19; // [esp-18h] [ebp-60h]
  int v20; // [esp-10h] [ebp-58h]
  int v21; // [esp-Ch] [ebp-54h]
  unsigned int v22; // [esp-8h] [ebp-50h]
  uint32_t v23[4]; // [esp+0h] [ebp-48h] BYREF
  void *Block; // [esp+10h] [ebp-38h]
  char *v25; // [esp+14h] [ebp-34h]
  char v26[4]; // [esp+18h] [ebp-30h] BYREF
  void *v27; // [esp+1Ch] [ebp-2Ch]
  int v28; // [esp+2Ch] [ebp-1Ch]
  unsigned int v29; // [esp+30h] [ebp-18h]
  int v30; // [esp+34h] [ebp-14h]
  uint32_t *v31; // [esp+38h] [ebp-10h]
  int v32; // [esp+44h] [ebp-4h]
  int v33; // [esp+50h] [ebp+8h]
  int v34; // [esp+54h] [ebp+Ch]

  v31 = v23;
  v30 = dword_796E50;
  v23[3] = this;
  v29 = 15;
  v28 = 0;
  LOBYTE(v27) = 0;
  sub_4014D0((std::_String_base *)v26, a4, 0, -1);
  v5 = *(this + 1);
  v32 = 0;
  if ( v5 != 0 )
    v6 = (*(this + 3) - v5) / 28;
  else
    v6 = 0;
  if ( a3 != 0 )
  {
    if ( v5 != 0 )
      v8 = (*(this + 2) - *(this + 1)) / 28;
    else
      v8 = 0;
    if ( 153391689 - v8 < a3 )
      sub_416610(this);
    if ( *(this + 1) != 0 )
      v9 = (*(this + 2) - *(this + 1)) / 28;
    else
      v9 = 0;
    if ( v6 >= a3 + v9 )
    {
      v16 = (void *)*(this + 2);
      Block = v16;
      if ( ((int)v16 - a2) / 28 >= a3 )
      {
        v33 = (int)v16 - 28 * a3;
        *(this + 2) = sub_4166E0(v33, (int)v16, (int)v16);
        sub_416680(a2, v33, Block);
        sub_52C080(a2, a2 + 28 * a3, v26);
      }
      else
      {
        sub_4166E0(a2, (int)v16, a2 + 28 * a3);
        v22 = a3 - (*(this + 2) - a2) / 28;
        v21 = *(this + 2);
        LOBYTE(v32) = 3;
        sub_416860(v21, v22, v26);
        v18 = 28 * a3 + *(this + 2);
        *(this + 2) = v18;
        v32 = 0;
        sub_52C080(a2, v18 - 28 * a3, v26);
      }
    }
    else
    {
      if ( 153391689 - (v6 >> 1) >= v6 )
        v10 = (v6 >> 1) + v6;
      else
        v10 = 0;
      if ( *(this + 1) != 0 )
        v11 = (*(this + 2) - *(this + 1)) / 28;
      else
        v11 = 0;
      if ( v10 < a3 + v11 )
        v10 = a3 + sub_52AEF0(this);
      v34 = 28 * v10;
      v12 = (char *)operator new(28 * v10);
      v19 = *(this + 1);
      Block = v12;
      v25 = v12;
      LOBYTE(v32) = 1;
      v25 = (char *)sub_4166E0(v19, a2, (int)v12);
      sub_416780((int)v25, a3, (int)v26);
      v20 = *(this + 2);
      v25 += 28 * a3;
      sub_4166E0(a2, v20, (int)v25);
      v13 = *(this + 1);
      if ( v13 != 0 )
        v13 = (*(this + 2) - v13) / 28;
      v14 = v13 + a3;
      v15 = *(this + 1);
      if ( v15 != 0 )
      {
        sub_4166A0(v15, *(this + 2));
        j__free((void *)*(this + 1));
      }
      *(this + 3) = (int)&v12[v34];
      *(this + 2) = (int)&v12[28 * v14];
      *(this + 1) = (int)v12;
    }
  }
  if ( v29 >= 0x10 )
    j__free(v27);
}


// ------------------------------------------------------------
// 0x416BD0 sub_416BD0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_416BD0(uint32_t *this, uint32_t *a2, size_t *a3, size_t *a4)
{
  int v5; // esi
  int v6; // esi

  v5 = *(this + 1);
  if ( v5 != 0 && (*(this + 2) - v5) / 28 != 0 )
    v6 = ((int)a3 - v5) / 28;
  else
    v6 = 0;
  sub_416890((int)this, a3, 1u, a4);
  *a2 = *(this + 1) + 28 * v6;
  return a2;
}



// ------------------------------------------------------------
// 0x416C40 sub_416C40
// ------------------------------------------------------------
size_t */*thiscall*/ sub_416C40(int this, size_t *a2)
{
  int v3; // ebx
  unsigned int v4; // esi
  int v5; // esi
  size_t *result; // eax

  v3 = *(uint32_t *)(this + 4);
  if ( v3 != 0 )
    v4 = (*(uint32_t *)(this + 8) - v3) / 28;
  else
    v4 = 0;
  if ( v3 == 0 || v4 >= (*(uint32_t *)(this + 12) - v3) / 28 )
    return sub_416BD0((uint32_t *)this, &a2, *(size_t **)(this + 8), a2);
  v5 = *(uint32_t *)(this + 8);
  result = sub_416780(v5, 1, a2);
  *(uint32_t *)(this + 8) = v5 + 28;
  return result;
}



// ============================================================
// SECTION 0x416CD0 — GDI 资源清理（DeleteObject 族）
// ============================================================
// ------------------------------------------------------------
// 0x416CD0 sub_416CD0
// ------------------------------------------------------------
int /*thiscall*/ sub_416CD0(uint8_t *this)
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
// 0x416D10 sub_416D10
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
// 0x416D50 sub_416D50
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
// 0x416DA0 sub_416DA0
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
// 0x416E70 sub_416E70
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
// 0x416EE0 sub_416EE0
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
int /*thiscall*/ sub_416F40(char *this, char *FileName)
{
  int result; // eax
  FILE *v4; // ebx
  int v5; // edx
  int v6; // ecx
  int v7; // esi
  CHAR Buffer[48]; // [esp+4h] [ebp-34h] BYREF
  int v9; // [esp+34h] [ebp-4h]

  v9 = dword_796E50;
  if ( *(this + 4) == 0 )
    return -2147483647;
  v4 = fopen(FileName, "wb");
  if ( v4 == nullptr )
    return -2147483644;
  memset(Buffer, 0, sizeof(Buffer));
  wsprintfA(Buffer, "NeopleFontFile");
  v5 = *((uint32_t *)this + 3);
  v6 = *((uint32_t *)this + 2);
  memset(&Buffer[36], 255, 12);
  *(uint32_t *)&Buffer[32] = 1;
  *(uint32_t *)&Buffer[36] = *(uint32_t *)(v5 + 8);
  *(uint32_t *)&Buffer[40] = v6;
  *(uint32_t *)&Buffer[44] = 1;
  sub_66BC25(Buffer, 0x30u, 1u, v4);
  sub_66BC25(this + 16, 0x3Cu, 1u, v4);
  v7 = (*(int (/*thiscall*/ **)(char *, FILE *))(*(uint32_t *)this + 40))(this, v4);
  fclose(v4);
  result = v7;
  if ( v7 >= 0 )
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
  FILE *v4; // eax
  int v5; // eax
  int v6; // ecx
  int v7; // esi
  FILE *Stream; // [esp+4h] [ebp-38h]
  char Buffer[32]; // [esp+8h] [ebp-34h] BYREF
  int v10; // [esp+28h] [ebp-14h]
  int v11; // [esp+30h] [ebp-Ch]
  int v12; // [esp+38h] [ebp-4h]

  v12 = dword_796E50;
  if ( *((uint8_t *)this + 4) == 0 )
    return -2147483647;
  v4 = fopen(FileName, "rb");
  Stream = v4;
  if ( v4 == nullptr )
    return -2147483644;
  sub_66BD5A(Buffer, 0x30u, 1u, v4);
  if ( strcmp(Buffer, "NeopleFontFile") == 0 && v10 == 1 && v11 == *(this + 2) )
  {
    sub_66BD5A(this + 4, 0x3Cu, 1u, Stream);
    v5 = *(this + 5);
    v6 = *(this + 4);
    *(this + 26) = v5;
    *(this + 27) = v6;
    *(this + 25) = 2 * v5;
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
// 0x417150 sub_417150
// ------------------------------------------------------------
int /*thiscall*/ sub_417150(unsigned int *this, int a2, int a3, int a4, int a5, const char *a6, int a7)
{
  const char *v7; // edi
  int result; // eax
  int v10; // esi
  char v11; // al
  uint16_t v12; // ax
  unsigned int v13; // esi
  int v14; // ecx
  unsigned int v15; // eax
  unsigned int v16; // ecx
  unsigned int v17; // esi
  int v18; // eax
  int v19; // edx
  int v20; // esi
  int v21; // edi
  int v22; // edx
  int v23; // edx
  bool v24; // cc
  int v25; // ecx
  int v26; // esi
  uint32_t v27[4]; // [esp+8h] [ebp-38h] BYREF
  int v28; // [esp+18h] [ebp-28h] BYREF
  int v29; // [esp+1Ch] [ebp-24h]
  int v30; // [esp+20h] [ebp-20h]
  int v31; // [esp+24h] [ebp-1Ch]
  unsigned int v32; // [esp+28h] [ebp-18h]
  unsigned int v33; // [esp+2Ch] [ebp-14h]
  int v34; // [esp+30h] [ebp-10h]
  int v35; // [esp+34h] [ebp-Ch]
  int v36; // [esp+38h] [ebp-8h]
  int v37; // [esp+3Ch] [ebp-4h]
  int v38; // [esp+50h] [ebp+10h]

  v7 = a6;
  v38 = a4 - 1;
  result = strlen(a6);
  v32 = result;
  if ( result != 0 )
  {
    v10 = 0;
    v36 = 0;
    v37 = 0;
    v35 = a3;
    while ( 1 )
    {
      v11 = v7[v10];
      v12 = v11 >= 0 ? word_8B77D8[v11] : word_8B77D8[*(uint16_t *)&v7[v10]];
      v13 = *(this + 30);
      v14 = v12;
      v15 = v12 / v13;
      v34 = *(this + 25);
      v16 = v14 - v15 * v13;
      v17 = *(this + 31);
      v33 = v15;
      v18 = v16 / v17;
      v19 = v16 % v17;
      v20 = v35;
      v27[0] = v35;
      v21 = v19 * v34;
      v22 = *(this + 27);
      v28 = v21;
      v30 = v34 + v21;
      v29 = v18 * v22;
      result = a3 + v37 + v34;
      v31 = v22 + v29;
      v23 = v38 + v22;
      v24 = v35 <= *(uint32_t *)(a2 + 20);
      v27[1] = v38;
      v27[2] = result;
      v27[3] = v23;
      if ( !v24 || v38 > *(uint32_t *)(a2 + 24) || v23 < 0 )
        break;
      if ( result > 0 )
      {
        v25 = *(uint32_t *)(*(this + 19) + 4 * v33);
        if ( v25 != 0 )
          (*(void (/*thiscall*/ **)(int, uint32_t *, int *, int, uint32_t, int, int))(*(uint32_t *)v25 + 132))(
            v25,
            v27,
            &v28,
            a2,
            0,
            a5,
            a7);
      }
      if ( a6[v36] >= 0 )
      {
        v26 = v20 + 5;
        v37 += 5;
        result = v36 + 1;
      }
      else
      {
        result = v36 + 2;
        v37 += 10;
        v26 = v20 + 10;
      }
      v35 = v26;
      v36 = result;
      if ( result >= v32 )
        break;
      v7 = a6;
      v10 = v36;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x4172B0 sub_4172B0
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
// 0x417450 sub_417450
// ------------------------------------------------------------
int /*thiscall*/ sub_417450(uint32_t *this, FILE *Stream)
{
  unsigned int i; // ebx
  int v4; // ecx

  sub_66BC25(this + 28, 4u, 1u, Stream);
  sub_66BC25(this + 29, 4u, 1u, Stream);
  sub_66BC25(this + 30, 4u, 1u, Stream);
  sub_66BC25(this + 31, 4u, 1u, Stream);
  sub_66BC25(this + 32, 4u, 1u, Stream);
  sub_66BC25(&byte_8A77D8, 0xFFFFu, 1u, Stream);
  for ( i = 0; i < *(this + 29); ++i )
  {
    v4 = *(uint32_t *)(*(this + 19) + 4 * i);
    (*(void (/*thiscall*/ **)(int, FILE *))(*(uint32_t *)v4 + 104))(v4, Stream);
  }
  return 1;
}



// ------------------------------------------------------------
// 0x4174F0 sub_4174F0
// ------------------------------------------------------------
int /*thiscall*/ sub_4174F0(unsigned int *this, FILE *Stream)
{
  unsigned int *v3; // ebx
  int v4; // edi
  int result; // eax
  unsigned int i; // edi
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx

  sub_66BD5A(this + 28, 4u, 1u, Stream);
  v3 = this + 29;
  sub_66BD5A(this + 29, 4u, 1u, Stream);
  sub_66BD5A(this + 30, 4u, 1u, Stream);
  sub_66BD5A(this + 31, 4u, 1u, Stream);
  sub_66BD5A(this + 32, 4u, 1u, Stream);
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
      if ( ++v4 >= *v3 )
        goto LABEL_4;
    }
  }
  else
  {
LABEL_4:
    for ( i = 0; i < *v3; ++i )
    {
      v7 = *(uint32_t *)(*(this + 19) + 4 * i);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 20))(v7);
      v8 = *(uint32_t *)(*(this + 19) + 4 * i);
      (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)v8 + 12))(v8, 1024, 1024);
      v9 = *(uint32_t *)(*(this + 19) + 4 * i);
      (*(void (/*thiscall*/ **)(int, FILE *))(*(uint32_t *)v9 + 108))(v9, Stream);
    }
    return 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x4175D0 sub_4175D0
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
// 0x4176A0 sub_4176A0
// ------------------------------------------------------------
unsigned int /*cdecl*/ sub_4176A0(const char *a1)
{
  return 5 * strlen(a1);
}



// ------------------------------------------------------------
// 0x4176C0 sub_4176C0
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
int /*thiscall*/ sub_4176E0(
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
int /*thiscall*/ sub_417B60(LONG *this, int a2, int a3, int a4)
{
  int v5; // eax
  unsigned int v6; // esi
  unsigned int v7; // eax
  int v8; // ecx
  unsigned int v9; // eax
  int v10; // esi
  int result; // eax
  int v12; // ecx
  unsigned int i; // esi
  int v15; // ecx
  int v16; // ecx
  int v17; // [esp+Ch] [ebp-4h] BYREF

  *(this + 25) = 2 * *(uint32_t *)(a2 + 4);
  *(this + 26) = *(uint32_t *)(a2 + 4);
  *(this + 27) = *(uint32_t *)a2;
  sub_402AE0((int)(this + 20), (const char *)(a2 + 28));
  v5 = *(this + 26);
  qmemcpy(this + 4, (const void *)a2, 0x3Cu);
  if ( v5 == 0 && a4 != 0 )
    *(this + 26) = a4;
  if ( a3 == 0 )
    a3 = -*(this + 27);
  v6 = 0x400u / *(this + 25);
  v7 = 0x400u / *(this + 27);
  *(this + 31) = v6;
  v8 = v6 * v7;
  *(this + 32) = v7;
  v9 = *(this + 28) / (v6 * v7);
  *(this + 30) = v8;
  *(this + 29) = ++v9;
  *(this + 19) = (LONG)operator new(4 * v9);
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
    v12 = *(this + 3);
    v17 = 0;
    (*(void (/*thiscall*/ **)(uint32_t, int, int *))(**(uint32_t **)(v12 + 12) + 8))(*(uint32_t *)(v12 + 12), 12, &v17);
    (*(void (/*thiscall*/ **)(int, int, int))(*(uint32_t *)v17 + 12))(v17, 1024, 1024);
    for ( i = 0; i < *(this + 29); ++i )
    {
      (*(void (/*thiscall*/ **)(int, uint32_t))(*(uint32_t *)v17 + 28))(v17, 0);
      *(uint32_t *)a2 = 12;
      sub_4176E0(
        this,
        v17,
        (int *)a2,
        a3,
        a4,
        (LPCSTR)(a2 + 28),
        i,
        (uint16_t)word_8A779E,
        (uint16_t)word_8A775E);
      sub_4176E0(
        this,
        v17,
        (int *)a2,
        a3,
        a4,
        (LPCSTR)(a2 + 28),
        i,
        (uint16_t)word_8A77A6,
        (uint16_t)word_8A7766);
      sub_4176E0(
        this,
        v17,
        (int *)a2,
        a3,
        a4,
        (LPCSTR)(a2 + 28),
        i,
        (uint16_t)word_8A77AA,
        (uint16_t)word_8A776A);
      *(uint32_t *)a2 = 15;
      *(uint8_t *)(a2 + 23) = 0;
      sub_4176E0(
        this,
        v17,
        (int *)a2,
        a3 - 3,
        a4,
        "Arial Narrow",
        i,
        (uint16_t)word_8A7798,
        (uint16_t)word_8A7758);
      sub_4176E0(
        this,
        v17,
        (int *)a2,
        a3 - 3,
        a4,
        "Arial Narrow",
        i,
        (uint16_t)word_8A77A0,
        (uint16_t)word_8A7760);
      sub_4176E0(
        this,
        v17,
        (int *)a2,
        a3 - 3,
        a4,
        "Arial Narrow",
        i,
        (uint16_t)word_8A77A2,
        (uint16_t)word_8A7762);
      sub_4176E0(
        this,
        v17,
        (int *)a2,
        a3 - 3,
        a4,
        "Arial Narrow",
        i,
        (uint16_t)word_8A77A4,
        (uint16_t)word_8A7764);
      sub_4176E0(
        this,
        v17,
        (int *)a2,
        a3 - 3,
        a4,
        "Arial Narrow",
        i,
        (uint16_t)word_8A77AE,
        (uint16_t)word_8A776E);
      *(uint32_t *)a2 = 11;
      *(uint8_t *)(a2 + 23) = -127;
      sub_4176E0(
        this,
        v17,
        (int *)a2,
        a3 + 1,
        a4,
        &byte_6C29C8,
        i,
        (uint16_t)word_8A77A8,
        (uint16_t)word_8A7768);
      sub_4176E0(
        this,
        v17,
        (int *)a2,
        a3 + 1,
        a4,
        &byte_6C29C8,
        i,
        (uint16_t)word_8A77AC,
        (uint16_t)word_8A776C);
      sub_4176E0(
        this,
        v17,
        (int *)a2,
        a3 + 1,
        a4,
        &byte_6C29C8,
        i,
        (uint16_t)word_8A779A,
        (uint16_t)word_8A775A);
      sub_4176E0(
        this,
        v17,
        (int *)a2,
        a3 + 1,
        a4,
        &byte_6C29C8,
        i,
        (uint16_t)word_8A779C,
        (uint16_t)word_8A775C);
      v15 = *(uint32_t *)(*(this + 19) + 4 * i);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v15 + 20))(v15);
      v16 = *(uint32_t *)(*(this + 19) + 4 * i);
      (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v16 + 16))(v16, v17);
    }
    (*(void (/*thiscall*/ **)(uint32_t, int *))(**(uint32_t **)(*(this + 3) + 12) + 12))(*(uint32_t *)(*(this + 3) + 12), &v17);
    return 1;
  }
  return result;
}


// ------------------------------------------------------------
// 0x417EE0 sub_417EE0
// ------------------------------------------------------------
int /*thiscall*/ sub_417EE0(uint32_t *this, FILE *Stream)
{
  FILE *v4; // edi
  int result; // eax
  unsigned int i; // edi
  int v7; // ecx
  int v8; // ecx
  FILE *Streama; // [esp+14h] [ebp+8h]

  sub_66BD5A(this + 28, 4u, 1u, Stream);
  sub_66BD5A(this + 29, 4u, 1u, Stream);
  sub_66BD5A(this + 30, 4u, 1u, Stream);
  sub_66BD5A(this + 31, 4u, 1u, Stream);
  sub_66BD5A(this + 32, 4u, 1u, Stream);
  sub_66BD5A(byte_8A77D8, 0xFFFFu, 1u, Stream);
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
      v7 = *(uint32_t *)(*(this + 19) + 4 * i);
      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v7 + 20))(v7);
      sub_411240(*(int **)(*(this + 19) + 4 * i), (int)Stream, i, 1024, 1024, 25);
      v8 = *(uint32_t *)(*(this + 19) + 4 * i);
      (*(void (/*thiscall*/ **)(int, FILE *))(*(uint32_t *)v8 + 108))(v8, Stream);
    }
    return 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x417FE0 sub_417FE0
// ------------------------------------------------------------
int /*thiscall*/ sub_417FE0(uint32_t *this, int a2)
{
  *(this + 6) = CreateFontA(-11, 0, 0, 0, 100, 0, 0, 0, 0x81u, 0, 0, 0, 0, &byte_6C29C0);
  *(this + 7) = CreateFontA(-11, 0, 0, 0, 100, 0, 0, 0, 0x81u, 0, 0, 0, 0, &byte_6C29C8);
  *(this + 8) = CreateFontA(-11, 0, 0, 0, 100, 0, 0, 0, 0x81u, 0, 0, 0, 0, &byte_6C29C0);
  return 1;
}



// ------------------------------------------------------------
// 0x418070 sub_418070
// ------------------------------------------------------------
int /*thiscall*/ sub_418070(int this)
{
  uint32_t *v2; // edi
  int i; // ebx

  v2 = (uint32_t *)(this + 131116);
  for ( i = 50; i != 0; --i )
  {
    if ( *v2 != 0 )
      (*(void (/*thiscall*/ **)(uint32_t, uint32_t *))(**(uint32_t **)(*(uint32_t *)(this + 12) + 12) + 12))(
        *(uint32_t *)(*(uint32_t *)(this + 12) + 12),
        v2);
    ++v2;
  }
  *(uint16_t *)(this + 42) = 0;
  *(uint16_t *)(this + 44) = 0;
  memset((void *)(this + 131116), 0, 0xC8u);
  memset((void *)(this + 46), 0xFFu, 0x1FFFCu);
  *(uint16_t *)(this + 131114) = -1;
  return sub_405060(2u, 0, 1);
}



// ------------------------------------------------------------
// 0x4180D0 sub_4180D0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_4180D0(uint32_t *this, uint32_t *a2, uint32_t *a3, uint32_t *a4)
{
  uint32_t *v4; // eax
  uint32_t *v5; // esi
  uint32_t *v6; // edx

  v4 = a4;
  if ( a3 != a4 )
  {
    v5 = (uint32_t *)*(this + 2);
    v6 = a3;
    if ( a4 != v5 )
    {
      do
      {
        *v6 = *v4;
        v6[1] = v4[1];
        v4 += 2;
        v6 += 2;
      }
      while ( v4 != v5 );
    }
    *(this + 2) = v6;
  }
  *a2 = a3;
  return a2;
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
  sub_4015C0(&v1, "invalid vector<T> subscript", 0x1Bu);
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
  sub_4015C0(&v1, "vector<T> too long", 0x12u);
  v5 = 0;
  sub_401740(pExceptionObject, &v1);
  pExceptionObject[0] = &std::length_error::`vftable';
  _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x418200 sub_418200
// ------------------------------------------------------------
int /*thiscall*/ sub_418200(int this)
{
  void *v2; // eax
  int result; // eax

  v2 = *(void **)(this + 24);
  *(uint32_t *)this = &off_6C29FC;
  if ( v2 != nullptr )
    DeleteObject(v2);
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
// 0x4182C0 sub_4182C0
// ------------------------------------------------------------
void /*thiscall*/ sub_4182C0(int this, int a2, unsigned int a3, int a4)
{
  void *v4; // edx
  int v6; // ecx
  unsigned int v7; // eax
  int v9; // edx
  int v10; // edx
  unsigned int v11; // eax
  int v12; // edx
  int v13; // eax
  char *v14; // edi
  int v15; // ecx
  int v16; // eax
  unsigned int v17; // ebx
  int v18; // eax
  bool v20; // cf
  int v21; // ecx
  int v22; // ebx
  int v23; // ebx
  int v24; // [esp-18h] [ebp-40h]
  int v25; // [esp-Ch] [ebp-34h]
  unsigned int v26; // [esp-8h] [ebp-30h]
  int v27; // [esp+0h] [ebp-28h] BYREF
  void *v28[4]; // [esp+Ch] [ebp-1Ch] BYREF
  int v29; // [esp+24h] [ebp-4h]
  int v30; // [esp+30h] [ebp+8h]
  int v31; // [esp+34h] [ebp+Ch]
  int v32; // [esp+38h] [ebp+10h]
  int v33; // [esp+38h] [ebp+10h]

  v4 = *(void **)(a4 + 4);
  v28[0] = *(void **)a4;
  v6 = *(uint32_t *)(this + 4);
  v28[3] = &v27;
  v28[1] = v4;
  if ( v6 != 0 )
    v7 = (*(uint32_t *)(this + 12) - v6) >> 3;
  else
    v7 = 0;
  if ( a3 != 0 )
  {
    if ( v6 != 0 )
      v9 = (*(uint32_t *)(this + 8) - v6) >> 3;
    else
      v9 = 0;
    if ( 0x1FFFFFFF - v9 < a3 )
      sub_418190(this);
    if ( v6 != 0 )
      v10 = (*(uint32_t *)(this + 8) - v6) >> 3;
    else
      v10 = 0;
    if ( v7 >= a3 + v10 )
    {
      v18 = *(uint32_t *)(this + 8);
      v20 = (v18 - a2) >> 3 < a3;
      v21 = 8 * a3;
      v30 = 8 * a3;
      v33 = v18;
      if ( v20 )
      {
        sub_44BD30(a2, v18, a2 + v21);
        v26 = a3 - ((*(uint32_t *)(this + 8) - a2) >> 3);
        v25 = *(uint32_t *)(this + 8);
        v29 = 2;
        sub_5E51F0(v25, v26, v28);
        v22 = v30 + *(uint32_t *)(this + 8);
        *(uint32_t *)(this + 8) = v22;
        sub_41FEB0(a2, v22 - v30, v28);
      }
      else
      {
        v23 = v18 - v21;
        *(uint32_t *)(this + 8) = sub_44BD30(v18 - v21, v18, v18);
        sub_44BD00(a2, v23, v33);
        sub_41FEB0(a2, a2 + v30, v28);
      }
    }
    else
    {
      if ( 0x1FFFFFFF - (v7 >> 1) >= v7 )
        v11 = (v7 >> 1) + v7;
      else
        v11 = 0;
      if ( v6 != 0 )
        v12 = (*(uint32_t *)(this + 8) - v6) >> 3;
      else
        v12 = 0;
      if ( v11 < a3 + v12 )
      {
        if ( v6 != 0 )
          v13 = (*(uint32_t *)(this + 8) - v6) >> 3;
        else
          v13 = 0;
        v11 = a3 + v13;
      }
      v31 = 8 * v11;
      v14 = (char *)operator new(8 * v11);
      v24 = *(uint32_t *)(this + 4);
      v28[2] = v14;
      v29 = 0;
      v32 = sub_44BD30(v24, a2, v14);
      sub_63A7C0(v32, a3, v28);
      sub_44BD30(a2, *(uint32_t *)(this + 8), v32 + 8 * a3);
      v15 = *(uint32_t *)(this + 4);
      if ( v15 != 0 )
        v16 = (*(uint32_t *)(this + 8) - v15) >> 3;
      else
        v16 = 0;
      v17 = v16 + a3;
      if ( v15 != 0 )
        j__free(*(void **)(this + 4));
      *(uint32_t *)(this + 12) = &v14[v31];
      *(uint32_t *)(this + 8) = &v14[8 * v17];
      *(uint32_t *)(this + 4) = v14;
    }
  }
}


// ------------------------------------------------------------
// 0x418510 sub_418510
// ------------------------------------------------------------
void */*thiscall*/ sub_418510(void *Block, char a2)
{
  sub_418200((int)Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x418540 sub_418540
// ------------------------------------------------------------
void /*thiscall*/ sub_418540(int *this, unsigned int a2, char a3, int a4)
{
  int v4; // edx
  unsigned int v5; // eax
  int v6; // eax

  v4 = *(this + 1);
  if ( v4 != 0 )
    v5 = (*(this + 2) - v4) >> 3;
  else
    v5 = 0;
  if ( v5 >= a2 )
  {
    if ( v4 != 0 && a2 < (*(this + 2) - v4) >> 3 )
      sub_4180D0(this, &a2, (uint32_t *)(v4 + 8 * a2), (uint32_t *)*(this + 2));
  }
  else
  {
    if ( v4 != 0 )
      v6 = (*(this + 2) - v4) >> 3;
    else
      v6 = 0;
    sub_4182C0((int)this, *(this + 2), a2 - v6, (int)&a3);
  }
}



// ============================================================
// SECTION 0x4185B0 — GDI 文本渲染三件套（DIB/TextOut/宽度表，0x4185B0/0x4186C0/0x418AA0）
// ============================================================
// ------------------------------------------------------------
// 0x4185B0 sub_4185B0
// ------------------------------------------------------------
int /*thiscall*/ sub_4185B0(int this, HWND hWnd, int a3, int a4)
{
  HDC DC; // edi
  HDC CompatibleDC; // eax
  void *v8; // [esp-4h] [ebp-48h]
  BITMAPINFO pbmi; // [esp+Ch] [ebp-38h] BYREF
  int v10; // [esp+40h] [ebp-4h]

  pbmi.bmiColors[0] = (RGBQUAD)this;
  sub_40B530((uint8_t *)this, a3, a4);
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
  v8 = *(void **)(this + 20);
  *(uint32_t *)(this + 16) = CompatibleDC;
  SelectObject(CompatibleDC, v8);
  ReleaseDC(hWnd, DC);
  *(uint32_t *)(this + 24) = 0;
  return this;
}



// ------------------------------------------------------------
// 0x4186C0 sub_4186C0
// ------------------------------------------------------------
uint16_t */*thiscall*/ sub_4186C0(int this, uint16_t a2)
{
  int v3; // ecx
  int v4; // ebx
  int v5; // eax
  int v6; // ecx
  uint16_t v8; // dx
  uint16_t v9; // ax
  int *v10; // esi
  int v11; // ecx
  uint16_t *v12; // ebx
  int v13; // edi
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
  unsigned int v26; // edi
  int v27; // eax
  uint32_t v28[4]; // [esp+Ch] [ebp-30h] BYREF
  int c; // [esp+1Ch] [ebp-20h]
  unsigned int v30; // [esp+20h] [ebp-1Ch]
  int i; // [esp+28h] [ebp-14h]
  int v32; // [esp+2Ch] [ebp-10h]
  int v33; // [esp+30h] [ebp-Ch]
  CHAR String; // [esp+34h] [ebp-8h] BYREF
  char v35; // [esp+35h] [ebp-7h]
  char v36; // [esp+36h] [ebp-6h]
  bool v37; // [esp+3Bh] [ebp-1h]

  v33 = this;
  v37 = a2 >= 0x80u;
  if ( a2 < 0x80u )
  {
    String = a2;
    v35 = 0;
  }
  else
  {
    String = HIBYTE(a2);
    v35 = a2;
    v36 = 0;
  }
  v3 = *(uint32_t *)(this + 131320);
  v4 = this + 131316;
  c = this + 131316;
  if ( v3 != 0 )
    v5 = (*(uint32_t *)(this + 131324) - v3) >> 3;
  else
    v5 = 0;
  if ( *(uint16_t *)(this + 42) == v5 )
  {
    if ( *(uint16_t *)(this + 44) == 50 )
      sub_418070(this);
    if ( (*(int (/*thiscall*/ **)(uint32_t, int, int))(**(uint32_t **)(*(uint32_t *)(this + 12) + 12) + 8))(
           *(uint32_t *)(*(uint32_t *)(this + 12) + 12),
           14,
           this + 4 * *(uint16_t *)(this + 44) + 131116) != 1 )
      return nullptr;
    v6 = *(uint32_t *)(this + 4 * *(uint16_t *)(this + 44) + 131116);
    if ( (*(int (/*thiscall*/ **)(int, int, int))(*(uint32_t *)v6 + 12))(v6, 256, 256) != 1 )
      return nullptr;
    sub_418540(162 * (uint16_t)++*(uint16_t *)(this + 44), 0, 0);
  }
  v8 = *(uint16_t *)(this + 44);
  v9 = *(uint16_t *)(this + 42);
  v10 = *(int **)(this + 4 * v8 + 131112);
  v30 = v9;
  v11 = *(uint32_t *)(this + 131320);
  if ( v11 == 0 )
LABEL_17:
    sub_418120(v4);
  if ( (*(uint32_t *)(this + 131324) - v11) >> 3 <= v30 )
  {
    v4 = c;
    goto LABEL_17;
  }
  v12 = (uint16_t *)(v11 + 8 * v30);
  *v12 = v8 - 1;
  v12[1] = (uint16_t)(v9 - 162 * (v8 - 1)) / 9;
  v12[2] = 2 * ((uint16_t)(v9 - 162 * (v8 - 1)) % 9);
  memset(*(void **)(this + 36), 1u, 0x800u);
  if ( a2 < 0xCAA1u || a2 > 0xF9FEu )
  {
    if ( v37 )
      SelectObject(*(HDC *)(v33 + 16), *(HGDIOBJ *)(v33 + 24));
    else
      SelectObject(*(HDC *)(v33 + 16), *(HGDIOBJ *)(v33 + 32));
    v13 = v33;
  }
  else
  {
    v13 = v33;
    SelectObject(*(HDC *)(v33 + 16), *(HGDIOBJ *)(v33 + 28));
  }
  SetBkMode(*(HDC *)(v13 + 16), 1);
  SetTextColor(*(HDC *)(v13 + 16), 0xFFFFFFFF);
  c = v37 + 1;
  TextOutA(*(HDC *)(v13 + 16), -1, 1, &String, c);
  (*(void (/*thiscall*/ **)(int *))(*v10 + 84))(v10);
  v30 = 2;
  do
  {
    --v30;
    v14 = 0;
    v15 = 0;
    v16 = 0;
    v37 = false;
    v32 = 0;
    for ( i = 0; ; i = v32 << 6 )
    {
      while ( 1 )
      {
        v17 = *(uint16_t *)(v16 + *(uint32_t *)(v33 + 36)) == 257;
        v18 = (uint16_t)v12[1];
        v19 = *v10;
        if ( v17 )
        {
          (*(void (/*thiscall*/ **)(int *, int, int, uint32_t))(v19 + 32))(
            v10,
            14 * (uint16_t)v12[2] + v15 + 1,
            14 * v18 + v14 + 1,
            0);
        }
        else
        {
          (*(void (/*thiscall*/ **)(int *, int, int, int))(v19 + 32))(
            v10,
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
    SelectObject(*(HDC *)(v33 + 16), *(HGDIOBJ *)(v33 + 32));
    TextOutA(*(HDC *)(v33 + 16), -1, 1, &String, c);
  }
  while ( v30 != 0 );
  v28[0] = 14 * (uint16_t)v12[2] + 1;
  v28[2] = v28[0] + 12;
  v20 = 14 * (uint16_t)v12[1] + 1;
  v28[3] = 14 * (uint16_t)v12[1] + 13;
  v28[1] = v20;
  v21 = 14 * (uint16_t)v12[2] + 15;
  v30 = v21 + 1;
  v22 = *v10;
  i = v20;
  (*(void (/*thiscall*/ **)(int *, int, int, int *, uint32_t *, int))(v22 + 148))(v10, v21 + 1, v20, v10, v28, -1);
  v23 = *v10;
  c = v21 - 1;
  (*(void (/*thiscall*/ **)(int *, int, int, int *, uint32_t *, int))(v23 + 148))(v10, v21 - 1, i, v10, v28, -1);
  v24 = *v10;
  v32 = i + 1;
  (*(void (/*thiscall*/ **)(int *, int, int, int *, uint32_t *, int))(v24 + 148))(v10, v21, i + 1, v10, v28, -1);
  v25 = *v10;
  (*(void (/*thiscall*/ **)(int *, int, int, int *, uint32_t *, int))(v25 + 148))(v10, v21, --i, v10, v28, -1);
  v26 = v30;
  (*(void (/*thiscall*/ **)(int *, unsigned int, int, int *, uint32_t *, int))(*v10 + 148))(v10, v30, v32, v10, v28, -1);
  (*(void (/*thiscall*/ **)(int *, int, int, int *, uint32_t *, int))(*v10 + 148))(v10, c, i, v10, v28, -1);
  (*(void (/*thiscall*/ **)(int *, unsigned int, int, int *, uint32_t *, int))(*v10 + 148))(v10, v26, i, v10, v28, -1);
  (*(void (/*thiscall*/ **)(int *, int, int, int *, uint32_t *, int))(*v10 + 148))(v10, c, v32, v10, v28, -1);
  (*(void (/*thiscall*/ **)(int *))(*v10 + 88))(v10);
  v27 = v33;
  *(uint16_t *)(v33 + 2 * a2 + 46) = *(uint16_t *)(v33 + 42);
  ++*(uint16_t *)(v27 + 42);
  sub_405060(2, 1, 0);
  return v12;
}


// ------------------------------------------------------------
// 0x418AA0 sub_418AA0
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
// 0x418CB0 sub_418CB0
// ------------------------------------------------------------
int /*thiscall*/ sub_418CB0(int *this)
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
FILE */*thiscall*/ sub_418CD0(uint8_t *this, int a2)
{
  bool v3; // zf
  unsigned int v4; // ecx
  FILE *v5; // eax
  char *v6; // eax
  FILE *v7; // ebx
  void *v8; // esi
  int v10; // [esp+8h] [ebp-8h] BYREF
  uint8_t *v11; // [esp+Ch] [ebp-4h]

  v3 = *(this + 100) == 0;
  v4 = *(uint32_t *)(a2 + 24);
  v11 = this;
  if ( v3 )
  {
    if ( v4 < 0x10 )
      v5 = fopen((const char *)(a2 + 4), "rb");
    else
      v5 = fopen(*(const char **)(a2 + 4), "rb");
  }
  else
  {
    if ( v4 < 0x10 )
      v6 = (char *)(a2 + 4);
    else
      v6 = *(char **)(a2 + 4);
    v5 = sub_40E3E0(&v10, &a2, v6, 0);
  }
  v7 = v5;
  if ( v5 == nullptr )
    return nullptr;
  v8 = this + 64;
  sub_66BD5A(v8, 0x20u, 1u, v5);
  if ( strcmp((const char *)v8, "Neople Image File") != 0 || *((uint32_t *)v11 + 21) != 0 )
  {
    if ( v11[100] == 0 )
      fclose(v7);
    return nullptr;
  }
  return v7;
}



// ------------------------------------------------------------
// 0x418DD0 sub_418DD0
// ------------------------------------------------------------
// 【解读】
//   按索引取图像对象: 12B 目录项（this+13 起 12*i）[+4] = 图像对象指针；越界/未建 → sub_419F00（全局占位图像）。
// ------------------------------------------------------------
int /*thiscall*/ sub_418DD0(uint32_t *this, unsigned int a2)
{
  int v2; // eax
  int v3; // eax

  v2 = *(this + 13);
  if ( v2 != 0 && a2 < (*(this + 14) - v2) / 12 && *(uint32_t *)((v3 = *(this + 13) + 12 * a2) + 4) != 0 )
    return *(uint32_t *)(v3 + 4);
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
int /*thiscall*/ sub_418E20(int this, unsigned int a2)
{
  unsigned int v2; // edi
  int v4; // ecx
  int v5; // ebx
  int v6; // eax
  FILE *v7; // eax
  FILE *v8; // ebx
  int v10; // edi
  int *v11; // eax
  unsigned int v12; // [esp+Ch] [ebp-8h]
  FILE *v13; // [esp+10h] [ebp-4h]
  FILE *v14; // [esp+1Ch] [ebp+8h]

  v2 = a2;
  v4 = *(uint32_t *)(this + 52);
  v5 = *(uint32_t *)(v4 + 12 * a2 + 4);
  v13 = (FILE *)v5;
  if ( v4 == 0 || a2 >= (*(uint32_t *)(this + 56) - v4) / 12 || v5 == 0 )
    return sub_419F00();
  v6 = sub_41A510(this + 8);
  LOBYTE(v6) = *(uint8_t *)(v5 + 4);
  if ( (uint8_t)v6 != 1 )
  {
    sub_404F40(v6, 0);
    v7 = sub_418CD0((uint8_t *)this, this + 20);
    v8 = v7;
    if ( v7 == nullptr )
      return sub_419F00();
    if ( dword_77F488 == 1 )
    {
      v14 = (FILE *)(a2 + 1);
    }
    else
    {
      v2 = 0;
      v7 = (FILE *)sub_418CB0((int *)this);
      v14 = v7;
    }
    v12 = v2;
    if ( v2 < (unsigned int)v14 )
    {
      v10 = 12 * v2;
      while ( 1 )
      {
        v11 = (int *)(v10 + *(uint32_t *)(this + 52));
        if ( *(uint8_t *)(v11[1] + 4) == 0 && *(uint32_t *)(this + 88) == 1 )
        {
          fseek(v8, *v11, 0);
          if ( (*(int (/*thiscall*/ **)(uint32_t, FILE *))(**(uint32_t **)(v10 + *(uint32_t *)(this + 52) + 4) + 108))(
                 *(uint32_t *)(v10 + *(uint32_t *)(this + 52) + 4),
                 v8) < 0 )
            break;
        }
        v7 = (FILE *)(v12 + 1);
        v10 += 12;
        if ( ++v12 >= (unsigned int)v14 )
          goto LABEL_19;
      }
      v7 = (FILE *)sub_419F00();
      v13 = v7;
    }
LABEL_19:
    sub_404F80((int)v7, 0, 0);
    if ( *(uint8_t *)(this + 100) == 0 )
      fclose(v8);
  }
  return (int)v13;
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
  sub_4015C0(&v1, "vector<T> too long", 0x12u);
  v5 = 0;
  sub_401740(pExceptionObject, &v1);
  pExceptionObject[0] = &std::length_error::`vftable';
  _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x418FD0 sub_418FD0
// ------------------------------------------------------------
int /*thiscall*/ sub_418FD0(int this)
{
  int i; // esi
  unsigned int v3; // esi
  char *v4; // edx
  char *v5; // ebx
  unsigned int v6; // eax
  char *v7; // ebx
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
  v3 = *(uint32_t *)(this + 44);
  v4 = (char *)(this + 24);
  if ( v3 < 0x10 )
    v5 = (char *)(this + 24);
  else
    v5 = *(char **)v4;
  v6 = (unsigned int)&v5[*(uint32_t *)(this + 40)];
  if ( v3 < 0x10 )
    v7 = (char *)(this + 24);
  else
    v7 = *(char **)v4;
  if ( v3 >= 0x10 )
    v4 = *(char **)v4;
  if ( v7 != nullptr )
    v8 = v7 - v4;
  else
    v8 = 0;
  if ( v6 != 0 )
    v6 -= (unsigned int)v7;
  sub_401230((uint32_t *)(this + 20), v8, v6);
  return sub_41A260(this + 8);
}



// ------------------------------------------------------------
// 0x419070 sub_419070
// ------------------------------------------------------------
// 【解读】
//   图像目录矢量中段插入（MSVC vector 模板实例，12B 元素: 偏移/对象/标志；0x357913941 = 12B 元素容量上限）。
// ------------------------------------------------------------
int /*thiscall*/ sub_419070(int *this, int a2, unsigned int a3, int *Block)
{
  int v5; // ecx
  int v6; // edx
  int v7; // ebx
  int result; // eax
  unsigned int v9; // ecx
  int v11; // eax
  int v12; // eax
  unsigned int v13; // ecx
  int v14; // eax
  int v15; // ebx
  int v16; // eax
  unsigned int v17; // edi
  void *v18; // ecx
  int v20; // edi
  int v21; // [esp-18h] [ebp-40h]
  int v22; // [esp-Ch] [ebp-34h]
  unsigned int v23; // [esp-8h] [ebp-30h]
  int v24; // [esp+0h] [ebp-28h] BYREF
  uint32_t v25[4]; // [esp+Ch] [ebp-1Ch] BYREF
  int v26; // [esp+24h] [ebp-4h]
  int v27; // [esp+30h] [ebp+8h]
  int v28; // [esp+34h] [ebp+Ch]
  char *Blocka; // [esp+38h] [ebp+10h]
  void *Blockb; // [esp+38h] [ebp+10h]

  v5 = *Block;
  v6 = Block[1];
  v7 = *(this + 1);
  result = Block[2];
  v25[3] = &v24;
  v25[0] = v5;
  v25[1] = v6;
  v25[2] = result;
  if ( v7 != 0 )
  {
    result = 715827883 * (*(this + 3) - v7);
    v9 = (*(this + 3) - v7) / 12;
  }
  else
  {
    v9 = 0;
  }
  if ( a3 != 0 )
  {
    if ( v7 != 0 )
      v11 = (*(this + 2) - v7) / 12;
    else
      v11 = 0;
    if ( 357913941 - v11 < a3 )
      sub_418F60(this);
    if ( v7 != 0 )
      v12 = (*(this + 2) - v7) / 12;
    else
      v12 = 0;
    if ( v9 >= a3 + v12 )
    {
      v18 = (void *)*(this + 2);
      Blockb = v18;
      if ( ((int)v18 - a2) / 12 >= a3 )
      {
        v27 = (int)v18 - 12 * a3;
        *(this + 2) = sub_59EE30(v27, v18, v18);
        sub_504450(a2, v27, Blockb);
        return sub_5043B0(a2, a2 + 12 * a3, v25);
      }
      else
      {
        sub_59EE30(a2, v18, a2 + 12 * a3);
        v23 = a3 - (*(this + 2) - a2) / 12;
        v22 = *(this + 2);
        v26 = 2;
        sub_5E51C0(v22, v23, v25);
        v20 = 12 * a3 + *(this + 2);
        *(this + 2) = v20;
        return sub_5043B0(a2, v20 - 12 * a3, v25);
      }
    }
    else
    {
      if ( 357913941 - (v9 >> 1) >= v9 )
        v13 = (v9 >> 1) + v9;
      else
        v13 = 0;
      if ( v7 != 0 )
        v14 = (*(this + 2) - v7) / 12;
      else
        v14 = 0;
      if ( v13 < a3 + v14 )
        v13 = a3 + sub_4DA030(this);
      v15 = 12 * v13;
      Blocka = (char *)operator new(12 * v13);
      v21 = *(this + 1);
      v26 = 0;
      v28 = sub_59EE30(v21, a2, Blocka);
      sub_623C10(v28, a3, v25);
      sub_59EE30(a2, *(this + 2), v28 + 12 * a3);
      v16 = *(this + 1);
      if ( v16 != 0 )
        v16 = (*(this + 2) - v16) / 12;
      v17 = v16 + a3;
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
  const char *v2; // eax

  *(uint32_t *)this = &off_6C2A64;
  *((uint32_t *)this + 2) = &off_6C2A60;
  if ( *((uint32_t *)this + 11) < 0x10u )
    v2 = this + 24;
  else
    v2 = *((const char **)this + 6);
  off_77F3FC("CNImagePackEx::Destroy - %s", v2);
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
// 0x4193D0 sub_4193D0
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_4193D0(int *this, unsigned int a2, int Block, int a4, int a5)
{
  int v6; // ecx
  unsigned int result; // eax
  int v8; // eax
  int v9; // edi

  v6 = *(this + 1);
  if ( v6 != 0 )
    result = (*(this + 2) - v6) / 12;
  else
    result = 0;
  if ( result >= a2 )
  {
    if ( v6 != 0 )
    {
      v9 = *(this + 2);
      result = (v9 - v6) / 12;
      if ( a2 < result )
      {
        result = v6 + 12 * a2;
        if ( result != v9 )
        {
          result = sub_47DDD0(v9, v9, result);
          *(this + 2) = result;
        }
      }
    }
  }
  else
  {
    if ( v6 != 0 )
      v8 = (*(this + 2) - v6) / 12;
    else
      v8 = 0;
    return sub_419070(this, *(this + 2), a2 - v8, &Block);
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
char */*thiscall*/ sub_419480(char *this, int a2)
{
  uint32_t *v3; // edi

  *(uint32_t *)this = &nengine::IObject::`vftable';
  *(this + 4) = 0;
  v3 = this + 8;
  sub_419E90(this + 8);
  *(uint32_t *)this = &off_6C2A64;
  *v3 = &off_6C2A60;
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
  *((uint32_t *)this + 24) = a2;
  return this;
}



// ------------------------------------------------------------
// 0x419520 sub_419520
// ------------------------------------------------------------
char */*thiscall*/ sub_419520(char *Block, char a2)
{
  sub_419320(Block);
  if ( (a2 & 1) != 0 )
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
  char v4; // cl
  bool v5; // al
  int *v6; // edi
  char *v7; // eax
  FILE *v8; // ebx
  const char *v9; // edi
  int v10; // edi
  int v11; // eax
  unsigned int v12; // ecx
  int v13; // ecx
  int v14; // eax
  int v15; // eax
  const char *v16; // eax
  const char *v17; // eax
  int v19; // [esp+14h] [ebp-11Ch]
  int Buffer; // [esp+1Ch] [ebp-114h] BYREF
  int v21; // [esp+20h] [ebp-110h] BYREF
  char v22; // [esp+27h] [ebp-109h]
  char FileName[260]; // [esp+28h] [ebp-108h] BYREF
  int v24; // [esp+12Ch] [ebp-4h]

  v24 = dword_796E50;
  sub_404F40(0);
  v4 = *(uint8_t *)(*(uint32_t *)(this + 96) + 12);
  v22 = 1;
  v5 = v4 == 1 && (uint8_t)ArgList == 0;
  v6 = Block;
  *(uint8_t *)(this + 100) = v5;
  if ( byte_8F77DC != 0 )
  {
    if ( (unsigned int)v6[6] < 0x10 )
      v7 = (char *)(v6 + 1);
    else
      v7 = (char *)v6[1];
    sub_419D40(FileName, v7, 0x104u, 1);
    if ( *(uint8_t *)(this + 100) == 1 )
    {
      if ( sub_40E3E0((int)&Block, (int)&ArgList, FileName, 0) != 0 )
        sub_4015C0(FileName, strlen(FileName));
    }
    else if ( _access(FileName, 0) == 0 )
    {
      sub_4015C0(FileName, strlen(FileName));
    }
  }
  sub_4014D0((std::_String_base *)(this + 20), v6, 0, -1);
  v8 = (FILE *)sub_418CD0(v6);
  if ( v8 != nullptr )
  {
    if ( *(uint32_t *)(this + 88) == 1 )
    {
      LOBYTE(v19) = 0;
      sub_4193D0(*(uint32_t *)(this + 92), 0, 0, v19);
      v10 = 0;
      ArgList = 0;
      while ( 1 )
      {
        v11 = *(uint32_t *)(this + 52);
        if ( v11 == 0 || ArgList >= (*(uint32_t *)(this + 56) - v11) / 12 )
          break;
        Buffer = 0;
        sub_66BD5A(&Buffer, 4u, 1u, v8);
        if ( Buffer == 17 )
        {
          Block = nullptr;
          sub_66BD5A(&Block, 4u, 1u, v8);
          *(uint32_t *)(v10 + *(uint32_t *)(this + 52) + 4) = *(uint32_t *)(*(uint32_t *)(this + 52) + 12 * (uint32_t)Block + 4);
          *(uint8_t *)(v10 + *(uint32_t *)(this + 52) + 8) = 1;
          v12 = ArgList + 1;
          *(uint32_t *)(v10 + *(uint32_t *)(this + 52)) = *(uint32_t *)(*(uint32_t *)(this + 52) + 12 * (uint32_t)Block);
          ArgList = v12;
          v10 += 12;
        }
        else
        {
          v13 = *(uint32_t *)(this + 96);
          v21 = 0;
          if ( (*(int (/*thiscall*/ **)(int, int, int *))(*(uint32_t *)v13 + 8))(v13, Buffer, &v21) < 0 )
          {
            if ( *(uint32_t *)(this + 44) < 0x10u )
              v16 = (const char *)(this + 24);
            else
              v16 = *(const char **)(this + 24);
            off_77F3FC("CNImagePackEx::Load - %s, CreateImage(%d) failed", v16, ArgList);
            v22 = 0;
            goto LABEL_38;
          }
          if ( sub_410750(v21, this, ArgList) < 0 )
          {
            off_77F3FC("CNImagePackEx::Load - SetImagePackEx(%d) failed", ArgList);
            v22 = 0;
            goto LABEL_38;
          }
          *(uint32_t *)(v10 + *(uint32_t *)(this + 52) + 4) = v21;
          Block = (int *)(v10 + *(uint32_t *)(this + 52));
          v14 = ftell(v8);
          *Block = v14;
          v15 = (*(int (/*thiscall*/ **)(int, FILE *))(*(uint32_t *)v21 + 116))(v21, v8);
          fseek(v8, v15 + *(uint32_t *)(v10 + *(uint32_t *)(this + 52)), 0);
          ++ArgList;
          v10 += 12;
        }
      }
    }
    if ( *(uint32_t *)(this + 44) < 0x10u )
      v17 = (const char *)(this + 24);
    else
      v17 = *(const char **)(this + 24);
    off_77F3FC("CNImagePackEx::Load - %s", v17);
    if ( *(uint8_t *)(this + 100) == 0 )
      fclose(v8);
  }
  else
  {
    if ( (unsigned int)v6[6] < 0x10 )
      v9 = (const char *)(v6 + 1);
    else
      v9 = (const char *)v6[1];
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
char */*thiscall*/ sub_4198A0(char *this, int a2, char *Src)
{
  uint32_t *v4; // edi
  size_t v6; // [esp+10h] [ebp-2Ch] BYREF
  void *Block; // [esp+14h] [ebp-28h]
  int v8; // [esp+24h] [ebp-18h]
  unsigned int v9; // [esp+28h] [ebp-14h]
  int v10; // [esp+2Ch] [ebp-10h]
  int v11; // [esp+38h] [ebp-4h]

  v10 = dword_796E50;
  *(uint32_t *)this = &nengine::IObject::`vftable';
  *(this + 4) = 0;
  v4 = this + 8;
  v11 = 0;
  sub_419E90(this + 8);
  *(uint32_t *)this = &off_6C2A64;
  *v4 = &off_6C2A60;
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
  *((uint32_t *)this + 24) = a2;
  v8 = 0;
  LOBYTE(Block) = 0;
  sub_4015C0(&v6, Src, strlen(Src));
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
MMRESULT /*cdecl*/ sub_4199A0(LPSTR pszFileName, HMMIO *a2, HGLOBAL *a3, LPMMCKINFO pmmcki)
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

  *a3 = nullptr;
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
      *a3 = v7;
      if ( v7 == nullptr )
      {
        v6 = 57344;
        goto LABEL_21;
      }
      *v7 = pch;
      *((uint32_t *)v7 + 2) = v12;
      *((uint32_t *)v7 + 3) = v13;
      *((uint16_t *)*a3 + 8) = *(uint16_t *)v14;
      if ( *(uint16_t *)v14 != 0 )
      {
        v8 = mmioRead(v5, (HPSTR)*a3 + 18, *(uint16_t *)v14);
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
        *a2 = v5;
        return result;
      }
    }
  }
  else
  {
    v6 = 57600;
  }
LABEL_21:
  if ( *a3 != nullptr )
  {
    GlobalFree(*a3);
    *a3 = nullptr;
  }
  if ( v5 != nullptr )
    mmioClose(v5, 0);
  *a2 = nullptr;
  return v6;
}



// ------------------------------------------------------------
// 0x419B40 sub_419B40
// ------------------------------------------------------------
MMRESULT /*cdecl*/ sub_419B40(HMMIO *a1, LPMMCKINFO pmmcki, MMCKINFO *pmmckiParent)
{
  mmioSeek(*a1, pmmckiParent->dwDataOffset + 4, 0);
  pmmcki->ckid = 1635017060;
  return mmioDescend(*a1, pmmcki, pmmckiParent, 0x10u);
}



// ------------------------------------------------------------
// 0x419B80 sub_419B80
// ------------------------------------------------------------
int /*cdecl*/ sub_419B80(HMMIO hmmio, unsigned int a2, int a3, int a4, unsigned int *a5)
{
  int result; // eax
  unsigned int v6; // edi
  unsigned int v7; // eax
  unsigned int v8; // esi
  HPSTR pchEndRead; // ecx
  char *pchNext; // eax
  char v11; // dl
  struct _MMIOINFO pmmioinfo; // [esp+Ch] [ebp-48h] BYREF

  result = mmioGetInfo(hmmio, &pmmioinfo, 0) != 0;
  if ( result != 0 )
    goto LABEL_11;
  v6 = a2;
  v7 = *(uint32_t *)(a4 + 4);
  if ( a2 > v7 )
    v6 = *(uint32_t *)(a4 + 4);
  v8 = 0;
  *(uint32_t *)(a4 + 4) = v7 - v6;
  if ( v6 == 0 )
  {
LABEL_10:
    result = mmioSetInfo(hmmio, &pmmioinfo, 0);
    if ( result == 0 )
    {
      *a5 = v6;
      return result;
    }
LABEL_11:
    *a5 = 0;
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
    *(uint8_t *)(v8 + a3) = v11;
    ++v8;
    pmmioinfo.pchNext = pchNext;
    if ( v8 >= v6 )
      goto LABEL_10;
  }
  *a5 = 0;
  return 57603;
}



// ------------------------------------------------------------
// 0x419C40 sub_419C40
// ------------------------------------------------------------
int /*cdecl*/ sub_419C40(HMMIO *a1, HGLOBAL *a2)
{
  if ( *a2 != nullptr )
  {
    GlobalFree(*a2);
    *a2 = nullptr;
  }
  if ( *a1 != nullptr )
  {
    mmioClose(*a1, 0);
    *a1 = nullptr;
  }
  return 0;
}



// ------------------------------------------------------------
// 0x419C90 sub_419C90
// ------------------------------------------------------------
int /*thiscall*/ sub_419C90(uint8_t *this, int a2)
{
  int result; // eax
  int v4; // edx

  if ( *(this + 4) != 0 )
    return -2147483646;
  v4 = *(uint32_t *)this;
  *((uint32_t *)this + 12) = a2;
  result = (*(int (/*thiscall*/ **)(uint8_t *))(v4 + 8))(this);
  if ( result >= 0 )
  {
    *(this + 4) = 1;
    return 1;
  }
  return result;
}



// ------------------------------------------------------------
// 0x419CD0 sub_419CD0
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
// 0x419CF0 sub_419CF0
// ------------------------------------------------------------
int /*cdecl*/ sub_419CF0(int a1)
{
  char v1; // cl

  if ( strlen((const char *)a1) == 2 )
  {
    byte_8F77DC = *(uint8_t *)a1;
    byte_8F77DD = *(uint8_t *)(a1 + 1);
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
int /*cdecl*/ sub_419D40(char *Buffer, char *Source, size_t Count, int a4)
{
  unsigned int v4; // eax
  char *v5; // esi
  char v6; // bl
  char v8; // cl
  char v9[260]; // [esp+10h] [ebp-108h] BYREF
  int v10; // [esp+114h] [ebp-4h]
  char v11; // [esp+12Fh] [ebp+17h]

  v10 = dword_796E50;
  v4 = strlen(Source);
  if ( a4 != 0 )
  {
    if ( a4 != 1 )
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
  if ( Count <= v4 + 5 )
    return 0x80000000;
  if ( v4 != 0 )
  {
    while ( 1 )
    {
      v8 = Source[v4];
      if ( v8 == 47 || v8 == 92 )
        break;
      if ( --v4 == 0 )
        goto LABEL_16;
    }
    qmemcpy(v9, Source, v4 + 1);
    v9[v4 + 1] = 0;
    sprintf(Buffer, "%s%c%s%c%s", v9, v6, v5, v11, &Source[v4 + 1]);
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
// 0x419E90 sub_419E90
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
// 0x419EB0 sub_419EB0
// ------------------------------------------------------------
int /*cdecl*/ sub_419EB0(uint32_t *a1)
{
  *(uint32_t *)(dword_8F77E0 + 28) = *a1;
  *(uint32_t *)(dword_8F77E0 + 32) = a1[1];
  return 1;
}



// ------------------------------------------------------------
// 0x419EE0 sub_419EE0
// ------------------------------------------------------------
int /*cdecl*/ sub_419EE0(uint32_t *a1)
{
  int v1; // ecx

  v1 = dword_8F77E0;
  *a1 = *(uint32_t *)(dword_8F77E0 + 28);
  a1[1] = *(uint32_t *)(v1 + 32);
  return 1;
}



// ------------------------------------------------------------
// 0x419F10 sub_419F10
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_419F10(uint32_t *a1, int a2, int a3, int a4, unsigned int a5, int a6, int a7)
{
  unsigned int v8; // eax
  unsigned int v9; // ecx
  unsigned int v10; // eax
  int v11; // edx
  unsigned int v12; // edi

  while ( a2 != a4 || a3 != a5 )
  {
    v8 = *(uint32_t *)(a4 + 8);
    v9 = --a5 >> 2;
    if ( v8 <= a5 >> 2 )
      v9 -= v8;
    v10 = (unsigned int)--a7 >> 2;
    v11 = a7 - 4 * v10;
    v12 = *(uint32_t *)(a6 + 8);
    if ( v12 <= v10 )
      v10 -= v12;
    *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(a6 + 4) + 4 * v10) + 4 * v11) = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(a4 + 4)
                                                                                              + 4 * v9)
                                                                                  + 4 * (a5 - 4 * (a5 >> 2)));
  }
  *a1 = a6;
  a1[1] = a7;
  return a1;
}



// ------------------------------------------------------------
// 0x419FA0 sub_419FA0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_419FA0(uint32_t *a1, int a2, unsigned int a3, int a4, int a5, int a6, unsigned int a7)
{
  unsigned int v7; // edx
  unsigned int v9; // eax
  unsigned int v10; // ecx
  unsigned int v11; // eax
  unsigned int v12; // edx
  unsigned int v13; // ebx

  v7 = a7;
  while ( a2 != a4 || a3 != a5 )
  {
    v9 = *(uint32_t *)(a2 + 8);
    v10 = a3 >> 2;
    if ( v9 <= a3 >> 2 )
      v10 -= v9;
    v11 = v7 >> 2;
    v12 = v7 - 4 * (v7 >> 2);
    v13 = *(uint32_t *)(a6 + 8);
    if ( v13 <= v11 )
      v11 -= v13;
    *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(a6 + 4) + 4 * v11) + 4 * v12) = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(a2 + 4)
                                                                                              + 4 * v10)
                                                                                  + 4 * (a3 - 4 * (a3 >> 2)));
    v7 = ++a7;
    ++a3;
  }
  *a1 = a6;
  a1[1] = v7;
  return a1;
}



// ------------------------------------------------------------
// 0x41A020 sub_41A020
// ------------------------------------------------------------
int **/*thiscall*/ sub_41A020(int *this, int **a2, int a3, unsigned int a4, int a5, unsigned int a6)
{
  int v7; // ebx
  unsigned int v8; // edi
  int v9; // ecx
  unsigned int v10; // eax
  unsigned int v11; // ebx
  int v12; // eax
  int v13; // ecx
  int v15; // [esp+18h] [ebp-8h]
  int v16; // [esp+1Ch] [ebp-4h]

  v7 = *(this + 3);
  v16 = a4 - v7;
  v8 = a6 - a4;
  v15 = v7 + *(this + 4);
  if ( a4 - v7 >= v15 - a6 )
  {
    sub_419FA0(&a3, a5, a6, (int)this, v15, a3, a4);
    if ( v8 != 0 )
    {
      v12 = *(this + 4);
      do
      {
        if ( v12 != 0 && --v12 == 0 )
          *(this + 3) = 0;
        --v8;
      }
      while ( v8 != 0 );
      *(this + 4) = v12;
    }
  }
  else
  {
    sub_419F10(&a3, (int)this, *(this + 3), a3, a4, a5, a6);
    if ( v8 != 0 )
    {
      v9 = *(this + 4);
      do
      {
        if ( v9 != 0 )
        {
          v10 = *(this + 3) + 1;
          v11 = 4 * *(this + 2);
          *(this + 3) = v10;
          if ( v11 <= v10 )
            *(this + 3) = 0;
          if ( --v9 == 0 )
            *(this + 3) = 0;
        }
        --v8;
      }
      while ( v8 != 0 );
      *(this + 4) = v9;
    }
  }
  v13 = *(this + 3);
  *a2 = this;
  a2[1] = (int *)(v16 + v13);
  return a2;
}



// ------------------------------------------------------------
// 0x41A110 sub_41A110
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
// 0x41A150 sub_41A150
// ------------------------------------------------------------
void /*thiscall*/ sub_41A150(uint8_t *this)
{
  *(uint32_t *)this = &off_6C2B30;
  sub_406E40((int)(this + 8));
  *(uint32_t *)this = &nengine::IObject::`vftable';
  *(this + 4) = 0;
}



// ------------------------------------------------------------
// 0x41A170 sub_41A170
// ------------------------------------------------------------
int sub_41A170()
{
  int v0; // edx
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

  v0 = dword_8F77E0;
  v1 = dword_8F77E0 + 8;
  for ( i = *(uint32_t *)(dword_8F77E0 + 20); v1 != v0 + 8 || i != *(uint32_t *)(v0 + 20) + *(uint32_t *)(v0 + 24); ++i )
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
    v0 = dword_8F77E0;
  }
  sub_406E40(v0 + 8);
  return 1;
}



// ------------------------------------------------------------
// 0x41A230 sub_41A230
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_41A230(uint8_t *Block, char a2)
{
  sub_41A150(Block);
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x41A260 sub_41A260
// ------------------------------------------------------------
int **/*cdecl*/ sub_41A260(int a1)
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
    if ( *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(dword_8F77E0 + 12) + 4 * v3) + 4 * (v1 - 4 * (v1 >> 2))) == a1 )
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
  sub_4015C0(&v1, "deque<T> too long", 0x11u);
  v5 = 0;
  sub_401740(pExceptionObject, &v1);
  pExceptionObject[0] = &std::length_error::`vftable';
  _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x41A340 sub_41A340
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_41A340(int this, unsigned int a2)
{
  unsigned int v2; // edx
  unsigned int v4; // eax
  unsigned int v5; // ecx
  unsigned int v6; // edi
  int v7; // esi
  char *v8; // eax
  const void *v9; // ecx
  char *v10; // eax
  char *v11; // edx
  unsigned int v12; // ecx
  char *v13; // edi
  size_t v14; // esi
  char *v15; // eax
  unsigned int result; // eax
  size_t v17; // [esp+8h] [ebp-Ch]
  char *v18; // [esp+10h] [ebp-4h]

  v2 = a2;
  v4 = *(uint32_t *)(this + 8);
  if ( 0xFFFFFFF - v4 < a2 )
    sub_41A2D0(this);
  v5 = v4 >> 1;
  if ( v4 >> 1 < 8 )
    v5 = 8;
  if ( a2 < v5 && v4 <= 0xFFFFFFF - v5 )
  {
    a2 = v5;
    v2 = v5;
  }
  v6 = *(uint32_t *)(this + 12) >> 2;
  v7 = 4 * v6;
  v18 = (char *)operator new(4 * (v2 + v4));
  v17 = 4 * ((int)(4 * *(uint32_t *)(this + 8) - 4 * v6) >> 2);
  v8 = (char *)memcpy_0(&v18[4 * v6], (const void *)(4 * v6 + *(uint32_t *)(this + 4)), v17);
  v9 = *(const void **)(this + 4);
  v10 = &v8[v17];
  if ( v6 > a2 )
  {
    memcpy_0(v10, v9, 4 * ((int)(4 * a2) >> 2));
    v14 = 4 * ((int)(v7 - 4 * a2) >> 2);
    v15 = (char *)memcpy_0(v18, (const void *)(4 * a2 + *(uint32_t *)(this + 4)), v14);
    v12 = a2;
    v13 = &v15[v14];
    if ( a2 == 0 )
      goto LABEL_15;
    goto LABEL_14;
  }
  v11 = (char *)memcpy_0(v10, v9, 4 * (v7 >> 2)) + 4 * (v7 >> 2);
  if ( a2 != v6 )
    memset(v11, 0, 4 * (a2 - v6));
  if ( v6 != 0 )
  {
    v12 = v6;
    v13 = v18;
LABEL_14:
    memset(v13, 0, 4 * v12);
  }
LABEL_15:
  if ( *(uint32_t *)(this + 4) != 0 )
    j__free(*(void **)(this + 4));
  result = a2 + *(uint32_t *)(this + 8);
  *(uint32_t *)(this + 4) = v18;
  *(uint32_t *)(this + 8) = result;
  return result;
}



// ------------------------------------------------------------
// 0x41A490 sub_41A490
// ------------------------------------------------------------
int /*thiscall*/ sub_41A490(int this, uint32_t *a2)
{
  int v3; // eax
  unsigned int v4; // eax
  unsigned int v5; // edi
  unsigned int v6; // ebx
  uint32_t *v7; // edi
  int result; // eax

  v3 = *(uint32_t *)(this + 16);
  if ( (((uint8_t)v3 + *(uint8_t *)(this + 12)) & 3) == 0 && *(uint32_t *)(this + 8) <= (unsigned int)(v3 + 4) >> 2 )
    sub_41A340(this, 1u);
  v4 = *(uint32_t *)(this + 8);
  v5 = *(uint32_t *)(this + 16) + *(uint32_t *)(this + 12);
  v6 = v5 >> 2;
  if ( v4 <= v5 >> 2 )
    v6 -= v4;
  if ( *(uint32_t *)(*(uint32_t *)(this + 4) + 4 * v6) == 0 )
    *(uint32_t *)(*(uint32_t *)(this + 4) + 4 * v6) = operator new(0x10u);
  v7 = (uint32_t *)(*(uint32_t *)(*(uint32_t *)(this + 4) + 4 * v6) + 4 * (v5 & 3));
  if ( v7 != nullptr )
    *v7 = *a2;
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
DWORD /*cdecl*/ sub_41A510(int a1)
{
  DWORD result; // eax
  int v2; // esi
  int v3; // ecx

  result = timeGetTime();
  v2 = a1;
  if ( *(uint16_t *)(a1 + 10) != 0 )
  {
    ++*(uint16_t *)(a1 + 8);
  }
  else
  {
    *(uint16_t *)(a1 + 8) = 0;
    v3 = *(uint32_t *)(v2 + 4);
    if ( v3 == -1 || v3 + *(uint32_t *)(dword_8F77E0 + 28) <= result )
      *(uint16_t *)(v2 + 10) = 1;
    else
      *(uint16_t *)(v2 + 10) = 2;
    *(uint32_t *)(v2 + 4) = timeGetTime();
    return sub_41A490(dword_8F77E0 + 8, &a1);
  }
  return result;
}



// ------------------------------------------------------------
// 0x41A580 sub_41A580
// ------------------------------------------------------------
void /*thiscall*/ sub_41A580(uint32_t *this)
{
  *this = &crypt4byte::`vftable';
  --dword_8F7A08;
}



// ------------------------------------------------------------
// 0x41A590 sub_41A590
// ------------------------------------------------------------
int /*fastcall*/ sub_41A590(unsigned int a1, int a2, int a3)
{
  uint8_t v4; // al
  int v5; // edx
  int result; // eax
  int v7; // ecx

  v4 = rand() & 0x7F;
  *(uint8_t *)(a1 + 4) = v4;
  *(uint8_t *)(a1 + 13) = v4;
  v5 = dword_8F7808[v4];
  result = v5 + HIWORD(a1);
  v7 = v5 + (uint16_t)a1;
  *(uint32_t *)(a1 + 5) = v7 ^ (result + a3);
  *(uint32_t *)(a1 + 9) = result ^ (a3 - v7);
  return result;
}



// ------------------------------------------------------------
// 0x41A5E0 sub_41A5E0
// ------------------------------------------------------------
int /*fastcall*/ sub_41A5E0(unsigned int a1)
{
  int v1; // edx
  int v2; // esi
  int result; // eax

  v1 = dword_8F7808[*(uint8_t *)(a1 + 4)] + HIWORD(a1);
  v2 = dword_8F7808[*(uint8_t *)(a1 + 13)] + (uint16_t)a1;
  result = (v2 ^ *(uint32_t *)(a1 + 5)) - v1;
  if ( result == v2 + (v1 ^ *(uint32_t *)(a1 + 9)) )
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
unsigned int /*fastcall*/ sub_41A630(unsigned int a1)
{
  bool v1; // zf
  __time32_t v3; // eax
  int *v4; // edi
  int v5; // ebx
  int v6; // ebx
  int v7; // ebx
  int v8; // edi
  uint8_t v9; // al
  int v10; // edx
  int v11; // eax
  int v12; // ecx
  int v13; // edx
  int v14; // edi
  int v15; // eax

  v1 = dword_8F7A08 == 0;
  *(uint32_t *)a1 = &crypt4byte::`vftable';
  if ( v1 )
  {
    v3 = time(nullptr);
    srand(v3);
    v4 = dword_8F7808;
    do
    {
      v5 = (uint8_t)rand();
      v6 = ((rand() << 8) | v5) << 8;
      v7 = ((uint8_t)rand() | v6) << 8;
      *v4++ = (uint8_t)rand() | v7;
    }
    while ( (int)v4 < (int)&dword_8F7A08 );
  }
  v8 = rand();
  v9 = rand() & 0x7F;
  *(uint8_t *)(a1 + 4) = v9;
  *(uint8_t *)(a1 + 13) = v9;
  v10 = dword_8F7808[v9];
  v11 = v10 + HIWORD(a1);
  v12 = v10 + (uint16_t)a1;
  v13 = v11 + v8;
  v14 = v11 ^ (v8 - v12);
  v15 = dword_8F7A08 + 1;
  *(uint32_t *)(a1 + 9) = v14;
  dword_8F7A08 = v15;
  *(uint32_t *)(a1 + 5) = v12 ^ v13;
  return a1;
}



// ------------------------------------------------------------
// 0x41A6F0 sub_41A6F0
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_41A6F0(uint32_t *Block, char a2)
{
  int v3; // ecx

  v3 = dword_8F7A08 - 1;
  *Block = &crypt4byte::`vftable';
  dword_8F7A08 = v3;
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x41A720 sub_41A720
// ------------------------------------------------------------
bool /*thiscall*/ sub_41A720(unsigned int *this, unsigned int a2)
{
  return a2 < *this
      && (uint8_t)(((1 << (a2 & 7)) & *(uint8_t *)((a2 >> 3) + *(this + 1))) >> (a2 & 7)) == 1;
}



// ------------------------------------------------------------
// 0x41A760 sub_41A760
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_41A760(unsigned int *this, unsigned int a2)
{
  uint8_t *result; // eax

  if ( a2 < *this )
  {
    result = (uint8_t *)(*(this + 1) + (a2 >> 3));
    *result &= ~(1 << (a2 & 7));
  }
  return result;
}



// ------------------------------------------------------------
// 0x41A790 sub_41A790
// ------------------------------------------------------------
void /*stdcall*/ sub_41A790(int a1)
{
  sub_6569D0(a1);
  j__free(*(void **)(a1 + 4));
  *(uint32_t *)(a1 + 4) = 0;
}



// ============================================================
// SECTION 0x41A7C0 — STL 容器模板实例族（vector/list/deque 诊断与操作）
// ============================================================
// ------------------------------------------------------------
// 0x41A7C0 sub_41A7C0 [串: "invalid vector<T> subscript"]
// ------------------------------------------------------------
void /*noreturn*/ sub_41A7C0()
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
  sub_4015C0(&v1, "invalid vector<T> subscript", 0x1Bu);
  v5 = 0;
  sub_401740(pExceptionObject, &v1);
  pExceptionObject[0] = &std::out_of_range::`vftable';
  _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
}



// ------------------------------------------------------------
// 0x41A830 sub_41A830 [串: "list<T> too long"]
// ------------------------------------------------------------
int /*thiscall*/ sub_41A830(uint32_t *this, unsigned int a2)
{
  int v2; // eax
  int result; // eax
  uint32_t pExceptionObject[10]; // [esp+4h] [ebp-50h] BYREF
  size_t v5; // [esp+2Ch] [ebp-28h] BYREF
  char v6; // [esp+30h] [ebp-24h]
  int v7; // [esp+40h] [ebp-14h]
  int v8; // [esp+44h] [ebp-10h]
  int v9; // [esp+50h] [ebp-4h]

  v2 = *(this + 2);
  if ( 0x3FFFFFFF - v2 < a2 )
  {
    v8 = 15;
    v7 = 0;
    v6 = 0;
    sub_4015C0(&v5, "list<T> too long", 0x10u);
    v9 = 0;
    sub_401740(pExceptionObject, &v5);
    pExceptionObject[0] = &std::length_error::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
  }
  result = a2 + v2;
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
  sub_4015C0(&v1, "vector<T> too long", 0x12u);
  v5 = 0;
  sub_401740(pExceptionObject, &v1);
  pExceptionObject[0] = &std::length_error::`vftable';
  _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x41A930 sub_41A930
// ------------------------------------------------------------
int /*cdecl*/ sub_41A930(int a1, int a2)
{
  int result; // eax
  int i; // esi
  uint32_t **v4; // ecx
  uint32_t *v5; // eax
  bool v6; // zf
  uint32_t *v7; // edi

  result = a2;
  for ( i = a1; i != a2; i += 12 )
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
    result = a2;
    *(uint32_t *)(i + 4) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x41A990 sub_41A990
// ------------------------------------------------------------
int /*thiscall*/ sub_41A990(uint32_t *this, unsigned int a2)
{
  int v2; // edx

  v2 = *(this + 1);
  if ( v2 == 0 || (*(this + 2) - v2) >> 2 <= a2 )
    sub_41A7C0();
  return v2 + 4 * a2;
}



// ------------------------------------------------------------
// 0x41A9C0 sub_41A9C0
// ------------------------------------------------------------
int /*thiscall*/ sub_41A9C0(uint32_t *this, unsigned int a2)
{
  int v2; // esi

  v2 = *(this + 1);
  if ( v2 == 0 || (*(this + 2) - v2) / 12 <= a2 )
    sub_41A7C0();
  return v2 + 12 * a2;
}



// ------------------------------------------------------------
// 0x41AA00 sub_41AA00
// ------------------------------------------------------------
unsigned int /*thiscall*/ sub_41AA00(int this, int Src, unsigned int a3, int *a4)
{
  int v5; // edx
  unsigned int result; // eax
  int v8; // ecx
  int v9; // ecx
  unsigned int v10; // eax
  int v11; // ecx
  int v12; // eax
  char *v14; // eax
  void *v15; // eax
  int v16; // eax
  int v17; // ecx
  unsigned int v18; // edi
  uint8_t *v19; // eax
  unsigned int v21; // edx
  int v22; // ecx
  char *v23; // edi
  int v24; // edi
  char *v25; // [esp+8h] [ebp-4h]
  int Srcb; // [esp+14h] [ebp+8h]
  char *Srca; // [esp+14h] [ebp+8h]
  int v28; // [esp+18h] [ebp+Ch]
  int v29; // [esp+18h] [ebp+Ch]

  v5 = *(uint32_t *)(this + 4);
  a4 = (int *)*a4;
  if ( v5 != 0 )
    result = (*(uint32_t *)(this + 12) - v5) >> 2;
  else
    result = 0;
  if ( a3 != 0 )
  {
    if ( v5 != 0 )
      v8 = (*(uint32_t *)(this + 8) - v5) >> 2;
    else
      v8 = 0;
    if ( 0x3FFFFFFF - v8 < a3 )
      sub_41A8C0(this);
    if ( v5 != 0 )
      v9 = (*(uint32_t *)(this + 8) - v5) >> 2;
    else
      v9 = 0;
    if ( result >= a3 + v9 )
    {
      v19 = *(uint8_t **)(this + 8);
      v21 = (int)&v19[-Src] >> 2;
      v22 = 4 * a3;
      v29 = (int)v19;
      Srca = (char *)(4 * a3);
      if ( v21 >= a3 )
      {
        v24 = (int)&v19[-v22];
        *(uint32_t *)(this + 8) = sub_55E7F0(&v19[-v22], (int)v19, v19);
        sub_5DAF70((void *)Src, v24, v29);
        return sub_49A9D0(Src, &Srca[Src], &a4);
      }
      else
      {
        sub_55E7F0((void *)Src, (int)v19, (void *)(Src + v22));
        sub_523700(*(uint32_t *)(this + 8), a3 - ((*(uint32_t *)(this + 8) - Src) >> 2), &a4);
        v23 = &Srca[*(uint32_t *)(this + 8)];
        *(uint32_t *)(this + 8) = v23;
        return sub_49A9D0(Src, v23 - Srca, &a4);
      }
    }
    else
    {
      if ( 0x3FFFFFFF - (result >> 1) >= result )
        v10 = (result >> 1) + result;
      else
        v10 = 0;
      if ( v5 != 0 )
        v11 = (*(uint32_t *)(this + 8) - v5) >> 2;
      else
        v11 = 0;
      if ( v10 < a3 + v11 )
      {
        if ( v5 != 0 )
          v12 = (*(uint32_t *)(this + 8) - v5) >> 2;
        else
          v12 = 0;
        v10 = a3 + v12;
      }
      v28 = 4 * v10;
      v25 = (char *)operator new(4 * v10);
      Srcb = 4 * ((Src - *(uint32_t *)(this + 4)) >> 2);
      v14 = (char *)memcpy_0(v25, *(const void **)(this + 4), Srcb);
      v15 = (void *)sub_523700(&v14[Srcb], a3, &a4);
      memcpy_0(v15, (const void *)Src, 4 * ((*(uint32_t *)(this + 8) - Src) >> 2));
      v16 = *(uint32_t *)(this + 4);
      if ( v16 != 0 )
        v17 = (*(uint32_t *)(this + 8) - v16) >> 2;
      else
        v17 = 0;
      v18 = v17 + a3;
      if ( v16 != 0 )
        j__free(*(void **)(this + 4));
      *(uint32_t *)(this + 12) = &v25[v28];
      *(uint32_t *)(this + 8) = &v25[4 * v18];
      *(uint32_t *)(this + 4) = v25;
      return (unsigned int)v25;
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x41ABE0 sub_41ABE0
// ------------------------------------------------------------
void /*thiscall*/ sub_41ABE0(uint32_t *this, int a2, int a3, uint32_t *a4, int a5)
{
  uint32_t *v5; // esi
  uint32_t *v6; // edi
  uint32_t v7[4]; // [esp+0h] [ebp-24h] BYREF
  uint32_t *v8; // [esp+10h] [ebp-14h]
  uint32_t *v9; // [esp+14h] [ebp-10h]
  int v10; // [esp+20h] [ebp-4h]

  v5 = (uint32_t *)a3;
  v9 = v7;
  v8 = this;
  v7[3] = a3;
  v10 = 0;
  while ( v5 != a4 )
  {
    v6 = sub_40C0F0(a2, *(uint32_t *)(a2 + 4), v5 + 2);
    sub_41A830(v8, 1u);
    *(uint32_t *)(a2 + 4) = v6;
    *(uint32_t *)v6[1] = v6;
    v5 = (uint32_t *)*v5;
  }
}



// ------------------------------------------------------------
// 0x41AC90 sub_41AC90
// ------------------------------------------------------------
int /*thiscall*/ sub_41AC90(uint32_t *this, unsigned int a2)
{
  int v2; // esi
  unsigned int v3; // edx

  v2 = *(this + 1);
  v3 = HIWORD(a2);
  if ( v2 != 0 && v3 < (*(this + 2) - v2) >> 2 )
    return *(uint32_t *)(v2 + 4 * v3) + 16 * ((uint16_t)a2 + 2);
  else
    return 0;
}



// ------------------------------------------------------------
// 0x41ACF0 sub_41ACF0
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
// 0x41AD10 sub_41AD10
// ------------------------------------------------------------
int /*thiscall*/ sub_41AD10(int *this, uint32_t *a2)
{
  int v3; // edi
  uint32_t *v4; // ebx
  int result; // eax

  v3 = *(this + 1);
  v4 = sub_40C0F0(v3, *(uint32_t *)(v3 + 4), a2);
  result = sub_41A830(this, 1u);
  *(uint32_t *)(v3 + 4) = v4;
  *(uint32_t *)v4[1] = v4;
  return result;
}



// ------------------------------------------------------------
// 0x41AD50 sub_41AD50
// ------------------------------------------------------------
int /*stdcall*/ sub_41AD50(int a1, int a2)
{
  return sub_41A930(a1, a2);
}



// ------------------------------------------------------------
// 0x41AD70 sub_41AD70
// ------------------------------------------------------------
int /*thiscall*/ sub_41AD70(uint32_t *this, uint8_t a2, int a3)
{
  unsigned int v4; // esi
  uint32_t *v5; // edi
  unsigned int v6; // ebx
  int v7; // eax
  int v8; // eax
  uint8_t *v9; // eax
  unsigned int v10; // esi
  int *v11; // eax
  int v12; // ebx
  int *v13; // eax

  if ( a2 < 4u || a2 > 0xCu )
    return -1;
  if ( (uint8_t)a3 == 1 && a2 == 4 )
    return -1;
  v4 = (uint8_t)(a2 - 4);
  v5 = this + 4;
  if ( *(uint32_t *)(sub_41A9C0(this + 4, v4) + 8) != 0 )
    v6 = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(sub_41A9C0(v5, (uint8_t)(a2 - 4)) + 4) + 4) + 8);
  else
    v6 = sub_41AD70(a2 + 1, 1);
  if ( v6 == -1 )
    return -1;
  v7 = sub_41A9C0(v5, v4);
  sub_5D2440(v7);
  v8 = sub_41A990(this, v4);
  if ( v6 < **(uint32_t **)v8 )
  {
    v9 = (uint8_t *)(*(uint32_t *)(*(uint32_t *)v8 + 4) + (v6 >> 3));
    *v9 |= 1 << (v6 & 7);
  }
  if ( (uint8_t)a3 != 1 )
    return v6 << (a2 - 4);
  v10 = v4 - 1;
  a3 = 2 * v6;
  v11 = (int *)sub_41A9C0(v5, v10);
  sub_41AD10(v11, &a3);
  v12 = 2 * v6 + 1;
  a3 = v12;
  v13 = (int *)sub_41A9C0(v5, v10);
  sub_41AD10(v13, &a3);
  return v12;
}



// ------------------------------------------------------------
// 0x41AE90 sub_41AE90
// ------------------------------------------------------------
char /*thiscall*/ sub_41AE90(uint32_t *this, unsigned int a2, int a3)
{
  uint8_t v5; // cl
  unsigned int v6; // edi
  unsigned int v7; // esi
  int v8; // eax
  unsigned int **v9; // eax
  unsigned int v10; // edi
  unsigned int **v11; // eax
  uint32_t *v12; // ebx
  uint32_t *v13; // eax
  int *v14; // eax
  void *v15; // [esp-8h] [ebp-14h]
  unsigned int v16; // [esp+8h] [ebp-4h] BYREF

  if ( a2 < 0x10000 )
  {
    if ( (uint8_t)a3 < 4u )
      return 1;
    if ( (uint8_t)a3 <= 0xCu )
    {
      v5 = a3 - 4;
      v6 = a2 >> (a3 - 4);
      v7 = (uint8_t)(a3 - 4);
      v8 = *(this + 1);
      v16 = v6;
      if ( v8 == 0 || (*(this + 2) - v8) >> 2 <= (unsigned int)v5 )
        sub_41A7C0(this);
      if ( !sub_41A720(*(unsigned int **)(v8 + 4 * v5), v6) )
        return 1;
      if ( (uint8_t)sub_41AE90(a2, (uint8_t)(a3 - 1)) != 1 )
        return 0;
      v9 = (unsigned int **)sub_41A990(this, v7);
      sub_41A760(*v9, v6);
      v10 = v6 ^ 1;
      v11 = (unsigned int **)sub_41A990(this, v7);
      if ( sub_41A720(*v11, v10) || (uint8_t)a3 == 12 )
      {
        v14 = (int *)sub_41A9C0(this + 4, v7);
        sub_41AD10(v14, &v16);
        return 0;
      }
      v12 = this + 4;
      a3 = *(uint32_t *)(sub_41A9C0(v12, v7) + 4);
      v13 = **(uint32_t ***)(sub_41A9C0(v12, v7) + 4);
      if ( v13 == (uint32_t *)a3 )
        return 1;
      while ( v13[2] != v10 )
      {
        v13 = (uint32_t *)*v13;
        if ( v13 == (uint32_t *)a3 )
          return 1;
      }
      v15 = v13;
      sub_41A9C0(v12, v7);
      sub_4371E0((int)&a3, v15);
      return 1;
    }
  }
  return 0;
}



// ------------------------------------------------------------
// 0x41AFC0 sub_41AFC0
// ------------------------------------------------------------
char /*thiscall*/ sub_41AFC0(uint32_t *this, unsigned int a2)
{
  int v2; // esi
  unsigned int v3; // eax

  v2 = *(this + 1);
  v3 = HIWORD(a2);
  if ( v2 != 0 && v3 < (*(this + 2) - v2) >> 2 )
    LOBYTE(v3) = sub_41AE90(*(uint32_t **)(v2 + 4 * v3), (uint16_t)a2, 12);
  return v3;
}



// ------------------------------------------------------------
// 0x41B010 sub_41B010
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
// 0x41B050 sub_41B050
// ------------------------------------------------------------
uint32_t */*thiscall*/ sub_41B050(uint32_t *this, int a2)
{
  int *v3; // eax
  int v5; // [esp-10h] [ebp-30h]
  int v6; // [esp-Ch] [ebp-2Ch]
  int *v7; // [esp-8h] [ebp-28h]
  int v8; // [esp+0h] [ebp-20h] BYREF
  void *v9; // [esp+Ch] [ebp-14h]
  int *v10; // [esp+10h] [ebp-10h]
  int v11; // [esp+1Ch] [ebp-4h]

  v10 = &v8;
  v9 = this;
  v3 = (int *)sub_425940(this);
  *(this + 1) = v3;
  *(this + 2) = 0;
  v7 = *(int **)(a2 + 4);
  v6 = *v7;
  v5 = *v3;
  v11 = 0;
  sub_41ABE0(this, v5, v6, v7, a2);
  return this;
}



// ------------------------------------------------------------
// 0x41B0D0 sub_41B0D0
// ------------------------------------------------------------
unsigned int */*thiscall*/ sub_41B0D0(unsigned int **this, unsigned int **a2)
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
  result = *a2;
  if ( *a2 != nullptr )
  {
    *this = result;
    ++result[2];
  }
  return result;
}



// ------------------------------------------------------------
// 0x41B120 sub_41B120
// ------------------------------------------------------------
void /*thiscall*/ sub_41B120(int *this)
{
  int v2; // eax

  v2 = *(this + 1);
  if ( v2 != 0 )
  {
    sub_41A930(v2, *(this + 2));
    j__free((void *)*(this + 1));
  }
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
}



// ------------------------------------------------------------
// 0x41B170 sub_41B170
// ------------------------------------------------------------
int /*cdecl*/ sub_41B170(int a1, int a2, int a3)
{
  int v3; // edi
  int v4; // esi
  int *v5; // ebx
  uint32_t **v6; // ecx
  uint32_t *v7; // eax
  bool v8; // zf
  uint32_t *v9; // edi
  int v11; // [esp+14h] [ebp+10h]

  v3 = a1;
  if ( a1 == a2 )
    return a3;
  v4 = a3;
  do
  {
    if ( v4 != v3 )
    {
      v5 = *(int **)(v3 + 4);
      v6 = *(uint32_t ***)(v4 + 4);
      v11 = *v5;
      v7 = *v6;
      *v6 = v6;
      *(uint32_t *)(*(uint32_t *)(v4 + 4) + 4) = *(uint32_t *)(v4 + 4);
      v8 = v7 == *(uint32_t **)(v4 + 4);
      *(uint32_t *)(v4 + 8) = 0;
      if ( !v8 )
      {
        do
        {
          v9 = (uint32_t *)*v7;
          j__free(v7);
          v7 = v9;
        }
        while ( v9 != *(uint32_t **)(v4 + 4) );
        v3 = a1;
      }
      sub_41ABE0((uint32_t *)v4, **(uint32_t **)(v4 + 4), v11, v5, a1);
    }
    v3 += 12;
    v4 += 12;
    a1 = v3;
  }
  while ( v3 != a2 );
  return v4;
}



// ------------------------------------------------------------
// 0x41B200 sub_41B200
// ------------------------------------------------------------
int /*cdecl*/ sub_41B200(int a1, int a2, int a3)
{
  int v3; // edi
  int v4; // esi
  int *v5; // ebx
  uint32_t **v6; // ecx
  uint32_t *v7; // eax
  bool v8; // zf
  uint32_t *v9; // edi
  int v11; // [esp+10h] [ebp+Ch]
  int v12; // [esp+14h] [ebp+10h]

  v3 = a2;
  if ( a1 == a2 )
    return a3;
  v4 = a3;
  do
  {
    v3 -= 12;
    v4 -= 12;
    v11 = v3;
    if ( v4 != v3 )
    {
      v5 = *(int **)(v3 + 4);
      v6 = *(uint32_t ***)(v4 + 4);
      v12 = *v5;
      v7 = *v6;
      *v6 = v6;
      *(uint32_t *)(*(uint32_t *)(v4 + 4) + 4) = *(uint32_t *)(v4 + 4);
      v8 = v7 == *(uint32_t **)(v4 + 4);
      *(uint32_t *)(v4 + 8) = 0;
      if ( !v8 )
      {
        do
        {
          v9 = (uint32_t *)*v7;
          j__free(v7);
          v7 = v9;
        }
        while ( v9 != *(uint32_t **)(v4 + 4) );
        v3 = v11;
      }
      sub_41ABE0((uint32_t *)v4, **(uint32_t **)(v4 + 4), v12, v5, v11);
    }
  }
  while ( v3 != a1 );
  return v4;
}



// ------------------------------------------------------------
// 0x41B280 sub_41B280
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_41B280(int a1, int a2, uint32_t *a3)
{
  uint32_t *v3; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  v3 = a3;
  v6[4] = v6;
  v6[3] = a3;
  v7 = 0;
  while ( a1 != a2 )
  {
    LOBYTE(v7) = 1;
    if ( v3 != nullptr )
      sub_41B050(v3, a1);
    v3 += 3;
    LOBYTE(v7) = 0;
    a1 += 12;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x41B310 sub_41B310
// ------------------------------------------------------------
void /*thiscall*/ sub_41B310(int this)
{
  unsigned int i; // ebx
  int v3; // ecx
  void **v4; // esi
  int v5; // eax

  for ( i = 0; ; ++i )
  {
    v3 = *(uint32_t *)(this + 4);
    if ( v3 == 0 || (*(uint32_t *)(this + 8) - v3) >> 2 <= i )
      break;
    v4 = *(void ***)(v3 + 4 * i);
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
  v5 = *(uint32_t *)(this + 20);
  if ( v5 != 0 )
  {
    sub_41A930(v5, *(uint32_t *)(this + 24));
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
// 0x41B420 sub_41B420
// ------------------------------------------------------------
int /*cdecl*/ sub_41B420(int a1, int a2, int a3)
{
  int result; // eax
  int i; // esi
  int *v5; // ebx
  uint32_t **v6; // ecx
  uint32_t *v7; // eax
  bool v8; // zf
  uint32_t *v9; // edi
  int v10; // [esp+Ch] [ebp+8h]

  result = a2;
  for ( i = a1; i != a2; i += 12 )
  {
    if ( i != a3 )
    {
      v5 = *(int **)(a3 + 4);
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
      sub_41ABE0((uint32_t *)i, **(uint32_t **)(i + 4), v10, v5, a2);
    }
    result = a2;
  }
  return result;
}



// ------------------------------------------------------------
// 0x41B4A0 sub_41B4A0
// ------------------------------------------------------------
int /*cdecl*/ sub_41B4A0(int a1, int a2, int a3)
{
  return sub_41B200(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x41B4C0 sub_41B4C0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_41B4C0(uint32_t *a1, int a2, int a3)
{
  uint32_t *v3; // esi
  uint32_t *result; // eax
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  v3 = a1;
  v6[4] = v6;
  v6[3] = a1;
  v7 = 0;
  while ( a2 != 0 )
  {
    LOBYTE(v7) = 1;
    if ( v3 != nullptr )
      result = sub_41B050(v3, a3);
    --a2;
    v3 += 3;
    LOBYTE(v7) = 0;
  }
  return result;
}



// ------------------------------------------------------------
// 0x41B550 sub_41B550
// ------------------------------------------------------------
void /*thiscall*/ sub_41B550(int this)
{
  unsigned int i; // esi
  int v3; // ecx
  void *v4; // edi

  for ( i = 0; ; ++i )
  {
    v3 = *(uint32_t *)(this + 4);
    if ( v3 == 0 || (*(uint32_t *)(this + 8) - v3) >> 2 <= i )
      break;
    v4 = *(void **)(v3 + 4 * i);
    if ( v4 != nullptr )
    {
      sub_41B310(*(uint32_t *)(v3 + 4 * i));
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
// 0x41B5E0 sub_41B5E0
// ------------------------------------------------------------
int */*thiscall*/ sub_41B5E0(int *this, int *a2, int a3, int a4)
{
  int v5; // edi

  if ( a3 != a4 )
  {
    v5 = sub_41B170(a4, *(this + 2), a3);
    sub_41A930(v5, *(this + 2));
    *(this + 2) = v5;
  }
  *a2 = a3;
  return a2;
}



// ------------------------------------------------------------
// 0x41B630 sub_41B630
// ------------------------------------------------------------
uint32_t */*stdcall*/ sub_41B630(uint32_t *a1, int a2, int a3)
{
  sub_41B4C0(a1, a2, a3);
  return &a1[3 * a2];
}



// ------------------------------------------------------------
// 0x41B660 sub_41B660
// ------------------------------------------------------------
void /*thiscall*/ sub_41B660(int *this, int a2, unsigned int a3, int a4)
{
  int v5; // ebx
  unsigned int v6; // ecx
  int v8; // eax
  int v9; // eax
  unsigned int v10; // ecx
  int v11; // eax
  char *v12; // ebx
  int v13; // eax
  unsigned int v14; // edi
  int v15; // eax
  uint32_t *v16; // ecx
  int v18; // edi
  uint32_t *v19; // esi
  uint32_t *v20; // eax
  bool v21; // zf
  uint32_t *v22; // edi
  int v23; // [esp-18h] [ebp-48h]
  uint32_t *v24; // [esp-Ch] [ebp-3Ch]
  int v25; // [esp-8h] [ebp-38h]
  int v26; // [esp+0h] [ebp-30h] BYREF
  int v27; // [esp+Ch] [ebp-24h] BYREF
  void *v28; // [esp+10h] [ebp-20h]
  void *Block; // [esp+18h] [ebp-18h]
  int *v30; // [esp+1Ch] [ebp-14h]
  int *v31; // [esp+20h] [ebp-10h]
  int v32; // [esp+2Ch] [ebp-4h]
  int v33; // [esp+38h] [ebp+8h]
  uint32_t *v34; // [esp+3Ch] [ebp+Ch]
  int v35; // [esp+40h] [ebp+10h]
  int v36; // [esp+40h] [ebp+10h]

  v31 = &v26;
  v30 = this;
  sub_41B050(&v27, a4);
  v5 = *(this + 1);
  v6 = 0;
  v32 = 0;
  if ( v5 != 0 )
    v6 = (*(this + 3) - v5) / 12;
  if ( a3 != 0 )
  {
    if ( v5 != 0 )
      v8 = (*(this + 2) - v5) / 12;
    else
      v8 = 0;
    if ( 357913941 - v8 < a3 )
      sub_41A8C0(this);
    if ( v5 != 0 )
      v9 = (*(this + 2) - v5) / 12;
    else
      v9 = 0;
    if ( v6 >= a3 + v9 )
    {
      v16 = (uint32_t *)*(this + 2);
      v36 = (int)v16;
      if ( ((int)v16 - a2) / 12 >= a3 )
      {
        v33 = (int)&v16[-3 * a3];
        *(this + 2) = (int)sub_41B280(v33, (int)v16, v16);
        sub_41B4A0(a2, v33, v36);
        sub_41B420(a2, a2 + 12 * a3, (int)&v27);
      }
      else
      {
        sub_41B280(a2, (int)v16, (uint32_t *)(a2 + 12 * a3));
        v25 = a3 - (*(this + 2) - a2) / 12;
        v24 = (uint32_t *)*(this + 2);
        LOBYTE(v32) = 3;
        sub_41B630(v24, v25, (int)&v27);
        v18 = 12 * a3 + *(this + 2);
        *(this + 2) = v18;
        v32 = 0;
        sub_41B420(a2, v18 - 12 * a3, (int)&v27);
      }
    }
    else
    {
      if ( 357913941 - (v6 >> 1) >= v6 )
        v10 = (v6 >> 1) + v6;
      else
        v10 = 0;
      if ( v5 != 0 )
        v11 = (*(this + 2) - v5) / 12;
      else
        v11 = 0;
      if ( v10 < a3 + v11 )
        v10 = a3 + sub_4DA030(this);
      v35 = 12 * v10;
      v12 = (char *)operator new(12 * v10);
      v23 = *(this + 1);
      Block = v12;
      LOBYTE(v32) = 1;
      v34 = sub_41B280(v23, a2, v12);
      sub_41B4C0(v34, a3, (int)&v27);
      sub_41B280(a2, *(this + 2), &v34[3 * a3]);
      v13 = *(this + 1);
      if ( v13 != 0 )
        v13 = (*(this + 2) - v13) / 12;
      v14 = v13 + a3;
      v15 = *(this + 1);
      if ( v15 != 0 )
      {
        sub_41A930(v15, *(this + 2));
        j__free((void *)*(this + 1));
      }
      *(this + 3) = (int)&v12[v35];
      *(this + 2) = (int)&v12[12 * v14];
      *(this + 1) = (int)v12;
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
// 0x41B970 sub_41B970
// ------------------------------------------------------------
void /*thiscall*/ sub_41B970(int *this, unsigned int a2, char a3, uint32_t **Block, int a5)
{
  int v5; // esi
  unsigned int v6; // eax
  int v7; // eax
  uint32_t *v8; // esi
  uint32_t *v9; // eax
  bool v10; // zf
  uint32_t *v11; // edi

  v5 = *(this + 1);
  if ( v5 != 0 )
    v6 = (*(this + 2) - v5) / 12;
  else
    v6 = 0;
  if ( v6 >= a2 )
  {
    if ( v5 != 0 && a2 < (*(this + 2) - v5) / 12 )
      sub_41B5E0(this, (int *)&a2, v5 + 12 * a2, *(this + 2));
  }
  else
  {
    if ( v5 != 0 )
      v7 = (*(this + 2) - v5) / 12;
    else
      v7 = 0;
    sub_41B660(this, *(this + 2), a2 - v7, (int)&a3);
  }
  v8 = Block;
  v9 = *Block;
  v10 = *Block == Block;
  *Block = Block;
  v8[1] = v8;
  if ( !v10 )
  {
    do
    {
      v11 = (uint32_t *)*v9;
      j__free(v9);
      v9 = v11;
    }
    while ( v11 != v8 );
  }
  j__free(v8);
}



// ------------------------------------------------------------
// 0x41BA60 sub_41BA60
// ------------------------------------------------------------
int */*thiscall*/ sub_41BA60(int *this)
{
  unsigned int *v2; // esi
  unsigned int v3; // eax
  void *v4; // eax
  unsigned int v5; // edx
  unsigned int v6; // ecx
  int v7; // edx
  unsigned int v8; // ecx
  unsigned int **v9; // eax
  bool v10; // zf
  uint32_t **v11; // eax
  int v12; // esi
  int v13; // edi
  int v14; // eax
  char v16[24]; // [esp-Ch] [ebp-34h] BYREF
  void *v17; // [esp+Ch] [ebp-1Ch]
  int v18; // [esp+10h] [ebp-18h] BYREF
  int v19; // [esp+14h] [ebp-14h]
  unsigned int i; // [esp+18h] [ebp-10h] BYREF
  int v21; // [esp+24h] [ebp-4h]

  v17 = this;
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
    v2 = (unsigned int *)operator new(8u);
    if ( v2 != nullptr )
    {
      v3 = ((1 << i) + 7) & 0xFFFFFFF8;
      *v2 = v3;
      v4 = malloc(v3 >> 3);
      v5 = *v2 >> 3;
      v6 = *v2 >> 5;
      v2[1] = (unsigned int)v4;
      memset(v4, 0, 4 * v6 + (v5 & 3));
    }
    else
    {
      v2 = nullptr;
    }
    v7 = *(this + 1);
    v18 = (int)v2;
    if ( v7 != 0 )
      v8 = (*(this + 2) - v7) >> 2;
    else
      v8 = 0;
    if ( v7 != 0 && v8 < (*(this + 3) - v7) >> 2 )
    {
      v9 = (unsigned int **)*(this + 2);
      *v9 = v2;
      *(this + 2) = (int)(v9 + 1);
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
    v12 = *(this + 6);
    v13 = *(uint32_t *)(v12 - 8);
    v18 = (int)sub_40C0F0(v13, *(uint32_t *)(v13 + 4), &i);
    sub_41A830((uint32_t *)(v12 - 12), 1u);
    v14 = v18;
    *(uint32_t *)(v13 + 4) = v18;
    **(uint32_t **)(v14 + 4) = v14;
  }
  return this;
}



// ------------------------------------------------------------
// 0x41BBE0 sub_41BBE0
// ------------------------------------------------------------
int /*thiscall*/ sub_41BBE0(void *this, unsigned int a2)
{
  void *v2; // esi
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
  void *v17; // ecx
  int v18; // edx
  unsigned int *v19; // esi
  unsigned int v20; // eax
  void *v21; // eax
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
  void *v40; // [esp+10h] [ebp-10h]
  int v41; // [esp+1Ch] [ebp-4h]

  v2 = this;
  result = 0;
  v40 = this;
  if ( a2 <= 0x1000 )
  {
    while ( a2 >= 1 << (result + 4) )
    {
      if ( (unsigned int)++result >= 9 )
        goto LABEL_6;
    }
    HIBYTE(a2) = result + 4;
LABEL_6:
    v4 = -1;
    v5 = 0;
    while ( 1 )
    {
      v6 = *((uint32_t *)v2 + 1);
      v39 = (uint32_t *)v5;
      if ( v6 == 0 || (*((uint32_t *)v2 + 2) - v6) >> 2 <= v5 )
        break;
      v7 = *(uint32_t **)(v6 + 4 * v5);
      Block = v7;
      if ( HIBYTE(a2) < 4u || HIBYTE(a2) > 0xCu )
      {
        v4 = -1;
        ++v5;
      }
      else
      {
        v8 = v7[5];
        v9 = v7 + 4;
        v10 = (uint8_t)(HIBYTE(a2) - 4);
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
          v11 = sub_41AD70(HIBYTE(a2) + 1, 1);
        }
        if ( v11 == -1 )
        {
          v2 = v40;
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
          v17 = Block;
          v18 = *((uint32_t *)Block + 1);
          if ( v18 == 0 || (*((uint32_t *)Block + 2) - v18) >> 2 <= v10 )
            goto LABEL_63;
          v19 = *(unsigned int **)(v18 + 4 * v10);
          if ( v11 < *v19 )
            *(uint8_t *)(v19[1] + (v11 >> 3)) |= 1 << (v11 & 7);
          v4 = v11 << (HIBYTE(a2) - 4);
          if ( v4 != -1 )
          {
            v20 = (unsigned int)v39;
            v2 = v40;
            goto LABEL_33;
          }
          v2 = v40;
          v5 = (unsigned int)v39 + 1;
        }
      }
    }
    v20 = a2;
LABEL_33:
    if ( v4 != -1 )
      return v4 + (v20 << 16);
    v21 = operator new(0x100020u);
    Block = v21;
    v41 = 0;
    if ( v21 != nullptr )
      v22 = (void *)sub_41BA60((int)v21);
    else
      v22 = nullptr;
    v23 = *((uint32_t *)v2 + 1);
    v41 = -1;
    Block = v22;
    if ( v23 != 0 )
      v24 = (*((uint32_t *)v2 + 2) - v23) >> 2;
    else
      v24 = 0;
    if ( v23 != 0 && v24 < (*((uint32_t *)v2 + 3) - v23) >> 2 )
    {
      v25 = *((uint32_t **)v2 + 2);
      *v25 = v22;
      *((uint32_t *)v2 + 2) = v25 + 1;
    }
    else
    {
      sub_41AA00(*((void **)v2 + 2), 1, (int)&Block);
    }
    v26 = *(uint32_t **)(*((uint32_t *)v2 + 2) - 4);
    v39 = v26;
    if ( HIBYTE(a2) >= 4u && HIBYTE(a2) <= 0xCu )
    {
      v27 = v26[5];
      v9 = v26 + 4;
      v28 = (uint8_t)(HIBYTE(a2) - 4);
      if ( v27 == 0 || (v9[2] - v27) / 12 <= v28 )
        sub_41A7C0(v9);
      if ( *(uint32_t *)(v27 + 12 * v28 + 8) != 0 )
      {
        v30 = v9[1];
        if ( v30 == 0 || (v9[2] - v30) / 12 <= v28 )
          sub_41A7C0(v9);
        v29 = *(uint32_t *)(*(uint32_t *)(*(uint32_t *)(v30 + 12 * v28 + 4) + 4) + 8);
      }
      else
      {
        v29 = sub_41AD70(HIBYTE(a2) + 1, 1);
      }
      if ( v29 != -1 )
      {
        Block = (void *)v9[1];
        if ( Block == nullptr || (v9[2] - (int)Block) / 12 <= v28 )
LABEL_58:
          sub_41A7C0(v9);
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
        v17 = v39;
        v34 = v39[1];
        if ( v34 == 0 || (v39[2] - v34) >> 2 <= v28 )
LABEL_63:
          sub_41A7C0(v17);
        v35 = *(unsigned int **)(v34 + 4 * v28);
        if ( v29 < *v35 )
          *(uint8_t *)(v35[1] + (v29 >> 3)) |= 1 << (v29 & 7);
        v2 = v40;
        v4 = v29 << (HIBYTE(a2) - 4);
        goto LABEL_69;
      }
      v2 = v40;
    }
    v4 = -1;
LABEL_69:
    v36 = *((uint32_t *)v2 + 1);
    if ( v36 != 0 )
      v37 = (*((uint32_t *)v2 + 2) - v36) >> 2;
    else
      v37 = 0;
    v20 = v37 - 1;
    return v4 + (v20 << 16);
  }
  return result;
}


// ------------------------------------------------------------
// 0x41BFE0 sub_41BFE0
// ------------------------------------------------------------
void /*thiscall*/ sub_41BFE0(void **this, const char *a2)
{
  unsigned int v3; // eax
  unsigned int v4; // esi
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
  if ( a2 != nullptr )
  {
    v3 = strlen(a2);
    v4 = v3;
    if ( v3 < 0x1000 )
    {
      if ( v3 != 0 )
      {
        v5 = v3 + 1;
        *this = operator new(0xCu);
        v6 = sub_41BBE0(v4 + 1);
        if ( v6 == -1 )
        {
          j__free(*this);
          *this = nullptr;
        }
        else
        {
          *(uint32_t *)*this = v6;
          *((uint32_t *)*this + 1) = v4;
          *((uint32_t *)*this + 2) = 1;
          qmemcpy((void *)sub_41AC90(*(uint32_t *)*this), a2, v5);
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
// 0x41C0C0 sub_41C0C0
// ------------------------------------------------------------
int /*stdcall*/ sub_41C0C0(char a1)
{
  return sub_423290(&a1, 1);
}



// ------------------------------------------------------------
// 0x41C0E0 sub_41C0E0
// ------------------------------------------------------------
int /*stdcall*/ sub_41C0E0(char a1)
{
  return sub_423290(&a1, 2);
}



// ------------------------------------------------------------
// 0x41C100 sub_41C100
// ------------------------------------------------------------
unsigned int /*stdcall*/ sub_41C100(const char *a1)
{
  const char *v1; // esi

  v1 = a1;
  if ( a1 == nullptr )
    return 0x80000000;
  a1 = (const char *)strlen(a1);
  sub_423290(&a1, 4);
  return sub_423290(v1, a1);
}



// ------------------------------------------------------------
// 0x41C150 sub_41C150
// ------------------------------------------------------------
int /*fastcall*/ sub_41C150(unsigned int a1, int a2, int a3)
{
  sub_41A590(a1, a2, a3);
  return a3;
}



// ------------------------------------------------------------
// 0x41C170 sub_41C170
// ------------------------------------------------------------
unsigned int **/*thiscall*/ sub_41C170(unsigned int **this, unsigned int **a2)
{
  *this = nullptr;
  sub_41B0D0(this, a2);
  return this;
}



// ------------------------------------------------------------
// 0x41C190 sub_41C190
// ------------------------------------------------------------
int /*thiscall*/ sub_41C190(uint32_t *this, int a2)
{
  return sub_425960(a2, *(this + 11), *(this + 26));
}



// ------------------------------------------------------------
// 0x41C1B0 sub_41C1B0
// ------------------------------------------------------------
int sub_41C1B0()
{
  return sub_429830((uint16_t)word_77F804);
}



// ------------------------------------------------------------
// 0x41C1C0 sub_41C1C0
// ------------------------------------------------------------
int /*thiscall*/ sub_41C1C0(uint8_t *this, char a2)
{
  *(this + 112) = a2;
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
// 0x41C210 sub_41C210
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
// 0x41C240 sub_41C240
// ------------------------------------------------------------
int /*thiscall*/ sub_41C240(uint32_t *this)
{
  uint32_t *v1; // esi
  int i; // edi

  v1 = this + 4;
  for ( i = 8; i != 0; --i )
  {
    if ( *v1 != 0 )
      (**(void (/*thiscall*/ ***)(uint32_t, int))*v1)(*v1, 1);
    *v1++ = 0;
  }
  return 1;
}



// ------------------------------------------------------------
// 0x41C270 sub_41C270
// ------------------------------------------------------------
int /*fastcall*/ sub_41C270(int a1, int a2, uint8_t a3)
{
  return sub_41A590(a1 + 248, a2, a3);
}



// ------------------------------------------------------------
// 0x41C290 sub_41C290
// ------------------------------------------------------------
BOOL /*thiscall*/ sub_41C290(void *this)
{
  return sub_41A5E0((unsigned int)this + 248) != 0;
}



// ------------------------------------------------------------
// 0x41C2B0 sub_41C2B0
// ------------------------------------------------------------
char /*thiscall*/ sub_41C2B0(int this, int a2)
{
  const char *v3; // esi
  int i; // esi
  char result; // al
  unsigned int v6; // [esp+Ch] [ebp-8h] BYREF
  uint8_t v7[4]; // [esp+10h] [ebp-4h] BYREF

  v3 = (const char *)(this + 113);
  off_77F3FC((char *)&byte_6C2B70, this + 113);
  sub_423200(dword_8F7B08, 1);
  if ( v3 != nullptr )
  {
    v6 = strlen(v3);
    sub_423290(&v6, 4);
    sub_423290(v3, v6);
  }
  if ( this != -177 )
  {
    v6 = strlen((const char *)(this + 177));
    sub_423290(&v6, 4);
    sub_423290(this + 177, v6);
  }
  for ( i = 0; i < 4; ++i )
  {
    v7[0] = *(uint8_t *)(this + i + 262);
    sub_423290(v7, 1);
  }
  sub_423290(a2, 16);
  sub_423380(dword_8F7B08);
  *(uint8_t *)(this + 92) = 1;
  *(uint8_t *)(this + 93) = 0;
  *(uint8_t *)(this + 94) = 0;
  result = sub_698F90(this + 80, 0, 0);
  *(uint8_t *)(this + 76) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x41C3C0 sub_41C3C0
// ------------------------------------------------------------
int /*thiscall*/ sub_41C3C0(uint32_t *this, int a2)
{
  *(this + 73) = a2;
  return a2;
}



// ------------------------------------------------------------
// 0x41C3D0 sub_41C3D0
// ------------------------------------------------------------
int /*thiscall*/ sub_41C3D0(uint32_t *this, char a2)
{
  int result; // eax
  uint32_t *v3; // esi
  int v4; // eax

  result = *(this + 73) - 1;
  if ( *(this + 73) == 1 )
  {
    v3 = *((uint32_t **)dword_8F8528 + 7);
    if ( a2 != 0 )
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
        return sub_431820(a2);
    }
  }
  return result;
}



// ------------------------------------------------------------
// 0x41C470 sub_41C470
// ------------------------------------------------------------
char /*thiscall*/ sub_41C470(uint8_t *this, int a2, char a3)
{
  *(this + a2 + 297) = a3;
  return a3;
}



// ------------------------------------------------------------
// 0x41C490 sub_41C490
// ------------------------------------------------------------
int /*thiscall*/ sub_41C490(uint32_t *this, int a2, int a3)
{
  *(this + a2 + 77) = a3;
  return a3;
}



// ------------------------------------------------------------
// 0x41C4B0 sub_41C4B0
// ------------------------------------------------------------
const CHAR */*stdcall*/ sub_41C4B0(int a1)
{
  const CHAR *result; // eax

  switch ( a1 )
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
// 0x41C570 sub_41C570
// ------------------------------------------------------------
int /*thiscall*/ sub_41C570(uint32_t *this, int a2)
{
  *(this + 88) = a2;
  dword_78FF38 = a2;
  return a2;
}



// ------------------------------------------------------------
// 0x41C590 sub_41C590
// ------------------------------------------------------------
bool /*thiscall*/ sub_41C590(uint32_t *this)
{
  return *(this + 87) == 4;
}



// ------------------------------------------------------------
// 0x41C5A0 sub_41C5A0
// ------------------------------------------------------------
int /*thiscall*/ sub_41C5A0(uint32_t *this)
{
  int v1; // edx

  v1 = *(this + 1);
  if ( v1 != 0 )
    return (*(this + 2) - v1) >> 2;
  else
    return 0;
}



// ------------------------------------------------------------
// 0x41C5C0 sub_41C5C0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_41C5C0(uint32_t *a1)
{
  uint32_t *result; // eax
  int *v2; // ecx

  result = a1;
  v2 = (int *)*a1;
  if ( *(uint8_t *)(*a1 + 33) == 0 )
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
// 0x41C5E0 sub_41C5E0
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
// 0x41C640 sub_41C640
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
// 0x41C6A0 sub_41C6A0
// ------------------------------------------------------------
unsigned int **/*cdecl*/ sub_41C6A0(unsigned int **a1, unsigned int **a2, unsigned int **a3)
{
  unsigned int **v3; // esi
  unsigned int **v4; // edi

  v3 = a1;
  if ( a1 == a2 )
    return a3;
  v4 = a3;
  do
    sub_41B0D0(v4++, v3++);
  while ( v3 != a2 );
  return v4;
}



// ------------------------------------------------------------
// 0x41C6E0 sub_41C6E0
// ------------------------------------------------------------
bool /*thiscall*/ sub_41C6E0(int *this)
{
  int v1; // esi

  v1 = *(this + 6);
  return sub_699000((int)this) >= v1;
}



// ------------------------------------------------------------
// 0x41C700 sub_41C700
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
// 0x41C7C0 sub_41C7C0
// ------------------------------------------------------------
void */*thiscall*/ sub_41C7C0(void *Block, char a2)
{
  sub_41C7F0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x41C7F0 sub_41C7F0
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
// 0x41C860 sub_41C860
// ------------------------------------------------------------
int /*thiscall*/ sub_41C860(uint32_t *this)
{
  int v2; // eax

  sub_4461F0(dword_8F8520);
  if ( *(uint8_t *)(dword_8F7B08 + 8) == 0 || (v2 = *(this + 27)) > 5 )
    sub_41C1E0();
  *(this + 27) = v2 + 1;
  sub_423200(dword_8F7B08, 3);
  return sub_423380(dword_8F7B08);
}



// ------------------------------------------------------------
// 0x41C8B0 sub_41C8B0
// ------------------------------------------------------------
int /*thiscall*/ sub_41C8B0(int this)
{
  int v3; // eax
  int v4; // ecx
  int v5; // edi
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
  v3 = *(uint32_t *)(this + 12);
  if ( v3 != 8 )
  {
    (*(void (/*thiscall*/ **)(uint32_t))(**(uint32_t **)(this + 4 * v3 + 16) + 8))(*(uint32_t *)(this + 4 * v3 + 16));
    v4 = *(uint32_t *)(this + 4 * *(uint32_t *)(this + 12) + 16);
    (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v4 + 4))(v4);
  }
  if ( *(uint8_t *)(this + 60) != 0 )
  {
    v5 = *(uint32_t *)(this + 72);
    if ( sub_699000(this + 48) >= v5 )
    {
      if ( *(uint8_t *)(dword_8F7B08 + 8) == 0 )
      {
        v6 = sub_422E70(841);
        sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v6, 1);
      }
      *(uint8_t *)(this + 60) = 0;
    }
  }
  if ( *(uint8_t *)(this + 92) != 0 && sub_699000(this + 80) >= 600000 )
  {
    v7 = sub_422E70(842);
    sub_44E8D0((char *)dword_8F8528, (void *)0x1B, v7, 1);
    *(uint8_t *)(this + 92) = 0;
  }
  return 1;
}



// ------------------------------------------------------------
// 0x41C9E0 sub_41C9E0
// ------------------------------------------------------------
int /*thiscall*/ sub_41C9E0(int this, int a2)
{
  int result; // eax

  result = a2;
  if ( *(uint8_t *)(this + 296) != (uint8_t)a2 )
  {
    *(uint8_t *)(this + 296) = a2;
    return sub_41C3D0((uint32_t *)this, a2);
  }
  return result;
}



// ------------------------------------------------------------
// 0x41CA00 sub_41CA00
// ------------------------------------------------------------
unsigned int **/*cdecl*/ sub_41CA00(unsigned int **a1, unsigned int **a2, unsigned int **a3)
{
  return sub_41C6A0(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x41CA20 sub_41CA20
// ------------------------------------------------------------
char /*stdcall*/ sub_41CA20(void **Block)
{
  void **v1; // edi
  char result; // al
  void **i; // esi

  v1 = Block;
  result = *((uint8_t *)Block + 21);
  for ( i = Block; result == 0; v1 = i )
  {
    sub_41CA20(i[2]);
    i = (void **)*i;
    j__free(v1);
    result = *((uint8_t *)i + 21);
  }
  return result;
}



// ------------------------------------------------------------
// 0x41CA60 sub_41CA60
// ------------------------------------------------------------
char /*stdcall*/ sub_41CA60(void **Block)
{
  void **v1; // edi
  char result; // al
  void **i; // esi

  v1 = Block;
  result = *((uint8_t *)Block + 21);
  for ( i = Block; result == 0; v1 = i )
  {
    sub_41CA60(i[2]);
    i = (void **)*i;
    j__free(v1);
    result = *((uint8_t *)i + 21);
  }
  return result;
}



// ------------------------------------------------------------
// 0x41CAA0 sub_41CAA0
// ------------------------------------------------------------
char /*stdcall*/ sub_41CAA0(void **Block)
{
  void **v1; // edi
  char result; // al
  void **i; // esi

  v1 = Block;
  result = *((uint8_t *)Block + 21);
  for ( i = Block; result == 0; v1 = i )
  {
    sub_41CAA0(i[2]);
    i = (void **)*i;
    j__free(v1);
    result = *((uint8_t *)i + 21);
  }
  return result;
}



// ------------------------------------------------------------
// 0x41CAE0 sub_41CAE0
// ------------------------------------------------------------
char /*stdcall*/ sub_41CAE0(void **Block)
{
  void **v1; // edi
  char result; // al
  void **i; // esi

  v1 = Block;
  result = *((uint8_t *)Block + 21);
  for ( i = Block; result == 0; v1 = i )
  {
    sub_41CAE0(i[2]);
    i = (void **)*i;
    j__free(v1);
    result = *((uint8_t *)i + 21);
  }
  return result;
}



// ------------------------------------------------------------
// 0x41CB20 sub_41CB20
// ------------------------------------------------------------
char /*stdcall*/ sub_41CB20(void **Block)
{
  void **v1; // edi
  char result; // al
  void **i; // esi

  v1 = Block;
  result = *((uint8_t *)Block + 21);
  for ( i = Block; result == 0; v1 = i )
  {
    sub_41CB20(i[2]);
    i = (void **)*i;
    j__free(v1);
    result = *((uint8_t *)i + 21);
  }
  return result;
}



// ------------------------------------------------------------
// 0x41CB60 sub_41CB60
// ------------------------------------------------------------
unsigned int **/*cdecl*/ sub_41CB60(unsigned int **a1, unsigned int **a2, unsigned int **a3)
{
  unsigned int **v3; // esi
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  v3 = a3;
  v6[4] = v6;
  v6[3] = a3;
  v7 = 0;
  while ( a1 != a2 )
  {
    LOBYTE(v7) = 1;
    if ( v3 != nullptr )
    {
      *v3 = nullptr;
      sub_41B0D0(v3, a1);
    }
    ++v3;
    LOBYTE(v7) = 0;
    ++a1;
  }
  return v3;
}



// ------------------------------------------------------------
// 0x41CBF0 sub_41CBF0
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
void /*thiscall*/ sub_41CC80(int this, int ArgList, int a3)
{
  int v3; // ebx
  int v4; // edi
  int v6; // ebx
  int v7; // eax
  int v8; // eax
  int v9; // ecx
  uint32_t *v10; // ebx
  int v11; // eax
  int i; // ebx
  int v13; // eax
  int v14; // eax
  int j; // ebx
  int v16; // eax
  int v17; // edi
  int v18; // eax
  int v19; // ebx
  int v20; // eax
  int k; // esi
  int v22; // eax
  int v23; // eax
  int v24; // [esp+Ch] [ebp-4h]

  v3 = a3;
  v4 = ArgList;
  if ( ArgList == a3 )
    return;
  off_77F3FC((char *)&byte_6C2CE8, ArgList, a3);
  sub_41A170();
  if ( a3 == 3 || a3 == 4 || (dword_77F488 = 1, a3 == 6) )
    dword_77F488 = 0;
  switch ( ArgList )
  {
    case 1:
      v8 = *(uint32_t *)(this + 20);
      if ( *(uint32_t *)(v8 + 216) == 1 )
        *(uint32_t *)(v8 + 216) = -1;
      goto LABEL_11;
    case 3:
      sub_4772A0(0);
      sub_45A420(0);
      v6 = *(uint32_t *)(*(uint32_t *)(this + 28) + 16);
      if ( v6 != 0 )
      {
        sub_425500(0);
        sub_424100(0);
        sub_475760();
        *(uint32_t *)(v6 + 108) = 0;
        sub_472AF0();
      }
      v3 = a3;
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
      switch ( v3 )
      {
        case 0:
          v9 = *(uint32_t *)(this + 16);
          *(uint32_t *)(this + 284) = *(uint32_t *)(*(uint32_t *)(this + 36) + 12);
          sub_46D300(v9);
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
            v3 = a3;
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
                    v14 = *(uint32_t *)(v13 + 196);
                    if ( v14 != 0 )
                      (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v14 + 1020))(v14);
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
                v3 = a3;
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
              v17 = *(uint32_t *)(v16 + 196);
              if ( v17 != 0 )
              {
                (*(void (/*thiscall*/ **)(int))(*(uint32_t *)v17 + 1020))(v17);
                (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v17 + 1200))(v17, 1);
                (*(void (/*thiscall*/ **)(int, int))(*(uint32_t *)v17 + 1212))(v17, v24);
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
          v23 = sub_656840(v22);
          sub_656630(v23);
          sub_656090(dword_8F8548);
          v3 = a3;
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
      sub_44EA20(v4, v3);
      return;
    default:
      goto LABEL_11;
  }
}


// ------------------------------------------------------------
// 0x41D300 sub_41D300
// ------------------------------------------------------------
void /*thiscall*/ sub_41D300(int *this, int a2)
{
  int v2; // [esp-8h] [ebp-8h]

  v2 = *(this + 3);
  *(this + 3) = a2;
  sub_41CC80((int)this, v2, a2);
}



// ------------------------------------------------------------
// 0x41D320 sub_41D320
// ------------------------------------------------------------
int /*thiscall*/ sub_41D320(int this)
{
  int v2; // eax
  uint32_t *v3; // edi
  void **v4; // edx
  int v5; // ecx
  uint32_t *v6; // eax
  int v7; // eax
  uint32_t *v8; // edi
  int result; // eax
  int v10; // [esp+Ch] [ebp-8h] BYREF
  char v11[4]; // [esp+10h] [ebp-4h] BYREF

  sub_65DC70(lpCriticalSection);
  v2 = *(uint32_t *)(this + 12);
  if ( v2 != 5 )
  {
    *(uint32_t *)(this + 12) = 0;
    sub_41CC80(this, v2, 0);
  }
  sub_4297A0(dword_8F8500);
  sub_4878B0(dword_8F8504);
  *(uint32_t *)(*(uint32_t *)(this + 20) + 164) = 0;
  v3 = *(uint32_t **)(this + 20);
  v4 = *(void ***)(v3[23] + 4);
  v10 = (int)v3;
  v3 += 22;
  sub_41CA60(v4);
  v5 = v10;
  *(uint32_t *)(v3[1] + 4) = v3[1];
  v6 = (uint32_t *)v3[1];
  v3[2] = 0;
  *v6 = v6;
  *(uint32_t *)(v3[1] + 8) = v3[1];
  sub_45C400(v5);
  v7 = *(uint32_t *)(this + 20);
  *(uint32_t *)(v7 + 104) = 0;
  *(uint32_t *)(v7 + 108) = 0;
  v8 = *(uint32_t **)(*(uint32_t *)(this + 28) + 16);
  if ( v8 != nullptr )
  {
    sub_425500(0);
    sub_424100(v8, 0);
    sub_475760();
    v8[27] = 0;
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
    sub_423200(dword_8F7B08, 8);
    v10 = 0xFFFF;
    sub_423290(&v10, 2);
    v11[0] = 2;
    sub_423290(v11, 1);
    return sub_423380(dword_8F7B08);
  }
  return result;
}



// ------------------------------------------------------------
// 0x41D520 sub_41D520
// ------------------------------------------------------------
int /*thiscall*/ sub_41D520(int *this)
{
  int v3; // [esp-8h] [ebp-Ch]

  sub_44AB50(1, 12);
  sub_44AB50(0, 12);
  *(uint8_t *)(*(this + 4) + 48) = 0;
  v3 = *(this + 3);
  *(this + 3) = 5;
  sub_41CC80((int)this, v3, 5);
  sub_423200(dword_8F7B08, 3);
  return sub_423380(dword_8F7B08);
}



// ------------------------------------------------------------
// 0x41D580 sub_41D580
// ------------------------------------------------------------
unsigned int **/*stdcall*/ sub_41D580(unsigned int **a1, unsigned int **a2, unsigned int **a3)
{
  return sub_41CB60(a1, a2, a3);
}



// ============================================================
// SECTION 0x41D5A0 — 模块切换辅助（map 容器/观察者清理/资源卸载链）
// ============================================================
// ------------------------------------------------------------
// 0x41D5A0 sub_41D5A0 [串: "vector<T> too long"]
// ------------------------------------------------------------
void /*noreturn*/ sub_41D5A0()
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
  sub_4015C0(&v1, "vector<T> too long", 0x12u);
  v5 = 0;
  sub_401740(pExceptionObject, &v1);
  pExceptionObject[0] = &std::length_error::`vftable';
  _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVlength_error_std__);
}



// ------------------------------------------------------------
// 0x41D610 sub_41D610 [串: "invalid map/set<T> iterator"]
// ------------------------------------------------------------
int ***/*thiscall*/ sub_41D610(uint32_t *this, int ***a2, int **a3)
{
  int **v3; // ebx
  int *v4; // edi
  int *v5; // ecx
  int *v6; // esi
  uint32_t *v7; // ecx
  int v8; // eax
  int *v9; // eax
  int v10; // ecx
  bool v11; // zf
  int v12; // eax
  int **v13; // eax
  char v14; // al
  uint32_t *v15; // ecx
  uint32_t *v16; // eax
  int v17; // eax
  uint32_t pExceptionObject[10]; // [esp+Ch] [ebp-5Ch] BYREF
  size_t v20; // [esp+34h] [ebp-34h] BYREF
  char v21; // [esp+38h] [ebp-30h]
  int v22; // [esp+48h] [ebp-20h]
  int v23; // [esp+4Ch] [ebp-1Ch]
  int v24; // [esp+50h] [ebp-18h]
  void *Block; // [esp+54h] [ebp-14h]
  uint32_t *v26; // [esp+58h] [ebp-10h]
  int v27; // [esp+64h] [ebp-4h]

  v26 = this;
  if ( *((uint8_t *)a3 + 21) != 0 )
  {
    v23 = 15;
    v22 = 0;
    v21 = 0;
    sub_4015C0(&v20, "invalid map/set<T> iterator", 0x1Bu);
    v27 = 0;
    sub_401740(pExceptionObject, &v20);
    pExceptionObject[0] = &std::out_of_range::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
  }
  v3 = a3;
  Block = a3;
  sub_41C5E0((int *)&a3);
  if ( *((uint8_t *)*v3 + 21) != 0 )
  {
    v4 = v3[2];
LABEL_8:
    v6 = v3[1];
    if ( *((uint8_t *)v4 + 21) == 0 )
      v4[1] = (int)v6;
    v7 = v26;
    v8 = v26[1];
    if ( *(int ***)(v8 + 4) == v3 )
    {
      *(uint32_t *)(v8 + 4) = v4;
    }
    else if ( (int **)*v6 == v3 )
    {
      *v6 = (int)v4;
    }
    else
    {
      v6[2] = (int)v4;
    }
    if ( *(int ***)v7[1] == v3 )
    {
      if ( *((uint8_t *)v4 + 21) != 0 )
      {
        v9 = v6;
      }
      else
      {
        v9 = (int *)sub_52E300(v4);
        v7 = v26;
      }
      *(uint32_t *)v7[1] = v9;
    }
    v10 = v7[1];
    v11 = *(uint32_t *)(v10 + 8) == (uint32_t)v3;
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
  if ( *((uint8_t *)v3[2] + 21) != 0 )
  {
    v4 = *v3;
    goto LABEL_8;
  }
  v5 = (int *)a3;
  v4 = a3[2];
  if ( a3 == v3 )
    goto LABEL_8;
  (*v3)[1] = (int)a3;
  *v5 = (int)*v3;
  if ( v5 == v3[2] )
  {
    v6 = v5;
  }
  else
  {
    v6 = (int *)v5[1];
    if ( *((uint8_t *)v4 + 21) == 0 )
      v4[1] = (int)v6;
    *v6 = (int)v4;
    v5[2] = (int)v3[2];
    v3[2][1] = (int)v5;
  }
  v12 = v26[1];
  if ( *(int ***)(v12 + 4) == v3 )
  {
    *(uint32_t *)(v12 + 4) = v5;
  }
  else
  {
    v13 = (int **)v3[1];
    if ( *v13 == (int *)v3 )
      *v13 = v5;
    else
      v13[2] = v5;
  }
  v5[1] = (int)v3[1];
  v14 = *((uint8_t *)v5 + 20);
  *((uint8_t *)v5 + 20) = *((uint8_t *)v3 + 20);
  *((uint8_t *)v3 + 20) = v14;
LABEL_35:
  if ( *((uint8_t *)Block + 20) == 1 )
  {
    v15 = v26;
    if ( v4 != *(int **)(v26[1] + 4) )
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
            v15 = v26;
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
            v15 = v26;
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
        v11 = v6 == *(int **)(v15[1] + 4);
        v6 = (int *)v6[1];
      }
      while ( !v11 );
    }
    *((uint8_t *)v4 + 20) = 1;
  }
  j__free(Block);
  v17 = v26[2];
  if ( v17 != 0 )
    v26[2] = v17 - 1;
  *a2 = a3;
  return a2;
}


// ------------------------------------------------------------
// 0x41D8D0 sub_41D8D0
// ------------------------------------------------------------
void /*thiscall*/ sub_41D8D0(uint32_t *this)
{
  char *v1; // esi
  int i; // edi

  *(uint8_t *)this = 0;
  *(this + 13) = 0;
  *(this + 14) = 0;
  v1 = (char *)(this + 16);
  for ( i = 5; i != 0; --i )
  {
    if ( *(uint32_t *)v1 != 0 )
      j__free(*(void **)v1);
    *(uint32_t *)v1 = 0;
    *((uint32_t *)v1 + 1) = 0;
    *((uint32_t *)v1 + 2) = 0;
    v1 += 16;
  }
}



// ------------------------------------------------------------
// 0x41D910 sub_41D910
// ------------------------------------------------------------
void /*thiscall*/ sub_41D910(char *this)
{
  `eh vector destructor iterator'(this + 60, 0x10u, 5, (void (/*thiscall*/ *)(void *))sub_5E5260);
}



// ------------------------------------------------------------
// 0x41D930 sub_41D930
// ------------------------------------------------------------
char /*thiscall*/ sub_41D930(uint32_t *this, unsigned int a2)
{
  char *v4; // eax

  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  if ( a2 == 0 )
    return 0;
  if ( a2 > 0x9249249 )
    sub_416610(this);
  v4 = (char *)operator new(28 * a2);
  *(this + 3) = &v4[28 * a2];
  *(this + 1) = v4;
  *(this + 2) = v4;
  return 1;
}



// ------------------------------------------------------------
// 0x41D980 sub_41D980
// ------------------------------------------------------------
int **/*thiscall*/ sub_41D980(int ***this, int **a2, int *a3, int *a4)
{
  int *v4; // ebx
  int *v5; // esi
  int v7; // eax
  uint32_t *v8; // eax
  int **v10; // ecx
  int **v11; // eax
  int *j; // eax
  int *i; // eax

  v4 = a4;
  v5 = a3;
  v7 = (int)*(this + 1);
  if ( a3 == *(int **)v7 && a4 == (int *)v7 )
  {
    sub_41CA60(*(void ***)(v7 + 4));
    (*(this + 1))[1] = (int *)*(this + 1);
    v8 = *(this + 1);
    *(this + 2) = nullptr;
    *v8 = v8;
    (*(this + 1))[2] = (int *)*(this + 1);
    *a2 = **(this + 1);
    return a2;
  }
  else
  {
    if ( a3 != a4 )
    {
      do
      {
        v10 = (int **)v5;
        if ( *((uint8_t *)v5 + 21) == 0 )
        {
          v11 = (int **)v5[2];
          if ( *((uint8_t *)v11 + 21) != 0 )
          {
            for ( i = (int *)v5[1]; *((uint8_t *)i + 21) == 0; i = (int *)i[1] )
            {
              if ( v5 != (int *)i[2] )
                break;
              v5 = i;
            }
            v5 = i;
          }
          else
          {
            v5 = (int *)v5[2];
            for ( j = *v11; *((uint8_t *)j + 21) == 0; j = (int *)*j )
              v5 = j;
          }
        }
        sub_41D610(this, (int ***)&a3, v10);
      }
      while ( v5 != v4 );
    }
    *a2 = v5;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x41DA40 sub_41DA40
// ------------------------------------------------------------
int **/*thiscall*/ sub_41DA40(int ***this, int **a2, int *a3, int *a4)
{
  int *v4; // ebx
  int *v5; // esi
  int v7; // eax
  uint32_t *v8; // eax
  int **v10; // ecx
  int **v11; // eax
  int *j; // eax
  int *i; // eax

  v4 = a4;
  v5 = a3;
  v7 = (int)*(this + 1);
  if ( a3 == *(int **)v7 && a4 == (int *)v7 )
  {
    sub_41CAA0(*(void ***)(v7 + 4));
    (*(this + 1))[1] = (int *)*(this + 1);
    v8 = *(this + 1);
    *(this + 2) = nullptr;
    *v8 = v8;
    (*(this + 1))[2] = (int *)*(this + 1);
    *a2 = **(this + 1);
    return a2;
  }
  else
  {
    if ( a3 != a4 )
    {
      do
      {
        v10 = (int **)v5;
        if ( *((uint8_t *)v5 + 21) == 0 )
        {
          v11 = (int **)v5[2];
          if ( *((uint8_t *)v11 + 21) != 0 )
          {
            for ( i = (int *)v5[1]; *((uint8_t *)i + 21) == 0; i = (int *)i[1] )
            {
              if ( v5 != (int *)i[2] )
                break;
              v5 = i;
            }
            v5 = i;
          }
          else
          {
            v5 = (int *)v5[2];
            for ( j = *v11; *((uint8_t *)j + 21) == 0; j = (int *)*j )
              v5 = j;
          }
        }
        sub_41D610(this, (int ***)&a3, v10);
      }
      while ( v5 != v4 );
    }
    *a2 = v5;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x41DB00 sub_41DB00
// ------------------------------------------------------------
int **/*thiscall*/ sub_41DB00(int ***this, int **a2, int *a3, int *a4)
{
  int *v4; // ebx
  int *v5; // esi
  int v7; // eax
  uint32_t *v8; // eax
  int **v10; // ecx
  int **v11; // eax
  int *j; // eax
  int *i; // eax

  v4 = a4;
  v5 = a3;
  v7 = (int)*(this + 1);
  if ( a3 == *(int **)v7 && a4 == (int *)v7 )
  {
    sub_41CAE0(*(void ***)(v7 + 4));
    (*(this + 1))[1] = (int *)*(this + 1);
    v8 = *(this + 1);
    *(this + 2) = nullptr;
    *v8 = v8;
    (*(this + 1))[2] = (int *)*(this + 1);
    *a2 = **(this + 1);
    return a2;
  }
  else
  {
    if ( a3 != a4 )
    {
      do
      {
        v10 = (int **)v5;
        if ( *((uint8_t *)v5 + 21) == 0 )
        {
          v11 = (int **)v5[2];
          if ( *((uint8_t *)v11 + 21) != 0 )
          {
            for ( i = (int *)v5[1]; *((uint8_t *)i + 21) == 0; i = (int *)i[1] )
            {
              if ( v5 != (int *)i[2] )
                break;
              v5 = i;
            }
            v5 = i;
          }
          else
          {
            v5 = (int *)v5[2];
            for ( j = *v11; *((uint8_t *)j + 21) == 0; j = (int *)*j )
              v5 = j;
          }
        }
        sub_41D610(this, (int ***)&a3, v10);
      }
      while ( v5 != v4 );
    }
    *a2 = v5;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x41DBC0 sub_41DBC0
// ------------------------------------------------------------
int **/*thiscall*/ sub_41DBC0(int ***this, int **a2, int *a3, int *a4)
{
  int *v4; // ebx
  int *v5; // esi
  int v7; // eax
  uint32_t *v8; // eax
  int **v10; // ecx
  int **v11; // eax
  int *j; // eax
  int *i; // eax

  v4 = a4;
  v5 = a3;
  v7 = (int)*(this + 1);
  if ( a3 == *(int **)v7 && a4 == (int *)v7 )
  {
    sub_41CB20(*(void ***)(v7 + 4));
    (*(this + 1))[1] = (int *)*(this + 1);
    v8 = *(this + 1);
    *(this + 2) = nullptr;
    *v8 = v8;
    (*(this + 1))[2] = (int *)*(this + 1);
    *a2 = **(this + 1);
    return a2;
  }
  else
  {
    if ( a3 != a4 )
    {
      do
      {
        v10 = (int **)v5;
        if ( *((uint8_t *)v5 + 21) == 0 )
        {
          v11 = (int **)v5[2];
          if ( *((uint8_t *)v11 + 21) != 0 )
          {
            for ( i = (int *)v5[1]; *((uint8_t *)i + 21) == 0; i = (int *)i[1] )
            {
              if ( v5 != (int *)i[2] )
                break;
              v5 = i;
            }
            v5 = i;
          }
          else
          {
            v5 = (int *)v5[2];
            for ( j = *v11; *((uint8_t *)j + 21) == 0; j = (int *)*j )
              v5 = j;
          }
        }
        sub_41D610(this, (int ***)&a3, v10);
      }
      while ( v5 != v4 );
    }
    *a2 = v5;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x41DC80 sub_41DC80
// ------------------------------------------------------------
int /*thiscall*/ sub_41DC80(int this, int a2)
{
  unsigned int **v3; // ebx
  unsigned int v4; // ecx
  unsigned int **v6; // eax
  unsigned int v7; // edx
  void **v8; // eax
  int v9; // eax
  int v10; // ecx
  unsigned int v11; // edx
  int v12; // edx
  unsigned int **v13; // ebx
  int v14; // ecx
  unsigned int v15; // eax

  if ( this == a2 )
    return this;
  v3 = *(unsigned int ***)(a2 + 4);
  if ( v3 == nullptr || (v4 = (*(uint32_t *)(a2 + 8) - (int)v3) >> 2) == 0 )
  {
    sub_4017E0(this);
    return this;
  }
  v6 = *(unsigned int ***)(this + 4);
  if ( v6 != nullptr )
    v7 = (*(uint32_t *)(this + 8) - (int)v6) >> 2;
  else
    v7 = 0;
  if ( v4 <= v7 )
  {
    v8 = (void **)sub_41C6A0(v3, *(unsigned int ***)(a2 + 8), v6);
    sub_4016E0(v8, *(void ***)(this + 8));
    v9 = *(uint32_t *)(a2 + 4);
    if ( v9 != 0 )
      v10 = *(uint32_t *)(this + 4) + 4 * ((*(uint32_t *)(a2 + 8) - v9) >> 2);
    else
      v10 = *(uint32_t *)(this + 4);
    *(uint32_t *)(this + 8) = v10;
    return this;
  }
  if ( v6 != nullptr )
    v11 = (*(uint32_t *)(this + 12) - (int)v6) >> 2;
  else
    v11 = 0;
  if ( v4 > v11 )
  {
    if ( v6 != nullptr )
    {
      sub_4016E0((void **)v6, *(void ***)(this + 8));
      j__free(*(void **)(this + 4));
    }
    v14 = *(uint32_t *)(a2 + 4);
    if ( v14 != 0 )
      v15 = (*(uint32_t *)(a2 + 8) - v14) >> 2;
    else
      v15 = 0;
    if ( sub_401950((uint32_t *)this, v15) != 0 )
      *(uint32_t *)(this + 8) = sub_41D580(
                                *(unsigned int ***)(a2 + 4),
                                *(unsigned int ***)(a2 + 8),
                                *(unsigned int ***)(this + 4));
    return this;
  }
  if ( v6 != nullptr )
    v12 = (*(uint32_t *)(this + 8) - (int)v6) >> 2;
  else
    v12 = 0;
  v13 = (unsigned int **)(*(uint32_t *)(a2 + 4) + 4 * v12);
  sub_41CA00(*(unsigned int ***)(a2 + 4), v13, *(unsigned int ***)(this + 4));
  *(uint32_t *)(this + 8) = sub_41CB60(v13, *(unsigned int ***)(a2 + 8), *(unsigned int ***)(this + 8));
  return this;
}



// ------------------------------------------------------------
// 0x41DDD0 sub_41DDD0
// ------------------------------------------------------------
void /*stdcall*/ sub_41DDD0(int a1, int a2)
{
  int i; // esi

  for ( i = a1; i != a2; i += 144 )
    sub_41CBF0(i);
}



// ------------------------------------------------------------
// 0x41DE00 sub_41DE00
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
// 0x41DE30 sub_41DE30
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
// 0x41E090 sub_41E090
// ------------------------------------------------------------
void */*thiscall*/ sub_41E090(void *Block, char a2)
{
  sub_41E0C0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x41E0C0 sub_41E0C0
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
// 0x41E260 sub_41E260
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
// 0x41E2A0 sub_41E2A0
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
// 0x41E400 sub_41E400
// ------------------------------------------------------------
void */*thiscall*/ sub_41E400(void *Block, char a2)
{
  sub_41E430();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x41E430 sub_41E430
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
int /*thiscall*/ sub_41E4F0(uint8_t *this, int a2)
{
  const char *v3; // edi
  const char *v4; // eax
  int v5; // esi
  char v7; // cl
  char v8; // cl

  sub_41DC80((int)(this + 268), a2);
  v3 = sub_41ACF0((unsigned int **)(*(uint32_t *)(a2 + 4) + 4));
  v4 = sub_41ACF0((unsigned int **)(*(uint32_t *)(a2 + 4) + 8));
  v5 = j__atol(v4);
  if ( strlen(v3) <= 0xF )
  {
    off_77F3FC((char *)&byte_6C2D68, v3, v5);
    *(uint32_t *)(dword_79C0A0 + 128) = dword_8F7B08;
    if ( sub_4231B0((char)v3, v5) >= 0 )
    {
      sub_4052D0();
      *(this + 60) = 1;
      *(this + 61) = 0;
      *(this + 62) = 0;
      sub_698F90((int)(this + 48), 600000, 0);
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
    off_77F3FC((char *)&byte_6C2D88, strlen(v3), v3);
    return 0x80000000;
  }
}



// ------------------------------------------------------------
// 0x41E600 sub_41E600
// ------------------------------------------------------------
int /*thiscall*/ sub_41E600(int *this)
{
  int v2; // esi
  int result; // eax
  int i; // edi

  v2 = *(this + 1);
  result = 0;
  if ( v2 != 0 )
  {
    for ( i = *(this + 2); v2 != i; v2 += 144 )
      sub_41CBF0(v2);
    j__free((void *)*(this + 1));
    result = 0;
  }
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 0;
  return result;
}



// ------------------------------------------------------------
// 0x41E650 sub_41E650
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
// 0x41E690 sub_41E690
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
// 0x41E6D0 sub_41E6D0
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
int ***/*thiscall*/ sub_41E720(uint32_t *this, int ***a2, int **a3)
{
  int **v3; // ebx
  int *v4; // edi
  int *v5; // ecx
  int *v6; // esi
  uint32_t *v7; // ecx
  int v8; // eax
  int *v9; // eax
  int v10; // ecx
  bool v11; // zf
  int v12; // eax
  int **v13; // eax
  char v14; // al
  uint32_t *v15; // ecx
  uint32_t *v16; // eax
  uint32_t *v17; // eax
  int v18; // eax
  void *v20; // [esp-4h] [ebp-64h]
  uint32_t pExceptionObject[10]; // [esp+4h] [ebp-5Ch] BYREF
  uint8_t v22[20]; // [esp+2Ch] [ebp-34h] BYREF
  int v23; // [esp+40h] [ebp-20h]
  int v24; // [esp+44h] [ebp-1Ch]
  int v25; // [esp+48h] [ebp-18h]
  void *Block; // [esp+4Ch] [ebp-14h]
  uint32_t *v27; // [esp+50h] [ebp-10h]
  int v28; // [esp+5Ch] [ebp-4h]

  v27 = this;
  if ( *((uint8_t *)a3 + 33) != 0 )
  {
    v24 = 15;
    v23 = 0;
    v22[4] = 0;
    sub_4015C0("invalid map/set<T> iterator", 0x1Bu);
    v28 = 0;
    sub_401740(pExceptionObject, (int)v22);
    pExceptionObject[0] = &std::out_of_range::`vftable';
    _CxxThrowException(pExceptionObject, (_ThrowInfo *)&_TI3_AVout_of_range_std__);
  }
  v3 = a3;
  Block = a3;
  sub_41C640(&a3);
  if ( *((uint8_t *)*v3 + 33) != 0 )
  {
    v4 = v3[2];
LABEL_8:
    v6 = v3[1];
    if ( *((uint8_t *)v4 + 33) == 0 )
      v4[1] = (int)v6;
    v7 = v27;
    v8 = v27[1];
    if ( *(int ***)(v8 + 4) == v3 )
    {
      *(uint32_t *)(v8 + 4) = v4;
    }
    else if ( (int **)*v6 == v3 )
    {
      *v6 = (int)v4;
    }
    else
    {
      v6[2] = (int)v4;
    }
    if ( *(int ***)v7[1] == v3 )
    {
      if ( *((uint8_t *)v4 + 33) != 0 )
      {
        v9 = v6;
      }
      else
      {
        v9 = (int *)sub_41C5C0(v4);
        v7 = v27;
      }
      *(uint32_t *)v7[1] = v9;
    }
    v10 = v7[1];
    v11 = *(uint32_t *)(v10 + 8) == (uint32_t)v3;
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
  if ( *((uint8_t *)v3[2] + 33) != 0 )
  {
    v4 = *v3;
    goto LABEL_8;
  }
  v5 = (int *)a3;
  v4 = a3[2];
  if ( a3 == v3 )
    goto LABEL_8;
  (*v3)[1] = (int)a3;
  *v5 = (int)*v3;
  if ( v5 == v3[2] )
  {
    v6 = v5;
  }
  else
  {
    v6 = (int *)v5[1];
    if ( *((uint8_t *)v4 + 33) == 0 )
      v4[1] = (int)v6;
    *v6 = (int)v4;
    v5[2] = (int)v3[2];
    v3[2][1] = (int)v5;
  }
  v12 = v27[1];
  if ( *(int ***)(v12 + 4) == v3 )
  {
    *(uint32_t *)(v12 + 4) = v5;
  }
  else
  {
    v13 = (int **)v3[1];
    if ( *v13 == (int *)v3 )
      *v13 = v5;
    else
      v13[2] = v5;
  }
  v5[1] = (int)v3[1];
  v14 = *((uint8_t *)v5 + 32);
  *((uint8_t *)v5 + 32) = *((uint8_t *)v3 + 32);
  *((uint8_t *)v3 + 32) = v14;
LABEL_35:
  if ( *((uint8_t *)Block + 32) == 1 )
  {
    v15 = v27;
    if ( v4 != *(int **)(v27[1] + 4) )
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
            v15 = v27;
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
            v15 = v27;
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
        v11 = v6 == *(int **)(v15[1] + 4);
        v6 = (int *)v6[1];
      }
      while ( !v11 );
    }
    *((uint8_t *)v4 + 32) = 1;
  }
  if ( *((uint32_t *)Block + 5) != 0 )
    j__free(*((void **)Block + 5));
  v17 = Block;
  v20 = Block;
  *((uint32_t *)Block + 5) = 0;
  v17[6] = 0;
  v17[7] = 0;
  j__free(v20);
  v18 = v27[2];
  if ( v18 != 0 )
    v27[2] = v18 - 1;
  *a2 = a3;
  return a2;
}


// ------------------------------------------------------------
// 0x41EA00 sub_41EA00
// ------------------------------------------------------------
char /*stdcall*/ sub_41EA00(void **Block)
{
  void **v1; // edi
  char result; // al
  void **i; // esi

  v1 = Block;
  result = *((uint8_t *)Block + 33);
  for ( i = Block; result == 0; v1 = i )
  {
    sub_41EA00(i[2]);
    i = (void **)*i;
    sub_4CEB50(v1);
    j__free(v1);
    result = *((uint8_t *)i + 33);
  }
  return result;
}



// ------------------------------------------------------------
// 0x41EA50 sub_41EA50
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_41EA50(uint8_t *this)
{
  char *v2; // edi
  int v3; // eax

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
  v2 = this + 68;
  v3 = sub_433AC0(this + 68);
  *((uint32_t *)v2 + 1) = v3;
  *(uint8_t *)(v3 + 21) = 1;
  *(uint32_t *)(*((uint32_t *)v2 + 1) + 4) = *((uint32_t *)v2 + 1);
  **((uint32_t **)v2 + 1) = *((uint32_t *)v2 + 1);
  *(uint32_t *)(*((uint32_t *)v2 + 1) + 8) = *((uint32_t *)v2 + 1);
  *((uint32_t *)v2 + 2) = 0;
  sub_4525D0(this);
  sub_452C50(this);
  return this;
}



// ------------------------------------------------------------
// 0x41EB00 sub_41EB00
// ------------------------------------------------------------
void */*thiscall*/ sub_41EB00(void *Block, char a2)
{
  sub_41EB30();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x41EB30 sub_41EB30
// ------------------------------------------------------------
int /*thiscall*/ sub_41EB30(int this)
{
  int *v3; // [esp-8h] [ebp-24h]
  int *v4; // [esp-4h] [ebp-20h]
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
// 0x41EBC0 sub_41EBC0
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
// 0x41ECB0 sub_41ECB0
// ------------------------------------------------------------
void */*thiscall*/ sub_41ECB0(void *Block, char a2)
{
  sub_41ECE0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x41ECE0 sub_41ECE0
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
// 0x41EDD0 sub_41EDD0
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_41EDD0(uint8_t *this)
{
  char *v2; // edi
  int v3; // eax

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
  v2 = this + 64;
  v3 = sub_433AC0(this + 64);
  *((uint32_t *)v2 + 1) = v3;
  *(uint8_t *)(v3 + 21) = 1;
  *(uint32_t *)(*((uint32_t *)v2 + 1) + 4) = *((uint32_t *)v2 + 1);
  **((uint32_t **)v2 + 1) = *((uint32_t *)v2 + 1);
  *(uint32_t *)(*((uint32_t *)v2 + 1) + 8) = *((uint32_t *)v2 + 1);
  *((uint32_t *)v2 + 2) = 0;
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
// 0x41EEF0 sub_41EEF0
// ------------------------------------------------------------
void */*thiscall*/ sub_41EEF0(void *Block, char a2)
{
  sub_41EF20();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x41EF20 sub_41EF20
// ------------------------------------------------------------
void /*thiscall*/ sub_41EF20(int this)
{
  int *v2; // [esp-8h] [ebp-28h]
  int *v3; // [esp-4h] [ebp-24h]
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
  v3 = *(int **)(this + 68);
  v2 = (int *)*v3;
  LOBYTE(v5) = 1;
  sub_41DA40((int ***)(this + 64), v4, v2, v3);
  j__free(*(void **)(this + 68));
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 72) = 0;
  *(uint8_t *)(this + 40) = 0;
  *(uint32_t *)(this + 36) = &nengine::IObject::`vftable';
  *(uint8_t *)(this + 4) = 0;
  *(uint32_t *)this = &nengine::IObject::`vftable';
}



// ------------------------------------------------------------
// 0x41EFF0 sub_41EFF0
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_41EFF0(uint8_t *this)
{
  char *v2; // edi
  int v3; // eax

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
  v2 = this + 76;
  v3 = sub_433AC0(this + 76);
  *((uint32_t *)v2 + 1) = v3;
  *(uint8_t *)(v3 + 21) = 1;
  *(uint32_t *)(*((uint32_t *)v2 + 1) + 4) = *((uint32_t *)v2 + 1);
  **((uint32_t **)v2 + 1) = *((uint32_t *)v2 + 1);
  *(uint32_t *)(*((uint32_t *)v2 + 1) + 8) = *((uint32_t *)v2 + 1);
  *((uint32_t *)v2 + 2) = 0;
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
// 0x41F0C0 sub_41F0C0
// ------------------------------------------------------------
void */*thiscall*/ sub_41F0C0(void *Block, char a2)
{
  sub_41F0F0();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x41F0F0 sub_41F0F0
// ------------------------------------------------------------
void /*thiscall*/ sub_41F0F0(int this)
{
  int *v2; // [esp-8h] [ebp-28h]
  int *v3; // [esp-4h] [ebp-24h]
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
// 0x41F190 sub_41F190
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
// 0x41F1F0 sub_41F1F0
// ------------------------------------------------------------
void */*thiscall*/ sub_41F1F0(void *Block, char a2)
{
  sub_41F220();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x41F220 sub_41F220
// ------------------------------------------------------------
void /*thiscall*/ sub_41F220(void *this)
{
  int v2; // eax

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
int sub_41F2C0()
{
  uint8_t *v0; // eax
  uint8_t *v1; // eax
  void *Block; // [esp+0h] [ebp-10h]

  v0 = operator new(0x30u);
  Block = v0;
  if ( v0 != nullptr )
    v1 = sub_41F190(v0);
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
// 0x41F690 sub_41F690
// ------------------------------------------------------------
int **/*thiscall*/ sub_41F690(int ***this, int **a2, int *a3, int *a4)
{
  int *v4; // ebx
  int *v5; // esi
  int v7; // eax
  uint32_t *v8; // eax
  int **v10; // ecx
  int **v11; // eax
  int *j; // eax
  int *i; // eax

  v4 = a4;
  v5 = a3;
  v7 = (int)*(this + 1);
  if ( a3 == *(int **)v7 && a4 == (int *)v7 )
  {
    sub_41EA00(*(void ***)(v7 + 4));
    (*(this + 1))[1] = (int *)*(this + 1);
    v8 = *(this + 1);
    *(this + 2) = nullptr;
    *v8 = v8;
    (*(this + 1))[2] = (int *)*(this + 1);
    *a2 = **(this + 1);
    return a2;
  }
  else
  {
    if ( a3 != a4 )
    {
      do
      {
        v10 = (int **)v5;
        if ( *((uint8_t *)v5 + 33) == 0 )
        {
          v11 = (int **)v5[2];
          if ( *((uint8_t *)v11 + 33) != 0 )
          {
            for ( i = (int *)v5[1]; *((uint8_t *)i + 33) == 0; i = (int *)i[1] )
            {
              if ( v5 != (int *)i[2] )
                break;
              v5 = i;
            }
            v5 = i;
          }
          else
          {
            v5 = (int *)v5[2];
            for ( j = *v11; *((uint8_t *)j + 33) == 0; j = (int *)*j )
              v5 = j;
          }
        }
        sub_41E720(this, (int ***)&a3, v10);
      }
      while ( v5 != v4 );
    }
    *a2 = v5;
    return a2;
  }
}



// ------------------------------------------------------------
// 0x41F750 sub_41F750
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
// 0x41F790 sub_41F790
// ------------------------------------------------------------
uint8_t */*thiscall*/ sub_41F790(uint8_t *this)
{
  char *v2; // edi
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax

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
  v2 = this + 52;
  v3 = sub_433AC0(this + 52);
  *((uint32_t *)v2 + 1) = v3;
  *(uint8_t *)(v3 + 21) = 1;
  *(uint32_t *)(*((uint32_t *)v2 + 1) + 4) = *((uint32_t *)v2 + 1);
  **((uint32_t **)v2 + 1) = *((uint32_t *)v2 + 1);
  *(uint32_t *)(*((uint32_t *)v2 + 1) + 8) = *((uint32_t *)v2 + 1);
  *((uint32_t *)v2 + 2) = 0;
  v4 = sub_433AC0(this + 64);
  *((uint32_t *)this + 17) = v4;
  *(uint8_t *)(v4 + 21) = 1;
  *(uint32_t *)(*((uint32_t *)this + 17) + 4) = *((uint32_t *)this + 17);
  **((uint32_t **)this + 17) = *((uint32_t *)this + 17);
  *(uint32_t *)(*((uint32_t *)this + 17) + 8) = *((uint32_t *)this + 17);
  *((uint32_t *)this + 18) = 0;
  v5 = sub_433B40(this + 76);
  *((uint32_t *)this + 20) = v5;
  *(uint8_t *)(v5 + 33) = 1;
  *(uint32_t *)(*((uint32_t *)this + 20) + 4) = *((uint32_t *)this + 20);
  **((uint32_t **)this + 20) = *((uint32_t *)this + 20);
  *(uint32_t *)(*((uint32_t *)this + 20) + 8) = *((uint32_t *)this + 20);
  *((uint32_t *)this + 21) = 0;
  v6 = sub_433AC0(this + 88);
  *((uint32_t *)this + 23) = v6;
  *(uint8_t *)(v6 + 21) = 1;
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
// 0x41F940 sub_41F940
// ------------------------------------------------------------
void */*thiscall*/ sub_41F940(void *Block, char a2)
{
  sub_41F970();
  if ( (a2 & 1) != 0 )
    j__free(Block);
  return Block;
}



// ------------------------------------------------------------
// 0x41F970 sub_41F970
// ------------------------------------------------------------
void /*thiscall*/ sub_41F970(int this)
{
  int *v2; // [esp-8h] [ebp-28h]
  int *v3; // [esp-8h] [ebp-28h]
  int *v4; // [esp-8h] [ebp-28h]
  int *v5; // [esp-8h] [ebp-28h]
  int *v6; // [esp-4h] [ebp-24h]
  int *v7; // [esp-4h] [ebp-24h]
  int *v8; // [esp-4h] [ebp-24h]
  int *v9; // [esp-4h] [ebp-24h]
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
  v6 = *(int **)(this + 92);
  v2 = (int *)*v6;
  LOBYTE(v11) = 4;
  sub_41D980((int ***)(this + 88), v10, v2, v6);
  j__free(*(void **)(this + 92));
  *(uint32_t *)(this + 92) = 0;
  *(uint32_t *)(this + 96) = 0;
  v7 = *(int **)(this + 80);
  v3 = (int *)*v7;
  LOBYTE(v11) = 3;
  sub_41F690((int ***)(this + 76), v10, v3, v7);
  j__free(*(void **)(this + 80));
  *(uint32_t *)(this + 80) = 0;
  *(uint32_t *)(this + 84) = 0;
  v8 = *(int **)(this + 68);
  v4 = (int *)*v8;
  LOBYTE(v11) = 2;
  sub_41DBC0((int ***)(this + 64), v10, v4, v8);
  j__free(*(void **)(this + 68));
  *(uint32_t *)(this + 68) = 0;
  *(uint32_t *)(this + 72) = 0;
  v9 = *(int **)(this + 56);
  v5 = (int *)*v9;
  LOBYTE(v11) = 1;
  sub_41DB00((int ***)(this + 52), v10, v5, v9);
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
  char *v2; // eax
  char *v3; // eax
  uint8_t *v4; // eax
  uint8_t *v5; // eax
  uint8_t *v6; // eax
  uint8_t *v7; // eax
  char *v8; // eax
  char *v9; // eax
  uint8_t *v10; // eax
  uint8_t *v11; // eax
  uint8_t *v12; // eax
  uint8_t *v13; // eax
  uint8_t *v14; // eax
  uint8_t *v15; // eax
  uint8_t *v16; // eax
  uint8_t *v17; // eax

  *(this + 4) = 0;
  *(this + 5) = 0;
  *(this + 6) = 0;
  *(this + 7) = 0;
  *(this + 8) = 0;
  *(this + 9) = 0;
  *(this + 10) = 0;
  *(this + 11) = 0;
  v2 = (char *)operator new(0x6D4u);
  if ( v2 != nullptr )
    v3 = sub_41DE30(v2);
  else
    v3 = nullptr;
  *(this + 9) = v3;
  v4 = operator new(0x118u);
  if ( v4 != nullptr )
    v5 = sub_41EBC0(v4);
  else
    v5 = nullptr;
  *(this + 4) = v5;
  v6 = operator new(0xDCu);
  if ( v6 != nullptr )
    v7 = sub_41F790(v6);
  else
    v7 = nullptr;
  *(this + 5) = v7;
  v8 = (char *)operator new(0x134u);
  if ( v8 != nullptr )
    v9 = sub_41E2A0(v8);
  else
    v9 = nullptr;
  *(this + 6) = v9;
  v10 = operator new(0x7Cu);
  if ( v10 != nullptr )
    v11 = sub_41C700(v10);
  else
    v11 = nullptr;
  *(this + 7) = v11;
  v12 = operator new(0x8Cu);
  if ( v12 != nullptr )
    v13 = sub_41EA50(v12);
  else
    v13 = nullptr;
  *(this + 8) = v13;
  v14 = operator new(0xC0u);
  if ( v14 != nullptr )
    v15 = sub_41EDD0(v14);
  else
    v15 = nullptr;
  *(this + 10) = v15;
  v16 = operator new(0x84u);
  if ( v16 != nullptr )
    v17 = sub_41EFF0(v16);
  else
    v17 = nullptr;
  *(this + 11) = v17;
  return 1;
}



// ------------------------------------------------------------
// 0x41FC50 sub_41FC50
// ------------------------------------------------------------
int sub_41FC50()
{
  void *v1; // eax
  int v2; // eax

  if ( dword_8F7B08 != 0 )
    return -2147483646;
  v1 = operator new(0x1D4u);
  if ( v1 == nullptr )
    return -2147483640;
  v2 = sub_4230A0(v1, v1);
  if ( v2 == 0 )
    return -2147483640;
  dword_8F7B08 = v2;
  return 1;
}



// ------------------------------------------------------------
// 0x41FCE0 sub_41FCE0
// ------------------------------------------------------------
int /*stdcall*/ sub_41FCE0(int a1)
{
  dword_9D3BC8 = a1;
  return a1;
}



// ------------------------------------------------------------
// 0x41FCF0 sub_41FCF0
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
// 0x41FD50 sub_41FD50
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
// 0x41FDC0 sub_41FDC0
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
// 0x41FE80 sub_41FE80
// ------------------------------------------------------------
unsigned int */*cdecl*/ sub_41FE80(unsigned int **a1, unsigned int **a2, unsigned int **a3)
{
  unsigned int **i; // esi
  unsigned int *result; // eax

  for ( i = a1; i != a2; ++i )
    result = sub_41B0D0(i, a3);
  return result;
}



// ------------------------------------------------------------
// 0x41FEB0 sub_41FEB0
// ------------------------------------------------------------
uint32_t */*cdecl*/ sub_41FEB0(uint32_t *a1, uint32_t *a2, uint32_t *a3)
{
  uint32_t *result; // eax

  for ( result = a1; result != a2; result += 2 )
  {
    *result = *a3;
    result[1] = a3[1];
  }
  return result;
}



// ------------------------------------------------------------
// 0x41FEE0 sub_41FEE0
// ------------------------------------------------------------
unsigned int **/*cdecl*/ sub_41FEE0(unsigned int **a1, unsigned int **a2, unsigned int **a3)
{
  unsigned int **v3; // esi
  unsigned int **v4; // edi

  v3 = a2;
  if ( a1 == a2 )
    return a3;
  v4 = a3;
  do
    sub_41B0D0(--v4, --v3);
  while ( v3 != a1 );
  return v4;
}



// ------------------------------------------------------------
// 0x41FF20 sub_41FF20
// ------------------------------------------------------------
unsigned int **/*cdecl*/ sub_41FF20(unsigned int **a1, unsigned int **a2, unsigned int **a3)
{
  return sub_41FEE0(a1, a2, a3);
}



// ------------------------------------------------------------
// 0x41FF40 sub_41FF40
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
// 0x41FFE0 sub_41FFE0
// ------------------------------------------------------------
unsigned int */*cdecl*/ sub_41FFE0(unsigned int **a1, int a2, unsigned int **a3)
{
  unsigned int **v3; // esi
  unsigned int *result; // eax
  uint32_t v6[5]; // [esp+0h] [ebp-20h] BYREF
  int v7; // [esp+1Ch] [ebp-4h]

  v3 = a1;
  v6[4] = v6;
  v6[3] = a1;
  v7 = 0;
  while ( a2 != 0 )
  {
    LOBYTE(v7) = 1;
    if ( v3 != nullptr )
    {
      *v3 = nullptr;
      result = sub_41B0D0(v3, a3);
    }
    --a2;
    ++v3;
    LOBYTE(v7) = 0;
  }
  return result;
}

