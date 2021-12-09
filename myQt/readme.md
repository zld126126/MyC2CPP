# myQt
- [myQt](#myqt)
  - [参考资料](#参考资料)
  - [安装Qt](#安装qt)
  - [创建项目](#创建项目)
  - [打开项目](#打开项目)
  - [编译&&打包 exe](#编译打包-exe)
  - [运行](#运行)

## 参考资料
    http://c.biancheng.net/view/1817.html

## 安装Qt
    下载:https://download.qt.io/archive/qt/5.9/5.9.9/
    见 QT安装.gif

## 创建项目
    见 编写第一个QT程序.docx

## 打开项目
    qt-creator 打开项目选择 CMakeLists.txt 即可打开

## 编译&&打包 exe
    Qt Creator 以 release 模式生成可执行文件
    备注:此时的 XXX.exe 是无法运行的，双击它系统会提示类似“找不到 xxx.dll”的错误信息。

    开始菜单找到: Qt 5.9.9 (MinGW 5.3.0 32-bit)
    运行 并在命令行执行:
        windeployqt XXX.exe

## 运行
    确认执行命令:
        windeployqt myQt.exe
    app/myQt.exe 可直接运行