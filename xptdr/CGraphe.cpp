#include "CGraphe.h"

/*****************************************************************************
***** CGraphe() : Constructeur par défaut                                *****
******************************************************************************
***** Entrée : Aucune                                                    *****
***** Précondition : Aucune                                              *****
***** Sortie : Aucune                                                    *****
***** Postcondition : L'objet CGraphe est créé et est par défaut orienté *****
*****************************************************************************/
CGraphe::CGraphe()
{
	bGRAType = Oriente;
}

/***********************************************************************************
***** CGraphe(bool bParam) : Constructeur de confort                           *****
************************************************************************************
***** Entrée : bParam (booléen représentant le type de graphe)                 *****
***** Précondition : Aucune                                                    *****
***** Sortie : Aucune                                                          *****
***** Postcondition : L'objet CGraphe est créé avec le type de graphe spécifié *****
***********************************************************************************/
CGraphe::CGraphe(bool bParam)
{
	bGRAType = bParam;
}

/*******************************************************************************************************************************************************
***** CGraphe(CGraphe & GRAParam) : Constructeur de recopie                                                                                        *****
********************************************************************************************************************************************************
***** Entrée : Une référence à un objet CGraphe (GRAParam) à copier                                                                                *****
***** Précondition : Aucune                                                                                                                        *****
***** Sortie : Aucune                                                                                                                              *****
***** Postcondition : Crée un objet CGraphe en copiant les valeurs du graphe source (GRAParam), y compris la liste des sommets (lisGRAListeSommet) *****
*******************************************************************************************************************************************************/
CGraphe::CGraphe(CGraphe & GRAParam)
{
	bGRAType = GRAParam.bGRAType;
	lisGRAListeSommet = GRAParam.lisGRAListeSommet;
}

/*************************************************************************************
***** ~CGraphe() : Destructeur                                                   *****
**************************************************************************************
***** Entrée : Aucune                                                            *****
***** Précondition : Aucune                                                      *****
***** Sortie : Aucune                                                            *****
***** Postcondition : Détruit l'objet CGraphe et libère toute ressource associée *****
*************************************************************************************/
CGraphe::~CGraphe()
{
}

/***************************************************************************************************************************************************************
***** GRATrouverSommet(int Identifiant) : Trouver un sommet dans le graphe                                                                                 *****
****************************************************************************************************************************************************************
***** Entrée : Un entier représentant l'identifiant du sommet à rechercher (Identifiant)                                                                   *****
***** Précondition : Aucune                                                                                                                                *****
***** Sortie : Un entier représentant l'indice du sommet trouvé dans la liste des sommets (lisGRAListeSommet). Retourne -998 si le sommet n'est pas trouvé *****
***** Postcondition : Parcourt la liste des sommets (lisGRAListeSommet) et recherche le sommet ayant l'identifiant spécifié.                               *****
***** Retourne l'indice du sommet trouvé ou -998 si le sommet n'est pas trouvé                                                                             *****
***************************************************************************************************************************************************************/
int CGraphe::GRATrouverSommet(int Identifiant)
{
	unsigned int taille = lisGRAListeSommet.LISTaille();
	for (unsigned int uiBoucle = 0; uiBoucle < taille; uiBoucle++)
	{
		int tempId = lisGRAListeSommet.LISLire(uiBoucle).SOMLireNumero();
		if (Identifiant == tempId)
		{
			return uiBoucle;
		}
	}
		return SOMMET_NON_TROUVEE;
}

