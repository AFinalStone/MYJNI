package com.shi.androidstudy.ctojava;


import android.content.Context;
import android.widget.Toast;


/**
 * ToastUtil
 * @author AFinalStone
 */
public class ToastUtil {

    public static Context mContext;

    private ToastUtil() {
        throw new AssertionError();
    }

    public static void register(Context context) {
        mContext = context;
    }


    private static void check() {
        if (mContext == null) {
            throw new NullPointerException(
                    "Must initial call ToastUtils.register(Context context) in your " +
                            "<? " +
                            "extends Application class>");
        }
    }

    public static void show(int resId) {
        check();
        show(mContext.getResources().getText(resId), Toast.LENGTH_SHORT);
    }

    public static void show(int resId, int duration) {
        check();
        show(mContext.getResources().getText(resId), duration);
    }

    public static void show(CharSequence text) {
        check();
        show(text, Toast.LENGTH_SHORT);
    }

    public static void show(CharSequence text, int duration) {
        check();
        Toast.makeText(mContext, text, duration).show();
    }

    public static void show( int resId, Object... args) {
        check();
        show(String.format(mContext.getResources().getString(resId), args), Toast.LENGTH_SHORT);
    }

    public static void show(String format, Object... args) {
        check();
        show(String.format(format, args), Toast.LENGTH_SHORT);
    }

    public static void show(int resId, int duration, Object... args) {
        check();
        show(String.format(mContext.getResources().getString(resId), args), duration);
    }

    public static void show( String format, int duration, Object... args) {
        check();
        show(String.format(format, args), duration);
    }
}
