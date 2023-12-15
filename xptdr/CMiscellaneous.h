#pragma once
#include"CPlayer.h"
//Classe qui gère les spécifités d'un personnage
class CMiscellaneous
{
private:
	CPlayer* player;
	const std::vector<std::string> supportedMisc{ "autoAim","velocUp" ,"doubleTirs1","doubleTirs2"};
	std::vector<std::string> listMisc;
	void traitermisc(std::string& misc);
public:
	CMiscellaneous() {
		player = NULL;
	}
	CMiscellaneous(CPlayer* player_) {
		player = player_;
	}
	CMiscellaneous(CPlayer* player_, std::vector<std::string> copyy) {
		player = player_;
		listMisc = copyy;
	}
	void addMisc(std::string m) {
		listMisc.push_back(m);
		traitermisc(listMisc[listMisc.size() - 1]);
	}

};

