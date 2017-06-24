### NDK学习笔记<一> 初步认识JNI|成功搭建NDK开发环境|成功运行一个包含NDK的简单Android程序
- **什么是JNI**

JNI，英文全名为：Java Native Interface
JNI就是java调用本地方法的技术，最简单的来说，java运行一个程序需要要和不同的系统平台打交道，在windows里就是和
windows平台底层打交道，mac就是要和mac打交道，jvm就是通过大量的jni技术使得java能够在不同平台上运行。而使用了
这技术的一个标志就是native,如果一个类里的一个方法被native修饰，那就说明这个方法是jni来实现的，他是通过本地系统
api里的方法来实现的。当然这个本地方法可能是C或者C++，当然也可能是别的语言。jni是java跨平台的基础，jvm通过
在不同系统上调用不同的本地方法使得jvm可以在不同平台间移植。
当前你自己也可以用jni来写一些程序，这种基本上是你以前使用了其他语言完成了一些功能，但是你有要用java来重复这些功能
的时候，就可以使用jni来完成了。不过带来的问题就是，如果你的那个本地方法是依托于本地操作系统的话，那就意味着你的
java程序也只能在这一个系统上运行了。所以jni就使得java很容易限定在了一个系统平台上，而jdk的作用在于他提供一个规
范，这个规范就是包含了很多native方法，这些方法都是要本地操作系统来实现的，
而实现了这些本地方法的操作系统就可以移植java平台了。

- **java和C语言的异同**

**Java属于解释型语言, 跨平台, 编译运行效率相对较低，高级语言**

**C语言属于编译型语言, 本地语言, 无法跨平台，性能卓越，低级语言**

**上面的高级和低级没有优差之分，只是说明了语言和底层机器的距离**

- **JNI的用途**


**1.市场上面，大多高级工程师，都要求会使用**

**2.效率优先的场合, 需要用到C语言**

**3.C语言有一些优秀的类库, 在做程序的时候需要用到(WebKit, FFMPEG)**

**4.操作硬件一般使用C语言, 需要使用Java调用C来控制硬件**

**5.安全性优先, 保密性优先的场合, 需要用到C语言, 因为C语言是几乎无法编译的**

- **如何学习JNI**

**1.首先要懂的Java代码**
**2.然后还要懂得C语言,C++语言**
**3.熟悉JNI接口规范，要懂得查看<jni.h>文件**

### <二> 成功搭建NDK开发环境

#### 工欲善其事必先利其器，进行NDK开发的第一步，当然是NDK的开发环境搭建了，这里简单讲述一下个人搭建过程

