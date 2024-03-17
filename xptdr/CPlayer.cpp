#include "CPlayer.h"




void CPlayer::setSprite()
{
	//getSprite().setScale(0.7f, 0.7f);
	//R2Sprite.setScale(0.7f, 0.7f);
	//R2Offset = R2Offset * 0.7f;
	setPositionEntity((assets->sCREEN_WIDTH / 4.f) - (getSprite().getGlobalBounds().width / 2), (assets->sCREEN_HEIGHT / 2.f) - (getSprite().getGlobalBounds().height / 2.f));
}

void CPlayer::initStat()
{
	score = 0;
}

void CPlayer::setValue(float& init, std::string modif)
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
}

void CPlayer::setValue(int& init, std::string modif)
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
}

void CPlayer::setAssets(CAssetManager* a)
{
	assets = a;
	mainWeapon->assets = a;
	secondaryWeapon->assets = a;
	assets->addSFX("bulletSound", &secondaryWeapon->bulletSound);
	assets->addSFX("bulletSound", &mainWeapon->bulletSound);
	setTexture(name);
	R2Sprite.setTexture(assets->GetTexture("R2D2"));
	R2Sprite.setOrigin(0.f, 0.f);
	R2Anim = CAnimation(&R2Sprite, sf::IntRect(0, 0, 30, 30), 1, 0.16f);
	R2Anim.pxbetFrames = 2;
	R2Offset = sf::Vector2f(22.f, -6.f);
	if (isAnimated) anim = CAnimation(getPointerSprite(), sf::IntRect(0, 0, 153, 66), 4, 0.16f);
	std::string nameImage;
	CWeaponStat ws((float)damagePerBullet, bulletSpeed, sf::Vector2f(1.f, 0.f), 0, nameImage, sf::Vector2f(1.f, 1.f), attackSpeed);
	mainWeapon->setWeaponStats(ws);
	if (name.find("Rancoeur") != std::string::npos) {
		mainWeapon->setBulletAsset("bulletImageRancoeur");
		nameImage = "bulletImageRancoeur";
		//mainWeapon->getWeaponStats().bulletScale = sf::Vector2f(1.5f, 1.5f);
	}
	if (name.find("Golden") != std::string::npos) {
		mainWeapon->setBulletAsset("bulletImageGolden");
		nameImage = "bulletImageGolden";
	}

	initLifeBar();
	setSprite();
	mainWeapon->setTouche(sf::Keyboard::Num1);
	ws.dir = sf::Vector2f(0.f, 1.f);
	secondaryWeapon->setWeaponStats(ws);
	secondaryWeapon->setBulletAsset("bulletSecond");
	secondaryWeapon->setTouche(sf::Keyboard::Num2);
	sf::Vector2f temp(0.f, -1.f);
	secondaryWeapon->getWeaponStats().addDir(temp);
	mainWeapon->setAimBoolean(&seekForTarget);
	secondaryWeapon->setAimBoolean(&seekForTarget);
}

bool CPlayer::checkGlobalCollisions()
{
	sf::FloatRect currentBounds = getGlobalBounds();
	sf::FloatRect nextBounds = currentBounds;
	nextBounds.left += currentBounds.width / 2.f;
	nextBounds.top += currentBounds.height / 2.f;
	//Top collision and bot collision

	if (currentBounds.top < 0){
		setPositionEntity(nextBounds.left, currentBounds.height / 2.f);
		 currentBounds = getGlobalBounds();
		 nextBounds = currentBounds;
		nextBounds.left += currentBounds.width / 2.f;
		nextBounds.top += currentBounds.height / 2.f;
	}
	else if(currentBounds.top + currentBounds.height > assets->sCREEN_HEIGHT){
		setPositionEntity(nextBounds.left, assets->sCREEN_HEIGHT - currentBounds.height / 2.f);
		currentBounds = getGlobalBounds();
		nextBounds = currentBounds;
		nextBounds.left += currentBounds.width / 2.f;
		nextBounds.top += currentBounds.height / 2.f;
	}
	//Left and right collision

	if (currentBounds.left < 0){
		setPositionEntity(currentBounds.width / 2.f, nextBounds.top);
		currentBounds = getGlobalBounds();
		nextBounds = currentBounds;
		nextBounds.left += currentBounds.width / 2.f;
		nextBounds.top += currentBounds.height / 2.f;
	}
	else if (currentBounds.left + currentBounds.width > assets->sCREEN_WIDTH){
		setPositionEntity(assets->sCREEN_WIDTH - currentBounds.width / 2.f, nextBounds.top);
		currentBounds = getGlobalBounds();
		nextBounds = currentBounds;
		nextBounds.left += currentBounds.width / 2.f;
		nextBounds.top += currentBounds.height / 2.f;
	}
	return false;
}

void CPlayer::resetMovement()
{
	isMovingDown = false;
	isMovingLeft = false;
	isMovingRight = false;
	isMovingUp = false;
}

