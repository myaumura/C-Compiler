#include <stdio.h>
#include <stdlib.h>

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
  int value;
} TokenLyteral;

int main() {
 FILE *file;
 file = fopen("test.unn", "r");
 char current = fgetc(file);

 while (current != EOF) {
  printf("%c", current);
  current = fgetc(file);
 }
}
