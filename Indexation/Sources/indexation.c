#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include "Sound/wavFile.h"
#include "Picture/openPicture.h"

/**
 * \mainpage DOCUMENTATION: Indexation d'une base de données - Indexing of data base
 *
 * \section section_cadre I - Cadre du projet - Context of the project
 * 
 * Ce projet s'inscrit dans le cadre de la formation L3 SMI 2013-2014 dispensée par l'Université Paul Sabatier de Toulouse.
 * 
 * Ce projet a été réalisé par: ERDELYI Jean-François, VEILLARD Aurélien et ZERBIB Yoanna.
 * 
 * __
 * 
 * This project takes place in L3 SMI formation delivered by Paul Sabatier University of Toulouse.
 * 
 * This project was directed by ERDELYI Jean-François, VEILLARD Aurélien et ZERBIB Yoanna.
 * ___
 * 
 * \section section_introduction II - Présentation - Overview
 *
 * Le but de ce projet était de créer un programme capable de traiter trois types de fichiers: 
 * 
 * 	- Les fichiers audio de types wave (.wav);
 * 
 * 	- Les fichiers images de types bmp et jpeg au format texte (.txt);
 * 
 * 	- Les fichiers textes de types xml.
 * 
 * L'indexation représente la première partie du projet à laquelle s'ajoutera un moteur de recherche.
 * 
 * __
 * 
 * The aim of this project was to create un program which is be able to process three types of files:
 * 
 * 	- Wave sound files (.wav);
 * 
 * 	- Picture files (jpeg and bmp) formatted as text files;
 * 
 * 	- Text files in format .xml.
 * 
 * The indexing part is the first part of the project that will add a search engine.
 * ___
 *
 * \section section_installation III - Utilisation - Using
 * 
 * \subsection subsection_prerequis 1 - Pré-requis - Prerequisites
 * 
 * Quelques points sont à respecter avant de lancer l'indexation:
 * 
 * 	- Les fichiers à indexer doivent être dans les formats suivants: .wav, .xml, .txt (correspondant à un .jpeg ou bmp);
 * 
 * 	- L'ensemble de ces fichiers doivent être placé dans un seul et même fichier nommé "Data";
 * 
 * 	- Le fichier "config.conf" doit absolument être présent et complet.
 * 
 * __
 * 
 * Some points must be respected before processing indexing:
 * 
 * 	- The index files must be in following formats: .wav, .xml, .txt (corresponding to a jpeg or a bmp file);
 * 
 * 	- All files should be place in only one folder named "Data";
 * 
 * 	- The "config.conf" file should be absolutely present and complete.
 * 
 * ___
 * 
 * \subsection subsection_installation 2 - Installation et lancement - Installation and running
 * 
 * Afin de procéder à l'indexation de la base de données, il faut que l'exécutable "Indexation", que le fichier "config.conf" et que le dossier "Data" soit au même niveau ou dans le même dossier.
 * 
 * Pour l'exécuter, il suffit de double cliquer dessus ou bien d'écrire ceci dans la fenêtre de commande:
 * 
 * \code
 * $ ./Indexation
 * \endcode
 * 
 * __
 * 
 * To perform indexing of the database, it's necessary that the executable "Indexation", the "config.conf" file and the "Data" folder is at the same level or in the same folder.
 * 
 * To run it, just double click on it or write it in the command window:
 *  
 * \code
 * $ ./Indexation
 * \endcode
 * ___
 * 
 * \subsection subsection_sortie 3 - Données de sortie - Output datas
 * 
 * Après exécution du programme, un dossier "Bases" a été créer automatiquement contenant les fichiers suivants:
 * 
 * 	- liste_base_audio.base : contenant les identifiants uniques et les fichiers associés (idem pour image et texte);
 * 
 * 	- base_descripteur_audio.base : contenant l'ensemble des descripteurs des fichiers traités (idem pour image et texte).
 * 
 * Ces fichiers pourront être ensuite utilisés pour le moteur de recherche.
 * 
 * __
 * 
 * After running, "Bases" folder was automatically created containing the following files:
 * 
 * 	- liste_base_audio.base: containing unique identifiers and associated files (same for image and text);
 * 
 * 	- base_descripteur_audio.base: containing all descriptors processed files (same for image and text).
 * 
 * Then, these files can be used for search engine.
 * 
 * ___
 * 
 * \section copyright Copyright and License
 * 
 * Ce projet est sous licence <a href="http://www.gnu.org/licenses/gpl-2.0.html">GNU GENERAL PUBLIC LICENSE v2</a>.
 * 
 * __
 * 
 * This project is under <a href="http://www.gnu.org/licenses/gpl-2.0.html">GNU GENERAL PUBLIC LICENSE v2</a>.
 * 
 */


