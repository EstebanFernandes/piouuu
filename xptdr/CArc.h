#pragma once
#include<iostream>
#include "CException.h"
class CArc
{
private :
	double uiARCpoids;
	int iARCDestination;
public :

	/*********************************************
	***** CArc() : Constructeur par d�faut   *****
	**********************************************
	***** Entr�e : Aucune                    *****
	***** Pr�condition : Aucune              *****
	***** Sortie : Aucune                    *****
	***** Postcondition : Cr�e un objet CArc *****
	*********************************************/
	CArc();

	/************************************************************************************
	***** CArc(CArc & ARCParam) : Constructeur de recopie                           *****
	*************************************************************************************
	***** Entr�e : Une r�f�rence � un objet CArc                                    *****
	***** Pr�condition : Aucune                                                     *****
	***** Sortie : Aucune                                                           *****
	***** Postcondition : Cr�e un objet CArc en copiant les valeurs de l'arc source *****
	************************************************************************************/
	CArc(const CArc & ARCParam);

	/*************************************************************************************************
	***** CArc(int iValeur) : Constructeur de confort                                            *****
	**************************************************************************************************
	***** Entr�e : Un entier repr�sentant la valeur de destination de l'arc (iValeur)            *****
	***** Pr�condition : Aucune                                                                  *****
	***** Sortie : Aucune                                                                        *****
	***** Postcondition : Cr�e un objet CArc en initialisant la valeur de destination de l'arc   *****
	***** (iARCDestination) avec la valeur sp�cifi�e (iValeur)                                   *****
	*************************************************************************************************/
	CArc(int iValeur);

	/****************************************************************************************************************************************
	***** CArc(int iValeur, unsigned int poids) : Constructeur de confort                                                               *****
	*****************************************************************************************************************************************
	***** Entr�e : Un entier repr�sentant la valeur de destination de l'arc ainsi qu'un entier repr�sentant la valeur du poids de l'arc *****
	***** Pr�condition : Aucune                                                                                                         *****
	***** Sortie : Aucune                                                                                                               *****
	***** Postcondition : Cr�e un objet CArc initialis� avec la valeur de destination de l'arc ainsi que le poids de l'arc              *****
	****************************************************************************************************************************************/
	CArc(int iValeur, double poids);

	/*************************************************************************
	***** ~CArc() : Destructeur                                          *****
	**************************************************************************
	***** Entr�e : Aucune                                                *****
	***** Pr�condition : Aucune                                          *****
	***** Sortie : Aucune                                                *****
	***** Postcondition : D�truit l'objet CArc et lib�re toute ressource *****
	*************************************************************************/

	~CArc();
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
	***** CArc& operator=(const CArc& ARCParam) : Op�rateur �gale pour la classe CArc                *****
	******************************************************************************************************
	***** Entr�e : ARCParam (r�f�rence constante vers un objet CArc)                                 *****
	***** Pr�condition : Aucune                                                                      *****
	***** Sortie : Une r�f�rence vers l'objet CArc courant                                           *****
	***** Postcondition : L'objet CArc courant est assign� avec les valeurs de l'objet CArc ARCParam *****
	*****************************************************************************************************/
	CArc& operator=(const CArc& ARCParam);

	/*****************************************************************************************************************************************
	***** operator<<(std::ostream & stream, const CArc & ARCParam) : Surcharge de l'op�rateur de sortie (<<) pour afficher un objet CArc *****
	******************************************************************************************************************************************
	***** Entr�e : Un flux de sortie (stream) et une r�f�rence constante � un objet CArc (ARCParam) � afficher                           *****
	***** Pr�condition : Aucune                                                                                                          *****
	***** Sortie : Une r�f�rence � un flux de sortie                                                                                     *****
	***** Postcondition : Affiche la valeur de destination de l'arc (iARCDestination) dans le flux de sortie en utilisant                *****
	***** l'op�rateur de flux de sortie (<<). Retourne une r�f�rence au flux de sortie modifi�                                           *****
	*****************************************************************************************************************************************/
	friend std::ostream& operator<< (std::ostream& stream, const CArc& ARCParam);
};


