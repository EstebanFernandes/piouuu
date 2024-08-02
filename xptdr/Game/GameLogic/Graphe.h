#pragma once
#define Oriente true
#define NonOriente false
#include"SommetUpgrade.h"

const int SOMMET_NON_TROUVEE = -998;

class Graphe
{
protected :
	bool bGRAType;
	std::vector<SommetUpgrade> lisGRAListeSommet;
public:

	/*****************************************************************************
	***** Graphe() : Constructeur par défaut                                *****
	******************************************************************************
	***** Entrée : Aucune                                                    *****
	***** Précondition : Aucune                                              *****
	***** Sortie : Aucune                                                    *****
	***** Postcondition : L'objet Graphe est créé et est par défaut orienté *****
	*****************************************************************************/
	Graphe();

	/***********************************************************************************
	***** Graphe(bool bParam) : Constructeur de confort                           *****
	************************************************************************************
	***** Entrée : bParam (booléen représentant le type de graphe)                 *****
	***** Précondition : Aucune                                                    *****
	***** Sortie : Aucune                                                          *****
	***** Postcondition : L'objet Graphe est créé avec le type de graphe spécifié *****
	***********************************************************************************/
	Graphe(bool bParam);

	/*******************************************************************************************************************************************************
	***** Graphe(Graphe & GRAParam) : Constructeur de recopie                                                                                        *****
	********************************************************************************************************************************************************
	***** Entrée : Une référence à un objet Graphe (GRAParam) à copier                                                                                *****
	***** Précondition : Aucune                                                                                                                        *****
	***** Sortie : Aucune                                                                                                                              *****
	***** Postcondition : Crée un objet Graphe en copiant les valeurs du graphe source (GRAParam), y compris la liste des sommets (lisGRAListeSommet) *****
	*******************************************************************************************************************************************************/
	Graphe(Graphe& GRAParam);

	/*************************************************************************************
	***** ~Graphe() : Destructeur                                                   *****
	**************************************************************************************
	***** Entrée : Aucune                                                            *****
	***** Précondition : Aucune                                                      *****
	***** Sortie : Aucune                                                            *****
	***** Postcondition : Détruit l'objet Graphe et libère toute ressource associée *****
	*************************************************************************************/
	~Graphe();

	/***************************************************************************************************************************************************************
	***** GRATrouverSommet(int Identifiant) : Trouver un sommet dans le graphe                                                                                 *****
	****************************************************************************************************************************************************************
	***** Entrée : Un entier représentant l'identifiant du sommet à rechercher (Identifiant)                                                                   *****
	***** Précondition : Aucune                                                                                                                                *****
	***** Sortie : Un entier représentant l'indice du sommet trouvé dans la liste des sommets (lisGRAListeSommet). Retourne -998 si le sommet n'est pas trouvé *****
	***** Postcondition : Parcourt la liste des sommets (lisGRAListeSommet) et recherche le sommet ayant l'identifiant spécifié.                               *****
	***** Retourne l'indice du sommet trouvé ou -998 si le sommet n'est pas trouvé                                                                             *****
	***************************************************************************************************************************************************************/
	int GRATrouverSommet(int Identifiant);

	/*******************************************************************************************
	***** GRARetourneNbSommet() : Retourne le nombre de sommets du graphe                  *****
	********************************************************************************************
	***** Entrée : Aucune                                                                  *****
	***** Précondition : Aucune                                                            *****
	***** Sortie : Le nombre de sommets présent dans le graphe                             *****
	***** Postcondition : Retourne le nombre de sommets présents dans la liste des sommets *****
	*******************************************************************************************/
	unsigned int GRARetourneNbSommet() { return (unsigned int)lisGRAListeSommet.size(); }

	/*****************************************************************************************
	***** GRARetourneType() : Retourne le type de graphe                                 *****
	******************************************************************************************
	***** Entrée : Aucune                                                                *****
	***** Précondition : Aucune                                                          *****
	***** Sortie : Le type de graphe                                                     *****
	***** Postcondition : Retourne le type du graphe c'est à dire orienté ou non orienté *****
	*****************************************************************************************/
	bool GRARetourneType() { return bGRAType; }

