/************************************************
By Ian Halpern -- 2007
*************************************************/

#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <cstdarg>
#include <string>
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define FPS 40
#define KEY_LEFT 100
#define KEY_UP 101
#define KEY_RIGHT 102
#define KEY_DOWN 103
#define KEY_ESC 27

float* hexColor(int r, int g, int b, float a) {
	// Converts a hex color representation to a glcolor3fv vector
	// Nice if your used to web colors!!
	float *rgba = new float[4];
	rgba[0] = ((float)r)/255.0f;
	rgba[1] = ((float)g)/255.0f;
	rgba[2] = ((float)b)/255.0f;
	rgba[3] = a;
	return rgba;
}

// Custom glut functions
void (*_custom_display)() = NULL;
void (*_custom_2DForeground_display)() = NULL;
void (*_custom_keyboard)(unsigned char, int, int) = NULL;
void (*_custom_multikey)(bool*, bool*) = NULL;
void (*_custom_window_special_key)(int, int, int) = NULL;
void (*_custom_reshape)(int, int) = NULL;
void (*_custom_mouseHandler)(int, int, int, int) = NULL;

class MyGlut {
/************************************************
MyGlut specifically holds my favorite gl and glut
setup in a nice reusable class
*************************************************/
	public:
		MyGlut(int, char**, char*);						// constructor;
		void attach_display_func(void (*)());
		void attach_2DForeground_display_func(void (*)());
		void attach_keyboard_func(void (*)(unsigned char, int, int));
		void attach_multikey_func(void (*)(bool*, bool*));
		void attach_window_special_key_func(void (*)(int, int, int));
		void attach_reshape_func(void (*)(int, int));
		void attach_mouse_func(void (*)(int, int, int, int));
		static int Printf (const char *format, ...);
		void start();
		static int fps;
		static bool pressedKeys[256];
		static bool pressedSpecialKeys[256];


	private:
		void _initGL();
		static void _reshape(int, int);
		static void _display();
		static void _timer(int);
		static void _keyboardHandler(unsigned char, int, int);
		static void _keyboardUpHandler(unsigned char, int, int);
		static void _mouseHandler(int, int, int, int);
		static void _motionHandler (int, int);
		static void _window_special_key(int, int, int);
		static void _window_special_key_up(int, int, int);
		static void _update_fps();
		static double _currTime;
		static double _prevTime;
		static int _currFrame;
};

MyGlut::MyGlut(int argc, char** argv, char* name){
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
	glutInitWindowSize (640, 480);
	glutInitWindowPosition (600, 300);
	glutCreateWindow (name);

	_initGL ();

	glutDisplayFunc(&_display);
	glutReshapeFunc(&_reshape);
	glutKeyboardFunc(&_keyboardHandler);
	glutKeyboardUpFunc(&_keyboardUpHandler);
	glutMouseFunc(&_mouseHandler);
	glutMotionFunc(&_motionHandler);
	glutSpecialFunc(&_window_special_key);
	glutSpecialUpFunc(&_window_special_key_up);

	_timer(0);
}

double MyGlut::_currTime = 0;
double MyGlut::_prevTime = 0;
int    MyGlut::fps = FPS;
int    MyGlut::_currFrame = 0;
bool   MyGlut::pressedKeys[256];
bool   MyGlut::pressedSpecialKeys[256];

void MyGlut::start() {
	// this function must be called last in int main() {}
	glutMainLoop();
}

void MyGlut::_initGL() {
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel(GL_SMOOTH);				// Enable Smooth Shading
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f);			// Black Background
	glClearDepth(1.0f);					// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);				// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);					// The Type Of Depth Testing To Do
//	glEnable(GL_POLYGON_SMOOTH);				// Anti-alias Polygons
//	glEnable(GL_LINE_SMOOTH);				// Anti-alias Lines
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
}

void MyGlut::_reshape(int w, int h) {
	if (h==0) h=1;						// Prevent A Divide By Zero By

	glViewport(0,0,w,h);					// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);				// Select The Projection Matrix
	glLoadIdentity();					// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window and sets the field of view, near, and far view
	// This is really just calling glFrustum
	gluPerspective(45.0f,(GLfloat)w/(GLfloat)h,0.1f,10000.0f);

	glMatrixMode(GL_MODELVIEW);				// Select The Modelview Matrix
	glLoadIdentity();

	if( (*_custom_reshape) != NULL ) {
		(*_custom_reshape)(w, h);
	}
}

