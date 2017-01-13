#include "app_state_playing.h"

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

	ifstream i("data/objects.json");
	i >> j;

	for (json::iterator it = j.begin(); it != j.end(); ++it) {

		size_t found = it.key().find("drawable");
		if (found != std::string::npos) {
			drawable = new Drawable;

			if (j[it.key()]["type"] == "plane")
			{
				drawable->Init_Plane();
			}

			else if (j[it.key()]["type"] == "obj")
			{
				obj_reader.Read(j[it.key()]["obj"]);
				drawable->Vertices() = obj_reader.vertices();
			}

			drawable->Position().setX(j[it.key()]["position"][0]);
			drawable->Position().setY(j[it.key()]["position"][1]);
			drawable->Position().setZ(j[it.key()]["position"][2]);

			drawable->Scale().setX(j[it.key()]["scale"][0]);
			drawable->Scale().setY(j[it.key()]["scale"][1]);
			drawable->Scale().setZ(j[it.key()]["scale"][2]);

			drawable->Rotation().setX(j[it.key()]["rotation"][0]);
			drawable->Rotation().setY(j[it.key()]["rotation"][1]);
			drawable->Rotation().setZ(j[it.key()]["rotation"][2]);

			drawable->Colour().setX(j[it.key()]["colour"][0]);
			drawable->Colour().setY(j[it.key()]["colour"][1]);
			drawable->Colour().setZ(j[it.key()]["colour"][2]);

			drawable->SetAngle(j[it.key()]["angle"]);
			drawables.push_back(drawable);
		}
	}

	ifstream ii("data/keybindings.json");
	ii >> j;

	for (json::iterator it = j.begin(); it != j.end(); ++it) {
		keyboard.AddKeyBinding(it.key(), it.value());
	}

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

	UpdateCamera();
}


void App_State_Playing::Update(float dt)
{
	if (!bPaused) {
		theRobot->Update(dt);
		camera[0].Update(dt);
		camera[1].Update(dt);
		camera[2].Update(dt);
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto & i : drawables) {
		i->Draw();
	}

	theRobot->DrawRobot();
}

void App_State_Playing::WindowProc(int iWindowProc, WPARAM& wParam, LPARAM& lParam)
{
	stringstream ss;
	string s;
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
		input("0");
		break;

	case APP_WM_KEYDOWN:
		fwKeys = (int)wParam;    // virtual-key code 
		keyData = lParam;          // key data 
		ss << (char)wParam;
		ss >> s;

		input(s);
		break;

	default:
		break;
	}

}

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

	V3D v3dCP(camera[iCameraSelected].Position());
	V3D v3dCD(camera[iCameraSelected].Direction());

	gluLookAt(
		v3dCP.x(), v3dCP.y(), v3dCP.z(),
		v3dCP.x() + v3dCD.x(), v3dCP.y() + v3dCD.y(), v3dCP.z() + v3dCD.z(),
		0.0f, 1.0f, 0.0f);

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
	input("0");
	UpdateCamera();
}

void App_State_Playing::input(std::string s) {

	if (bPaused) {
		return;
	}

	if (s == "0") {
		theRobot->Move(0);
		theRobot->AnimationMove(0);
	}

	if (s == keyboard.GetKeyBinding("MOVEMENT_ROBOT_FORWARD")){
		theRobot->AnimationMove(1);
		theRobot->Move(1);
	}
	else if (s == keyboard.GetKeyBinding("MOVEMENT_ROBOT_LEFT")) {
		theRobot->rotate(4.0f);
	}else if (s == keyboard.GetKeyBinding("MOVEMENT_ROBOT_RIGHT")) {
		theRobot->rotate(-4.0f);
	}else if (s == keyboard.GetKeyBinding("MOVEMENT_ROBOT_BACKWARD")) {
		theRobot->Move(0);
		theRobot->AnimationMove(0);
	}

	if (iCameraSelected == C_OVERVIEW){
		if (s == keyboard.GetKeyBinding("MOVEMENT_CAMERA_FORWARD"))
		{
			camera[iCameraSelected].Move(C_FORWARD);
		}else if (s == keyboard.GetKeyBinding("MOVEMENT_CAMERA_BACKWARD")){
			camera[iCameraSelected].Move(C_BACKWARD);
		}
		else if (s == keyboard.GetKeyBinding("MOVEMENT_CAMERA_LEFT")) {
			camera[iCameraSelected].Move(C_LEFT);
		}
		else if (s == keyboard.GetKeyBinding("MOVEMENT_CAMERA_RIGHT")) {
			camera[iCameraSelected].Move(C_RIGHT);
		}
		else if (s == keyboard.GetKeyBinding("MOVEMENT_CAMERA_UP")) {
			camera[iCameraSelected].Move(C_UP);
		}
		else if (s == keyboard.GetKeyBinding("MOVEMENT_CAMERA_DOWN")) {
			camera[iCameraSelected].Move(C_DOWN);
		}
	}
	
	if (iCameraSelected == C_ROBOT_BEHIND) {
		camera[iCameraSelected].Direction().set(theRobot->Direction());
		camera[iCameraSelected].Position().set(
			theRobot->Position().x() - (theRobot->Direction().x() * 1000),
			theRobot->Position().y() - (theRobot->Direction().y() * 1000),
			theRobot->Position().z() - (theRobot->Direction().z() * 1000)
		);
	}

	if (iCameraSelected == C_ROBOT_FRONT) {
		camera[iCameraSelected].Direction().set(theRobot->Direction());
		camera[iCameraSelected].Position().set(
			theRobot->Position().x() + (theRobot->Direction().x() * 100),
			theRobot->Position().y() + (theRobot->Direction().y() * 100),
			theRobot->Position().z() + (theRobot->Direction().z() * 100)
		);
	}

	UpdateCamera();
}

void App_State_Playing::ExitState()
{
	delete theRobot;
	delete drawable;

}

Robot App_State_Playing::robot()
{
	return *theRobot;
}
