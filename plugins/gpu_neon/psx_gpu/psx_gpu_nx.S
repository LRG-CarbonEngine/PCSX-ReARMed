 
#include <nn/util/util_Assembly.h>
 
#include "psx_gpu.h"
#include "psx_gpu_offsets.h"

#define psx_gpu_b_dx_offset (psx_gpu_b_block_span_offset + 4)

#define edge_data_left_x_offset                           0
#define edge_data_num_blocks_offset                       2
#define edge_data_right_mask_offset                       4
#define edge_data_y_offset                                6
 
.text
 
#undef psx_gpu
#undef num_blocks
#undef triangle
#undef c_64

#define psx_gpu                                  w0
#define block_ptr                                w1
#define num_blocks                               w2
#define uv_01                                    w3
#define uv_23                                    w4
#define uv_45                                    w5
#define uv_67                                    w6
#define uv_0                                     w7
#define uv_1                                     w3
#define uv_2                                     w8
#define uv_3                                     w4
#define uv_4                                     w9
#define uv_5                                     w5
#define uv_6                                     w10
#define uv_7                                     w6
#define texture_ptr                              w11

#define pixel_0                                  r7
#define pixel_1                                  r3
#define pixel_2                                  r8
#define pixel_3                                  r4
#define pixel_4                                  r9
#define pixel_5                                  r5
#define pixel_6                                  r10
#define pixel_7                                  r6

#define pixels_a                                 r7
#define pixels_b                                 r9
#define pixels_c                                 r8
#define pixels_d                                 r10

#define c_64                                     r0

#define clut_ptr                                 r12
#define current_texture_mask                     r5
#define dirty_textures_mask                      r6

#define texels                                   d0

#define clut_low_a                               w2
#define clut_low_b                               w3
#define clut_high_a                              w4
#define clut_high_b                              w5

#define clut_a                                   x1
#define clut_b                                   x2

#define texels_low                               d6
#define texels_high                              d7

.align 3

//NN_UTIL_ASM_FUNCTION_BEGIN(texture_blocks_4bpp)
//  stmdb sp!, { w3 - w11, w14 }
//  ret
//NN_UTIL_ASM_FUNCTION_END(texture_blocks_4bpp)