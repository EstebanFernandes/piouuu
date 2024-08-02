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
	***** Graphe() : Constructeur par d�faut                                *****
	******************************************************************************
	***** Entr�e : Aucune                                                    *****
	***** Pr�condition : Aucune                                              *****
	***** Sortie : Aucune                                                    *****
	***** Postcondition : L'objet Graphe est cr�� et est par d�faut orient� *****
	*****************************************************************************/
	Graphe();

	/***********************************************************************************
	***** Graphe(bool bParam) : Constructeur de confort                           *****
	************************************************************************************
	***** Entr�e : bParam (bool�en repr�sentant le type de graphe)                 *****
	***** Pr�condition : Aucune                                                    *****
	***** Sortie : Aucune                                                          *****
	***** Postcondition : L'objet Graphe est cr�� avec le type de graphe sp�cifi� *****
	***********************************************************************************/
	Graphe(bool bParam);

	/*******************************************************************************************************************************************************
	***** Graphe(Graphe & GRAParam) : Constructeur de recopie                                                                                        *****
	********************************************************************************************************************************************************
	***** Entr�e : Une r�f�rence � un objet Graphe (GRAParam) � copier                                                                                *****
	***** Pr�condition : Aucune                                                                                                                        *****
	***** Sortie : Aucune                                                                                                                              *****
	***** Postcondition : Cr�e un objet Graphe en copiant les valeurs du graphe source (GRAParam), y compris la liste des sommets (lisGRAListeSommet) *****
	*******************************************************************************************************************************************************/
	Graphe(Graphe& GRAParam);

	/*************************************************************************************
	***** ~Graphe() : Destructeur                                                   *****
	**************************************************************************************
	***** Entr�e : Aucune                                                            *****
	***** Pr�condition : Aucune                                                      *****
	***** Sortie : Aucune                                                            *****
	***** Postcondition : D�truit l'objet Graphe et lib�re toute ressource associ�e *****
	*************************************************************************************/
	~Graphe();

	/***************************************************************************************************************************************************************
	***** GRATrouverSommet(int Identifiant) : Trouver un sommet dans le graphe                                                                                 *****
	****************************************************************************************************************************************************************
	***** Entr�e : Un entier repr�sentant l'identifiant du sommet � rechercher (Identifiant)                                                                   *****
	***** Pr�condition : Aucune                                                                                                                                *****
	***** Sortie : Un entier repr�sentant l'indice du sommet trouv� dans la liste des sommets (lisGRAListeSommet). Retourne -998 si le sommet n'est pas trouv� *****
	***** Postcondition : Parcourt la liste des sommets (lisGRAListeSommet) et recherche le sommet ayant l'identifiant sp�cifi�.                               *****
	***** Retourne l'indice du sommet trouv� ou -998 si le sommet n'est pas trouv�                                                                             *****
	***************************************************************************************************************************************************************/
	int GRATrouverSommet(int Identifiant);

	/*******************************************************************************************
	***** GRARetourneNbSommet() : Retourne le nombre de sommets du graphe                  *****
	********************************************************************************************
	***** Entr�e : Aucune                                                                  *****
	***** Pr�condition : Aucune                                                            *****
	***** Sortie : Le nombre de sommets pr�sent dans le graphe                             *****
	***** Postcondition : Retourne le nombre de sommets pr�sents dans la liste des sommets *****
	*******************************************************************************************/
	unsigned int GRARetourneNbSommet() { return (unsigned int)lisGRAListeSommet.size(); }

	/*****************************************************************************************
	***** GRARetourneType() : Retourne le type de graphe                                 *****
	******************************************************************************************
	***** Entr�e : Aucune                                                                *****
	***** Pr�condition : Aucune                                                          *****
	***** Sortie : Le type de graphe                                                     *****
	***** Postcondition : Retourne le type du graphe c'est � dire orient� ou non orient� *****
	*****************************************************************************************/
	bool GRARetourneType() { return bGRAType; }

	/**********************************************************************************************************************************
	***** GRAAjouterSommet(int NumSommet) : Ajouter un sommet au graphe                                                           *****
	***********************************************************************************************************************************
	***** Entr�e : Un entier repr�sentant le num�ro du sommet � ajouter (NumSommet)                                               *****
	***** Pr�condition : Aucune                                                                                                   *****
	***** Sortie : Aucune                                                                                                         *****
	***** Postcondition : Ajoute un nouveau sommet � la liste des sommets (lisGRAListeSommet) avec le num�ro sp�cifi� (NumSommet) *****
	**********************************************************************************************************************************/
	void GRAAjouterSommet(int NumSommet);

	void GRAAjouterSommet(SommetUpgrade temp);

	/*********************************************************************************************************************
	***** GRAModifierSommet(int AncienNum, int NouveauNum) : Modifier un sommet dans le graphe                       *****
	**********************************************************************************************************************
	***** Entr�e : Deux entiers repr�sentant le num�ro d'origine du sommet � modifier et le nouveau num�ro du sommet *****
	***** Pr�condition : Le sommet d'origine existe dans le graphe.													 *****
	***** Sortie : Aucune																							 *****
	***** Postcondition : Modifie le num�ro du sommet d'origine par le nouveau num�ro sp�cifi�.						 *****
	***** Lance une exception de type int si le sommet n'est pas trouv�.											 *****
	*********************************************************************************************************************/
	void GRAModifierSommet(int AncienNum, int NouveauNum);
	
	/*****************************************************************************************************************************
	***** GRASupprimerSommet(int NumSommet) : Supprimer un sommet du graphe                                                  *****
	******************************************************************************************************************************
	***** Entr�e : Un entier repr�sentant le num�ro du sommet � supprimer (NumSommet)                                        *****
	***** Pr�condition : Aucune                                                                                              *****
	***** Sortie : Aucune                                                                                                    *****
	***** Postcondition : Supprime le sommet correspondant au num�ro sp�cifi� de la liste des sommets (lisGRAListeSommet).   *****
	***** Lance une exception de type Exception si le sommet n'est pas trouv�                                               *****
	*****************************************************************************************************************************/
	void GRASupprimerSommet( int NumSommet);

	/*****************************************************************************************************************************************
	***** GRAAjouterArc(int iSource, int iDestination) : Ajouter un arc au graphe                                                        *****
	******************************************************************************************************************************************
	***** Entr�e : Deux entiers repr�sentant les num�ros des sommets source et destination de l'arc (iSource, iDestination)              *****
	***** Pr�condition : Aucune                                                                                                          *****
	***** Sortie : Aucune                                                                                                                *****
	***** Postcondition : Ajoute un nouvel arc reliant les sommets source et destination dans la liste des sommets (lisGRAListeSommet).  *****
	***** Lance une exception de type int si l'un des sommets n'est pas trouv�                                                           *****
	*****************************************************************************************************************************************/
	void GRAAjouterArc( int iSource, int iDestination);

	/**********************************************************************************************************************************************************
	***** GRAAjouterArc(int iSource, int iDestination, unsigned int uipoids) : Ajoute un arc au graphe en pr�cisant son poids si celui-ci est non orient� *****
	***********************************************************************************************************************************************************
	***** Entr�e : Deux entiers repr�sentant les num�ros des sommets source et destination de l'arc et un entier repr�sentant le poids de l'arc � cr�er   *****
	***** Pr�condition : Aucune                                                                                                                           *****
	***** Sortie : Aucune                                                                                                                                 *****
	***** Postcondition : Ajoute un arc reliant les sommets source et destination et si le graphe est non orient� le poids sur l'arc est ajout�.          *****
	***** Lance une exception si l'un des sommets n'est pas trouv�                                                                                        *****
	**********************************************************************************************************************************************************/
	void GRAAjouterArc(int iSource, int iDestination, double dpoids);

	/******************************************************************************************************************************************************
	***** GRAModifierArc(int AncienSource, int AncienneDestination, int NouvelleSource, int NouvelleDestination) : Modifier un arc dans le graphe     *****
	*******************************************************************************************************************************************************
	***** Entr�e : Quatre entiers repr�sentant les num�ros des sommets source et destination de l'arc � modifier : AncienSource, AncienneDestination, *****
	***** NouvelleSource, NouvelleDestination																										  *****
	***** Pr�condition : les sommets existent																										  *****
	***** Sortie : Aucune																															  *****
	***** Postcondition : Modifie l'arc reliant les sommets source et destination d'origine par un nouvel arc reliant les sommets source et			  *****
	***** destination de remplacement. Lance une exception de type int si l'un des sommets n'est pas trouv�.										  *****
	******************************************************************************************************************************************************/
	void GRAModifierArc(int AncienSource, int AncienneDestination, int NouvelleSource, int NouvelleDestination);

	/*********************************************************************************************************************************************************
	***** GRAModifierArc(int iSource, int iDestination, unsigned int uipoids) : Modifie la valeur du poids de l'arc                                      *****
	**********************************************************************************************************************************************************
	***** Entr�e : Deux entiers repr�sentant les num�ros des sommets source et destination de l'arc et un entier repr�sentant le nouveau poids de l'arc  *****
	***** Pr�condition : Aucune                                                                                                                          *****
	***** Sortie : Aucune                                                                                                                                *****
	***** Postcondition : Modifie le valeur du poids de l'arc si celui-ci est trouv� sinon une exception est lanc�                                       *****
	*********************************************************************************************************************************************************/
	void GRAModifierArc(int iSource, int iDestination, double dpoids);

	/*****************************************************************************************************************************************
	***** GRASupprimerArc(int iSource, int iDestination) : Supprime un arc au graphe                                                     *****
	******************************************************************************************************************************************
	***** Entr�e : Deux entiers repr�sentant les num�ros des sommets source et destination de l'arc (iSource, iDestination)              *****
	***** Pr�condition : Aucune                                                                                                          *****
	***** Sortie : Aucune                                                                                                                *****
	***** Postcondition : Supprime un arc reliant les sommets source et destination dans la liste des sommets (lisGRAListeSommet).       *****
	***** Lance une exception de type int si l'un des sommets n'est pas trouv�                                                           *****
	*****************************************************************************************************************************************/
	void GRASupprimerArc( int iSource, int iDestination);

	/**************************************************************************************************************************************************
	***** operator=(Graphe & GRAParam) : Surcharge de l'op�rateur d'affectation (=) pour copier un graphe                                        *****
	***************************************************************************************************************************************************
	***** Entr�e : Une r�f�rence � un objet Graphe (GRAParam) � copier                                                                           *****
	***** Pr�condition : Aucune                                                                                                                   *****
	***** Sortie : Une r�f�rence � un objet Graphe                                                                                               *****
	***** Postcondition : opie les valeurs du graphe source (GRAParam) dans l'objet actuel, y compris la liste des sommets (lisGRAListeSommet).   *****
	***** Retourne une r�f�rence � l'objet Graphe modifi�                                                                                        *****
	**************************************************************************************************************************************************/
	Graphe& operator=(const Graphe& GRAParam);

	/***********************************************************************************************************************************************
	***** operator<<(std::ostream & stream, const Graphe & GRAParam) : Surcharge de l'op�rateur de sortie (<<) pour afficher un objet Graphe *****
	************************************************************************************************************************************************
	***** Entr�e : Un flux de sortie et une r�f�rence constante � un objet Graphe (GRAParam) � afficher                                       *****
	***** Pr�condition : Aucune                                                                                                                *****
	***** Sortie : Une r�f�rence � un flux de sorte                                                                                            *****
	***** Postcondition : Affiche le contenu du graphe (liste des sommets et leurs arcs) dans le flux de sortie (stream) en utilisant          *****
	***** l'op�rateur de flux de sortie (<<). Retourne une r�f�rence au flux de sortie modifi�                                                 *****
	***********************************************************************************************************************************************/
	friend std::ostream& operator<< (std::ostream& stream, const Graphe& GRAParam);

	/***************************************************************************************
	***** CListe<Sommet>& GRAObtenirListeSommet() : Obtenir la r�f�rence � un Sommet *****
	****************************************************************************************
	***** Entr�e : Aucune                                                              *****
	***** Pr�condition : Aucune                                                        *****
	***** Sortie : Une r�f�rence � la liste des sommets de type CListe<Sommet>        *****
	***** Postcondition : Aucune                                                       *****
	***************************************************************************************/
	std::vector<SommetUpgrade>& GRAObtenirListeSommet() {
		return lisGRAListeSommet;
	}
};

