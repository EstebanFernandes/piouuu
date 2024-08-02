#pragma once
#define FAUX 0
//
//#define IndexHorsTableau 1
//#define TailleInvalide 2
//#define DivisionImpossible 3
//#define DimensionIncohérente 4
//#define FichierIntrouvable 5
//#define LectureFichierImpossible 6
//#define MatriceNul 7
//#define TailleInvalideConstruct 8
//#define MauvaisTypeDonnees 9
//#define ValeurAttenduInvalide 10
//#define NombreDArgumentInvalide 11
//#define FinLigneAttendue 12
#define PositionIncoherente 1
#define SupprimerNulle 2
#define ArcPartantIntrouvable 3
#define ArcArrivantIntrouvable 4
#define SommetSupprimerIntrouvable 5
#define SommetExistant 6
#define SommetSourceIntrouvable 7
#define SommetDestinationIntrouvable 8
#define LectureSommet 9
#define LectureArc 10
#define LectureValeurSommet 11
#define LectureValeurArc 12
#define ArcExistant 13
#define NombreDArgumentInvalide 14
#define NomFichierInexistant 15
#define ValeurPoidsNégatif 16
#define LectureFichierImpossible 17
#define LectureOrientation 18
#define ErreurTypeGraphe 19
#include<iostream>
class Exception
{
	//Atributs :
private:
	unsigned int uiEXCvaleur;
public:

	/**********************************************************************
	***** Exception() : Constructeur par défaut, initialise un objet *****
	***********************************************************************
	***** Entrée : Rien                                               *****
	***** Précondition : Rien                                         *****
	***** Sortie : Rien                                               *****
	***** Postcondition : L'exception est initialisée                 *****
	**********************************************************************/
	Exception();

	/**************************************************************************************************************
	***** Exception(unsigned int valeur) : Constructeur de confort qui initialise l'exception avec sa valeur *****
	***************************************************************************************************************
	***** Entrée : la valeur de l'exception                                                                   *****
	***** Précondition : Rien                                                                                 *****
	***** Sortie : Rien                                                                                       *****
	***** Postcondition : L'exception est crée avec une valeur déjà assigné                                   *****
	**************************************************************************************************************/
	Exception(unsigned int valeur);

	/***************************************************
	***** ~Exception() : Destructeur de la classe *****
	****************************************************
	***** Entrée : Rien                            *****
	***** Précondition : Rien                      *****
	***** Sortie : Rien                            *****
	***** Postcondition : L'exception est détruite *****
	***************************************************/
	~Exception() {}

	/*******************************************************************************
	***** EXCModifierValeur() : Cette méthode modifie la valeur de l'exception *****
	********************************************************************************
	***** Entrée : Nouvelle valeur de l'exception                              *****
	***** Précondition : Rien                                                  *****
	***** Sortie : Rien                                                        *****
	***** Postcondition : L'exception est modifiée                             *****
	*******************************************************************************/
	void EXCModifierValeur(unsigned int);

	/****************************************************************************************
	***** EXCLireValeur() : Cette fonction permet de consulter la valeur de l'exception *****
	*****************************************************************************************
	***** Entrée : Rien                                                                 *****
	***** Précondition : Rien                                                           *****
	***** Sortie : La valeur de l'exception                                             *****
	***** Postcondition : L'exception est retournée                                     *****
	****************************************************************************************/
	unsigned int EXCLireValeur();

	/*********************************************************************
	***** EXCHandleException() : Gestion des exceptions              *****
	**********************************************************************
	***** Entrée : Aucune puisqu'elle utilise des variables globales *****
	***** Précondition : Aucune                                      *****
	***** Sortie : Aucune (elle affiche seulement un message)        *****
	***** Postcondition : Aucune                                     *****
	*********************************************************************/
	void EXCHandleException();
};

