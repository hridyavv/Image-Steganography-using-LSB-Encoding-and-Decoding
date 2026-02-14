#include<stdio.h>
#include<string.h>
#include"common.h"
#include<unistd.h>
#include"types.h"
#include"decode.h"
/*Function Definitions*/
Status read_and_validate_decode_args(char *argv[],DecodeInfo *decInfo,int argc)
{
    //checking condition if argc greater than or equal to 3
    if(argc>=3)
    {
        decInfo->fptr_src_decode=fopen(argv[2],"r");
        if(decInfo->fptr_src_decode!=NULL)
        {
            return e_success;
        }
        else
        {
            return e_failure;
        }
    }
    else
    {
	//if yes print error msg
        printf("Info : Pass three arguments\n");
        return e_failure;
    }
}
Status do_decoding(DecodeInfo *decInfo)
{
    //call decode_magic_string(MAGIC_STRING, decInfo ->fptr_src_decode)
    if(decode_magic_string(MAGIC_STRING,decInfo->fptr_src_decode)==e_success)
    {
        sleep(1);
        printf("INFO: Magic string is decoded\n");
	//call decode_secret_file_extn_size(decInfo)
        if(decode_secret_file_extn_size(decInfo)==e_success)
        {
	    //call decode_secret_file_extn(decInfo)
            if(decode_secret_file_extn(decInfo)==e_success)
            {
		//call dest_open(decInfo)
                if(dest_open(decInfo)==e_success)
                {
		    //call decode_secret_file_size(decInfo)
                    if(decode_secret_file_size(decInfo)==e_success)
                    {
			//call decode_secret_file_data(decInfo)
                        if(decode_secret_file_data(decInfo)==e_success)
                        {
                            printf("Decode Completed\n");
                        }
                    }
                }
            }
        }
    }
}
Status decode_secret_file_data(DecodeInfo *decInfo)
{

    int size=decInfo->txt_size;
    char str[size];
    char buffer[8];
    int i;
    for (i=0;i<size;i++)
    {
        fread(buffer,8,1,decInfo->fptr_src_decode);
        int sum=0;
        for (int j=0;j<8;j++)
        {
            sum=((buffer[j]&1)<<j)|sum;
        }
        str[i]=sum;
    }
    fwrite(str,size,1,decInfo->file);
    printf("INFO: Secret file data decoded\n");
    return e_success;
}

Status decode_secret_file_size(DecodeInfo *decInfo)
{
    char buffer[32];
    fread(buffer,32,1,decInfo->fptr_src_decode);
    int sum=0;
    for (int i=0;i<32;i++)
    {
        if(buffer[i]&1)
        {
            sum=sum|(1<<i);
        }
    }
    decInfo->txt_size=sum;
    printf("INFO: Secret file size decoded\n");
    return e_success;
}

Status dest_open(DecodeInfo *decInfo)
{

    char str[30]="Output";
    strcat(str,decInfo->dest_name);
    decInfo->d=str;
    decInfo->file=fopen(decInfo->d,"w");
    return e_success;
}

Status decode_secret_file_extn(DecodeInfo *decInfo)
{
    int size=decInfo->extn_size;
    char str[size];
    char buffer[8];
    int i;
    for (i=0;i<size;i++)
    {
        fread(buffer,8,1,decInfo->fptr_src_decode);
        int sum=0;
        for (int j=0;j<8;j++)
        {
            sum=((buffer[j]&1)<<j)|sum;
        }
        str[i]=sum;
    }
    str[i]='\0';
    strcpy(decInfo->dest_name,str);
    printf("INFO: Secret file extension decoded\n");
    return e_success;
}
Status decode_secret_file_extn_size(DecodeInfo *decInfo)
{
    char buffer[32];
    fread(buffer,32,1,decInfo->fptr_src_decode);
    int sum=0;
    for (int i=0;i<32;i++)
    {
        if(buffer[i]&1)
        {
            sum=sum|(1<<i);
        }
    }
    decInfo->extn_size=sum;
    printf("size = %d\n",decInfo->extn_size);
    printf("INFO: Secret file extension size decoded\n");
    return e_success;
    
}

Status decode_magic_string(const char *magic_string,FILE *fptr_src_image)
{
    rewind(fptr_src_image);
    fseek(fptr_src_image,54,SEEK_SET);
    int l=strlen(magic_string);
    char buffer[8];
    char magic[l];
    int c=0;
    int i;
    for ( i=0;i<l;i++)
    {
        fread(buffer,8,1,fptr_src_image);
        char sum=0;
        for (int j=0;j<8;j++)
        {
            if(buffer[j]&1)
            {
                sum=sum|(1<<j);
            }
        }
        magic[i]=sum;
        printf("magic string = %c\n",magic[i]);
        if(magic_string[i]==sum);
        {
            c=c+1;
        }
    }
    magic[i]='\0';
    if(c==l)
    {
        return e_success;
    }
    else
    {
        return e_failure;
    }
}
