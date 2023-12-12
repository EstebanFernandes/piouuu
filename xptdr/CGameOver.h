#pragma once
#include "DEFINITIONS.h"
#include "CParserCSV.h"
#include "CCLavierVirtuel.h"
#include "CScoreboard.h"
#include "CButton.h"

template <class MType> class CGameOver : public CState
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
	sf::Texture texta;
	CCharacter character;

	//private methods
	void updateCharacter();
	void setRank();
	void updateFileRanks();
public:
	CGameOver<MType>(GameDataRef _data) {
		data = _data;
		selectedButton = 0;
	}
	CGameOver<MType>(GameDataRef _data, CCharacter characterParam, float scoreParam) {
		selectedButton = 0;
		data = _data;
		character = characterParam;
		score = scoreParam;
		askedScore = false;
		setRank();
		updateCharacter();
	}
	void STEInit();
	void STEHandleInput();
	void STEUpdate(float delta);
	void STEDraw(float delta);
	void STEResume();
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
		std::cout << "screenshot saved to filename.jpg" << std::endl;
	}
	texta = textur;
	//	texta = data->assets.GetTexture("endScreen");
	if (!Shader.loadFromFile("vertexbandw.vert", "fragbandw.frag"))
	{
		std::cout << "bof";

	}
	Shader.setUniform("texture", sf::Shader::CurrentTexture);
	backGroundImage.setTexture(texta);


	if (rank > 10) {
		//écrire le nom du looser
		updateFileRanks();
		scoreboard = CScoreboard(&(data->assets), rank);
		scoreboard.setPosAuto();
	}


	textGameOver.setFont(data->assets.GetFont("Lato"));
	textGameOver.setString("mdrr gros naze");
	textGameOver.setCharacterSize(30);
	textGameOver.setPosition((data->assets.sCREEN_WIDTH / 2) - (textGameOver.getGlobalBounds().width / 2),
		(data->assets.sCREEN_HEIGHT * 0.15f));

	CButton restartButton = CButton(data);
	restartButton.setString("Rejouer");
	restartButton.setPos(data->assets.sCREEN_WIDTH *0.2f, data->assets.sCREEN_HEIGHT * 0.8f);
	restartButton.setOutlineThickness(4);
	restartButton.setThicknessColor(sf::Color::White);
	restartButton.setSize(data->assets.sCREEN_WIDTH * 0.15f, data->assets.sCREEN_HEIGHT * 0.1f);
	restartButton.setColor(sf::Color(174, 137, 100));

	CButton menuButton = CButton(data);
	menuButton.setString("Menu Principal");
	menuButton.setPos(data->assets.sCREEN_WIDTH * 0.8f, data->assets.sCREEN_HEIGHT * 0.8f);
	menuButton.setThicknessColor(sf::Color::White);
	menuButton.setSize(data->assets.sCREEN_WIDTH * 0.15f, data->assets.sCREEN_HEIGHT * 0.1f);
	menuButton.setColor(sf::Color(174, 137, 100));
	

	buttonList.push_back(restartButton);
	buttonList.push_back(menuButton);
	//data->machine.AddState(StateRef(new CScoreboard(data, score)), false);
}
template <class MType>
void CGameOver<MType>::STEHandleInput()
{
	sf::Event event;
	while (data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
			data->window.close();
		/*
		else if (data->inputs.IsTextClicked(buttons[0], sf::Mouse::Left, data->window))
			data->machine.AddState(StateRef(new CMainMenuState(data)), true);
		else if (data->inputs.IsTextClicked(buttons[1], sf::Mouse::Left, data->window))
			data->machine.AddState(StateRef(new MType(data, character)), true);*/
		else if (event.type == sf::Event::KeyReleased) {
			if (event.key.code == sf::Keyboard::D) {
				buttonList[selectedButton].setOutlineThickness(0);
				selectedButton = (selectedButton + 1) % 2;
				buttonList[selectedButton].setOutlineThickness(5);
			}
			else if (event.key.code == sf::Keyboard::Q) {
				buttonList[selectedButton].setOutlineThickness(0);
				selectedButton = abs(selectedButton - 1) % 2;
				buttonList[selectedButton].setOutlineThickness(5);
			}
			else if (event.key.code == sf::Keyboard::Enter) {
				if (selectedButton == 0) {
					data->machine.AddState(StateRef(new MType(data, character)), true);
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

}
template <class MType>
void CGameOver<MType>::STEUpdate(float delta)
{
	if (rank <= 10 && !askedScore) {
		data->machine.AddState(StateRef(new CClavierVirtuel(data, score, rank, playerName)), false);
		askedScore = true;
	}
}
template <class MType>
void CGameOver<MType>::STEDraw(float delta)
{
	sf::RenderWindow& temp = data->window;
	temp.clear();
	temp.draw(backGroundImage, &Shader);
	temp.draw(textGameOver);
	temp.draw(scoreboard);

	for (int i = 0; i < buttonList.size(); i++) {
		temp.draw(buttonList[i]);
	}

	temp.display();
}

template<class MType>
inline void CGameOver<MType>::STEResume()
{
	updateFileRanks();
	scoreboard = CScoreboard(&(data->assets), 20, 20, rank);
}

template<class MType>
inline void CGameOver<MType>::updateCharacter()
{
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

template<class MType>
inline void CGameOver<MType>::setRank()
{
	CParserCSV parser = CParserCSV("res/data/Scoreboard.csv");
	std::vector<std::vector<std::string>> elements = parser.getElements();

	int index = (int)elements.size() - 1;

	while (index >= 0 && score > std::stoi(elements[index][2])) {
		index -= 1;
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
		//T'ES NUL, pas top 100
	}
}

template<class MType>
inline void CGameOver<MType>::updateFileRanks()
{
	std::cout << "le nom : " << playerName << std::endl;

	//ICI, on ajoute le nom dans le classement
	std::string scoreString = std::to_string(score);
	size_t r = scoreString.find('.') + 3;
	scoreString.erase(r, scoreString.size() - r);

	std::string textToAdd = playerName + ";" + character.getName() + ";" + scoreString;
	std::cout << "text to add : " << textToAdd << std::endl;

	std::vector<std::string> lines;
	std::string line;

	std::ifstream file("res/data/Scoreboard.csv");
	if (!file.is_open()) {
		std::cout << "Can't open scoreboard file\n";
	}
	else {
		//On complete ici pour ajouter textToAdd en position rank-1
		while (std::getline(file, line)) {
			lines.push_back(line);
		}
		file.close();

		if (lines.size() == rank - 1) {
			lines.push_back(textToAdd);
		}
		else {
			lines.insert(lines.begin() + rank - 1, textToAdd);
		}


		std::ofstream outputFile("res/data/Scoreboard.csv");
		for (const std::string& line : lines) {
			outputFile << line << std::endl;
		}
		outputFile.close();
	}
}
