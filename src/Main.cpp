#include "Main.h"
#ifndef GL_VERSION_2_1
#define GL_VERSION_2_1 1
// GL 2.1 definitions
#endif
#ifndef GL_VERSION_3_0
#define GL_VERSION_3_0 1
// GL 3.0 definitions
#endif
#ifndef GL_VERSION_3_1
#define GL_VERSION_3_1 1
// GL 3.1 definitions
#endif
int main(int argc, char** argv)
{
	RunScene(argc, argv);
	return 0;
}