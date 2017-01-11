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
	std::vector<V3D> finalVertices;
public:

	bool loadOBJ(
		const char * path,
		std::vector < V3D > & out_vertices,
		std::vector < V3D > & out_uvs,
		std::vector < V3D > & out_normals
	);



	OBJ_Reader();
	void Read(std::string filename);
	int GetNextSlashes(std::istringstream& parserIn);

	std::vector<V3D> vertices();

};