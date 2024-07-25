#pragma once
#include "DEFINITIONS.h"
#include "CParserCSV.h"
#include "CCLavierVirtuel.h"
#include "CScoreboard.h"
#include "CButton.h"
#include"InterfaceState.h"

template <class MType> class CGameOver : public CState, public InterfaceState
{
private:
	bool askedScore;
	float score;
	int rank;
	std::string playerName = "None";
	CScoreboard scoreboard;
	GameDataRef data;
	sf::Shader Shader;
	sf::Sprite backGroundImage;
	sf::Text textGameOver;
	std::vector<CButton> buttonList;
	int selectedButton;
	//sf::Text textRestart;
	//sf::Text textMainMenu;
	sf::Texture texture;
	std::vector<CCharacter> characters;
	sf::Text info;
	//private methods
	void updateCharacter();
	void setRank();
	void updateFileRanks();
public:
	CGameOver<MType>(GameDataRef _data) {
		data = _data;
		selectedButton = 0;
	}
	CGameOver<MType>(GameDataRef _data, std::vector<CCharacter> characters_, float scoreParam) {
		selectedButton = 0;
		data = _data;
		characters = characters_;
		score = scoreParam;
		askedScore = false;
	}
	void STEInit();
	void STEHandleInput(sf::Event& event);
	void STEUpdate(float delta);
	void STEDraw(float delta);
	void STEResume();
};

template <class MType>
void CGameOver<MType>::STEInit()
{
	setRank();
	updateCharacter();
	texture.create(data->window.getSize().x, data->window.getSize().y);
	texture.update(data->window);
	backGroundImage.setTexture(texture);
	if (!Shader.loadFromFile("shaders/fragbandw.frag",sf::Shader::Fragment))
	{
		std::cout << "bof";

	}
	Shader.setUniform("textureSampler", sf::Shader::CurrentTexture);
	Shader.setUniform("u_resolution", sf::Glsl::Vec2(data->assets.getEcranBound()));

	if (rank > 10) {
		//�crire le nom du looser
		updateFileRanks();
		scoreboard = CScoreboard(&(data->assets), rank);
		scoreboard.setPosAuto();
	}


	textGameOver.setFont(data->assets.GetFont("Lato"));
	//textGameOver.setString("mdrr gros gros naze");
	textGameOver.setCharacterSize(30);
	textGameOver.setPosition((data->assets.sCREEN_WIDTH / 2) - (textGameOver.getGlobalBounds().width / 2),
		(data->assets.sCREEN_HEIGHT * 0.15f));

	CButton button(&(data->assets));
	button.setString("Rejouer");
	button.setOutlineThickness(4);
	button.setThicknessColor(sf::Color::White);
	button.setSize(data->assets.sCREEN_WIDTH * 0.15f, data->assets.sCREEN_HEIGHT * 0.1f);
	button.setColor(sf::Color(174, 137, 100));
	button.setPosition((data->assets.sCREEN_WIDTH * 0.2f-button.getGlobalBounds().width/2.f), 
		data->assets.sCREEN_HEIGHT * 0.8f-button.getGlobalBounds().height/2.f);
	button.displayButtonInfo();
	buttonList.push_back(button);
	button.setString("Menu Principal");
	button.setOutlineThickness(0);
	button.setPosition(data->assets.sCREEN_WIDTH * 0.8f - button.getGlobalBounds().width / 2.f,
		data->assets.sCREEN_HEIGHT * 0.8f - button.getGlobalBounds().height / 2.f);
	buttonList.push_back(button);
	std::vector<CUI*> mdrr;
	for (int i = 0; i < buttonList.size(); i++)
	{
		mdrr.push_back(&buttonList[i]);
	}
	InterfaceState::applymaxMinCharSize(mdrr);
	//data->machine.AddState(StateRef(new CScoreboard(data, score)), false);
	data->assets.stopMusique("PartieJour");
}
template <class MType>
void CGameOver<MType>::STEHandleInput(sf::Event& event)
{
		if (sf::Event::Closed == event.type)
			data->window.close();
		/*
		else if (data->inputs.IsTextClicked(buttons[0], sf::Mouse::Left, data->window))
			data->machine.AddState(StateRef(new CMainMenuState(data)), true);
		else if (data->inputs.IsTextClicked(buttons[1], sf::Mouse::Left, data->window))
			data->machine.AddState(StateRef(new MType(data, character)), true);*/
		else if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == inputOfPlayers[0].moveRight) {
				buttonList[selectedButton].setOutlineThickness(0);
				selectedButton = (selectedButton + 1) % 2;
				buttonList[selectedButton].setOutlineThickness(5);
			}
			else if (event.key.code == inputOfPlayers[0].moveLeft) {
				buttonList[selectedButton].setOutlineThickness(0);
				selectedButton = abs(selectedButton - 1) % 2;
				buttonList[selectedButton].setOutlineThickness(5);
			}
			else if (event.key.code == inputOfPlayers[0].button1) {
				if (selectedButton == 0) {
					data->machine.AddState(StateRef(new MType(data, characters)), true);
				}
				else if (selectedButton == 1) {
					data->machine.AddState(StateRef(new CMainMenuState(data)), true);
				}
				else {
					std::cout << "bizarre";
				}
			}
		}
}
template <class MType>
void CGameOver<MType>::STEUpdate(float delta)
{
	if (rank <= 10 && !askedScore) {
		data->machine.AddState(StateRef(new CClavierVirtuel(data, score, rank, &playerName,(int)characters.size())), false);
		askedScore = true;
	}
	std::stringstream ss;
	sf::Vector2i mousePositionScreen = sf::Mouse::getPosition(data->window);
	ss << "mouse position : \n" << "Window : " << mousePositionScreen.x << " " << mousePositionScreen.y << "\n";
	info.setString(ss.str());
}
template <class MType>
void CGameOver<MType>::STEDraw(float delta)
{
	sf::RenderWindow& temp = data->window;
	temp.draw(backGroundImage, &Shader);
	//temp.draw(textGameOver);
	//temp.draw(scoreboard);

	for (int i = 0; i < buttonList.size(); i++) {
		temp.draw(buttonList[i]);
	}

}

