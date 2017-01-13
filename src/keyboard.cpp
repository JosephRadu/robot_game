/**
* @Author	Joseph Radu
* @date		13th January 2017
* @brief	Keyboard for input handling and key bindings!
*
*/

#include "keyboard.h"

Keyboard::Keyboard()
{

}

void Keyboard::AddKeyBinding(std::string binding, std::string key)
{
	vKeyBindings[binding] = key;
}


std::string Keyboard::GetKeyBinding(std::string binding)
{
	return vKeyBindings.at(binding);
}
