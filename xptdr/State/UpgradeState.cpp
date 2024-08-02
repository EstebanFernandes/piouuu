#include "UpgradeState.h"

void StateNS::UpgradeState::fillUpgrade(upgradeForOnePlayer& player, int nbofUpgrade)
{
	std::vector<std::string> typeString = { "maxHealthPoint",
										"moveSpeed","damagePerBullet",
											"attackSpeed","bulletSpeed","dashDamage" };
	do {
		int randInt = (rand() % typeString.size());
		if (std::find(player.listUpgradeMax.begin(), player.listUpgradeMax.end(), typeString[randInt]) != player.listUpgradeMax.end())
		{}
		else {
			player.listUpgradeMax.push_back(typeString[randInt]);
		}
	} while (player.listUpgradeMax.size() != nbofUpgrade);
}

void StateNS::UpgradeState::createCardTexture(upgradeForOnePlayer& player, int nbOfUpgrade)
{
	sf::Vector2f sizeOfCardWithoutThick = sf::Vector2f(255, 365.f);
	sf::Vector2f pos;
	pos.y =  10.f;
	GrapheUpdate graph = US->currentGraph(*player.playerComp);
	std::vector<CardUpgrade>tempCardList;
	for (int i = 0; i < nbOfUpgrade; i++)
	{
		SommetUpgrade& baseSommet = graph.GRAObtenirListeSommet()[player.indexesUpgrade[i]];
		if (!player.isFirstTime)
		{
			CardUpgrade temp(baseSommet.returnValues(), graph.ListeType, &(data->assets), 0);

			temp.setSize(sizeOfCardWithoutThick);
			pos.x = i * sizeOfCardWithoutThick.x;
			temp.setPosition(pos);
			tempCardList.push_back(temp);
		}
		else
		{

			CardUpgrade temp(baseSommet.returnValues(), US->graphs[stoi(graph.Name)][player.indexesUpgrade[i]-1].ListeType, &(data->assets), 0);
			temp.setSize(sizeOfCardWithoutThick);
			pos.x = i * sizeOfCardWithoutThick.x;
			temp.setPosition(pos);
			tempCardList.push_back(temp);
		}
		tempCardList[i].setFontColor(sf::Color(0, 0, 0, 255));
		tempCardList[i].setBackColor(sf::Color(255, 255, 255, 255));
	}
	InterfaceState::applyCardUpgrademaxMinCharSize(tempCardList);
	for (int i = 0; i < tempCardList.size(); ++i)
	{
		tempCardList[i].resizeTexts();
	}
	sf::RenderTexture renderTexture;
	renderTexture.create((int)(sizeOfCard.x * nbOfUpgrade+1), (int)(sizeOfCard.y) );
	renderTexture.clear(sf::Color::White);
	for (int i = 0; i < nbOfUpgrade; i++)
	{
		renderTexture.draw(tempCardList[i]);
	}
	renderTexture.display();
	player.cardTexture = renderTexture.getTexture();
}

//Si on a plus d'améliorations possible
void StateNS::UpgradeState::plusStats(upgradeForOnePlayer& player)
{
	//float screen_Height = player.bord.height;
	//float screen_Width = player.bord.width;
	//int nbofUpgrade = 6;
	//fillUpgrade(player,nbofUpgrade);
	//for (int i = 0; i < nbofUpgrade; i++)
	//{
	//	sf::Vector2f pos;
	//	CardUpgrade temp("*1.1", player.listUpgradeMax[i], &(data->assets));
	//	float ratio = 1 / (float)nbofUpgrade;
	//	//Distance qui n'est pas prise par les cartes
	//	float t = screen_Width - (temp.getGlobalBounds().width * nbofUpgrade);
	//	while (t <= screen_Width * 0.2)
	//	{
	//		temp.reduceScale();
	//		t = screen_Width - (temp.getGlobalBounds().width * nbofUpgrade);
	//	}
	//	float spaceBetweenCard = t / (float)(nbofUpgrade + 1);
	//	pos.x =player.bord.left+ spaceBetweenCard + (spaceBetweenCard + temp.getGlobalBounds().width) * i;
	//	pos.y = (screen_Height / 2.f) - (temp.getGlobalBounds().height / 2.f);
	//	temp.setPosition(pos);
	//	player.CardList.push_back(temp);
	//}
}

