#include <jni.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "JniDarknet.h"
#include "parser.h"
#include "utils.h"
#include "cuda.h"
#include "blas.h"
#include "connected_layer.h"

#ifdef OPENCV
#include "opencv2/highgui/highgui_c.h"
#endif

extern int find_enter_exit(char *datacfg, char *cfgfile, char *weightfile, char *filename, float thresh);
JNIEXPORT jbool JNICALL Java_JniDarknet_Detect$
  (JNIEnv * env, jobject this, jstring filename) {
    int is_enter_exit = 0;
    #ifndef GPU
        gpu_index = -1;
    #else
        if(gpu_index >= 0) cuda_set_device(gpu_index);
    #endif
    const jbyte * c_filename = (*env)->GetStringUTFChars(env, filename, NULL);
    is_enter_exit = find_enter_exit("cfg/voc.data", "cfg/tiny-yolo-voc.cfg", "tiny-yolo-voc.weights", filename, 0.24);
    (*env)->ReleaseStringUTFChars(env, filename, c_filename);
    return is_enter_exit;
}