Weapon* CPlayer::getMainWeapon()
{
	return mainWeapon;
}

void CPlayer::setMainWeapon(Weapon* weaponParam)
{
	delete mainWeapon;
	mainWeapon = weaponParam;
}

Weapon* CPlayer::getSecondaryWeapon()
{
	return secondaryWeapon;
}

void CPlayer::setSecondaryWeapon(Weapon* weaponParam)
{
	delete secondaryWeapon;
	secondaryWeapon = weaponParam;
}

void CPlayer::traitermisc(std::string& misc)
{
	const std::vector<std::string> supportedMisc{ "autoAim","velocUp" ,"doubleTirs1","doubleTirs2","gunshot","dot", "laser","explosiveBullet"};
	int pos = (int)(std::find(supportedMisc.begin(), supportedMisc.end(), misc) - supportedMisc.begin());
	if (pos >= supportedMisc.size()) {
		std::cout << "Rien a été trouvé\n";
	}
	else if (pos==6) {
		sf::Keyboard::Key temp = mainWeapon->getTouche();
		setMainWeapon(new laserWeapon(assets));
		mainWeapon->setTouche(temp);
		misc.insert(0, "+");
	}
	else {
		mainWeapon->traiterMisc(pos);
		misc.insert(0, "+");
	}
}

void CPlayer::traitermisc(std::string& misc, int type)
{
	const std::vector<std::string> supportedMisc{ "autoAim","velocUp" ,"doubleTirs1","doubleTirs2","gunshot","dot", "laser","explosiveBullet","spin"};
	int pos = (int)(std::find(supportedMisc.begin(), supportedMisc.end(), misc) - supportedMisc.begin());
	if (pos >= supportedMisc.size()) {
		std::cout << "Rien a été trouvé\n";
	}
	else if (pos == 6) {
		if (type == 1)
		{
			sf::Keyboard::Key t = secondaryWeapon->getTouche();
			CWeaponStat a = secondaryWeapon->getWeaponStats();
			setSecondaryWeapon(new laserWeapon(assets));
			secondaryWeapon->setWeaponStats(a);
			secondaryWeapon->setTouche(t);
		}
		else if (type == 0)
		{
			sf::Keyboard::Key t = mainWeapon->getTouche();
			CWeaponStat a = mainWeapon->getWeaponStats();
			setMainWeapon(new laserWeapon(assets));
			mainWeapon->setWeaponStats(a);
			mainWeapon->setTouche(t);
		}
	}
	else {
		if (type == 1)
		{
			secondaryWeapon->traiterMisc(pos);
		}
		else if (type == 0)
		{
			mainWeapon->traiterMisc(pos);
		}
	}
	misc.insert(0, "+");
	specificites.push_back(misc);
}

void CPlayer::updateMisc()
{
	for (int i = 0; i < specificites.size(); i++)
	{
		traitermisc(specificites[i]);
	}
}

void CPlayer::iNeedMoreBullet()
{
}




 
CPlayer::CPlayer()
{
	setType(Player);
	initStat();
}

CPlayer::CPlayer(CAssetManager* a)
{
	imageName = "player1Image";
	setType(Player);
	setAssets(a);
}

CPlayer::~CPlayer()
{
	delete mainWeapon;
	delete secondaryWeapon;
}


void CPlayer::initLifeBar()
{
	float lp = 87.f;
	previouslifePoint = maxHealthPoint;
	previousMaxHealth = maxHealthPoint;
	float scaleFactor = 1.f;
	float lifebarwidth = lp * maxHealthPoint;
	if (lifebarwidth >= assets->sCREEN_WIDTH * 0.5f)
	{
		float maxWidthPerPoint = assets->sCREEN_WIDTH * 0.5f / (float)maxHealthPoint;
		scaleFactor = maxWidthPerPoint / lp;
	}
	for (int i = 0; i < maxHealthPoint; i++)
	{
		sf::Sprite temp;
		temp.setTexture(assets->GetTexture("lifepoint"));
		temp.setTextureRect(sf::IntRect(0, 0, (int)lp, 26));
		temp.setScale(scaleFactor, scaleFactor * 2.f);
		temp.setPosition(100.f + i * temp.getGlobalBounds().width , 30.f);
		lifeBar.push_back(temp);
	}
}