void StateNS::UpgradeState::applyStats(upgradeForOnePlayer& player)
{
	if (player.isFirstTime)
	{
		//Jcrois ca fonctionne pas trop
		int indexI = (player.playerComp->pos.x);
		int index = player.indexesUpgrade[player.iCardSelection]-1;
		std::vector<std::string>& types = US->graphs.at(indexI).at(index).ListeType;
		std::vector<std::string>& values = US->currentGraph(*player.playerComp).GRAObtenirListeSommet()[player.indexesUpgrade[player.iCardSelection]].values;
		for (int i = 0; i < types.size(); i++)
		{//ça fonctionne surement pas
			matchTypeWithValue(player, types[i], values[i]);
		}
	}
	else {
		std::vector<std::string>& types = US->currentGraph(*player.playerComp).ListeType;
		std::vector<std::string>& values = US->currentGraph(*player.playerComp).GRAObtenirListeSommet() [player.indexesUpgrade[player.iCardSelection]] .values;
		for (int i = 0; i <types.size(); i++)
		{//ça fonctionne surement pas
			matchTypeWithValue(player, US->currentGraph(*player.playerComp).ListeType[i], values[i]);
		}
	}
}

float StateNS::UpgradeState::setValue(float init, std::string modif)
{
	switch (modif[0])
	{
	case '*':
		init = init * std::stof(modif.substr(1));
		break;
	case '+':
		init = init + std::stof(modif.substr(1));
		break;
	case '-':
		init = init - std::stof(modif.substr(1));
		break;
	default:
		init = std::stof(modif);
		break;
	}
	return init;
}

int StateNS::UpgradeState::setValue(int init, std::string modif)
{
	switch (modif[0])
	{
	case '*':
		init = init * std::stoi(modif.substr(1));
		break;
	case '+':
		init = init + std::stoi(modif.substr(1));
		break;
	case '-':
		init = init - std::stoi(modif.substr(1));
		break;
	default:
		init = std::stoi(modif);
		break;
	}
	return init;
}



StateNS::UpgradeState::UpgradeState(GameDataRef d, Player* player, upgradeStock* pointerToUpgradeStocks, State* prev)
	: data(d),pointertoGameState(prev)
{
	sf::FloatRect bord(0.f, 0.f, (float)Engine::SCREEN_WIDTH, (float)Engine::SCREEN_HEIGHT);
	if (player != NULL)
	{
		upgradeForOnePlayer temp;
		temp.bord = bord;
		players.push_back(temp);
		players.front().pointerToPlayer = player;
	}
	if (pointerToUpgradeStocks != NULL)
		US = pointerToUpgradeStocks;
}

StateNS::UpgradeState::UpgradeState(GameDataRef d, std::list<Player>* players, upgradeStock* pointerToUpgradeStocks, State* prev)
	:data(d),pointertoGameState(prev)
{
	sf::FloatRect bord(0.f,0.f, (float)Engine::SCREEN_WIDTH, (float)Engine::SCREEN_HEIGHT);
	if (players->size()==2)
	{
		bord.width = bord.width/2.f;
	}
	for (auto player = (*players).begin(); player != (*players).end(); player++)
	{
		upgradeForOnePlayer temp;
		temp.pointerToPlayer = &(*player);
		temp.bord = bord;
		bord.left += bord.width;
		this->players.push_back(temp);
	}
	if (pointerToUpgradeStocks != NULL)
		US = pointerToUpgradeStocks;
}

