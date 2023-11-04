#include "CException.h"

using namespace std;
/**********************************************************************
***** CException() : Constructeur par d�faut, initialise un objet *****
***********************************************************************
***** Entr�e : Rien                                               *****
***** Pr�condition : Rien                                         *****
***** Sortie : Rien                                               *****
***** Postcondition : L'exception est initialis�e                 *****
**********************************************************************/
CException::CException()
{
	uiEXCvaleur = FAUX;
}

/**************************************************************************************************************
***** CException(unsigned int valeur) : Constructeur de confort qui initialise l'exception avec sa valeur *****
***************************************************************************************************************
***** Entr�e : la valeur de l'exception                                                                   *****
***** Pr�condition : Rien                                                                                 *****
***** Sortie : Rien                                                                                       *****
***** Postcondition : L'exception est cr�e avec une valeur d�j� assign�                                   *****
**************************************************************************************************************/
CException::CException(unsigned int valeur)
{
	uiEXCvaleur = valeur;
}

/*******************************************************************************
***** EXCModifierValeur() : Cette m�thode modifie la valeur de l'exception *****
********************************************************************************
***** Entr�e : Nouvelle valeur de l'exception                              *****
***** Pr�condition : Rien                                                  *****
***** Sortie : Rien                                                        *****
***** Postcondition : L'exception est modifi�e                             *****
*******************************************************************************/
void CException::EXCModifierValeur(unsigned int value)
{
	uiEXCvaleur = value;
}

/****************************************************************************************
***** EXCLireValeur() : Cette fonction permet de consulter la valeur de l'exception *****
*****************************************************************************************
***** Entr�e : Rien                                                                 *****
***** Pr�condition : Rien                                                           *****
***** Sortie : La valeur de l'exception                                             *****
***** Postcondition : L'exception est retourn�e                                     *****
****************************************************************************************/
inline unsigned int CException::EXCLireValeur()
{
	return uiEXCvaleur;
}

/*********************************************************************
***** EXCHandleException() : Gestion des exceptions              *****
**********************************************************************
***** Entr�e : Aucune puisqu'elle utilise des variables globales *****
***** Pr�condition : Aucune                                      *****
***** Sortie : Aucune (elle affiche seulement un message)        *****
***** Postcondition : Aucune                                     *****
*********************************************************************/
void CException::EXCHandleException()
{
	switch (uiEXCvaleur)
	{
	case PositionIncoherente:
		cout << "La position donnee n'est pas valide";
		break;
	case SupprimerNulle:
		cout << "Impossible de supprimer un �l�ment d'une liste vide";
		break;
	case ArcPartantIntrouvable:
		cout << "L'arc partant � supprimer est introuvable";
		break;
	case ArcArrivantIntrouvable:
		cout << "L'arc arrivant � supprimer est introuvable";
		break;
	case SommetExistant:
		cout << "Le sommet � ajouter existe d�j�";
		break;
	case SommetSupprimerIntrouvable:
		cout << "Le sommet � supprimer est introuvable";
		break;
	case SommetDestinationIntrouvable:
		cout << "Le sommet de destination est introuvable";
		break;
	case SommetSourceIntrouvable:
		cout << "Le sommet source est introuvable";
		break;
	case LectureSommet:
		cout << "Le parser n'a pas pu correctement lire le nombre de sommets";
		break;
	case LectureArc:
		cout << "Le parser n'a pas pu correctement lire le nombre d'arcs";
		break;
	case LectureValeurSommet:
		cout << "Le parser a detecte une erreur dans\n la lecture des valeurs du sommets";
		break;
	case LectureValeurArc:
		cout << "Le parser a detecte une erreur dans\n la lecture des valeurs des arcs";
		break;
	case ArcExistant:
		cout << "Il est impossible d'ajouter un arc qui est d�j� existant";
		break;
	case NombreDArgumentInvalide:
		cout << "Nombre d'argument invalide\n";
		break;

	case NomFichierInexistant:
		cout << "Le nom du fichier n'est pas defini\n";
		break;
	case LectureOrientation:
		cout << "L'orientation du graphe n'a pas pu etre lu, les seules reponses acceptees sont oui ou non \n";
		break;

	case ValeurPoidsN�gatif:
		cout << "La valeur du poids doit �tre positive";
		break;
	case LectureFichierImpossible:
		cout << "La lecture du fichier est impossible\n";
		break;

	case ErreurTypeGraphe:
			cout << "Le graphe doit etre de type non oriente\n";
			break;

	//case IndexHorsTableau:
	//	cout << "Index hors tableau \n";
	//	break;
	//case TailleInvalide:
	//	cout << "La taille (ligne ou colonne) pass�e en parametre n'est pas valide,";
	//	cout << "verifiee qu'elle soit superieur a 0 et au maximum egale a la taille de la matrice -1 \n ";
	//	break;
	//case DivisionImpossible:
	//	cout << "La division de la matrice par cette constante est impossible";
	//	break;
	////case DimensionIncoh�rente:
	//	cout << "Les dimensions des deux matrices sont incoherentes\n";
	//	break;
	//case FichierIntrouvable:
	//	cout << "Le chemin du fichier est introuvable\n";
	//	break;
	//case LectureFichierImpossible:
	//	cout << "La lecture du fichier est impossible\n";
	//	break;
	//case MatriceNul:
	//	cout << "La matrice passee en parametre est nulle\n";
	//	break;
	//case TailleInvalideConstruct:
	//	cout << "La taille (ligne ou colonne) passee en parametre n'est pas valide, elle doit etre superieur � 0 \n";
	//	break;
	//case MauvaisTypeDonnees:
	//	cout << "Le type de donn�es attendu n'est pas valide\n";
	//	break;
	//case ValeurAttenduInvalide:
	//	cout << "Le nombre de valeurs dans le fichier diff�rent de celui attendu\n";
	//	break;
	//case FinLigneAttendue:
	//	cout << "La taille de la matrice est incoherente\n";
	//	break;
	}
}
