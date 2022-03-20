#include "vgg16_cuda.h"
__global__
void cuda_normalize(const uint8_t* const image, float* input) {
    // Initialize variables
    float max_int = 255.0L;
    float mean = 0.5L;
    float var = 0.5L;

    // index calculation
    int B = gridDim.x; int b = blockIdx.x;
    int C = gridDim.y; int c = blockIdx.y;
    int W = blockDim.x; int w = threadIdx.x;
    int H = blockDim.y; int h = threadIdx.y;
    int idx = b * (C * H * W) + c * (H * W) + h * (W) + w;

    // Normalize
    if (idx < B * C * W * H) {
        input[idx] = image[idx] / max_int;       // transforms.ToTensor();
        input[idx] = (input[idx] - mean) / var;  // transforms.Normalize();
    }
}

__global__
void cuda_relu(float* feature_map) {
    // index calculation
    int B = gridDim.x; int b = blockIdx.x;
    int C = gridDim.y; int c = blockIdx.y;
    int W = blockDim.x; int w = threadIdx.x;
    int H = blockDim.y; int h = threadIdx.y;
    int idx = b * (C * H * W) + c * (H * W) + h * (W) + w;

    // relu if (idx < size) 
    if (idx < B * C * W * H) {
        feature_map[idx] = feature_map[idx] > (float)0.0 ? feature_map[idx] : (float)0.0;
    }
}

__global__
void cuda_pad(float* input, float* input_padded, int P) {
    // variable
    int B = gridDim.x; int b = blockIdx.x;
    int C = gridDim.y; int c = blockIdx.y;
    int W = blockDim.x; int w = threadIdx.x;
    int H = blockDim.y; int h = threadIdx.y;

    // length changed after padding
    int H_OUT = H + 2 * P;
    int W_OUT = W + 2 * P;

    int input_base = b * (C * H * W) + c * (H * W) + h * (W) + w;
    if (input_base < B * C * W * H) {
        int output_idx = b * (C * H_OUT * W_OUT) + c * (H_OUT * W_OUT) + (h + P) * W_OUT + (w + P);
        input_padded[output_idx] = input[input_base];
    }
}

__global__
void cuda_conv(float* input, float* output, float* weight, float* bias, int IC, int K) {
    int B = gridDim.x; int b = blockIdx.x;
    int OC = gridDim.y; int oc = blockIdx.y;
    int W_OUT = blockDim.x; int w = threadIdx.x;
    int H_OUT = blockDim.y; int h = threadIdx.y;
    int W = W_OUT + (K - 1); int H = H_OUT + (K - 1);

    // convolution
    int output_idx = b * (OC * H_OUT * W_OUT) + oc * (H_OUT * W_OUT) + h * W_OUT + w;
    if (output_idx < B * OC * H_OUT * W_OUT) {
        float acc = bias[oc];
        for (int ic = 0; ic < IC; ic++) {
            int input_base = b * (IC * H * W) + ic * (H * W) + h * (W) + w;
            int kernel_base = oc * (IC * K * K) + ic * (K * K);

            for (int kh = 0; kh < K; kh++)
                for (int kw = 0; kw < K; kw++) {
                    acc += input[input_base + kh * (W) + kw] * weight[kernel_base + kh * (K) + kw];
                }
        }
        output[output_idx] = acc;
    }
}

__global__
void cuda_conv_b5(float* input, float* output, float* weight, float* bias, int output_size, int IC, int K) {
    int B = gridDim.x; int b = blockIdx.x;
    int OC = blockDim.x; int oc = threadIdx.x;

    int W_OUT = output_size; int H_OUT = output_size;
    int W = W_OUT + (K - 1); int H = H_OUT + (K - 1);

    __shared__ float bias_shared[512];

    // convolution
    int block_id = b * (OC) + oc;
    if (block_id < B * OC) {
        for (int bi = 0; bi < 512; bi++) bias_shared[bi] = bias[bi];
        __syncthreads();

        for (int h = 0; h < H_OUT; h++)
            for (int w = 0; w < W_OUT; w++) {
                float acc = 0;
                int output_idx = b * (OC * H_OUT * W_OUT) + oc * (H_OUT * W_OUT) + h * W_OUT + w;
                for (int ic = 0; ic < IC; ic++) {
                    int input_base = b * (IC * H * W) + ic * (H * W) + h * (W) + w;
                    int kernel_base = oc * (IC * K * K) + ic * (K * K);
                    for (int kh = 0; kh < K; kh++)
                        for (int kw = 0; kw < K; kw++) {
                            acc += input[input_base + kh * (W) + kw] * weight[kernel_base + kh * (K) + kw];
                        }
                }
                output[output_idx] = acc + bias_shared[oc];
            }
    }
}

__global__
void cuda_pool(float* input, float* output) {
    // Initilaize variable
    int B = gridDim.x; int b = blockIdx.x;
    int C = gridDim.y; int c = blockIdx.y;
    int W_OUT = blockDim.x; int w = threadIdx.x;
    int H_OUT = blockDim.y; int h = threadIdx.y;

    int scale = 2;
    int H = H_OUT * scale;
    int W = W_OUT * scale;

    // Max Pooling
    // Init values
    float max_val = -256;
    int output_index = b * (C * H_OUT * W_OUT) + c * (H_OUT * W_OUT) + h * W_OUT + w;
    if (output_index < B * C * H_OUT * W_OUT) {
        // Find maximum
        for (int sh = 0; sh < scale; sh++)
            for (int sw = 0; sw < scale; sw++) {
                float val = input[b * (C * H * W) + c * (H * W) + (2 * h + sh) * (W) + (2 * w + sw)];
                if (val - max_val > 0) {
                    max_val = val;
                }
            }
        // Set output with max value
        output[output_index] = max_val;
    }
}

