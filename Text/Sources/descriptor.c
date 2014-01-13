//======================================================================//
// Projet Informatique: Indexation de Fichiers
//======================================================================//
// UPSSITECH L3 SMI 2013-2014
// Auteur: ZERBIB Yoanna
// Date de création: 18/11/13
//======================================================================//
// Fichier C: descriptor.c
//======================================================================//
// Module TEXTES:
// - Indexation des textes (.xml)
//======================================================================//

#include "histogramText.h"
#include "descriptor.h"
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>

/**
 * \file descriptor.c
 * \author Yoanna Zerbib
 * \brief Crée et manipuler des descripteurs pour des fichiers xml.
 * \version 1
 * \date 25 decembre 2013.
 *
 */

/**
* \fn void init_descriptor(Descriptor *d)
* \brief Permet d'initialiser un descripteur.
*
* \param d Le descripteur. 
*/
void init_descriptor(Descriptor *d) {
	d->id = (char*)calloc(30, sizeof(char));
	strcpy(d->id, "\0");
	d->ptr_histo = (Histogram*)malloc(sizeof(Histogram));
	init_histogram(d->ptr_histo);
	d->nb_words = 0;
}

/**
* \fn void free_descriptor(Descriptor *d)
* \brief Permet de liberer l'espace memoire du descripteur.
*
* \param d Le descripteur. 
*/
void free_descriptor(Descriptor *d) {
	free_histogram(d->ptr_histo);
	free(d->id);
}

/**
* \fn void add_value(char *key, Descriptor *d)
* \brief Permet d'ajouter une nouvelle valeur dans l'histogramme
*
* \param key Le mot a ajouter.
* \param d Le descripteur. 
*/
void add_value(char *key, Descriptor *d) {
	Cel *current_cel;
	Cel *newc;
	
	//l'histogramme est vide
	if(is_void(d->ptr_histo)) {
		newc = (Cel*)malloc(sizeof(Cel));
		strcpy(newc->key, key);
		newc->value = 1;
		newc->ptr_next_cel = NULL;
		d->ptr_histo->begin = newc;
		d->ptr_histo->end = newc;
	} else {
		current_cel = d->ptr_histo->begin;
		while (current_cel != NULL) {	
			// le mot existe deja : on augmente juste son occurence
			if (strcmp(current_cel->key, key) == 0) {
				current_cel->value++;
				break;
			} else {
				// on passe a la cellule suivante
				current_cel = current_cel->ptr_next_cel;
			}
		}
		//le mot n'existe pas
		if (current_cel == NULL)  {
			newc = (Cel*)malloc(sizeof(Cel));
			strcpy(newc->key, key);
			newc->value = 1;
			newc->ptr_next_cel = NULL;		
			d->ptr_histo->end->ptr_next_cel = newc;
			d->ptr_histo->end = d->ptr_histo->end->ptr_next_cel;
		}
	}
}

/**
* \fn void display_descriptor(Descriptor *d, FILE *out)
* \brief Permet d'afficher le descripteur dans un fichier texte
*
* \param d Le descripteur. 
* \param out Un fichier txt de sortie.
*/
int display_descriptor(Descriptor *d, FILE *out, char *filename, FILE *log) {
	struct stat st;
// 	srand(time(NULL));
	if(stat(filename, &st) == -1) {
		fprintf(log, "STAT ERROR ");
		return(-1);
	}
	sprintf(d->id, "ID%d%s", rand(), filename);
	fprintf(out, "%s\t%d\t%d\t%s\t%s", d->id, 2, get_nb_words(d->ptr_histo), "text", ctime(&st.st_mtime));
	display_histogram(d->ptr_histo, out);
}

/**
* \fn void add_base_descriptors(Descriptor *d, FILE *out)
* \brief Permet d'ajouter une ligne du descripteur d'un texte dans le fichier liste_base_descripteurs
*
* \param d Le descripteur. 
* \param out Un fichier txt de sortie.
*/
void add_base_descriptors(Descriptor *d, FILE *out, char *filename) {
	fprintf(out, "%s\t%s\n", filename, d->id);
/*	fprintf(out, "%s\n", argv[1]);*/
}
