#include "CUpgradeState.h"




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
	int nbofUpgrade = 4;
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

void CUpgradeState::applyStats()
{
	for (int i = 0; i < CardList[iCardSelection].type.size(); i++)
	{
		matchTypeWithValue(CardList[iCardSelection].type[i], CardList[iCardSelection].Upgrade[i]);
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
	if (player != NULL)
	{
		pointerToPlayer1 = player; 
	}
	if (pointerToUpgradeStocks != NULL)
		US = pointerToUpgradeStocks;
}

void CUpgradeState::STEInit() 
{
	levelofPlayer = pointerToPlayer1->getLevel();
	if (levelofPlayer <= 2)
		isFirstTime = true;
	else
		isFirstTime = false;
	type = whichKindofUpgrade();
	playerComp = &pointerToPlayer1->curUpgrade[type];
	currentGraph = &US->currentGraph((*playerComp));
	CreateCard();
	std::string typestring;
	switch (type)
	{
	case 0:
		typestring = "\nAmélioration de l'arme principale ";
		pointerToWeapon = pointerToPlayer1->getMainWeapon();
		break;
	case 1:
		typestring = "\nAmélioration de l'arme secondaire ";
		pointerToWeapon = pointerToPlayer1->getSecondaryWeapon();
		break;
	case 2:
		typestring = "\nAmélioration diverse ";
		break;
	}
	CardList[iCardSelection].setOutlineThickNess(10.f);
	applyCardUpgrademaxMinCharSize(CardList);
	for (int i = 0; i < CardList.size(); i++)
	{
		CardList[i].resizeTexts();
	}
	std::string temp = "Passage au niveau " + std::to_string(this->levelofPlayer) + typestring;
	title.setString(temp);
	title.setFont(data->assets.GetFont("Nouvelle"));
	title.setCharacterSize(40);
	title.setPosition(sf::Vector2f((data->assets.sCREEN_WIDTH - title.getGlobalBounds().width) / 2, (data->assets.sCREEN_HEIGHT * 0.1f - title.getGlobalBounds().height) / 2));
	if (!blurShader.loadFromFile("shaders/vertexbandw.vert", "shaders/blurFrag.frag"))
		std::cout << "bof";
	blurShader.setUniform("texture", sf::Shader::CurrentTexture);
	blurShader.setUniform("u_resolution", sf::Glsl::Vec2((float)data->assets.sCREEN_WIDTH,(float)data->assets.sCREEN_HEIGHT));
}
void CUpgradeState::STEHandleInput()
{
	sf::Event event;
	while (data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
			data->window.close();
		else if (sf::Keyboard::isKeyPressed(inputOfPlayers[this->pointerToPlayer1->numero-1].button1)) {
			//prevent from multiple key detection
			if (hasPressedKey++ == 1)
			{
				applyStats();
				US->avancer(*playerComp,iCardSelection);
				pointerToPlayer1->setBoolLevelUp(false);
				data->machine.RemoveState();
			}
		}
		else if (event.type == sf::Event::KeyPressed)
		{
				int previousSelec = iCardSelection;
			if (event.key.code == inputOfPlayers[this->pointerToPlayer1->numero-1].moveRight)
			{
				iCardSelection = (iCardSelection + 1) % CardList.size();
			}
			else if (event.key.code == inputOfPlayers[this->pointerToPlayer1->numero-1].moveLeft)
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
	sf::RenderTexture back;
	back.create(data->assets.sCREEN_WIDTH, data->assets.sCREEN_HEIGHT);
	back.clear();
	blurShader.setUniform("texture", sf::Shader::CurrentTexture);
	pointertoGameState->drawOnTarget(back,delta);
	back.display();
	fond = sf::Sprite(back.getTexture());
	data->window.draw(fond, &blurShader);
	for (int i = 0; i < CardList.size(); i++)
	{
		data->window.draw(CardList[i]);
	}
	data->window.draw(title);
}

bool CUpgradeState::matchTypeWithValue(std::string type, std::string value)
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
				pointerToPlayer1->setMaxXp(setValue(pointerToPlayer1->getMaxXp(), value));
				break;
			case 1:  //Health Point
				pointerToPlayer1->setLifePoint(setValue(pointerToPlayer1->getLifePoint(), value));
			case 2: // Max HealthPoint
				pointerToPlayer1->setMaxXp((int)setValue(pointerToPlayer1->getMaxHealth(), value));
				break;
			case 3: //move Speed
				pointerToPlayer1->setMoveSpeed(setValue(pointerToPlayer1->getMoveSpeed(), value));
				break;
			case 4: //canon number
				//On s'en branle
				break;
			case 5: //DamagePerBullet
				pointerToWeapon->getWeaponStats().bulletDamage = setValue(pointerToWeapon->getWeaponStats().bulletDamage, value);
				break;
			case 6: //attack speed
				pointerToWeapon->getWeaponStats().attackSpeed = setValue(pointerToWeapon->getWeaponStats().attackSpeed, value);
				break;
			case 7: // bullet speed
				pointerToWeapon->getWeaponStats().bulletSpeed = setValue(pointerToWeapon->getWeaponStats().bulletSpeed, value);
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
					pointerToPlayer1->traitermisc(value, this->type);
					break;
				}
				break;
			case 9: //dash distance
				pointerToPlayer1->setDashDistance(setValue(pointerToPlayer1->getDashDistance(), value));
				break;
			case 10: // dash damage
				pointerToPlayer1->setDashDamage(setValue(pointerToPlayer1->getDashDamage(), value));
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
				pointerToPlayer1->setIsDashInvicible(temp);
				break;
			}
		}
		return true;
	}
	return true;
}