void MyGlut::_update_fps() {
	_currFrame++;
	_currTime = glutGet (GLUT_ELAPSED_TIME) * 0.001f;
	if( (_currTime - _prevTime) >= 1.0 ) {
		fps = _currFrame;
		_currFrame = 0;
		_prevTime = _currTime;
	}
}

void MyGlut::_timer(int value) {
	_update_fps();

	if((*_custom_multikey) != NULL) {
		(*_custom_multikey)(pressedKeys, pressedSpecialKeys);
	}

	glutPostRedisplay();
	glutTimerFunc(1000/FPS, &_timer, 0);
}

void MyGlut::_display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	if( (*_custom_display) != NULL ) {
		(*_custom_display)();
	}

	if( (*_custom_2DForeground_display) != NULL ) {
		int width = glutGet (GLUT_WINDOW_WIDTH);
		int height = glutGet (GLUT_WINDOW_HEIGHT);

		glMatrixMode (GL_PROJECTION);
		glPushMatrix ();

		glLoadIdentity ();
		// since this surface is 2D we use orthographic projection
		glOrtho (0, width, 0, height, -1.0f, 1.0f);

		glMatrixMode (GL_MODELVIEW);
		glLoadIdentity ();


		(*_custom_2DForeground_display)();


		glMatrixMode (GL_PROJECTION);
		glPopMatrix ();
		glMatrixMode (GL_MODELVIEW);
	}

	glutSwapBuffers();
}

int MyGlut::Printf (const char *format, ...) {
	// Stole from David Henry, simulates printf, brilliant!!!!
	char buffer[1024];
	std::va_list arg;
	int ret;

	// Format the text
	va_start (arg, format);
	ret = std::vsnprintf (buffer, sizeof (buffer), format, arg);
	va_end (arg);

	// Print it
	for (unsigned int i = 0; i < strlen (buffer); ++i)
		glutBitmapCharacter (GLUT_BITMAP_HELVETICA_12, buffer[i]);

	return ret;
}

void MyGlut::attach_display_func(void (*pt2func)()) {
	_custom_display = pt2func;
}

void MyGlut::attach_2DForeground_display_func(void (*pt2func)()) {
	_custom_2DForeground_display = pt2func;
}

void MyGlut::attach_keyboard_func(void (*pt2func)(unsigned char, int , int)) {
	_custom_keyboard = pt2func;
}

void MyGlut::attach_mouse_func(void (*pt2func)(int, int, int, int)){
	_custom_mouseHandler = pt2func;
}

void MyGlut::attach_window_special_key_func(void (*pt2func)(int, int , int)) {
	_custom_window_special_key = pt2func;
}

void MyGlut::attach_multikey_func(void (*pt2func)(bool*, bool*)) {
	_custom_multikey = pt2func;
}

void MyGlut::attach_reshape_func(void (*pt2func)(int, int)) {
	_custom_reshape = pt2func;
}

void MyGlut::_keyboardHandler(unsigned char key, int x, int y) {
	//printf("Pressed %c (code %d) key...\n", key, (int)key);
	pressedKeys[(int)key] = true;

	if((*_custom_keyboard) != NULL) {
		(*_custom_keyboard)(key, x, y);
	}
}

void MyGlut::_keyboardUpHandler(unsigned char key, int x, int y) {
	//printf("Up %c (code %d) key...\n", key, (int)key);
	if (pressedKeys[(int)key - 32]) {
		pressedKeys[(int)key - 32] = false;
	}
	if (pressedKeys[(int)key + 32]) {
		pressedKeys[(int)key + 32] = false;
	}
	pressedKeys[(int)key] = false;
}

void MyGlut::_window_special_key(int key, int x, int y) {
	//printf("Pressed Special key code %d key...\n", (int)key);
	pressedSpecialKeys[key] = true;
	if((*_custom_window_special_key) != NULL) {
		(*_custom_window_special_key)(key, x, y);
	}
}

void MyGlut::_window_special_key_up(int key, int x, int y) {
	pressedSpecialKeys[key] = false;
}

void MyGlut::_mouseHandler(int button, int state, int x, int y) {
	printf("Pressed %i button, state %i at x=%i, y=%i\n", button, state, x, y);
	if((*_custom_mouseHandler) != NULL) {
		(*_custom_mouseHandler)(button, state, x, y);
	}
}

void MyGlut::_motionHandler (int x, int y) {
	printf("Motion to x=%i, y=%i\n", x, y);
}
