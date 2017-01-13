#pragma once

/**
* @Author	Joseph Radu
* @date		1st November 2016
* @brief	Base of application states.
*
*/

#include <math.h>
#include <gl/gl.h>
#include <gl/glu.h>

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

	/*!
	\ brief Exit the state and delete anything we might need to.
	*/
	virtual void ExitState() = 0;

	/*!
	\ brief Pass any events that have happened on the window.
	\ param int iWIndowProc
	\ param WPARAM
	\ param LPARAM
	*/
	virtual void WindowProc(int iWindowProc, WPARAM& wParam, LPARAM& lParam) = 0;

	/*!
	\ brief Pass the size of the window.
	\ param int width
	\ param int height
	*/
	virtual void SetupProjection(int width, int height) = 0;


};