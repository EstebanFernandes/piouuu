#include "CUpgradeState.h"

void CUpgradeState::PremiereFois()
{
	levelofPlayer = pointerToPlayer1->getLevel();
	currentGraph->currentVert = &currentGraph->GRAObtenirListeSommet()[0];
}

void CUpgradeState::PasPremiereFois()
{
 	levelofPlayer = pointerToPlayer1->getLevel();
	//nbOfGraph = whichKindofUpgrade();
	//currentGraph = (&(*Graphs)[nbOfGraph]); à remttre quand ce sera fix
	nbOfGraph = 0;
	currentGraph = (&(*Graphs)[nbOfGraph]);
	//currentGraph->currentVert = &currentGraph->GRAObtenirListeSommet()[0];
	if (currentGraph->endOfGraph)
		plusStats();
	CreateCard(currentGraph->ListeType);
}

void CUpgradeState::fillUpgrade(int nbofUpgrade)
{
	std::vector<std::string> typeString = { "maxHealthPoint",
										"moveSpeed","damagePerBullet",
											"attackSpeed","bulletSpeed",};
	do {
		int randInt = (rand() % typeString.size());
		if (std::find(listUpgradeMax.begin(), listUpgradeMax.end(), typeString[randInt]) != listUpgradeMax.end())
		{}
		else {
			listUpgradeMax.push_back(typeString[randInt]);
		}
	} while (listUpgradeMax.size() != nbofUpgrade);
}

//Si on a plus d'améliorations possible
void CUpgradeState::plusStats()
{
	int screen_Height = data->assets.sCREEN_HEIGHT;
	int screen_Width = data->assets.sCREEN_WIDTH;
	int nbofUpgrade = 3;
	fillUpgrade(nbofUpgrade);
	for (int i = 0; i < nbofUpgrade; i++)
	{
		sf::Vector2f pos;
		CCardUpgrade temp("*1.1", listUpgradeMax[i], &(data->assets));
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
	std::string temp = "Passage au niveau " + std::to_string(this->levelofPlayer);
	title.setString(temp);
	title.setFont(data->assets.GetFont("Lato"));
	title.setCharacterSize(40);
	title.setPosition(sf::Vector2f((data->assets.sCREEN_WIDTH - title.getGlobalBounds().width) / 2, (data->assets.sCREEN_HEIGHT * 0.1f - title.getGlobalBounds().height) / 2));
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
				for (int i = 0; i < CardList[iCardSelection].type.size(); i++)
				{
					pointerToPlayer1->matchTypewithValue(CardList[iCardSelection].type[i], CardList[iCardSelection].Upgrade[i]);
				}
				if (isFirstTime)
				{
				int iDNextVert = (*(currentGraph->currentVert)).SOMLireArcPartant()[iCardSelection].ARCObtenirDest();
				CSommetUpgrade nextVert = currentGraph->GRAObtenirListeSommet()[currentGraph->GRATrouverSommet(iDNextVert)];
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
					currentGraph = (&(*Graphs)[indexpastoucher]);
					currentGraph->currentVert = &currentGraph->GRAObtenirListeSommet()[0];
				}
				else if(currentGraph->endOfGraph != true){
					int iDNextVert = (*(currentGraph->currentVert)).SOMLireArcPartant()[iCardSelection].ARCObtenirDest();
					CSommetUpgrade nextVert = currentGraph->GRAObtenirListeSommet()[currentGraph->GRATrouverSommet(iDNextVert)];
					currentGraph = (&(*Graphs)[nbOfGraph]);
					for (int i = 0; i < currentGraph->currentVert->SOMLireArcPartant().size(); i++)
					{
						if (currentGraph->currentVert->SOMLireArcPartant()[i].ARCObtenirDest() != iDNextVert)
							currentGraph->supprimerSommetetDescendences(currentGraph->currentVert->SOMLireArcPartant()[i].ARCObtenirDest());
					}

					currentGraph->GRASupprimerSommet(currentGraph->currentVert->SOMLireNumero());
					currentGraph->currentVert = &(currentGraph->GRAObtenirListeSommet()[currentGraph->GRATrouverSommet(iDNextVert)]);
			if (currentGraph->currentVert->SOMTailleListeArc(Partant)==0)
				currentGraph->endOfGraph = true;
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
			}
			else if (event.key.code == sf::Keyboard::Q)
			{
				if (iCardSelection == 0) {
					iCardSelection = (int)CardList.size() - 1;
				}
				else {
					iCardSelection = (iCardSelection - 1) % CardList.size();
				}
			}
				CardList[previousSelec].setOutlineThickNess(0.f);
				CardList[iCardSelection].setOutlineThickNess(10.f);
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
	data->window.draw(title);
	data->window.display();
}
