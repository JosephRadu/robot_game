#pragma once

/**
* @Author	Joseph Radu
* @date		1st November 2016
* @brief	Playing application state.
*
*/

#include "base_app_state.h"
#include <Windows.h>
#include <fstream>
#include <sstream>
#include "resource.h"

enum _Camera { C_OVERVIEW = 0, C_ROBOT_BEHIND = 1, C_ROBOT_FRONT = 2 };

class App_State_Playing : public Base_App_State
{
private:
	bool bPaused;

	Drawable cube;

	Robot *theRobot;
	int iCameraSelected;

	Camera camera[3];

	// Bespoke Functions

	void TogglePause();

	void SwitchToCamera(int i);


	void input(char s);

	Robot robot();

	//void OBJRead(std::string s);

	//int GetNextSlashes(istringstream& parserIn);

	void UpdateCamera();

public:
	/*!
	\ brief Constructor.
	*/
	App_State_Playing();

	/*!
	\ brief Initialise state.
	*/
	void Init();

	/*!
	\ brief Update state.
	*/
	void Update(float dt);

	void ExitState();

	/*!
	\ brief Pass user input.
	\param event is a reference to an event.
	\param v2dMousePosIn is a reference to the 2D coordinates of the mouse position.
	*/
	void WindowProc(WPARAM& wParam, LPARAM& lParam);

	void SetupProjection(int width, int height);
};