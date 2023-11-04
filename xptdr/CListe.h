#pragma once
#define Ajouter true
#define Supprimer false
#include<iostream>
#include"CException.h"
#include<stdio.h>
#include "CException.h"
template <class LType> class CListe
{
private:
	unsigned int uiLISTaille;
	LType * pLLISListe;
public:

	/*****************************************************************************************************************
	***** CListe() : Constructeur par défaut de la classe CListe                                                 *****
	******************************************************************************************************************
	***** Entrée : Aucune                                                                                        *****
	***** Précondition : Aucune                                                                                  *****
	***** Sortie : Aucune                                                                                        *****
	***** Postcondition : Initialise un objet CListe avec une taille de liste (uiLISTaille) de 0 et un pointeur  *****
	***** de liste (pLLISListe) pointant vers nullptr                                                            *****
	*****************************************************************************************************************/
	CListe();

	/***********************************************************************************************
	***** CListe(CListe<LType> &LisParam) : Constructeur de recopie                            *****
	************************************************************************************************
	***** Entrée : Référence à un objet CListe (LisParam) à copier                             *****
	***** Précondition : Aucune                                                                *****
	***** Sortie : Aucune                                                                      *****
	***** Postcondition : Initialise un nouvel objet CListe avec une de la liste de LisParam,  *****
	***** en copiant la taille de liste (uiLISTaille) et les éléments de la liste (pLLISListe) *****
	***********************************************************************************************/
	CListe(CListe<LType> &LisParam);

	/*************************************************************************************************
	***** ~CListe() : Destructeur                                                                *****
	**************************************************************************************************
	***** Entrée : Aucune                                                                        *****
	***** Précondition : Aucune                                                                  *****
	***** Sortie : Aucune                                                                        *****
	***** Postcondition : Libère la mémoire allouée pour la liste (pLLISListe) de l'objet CListe *****
	*************************************************************************************************/
	~CListe();

	/******************************************************************************************************
	***** LISAfficherTaille() : Afficher la taille de la liste                                        *****
	*******************************************************************************************************
	***** Entrée : Aucune                                                                             *****
	***** Précondition : Aucune                                                                       *****
	***** Sortie : Aucune                                                                             *****
	***** Postcondition : Affiche la taille actuelle de la liste (uiLISTaille) sur la sortie standard *****
	******************************************************************************************************/
	void LISAfficherTaille();

	/****************************************************************************************************************************************************
	***** LISAjouter(LType valeur, unsigned int uiPosition) : Ajouter un élément à une position donnée                                              *****
	*****************************************************************************************************************************************************
	***** Entrée : Une valeur de type LType à ajouter (valeur) et la position à laquelle l'ajouter (uiPosition)                                     *****
	***** Précondition : Aucune                                                                                                                     *****
	***** Sortie : Aucune                                                                                                                           *****
	***** Postcondition :  Ajoute la valeur à la position spécifiée dans la liste (pLLISListe), en décalant les éléments existants vers la droite.  *****
	*****  Si la position est en dehors des limites de la liste, une exception peut être levée                                                      *****
	****************************************************************************************************************************************************/
	void LISAjouter(LType valeur, unsigned int uiPosition);

	/******************************************************************************************************************************
	***** LISModifier(LType valeur, unsigned int uiPosition) : Modifier un élément à une position donnée                      *****
	*******************************************************************************************************************************
	***** Entrée : Une valeur de type LType à mettre à jour (valeur) et la position de l'élément à mettre à jour (uiPosition) *****
	***** Précondition : Aucune                                                                                               *****
	***** Sortie : Aucune                                                                                                     *****
	***** Postcondition : Modifie la valeur à la position spécifiée dans la liste (pLLISListe). Si la position est            *****
	***** en dehors des limites de la liste, une exception peut être levée.                                                   *****
	******************************************************************************************************************************/
	void LISModifier(LType valeur, unsigned int uiPosition);

	/*****************************************************************************************************************************************************
	***** LISSupprimer(unsigned int uiPosition) : Supprimer un élément à une position donnée                                                         *****
	******************************************************************************************************************************************************
	***** Entrée : La position de l'élément à supprimer (uiPosition)                                                                                 *****
	***** Précondition : Aucune                                                                                                                      *****
	***** Sortie : Aucune                                                                                                                            *****
	***** Postcondition : Supprime l'élément à la position spécifiée dans la liste (pLLISListe), en décalant les éléments suivants vers la gauche.   *****
	***** Si la position est en dehors des limites de la liste, une exception peut être levée.                                                       *****
	*****************************************************************************************************************************************************/
	void LISSupprimer(unsigned int uiPosition);

	/*********************************************************************************************************************************
	*****  LISAjouterDernier(LType valeur) :  Ajouter un élément à la fin de la liste                                            *****
	**********************************************************************************************************************************
	***** Entrée : Une valeur de type LType à ajouter (valeur)                                                                   *****
	***** Précondition : Aucune                                                                                                  *****
	***** Sortie : Aucune                                                                                                        *****
	***** Postcondition : Ajoute la valeur à la fin de la liste (pLLISListe), en augmentant la taille de la liste (uiLISTaille)  *****
	***** et en déplaçant les éléments existants vers la droite.                                                                 *****
	*********************************************************************************************************************************/
	void LISAjouterDernier(LType valeur);

	/**************************************************************************************************************************************
	***** LISLire(unsigned int uiPosition) const : Lire la valeur d'un élément à une position donnée                                  *****
	***************************************************************************************************************************************
	***** Entrée : La position de l'élément à lire (uiPosition)                                                                       *****
	***** Précondition : Aucune                                                                                                       *****
	***** Sortie : Une référence constante à la valeur de type LType de l'élément à la position spécifiée                             *****
	***** Postcondition : Retourne la valeur de l'élément à la position spécifiée dans la liste (pLLISListe). Si la position est en   *****
	***** dehors des limites de la liste, une exception peut être levée.                                                              *****
	**************************************************************************************************************************************/
	LType& LISLire(unsigned int uiPosition) const;

	/*******************************************************************
	***** LISTaille() const : Obtenir la taille de la liste        *****
	********************************************************************
	***** Entrée : AUcune                                          *****
	***** Précondition : Aucune                                    *****
	***** Sortie : La taille actuelle de la liste (uiLISTaille)    *****
	***** Postcondition : Retourne la taille actuelle de la liste. *****
	*******************************************************************/
	unsigned int LISTaille() const;

	/*****************************************************************************************************************************************
	***** operator=(const CListe<LType> &ListeB) : Surcharge de l'opérateur =                                                            *****
	******************************************************************************************************************************************
	***** Entrée : Référence constante à un objet CListe (ListeB) à assigner                                                             *****
	***** Précondition : Aucune                                                                                                          *****
	***** Sortie : Une référence à l'objet CListe après l'assignation                                                                    *****
	***** Postcondition : Effectue une copie de la liste de ListeB dans l'objet courant, en copiant la taille de liste (uiLISTaille) et  *****
	*****  les éléments de la liste (pLLISListe). Retourne une référence à l'objet CListe courant                                        *****
	*****************************************************************************************************************************************/
	CListe<LType>& operator=(const CListe<LType> &ListeB);

	/*****************************************************************************************************************************
	***** operator[](int iPos) : Accéder à un élément de la liste via l'opérateur []                                         *****
	******************************************************************************************************************************
	***** Entrée : Un entier représentant la position de l'élément à accéder (iPos)                                          *****
	***** Précondition : Aucune                                                                                              *****
	***** Sortie : Une référence à la valeur de type LType de l'élément à la position spécifiée                              *****
	***** Postcondition : Retourne une référence à la valeur de l'élément à la position spécifiée dans la liste (pLLISListe) *****
	*****************************************************************************************************************************/
	LType& operator[](int iPos);

	/*************************************************************************************************************************************************************
	*****  operator<< (std::ostream& stream, const CListe<LType>& LISParam) : Surcharge de l'opérateur de sortie (<<) pour afficher la liste                 *****
	**************************************************************************************************************************************************************
	***** Entrée : Un flux de sortie (stream) et une référence constante à un objet CListe (LISParam) à afficher                                             *****
	***** Précondition : Aucune                                                                                                                              *****
	***** Sortie : Une référence à un flux de sortie (stream)                                                                                                *****
	***** Postcondition : Affiche le contenu de la liste (pLLISListe) dans le flux de sortie (stream). Si la liste est vide, affiche "Liste vide".           *****
	***** Sinon, affiche chaque élément de la liste sur une nouvelle ligne en utilisant l'opérateur de flux de sortie (<<) pour les valeurs de type LType.   *****
	***** Retourne une référence au flux de sortie modifié                                                                                                   *****
	*************************************************************************************************************************************************************/
	friend std::ostream& operator<< (std::ostream& stream, const CListe<LType>& LISParam) 
	{
		if (LISParam.LISTaille() == 0) stream << "     >Liste vide<\n";
		else
		{
			for (unsigned int uiBoucle = 0; uiBoucle < LISParam.LISTaille(); uiBoucle++)
			{
				stream << LISParam.LISLire(uiBoucle) << "\n";
			}
		}
		return stream;
	}
private:
	void LISCopiermemoire(bool type);
};


#include"CListe.cpp"