void CPlayer::PLYupdateMovement(sf::Event event)
{
	switch (event.type)
	{
	case sf::Event::KeyPressed :
		if (event.key.code == upKey)
			isMovingUp = true;
		else if (event.key.code == leftKey)
			isMovingLeft = true;
		else if (event.key.code == downKey)
			isMovingDown = true;
		else if (event.key.code == rightKey)
			isMovingRight = true;
		if (event.key.code == dashKey &&dashClock.getElapsedTime().asSeconds()>=cdDash)
		{
			wantToDash = true;
			dashClock.restart();
		}
		break;
	case sf::Event::KeyReleased:
		if (event.key.code == upKey)
			isMovingUp = false;
		else if (event.key.code == leftKey)
			isMovingLeft = false;
		else if (event.key.code == downKey)
			isMovingDown = false;
		else if (event.key.code == rightKey)
			isMovingRight = false;
		if (event.key.code == dashKey)
			wantToDash = false;
		break;
	default:
		break;


	}
}
void CPlayer::updateDash(float delta)
{
	if (distancethrought < dashDistance)
	{
		distancethrought += utilities::renvoieNormeVecteur(dir * msDash * delta * 60.f);
		moveEntity(dir * msDash * delta * 60.f);
	}
	else {//Le dash est fini
		dashClock.restart();
		isDashing = false;
		distancethrought = 0.f;
		wantToDash = false;
	}
}


void CPlayer::updateMovement(float dt)
{
	if (isDashing)
	{
		updateDash(dt);
	}
	else {
		sf::Vector2f direction;
		if (isMovingUp)
			direction.y -= 1.f;
		if (isMovingDown)
			direction.y += 1.f;
		if (isMovingLeft)
			direction.x -= 1.f;
		if (isMovingRight)
			direction.x += 1.f;
		if (direction.y == 1.f)
		{
			R2Anim.setDifferentAnimation(2);
			R2Offset.y = -8.f;
			setPositionEntity(getSprite().getPosition());
			anim.setDifferentAnimation(2);
		}
		else if (direction.y == -1.f)
		{
			R2Offset.y = -5.f;
			setPositionEntity(getSprite().getPosition());
			R2Anim.setDifferentAnimation(1);
			anim.setDifferentAnimation(1);
		}
		else
		{
			R2Offset.y = -6.f;
			setPositionEntity(getSprite().getPosition());
			R2Anim.resetAnimation();
			anim.resetAnimation();
		}
		dir = direction;
		if (wantToDash)
		{
			isDashing = true;
			if (dir == sf::Vector2f(0.f, 0.f))
				dir = sf::Vector2f(1.f, 0.f);
		}
		else
			moveEntity(direction * moveSpeed * dt * 60.f);
	}
}




void CPlayer::renderLifeBar(sf::RenderTarget& target)
{
	for (int i = 0; i < lifeBar.size(); i++)
	{
		target.draw(lifeBar[i]);
	}
}


void CPlayer::gainXP(int levelofEntity)
{
	xp += 4 * levelofEntity;
}
void CPlayer::updateLifeBar()
{
	if (previouslifePoint > healthPoint)
	{
		for (int i = (int)healthPoint; i < previouslifePoint; i++)
		{

			lifeBar[i].setTextureRect(sf::IntRect(87, 0, 87, 26));
		}
		previouslifePoint = healthPoint;
		hasBeenHit = false;
	}
	else 
	{
		for (int i = (int)previouslifePoint; i < healthPoint; i++)
		{

			lifeBar[i].setTextureRect(sf::IntRect(0, 0, 87, 26));
		}
		previouslifePoint = healthPoint;
		hasBeenHit = false;
	}
	if (healthPoint <= 0)
		needDelete = true;
}
void CPlayer::updateEntity(float dt)
{
	updateMovement(dt);
	checkGlobalCollisions();
	updateFx();
	updateBuff(dt);
	updateLifeBar();
 	if (xp >= maxXp&& hasLevelUp==false)
	{
		level++;
		xp -= maxXp;
		maxXp += 10;
		hasLevelUp = true;
	}
	sf::Vector2f nezdeLavion(getSprite().getPosition().x + getGlobalBounds().width / 2.f,
		getSprite().getPosition().y);
	secondaryWeapon->setWeaponPos(R2Sprite.getPosition());
	secondaryWeapon->weaponControls(sf::Event());
	secondaryWeapon->updateWeapon(dt);
	mainWeapon->setWeaponPos(nezdeLavion);
	mainWeapon->weaponControls(sf::Event());
	mainWeapon->updateWeapon(dt);
}

void CPlayer::renderEntity(sf::RenderTarget& target)
{
	target.draw(getSprite());
	mainWeapon->renderWeapon(target);
	secondaryWeapon->renderWeapon(target);
	target.draw(R2Sprite);
}


void CPlayer::updateFx()
{
	if (getAnimated()) {
		anim.updateAnimation();
		R2Anim.updateAnimation();
	}
	if (hasBeenHit)
	{
		hittype = true;
		getSprite().setColor(sf::Color::Red);
		isInvulnerable = true;
		std::cout << "debut invu" << std::endl;
		hitClock.restart();
	}
	if (hittype)
	{
		if (hitClock.getElapsedTime().asSeconds() >= 0.5f)
		{
			getSprite().setColor(sf::Color::White);
			hitClock.restart();
			isInvulnerable = false;
			std::cout << "fin invu" << std::endl;
			hittype = false;
			hasBeenHit = false;
		}
	}
}


bool CPlayer::matchTypewithValue(std::string type, std::string value)
{
	return false;
}