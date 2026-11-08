# 1031 UI 渲染源码与证据交接包

主规范：[1031-UI层跨项目复刻规范](ui_lab_1031/docs/1031-UI层跨项目复刻规范.md)。
全部322 UI、36配置、物理资源候选和逐控件支持表在 `ui_lab_1031/handoff/`。
**不是所有UI完整复刻的完成证明**；所有窗口均保留缺项。原生已证规则、资源解码与Qt候选明确区分。

## 离线运行

Windows x64 / Python 3.11+。持有固定版客户端；ZIP不重复分发客户端、完整内存快照或采集日志。

```powershell
python -m pip install -r requirements.txt
python ui_lab_1031/tools/render_reference.py list
python ui_lab_1031/tools/render_reference.py render --client "D:/你的客户端目录" --ui ui/boosterselect/boosterselectpass.ui --out output/select
python ui_lab_1031/tools/render_reference.py render --client "D:/你的客户端目录" --config ui/pvp/channel/channelbutton.cbt --group 1 --highlight --out output/cbt
python ui_lab_1031/tools/render_reference.py bundle --input output/select --out output/reopened
```

输出PNG、version1离线包、物理来源/诊断；不是原生截图。`--client`只读取，不运行DNF.exe。
`manifest.json`对所有交付文件保存SHA256及原文件SHA256；不包括自身哈希，ZIP外层SHA在交付验证报告。
只有npk-index归档路径和assets.py的decoder源码查找有路径适配，manifest记录变换，不改资源/绘制算法。
`src/observer.cpp`只供审阅来源，不参与离线执行；未包含observer DLL和部署入口。
历史证据可能引用未打包的大归档/快照或旧绝对路径；这些引用保留历史身份，不是运行依赖。

## 重建独立helper（可选）

已有Windows x64二进制可直接使用；要重建使用与静态zlib库ABI兼容的LLVM-MinGW x64工具链：

```powershell
python ui_lab_1031/tools/build_render_helper.py --compiler "<toolchain>/bin/x86_64-w64-mingw32-clang++.exe"
```

重建后helper哈希改变是正常现象；需重验对应资源样本，不将旧manifest当新二进制证明。
第三方头文件保持原有许可声明，未另造版权或许可。
