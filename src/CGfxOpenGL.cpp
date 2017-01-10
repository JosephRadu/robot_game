#ifdef _WINDOWS
#include <windows.h>
#endif
#include "CGfxOpenGL.h"


// disable implicit float-double casting
#pragma warning(disable:4305)

Application::Application()
{
	manager_app_state.StateCreateStates();
}

Application::~Application()
{

}

void Application::Init()
{
	manager_app_state.StateSwitch(PLAYING);
	manager_app_state.StateInit(PLAYING);
}

void Application::Update(float dt)
{
	manager_app_state.Update(dt);
}


void Application::WindowProc(WPARAM& wParam, LPARAM& lParam)
{
	manager_app_state.WindowProc(wParam, lParam);
}

Manager_App_State&  Application::GetStateManager()
{
	return manager_app_state;
}