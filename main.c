/*
Name: HRIDYA V V
Date: 5/1/2024
Description: Steganography Project
*/
#include <stdio.h>
#include<string.h>
#include "encode.h"
#include "decode.h"
#include "types.h"

/* Command line arguments are collected */
int main(int argc, char *argv[])
{
    /*Function calling for checking operation type and storing in res */
    int res = check_operation_type(argv);
    //STEP1 : Check the res is e_encode or not
    //      : if yes ->
    if(res == 0)
    {
        printf("Encode\n");
        /* Structure variable */
        EncodeInfo encInfo;
	/*Function calling read and validate and checking wheater the function return successfully */
        if (read_and_validate_encode_args(argv, &encInfo) == e_success)
        {
	    /*Function calling for encoding */
            do_encoding(&encInfo);
	    //print some msg
	    printf("<<<----ENCODING COMPLETED---->>>\n");
           
        }
    //      : else ->Goto STEP2

    //STEP2 : Check the is e_decode or not.
    //      : if yes -> Print some msg
    //      : else -> Goto STEP3

    //STEP3 : Print un_supported
    }
    else if(res == 1)
    {
        printf("INFO: Decoding selected\n");
        DecodeInfo decInfo;
        if (read_and_validate_decode_args(argv, &decInfo,argc) == e_success)
        {
	    /* Function calling for decoding */
            do_decoding(&decInfo);
	    //print some msg
	    printf("<<<----DECODING COMPLETED---->>>\n");
        }
    }
    else
    {
        printf("Unsupported");
    }
    return 0;
}

OperationType check_operation_type(char *argv[])
{
    //STEP1 : Check argv[1] is equal to "-e" or not
    //      : yes -> return e_encode
    //      else -> Goto STEP2

    //STEP2 : Check argv{1} is equal to "-d" or not
    //      : if yes -> return e_decode
    //      : else -> return e_unsupported
    int i = 0;
    if(strcmp(argv[1],"-e") == 0)
    {
        return e_encode;
    }
    else if(strcmp(argv[1],"-d") == 0)
    {
        return e_decode;
    }
    else
    {
        return e_unsupported;
    }


}
