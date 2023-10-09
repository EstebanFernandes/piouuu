#pragma once
#include <memory>
#include <stack>
#include "CState.h"
#include <iostream>
#include<vector>

typedef std::unique_ptr<CState> StateRef;

class CStateMachine
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
	CStateMachine();
	~CStateMachine() {};
	// M�thodes
	void AddState(StateRef newState, bool isReplacing= true);
	void RemoveState();

	void ProcessStateChanges();

	StateRef& GetActiveState(); 
};

