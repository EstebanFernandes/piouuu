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
		std::stack<StateRef> states; // pile qui g�rent les diff�rents �tats
		StateRef newState;// Pointeur vers un nouvel �tat
		bool _isRemoving = false;
		bool _isAdding= false;
		bool _isReplacing = false;
	public:
		//Constructeurs et destructeurs
		StateMachine();
		~StateMachine() {};
		// M�thodes
		void AddState(StateRef newState, bool isReplacing= true);
		void RemoveState();

		void ProcessStateChanges();

		StateRef& GetActiveState(); 
	};
}
using Engine::StateRef;