#### 一、在AndroidStudio中依次点击Tools->Android->SDK Manager

 ![图一](http://img.blog.csdn.net/20170321100222067?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvYWJjNjM2ODc2NQ==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

#### 二、在Android SDK中点击SDK Tools，然后勾选LLDB和NDK选项，然后OK确认，进行NDK Build的下载

 ![图二](http://img.blog.csdn.net/20170321100306874?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvYWJjNjM2ODc2NQ==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

#### 三、成功更新下载NDK Build之后，我们要进行NDK环境变量的配置，右键计算机->属性->高级系统设置->环境变量->Path ，
  双击Path进行编辑，我的NDK Build是下载到了D:\Android_Studio\SDK\ndk-bundle文件夹下面，所以我在Path的后面
  添加 **;D:\Android_Studio\SDK\ndk-bundle**

  ![图三](http://img.blog.csdn.net/20170321100504296?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvYWJjNjM2ODc2NQ==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

#### 四、配置完成之后，我们在运行窗口中输入cmd，打开命令行窗口，输入ndk-build -version，看到如图所示内容，说明配置成功

  ![图四](http://img.blog.csdn.net/20170321101340112?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvYWJjNjM2ODc2NQ==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

### <三> 成功运行一个包含NDK的简单Android程序

#### 一、我们新建一个普通的Android项目，这里我取名为MYJNI，接着编写MainActivity.java的具体代码

```java

package com.shi.androidstudy.ndk;

import android.os.SystemClock;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        new Thread(new Runnable() {
            @Override
            public void run() {
                SystemClock.sleep(2000);
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        Toast.makeText(MainActivity.this,sayHello(),Toast.LENGTH_LONG).show();
                    }
                });
            }
        }).start();
    }

    public native String sayHello();

    static {
        // 导入动态库
        System.loadLibrary("hello");
    }
}


```


#### 二、然后我们在app目录下面添加**jni文件夹**，并在里面添加三个文件：

![图五](http://img.blog.csdn.net/20170321101914247?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvYWJjNjM2ODc2NQ==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

* hello.c

下面是具体的C语言代码

```c
#include <jni.h>

/*
 * 对应的native方法, 需要一个string的返回值
 * jstring 对应Java中的String
 * Java_com_shi_androidstudy_myjni_MainActivity_sayHello 方法名
 * Java_包名(.改成_)_类名_方法名
 *
 * JNIEnv* Java当前虚拟机运行环境
 * jobject 当前调用这个函数的Java对象
 */
jstring Java_com_shi_androidstudy_ndk_MainActivity_sayHello(JNIEnv* env, jobject obj) {
	char* pc = "Hello from c";
	// jstring返回值  (*NewStringUTF)(JNIEnv*  java虚拟机运行环境, const char* C语言中的字符串);
	jstring str = (**env).NewStringUTF(env, pc);
	return str;
}


```


* Android.mk

这个文件主要是为了告诉ndk-build我们想要生成的库文件名和需要编译的C或者C++文件名，在这里我想要编辑的C文件名
             叫做hello.c，我想要使用的库文件名叫做hello
```mk

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := hello
LOCAL_SRC_FILES := hello.c

include $(BUILD_SHARED_LIBRARY)

```


* Application.mk

这个文件主要是为了告诉ndk-build我们想要生成适用于那些CPU指令集的库文件，=all就是编译生成所有CPU指令集的库文件

```mk

APP_ABI := all

```


#### 三、接着我们选中hello.c文件，右键Show in explorer，进入上面三个文件所在的文件夹，按住shift按键，然后右键点击在此处打开命令窗口

![图六](http://img.blog.csdn.net/20170321102650648?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvYWJjNjM2ODc2NQ==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

#### 四、我们在命令行窗口中输入ndk-build，点击回车

![图七](http://img.blog.csdn.net/20170321102722760?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvYWJjNjM2ODc2NQ==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

![图八](http://img.blog.csdn.net/20170321102928026?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvYWJjNjM2ODc2NQ==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

#### 五、修改build.gradle

我们需要修改build.gradle文件，否次运行程序，会提示findLibrary returned null之类的错误信息

```gridle

android {
    sourceSets {
        main {
        jniLibs.srcDirs = ['libs']
        jni.srcDirs = []
        }
}
```

#### 六、成功运行项目

![图九](http://img.blog.csdn.net/20170321104040111?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvYWJjNjM2ODc2NQ==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)


#### 这里我们说一下NDK开发Android应用的步骤
1. 定义native方法
2. 创建jni(名字一定是jni)文件夹
3. 创建C代码文件
4. 创建C函数
	* 返回值和传入参数类型需要用到Java对应的C类型(主要参考jni.h文件的具体内容)
	* 函数名Java_包名(.改成_)_类名_native方法名
	* 默认传入两个参数 JNIEnv* env(jvm运行环境), jobject obj(调用这个函数的Java对象)
5. 编译
	* ndk-build命令来编译
	* Android.mk文件来指定编译谁
6. 加载动态库
	* 需要在static代码块中加载
	* System.loadLibrary
	* 加载时候的名字: 库文件去掉.so, 去掉前面的lib
7. 可以开始使用native方法了, 这个时候native方法已经和so文件对应了

#### NDK开发中常见错误
* 加载动态库出错
    java.lang.UnsatisfiedLinkError: Couldn't load hello123 from loader dalvik.system.PathClassLoader
    [dexPath=/data/app/apk名称,libraryPath=/data/app-lib/apk名称]: findLibrary returned null
    解决之道:
    1、写对库文件名字
    2、加载时候的名字: 库文件去掉.so, 去掉前面的lib
    3、按照文章的第五步修改gradle文件

* C函数名写错
    java.lang.UnsatisfiedLinkError: Native method not found:
    com.shi.androidstudy.myjni.MainActivity.sayHello:()Ljava/lang/String;
	解决之道:
	函数名Java_包名(.改成_)_类名_native方法名

* 在不支持的平台上运行(无法安装的问题)
	Installation error: INSTALL_FAILED_CPU_ABI_INCOMPATIBLE
	解决之道:
    1. 新建Application.mk文件(jni目录)
    2. APP_ABI := all

