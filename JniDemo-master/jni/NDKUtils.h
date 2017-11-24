#include <jni.h>

#ifndef _NDK_UTILS_
#define _NDK_UTILS_
#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jstring JNICALL Java_demo_jnidemo_NDKUtils_getVipString(JNIEnv *, jobject);

JNIEXPORT jstring JNICALL Java_demo_jnidemo_NDKUtils_staticGenerateKey(JNIEnv *, jobject, jstring);

JNIEXPORT jstring JNICALL native_dynamic_key(JNIEnv *env, jobject obj, jstring name);

#ifdef __cplusplus
}
#endif
#endif