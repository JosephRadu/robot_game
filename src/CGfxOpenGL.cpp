#ifdef _WINDOWS
#include <windows.h>
#endif
#include "CGfxOpenGL.h"


// disable implicit float-double casting
#pragma warning(disable:4305)

CGfxOpenGL::CGfxOpenGL()
{
}

CGfxOpenGL::~CGfxOpenGL()
{
}

bool CGfxOpenGL::Init()
{
	theRobot = new Robot;

	rotationAngle = 0.0f;

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	bPaused = false;

	
	cube.Init_Plane();
	cube.Position().setZ(-20);
	cube.Position().setX(0);
	cube.Position().setY(-20);
	cube.Rotation().setY(1);
	//cube.SetAngle(45);
	cube.Scale().setX(100);
	cube.Scale().setY(100);
	cube.Scale().setZ(100);

	//OBJRead("teapot.obj");

	camera.SetAngle(0);
	camera.Position().set(0, 0, 0);
	

	return true;
}

void CGfxOpenGL::OBJRead(std::string s)
{
	fstream modelfile(s, std::ios_base::in);
	int iNumValuesInLine = 0;
	float num;
	string text;
	string line;
	string name;

	// Raw data
	vector<float> rawVertices; //v
	vector<float> rawVerticesTextures; //vt
	vector<float> rawVerticesNormals; //vn

	// Actual ones we use for openGL.
	vector<float> vertices; //f
	vector<int> verticesTextures;
	vector<int> verticesNormals;

	if (modelfile.is_open())
	{
		while (getline(modelfile, line))
		{
			istringstream parser;
			parser.str(line);
			string character;

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
	V3D v3d;
	cube.Vertices().clear();
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
			cube.Vertices().push_back(v3d);
			k = -1;
		}
	}

	//std::reverse(cube.Vertices().begin(), cube.Vertices().end());

	modelfile.close();
}

int CGfxOpenGL::GetNextSlashes(istringstream& parserIn)
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

Robot CGfxOpenGL::robot()
{
	return *theRobot;
}

bool CGfxOpenGL::Shutdown()
{
	delete theRobot;

	return true;
}

void CGfxOpenGL::SetupProjection(int width, int height)
{
	if (height == 0)					// don't want a divide by zero
	{
		height = 1;
	}

	glViewport(0, 0, width, height);		// reset the viewport to new dimensions
	glMatrixMode(GL_PROJECTION);			// set projection matrix current matrix
	glLoadIdentity();						// reset projection matrix
											// calculate aspect ratio of window
	gluPerspective(90.0f, (GLfloat)width / (GLfloat)height, 1.0f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);				// set modelview matrix
	glLoadIdentity();						// reset modelview matrix

	m_windowWidth = width;
	m_windowHeight = height;
}

void CGfxOpenGL::UpdateCamera()
{
	if (m_windowHeight == 0)					// don't want a divide by zero
	{
		m_windowHeight = 1;
	}



	glViewport(0, 0, m_windowWidth, m_windowHeight);	// reset the viewport to new dimensions
	glMatrixMode(GL_PROJECTION);			// set projection matrix current matrix
	glLoadIdentity();						// reset projection matrix

	// calculate aspect ratio of window
	gluPerspective(90.0f, (GLfloat)m_windowWidth / (GLfloat)m_windowHeight, 1.0f, 1000.0f);

	//glTranslatef(camera.Position().x(), camera.Position().y(), camera.Position().z());

	//glRotatef(camera.Angle(), camera.Rotation().x(), camera.Rotation().y(), camera.Rotation().z());	// rotate the drawable on its y-axis

	//float angle = camera.Angle();

	//float x = sin(PI * angle) * 1;
	//float z = cos(PI * angle) * 1;

	//camera.Position().set(camera.Position().x() + x, camera.Position().y(), camera.Position().z() + z);

	gluLookAt(x, y, z,
		x + lx, y + ly, z + lz,
		0.0f, 1.0f, 0.0f);

	/*
	gluLookAt(camera.Position().x(), camera.Position().y(), camera.Position().z(),
		camera.Position().x() + x, camera.Position().y(), camera.Position().z() + z,
		0, -1, 0);
		*/
		
	

	glMatrixMode(GL_MODELVIEW);				// set modelview matrix
	glLoadIdentity();						// reset modelview matrix
}

void CGfxOpenGL::Prepare(float dt)
{
	if (bPaused) {
		return;
	}

	theRobot->AnimationPrepare(dt);
}

void CGfxOpenGL::Render()
{
	// clear screen and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	cube.Draw();

	theRobot->DrawRobot();		// draw the robot
}

void CGfxOpenGL::input(char s) {

	if (bPaused) {
		return;
	}

	theRobot->AnimationMove(0);
	UpdateCamera();
	switch (s)
	{
	// A
	case 65:
		theRobot->rotate(4.0f);
		break;
	// D
	case 68:
		theRobot->rotate(-4.0f);
		break;
	// W
	case 87:
		theRobot->AnimationMove(1);
		theRobot->Move(1);
		break;
	// S
	case 83:
		theRobot->Move(0);
		break;
	// Camera look up
	case 38:
		angle += 0.04f;
		ly = tan(angle);

		break;
	// Camera look left
	case 37:
		angle -= 0.08f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	// Camera look right
	case 39:
		angle += 0.08f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	// Camera look down
	case 40:
		angle -= 0.04f;
		ly = tan(angle);
		break;
	// Camera forward
	case 84:
		x += lx * 1.2;
		y += ly * 1.2;
		z += lz * 1.2;
		break;

	// Camera backwards
	case 71:
		x -= lx * 1.2;
		y -= ly * 1.2;
		z -= lz * 1.2;
		break;

	default:
		break;
	}

}

void CGfxOpenGL::TogglePause() {
	if (bPaused) {
		bPaused = false;
	}
	else {
		bPaused = true;
	}
}