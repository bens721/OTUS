#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_SIZE 255
#define READ1B fread(&buffer, sizeof(uint8_t), 1, file)  
#define ERROR_READ                                                             \
  printf("error to read file");                                                \
  exit(1)

static uint8_t buffer; 


bool file_names(FILE *file, uint8_t buffer) {
  fseek(file, 0, SEEK_SET);
  size_t counter = 0; 
  uint16_t filename_len;
  uint8_t *filename = (uint8_t *)calloc(MAX_NAME_SIZE, sizeof(uint8_t));
  if (filename == NULL){
    printf("allocated error");
    exit(1); 
    }
  while (READ1B != 0) {   //чтение по одному байту, и сравнение с сигнатурой     
    if (buffer == 0x50) {
      if (READ1B <= 0) {
        ERROR_READ;
      }
      if (buffer == 0x4B) {
        if (READ1B <= 0) {
          ERROR_READ;
        }
        if (buffer == 0x01) {
          if (READ1B <= 0) {
            ERROR_READ;
          }
          if (buffer == 0x02) {
            counter++;
            fseek(file, 24, SEEK_CUR);    //смещаемся на 24 байта,для нахождения длины имени файла                                    
             if (fread(&filename_len, sizeof(uint16_t), 1, file) <= 0) {
              ERROR_READ;
            }        
              fseek(file, 16, SEEK_CUR);    //смещаемся на 16 байт,читаем имя, выводим на экран                                    
              for (size_t i = 0; i <= filename_len; i++) {
                filename[i] = fgetc(file);
              }
              printf("filename %lu: ", counter);
              for (size_t i = 0; i <= filename_len; i++) {
                printf("%c", filename[i]);
              }
              printf("\n");
              memset(filename,'0',filename_len);                       
          }
        }
      }
    }
  }
  free(filename);
  return true;
}

                                        
bool zip_check(FILE *file, uint8_t buffer) { 
    fseek(file, -200, SEEK_END); 
  while (READ1B != 0) {   //чтение по одному байту, и сравнение с сигнатурой          
    if (buffer == 0x50) {
      if (READ1B <= 0) {
        ERROR_READ;
      }
      if (buffer == 0x4B) {
        if (READ1B <= 0) {
          ERROR_READ;
        }
        if (buffer == 0x05) {
          if (READ1B <= 0) {
            ERROR_READ;
          }
          if (buffer == 0x06) {
            return true;
          }
        }
      }
    }
  }
  return false;
}


bool jpg_check(FILE *file, uint8_t buffer) {
  fseek(file, 0, SEEK_SET); 
  if (READ1B <= 0) {    //чтение по одному байту, и сравнение с сигнатурой
    ERROR_READ;
  }
  if (buffer == 0xFF) {
    if (READ1B <= 0) {
      ERROR_READ;
    }
    if (buffer == 0xD8) {
      fseek(file, -2, SEEK_END);    //смещаемся в конец файла
      if (READ1B <= 0) {
        ERROR_READ;
      }
      if (buffer == 0xFF) {
        if (READ1B <= 0) {
          ERROR_READ;
        }
        if (buffer == 0xD9) {
          return true;
        }
      }
    }
  }
  return false;
}


int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("wrong the filename, try zipjpeg filename\n");
    exit(1);
  }
  FILE *file;
  if ((file = fopen(argv[1], "rb")) != NULL) {
    if (jpg_check(file, buffer) == true && zip_check(file, buffer) == false)
      printf("This is jpg file\n");
    if (jpg_check(file, buffer) == false && zip_check(file, buffer) == true)
      file_names(file, buffer);
    if (jpg_check(file, buffer) == false && zip_check(file, buffer) == false)
      printf("unknown_file\n");
  }
  else {
    printf("not exist filename\n");
    exit(1);
  }
  fclose(file);
  return 0;
}
