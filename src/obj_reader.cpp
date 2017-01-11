#include "obj_reader.h"

OBJ_Reader::OBJ_Reader()
{

}

bool OBJ_Reader::loadOBJ(const char * path, std::vector < V3D > & out_vertices, std::vector < V3D > & out_uvs, std::vector < V3D > & out_normals)
{
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< V3D > temp_vertices;
	std::vector< V3D > temp_uvs;
	std::vector< V3D > temp_normals;

	FILE * file = fopen(path, "r");
	if (file == NULL) {
		printf("Impossible to open the file !\n");
		return false;
	}

	while (1) {

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

				   // else : parse lineHeader

		if (strcmp(lineHeader, "v") == 0) {
			V3D vertex;
			float x, y, z;
			fscanf(file, "%f %f %f\n", &x, &y, &z);

			vertex.set(x, y, z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			V3D uv;
			float x, y;
			fscanf(file, "%f %f\n", &x, &y);
			uv.set(x, y, 0);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			V3D normal;
			float x, y, z;
			fscanf(file, "%f %f %f\n", &x, &y, &z);
			normal.set(x, y, z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return false;
			}

				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);

		}

		// For each vertex of each triangle
		for (unsigned int i = 0; i < vertexIndices.size(); i++) {
			unsigned int vertexIndex = vertexIndices[i];
			V3D vertex = temp_vertices[vertexIndex - 1];
			out_vertices.push_back(vertex);
		}
	}
}

void OBJ_Reader::Read(std::string s)
{








	std::fstream modelfile(s, std::ios_base::in);
	int iNumValuesInLine = 0;
	float num;
	std::string text;
	std::string line;
	std::string name;

	// Raw data
	std::vector<float> rawVertices; //v
	std::vector<float> rawVerticesTextures; //vt
	std::vector<float> rawVerticesNormals; //vn

	// Actual ones we use for openGL.
	std::vector<float> vertices; //f
	std::vector<int> verticesTextures;
	std::vector<int> verticesNormals;

	if (modelfile.is_open())
	{
		while (getline(modelfile, line))
		{
			std::istringstream parser;
			parser.str(line);
			std::string character;

			parser >> character;

			if (character == "v")
			{
				iNumValuesInLine = 0;
				while (parser >> num)
				{
				rawVertices.push_back(num);
				iNumValuesInLine++;
				}
			}
			else if (character == "vn")
			{
				while (parser >> num)
				rawVerticesNormals.push_back(num);
			}
			else if (character == "vt")
			{
				while (parser >> num)
				rawVerticesTextures.push_back(num);
			}
			else if (character == "f")
			{
				while (parser >> num)
				{
					for (int i = 0; i < 3; i++) //V
					vertices.push_back(rawVertices.at((num * 3) - 3 + i));

					int iNumSlashes = GetNextSlashes(parser);

					if (iNumSlashes == 1) //VT
					{
						// line is format   v/vt...
						// so read the vt value
						parser >> num;

						// after the texture value - should be a normal
						iNumSlashes = 0;
						GetNextSlashes(parser);
						if (iNumSlashes == 1) //VN
						{
							// pick up the normal
							parser >> num;
							for (int i = 0; i < 3; i++)
							verticesNormals.push_back(rawVerticesNormals.at((num * 3) - 3 + i));
						}
					}
					else if (iNumSlashes == 2) //   v/vt/vn is the line
					{
						// pick up the normal index
						parser >> num;

						for (int i = 0; i < 3; i++) //VN
							verticesNormals.push_back(rawVerticesNormals.at((num * 3) - 3 + i));
					}
					else
					{
						// no slashes so ready to read next face value
					}
				}
			}
		}
	}

	finalVertices.clear();

	V3D v3d;
	int k = -1;
	for (auto & i : vertices) {
		k++;
		if (k == 0) {
			v3d.setX(i);
		}

		if (k == 1) {
			v3d.setY(i);
		}

		if (k == 2) {
			v3d.setZ(i);
			finalVertices.push_back(v3d);
			k = -1;
		}
	}

	modelfile.close();
}

int OBJ_Reader::GetNextSlashes(std::istringstream& parserIn)
{
	int slashes = 0;
	int c = parserIn.peek();

	while (parserIn.peek() == 0x2f)
	{
		slashes++;
		parserIn.get();
	}
	return slashes;
}

std::vector<V3D> OBJ_Reader::vertices()
{
	return finalVertices;
}