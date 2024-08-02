#pragma once
#define Arrivant true
#define Partant false
#include <vector>
#include "Arc.h"

const int ARC_NON_TROUVEE = -999;

class Sommet   
{
protected :
	int iSOMNumero;
	std::vector<Arc> lisSOMArcArrivant;
	std::vector<Arc> lisSOMArcPartant;
public :

	/**************************************************************************************
	***** Sommet() : Constructeur par défaut                                         *****
	***************************************************************************************
	***** Entrée : Aucune                                                             *****
	***** Précondition : Aucune                                                       *****
	***** Sortie : Aucune                                                             *****
	***** Postcondition : Crée un objet Sommet sans aucune initialisation spécifique *****
	**************************************************************************************/
	Sommet();

	/**************************************************************************************************
	***** Sommet(int Num) : Constructeur de confort                                              *****
	***************************************************************************************************
	***** Entrée : Un entier représentant le numéro du sommet (Num)                               *****
	***** Précondition : Aucune                                                                   *****
	***** Sortie : Aucune                                                                         *****
	***** Postcondition : Crée un objet Sommet en initialisant le numéro du sommet (iSOMNumero)  *****
	***** avec la valeur spécifiée (Num)                                                          *****
	**************************************************************************************************/
	Sommet(int Num);

	/***********************************************************************************************************************************
	***** Sommet(Sommet & SOMParam) : Constructeur de recopie                                                                    *****
	************************************************************************************************************************************
	***** Entrée : Une référence à un objet Sommet (SOMParam) à copier                                                            *****
	***** Précondition : Aucune                                                                                                    *****
	***** Sortie : Aucune                                                                                                          *****
	***** Postcondition : Crée un objet Sommet en copiant les valeurs du sommet source (SOMParam), y compris le numéro du sommet  *****
	***** (iSOMNumero) et les listes d'arcs arrivants et partants                                                                  *****
	***********************************************************************************************************************************/
	Sommet(const Sommet& SOMParam);

	/*************************************************************************************
	***** ~Sommet() : Destructeur                                                   *****
	**************************************************************************************
	***** Entrée : Aucune                                                            *****
	***** Précondition : Aucune                                                      *****
	***** Sortie : Aucune                                                            *****
	***** Postcondition : Détruit l'objet Sommet et libère toute ressource associée *****
	*************************************************************************************/
	~Sommet();

	/***************************************************************************
	***** SOMLireNumero() const : Lire le numéro du sommet                 *****
	****************************************************************************
	***** Entrée : Aucune                                                  *****
	***** Précondition : Aucune                                            *****
	***** Sortie : Un entier représentant le numéro du sommet (iSOMNumero) *****
	***** Postcondition : Retourne le numéro du sommet                     *****
	***************************************************************************/
	int SOMLireNumero() const;

	/****************************************************************************************************
	***** SOMModifierNumero(int NouveauNumero) : Modifie le numéro du sommet                           *****
	*****************************************************************************************************
	***** Entrée : Un entier représentant le nouveau numéro du sommet (NouveauNumero)                *****
	***** Précondition : Aucune                                                                      *****
	***** Sortie : Aucune                                                                            *****
	***** Postcondition : Met à jour le numéro du sommet avec la nouvelle valeur spécifiée            *****
	****************************************************************************************************/
	void SOMModifierNumero(int NouveauNumero) {
		iSOMNumero = NouveauNumero;
	}

	/***************************************************************************************************************************************************
	***** SOMAjouterArc(bool type, int Destination) : Ajouter un arc au sommet                                                                     *****
	****************************************************************************************************************************************************
	***** Entrée : Un booléen représentant le type d'arc (type) : Arrivant ou Partant, et un entier                                                *****
	***** représentant la destination de l'arc (Destination)                                                                                       *****
	***** Précondition : Aucune                                                                                                                    *****
	***** Sortie : Aucune                                                                                                                          *****
	***** Postcondition : Ajoute un nouvel arc à la liste d'arcs arrivants (lisSOMArcArrivant) ou à la liste d'arcs partants (lisSOMArcPartant),   *****
	***** en fonction du type d'arc spécifié. L'arc est créé avec la destination spécifiée                                                         *****
	***************************************************************************************************************************************************/
	void SOMAjouterArc(bool type,int Destination);

