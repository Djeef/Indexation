//======================================================================//
// Projet Informatique: Indexation de Fichiers
//======================================================================//
// UPSSITECH L3 SMI 2013-2014
// Auteur: ZERBIB Yoanna
// Date de création: 18/11/13
//======================================================================//
// Fichier C: fonctions.c
//======================================================================//
// Module TEXTES:
// - Indexation des textes (.xml)
//======================================================================//

#include "parser.h"
#include "histogramText.h"
#include "descriptor.h"
#include "Utility/utility.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/**
 * \file parser.c
 * \author Yoanna Zerbib
 * \brief Permet de "parser" un fichier xml. 
 * \version 1
 * \date 25 decembre 2013.
 * 
 */

/**
* \fn int good_word(char* word)
* \brief Permet de ne garder que les 'bons' mots
*
* \param word La chaine de caracteres a modifier si necessaire
*/
int good_word(char* word, FILE *log) {
	int res = 1;
	int i = 0;
	int der_lettre = strlen(word)-1;
	int nbWords;
	char *ptr_virgule = strchr(word, ',');
	char *ptr_point = strchr(word, '.');
	
	if(getValueOf("NB_MAX_WORDS", &nbWords) == -1) {
		fprintf(log, "CONFIG ERROR ");
		return(-1);
	}
	//si le premier caractere est une ponctuation
	if (ispunct(word[i])) {
		word[i] = word[i+1];
	}
	//si le 2eme caractere est une apostrophe (s'appelait)
	if (word[1] == '\'') {
		for (i = 0 ; i < strlen(word) ; i++) {
			word[i] = word[i+2];
		}
	}
	//si le 3eme caractere est une apostrophe (qu'il)
	if (word[2] == '\'') {
		for (i = 0 ; i < strlen(word) ; i++) {
			word[i] = word[i+3];
		}
	}
	//si le mot fait moins de NB_MAX_WORDS caracteres
	if (strlen(word) <= nbWords) {
		res = 0;
	} 
	//si le mot est un pronom ou un article (ou n'importe quel autre mot n'ayant aucune importance)
	if (strcmp(word, "un") == 0 || strcmp(word, "une") == 0 || strcmp(word, "de") == 0 || strcmp(word, "des") == 0 || strcmp(word, "le") == 0 || strcmp(word, "la") == 0 || strcmp(word, "les") == 0 || strcmp(word, "je") == 0 || strcmp(word, "me") == 0 || strcmp(word, "se") == 0 || strcmp(word, "te") == 0 || strcmp(word, "pour") == 0 ) {
		res = 0;
	}	
	
	return res;
}

/**
* \fn void get_words(FILE *file)
* \brief Permet de recuperer tous les mots sans les balises
*
* \param file Le fichier txt d'ou on veut extraire le texte 
*/
int get_words(FILE *file, FILE *log, FILE *descriptorBase, char *filename) { 
	char sentence[MAX_BUFFER_SIZE] = {0};
	char word[MAX_BUFFER_SIZE] = {0};
	int read = 0;
	int i, j;
	Descriptor d;

	FILE *textBase = fopen("Bases/base_descripteur_text.base", "a");
	if (textBase == NULL) {
		system("mkdir Bases");
		textBase = fopen("Bases/base_descripteur_text.base", "a+");
	}
	init_descriptor(&d);
	while(!feof(file)) {
		//On lit toute la ligne 
		fgets(sentence, MAX_BUFFER_SIZE, file);
		read = 0;
		for (i = 0, j = 0; i < MAX_BUFFER_SIZE; i++) {
			if (sentence[i] == '\n') {
				break;
			}
			if (sentence[i] == '<') {
				read = 0;
			} 
			if(sentence[i] == '>' && sentence[i+1] != '<' ) {
				read = 1;
				i++;
			}
			// s'il s'agit d'un 'vrai' mot
 			if (read) {
 				sentence[i] = tolower(sentence[i]);
				if(sentence[i] == '\n') {
					break;
				}
 				if (sentence[i] != ' ' && sentence[i] != ',' && sentence[i] != '.' && sentence[i+1] != '<') {
					word[j] = sentence[i];
					j++;
				}
				//le mot est fini
 				else {
	 				if (good_word(word, log)) {
						add_value(word, &d);
					}
					j = 0;
					memset(word, 0, MAX_BUFFER_SIZE);
	 			}
 			}
 		}
	}
	if(display_descriptor(&d, textBase, filename, log) == -1) {
		return(-1);
	}
	add_base_descriptors(&d, descriptorBase, filename);
	free_descriptor(&d);
	fclose(textBase);
}


