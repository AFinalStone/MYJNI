package com.shi.androidstudy.ctojava;

import java.text.SimpleDateFormat;

import android.content.Context;
import android.util.Log;
import android.widget.Toast;

/**
 * 简单  Log 输出 集合
 *
 * 		isSystemPrint等标签为是否输出信息的开关
 *
 * @author luxiaofeng
 *
 */
public class LogUtils {

	public static Boolean isSystemPrint = true;
	public static Boolean isLogCatPrint = true;
	public static Boolean isFilePrint = true;
	public static Boolean isToastMessage = true;
	public static SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");

	public static void printWithSystemOut(Boolean flag,String content) {
		if(flag) {
			System.out.println(sdf.format(System.currentTimeMillis())+"   ----   "+content);
		}
	}

	public static void printWithSystemOut(String content) {
		printWithSystemOut(isSystemPrint,content);
	}

	public static void printWithLogCat(Boolean flag,String filter,String content) {
		if(flag) {
			Log.i(filter,sdf.format(System.currentTimeMillis())+"   ----   "+content);
		}
	}

	public static void printWithLogCat(String filter,String content) {
		printWithLogCat(isLogCatPrint,filter,content);
	}

	public static void toastMessage(Context mContext,Boolean flag,String strMsg) {
		if(flag) {
			Toast.makeText(mContext, strMsg, Toast.LENGTH_SHORT).show();
		}
	}

	public static void toastMessage(Context mContext,String strMsg) {
		toastMessage(mContext,isToastMessage,strMsg);
	}

	public static void setLogOnOff(boolean flag) {
		isSystemPrint = flag;
		isLogCatPrint = flag;
		isFilePrint = flag;
		isToastMessage = flag;
	}
}
