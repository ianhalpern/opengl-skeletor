#include "BMPLoader/BMPLoader.h"

string BMPTextures_dir = "BMPTextures/";

GLuint groundTexture, roadTexture;


GLuint loadBMPTexture(string file) {
	BMPClass bmp;
	BMPLoad(BMPTextures_dir+file,bmp);
	GLuint texture;
	// allocate a texture name
	glGenTextures( 1, &texture );
	
	// select our current texture
	glBindTexture( GL_TEXTURE_2D, texture );
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,0,3,bmp.width,bmp.height,0,GL_RGB,GL_UNSIGNED_BYTE,bmp.bytes);
	
	return texture;
}


void loadTextures() {
	glEnable(GL_TEXTURE_2D);
	//groundTexture = loadBMPTexture("checkers.bmp");
	groundTexture = loadBMPTexture("grass41.bmp");
	roadTexture = loadBMPTexture("pavement1.bmp");
	glDisable(GL_TEXTURE_2D);
}
