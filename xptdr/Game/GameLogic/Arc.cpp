#include "Arc.h"

/*********************************************
***** Arc() : Constructeur par défaut   *****
**********************************************
***** Entrée : Aucune                    *****
***** Précondition : Aucune              *****
***** Sortie : Aucune                    *****
***** Postcondition : Crée un objet Arc *****
*********************************************/
Arc::Arc()
{
	iARCDestination = 0;
	uiARCpoids = 0;
}

/************************************************************************************
***** Arc(Arc & ARCParam) : Constructeur de recopie                           *****
*************************************************************************************
***** Entrée : Une référence à un objet Arc                                    *****
***** Précondition : Aucune                                                     *****
***** Sortie : Aucune                                                           *****
***** Postcondition : Crée un objet Arc en copiant les valeurs de l'arc source *****
************************************************************************************/
Arc::Arc(const Arc & ARCParam)
{
	iARCDestination = ARCParam.iARCDestination;
	uiARCpoids = ARCParam.uiARCpoids;
}


/*************************************************************************************************
***** Arc(int iValeur) : Constructeur de confort                                            *****
**************************************************************************************************
***** Entrée : Un entier représentant la valeur de destination de l'arc (iValeur)            *****
***** Précondition : Aucune                                                                  *****
***** Sortie : Aucune                                                                        *****
***** Postcondition : Crée un objet Arc en initialisant la valeur de destination de l'arc   *****
***** (iARCDestination) avec la valeur spécifiée (iValeur)                                   *****
*************************************************************************************************/
Arc::Arc(int iValeur)
{
	iARCDestination = iValeur;
	uiARCpoids = 0;
}

/****************************************************************************************************************************************
***** Arc(int iValeur, unsigned int poids) : Constructeur de confort                                                               *****
*****************************************************************************************************************************************
***** Entrée : Un entier représentant la valeur de destination de l'arc ainsi qu'un entier représentant la valeur du poids de l'arc *****
***** Précondition : Aucune                                                                                                         *****
***** Sortie : Aucune                                                                                                               *****
***** Postcondition : Crée un objet Arc initialisé avec la valeur de destination de l'arc ainsi que le poids de l'arc              *****
****************************************************************************************************************************************/
Arc::Arc(int iValeur, double poids)
{
	if (poids < 0) {
		throw(Exception(ValeurPoidsNégatif));
	}
	iARCDestination = iValeur;
	uiARCpoids = poids;
}

/*************************************************************************
***** ~Arc() : Destructeur                                          *****
**************************************************************************
***** Entrée : Aucune                                                *****
***** Précondition : Aucune                                          *****
***** Sortie : Aucune                                                *****
***** Postcondition : Détruit l'objet Arc et libère toute ressource *****
*************************************************************************/
Arc::~Arc()
{
}

/**********************************************************************************************
***** ARCObtenirDest() : Obtenir la valeur de destination de l'arc                        *****
***********************************************************************************************
***** Entrée : Aucune                                                                     *****
***** Précondition : Aucune                                                               *****
***** Sortie : Un entier représentant la valeur de destination de l'arc (iARCDestination) *****
***** Postcondition : Retourne la valeur de destination de l'arc (iARCDestination)        *****
**********************************************************************************************/
int Arc::ARCObtenirDest()
{
	return iARCDestination;
}
/*****************************************************************************************************
***** ARCModifier(int iValeur) : Modifier la valeur de destination de l'arc                      *****
******************************************************************************************************
***** Entrée : Un entier représentant la nouvelle valeur de destination de l'arc (iValeur)       *****
***** Précondition : Aucune                                                                      *****
***** Sortie : Aucune                                                                            *****
***** Postcondition : Modifie la valeur de destination de l'arc (iARCDestination) en utilisant   *****
***** la nouvelle valeur spécifiée (iValeur)                                                     *****
*****************************************************************************************************/
void Arc::ARCModifier(int iValeur)
{
	iARCDestination = iValeur;
}

/************************************************************************************************
***** ARCModifier(unsigned int poids) : Modifier la valeur du poids de l'arc                *****
*************************************************************************************************
***** Entrée : Un entier positif représentant la nouvelle valeur du poids de l'arc          *****
***** Précondition : Aucune                                                                 *****
***** Sortie : Aucune                                                                       *****
***** Postcondition : Modifie la valeur du poids de l'arc avec la nouvelle valeur spécifiée *****
************************************************************************************************/
void Arc::ARCModifier(double poids)
{
	if (poids < 0) throw(Exception(ValeurPoidsNégatif));
	uiARCpoids = poids;
}

/********************************************************************************************************************************************************
***** ARCModifier(int iDestination, unsigned int poids) : Modifier la valeur du poids de l'arc et la valeur de destination de l'arc                 *****
*********************************************************************************************************************************************************
***** Entrée : Un entier positif représentant la nouvelle valeur du poids de l'arc ainsi qu'un entier représentant la nouvelle destination de l'arc *****
***** Précondition : Aucune                                                                                                                         *****
***** Sortie : Aucune                                                                                                                               *****
***** Postcondition : Modifie la valeur du poids de l'arc et la destination de l'arc avec les nouvelles valeurs spécifiées                          *****
********************************************************************************************************************************************************/
void Arc::ARCModifier(int iDestination, double poids)
{
	if (poids < 0) throw(Exception(ValeurPoidsNégatif));
	uiARCpoids = poids;
	iARCDestination = iDestination;
}

/*****************************************************************************************************
***** Arc& operator=(const Arc& ARCParam) : Opérateur égale pour la classe Arc                *****
******************************************************************************************************
***** Entrée : ARCParam (référence constante vers un objet Arc)                                 *****
***** Précondition : Aucune                                                                      *****
***** Sortie : Une référence vers l'objet Arc courant                                           *****
***** Postcondition : L'objet Arc courant est assigné avec les valeurs de l'objet Arc ARCParam *****
*****************************************************************************************************/
Arc & Arc::operator=(const Arc & ARCParam)
{
	this->iARCDestination = ARCParam.iARCDestination;
	uiARCpoids = ARCParam.uiARCpoids;
	return *this;
}

/*****************************************************************************************************************************************
***** operator<<(std::ostream & stream, const Arc & ARCParam) : Surcharge de l'opérateur de sortie (<<) pour afficher un objet Arc *****
******************************************************************************************************************************************
***** Entrée : Un flux de sortie (stream) et une référence constante à un objet Arc (ARCParam) à afficher                           *****
***** Précondition : Aucune                                                                                                          *****
***** Sortie : Une référence à un flux de sortie                                                                                     *****
***** Postcondition : Affiche la valeur de destination de l'arc (iARCDestination) dans le flux de sortie en utilisant                *****
***** l'opérateur de flux de sortie (<<). Retourne une référence au flux de sortie modifié                                           *****
*****************************************************************************************************************************************/
std::ostream & operator<<(std::ostream & stream, const Arc & ARCParam)
{
	stream << "-->" << ARCParam.iARCDestination;
	if(ARCParam.uiARCpoids!=0) 
		stream<< ", poids : "<<ARCParam.uiARCpoids;
	return stream;
}
