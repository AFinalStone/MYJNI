package com.shi.androidstudy.ndk02;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    EditText et_addA;
    EditText et_addB;
    EditText et_minuend;
    EditText et_sub;
    EditText et_userName;
    EditText et_userPassword;
    EditText et_strMessage;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        et_addA = (EditText) findViewById(R.id.et_addA);
        et_addB = (EditText) findViewById(R.id.et_addB);
        et_minuend = (EditText) findViewById(R.id.et_minuend);
        et_sub = (EditText) findViewById(R.id.et_sub);
        et_userName = (EditText) findViewById(R.id.et_userName);
        et_userPassword = (EditText) findViewById(R.id.et_userPassword);
        et_strMessage = (EditText) findViewById(R.id.et_strMessage);
    }

    public void onClick(View view) {
        switch (view.getId()) {
            case R.id.tv_add:
                int addA = Integer.parseInt(et_addA.getText().toString().trim());
                int addB = Integer.parseInt(et_addB.getText().toString().trim());
                showMessage("两数相加结果为：" + add(addA, addB));
                break;
            case R.id.tv_sub:
                int subA = Integer.parseInt(et_minuend.getText().toString().trim());
                int subB = Integer.parseInt(et_sub.getText().toString().trim());
                showMessage("两数相减结果为：" + sub(subA, subB));
                break;
            case R.id.tv_encryptPassword:
                int passWord = Integer.parseInt(et_userPassword.getText().toString().trim());
                showMessage("密码异或加密之后为：" + encryptPassword(passWord));
                break;
            case R.id.tv_encryptMessage:
                showMessage("字符串加密之后为：" + encryptString(et_strMessage.getText().toString().trim()));
                break;
        }
    }

    private void showMessage(String message) {
        Toast.makeText(this, message, Toast.LENGTH_SHORT).show();
    }

    public native int add(int i, int j);

    public native int sub(int i, int j);

    public native int encryptPassword(int password);

    public native String encryptString(String strMessage);

    static {
        System.loadLibrary("MyNdk");
    }

}
