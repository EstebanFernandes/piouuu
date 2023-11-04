#include "CArc.h"

/*********************************************
***** CArc() : Constructeur par défaut   *****
**********************************************
***** Entrée : Aucune                    *****
***** Précondition : Aucune              *****
***** Sortie : Aucune                    *****
***** Postcondition : Crée un objet CArc *****
*********************************************/
CArc::CArc()
{
	iARCDestination = 0;
	uiARCpoids = 0;
}

/************************************************************************************
***** CArc(CArc & ARCParam) : Constructeur de recopie                           *****
*************************************************************************************
***** Entrée : Une référence à un objet CArc                                    *****
***** Précondition : Aucune                                                     *****
***** Sortie : Aucune                                                           *****
***** Postcondition : Crée un objet CArc en copiant les valeurs de l'arc source *****
************************************************************************************/
CArc::CArc(CArc & ARCParam)
{
	iARCDestination = ARCParam.ARCObtenirDest();
	uiARCpoids = ARCParam.uiARCpoids;
}


/*************************************************************************************************
***** CArc(int iValeur) : Constructeur de confort                                            *****
**************************************************************************************************
***** Entrée : Un entier représentant la valeur de destination de l'arc (iValeur)            *****
***** Précondition : Aucune                                                                  *****
***** Sortie : Aucune                                                                        *****
***** Postcondition : Crée un objet CArc en initialisant la valeur de destination de l'arc   *****
***** (iARCDestination) avec la valeur spécifiée (iValeur)                                   *****
*************************************************************************************************/
CArc::CArc(int iValeur)
{
	iARCDestination = iValeur;
	uiARCpoids = 0;
}

/****************************************************************************************************************************************
***** CArc(int iValeur, unsigned int poids) : Constructeur de confort                                                               *****
*****************************************************************************************************************************************
***** Entrée : Un entier représentant la valeur de destination de l'arc ainsi qu'un entier représentant la valeur du poids de l'arc *****
***** Précondition : Aucune                                                                                                         *****
***** Sortie : Aucune                                                                                                               *****
***** Postcondition : Crée un objet CArc initialisé avec la valeur de destination de l'arc ainsi que le poids de l'arc              *****
****************************************************************************************************************************************/
CArc::CArc(int iValeur, double poids)
{
	if (poids < 0) {
		throw(CException(ValeurPoidsNégatif));
	}
	iARCDestination = iValeur;
	uiARCpoids = poids;
}

/*************************************************************************
***** ~CArc() : Destructeur                                          *****
**************************************************************************
***** Entrée : Aucune                                                *****
***** Précondition : Aucune                                          *****
***** Sortie : Aucune                                                *****
***** Postcondition : Détruit l'objet CArc et libère toute ressource *****
*************************************************************************/
CArc::~CArc()
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
int CArc::ARCObtenirDest()
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
void CArc::ARCModifier(int iValeur)
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
void CArc::ARCModifier(double poids)
{
	if (poids < 0) throw(CException(ValeurPoidsNégatif));
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
void CArc::ARCModifier(int iDestination, double poids)
{
	if (poids < 0) throw(CException(ValeurPoidsNégatif));
	uiARCpoids = poids;
	iARCDestination = iDestination;
}

/*****************************************************************************************************
***** CArc& operator=(const CArc& ARCParam) : Opérateur égale pour la classe CArc                *****
******************************************************************************************************
***** Entrée : ARCParam (référence constante vers un objet CArc)                                 *****
***** Précondition : Aucune                                                                      *****
***** Sortie : Une référence vers l'objet CArc courant                                           *****
***** Postcondition : L'objet CArc courant est assigné avec les valeurs de l'objet CArc ARCParam *****
*****************************************************************************************************/
CArc & CArc::operator=(const CArc & ARCParam)
{
	this->iARCDestination = ARCParam.iARCDestination;
	uiARCpoids = ARCParam.uiARCpoids;
	return *this;
}

/*****************************************************************************************************************************************
***** operator<<(std::ostream & stream, const CArc & ARCParam) : Surcharge de l'opérateur de sortie (<<) pour afficher un objet CArc *****
******************************************************************************************************************************************
***** Entrée : Un flux de sortie (stream) et une référence constante à un objet CArc (ARCParam) à afficher                           *****
***** Précondition : Aucune                                                                                                          *****
***** Sortie : Une référence à un flux de sortie                                                                                     *****
***** Postcondition : Affiche la valeur de destination de l'arc (iARCDestination) dans le flux de sortie en utilisant                *****
***** l'opérateur de flux de sortie (<<). Retourne une référence au flux de sortie modifié                                           *****
*****************************************************************************************************************************************/
std::ostream & operator<<(std::ostream & stream, const CArc & ARCParam)
{
	stream << "-->" << ARCParam.iARCDestination;
	if(ARCParam.uiARCpoids!=0) 
		stream<< ", poids : "<<ARCParam.uiARCpoids;
	return stream;
}
