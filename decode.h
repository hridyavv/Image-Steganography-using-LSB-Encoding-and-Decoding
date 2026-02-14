#ifndef DECODE_H
#define DECODE_H

#include "types.h" // Contains user defined types

/*
 * Structure to store information required for
 * decoding  src_decode to new file
 * Info about output and intermediate data is
 * also stored
 */
/*Get file extension size by decoding 32 bytes*/
#define DECODE_FILE_EXTN_SIZE 32
/*Get file size by decoding 32 bytes*/
#define DECODE_FILE_SIZE 32

typedef struct _DecodeInfo
{
    /* src_decode info */
    char *src_decode;     //name of image
    FILE *fptr_src_decode;
    int extn_size;    //address of file
    int txt_size;
    char dest_name[30];
    char *d;
    FILE *file;
} DecodeInfo;


/* Read and validate Encode args from argv */
Status read_and_validate_decode_args(char *argv[], DecodeInfo *decInfo,int argc);
/* Perform the decoding */
Status do_decoding(DecodeInfo *decInfo);
/*Store magic string*/
Status decode_magic_string(const char *magic_string,FILE *fptr_src_image);
/*Decode secret file extension size */
Status decode_secret_file_extn_size(DecodeInfo *decInfo);
/*Decode secret file extn */
Status decode_secret_file_extn(DecodeInfo *decInfo);
/* dest open */
Status dest_open(DecodeInfo *decInfo);
/* Decode secret file size */
Status decode_secret_file_size(DecodeInfo *decInfo);
/*Decode secret file data*/
Status decode_secret_file_data(DecodeInfo *decInfo);
#endif
