#include "CScoreboard.h"

CScoreboard::CScoreboard(GameDataRef _data)
{
	data = _data;
}

CScoreboard::CScoreboard(GameDataRef _data, int score)
{
	data = _data;

	CParserCSV parser = CParserCSV("res/data/Scoreboard.csv");
	std::vector<std::vector<std::string>> elements = parser.getElements();

	int index = elements.size() - 1;

	while (index >= 0 && score > std::stoi(elements[index][1])) {
		index -= 1;
	}
	if (index == -1) {
		//TOP 1 !!!!!!!!!!!!!!!!!
		std::cout << "score : " << score << ", rank 1 tu es le goat de PIOU" << std::endl;
	}
	else if (index + 2 <= 100) {
		//DANS LE TOP 100 !!
		//demander le nom puis faut ajouter dans le tableau, afficher 
		std::cout << "score : " << score << ", ton rang : " << index + 2 << " (c'est naze)" << std::endl;
	}
	else {
		//T'ES NUL
		// faut juste afficher le tableau des scores
	}



}

void CScoreboard::STEInit() {

}

void CScoreboard::STEHandleInput() {

}
void CScoreboard::STEUpdate(float delta) {

}

void CScoreboard::STEDraw(float delta) {

}