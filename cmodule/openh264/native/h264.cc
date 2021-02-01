/*
 * @Author: xiuquanxu
 * @Company: kaochong
 * @Date: 2021-01-28 15:11:41
 * @LastEditors: xiuquanxu
 * @LastEditTime: 2021-02-01 17:45:48
*/
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "h264.h"
bool nalu_start(char* data, int pos) {
    if (data[pos] == 0 && data[pos + 1] == 0 && data[pos + 2] == 1) {
        return true;
    }
    if (data[pos] == 0 && data[pos + 1] == 0 && data[pos + 2] == 0 && data[pos + 3] == 1) {
        return true;
    }
    return false;
}
int nalu_end(char* data, int pos, int size) {
    int end = pos;
    while (end < size)
    {
        if (nalu_start(data, end)) {
            return end;
        }
        end += 1;
    }
    return 0;
}

// extern "C" {
  

    int h264_decoder_frame(H264Decoder* decoder, char* input, int size, char* out) {
        // char* in = (char *)malloc(size * sizeof(char));
        printf("size:%d\n", size);
        int i_ret = decoder->pSvcDecoder->DecodeFrameNoDelay((unsigned char *)input, size, decoder->pData, decoder->sDstBufInfo);
        printf("i_ret:%d\n", i_ret);
        if (i_ret != 0) {
            printf("h264 decode error i_ret:%d\n", i_ret);
            return i_ret;
        }
        if (decoder->sDstBufInfo->iBufferStatus == 1) {
            int width = decoder->sDstBufInfo->UsrData.sSystemBuffer.iWidth;
            int height = decoder->sDstBufInfo->UsrData.sSystemBuffer.iHeight;
            printf("height:%d widht:%d\n", height, width);
        }
        return 0;
    }

    H264Decoder* h264_decoder_init() {
        H264Decoder* decoder = (H264Decoder *)malloc(sizeof(H264Decoder));
        memset(decoder, 0, sizeof(H264Decoder));
        int w_ret = WelsCreateDecoder(&decoder->pSvcDecoder);
        if (w_ret != 0) {
            printf("error:%d\n", w_ret);
        }
        memset(&decoder->sDstBufInfo, 0, sizeof(SBufferInfo));
        memset(decoder->pData, 0, sizeof(decoder->pData));
        SDecodingParam sParam = { 0 };
        int i_ret = decoder->pSvcDecoder->Initialize(&sParam);
        if (i_ret != 0) {
            printf("error:%d\n", i_ret);
        }
        return decoder;
    }
    

    void h264_decoder_destory(H264Decoder* decoder){
        if (decoder) {
                if (decoder->pSvcDecoder) {
                    decoder->pSvcDecoder->Uninitialize();
                    WelsDestroyDecoder(decoder->pSvcDecoder);
                }
                free(decoder);
                decoder = NULL;
        }
    }
// }

  int main() {
        H264Decoder* decoder = h264_decoder_init();
        printf("init decoder success \n");
        FILE* input = NULL;
        input = fopen("./test.h264", "rb");
        fseek(input, 0, SEEK_END);
        char* out = (char *)malloc(1024 * 1024);
        int length = ftell(input);
        char* data = (char *)malloc((length + 1) * sizeof(char));
        rewind(input);
        length = fread(data, 1, length, input);
        fclose(input);
        int pos = 0;
        // printf("pos:%d, length:%d\n", pos, length);
        while (pos < length - 4)
        {
            printf("pos:%d, length:%d\n", pos, length);
            if (nalu_start(data, pos)) {
                int end = nalu_end(data, pos + 2, length);
                printf("start:%d, end:%d\n", pos, end);
                pos += 3;
                int ret = h264_decoder_frame(decoder, data + pos, end - pos, out);
            } else {
                pos += 1;
            }
        }
        
        // h264_decoder_frame();
        return 0;
    }