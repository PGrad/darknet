#include <jni.h>
#include "HelloJni.h"

JNIEXPORT jstring JNICALL Java_HelloJni_getJniString(JNIEnv* env, jobject this) {
    return (*env)->NewStringUTF(env, "Hello from C!");
}
