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

	for (json::iterator it = j.begin(); it != j.end(); ++it) {

		if (it.key() == "drawable") {
			float f = j[it.key()]["colour"][0];
		}

	}
}