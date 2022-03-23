#include "InputManager.h"
#include <iostream>

namespace wangine {
	InputManager::InputManager() : _mouseCoords(0.0f)
	{

	}

void InputManager::update()
{
		//loop through key map using a for each loop
	for(auto& it : _keyMap){
		_previosKeyMap[it.first] = it.second;
	}
}

	
void InputManager::PressKey(unsigned int keyID)
{
	_keyMap[keyID] = true;
}

void InputManager::releaseKey(unsigned int keyID) 
{
	_keyMap[keyID] = false;
}

bool InputManager::isKeyPressed(unsigned int keyID)
{
	auto it = _keyMap.find(keyID);

	//found the key
	if (it != _keyMap.end()){ return it->second; }
	//if key not found
	else
	return false;
}

bool InputManager::isKeyPressedTrue(unsigned int keyID)
{
		//check if it's pressed
	bool isPressed;
		if(isKeyPressed(keyID == true && wasKeyDown(keyID) == false))
		{
			printf("test");

			return  true;
		}
		return false;
}

bool InputManager::wasKeyDown(unsigned int keyID)
{
	auto it = _previosKeyMap.find(keyID);

	//found the key
	if (it != _previosKeyMap.end()) { return it->second; }
	//if key not found
	else {
		return false;
	}
}



void InputManager::setMouseCoords(float x, float y)
{
	_mouseCoords.x = x;
	_mouseCoords.y = y;
}

}
