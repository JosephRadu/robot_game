#pragma once

/**
* @Author	Joseph Radu
* @date		13th January 2017
* @brief	Keyboard for input handling and key bindings!
*
*/

#include <map>
#include <vector>
class Keyboard
{
private:
	std::map<std::string, std::string> vKeyBindings;
public:
	Keyboard();

	/*!
	\brief Add a key binding
	\param std::string
	\param std::string
	*/
	void AddKeyBinding(std::string binding, std::string key);


	/*!
	\brief Get key binding
	\param std::string Binding
	\return std::string
	*/
	std::string GetKeyBinding(std::string binding);


};