## NDK学习笔记<二> 成功搭建NDK开发环境

### 工欲善其事必先利其器，进行NDK开发的第一步，当然是NDK的开发环境搭建了，这里简单讲述一下个人搭建过程

##### 一、在AndroidStudio中依次点击Tools->Android->SDK Manager

 ![图一](/screen/S2_01.png)

##### 二、在Android SDK中点击SDK Tools，然后勾选LLDB和NDK选项，然后OK确认，进行NDK Build的下载

 ![图二](/screen/S2_02.png)

##### 三、成功更新下载NDK Build之后，我们要进行NDK环境变量的配置，右键计算机->属性->高级系统设置->环境变量
->Path ，双击Path进行编辑，我的NDK Build是下载到了D:\Android_Studio\SDK\ndk-bundle文件夹下面，
所以我在Path的后面添加 **;D:\Android_Studio\SDK\ndk-bundle**

 ![图三](/screen/S2_03.png)

##### 四、成功更新下载NDK Build之后，我们要进行NDK环境变量的配置，右键计算机->属性->高级系统设置->环境变量->Path ，
  双击Path进行编辑，我的NDK Build是下载到了D:\Android_Studio\SDK\ndk-bundle文件夹下面，所以我在Path的后面
  添加 **;D:\Android_Studio\SDK\ndk-bundle**

  ![图三](/screen/S2_03.png)

##### 五、配置完成之后，我们在运行窗口中输入cmd，打开命令行窗口，输入ndk-build -version，看到如图所示内容，说明配置成功

  ![图四](/screen/S2_04.png);















