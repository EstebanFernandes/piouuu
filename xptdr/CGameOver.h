#pragma once
#include "CState.h"
#include "CMainMenuState.h"
#include "DEFINITIONS.h"
#include "CParserCSV.h"
#include "CCLavierVirtuel.h"
#include "CScoreboard.h"

template <class MType> class CGameOver : public CState
{
private:
	int score;
	sf::Texture texture;
	bool premierefois=true;
	GameDataRef data;
	sf::Shader Shader;
	sf::Sprite backGroundImage;
	sf::Text textGameOver;
	sf::Text textRestart;
	sf::Text textMainMenu;
	sf::Texture texta;
	CCharacter character;
public:
	CGameOver<MType>(GameDataRef _data) {
		data = _data;
	}
	CGameOver<MType>(GameDataRef _data, CCharacter characterParam, int scoreParam) {
		data = _data;
		character = characterParam;
		score = scoreParam;

		CParserCSV parser = CParserCSV("res/data/characters.csv");
		std::vector<std::vector<std::string>> charactersInfo = parser.getElements();

		for (int i = 1; i < charactersInfo.size(); i++) {
			if (charactersInfo[i][0] == character.getName()) {

				int maxHealthPointTemp = 20;
				if (charactersInfo[i][4] != "" && typeid(std::stoi(charactersInfo[i][4])) == typeid(int)) maxHealthPointTemp = std::stoi(charactersInfo[i][4]);

				float moveSpeedTemp = 0.5f;
				if (charactersInfo[i][5] != "" && typeid(std::stof(charactersInfo[i][5])) == typeid(float)) moveSpeedTemp = std::stof(charactersInfo[i][5]);

				int canonNumberTemp = 1;
				if (charactersInfo[i][6] != "" && typeid(std::stoi(charactersInfo[i][6])) == typeid(int)) canonNumberTemp = std::stoi(charactersInfo[i][6]);

				int damagePerBulletTemp = 5;
				if (charactersInfo[i][7] != "" && typeid(std::stoi(charactersInfo[i][7])) == typeid(int)) damagePerBulletTemp = std::stoi(charactersInfo[i][7]);

				float attackSpeedTemp = 8.f;
				if (charactersInfo[i][8] != "" && typeid(std::stof(charactersInfo[i][8])) == typeid(float)) attackSpeedTemp = std::stof(charactersInfo[i][8]);

				float bulletSpeedTemp = 2.0f;
				if (charactersInfo[i][9] != "" && typeid(std::stof(charactersInfo[i][9])) == typeid(float)) bulletSpeedTemp = std::stof(charactersInfo[i][9]);

				character.setCharacterStats(maxHealthPointTemp, moveSpeedTemp, canonNumberTemp, damagePerBulletTemp, attackSpeedTemp, bulletSpeedTemp);
			}
		}
	}
	void STEInit();
	void STEHandleInput();
	void STEUpdate(float delta);
	void STEDraw(float delta);
};

template <class MType>
void CGameOver<MType>::STEInit()
{
	/*if (!Shader.loadFromFile("vertexbandw.vert", "fragbandw.frag"))
	{
		std::cout << "bof";

	}
	Shader.setUniform("texture", sf::Shader::CurrentTexture);*/
	sf::RenderWindow& Renderwindow = data->window;
	//sf::Texture textur;
	//textur.create(Renderwindow.getSize().x, Renderwindow.getSize().y);
	//textur.update(Renderwindow);
	//texta = textur;
	//backGroundImage.setTexture(texta);
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

	data->machine.AddState(StateRef(new CScoreboard(data, score)), false);
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
			data->machine.AddState(StateRef(new MType(data, character)), true);
	}

}
template <class MType>
void CGameOver<MType>::STEUpdate(float delta)
{
	sf::RenderWindow& temp = data->window;
	if (premierefois)
	{
		texture.create(temp.getSize().x, temp.getSize().y);
		texture.update(temp);
		backGroundImage.setTexture(texture);
		premierefois = false;
	}
}
template <class MType>
void CGameOver<MType>::STEDraw(float delta)
{
	sf::RenderWindow& temp = data->window;
	temp.clear();
	temp.draw(backGroundImage);
	temp.draw(textGameOver);
	temp.draw(textMainMenu);
	temp.draw(textRestart);
	temp.display();
}
