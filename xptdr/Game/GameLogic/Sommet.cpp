#include "Sommet.h"

/**************************************************************************************
***** Sommet() : Constructeur par défaut                                         *****
***************************************************************************************
***** Entrée : Aucune                                                             *****
***** Précondition : Aucune                                                       *****
***** Sortie : Aucune                                                             *****
***** Postcondition : Crée un objet Sommet sans aucune initialisation spécifique *****
**************************************************************************************/
Sommet::Sommet()
{
}

/**************************************************************************************************
***** Sommet(int Num) : Constructeur de confort                                              *****
***************************************************************************************************
***** Entrée : Un entier représentant le numéro du sommet (Num)                               *****
***** Précondition : Aucune                                                                   *****
***** Sortie : Aucune                                                                         *****
***** Postcondition : Crée un objet Sommet en initialisant le numéro du sommet (iSOMNumero)  *****
***** avec la valeur spécifiée (Num)                                                          *****
**************************************************************************************************/
Sommet::Sommet(int Num)
{
	iSOMNumero = Num;
}

/***********************************************************************************************************************************
***** Sommet(Sommet & SOMParam) : Constructeur de recopie                                                                    *****
************************************************************************************************************************************
***** Entrée : Une référence à un objet Sommet (SOMParam) à copier                                                            *****
***** Précondition : Aucune                                                                                                    *****
***** Sortie : Aucune                                                                                                          *****
***** Postcondition : Crée un objet Sommet en copiant les valeurs du sommet source (SOMParam), y compris le numéro du sommet  *****
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
***** Entrée : Aucune                                                            *****
***** Précondition : Aucune                                                      *****
***** Sortie : Aucune                                                            *****
***** Postcondition : Détruit l'objet Sommet et libère toute ressource associée *****
*************************************************************************************/
Sommet::~Sommet()
{
}

/***************************************************************************
***** SOMLireNumero() const : Lire le numéro du sommet                 *****
****************************************************************************
***** Entrée : Aucune                                                  *****
***** Précondition : Aucune                                            *****
***** Sortie : Un entier représentant le numéro du sommet (iSOMNumero) *****
***** Postcondition : Retourne le numéro du sommet                     *****
***************************************************************************/
int Sommet::SOMLireNumero() const
{
	return iSOMNumero;
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
***** SOMAjouterArc(bool type, Arc Arc) : Surcharge de la fonction SOMAjouter ajouter pour le cas où on a déjà l'arc qu'on veut ajouter *****
**********************************************************************************************************************************************
***** Entrée : un bool qui précise le type et un Arc qu'on va ajouter au sommet                                                         *****
***** Précondition : Aucune                                                                                                              *****
***** Sortie : Aucune                                                                                                                    *****
***** Postcondition : L'arc est ajouté au sommet                                                                                         *****
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
***** Entrée : Un booléen représentant le type d'arc (type) : Arrivant ou Partant, un entier représentant l'ancienne destination de l'arc          *****
***** (AncienneDestination) et un entier représentant la nouvelle destination de l'arc (NouvelleDestination)                                       *****
***** Précondition : Aucune                                                                                                                        *****
***** Sortie : Aucune                                                                                                                              *****
***** Postcondition : Modifie la destination de l'arc spécifié dans la liste d'arcs arrivants (lisSOMArcArrivant) ou dans la liste d'arcs		   *****
***** partants (lisSOMArcPartant), en fonction du type d'arc spécifié																			   *****
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
***** Entrée : un bool qui précise le type, la destination de l'arc à modifier et le nouveau poids de l'arc *****
***** Précondition : Aucune                                                                                 *****
***** Sortie : Aucune                                                                                       *****
***** Postcondition : L'arc est modifié avec un nouveau poids                                               *****
****************************************************************************************************************/
void Sommet::SOMModifierArc(bool type, int Destination, double dPoids)
{
	if (dPoids < 0) {
		throw(Exception(ValeurPoidsNégatif));
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
***** Entrée : Un booléen représentant le type d'arc (type) : Arrivant ou Partant, et un entier                                    *****
***** Précondition : Aucune                                                                                                        *****
***** Sortie : Aucune                                                                                                              *****
***** Postcondition : Supprime l'arc correspondant à la destination spécifiée de la liste d'arcs arrivants (lisSOMArcArrivant) ou  *****
***** de la liste d'arcs partants (lisSOMArcPartant), en fonction du type d'arc spécifié                                           *****
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
***** Entrée : Un booléen représentant le type d'arc (type) : Arrivant ou Partant, et un entier représentant la destination de                    *****
***** l'arc à rechercher (Element)                                                                                                                *****
***** Précondition : Aucune                                                                                                                       *****
***** Sortie : Un entier représentant l'indice de l'arc trouvé dans la liste d'arcs arrivants (lisSOMArcArrivant) ou dans la liste                *****
***** d'arcs partants (lisSOMArcPartant). Retourne -999 si l'arc n'est pas trouvé                                                                 *****
***** Postcondition : Parcourt la liste d'arcs arrivants (lisSOMArcArrivant) ou la liste d'arcs partants (lisSOMArcPartant), en fonction du       *****
***** type d'arc spécifié, et recherche l'arc ayant la destination spécifiée. Retourne l'indice de l'arc trouvé ou -999 si l'arc n'est pas trouvé *****
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
***** operator=(Sommet & SOMParam) : Surcharge de l'opérateur d'affectation (=) pour copier un sommet                               *****
******************************************************************************************************************************************
***** Entrée : Une référence à un objet Sommet (SOMParam) à copier                                                                  *****
***** Précondition : Aucune                                                                                                          *****
***** Sortie : Une référence à un objet Sommet                                                                                      *****
***** Postcondition : Copie les valeurs du sommet source (SOMParam) dans l'objet actuel, y compris le numéro du sommet (iSOMNumero)  *****
***** et les listes d'arcs arrivants et partants. Retourne une référence à l'objet Sommet modifié                                   *****
*****************************************************************************************************************************************/
Sommet & Sommet::operator=(const Sommet & SOMParam)
{
	iSOMNumero = SOMParam.iSOMNumero;
	lisSOMArcArrivant = SOMParam.lisSOMArcArrivant;
	lisSOMArcPartant = SOMParam.lisSOMArcPartant;
	return *this;
}



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
std::ostream & operator<<(std::ostream & stream, const Sommet & SOMParam)
{
	stream << "Sommet numero " << SOMParam.SOMLireNumero()<<"\n";
	//stream << "Liste des arcs arrivant : \n" << SOMParam.lisSOMArcArrivant;
	//stream << "Liste des arcs partant : \n" << SOMParam.lisSOMArcPartant;
	return stream;
}