__global__
void cuda_fc(float* input, float* output, float* weight, float* bias, int IC) {
    int B = gridDim.x; int b = blockIdx.x;
    int OC = blockDim.x; int oc = threadIdx.x;
    int idx = b * OC + oc;

    if (idx < B * OC) {
        float acc = bias[oc];
        for (int ic = 0; ic < IC; ic++) {
            acc += weight[oc * IC + ic] * input[b * IC + ic];
        }
        output[idx] = acc;
    }
}

void vgg16_cuda::predict(int batch) {
    //////////////////////////////////////////////////
    // Normalization
    dim3 dimBlock_norm(input_size, input_size);
    dim3 dimGrid_norm(batch, input_channel);
    cuda_normalize<<<dimGrid_norm, dimBlock_norm>>>(d_image, d_input);

    //////////BLOCK 1/////////////////////////////////
    // TODO: Implement pad
    dim3 dimBlock_pad1_1(input_size, input_size);
    dim3 dimGrid_pad1_1(batch, conv1_1_in_channel);
    cuda_pad<<<dimGrid_pad1_1, dimBlock_pad1_1>>>(d_input, d_input_padded, conv1_1_padding_size);

    // TODO: Implement conv1_1
    dim3 dimBlock_conv1_1(C1_1_size, C1_1_size);
    dim3 dimGrid_conv1_1(batch, C1_1_channel);
    cuda_conv<<<dimGrid_conv1_1, dimBlock_conv1_1>>>(d_input_padded, d_C1_1_feature_map, d_conv1_1_weight, d_conv1_1_bias, 
                                                        conv1_1_in_channel, conv1_1_kernel_size);                                           

    // TODO: Implement relu
    dim3 dimBlock_relu1_1(C1_1_size, C1_1_size);
    dim3 dimGrid_relu1_1(batch, C1_1_channel);
    cuda_relu<<<dimGrid_relu1_1, dimBlock_relu1_1>>>(d_C1_1_feature_map);

    // TODO: Implement pad
    dim3 dimBlock_pad1_2(C1_1_size, C1_1_size);
    dim3 dimGrid_pad1_2(batch, C1_1_channel);
    cuda_pad<<<dimGrid_pad1_2, dimBlock_pad1_2>>>(d_C1_1_feature_map, d_C1_1_feature_map_padded, conv1_2_padding_size);

    // TODO: Implement conv1_2
    dim3 dimBlock_conv1_2(C1_2_size, C1_2_size);
    dim3 dimGrid_conv1_2(batch, C1_2_channel);
    cuda_conv<<<dimGrid_conv1_2, dimBlock_conv1_2>>>(d_C1_1_feature_map_padded, d_C1_2_feature_map, d_conv1_2_weight, d_conv1_2_bias, 
                                                        conv1_2_in_channel, conv1_2_kernel_size);

    // TODO: Implement relu
    dim3 dimBlock_relu1_2(C1_2_size, C1_2_size);
    dim3 dimGrid_relu1_2(batch, C1_2_channel);
    cuda_relu<<<dimGrid_relu1_2, dimBlock_relu1_2>>>(d_C1_2_feature_map);

    // TODO: Implement pool
    dim3 dimBlock_pool1(S1_size, S1_size);
    dim3 dimGrid_pool1(batch, S1_channel);
    cuda_pool<<<dimGrid_pool1, dimBlock_pool1>>>(d_C1_2_feature_map, d_S1_feature_map);    

    //////////BLOCK 2/////////////////////////////////
    // TODO: Implement pad
    dim3 dimBlock_pad2_1(S1_size, S1_size);
    dim3 dimGrid_pad2_1(batch, S1_channel);
    cuda_pad<<<dimGrid_pad2_1, dimBlock_pad2_1>>>(d_S1_feature_map, d_S1_feature_map_padded, conv2_1_padding_size);

    // TODO: Implement conv2_1
    dim3 dimBlock_conv2_1(C2_1_size, C2_1_size);
    dim3 dimGrid_conv2_1(batch, C2_1_channel);
    cuda_conv<<<dimGrid_conv2_1, dimBlock_conv2_1>>>(d_S1_feature_map_padded, d_C2_1_feature_map, d_conv2_1_weight, d_conv2_1_bias,
                                                        conv2_1_in_channel, conv2_1_kernel_size);

    // TODO: Implement relu
    dim3 dimBlock_relu2_1(C2_1_size, C2_1_size);
    dim3 dimGrid_relu2_1(batch, C2_1_channel);
    cuda_relu<<<dimGrid_relu2_1, dimBlock_relu2_1>>>(d_C2_1_feature_map);

    // TODO: Implement pad
    dim3 dimBlock_pad2_2(C2_1_size, C2_1_size);
    dim3 dimGrid_pad2_2(batch, C2_1_channel);
    cuda_pad<<<dimGrid_pad2_2, dimBlock_pad2_2>>>(d_C2_1_feature_map, d_C2_1_feature_map_padded, conv2_2_padding_size);

    // TODO: Implement conv2_2
    dim3 dimBlock_conv2_2(C2_2_size, C2_2_size);
    dim3 dimGrid_conv2_2(batch, C2_2_channel);
    cuda_conv<<<dimGrid_conv2_2, dimBlock_conv2_2>>>(d_C2_1_feature_map_padded, d_C2_2_feature_map, d_conv2_2_weight, d_conv2_2_bias,
                                                        conv2_2_in_channel, conv2_2_kernel_size);

    // TODO: Implement relu
    dim3 dimBlock_relu2_2(C2_2_size, C2_2_size);
    dim3 dimGrid_relu2_2(batch, C2_2_channel);
    cuda_relu<<<dimGrid_relu2_2, dimBlock_relu2_2>>>(d_C2_2_feature_map);

    // TODO: Implement pool
    dim3 dimBlock_pool2(S2_size, S2_size);
    dim3 dimGrid_pool2(batch, S2_channel);
    cuda_pool<<<dimGrid_pool2, dimBlock_pool2>>>(d_C2_2_feature_map, d_S2_feature_map);

    //////////BLOCK 3/////////////////////////////////
    // TODO: Implement pad
    dim3 dimBlock_pad3_1(S2_size, S2_size);
    dim3 dimGrid_pad3_1(batch, S2_channel);
    cuda_pad<<<dimGrid_pad3_1, dimBlock_pad3_1>>>(d_S2_feature_map, d_S2_feature_map_padded, conv3_1_padding_size);

    // TODO: Implement conv3_1
    dim3 dimBlock_conv3_1(C3_1_size, C3_1_size);
    dim3 dimGrid_conv3_1(batch, C3_1_channel);
    cuda_conv<<<dimGrid_conv3_1, dimBlock_conv3_1>>>(d_S2_feature_map_padded, d_C3_1_feature_map, d_conv3_1_weight, d_conv3_1_bias,
                                                        conv3_1_in_channel, conv3_1_kernel_size);

    // TODO: Implement relu
    dim3 dimBlock_relu3_1(C3_1_size, C3_1_size);
    dim3 dimGrid_relu3_1(batch, C3_1_channel);
    cuda_relu<<<dimGrid_relu3_1, dimBlock_relu3_1>>>(d_C3_1_feature_map);

    // TODO: Implement pad
    dim3 dimBlock_pad3_2(C3_1_size, C3_1_size);
    dim3 dimGrid_pad3_2(batch, C3_1_channel);
    cuda_pad<<<dimGrid_pad3_2, dimBlock_pad3_2>>>(d_C3_1_feature_map, d_C3_1_feature_map_padded, conv3_2_padding_size);

    // TODO: Implement conv3_2
    dim3 dimBlock_conv3_2(C3_2_size, C3_2_size);
    dim3 dimGrid_conv3_2(batch, C3_2_channel);
    cuda_conv<<<dimGrid_conv3_2, dimBlock_conv3_2>>>(d_C3_1_feature_map_padded, d_C3_2_feature_map, d_conv3_2_weight, d_conv3_2_bias,
                                                        conv3_2_in_channel, conv3_2_kernel_size);

    // TODO: Implement relu
    dim3 dimBlock_relu3_2(C3_2_size, C3_2_size);
    dim3 dimGrid_relu3_2(batch, C3_2_channel);
    cuda_relu<<<dimGrid_relu3_2, dimBlock_relu3_2>>>(d_C3_2_feature_map);

    // TODO: Implement pad
    dim3 dimBlock_pad3_3(C3_2_size, C3_2_size);
    dim3 dimGrid_pad3_3(batch, C3_2_channel);
    cuda_pad<<<dimGrid_pad3_3, dimBlock_pad3_3>>>(d_C3_2_feature_map, d_C3_2_feature_map_padded, conv3_3_padding_size);

    // TODO: Implement conv3_3
    dim3 dimBlock_conv3_3(C3_3_size, C3_3_size);
    dim3 dimGrid_conv3_3(batch, C3_3_channel);
    cuda_conv<<<dimGrid_conv3_3, dimBlock_conv3_3>>>(d_C3_2_feature_map_padded, d_C3_3_feature_map, d_conv3_3_weight, d_conv3_3_bias,
                                                        conv3_3_in_channel, conv3_3_kernel_size);
    // TODO: Implement relu
    dim3 dimBlock_relu3_3(C3_3_size, C3_3_size);
    dim3 dimGrid_relu3_3(batch, C3_3_channel);
    cuda_relu<<<dimGrid_relu3_3, dimBlock_relu3_3>>>(d_C3_3_feature_map);

    // TODO: Implement pool
    dim3 dimBlock_pool3(S3_size, S3_size);
    dim3 dimGrid_pool3(batch, S3_channel);
    cuda_pool<<<dimGrid_pool3, dimBlock_pool3>>>(d_C3_3_feature_map, d_S3_feature_map);

    //////////BLOCK 4/////////////////////////////////
    // TODO: Implement pad
    dim3 dimBlock_pad4_1(S3_size, S3_size);
    dim3 dimGrid_pad4_1(batch, S3_channel);
    cuda_pad<<<dimGrid_pad4_1, dimBlock_pad4_1>>>(d_S3_feature_map, d_S3_feature_map_padded, conv4_1_padding_size);

    // TODO: Implement conv4_1
    dim3 dimBlock_conv4_1(C4_1_size, C4_1_size);
    dim3 dimGrid_conv4_1(batch, C4_1_channel);
    cuda_conv<<<dimGrid_conv4_1, dimBlock_conv4_1>>>(d_S3_feature_map_padded, d_C4_1_feature_map, d_conv4_1_weight, d_conv4_1_bias,
                                                        conv4_1_in_channel, conv4_1_kernel_size);

    // TODO: Implement relu
    dim3 dimBlock_relu4_1(C4_1_size, C4_1_size);
    dim3 dimGrid_relu4_1(batch, C4_1_channel);
    cuda_relu<<<dimGrid_relu4_1, dimBlock_relu4_1>>>(d_C4_1_feature_map);

    // TODO: Implement pad
    dim3 dimBlock_pad4_2(C4_1_size, C4_1_size);
    dim3 dimGrid_pad4_2(batch, C4_1_channel);
    cuda_pad<<<dimGrid_pad4_2, dimBlock_pad4_2>>>(d_C4_1_feature_map, d_C4_1_feature_map_padded, conv4_2_padding_size);

    // TODO: Implement conv4_2
    dim3 dimBlock_conv4_2(C4_2_size, C4_2_size);
    dim3 dimGrid_conv4_2(batch, C4_2_channel);
    cuda_conv<<<dimGrid_conv4_2, dimBlock_conv4_2>>>(d_C4_1_feature_map_padded, d_C4_2_feature_map, d_conv4_2_weight, d_conv4_2_bias,
                                                        conv4_2_in_channel, conv4_2_kernel_size);

    // TODO: Implement relu
    dim3 dimBlock_relu4_2(C4_2_size, C4_2_size);
    dim3 dimGrid_relu4_2(batch, C4_2_channel);
    cuda_relu<<<dimGrid_relu4_2, dimBlock_relu4_2>>>(d_C4_2_feature_map);

    // TODO: Implement pad
    dim3 dimBlock_pad4_3(C4_2_size, C4_2_size);
    dim3 dimGrid_pad4_3(batch, C4_2_channel);
    cuda_pad<<<dimGrid_pad4_3, dimBlock_pad4_3>>>(d_C4_2_feature_map, d_C4_2_feature_map_padded, conv4_3_padding_size);

    // TODO: Implement conv4_3
    dim3 dimBlock_conv4_3(C4_3_size, C4_3_size);
    dim3 dimGrid_conv4_3(batch, C4_3_channel);
    cuda_conv<<<dimGrid_conv4_3, dimBlock_conv4_3>>>(d_C4_2_feature_map_padded, d_C4_3_feature_map, d_conv4_3_weight, d_conv4_3_bias,
                                                        conv4_3_in_channel, conv4_3_kernel_size);

    // TODO: Implement relu
    dim3 dimBlock_relu4_3(C4_3_size, C4_3_size);
    dim3 dimGrid_relu4_3(batch, C4_3_channel);
    cuda_relu<<<dimGrid_relu4_3, dimBlock_relu4_3>>>(d_C4_3_feature_map);

    // TODO: Implement pool
    dim3 dimBlock_pool4(S4_size, S4_size);
    dim3 dimGrid_pool4(batch, S4_channel);
    cuda_pool<<<dimGrid_pool4, dimBlock_pool4>>>(d_C4_3_feature_map, d_S4_feature_map);

    //////////BLOCK 5/////////////////////////////////
    // TODO: Implement pad
    dim3 dimBlock_pad5_1(S4_size, S4_size);
    dim3 dimGrid_pad5_1(batch, S4_channel);
    cuda_pad<<<dimGrid_pad5_1, dimBlock_pad5_1>>>(d_S4_feature_map, d_S4_feature_map_padded, conv5_1_padding_size);

    // TODO: Implement conv5_1
    dim3 dimBlock_conv5_1(C5_1_channel, 1);
    dim3 dimGrid_conv5_1(batch, 1);
    cuda_conv_b5<<<dimGrid_conv5_1, dimBlock_conv5_1>>>(d_S4_feature_map_padded, d_C5_1_feature_map, d_conv5_1_weight, d_conv5_1_bias,
                                                        C5_1_size, conv5_1_in_channel, conv5_1_kernel_size);

    // TODO: Implement relu
    dim3 dimBlock_relu5_1(C5_1_size, C5_1_size);
    dim3 dimGrid_relu5_1(batch, C5_1_channel);
    cuda_relu<<<dimGrid_relu5_1, dimBlock_relu5_1>>>(d_C5_1_feature_map);

    // TODO: Implement pad
    dim3 dimBlock_pad5_2(C5_1_size, C5_1_size);
    dim3 dimGrid_pad5_2(batch, C5_1_channel);
    cuda_pad<<<dimGrid_pad5_2, dimBlock_pad5_2>>>(d_C5_1_feature_map, d_C5_1_feature_map_padded, conv5_2_padding_size);

    // TODO: Implement conv5_2
    dim3 dimBlock_conv5_2(C5_2_channel, 1);
    dim3 dimGrid_conv5_2(batch, 1);
    cuda_conv_b5<<<dimGrid_conv5_2, dimBlock_conv5_2>>>(d_C5_1_feature_map_padded, d_C5_2_feature_map, d_conv5_2_weight, d_conv5_2_bias,
                                                        C5_2_size, conv5_2_in_channel, conv5_2_kernel_size);

    // TODO: Implement relu
    dim3 dimBlock_relu5_2(C5_2_size, C5_2_size);
    dim3 dimGrid_relu5_2(batch, C5_2_channel);
    cuda_relu<<<dimGrid_relu5_2, dimBlock_relu5_2>>>(d_C5_2_feature_map);

    // TODO: Implement pad
    dim3 dimBlock_pad5_3(C5_2_size, C5_2_size);
    dim3 dimGrid_pad5_3(batch, C5_2_channel);
    cuda_pad<<<dimGrid_pad5_3, dimBlock_pad5_3>>>(d_C5_2_feature_map, d_C5_2_feature_map_padded, conv5_3_padding_size);

    // TODO: Implement conv5_3
    dim3 dimBlock_conv5_3(C5_3_channel, 1);
    dim3 dimGrid_conv5_3(batch, 1);
    cuda_conv_b5<<<dimGrid_conv5_3, dimBlock_conv5_3>>>(d_C5_2_feature_map_padded, d_C5_3_feature_map, d_conv5_3_weight, d_conv5_3_bias,
                                                        C5_3_size, conv5_3_in_channel, conv5_3_kernel_size);

    // TODO: Implement relu
    dim3 dimBlock_relu5_3(C5_3_size, C5_3_size);
    dim3 dimGrid_relu5_3(batch, C5_3_channel);
    cuda_relu<<<dimGrid_relu5_3, dimBlock_relu5_3>>>(d_C5_3_feature_map);

    // TODO: Implement pool
    dim3 dimBlock_pool5(S5_size, S5_size);
    dim3 dimGrid_pool5(batch, S5_channel);
    cuda_pool<<<dimGrid_pool5, dimBlock_pool5>>>(d_C5_3_feature_map, d_S5_feature_map);
    
    ////////////////////////////////////////////////////
    // TODO: Implement fc1
    dim3 dimBlock_fc(fc1_out_channel, 1);
    dim3 dimGrid_fc(batch, 1);
    cuda_fc<<<dimGrid_fc, dimBlock_fc>>>(d_S5_feature_map, d_output, d_fc1_weight, d_fc1_bias, fc1_in_channel);

    // TODO: Implement relu
    /* NOTE: unless you want to make a major change to this class structure, 
    *  you need to write your output to the device memory d_output 
    *  so that classify() can handle the rest.
    */
}

