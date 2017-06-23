>上篇文章中，我们C文件代码中的函数名是手动书写的，这次我们来尝试使用javah生成我们需要的函数名

#### 一、我们新建一个普通的安卓项目，这里我取名为ndk_02，添加MainActivity

```java

package com.shi.androidstudy.ndk;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    String str;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void onClick(View view){
        Toast.makeText(this, useJavah(), Toast.LENGTH_SHORT).show();
    }

    public native String useJavah();

    static {
        // 导入动态库
        System.loadLibrary("javah");
    }
}


```

#### 二、打开当前包名的根目录，按住shift键，点击鼠标右键，打开命令行，
#### 输入javah com.shi.androidstudy.ndk.MainActivity，
#### 会在当前目录下面生成一个com_shi_androidstudy_ndk_MainActivity.h的文件

![使用javah生成](http://img.blog.csdn.net/20170321114958687?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvYWJjNjM2ODc2NQ==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

#### 三、在当前项目中添加jni文件夹，在文件夹下面添加javah.c文件，并
#### 把com_shi_androidstudy_ndk01_MainActivity.h文件中的函数名称复制粘贴进去
```c
#include <jni.h>

JNIEXPORT jstring JNICALL Java_com_shi_androidstudy_ndk_MainActivity_useJavah
  (JNIEnv * env, jobject obj){
  	char* pc = "use javah make .h文件";
  	jstring str = (**env).NewStringUTF(env, pc);
  	return str;
  }

```
#### 继续在jin文件中添加Android.mk
```mk

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := javah
LOCAL_SRC_FILES := javah.c

include $(BUILD_SHARED_LIBRARY)

```

#### 继续在jin文件中添加Application.mk
```mk

APP_ABI := all

```

![添加jni文件夹](http://img.blog.csdn.net/20170321114759137?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvYWJjNjM2ODc2NQ==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

#### 四、继续在jni文件夹中打开命令行窗口，ndk-build 生成.so文件，修改gradle文件(不修改项目无法找到库文件)
#### ，然后成功运行项目

![运行项目](http://img.blog.csdn.net/20170321114846048?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvYWJjNjM2ODc2NQ==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

##### 五、更加方便的使用javah

本文主要实现了如何对一个包含native方法的对象生成.h文件，以方便我们使用其中的函数名，上面我们是通过命令行来
生成.h文件，下面我们再介绍一种更加简单的方法，把javah添加的AndroidStudio的Tool中，我们直接右键就能生成
我们想要的.h文件

- 在设置界面，找到External Tools，如下图，然后点击右边方框的“+”。

![设置tool](http://img.blog.csdn.net/20170321115615476?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvYWJjNjM2ODc2NQ==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

继续设置相应的参数

![设置tool参数](http://img.blog.csdn.net/20170321115729744?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvYWJjNjM2ODc2NQ==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

```参数

Program: $JDKPath$\bin\javah.exe
Parameters: -classpath . -jni -d $ModuleFileDir$/src/main/jni $FileClass$
Working directory: $ModuleFileDir$\src\main\Java

```
使用我们添加的Tool，成功生成.h文件
![设置tool参数](http://img.blog.csdn.net/20170321115843636?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvYWJjNjM2ODc2NQ==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)