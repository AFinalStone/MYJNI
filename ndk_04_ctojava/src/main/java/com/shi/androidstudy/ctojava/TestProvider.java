package com.shi.androidstudy.ctojava;

public class TestProvider {

    public static String getTime() {
        LogUtil.i("Call From C Java Static Method");
        ToastUtil.show("Call From C To Java Static Method_getTime(获取时间)");
        return String.valueOf(System.currentTimeMillis());
    }

    public void sayHello(String msg) {
        LogUtil.i("Call From C Java Not Static Method ：" + msg);
        ToastUtil.show("Call From C TO Java Not Static Method_sayHello(你好) ：" + msg);
    }

}