void StateNS::UpgradeState::STEInit()
{
	updateTime();
	for (int i = 0; i < players.size(); i++)
	{
		players[i].levelOfPlayer = players[i].pointerToPlayer->getLevel();
		if (players[i].levelOfPlayer <= 2)
			players[i].isFirstTime = true;
		else
			players[i].isFirstTime = false;
		players[i].type = whichKindofUpgrade(players[i]);
		players[i].playerComp = &(players[i].pointerToPlayer->curUpgrade[players[i].type]);
		CreateCard(players[i]);
		std::string typestring;
		switch (players[i].type)
		{
		case 0:
			typestring = "Amélioration de l'arme principale ";
			players[i].pointerToWeaponPlayer = players[i].pointerToPlayer->getMainWeapon();
			break;
		case 1:
			typestring = "Amélioration de l'arme secondaire ";
			players[i].pointerToWeaponPlayer = players[i].pointerToPlayer->getSecondaryWeapon();
			break;
		case 2:
			typestring = "Amélioration diverse ";
			break;
		}
		int titleCharSize = 40, subTitleCharSize = 35;
		if (players.size() == 2)
		{
			titleCharSize -= 5;
			subTitleCharSize -= 5;
		}
		if (Engine::SCREEN_WIDTH<=1000)
		{
			titleCharSize -= 5;
			subTitleCharSize -= 5;
		}

		std::string subtitle = "Passage au niveau " + std::to_string(players[i].levelOfPlayer) ;
		players[i].subtitle.setString(subtitle);
		players[i].subtitle.setFont(data->assets.GetFont("Nouvelle"));
		players[i].subtitle.setCharacterSize(subTitleCharSize);
		utilities::centerObject(players[i].subtitle);
		players[i].subtitle.setPosition(
			players[i].bord.left + (players[i].bord.width / 2.f),
			players[i].bord.height * 0.22f);
		players[i].title.setString(typestring);
		players[i].title.setFont(data->assets.GetFont("Nouvelle"));
		players[i].title.setCharacterSize(titleCharSize);
		utilities::centerObject(players[i].title);
		players[i].title.setPosition(
			players[i].bord.left + (players[i].bord.width / 2.f),
			players[i].bord.height * 0.24f);
		players[i].timeOffset = time;
	}
	if (!blurShader.loadFromFile( "shaders/blurFrag.frag",sf::Shader::Fragment))
		std::cout << "bof";
	blurShader.setUniform("textureSampler", sf::Shader::CurrentTexture);
	blurShader.setUniform("u_resolution", sf::Glsl::Vec2(getEcranBound()));

	if (!fadeShader.loadFromFile("shaders/fadeFrag.frag",sf::Shader::Fragment))
		std::cout << "bof";
	fadeShader.setUniform("textureSampler", sf::Shader::CurrentTexture);
	
	if (players.size() == 2)
	{
		frontiere.setSize(sf::Vector2f(8.f, (float)Engine::SCREEN_HEIGHT));
		frontiere.setOrigin(4.f, 0.f);
		frontiere.setPosition((float)Engine::SCREEN_WIDTH / 2.f, 0.f);
	}
}
void StateNS::UpgradeState::STEHandleInput(sf::Event& event)
{
	if(state!=0)
	{
		if (sf::Event::Closed == event.type)
			data->window.close();
		for (int i = 0; i < players.size(); i++)
		{
			handleInput(players[i], event);
		}
	}
}


void StateNS::UpgradeState::STEUpdate(float delta)
{

		bool updateCard = true;
		for (int i = 0; i < players.size(); i++)
		{
			updateCard = updateCards(players[i]);
			if(updateCard&&state==0)
				updateChosenCard(players[i], 0);
		}
		if (updateCard)
			state++;
		updateTime();

		fadeShader.setUniform("time", time);
	bool finalBool = false;
	for (int i = 0; i < players.size(); i++)
	{
		finalBool = (players[i].cfini) ? true : false;
	}
	if (finalBool&&updateCard)
		data->machine.RemoveState();
}

