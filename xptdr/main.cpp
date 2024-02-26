#include "CJeu.h"
#include "DEFINITIONS.h"
//SIUUUUU
int main() {
	//Assure que chaque appelle à rand donne un nombre différent
	srand(static_cast<unsigned int>(time(nullptr)));
	CJeu(1280, 720, "PIOU PIOU");
}