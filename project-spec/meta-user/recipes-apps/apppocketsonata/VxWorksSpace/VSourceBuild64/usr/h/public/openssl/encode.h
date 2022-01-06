/* encode.h -- base64 encoding/decoding functions */ 

/* Copyright 2016 Wind River Systems, Inc. */
 
/*
modification history:
---------------------
# 22aug16,l_y  Created for vx7 openssl-1.0.2h update
*/

#ifndef HEADER_ENCODE_H
#define HEADER_ENCODE_H 

typedef struct evp_Encode_Ctx_st
{
    int num;    /* number saved in a partial encode/decode */
    int length;    /* The length is either the output line length
             * (in input bytes) or the shortest input line
             * length that is ok.  Once decoding begins,
             * the length is adjusted up each time a longer
             * line is decoded */
    unsigned char enc_data[80];    /* data to encode */
    int line_num;    /* number read on current line */
    int expect_nl;
} EVP_ENCODE_CTX;


void EVP_EncodeInit(EVP_ENCODE_CTX *ctx);

void EVP_EncodeUpdate(EVP_ENCODE_CTX *ctx, unsigned char *out, int *outl,
                    const unsigned char *in, int inl);

void EVP_EncodeFinal(EVP_ENCODE_CTX *ctx, unsigned char *out, int *outl);

void EVP_DecodeInit(EVP_ENCODE_CTX *ctx);

int EVP_DecodeUpdate(EVP_ENCODE_CTX *ctx, unsigned char *out, int *outl,
         const unsigned char *in, int inl);

int EVP_DecodeFinal(EVP_ENCODE_CTX *ctx, unsigned char *out, int *outl);

#endif