void StateNS::UpgradeState::STEDraw(float delta)
{
	sf::RenderTexture back;
	back.create(Engine::SCREEN_WIDTH, Engine::SCREEN_HEIGHT);
	back.clear();
	pointertoGameState->drawOnTarget(back,delta);
	back.display();
	fond = sf::Sprite(back.getTexture());
	data->window.draw(fond, &blurShader);
	if(players.size()==2)
		data->window.draw(frontiere);
	for(int i=0;i<players.size();i++)
	{
		data->window.draw(players[i].subtitle);
		data->window.draw(players[i].title);
		switch(state)
		{
		case 0:
			for (int j = 0; j < players[i].CardList.size(); j++)
			{
				players[i].CardList[j].draw(data->window);
			}
			break;
		case 2:
			for (int j = 0; j < players[i].CardList.size(); j++)
			{
				if (j!=players[i].iCardSelection)
				{
					data->window.draw(*players[i].CardList[j].cardBack, &fadeShader);
					data->window.draw(*players[i].CardList[j].cardFace, &fadeShader);
				}
			}
			players[i].CardList[players[i].iCardSelection].draw(data->window);
			break;
			default:
				for (int j = 0; j < players[i].CardList.size(); j++)
					players[i].CardList[j].draw(data->window);
				players[i].CardList[players[i].iCardSelection].draw(data->window);
				break;
		}
	}
}

bool StateNS::UpgradeState::matchTypeWithValue(upgradeForOnePlayer& player, std::string type, std::string value)
{
	std::vector<std::string> typeString = { "maxXp","healthPoint","maxHealthPoint",
	"moveSpeed","damagePerBullet","attackSpeed","bulletSpeed",
		"misc","dashDistance","dashDamage","isDashInvicible",
	"dotCD","dotTimer","dotDamage","factor","penetration"};
	int pos = (int)(std::find(typeString.begin(), typeString.end(), type) - typeString.begin());
	if (type == "dotDamage")
		pos = 13;
	if (pos >= typeString.size()) {
		return false;
	}
	else {
		if (value != "")
		{
			switch (pos)
			{
			case 0: //Max XP
				player.pointerToPlayer->setMaxXp(setValue(player.pointerToPlayer->getMaxXp(), value));
				break;
			case 1:  //Health Point
				player.pointerToPlayer->setLifePoint(setValue(player.pointerToPlayer->getLifePoint(), value));
			case 2: // Max HealthPoint
				player.pointerToPlayer->setMaxXp((int)setValue(player.pointerToPlayer->getMaxHealth(), value));
				break;
			case 3: //move Speed
				player.pointerToPlayer->setMoveSpeed(setValue(player.pointerToPlayer->getMoveSpeed(), value));
				break;
			case 4: //DamagePerBullet
				player.pointerToWeaponPlayer->getWeaponStats().bulletDamage = setValue(player.pointerToWeaponPlayer->getWeaponStats().bulletDamage, value);
				break;
			case 5: //attack speed
				player.pointerToWeaponPlayer->getWeaponStats().attackSpeed = setValue(player.pointerToWeaponPlayer->getWeaponStats().attackSpeed, value);
				break;
			case 6: // bullet speed
				player.pointerToWeaponPlayer->getWeaponStats().bulletSpeed = setValue(player.pointerToWeaponPlayer->getWeaponStats().bulletSpeed, value);
				break;
			case 7: //misc
					player.pointerToPlayer->traitermisc(value, player.type);
				break;
			case 8: //dash distance
				player.pointerToPlayer->setDashDistance(setValue(player.pointerToPlayer->getDashDistance(), value));
				break;
			
			case 9: // dash damage
				player.pointerToPlayer->setDashDamage(setValue(player.pointerToPlayer->getDashDamage(), value));
				break;
			case 10: //isDashInvicible
				bool temp;
				if (value == "true" || value == "1")
				{
					temp = true;
				}
				else if (value == "false" || value == "0")
				{
					temp = false;
				}
				else
					break;
				player.pointerToPlayer->setIsDashInvicible(temp);
				break;
			case 11: //dotCD
				player.pointerToWeaponPlayer->getWeaponStats().dotCD = setValue(player.pointerToWeaponPlayer->getWeaponStats().dotCD, value);
				break;
			case 12: //dotTimer
				player.pointerToWeaponPlayer->getWeaponStats().dotTimer = setValue(player.pointerToWeaponPlayer->getWeaponStats().dotTimer, value);
				break;
			case 13: // dotDamage
				player.pointerToWeaponPlayer->getWeaponStats().dotDamage = setValue(player.pointerToWeaponPlayer->getWeaponStats().dotDamage, value);
				break;
			case 14: //Factor(j'attends le merge avec mathéo)
				std::cout << "on augmente le facteur (ppour la glace notamment)";
				break;
			case 15: //Penetration
				player.pointerToWeaponPlayer->getWeaponStats().penetration = setValue((int)player.pointerToWeaponPlayer->getWeaponStats().penetration, value);
				break;
			}
		}
		return true;
	}
	return true;
}

