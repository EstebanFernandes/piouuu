#include "CommentJouer.h"

const sf::IntRect StateNS::bouton::pasEnfonce = sf::IntRect(0, 0, 11, 12);
const sf::IntRect StateNS::bouton::Enfonce = sf::IntRect(11, 1, 11, 11);
StateNS::CCommentJouer::CCommentJouer(GameDataRef data_)
	: data(data_)
{
}

void StateNS::CCommentJouer::initAssets()
{
	data->assets.deleteEverythingBut("");
	std::vector<std::vector<std::string>> charactersInfo = IO::retrieveCSVFile("res/data/characters.csv");

	//Nouvelle méthode pour initialiser les stats
	for (int i = 1; i < 2;i++) {
		characterList.push_back(Character(charactersInfo[i][1], charactersInfo[i][0], charactersInfo[i][2], charactersInfo[i][3] == "animated"));
		data->assets.LoadTexture(charactersInfo[i][0], charactersInfo[i][1]);
	}
	player.updateStates(characterList[0]);

	//Initialisation joystick et bouton
	data->assets.LoadTexture("joystick", "res/img/ui/joystick.png");
	data->assets.LoadTexture("bouton", "res/img/ui/boutonseul.png");
	data->assets.LoadTexture("micel", "res\\img\\characters\\micel.png");
	data->assets.LoadTexture("micelsb", "res\\img\\characters\\miceletsb.png");
	data->assets.LoadTexture("sb", "res\\img\\characters\\sb.png");
	data->assets.LoadSFX("bulletSound", "res\\sfx\\Piou.wav");
	data->assets.LoadTexture("bulletImage", "res\\img\\characters\\bulletImage.png");
	data->assets.LoadTexture("bulletSecond", "res\\img\\characters\\bullet_Second.png");
	data->assets.LoadTexture("explosionPlayer", "res\\img\\characters\\explosionPlayer.png");
	data->assets.LoadTexture("bulletImageRancoeur", "res\\img\\characters\\bulletRancoeur.png");
	data->assets.LoadTexture("bulletImageGolden", "res\\img\\bullet_Golden.png");
	data->assets.LoadTexture("R2D2", "res\\img\\characters\\Droide2.png");
	data->assets.LoadTexture("logonormal", "res\\img\\characters\\logonormal2.png");
	data->assets.LoadSFX("planeSound", "res\\sfx\\plane.mp3");
	data->assets.LoadTexture("muzzleFlash", "res\\img\\muzzleFlash.png");
	data->assets.LoadTexture("buttonArcade", "res\\img\\UI\\boutonenfonce2.png");
}

