#pragma once

/**
* @Author	Joseph Radu
* @date		12tg January 2017
* @brief	Data handling for json.
*
*/

#include "json.hpp"

using json = nlohmann::json;

class Manager_JSON
{
private:
	json j;
public:
	/*
	*@brief	Default constructor.
	*/
	Manager_JSON();

	/*
	*@brief	Read the json file and process the data inside it.
	*@param string File name.
	*/
	void ReadFile(std::string sFileName);
};