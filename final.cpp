/*****************************
Things I would Like to do...
render the next frame...time it...
then sleep for that time minus the frame render time
to more accurately play animation at the defined fps

call: gcc -o final final.cpp md2loader/Md2Model.cpp md2loader/Texture.cpp md2loader/Image.cpp BMPLoader/BMPLoader.cpp -lGL -lglut -lGLEW && final
*****************************/

#include <stdio.h>
#include <math.h>
#include "MyGlut.h"
#include "MyGlView.h"
#include "Models.cpp"
#include "Scene.cpp"
#include "Textures.cpp"
#include "SceneDefinition.cpp"

MyGlut *gl;

void changeGameComponent(int);
#define TRAVEL_COMP 1
#define TRANSITION_COMP 2
#define EXPLORATION_COMP 3
int game_component = TRAVEL_COMP;
//int game_component =  EXPLORATION_COMP;

#include "Exploration_Component.cpp"
#include "Travel_Component.cpp"

void changeGameComponent(int component) {
	game_component = component;
	
	switch(game_component) {
		case EXPLORATION_COMP:
			changeToExplorationComponent();
			break;
		case TRAVEL_COMP:
			//display_travel();
			break;
		case TRANSITION_COMP:
			break;
	}
}


static void draw2DForeground () {
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	
	glColor3f (1.0f, 1.0f, 1.0f);

	glRasterPos2i (10, 10);
	gl->Printf ("FPS: %i", gl->fps);

	glRasterPos2i (10, glutGet (GLUT_WINDOW_HEIGHT) - 20);
	gl->Printf ("Final Project");

	glRasterPos2i (10, glutGet (GLUT_WINDOW_HEIGHT) - 35);
	gl->Printf ("Ian Halpern");
	
	switch(game_component) {
		case EXPLORATION_COMP:
			displayFlat_exploration();
			break;
		case TRAVEL_COMP:
			displayFlat_travel();
			break;
		case TRANSITION_COMP:
			break;
	}
}




//GLfloat vanPosition = 0.0;
void display() {
	viewUpdate();
	
//	skeletor.animate (0.1);
//	van.animate (0.1);
//	guy.animate (0.1);
	
	
	glLightfv(GL_LIGHT0, GL_POSITION, l);
	
	// Draw Position of GL_LIGHT0  (the sun)
	glPushMatrix();
		glDisable(GL_TEXTURE_2D);
		glTranslatef(l[0], l[1], l[2]);
		glColor3f(1.0, 1.0, 0.0);
		glutSolidSphere(15.0f,20,20);
	glPopMatrix();
	
	traverse(&root_node);


	glEnable (GL_TEXTURE_2D);
	
		
	glPushMatrix();
		
		glTranslatef(vanPosition[0], vanPosition[1], vanPosition[2]);
		glRotatef(-90, 0.0, 1.0, 0.0);
	
		van.drawObjectItp (false,
			static_cast<Md2Object::Md2RenderMode>(0));
	glPopMatrix();
	glPushMatrix();
		glShadowProjection(l,e,n);
		glTranslatef(vanPosition[0], vanPosition[1], vanPosition[2]);
		glRotatef(-90, 0.0, 1.0, 0.0);
		glDisable(GL_LIGHTING);
		glDisable (GL_TEXTURE_2D);
		//glColor4f(0.1,0.1,0.1,1.0);
		glColor4f(0.0,0.0,0.0,1.0);
		van.drawObjectItp (false,
			static_cast<Md2Object::Md2RenderMode>(0));
	glPopMatrix();
	
	switch(game_component) {
		case EXPLORATION_COMP:
			display_exploration();
			break;
		case TRAVEL_COMP:
			display_travel();
			break;
		case TRANSITION_COMP:
			break;
	}
	

//	// Now we draw the shadow
//	glPushMatrix();
//		glShadowProjection(l,e,n);	
//		glDisable(GL_LIGHTING);
//		glDisable (GL_TEXTURE_2D);
//		glColor4f(0.1,0.1,0.1,1.0);
//		
//		glRotatef(90, 0.0, 0.0, 1.0);
//		glTranslatef(-30.0, 24.0, vanPosition)
//		van.drawObjectItp (false,
//		static_cast<Md2Object::Md2RenderMode>(0));
//	glPopMatrix();
	
	
}

void reshape(int w, int h) {
	viewUpdate();
}

void keyboard(unsigned char key, int x, int y) {
	//printf("press\n");
	if (key == KEY_ESC) {
		exit(-1);
	}
	switch(game_component) {
		case EXPLORATION_COMP:
			keyboard_exploration(key, x, y);
			break;
		case TRAVEL_COMP:
			keyboard_travel(key, x, y);
			break;
		case TRANSITION_COMP:
			break;
	}
	
}

