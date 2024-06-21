# iCVIPLib
 对基于OpenCV实现的方法进行安全封装，同时也兼容原生的OpenCV直接调用。
 
## 源码地址
- [https://git-in.iflytek.com/RS_RDG_AI_Group/cv3/engine/wensha2/iCVIPLib.git](https://git-in.iflytek.com/RS_RDG_AI_Group/cv3/engine/wensha2/iCVIPLib.git)
## 源码下载
- git clone https://git-in.iflytek.com/RS_RDG_AI_Group/cv3/engine/wensha2/iCVIPLib.git

## 功能简介
1. 采用标准化接口设计，使用简单、方便，需要支持C++11，跨平台，目前支持x86_64_linux、android v7a&v8a、qnx700、vs2015&vs2019
2. 基于OpenCV的安全封装，为了是引擎调用部分不要有过多的异常判断代码，所以对OpenCV的接口进行了封装，方便引擎调用。

## 项目结构
├── CMakeLists.txt
├── README.md
├── assets
│   └── images
│       └── qfliu.jpg
├── build_scripts
│   ├── aarch64_qnx
│   │   └── build_700.sh
│   ├── android
│   │   ├── build_armv7a.sh
│   │   └── build_armv8a.sh
│   ├── windows
│   │   ├── build_vs2015.bat
│   │   └── build_vs2019.bat
│   └── x86_64_linux
│       └── build.sh
├── cmake
│   ├── aarch64_linux.toolchain.cmake
│   ├── aarch64_qnx700.toolchain.cmake
│   ├── aarch64_qnx710.toolchain.cmake
│   ├── arm_linux.toolchain.cmake
│   ├── func.cmake
│   ├── ios.toolchain.cmake
│   ├── platform.cmake
│   └── x86_64_linux.toolchain.cmake
├── source
│   ├── iCVIPLibApi
│   │   ├── CMakeLists.txt
│   │   ├── iCVIPLibApi.h
│   │   ├── iCVIPLib_config.h.in
│   │   ├── iCVSafeOpenCVBase.cpp
│   │   ├── iCVSafeOpenCVBase.h
│   │   └── iCVSafeOpenCVReal.hpp
│   ├── iCVIPLibTest
│   │   ├── CMakeLists.txt
│   │   └── iCVIPLibTest.cpp
│   ├── include
│   │   ├── core
│   │   ├── opencv2
│   │   └── utils
│   └── submodules
│       └── Opencv4.9.0
└── version.txt

## 开发维护人员
沙文(shawen@mail.ustc.edu.cn)

## 修复记录
| Date | Description | Author |
| ---- | ----------- | ------ |
| 06/21/2024 10:00 | 设置基线 | Chauvin |
