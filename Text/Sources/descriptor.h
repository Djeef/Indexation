//======================================================================//
// Projet Informatique: Indexation de Fichiers
//======================================================================//
// UPSSITECH L3 SMI 2013-2014
// Auteur: ZERBIB Yoanna
// Date de création: 18/11/13
//======================================================================//
// Fichier H: descriptor.h
//======================================================================//
// Module TEXTES:
// - Indexation des textes (.xml)
//======================================================================//

#ifndef DESCRIPTOR_H
#define DESCRIPTOR_H

/**
 * \file descriptor.h
 * \author Yoanna Zerbib
 * \brief Crée et manipuler des descripteurs pour des fichiers xml.
 * \version 1
 * \date 25 decembre 2013.
 *
 */


/**
* \struct Descriptor
* \brief Descriptor.
*
* Permet de stocker un id, un histogramme et son nombre de mots
*/
typedef struct Descriptor {
	char* id;
	Histogram *ptr_histo;
	int nb_words;
} Descriptor;


//Sous-programmes des descripteurs
void init_descriptor(Descriptor *d);
void add_value(char *key, Descriptor *d);
int display_descriptor(Descriptor *d, FILE *out, char *filename, FILE *log);
void add_base_descriptors(Descriptor *d, FILE *out, char *filename);
void free_descriptor(Descriptor *d);

#endif /*DESCRIPTOR_H*/
