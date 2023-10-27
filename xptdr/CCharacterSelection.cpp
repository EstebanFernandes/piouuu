#include "CCharacterSelection.h"
#include "CTestGame.h"

CCharacterSelection::CCharacterSelection(GameDataRef _data) : data(_data)
{
}

void CCharacterSelection::STEInit()
{
	data->assets.LoadFont("Lato", FONT_FILE_PATH); //Load la police d'écriture

	//temp
	data->assets.LoadTexture("Vaisso",
		GAME_SPACESHIP_FILEPATH);
	data->assets.LoadTexture("backgroundCharacter", CHARACTERBACKGROUND);

	characterCard = CCard(425, 40, "blabla", "Descrption", "Vaisso", &(data->assets));
	 

	CMMBackground.setTexture(data->assets.GetTexture("Background"));
	CMMBackground.setScale(1.2f, 1.2f);


}

void CCharacterSelection::STEHandleInput()
{
	sf::Event event;
	while (data->window.pollEvent(event)) {

		//Pour pouvoir fermer la fenêtre
		if (sf::Event::Closed == event.type) {
			data->window.close();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
			data->machine.AddState(StateRef(new CTestGame(data)), true);
		}
	}
}

void CCharacterSelection::STEUpdate(float delta)
{
	characterCard.update(delta);
}

void CCharacterSelection::STEDraw(float delta)
{
	data->window.clear(sf::Color::Red);
	data->window.draw(CMMBackground);
	data->window.draw(characterCard);
	data->window.display();
}

