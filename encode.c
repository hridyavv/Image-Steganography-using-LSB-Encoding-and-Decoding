#include <stdio.h>
#include <string.h>
#include "encode.h"
#include "types.h"
#include "common.h"
int secret_file_size;

/* Function Definitions */
Status read_and_validate_encode_args(char *argv[], EncodeInfo *encInfo)
{
    //step1: collect argv[2] and check the extension is ".bmp" or not
    if( !strcmp(strstr(argv[2],"."),".bmp" ))
    {
        //      : If yes -> Storing argv[2] into src_image_fname and goto step 2
        encInfo -> src_image_fname = argv[2];
        //STEP2 : Collect argv[3] and check the extension is .txt or not
        if(!strcmp(strstr(argv[3],"."),".txt"))
        {
            //    : If yes -> Storing argv[3] into secret_fname and ".txt" into extn_secret_ file[] then Goto STEP3
            encInfo -> secret_fname = argv[3];
            strcpy( encInfo -> extn_secret_file,".txt");
            //STEP3: check argv[4] passsed or not
            if(argv[4] != NULL)
            {
                //     : If yes -> Check extension is ".bmp" or not
                if(!strcmp(strstr(argv[4], "."), ".bmp"))
                {
                    //    : If yes -> Store argv[4] into stego_image_fname and return e_success
                    encInfo -> stego_image_fname = argv[4];
                    return e_success;
                }
                else
                {
                    //     : else -> e_failure
                    return e_failure;
                }
            }
            else
            {
                //     :else(STEP3)  -> Create default filename and store in to stego_image_fname and  return e_success
                char *f1 = "output.bmp" ;
                encInfo -> stego_image_fname = f1;
                printf("INFO : Output file not mentioned, default file is created\n");
                return e_success;

            }
        }
        else
        {
            //    : else(STEP2) -> return e_failure
            return e_failure;
        }
    }
    else
    {
        //     : else(STEP1) -> return_e_failure
        return e_failure;
    }
}



Status do_encoding(EncodeInfo *encInfo)
{
    //All the function call
    if(open_files(encInfo) == e_success)
    {
        printf("\nINFO : Files are opened successfuly\n");
        //Goto STEP1:
        //STEP1 : call  the check_capacity()
        //      : success -> Goto STEP2 , failure -> return e_failure.
        if(check_capacity(encInfo) == e_success)
        {
            printf("INFO : We have enough space\n");
            //STEP2 : copy_bmp_header(encInfo -> fptr_src_image , encInfo -> fptr_stego_image)
            if(copy_bmp_header(encInfo -> fptr_src_image , encInfo -> fptr_stego_image) == e_success)
            {
                 //      : check returning success or failure
                //      : success -> Goto STEP3,failure ->return e_failure
                printf("INFO : bmp header successfuly copied\n");
                //STEP3 : call encode_magic_string(MAGIC_STRING,encInfo -> fptr_src_image, encInfo -> fptr_stego_image )
                if(encode_magic_string(MAGIC_STRING,encInfo -> fptr_src_image , encInfo ->fptr_stego_image)== e_success)
                {
                    //      :check returning success or failure
                    //      : success -> Goto STEP4 ,failure -> return e_failure
                    printf("INFO : magic string successfuly encoded\n");
                    //STEP4 : encode_secret_file_extn_size(size_of_extn,envInfo -> fptr_src_image, encInfo -> fptr_stego_image)
                    if(encode_secret_file_extn_size(4,encInfo -> fptr_src_image , encInfo -> fptr_stego_image)==e_success)
                    {
                         //      : Check returning success or failure
                        //      : success ->Goto STEP5 ,failure ->return e_failure
                        printf("INFO : secret file extension size successfuly encoded\n");
                        //STEP5 : Call encode_secret_file_extn(encInfo -> extn_secret_file ,encInfo -> fptr_src_image , encInfo -> fptr_stego_image)
                        if(encode_secret_file_extn(encInfo ->extn_secret_file , encInfo ->fptr_src_image , encInfo ->fptr_stego_image)==e_success)
                        {
                             //      : Check returning success or failure
                            //      : success ->Goto STEP6 ,failure ->return e_failure.
                            printf("INFO : secret file extension successfuly encoded\n");
                            //STEP6 : Call encode_secret_file_size(secret_file_size,encInfo -> fptr_src_image , encInfo ->fptr_stego_image)
                            if(encode_secret_file_size(secret_file_size , encInfo -> fptr_src_image , encInfo -> fptr_stego_image) == e_success)
                            {
                                //      : Check returning success or failure
                                //      : success ->Goto STEP7 ,failure ->return e_failure.
                                printf("INFO : secret file size successfuly encoded\n");
                                //STEP7 :Call encode_secret_file_data(encInfo -> fptr_secret, encInfo -> fptr_src_image, encInfo -> fptr_stego_image)
                                if(encode_secret_file_data( encInfo ->fptr_secret, encInfo ->fptr_src_image , encInfo -> fptr_stego_image) ==e_success)
                                {
                                    //      : Check returning success or failure
                                    //      : success ->Goto STEP8 ,failure ->return e_failure.
                                    printf("INFO : secret file data successfuly encoded\n");
                                    //STEP8 : Call copy_remaining_img_data(encInfo -> fpte_src_image, encInfo -> fptr_stego_image);
                                    if(copy_remaining_img_data ( encInfo -> fptr_src_image ,encInfo ->fptr_stego_image) == e_success)
                                    {
                                        //      : Check returning success or failure
                                        //      : success ->Goto STEP9 ,failure ->return e_failure.
                                        printf("INFO : remaining data successfuly copies\n");
                                    }
                                    else
                                    {
                                        //failure -> return e_failure
                                        printf("remaining data is not copied");
                                        return e_failure;
                                    }
                                }
                                else
                                {
                                    //failure -> return e_failure
                                    printf("encoding of secret file data failes");
                                    return e_failure;

                                }
                            }
                            else
                            {
                                //failure -> return e_failure
                                printf("encoding of secret file size failed");
                                return e_failure;
                            }
                        }
                        else
                        {
                            //failure -> return e_failure
                            printf("encoding of secret file extension failed");
                            return e_failure;
                        }
                    }
                    else
                    {
                        //failure -> return e_failure
                        printf("encoding of secret file extension size failed");
                        return e_failure;
                    }
                }
                else
                {
                    //failure -> return e_failure
                    printf("encoding of magic string failed");
                    return e_failure;
                }
            }
            else
            {
                //failure -> return e_failure
                printf("bmp header not copied");
                return e_failure;
            }
        }
        else
        {
            //failure -> return e_failure
            printf("INFO :We dont have enough space\n");
            return e_failure;
        }
    }
    else
    {
        //failure -> return e_failure
        printf("INFO : Files opening failed\n");
        return e_failure;

    }
    //STEP9 : return e_success
    return e_success;
}


