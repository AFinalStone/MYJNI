## NDK学习笔记<七> 使用AndroidStudio本身，编译C/C++文件生成SO文件

之前的项目我们基本都是使用Ndk-build的命令行来编译C/C++文件生成.so库文件的。本篇我们使用AndroidStudio的RebuildProject来编译C/C++文件，生成我们需要的.so库文件。

### 一、给已经存在的项目配置AndroidStudio开发NDK的环境

#### 1、在我们的项目中的app中的build.gradle中添加

defaultConfig｛｝后面添加：

```gradle
  externalNativeBuild {
      cmake {
          cppFlags "-std=c++11"
      }
  }
```

或者：

```gradle
  externalNativeBuild {
      cmake {
          cppFlags ""
      }
  }
```

cmake在编译C/C++代码的时候，回根据上面的两种不同设置来使用C++的两种不同标准，C++11或者默认标准

android {｝后面添加：

```gradle
    externalNativeBuild {
        cmake {
            path "CMakeLists.txt"
        }
    }
```

指定cmake的具体路径为当前项目的根路径,名字为CMakeLists.txt。


整个build.gradle的内容如下：

```gradle

apply plugin: 'com.android.application'

android {
    compileSdkVersion 25
    buildToolsVersion "25.0.1"

    defaultConfig {
        applicationId "com.afinalstone.administrator.ndk_07_buildbyas"
        minSdkVersion 16
        targetSdkVersion 25
        versionCode 1
        versionName "1.0"
        testInstrumentationRunner "android.support.test.runner.AndroidJUnitRunner"
        externalNativeBuild {
            cmake {
                cppFlags "-std=c++11"
            }
        }
    }
    buildTypes {
        release {
            minifyEnabled false
            proguardFiles getDefaultProguardFile('proguard-android.txt'), 'proguard-rules.pro'
        }
    }
    externalNativeBuild {
        cmake {
            path "CMakeLists.txt"
        }
    }
}

dependencies {
    compile fileTree(dir: 'libs', include: ['*.jar'])
    androidTestCompile('com.android.support.test.espresso:espresso-core:2.2.2', {
        exclude group: 'com.android.support', module: 'support-annotations'
    })
    compile 'com.android.support:appcompat-v7:25.+'
    compile 'com.android.support.constraint:constraint-layout:1.0.2'
    testCompile 'junit:junit:4.12'
}

```

2、在我们的项目中的app根目录添加CMakeLists.txt文件，具体内容如下：

```
# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html
# 需要查阅更多关于AndroidStudio中CMake的更多相关信息，可以查阅文档：https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.
#设置CMake编译本地代码生成库文件需要的最低版本号

cmake_minimum_required(VERSION 3.4.1)

add_library( # Sets the name of the library.
             # 设置library的名称，我们加载库文件的时候要和这个保持一致
             native-lib

             # Sets the library as a shared library. 
             #设置libray作为一个共享libary
             SHARED 

             # Provides a relative path to your source file(s). 
             # 提供出我们代码文件的相对路径,如果有多个代码文件，可以依次在这里添加多个
             src/main/cpp/native-lib.cpp )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.
#搜寻指定的预构建库，并将路径存储在一个变量中；因为CMake默认已经包含了系统依赖库的路径，
#我们仅仅需要添加我们想要添加的特定的NDK库文件，CMake在完成编译代码之前会去核实我们添加的library是否真的存在。



find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.
#指定那些在我们生成目标library的过程需要的其他libary，我们可以链接多个librayr
#例如你提前定义的或者其他第三方预加载的library，或者系统library。


target_link_libraries( # Specifies the target library.
                       # 指定目标library，假如有多个library,我们都需要在这里添加
                       native-lib

                       # Links the target library to the log library
                       # included in the NDK.
                       # 将目标library链接到日志库中
                       ${log-lib} )
```

关于CMake的具体使用，这里再列举另外一个项目中CMakeLists.txt的具体内容：

```
cmake_minimum_required(VERSION 3.4.1)

#FFMpeg配置
#FFmpeg配置目录
set(SO_DIR src/main/jniLibs)
set(CPP_DIR src/main/cpp)

# 编解码(最重要的库)
add_library(
            avcodec
            SHARED
            IMPORTED)
set_target_properties(
            avcodec
            PROPERTIES IMPORTED_LOCATION
            ${CMAKE_SOURCE_DIR}/${SO_DIR}/${ANDROID_ABI}/libavcodec-57.so
            )

# 滤镜特效处理库
add_library( 
            avfilter 
            SHARED
            IMPORTED)
set_target_properties(
            avfilter
            PROPERTIES IMPORTED_LOCATION
             ${CMAKE_SOURCE_DIR}/${SO_DIR}/${ANDROID_ABI}/libavfilter-6.so)

# 封装格式处理库
add_library(
            avformat
            SHARED
            IMPORTED)
set_target_properties(
            avformat
            PROPERTIES IMPORTED_LOCATION
            ${CMAKE_SOURCE_DIR}/${SO_DIR}/${ANDROID_ABI}/libavformat-57.so)

# 工具库(大部分库都需要这个库的支持)
add_library(
            avutil
            SHARED
            IMPORTED)
set_target_properties(
            avutil
            PROPERTIES IMPORTED_LOCATION
            ${CMAKE_SOURCE_DIR}/${SO_DIR}/${ANDROID_ABI}/libavutil-55.so)

# 音频采样数据格式转换库
add_library(
            swresample
            SHARED
            IMPORTED)
set_target_properties(
            swresample
            PROPERTIES IMPORTED_LOCATION
            ${CMAKE_SOURCE_DIR}/${SO_DIR}/${ANDROID_ABI}/libswresample-2.so)

# 视频像素数据格式转换
add_library(
            swscale
            SHARED
            IMPORTED)
set_target_properties(
            swscale
            PROPERTIES IMPORTED_LOCATION
            ${CMAKE_SOURCE_DIR}/${SO_DIR}/${ANDROID_ABI}/libswscale-4.so)


#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
#判断编译器类型,如果是gcc编译器,则在编译选项中加入c++11支持
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
    message(STATUS "optional:-std=c++11")
endif(CMAKE_COMPILER_IS_GNUCXX)

#配置编译的头文件
include_directories(src/main/jniLibs/include)

add_library(
             native-lib

             SHARED

             ${CPP_DIR}/com_xy_ndk_ffmpeg_NDKFFmpeg.cpp )

find_library(
              log-lib

              log )

target_link_libraries(
                       native-lib  avcodec avfilter avformat avutil swresample swscale

                       ${log-lib} )

```


再推荐几篇关于Cmake的使用和语法的文章：

[cmake使用示例与整理总结](http://blog.csdn.net/wzzfeitian/article/details/40963457)

[CMakeList配置之编译多个.cpp文件](http://blog.csdn.net/u011028777/article/details/53424927)

[AndroidStudio2.2下利用CMake编译方式的NDK opencv开发](http://blog.csdn.net/ddjjll8877/article/details/52670097?)

#### 2、到这里查看一下我们的整个项目结构：

![结构](picture/结构.png)

### 二、新建自带AndroidStudio开发NDK环境的项目

New Project之后，需要注意下面两个页面：


![勾选项目包含C++](picture/步骤一.png)

![选择C++标准](picture/步骤二.png)

### 三、编译生成.so库文件

点击Build->Rebuild Project，重新编译整个项目包括.so库文件。

![结构](picture/so库文件.png)

这样我们打包生成的app里面就自动包含我们需要的.so库文件。

### 四、NDK需要注意的方面：

- 关于NDK部分文件的后缀名：

1>使用C++来写代码，文件名就必须以.cpp为后缀，.c后缀不行；

2>使用C来写代码，文件名就必须以.c为后缀；

- 关于代码的调用：

1>C格式
```
return (*env)->NewStringUTF(env, "Hello JNI !");
```
2>C++格式
```
 return env->NewStringUTF((char *)"Hello JNI !");
```


参考文章：http://blog.csdn.net/krubo1/article/details/50547681

JNI错误总结：http://www.cnblogs.com/xingyun/archive/2012/08/03/2622410.html

C和C++代码的区别：http://blog.csdn.net/forandever/article/details/50396058

Javap的使用：http://www.365mini.com/page/javap-disassemble-class-file-code.htm


项目地址：[传送门](https://github.com/AFinalStone/MYJNI)