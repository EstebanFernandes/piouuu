#include "CGraphe.h"

/*****************************************************************************
***** CGraphe() : Constructeur par d�faut                                *****
******************************************************************************
***** Entr�e : Aucune                                                    *****
***** Pr�condition : Aucune                                              *****
***** Sortie : Aucune                                                    *****
***** Postcondition : L'objet CGraphe est cr�� et est par d�faut orient� *****
*****************************************************************************/
CGraphe::CGraphe()
{
	bGRAType = Oriente;
}

/***********************************************************************************
***** CGraphe(bool bParam) : Constructeur de confort                           *****
************************************************************************************
***** Entr�e : bParam (bool�en repr�sentant le type de graphe)                 *****
***** Pr�condition : Aucune                                                    *****
***** Sortie : Aucune                                                          *****
***** Postcondition : L'objet CGraphe est cr�� avec le type de graphe sp�cifi� *****
***********************************************************************************/
CGraphe::CGraphe(bool bParam)
{
	bGRAType = bParam;
}

/*******************************************************************************************************************************************************
***** CGraphe(CGraphe & GRAParam) : Constructeur de recopie                                                                                        *****
********************************************************************************************************************************************************
***** Entr�e : Une r�f�rence � un objet CGraphe (GRAParam) � copier                                                                                *****
***** Pr�condition : Aucune                                                                                                                        *****
***** Sortie : Aucune                                                                                                                              *****
***** Postcondition : Cr�e un objet CGraphe en copiant les valeurs du graphe source (GRAParam), y compris la liste des sommets (lisGRAListeSommet) *****
*******************************************************************************************************************************************************/
CGraphe::CGraphe(CGraphe & GRAParam)
{
	bGRAType = GRAParam.bGRAType;
	lisGRAListeSommet = GRAParam.lisGRAListeSommet;
}

/*************************************************************************************
***** ~CGraphe() : Destructeur                                                   *****
**************************************************************************************
***** Entr�e : Aucune                                                            *****
***** Pr�condition : Aucune                                                      *****
***** Sortie : Aucune                                                            *****
***** Postcondition : D�truit l'objet CGraphe et lib�re toute ressource associ�e *****
*************************************************************************************/
CGraphe::~CGraphe()
{
}

