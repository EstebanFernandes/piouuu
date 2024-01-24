#include "Boss.h"

Boss::Boss(CAssetManager* assetsParam, CPlayer* playerParam, std::vector<CHittingEntity*>* entityListParam, int* enemyNumberParam)
{
	BAW.assets = assetsParam;

	player1 = playerParam;
	entityList = entityListParam;
	assets = assetsParam;
	enemyNumber = enemyNumberParam;

	initEnnemy(assets, "boss");
	getSprite().setScale(0.7f, 0.7f);
	rotate(180);

	initPositionX = assets->sCREEN_WIDTH * 1.15f;
	initPositionY = assets->sCREEN_HEIGHT * 0.5f;
	explosionSprite.setScale(0.6f, 0.6f);
	moveSpeed = 3.f;
	attackSpeed = 1.75f;

	setDamagePerBullet(0);

	setBulletSpeed(1.0f);
	setMaxHealth(100);

	setSprite();

	//getSprite().setRotation(180);
		
	//getSprite().setOrigin(getSprite().getLocalBounds().width / 2.f, getSprite().getLocalBounds().height / 2.f);
	//getSprite().setScale(0.7f, 0.7f);

	phasesCaps.push_back(75.f);
	phasesCaps.push_back(50.f);
	phasesCaps.push_back(25.f);
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
	int enemyColumnNumber = assets->sCREEN_HEIGHT / enemyTest.getSprite().getGlobalBounds().height;
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
	BAW.updateEntity(delta);

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
			sf::Vector2f r(
				getSprite().getPosition().x - getGlobalBounds().width / 2.f,
				getSprite().getPosition().y);

			BAW.shootTowardDirection(r, player1->getSprite().getPosition(), damagePerBullet, bulletSpeed);
			// vient juste le restart le timer à la fin
			bulletClock.restart();
		}
	}
}

void Boss::updatewPlayer(float delta, CPlayer& player)
{
	CEnemy::updatewPlayer(delta, player);

	std::vector<CBulletAuto>* bullets = BAW.getVector();
	size_t temp = bullets->size();
	for (int i = 0; i < temp; i++) {
		if (player.checkCollisions((*bullets)[i])) {
			player.reduceHP((*bullets)[i].getDamage());
			bullets->erase(bullets->begin() + i);
			if (i != 0)
				i--;
			temp--;
		}
	}
}

void Boss::renderEntity(sf::RenderTarget& target)
{
	CEnemy::renderEntity(target);
	BAW.renderEntity(target);
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
