#pragma once
#include "renderlib_api.h"
#include <GLFW/glfw3.h>


/** \class	Display
	\brief	This class represents the display in which the gameplay is rendered to. 
			Can be windowed or fullscreen.



*/
#ifdef _WIN32
class RENDERLIB_API Display {
#endif
class Display {
public:
	Display(int w, int h, bool fullscreen);
	virtual ~Display(); 
	virtual void swapBuffers() = 0;
	virtual void pollEvents() = 0;

protected:
	int _screenWidth;
	int _screenHeight;


};

#ifdef _WIN32
class RENDERLIB_API GLFWDisplay : public Display {
#endif
class GLFWDisplay : public Display {

public:
	GLFWDisplay(int w, int h, bool fullscreen);
	virtual ~GLFWDisplay();
	virtual void swapBuffers();
	virtual void pollEvents();

private:
	GLFWwindow* _window;
};


