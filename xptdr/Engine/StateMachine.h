#pragma once
#include <memory>
#include <stack>
#include "../State/State.h"
#include <iostream>
#include<vector>
using StateNS::State;

namespace Engine {

typedef std::unique_ptr<State> StateRef;
	class StateMachine
	{
	private:
		//Attributs
		std::vector<int> aaa;
		int i = 0;
		std::stack<StateRef> states; // pile qui gèrent les différents états
		StateRef newState;// Pointeur vers un nouvel état
		bool _isRemoving = false;
		bool _isAdding= false;
		bool _isReplacing = false;
	public:
		//Constructeurs et destructeurs
		StateMachine();
		~StateMachine() {};
		// Méthodes
		void AddState(StateRef newState, bool isReplacing= true);
		void RemoveState();

		void ProcessStateChanges();

		StateRef& GetActiveState(); 
	};
}
using Engine::StateRef;