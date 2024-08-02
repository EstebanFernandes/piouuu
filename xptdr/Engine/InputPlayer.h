#pragma once
#include<SFML/Graphics.hpp>
using input = sf::Keyboard::Key;
/// <summary>
/// Cette classe permet de gérer les inputs réaliser par un joueur, les touches spécifier sont celles de la borne
/// Pour cela on a des attributs const défini par le constructeur qui renvoie vers les clés de chaque joueur pour chaque bouton 
/// https://github.com/PppTours/launcherBorne
/// </summary>
class InputPlayer
{
public:
	const input moveUp;
	const input moveDown;
	const input moveLeft;
	const input moveRight;
	const input button1;
	const input button2;
	const input button3;
	const input button4;
	const input button5;
	const input button6;
	/// <summary>
	/// Constructeur qui prend un numéro (ie quel joueur on a) 
	/// et défini les bonnes clés du clavier pour le joueur associé
	/// </summary>
	/// <param name="number"></param>
	InputPlayer(int number);
};

