#include "app_state_playing.h"

void App_State_Playing::SetupProjection(int width, int height)
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

void App_State_Playing::UpdateCamera()
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


	V3D v3dCP(camera[iCameraSelected].Position());
	V3D v3dCD(camera[iCameraSelected].Direction());

	gluLookAt(
		v3dCP.x(), v3dCP.y(), v3dCP.z(),
		v3dCP.x() + v3dCD.x(), v3dCP.y() + v3dCD.y(), v3dCP.z() + v3dCD.z(),
		0.0f, 1.0f, 0.0f);


	glMatrixMode(GL_MODELVIEW);				// set modelview matrix
	glLoadIdentity();						// reset modelview matrix
}

void App_State_Playing::TogglePause() {
	if (bPaused) {
		bPaused = false;
	}
	else {
		bPaused = true;
	}
}

void App_State_Playing::SwitchToCamera(int i)
{
	iCameraSelected = i;
	input('0');
	UpdateCamera();
}


void App_State_Playing::input(char s) {

	if (bPaused) {
		return;
	}

	/*
	if (iCameraSelected == C_ROBOT_BEHIND || iCameraSelected == C_ROBOT_FRONT)
	{
	if (s == 38 || s == 37 || s == 39 || s == 40 || s == 84 || s == 71) {
	camera[iCameraSelected].Move(s);
	}
	}
	*/

	if (iCameraSelected == C_ROBOT_BEHIND) {
		camera[iCameraSelected].Direction().set(theRobot->Direction());
		camera[iCameraSelected].Position().set(
			theRobot->Position().x() - (theRobot->Direction().x() * 10),
			theRobot->Position().y() - (theRobot->Direction().y() * 10),
			theRobot->Position().z() - (theRobot->Direction().z() * 10)
		);
	}

	if (iCameraSelected == C_ROBOT_FRONT) {
		camera[iCameraSelected].Direction().set(theRobot->Direction());
		camera[iCameraSelected].Position().set(
			theRobot->Position().x() + (theRobot->Direction().x() * 10),
			theRobot->Position().y() + (theRobot->Direction().y() * 10),
			theRobot->Position().z() + (theRobot->Direction().z() * 10)
		);
	}






	if (s != 87)
	{
		theRobot->AnimationMove(0);
		//theRobot->Move(0);
	}



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
	default:
		break;
	}

	UpdateCamera();

}

/*

void Application::OBJRead(std::string s)
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

int Application::GetNextSlashes(istringstream& parserIn)
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
*/


void App_State_Playing::ExitState()
{
	delete theRobot;
}

Robot App_State_Playing::robot()
{
	return *theRobot;
}



App_State_Playing::App_State_Playing()
{
}

void App_State_Playing::Init()
{
	theRobot = new Robot;

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	bPaused = false;

	cube.Init_Plane();
	cube.Position().setZ(0);
	cube.Position().setX(0);
	cube.Position().setY(-12);
	cube.Rotation().setY(1);
	//cube.SetAngle(45);
	cube.Scale().setX(100);
	cube.Scale().setY(100);
	cube.Scale().setZ(100);

	//OBJRead("teapot.obj");
	iCameraSelected = C_OVERVIEW;

	camera[0].Position().set(0, 20, 0);
	camera[0].Direction().set(-0.67, -1, -0.75);
	camera[0].Rotation().set(-4, -4, 0);

	camera[1].Direction().set(0, 0, 1);
	camera[1].Position().set(-20, 0, -30);

	camera[2].Direction().set(0, 0, 1);
	camera[2].Position().set(20, 0, 30);

	theRobot->Direction().set(0, 0, 0);
	theRobot->Rotation().set(0, 0, 0);
	theRobot->Position().set(-20, 0, -20);

	//camera.SetAngle(0);
	//camera.Position().set(0, 0, -10);
	UpdateCamera();
}

void App_State_Playing::Update(float dt)
{

	if (bPaused) {
		return;
	}

	theRobot->AnimationPrepare(dt);

	// clear screen and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	cube.Draw();

	theRobot->DrawRobot();		// draw the robot


}

void App_State_Playing::WindowProc(WPARAM& wParam, LPARAM& lParam)
{
	int fwKeys;
	LPARAM keyData;

	// dispatch messages
	switch (uMsg)
	{
	case WM_COMMAND:
		fwKeys = (int)wParam;    // virtual-key code 
		keyData = lParam;          // key data 

		switch (fwKeys)
		{
		case ID_MENU_LOL:
			//TogglePause();
			break;

		case ID_CAMERA_OVERVIEW:
			//SwitchToCamera(C_OVERVIEW);
			break;

		case ID_CAMERA_ROBOTBEHIND:
			//SwitchToCamera(C_ROBOT_BEHIND);
			break;

		case ID_CAMERA_ROBOTFRONT:
			//SwitchToCamera(C_ROBOT_FRONT);
			break;

		default:
			break;
		}
		break;

	case WM_ACTIVATEAPP:		// activate app
		break;

	case WM_LBUTTONDOWN:		// left mouse button
		break;

	case WM_RBUTTONDOWN:		// right mouse button
		break;

	case WM_MOUSEMOVE:			// mouse movement
		break;

	case WM_LBUTTONUP:			// left button release
		break;

	case WM_RBUTTONUP:			// right button release
		break;

	case WM_KEYUP:
		input('0');
		break;

	case WM_KEYDOWN:
		fwKeys = (int)wParam;    // virtual-key code 
		keyData = lParam;          // key data 
		input((char)wParam);
		break;


	default:
		break;
	}

}