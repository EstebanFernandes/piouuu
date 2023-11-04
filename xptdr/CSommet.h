#pragma once
#define Arrivant true
#define Partant false
#include "CListe.h"
#include "CArc.h"

const int ARC_NON_TROUVEE = -999;

class CSommet
{
private :
	int iSOMNumero;
	CListe<CArc> lisSOMArcArrivant;
	CListe<CArc> lisSOMArcPartant;
public :

	/**************************************************************************************
	***** CSommet() : Constructeur par d�faut                                         *****
	***************************************************************************************
	***** Entr�e : Aucune                                                             *****
	***** Pr�condition : Aucune                                                       *****
	***** Sortie : Aucune                                                             *****
	***** Postcondition : Cr�e un objet CSommet sans aucune initialisation sp�cifique *****
	**************************************************************************************/
	CSommet();

	/**************************************************************************************************
	***** CSommet(int Num) : Constructeur de confort                                              *****
	***************************************************************************************************
	***** Entr�e : Un entier repr�sentant le num�ro du sommet (Num)                               *****
	***** Pr�condition : Aucune                                                                   *****
	***** Sortie : Aucune                                                                         *****
	***** Postcondition : Cr�e un objet CSommet en initialisant le num�ro du sommet (iSOMNumero)  *****
	***** avec la valeur sp�cifi�e (Num)                                                          *****
	**************************************************************************************************/
	CSommet(int Num);

	/***********************************************************************************************************************************
	***** CSommet(CSommet & SOMParam) : Constructeur de recopie                                                                    *****
	************************************************************************************************************************************
	***** Entr�e : Une r�f�rence � un objet CSommet (SOMParam) � copier                                                            *****
	***** Pr�condition : Aucune                                                                                                    *****
	***** Sortie : Aucune                                                                                                          *****
	***** Postcondition : Cr�e un objet CSommet en copiant les valeurs du sommet source (SOMParam), y compris le num�ro du sommet  *****
	***** (iSOMNumero) et les listes d'arcs arrivants et partants                                                                  *****
	***********************************************************************************************************************************/
	CSommet(CSommet& SOMParam);

	/*************************************************************************************
	***** ~CSommet() : Destructeur                                                   *****
	**************************************************************************************
	***** Entr�e : Aucune                                                            *****
	***** Pr�condition : Aucune                                                      *****
	***** Sortie : Aucune                                                            *****
	***** Postcondition : D�truit l'objet CSommet et lib�re toute ressource associ�e *****
	*************************************************************************************/
	~CSommet();

	/***************************************************************************
	***** SOMLireNumero() const : Lire le num�ro du sommet                 *****
	****************************************************************************
	***** Entr�e : Aucune                                                  *****
	***** Pr�condition : Aucune                                            *****
	***** Sortie : Un entier repr�sentant le num�ro du sommet (iSOMNumero) *****
	***** Postcondition : Retourne le num�ro du sommet                     *****
	***************************************************************************/
	int SOMLireNumero() const;

	/****************************************************************************************************
	***** SOMModifierNumero(int NouveauNumero) : Modifie le num�ro du sommet                           *****
	*****************************************************************************************************
	***** Entr�e : Un entier repr�sentant le nouveau num�ro du sommet (NouveauNumero)                *****
	***** Pr�condition : Aucune                                                                      *****
	***** Sortie : Aucune                                                                            *****
	***** Postcondition : Met � jour le num�ro du sommet avec la nouvelle valeur sp�cifi�e            *****
	****************************************************************************************************/
	void SOMModifierNumero(int NouveauNumero) {
		iSOMNumero = NouveauNumero;
	}

	/***************************************************************************************************************************************************
	***** SOMAjouterArc(bool type, int Destination) : Ajouter un arc au sommet                                                                     *****
	****************************************************************************************************************************************************
	***** Entr�e : Un bool�en repr�sentant le type d'arc (type) : Arrivant ou Partant, et un entier                                                *****
	***** repr�sentant la destination de l'arc (Destination)                                                                                       *****
	***** Pr�condition : Aucune                                                                                                                    *****
	***** Sortie : Aucune                                                                                                                          *****
	***** Postcondition : Ajoute un nouvel arc � la liste d'arcs arrivants (lisSOMArcArrivant) ou � la liste d'arcs partants (lisSOMArcPartant),   *****
	***** en fonction du type d'arc sp�cifi�. L'arc est cr�� avec la destination sp�cifi�e                                                         *****
	***************************************************************************************************************************************************/
	void SOMAjouterArc(bool type,int Destination);

