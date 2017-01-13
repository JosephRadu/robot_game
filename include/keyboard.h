#pragma once

/**
* @Author	Joseph Radu
* @date		13th January 2017
* @brief	Keyboard for input handling and key bindings!
*
*/

#include <map>
#include <vector>
#include <iostream>

using namespace std;

class Keyboard
{
private:
	map<string, string> vKeyBindings;
public:
	Keyboard();

	/*!
	\brief Add a key binding
	\param std::string
	\param std::string
	*/
	void AddKeyBinding(string binding, string key);

	/*!
	\brief Get key binding
	\param string Binding
	\return string
	*/
	string GetKeyBinding(string binding);

};