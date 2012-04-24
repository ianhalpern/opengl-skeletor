/*****************************
Things I would Like to do...
render the next frame...time it...
then sleep for that time minus the frame render time
to more accurately play animation at the defined fps

call: gcc -o final final.cpp md2loader/Md2Model.cpp md2loader/Texture.cpp -lGL md2loader/Image.cpp -lglut -lGLEW && final
*****************************/

#include <stdio.h>
#include <math.h>
#include "MyGlut.h"
#include "MyGlView.h"

#include "Textures.cpp"

MyGlut *gl;

GLfloat mat_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat light_position[] = { 0.0, 0.0, 10.0, 1.0 };
GLfloat lm_ambient[] = { 0.2, 0.2, 0.2, 0.5 };


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
}





GLfloat x=1.0;
void display() {
	viewUpdate();
	
	glDisable(GL_TEXTURE_2D);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glTranslatef(light_position[0], light_position[1], light_position[2]);
	glColor3f(1.0, 1.0, 0.0);
	glutSolidSphere(1.0f,20,20);
	
	glEnable(GL_LIGHTING);
	//glEnable(GL_COLOR_MATERIAL);
	
	glTranslatef(-light_position[0], -light_position[1]+40, -light_position[2]);
	x+=0.4;
	glRotatef(x, 1.0, 1.0, 1.0);
	glutSolidCube(10.0);
	glRotatef(-x, 1.0, 1.0, 1.0);
	glTranslatef(10, 10, 10);
	
	
	GLfloat width = 50, length = 50;
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D,groundTexture);
	glColor4fv(hexColor(0x00, 0x99, 0x33, 1.0f));

	glBegin(GL_QUADS);
		
		GLfloat a[] = {-width, 0.0, -length};
		GLfloat c[] = { width, 0.0, -length};
		GLfloat b[] = { width, 0.0,  length};
		GLfloat *v1 = vSubtract(a, c);
		GLfloat *v2 = vSubtract(b, c);
		
		GLfloat *v3 = vToUnitVector(vCrossProduct(v1, v2));
		glNormal3fv(v3);
		//printf("%f %f %f\n", v3[0], v3[1], v3[2]);
		glTexCoord2d(0,2);
		glVertex3f(-width, 0.0, -length);
		glTexCoord2d(2,2);
		glVertex3f(-width, 0.0,  length);
		glTexCoord2d(2,0);
		glVertex3f( width, 0.0,  length);
		glTexCoord2d(0,0);
		glVertex3f( width, 0.0, -length);
	glEnd();

}

void reshape(int w, int h) {
	viewUpdate();
}

void keyboard(unsigned char key, int x, int y) {
	//printf("press\n");
	if (key == KEY_ESC) {
		exit(-1);
	}
}

void multikey( bool *keys, bool *special_keys) {
	if (keys[(int)'Z'] )
		viewRoll(1.0);
		
	if (keys[(int)'z'] )
		viewRoll(-1.0);
	
	if (keys[(int)'X'] )
		viewPitch(1.0);
		
	if (keys[(int)'x'] )
		viewPitch(-1.0);
	
	if (keys[(int)'C'] )
		viewYaw(8.0);
	
	if (keys[(int)'c'] )
		viewYaw(-8.0);
	
	if (keys[(int)'l'] ) // Reset Camera to face forward
		viewLevelOut();
	
	if (special_keys[KEY_UP])
		viewSlidePerpendicular( -3.0 );
	
			
	if (special_keys[KEY_DOWN])
		viewSlidePerpendicular( 3.0 );
				
	if (special_keys[KEY_RIGHT])
		viewSlideHorizonally(-3.0);
			
	if (special_keys[KEY_LEFT])
		viewSlideHorizonally(3.0);
}

void special_key(int key, int x, int y) {

}


int main(int argc, char** argv) {

	gl = new MyGlut(argc, argv, "Final Project");
	gl->attach_display_func(&display);
	gl->attach_reshape_func(&reshape);
	gl->attach_keyboard_func(&keyboard);
	gl->attach_window_special_key_func(&special_key);
	gl->attach_2DForeground_display_func(&draw2DForeground);
	gl->attach_multikey_func(&multikey);
//	initScene();
	
	

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 80.0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lm_ambient);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,0);
	glColorMaterial ( GL_FRONT_AND_BACK, GL_EMISSION ) ;
	glLightModeli (GL_LIGHT_MODEL_COLOR_CONTROL,GL_SEPARATE_SPECULAR_COLOR);

	glEnable (GL_LIGHTING);
	glEnable (GL_LIGHT0);
	
	glEnable(GL_TEXTURE_2D);
	

	loadTextures();
	
	
	GLfloat startPos[3] = {80.0, 50.0, 100.0};
	viewMoveTo(startPos);
	viewYaw(75.0);
	viewPitch(-10.0);
	
	gl->start();
	return 1;
}
