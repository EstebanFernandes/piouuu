#include "Weapon.h"

void Weapon::setTypeArme(int type)
{
	if (type == gunslinger || type == laser) {
		typeArme = type;
	}
}

int Weapon::getTypeArme()
{
	return typeArme;
}
