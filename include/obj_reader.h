#pragma once

/**
* @Author	Joseph Radu
* @date		10th January 2017
* @brief	OBJ file reader and processor.
*
*/

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "V3D.h"

class OBJ_Reader
{
private:
public:
	OBJ_Reader();
	void Read(std::string filename);
	int GetNextSlashes(std::istringstream& parserIn);

};