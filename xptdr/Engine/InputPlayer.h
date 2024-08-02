#pragma once
#include<SFML/Graphics.hpp>
using input = sf::Keyboard::Key;
/// <summary>
/// Cette classe permet de g�rer les inputs r�aliser par un joueur, les touches sp�cifier sont celles de la borne
/// Pour cela on a des attributs const d�fini par le constructeur qui renvoie vers les cl�s de chaque joueur pour chaque bouton 
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
	/// Constructeur qui prend un num�ro (ie quel joueur on a) 
	/// et d�fini les bonnes cl�s du clavier pour le joueur associ�
	/// </summary>
	/// <param name="number"></param>
	InputPlayer(int number);
};

