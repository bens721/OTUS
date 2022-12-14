#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define READ1B \
fread(&buffer, sizeof(uint8_t), 1, file)

#define ERROR_READ\
  printf("error to read file");\
  fclose(file);\
  exit(1)\



bool file_names(FILE *file) {

  uint8_t buffer;
  size_t counter = 0;

  fseek(file, 0, SEEK_SET);
  while (READ1B != 0) { //чтение по одному байту, и сравнение с сигнатурой
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
            fseek(file, 24, SEEK_CUR); //смещаемся на 24 байта для определения
                                       //размера имени файла
            uint16_t filename_len;
            if (fread(&filename_len, sizeof(uint16_t), 1, file) <= 0){
              ERROR_READ;
            }
            uint8_t filename[filename_len+1];
            fseek(file, 16, SEEK_CUR); //смещаемся на 16 байт и читаем имя
                                       //файла, выводим на экран
            if (fread(filename, filename_len, 1, file) <= 0) {
              ERROR_READ;
            }
            counter++;
            printf("filename %lu: ", counter);
            printf("%.*s\n",filename_len,filename);
          }
        }
      }
    }
  }
  return true;
}


bool zip_check(FILE *file) {
  
  uint8_t buffer = 0;
  fseek(file, -200, SEEK_END); //ищем в конце файла нужную сигнатуру
  while (READ1B != 0) { //чтение по одному байту, и сравнение с сигнатурой
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


bool jpg_check(FILE *file) {
  
  uint8_t buffer = 0;
  fseek(file, 0, SEEK_SET); //ищем в начале файла нужную сигнатуру

  if (READ1B <= 0) { //чтение по одному байту, и сравнение с сигнатурой
    ERROR_READ;
  }
  if (buffer == 0xFF) {
    if (READ1B <= 0) {
      ERROR_READ;
    }
    if (buffer == 0xD8) {
      fseek(file, -2, SEEK_END); //смещаемся в конец файла
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
    if (jpg_check(file) == true && zip_check(file) == false)
      printf("This is jpg file\n");
    if (jpg_check(file) == false && zip_check(file) == true)
      file_names(file);
    if (jpg_check(file) == false && zip_check(file) == false)
      printf("unknown_file\n");
  }
  else {
    printf("not exist filename\n");
    exit(1);
  }
  fclose(file);
  return 0;
}