void StateNS::CCommentJouer::STEInit()
{
	float width = (float)Engine::SCREEN_WIDTH;
	float height = (float)Engine::SCREEN_HEIGHT;
	initAssets();
	player.setAssets(&data->assets);
	player.setTouche(&inputOfPlayers[0]);

	fond.setSize(sf::Vector2f(getEcranBound()));
	fond.setFillColor(sf::Color(255, 255, 255, 50));
	
	//Initialisation des images 
	joystick.sprite.setTexture(data->assets.GetTexture("joystick"));
	joystick.sprite.setScale(scale,scale);
	bouton boutonImage(&data->assets,scale);
	for(int i=0;i<6;i++)
		buttons.push_back(boutonImage);

	joystick.anim = Animation(&joystick.sprite, sf::Vector2i(20, 20), 9, -1.f, 2);
	sf::Vector2i size(20, 20);
	joystick.sprite.setOrigin(joystick.sprite.getLocalBounds().width/2.f, joystick.sprite.getLocalBounds().height);
	
	joystick.sprite.setPosition(width * 0.05f, height * 0.8f-joystick.sprite.getGlobalBounds().height/2.f);
	sf::Vector2f basePosition(
		joystick.sprite.getPosition().x + joystick.sprite.getGlobalBounds().width / 2.f +width*0.1f,
		joystick.sprite.getPosition().y-(joystick.sprite.getGlobalBounds().height + 33.f*scale/2.f) / 2.f
		);
	for(int i =0;i<6;i++)//Tous les boutons sont placés là où l'image des boutons était
		buttons[i].sprite.setPosition(basePosition);

	buttons[0].sprite.move(0.f,5.f*scale);
	buttons[1].sprite.move(18.f*scale,0.f);
	buttons[2].sprite.move(36.f*scale,0.f);
	buttons[3].sprite.move(0.f, 21.f * scale);
	buttons[4].sprite.move(18.f*scale, 17.f * scale);
	buttons[5].sprite.move(36.f * scale, 16.f * scale);
	

	//Cercle 
	
	sf::CircleShape cercle;
	cercle.setRadius(5.f);
	utilities::centerObject(cercle);
	cercle.setFillColor(sf::Color::Black);
	for (int i = 0; i < 6; i++)
		buttons[i].cercle = cercle;
	//Ligne pour les boutons
	line ligne;
	ligne.rs1.setSize(sf::Vector2f(5.f,height*0.15f ));
	ligne.rs1.setFillColor(sf::Color::Black);
	ligne.rs2.setSize(sf::Vector2f(5.f, height * 0.08f));
	ligne.rs2.setFillColor(sf::Color::Black);
	ligne.rs2.setOrigin(ligne.rs2.getLocalBounds().width / 2.f,
		ligne.rs2.getLocalBounds().height);
	ligne.rs1.setOrigin(ligne.rs1.getLocalBounds().width / 2.f,
		ligne.rs1.getLocalBounds().height);
	ligne.rs2.setRotation(315.f);
	for (int i = 0; i < 6; i++)
	{
		switch (i)
		{
		case 1 :
			ligne.rs1.setSize(sf::Vector2f(5.f, height * 0.12f));
			ligne.rs1.setOrigin(ligne.rs1.getLocalBounds().width / 2.f,
				ligne.rs1.getLocalBounds().height);
			break;
		case 2:
			ligne.rs2.setRotation(45.f);
			ligne.rs1.setSize(sf::Vector2f(5.f, height * 0.13f));
			ligne.rs1.setOrigin(ligne.rs1.getLocalBounds().width / 2.f,
				ligne.rs1.getLocalBounds().height);
			break;
		case 3:
			ligne.rs2.setRotation(225.f);
			ligne.rs1.setRotation(180.f);
			ligne.rs2.setSize(sf::Vector2f(5.f, height * 0.1f));
			ligne.rs2.setOrigin(ligne.rs2.getLocalBounds().width / 2.f,
				ligne.rs2.getLocalBounds().height);
			break;
		case 4:
			ligne.rs2.setRotation(225.f);
			ligne.rs1.setRotation(180.f);
			ligne.rs2.setSize(sf::Vector2f(5.f, height * 0.07f));
			ligne.rs2.setOrigin(ligne.rs2.getLocalBounds().width / 2.f,
				ligne.rs2.getLocalBounds().height);
			break;
		case 5:
			ligne.rs2.setRotation(225.f);
			ligne.rs1.setRotation(180.f);
			ligne.rs2.setSize(sf::Vector2f(5.f, height * 0.07f));
			ligne.rs2.setOrigin(ligne.rs2.getLocalBounds().width / 2.f,
				ligne.rs2.getLocalBounds().height );
			break;
		}
		
		buttons[i].ligne = ligne;

		switch (i)
		{
		case 1:
			buttons[i].ligne.rs2.setSize(sf::Vector2f(0.f, 0.f));
			buttons[i].ligne.rs2.setOrigin(sf::Vector2f(0.f, 0.f));
			break;
		case 4:
			buttons[i].ligne.rs2.setSize(sf::Vector2f(0.f, 0.f));
			buttons[i].ligne.rs2.setOrigin(sf::Vector2f(0.f, 0.f));
			break;
		}

		buttons[i].ligne.rs2.setPosition(buttons[i].sprite.getPosition());
		switch(i)
		{
		case 2:
			buttons[i].ligne.rs1.setPosition(
				buttons[i].ligne.rs2.getGlobalBounds().left+ buttons[i].ligne.rs2.getGlobalBounds().width - ligne.rs1.getGlobalBounds().width / 2.f,
				buttons[i].ligne.rs2.getGlobalBounds().top + ligne.rs1.getGlobalBounds().width);
			break;
		case 3:

			buttons[i].ligne.rs1.setPosition(
				buttons[i].ligne.rs2.getGlobalBounds().left + ligne.rs1.getGlobalBounds().width / 2.f,
				buttons[i].ligne.rs2.getGlobalBounds().top + ligne.rs2.getGlobalBounds().width - ligne.rs1.getGlobalBounds().width / 2.f);
			break;
		
		case 1:
			buttons[i].ligne.rs1.setPosition(buttons[i].sprite.getPosition());
			break;
		case 4:
			buttons[i].ligne.rs1.setPosition(buttons[i].sprite.getPosition());
			break;

		default:
			buttons[i].ligne.rs1.setPosition(
				buttons[i].ligne.rs2.getGlobalBounds().left + ligne.rs1.getGlobalBounds().width / 2.f,
				buttons[i].ligne.rs2.getGlobalBounds().top + ligne.rs1.getGlobalBounds().width);
			break;
		}
		
	}

	//Texte pour les boutons
	sf::Text text;
	text.setFont(data->assets.GetFont("Nouvelle"));
	text.setFillColor(sf::Color::Black);
	//Joystick
	text.setString("Se déplacer");
	text.setOrigin(
		text.getLocalBounds().width / 2.f,
		text.getLocalBounds().height / 2.f);
	text.setPosition(joystick.sprite.getPosition());
	text.move(0.f, 10.f);
	joystickText = text;
	//Bouton arme principale
	text.setString("Principale");
	text.setOrigin(
		text.getLocalBounds().width / 2.f,
		text.getLocalBounds().height / 2.f);
	text.setPosition(
		buttons[0].ligne.rs1.getGlobalBounds().left-buttons[0].ligne.rs1.getGlobalBounds().width/2.f,
		buttons[0].ligne.rs1.getGlobalBounds().top);
	text.move(0.f, -text.getGlobalBounds().height*0.8f);
	buttons[0].texte = text;
	//Bouton arme secondaire
	text.setString("Secondaire");
	text.setOrigin(
		text.getLocalBounds().width / 2.f,
		text.getLocalBounds().height / 2.f);
	text.setPosition(
		buttons[1].ligne.rs1.getGlobalBounds().left - buttons[1].ligne.rs1.getGlobalBounds().width / 2.f,
		buttons[1].ligne.rs1.getGlobalBounds().top);
	text.move(0.f, -text.getGlobalBounds().height * 0.8f);
	buttons[1].texte = text;
	//Dash
	text.setString("Dash");
	text.setOrigin(
		text.getLocalBounds().width / 2.f,
		text.getLocalBounds().height / 2.f);
	text.setPosition(
		buttons[3].ligne.rs1.getGlobalBounds().left - buttons[3].ligne.rs1.getGlobalBounds().width / 2.f,
		buttons[3].ligne.rs1.getGlobalBounds().top+buttons[3].ligne.rs1.getGlobalBounds().height);
	text.move(0.f, +text.getGlobalBounds().height * 0.6f);
	buttons[3].texte = text;
	//Amélioration
	text.setString("Amélioration");
	text.setOrigin(
		text.getLocalBounds().width / 2.f,
		text.getLocalBounds().height / 2.f);
	text.setPosition(
		buttons[4].ligne.rs1.getGlobalBounds().left - buttons[4].ligne.rs1.getGlobalBounds().width / 2.f,
		buttons[4].ligne.rs1.getGlobalBounds().top+ buttons[4].ligne.rs1.getGlobalBounds().height);
	text.move(0.f, +text.getGlobalBounds().height * 0.6f);
	buttons[4].texte = text;
	for (int i = 0; i < 6; i++)
		buttons[i].cercle.setPosition(buttons[i].sprite.getPosition());

	//Mannequin
	mannequin.setAssets(&data->assets);

}

