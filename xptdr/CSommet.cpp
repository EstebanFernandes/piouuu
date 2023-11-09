#include "CSommet.h"

/**************************************************************************************
***** CSommet() : Constructeur par d�faut                                         *****
***************************************************************************************
***** Entr�e : Aucune                                                             *****
***** Pr�condition : Aucune                                                       *****
***** Sortie : Aucune                                                             *****
***** Postcondition : Cr�e un objet CSommet sans aucune initialisation sp�cifique *****
**************************************************************************************/
CSommet::CSommet()
{
}

/**************************************************************************************************
***** CSommet(int Num) : Constructeur de confort                                              *****
***************************************************************************************************
***** Entr�e : Un entier repr�sentant le num�ro du sommet (Num)                               *****
***** Pr�condition : Aucune                                                                   *****
***** Sortie : Aucune                                                                         *****
***** Postcondition : Cr�e un objet CSommet en initialisant le num�ro du sommet (iSOMNumero)  *****
***** avec la valeur sp�cifi�e (Num)                                                          *****
**************************************************************************************************/
CSommet::CSommet(int Num)
{
	iSOMNumero = Num;
}

/***********************************************************************************************************************************
***** CSommet(CSommet & SOMParam) : Constructeur de recopie                                                                    *****
************************************************************************************************************************************
***** Entr�e : Une r�f�rence � un objet CSommet (SOMParam) � copier                                                            *****
***** Pr�condition : Aucune                                                                                                    *****
***** Sortie : Aucune                                                                                                          *****
***** Postcondition : Cr�e un objet CSommet en copiant les valeurs du sommet source (SOMParam), y compris le num�ro du sommet  *****
***** (iSOMNumero) et les listes d'arcs arrivants et partants                                                                  *****
***********************************************************************************************************************************/
CSommet::CSommet(const CSommet & SOMParam)
{
	iSOMNumero = SOMParam.iSOMNumero;
	lisSOMArcArrivant = SOMParam.lisSOMArcArrivant;
	lisSOMArcPartant = SOMParam.lisSOMArcPartant;
}

/*************************************************************************************
***** ~CSommet() : Destructeur                                                   *****
**************************************************************************************
***** Entr�e : Aucune                                                            *****
***** Pr�condition : Aucune                                                      *****
***** Sortie : Aucune                                                            *****
***** Postcondition : D�truit l'objet CSommet et lib�re toute ressource associ�e *****
*************************************************************************************/
CSommet::~CSommet()
{
}

