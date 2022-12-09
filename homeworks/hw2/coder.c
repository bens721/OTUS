#include <getopt.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *koi8[128] = {
    "\u2500", "\u2502", "\u250c", "\u2510", "\u2514", "\u2518", "\u251c",
    "\u2524", "\u252c", "\u2534", "\u253c", "\u2580", "\u2584", "\u2588",
    "\u258c", "\u2590", "\u2591", "\u2592", "\u2593", "\u2320", "\u25a0",
    "\u2219", "\u221a", "\u2248", "\u2264", "\u2265", "\u00a0", "\u2321",
    "\u00b0", "\u00b2", "\u00b7", "\u00f7", "\u2550", "\u2551", "\u2552",
    "\u0451", "\u2553", "\u2554", "\u2555", "\u2556", "\u2557", "\u2558",
    "\u2559", "\u255a", "\u255b", "\u255c", "\u255d", "\u255e", "\u255f",
    "\u2560", "\u2561", "\u0401", "\u2562", "\u2563", "\u2564", "\u2565",
    "\u2566", "\u2567", "\u2568", "\u2569", "\u256a", "\u256b", "\u256c",
    "\u00a9", "\u044e", "\u0430", "\u0431", "\u0446", "\u0434", "\u0435",
    "\u0444", "\u0433", "\u0445", "\u0438", "\u0439", "\u043a", "\u043b",
    "\u043c", "\u043d", "\u043e", "\u043f", "\u044f", "\u0440", "\u0441",
    "\u0442", "\u0443", "\u0436", "\u0432", "\u044c", "\u044b", "\u0437",
    "\u0448", "\u044d", "\u0449", "\u0447", "\u044a", "\u042e", "\u0410",
    "\u0411", "\u0426", "\u0414", "\u0415", "\u0424", "\u0413", "\u0425",
    "\u0418", "\u0419", "\u041a", "\u041b", "\u041c", "\u041d", "\u041e",
    "\u041f", "\u042f", "\u0420", "\u0421", "\u0422", "\u0423", "\u0416",
    "\u0412", "\u042c", "\u042b", "\u0417", "\u0428", "\u042d", "\u0429",
    "\u0427", "\u042a"};

char *cp1251[128] = {
    "\u0402", "\u0403", "\u201a", "\u0453", "\u201e", "\u2026", "\u2020",
    "\u2021", "\u20ac", "\u2030", "\u0409", "\u2039", "\u040a", "\u040c",
    "\u040b", "\u040f", "\u0452", "\u2018", "\u2019", "\u201c", "\u201d",
    "\u2022", "\u2013", "\u2014", "\ufffd", "\u2122", "\u0459", "\u203a",
    "\u045a", "\u045c", "\u045b", "\u045f", "\u00a0", "\u040e", "\u045e",
    "\u0408", "\u00a4", "\u0490", "\u00a6", "\u00a7", "\u0401", "\u00a9",
    "\u0404", "\u00ab", "\u00ac", "\u00ad", "\u00ae", "\u0407", "\u00b0",
    "\u00b1", "\u0406", "\u0456", "\u0491", "\u00b5", "\u00b6", "\u00b7",
    "\u0451", "\u2116", "\u0454", "\u00bb", "\u0458", "\u0405", "\u0455",
    "\u0457", "\u0410", "\u0411", "\u0412", "\u0413", "\u0414", "\u0415",
    "\u0416", "\u0417", "\u0418", "\u0419", "\u041a", "\u041b", "\u041c",
    "\u041d", "\u041e", "\u041f", "\u0420", "\u0421", "\u0422", "\u0423",
    "\u0424", "\u0425", "\u0426", "\u0427", "\u0428", "\u0429", "\u042a",
    "\u042b", "\u042c", "\u042d", "\u042e", "\u042f", "\u0430", "\u0431",
    "\u0432", "\u0433", "\u0434", "\u0435", "\u0436", "\u0437", "\u0438",
    "\u0439", "\u043a", "\u043b", "\u043c", "\u043d", "\u043e", "\u043f",
    "\u0440", "\u0441", "\u0442", "\u0443", "\u0444", "\u0445", "\u0446",
    "\u0447", "\u0448", "\u0449", "\u044a", "\u044b", "\u044c", "\u044d",
    "\u044e", "\u044f",
};

