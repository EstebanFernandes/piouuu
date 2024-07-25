#include "CPlayer.h"
#include"chargeShot.h"



void CPlayer::setSprite()
{
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

void CPlayer::updateXpBar()
{
	float perc = (xp > maxXp) ? (float)maxXp : (float)xp;
	perc = (perc == 0) ? 0.05f : perc;
	float fullSize = lifeBarBG2.getGlobalBounds().width - lifeBarBG2.getOutlineThickness();
	xpBar.setSize(sf::Vector2f(fullSize* perc / maxXp, 10.f));
	xpBar.setFillColor(sf::Color(204, 150-150 * perc / maxXp, 255, 200));
}

void CPlayer::setAssets(CAssetManager* a)
{
	mainWeapon = new CGunslinger();
	secondaryWeapon = new CGunslinger();
	assets = a;
	mainWeapon->assets = a;
	secondaryWeapon->assets = a;
	assets->addSFX("bulletSound", &secondaryWeapon->bulletSound);
	assets->addSFX("bulletSound", &mainWeapon->bulletSound);
	setTexture(name);
	R2Sprite.setTexture(assets->GetTexture("R2D2"));
	R2Sprite.setOrigin(0.f, 0.f);
	R2Anim = CAnimation(&R2Sprite, sf::Vector2i( 30, 30), sf::Vector2i(1,3), 0.16f,2);
	R2Offset = sf::Vector2f(22.f, -6.f);
	if (isAnimated) anim = CAnimation(getPointerSprite(), sf::Vector2i( 153, 66), sf::Vector2i(4,3), 0.16f);
	std::string nameImage;
	CWeaponStat ws((float)damagePerBullet, bulletSpeed, sf::Vector2f(1.f, 0.f), 0, nameImage, sf::Vector2f(1.f, 1.f), attackSpeed);
	mainWeapon->setWeaponStats(ws);
	muzzleFlash.setTexture(assets->GetTexture("muzzleFlash"));
	muzzleFlash.setOrigin(0.f,muzzleFlash.getLocalBounds().height/2.f);
	muzzleFlash.setScale(0.05f, 0.05f);
	if (name.find("Rancoeur") != std::string::npos) {
		mainWeapon->setBulletAsset("bulletImageRancoeur");
		nameImage = "bulletImageRancoeur";
		anim.changeIntRect(1, sf::Vector2i(153, 67));
		anim.changeIntRect(2, sf::Vector2i(153, 67));
		muzzleFlash.setColor(sf::Color(116, 66, 200));
	}
	else if (name.find("Golden") != std::string::npos) {
		mainWeapon->setBulletAsset("bulletImageGolden");
		anim.changeIntRect(1, sf::Vector2i(153, 63));
		anim.changeIntRect(2, sf::Vector2i(153, 72));
		muzzleFlash.setColor(sf::Color(255, 255, 0));
		nameImage = "bulletImageGolden";
	}
	explosionSprite.setTexture(assets->GetTexture("explosionPlayer"));
	explosionSprite.setScale(2.5f, 2.5f);
	animExplosionSprite = CAnimation(&explosionSprite, sf::Vector2i( 96, 96), sf::Vector2i(12,1), 2.f/12.f);
	setSprite();
	mainWeapon->setTouche(sf::Keyboard::Num1);
	mainWeapon->pointerToPlayer = this;
	ws.dir = sf::Vector2f(0.f, 1.f);
	secondaryWeapon->setWeaponStats(ws);
	secondaryWeapon->setBulletAsset("bulletSecond");
	secondaryWeapon->setTouche(sf::Keyboard::Num2);
	sf::Vector2f temp(0.f, -1.f);
	secondaryWeapon->getWeaponStats().addDir(temp);
	secondaryWeapon->pointerToPlayer=this;
	mainWeapon->setAimBoolean(&seekForTarget);
	secondaryWeapon->setAimBoolean(&seekForTarget);
	assets->addSFX("planeSound", &planeSound);
	assets->volumeSon(planeSound, 30.f);
	planeSound->setPitch(0.5f);
	planeSound->setLoop(true);
	planeSound->play();
	cercleRevive.initCercle(this);
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

void CPlayer::setMainWeapon(Weapon* weaponParam,bool isFirstTime)
{
	std::string bulletAssets = mainWeapon->getBulletAsset();
	sf::Keyboard::Key t = mainWeapon->getTouche();
	CWeaponStat a = mainWeapon->getWeaponStats();
delete mainWeapon;
	mainWeapon = weaponParam;
	mainWeapon->assets = assets;
	assets->addSFX("bulletSound", &mainWeapon->bulletSound);
	mainWeapon->setWeaponStats(a);
	mainWeapon->setBulletAsset(bulletAssets);
	mainWeapon->setTouche(t);
	mainWeapon->pointerToPlayer = this;
	mainWeapon->setAimBoolean(&seekForTarget);
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
//Si on ne précise pas c'est que l'on applique le bonus sur l'arme principale et secondaire
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
	const std::vector<std::string> supportedMisc{ "autoAim","velocUp" ,"doubleTirs1","doubleTirs2",
"gunshot","dot", "laser","explosiveBullet","spin","doubleTirs3","fire","ice","thunder"};
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
	assets->deleteSound(planeSound);
}

//Initialise l'icone ainsi que la barre de vie
void CPlayer::initLifeBar()
{
	float baseThickness = 4.f;
	icon.setTexture(assets->GetTexture("logonormal"));
	int num = 0;
	if (name == "Rancoeur")
		num = 1;
	else if (name == "La Golden Shower")
		num = 2;
	int offset = num * (int)icon.getTexture()->getSize().y + num * 2;
	icon.setTextureRect(sf::IntRect(offset, 0, 468, 468));
	icon.setScale(0.2f, 0.2f);

	iconCircle = sf::CircleShape(icon.getGlobalBounds().width/2.f,60);
	iconCircle.setOrigin(iconCircle.getRadius(), iconCircle.getRadius());
	iconCircle.setFillColor(sf::Color::Transparent);
	iconCircle.setOutlineColor(playerColor);
	iconCircle.setOutlineThickness(baseThickness);

	iconCircle2 = iconCircle;
	iconCircle2.setFillColor(sf::Color(0,0,0,60));
	iconCircle2.setOutlineColor(sf::Color::Black);
	iconCircle2.setRadius(iconCircle.getRadius() - (iconCircle.getOutlineThickness() / 2.f));
	iconCircle2.setOrigin(iconCircle2.getRadius(),
		iconCircle2.getRadius());
	iconCircle2.setOutlineThickness(baseThickness * 2.f);
	
	lifeBar = sf::RectangleShape(sf::Vector2f(assets->sCREEN_WIDTH / 8.f, 15.f));
	lifeBar.setOrigin(0.f, lifeBar.getLocalBounds().height / 2.f);
	lifeBar.setFillColor(sf::Color::Red);

	lifeBarBG2 = sf::RectangleShape(lifeBar);
	lifeBarBG2.setFillColor(sf::Color(0,0,0,20));
	lifeBarBG2.setOutlineColor(sf::Color::Black);
	lifeBarBG2.setOutlineThickness(baseThickness *2.f);
	lifeBarBackground = lifeBarBG2;
	sf::Vector2f newSize(lifeBarBG2.getSize());
	newSize.x += baseThickness;
	newSize.y += baseThickness;
	lifeBarBackground.setSize(newSize);
	lifeBarBackground.setFillColor(sf::Color::Transparent);
	lifeBarBackground.setOutlineColor(playerColor);
	lifeBarBackground.setOutlineThickness(baseThickness);
	lifeBarBackground.setOrigin(0.f, lifeBarBackground.getLocalBounds().height / 2.f);
	xpBar.setSize(sf::Vector2f(10.f, 10.f));
	//Violet rgb(204, 102, 255)
	xpBar.setFillColor(sf::Color(204,102,255,200));
	updateXpBar();
}


void CPlayer::PLYupdateMovement(sf::Event& event)
{
	mainWeapon->weaponControls(event);
	secondaryWeapon->weaponControls(event);
	switch (event.type)
	{
		case sf::Event::KeyPressed :
		{
			if (event.key.code == inputForPlayer->button5 && hasLevelUp)
				wantToLevelUp = true;
				if (event.key.code == inputForPlayer->moveUp)
					isMovingUp = true;
				if (event.key.code == inputForPlayer->moveLeft)
					isMovingLeft = true;
				if (event.key.code == inputForPlayer->moveDown)
					isMovingDown = true;
				if (event.key.code == inputForPlayer->moveRight)
					isMovingRight = true;
				if (event.key.code == inputForPlayer->button4 && dashClock.getElapsedTime().asSeconds() >= cdDash)
				{
					wantToDash = true;
					dashClock.restart();
				}
				break;
		}
		case sf::Event::KeyReleased:
		{
			if (event.key.code == inputForPlayer->moveUp)
				isMovingUp = false;
			if (event.key.code == inputForPlayer->moveLeft)
				isMovingLeft = false;
			if (event.key.code == inputForPlayer->moveDown)
				isMovingDown = false;
			if (event.key.code == inputForPlayer->moveRight)
				isMovingRight = false;
			if (event.key.code == inputForPlayer->button4)
				wantToDash = false;
			break;
		}
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
			anim.setDifferentAnimation(2);
			R2Offset.y = -8.f;
			setPositionEntity(getSprite().getPosition());
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
	target.draw(xpBar);
	target.draw(lifeBarBG2);
	target.draw(lifeBarBackground);
	target.draw(lifeBar);
	target.draw(iconCircle2);
	target.draw(icon);
	target.draw(iconCircle);
}


void CPlayer::gainXP(int xp_)
{
	xp += xp_;
	updateXpBar();
}
void CPlayer::updateLifeBar()
{
	if (hasBeenHit)
	{
		lifeBar.setSize(sf::Vector2f(lifeBarBG2.getSize().x * healthPoint / maxHealthPoint, 15.f));
		hasBeenHit = false;
	}
	if (healthPoint <= 0)
	{
		isDead = true;
	}
}
void CPlayer::updateEntity(float dt)
{
	if (isDead)
	{
		if (animExplosionSprite.getCurrentFrameNumber().x == 0)
		{
			explosionSprite.setPosition(sf::Vector2f(getPosition().x,
				getPosition().y ));
			animExplosionSprite.resetAnimation();
		}
		animExplosionSprite.updateAnimation();
		if (animExplosionSprite.getCurrentFrameNumber().x == 11)
		{
			if(cercleRevive.canRevive)
			{
				betweenDeathAndLife = true;
				cercleRevive.cercleClock.restart();
			}
			else {//On est tout seul
				needDelete = true;
			}
			if(cercleRevive.canRevive)
				cercleRevive.centerCercle();
		}
		secondaryWeapon->updateWeapon(dt);
		mainWeapon->updateWeapon(dt);
	}
	else
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
			timeUpgradeAnim.restart();
			if (level == 1)
				spriteButtonUpgrade.setPosition(
				upgradeText.getGlobalBounds().left+ upgradeText.getGlobalBounds().width*1.1f+ spriteButtonUpgrade.getGlobalBounds().width/2.f,
					upgradeText.getGlobalBounds().top+( (spriteButtonUpgrade.getGlobalBounds().height - upgradeText.getGlobalBounds().height*0.5f)/2.f) );
		}
		sf::Vector2f nezdeLavion(getSprite().getPosition().x + getGlobalBounds().width / 2.f,
			getSprite().getPosition().y);
		secondaryWeapon->setWeaponPos(R2Sprite.getPosition());
		secondaryWeapon->updateWeapon(dt);
		mainWeapon->setWeaponPos(nezdeLavion);
		mainWeapon->updateWeapon(dt);
	}
}



void CPlayer::renderEntity(sf::RenderTarget& target)
{
	bool isShooting = mainWeapon->isWeaponShooting();
	mainWeapon->renderWeapon(target);
	if (isShooting)
	{
		target.draw(muzzleFlash);
		utilities::flipSprite(muzzleFlash,false);
	}
	secondaryWeapon->renderWeapon(target);
	if (!isDead)
	{
		target.draw(getSprite());
		target.draw(R2Sprite);
	}
	if(animExplosionSprite.getCurrentFrameNumber().x<4&&betweenDeathAndLife==false)
	{
	}
	if (isDead&& betweenDeathAndLife ==false)
		target.draw(explosionSprite);
	else if(betweenDeathAndLife){
		cercleRevive.renderCercle(target);
	}
}


void CPlayer::updateFx()
{
	if (isAnimated) {
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

void CPlayer::setLifeBarPosition(sf::Vector2f& pos)
{
	icon.setPosition(pos.x,pos.y);
	iconCircle.setPosition((icon.getGlobalBounds().width / 2.f) + icon.getGlobalBounds().left,
		icon.getGlobalBounds().top + icon.getGlobalBounds().height / 2.f);
	iconCircle2.setPosition(iconCircle.getPosition());
	sf::Vector2f newpos(iconCircle2.getGlobalBounds().width + iconCircle2.getGlobalBounds().left - iconCircle2.getOutlineThickness() + lifeBarBG2.getOutlineThickness(),
		iconCircle2.getPosition().y);
	lifeBarBG2.setPosition(newpos);
	lifeBar.setPosition(newpos);
	newpos.x -= lifeBarBackground.getOutlineThickness() / 2.f;
	newpos.y += lifeBarBackground.getOutlineThickness();
	lifeBarBackground.setPosition(newpos);
	newpos.x -= lifeBarBackground.getOutlineThickness();
	newpos.y += lifeBarBackground.getGlobalBounds().height/2.f- lifeBarBackground.getOutlineThickness() / 2.f;
	xpBar.setPosition(newpos);
}

void CPlayer::setNumero(int& i)
{
	switch (i)
	{
	case 2:
	{
		playerColor = sf::Color(52, 199, 62);
		break;
	}
	}
	initLifeBar();
	sf::Vector2f pos(assets->sCREEN_WIDTH * 0.05f, assets->sCREEN_HEIGHT * 0.05f);
	switch (i)
	{
	case 1:
		setLifeBarPosition(pos);
		break;
	case 2:
		pos = sf::Vector2f(assets->sCREEN_WIDTH * 0.95f - lifeBarBG2.getGlobalBounds().width-iconCircle2.getGlobalBounds().width, assets->sCREEN_HEIGHT * 0.05f);
		setLifeBarPosition(pos);
		break;
	}
	numero = i;

	upgradeText.setFont(assets->GetFont("Nouvelle"));
	upgradeText.setCharacterSize(15);
	upgradeText.setString("+1 NIVEAU \nAppuyez sur");
	spriteButtonUpgrade.setTexture(assets->GetTexture("buttonArcade"));
	animboutonUpgrade = CAnimation(&spriteButtonUpgrade, sf::Vector2i(47, 33), 7,-1.f,1);
	upgradeText.setPosition(xpBar.getPosition().x, xpBar.getPosition().y + xpBar.getSize().y * 1.5f);
	if(assets->sCREEN_WIDTH==1280.f)
		spriteButtonUpgrade.setScale(2.f,2.f);
	else
		spriteButtonUpgrade.setScale(1.5f, 1.5f);
}

void CPlayer::setTouche(inputPlayer* inputt)
{
	if (inputt != NULL)
	{
		inputForPlayer = inputt;
		mainWeapon->setTouche(inputForPlayer->button1);
		secondaryWeapon->setTouche(inputForPlayer->button2);
	}
}

void CPlayer::AAAA()
{
	setMainWeapon(new chargeShot(assets));
}

void CPlayer::reduceHP(float damage)
{
	CMob::reduceHP(damage);
}

void CPlayer::revivePlayer()
{
	betweenDeathAndLife = false;
	isDead = false;
	healthPoint = maxHealthPoint * 0.4f;
	hasBeenHit = true;
	updateLifeBar();
}