template<class MType>
inline void CGameOver<MType>::STEResume()
{
	updateFileRanks();
	// TO DO : Bien placer le scoreboard
	scoreboard = CScoreboard(&(data->assets), rank);
	scoreboard.setPosAuto();
}

template<class MType>
inline void CGameOver<MType>::updateCharacter()
{
	CParserCSV parser = CParserCSV("res/data/characters.csv");
	std::vector<std::vector<std::string>> charactersInfo = parser.getElements();
	for (int j = 0; j < characters.size(); j++)
	{
		for (int i = 1; i < charactersInfo.size(); i++) {
			if (charactersInfo[i][0] == characters[j].getName()) {

				float maxHealthPointTemp = 20;
				if (charactersInfo[i][4] != "" && typeid(std::stof(charactersInfo[i][4])) == typeid(int)) maxHealthPointTemp = std::stof(charactersInfo[i][4]);

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
				characters[j].setCharacterStats(maxHealthPointTemp, moveSpeedTemp, canonNumberTemp, damagePerBulletTemp, attackSpeedTemp, bulletSpeedTemp);
			}
		}
	}
}

template<class MType>
inline void CGameOver<MType>::setRank()
{
	CParserCSV parser = CParserCSV("res/data/Scoreboard.csv");
	std::vector<std::vector<std::string>> elements = parser.getElements();

	int index = (int)elements.size() - 1;
	if (parser.isEmpty())
		index = -1;
	else {
		while (index >= 0 && score > std::stoi(elements[index][2])) {
			index -= 1;
		}
	}
	if (index == -1) {
		//TOP 1 !!!!!!!!!!!!!!!!!
		std::cout << "score : " << score << ", rank 1 tu es le goat de PIOU" << std::endl;
		rank = 1;
	}
	else if (index + 2 <= 100) {
		//DANS LE TOP 100 !!
		rank = index + 2;
		std::cout << "score : " << score << ", ton rang : " << rank << " (c'est naze)" << std::endl;
	}
	else {
		rank = index + 2;
		//T'ES NUL, pas top 100
	}
}

template<class MType>
inline void CGameOver<MType>::updateFileRanks()
{
	std::cout << "le nom : " << playerName << std::endl;

	//ICI, on ajoute le nom dans le classement
	std::string scoreString = std::to_string(score);
	std::string nameCharacter = "";
	for (int i = 0; i < characters.size(); i++)
	{
		nameCharacter = nameCharacter + characters[i].getName();
		if (i == 0&& characters.size()!=1)
			nameCharacter = std::string(nameCharacter + "&");
	}
	size_t r = scoreString.find('.') + 3;
	scoreString.erase(r, scoreString.size() - r);
	std::string textToAdd = playerName + ";" + nameCharacter + ";" + scoreString;
	std::cout << "text to add : " << textToAdd << std::endl;

	std::vector<std::string> lines;
	std::string line;

	std::ifstream file("res/data/Scoreboard.csv");
	if (!file.is_open()) {
		std::cout << "Can't open scoreboard file\n";
	}
	else if (rank <= 100) {
		//On complete ici pour ajouter textToAdd en position rank-1
		while (std::getline(file, line)) {
			lines.push_back(line);
		}
		file.close();

		if (lines.size() == rank - 1) {
			lines.push_back(textToAdd);
		}
		else {
			// top 100 : on ne rentre pas dans le classement
			lines.insert(lines.begin() + rank - 1, textToAdd);
		}


		std::ofstream outputFile("res/data/Scoreboard.csv");
		for (const std::string& line : lines) {
			outputFile << line << std::endl;
		}
		outputFile.close();
	}
}
