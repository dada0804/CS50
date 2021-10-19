#include <stdio.h>
#include <stdlib.h>
 
int main(int argc, char *argv[])
{
    typedef uint8_t BYTE;
    if (argsc!=2)
    {
        printf("You need to give me one file to process\n");
        return 1;
    }
    
    FILE *file = fopen(argv[1],'r');
    if (file == NULL)
    {
        printf("This file cannot be opened\n");
        return 1;
    }
    
    
    BYTE buffer[3];
    
    while (fread(&buffer, sizeof(BYTE),3, source))
    {
       
         if(bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff)
         {
             fwrite(&buffer, sizeof(BYTE),1,sprintf(buffer, "%3f.jpg",i) )
         }
    }
    
    BYTE bytes[512];
    fread(bytes, sizeofBYTE,3,file);
    
   
    {
        FILE *destination = fopen(output, "w")
        
    }
    
    
 
}