## NDK学习笔记<三> 成功运行一个包含NDK的简单Android程序

##### 一、我们新建一个普通的Android项目，这里我取名为MYJNI，接着编写MainActivity.java的具体代码

```java

package com.shi.androidstudy.myjni;

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

    //定义JNI方法名，使得java代码可以调用C代码
    public native String sayHello();

    static {
        // 虚拟机加载类的第一步，首先要导入动态库，这里我生成的链接库名称叫做hello，
        // 也就是libhello.so去掉前面的lib和后面的.so字段
        System.loadLibrary("hello");
    }
}

```


##### 二、然后我们在app目录下面添加**jni文件夹**，并在里面添加三个文件：

![图五](/screen/S2_05.png);

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
jstring Java_com_shi_androidstudy_myjni_MainActivity_sayHello(JNIEnv* env, jobject obj) {
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


##### 三、接着我们选中hello.c文件，右键Show in explorer，进入上面三个文件所在的文件夹，按住shift按键，然后右键点击在此处打开命令窗口

![图六](/screen/S2_06.png)

##### 四、我们在命令行窗口中输入ndk-build，点击回车

![图七](/screen/S2_07.png)

![图八](/screen/GIF.gif)

##### 五、修改build.gradle

我们需要修改build.gradle文件，否次运行程序，会提示findLibrary returned null之类的错误信息

```gridle

android {
    sourceSets {
        main {
            jniLibs.srcDirs = ['libs']
        }
}
```

##### 六、成功运行项目

![图九](/screen/SUCCESS.gif)















