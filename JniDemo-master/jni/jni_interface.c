#include <jni.h>
#include <string.h>
#include <assert.h>
#include "NDKUtils.h"
#include "localJni/localconf.h"
#include "util/android_log_print.h"

JNIEXPORT jstring JNICALL Java_demo_jnidemo_NDKUtils_getVipString(JNIEnv *env, jobject obj){
	LOGD("(%s:%d)\n", __FUNCTION__, __LINE__);
    return (*env)->NewStringUTF(env, "NDKUtils_getVipString!中文");
}

JNIEXPORT jstring JNICALL Java_demo_jnidemo_NDKUtils_staticGenerateKey(JNIEnv *env, jobject obj, jstring name) {
	//return (*env)->NewStringUTF(env, "staticGenerateKey!");
    char key[512] = {0};
    memset(key, 0, sizeof(key));
    char temp[KEY_NAME_SIZE] = {0};
   const char *pName = (*env)->GetStringUTFChars(env, name, NULL); // 转为本地utf的char*
   if (NULL != pName) {
        strcpy(temp, pName);
		strcpy(key, __FILE__);
		strcat(key, "\n");
		strcat(key, __FUNCTION__);
        //java的字符串对象不需要再使用,通知虚拟机回收name
        (*env)->ReleaseStringUTFChars(env, name, pName);
    }
    return (*env)->NewStringUTF(env, key);
}


JNIEXPORT jstring JNICALL native_dynamic_key(JNIEnv *env, jobject obj, jstring name) {
    char key[KEY_SIZE] = {0};
	LOGD("(%s:%d)\n", __FUNCTION__, __LINE__);
    memset(key, 0, sizeof(key));
    char temp[KEY_NAME_SIZE] = {0};
    const char *pName = (*env)->GetStringUTFChars(env, name, NULL);
    if (NULL != pName) {
        strcpy(temp, pName);
		strcpy(key, __FILE__);
		strcat(key, "\n");
		strcat(key, __FUNCTION__);
        (*env)->ReleaseStringUTFChars(env, name, pName);
    }
    return (*env)->NewStringUTF(env, key);
}


static JNINativeMethod methods[] = {
        {"dynamicGenerateKey", "(Ljava/lang/String;)Ljava/lang/String;", (void *) native_dynamic_key},
        //这里可以有很多其他映射函数
};

//为某一个类注册本地方法，调用Jni注册
static int registerNativeMethods(JNIEnv *env, const char *className, JNINativeMethod *gMethods, int numMethods) {
    jclass clazz;
    clazz = (*env)->FindClass(env, className);
    if (clazz == NULL) {
        return JNI_FALSE;
    }
    if ((*env)->RegisterNatives(env, clazz, gMethods, numMethods) < 0) {
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

//注册Native
static int registerNatives(JNIEnv *env) {
    const char *className = "demo/jnidemo/NDKUtils"; //指定注册的类
    return registerNativeMethods(env, className, methods, sizeof(methods) / sizeof(methods[0]));
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved)
{
    LOGD("-------------JNI_OnLoad into.--------\n");
    JNIEnv* env = NULL;
    jint result = -1;

    if ((*vm)->GetEnv(vm, (void**) &env, JNI_VERSION_1_4) != JNI_OK){
        return -1;
    }
    assert(env != NULL);

    //动态注册，自定义函数
    if (!registerNatives(env)) {
        return -1;
    }

    return JNI_VERSION_1_4;
}