Status check_capacity(EncodeInfo *encInfo)
{
    //STEP1 : Find the size of source_image and store into image capacity(struct member)
    encInfo -> image_capacity = get_image_size_for_bmp( encInfo -> fptr_src_image);
    //STEP2 : Find the size of secret file
    secret_file_size = get_file_size(encInfo -> fptr_secret);
    //STEP3 : Compare image capacity > (magic string(16) + size_of_extn(32)+ Extn(32) + File_size(32) + file_data(file size * 8) + header(54))
    if(encInfo -> image_capacity > 54 +16 +32 +(strlen(encInfo -> extn_secret_file)*8) + 32 + (secret_file_size *8))
    {
        return e_success;
    }
    else
    {
        return e_failure;
    }
}
Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_stego_image)
{
    char buffer[54];
    //STEP1: rewind the source image file pointer
    rewind(fptr_src_image);
    //STEP2:Read 54 byte of data from source image
    fread(buffer ,54,1,fptr_src_image);
    //STEP3:Write 54 bytes of data to stego image
    fwrite(buffer,54,1,fptr_stego_image);
    return e_success;


}
Status encode_magic_string(char *magic_string , FILE *fptr_src_image, FILE *fptr_stego_image)
{
    encode_data_to_image( magic_string , fptr_src_image , fptr_stego_image);
    return e_success;
}
Status encode_data_to_image(char *data , FILE *fptr_src_image , FILE *fptr_stego_image)
{
    char image_buffer[8] ;
    //STEP1 : Read 8 bytes of data from source image ->image_buffer[8]
    for(int i=0;i<strlen(data);i++)
    {
        fread(image_buffer, 8, 1,fptr_src_image);
        //STEP2 : call the encode_byte_to_lsb
        encode_byte_to_lsb(data[i], image_buffer);
        //STEP3 : Write the encode data into stego_image.
        fwrite(image_buffer, 8,1,fptr_stego_image);
        //STEP4 : Repeat by no.of character of data times.
    }
}
Status encode_byte_to_lsb(char ch, char *buffer)
{
    //Encode process
    //STEP1 : get a bit from ch
    for(int i=0;i<8;i++)
    {
        int res = ch&(1<<i);
        res= res>>i;
        //STEP2 : clear LSB of buffer[0]
        buffer[i] = buffer[i] & ~(-1);
        //STEP3 : replace the got bit into buffer[0]
        buffer[i] = buffer[i] |res;
        //STEP4 : repeat it 8 times
    }
}
Status encode_secret_file_extn_size( int extn_size , FILE *fptr_src_image , FILE *fptr_stego_image)
{
    char image_buffer[32];
    //STEP1 : Read 32 bytesog data from source image.
    fread(image_buffer,32,1,fptr_src_image);
    //STEP2: Call the encode_size_to_lsb
    encode_size_to_lsb(extn_size , image_buffer );
    //STEP3 : Write 32 bytes to image_stego);
    fwrite(image_buffer,32,1,fptr_stego_image);
    return e_success;
}
Status encode_size_to_lsb(int size ,char *buffer)
{
    //STEP1 : Get a bit from size
    for(int i=0;i<32;i++)
    {
        int res = size & (1<<i);
        res =res>>i;
    //STEP2 : Clear the LSB of buffer[0]
        buffer[i] = buffer[i] & ~(1);

    //STEP3 : Repalce the got bit into buffer[0]
        buffer[i] = buffer[i] | res;
    }
    //STEO4 : Repeat 32 times.
}
Status encode_secret_file_extn( char *extn,FILE *fptr_src_image,FILE *fptr_stego_image)
{
    encode_data_to_image(extn , fptr_src_image, fptr_stego_image);
    return e_success;
}
Status encode_secret_file_size( int size, FILE *fptr_src_image,FILE *fptr_stego_image)
{
    char buffer[32];
    //Read 32 bytes of data from src_image and store into buffer
    fread(buffer , 32 ,1 ,fptr_src_image);
    encode_size_to_lsb(size,buffer);
    //Write the buffer into stego_image
    fwrite(buffer, 32,1,fptr_stego_image);
    return e_success;
}
Status encode_secret_file_data(FILE *fptr_secret, FILE *fptr_src_image,FILE *fptr_stego_image)
{
    char buffer[secret_file_size];
    //STEP1: Rewind the fptr_secret
    rewind(fptr_secret);
    //STEP2: Read secret_file_size data from fptr_secret and store into buffer
    fread(buffer , secret_file_size, 1, fptr_secret);
    encode_data_to_image(buffer ,fptr_src_image , fptr_stego_image);
    return e_success;
}
Status copy_remaining_img_data(FILE *src_image ,FILE *stego_image)
{
    char ch;
    while(fread(&ch, 1, 1,src_image) != 0)
    {
        fwrite(&ch, 1, 1 , stego_image);
    }
    return e_success;
}

