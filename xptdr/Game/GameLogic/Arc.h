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
	***** Arc() : Constructeur par d�faut   *****
	**********************************************
	***** Entr�e : Aucune                    *****
	***** Pr�condition : Aucune              *****
	***** Sortie : Aucune                    *****
	***** Postcondition : Cr�e un objet Arc *****
	*********************************************/
	Arc();

	/************************************************************************************
	***** Arc(Arc & ARCParam) : Constructeur de recopie                           *****
	*************************************************************************************
	***** Entr�e : Une r�f�rence � un objet Arc                                    *****
	***** Pr�condition : Aucune                                                     *****
	***** Sortie : Aucune                                                           *****
	***** Postcondition : Cr�e un objet Arc en copiant les valeurs de l'arc source *****
	************************************************************************************/
	Arc(const Arc & ARCParam);

	/*************************************************************************************************
	***** Arc(int iValeur) : Constructeur de confort                                            *****
	**************************************************************************************************
	***** Entr�e : Un entier repr�sentant la valeur de destination de l'arc (iValeur)            *****
	***** Pr�condition : Aucune                                                                  *****
	***** Sortie : Aucune                                                                        *****
	***** Postcondition : Cr�e un objet Arc en initialisant la valeur de destination de l'arc   *****
	***** (iARCDestination) avec la valeur sp�cifi�e (iValeur)                                   *****
	*************************************************************************************************/
	Arc(int iValeur);

	/****************************************************************************************************************************************
	***** Arc(int iValeur, unsigned int poids) : Constructeur de confort                                                               *****
	*****************************************************************************************************************************************
	***** Entr�e : Un entier repr�sentant la valeur de destination de l'arc ainsi qu'un entier repr�sentant la valeur du poids de l'arc *****
	***** Pr�condition : Aucune                                                                                                         *****
	***** Sortie : Aucune                                                                                                               *****
	***** Postcondition : Cr�e un objet Arc initialis� avec la valeur de destination de l'arc ainsi que le poids de l'arc              *****
	****************************************************************************************************************************************/
	Arc(int iValeur, double poids);

	/*************************************************************************
	***** ~Arc() : Destructeur                                          *****
	**************************************************************************
	***** Entr�e : Aucune                                                *****
	***** Pr�condition : Aucune                                          *****
	***** Sortie : Aucune                                                *****
	***** Postcondition : D�truit l'objet Arc et lib�re toute ressource *****
	*************************************************************************/

	~Arc();
	/**********************************************************************************************
	***** ARCObtenirDest() : Obtenir la valeur de destination de l'arc                        *****
	***********************************************************************************************
	***** Entr�e : Aucune                                                                     *****
	***** Pr�condition : Aucune                                                               *****
	***** Sortie : Un entier repr�sentant la valeur de destination de l'arc (iARCDestination) *****
	***** Postcondition : Retourne la valeur de destination de l'arc (iARCDestination)        *****
	**********************************************************************************************/
	int ARCObtenirDest();

	/**********************************************************************
	***** ARCObtenirPoids() : Obtenir la valeur du poids de l'arc     *****
	***********************************************************************
	***** Entr�e : Aucune                                             *****
	***** Pr�condition : Aucune                                       *****
	***** Sortie : Un entier repr�sentant la valeur du poids de l'arc *****
	***** Postcondition : Retourne la valeur du poids de l'arc        *****
	**********************************************************************/
	double ARCObtenirPoids() { return uiARCpoids; }

	/*****************************************************************************************************
	***** ARCModifier(int iValeur) : Modifier la valeur de destination de l'arc                      *****
	******************************************************************************************************
	***** Entr�e : Un entier repr�sentant la nouvelle valeur de destination de l'arc (iValeur)       *****
	***** Pr�condition : Aucune                                                                      *****
	***** Sortie : Aucune                                                                            *****
	***** Postcondition : Modifie la valeur de destination de l'arc (iARCDestination) en utilisant   *****
	***** la nouvelle valeur sp�cifi�e (iValeur)                                                     *****
	*****************************************************************************************************/
	void ARCModifier(int iValeur);

	/************************************************************************************************
	***** ARCModifier(unsigned int poids) : Modifier la valeur du poids de l'arc                *****
	*************************************************************************************************
	***** Entr�e : Un entier positif repr�sentant la nouvelle valeur du poids de l'arc          *****
	***** Pr�condition : Aucune                                                                 *****
	***** Sortie : Aucune                                                                       *****
	***** Postcondition : Modifie la valeur du poids de l'arc avec la nouvelle valeur sp�cifi�e *****
	************************************************************************************************/
	void ARCModifier(double poids);

	/********************************************************************************************************************************************************
	***** ARCModifier(int iDestination, unsigned int poids) : Modifier la valeur du poids de l'arc et la valeur de destination de l'arc                 *****
	*********************************************************************************************************************************************************
	***** Entr�e : Un entier positif repr�sentant la nouvelle valeur du poids de l'arc ainsi qu'un entier repr�sentant la nouvelle destination de l'arc *****
	***** Pr�condition : Aucune                                                                                                                         *****
	***** Sortie : Aucune                                                                                                                               *****
	***** Postcondition : Modifie la valeur du poids de l'arc et la destination de l'arc avec les nouvelles valeurs sp�cifi�es                          *****
	********************************************************************************************************************************************************/
	void ARCModifier(int iDestination, double poids);

	/*****************************************************************************************************
	***** Arc& operator=(const Arc& ARCParam) : Op�rateur �gale pour la classe Arc                *****
	******************************************************************************************************
	***** Entr�e : ARCParam (r�f�rence constante vers un objet Arc)                                 *****
	***** Pr�condition : Aucune                                                                      *****
	***** Sortie : Une r�f�rence vers l'objet Arc courant                                           *****
	***** Postcondition : L'objet Arc courant est assign� avec les valeurs de l'objet Arc ARCParam *****
	*****************************************************************************************************/
	Arc& operator=(const Arc& ARCParam);

	/*****************************************************************************************************************************************
	***** operator<<(std::ostream & stream, const Arc & ARCParam) : Surcharge de l'op�rateur de sortie (<<) pour afficher un objet Arc *****
	******************************************************************************************************************************************
	***** Entr�e : Un flux de sortie (stream) et une r�f�rence constante � un objet Arc (ARCParam) � afficher                           *****
	***** Pr�condition : Aucune                                                                                                          *****
	***** Sortie : Une r�f�rence � un flux de sortie                                                                                     *****
	***** Postcondition : Affiche la valeur de destination de l'arc (iARCDestination) dans le flux de sortie en utilisant                *****
	***** l'op�rateur de flux de sortie (<<). Retourne une r�f�rence au flux de sortie modifi�                                           *****
	*****************************************************************************************************************************************/
	friend std::ostream& operator<< (std::ostream& stream, const Arc& ARCParam);
};


