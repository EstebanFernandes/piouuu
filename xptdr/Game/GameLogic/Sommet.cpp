#include "Sommet.h"

/**************************************************************************************
***** Sommet() : Constructeur par d�faut                                         *****
***************************************************************************************
***** Entr�e : Aucune                                                             *****
***** Pr�condition : Aucune                                                       *****
***** Sortie : Aucune                                                             *****
***** Postcondition : Cr�e un objet Sommet sans aucune initialisation sp�cifique *****
**************************************************************************************/
Sommet::Sommet()
{
}

/**************************************************************************************************
***** Sommet(int Num) : Constructeur de confort                                              *****
***************************************************************************************************
***** Entr�e : Un entier repr�sentant le num�ro du sommet (Num)                               *****
***** Pr�condition : Aucune                                                                   *****
***** Sortie : Aucune                                                                         *****
***** Postcondition : Cr�e un objet Sommet en initialisant le num�ro du sommet (iSOMNumero)  *****
***** avec la valeur sp�cifi�e (Num)                                                          *****
**************************************************************************************************/
Sommet::Sommet(int Num)
{
	iSOMNumero = Num;
}

/***********************************************************************************************************************************
***** Sommet(Sommet & SOMParam) : Constructeur de recopie                                                                    *****
************************************************************************************************************************************
***** Entr�e : Une r�f�rence � un objet Sommet (SOMParam) � copier                                                            *****
***** Pr�condition : Aucune                                                                                                    *****
***** Sortie : Aucune                                                                                                          *****
***** Postcondition : Cr�e un objet Sommet en copiant les valeurs du sommet source (SOMParam), y compris le num�ro du sommet  *****
***** (iSOMNumero) et les listes d'arcs arrivants et partants                                                                  *****
***********************************************************************************************************************************/
Sommet::Sommet(const Sommet & SOMParam)
{
	iSOMNumero = SOMParam.iSOMNumero;
	lisSOMArcArrivant = SOMParam.lisSOMArcArrivant;
	lisSOMArcPartant = SOMParam.lisSOMArcPartant;
}

/*************************************************************************************
***** ~Sommet() : Destructeur                                                   *****
**************************************************************************************
***** Entr�e : Aucune                                                            *****
***** Pr�condition : Aucune                                                      *****
***** Sortie : Aucune                                                            *****
***** Postcondition : D�truit l'objet Sommet et lib�re toute ressource associ�e *****
*************************************************************************************/
Sommet::~Sommet()
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
int Sommet::SOMLireNumero() const
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
void Sommet::SOMAjouterArc(bool type, int Destination)
{
	Arc temp(Destination);
	if (type == Arrivant) {
		for (int uiBoucle = 0; uiBoucle < lisSOMArcArrivant.size(); ++uiBoucle) {
			if (lisSOMArcArrivant[uiBoucle].ARCObtenirDest() == Destination) {
				throw(Exception(ArcExistant));
			}
		}
		lisSOMArcArrivant.push_back(temp);
	}
	else {
		for (int uiBoucle = 0; uiBoucle < lisSOMArcPartant.size(); ++uiBoucle) {
			if (lisSOMArcPartant[uiBoucle].ARCObtenirDest() == Destination) {
				throw(Exception(ArcExistant));
			}
		}
		lisSOMArcPartant.push_back(temp);
	}
}