	/*********************************************************************************************************************************************
	***** SOMAjouterArc(bool type, CArc Arc) : Surcharge de la fonction SOMAjouter ajouter pour le cas o� on a d�j� l'arc qu'on veut ajouter *****
	**********************************************************************************************************************************************
	***** Entr�e : un bool qui pr�cise le type et un CArc qu'on va ajouter au sommet                                                         *****
	***** Pr�condition : Aucune                                                                                                              *****
	***** Sortie : Aucune                                                                                                                    *****
	***** Postcondition : L'arc est ajout� au sommet                                                                                         *****
	*********************************************************************************************************************************************/
	void SOMAjouterArc(bool type, CArc Arc);

	/*******************************************************************************************************************************************************
	***** SOMModifierArc(bool type, int AncienneDestination, int NouvelleDestination) : Modifier la destination d'un arc dans le sommet                *****
	********************************************************************************************************************************************************
	***** Entr�e : Un bool�en repr�sentant le type d'arc (type) : Arrivant ou Partant, un entier repr�sentant l'ancienne destination de l'arc          *****
	***** (AncienneDestination) et un entier repr�sentant la nouvelle destination de l'arc (NouvelleDestination)                                       *****
	***** Pr�condition : Aucune                                                                                                                        *****
	***** Sortie : Aucune                                                                                                                              *****
	***** Postcondition : Modifie la destination de l'arc sp�cifi� dans la liste d'arcs arrivants (lisSOMArcArrivant) ou dans la liste d'arcs		   *****
	***** partants (lisSOMArcPartant), en fonction du type d'arc sp�cifi�																			   *****
	*******************************************************************************************************************************************************/
	void SOMModifierArc(bool type, int AncienneDestination, int NouvelleDestination);

	/****************************************************************************************************************
	***** SOMModifierArc(bool type, int Destination, unsigned int uipoids) : Modifier le poids d'un arc         *****
	*****************************************************************************************************************
	***** Entr�e : un bool qui pr�cise le type, la destination de l'arc � modifier et le nouveau poids de l'arc *****
	***** Pr�condition : Aucune                                                                                 *****
	***** Sortie : Aucune                                                                                       *****
	***** Postcondition : L'arc est modifi� avec un nouveau poids                                               *****
	****************************************************************************************************************/
	void SOMModifierArc(bool type, int Destination, double dPoids);

	/***************************************************************************************************************************************
	***** SOMSupprimerArc(bool type, int Destination) : Supprimer un arc du sommet                                                     *****
	****************************************************************************************************************************************
	***** Entr�e : Un bool�en repr�sentant le type d'arc (type) : Arrivant ou Partant, et un entier                                    *****
	***** Pr�condition : Aucune                                                                                                        *****
	***** Sortie : Aucune                                                                                                              *****
	***** Postcondition : Supprime l'arc correspondant � la destination sp�cifi�e de la liste d'arcs arrivants (lisSOMArcArrivant) ou  *****
	***** de la liste d'arcs partants (lisSOMArcPartant), en fonction du type d'arc sp�cifi�                                           *****
	***************************************************************************************************************************************/
	void SOMSupprimerArc(bool type,int Destination);

	/******************************************************************************************************************************************************
	***** SOMRechercherArc(bool type, int Element) : Rechercher un arc dans le sommet																  *****
	*******************************************************************************************************************************************************
	***** Entr�e : Un bool�en repr�sentant le type d'arc (type) : Arrivant ou Partant, et un entier repr�sentant la destination de					  *****
	***** l'arc � rechercher (Element)																												  *****
	***** Pr�condition : Aucune																														  *****
	***** Sortie : Un entier repr�sentant l'indice de l'arc trouv� dans la liste d'arcs arrivants (lisSOMArcArrivant) ou dans la liste				  *****
	***** d'arcs partants (lisSOMArcPartant). Retourne -999 si l'arc n'est pas trouv�																  *****
	***** Postcondition : Parcourt la liste d'arcs arrivants (lisSOMArcArrivant) ou la liste d'arcs partants (lisSOMArcPartant), en fonction du		  *****
	***** type d'arc sp�cifi�, et recherche l'arc ayant la destination sp�cifi�e. Retourne l'indice de l'arc trouv� ou -999 si l'arc n'est pas trouv� *****
	******************************************************************************************************************************************************/
	int SOMRechercherArc(bool type, int Element);