	/*********************************************************************************************************************************************
	***** SOMAjouterArc(bool type, Arc Arc) : Surcharge de la fonction SOMAjouter ajouter pour le cas où on a déjà l'arc qu'on veut ajouter *****
	**********************************************************************************************************************************************
	***** Entrée : un bool qui précise le type et un Arc qu'on va ajouter au sommet                                                         *****
	***** Précondition : Aucune                                                                                                              *****
	***** Sortie : Aucune                                                                                                                    *****
	***** Postcondition : L'arc est ajouté au sommet                                                                                         *****
	*********************************************************************************************************************************************/
	void SOMAjouterArc(bool type, Arc Arc);

	/*******************************************************************************************************************************************************
	***** SOMModifierArc(bool type, int AncienneDestination, int NouvelleDestination) : Modifier la destination d'un arc dans le sommet                *****
	********************************************************************************************************************************************************
	***** Entrée : Un booléen représentant le type d'arc (type) : Arrivant ou Partant, un entier représentant l'ancienne destination de l'arc          *****
	***** (AncienneDestination) et un entier représentant la nouvelle destination de l'arc (NouvelleDestination)                                       *****
	***** Précondition : Aucune                                                                                                                        *****
	***** Sortie : Aucune                                                                                                                              *****
	***** Postcondition : Modifie la destination de l'arc spécifié dans la liste d'arcs arrivants (lisSOMArcArrivant) ou dans la liste d'arcs		   *****
	***** partants (lisSOMArcPartant), en fonction du type d'arc spécifié																			   *****
	*******************************************************************************************************************************************************/
	void SOMModifierArc(bool type, int AncienneDestination, int NouvelleDestination);

	/****************************************************************************************************************
	***** SOMModifierArc(bool type, int Destination, unsigned int uipoids) : Modifier le poids d'un arc         *****
	*****************************************************************************************************************
	***** Entrée : un bool qui précise le type, la destination de l'arc à modifier et le nouveau poids de l'arc *****
	***** Précondition : Aucune                                                                                 *****
	***** Sortie : Aucune                                                                                       *****
	***** Postcondition : L'arc est modifié avec un nouveau poids                                               *****
	****************************************************************************************************************/
	void SOMModifierArc(bool type, int Destination, double dPoids);

	/***************************************************************************************************************************************
	***** SOMSupprimerArc(bool type, int Destination) : Supprimer un arc du sommet                                                     *****
	****************************************************************************************************************************************
	***** Entrée : Un booléen représentant le type d'arc (type) : Arrivant ou Partant, et un entier                                    *****
	***** Précondition : Aucune                                                                                                        *****
	***** Sortie : Aucune                                                                                                              *****
	***** Postcondition : Supprime l'arc correspondant à la destination spécifiée de la liste d'arcs arrivants (lisSOMArcArrivant) ou  *****
	***** de la liste d'arcs partants (lisSOMArcPartant), en fonction du type d'arc spécifié                                           *****
	***************************************************************************************************************************************/
	void SOMSupprimerArc(bool type,int Destination);

	/******************************************************************************************************************************************************
	***** SOMRechercherArc(bool type, int Element) : Rechercher un arc dans le sommet																  *****
	*******************************************************************************************************************************************************
	***** Entrée : Un booléen représentant le type d'arc (type) : Arrivant ou Partant, et un entier représentant la destination de					  *****
	***** l'arc à rechercher (Element)																												  *****
	***** Précondition : Aucune																														  *****
	***** Sortie : Un entier représentant l'indice de l'arc trouvé dans la liste d'arcs arrivants (lisSOMArcArrivant) ou dans la liste				  *****
	***** d'arcs partants (lisSOMArcPartant). Retourne -999 si l'arc n'est pas trouvé																  *****
	***** Postcondition : Parcourt la liste d'arcs arrivants (lisSOMArcArrivant) ou la liste d'arcs partants (lisSOMArcPartant), en fonction du		  *****
	***** type d'arc spécifié, et recherche l'arc ayant la destination spécifiée. Retourne l'indice de l'arc trouvé ou -999 si l'arc n'est pas trouvé *****
	******************************************************************************************************************************************************/
	int SOMRechercherArc(bool type, int Element);