/**********************************************************************************************************************************
***** GRAAjouterSommet(int NumSommet) : Ajouter un sommet au graphe                                                           *****
***********************************************************************************************************************************
***** Entrée : Un entier représentant le numéro du sommet à ajouter (NumSommet)                                               *****
***** Précondition : Aucune                                                                                                   *****
***** Sortie : Aucune                                                                                                         *****
***** Postcondition : Ajoute un nouveau sommet à la liste des sommets (lisGRAListeSommet) avec le numéro spécifié (NumSommet) *****
**********************************************************************************************************************************/
void CGraphe::GRAAjouterSommet(int NumSommet)
{
		//vérification que le int n'existe pas déjà
		int trouve = GRATrouverSommet(NumSommet);
		if (trouve == SOMMET_NON_TROUVEE) //Le sommet n'existe pas, on peut donc l'ajouter
		{
			CSommet sommetAajouter(NumSommet);
			lisGRAListeSommet.LISAjouterDernier(sommetAajouter);
		}
		else {
			CException existe(SommetExistant);
			throw (existe);
		}
}

void CGraphe::GRAAjouterSommet(CSommet somParam) 
{
	if (GRATrouverSommet(somParam.SOMLireNumero()) == SOMMET_NON_TROUVEE)
	{
		lisGRAListeSommet.LISAjouterDernier(somParam);
	}
}

/*********************************************************************************************************************
***** GRAModifierSommet(int AncienNum, int NouveauNum) : Modifier un sommet dans le graphe                       *****
**********************************************************************************************************************
***** Entrée : Deux entiers représentant le numéro d'origine du sommet à modifier et le nouveau numéro du sommet *****
***** Précondition : Le sommet d'origine existe dans le graphe.													 *****
***** Sortie : Aucune																							 *****
***** Postcondition : Modifie le numéro du sommet d'origine par le nouveau numéro spécifié.						 *****
***** Lance une exception de type int si le sommet n'est pas trouvé.											 *****
*********************************************************************************************************************/
void CGraphe::GRAModifierSommet(int AncienNum, int NouveauNum)
{
	int trouve = GRATrouverSommet(AncienNum);
	if (trouve == SOMMET_NON_TROUVEE) {
		CException introuvable(SommetSupprimerIntrouvable);
		throw(introuvable);
	}
	else {
		CSommet& sommetAModifier = lisGRAListeSommet.LISLire(trouve);
		sommetAModifier.SOMModifierNumero(NouveauNum);
	}
}


/*****************************************************************************************************************************
***** GRASupprimerSommet(int NumSommet) : Supprimer un sommet du graphe                                                  *****
******************************************************************************************************************************
***** Entrée : Un entier représentant le numéro du sommet à supprimer (NumSommet)                                        *****
***** Précondition : Aucune                                                                                              *****
***** Sortie : Aucune                                                                                                    *****
***** Postcondition : Supprime le sommet correspondant au numéro spécifié de la liste des sommets (lisGRAListeSommet).   *****
***** Lance une exception de type CException si le sommet n'est pas trouvé                                               *****
*****************************************************************************************************************************/
void CGraphe::GRASupprimerSommet(int NumSommet)
{
	int trouve = GRATrouverSommet(NumSommet);
	if (trouve == SOMMET_NON_TROUVEE) //le sommet n'existe pas, on ne peut donc pas le supprimer
	{
		CException introuvable(SommetSupprimerIntrouvable);
		throw(introuvable);
	}
	else {
		CSommet& sommetASupprimer = lisGRAListeSommet.LISLire(trouve);
		unsigned int uiBoucle;
		if (bGRAType == Oriente) {
			for (uiBoucle = 0;uiBoucle < sommetASupprimer.SOMTailleListeArc(Partant);uiBoucle++) {

				int SommetARCArrivantaSuppr = sommetASupprimer.SOMLireArcPartant().LISLire(uiBoucle).ARCObtenirDest();
				int idsommetarcsuppr = GRATrouverSommet(SommetARCArrivantaSuppr);
				lisGRAListeSommet.LISLire(idsommetarcsuppr).SOMSupprimerArc(Arrivant, NumSommet);
			}
			unsigned int taille = sommetASupprimer.SOMTailleListeArc(Arrivant);
			for (uiBoucle = 0; uiBoucle < taille; uiBoucle++) {
				int SommetARCPartantaSuppr = sommetASupprimer.SOMLireArcArrivant().LISLire(uiBoucle).ARCObtenirDest();
				int idsommetarcsuppr = GRATrouverSommet(SommetARCPartantaSuppr);
				lisGRAListeSommet.LISLire(idsommetarcsuppr).SOMSupprimerArc(Partant, NumSommet);
			}
		}
		else {
			for (uiBoucle = 0; uiBoucle < sommetASupprimer.SOMTailleListeArc(Partant);uiBoucle++) {
				int SommetArcPartantArrivant = sommetASupprimer.SOMLireArcPartant().LISLire(uiBoucle).ARCObtenirDest();
				lisGRAListeSommet.LISLire(GRATrouverSommet(SommetArcPartantArrivant)).SOMSupprimerArc(Arrivant, NumSommet);
				lisGRAListeSommet.LISLire(GRATrouverSommet(SommetArcPartantArrivant)).SOMSupprimerArc(Partant, NumSommet);
			}
		}
		lisGRAListeSommet.LISSupprimer(trouve);
	}
}

