#include "layer.h"
#include "cuda.h"
#include <stdlib.h>

void free_layer(layer l)
{
    if(l.type == DROPOUT){
        if(l.rand)           free(l.rand);
#ifdef GPU
        if(l.rand_gpu)             cuda_free(l.rand_gpu);
#endif
        return;
    }
    if(l.cweights)           free(l.cweights);
    if(l.indexes)            free(l.indexes);
    if(l.input_layers)       free(l.input_layers);
    if(l.input_sizes)        free(l.input_sizes);
    if(l.map)                free(l.map);
    if(l.rand)               free(l.rand);
    if(l.cost)               free(l.cost);
    if(l.state)              free(l.state);
    if(l.prev_state)         free(l.prev_state);
    if(l.forgot_state)       free(l.forgot_state);
    if(l.forgot_delta)       free(l.forgot_delta);
    if(l.state_delta)        free(l.state_delta);
    if(l.concat)             free(l.concat);
    if(l.concat_delta)       free(l.concat_delta);
    if(l.binary_weights)     free(l.binary_weights);
    if(l.biases)             free(l.biases);
    if(l.bias_updates)       free(l.bias_updates);
    if(l.scales)             free(l.scales);
    if(l.scale_updates)      free(l.scale_updates);
    if(l.weights)            free(l.weights);
    if(l.weight_updates)     free(l.weight_updates);
    if(l.col_image)          free(l.col_image);
    if(l.delta)              free(l.delta);
    if(l.output)             free(l.output);
    if(l.squared)            free(l.squared);
    if(l.norms)              free(l.norms);
    if(l.spatial_mean)       free(l.spatial_mean);
    if(l.mean)               free(l.mean);
    if(l.variance)           free(l.variance);
    if(l.mean_delta)         free(l.mean_delta);
    if(l.variance_delta)     free(l.variance_delta);
    if(l.rolling_mean)       free(l.rolling_mean);
    if(l.rolling_variance)   free(l.rolling_variance);
    if(l.x)                  free(l.x);
    if(l.x_norm)             free(l.x_norm);
    if(l.m)                  free(l.m);
    if(l.v)                  free(l.v);
    if(l.z_cpu)              free(l.z_cpu);
    if(l.r_cpu)              free(l.r_cpu);
    if(l.h_cpu)              free(l.h_cpu);
    if(l.binary_input) free(l.binary_input);

#ifdef GPU
    if(l.indexes_gpu)          cuda_free((float *)l.indexes_gpu);
    if(l.weights_gpu)          cuda_free(l.weights_gpu);
    if(l.weight_updates_gpu)   cuda_free(l.weight_updates_gpu);
    if(l.col_image_gpu)        cuda_free(l.col_image_gpu);
    if(l.weights_gpu)          cuda_free(l.weights_gpu);
    if(l.biases_gpu)           cuda_free(l.biases_gpu);
    if(l.weight_updates_gpu)   cuda_free(l.weight_updates_gpu);
    if(l.bias_updates_gpu)     cuda_free(l.bias_updates_gpu);
    if(l.output_gpu)           cuda_free(l.output_gpu);
    if(l.delta_gpu)            cuda_free(l.delta_gpu);
    if(l.rand_gpu)             cuda_free(l.rand_gpu);
    if(l.squared_gpu)          cuda_free(l.squared_gpu);
    if(l.norms_gpu)            cuda_free(l.norms_gpu);
#endif
}