/***************************************************************************************************************************************************************
***** GRATrouverSommet(int Identifiant) : Trouver un sommet dans le graphe                                                                                 *****
****************************************************************************************************************************************************************
***** Entr�e : Un entier repr�sentant l'identifiant du sommet � rechercher (Identifiant)                                                                   *****
***** Pr�condition : Aucune                                                                                                                                *****
***** Sortie : Un entier repr�sentant l'indice du sommet trouv� dans la liste des sommets (lisGRAListeSommet). Retourne -998 si le sommet n'est pas trouv� *****
***** Postcondition : Parcourt la liste des sommets (lisGRAListeSommet) et recherche le sommet ayant l'identifiant sp�cifi�.                               *****
***** Retourne l'indice du sommet trouv� ou -998 si le sommet n'est pas trouv�                                                                             *****
***************************************************************************************************************************************************************/
int CGraphe::GRATrouverSommet(int Identifiant)
{
	unsigned int taille = (unsigned int)lisGRAListeSommet.size();
	for (unsigned int uiBoucle = 0; uiBoucle < taille; uiBoucle++)
	{
		int tempId = lisGRAListeSommet[uiBoucle].SOMLireNumero();
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
***** Entr�e : Un entier repr�sentant le num�ro du sommet � ajouter (NumSommet)                                               *****
***** Pr�condition : Aucune                                                                                                   *****
***** Sortie : Aucune                                                                                                         *****
***** Postcondition : Ajoute un nouveau sommet � la liste des sommets (lisGRAListeSommet) avec le num�ro sp�cifi� (NumSommet) *****
**********************************************************************************************************************************/
void CGraphe::GRAAjouterSommet(int NumSommet)
{
		//v�rification que le int n'existe pas d�j�
		int trouve = GRATrouverSommet(NumSommet);
		if (trouve == SOMMET_NON_TROUVEE) //Le sommet n'existe pas, on peut donc l'ajouter
		{
			CSommetUpgrade sommetAajouter(NumSommet);
			lisGRAListeSommet.push_back(sommetAajouter);
		}
		else {
			CException existe(SommetExistant);
			throw (existe);
		}
}
//Surcharge qui prend un CSommet en parametre
void CGraphe::GRAAjouterSommet(CSommetUpgrade temp)
{
	//v�rification que le int n'existe pas d�j�
	int trouve = GRATrouverSommet(temp.SOMLireNumero());
	if (trouve == SOMMET_NON_TROUVEE) //Le sommet n'existe pas, on peut donc l'ajouter
	{
		lisGRAListeSommet.push_back(temp);
	}
	else {
		CException existe(SommetExistant);
		throw (existe);
	}
}

/*********************************************************************************************************************
***** GRAModifierSommet(int AncienNum, int NouveauNum) : Modifier un sommet dans le graphe                       *****
**********************************************************************************************************************
***** Entr�e : Deux entiers repr�sentant le num�ro d'origine du sommet � modifier et le nouveau num�ro du sommet *****
***** Pr�condition : Le sommet d'origine existe dans le graphe.													 *****
***** Sortie : Aucune																							 *****
***** Postcondition : Modifie le num�ro du sommet d'origine par le nouveau num�ro sp�cifi�.						 *****
***** Lance une exception de type int si le sommet n'est pas trouv�.											 *****
*********************************************************************************************************************/
void CGraphe::GRAModifierSommet(int AncienNum, int NouveauNum)
{
	int trouve = GRATrouverSommet(AncienNum);
	if (trouve == SOMMET_NON_TROUVEE) {
		CException introuvable(SommetSupprimerIntrouvable);
		throw(introuvable);
	}
	else {
		CSommet& sommetAModifier = lisGRAListeSommet[trouve];
		sommetAModifier.SOMModifierNumero(NouveauNum);
	}
}


/*****************************************************************************************************************************
***** GRASupprimerSommet(int NumSommet) : Supprimer un sommet du graphe                                                  *****
******************************************************************************************************************************
***** Entr�e : Un entier repr�sentant le num�ro du sommet � supprimer (NumSommet)                                        *****
***** Pr�condition : Aucune                                                                                              *****
***** Sortie : Aucune                                                                                                    *****
***** Postcondition : Supprime le sommet correspondant au num�ro sp�cifi� de la liste des sommets (lisGRAListeSommet).   *****
***** Lance une exception de type CException si le sommet n'est pas trouv�                                               *****
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
		CSommet& sommetASupprimer = lisGRAListeSommet[trouve];
		unsigned int uiBoucle;
		if (bGRAType == Oriente) {
			for (uiBoucle = 0;uiBoucle < sommetASupprimer.SOMTailleListeArc(Partant);uiBoucle++) {

				int SommetARCArrivantaSuppr = sommetASupprimer.SOMLireArcPartant()[uiBoucle].ARCObtenirDest();
				int idsommetarcsuppr = GRATrouverSommet(SommetARCArrivantaSuppr);
				lisGRAListeSommet[idsommetarcsuppr].SOMSupprimerArc(Arrivant, NumSommet);
			}
			unsigned int taille = sommetASupprimer.SOMTailleListeArc(Arrivant);
			for (uiBoucle = 0; uiBoucle < taille; uiBoucle++) {
				int SommetARCPartantaSuppr = sommetASupprimer.SOMLireArcArrivant()[uiBoucle].ARCObtenirDest();
				int idsommetarcsuppr = GRATrouverSommet(SommetARCPartantaSuppr);
				lisGRAListeSommet[idsommetarcsuppr].SOMSupprimerArc(Partant, NumSommet);
			}
		}
		else {
			for (uiBoucle = 0; uiBoucle < sommetASupprimer.SOMTailleListeArc(Partant);uiBoucle++) {
				int SommetArcPartantArrivant = sommetASupprimer.SOMLireArcPartant()[uiBoucle].ARCObtenirDest();
				lisGRAListeSommet[GRATrouverSommet(SommetArcPartantArrivant)].SOMSupprimerArc(Arrivant, NumSommet);
				lisGRAListeSommet[GRATrouverSommet(SommetArcPartantArrivant)].SOMSupprimerArc(Partant, NumSommet);
			}
		}
		lisGRAListeSommet.erase(lisGRAListeSommet.begin()+trouve);
	}
}

/*****************************************************************************************************************************************
***** GRAAjouterArc(int iSource, int iDestination) : Ajouter un arc au graphe                                                        *****
******************************************************************************************************************************************
***** Entr�e : Deux entiers repr�sentant les num�ros des sommets source et destination de l'arc (iSource, iDestination)              *****
***** Pr�condition : Aucune                                                                                                          *****
***** Sortie : Aucune                                                                                                                *****
***** Postcondition : Ajoute un nouvel arc reliant les sommets source et destination dans la liste des sommets (lisGRAListeSommet).  *****
***** Lance une exception de type int si l'un des sommets n'est pas trouv�                                                           *****
*****************************************************************************************************************************************/
void CGraphe::GRAAjouterArc(int iSource, int iDestination) {
	int trouveSource = GRATrouverSommet(iSource);
	int trouveDestination = GRATrouverSommet(iDestination);

	if (trouveSource != SOMMET_NON_TROUVEE || trouveDestination != SOMMET_NON_TROUVEE) {
		if (bGRAType == Oriente) {
			lisGRAListeSommet[trouveSource].SOMAjouterArc(Partant, iDestination);
			lisGRAListeSommet[trouveDestination].SOMAjouterArc(Arrivant, iSource);
		}
		else {
			lisGRAListeSommet[trouveSource].SOMAjouterArc(Partant, iDestination);
			lisGRAListeSommet[trouveSource].SOMAjouterArc(Arrivant, iDestination);
			lisGRAListeSommet[trouveDestination].SOMAjouterArc(Partant, iSource);
			lisGRAListeSommet[trouveDestination].SOMAjouterArc(Arrivant, iSource);
		}
	}
	else {
		CException introuvable(SommetDestinationIntrouvable);
		throw introuvable;
	}
}

/**********************************************************************************************************************************************************
***** GRAAjouterArc(int iSource, int iDestination, unsigned int uipoids) : Ajoute un arc au graphe en pr�cisant son poids si celui-ci est non orient� *****
***********************************************************************************************************************************************************
***** Entr�e : Deux entiers repr�sentant les num�ros des sommets source et destination de l'arc et un entier repr�sentant le poids de l'arc � cr�er   *****
***** Pr�condition : Aucune                                                                                                                           *****
***** Sortie : Aucune                                                                                                                                 *****
***** Postcondition : Ajoute un arc reliant les sommets source et destination et si le graphe est non orient� le poids sur l'arc est ajout�.          *****
***** Lance une exception si l'un des sommets n'est pas trouv�                                                                                        *****
**********************************************************************************************************************************************************/
void CGraphe::GRAAjouterArc(int iSource, int iDestination, double dpoids)
{
	if (dpoids < 0) {
		throw(CException(ValeurPoidsN�gatif));
	}
	int trouveSource = GRATrouverSommet(iSource);
	int trouveDestination = GRATrouverSommet(iDestination);
	CArc temp1(iSource, dpoids);
	CArc temp2(iDestination, dpoids);
	if (trouveSource != SOMMET_NON_TROUVEE || trouveDestination != SOMMET_NON_TROUVEE) {
		if (bGRAType == Oriente) {
			lisGRAListeSommet[trouveSource].SOMAjouterArc(Partant, iDestination);
			lisGRAListeSommet[trouveDestination].SOMAjouterArc(Arrivant, iSource);
		}
		else {
			lisGRAListeSommet[trouveSource].SOMAjouterArc(Partant, temp2);
			lisGRAListeSommet[trouveSource].SOMAjouterArc(Arrivant, temp2);
			lisGRAListeSommet[trouveDestination].SOMAjouterArc(Partant, temp1);
			lisGRAListeSommet[trouveDestination].SOMAjouterArc(Arrivant, temp1);
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
***** Entr�e : Quatre entiers repr�sentant les num�ros des sommets source et destination de l'arc � modifier : AncienSource, AncienneDestination, *****
***** NouvelleSource, NouvelleDestination																										  *****
***** Pr�condition : les sommets existent																										  *****
***** Sortie : Aucune																															  *****
***** Postcondition : Modifie l'arc reliant les sommets source et destination d'origine par un nouvel arc reliant les sommets source et			  *****
***** destination de remplacement. Lance une exception de type int si l'un des sommets n'est pas trouv�.										  *****
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
***** Entr�e : Deux entiers repr�sentant les num�ros des sommets source et destination de l'arc et un entier repr�sentant le nouveau poids de l'arc  *****
***** Pr�condition : Aucune                                                                                                                          *****
***** Sortie : Aucune                                                                                                                                *****
***** Postcondition : Modifie le valeur du poids de l'arc si celui-ci est trouv� sinon une exception est lanc�                                       *****
*********************************************************************************************************************************************************/
void CGraphe::GRAModifierArc(int iSource, int iDestination, double dpoids)
{
	if (dpoids < 0) {
		throw(CException(ValeurPoidsN�gatif));
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
***** Entr�e : Deux entiers repr�sentant les num�ros des sommets source et destination de l'arc (iSource, iDestination)              *****
***** Pr�condition : Aucune                                                                                                          *****
***** Sortie : Aucune                                                                                                                *****
***** Postcondition : Supprime un arc reliant les sommets source et destination dans la liste des sommets (lisGRAListeSommet).       *****
***** Lance une exception de type int si l'un des sommets n'est pas trouv�                                                           *****
*****************************************************************************************************************************************/
void CGraphe::GRASupprimerArc( int iSource, int iDestination)
{
	int trouveSource = GRATrouverSommet(iSource), trouveDestination = GRATrouverSommet(iDestination);
	if (trouveSource != SOMMET_NON_TROUVEE || trouveDestination != SOMMET_NON_TROUVEE)
	{
		if (bGRAType == Oriente) {
			lisGRAListeSommet[trouveDestination].SOMSupprimerArc(Arrivant, iSource);
			lisGRAListeSommet[trouveSource].SOMSupprimerArc(Partant, iDestination);
		}
		else {
			lisGRAListeSommet[trouveDestination].SOMSupprimerArc(Arrivant, iSource);
			lisGRAListeSommet[trouveDestination].SOMSupprimerArc(Partant, iSource);
			lisGRAListeSommet[trouveSource].SOMSupprimerArc(Partant, iDestination);
			lisGRAListeSommet[trouveSource].SOMSupprimerArc(Arrivant, iDestination);
		}
	}
	else {
	CException introuvable(SommetDestinationIntrouvable);
	throw(introuvable);
	}
}

/**************************************************************************************************************************************************
***** operator=(CGraphe & GRAParam) : Surcharge de l'op�rateur d'affectation (=) pour copier un graphe                                        *****
***************************************************************************************************************************************************
***** Entr�e : Une r�f�rence � un objet CGraphe (GRAParam) � copier                                                                           *****
***** Pr�condition : Aucune                                                                                                                   *****
***** Sortie : Une r�f�rence � un objet CGraphe                                                                                               *****
***** Postcondition : copie les valeurs du graphe source (GRAParam) dans l'objet actuel, y compris la liste des sommets (lisGRAListeSommet).  *****
***** Retourne une r�f�rence � l'objet CGraphe modifi�                                                                                        *****
**************************************************************************************************************************************************/
CGraphe& CGraphe::operator=(const CGraphe & GRAParam)
{
	bGRAType = GRAParam.bGRAType;
	lisGRAListeSommet = GRAParam.lisGRAListeSommet;
	return *this;
}

/***********************************************************************************************************************************************
***** operator<<(std::ostream & stream, const CGraphe & GRAParam) : Surcharge de l'op�rateur de sortie (<<) pour afficher un objet CGraphe *****
************************************************************************************************************************************************
***** Entr�e : Un flux de sortie et une r�f�rence constante � un objet CGraphe (GRAParam) � afficher                                       *****
***** Pr�condition : Aucune                                                                                                                *****
***** Sortie : Une r�f�rence � un flux de sorte                                                                                            *****
***** Postcondition : Affiche le contenu du graphe (liste des sommets et leurs arcs) dans le flux de sortie (stream) en utilisant          *****
***** l'op�rateur de flux de sortie (<<). Retourne une r�f�rence au flux de sortie modifi�                                                 *****
***********************************************************************************************************************************************/
std::ostream & operator<<(std::ostream & stream, const CGraphe & GRAParam)
{
	/*stream << "Affichage du graphe ";
	if (GRAParam.bGRAType == Oriente)
		stream << "oriente :\n";
	else
		stream << "non oriente :\n"<<std::endl;
		for (int i = 0; i < GRAParam.lisGRAListeSommet.size(); i++)
		{
			stream << "Sommet numero " << GRAParam.lisGRAListeSommet[i].SOMLireNumero() << std::endl;
			for (int j = 0; j < GRAParam.lisGRAListeSommet[i].SOMLireArcArrivant().size(); j++)
			{
				stream << GRAParam.lisGRAListeSommet[i].SOMLireArcArrivant()[j]<<std::endl;
			}
			stream << std::endl;
		}*/
	return stream;
}
