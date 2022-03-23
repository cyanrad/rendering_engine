#pragma once
#include <unordered_map>
#include "glm/glm.hpp"

namespace wangine {
class InputManager
{
public:
	InputManager();

	void update();
	void PressKey(unsigned int keyID);
	void releaseKey(unsigned int keyID);
	bool isKeyPressed(unsigned int keyID);
	bool isKeyPressedTrue(unsigned int keyID);

	//setter
	void setMouseCoords(float x, float y);

	//getter
	glm::vec2 getMouseCoords() const { return _mouseCoords; }
private:
	bool wasKeyDown(unsigned int keyID);
	
	std::unordered_map<unsigned int, bool> _keyMap;
	std::unordered_map<unsigned int, bool> _previosKeyMap;
	glm::vec2 _mouseCoords;
};
}
