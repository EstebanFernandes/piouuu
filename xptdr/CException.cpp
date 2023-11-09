#include "CException.h"

using namespace std;
/**********************************************************************
***** CException() : Constructeur par défaut, initialise un objet *****
***********************************************************************
***** Entrée : Rien                                               *****
***** Précondition : Rien                                         *****
***** Sortie : Rien                                               *****
***** Postcondition : L'exception est initialisée                 *****
**********************************************************************/
CException::CException()
{
	uiEXCvaleur = FAUX;
}

/**************************************************************************************************************
***** CException(unsigned int valeur) : Constructeur de confort qui initialise l'exception avec sa valeur *****
***************************************************************************************************************
***** Entrée : la valeur de l'exception                                                                   *****
***** Précondition : Rien                                                                                 *****
***** Sortie : Rien                                                                                       *****
***** Postcondition : L'exception est crée avec une valeur déjà assigné                                   *****
**************************************************************************************************************/
CException::CException(unsigned int valeur)
{
	uiEXCvaleur = valeur;
}

/*******************************************************************************
***** EXCModifierValeur() : Cette méthode modifie la valeur de l'exception *****
********************************************************************************
***** Entrée : Nouvelle valeur de l'exception                              *****
***** Précondition : Rien                                                  *****
***** Sortie : Rien                                                        *****
***** Postcondition : L'exception est modifiée                             *****
*******************************************************************************/
void CException::EXCModifierValeur(unsigned int value)
{
	uiEXCvaleur = value;
}

/****************************************************************************************
***** EXCLireValeur() : Cette fonction permet de consulter la valeur de l'exception *****
*****************************************************************************************
***** Entrée : Rien                                                                 *****
***** Précondition : Rien                                                           *****
***** Sortie : La valeur de l'exception                                             *****
***** Postcondition : L'exception est retournée                                     *****
****************************************************************************************/
inline unsigned int CException::EXCLireValeur()
{
	return uiEXCvaleur;
}

/*********************************************************************
***** EXCHandleException() : Gestion des exceptions              *****
**********************************************************************
***** Entrée : Aucune puisqu'elle utilise des variables globales *****
***** Précondition : Aucune                                      *****
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
		cout << "Impossible de supprimer un élément d'une liste vide";
		break;
	case ArcPartantIntrouvable:
		cout << "L'arc partant à supprimer est introuvable";
		break;
	case ArcArrivantIntrouvable:
		cout << "L'arc arrivant à supprimer est introuvable";
		break;
	case SommetExistant:
		cout << "Le sommet à ajouter existe déjà";
		break;
	case SommetSupprimerIntrouvable:
		cout << "Le sommet à supprimer est introuvable";
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
		cout << "Il est impossible d'ajouter un arc qui est déjà existant";
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

	case ValeurPoidsNégatif:
		cout << "La valeur du poids doit être positive";
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
	//	cout << "La taille (ligne ou colonne) passée en parametre n'est pas valide,";
	//	cout << "verifiee qu'elle soit superieur a 0 et au maximum egale a la taille de la matrice -1 \n ";
	//	break;
	//case DivisionImpossible:
	//	cout << "La division de la matrice par cette constante est impossible";
	//	break;
	////case DimensionIncohérente:
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
	//	cout << "La taille (ligne ou colonne) passee en parametre n'est pas valide, elle doit etre superieur à 0 \n";
	//	break;
	//case MauvaisTypeDonnees:
	//	cout << "Le type de données attendu n'est pas valide\n";
	//	break;
	//case ValeurAttenduInvalide:
	//	cout << "Le nombre de valeurs dans le fichier différent de celui attendu\n";
	//	break;
	//case FinLigneAttendue:
	//	cout << "La taille de la matrice est incoherente\n";
	//	break;
	}
}
