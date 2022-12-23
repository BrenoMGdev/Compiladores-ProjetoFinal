#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define stacksize 5012
#define number_children 2

typedef struct {
  int position;
  char value;
} Node;

Node asa[stacksize];
char np[stacksize];

int top_asa, top_np;



void load_asa(){
	FILE *file;
  int i;

  file = fopen("asa.txt", "r");

	i = 0;
	while(fscanf(file, "%d,%c\n", &(asa[i].position), &(asa[i].value)) != EOF) ++i;

	top_asa = i - 1;

  fclose(file);
}

int find_by_position(int position) {
	int i, size_asa = top_asa + 1;

	for(i = 0; i < size_asa; ++i) {
		if(asa[i].position == position) {
			return(i);
		} else if(asa[i].position > position) {
			return(-1);
		}
	}

	return(-1);
}

void push_np(char value) {
  np[++top_np] = value;
}


void generate_np(Node father) {
	int i, position_asa, child, index_child;

	position_asa = number_children * father.position;

	child = 1;
	while(1){
		if(child > number_children) {
			break;
		}

		index_child = find_by_position(position_asa + child);

		if(index_child == -1) {
			break;
		}

		generate_np(asa[index_child]);

		++child;
	}

	push_np(father.value);
}


void end() {
  FILE *file;
  int i, size_np = top_np + 1;

  file = fopen("np.txt", "w");

  for(i = 0; i < size_np; ++i){
		fputc(np[i], file);
  }

  fclose(file);
}


int main(void) {
	top_np = -1;

	load_asa();
	generate_np(asa[0]);
	end();

	return(0);
}