void StateNS::UpgradeState::handleInput(upgradeForOnePlayer& player, sf::Event& event)
{
	if (sf::Keyboard::isKeyPressed(inputOfPlayers[player.pointerToPlayer->numero - 1].button1)&&player.cfini==false) {
		//prevent from multiple key detection
		if (player.hasPressedKey++ == 1)
		{
			state = 2;
			player.timeOffset = time;
			applyStats(player);
			if(player.isFirstTime)
				US->avancer(*player.playerComp, player.indexesUpgrade[player.iCardSelection]-1);
			else
				US->avancer(*player.playerComp, player.indexesUpgrade[player.iCardSelection]);
			player.pointerToPlayer->setBoolLevelUp(false);
			player.pointerToPlayer->wantToLevelUp = false;
				player.pointerToPlayer->updateXpBar();
			player.cfini = true;
			player.hasPressedKey = 0;
		}
	}
	else if (sf::Keyboard::isKeyPressed(inputOfPlayers[player.pointerToPlayer->numero - 1].button2) && player.cfini == true) {
		//prevent from multiple key detection
		if (player.hasPressedKey++ == 1)
		{
			player.cfini = false;
			player.hasPressedKey = 0;
		}
	}
	else if (event.type == sf::Event::KeyPressed && player.cfini == false)
	{
		int previousSelec = player.iCardSelection;
		if (event.key.code == inputOfPlayers[player.pointerToPlayer->numero - 1].moveRight)
		{
			player.iCardSelection = (player.iCardSelection + 1) % player.CardList.size();
		}
		else if (event.key.code == inputOfPlayers[player.pointerToPlayer->numero - 1].moveLeft)
		{
			if (player.iCardSelection == 0) {
				player.iCardSelection = (int)player.CardList.size() - 1;
			}
			else {
				player.iCardSelection = (player.iCardSelection - 1) % player.CardList.size();
			}
		}
		if (previousSelec != player.iCardSelection)
			updateChosenCard(player,previousSelec);
	}
}

