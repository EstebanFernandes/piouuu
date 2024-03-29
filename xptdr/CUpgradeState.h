#pragma once
#include "CState.h"
#include <string>
#include "CJeu.h"
#include"CPlayer.h"
#include"CHugoDecrypte.h"
#include"CCardUpgrade.h"
#include"InterfaceState.h"
//�tat qui g�re les am�liorations du joueur 1
class CUpgradeState : public CState, public InterfaceState
{
private:
	GameDataRef data;
	int nbOfGraph;
	int type;
	//Liste des graphes qui suivent les am�liorations du joueur
	std::vector<CGrapheUpdate>* Graphs;
	//Pointeur sur le joueur afin d'acc�der plus facilement � ces stats
	CPlayer* pointerToPlayer1;
	Weapon* pointerToWeapon;
	int levelofPlayer;
	//Liste qui g�re les am�liorations une fois que l'on arrive � la fin d'un arbre
	std::vector<std::string> listUpgradeMax;
	CGrapheUpdate* currentGraph;
	bool isFirstTime = false;

	int hasPressedKey = 0;
	//Graphique
	std::vector<CCardUpgrade> CardList;
	sf::Text title;
	//Selection
	int iCardSelection = 0;
	int tailleAvantAjout = 0;
	int nbgrapheajoute = 0;
	//Si il n'y a pas de graph pour l'am�lioration � venir on charge tous les premiers sommets des graphes possibles
	//Sinon la fonction renvoie false
	bool pointsurlesgraphs()
	{
		std::string fileName;
		switch(Graphs->size())
		{
		case 0:
			fileName = "res/data/principalweapon.csv";
			type = 0;
			break;
		case 1:
			fileName = "res/data/secondaryweapon.csv";
			type = 1;
			break;
		case 2:
			fileName = "";
			type = 2;
			break;
		}
		if (fileName == "")
			return false;
		CHugoDecrypte r(fileName);
		CGrapheUpdate t;
		t.GRAAjouterSommet(0);
		nbgrapheajoute = (int)r.returnGraphs().size();
		tailleAvantAjout = (int)Graphs->size();
		for (int i = 0; i < nbgrapheajoute; i++)
		{
			Graphs->push_back(r.returnGraphs()[i]);
			CSommetUpgrade temp = r.returnGraphs()[i].GRAObtenirListeSommet()[0];
			temp.SOMModifierNumero(i + 1);
			t.GRAAjouterSommet(temp);
			t.GRAAjouterArc(0, i + 1);
		}

		Graphs->push_back(t);
		currentGraph = (&(*Graphs)[Graphs->size()-1]);
		levelofPlayer = pointerToPlayer1->getLevel();
		currentGraph->currentVert = &currentGraph->GRAObtenirListeSommet()[0];

		int screen_Height = data->assets.sCREEN_HEIGHT;
		int screen_Width = data->assets.sCREEN_WIDTH;
		int nbofUpgrade = (int)currentGraph->currentVert->SOMLireArcPartant().size();
		for (int i = 0; i < nbofUpgrade; i++)
		{
			sf::Vector2f pos;
			int iDNextVert = (*currentGraph->currentVert).SOMLireArcPartant()[i].ARCObtenirDest();
			CSommetUpgrade nextVert = currentGraph->GRAObtenirListeSommet()[iDNextVert];
			
			CCardUpgrade card(nextVert.returnValues(), r.returnGraphs()[i].ListeType, &(data->assets));
			float ratio = 1 / (float)nbofUpgrade;
			//Distance qui n'est pas prise par les cartes
			float t = screen_Width - (card.getGlobalBounds().width * nbofUpgrade);
			while(t <= screen_Width * 0.2)
			{
				card.reduceScale();
				t = screen_Width - (card.getGlobalBounds().width * nbofUpgrade);
			}
			float spaceBetweenCard = t / (float)(nbofUpgrade + 1);
			pos.x = spaceBetweenCard + (spaceBetweenCard + card.getGlobalBounds().width) * i;
			pos.y = (screen_Height / 2.f) - (card.getGlobalBounds().height / 2.f);
			card.setPosition(pos);
			CardList.push_back(card);
		}
		return true;
	}

	void PremiereFois();
	void PasPremiereFois();

	void fillUpgrade(int nbofUpgrade);
	//M�thodes et constructeurs
	int whichKindofUpgrade() {
		int temp = levelofPlayer;
		int res = temp % 3;
		if (res == 2)
			res = 1;
		type = res;
		return res;
	}

	void CreateCard(std::vector<std::string> type)
	{
		int screen_Height = data->assets.sCREEN_HEIGHT;
		int screen_Width = data->assets.sCREEN_WIDTH;
		int nbofUpgrade = (int)currentGraph->currentVert->SOMLireArcPartant().size();
		for (int i = 0; i < nbofUpgrade; i++)
		{
			sf::Vector2f pos;
			int iDNextVert = (*currentGraph->currentVert).SOMLireArcPartant()[i].ARCObtenirDest();
			CSommetUpgrade nextVert = currentGraph->GRAObtenirListeSommet()[currentGraph->GRATrouverSommet(iDNextVert)];
			CCardUpgrade temp(nextVert.returnValues(), type, &(data->assets));
			float ratio = 1 / (float)nbofUpgrade;
			//Distance qui n'est pas prise par les cartes
			float t = screen_Width - (temp.getGlobalBounds().width * nbofUpgrade);
			while (t <= screen_Width * 0.2)
			{
				temp.reduceScale();
				t = screen_Width - (temp.getGlobalBounds().width * nbofUpgrade);
			}
			float spaceBetweenCard = t / (float)(nbofUpgrade + 1);
			pos.x = spaceBetweenCard + (spaceBetweenCard + temp.getGlobalBounds().width) * i;
			pos.y = (screen_Height / 2.f) - (temp.getGlobalBounds().height / 2.f);
			temp.setPosition(pos);
			CardList.push_back(temp);
		}
	}
	void plusStats();
	void applyStats();
	float setValue(float init, std::string modif);
	int setValue(int init, std::string modif);
	bool matchTypeWithValue(std::string type, std::string value);
public:
	CUpgradeState(GameDataRef d, CPlayer* player, std::vector<CGrapheUpdate>* pointerToPlayerGraphs);
	void STEInit(); 
	void STEHandleInput();
	void STEUpdate(float delta);
	void STEDraw(float delta);
	
};