void StateNS::CCommentJouer::STEHandleInput(sf::Event& event)
{
	player.PLYupdateMovement(event);
	if (sf::Event::Closed == event.type)
		data->window.close();
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Escape)
		{
			data->machine.RemoveState();
			hasChanges = true;
		}
	}
	if(sf::Keyboard::isKeyPressed(inputOfPlayers[0].button1))
	{
		buttons[0].changeBool(true);
	}
	else
		buttons[0].changeBool(false);
	if (sf::Keyboard::isKeyPressed(inputOfPlayers[0].button2))
	{
		buttons[1].changeBool(true);
	}
	else
		buttons[1].changeBool(false);
	if (sf::Keyboard::isKeyPressed(inputOfPlayers[0].button3))
	{
		buttons[2].changeBool(true);
	}
	else
		buttons[2].changeBool(false);
	if (sf::Keyboard::isKeyPressed(inputOfPlayers[0].button4))
	{
		buttons[3].changeBool(true);
	}
	else
		buttons[3].changeBool(false);
	if (sf::Keyboard::isKeyPressed(inputOfPlayers[0].button5))
	{
		buttons[4].changeBool(true);
	}
	else
		buttons[4].changeBool(false);
	if (sf::Keyboard::isKeyPressed(inputOfPlayers[0].button6))
	{
		buttons[5].changeBool(true);
	}
	else
		buttons[5].changeBool(false);
}

void StateNS::CCommentJouer::STEUpdate(float delta)
{
	updateTime();
	background.updateBackground(delta);
	player.updateEntity(delta);
	mannequin.updateEntity(delta);
	mannequin.updatewPlayer(delta, player);
	sf::Vector2f direction = player.getDirection();
	sf::Vector2i anim(0,0);
	switch ((int)direction.x)
	{
	case -1:
		anim.x = 1;
		break;
	case 1:
		anim.x = 2;
		break;
	}
	switch ((int)direction.y)
	{
	case -1:
		anim.y = 3;
		break;
	case 1:
		anim.y = 6;
		break;
	}
	joystick.anim.setcurrentXFrameNumber(anim.x + anim.y);
}

void StateNS::CCommentJouer::STEDraw(float delta)
{
	background.renderBackground(data->window);
	data->window.draw(fond);
	//Touches 
	data->window.draw(joystick.sprite);
	for (int i = 0; i < 6; i++)
	{
		data->window.draw(buttons[i].sprite);
		switch(i)
		{
		case 2:
			break;
		case 5:
			break;
		default:
			data->window.draw(buttons[i].ligne.rs1);
			data->window.draw(buttons[i].ligne.rs2);
			data->window.draw(buttons[i].texte);
			data->window.draw(buttons[i].cercle);
			break;
		}
	}
	data->window.draw(joystickText);
	mannequin.renderEntity(data->window);
	player.renderEntity(data->window);
	/*for (int i = 0; i < entityList.size(); i++)
	{
		entityList[i]->renderEntity(data->window);
	}*/
}
