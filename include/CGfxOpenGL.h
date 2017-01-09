#ifndef __GL_COMPONENT
#define __GL_COMPONENT

#include "manager_app_state.h"

class Robot;

using namespace std;

class Application
{
private:
	Manager_App_State manager_app_state; //!< Controls the current state of the app.

public:
	Application();
	virtual ~Application();

	/*!
	\brief Initialise the managers.
	*/
	void Init();

	/*!
	\ brief Start the application by setting the correct state. To be done after init().
	*/
	void Start();

	/*!
	\ brief Updates the application.
	\ param float framerate?
	*/
	void Update(float dt);

	void WindowProc(UINT& uMsg, WPARAM& wParam, LPARAM& lParam);
};

#endif