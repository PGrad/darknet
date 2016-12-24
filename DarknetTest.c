#include <jni.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "DarknetTest.h"
#include "./src/parser.h"
#include "./src/utils.h"
#include "./src/cuda.h"
#include "./src/blas.h"
#include "./src/connected_layer.h"

#ifdef OPENCV
#include "opencv2/highgui/highgui_c.h"
#endif

extern int find_enter_exit(char *datacfg, char *cfgfile, char *weightfile, char *filename, float thresh);
JNIEXPORT jboolean JNICALL Java_DarknetTest_Detect
  (JNIEnv * env, jobject this, jstring filename) {
    int is_enter_exit = 0;
    #ifndef GPU
        gpu_index = -1;
    #else
        if(gpu_index >= 0) cuda_set_device(gpu_index);
    #endif
    const char * c_filename = (*env)->GetStringUTFChars(env, filename, NULL);
    is_enter_exit = find_enter_exit("cfg/voc.data", "cfg/tiny-yolo-voc.cfg", "tiny-yolo-voc.weights", c_filename, 0.24);
    (*env)->ReleaseStringUTFChars(env, filename, c_filename);
    return is_enter_exit;
}