/*****************************************************************************************************************************************
***** GRAAjouterArc(int iSource, int iDestination) : Ajouter un arc au graphe                                                        *****
******************************************************************************************************************************************
***** Entrée : Deux entiers représentant les numéros des sommets source et destination de l'arc (iSource, iDestination)              *****
***** Précondition : Aucune                                                                                                          *****
***** Sortie : Aucune                                                                                                                *****
***** Postcondition : Ajoute un nouvel arc reliant les sommets source et destination dans la liste des sommets (lisGRAListeSommet).  *****
***** Lance une exception de type int si l'un des sommets n'est pas trouvé                                                           *****
*****************************************************************************************************************************************/
void CGraphe::GRAAjouterArc(int iSource, int iDestination) {
	int trouveSource = GRATrouverSommet(iSource);
	int trouveDestination = GRATrouverSommet(iDestination);

	if (trouveSource != SOMMET_NON_TROUVEE || trouveDestination != SOMMET_NON_TROUVEE) {
		if (bGRAType == Oriente) {
			lisGRAListeSommet.LISLire(trouveSource).SOMAjouterArc(Partant, iDestination);
			lisGRAListeSommet.LISLire(trouveDestination).SOMAjouterArc(Arrivant, iSource);
		}
		else {
			lisGRAListeSommet.LISLire(trouveSource).SOMAjouterArc(Partant, iDestination);
			lisGRAListeSommet.LISLire(trouveSource).SOMAjouterArc(Arrivant, iDestination);
			lisGRAListeSommet.LISLire(trouveDestination).SOMAjouterArc(Partant, iSource);
			lisGRAListeSommet.LISLire(trouveDestination).SOMAjouterArc(Arrivant, iSource);
		}
	}
	else {
		CException introuvable(SommetDestinationIntrouvable);
		throw introuvable;
	}
}