/* Get image size
 * Input: Image file ptr
 * Output: width  * height * bytes per pixel (3 in our case)
 * Description: In BMP Image, width is stored in offset 18
 * and height after that. size is 4 bytes
 */

uint get_image_size_for_bmp(FILE *fptr_image)
{
    uint width, height;
    // Seek to 18th byte
    fseek(fptr_image, 18, SEEK_SET);


    // Read the width (an int)
    fread(&width, sizeof(int), 1, fptr_image);
    printf("width = %u\n", width);

    // Read the height (an int)
    fread(&height, sizeof(int), 1, fptr_image);
    printf("height = %u\n", height);

    // Return image capacity

    return width * height * 3;

}
uint get_file_size( FILE *fptr_secret)
{
    fseek( fptr_secret,0, SEEK_END);
    return ftell(fptr_secret);
    //find the size of secret file
}

/*
 * Get File pointers for i/p and o/p files
 * Inputs: Src Image file, Secret file and
 * Stego Image file
 * Output: FILE pointer for above files
 * Return Value: e_success or e_failure, on file errors
 */
Status open_files(EncodeInfo *encInfo)
{
    // Src Image file
    encInfo->fptr_src_image = fopen(encInfo->src_image_fname, "r");
    // Do Error handling
    if (encInfo->fptr_src_image == NULL)
    {
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->src_image_fname);

        return e_failure;
    }

    // Secret file
    encInfo->fptr_secret = fopen(encInfo->secret_fname, "r");
    // Do Error handling
    if (encInfo->fptr_secret == NULL)
    {
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->secret_fname);

        return e_failure;
    }

    // Stego Image file
    encInfo->fptr_stego_image = fopen(encInfo->stego_image_fname, "w");
    // Do Error handling
    if (encInfo->fptr_stego_image == NULL)
    {
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->stego_image_fname);

        return e_failure;
    }

    // No failure return e_success
    return e_success;
}
