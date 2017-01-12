/**
* @Author	Joseph Radu
* @date		12tg January 2017
* @brief	Data handling for json.
*
*/

#include "manager_json.h"
#include <fstream>
#include <sstream>

Manager_JSON::Manager_JSON()
{

}

void Manager_JSON::ReadFile(std::string sFileName)
{
	std::ifstream i(sFileName);
	json j;
	i >> j;

	/*
	json json_data_map = {
	{ "drawable_1",{
	{ "type", "plane" },
	{ "position", { 0, 0, -12 } },
	{ "rotation",{ 0, 1, 0 } },
	{ "scale",{ 1, 1, 1 } },
	{ "colour",{ 0.5, 0.5, 0.25 } },
	} }
	};
	*/

	for (json::iterator it = j.begin(); it != j.end(); ++it) {

		if (it.key() == "drawable") {

			std::cout << it.value();

		}

	}
}