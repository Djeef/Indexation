//======================================================================//
// Projet Informatique: Indexation de Fichiers
//======================================================================//
// UPSSITECH L3 SMI 2013-2014
// Auteur: ZERBIB Yoanna
// Date de création: 18/11/13
//======================================================================//
// Fichier H: histogram.h
//======================================================================//
// Module TEXTES:
// - Indexation des textes (.xml)
//======================================================================//

#ifndef HISTOGRAM_TEXT_H
#define HISTOGRAM_TEXT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_SIZE 1000

/**
 * \file histogramText.h
 * \author Yoanna Zerbib
 * \brief Crée et manipuler des histogrammes pour des fichiers xml.
 * \version 1
 * \date 25 decembre 2013.
 *
 */

/**
* \struct Cel
* \brief Cellule d'un histogramme.
*
* Permet de stocker un mot avec son occurence, et la cellule suivante
*/
typedef struct Cel {
	char key[MAX_BUFFER_SIZE];
	int value;
	struct Cel* ptr_next_cel;
} Cel;

/**
* \struct Histogram
* \brief Données d'un histogramme 
*
* Permet de connaitre la premiere et la derniere donnée d'un fichier charge
* ainsi que le nombre de cellules.
*/
typedef struct Histogram {
	Cel* begin;
	Cel* end;
} Histogram;


//Sous-programmes des histogrammes
void init_histogram(Histogram *h);
int is_void(Histogram *h);
void display_histogram(Histogram *h, FILE *out);
int get_nb_words(Histogram *h);
void add_key_value(Histogram *h, char *key, int value);
int get_value(Histogram *h, char *key, int *value);
void free_histogram(Histogram *h);

#endif /*HISTOGRAM_TEXT_H*/
