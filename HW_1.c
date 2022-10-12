#include <stdio.h>
#include <stdlib.h>


void file_read(char* filename_t) //чтение из файла
{
int buffer_symbol;
FILE* file_read = fopen(filename_t,"r");
  
        if (file_read!=NULL)
           {
             printf("-----------Text from file--------\n\n");
             while(1)
             {
                buffer_symbol = fgetc(file_read);
                printf("%c",buffer_symbol);

                if(buffer_symbol==EOF)
                {
                  if(feof(file_read)!=0)
                  {
                    printf("\n");
                    break;

                  }
                  else
                  {
                    printf("error to read file\n");
                    break;
                  }

                }
             }
            
            }
        else
        {
          printf("-----Error to read file-----\n");
          exit(1);
        }
   fclose(file_read);

}
int main (int argc,char *argv[]){
	if (argc!=2)
		printf("try zipjpeg file-name\n");

file_read(argv[1]);
return 0;
}
