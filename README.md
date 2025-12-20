# Calculator (Qt 5.15.2)

这是一个基于 Qt 5.15.2 的简单计算器示例工程，使用 `qmake` 构建，目标可执行文件名为 `Calculator`。

功能:
- 支持加、减、乘、除
- 小数点支持
- 清空（C）
- 等号计算（=）
- 退出按钮（Exit）

文件:
- `Calculator.pro`：qmake 工程文件
- `main.cpp`：程序入口
- `mainwindow.h/.cpp`：主窗口与逻辑实现

快速构建（本机）：
```powershell
qmake Calculator.pro
mingw32-make # or make on Linux
```

交叉编译到 aarch64（示例说明）:

1) 推荐做法：使用你为 aarch64 编译的 Qt 5.15.2 的 qmake（如果你有预构建的交叉 Qt）：

```powershell
/opt/qt5.15.2-aarch64/bin/qmake -spec linux-aarch64-g++ Calculator.pro
make -j
```

2) 如果只想强制使用交叉工具链（取决于你的 Qt 构建与工具链），可以传入环境变量：

```powershell
/path/to/host/qt/bin/qmake "QMAKE_CC=/usr/bin/aarch64-linux-gnu-gcc" "QMAKE_CXX=/usr/bin/aarch64-linux-gnu-g++" Calculator.pro
make -j
```

注意:
- 交叉编译需要你有针对 aarch64 的 Qt 库（即 Qt 是为目标平台构建的），仅替换编译器通常不足以生成可在目标上运行的二进制。
- 上面的命令根据目标系统与交叉工具链路径需要调整。