int main(int argc, char *argv[]) {
	struct dirent *currentElement;
	DIR *data;
	WavFile wavFile;
	char extension[BUFFER_SIZE] = {0};
	char buffer[BUFFER_SIZE] = {0};
	char path[BUFFER_SIZE] = {0};
	char id[BUFFER_SIZE] = {0};
	FILE *descriptorBaseSound;
	FILE *descriptorBaseTexts;
	FILE *descriptorBasePictures;
	FILE *log;
	FILE *currentPicture;
	FILE *currentText;
	int ret;
	time_t aclock;

	time(&aclock);

	log = fopen("log.log", "a");
	fprintf(log, "%s", ctime(&aclock));
	data = opendir("Data/");
	if(data == NULL) {
		fprintf(log, "OPPENING DATABASE FAIL ");
		return(EXIT_FAILURE);
	}
	descriptorBaseSound = fopen("Bases/liste_base_audio.base", "a+");
	if(descriptorBaseSound == NULL) {
		system("mkdir Bases");
		descriptorBaseSound = fopen("Bases/liste_base_audio.base", "a+");
	}
	descriptorBasePictures = fopen("Bases/liste_base_image.base", "a+");
	descriptorBaseTexts = fopen("Bases/liste_base_text.base", "a+");

	checkDescriptorBase(descriptorBaseSound, log, "sound");
	checkDescriptorBase(descriptorBasePictures, log, "image");
	checkDescriptorBase(descriptorBaseTexts, log, "text");
	while((currentElement = readdir(data))) {
		extractExtension(currentElement->d_name, extension);
		if(strcmp(extension, ".wav") == 0) {
			createPath(currentElement->d_name, "Data/", extension, path);
			fprintf(log, "OPPENING FILE : %s \t ", path);
			if(!getIdInDescriptorBase(descriptorBaseSound, id, path)) {
				openWavFile(&wavFile, path);
				if(writeDescriptor(&wavFile, descriptorBaseSound, log) == -1) {
					fprintf(log, " : WRITING SOUND DATA FAIL ! \n");
					continue;
				}
				fprintf(log, "FILE INDEXED ! \n");
				closeWavFile(&wavFile);
			} else {
				ret = getIfFileHasModified(id, path, log, "sound");
				if(ret == 1) {
					fprintf(log, "FILE ALLREADY INDEXED ! \n");
				} else if(ret == -1){
					fprintf(log, "READ DESCRIPTOR FAIL ! \n");
				} else {
					memset(buffer, 0, BUFFER_SIZE);
					sprintf(buffer, "%s\t%s\n", path, id);
					supprDescriptorHeader(descriptorBaseSound, buffer, "sound");
					supprDescriptor(id, "sound");
					openWavFile(&wavFile, path);
					if(writeDescriptor(&wavFile, descriptorBaseSound, log) == -1) {
						fprintf(log, " : WRITING DATA FAIL ! \n");
						continue;
					}
					closeWavFile(&wavFile);
					fprintf(log, "FILE HAS BEEN MODIFIED ! \n");
				}
			}
			
		/**
		 * Fichier image sous forme de texte
		 */
		} else if(strcmp(extension, ".txt") == 0) {
			createPath(currentElement->d_name, "Data/", extension, path);
			fprintf(log, "OPPENING FILE : %s \t ", path);
			if(!getIdInDescriptorBase(descriptorBasePictures, id, path)) {
				currentPicture = fopen(path, "r");
				if(openPict(currentPicture, log, descriptorBasePictures, path) == -1) {
					fprintf(log, " : WRITING IMAGE DATA FAIL ! \n");
					continue;
				}
				fprintf(log, "FILE INDEXED ! \n");
				fclose(currentPicture);
			} else {
				ret = getIfFileHasModified(id, path, log, "image");
				if(ret == 1) {
					fprintf(log, "FILE ALLREADY INDEXED ! \n");
				} else if(ret == -1){
					fprintf(log, "READ DESCRIPTOR FAIL ! \n");
				} else {
					memset(buffer, 0, BUFFER_SIZE);
					sprintf(buffer, "%s\t%s\n", path, id);
					supprDescriptorHeader(descriptorBasePictures, buffer, "image");
					supprDescriptor(id, "image");
					currentPicture = fopen(path, "r");
					if(openPict(currentPicture, log, descriptorBasePictures, path) == -1) {
						fprintf(log, " : WRITING IMAGE DATA FAIL ! \n");
						continue;
					}
					fclose(currentPicture);
					fprintf(log, "FILE HAS BEEN MODIFIED ! \n");
				}
			}
		/**
		 * Fichier Textes
		 */
		} else if(strcmp(extension, ".xml") == 0) {
			createPath(currentElement->d_name, "Data/", extension, path);
			fprintf(log, "OPPENING FILE : %s \t ", path);
			if(!getIdInDescriptorBase(descriptorBaseTexts, id, path)) {
				currentText = fopen(path, "r");
				if(get_words(currentText, log, descriptorBaseTexts, path) == -1) {
					fprintf(log, " : WRITING TEXT DATA FAIL ! \n");
					continue;
				}
				fprintf(log, "FILE INDEXED ! \n");
				fclose(currentText);
			} else {
				ret = getIfFileHasModified(id, path, log, "text");
				if(ret == 1) {
					fprintf(log, "FILE ALLREADY INDEXED ! \n");
				} else if(ret == -1){
					fprintf(log, "READ DESCRIPTOR FAIL ! \n");
				} else {
					memset(buffer, 0, BUFFER_SIZE);
					sprintf(buffer, "%s\t%s\n", path, id);
					supprDescriptorHeader(descriptorBaseTexts, buffer, "text");
					supprDescriptor(id, "text");
					currentText = fopen(path, "r");
					if(get_words(currentText, log, descriptorBaseTexts, path) == -1) {
						fprintf(log, " : WRITING TEXT DATA FAIL ! \n");
						continue;
					}
					fclose(currentText);
					fprintf(log, "FILE HAS BEEN MODIFIED ! \n");
				}
			}
		}
		memset(path, 0, BUFFER_SIZE);
	}

	/**
	 * Fermer le dossier et rentree a la maison
	 */
	closedir(data);
	fclose(descriptorBaseSound);
	fclose(descriptorBasePictures);
	fclose(descriptorBaseTexts);
	fclose(log);
	printf("DONE ! \n");
	return(EXIT_SUCCESS);
}