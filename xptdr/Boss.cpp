#include "Boss.h"

Boss::Boss(CAssetManager* assetsParam, CPlayer* playerParam, std::vector<CHittingEntity*>* entityListParam, int* enemyNumberParam)
{
	BAW.assets = assetsParam;

	player1 = playerParam;
	entityList = entityListParam;
	assets = assetsParam;
	enemyNumber = enemyNumberParam;

	initEnnemy(assets);
	getSprite().setScale(0.7f, 0.7f);
	rotate(180);
	setTexture("boss");
	initPositionX = ((float)assets->sCREEN_WIDTH) * 1.15f;
	initPositionY = (int)(((float)assets->sCREEN_HEIGHT) * 0.5f);
	explosionSprite.setScale(0.6f, 0.6f);
	moveSpeed = 3.f;
	attackSpeed = 1.75f;

	setDamagePerBullet(0);

	setBulletSpeed(1.0f);
	setMaxHealth(100);

	setSprite();

	phasesCaps.push_back(75.f);
	phasesCaps.push_back(50.f);
	phasesCaps.push_back(25.f);
	BAW.getWeaponStats() = CWeaponStat((float)damagePerBullet, bulletSpeed, sf::Vector2f(-1.f, 0.f), 0, "", BAW.bulletScale, attackSpeed);
	BAW.setWeaponPos(sf::Vector2f(getGlobalBounds().width / 2.f, 0.f));
}

void Boss::addEnemy(std::string enemyName)
{
	if (enemyName == "roaming") {
		RoamingEnemy* enemy = new RoamingEnemy(assets);
		enemy->setMaxHealth(1);
		enemy->setScoreGived(0);
		enemy->setLevel(0);
		entityList->push_back(enemy);
		(*enemyNumber)++;
	}
	else if (enemyName == "shooter") {
		ShootingEnemy* enemy = new ShootingEnemy(assets);
		entityList->push_back(enemy);
		(*enemyNumber)++;
	}
	else {
		std::cout << "no enemy named : " << enemyName;
	}
}

void Boss::addEnemyColumn()
{
	RoamingEnemy enemyTest = RoamingEnemy(assets);
	int enemyColumnNumber = assets->sCREEN_HEIGHT / (int)enemyTest.getSprite().getGlobalBounds().height;
	int enemyMissing = std::rand() % enemyColumnNumber;
	for (int i = 0; i < enemyColumnNumber; i++) {
		if (i != enemyMissing) {
			RoamingEnemy* enemy = new RoamingEnemy(assets);
			enemy->setMaxHealth(200);
			enemy->setScoreGived(0);
			enemy->setLevel(0);
			enemy->setPositionEntity((float)assets->sCREEN_WIDTH, enemyTest.getSprite().getGlobalBounds().height / 2 + assets->sCREEN_HEIGHT * (i / (float)enemyColumnNumber));
			enemy->setDirectionY(0);
			entityList->push_back(enemy);
			(*enemyNumber)++;
		}
	}
}



void Boss::updateMovement(float delta)
{
	if (checkGlobalCollisions() && isPositionated)
		needDelete = true;
	updateLifeBar();
	if (onAvance == true && !isPositionated)
		moveEntity(sf::Vector2f(moveSpeed * -delta, 0));
	if (!isPositionated && getSprite().getPosition().x <= assets->sCREEN_WIDTH - getSprite().getGlobalBounds().width / 2.f) {
		isPositionated = true;
	}
}

void Boss::updateEntity(float delta)
{
	CEnemy::updateEntity(delta);
	BAW.updateWeapon(delta);

	//check for a phase switch
	if (currentLifePhase != phasesCaps.size()+1 && healthPoint / maxHealthPoint <= phasesCaps[currentLifePhase - 1]/100.f) {
		currentLifePhase++;
		changePhase();
	}


	if (currentPhase == 2) {
		//Phase 2 : apparition des ennemis
		if (invokeClock.getElapsedTime().asSeconds() >= 1.5) {
			addEnemyColumn();
			invokeClock.restart();
		}
		if (invulnerabilityClock.getElapsedTime().asSeconds() >= 10.0f) {
			isInvulnerable = false;
			changePhase();
		}
	}
	else if (currentPhase == 1) {
		if (bulletClock.getElapsedTime().asSeconds() >= 1.f / attackSpeed && isPositionated) {

			BAW.shootTowardDirection(getSprite().getPosition(), player1->getSprite().getPosition());
			// vient juste le restart le timer à la fin
			bulletClock.restart();
		}
	}
}

void Boss::updatewPlayer(float delta, CPlayer& player)
{
	CEnemy::updatewPlayer(delta, player);
	updateShootWithPlayer(player);
	if (needDelete)
		transferBullet(BAW);
}

void Boss::renderEntity(sf::RenderTarget& target)
{
	CEnemy::renderEntity(target);
	BAW.renderWeapon(target);
}

void Boss::changePhase()
{
	currentPhase++;
	std::cout << "phase : " << currentPhase << std::endl;
	if (currentPhase == 2) {
		isInvulnerable = true;
		invulnerabilityClock.restart();
	}
}