void vgg16_cuda::prepare_device_memory(uint8_t* image) {
  // Alloc Model Parameters

  //////////BLOCK 1/////////////////////////////////
  cudaMalloc((void**)&d_conv1_1_weight,
             sizeof(float) * conv1_1_in_channel * conv1_1_out_channel *
                 conv1_1_kernel_size * conv1_1_kernel_size);
  cudaMalloc((void**)&d_conv1_1_bias, sizeof(float) * conv1_1_out_channel);
  cudaMalloc((void**)&d_conv1_2_weight,
             sizeof(float) * conv1_2_in_channel * conv1_2_out_channel *
                 conv1_2_kernel_size * conv1_2_kernel_size);
  cudaMalloc((void**)&d_conv1_2_bias, sizeof(float) * conv1_2_out_channel);

  //////////BLOCK 2/////////////////////////////////
  cudaMalloc((void**)&d_conv2_1_weight,
             sizeof(float) * conv2_1_in_channel * conv2_1_out_channel *
                 conv2_1_kernel_size * conv2_1_kernel_size);
  cudaMalloc((void**)&d_conv2_1_bias, sizeof(float) * conv2_1_out_channel);
  cudaMalloc((void**)&d_conv2_2_weight,
             sizeof(float) * conv2_2_in_channel * conv2_2_out_channel *
                 conv2_2_kernel_size * conv2_2_kernel_size);
  cudaMalloc((void**)&d_conv2_2_bias, sizeof(float) * conv2_2_out_channel);

  //////////BLOCK 3/////////////////////////////////
  cudaMalloc((void**)&d_conv3_1_weight,
             sizeof(float) * conv3_1_in_channel * conv3_1_out_channel *
                 conv3_1_kernel_size * conv3_1_kernel_size);
  cudaMalloc((void**)&d_conv3_1_bias, sizeof(float) * conv3_1_out_channel);
  cudaMalloc((void**)&d_conv3_2_weight,
             sizeof(float) * conv3_2_in_channel * conv3_2_out_channel *
                 conv3_2_kernel_size * conv3_2_kernel_size);
  cudaMalloc((void**)&d_conv3_2_bias, sizeof(float) * conv3_2_out_channel);
  cudaMalloc((void**)&d_conv3_3_weight,
             sizeof(float) * conv3_3_in_channel * conv3_3_out_channel *
                 conv3_3_kernel_size * conv3_3_kernel_size);
  cudaMalloc((void**)&d_conv3_3_bias, sizeof(float) * conv3_3_out_channel);

  //////////BLOCK 4/////////////////////////////////
  cudaMalloc((void**)&d_conv4_1_weight,
             sizeof(float) * conv4_1_in_channel * conv4_1_out_channel *
                 conv4_1_kernel_size * conv4_1_kernel_size);
  cudaMalloc((void**)&d_conv4_1_bias, sizeof(float) * conv4_1_out_channel);
  cudaMalloc((void**)&d_conv4_2_weight,
             sizeof(float) * conv4_2_in_channel * conv4_2_out_channel *
                 conv4_2_kernel_size * conv4_2_kernel_size);
  cudaMalloc((void**)&d_conv4_2_bias, sizeof(float) * conv4_2_out_channel);
  cudaMalloc((void**)&d_conv4_3_weight,
             sizeof(float) * conv4_3_in_channel * conv4_3_out_channel *
                 conv4_3_kernel_size * conv4_3_kernel_size);
  cudaMalloc((void**)&d_conv4_3_bias, sizeof(float) * conv4_3_out_channel);

  //////////BLOCK 5/////////////////////////////////
  cudaMalloc((void**)&d_conv5_1_weight,
             sizeof(float) * conv5_1_in_channel * conv5_1_out_channel *
                 conv5_1_kernel_size * conv5_1_kernel_size);
  cudaMalloc((void**)&d_conv5_1_bias, sizeof(float) * conv5_1_out_channel);
  cudaMalloc((void**)&d_conv5_2_weight,
             sizeof(float) * conv5_2_in_channel * conv5_2_out_channel *
                 conv5_2_kernel_size * conv5_2_kernel_size);
  cudaMalloc((void**)&d_conv5_2_bias, sizeof(float) * conv5_2_out_channel);
  cudaMalloc((void**)&d_conv5_3_weight,
             sizeof(float) * conv5_3_in_channel * conv5_3_out_channel *
                 conv5_3_kernel_size * conv5_3_kernel_size);
  cudaMalloc((void**)&d_conv5_3_bias, sizeof(float) * conv5_3_out_channel);

  //////////FC 1////////////////////////////////////
  cudaMalloc((void**)&d_fc1_weight,
             sizeof(float) * fc1_in_channel * fc1_out_channel);
  cudaMalloc((void**)&d_fc1_bias, sizeof(float) * fc1_out_channel);

  // Alloc Activations
  cudaMalloc((void**)&d_image,
             sizeof(uint8_t) * batch * input_size * input_size * input_channel);
  cudaMalloc((void**)&d_input,
             sizeof(float) * batch * input_channel * input_size * input_size);

  //////////BLOCK 1/////////////////////////////////
  cudaMalloc((void**)&d_input_padded,
             sizeof(float) * batch * input_channel * (input_size+2*conv1_1_padding_size) * (input_size+2*conv1_1_padding_size));
  cudaMalloc((void**)&d_C1_1_feature_map,
             sizeof(float) * batch * C1_1_channel * C1_1_size * C1_1_size);
  cudaMalloc((void**)&d_C1_1_feature_map_padded,
             sizeof(float) * batch * C1_1_channel * (C1_1_size+2*conv1_2_padding_size) * (C1_1_size+2*conv1_2_padding_size));
  cudaMalloc((void**)&d_C1_2_feature_map,
             sizeof(float) * batch * C1_2_channel * C1_2_size * C1_2_size);
  cudaMalloc((void**)&d_S1_feature_map,
             sizeof(float) * batch * S1_channel * S1_size * S1_size);

  //////////BLOCK 2/////////////////////////////////
  cudaMalloc((void**)&d_S1_feature_map_padded,
             sizeof(float) * batch * S1_channel * (S1_size+2*conv2_1_padding_size) * (S1_size+2*conv2_1_padding_size));
  cudaMalloc((void**)&d_C2_1_feature_map,
             sizeof(float) * batch * C2_1_channel * C2_1_size * C2_1_size);
  cudaMalloc((void**)&d_C2_1_feature_map_padded,
             sizeof(float) * batch * C2_1_channel * (C2_1_size+2*conv2_2_padding_size) * (C2_1_size+2*conv2_2_padding_size));
  cudaMalloc((void**)&d_C2_2_feature_map,
             sizeof(float) * batch * C2_2_channel * C2_2_size * C2_2_size);
  cudaMalloc((void**)&d_S2_feature_map,
             sizeof(float) * batch * S2_channel * S2_size * S2_size);

  //////////BLOCK 3/////////////////////////////////
  cudaMalloc((void**)&d_S2_feature_map_padded,
             sizeof(float) * batch * S2_channel * (S2_size+2*conv3_1_padding_size) * (S2_size+2*conv3_1_padding_size));
  cudaMalloc((void**)&d_C3_1_feature_map,
             sizeof(float) * batch * C3_1_channel * C3_1_size * C3_1_size);
  cudaMalloc((void**)&d_C3_1_feature_map_padded,
             sizeof(float) * batch * C3_1_channel * (C3_1_size+2*conv3_2_padding_size) * (C3_1_size+2*conv3_2_padding_size));
  cudaMalloc((void**)&d_C3_2_feature_map,
             sizeof(float) * batch * C3_2_channel * C3_2_size * C3_2_size);
  cudaMalloc((void**)&d_C3_2_feature_map_padded,
             sizeof(float) * batch * C3_2_channel * (C3_2_size+2*conv3_3_padding_size) * (C3_2_size+2*conv3_3_padding_size));
  cudaMalloc((void**)&d_C3_3_feature_map,
             sizeof(float) * batch * C3_3_channel * C3_3_size * C3_3_size);
  cudaMalloc((void**)&d_S3_feature_map,
             sizeof(float) * batch * S3_channel * S3_size * S3_size);

  //////////BLOCK 4/////////////////////////////////
  cudaMalloc((void**)&d_S3_feature_map_padded,
             sizeof(float) * batch * S3_channel * (S3_size+2*conv4_1_padding_size) * (S3_size+2*conv4_1_padding_size));
  cudaMalloc((void**)&d_C4_1_feature_map,
             sizeof(float) * batch * C4_1_channel * C4_1_size * C4_1_size);
  cudaMalloc((void**)&d_C4_1_feature_map_padded,
             sizeof(float) * batch * C4_1_channel * (C4_1_size+2*conv4_2_padding_size) * (C4_1_size+2*conv4_2_padding_size));
  cudaMalloc((void**)&d_C4_2_feature_map,
             sizeof(float) * batch * C4_2_channel * C4_2_size * C4_2_size);
  cudaMalloc((void**)&d_C4_2_feature_map_padded,
             sizeof(float) * batch * C4_2_channel * (C4_2_size+2*conv4_3_padding_size) * (C4_2_size+2*conv4_3_padding_size));
  cudaMalloc((void**)&d_C4_3_feature_map,
             sizeof(float) * batch * C4_3_channel * C4_3_size * C4_3_size);
  cudaMalloc((void**)&d_S4_feature_map,
             sizeof(float) * batch * S4_channel * S4_size * S4_size);

  //////////BLOCK 5/////////////////////////////////
  cudaMalloc((void**)&d_S4_feature_map_padded,
             sizeof(float) * batch * S4_channel * (S4_size+2*conv5_1_padding_size) * (S4_size+2*conv5_1_padding_size));
  cudaMalloc((void**)&d_C5_1_feature_map,
             sizeof(float) * batch * C5_1_channel * C5_1_size * C5_1_size);
  cudaMalloc((void**)&d_C5_1_feature_map_padded,
             sizeof(float) * batch * C5_1_channel * (C5_1_size+2*conv5_2_padding_size) * (C5_1_size+2*conv5_2_padding_size));
  cudaMalloc((void**)&d_C5_2_feature_map,
             sizeof(float) * batch * C5_2_channel * C5_2_size * C5_2_size);
  cudaMalloc((void**)&d_C5_2_feature_map_padded,
             sizeof(float) * batch * C5_2_channel * (C5_2_size+2*conv5_3_padding_size) * (C5_2_size+2*conv5_3_padding_size));
  cudaMalloc((void**)&d_C5_3_feature_map,
             sizeof(float) * batch * C5_3_channel * C5_3_size * C5_3_size);
  cudaMalloc((void**)&d_S5_feature_map,
             sizeof(float) * batch * S5_channel * S5_size * S5_size);


  cudaMalloc((void**)&d_output, sizeof(float) * batch * output_size);

  // Copy Parameters
  //////////BLOCK 1/////////////////////////////////
  cudaMemcpy(d_conv1_1_weight, conv1_1_weight,
             sizeof(float) * conv1_1_in_channel * conv1_1_out_channel *
                 conv1_1_kernel_size * conv1_1_kernel_size,
             cudaMemcpyHostToDevice);
  cudaMemcpy(d_conv1_1_bias, conv1_1_bias, sizeof(float) * conv1_1_out_channel,
             cudaMemcpyHostToDevice);
  cudaMemcpy(d_conv1_2_weight, conv1_2_weight,
              sizeof(float) * conv1_2_in_channel * conv1_2_out_channel *
                  conv1_2_kernel_size * conv1_2_kernel_size,
              cudaMemcpyHostToDevice);
   cudaMemcpy(d_conv1_2_bias, conv1_2_bias, sizeof(float) * conv1_2_out_channel,
              cudaMemcpyHostToDevice);

  //////////BLOCK 2/////////////////////////////////
  cudaMemcpy(d_conv2_1_weight, conv2_1_weight,
             sizeof(float) * conv2_1_in_channel * conv2_1_out_channel *
                 conv2_1_kernel_size * conv2_1_kernel_size,
             cudaMemcpyHostToDevice);
  cudaMemcpy(d_conv2_1_bias, conv2_1_bias, sizeof(float) * conv2_1_out_channel,
             cudaMemcpyHostToDevice);
  cudaMemcpy(d_conv2_2_weight, conv2_2_weight,
              sizeof(float) * conv2_2_in_channel * conv2_2_out_channel *
                  conv2_2_kernel_size * conv2_2_kernel_size,
              cudaMemcpyHostToDevice);
  cudaMemcpy(d_conv2_2_bias, conv2_2_bias, sizeof(float) * conv2_2_out_channel,
              cudaMemcpyHostToDevice);

  //////////BLOCK 3/////////////////////////////////
  cudaMemcpy(d_conv3_1_weight, conv3_1_weight,
             sizeof(float) * conv3_1_in_channel * conv3_1_out_channel *
                 conv3_1_kernel_size * conv3_1_kernel_size,
             cudaMemcpyHostToDevice);
  cudaMemcpy(d_conv3_1_bias, conv3_1_bias, sizeof(float) * conv3_1_out_channel,
             cudaMemcpyHostToDevice);
  cudaMemcpy(d_conv3_2_weight, conv3_2_weight,
              sizeof(float) * conv3_2_in_channel * conv3_2_out_channel *
                  conv3_2_kernel_size * conv3_2_kernel_size,
              cudaMemcpyHostToDevice);
  cudaMemcpy(d_conv3_2_bias, conv3_2_bias, sizeof(float) * conv3_2_out_channel,
              cudaMemcpyHostToDevice);
  cudaMemcpy(d_conv3_3_weight, conv3_3_weight,
              sizeof(float) * conv3_3_in_channel * conv3_3_out_channel *
                  conv3_3_kernel_size * conv3_3_kernel_size,
              cudaMemcpyHostToDevice);
  cudaMemcpy(d_conv3_3_bias, conv3_3_bias, sizeof(float) * conv3_3_out_channel,
              cudaMemcpyHostToDevice);

  //////////BLOCK 4/////////////////////////////////
  cudaMemcpy(d_conv4_1_weight, conv4_1_weight,
             sizeof(float) * conv4_1_in_channel * conv4_1_out_channel *
                 conv4_1_kernel_size * conv4_1_kernel_size,
             cudaMemcpyHostToDevice);
  cudaMemcpy(d_conv4_1_bias, conv4_1_bias, sizeof(float) * conv4_1_out_channel,
             cudaMemcpyHostToDevice);
  cudaMemcpy(d_conv4_2_weight, conv4_2_weight,
              sizeof(float) * conv4_2_in_channel * conv4_2_out_channel *
                  conv4_2_kernel_size * conv4_2_kernel_size,
              cudaMemcpyHostToDevice);
  cudaMemcpy(d_conv4_2_bias, conv4_2_bias, sizeof(float) * conv4_2_out_channel,
              cudaMemcpyHostToDevice);
  cudaMemcpy(d_conv4_3_weight, conv4_3_weight,
              sizeof(float) * conv4_3_in_channel * conv4_3_out_channel *
                  conv4_3_kernel_size * conv4_3_kernel_size,
              cudaMemcpyHostToDevice);
  cudaMemcpy(d_conv4_3_bias, conv4_3_bias, sizeof(float) * conv4_3_out_channel,
              cudaMemcpyHostToDevice);

  //////////BLOCK 5/////////////////////////////////
  cudaMemcpy(d_conv5_1_weight, conv5_1_weight,
             sizeof(float) * conv5_1_in_channel * conv5_1_out_channel *
                 conv5_1_kernel_size * conv5_1_kernel_size,
             cudaMemcpyHostToDevice);
  cudaMemcpy(d_conv5_1_bias, conv5_1_bias, sizeof(float) * conv5_1_out_channel,
             cudaMemcpyHostToDevice);
  cudaMemcpy(d_conv5_2_weight, conv5_2_weight,
              sizeof(float) * conv5_2_in_channel * conv5_2_out_channel *
                  conv5_2_kernel_size * conv5_2_kernel_size,
              cudaMemcpyHostToDevice);
  cudaMemcpy(d_conv5_2_bias, conv5_2_bias, sizeof(float) * conv5_2_out_channel,
              cudaMemcpyHostToDevice);
  cudaMemcpy(d_conv5_3_weight, conv5_3_weight,
              sizeof(float) * conv5_3_in_channel * conv5_3_out_channel *
                  conv5_3_kernel_size * conv5_3_kernel_size,
              cudaMemcpyHostToDevice);
  cudaMemcpy(d_conv5_3_bias, conv5_3_bias, sizeof(float) * conv5_3_out_channel,
              cudaMemcpyHostToDevice);


  cudaMemcpy(d_fc1_weight, fc1_weight,
             sizeof(float) * fc1_in_channel * fc1_out_channel,
             cudaMemcpyHostToDevice);
  cudaMemcpy(d_fc1_bias, fc1_bias, sizeof(float) * fc1_out_channel,
             cudaMemcpyHostToDevice);

  // copy input image
  size_t image_size = batch * input_size * input_size * input_channel;
  cudaMemcpy(d_image, image, image_size * sizeof(uint8_t),
             cudaMemcpyHostToDevice);
}

