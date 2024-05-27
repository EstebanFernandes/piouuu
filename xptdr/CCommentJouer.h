#pragma once
#include"CState.h"
#include "CPlayer.h"
#include "CJeu.h"
	struct image{//Struct qui encapsule ce qu'on a besoin pour gérer une image 
		sf::Sprite sprite;
		CAnimation anim;
		bool isDraw = false;
	};
	struct line {
		sf::RectangleShape rs1;
		sf::RectangleShape rs2;
	};
	struct bouton {
		sf::Sprite sprite;
		sf::Text texte;
		line ligne;
		sf::CircleShape cercle;
		bouton(CAssetManager* asset,float scale) {
			sprite.setTexture(asset->GetTexture("bouton"));
			sprite.setScale(scale, scale);
			texturerect = pasEnfonce;
			sprite.setTextureRect(texturerect);
			sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height/2.f);
		}
		//Change le de enfonce a pas enfonce et corrige le sprite
		void changeBool(bool alors) {
			if(isEnfonce!=alors)
			{
				isEnfonce = alors;
				texturerect = (isEnfonce) ? Enfonce : pasEnfonce;
				sprite.setTextureRect(texturerect);
				if (isEnfonce)
					sprite.move(0.f, 1.f*sprite.getScale().x);
				else
					sprite.move(0.f, -1.f*sprite.getScale().x);
			}
		}
	private:
		sf::IntRect texturerect;
		bool isEnfonce = false;
		static const sf::IntRect pasEnfonce;
		static const sf::IntRect Enfonce;
	};

//Menu qui sert aux conns de joueurs à apprendre comment jouer
class CCommentJouer : public CState
{
private:
	CPlayer player;
	GameDataRef data;
	std::vector<CCharacter> characterList;
	image joystick;
	std::vector<bouton> buttons;
	std::vector<bool> isDraw;
	sf::Text joystickText;
	sf::RectangleShape fond;
	float scale = 5.f;
public:
	CCommentJouer(GameDataRef data_);
	void initAssets();
	void STEInit();
	void STEHandleInput();
	void STEUpdate(float delta);
	void STEDraw(float delta);
	void GameOver(){}
};

