#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define stacksize 5012
#define number_children 12

typedef struct {
  int position;
  char value;
} Node;

Node stack[stacksize];
Node tree[stacksize];

int top_stack, top_tree;
Node father;
char token, production[number_children + 1];

void pop() {
  father = stack[top_stack--];
}

void push_stack(int position, char value) {
  ++top_stack;
  stack[top_stack].position = position;
  stack[top_stack].value = value;
}

void push_tree(int position, char value) {
  ++top_tree;
  tree[top_tree].position = position;
  tree[top_tree].value = value;
}

void push() {
  int i, position, len_production = strlen(production);

  Node array_aux[len_production];

  if(strcmp(production, "S")) {
    position = number_children * father.position + 1;
  } else {
    position = 0;
  }

  for(i = 0; i < len_production; ++i){
    array_aux[i].position = position + i;
    array_aux[i].value = production[i];
  }

  for(i = 0; i < len_production; ++i){
    push_tree(array_aux[i].position, array_aux[i].value);
  }

  for(i = len_production - 1; i >= 0; --i){
    push_stack(array_aux[i].position, array_aux[i].value);
  }
}

void error(){
  printf("\nERROR - Word does not accept!\n");
  
  exit(0);
}

int comparator(const void *a, const void *b) {
  Node *item_1 = (Node *)a;
  Node *item_2 = (Node *)b;

  return (item_1->position - item_2->position);
}

void end() {
  FILE *file;
  int i, size_tree = top_tree + 1;

  qsort(tree, size_tree, sizeof(Node), comparator);

  file = fopen("ada.txt", "w");

  for(i = 0; i < size_tree; ++i){
    fprintf(file, "%d,%c\n", tree[i].position, tree[i].value);
  }

  fclose(file);

  exit(0);
}

