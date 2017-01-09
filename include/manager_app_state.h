#pragma once

/**
* @Author	Joseph Radu
* @date		1st November 2016
* @brief	Manager of application states.
*
*/

#include "app_state_playing.h"
#include <unordered_map>
#include <memory>
#include <windows.h>

/*!
\ Possible states the application can have. This should correlate with all the app state classes.
*/
enum appState {SPLASH, PLAYING, PAUSED, EXIT};

class Manager_App_State
{
private:
	std::unordered_map<appState, std::unique_ptr <Base_App_State>> states; //!< Store states against appState enum.
	appState appStateCurrent; //!< Current state that is handled.
public:
	/*!
	\ brief Constructor.
	*/
	Manager_App_State();

	/*!
	\ brief Create all states.
	*/
	void StateCreateStates();

	/*!
	\ brief Switch state to use.
	\ param state enum to use.
	*/
	void StateSwitch(appState state);

	/*!
	\ brief Initialise state provided.
	\ param state to be initialised.
	*/
	void StateInit(appState state);

	/*!
	\brief Draws everything necessary to the screen from state selected.
	\param window is a reference to a render window.
	*/
	void Update(float dt);

	/*!
	\brief 
	\param 
	*/
	void WindowProc(UINT& uMsg, WPARAM& wParam, LPARAM& lParam);

	/*!
	\ brief Update current state selected.
	*/
	void Update();
};
