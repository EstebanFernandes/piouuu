#include "CUpgradeState.h"




void CUpgradeState::fillUpgrade(upgradeForOnePlayer& player, int nbofUpgrade)
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

//Si on a plus d'améliorations possible
void CUpgradeState::plusStats(upgradeForOnePlayer& player)
{
	float screen_Height = player.bord.height;
	float screen_Width = player.bord.width;
	int nbofUpgrade = 6;
	fillUpgrade(player,nbofUpgrade);
	for (int i = 0; i < nbofUpgrade; i++)
	{
		sf::Vector2f pos;
		CCardUpgrade temp("*1.1", player.listUpgradeMax[i], &(data->assets));
		float ratio = 1 / (float)nbofUpgrade;
		//Distance qui n'est pas prise par les cartes
		float t = screen_Width - (temp.getGlobalBounds().width * nbofUpgrade);
		while (t <= screen_Width * 0.2)
		{
			temp.reduceScale();
			t = screen_Width - (temp.getGlobalBounds().width * nbofUpgrade);
		}
		float spaceBetweenCard = t / (float)(nbofUpgrade + 1);
		pos.x =player.bord.left+ spaceBetweenCard + (spaceBetweenCard + temp.getGlobalBounds().width) * i;
		pos.y = (screen_Height / 2.f) - (temp.getGlobalBounds().height / 2.f);
		temp.setPosition(pos);
		player.CardList.push_back(temp);
	}
}

void CUpgradeState::applyStats(upgradeForOnePlayer& player)
{
	for (int i = 0; i < player.CardList[player.iCardSelection].type.size(); i++)
	{
		matchTypeWithValue(player,player.CardList[player.iCardSelection].type[i], player.CardList[player.iCardSelection].Upgrade[i]);
	}
}

float CUpgradeState::setValue(float init, std::string modif)
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

int CUpgradeState::setValue(int init, std::string modif)
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


CUpgradeState::CUpgradeState(GameDataRef d, CPlayer* player, upgradeStock* pointerToUpgradeStocks, CState* prev)
	: data(d),pointertoGameState(prev)
{
	sf::FloatRect bord(0.f, 0.f, (float)d->assets.sCREEN_WIDTH, (float)d->assets.sCREEN_HEIGHT);
	if (player != NULL)
	{
		upgradeForOnePlayer temp;
		temp.pointerToPlayer = player;
		temp.bord = bord;
		players.push_back(temp);
	}
	if (pointerToUpgradeStocks != NULL)
		US = pointerToUpgradeStocks;
}

CUpgradeState::CUpgradeState(GameDataRef d, std::list<CPlayer>* players, upgradeStock* pointerToUpgradeStocks, CState* prev)
	:data(d),pointertoGameState(prev)
{
	sf::FloatRect bord(0.f,0.f, (float)d->assets.sCREEN_WIDTH, (float)d->assets.sCREEN_HEIGHT);
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

void CUpgradeState::STEInit() 
{
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
			typestring = "\nAmélioration de l'arme principale ";
			players[i].pointerToWeaponPlayer = players[i].pointerToPlayer->getMainWeapon();
			break;
		case 1:
			typestring = "\nAmélioration de l'arme secondaire ";
			players[i].pointerToWeaponPlayer = players[i].pointerToPlayer->getSecondaryWeapon();
			break;
		case 2:
			typestring = "\nAmélioration diverse ";
			break;
		}
		players[i].CardList[players[i].iCardSelection].setOutlineThickNess(10.f);
		applyCardUpgrademaxMinCharSize(players[i].CardList);
		for (int j = 0; j < players[i].CardList.size(); j++)
		{
			players[i].CardList[j].resizeTexts();
		}
		std::string temp = "Passage au niveau " + std::to_string(players[i].levelOfPlayer) + typestring;
		players[i].title.setString(temp);
		players[i].title.setFont(data->assets.GetFont("Nouvelle"));
		players[i].title.setCharacterSize(20);
		players[i].title.setPosition(sf::Vector2f(players[i].bord.left+((players[i].bord.width - players[i].title.getGlobalBounds().width) / 2.f), (players[i].bord.height * 0.1f - players[i].title.getGlobalBounds().height) / 2.f));
		}
	if (!blurShader.loadFromFile("shaders/vertexbandw.vert", "shaders/blurFrag.frag"))
		std::cout << "bof";
	blurShader.setUniform("texture", sf::Shader::CurrentTexture);
	blurShader.setUniform("u_resolution", sf::Glsl::Vec2((float)data->assets.sCREEN_WIDTH,(float)data->assets.sCREEN_HEIGHT));
	if (players.size() == 2)
	{
		frontiere.setSize(sf::Vector2f(10.f, (float)data->assets.sCREEN_HEIGHT));
		frontiere.setOrigin(5.f, 0.f);
		frontiere.setPosition((float)data->assets.sCREEN_WIDTH / 2.f, 0.f);
	}
}
void CUpgradeState::STEHandleInput()
{
	sf::Event event;
	while (data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
			data->window.close();
		for (int i = 0; i < players.size(); i++)
		{
			handleInput(players[i], event);
		}
	}
}


