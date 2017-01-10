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

	
	if (iCameraSelected == C_OVERVIEW )
	{
		if (s == 38 || s == 37 || s == 39 || s == 40 || s == 84 || s == 71) {
			camera[iCameraSelected].Move(s);
		}
	}
	

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

	
	
	drawable = new Drawable;
	drawable->Init_Plane();
	drawable->Position().setZ(0);
	drawable->Position().setX(0);
	drawable->Position().setY(-12);
	drawable->Rotation().setY(1);
	drawable->Scale().setX(100);
	drawable->Scale().setZ(100);
	drawable->Colour().set(0.5, 0.5, 0.25);

	drawables.push_back(drawable);

	drawable = new Drawable;
	drawable->Init_Plane();
	drawable->Position().setZ(-100);
	drawable->Position().setX(0);
	drawable->Position().setY(-12);
	drawable->Rotation().setX(1);
	drawable->SetAngle(90);
	drawable->Scale().setX(100);
	drawable->Scale().setZ(10);
	drawable->Colour().set(0.25, 0.3, 0.25);

	drawables.push_back(drawable);

	drawable = new Drawable;
	drawable->Init_Plane();
	drawable->Position().setZ(0);
	drawable->Position().setX(-100);
	drawable->Position().setY(-12);
	drawable->Rotation().setZ(1);
	drawable->SetAngle(270);
	drawable->Scale().setX(10);
	drawable->Scale().setZ(100);
	drawable->Colour().set(0.4, 0.3, 0.3);

	drawables.push_back(drawable);

	obj_reader->Read("teapot.obj");

	drawable = new Drawable;
	drawable->Vertices() = obj_reader->vertices();
	drawable->Position().setZ(0);
	drawable->Position().setX(0);
	drawable->Position().setY(0);
	drawable->Rotation().setY(1);
	drawable->Scale().setX(1);
	drawable->Scale().setZ(1);
	drawable->Colour().set(0.5, 0.5, 0.25);

	drawables.push_back(drawable);



	//OBJRead("teapot.obj");
	iCameraSelected = C_OVERVIEW;

	camera[0].Position().set(0, 20, 0);
	camera[0].Direction().set(-0.67, -1, -0.75);
	camera[0].Rotation().set(-4, -4, 0);

	camera[1].Direction().set(0, 0, 1);
	camera[1].Position().set(-20, 0, -30);

	camera[2].Direction().set(0, 0, 1);
	camera[2].Position().set(20, 0, 30);

	theRobot->Direction().set(0, 0, 0.01);
	theRobot->Rotation().set(0, 0, 0);
	theRobot->Position().set(-20, 0, -20);

	//camera.SetAngle(0);
	//camera.Position().set(0, 0, -10);
	UpdateCamera();
}



void App_State_Playing::Update(float dt)
{
	if (!bPaused) {
		theRobot->SetTimeScale(dt);
		camera[0].SetTimeScale(dt);
		camera[1].SetTimeScale(dt);
		camera[2].SetTimeScale(dt);
		theRobot->AnimationPrepare(dt);
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto & i : drawables) {
		i->Draw();
	}

	theRobot->DrawRobot();
}

void App_State_Playing::WindowProc(int iWindowProc, WPARAM& wParam, LPARAM& lParam)
{
	int fwKeys;
	LPARAM keyData;

	// dispatch messages
	switch (iWindowProc)
	{
	case APP_WM_COMMAND:
		fwKeys = (int)wParam;    // virtual-key code 
		keyData = lParam;          // key data 

		switch (fwKeys)
		{
		case ID_MENU_LOL:
			TogglePause();
			break;

		case ID_CAMERA_OVERVIEW:
			SwitchToCamera(C_OVERVIEW);
			break;

		case ID_CAMERA_ROBOTBEHIND:
			SwitchToCamera(C_ROBOT_BEHIND);
			break;

		case ID_CAMERA_ROBOTFRONT:
			SwitchToCamera(C_ROBOT_FRONT);
			break;

		default:
			break;
		}
		break;

	case APP_WM_KEYUP:
		input('0');
		break;

	case APP_WM_KEYDOWN:
		fwKeys = (int)wParam;    // virtual-key code 
		keyData = lParam;          // key data 
		input((char)wParam);
		break;

	default:
		break;
	}

}