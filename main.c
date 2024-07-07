#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef enum {
  SEMI,
  OPEN_PAREN,
  CLOSE_PAREN
} TypeSeparator;

typedef enum {
  EXIT
} TypeKeyword;

typedef enum {
  INT
} TypeLyteral;

typedef struct {
  TypeSeparator type;  
} TokenSeparator;

typedef struct {
  TypeKeyword type;
} TokenKeyword;

typedef struct {
  TypeLyteral type;
  char *value;
} TokenLyteral;

TokenLyteral *generate_number(char *current, int *index) {
  TokenLyteral *token = malloc(sizeof(TypeLyteral)); 
  token->type = INT;
  char *value = malloc(sizeof(char) * 8);
  int value_index = 0;

  while (isdigit(current[*index]) && current[*index] != '\0') {
    if (!isdigit(current[*index])) { break; }
    value[value_index] = current[*index];
    value_index++;
    *index += 1;
  }

  token->value = value;
  return token;
}

TokenKeyword *generate_keyword(char *current, int *index) {
  TokenKeyword *keyword = malloc(sizeof(TokenKeyword));
  char *value = malloc(sizeof(char) * 8);
  int value_index = 0;

  while (isalpha(current[*index]) && current[*index] != '\0') {
    value[value_index] = current[*index];
    value_index++;
    *index += 1;
  }

  if (strcmp(value, "exit") == 0) {
    printf("%s\n", value);
    keyword->type = EXIT;
  }

  return keyword;
}

void lexer(FILE *file) {
  int lenght = 0;
  char *buffer = 0;
  fseek(file, 0, SEEK_END);
  lenght = ftell(file);
  fseek(file, 0, SEEK_SET);
  buffer = malloc(sizeof(char) * lenght);
  fread(buffer, 1, lenght, file);
  fclose(file);
  buffer[lenght + 1] = '\0';
  char *current = malloc(sizeof(char) * lenght + 1);
  current = buffer;
  int index = 0;

  while (current[index] != '\0') {
    if (current[index] == ';') {
      printf("FOUND SEMICOLON\n");
    } else if (current[index] == '(') {
      printf("FOUND OPEN PAREN\n");
    } else if (current[index] == ')') {
      printf("FOUND CLOSE PAREN\n");
    } else if (isdigit(current[index])) {
      TokenLyteral *test_token = generate_number(current, &index);
      printf("TEST TOKEN VALUE: %s\n", test_token->value);
    } else if (isalpha(current[index])) {
      TokenKeyword *test_keyword = generate_keyword(current, &index);
      printf("TEST KEYWORD: %d\n", test_keyword->type);
    }
    index++;
  }
}

int main() {

  FILE *file;
  char file_name[9] = "test.unn";
  file = fopen(file_name, "r");
  if (file == NULL) {
    perror("ERROR WITH OPENING FILE\n");
    exit(1);
  }
  lexer(file);

}