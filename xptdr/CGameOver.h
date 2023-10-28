#pragma once
#include "CState.h"
#include "CMainMenuState.h"
#include "DEFINITIONS.h"
template <class MType> class CGameOver : public CState
{
private:
	GameDataRef data;
	sf::Shader Shader;
	sf::Sprite backGroundImage;
	sf::Text textGameOver;
	sf::Text textRestart;
	sf::Text textMainMenu;
	sf::Texture texta;
public:
	CGameOver<MType>(GameDataRef _data) {
		data = _data;
	}
	void STEInit();
	void STEHandleInput();
	void STEUpdate(float delta);
	void STEDraw(float delta);
};

template <class MType>
void CGameOver<MType>::STEInit()
{
	sf::RenderWindow& Renderwindow = data->window;
	sf::Texture textur;
	textur.create(Renderwindow.getSize().x, Renderwindow.getSize().y);
	textur.update(Renderwindow);

	if (textur.copyToImage().saveToFile("filename.jpg"))
	{
		std::cout << "screenshot saved to filename.jpg" <<std::endl;
	}
	texta = textur;
//	texta = data->assets.GetTexture("endScreen");
	if (!Shader.loadFromFile("vertexbandw.vert","fragbandw.frag"))
	{
		std::cout << "bof";

	}
	Shader.setUniform("texture", sf::Shader::CurrentTexture);
	backGroundImage.setTexture(texta);
	textGameOver.setFont(data->assets.GetFont("Lato"));
	textGameOver.setString("mdrr gros naze");
	textGameOver.setCharacterSize(30);
	textGameOver.setPosition((data->assets.sCREEN_WIDTH / 2) - (textGameOver.getGlobalBounds().width / 2),
		(data->assets.sCREEN_HEIGHT * 0.15f));
	textRestart.setFont(data->assets.GetFont("Lato"));
	textRestart.setString("Rejouer");
	textRestart.setCharacterSize(30);
	textRestart.setPosition((data->assets.sCREEN_WIDTH / 2) - (textRestart.getGlobalBounds().width / 2),
		(data->assets.sCREEN_HEIGHT * 0.3f));
	textMainMenu.setFont(data->assets.GetFont("Lato"));
	textMainMenu.setString("Retour vers le menu principal\n(pas le futur lol ;-) )");
	textMainMenu.setCharacterSize(30);
	textMainMenu.setPosition((data->assets.sCREEN_WIDTH / 2) - (textMainMenu.getGlobalBounds().width / 2),
		(data->assets.sCREEN_HEIGHT * 0.5f));
}
template <class MType>
void CGameOver<MType>::STEHandleInput()
{
	sf::Event event;
	while (data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
			data->window.close();
		else if (data->inputs.IsTextClicked(textMainMenu, sf::Mouse::Left, data->window))
			data->machine.AddState(StateRef(new CMainMenuState(data)), true);
		else if (data->inputs.IsTextClicked(textRestart, sf::Mouse::Left, data->window))
			data->machine.AddState(StateRef(new MType(data)), true);
	}

}
template <class MType>
void CGameOver<MType>::STEUpdate(float delta)
{
}
template <class MType>
void CGameOver<MType>::STEDraw(float delta)
{
	sf::RenderWindow& temp = data->window;
	temp.clear();
	temp.draw(backGroundImage, &Shader);
	temp.draw(textGameOver);
	temp.draw(textMainMenu);
	temp.draw(textRestart);
	temp.display();
}