bool StateNS::UpgradeState::updateCards(upgradeForOnePlayer& player)
{
	if (state == 0)//Intro 
	{
		bool isInPlace = true;
			float nbOff = time - player.timeOffset;
		for (int i = 0; i < player.CardList.size(); i++)
		{
			if ( nbOff/ 0.5f >= i&&player.CardList[i].cardFace->getPosition().y >= player.CardList[i].finalPos.y)
			{
				player.CardList[i].move(0.f, -speedCard);
				isInPlace=false;
			}
			else if(player.CardList[i].cardFace->getPosition().y >= player.CardList[i].finalPos.y)
				isInPlace = false;
				float distanceParcourue = Engine::SCREEN_HEIGHT-player.CardList[i].cardFace->getPosition().y;
				float perc = distanceParcourue / (Engine::SCREEN_HEIGHT - player.CardList[i].finalPos.y);
				player.CardList[i].degree = 180.f * (1.f - perc);
				player.CardList[i].spin(player.CardList[i].degree);
		}
		return isInPlace;
	}
	else if (player.cfini) //Si le joueur a validé le choix
	{
		//Ici on va 
		bool hasLeave = true;
			float cardHeight = (players.size() == 2) ? sizeOfCard.y*0.8f : sizeOfCard.y;
			if (player.CardList[player.iCardSelection].cardFace->getPosition().y+(cardHeight* player.CardList[player.iCardSelection].getScale().x) >= 0.f)
			{
				float duration = time - player.timeOffset;
				if(duration>=0.5f)
				{
					if (player.CardList[player.iCardSelection].degree != 0.f)
					{
						player.CardList[player.iCardSelection].spin(0.f);
						player.CardList[player.iCardSelection].degree = 0.f;
					}
					player.CardList[player.iCardSelection].move(0.f, -speedCard);
	
				}
				else {
					player.CardList[player.iCardSelection].move( 0.f, 0.02f);
					player.CardList[player.iCardSelection].setScale(player.CardList[player.iCardSelection].getScale().x + 0.002f);
					// Calculer le degré de rotation en fonction du temps écoulé
					float rotationSpeed = 1440.0f; // Vitesse de rotation (degrés par seconde)
					float degree = rotationSpeed * duration; // Rotation basée sur la durée
					if (degree / 360.f >= (float)player.nbDeTours-0.1 &&
						degree / 360.f <= (float)player.nbDeTours)
					{
						player.weStop = true;
					}

					// Limiter la rotation entre 0 et 360 degrés
					degree = fmod(degree, 360.0f);
					if (player.weStop && degree > 0.f && degree < 320.f)
					{//C'est qu'on a dépasse le n Tours
						player.CardList[player.iCardSelection].spin(0);
						player.CardList[player.iCardSelection].degree = 0;
					}
					else
					{
						player.CardList[player.iCardSelection].spin(degree);
						player.CardList[player.iCardSelection].degree = degree;
					}
				}
				float perc = duration / 1.f;
				perc = (perc > 1.f) ? 1.f : perc;
				fadeShader.setUniform("uAlphaChance", perc);
				hasLeave = false;


			}
			else {
				std::cout << player.CardList[player.iCardSelection].cardFace->getPosition().y << std::endl;
			}
		return hasLeave;
	}
	else { //Je pense qu'on fait bouger celui qui est sélectionner
		// Mouvement organique
		float amplitude = 10.f; // Amplitude de l'oscillation
		float speed = 2.f; // Vitesse de l'oscillation
		float offsetX = amplitude * sin(time * speed);
		float offsetY = amplitude * cos(time * speed);

		player.CardList[player.iCardSelection].setPosition(player.CardList[player.iCardSelection].finalPos + sf::Vector2f(offsetX, offsetY));
		return false;
	}
}

void StateNS::UpgradeState::updateState()
{
	bool updateCard = true;
	for (int i = 0; i < players.size(); i++)
		updateCard = updateCards(players[i]);
	if (updateCard)
		state++;
}

void StateNS::UpgradeState::updateChosenCard(upgradeForOnePlayer& player, int previousSelec)
{
	player.CardList[previousSelec].spinVertically(0.f);
	player.CardList[previousSelec].setScale(1.f);
	player.CardList[previousSelec].move(0.f, 30.f);
	player.CardList[player.iCardSelection].spinVertically(345.f);
	player.CardList[player.iCardSelection].setScale(1.2f);
	player.CardList[player.iCardSelection].move(0.f, -30.f);
}