/*********************************************************************************************************************************************
***** SOMAjouterArc(bool type, Arc Arc) : Surcharge de la fonction SOMAjouter ajouter pour le cas o� on a d�j� l'arc qu'on veut ajouter *****
**********************************************************************************************************************************************
***** Entr�e : un bool qui pr�cise le type et un Arc qu'on va ajouter au sommet                                                         *****
***** Pr�condition : Aucune                                                                                                              *****
***** Sortie : Aucune                                                                                                                    *****
***** Postcondition : L'arc est ajout� au sommet                                                                                         *****
*********************************************************************************************************************************************/
void Sommet::SOMAjouterArc(bool type, Arc Arc)
{
	if (type == Arrivant) {
		for (int uiBoucle = 0; uiBoucle < lisSOMArcArrivant.size(); ++uiBoucle) {
			if (lisSOMArcArrivant[uiBoucle].ARCObtenirDest() == Arc.ARCObtenirDest()) {
				throw(Exception(ArcExistant));
			}
		}
		lisSOMArcArrivant.push_back(Arc);
	}
	else {
		for (int uiBoucle = 0; uiBoucle < lisSOMArcPartant.size(); ++uiBoucle) {
			if (lisSOMArcPartant[uiBoucle].ARCObtenirDest() == Arc.ARCObtenirDest()) {
				throw(Exception(ArcExistant));
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
void Sommet::SOMModifierArc(bool type, int AncienneDestination, int NouvelleDestination)
{
	if (type == Arrivant) {
		int iNumListe = SOMRechercherArc(Arrivant, AncienneDestination);
		if (iNumListe == ARC_NON_TROUVEE) {
			Exception introuvable(ArcArrivantIntrouvable);
			throw(introuvable);
		}
		else {
			// Supprimer l'arc avec l'ancienne destination
			lisSOMArcArrivant.erase(lisSOMArcArrivant.begin()+iNumListe);

			// Ajouter un nouvel arc avec la nouvelle destination
			Arc nouvelArc(NouvelleDestination);
			lisSOMArcArrivant.push_back(nouvelArc);
		}
	}
	else {
		int iNumListe = SOMRechercherArc(Partant, AncienneDestination);
		if (iNumListe == ARC_NON_TROUVEE) {
			Exception introuvable(ArcPartantIntrouvable);
			throw(introuvable);
		}
		else {
			// Supprimer l'arc avec l'ancienne destination
			lisSOMArcArrivant.erase(lisSOMArcArrivant.begin() + iNumListe);

			// Ajouter un nouvel arc avec la nouvelle destination
			Arc nouvelArc(NouvelleDestination);
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
void Sommet::SOMModifierArc(bool type, int Destination, double dPoids)
{
	if (dPoids < 0) {
		throw(Exception(ValeurPoidsN�gatif));
	}
	if (type == Arrivant) {
		int iNumListe = SOMRechercherArc(Arrivant, Destination);
		if (iNumListe == ARC_NON_TROUVEE) {
			Exception introuvable(ArcArrivantIntrouvable);
			throw(introuvable);
		}
		else {
			lisSOMArcArrivant[iNumListe].ARCModifier(dPoids);
		}
	}
	else {
		int iNumListe = SOMRechercherArc(Partant, Destination);
		if (iNumListe == ARC_NON_TROUVEE) {
			Exception introuvable(ArcPartantIntrouvable);
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
void Sommet::SOMSupprimerArc(bool type, int Destination)
{
	if (type == Arrivant) {
		int iNumListe = SOMRechercherArc(Arrivant, Destination);
		if (iNumListe == ARC_NON_TROUVEE) {
			Exception introuvable(ArcArrivantIntrouvable);
			throw(introuvable);
		}
		else {
			lisSOMArcArrivant.erase(lisSOMArcArrivant.begin() + iNumListe);
		}
	}
	else {
		int iNumListe = SOMRechercherArc(Partant, Destination);
		if (iNumListe == ARC_NON_TROUVEE) {
			Exception introuvable(ArcPartantIntrouvable);
			throw(introuvable);
		}
		else {
			lisSOMArcPartant.erase(lisSOMArcPartant.begin() + iNumListe);
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
int Sommet::SOMRechercherArc(bool type, int Element)
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
***** operator=(Sommet & SOMParam) : Surcharge de l'op�rateur d'affectation (=) pour copier un sommet                               *****
******************************************************************************************************************************************
***** Entr�e : Une r�f�rence � un objet Sommet (SOMParam) � copier                                                                  *****
***** Pr�condition : Aucune                                                                                                          *****
***** Sortie : Une r�f�rence � un objet Sommet                                                                                      *****
***** Postcondition : Copie les valeurs du sommet source (SOMParam) dans l'objet actuel, y compris le num�ro du sommet (iSOMNumero)  *****
***** et les listes d'arcs arrivants et partants. Retourne une r�f�rence � l'objet Sommet modifi�                                   *****
*****************************************************************************************************************************************/
Sommet & Sommet::operator=(const Sommet & SOMParam)
{
	iSOMNumero = SOMParam.iSOMNumero;
	lisSOMArcArrivant = SOMParam.lisSOMArcArrivant;
	lisSOMArcPartant = SOMParam.lisSOMArcPartant;
	return *this;
}



/***********************************************************************************************************************************************
***** operator<<(std::ostream & stream, const Sommet & SOMParam) : Surcharge de l'op�rateur de sortie (<<) pour afficher un objet Sommet *****
************************************************************************************************************************************************
***** Entr�e : Un flux de sortie (stream) et une r�f�rence constante � un objet Sommet (SOMParam) � afficher                              *****
***** Pr�condition : Aucune                                                                                                                *****
***** Sortie :  Une r�f�rence � un flux de sortie                                                                                          *****
***** Postcondition : Affiche le num�ro du sommet (iSOMNumero), ainsi que les listes d'arcs arrivants et partants (lisSOMArcArrivant et    *****
*****  lisSOMArcPartant) dans le flux de sortie (stream) en utilisant l'op�rateur de flux de sortie (<<). Retourne une r�f�rence           *****
***** au flux de sortie modifi�                                                                                                            *****
***********************************************************************************************************************************************/
std::ostream & operator<<(std::ostream & stream, const Sommet & SOMParam)
{
	stream << "Sommet numero " << SOMParam.SOMLireNumero()<<"\n";
	//stream << "Liste des arcs arrivant : \n" << SOMParam.lisSOMArcArrivant;
	//stream << "Liste des arcs partant : \n" << SOMParam.lisSOMArcPartant;
	return stream;
}
