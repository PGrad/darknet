#include <jni.h>

#include "ObjectDetector.h"
#include "./src/cuda.h"

#ifdef OPENCV
#include "opencv2/highgui/highgui_c.h"
#endif

extern int ** get_rects(const char *datacfg, const char *cfgfile, const char *weightfile, const char *filename, float thresh);
extern void free_ptrs(void ** ptrs, int size);
JNIEXPORT jobjectArray JNICALL Java_xikuiw_volcano_hermit_analyzer_ObjectDetector_GetDarknetObjectBounds
  (JNIEnv * env, jobject this, jstring filename) {
    int ** c_rects;
    int num_rects;
    jclass intArrayClass = (*env)->FindClass(env, "[I");
    int i;
    const int NUM_CORNERS = 4;
    #ifndef GPU
        gpu_index = -1;
    #else
        if(gpu_index >= 0) cuda_set_device(gpu_index);
    #endif
    const char * c_filename = (*env)->GetStringUTFChars(env, filename, NULL);
    c_rects = get_rects((char *) "cfg/voc.data", (char *) "cfg/tiny-yolo-voc.cfg",
                        (char *) "weights/tiny-yolo-voc.weights", c_filename, 0.24);
    if(!c_rects)
        return (*env)->NewObjectArray(env, (jsize) 0, intArrayClass, NULL); 
    num_rects = sizeof(c_rects) / sizeof(int *);
    jobjectArray rects = (*env)->NewObjectArray(env, (jsize) num_rects, intArrayClass, NULL);
    for(i = 0; i < num_rects; ++i) {
        jintArray rect = (*env)->NewIntArray(env, NUM_CORNERS);
        (*env)->SetIntArrayRegion(env, rect, (jsize) 0, (jsize) NUM_CORNERS, (jint *) c_rects[i]);
        (*env)->SetObjectArrayElement(env, rects, (jsize) i, rect);
        (*env)->DeleteLocalRef(env, rect);
    }
    free_ptrs((void **) c_rects, num_rects);
    (*env)->ReleaseStringUTFChars(env, filename, c_filename);
    (*env)->DeleteLocalRef(env, intArrayClass);
    return rects;
}

