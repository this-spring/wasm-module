/*
 * @Author: xiuquanxu
 * @Company: kaochong
 * @Date: 2021-01-28 15:12:01
 * @LastEditors: xiuquanxu
 * @LastEditTime: 2021-01-29 15:54:35
*/
#include "../codec/api/svc/codec_api.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct H264Decoder 
{
    ISVCDecoder *pSvcDecoder;
    SBufferInfo *sDstBufInfo;
    unsigned char *pData[3];
    char* input;
    int i_size;
} h264_decoder;

H264Decoder* h264_decoder_init();

int h264_decoder_frame(H264Decoder* decoder, char* input, int size, char* out);

void h264_decoder_destory(H264Decoder* decoder);