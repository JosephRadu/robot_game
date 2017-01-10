#include "obj_reader.h"

OBJ_Reader::OBJ_Reader()
{

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