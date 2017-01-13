#pragma once

/**
* @Author	Joseph Radu
* @date		1st November 2016
* @brief	Playing application state.
*
*/

#include <Windows.h>
#include <iostream>

using namespace std;

#include "base_app_state.h"
#include "resource.h"
#include "obj_reader.h"
#include "keyboard.h"
#include "json.hpp"
#include "drawable.h"
#include "camera.h"
#include "Robot.h"

class Robot;
enum _Camera { C_OVERVIEW = 0, C_ROBOT_BEHIND = 1, C_ROBOT_FRONT = 2 };

class App_State_Playing : public Base_App_State
{
private:

	using json = nlohmann::json; // JSON reader.

	bool bPaused;

	vector <Drawable*> drawables;

	Robot *theRobot;
	Drawable *drawable;
	OBJ_Reader obj_reader;
	Keyboard keyboard;
	json j;

	int iCameraSelected;

	Camera camera[3];

	GLuint image;

	// Bespoke Functions
	void TogglePause();
	void SwitchToCamera(int i);
	void input(string s);
	Robot robot();
	void UpdateCamera();

public:
	/*!
	\ brief Default constructor..
	*/
	App_State_Playing();

	/*!
	\ brief Initialise state.
	*/
	void Init();

	/*!
	\ brief Update state.
	\ param float timescale
	*/
	void Update(float dt);

	/*!
	\ brief Exit the state and delete anything we might need to.
	*/
	void ExitState();

	/*!
	\ brief Pass any events that have happened on the window.
	\ param int iWIndowProc
	\ param WPARAM
	\ param LPARAM
	*/
	void WindowProc(int iWindowProc, WPARAM& wParam, LPARAM& lParam);

	/*!
	\ brief Pass the size of the window.
	\ param int width
	\ param int height
	*/
	void SetupProjection(int width, int height);
};