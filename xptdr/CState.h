#pragma once
//Classe virtuelle qu'on doit h�riter pour construire une sc�ne, on red�finit les m�thodes init (appel�s en premier),
//update( appel� pour update la sc�ne (faire bouger les personnages par exemple))
//HandleInput o� on peut g�rer les inputs et ce que l'on fait avec
//Et draw qui sert � afficher sur l'�cran (on doit toujours commencer par window.clear et finir par window.display)
class CState
{
public:
	//M�thodes :
	virtual void STEInit() = 0;
	virtual void STEHandleInput() = 0;
	virtual void STEUpdate(float delta) = 0;
	virtual void STEDraw(float delta) = 0; // diff�rence entre les frames
	virtual void STEPause() {};
	virtual void STEResume() {};
};

