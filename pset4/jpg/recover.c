/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recover JPEG's image from a SD card.
 */
       
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t  BYTE;

typedef struct
{
    BYTE block[512];
}JPEGBODY;

int main(void)
{
    int count = 0;
    int open;
    char image[8];
    FILE* img = 0;
    
    // open input file 
    FILE* file = fopen("card.raw", "r");
    if (file == NULL)
    {
        printf("Could not open card.raw.\n");
        return 1;
    }
    
    
    //read card.raw chunks
    JPEGBODY cf;
    do
    {
        //checking for JPEG signature
        if(cf.block[0] == 0xff && cf.block[1] == 0xd8 && cf.block[2] == 0xff && (cf.block[3] >= 0xe0 && cf.block[3] <= 0xef))
        {
            if(open != 1)
            {
                // open output file
                sprintf(image, "%03i.jpg", count);
                
                img = fopen(image, "w");
                if (img == NULL)
                {
                    fprintf(stderr, "Could not create %s.\n", image);
                    return 2;
                }
            
                //write each block of memory into img file
                fwrite(&cf, sizeof(JPEGBODY), 1, img);
                count++;
                open = 1;
            }
            else
            {
                fclose(img);
                
                // open output file
                sprintf(image, "%03i.jpg", count);
                
                img = fopen(image, "w");
                if (img == NULL)
                {
                    fprintf(stderr, "Could not create %s.\n", image);
                    return 2;
                }
            
                //write each block of memory into img file
                fwrite(&cf, sizeof(JPEGBODY), 1, img);
                count++;
            }
        }
        else if(open == 1)
        {
            //write each block of memory into img file
            fwrite(&cf, sizeof(JPEGBODY), 1, img);
        }
    }
    while(fread(&cf, sizeof(JPEGBODY), 1, file) != 0);
    
    //close image
    fclose(img);
    
    // close infile
    fclose(file);
    
    // that's all folks
    return 0;
}