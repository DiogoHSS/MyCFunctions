#include <stdio.h>  /* fputs stdout fgetc stdin fgets */
#include <stdlib.h> /* strtol malloc */
#include <string.h> /* strlen strcspn strncpy */

void print(const char *text) { fputs(text, stdout); }

void println(const char *text) {
  fputs(text, stdout);
  fputs("\n", stdout);
}

void clean_stdin() {
  char c = 0;

  while ((c = (char)fgetc(stdin)) != EOF && c != '\n')
    ;
}

int read_int(const char *output, int *input, const int *validate,
             int validate_size) {
  const int INT_OVERFLOW_DIGITS = 12;
  char buffer[INT_OVERFLOW_DIGITS];
  int valid = 0;
  char *pEnd = 0;

  print(output);
  print(": ");

  if (!fgets(buffer, (int)sizeof(buffer), stdin))
    return 1;

  *input = (int)strtol(buffer, &pEnd, 10);

  if (validate_size < 1)
    valid = 1;
  for (int i = 0; i < validate_size; ++i) {
    if (*input == validate[i])
      valid = 1;
  }

  if (!valid)
    return 1;

  return 0;
}

int read_char(const char *output, char *input, const char *validate,
              int validate_size) {
  int valid = 0;

  print(output);
  print(": ");

  *input = (char)fgetc(stdin);
  clean_stdin();

  if (validate_size < 1)
    valid = 1;
  for (int i = 0; i < validate_size; ++i) {
    if (*input == validate[i])
      valid = 1;
  }

  if (!valid)
    return 1;

  return 0;
}

int read_string(const char *output, char **input, int size_of_buffer) {
  char buffer[size_of_buffer];
  print(output);
  print(": ");
  if (!fgets(buffer, (int)sizeof(buffer), stdin))
    return 1;

  int tamanho = (int)strlen(buffer);
  int newline = (int)strcspn(buffer, "\n");
  if (newline == tamanho)
    clean_stdin();
  if (tamanho < 2)
    return 1;
  buffer[newline] = '\0';
  int size_of_input = tamanho * sizeof(char);
  *input = (char *)malloc(size_of_input);
  strncpy(*input, buffer, size_of_input);

  return 0;
}
