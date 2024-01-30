#include "CMiscellaneous.h"

void CMiscellaneous::traitermisc(std::string& misc)
{
	const std::vector<std::string> supportedMisc{ "autoAim","velocUp" ,"doubleTirs1","doubleTirs2","gunshot"};
	int pos = (int)(std::find(supportedMisc.begin(), supportedMisc.end(), misc) - supportedMisc.begin());
	if (pos >= supportedMisc.size()) {
		std::cout << "La string est vide\n";
	}
	switch (pos)
	{
		//auto aim
		player->BAW.addShootType(player->BAW.autoAim);
	case 0:

		break;
		//Velocity up
	case 1:

		break;
		//doubleTirs1
	case 2:
		player->BAW.addShootType( player->BAW.doubleTirs1);
		break;
		//doubleTirs2
	case 3:
		player->BAW.addShootType(player->BAW.doubleTirs2);
		break;
		//gunshot
	case 4:
		player->BAW.addShootType(player->BAW.gunshotAim);
		break;
		misc.insert(0, "+");

	}
}
