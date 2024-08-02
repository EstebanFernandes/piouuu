#pragma once
#include<iostream>
#include "Exception.h"
class Arc
{
private :
	double uiARCpoids;
	int iARCDestination;
public :

	/*********************************************
	***** Arc() : Constructeur par défaut   *****
	**********************************************
	***** Entrée : Aucune                    *****
	***** Précondition : Aucune              *****
	***** Sortie : Aucune                    *****
	***** Postcondition : Crée un objet Arc *****
	*********************************************/
	Arc();

	/************************************************************************************
	***** Arc(Arc & ARCParam) : Constructeur de recopie                           *****
	*************************************************************************************
	***** Entrée : Une référence à un objet Arc                                    *****
	***** Précondition : Aucune                                                     *****
	***** Sortie : Aucune                                                           *****
	***** Postcondition : Crée un objet Arc en copiant les valeurs de l'arc source *****
	************************************************************************************/
	Arc(const Arc & ARCParam);

	/*************************************************************************************************
	***** Arc(int iValeur) : Constructeur de confort                                            *****
	**************************************************************************************************
	***** Entrée : Un entier représentant la valeur de destination de l'arc (iValeur)            *****
	***** Précondition : Aucune                                                                  *****
	***** Sortie : Aucune                                                                        *****
	***** Postcondition : Crée un objet Arc en initialisant la valeur de destination de l'arc   *****
	***** (iARCDestination) avec la valeur spécifiée (iValeur)                                   *****
	*************************************************************************************************/
	Arc(int iValeur);

	/****************************************************************************************************************************************
	***** Arc(int iValeur, unsigned int poids) : Constructeur de confort                                                               *****
	*****************************************************************************************************************************************
	***** Entrée : Un entier représentant la valeur de destination de l'arc ainsi qu'un entier représentant la valeur du poids de l'arc *****
	***** Précondition : Aucune                                                                                                         *****
	***** Sortie : Aucune                                                                                                               *****
	***** Postcondition : Crée un objet Arc initialisé avec la valeur de destination de l'arc ainsi que le poids de l'arc              *****
	****************************************************************************************************************************************/
	Arc(int iValeur, double poids);

	/*************************************************************************
	***** ~Arc() : Destructeur                                          *****
	**************************************************************************
	***** Entrée : Aucune                                                *****
	***** Précondition : Aucune                                          *****
	***** Sortie : Aucune                                                *****
	***** Postcondition : Détruit l'objet Arc et libère toute ressource *****
	*************************************************************************/

	~Arc();
	/**********************************************************************************************
	***** ARCObtenirDest() : Obtenir la valeur de destination de l'arc                        *****
	***********************************************************************************************
	***** Entrée : Aucune                                                                     *****
	***** Précondition : Aucune                                                               *****
	***** Sortie : Un entier représentant la valeur de destination de l'arc (iARCDestination) *****
	***** Postcondition : Retourne la valeur de destination de l'arc (iARCDestination)        *****
	**********************************************************************************************/
	int ARCObtenirDest();

	/**********************************************************************
	***** ARCObtenirPoids() : Obtenir la valeur du poids de l'arc     *****
	***********************************************************************
	***** Entrée : Aucune                                             *****
	***** Précondition : Aucune                                       *****
	***** Sortie : Un entier représentant la valeur du poids de l'arc *****
	***** Postcondition : Retourne la valeur du poids de l'arc        *****
	**********************************************************************/
	double ARCObtenirPoids() { return uiARCpoids; }

	/*****************************************************************************************************
	***** ARCModifier(int iValeur) : Modifier la valeur de destination de l'arc                      *****
	******************************************************************************************************
	***** Entrée : Un entier représentant la nouvelle valeur de destination de l'arc (iValeur)       *****
	***** Précondition : Aucune                                                                      *****
	***** Sortie : Aucune                                                                            *****
	***** Postcondition : Modifie la valeur de destination de l'arc (iARCDestination) en utilisant   *****
	***** la nouvelle valeur spécifiée (iValeur)                                                     *****
	*****************************************************************************************************/
	void ARCModifier(int iValeur);

	/************************************************************************************************
	***** ARCModifier(unsigned int poids) : Modifier la valeur du poids de l'arc                *****
	*************************************************************************************************
	***** Entrée : Un entier positif représentant la nouvelle valeur du poids de l'arc          *****
	***** Précondition : Aucune                                                                 *****
	***** Sortie : Aucune                                                                       *****
	***** Postcondition : Modifie la valeur du poids de l'arc avec la nouvelle valeur spécifiée *****
	************************************************************************************************/
	void ARCModifier(double poids);

	/********************************************************************************************************************************************************
	***** ARCModifier(int iDestination, unsigned int poids) : Modifier la valeur du poids de l'arc et la valeur de destination de l'arc                 *****
	*********************************************************************************************************************************************************
	***** Entrée : Un entier positif représentant la nouvelle valeur du poids de l'arc ainsi qu'un entier représentant la nouvelle destination de l'arc *****
	***** Précondition : Aucune                                                                                                                         *****
	***** Sortie : Aucune                                                                                                                               *****
	***** Postcondition : Modifie la valeur du poids de l'arc et la destination de l'arc avec les nouvelles valeurs spécifiées                          *****
	********************************************************************************************************************************************************/
	void ARCModifier(int iDestination, double poids);

	/*****************************************************************************************************
	***** Arc& operator=(const Arc& ARCParam) : Opérateur égale pour la classe Arc                *****
	******************************************************************************************************
	***** Entrée : ARCParam (référence constante vers un objet Arc)                                 *****
	***** Précondition : Aucune                                                                      *****
	***** Sortie : Une référence vers l'objet Arc courant                                           *****
	***** Postcondition : L'objet Arc courant est assigné avec les valeurs de l'objet Arc ARCParam *****
	*****************************************************************************************************/
	Arc& operator=(const Arc& ARCParam);

	/*****************************************************************************************************************************************
	***** operator<<(std::ostream & stream, const Arc & ARCParam) : Surcharge de l'opérateur de sortie (<<) pour afficher un objet Arc *****
	******************************************************************************************************************************************
	***** Entrée : Un flux de sortie (stream) et une référence constante à un objet Arc (ARCParam) à afficher                           *****
	***** Précondition : Aucune                                                                                                          *****
	***** Sortie : Une référence à un flux de sortie                                                                                     *****
	***** Postcondition : Affiche la valeur de destination de l'arc (iARCDestination) dans le flux de sortie en utilisant                *****
	***** l'opérateur de flux de sortie (<<). Retourne une référence au flux de sortie modifié                                           *****
	*****************************************************************************************************************************************/
	friend std::ostream& operator<< (std::ostream& stream, const Arc& ARCParam);
};


