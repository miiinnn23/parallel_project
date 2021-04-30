#ifndef TextureH
#define TextureH

#include <Windows.h>
#include "..\usr\include\GL\freeglut.h"
#include <string>

class Texture {

public:
	Texture::Texture();
	static GLuint loadTexture(char * fileName);

private:
	static GLuint loadTGAFile(char * filename);
	static bool hasEnding (std::string const &fullString, std::string const &ending);
};

#endif