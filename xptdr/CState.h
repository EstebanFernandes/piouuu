#pragma once
//Classe virtuelle qu'on doit hériter pour construire une scène, on redéfinit les méthodes init (appelés en premier),
//update( appelé pour update la scène (faire bouger les personnages par exemple))
//HandleInput où on peut gérer les inputs et ce que l'on fait avec
//Et draw qui sert à afficher sur l'écran (on doit toujours commencer par window.clear et finir par window.display)
class CState
{
public:
	//Méthodes :
	virtual void STEInit() = 0;
	virtual void STEHandleInput() = 0;
	virtual void STEUpdate(float delta) = 0;
	virtual void STEDraw(float delta) = 0; // différence entre les frames
	virtual void STEPause() {};
	virtual void STEResume() {};
};

