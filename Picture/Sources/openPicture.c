//======================================================================//
// Projet Informatique: Indexation de Fichiers
//======================================================================//
// UPSSITECH L3 SMI 2013-2014
// Auteur: VEILLARD Aurélien
// Date de création: 30/11/13
//======================================================================//
// Fichier C: openPicture.c
//======================================================================//
// Fonctions:
// - Ouverture d'une image (au format .txt)
// - Appel de la fonction de lecture et stockage temp des images
// - Fermeture de l'image ouverte
//======================================================================//

#include "openPicture.h"
#include "Utility/utility.h"

//======================================================================//

int openPict(FILE* picture, FILE* log, FILE* descriptorBase, char* filename) {
	PictureRGB pictRGB;
	PictureBW pictBW;
	Histogram hist;
	Quantification quant;
	time_t clock;
	int i, j, k, sizeXTemp, sizeYTemp, nbComponent, exponent, quantifyingLevel;
	int flagPictureRGB = -1; 	// 1 if picture RGB
					// 0 if picture B&W
	char id[100];

	// Base des descripteur d'images
	//TODO : Il ne faut pas oublier d'inscrire le descripteur 
	//	dans la bases des descripteur !
	FILE* pictureBase = fopen("Bases/base_descripteur_image.base", "a+");
// 	srand(time(NULL));
	sprintf(id, "ID%d", rand());
	
	// Allocation de la mémoire pour stocker l'image
	fscanf(picture, "%d %d %d", &sizeYTemp, &sizeXTemp, &nbComponent);
	
	if(getValueOf("NB_SIGNIFICANT_BIT_FOR_QUANTIFICATION", &quant.nbBit) == -1) {
		fprintf(log, "CONFIG ERROR ");
		return(-1);
	}
	
	if(nbComponent == 3) {
		int RedValue, GreenValue, BlueValue;
		// Création d'un histogramme RGB temporaire
		initHistogram(&hist, pow(2, (quant.nbBit*3)), log);
		
		pictRGB.filename = (char*)malloc(sizeof(*filename));
		strcpy(pictRGB.filename, filename);
		
		flagPictureRGB = 1;
		// Création de l'image temp en RGB
		pictRGB.sizeX = sizeXTemp;
		pictRGB.sizeY = sizeYTemp;
		pictRGB.component = nbComponent;
			
		pictRGB.matrixRed = allocMatrix2D(pictRGB.sizeY, pictRGB.sizeX, log);
		pictRGB.matrixGreen = allocMatrix2D(pictRGB.sizeY, pictRGB.sizeX, log);
		pictRGB.matrixBlue = allocMatrix2D(pictRGB.sizeY, pictRGB.sizeX, log);
			
		// STOCKAGE TEMPORAIRE DES COMPOSANTES
		// 1ere matrice: matrice rouge
		for(i = 0; i < pictRGB.sizeY; i++) {
			for(j = 0; j < pictRGB.sizeX; j++) {
				fscanf(picture, "%d", &pictRGB.matrixRed[i][j]);
			}
		}
		
		// 2ième matrice: matrice verte
		for(i = 0; i < pictRGB.sizeY; i++) {
			for(j = 0; j < pictRGB.sizeX; j++) {
				fscanf(picture, "%d", &pictRGB.matrixGreen[i][j]);
			}
		}
		
		// 3ième matrice: matrice bleue
		for(i = 0; i < pictRGB.sizeY; i++) {
			for(j = 0; j < pictRGB.sizeX; j++) {
				fscanf(picture, "%d", &pictRGB.matrixBlue[i][j]);
			}
		}
		
		// Traitement sur l'image
		for(i = 0; i < pictRGB.sizeY; i++) {
			for(j = 0; j < pictRGB.sizeX; j++) {
				// Quantification
				RedValue = pictRGB.matrixRed[i][j];
				GreenValue = pictRGB.matrixGreen[i][j];
				BlueValue = pictRGB.matrixBlue[i][j];
				quantifyRGB(&quant, RedValue, GreenValue, BlueValue);
				
				// Transformation du résultat de quantification
				exponent = ((quant.nbBit)*(pictRGB.component)) - 1;
				quantifyingLevel = 0;
				
				for(k = 0; k < ((quant.nbBit)*(pictRGB.component)); k++) {	// Parcours du tableau de la gauche vers la droite (du poids fort au poids faible)
					if(quant.quantifyingNumber[k] == 1) {	// Si le bit est a 1 alors on ajoute "son poids" au résultat
						quantifyingLevel += pow(2, exponent);	// Ajout du poids du bit à un 1
					}
					exponent--;	// Diminution du rang de l'exposant
				}
				hist.matrixHisto[1][quantifyingLevel]++;	// Incrémentation de la case de l'histogramme correspondant (car classé de 0 à n-1) à la valeur calculée
			}
		}
		
<<<<<<< HEAD
=======
		// Calcul de la quantification
		calculateMatrixRGBQuantification(&pictRGB, &quant, &hist, filename);
		calculateScore(&hist);
>>>>>>> 1a0055ce8d6dc04d1e4c7c712d8386a2c9d9094e
		
		// Ecriture histogramme
		strcat(id, "-");
		strcat(id, pictRGB.filename);
		time(&clock);
<<<<<<< HEAD
		fprintf(descriptorBase, "%s\t%d\t%d\t%d\t%d\t%s", id, pictRGB.sizeY, pictRGB.sizeX , pictRGB.component, quant.nbBit, ctime(&clock));
=======
		fprintf(descriptorBase, "%s\t%d\t%d\t%d\t%d\t%d\t%s", id, pictRGB.sizeY, pictRGB.sizeX , pictRGB.component, quant.nbBit, hist.score, ctime(&clock));
		writingHistogram(&hist, descriptorBase, (quant.nbBit*3));
>>>>>>> 1a0055ce8d6dc04d1e4c7c712d8386a2c9d9094e
		
		for(i = 0; i < pow(2, (quant.nbBit*3)); i++) {
			fprintf(descriptorBase, "%d\t%d\n", hist.matrixHisto[0][i], hist.matrixHisto[1][i]);
			fflush(stdout);
		}
		
		removeHistogram(&hist, log);
		freeMatrix2D(pictRGB.matrixRed, pictRGB.sizeY, log);
		freeMatrix2D(pictRGB.matrixGreen, pictRGB.sizeY, log);
		freeMatrix2D(pictRGB.matrixBlue, pictRGB.sizeY, log);
	//////////////////////////////////////
	} else if (nbComponent == 1) {
		int GreyValue;
		// Création d'un histogramme B&W temporaire
		initHistogram(&hist, pow(2, quant.nbBit), log);
		
		pictBW.filename = (char*)malloc(sizeof(*filename));
		strcpy(pictBW.filename, filename);
		
		flagPictureRGB = 0;
		// Création de l'image temp en B&W
		pictBW.sizeX = sizeXTemp;
		pictBW.sizeY = sizeYTemp;
		pictBW.component = nbComponent;
		pictBW.matrixGrey = allocMatrix2D(pictBW.sizeY, pictBW.sizeX, log);
		
<<<<<<< HEAD
		// STOCKAGE TEMPORAIRE DE LA COMPOSANTE GRISE
		// Matrice grey
		for(i = 0; i < pictBW.sizeY; i++) {
			for(j = 0; j < pictBW.sizeX; j++) {
				fscanf(picture, "%d", &pictBW.matrixGrey[i][j]);
			}
		}
		
		// Traitement sur l'image
		for(i = 0; i < pictBW.sizeY; i++) {
			for(j = 0; j < pictBW.sizeX; j++) {
				// Quantification
				GreyValue = pictBW.matrixGrey[i][j];
				quantifyBW(&quant, GreyValue);
				
				// Transformation du résultat de quantification
				exponent = quant.nbBit - 1;
				quantifyingLevel = 0;
				
				for(k = 0; k < ((quant.nbBit)*(pictBW.component)); k++) {
					if(quant.quantifyingNumber[k] == 1) {
						quantifyingLevel += pow(2, exponent);
					}
					exponent--;
				}
				hist.matrixHisto[1][quantifyingLevel]++;
			}
		}
=======
		// Calcul de la quantification
		calculateMatrixBWQuantification(&pictBW, &quant, &hist, filename);
		calculateScore(&hist);
>>>>>>> 1a0055ce8d6dc04d1e4c7c712d8386a2c9d9094e
		
		// Ecriture histogramme
		strcat(id, "-");
		strcat(id, pictBW.filename);
		time(&clock);
<<<<<<< HEAD
		fprintf(pictureBase, "%s\t%d\t%d\t%d\t%d\t%s", id, pictBW.sizeY, pictBW.sizeX , pictBW.component, quant.nbBit, ctime(&clock));
		
		for(i = 0; i < pow(2, quant.nbBit); i++) {
			fprintf(pictureBase, "%d\t%d\n", hist.matrixHisto[0][i], hist.matrixHisto[1][i]);
			fflush(stdout);
		}
=======
		fprintf(descriptorBase, "%s\t%d\t%d\t%d\t%d\t%d\t%s", id, pictBW.sizeY, pictBW.sizeX , pictBW.component, quant.nbBit, hist.score, ctime(&clock));
		writingHistogram(&hist, descriptorBase, quant.nbBit);
>>>>>>> 1a0055ce8d6dc04d1e4c7c712d8386a2c9d9094e
		
		removeHistogram(&hist, log);
		freeMatrix2D(pictBW.matrixGrey, pictBW.sizeY, log);
	/////////////////////////////////////////////
		
	} else {
		fprintf(log, "> ERROR: number of component of the picture is incorrect (components = %d)\n", nbComponent);
		fflush(stdout);
	}
}

//======================================================================//