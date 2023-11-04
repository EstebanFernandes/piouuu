#include "CArc.h"

/*********************************************
***** CArc() : Constructeur par d�faut   *****
**********************************************
***** Entr�e : Aucune                    *****
***** Pr�condition : Aucune              *****
***** Sortie : Aucune                    *****
***** Postcondition : Cr�e un objet CArc *****
*********************************************/
CArc::CArc()
{
	iARCDestination = 0;
	uiARCpoids = 0;
}

/************************************************************************************
***** CArc(CArc & ARCParam) : Constructeur de recopie                           *****
*************************************************************************************
***** Entr�e : Une r�f�rence � un objet CArc                                    *****
***** Pr�condition : Aucune                                                     *****
***** Sortie : Aucune                                                           *****
***** Postcondition : Cr�e un objet CArc en copiant les valeurs de l'arc source *****
************************************************************************************/
CArc::CArc(CArc & ARCParam)
{
	iARCDestination = ARCParam.ARCObtenirDest();
	uiARCpoids = ARCParam.uiARCpoids;
}


/*************************************************************************************************
***** CArc(int iValeur) : Constructeur de confort                                            *****
**************************************************************************************************
***** Entr�e : Un entier repr�sentant la valeur de destination de l'arc (iValeur)            *****
***** Pr�condition : Aucune                                                                  *****
***** Sortie : Aucune                                                                        *****
***** Postcondition : Cr�e un objet CArc en initialisant la valeur de destination de l'arc   *****
***** (iARCDestination) avec la valeur sp�cifi�e (iValeur)                                   *****
*************************************************************************************************/
CArc::CArc(int iValeur)
{
	iARCDestination = iValeur;
	uiARCpoids = 0;
}

/****************************************************************************************************************************************
***** CArc(int iValeur, unsigned int poids) : Constructeur de confort                                                               *****
*****************************************************************************************************************************************
***** Entr�e : Un entier repr�sentant la valeur de destination de l'arc ainsi qu'un entier repr�sentant la valeur du poids de l'arc *****
***** Pr�condition : Aucune                                                                                                         *****
***** Sortie : Aucune                                                                                                               *****
***** Postcondition : Cr�e un objet CArc initialis� avec la valeur de destination de l'arc ainsi que le poids de l'arc              *****
****************************************************************************************************************************************/
CArc::CArc(int iValeur, double poids)
{
	if (poids < 0) {
		throw(CException(ValeurPoidsN�gatif));
	}
	iARCDestination = iValeur;
	uiARCpoids = poids;
}

/*************************************************************************
***** ~CArc() : Destructeur                                          *****
**************************************************************************
***** Entr�e : Aucune                                                *****
***** Pr�condition : Aucune                                          *****
***** Sortie : Aucune                                                *****
***** Postcondition : D�truit l'objet CArc et lib�re toute ressource *****
*************************************************************************/
CArc::~CArc()
{
}

/**********************************************************************************************
***** ARCObtenirDest() : Obtenir la valeur de destination de l'arc                        *****
***********************************************************************************************
***** Entr�e : Aucune                                                                     *****
***** Pr�condition : Aucune                                                               *****
***** Sortie : Un entier repr�sentant la valeur de destination de l'arc (iARCDestination) *****
***** Postcondition : Retourne la valeur de destination de l'arc (iARCDestination)        *****
**********************************************************************************************/
int CArc::ARCObtenirDest()
{
	return iARCDestination;
}
/*****************************************************************************************************
***** ARCModifier(int iValeur) : Modifier la valeur de destination de l'arc                      *****
******************************************************************************************************
***** Entr�e : Un entier repr�sentant la nouvelle valeur de destination de l'arc (iValeur)       *****
***** Pr�condition : Aucune                                                                      *****
***** Sortie : Aucune                                                                            *****
***** Postcondition : Modifie la valeur de destination de l'arc (iARCDestination) en utilisant   *****
***** la nouvelle valeur sp�cifi�e (iValeur)                                                     *****
*****************************************************************************************************/
void CArc::ARCModifier(int iValeur)
{
	iARCDestination = iValeur;
}

/************************************************************************************************
***** ARCModifier(unsigned int poids) : Modifier la valeur du poids de l'arc                *****
*************************************************************************************************
***** Entr�e : Un entier positif repr�sentant la nouvelle valeur du poids de l'arc          *****
***** Pr�condition : Aucune                                                                 *****
***** Sortie : Aucune                                                                       *****
***** Postcondition : Modifie la valeur du poids de l'arc avec la nouvelle valeur sp�cifi�e *****
************************************************************************************************/
void CArc::ARCModifier(double poids)
{
	if (poids < 0) throw(CException(ValeurPoidsN�gatif));
	uiARCpoids = poids;
}

/********************************************************************************************************************************************************
***** ARCModifier(int iDestination, unsigned int poids) : Modifier la valeur du poids de l'arc et la valeur de destination de l'arc                 *****
*********************************************************************************************************************************************************
***** Entr�e : Un entier positif repr�sentant la nouvelle valeur du poids de l'arc ainsi qu'un entier repr�sentant la nouvelle destination de l'arc *****
***** Pr�condition : Aucune                                                                                                                         *****
***** Sortie : Aucune                                                                                                                               *****
***** Postcondition : Modifie la valeur du poids de l'arc et la destination de l'arc avec les nouvelles valeurs sp�cifi�es                          *****
********************************************************************************************************************************************************/
void CArc::ARCModifier(int iDestination, double poids)
{
	if (poids < 0) throw(CException(ValeurPoidsN�gatif));
	uiARCpoids = poids;
	iARCDestination = iDestination;
}

/*****************************************************************************************************
***** CArc& operator=(const CArc& ARCParam) : Op�rateur �gale pour la classe CArc                *****
******************************************************************************************************
***** Entr�e : ARCParam (r�f�rence constante vers un objet CArc)                                 *****
***** Pr�condition : Aucune                                                                      *****
***** Sortie : Une r�f�rence vers l'objet CArc courant                                           *****
***** Postcondition : L'objet CArc courant est assign� avec les valeurs de l'objet CArc ARCParam *****
*****************************************************************************************************/
CArc & CArc::operator=(const CArc & ARCParam)
{
	this->iARCDestination = ARCParam.iARCDestination;
	uiARCpoids = ARCParam.uiARCpoids;
	return *this;
}

/*****************************************************************************************************************************************
***** operator<<(std::ostream & stream, const CArc & ARCParam) : Surcharge de l'op�rateur de sortie (<<) pour afficher un objet CArc *****
******************************************************************************************************************************************
***** Entr�e : Un flux de sortie (stream) et une r�f�rence constante � un objet CArc (ARCParam) � afficher                           *****
***** Pr�condition : Aucune                                                                                                          *****
***** Sortie : Une r�f�rence � un flux de sortie                                                                                     *****
***** Postcondition : Affiche la valeur de destination de l'arc (iARCDestination) dans le flux de sortie en utilisant                *****
***** l'op�rateur de flux de sortie (<<). Retourne une r�f�rence au flux de sortie modifi�                                           *****
*****************************************************************************************************************************************/
std::ostream & operator<<(std::ostream & stream, const CArc & ARCParam)
{
	stream << "-->" << ARCParam.iARCDestination;
	if(ARCParam.uiARCpoids!=0) 
		stream<< ", poids : "<<ARCParam.uiARCpoids;
	return stream;
}
