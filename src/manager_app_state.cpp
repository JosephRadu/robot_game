/**
* @Author	Joseph Radu
* @date		1st November 2016
* @brief	Manager of application states.
*
*/

#include "manager_app_state.h"

Manager_App_State::Manager_App_State()
{

}

void Manager_App_State::StateCreateStates()
{
	states[PLAYING] = std::make_unique<App_State_Playing>();
}

void Manager_App_State::StateSwitch(appState state)
{
	appStateCurrent = state;
}

void Manager_App_State::StateInit(appState state)
{
	states[state]->Init();
}

void Manager_App_State::WindowProc(int iWindowProc, WPARAM& wParam, LPARAM& lParam)
{
	states[appStateCurrent]->WindowProc(iWindowProc, wParam, lParam);
}

void Manager_App_State::Update(float dt)
{
	states[appStateCurrent]->Update(dt);
}

std::unique_ptr <Base_App_State>&  Manager_App_State::CurrentState()
{
	return states[appStateCurrent];
}