	/**********************************************************************************************************************************
	***** GRAAjouterSommet(int NumSommet) : Ajouter un sommet au graphe                                                           *****
	***********************************************************************************************************************************
	***** Entrée : Un entier représentant le numéro du sommet à ajouter (NumSommet)                                               *****
	***** Précondition : Aucune                                                                                                   *****
	***** Sortie : Aucune                                                                                                         *****
	***** Postcondition : Ajoute un nouveau sommet à la liste des sommets (lisGRAListeSommet) avec le numéro spécifié (NumSommet) *****
	**********************************************************************************************************************************/
	void GRAAjouterSommet(int NumSommet);

	void GRAAjouterSommet(SommetUpgrade temp);

	/*********************************************************************************************************************
	***** GRAModifierSommet(int AncienNum, int NouveauNum) : Modifier un sommet dans le graphe                       *****
	**********************************************************************************************************************
	***** Entrée : Deux entiers représentant le numéro d'origine du sommet à modifier et le nouveau numéro du sommet *****
	***** Précondition : Le sommet d'origine existe dans le graphe.													 *****
	***** Sortie : Aucune																							 *****
	***** Postcondition : Modifie le numéro du sommet d'origine par le nouveau numéro spécifié.						 *****
	***** Lance une exception de type int si le sommet n'est pas trouvé.											 *****
	*********************************************************************************************************************/
	void GRAModifierSommet(int AncienNum, int NouveauNum);
	
	/*****************************************************************************************************************************
	***** GRASupprimerSommet(int NumSommet) : Supprimer un sommet du graphe                                                  *****
	******************************************************************************************************************************
	***** Entrée : Un entier représentant le numéro du sommet à supprimer (NumSommet)                                        *****
	***** Précondition : Aucune                                                                                              *****
	***** Sortie : Aucune                                                                                                    *****
	***** Postcondition : Supprime le sommet correspondant au numéro spécifié de la liste des sommets (lisGRAListeSommet).   *****
	***** Lance une exception de type Exception si le sommet n'est pas trouvé                                               *****
	*****************************************************************************************************************************/
	void GRASupprimerSommet( int NumSommet);

	/*****************************************************************************************************************************************
	***** GRAAjouterArc(int iSource, int iDestination) : Ajouter un arc au graphe                                                        *****
	******************************************************************************************************************************************
	***** Entrée : Deux entiers représentant les numéros des sommets source et destination de l'arc (iSource, iDestination)              *****
	***** Précondition : Aucune                                                                                                          *****
	***** Sortie : Aucune                                                                                                                *****
	***** Postcondition : Ajoute un nouvel arc reliant les sommets source et destination dans la liste des sommets (lisGRAListeSommet).  *****
	***** Lance une exception de type int si l'un des sommets n'est pas trouvé                                                           *****
	*****************************************************************************************************************************************/
	void GRAAjouterArc( int iSource, int iDestination);

	/**********************************************************************************************************************************************************
	***** GRAAjouterArc(int iSource, int iDestination, unsigned int uipoids) : Ajoute un arc au graphe en précisant son poids si celui-ci est non orienté *****
	***********************************************************************************************************************************************************
	***** Entrée : Deux entiers représentant les numéros des sommets source et destination de l'arc et un entier représentant le poids de l'arc à créer   *****
	***** Précondition : Aucune                                                                                                                           *****
	***** Sortie : Aucune                                                                                                                                 *****
	***** Postcondition : Ajoute un arc reliant les sommets source et destination et si le graphe est non orienté le poids sur l'arc est ajouté.          *****
	***** Lance une exception si l'un des sommets n'est pas trouvé                                                                                        *****
	**********************************************************************************************************************************************************/
	void GRAAjouterArc(int iSource, int iDestination, double dpoids);

