#pragma once

#include <iostream>
#include "Utils.h"
#include "SceneObjects.h"

//Adding this like renia asked
#ifdef _WIN32

#include "glut.h"
#pragma comment(lib, "glut32.lib")

#else

#ifdef __APPLE__

#include <GLUT / glut.h>

#else

#include <GL/glut.h>

#endif

#endif

//The main  func to run my beautiful scene
void RunScene(int argc, char** argv);
