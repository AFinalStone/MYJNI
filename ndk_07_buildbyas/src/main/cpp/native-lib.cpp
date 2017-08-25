#include <jni.h>
#include <string>
#include <android/log.h>
#include <stdlib.h>

#ifndef TASK_CHECKSUM_H
#define TASK_CHECKSUM_H

typedef signed char int8_t;
typedef short int int16_t;
typedef int int32_t;


bool checksum(const char *src_data, unsigned short& check_ret);
char *Jstring_To_charX(JNIEnv *env, jstring jstr);

#endif

extern "C"
JNIEXPORT jstring JNICALL
Java_com_afinalstone_administrator_ndk_107_1buildbyas_MainActivity_checkSum(
        JNIEnv *env, jobject obj, jstring msg) {
    char *cMsg = Jstring_To_charX(env, msg);
    unsigned short code = 0;
    __android_log_print(ANDROID_LOG_INFO, "MainActivity_checkSum", "code的初始化内容为：%d", code);
    checksum(cMsg, code);
    __android_log_print(ANDROID_LOG_INFO, "MainActivity_checkSum", "调用checksum方法之后code = %d", code);
    char *result;
    sprintf(result, "%d", code);
    __android_log_print(ANDROID_LOG_INFO, "MainActivity_checkSum", "result = %s", result);
    return env->NewStringUTF(result);
}

/* --------------------------------------------------------------------------*/
/**
 * @Synopsis          checksum加密算法
 *
 * @Param src_data    被加密的字符串
 *
 * @Param check_ret   int16_t类型的加密结果
 *
 * @Returns           加密是否成功
 */
/* ----------------------------------------------------------------------------*/
bool checksum(const char *src_data,unsigned short& check_ret) {
    bool ret = true;

    do {
        const int16_t *opt_data = reinterpret_cast<const int16_t *>(src_data);
        if (opt_data == NULL || src_data == NULL) {
            ret = false;
            /*TODO*/
            // warn_log();
            break;
        }
        int32_t accu_sum = 0;
        int32_t data_len = strlen(src_data);

        while (data_len > 1) {
            accu_sum += *(opt_data);
            opt_data++;
            data_len = data_len - 2;

            if (accu_sum & 0x80000000) {
                accu_sum = (accu_sum >> 16) + (accu_sum & 0xFFFF);
            }
        }

        if (data_len == 1) {
            accu_sum += *(reinterpret_cast<const int8_t *>(opt_data));
        }

        while (accu_sum >> 16) {
            accu_sum = (accu_sum >> 16) + (accu_sum & 0xFFFF);
        }
        check_ret = 0xFFFF & accu_sum;

//        check_ret = (accu_sum == 0xFFFF)?~accu_sum:accu_sum;

//        check_ret = (accu_sum == 0xFFFF)?accu_sum:~accu_sum;
    } while (0);

    return ret;
}

char * Jstring_To_charX(JNIEnv *env, jstring jstr) {

    char *rtn = NULL;

    jclass clsstring = env->FindClass("java/lang/String");
    jstring strencode = env->NewStringUTF("GB2312");

    jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");

    jbyteArray barr = (jbyteArray) env->CallObjectMethod(jstr, mid,
                                                         strencode); // String.getByte("GB2312");
    jsize alen = env->GetArrayLength(barr);
    jbyte *ba = env->GetByteArrayElements(barr, JNI_FALSE);

    if (alen > 0) {
        rtn = (char *) malloc(alen + 1); //"\0"
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }

    env->ReleaseByteArrayElements(barr, ba, 0);

    return rtn;
}



