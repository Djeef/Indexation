#ifndef Histogram
#define Histogram

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_SIZE 100

//structure d'une cellule
typedef struct Cel {
	char* key[MAX_BUFFER_SIZE];
	int value;
	struct Cel* ptr_next_cel;
} Cel;

//pointeurs de debut et fin sur l'histogramme
typedef struct Histogram {
	Cel* begin;
	Cel* end;
} Histogram;

// //structure d'un descripteur
// typedef struct Descriptor {
// 	int id;
// 	Histogram h;
// 	int nb_words;
// } Descriptor;

void get_words(FILE *file);
void addValue(String key, Histogram h);
// void free_descriptor(Histogram h);

#endif /*Histogram*/
