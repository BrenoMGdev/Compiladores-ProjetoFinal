#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define stacksize 5012
#define number_children 12

typedef struct {
  int position;
  char value;
} Node;

Node ada[stacksize];
Node asa[stacksize];

int top_ada, top_asa;

char syntactic_sugars[20];


char group_productions_1[3][number_children + 1] = {"n(){A;r(E);}", "g(){A;r(E);}", "m(){A;r(E);}"};
char group_productions_2[5][number_children + 1] = {"h=g()", "i=n()", "j=E", "k=E", "z=E"};
char group_productions_3[1][number_children + 1] = {"(EXE)"};
char group_productions_4[2][number_children + 1] = {"w(E){CD", "f(E){CD"};
char group_productions_5[1][number_children + 1] = {"o(E;E;E){CD"};


void load_ada(){
	FILE *file;
  int i;

  file = fopen("ada.txt", "r");

	i = 0;
	while(fscanf(file, "%d,%c\n", &(ada[i].position), &(ada[i].value)) != EOF) ++i;

	top_ada = i - 1;

  fclose(file);
}

int find_by_position(int position) {
	int i, size_ada = top_ada + 1;

	for(i = 0; i < size_ada; ++i) {
		if(ada[i].position == position) {
			return(i);
		} else if(ada[i].position > position) {
			return(-1);
		}
	}

	return(-1);
}

void push_asa(int position, char value) {
  ++top_asa;
  asa[top_asa].position = position;
  asa[top_asa].value = value;
}

int comparator(const void *a, const void *b) {
  Node *item_1 = (Node *)a;
  Node *item_2 = (Node *)b;

  return (item_1->position - item_2->position);
}

int is_syntactic_sugar(Node current_node) {
	int i = 0, length = strlen(syntactic_sugars);

	for(i = 0; i < length; ++i) {
		if(current_node.value == syntactic_sugars[i]) {
			return(1);
		}
	}

	return(0);
}

void generate_asa(Node father, int position_asa) {
	int i, position_ada, child, index_child;
	Node production[number_children];
	char production_str[number_children];

	position_ada = number_children * father.position;

	strcpy(production_str, "");

	child = 1;
	while(1){
		if(child > number_children) {
			break;
		}

		index_child = find_by_position(position_ada + child);

		if(index_child == -1) {
			break;
		}

		production[child - 1].position = ada[index_child].position;
		production[child - 1].value = ada[index_child].value;
		production_str[child - 1] = ada[index_child].value;

		++child;
	}

	production_str[child - 1] = '\0';

	for(i = 0; strcmp(production_str, group_productions_1[i]) && i < 3; ++i);
	if(i != 3) {
		push_asa(position_asa, production[0].value);

		position_asa = 2 * position_asa;

		generate_asa(production[4], ++position_asa);

		push_asa(++position_asa, production[6].value);

		position_asa = 2 * position_asa;

		generate_asa(production[8], ++position_asa);
	} else {
		for(i = 0; strcmp(production_str, group_productions_2[i]) && i < 5; ++i);
		if(i != 5) {
			push_asa(position_asa, production[1].value);

			position_asa = 2 * position_asa;

			push_asa(++position_asa, production[0].value);

			if(production_str[2] == 'E') {
				generate_asa(production[2], ++position_asa);
			} else {
				push_asa(++position_asa, production[2].value);
			}
		} else {
			if(strcmp(production_str, group_productions_3[0]) == 0) {
				generate_asa(production[2], position_asa);

				position_asa = 2 * position_asa;

				generate_asa(production[1], ++position_asa);

				generate_asa(production[3], ++position_asa);
			} else {
				for(i = 0; strcmp(production_str, group_productions_4[i]) && i < 2; ++i);
				if(i != 2) {
					push_asa(position_asa, production[0].value);

					position_asa = 2 * position_asa;

					generate_asa(production[2], ++position_asa);

					generate_asa(production[5], ++position_asa);

					position_asa = 2 * asa[top_asa].position;

					generate_asa(production[6], ++position_asa);
				} else {
					if(strcmp(production_str, group_productions_5[0]) == 0) {
						push_asa(position_asa, production[0].value);

						position_asa = 2 * position_asa;

						generate_asa(production[4], ++position_asa);

						generate_asa(production[2], ++position_asa);

						position_asa = 2 * position_asa;

						generate_asa(production[6], ++position_asa);

						position_asa = 2 * position_asa;

						generate_asa(production[9], ++position_asa);

						position_asa = 2 * position_asa;

						generate_asa(production[10], ++position_asa);
					} else {
						child = 1;
						while(1){
							if(child > number_children) {
								break;
							}

							index_child = find_by_position(position_ada + child);

							if(index_child == -1) {
								break;
							}

							if(is_syntactic_sugar(ada[index_child])) {
								generate_asa(ada[index_child], position_asa);
							} else {
								push_asa(position_asa, ada[index_child].value);
							}

							++child;
						}
					}
				}
			}
		}
	}
}



void end() {
  FILE *file;
  int i, size_asa = top_asa + 1;

	qsort(asa, size_asa, sizeof(Node), comparator);

  file = fopen("asa.txt", "w");

  for(i = 0; i < size_asa; ++i){
    fprintf(file, "%d,%c\n", asa[i].position, asa[i].value);
  }

  fclose(file);
}


int main(void) {
	strcpy(syntactic_sugars, "SNGMACB.;E()XD{}");

	top_asa = -1;

	load_ada();
	generate_asa(ada[0], 0);
	end();

	return(0);
}