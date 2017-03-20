## NDK学习笔记<四> 使用javah生成头文件

>上篇文章中，我们C文件代码中的函数名是手动书写的，这次我们来尝试使用javah生成我们需要的函数名

##### 一、我们新建一个普通的安卓项目，这里我取名为ndk01，添加MainActivity

```java

package com.shi.androidstudy.ndk01;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }
    public native String useJavah();

    static {
        // 导入动态库
        System.loadLibrary("javah");
    }
}

```

##### 二、打开当前包名的根目录，按住shift键，点击鼠标右键，打开命令行，
##### 输入javah com.shi.androidstudy.ndk01.MainActivity，
##### 会在当前目录下面生成一个com_shi_androidstudy_ndk01_MainActivity.h的文件

![使用javah生成](/screen/ndk01_01.gif)

##### 三、在当前项目中添加jni文件夹，在文件夹下面添加javah.c文件，并
##### 把com_shi_androidstudy_ndk01_MainActivity.h文件中的函数名称复制粘贴进去
```c
#include <jni.h>

JNIEXPORT jstring JNICALL Java_com_shi_androidstudy_ndk01_MainActivity_useJavah
  (JNIEnv * env, jobject obj){
  	char* pc = "use javah make .h文件";
  	jstring str = (**env).NewStringUTF(env, pc);
  	return str;
  }

```
##### 继续在jin文件中添加Android.mk
```mk

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := javah
LOCAL_SRC_FILES := javah.c

include $(BUILD_SHARED_LIBRARY)

```

##### 继续在jin文件中添加Application.mk
```mk

APP_ABI := all

```

![添加jni文件夹](/screen/ndk01_02.png)

##### 四、继续在jni文件夹中打开命令行窗口，ndk-build 生成.so文件，修改gradle文件(不修改项目无法找到库文件)
##### ，然后成功运行项目

![运行项目](/screen/ndk01_03.gif)












