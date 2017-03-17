## JNI学习笔记<一>

### 什么是JNI

##### JNI，英文全名为：Java Native Interface

jNi就是java调用本地方法的技术，最简单的来说，java运行一个程序需要要和不同的系统平台打交道，在windows里就是和

windows平台底层打交道，mac就是要和mac打交道，jvm就是通过大量的jni技术使得java能够在不同平台上运行。而使用了

这技术的一个标志就是native,如果一个类里的一个方法被native修饰，那就说明这个方法是jni来实现的，他是通过本地系统

api里的方法来实现的。当然这个本地方法可能是c或者C++，当然也可能是别的语言。jni是java跨平台的基础，jvm通过

在不同系统上调用不同的本地方法使得jvm可以在不同平台间移植。

当前你自己也可以用jni来写一些程序，这种基本上是你以前使用了其他语言完成了一些功能，但是你有要用java来重复这些功能

的时候，就可以使用jni来完成了。不过带来的问题就是，如果你的那个本地方法是依托于本地操作系统的话，那就意味着你的

java程序也只能在这一个系统上运行了。所以jni就使得java很容易限定在了一个系统平台上，而jdk的作用在于他提供一个规

范，这个规范就是包含了很多native方法，这些方法都是要本地操作系统来实现的，

而实现了这些本地方法的操作系统就可以移植java平台了。

##### java和C语言的异同

Java属于解释型语言, 跨平台, 编译运行效率相对较低，高级语言

C语言属于编译型语言, 本地语言, 无法跨平台，性能卓越，低级语言

上面的高级和低级没有优差之分，只是说明了语言和底层机器的距离

### JNI的用途

- **1. 市场上面，大多高级工程师，都要求会使用**
- **2. 效率优先的场合, 需要用到C语言**
- **3. C语言有一些优秀的类库, 在做程序的时候需要用到(WebKit, FFMPEG)**
- **4. 操作硬件一般使用C语言, 需要使用Java调用C来控制硬件**
- **5. 安全性优先, 保密性优先的场合, 需要用到C语言, 因为C语言是几乎无法编译的**

### 如何学习JNI

- **1. 首先要懂的Java代码**
- **2. 然后还要懂得C语言,C++语言**
- **3. 熟悉JNI接口规范，要懂得查看<jni.h>文件**