int main(void) {
  int position;
  top_stack = top_tree = position = -1;

  q0:
    strcpy(production, "S");
    push();

    if(scanf("%c", &token) == EOF) {
      error();
    }

    goto q1;

  q1:
    if(stack[top_stack].value == 'S') {
      if(token == 'm') {
        pop();

        strcpy(production, "M");
        push();
      } else if(token == 'g') {
        pop();
        
        strcpy(production, "GM");
        push();
      } else if(token == 'n') {
        pop();

        strcpy(production, "NGM");
        push();
      } else {
        error();
      }

      goto q1;
    } else if(stack[top_stack].value == 'N' && token == 'n') {
      pop();

      strcpy(production, "n(){A;r(E);}");
      push();

      goto q1;
    } else if(stack[top_stack].value == 'G' && token == 'g') {
      pop();
      
      strcpy(production, "g(){A;r(E);}");
      push();

      goto q1;
    } else if(stack[top_stack].value == 'M' && token == 'm') {
      pop();

      strcpy(production, "m(){A;r(E);}");
      push();

      goto q1;
    } else if(stack[top_stack].value == 'A') {
      pop();

      strcpy(production, "CB");
      push();

      goto q1;
    } else if(stack[top_stack].value == 'B') {
      if(token == '.') {
        pop();

        strcpy(production, ".");
        push();
      } else if(token == ';') {
        pop();

        strcpy(production, ";CB");
        push();
      } else {
        error();
      }

      goto q1;
    } else if(stack[top_stack].value == 'E') {
      if(token == '0') {
        pop();

        strcpy(production, "0");
        push();
      } else if(token == '1') {
        pop();

        strcpy(production, "1");
        push();
      } else if(token == '2') {
        pop();

        strcpy(production, "2");
        push();
      } else if(token == '3') {
        pop();

        strcpy(production, "3");
        push();
      } else if(token == '4') {
        pop();

        strcpy(production, "4");
        push();
      } else if(token == '5') {
        pop();

        strcpy(production, "5");
        push();
      } else if(token == '6') {
        pop();

        strcpy(production, "6");
        push();
      } else if(token == '7') {
        pop();

        strcpy(production, "7");
        push();
      } else if(token == '8') {
        pop();

        strcpy(production, "8");
        push();
      } else if(token == '9') {
        pop();

        strcpy(production, "9");
        push();
      } else if(token == 'x') {
        pop();

        strcpy(production, "x");
        push();
      } else if(token == 'y') {
        pop();

        strcpy(production, "y");
        push();
      } else if(token == '(') {
        pop();

        strcpy(production, "(EXE)");
        push();
      } else {
        error();
      }

      goto q1;
    } else if(stack[top_stack].value == 'X') {
      if(token == '+') {
        pop();

        strcpy(production, "+");
        push();
      } else if(token == '-') {
        pop();

        strcpy(production, "-");
        push();
      } else if(token == '*') {
        pop();

        strcpy(production, "*");
        push();
      } else if(token == '/') {
        pop();

        strcpy(production, "/");
        push();
      } else {
        error();
      }

      goto q1;
    } else if(stack[top_stack].value == 'C') {
      if(token == 'h') {
        pop();

        strcpy(production, "h=g()");
        push();
      } else if(token == 'i') {
        pop();

        strcpy(production, "i=n()");
        push();
      } else if(token == 'j') {
        pop();

        strcpy(production, "j=E");
        push();
      } else if(token == 'k') {
        pop();

        strcpy(production, "k=E");
        push();
      } else if(token == 'z') {
        pop();

        strcpy(production, "z=E");
        push();
      } else if(token == '(') {
        pop();

        strcpy(production, "(EXE)");
        push();
      } else if(token == 'w') {
        pop();

        strcpy(production, "w(E){CD");
        push();
      } else if(token == 'f') {
        pop();

        strcpy(production, "f(E){CD");
        push();
      } else if(token == 'o') {
        pop();

        strcpy(production, "o(E;E;E){CD");
        push();
      } else {
        error();
      }

      goto q1;
    } else if(stack[top_stack].value == 'D') {
      if(token == '}') {
        pop();

        strcpy(production, "}");
        push();
      } else if(token == ';') {
        pop();

        strcpy(production, ";CD");
        push();
      } else {
        error();
      }

      goto q1;
    } else if(stack[top_stack].value == token && token == 'n') {
      pop();

      if(scanf("%c", &token) == EOF) {
        end();
      }

      goto q1;
    } else if(stack[top_stack].value == token && token == 'g') {
      pop();

      if(scanf("%c", &token) == EOF) {
        end();
      }

      goto q1;
    } else if(stack[top_stack].value == token && token == 'm') {
      pop();

      if(scanf("%c", &token) == EOF) {
        end();
      }

      goto q1;
    } else if(stack[top_stack].value == token && token == 'r') {
      pop();

      if(scanf("%c", &token) == EOF) {
        end();
      }

      goto q1;
    } else if(stack[top_stack].value == token && token == '(') {
      pop();

      if(scanf("%c", &token) == EOF) {
        end();
      }

      goto q1;
    } else if(stack[top_stack].value == token && token == ')') {
      pop();

      if(scanf("%c", &token) == EOF) {
        end();
      }

      goto q1;
    } else if(stack[top_stack].value == token && token == '{') {
      pop();

      if(scanf("%c", &token) == EOF) {
        end();
      }

      goto q1;
    } else if(stack[top_stack].value == token && token == '}') {
      pop();

      if(scanf("%c", &token) == EOF) {
        end();
      }

      goto q1;
    } else if(stack[top_stack].value == token && token == ';') {
      pop();

      if(scanf("%c", &token) == EOF) {
        end();
      }

      goto q1;
    } else if(stack[top_stack].value == token && token == '.') {
      pop();

      if(scanf("%c", &token) == EOF) {
        end();
      }

      goto q1;
    } else if(stack[top_stack].value == token && token == '0') {
      pop();

      if(scanf("%c", &token) == EOF) {
        end();
      }

      goto q1;
    } else if(stack[top_stack].value == token && token == '1') {
      pop();

      if(scanf("%c", &token) == EOF) {
        end();
      }

      goto q1;
    } else if(stack[top_stack].value == token && token == '2') {
      pop();

      if(scanf("%c", &token) == EOF) {
        end();
      }

      goto q1;
    } else if(stack[top_stack].value == token && token == '3') {
      pop();

      if(scanf("%c", &token) == EOF) {
        end();
      }

      goto q1;
    } else if(stack[top_stack].value == token && token == '4') {
      pop();

      if(scanf("%c", &token) == EOF) {
        end();
      }

      goto q1;
    } else if(stack[top_stack].value == token && token == '5') {
      pop();

      if(scanf("%c", &token) == EOF) {
        end();
      }

      goto q1;
    } else if(stack[top_stack].value == token && token == '6') {
      pop();

      if(scanf("%c", &token) == EOF) {
        end();
      }

      goto q1;
    } else if(stack[top_stack].value == token && token == '7') {
      pop();

      if(scanf("%c", &token) == EOF) {
        end();
      }

      goto q1;
    } else if(stack[top_stack].value == token && token == '8') {
      pop();

      if(scanf("%c", &token) == EOF) {
        end();
      }

      goto q1;
    } else if(stack[top_stack].value == token && token == '9') {
      pop();

      if(scanf("%c", &token) == EOF) {
        end();
      }

      goto q1;
    } else if(stack[top_stack].value == token && token == 'x') {
      pop();

      if(scanf("%c", &token) == EOF) {
        end();
      }

      goto q1;
    } else if(stack[top_stack].value == token && token == 'y') {
      pop();

      if(scanf("%c", &token) == EOF) {
        end();
      }

      goto q1;
    } else if(stack[top_stack].value == token && token == '+') {
      pop();

      if(scanf("%c", &token) == EOF) {
        end();
      }

      goto q1;
    } else if(stack[top_stack].value == token && token == '-') {
      pop();

      if(scanf("%c", &token) == EOF) {
        end();
      }

      goto q1;
    } else if(stack[top_stack].value == token && token == '*') {
      pop();

      if(scanf("%c", &token) == EOF) {
        end();
      }

      goto q1;
    } else if(stack[top_stack].value == token && token == '/') {
      pop();

      if(scanf("%c", &token) == EOF) {
        end();
      }

      goto q1;
    } else if(stack[top_stack].value == token && token == '=') {
      pop();

      if(scanf("%c", &token) == EOF) {
        end();
      }

      goto q1;
    } else if(stack[top_stack].value == token && token == 'h') {
      pop();

      if(scanf("%c", &token) == EOF) {
        end();
      }

      goto q1;
    } else if(stack[top_stack].value == token && token == 'i') {
      pop();

      if(scanf("%c", &token) == EOF) {
        end();
      }

      goto q1;
    } else if(stack[top_stack].value == token && token == 'j') {
      pop();

      if(scanf("%c", &token) == EOF) {
        end();
      }

      goto q1;
    } else if(stack[top_stack].value == token && token == 'k') {
      pop();

      if(scanf("%c", &token) == EOF) {
        end();
      }

      goto q1;
    } else if(stack[top_stack].value == token && token == 'z') {
      pop();

      if(scanf("%c", &token) == EOF) {
        end();
      }

      goto q1;
    } else if(stack[top_stack].value == token && token == 'w') {
      pop();

      if(scanf("%c", &token) == EOF) {
        end();
      }

      goto q1;
    } else if(stack[top_stack].value == token && token == 'f') {
      pop();

      if(scanf("%c", &token) == EOF) {
        end();
      }

      goto q1;
    } else if(stack[top_stack].value == token && token == 'o') {
      pop();

      if(scanf("%c", &token) == EOF) {
        end();
      }

      goto q1;
    } else {
      error();
    }

  return(0);
}