/**********************************************************************************************************************************************************
***** GRAAjouterArc(int iSource, int iDestination, unsigned int uipoids) : Ajoute un arc au graphe en précisant son poids si celui-ci est non orienté *****
***********************************************************************************************************************************************************
***** Entrée : Deux entiers représentant les numéros des sommets source et destination de l'arc et un entier représentant le poids de l'arc à créer   *****
***** Précondition : Aucune                                                                                                                           *****
***** Sortie : Aucune                                                                                                                                 *****
***** Postcondition : Ajoute un arc reliant les sommets source et destination et si le graphe est non orienté le poids sur l'arc est ajouté.          *****
***** Lance une exception si l'un des sommets n'est pas trouvé                                                                                        *****
**********************************************************************************************************************************************************/
void CGraphe::GRAAjouterArc(int iSource, int iDestination, double dpoids)
{
	if (dpoids < 0) {
		throw(CException(ValeurPoidsNégatif));
	}
	int trouveSource = GRATrouverSommet(iSource);
	int trouveDestination = GRATrouverSommet(iDestination);
	CArc temp1(iSource, dpoids);
	CArc temp2(iDestination, dpoids);
	if (trouveSource != SOMMET_NON_TROUVEE || trouveDestination != SOMMET_NON_TROUVEE) {
		if (bGRAType == Oriente) {
			lisGRAListeSommet.LISLire(trouveSource).SOMAjouterArc(Partant, iDestination);
			lisGRAListeSommet.LISLire(trouveDestination).SOMAjouterArc(Arrivant, iSource);
		}
		else {
			lisGRAListeSommet.LISLire(trouveSource).SOMAjouterArc(Partant, temp2);
			lisGRAListeSommet.LISLire(trouveSource).SOMAjouterArc(Arrivant, temp2);
			lisGRAListeSommet.LISLire(trouveDestination).SOMAjouterArc(Partant, temp1);
			lisGRAListeSommet.LISLire(trouveDestination).SOMAjouterArc(Arrivant, temp1);
		}
	}
	else {
		CException introuvable(SommetDestinationIntrouvable);
		throw introuvable;
	}
}

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
void CGraphe::GRAModifierArc(int AncienSource, int AncienneDestination, int NouvelleSource, int NouvelleDestination) {
	int indiceAncienSource = GRATrouverSommet(AncienSource);
	int indiceAncienneDestination = GRATrouverSommet(AncienneDestination);
	if (indiceAncienSource == SOMMET_NON_TROUVEE || indiceAncienneDestination == SOMMET_NON_TROUVEE) {
		CException introuvable(SommetSourceIntrouvable);
		throw introuvable;
	}
	int indiceNouvelleSource = GRATrouverSommet(NouvelleSource);
	int indiceNouvelleDestination = GRATrouverSommet(NouvelleDestination);
	if (indiceNouvelleSource == SOMMET_NON_TROUVEE || indiceNouvelleDestination == SOMMET_NON_TROUVEE) {
		CException introuvable(SommetSourceIntrouvable);
		throw introuvable;
	}
	GRASupprimerArc(AncienSource, AncienneDestination);
	GRAAjouterArc(NouvelleSource, NouvelleDestination);
}

/*********************************************************************************************************************************************************
***** GRAModifierArc(int iSource, int iDestination, unsigned int uipoids) : Modifie la valeur du poids de l'arc                                      *****
**********************************************************************************************************************************************************
***** Entrée : Deux entiers représentant les numéros des sommets source et destination de l'arc et un entier représentant le nouveau poids de l'arc  *****
***** Précondition : Aucune                                                                                                                          *****
***** Sortie : Aucune                                                                                                                                *****
***** Postcondition : Modifie le valeur du poids de l'arc si celui-ci est trouvé sinon une exception est lancé                                       *****
*********************************************************************************************************************************************************/
void CGraphe::GRAModifierArc(int iSource, int iDestination, double dpoids)
{
	if (dpoids < 0) {
		throw(CException(ValeurPoidsNégatif));
	}
	int indiceSource = GRATrouverSommet(iSource);
	int indiceDestination = GRATrouverSommet(iDestination);
	if (indiceSource == SOMMET_NON_TROUVEE || indiceDestination == SOMMET_NON_TROUVEE) {
		CException introuvable(SommetSourceIntrouvable);
		throw introuvable;
	}
	GRASupprimerArc(indiceSource, indiceDestination);
	GRAAjouterArc(indiceSource, indiceDestination, dpoids);
}