void vgg16_cuda::classify(int* predict, int batch) {
  // read logits back to cpu
  cudaMemcpy(output, d_output, sizeof(float) * output_size * batch,
             cudaMemcpyDeviceToHost);
  // Softmax
  softmax(output, predict, batch, output_size);
}

vgg16_cuda::~vgg16_cuda() {
  cudaFree(d_conv1_1_weight);   
  cudaFree(d_conv1_2_weight);   
  cudaFree(d_conv2_1_weight);   
  cudaFree(d_conv2_2_weight);  
  cudaFree(d_conv3_1_weight);   
  cudaFree(d_conv3_2_weight);   
  cudaFree(d_conv3_3_weight);   
  cudaFree(d_conv4_1_weight);   
  cudaFree(d_conv4_2_weight);   
  cudaFree(d_conv4_3_weight); 
  cudaFree(d_conv5_1_weight);   
  cudaFree(d_conv5_2_weight);   
  cudaFree(d_conv5_3_weight);   
 
  cudaFree(d_conv1_1_bias);   
  cudaFree(d_conv1_2_bias);   
  cudaFree(d_conv2_1_bias);   
  cudaFree(d_conv2_2_bias);  
  cudaFree(d_conv3_1_bias);   
  cudaFree(d_conv3_2_bias);   
  cudaFree(d_conv3_3_bias);   
  cudaFree(d_conv4_1_bias);   
  cudaFree(d_conv4_2_bias);   
  cudaFree(d_conv4_3_bias); 
  cudaFree(d_conv5_1_bias);   
  cudaFree(d_conv5_2_bias);   
  cudaFree(d_conv5_3_bias);   
   
  cudaFree(d_fc1_weight);     
  cudaFree(d_fc1_bias);        

  cudaFree(d_image);          
  cudaFree(d_input); 

  cudaFree(d_input_padded);          
  cudaFree(d_C1_1_feature_map); 
  cudaFree(d_C1_1_feature_map_padded); 
  cudaFree(d_C1_2_feature_map); 
  cudaFree(d_S1_feature_map); 

  cudaFree(d_S1_feature_map_padded); 
  cudaFree(d_C2_1_feature_map); 
  cudaFree(d_C2_1_feature_map_padded); 
  cudaFree(d_C2_2_feature_map); 
  cudaFree(d_S2_feature_map); 

  cudaFree(d_S2_feature_map_padded); 
  cudaFree(d_C3_1_feature_map); 
  cudaFree(d_C3_1_feature_map_padded); 
  cudaFree(d_C3_2_feature_map); 
  cudaFree(d_C3_2_feature_map_padded); 
  cudaFree(d_C3_3_feature_map); 
  cudaFree(d_S3_feature_map); 

  cudaFree(d_S3_feature_map_padded); 
  cudaFree(d_C4_1_feature_map); 
  cudaFree(d_C4_1_feature_map_padded); 
  cudaFree(d_C4_2_feature_map); 
  cudaFree(d_C4_2_feature_map_padded); 
  cudaFree(d_C4_3_feature_map); 
  cudaFree(d_S4_feature_map); 

  cudaFree(d_S4_feature_map_padded); 
  cudaFree(d_C5_1_feature_map); 
  cudaFree(d_C5_1_feature_map_padded); 
  cudaFree(d_C5_2_feature_map); 
  cudaFree(d_C5_2_feature_map_padded); 
  cudaFree(d_C5_3_feature_map); 
  cudaFree(d_S5_feature_map); 
 
  cudaFree(d_output);       
  cudaFree(d_predict_cuda);   
}