	/*****************************************************************************************************************************************
	***** operator=(Sommet & SOMParam) : Surcharge de l'opérateur d'affectation (=) pour copier un sommet                               *****
	******************************************************************************************************************************************
	***** Entrée : Une référence à un objet Sommet (SOMParam) à copier                                                                  *****
	***** Précondition : Aucune                                                                                                          *****
	***** Sortie : Une référence à un objet Sommet                                                                                      *****
	***** Postcondition : Copie les valeurs du sommet source (SOMParam) dans l'objet actuel, y compris le numéro du sommet (iSOMNumero)  *****
	***** et les listes d'arcs arrivants et partants. Retourne une référence à l'objet Sommet modifié                                   *****
	*****************************************************************************************************************************************/
	Sommet& operator=(const Sommet& SOMParam);

	/***********************************************************************************************************************************************
	***** operator<<(std::ostream & stream, const Sommet & SOMParam) : Surcharge de l'opérateur de sortie (<<) pour afficher un objet Sommet *****
	************************************************************************************************************************************************
	***** Entrée : Un flux de sortie (stream) et une référence constante à un objet Sommet (SOMParam) à afficher                              *****
	***** Précondition : Aucune                                                                                                                *****
	***** Sortie :  Une référence à un flux de sortie                                                                                          *****
	***** Postcondition : Affiche le numéro du sommet (iSOMNumero), ainsi que les listes d'arcs arrivants et partants (lisSOMArcArrivant et    *****
	*****  lisSOMArcPartant) dans le flux de sortie (stream) en utilisant l'opérateur de flux de sortie (<<). Retourne une référence           *****
	***** au flux de sortie modifié                                                                                                            *****
	***********************************************************************************************************************************************/
	friend std::ostream& operator<< (std::ostream& stream, const Sommet& SOMParam);
	
	/****************************************************************************************************************************
	***** CListe<Arc>& SOMLireArcArrivant() : Retourne une référence à la liste des arcs arrivant                          *****
	*****************************************************************************************************************************
	***** Entrée : Aucune                                                                                                   *****
	***** Précondition : Aucune                                                                                             *****
	***** Sortie : Une référence à une liste d'objets de type "Arc"                                                        *****
	***** Postcondition : La fonction renvoie une référence à la liste des arcs arrivant (lisSOMArcArrivant) de l'objet SOM *****
	****************************************************************************************************************************/
	std::vector<Arc>& SOMLireArcArrivant() {
		return lisSOMArcArrivant;
	}

	/**************************************************************************************************************************
	***** CListe<Arc>& SOMLireArcPartant() : Retourne une référence à la liste des arcs partants                         *****
	***************************************************************************************************************************
	***** Entrée : Aucune                                                                                                 *****
	***** Précondition : Aucune                                                                                           *****
	***** Sortie : Une référence à une liste d'objets de type "Arc"                                                      *****
	***** Postcondition : La fonction renvoie une référence à la liste des arcs partant (lisSOMArcPartant) de l'objet SOM *****
	**************************************************************************************************************************/
	std::vector<Arc>& SOMLireArcPartant() {
		return lisSOMArcPartant;
	}

	/*******************************************************************************************
	***** unsigned int SOMTailleListeArc(bool type) : Donne la taille de la liste des arcs *****
	********************************************************************************************
	***** Entrée : Un booléen représentant le type d'arc (type) : Arrivant ou Partant      *****
	***** Précondition : Aucune                                                            *****
	***** Sortie : Un entier représentant la taille de l'arc                               *****
	***** Postcondition : Retourne la taille de la liste de l'arc demandé                  *****
	*******************************************************************************************/
	unsigned int SOMTailleListeArc(bool type) {
		if (type == Arrivant) return (unsigned int)lisSOMArcArrivant.size();
		else {
			return (unsigned int)lisSOMArcPartant.size();
		}
	}
};

