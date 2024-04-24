# QT_Linux_OCC
## 一、环境
### QT Linux（Ubuntu）
下载QT安装包 并安装
https://download.qt.io/archive/qt/5.12/5.12.12/qt-opensource-linux-x64-5.12.12.run

安装时选择 Desktop gcc 64-bit即可  

配置GCC的环境  
```
sudo apt-get install build-essential

sudo apt-get install libdrm-dev libxxf86vm-dev libxt-dev xutils-dev flex bison xcb libx11-xcb-dev libxcb-glx0 libxcb-glx0-dev xorg-dev libxcb-dri2-0-dev

sudo apt install cmake
```
或者安装GUI的Cmake
```
sudo apt install cmake-gui
```
PS：如果你打不开QtCreator，手动安装一下Qt5环境（也不知道怎么回事，这厮利用不上自己安装包的Qt5 ？？？？）
```
sudo apt install qt5-default
```
.   
.  

### OpenCASCADE
下载  
https://codeload.github.com/Open-Cascade-SAS/OCCT/zip/refs/tags/V7_8_0  

编译
```
cd [OCC源码路径]
mkdir build
cd build
cmake -G "Unix Makefiles" .. -DBUILD_MODULE_Draw=OFF -DUSE_FREETYPE=OFF -DCMAKE_INSTALL_PREFIX=../install
make -j8
make install
```
PS：如果需要FreeType请编译并配置FreeType，建议安装CMAKE-GUI进行配置（不会命令的boy），此外我们不需要Draw程序，如果需要自行编译并配置tcl/tk

.   
.   

## 二、拉取并配置项目