/***************************************************************************
***** SOMLireNumero() const : Lire le num�ro du sommet                 *****
****************************************************************************
***** Entr�e : Aucune                                                  *****
***** Pr�condition : Aucune                                            *****
***** Sortie : Un entier repr�sentant le num�ro du sommet (iSOMNumero) *****
***** Postcondition : Retourne le num�ro du sommet                     *****
***************************************************************************/
int CSommet::SOMLireNumero() const
{
	return iSOMNumero;
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
void CSommet::SOMAjouterArc(bool type, int Destination)
{
	CArc temp(Destination);
	if (type == Arrivant) {
		for (int uiBoucle = 0; uiBoucle < lisSOMArcArrivant.size(); ++uiBoucle) {
			if (lisSOMArcArrivant[uiBoucle].ARCObtenirDest() == Destination) {
				throw(CException(ArcExistant));
			}
		}
		lisSOMArcArrivant.push_back(temp);
	}
	else {
		for (int uiBoucle = 0; uiBoucle < lisSOMArcPartant.size(); ++uiBoucle) {
			if (lisSOMArcPartant[uiBoucle].ARCObtenirDest() == Destination) {
				throw(CException(ArcExistant));
			}
		}
		lisSOMArcPartant.push_back(temp);
	}
}

/*********************************************************************************************************************************************
***** SOMAjouterArc(bool type, CArc Arc) : Surcharge de la fonction SOMAjouter ajouter pour le cas o� on a d�j� l'arc qu'on veut ajouter *****
**********************************************************************************************************************************************
***** Entr�e : un bool qui pr�cise le type et un CArc qu'on va ajouter au sommet                                                         *****
***** Pr�condition : Aucune                                                                                                              *****
***** Sortie : Aucune                                                                                                                    *****
***** Postcondition : L'arc est ajout� au sommet                                                                                         *****
*********************************************************************************************************************************************/
void CSommet::SOMAjouterArc(bool type, CArc Arc)
{
	if (type == Arrivant) {
		for (int uiBoucle = 0; uiBoucle < lisSOMArcArrivant.size(); ++uiBoucle) {
			if (lisSOMArcArrivant[uiBoucle].ARCObtenirDest() == Arc.ARCObtenirDest()) {
				throw(CException(ArcExistant));
			}
		}
		lisSOMArcArrivant.push_back(Arc);
	}
	else {
		for (int uiBoucle = 0; uiBoucle < lisSOMArcPartant.size(); ++uiBoucle) {
			if (lisSOMArcPartant[uiBoucle].ARCObtenirDest() == Arc.ARCObtenirDest()) {
				throw(CException(ArcExistant));
			}
		}
		lisSOMArcPartant.push_back(Arc);
	}
}


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
void CSommet::SOMModifierArc(bool type, int AncienneDestination, int NouvelleDestination)
{
	if (type == Arrivant) {
		int iNumListe = SOMRechercherArc(Arrivant, AncienneDestination);
		if (iNumListe == ARC_NON_TROUVEE) {
			CException introuvable(ArcArrivantIntrouvable);
			throw(introuvable);
		}
		else {
			// Supprimer l'arc avec l'ancienne destination
			lisSOMArcArrivant.erase(lisSOMArcArrivant.begin()+iNumListe);

			// Ajouter un nouvel arc avec la nouvelle destination
			CArc nouvelArc(NouvelleDestination);
			lisSOMArcArrivant.push_back(nouvelArc);
		}
	}
	else {
		int iNumListe = SOMRechercherArc(Partant, AncienneDestination);
		if (iNumListe == ARC_NON_TROUVEE) {
			CException introuvable(ArcPartantIntrouvable);
			throw(introuvable);
		}
		else {
			// Supprimer l'arc avec l'ancienne destination
			lisSOMArcArrivant.erase(lisSOMArcArrivant.begin() + iNumListe);

			// Ajouter un nouvel arc avec la nouvelle destination
			CArc nouvelArc(NouvelleDestination);
			lisSOMArcPartant.push_back(nouvelArc);
		}
	}
}

/****************************************************************************************************************
***** SOMModifierArc(bool type, int Destination, unsigned int uipoids) : Modifier le poids d'un arc         *****
*****************************************************************************************************************
***** Entr�e : un bool qui pr�cise le type, la destination de l'arc � modifier et le nouveau poids de l'arc *****
***** Pr�condition : Aucune                                                                                 *****
***** Sortie : Aucune                                                                                       *****
***** Postcondition : L'arc est modifi� avec un nouveau poids                                               *****
****************************************************************************************************************/
void CSommet::SOMModifierArc(bool type, int Destination, double dPoids)
{
	if (dPoids < 0) {
		throw(CException(ValeurPoidsN�gatif));
	}
	if (type == Arrivant) {
		int iNumListe = SOMRechercherArc(Arrivant, Destination);
		if (iNumListe == ARC_NON_TROUVEE) {
			CException introuvable(ArcArrivantIntrouvable);
			throw(introuvable);
		}
		else {
			lisSOMArcArrivant[iNumListe].ARCModifier(dPoids);
		}
	}
	else {
		int iNumListe = SOMRechercherArc(Partant, Destination);
		if (iNumListe == ARC_NON_TROUVEE) {
			CException introuvable(ArcPartantIntrouvable);
			throw(introuvable);
		}
		else {
			// Modifie le poids
			lisSOMArcArrivant[iNumListe].ARCModifier(dPoids);
		}
	}
}


/***************************************************************************************************************************************
***** SOMSupprimerArc(bool type, int Destination) : Supprimer un arc du sommet                                                     *****
****************************************************************************************************************************************
***** Entr�e : Un bool�en repr�sentant le type d'arc (type) : Arrivant ou Partant, et un entier                                    *****
***** Pr�condition : Aucune                                                                                                        *****
***** Sortie : Aucune                                                                                                              *****
***** Postcondition : Supprime l'arc correspondant � la destination sp�cifi�e de la liste d'arcs arrivants (lisSOMArcArrivant) ou  *****
***** de la liste d'arcs partants (lisSOMArcPartant), en fonction du type d'arc sp�cifi�                                           *****
***************************************************************************************************************************************/
void CSommet::SOMSupprimerArc(bool type, int Destination)
{
	if (type == Arrivant) {
		int iNumListe = SOMRechercherArc(Arrivant, Destination);
		if (iNumListe == ARC_NON_TROUVEE) {
			CException introuvable(ArcArrivantIntrouvable);
			throw(introuvable);
		}
		else {
			lisSOMArcArrivant.erase(lisSOMArcArrivant.begin() + iNumListe);
		}
	}
	else {
		int iNumListe = SOMRechercherArc(Partant, Destination);
		if (iNumListe == ARC_NON_TROUVEE) {
			CException introuvable(ArcPartantIntrouvable);
			throw(introuvable);
		}
		else {
			lisSOMArcArrivant.erase(lisSOMArcArrivant.begin() + iNumListe);
		}
	}
}

/******************************************************************************************************************************************************
***** SOMRechercherArc(bool type, int Element) : Rechercher un arc dans le sommet                                                                 *****
*******************************************************************************************************************************************************
***** Entr�e : Un bool�en repr�sentant le type d'arc (type) : Arrivant ou Partant, et un entier repr�sentant la destination de                    *****
***** l'arc � rechercher (Element)                                                                                                                *****
***** Pr�condition : Aucune                                                                                                                       *****
***** Sortie : Un entier repr�sentant l'indice de l'arc trouv� dans la liste d'arcs arrivants (lisSOMArcArrivant) ou dans la liste                *****
***** d'arcs partants (lisSOMArcPartant). Retourne -999 si l'arc n'est pas trouv�                                                                 *****
***** Postcondition : Parcourt la liste d'arcs arrivants (lisSOMArcArrivant) ou la liste d'arcs partants (lisSOMArcPartant), en fonction du       *****
***** type d'arc sp�cifi�, et recherche l'arc ayant la destination sp�cifi�e. Retourne l'indice de l'arc trouv� ou -999 si l'arc n'est pas trouv� *****
******************************************************************************************************************************************************/
int CSommet::SOMRechercherArc(bool type, int Element)
{
	if (type == Arrivant) {
		unsigned int uiTaille = (unsigned int)lisSOMArcArrivant.size();
		for (unsigned int uiBoucle = 0; uiBoucle < uiTaille; uiBoucle++) {
			if (lisSOMArcArrivant[uiBoucle].ARCObtenirDest() == Element)
				return uiBoucle;
		}
	}
	else {
		unsigned int uiTaille = (unsigned int)lisSOMArcPartant.size();
		for (unsigned int uiBoucle = 0; uiBoucle < uiTaille; uiBoucle++) {
			if (lisSOMArcPartant[uiBoucle].ARCObtenirDest() == Element) return uiBoucle;
		}
	}
	return ARC_NON_TROUVEE;
}

/*****************************************************************************************************************************************
***** operator=(CSommet & SOMParam) : Surcharge de l'op�rateur d'affectation (=) pour copier un sommet                               *****
******************************************************************************************************************************************
***** Entr�e : Une r�f�rence � un objet CSommet (SOMParam) � copier                                                                  *****
***** Pr�condition : Aucune                                                                                                          *****
***** Sortie : Une r�f�rence � un objet CSommet                                                                                      *****
***** Postcondition : Copie les valeurs du sommet source (SOMParam) dans l'objet actuel, y compris le num�ro du sommet (iSOMNumero)  *****
***** et les listes d'arcs arrivants et partants. Retourne une r�f�rence � l'objet CSommet modifi�                                   *****
*****************************************************************************************************************************************/
CSommet & CSommet::operator=(const CSommet & SOMParam)
{
	iSOMNumero = SOMParam.iSOMNumero;
	lisSOMArcArrivant = SOMParam.lisSOMArcArrivant;
	lisSOMArcPartant = SOMParam.lisSOMArcPartant;
	return *this;
}



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
std::ostream & operator<<(std::ostream & stream, const CSommet & SOMParam)
{
	stream << "Sommet numero " << SOMParam.SOMLireNumero()<<"\n";
	//stream << "Liste des arcs arrivant : \n" << SOMParam.lisSOMArcArrivant;
	//stream << "Liste des arcs partant : \n" << SOMParam.lisSOMArcPartant;
	return stream;
}
