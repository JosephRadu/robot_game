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

void Keyboard::AddKeyBinding(string binding, string key)
{
	vKeyBindings[binding] = key;
}

string Keyboard::GetKeyBinding(string binding)
{
	return vKeyBindings.at(binding);
}
