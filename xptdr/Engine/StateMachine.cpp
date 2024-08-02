#include "StateMachine.h"

Engine::StateMachine::StateMachine()
{
}

void Engine::StateMachine::AddState(StateRef newState_, bool isReplacing)
{
	_isAdding = true;
	_isReplacing = isReplacing;
	newState = std::move(newState_);
	if(states.size()!=0)
		states.top()->hasChanges = true;
}

void Engine::StateMachine::RemoveState()
{
	_isRemoving = true;
	states.top()->hasChanges = true;
}

void Engine::StateMachine::ProcessStateChanges()
{
	if (_isRemoving == true && !states.empty() ) //Si ce n'est pas vide et qu'on doit remove
	{
		std::cout << "On supprime un etat" << std::endl;
		states.pop(); // C'est une pile donc rien de compliqué

		if (!states.empty())
		{
			states.top()->STEResume();
			states.top()->hasChanges = false;
		}
		_isRemoving = false;
	}
	if (_isAdding)
	{
		if ( ! states.empty() ) {
			if (_isReplacing) 
			{
				std::cout << "On supprime un etat" << std::endl;
				states.pop();
			}
			else {
				states.top()->STEPause();
			}
		}
		std::cout << "On ajoute un etat" << std::endl;
		states.push(std::move(newState));
		_isAdding = false;
		states.top()->hasChanges = false;
		states.top()->STEInit();
	}
	
}

Engine::StateRef& Engine::StateMachine::GetActiveState()
{
	return states.top();
}
