#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Utility/utility.h"
#include "Text/histogramText.h"

float comparePicture(FILE *descriptorFile1, FILE *descriptorFile2, int nbLinesMin, int nbLinesMax);
float compareSound(FILE *descriptorFile1, FILE *descriptorFile2, int nbLinesMin, int nbLinesMax, int nbColumnsMin, int nbColumnsMax);
float compareText(FILE *descriptorFile1, FILE *descriptorFile2, int nbLigneDesc1, int nbLigneDesc2, int descMax);

int main(int argc, char *argv[]) {
	FILE *descriptorFile1;
	FILE *descriptorFile2;
	char header1[BUFFER_SIZE];
	char header2[BUFFER_SIZE];
	char date1[BUFFER_SIZE] = {0};
	char fileDate1[BUFFER_SIZE] = {0};
	char headerID1[BUFFER_SIZE] = {0};
	char type1[BUFFER_SIZE] = {0};
	char id1[BUFFER_SIZE] = {0};
	char date2[BUFFER_SIZE] = {0};
	char fileDate2[BUFFER_SIZE] = {0};
	char headerID2[BUFFER_SIZE] = {0};
	char type2[BUFFER_SIZE] = {0};
	char id2[BUFFER_SIZE] = {0};
	int nbColumns1;
	int nbLines1;
	int nbColumns2;
	int nbLines2;
	int nbColumnsMin;
	int nbColumnsMax;
	int nbLinesMin;
	int nbLinesMax;
	int value;
	int descMax = 0;

	if(argc < 3) {
		fprintf(stderr, "Usage : <Descriptor 1> <Descriptor 2> of the same type \n");
		return(EXIT_FAILURE);
	}
	descriptorFile1 = fopen(argv[1], "r");
	descriptorFile2 = fopen(argv[2], "r");	
	if(descriptorFile1 == NULL || descriptorFile2 == NULL) {
		fprintf(stderr, "DESCRIPTOR OPENNING FAILED \n");
		return(EXIT_FAILURE);
	}

	fgets(header1, BUFFER_SIZE, descriptorFile1);
	fgets(header2, BUFFER_SIZE, descriptorFile2);

	splitHeader(header1, id1, &nbColumns1, &nbLines1, type1, date1);
	splitHeader(header2, id2, &nbColumns2, &nbLines2, type2, date2);

	if(strcmp(type1, type2) != 0) {
		fprintf(stderr, "NOT SAME TYPE %s vs %s\n", type1, type2);
		return(EXIT_FAILURE);
	}

	if(nbLines1 < nbLines2) {
		nbLinesMin = nbLines1;
		nbLinesMax = nbLines2;
		descMax = 2;
	} else {
		nbLinesMin = nbLines2;
		nbLinesMax = nbLines1;
		descMax = 1;
	}
	if(nbColumns1 < nbColumns2) {
		nbColumnsMin = nbColumns1;
		nbColumnsMax = nbColumns2;
	} else {
		nbColumnsMin = nbColumns2;
		nbColumnsMax = nbColumns1;
	}
	if(strcmp(type1, "picture") == 0) {
		printf("%f\n", comparePicture(descriptorFile1, descriptorFile2, nbLinesMin, nbLinesMax));
	} else if(strcmp(type1, "sound") == 0) {
		printf("%f\n", compareSound(descriptorFile1, descriptorFile2, nbLinesMin, nbLinesMax, nbColumnsMin, nbColumnsMax));
	} else if(strcmp(type1, "text") == 0) {
		printf("%f\n", compareText(descriptorFile1, descriptorFile2, nbLines1, nbLines2, descMax));
	} else {
		printf("NOT RECONIZED TYPE \n");
	}
	fclose(descriptorFile1);
	fclose(descriptorFile2);
	return(EXIT_SUCCESS);
}

float comparePicture(FILE *descriptorFile1, FILE *descriptorFile2, int nbLinesMin, int nbLinesMax) {
	char buffer1[BUFFER_SIZE] = {0};
	char buffer2[BUFFER_SIZE] = {0};
	int value1;
	int value2;
	int i;
	int nbSameValue = 0;

	for(i = 0; i < nbLinesMin; i++) {
		fgets(buffer1, BUFFER_SIZE, descriptorFile1);
		fgets(buffer2, BUFFER_SIZE, descriptorFile2);
		sscanf(buffer1, "%*s\t%d", &value1);
		sscanf(buffer2, "%*s\t%d", &value2);
		if(value1 == value2) {
			nbSameValue++;
		}
	}
	return(nbSameValue / (float)nbLinesMax * 100.0);
}

float compareSound(FILE *descriptorFile1, FILE *descriptorFile2, int nbLinesMin, int nbLinesMax, int nbColumnsMin, int nbColumnsMax) {
	char buffer1[BUFFER_SIZE] = {0};
	char buffer2[BUFFER_SIZE] = {0};
	char currentChar2;
	char currentChar1;
	int value1;
	int value2;
	int i, j;
	int nbSameValue = 0;

	for(i = 0; i < nbLinesMin; i++) {
		for(j = 0; j < nbColumnsMin; j++) {
			do {
				currentChar1 = fgetc(descriptorFile1);
				buffer1[strlen(buffer1)] =  currentChar1;
			} while(currentChar1 != '\t' && currentChar1 != '\n');
			do {
				currentChar2 = fgetc(descriptorFile2);
				buffer2[strlen(buffer2)] =  currentChar2;
			} while(currentChar2 != '\t' && currentChar2 != '\n');
			value1 = atoi(buffer1);
			value2 = atoi(buffer2);
			if(value1 == value2) {
				nbSameValue++;
			}
			memset(buffer1, 0, BUFFER_SIZE);
			memset(buffer2, 0, BUFFER_SIZE);
		}
	}
	return(nbSameValue / ((float)nbLinesMax * (float)nbColumnsMax)* 100.0);
}


float compareText(FILE *descriptorFile1, FILE *descriptorFile2, int nbLigneDesc1, int nbLigneDesc2, int descMax) {
	char buffer[BUFFER_SIZE] = {0};
	char key[BUFFER_SIZE] = {0};
	int value;
	int ret;
	int i;
	int nbSameValue = 0;
	int max = 0;
	Histogram histogramText;
	int maxLine;
	int minLine;

	if(descMax == 1) {
		maxLine = nbLigneDesc1;
		minLine = nbLigneDesc2;
	} else {
		maxLine = nbLigneDesc2;
		minLine = nbLigneDesc1;
	}

	for(i = 0; i < maxLine; i++) {
		if(descMax == 1) {
			fgets(buffer, BUFFER_SIZE, descriptorFile1);
		} else {
			fgets(buffer, BUFFER_SIZE, descriptorFile2);
		}
		sscanf(buffer, "%d\t%s", &value, key);
		add_key_value(&histogramText, key, value);
		max += value;
	}
	for(i = 0; i < minLine; i++) {
		if(descMax == 1) {
			fgets(buffer, BUFFER_SIZE, descriptorFile2);
		} else {
			fgets(buffer, BUFFER_SIZE, descriptorFile1);
		}
		sscanf(buffer, "%d\t%s", &value, key);
		if(get_value(&histogramText, key, &ret) == 0) {
			if(value > ret) {
				nbSameValue += ret;
			} else {
				nbSameValue += value;
			}
		}
	}
	return(nbSameValue / (float)max * 100.0);
}


