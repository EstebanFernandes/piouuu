#include "CUpgradeState.h"

void CUpgradeState::PremiereFois()
{
	levelofPlayer = pointerToPlayer1->getLevel();
	currentVert = &currentGraph->GRAObtenirListeSommet()[0];


}

void CUpgradeState::PasPremiereFois()
{
	levelofPlayer = pointerToPlayer1->getLevel();
	//currentGraph = (&(*Graphs)[whichKindofUpgrade()]);
	currentGraph = (&(*Graphs)[0]);
	currentVert = &currentGraph->GRAObtenirListeSommet()[0];
	CreateCard(currentGraph->ListeType);
}

CUpgradeState::CUpgradeState(GameDataRef d, CCharacter* player, std::vector<CGrapheUpdate>* pointerToPlayerGraphs) : data(d)
{
	if (player != NULL)
		pointerToPlayer1 = player;
	if (pointerToPlayerGraphs != NULL)
		Graphs = pointerToPlayerGraphs;
}

void CUpgradeState::STEInit() 
{
	isFirstTime = pointsurlesgraphs();
	if (!isFirstTime)
		PasPremiereFois();
	CardList[iCardSelection].setOutlineThickNess(10.f);
}
void CUpgradeState::STEHandleInput()
{
	sf::Event event;
	while (data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
			data->window.close();
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) ) {
			//prevent from multiple key detection
			if (hasPressedKey++ == 1)
			{
				int iDNextVert = (*currentVert).SOMLireArcPartant()[iCardSelection].ARCObtenirDest();
				CSommetUpgrade nextVert = currentGraph->GRAObtenirListeSommet()[iDNextVert];
				for (int i = 0; i < CardList[iCardSelection].type.size(); i++)
				{
					pointerToPlayer1->matchTypewithValue(CardList[iCardSelection].type[i],nextVert.returnValues()[i+2]);
				}
				if (isFirstTime)
				{
					int nbTotalGraph = (int)Graphs->size();
					int indexpastoucher = iCardSelection+tailleAvantAjout;
					for (int i = tailleAvantAjout; i < nbTotalGraph; i++)
					{
						if(i!=indexpastoucher)
						{
							Graphs->erase(Graphs->begin() + i);
							i = tailleAvantAjout-1;
							nbTotalGraph--;
							if(indexpastoucher!=0)
								indexpastoucher--;
						}
					}
				}
				else {
					int iDNextVert = (*currentVert).SOMLireArcPartant()[iCardSelection].ARCObtenirDest();
					for (int i = 0; i < currentVert->SOMLireArcPartant().size(); i++)
					{
						if (currentVert->SOMLireArcPartant()[i].ARCObtenirDest() != iDNextVert)
							currentGraph->GRASupprimerArc(currentVert->SOMLireNumero(), currentVert->SOMLireArcPartant()[i].ARCObtenirDest());
					}
					currentGraph->GRASupprimerSommet(currentVert->SOMLireNumero());
				}
				data->machine.RemoveState();
			}
		}
		else if (event.type == sf::Event::KeyPressed)
		{
				int previousSelec = iCardSelection;
			if (event.key.code == sf::Keyboard::D)
			{
				iCardSelection = (iCardSelection + 1) % CardList.size();
				CardList[previousSelec].setOutlineThickNess(0.f);
				CardList[iCardSelection].setOutlineThickNess(10.f);
			}
			else if (event.key.code == sf::Keyboard::Q)
			{
				if (iCardSelection == 0) {
					iCardSelection = (int)CardList.size() - 1;
				}
				else {
					iCardSelection = (iCardSelection - 1) % CardList.size();
				}
				CardList[previousSelec].setOutlineThickNess(0.f);
				CardList[iCardSelection].setOutlineThickNess(10.f);
			}
		}
	}
}


void CUpgradeState::STEUpdate(float delta)
{

}

void CUpgradeState::STEDraw(float delta)
{
	data->window.clear(sf::Color(174, 177, 184));
	for (int i = 0; i < CardList.size(); i++)
	{
		data->window.draw(CardList[i]);
	}
	data->window.display();
}
