#define BEHIND_VIEW 1
#define INFRONT_VIEW 2

//GLfloat vanPosition[] = {3650.0, e[1]+0.1, 0.0};
GLfloat vanPosition[] = {1000.0, e[1]+0.1, 0.0};
GLint view = INFRONT_VIEW;

void setTravelView(GLint new_view) {
	if (new_view != view) {
		if(new_view == INFRONT_VIEW) {
			viewPitch(10.0);
			eye[1] = 50;
			eye[0] -=210;
			view = INFRONT_VIEW;
		}
		else {
			eye[1] = 100;
			eye[0] +=210;
		
			viewPitch(-10.0);
			view = BEHIND_VIEW;
		}
	}
}

void toggleTravelViews() {
	if(view == BEHIND_VIEW) {
		setTravelView(INFRONT_VIEW);
	}
	else {
		setTravelView(BEHIND_VIEW);
	}
}

void display_travel() {
//	vanPosition[0] -= 2.0;
	GLfloat dir[] = {-1.0, 0.0, 0.0};
	GLfloat speed=2.0;
//	GLfloat *tmp = vScale(vpn,speed);
//	GLfloat moveToV[] = {tmp[0], 0.0, 0.0};
//	
	GLfloat *tmp = vScale(dir,speed);
	GLfloat moveToV[] = {tmp[0], 0.0, 0.0};
	viewMoveTo(moveToV);
	
	GLfloat *eye_tmp = vAdd(vanPosition, moveToV);
	vanPosition[0] = eye_tmp[0];
	vanPosition[1] = eye_tmp[1];
	vanPosition[2] = eye_tmp[2];
	

	
	if (vanPosition[0] < 0.0f) {
		setTravelView(INFRONT_VIEW);
		viewLevelOut();
		changeGameComponent(EXPLORATION_COMP);
	}
}

void displayFlat_travel() {
	int n = 4;
	glRasterPos2i (10, glutGet (GLUT_WINDOW_HEIGHT)/2 + 15*(n-0));
	gl->Printf ("Current Controls:");

	glRasterPos2i (10, glutGet (GLUT_WINDOW_HEIGHT)/2 + 15*(n-1));
	gl->Printf ("v: Toggle view");
	
//	glRasterPos2i (10, glutGet (GLUT_WINDOW_HEIGHT)/2 + 15*(n-2));
//	gl->Printf ("Up and Down: Pitch");
	
	glRasterPos2i (10, glutGet (GLUT_WINDOW_HEIGHT)/2 + 15*(n-2));
	gl->Printf ("S and s: Roll");
	
	glRasterPos2i (10, glutGet (GLUT_WINDOW_HEIGHT)/2 + 15*(n-3));
	gl->Printf ("Left and Right: Turn(yaw)");
	
	glRasterPos2i (10, glutGet (GLUT_WINDOW_HEIGHT)/2 + 15*(n-4));
	gl->Printf ("l: Level view");
}

void keyboard_travel(unsigned char key, int x, int y) {
	if (key == 'v' || key == 'V') {
		toggleTravelViews();
	}
}

void multikey_travel( bool *keys, bool *special_keys) {
//	if (special_keys[KEY_UP])
//		viewPitch(1.0);
//		
//	if (special_keys[KEY_DOWN])
//		viewPitch(-1.0);
	
	if (special_keys[KEY_LEFT])
		viewYaw(8.0);
	
	if (special_keys[KEY_RIGHT])
		viewYaw(-8.0);
	
	if (keys[(int)'S'] )
		viewRoll(1.0);
		
	if (keys[(int)'s'] )
		viewRoll(-1.0);
		
	if (keys[(int)'l'])
		viewLevelOut();

//	if (special_keys[KEY_LEFT]) {
//		viewYawAround(vAdd(eye, vScale(vpn, 100)), -2.0);
//	}
//	if (special_keys[KEY_RIGHT]) {
//		viewYawAround(vAdd(eye, vScale(vpn, 100)), 2.0);
//	}
				
//	if (special_keys[KEY_RIGHT])
//		viewSlideHorizonally(-3.0);
//			
//	if (special_keys[KEY_LEFT])
//		viewSlideHorizonally(3.0);
}