	/*****************************************************************************************************************************************
	***** operator=(CSommet & SOMParam) : Surcharge de l'op�rateur d'affectation (=) pour copier un sommet                               *****
	******************************************************************************************************************************************
	***** Entr�e : Une r�f�rence � un objet CSommet (SOMParam) � copier                                                                  *****
	***** Pr�condition : Aucune                                                                                                          *****
	***** Sortie : Une r�f�rence � un objet CSommet                                                                                      *****
	***** Postcondition : Copie les valeurs du sommet source (SOMParam) dans l'objet actuel, y compris le num�ro du sommet (iSOMNumero)  *****
	***** et les listes d'arcs arrivants et partants. Retourne une r�f�rence � l'objet CSommet modifi�                                   *****
	*****************************************************************************************************************************************/
	CSommet& operator=(CSommet& SOMParam);

	/***********************************************************************************************************************************************
	***** operator<<(std::ostream & stream, const CSommet & SOMParam) : Surcharge de l'op�rateur de sortie (<<) pour afficher un objet CSommet *****
	************************************************************************************************************************************************
	***** Entr�e : Un flux de sortie (stream) et une r�f�rence constante � un objet CSommet (SOMParam) � afficher                              *****
	***** Pr�condition : Aucune                                                                                                                *****
	***** Sortie :  Une r�f�rence � un flux de sortie                                                                                          *****
	***** Postcondition : Affiche le num�ro du sommet (iSOMNumero), ainsi que les listes d'arcs arrivants et partants (lisSOMArcArrivant et    *****
	*****  lisSOMArcPartant) dans le flux de sortie (stream) en utilisant l'op�rateur de flux de sortie (<<). Retourne une r�f�rence           *****
	***** au flux de sortie modifi�                                                                                                            *****
	***********************************************************************************************************************************************/
	friend std::ostream& operator<< (std::ostream& stream, const CSommet& SOMParam);
	
	/****************************************************************************************************************************
	***** CListe<CArc>& SOMLireArcArrivant() : Retourne une r�f�rence � la liste des arcs arrivant                          *****
	*****************************************************************************************************************************
	***** Entr�e : Aucune                                                                                                   *****
	***** Pr�condition : Aucune                                                                                             *****
	***** Sortie : Une r�f�rence � une liste d'objets de type "CArc"                                                        *****
	***** Postcondition : La fonction renvoie une r�f�rence � la liste des arcs arrivant (lisSOMArcArrivant) de l'objet SOM *****
	****************************************************************************************************************************/
	CListe<CArc>& SOMLireArcArrivant() {
		return lisSOMArcArrivant;
	}

	/**************************************************************************************************************************
	***** CListe<CArc>& SOMLireArcPartant() : Retourne une r�f�rence � la liste des arcs partants                         *****
	***************************************************************************************************************************
	***** Entr�e : Aucune                                                                                                 *****
	***** Pr�condition : Aucune                                                                                           *****
	***** Sortie : Une r�f�rence � une liste d'objets de type "CArc"                                                      *****
	***** Postcondition : La fonction renvoie une r�f�rence � la liste des arcs partant (lisSOMArcPartant) de l'objet SOM *****
	**************************************************************************************************************************/
	CListe<CArc>& SOMLireArcPartant() {
		return lisSOMArcPartant;
	}

	/*******************************************************************************************
	***** unsigned int SOMTailleListeArc(bool type) : Donne la taille de la liste des arcs *****
	********************************************************************************************
	***** Entr�e : Un bool�en repr�sentant le type d'arc (type) : Arrivant ou Partant      *****
	***** Pr�condition : Aucune                                                            *****
	***** Sortie : Un entier repr�sentant la taille de l'arc                               *****
	***** Postcondition : Retourne la taille de la liste de l'arc demand�                  *****
	*******************************************************************************************/
	unsigned int SOMTailleListeArc(bool type) {
		if (type == Arrivant) return lisSOMArcArrivant.LISTaille();
		else {
			return lisSOMArcPartant.LISTaille();
		}
	}
};

