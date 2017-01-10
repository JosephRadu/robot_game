#pragma once

/**
* @Author	Joseph Radu
* @date		1st November 2016
* @brief	Base of application states.
*
*/

#include <math.h>
#include "drawable.h"
#include "camera.h"
#include "Robot.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include <windows.h>

#define PI 3.14159
#define TWO_PI PI*2.0
#define HALF_PI PI/2.0

enum _WindowProc { APP_WM_COMMAND, APP_WM_KEYDOWN, APP_WM_KEYUP};

class Base_App_State
{
private:

protected:
	int m_windowWidth;
	int m_windowHeight;
public:
	/*!
	\brief Initialise the state.
	*/
	virtual void Init() = 0;

	/*!
	\brief Draws everything necessary to the screen.
	\param window is a reference to a render window.
	*/
	virtual void Update(float dt) = 0;

	virtual void ExitState() = 0;

	virtual void WindowProc(int iWindowProc, WPARAM& wParam, LPARAM& lParam) = 0;

	virtual void SetupProjection(int width, int height) = 0;


};