void CUpgradeState::STEUpdate(float delta)
{
	bool finalBool = false;
	for (int i = 0; i < players.size(); i++)
	{
		finalBool = (players[i].cfini) ? true : false;
	}
	if (finalBool)
		data->machine.RemoveState();
}

void CUpgradeState::STEDraw(float delta)
{
	sf::RenderTexture back;
	back.create(data->assets.sCREEN_WIDTH, data->assets.sCREEN_HEIGHT);
	back.clear();
	blurShader.setUniform("texture", sf::Shader::CurrentTexture);
	pointertoGameState->drawOnTarget(back,delta);
	back.display();
	fond = sf::Sprite(back.getTexture());
	data->window.draw(fond, &blurShader);
	if(players.size()==2)
		data->window.draw(frontiere);
	for(int i=0;i<players.size();i++)
	{
		for (int j = 0;j < players[i].CardList.size(); j++)
		{
			data->window.draw(players[i].CardList[j]);
		}
		data->window.draw(players[i].CardList[players[i].iCardSelection]);
		data->window.draw(players[i].title);
	}
	for (int i = 0; i < players.size(); i++)
	{
		data->window.draw(players[i].CardList[players[i].iCardSelection]);
	}
}

bool CUpgradeState::matchTypeWithValue(upgradeForOnePlayer& player, std::string type, std::string value)
{
	std::vector<std::string> typeString = { "maxXp","healthPoint","maxHealthPoint",
									"moveSpeed","canonNumber","damagePerBullet",
										"attackSpeed","bulletSpeed","misc","dashDistance","msDash","dashDamage","isDashInvicible" };
	int pos = (int)(std::find(typeString.begin(), typeString.end(), type) - typeString.begin());
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
			case 4: //canon number
				//On s'en branle
				break;
			case 5: //DamagePerBullet
				player.pointerToWeaponPlayer->getWeaponStats().bulletDamage = setValue(player.pointerToWeaponPlayer->getWeaponStats().bulletDamage, value);
				break;
			case 6: //attack speed
				player.pointerToWeaponPlayer->getWeaponStats().attackSpeed = setValue(player.pointerToWeaponPlayer->getWeaponStats().attackSpeed, value);
				break;
			case 7: // bullet speed
				player.pointerToWeaponPlayer->getWeaponStats().bulletSpeed = setValue(player.pointerToWeaponPlayer->getWeaponStats().bulletSpeed, value);
				break;
			case 8: //misc
				switch (value[0])
				{
				case '*':
					return false;
					break;
				case '+':
					return false;
					break;
				case '-':
					return false;
					break;
				default:
					player.pointerToPlayer->traitermisc(value, player.type);
					break;
				}
				break;
			case 9: //dash distance
				player.pointerToPlayer->setDashDistance(setValue(player.pointerToPlayer->getDashDistance(), value));
				break;
			case 10: // dash damage
				player.pointerToPlayer->setDashDamage(setValue(player.pointerToPlayer->getDashDamage(), value));
				break;
			case 11: //isDashInvicible
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
			}
		}
		return true;
	}
	return true;
}

void CUpgradeState::handleInput(upgradeForOnePlayer& player, sf::Event& event)
{
	if (sf::Keyboard::isKeyPressed(inputOfPlayers[player.pointerToPlayer->numero - 1].button1)&&player.cfini==false) {
		//prevent from multiple key detection
		if (player.hasPressedKey++ == 1)
		{
			applyStats(player);
			US->avancer(*player.playerComp, player.iCardSelection);
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
		player.CardList[previousSelec].setOutlineThickNess(0.f);
		player.CardList[player.iCardSelection].setOutlineThickNess(10.f);
	}
}
