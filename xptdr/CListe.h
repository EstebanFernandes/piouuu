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
	***** CListe() : Constructeur par d�faut de la classe CListe                                                 *****
	******************************************************************************************************************
	***** Entr�e : Aucune                                                                                        *****
	***** Pr�condition : Aucune                                                                                  *****
	***** Sortie : Aucune                                                                                        *****
	***** Postcondition : Initialise un objet CListe avec une taille de liste (uiLISTaille) de 0 et un pointeur  *****
	***** de liste (pLLISListe) pointant vers nullptr                                                            *****
	*****************************************************************************************************************/
	CListe();

	/***********************************************************************************************
	***** CListe(CListe<LType> &LisParam) : Constructeur de recopie                            *****
	************************************************************************************************
	***** Entr�e : R�f�rence � un objet CListe (LisParam) � copier                             *****
	***** Pr�condition : Aucune                                                                *****
	***** Sortie : Aucune                                                                      *****
	***** Postcondition : Initialise un nouvel objet CListe avec une de la liste de LisParam,  *****
	***** en copiant la taille de liste (uiLISTaille) et les �l�ments de la liste (pLLISListe) *****
	***********************************************************************************************/
	CListe(CListe<LType> &LisParam);

	/*************************************************************************************************
	***** ~CListe() : Destructeur                                                                *****
	**************************************************************************************************
	***** Entr�e : Aucune                                                                        *****
	***** Pr�condition : Aucune                                                                  *****
	***** Sortie : Aucune                                                                        *****
	***** Postcondition : Lib�re la m�moire allou�e pour la liste (pLLISListe) de l'objet CListe *****
	*************************************************************************************************/
	~CListe();

	/******************************************************************************************************
	***** LISAfficherTaille() : Afficher la taille de la liste                                        *****
	*******************************************************************************************************
	***** Entr�e : Aucune                                                                             *****
	***** Pr�condition : Aucune                                                                       *****
	***** Sortie : Aucune                                                                             *****
	***** Postcondition : Affiche la taille actuelle de la liste (uiLISTaille) sur la sortie standard *****
	******************************************************************************************************/
	void LISAfficherTaille();

	/****************************************************************************************************************************************************
	***** LISAjouter(LType valeur, unsigned int uiPosition) : Ajouter un �l�ment � une position donn�e                                              *****
	*****************************************************************************************************************************************************
	***** Entr�e : Une valeur de type LType � ajouter (valeur) et la position � laquelle l'ajouter (uiPosition)                                     *****
	***** Pr�condition : Aucune                                                                                                                     *****
	***** Sortie : Aucune                                                                                                                           *****
	***** Postcondition :  Ajoute la valeur � la position sp�cifi�e dans la liste (pLLISListe), en d�calant les �l�ments existants vers la droite.  *****
	*****  Si la position est en dehors des limites de la liste, une exception peut �tre lev�e                                                      *****
	****************************************************************************************************************************************************/
	void LISAjouter(LType valeur, unsigned int uiPosition);

	/******************************************************************************************************************************
	***** LISModifier(LType valeur, unsigned int uiPosition) : Modifier un �l�ment � une position donn�e                      *****
	*******************************************************************************************************************************
	***** Entr�e : Une valeur de type LType � mettre � jour (valeur) et la position de l'�l�ment � mettre � jour (uiPosition) *****
	***** Pr�condition : Aucune                                                                                               *****
	***** Sortie : Aucune                                                                                                     *****
	***** Postcondition : Modifie la valeur � la position sp�cifi�e dans la liste (pLLISListe). Si la position est            *****
	***** en dehors des limites de la liste, une exception peut �tre lev�e.                                                   *****
	******************************************************************************************************************************/
	void LISModifier(LType valeur, unsigned int uiPosition);

	/*****************************************************************************************************************************************************
	***** LISSupprimer(unsigned int uiPosition) : Supprimer un �l�ment � une position donn�e                                                         *****
	******************************************************************************************************************************************************
	***** Entr�e : La position de l'�l�ment � supprimer (uiPosition)                                                                                 *****
	***** Pr�condition : Aucune                                                                                                                      *****
	***** Sortie : Aucune                                                                                                                            *****
	***** Postcondition : Supprime l'�l�ment � la position sp�cifi�e dans la liste (pLLISListe), en d�calant les �l�ments suivants vers la gauche.   *****
	***** Si la position est en dehors des limites de la liste, une exception peut �tre lev�e.                                                       *****
	*****************************************************************************************************************************************************/
	void LISSupprimer(unsigned int uiPosition);

	/*********************************************************************************************************************************
	*****  LISAjouterDernier(LType valeur) :  Ajouter un �l�ment � la fin de la liste                                            *****
	**********************************************************************************************************************************
	***** Entr�e : Une valeur de type LType � ajouter (valeur)                                                                   *****
	***** Pr�condition : Aucune                                                                                                  *****
	***** Sortie : Aucune                                                                                                        *****
	***** Postcondition : Ajoute la valeur � la fin de la liste (pLLISListe), en augmentant la taille de la liste (uiLISTaille)  *****
	***** et en d�pla�ant les �l�ments existants vers la droite.                                                                 *****
	*********************************************************************************************************************************/
	void LISAjouterDernier(LType valeur);

	/**************************************************************************************************************************************
	***** LISLire(unsigned int uiPosition) const : Lire la valeur d'un �l�ment � une position donn�e                                  *****
	***************************************************************************************************************************************
	***** Entr�e : La position de l'�l�ment � lire (uiPosition)                                                                       *****
	***** Pr�condition : Aucune                                                                                                       *****
	***** Sortie : Une r�f�rence constante � la valeur de type LType de l'�l�ment � la position sp�cifi�e                             *****
	***** Postcondition : Retourne la valeur de l'�l�ment � la position sp�cifi�e dans la liste (pLLISListe). Si la position est en   *****
	***** dehors des limites de la liste, une exception peut �tre lev�e.                                                              *****
	**************************************************************************************************************************************/
	LType& LISLire(unsigned int uiPosition) const;

	/*******************************************************************
	***** LISTaille() const : Obtenir la taille de la liste        *****
	********************************************************************
	***** Entr�e : AUcune                                          *****
	***** Pr�condition : Aucune                                    *****
	***** Sortie : La taille actuelle de la liste (uiLISTaille)    *****
	***** Postcondition : Retourne la taille actuelle de la liste. *****
	*******************************************************************/
	unsigned int LISTaille() const;

	/*****************************************************************************************************************************************
	***** operator=(const CListe<LType> &ListeB) : Surcharge de l'op�rateur =                                                            *****
	******************************************************************************************************************************************
	***** Entr�e : R�f�rence constante � un objet CListe (ListeB) � assigner                                                             *****
	***** Pr�condition : Aucune                                                                                                          *****
	***** Sortie : Une r�f�rence � l'objet CListe apr�s l'assignation                                                                    *****
	***** Postcondition : Effectue une copie de la liste de ListeB dans l'objet courant, en copiant la taille de liste (uiLISTaille) et  *****
	*****  les �l�ments de la liste (pLLISListe). Retourne une r�f�rence � l'objet CListe courant                                        *****
	*****************************************************************************************************************************************/
	CListe<LType>& operator=(const CListe<LType> &ListeB);

	/*****************************************************************************************************************************
	***** operator[](int iPos) : Acc�der � un �l�ment de la liste via l'op�rateur []                                         *****
	******************************************************************************************************************************
	***** Entr�e : Un entier repr�sentant la position de l'�l�ment � acc�der (iPos)                                          *****
	***** Pr�condition : Aucune                                                                                              *****
	***** Sortie : Une r�f�rence � la valeur de type LType de l'�l�ment � la position sp�cifi�e                              *****
	***** Postcondition : Retourne une r�f�rence � la valeur de l'�l�ment � la position sp�cifi�e dans la liste (pLLISListe) *****
	*****************************************************************************************************************************/
	LType& operator[](int iPos);

	/*************************************************************************************************************************************************************
	*****  operator<< (std::ostream& stream, const CListe<LType>& LISParam) : Surcharge de l'op�rateur de sortie (<<) pour afficher la liste                 *****
	**************************************************************************************************************************************************************
	***** Entr�e : Un flux de sortie (stream) et une r�f�rence constante � un objet CListe (LISParam) � afficher                                             *****
	***** Pr�condition : Aucune                                                                                                                              *****
	***** Sortie : Une r�f�rence � un flux de sortie (stream)                                                                                                *****
	***** Postcondition : Affiche le contenu de la liste (pLLISListe) dans le flux de sortie (stream). Si la liste est vide, affiche "Liste vide".           *****
	***** Sinon, affiche chaque �l�ment de la liste sur une nouvelle ligne en utilisant l'op�rateur de flux de sortie (<<) pour les valeurs de type LType.   *****
	***** Retourne une r�f�rence au flux de sortie modifi�                                                                                                   *****
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