/*****************************************************************************************************************************************
***** GRASupprimerArc(int iSource, int iDestination) : Supprime un arc au graphe                                                     *****
******************************************************************************************************************************************
***** Entrée : Deux entiers représentant les numéros des sommets source et destination de l'arc (iSource, iDestination)              *****
***** Précondition : Aucune                                                                                                          *****
***** Sortie : Aucune                                                                                                                *****
***** Postcondition : Supprime un arc reliant les sommets source et destination dans la liste des sommets (lisGRAListeSommet).       *****
***** Lance une exception de type int si l'un des sommets n'est pas trouvé                                                           *****
*****************************************************************************************************************************************/
void CGraphe::GRASupprimerArc( int iSource, int iDestination)
{
	int trouveSource = GRATrouverSommet(iSource), trouveDestination = GRATrouverSommet(iDestination);
	if (trouveSource != SOMMET_NON_TROUVEE || trouveDestination != SOMMET_NON_TROUVEE)
	{
		if (bGRAType == Oriente) {
			lisGRAListeSommet.LISLire(trouveDestination).SOMSupprimerArc(Arrivant, iSource);
			lisGRAListeSommet.LISLire(trouveSource).SOMSupprimerArc(Partant, iDestination);
		}
		else {
			lisGRAListeSommet.LISLire(trouveDestination).SOMSupprimerArc(Arrivant, iSource);
			lisGRAListeSommet.LISLire(trouveDestination).SOMSupprimerArc(Partant, iSource);
			lisGRAListeSommet.LISLire(trouveSource).SOMSupprimerArc(Partant, iDestination);
			lisGRAListeSommet.LISLire(trouveSource).SOMSupprimerArc(Arrivant, iDestination);
		}
	}
	else {
	CException introuvable(SommetDestinationIntrouvable);
	throw(introuvable);
	}
}

/**************************************************************************************************************************************************
***** operator=(CGraphe & GRAParam) : Surcharge de l'opérateur d'affectation (=) pour copier un graphe                                        *****
***************************************************************************************************************************************************
***** Entrée : Une référence à un objet CGraphe (GRAParam) à copier                                                                           *****
***** Précondition : Aucune                                                                                                                   *****
***** Sortie : Une référence à un objet CGraphe                                                                                               *****
***** Postcondition : copie les valeurs du graphe source (GRAParam) dans l'objet actuel, y compris la liste des sommets (lisGRAListeSommet).  *****
***** Retourne une référence à l'objet CGraphe modifié                                                                                        *****
**************************************************************************************************************************************************/
CGraphe& CGraphe::operator=(const CGraphe & GRAParam)
{
	bGRAType = GRAParam.bGRAType;
	lisGRAListeSommet = GRAParam.lisGRAListeSommet;
	return *this;
}

/***********************************************************************************************************************************************
***** operator<<(std::ostream & stream, const CGraphe & GRAParam) : Surcharge de l'opérateur de sortie (<<) pour afficher un objet CGraphe *****
************************************************************************************************************************************************
***** Entrée : Un flux de sortie et une référence constante à un objet CGraphe (GRAParam) à afficher                                       *****
***** Précondition : Aucune                                                                                                                *****
***** Sortie : Une référence à un flux de sorte                                                                                            *****
***** Postcondition : Affiche le contenu du graphe (liste des sommets et leurs arcs) dans le flux de sortie (stream) en utilisant          *****
***** l'opérateur de flux de sortie (<<). Retourne une référence au flux de sortie modifié                                                 *****
***********************************************************************************************************************************************/
std::ostream & operator<<(std::ostream & stream, const CGraphe & GRAParam)
{
	stream << "Affichage du graphe ";
	if (GRAParam.bGRAType == Oriente)
		stream << "oriente :\n";
	else
		stream << "non oriente :\n"<<std::endl;
		for (int i = 0; i < GRAParam.lisGRAListeSommet.LISTaille(); i++)
		{
			stream << "Sommet numero " << GRAParam.lisGRAListeSommet.LISLire(i).SOMLireNumero()<<std::endl;
			for (int j = 0; j < GRAParam.lisGRAListeSommet.LISLire(i).SOMLireArcArrivant().LISTaille(); j++)
			{
				stream << GRAParam.lisGRAListeSommet.LISLire(i).SOMLireArcArrivant().LISLire(j)<<std::endl;
			}
			stream << std::endl;
		}
	return stream;
}
