#include "State.h"

//Nécessaire pour éviter les erreurs de link (vive le c++)
Engine::Transition StateNS::State::currentTransi= Transition();
float StateNS::State::angleOffset = (float)(rand() % 360);
float StateNS::State::time = 0.f;
sf::Clock StateNS::State::globalClock = sf::Clock();
Engine::Background StateNS::State::background = Background();
//char A::a[6] = {1,2,3,4,5,6}; 
InputPlayer StateNS::State::inputOfPlayers[2] = { InputPlayer(0),InputPlayer(1) };
void StateNS::State::updateTime()
{
	time = globalClock.getElapsedTime().asSeconds();
}

inline void StateNS::State::updateIMGUI(sf::RenderWindow& window, float dt)
{
		ImGui::SFML::Update(window, sf::seconds(dt));
		ImGui::Begin("Debug window");
		debugInfo();
		ImGui::End();
		ImGui::EndFrame();
}

StateNS::State::~State()
{
}