	/******************************************************************************************************************************************************
	***** GRAModifierArc(int AncienSource, int AncienneDestination, int NouvelleSource, int NouvelleDestination) : Modifier un arc dans le graphe     *****
	*******************************************************************************************************************************************************
	***** Entrée : Quatre entiers représentant les numéros des sommets source et destination de l'arc à modifier : AncienSource, AncienneDestination, *****
	***** NouvelleSource, NouvelleDestination																										  *****
	***** Précondition : les sommets existent																										  *****
	***** Sortie : Aucune																															  *****
	***** Postcondition : Modifie l'arc reliant les sommets source et destination d'origine par un nouvel arc reliant les sommets source et			  *****
	***** destination de remplacement. Lance une exception de type int si l'un des sommets n'est pas trouvé.										  *****
	******************************************************************************************************************************************************/
	void GRAModifierArc(int AncienSource, int AncienneDestination, int NouvelleSource, int NouvelleDestination);

	/*********************************************************************************************************************************************************
	***** GRAModifierArc(int iSource, int iDestination, unsigned int uipoids) : Modifie la valeur du poids de l'arc                                      *****
	**********************************************************************************************************************************************************
	***** Entrée : Deux entiers représentant les numéros des sommets source et destination de l'arc et un entier représentant le nouveau poids de l'arc  *****
	***** Précondition : Aucune                                                                                                                          *****
	***** Sortie : Aucune                                                                                                                                *****
	***** Postcondition : Modifie le valeur du poids de l'arc si celui-ci est trouvé sinon une exception est lancé                                       *****
	*********************************************************************************************************************************************************/
	void GRAModifierArc(int iSource, int iDestination, double dpoids);

	/*****************************************************************************************************************************************
	***** GRASupprimerArc(int iSource, int iDestination) : Supprime un arc au graphe                                                     *****
	******************************************************************************************************************************************
	***** Entrée : Deux entiers représentant les numéros des sommets source et destination de l'arc (iSource, iDestination)              *****
	***** Précondition : Aucune                                                                                                          *****
	***** Sortie : Aucune                                                                                                                *****
	***** Postcondition : Supprime un arc reliant les sommets source et destination dans la liste des sommets (lisGRAListeSommet).       *****
	***** Lance une exception de type int si l'un des sommets n'est pas trouvé                                                           *****
	*****************************************************************************************************************************************/
	void GRASupprimerArc( int iSource, int iDestination);

	/**************************************************************************************************************************************************
	***** operator=(Graphe & GRAParam) : Surcharge de l'opérateur d'affectation (=) pour copier un graphe                                        *****
	***************************************************************************************************************************************************
	***** Entrée : Une référence à un objet Graphe (GRAParam) à copier                                                                           *****
	***** Précondition : Aucune                                                                                                                   *****
	***** Sortie : Une référence à un objet Graphe                                                                                               *****
	***** Postcondition : opie les valeurs du graphe source (GRAParam) dans l'objet actuel, y compris la liste des sommets (lisGRAListeSommet).   *****
	***** Retourne une référence à l'objet Graphe modifié                                                                                        *****
	**************************************************************************************************************************************************/
	Graphe& operator=(const Graphe& GRAParam);

	/***********************************************************************************************************************************************
	***** operator<<(std::ostream & stream, const Graphe & GRAParam) : Surcharge de l'opérateur de sortie (<<) pour afficher un objet Graphe *****
	************************************************************************************************************************************************
	***** Entrée : Un flux de sortie et une référence constante à un objet Graphe (GRAParam) à afficher                                       *****
	***** Précondition : Aucune                                                                                                                *****
	***** Sortie : Une référence à un flux de sorte                                                                                            *****
	***** Postcondition : Affiche le contenu du graphe (liste des sommets et leurs arcs) dans le flux de sortie (stream) en utilisant          *****
	***** l'opérateur de flux de sortie (<<). Retourne une référence au flux de sortie modifié                                                 *****
	***********************************************************************************************************************************************/
	friend std::ostream& operator<< (std::ostream& stream, const Graphe& GRAParam);

	/***************************************************************************************
	***** CListe<Sommet>& GRAObtenirListeSommet() : Obtenir la référence à un Sommet *****
	****************************************************************************************
	***** Entrée : Aucune                                                              *****
	***** Précondition : Aucune                                                        *****
	***** Sortie : Une référence à la liste des sommets de type CListe<Sommet>        *****
	***** Postcondition : Aucune                                                       *****
	***************************************************************************************/
	std::vector<SommetUpgrade>& GRAObtenirListeSommet() {
		return lisGRAListeSommet;
	}
};

