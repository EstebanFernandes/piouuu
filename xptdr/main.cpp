#include "Engine/MainLoop.h"
#include "DEFINITIONS.h"
using Engine::MainLoop;
//SIUUUUU
int main() {
	//Assure que chaque appelle � rand donne un nombre diff�rent
	srand(static_cast<unsigned int>(time(nullptr)));
	MainLoop(1280, 720, "PIOU PIOU");
	
}