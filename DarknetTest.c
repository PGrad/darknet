#include <jni.h>

#include "DarknetTest.h"
#include "./src/cuda.h"

#ifdef OPENCV
#include "opencv2/highgui/highgui_c.h"
#endif

extern int ** get_rects(const char *datacfg, const char *cfgfile, const char *weightfile, const char *filename, float thresh);
extern void free_rect_bounds(int ** rectBounds, int size);
JNIEXPORT jobjectArray JNICALL Java_DarknetTest_Detect
  (JNIEnv * env, jobject this, jstring filename) {
    jint ** c_rects;
    jint num_rects;
    jclass intArray = (*env)->FindClass(env, "[I");
    int i;
    #ifndef GPU
        gpu_index = -1;
    #else
        if(gpu_index >= 0) cuda_set_device(gpu_index);
    #endif
    const char * c_filename = (*env)->GetStringUTFChars(env, filename, NULL);
    c_rects = get_rects("cfg/voc.data", "cfg/tiny-yolo-voc.cfg",
                        "weights/tiny-yolo-voc.weights", c_filename, 0.24);
    num_rects = sizeof(c_rects) / sizeof(int *);
    jobjectArray rects = (*env)->NewObjectArray(env, num_rects, intArray, NULL);
    for(i = 0; i < num_rects; ++i) {
        jintArray rect = (*env)->NewIntArray(env, 4);
        (*env)->SetIntArrayRegion(env, rect, 0, 4, c_rects[i]);
        (*env)->SetObjectArrayElement(env, rects, i, rect);
    }
    free_rect_bounds(c_rects, num_rects);
    (*env)->ReleaseStringUTFChars(env, filename, c_filename);
    return rects;
}