char *iso8859_5[128] = {
    "000000", "000000", "000000", "000000", "000000", "000000", "000000",
    "000000", "000000", "000000", "000000", "000000", "000000", "000000",
    "000000", "000000", "000000", "000000", "000000", "000000", "000000",
    "000000", "000000", "000000", "000000", "000000", "000000", "000000",
    "000000", "000000", "000000", "000000", "\u00a0", "\u0401", "\u0402",
    "\u0403", "\u0404", "\u0405", "\u0406", "\u0407", "\u0408", "\u0409",
    "\u040a", "\u040b", "\u040c", "\u00ad", "\u040e", "\u040f", "\u0410",
    "\u0411", "\u0412", "\u0413", "\u0414", "\u0415", "\u0416", "\u0417",
    "\u0418", "\u0419", "\u041a", "\u041b", "\u041c", "\u041d", "\u041e",
    "\u041f", "\u0420", "\u0421", "\u0422", "\u0423", "\u0424", "\u0425",
    "\u0426", "\u0427", "\u0428", "\u0429", "\u042a", "\u042b", "\u042c",
    "\u042d", "\u042e", "\u042f", "\u0430", "\u0431", "\u0432", "\u0433",
    "\u0434", "\u0435", "\u0436", "\u0437", "\u0438", "\u0439", "\u043a",
    "\u043b", "\u043c", "\u043d", "\u043e", "\u043f", "\u0440", "\u0441",
    "\u0442", "\u0443", "\u0444", "\u0445", "\u0446", "\u0447", "\u0448",
    "\u0449", "\u044a", "\u044b", "\u044c", "\u044d", "\u044e", "\u044f",
    "\u2116", "\u0451", "\u0452", "\u0453", "\u0454", "\u0455", "\u0456",
    "\u0457", "\u0458", "\u0459", "\u045a", "\u045b", "\u045c", "\u00a7",
    "\u045e", "\u045f",
};

bool encoding(char *table[], FILE *input, FILE *output) {
  uint8_t buffer;
  fseek(input, 0, SEEK_SET);
  while (fread(&buffer, sizeof(uint8_t), 1, input) == 1) {
    if (buffer > 0x7F) {

      if (fwrite((char *)table[buffer - 0x80], sizeof(uint8_t), 2, output) ==
          0) {
        printf("File write error\n");
        exit(1);
      }
    } else if (fwrite(&buffer, sizeof(uint8_t), 1, output) == 0) {
      printf("File write error\n");
      exit(1);
    }
  }
  if (feof(input)) {
    printf("File read done\n");
    return true;
  } else {
    printf("File read error\n");
    return false;
  }
}

int main(int argc, char *argv[]) {

  if (argc < 2 || argc == 3 || argc > 4) {
    printf("Please use -h for help\n");
    exit(1);
  }

  int result, option_index = 0;
  const struct option long_options[] = {
      {"koi8", required_argument, 0, 'k'},
      {"cp1251", required_argument, 0, 'c'},
      {"iso8859_5", required_argument, 0, 'i'},
      {"help", no_argument, 0, 'h'},
      {NULL, 0, NULL, 0}};
  const char *short_options = "k:c:i:h";
  FILE *input = NULL;
  FILE *output = NULL;
  if (argc == 4) {
    input = fopen(argv[2], "rb");
    if (!input) {
      printf("File opening error\n");
      fclose(input);
      exit(1);
    }
    output = fopen(argv[3], "w");
    if (!output) {
      printf("File opening error\n");
      fclose(output);
      exit(1);
    }
  }

  if ((result = getopt_long(argc, argv, short_options, long_options,
                            &option_index)) != -1) {

    switch (result) {

    case 'k':
      if (strcmp(argv[1], "-k") != 0 && strcmp(argv[1], "--koi8") != 0) {
        printf("Wrong option, please use -h for help\n");
        exit(1);
      }
      if (encoding(koi8, input, output))
        printf("Done encoding KOI8 to UTF8\n");
      fclose(input);
      fclose(output);
      break;
    case 'c':
      if (strcmp(argv[1], "-c") != 0 && strcmp(argv[1], "--cp1251") != 0) {
        printf("Wrong option, please use -h for help\n");
        exit(1);
      }
      if (encoding(cp1251, input, output))
        printf("Done encoding CP1251 to UTF8\n");
      fclose(input);
      fclose(output);
      break;
    case 'i':
      if (strcmp(argv[1], "-i") != 0 && strcmp(argv[1], "--iso8859_5") != 0) {
        printf("Wrong option, please use -h for help\n");
        exit(1);
      }
      if (encoding(iso8859_5, input, output))
        printf("Done encoding ISO8859_5 to UTF8\n");
      fclose(input);
      fclose(output);
      break;

    case 'h':
      if (strcmp(argv[1], "-h") != 0 && strcmp(argv[1], "--help") != 0) {
        printf("Wrong option, please use -h for help\n");
        exit(1);
      }

      printf("Please use ./coder [OPTION] <input_filename> "
             "<output_filename>\n");
      printf("-h,--help       -coder help.\n");
      printf("-k,--koi8       -koi8 decoding.\n");
      printf("-i,--iso8859_5  -iso8859_5 decoding.\n");
      printf("-c,--cp1251     -cp1251 decoding.\n");
      break;
    case '?':
      printf("Illegal option, please use -h for help\n");
      break;
    }
  } else
    printf("Please use ./coder [Option] <input_filename> "
           "<output_filename>\n");
  return 0;
}
