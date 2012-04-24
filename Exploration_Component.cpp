bool run = true;

GLfloat guy_position[]={0.0, 0.0, 0.0};

void displayFlat_exploration() {
	int n = 5;
	glRasterPos2i (10, glutGet (GLUT_WINDOW_HEIGHT)/2 + 15*(n-0));
	gl->Printf ("Current Controls:");

	glRasterPos2i (10, glutGet (GLUT_WINDOW_HEIGHT)/2 + 15*(n-1));
	gl->Printf ("A and a: Pitch");
	
	glRasterPos2i (10, glutGet (GLUT_WINDOW_HEIGHT)/2 + 15*(n-2));
	gl->Printf ("S and s: Roll");
	
	glRasterPos2i (10, glutGet (GLUT_WINDOW_HEIGHT)/2 + 15*(n-3));
	gl->Printf ("Up: Forward");
	
	glRasterPos2i (10, glutGet (GLUT_WINDOW_HEIGHT)/2 + 15*(n-4));
	gl->Printf ("Left and Right: Turn");
	
	glRasterPos2i (10, glutGet (GLUT_WINDOW_HEIGHT)/2 + 15*(n-5));
	gl->Printf ("Scroll Wheel: In and Out");
}
void multikey_exploration( bool *keys, bool *special_keys) {
	
	if (keys[(int)'a']) {
		viewPitchAround(vAdd(eye, vScale(vpn, vLen(vSubtract(guy_position, eye)))), 2.0);
	}
	
	if (keys[(int)'A']) {
		viewPitchAround(vAdd(eye, vScale(vpn, vLen(vSubtract(guy_position, eye)))), -2.0);
	}
	
	if (keys[(int)'s'] )
		viewRoll(1.0);
		
	if (keys[(int)'S'] ) 
		viewRoll(-1.0);
	
//	if (keys[(int)'l'])
//		viewLevelOut();
	
	if (special_keys[KEY_LEFT]) {
		//viewLevelOut();
		GLfloat *tmp = vAdd(eye, vScale(vpn, vLen(vSubtract(guy_position, eye))));
		//viewRoll(h-eye[1]);
		//tmp[1] = eye[1];
		viewYawAround(tmp, -2.0);
		//viewRoll(2);
		//u[1] = 0.0;
		//viewPitchAround(vAdd(eye, vScale(vpn, vLen(vSubtract(guy_position, eye)))), 2);
		//viewRoll(h-eye[1]);
		//printf("%f %f %f\n", h, eye[1], eye[1]-h);
	}
	if (special_keys[KEY_RIGHT]) {
		viewYawAround(vAdd(eye, vScale(vpn, vLen(vSubtract(guy_position, eye)))), 2.0);
	}
		
	if (special_keys[KEY_UP]) {
		GLfloat speed=3.0;
		if (run) {
			changeModelAnimation(&skeletor, 11);
		}
		else {
			speed = 1.0;
			changeModelAnimation(&skeletor, 5);
			GLfloat *tmp = vScale(vpn,1.0);
		}
		GLfloat *tmp = vScale(vpn,speed);
		GLfloat moveToV[] = {tmp[0], 0.0, tmp[2]};
		viewMoveTo(moveToV);
		
		GLfloat *eye_tmp = vAdd(guy_position, moveToV);
		guy_position[0] = eye_tmp[0];
		guy_position[1] = eye_tmp[1];
		guy_position[2] = eye_tmp[2];
	} else {
		// rest
		//changeModelAnimation(&skeletor, 4);
		// stand
		changeModelAnimation(&skeletor, 13);
	}
}
void keyboard_exploration(unsigned char key, int x, int y) {
	if (key == 'r' || key == 'R') {
		run = !run;
	}
}

void mouse_exploration(int button, int state, int x, int y) {
	if (button == 3 && state == 0) {
		viewSlidePerpendicular(-4.0 );
	} else if (button == 4 && state == 0) {
		viewSlidePerpendicular( 4.0 );
	}
}

void display_exploration() {
	glEnable(GL_LIGHTING);
	glEnable (GL_TEXTURE_2D);
	if (run) skeletor.animate (0.2);
	else skeletor.animate (0.1);
	glPushMatrix();
		//viewSlidePerpendicular( -2.0 );
		{
			//printf("%f %f %f\n", vpn[0], vpn[1], vpn[2]);

			//GLfloat *at = vAdd(guy_position, vScale(vpn, 150));
			glTranslatef(guy_position[0], guy_position[1], guy_position[2]);
			glRotatef(-90, 0.0, 1.0, 0.0);
			float angle = get_angle_between_in_degrees(-1, 0, vpn[0], vpn[2]);
			if (vpn[2] > 0 && vpn[0] > 0) {
				angle *= -1;
				angle += 180;
			} else if (vpn[2] < 0 && vpn[0] > 0) {
				angle += 180;
			}  else if (vpn[2] < 0 && vpn[0] < 0) {
			}  else if (vpn[2] > 0 && vpn[0] < 0) {
				angle *= -1;
			} 
			glRotatef(-angle, 0.0, 1.0, 0.0);
		}
		
		
	
		skeletor.drawObjectItp (true,
			static_cast<Md2Object::Md2RenderMode>(0));
	glPopMatrix();
	
	glPushMatrix();
		glShadowProjection(l,e,n);
		{
			//printf("%f %f %f\n", vpn[0], vpn[1], vpn[2]);
			//GLfloat *at = vAdd(eye, vScale(vpn, 150));
			glTranslatef(guy_position[0], guy_position[1], guy_position[2]);
			glRotatef(-90, 0.0, 1.0, 0.0);
			float angle = get_angle_between_in_degrees(-1, 0, vpn[0], vpn[2]);
			if (vpn[2] > 0 && vpn[0] > 0) {
				angle *= -1;
				angle += 180;
			} else if (vpn[2] < 0 && vpn[0] > 0) {
				angle += 180;
			}  else if (vpn[2] < 0 && vpn[0] < 0) {
			}  else if (vpn[2] > 0 && vpn[0] < 0) {
				angle *= -1;
			} 
			glRotatef(-angle, 0.0, 1.0, 0.0);
		}
		
			
		glDisable(GL_LIGHTING);
		glDisable (GL_TEXTURE_2D);
		glColor4f(0.0,0.0,0.0,1.0);
		skeletor.drawObjectItp (true,
			static_cast<Md2Object::Md2RenderMode>(0));
	glPopMatrix();
}

void changeToExplorationComponent() {
	GLfloat *at = vAdd(eye, vScale(vpn, 150));
	guy_position[0]=at[0];
	guy_position[1]=23.5;
	guy_position[2]=at[2];
}
