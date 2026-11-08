# dnf-nut-script

`dnf-nut-script` 是一个使用 Squirrel 编写的脚本项目，专用于 dnf pvf nut 脚本。

## 项目简介

本项目包含了一系列用于 dnf pvf nut 的实用脚本，旨在帮助用户更高效地进行相关操作。

## 目录结构与功能描述

- `sqr/ui/ui.nut`:
  - 定义了绘制新风格的连击UI的函数，包括绘制连击数字、技能冷却时间、怪物血量等各类UI效果。

- `sqr/apjh/lue.nut`:
  - 包含多个脚本的调用，用于技能冷却时间、地图加载、自定义UI绘制、鼠标点击等功能的实现。

- `sqr/map/monstericon/7.ani`:
  - 动画文件，定义了怪物图标的帧数、图像位置和延迟时间。

- `sqr/map/anton.nut`:
  - 定义了与Anton地图相关的处理逻辑，包括加载和移除地图附加组件。

- `sqr/map/monstericon/6.ani`:
  - 动画文件，定义了怪物图标的帧数、图像位置和延迟时间。

- `sqr/map/monstericon/8.ani`:
  - 动画文件，定义了怪物图标的帧数、图像位置和延迟时间。

- `sqr/map/ap_enemy.nut`:
  - 定义了敌人相关的处理函数，包括HP处理、伤害应用等。

- `sqr/common_class.nut`:
  - 定义了 `NewDamageFontObject` 类及其相关方法，用于处理新伤害字体对象的基本变量、绘制和位置设置等。

- `sqr/map/monstericon/16.ani`:
  - 动画文件，定义了怪物图标的帧数、图像位置和延迟时间。

- `sqr/map/monstericon/13.ani`:
  - 动画文件，定义了怪物图标的帧数、图像位置和延迟时间。

## 安装与使用

1. 克隆仓库到本地：
    ```sh
    git clone https://github.com/heihuo000/dnf-nut-script.git
    ```
2. 进入项目目录：
    ```sh
    cd dnf-nut-script
    ```
3. 按照文档中的说明进行配置和运行脚本。

## 贡献指南

欢迎大家为本项目贡献代码！请遵循以下步骤：

1. Fork 本仓库。
2. 创建一个新的分支：
    ```sh
    git checkout -b feature/your-feature
    ```
3. 提交你的修改：
    ```sh
    git commit -am 'Add some feature'
    ```
4. 推送到你的分支：
    ```sh
    git push origin feature/your-feature
    ```
5. 创建一个 Pull Request。

## 许可证

本项目使用 MIT 许可证。详细信息请参阅 [LICENSE](./LICENSE) 文件。

## 联系方式

如果你有任何问题或建议，请通过 [issue](https://github.com/heihuo000/dnf-nut-script/issues) 提交，或者发送邮件至 [your-email@example.com]。
