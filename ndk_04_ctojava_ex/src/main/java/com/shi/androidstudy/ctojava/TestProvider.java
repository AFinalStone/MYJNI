package com.shi.androidstudy.ctojava;

public class TestProvider {

    public static String getTime() {
        LogUtils.printWithSystemOut("Call From C Java Static Method");
        LogUtils.toastMessage(MainActivity.mContext, "Call From C To Java Static Method_getTime(获取时间)");
        return String.valueOf(System.currentTimeMillis());
    }

    public void sayHello(String msg) {
        LogUtils.printWithSystemOut("Call From C Java Not Static Method ：" + msg);
        LogUtils.toastMessage(MainActivity.mContext, "Call From C TO Java Not Static Method_sayHello(哈喽) ：" + msg);
    }

}