void multikey( bool *keys, bool *special_keys) {
	switch(game_component) {
		case EXPLORATION_COMP:
			multikey_exploration(keys, special_keys);
			break;
		case TRAVEL_COMP:
			multikey_travel(keys, special_keys);
			break;
		case TRANSITION_COMP:
			break;
	}

//	if (keys[(int)'Z'] )
//		viewRoll(1.0);
//		
//	if (keys[(int)'z'] )
//		viewRoll(-1.0);
//	
//	if (keys[(int)'X'] )
//		viewPitch(1.0);
//		
//	if (keys[(int)'x'] )
//		viewPitch(-1.0);
//	
//	if (keys[(int)'C'] )
//		viewYaw(8.0);
//	
//	if (keys[(int)'c'] )
//		viewYaw(-8.0);
//	
//	if (keys[(int)'l'] ) // Reset Camera to face forward
//		viewLevelOut();
//	if (keys[(int)'u'])
//		viewSlideUp(4);
//	if (keys[(int)'U'])
//		viewSlideUp(-4);
//	if (keys[(int)'j'])
//		viewYawAround(vAdd(eye, vScale(vpn, 150)), 2.0);
//	if (keys[(int)'k'])
//		viewPitchAround(vAdd(eye, vScale(vpn, 150)), 2.0);
//	if (keys[(int)'J'])
//		viewYawAround(vAdd(eye, vScale(vpn, 150)), -2.0);
//	if (keys[(int)'K'])
//		viewPitchAround(vAdd(eye, vScale(vpn, 150)), -2.0);
////	if (keys[(int)'l'])
////		viewRollAround(vAdd(eye, vScale(vpn, 150)), 2.0);
//	
//	if (special_keys[KEY_UP]) {
//		viewSlidePerpendicular( -3.0 );
//		if (game_component == EXPLORATION_COMP) {
//			//creap 
//			if (run)
//				changeModelAnimation(&skeletor, 11);
//			else {
//				viewSlidePerpendicular( 2.0 );
//				changeModelAnimation(&skeletor, 5);
//			}
//			
//			
//		}
//	} else {
//		if (game_component == EXPLORATION_COMP){ 
//			// rest
//			//changeModelAnimation(&skeletor, 4);
//			// stand
//			changeModelAnimation(&skeletor, 13);
//			
//		}
//	}
//			
//	if (special_keys[KEY_DOWN])
//		viewSlidePerpendicular( 3.0 );
//				
//	if (special_keys[KEY_RIGHT])
//		viewSlideHorizonally(-3.0);
//			
//	if (special_keys[KEY_LEFT])
//		viewSlideHorizonally(3.0);
}

void mouse(int button, int state, int x, int y) {
	switch(game_component) {
		case EXPLORATION_COMP:
			mouse_exploration(button, state, x, y);
			break;
		case TRAVEL_COMP:
			//multikey_travel(keys, special_keys);
			break;
		case TRANSITION_COMP:
			break;
	}
}

void special_key(int key, int x, int y) {
//	switch(key) {
//		case KEY_UP:
//			viewSlidePerpendicular( -0.5 );
//			break;
//			
//		case KEY_DOWN:
//			viewSlidePerpendicular( 0.5 );
//			break;
//			
//		case KEY_RIGHT:
//			viewSlideHorizonally(0.5);
//			break;
//			
//		case KEY_LEFT:
//			viewSlideHorizonally(-0.5);
//			break;
//	}
}



int main(int argc, char** argv) {

	gl = new MyGlut(argc, argv, "Final Project");
	gl->attach_display_func(&display);
	gl->attach_reshape_func(&reshape);
	gl->attach_keyboard_func(&keyboard);
	gl->attach_window_special_key_func(&special_key);
	gl->attach_2DForeground_display_func(&draw2DForeground);
	gl->attach_multikey_func(&multikey);
	gl->attach_mouse_func(&mouse);
	
	GLfloat mat_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat lm_ambient[] = { 0.1, 0.1, 0.1, 0.5 };
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 80.0);
	glLightfv(GL_LIGHT0, GL_POSITION, l);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lm_ambient);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);
	glColorMaterial ( GL_FRONT_AND_BACK, GL_EMISSION ) ;
	glLightModeli (GL_LIGHT_MODEL_COLOR_CONTROL,GL_SEPARATE_SPECULAR_COLOR);

	glEnable (GL_NORMALIZE);  // corrections when using glScale
	glEnable (GL_LIGHTING);
	glEnable (GL_LIGHT0);
	
	loadMD2Models();
	loadTextures();
	initScene();
	
	GLfloat startPos[3] = {vanPosition[0]-50, 50.0, 0.0};
	viewMoveTo(startPos);
	viewYaw(90.0);
	viewPitch(-10.0);
	
	
	setTravelView(INFRONT_VIEW);
	//changeGameComponent(EXPLORATION_COMP);
	
	glDisable (GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	
	gl->start();
	return 1;
}
