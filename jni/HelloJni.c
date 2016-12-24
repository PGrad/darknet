#include <jni.h>
#include "HelloJni.h"

JNIEXPORT void JNICALL Java_HelloJni_getJniString(JNIEnv* env, jobject this, jstring greeting) {
    const jbyte * c_greet;
		c_greet = (*env)->GetStringUTFChars(env, greeting, NULL);
		printf("%s from C!\n", c_greet);
		(*env)->ReleaseStringUTFChars(env, greeting, c_greet);
		//return (*env)->NewStringUTF(env, "Hello from C!");
}
