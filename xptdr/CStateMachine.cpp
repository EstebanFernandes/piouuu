#include "CStateMachine.h"

CStateMachine::CStateMachine()
{
}

void CStateMachine::AddState(StateRef newState_, bool isReplacing)
{
	_isAdding = true;
	_isReplacing = isReplacing;
	newState = std::move(newState_);
}

void CStateMachine::RemoveState()
{
	_isRemoving = true;
}

void CStateMachine::ProcessStateChanges()
{
	if (_isRemoving == true && !states.empty() ) //Si ce n'est pas vide et qu'on doit remove
	{
		std::cout << "On supprime un etat" << std::endl;
		states.pop(); // C'est une pile donc rien de compliqu�

		if (!states.empty())
		{
			states.top()->STEResume();
		}
		_isRemoving = false;
	}
	if (_isAdding)
	{
		if ( ! states.empty() ) {
			if (_isReplacing) 
				states.pop();
			else {
				states.top()->STEPause();
			}
		}
		std::cout << "On ajoute un etat" << std::endl;
		states.push(std::move(newState));
		_isAdding = false;
		states.top()->STEInit();
	}
	
}

StateRef& CStateMachine::GetActiveState()
{
	return states.top();
}
