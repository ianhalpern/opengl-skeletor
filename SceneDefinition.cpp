treenode root_node;

void drawAxis () {
	glBegin(GL_LINES);
		// y white
		glColor4f(1.0f,1.0f,1.0f,1.0);
		glVertex3f( 0.0f,-100.0f,0.0f);
		glVertex3f( 0.0f, 100.0f,0.0f);
		// x pink
		glColor4f(1.0f,0.5f,0.5f,1.0);
		glVertex3f(-100.0f, 0.0f,0.0f);
		glVertex3f( 100.0f, 0.0f,0.0f);
		// z green
		glColor4f(0.5f,1.0f,0.5f,1.0);
		glVertex3f( 0.0f, 0.0f,-100.0f);
		glVertex3f( 0.0f, 0.0f, 100.0f);
	glEnd();
}


void drawMotorcycle() {
	motor.drawObjectItp (false,
			static_cast<Md2Object::Md2RenderMode>(0));
}

void drawGround() {
	
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D,groundTexture);
	GLfloat width = 4000, length = 500, height = e[1]-0.6;

	glColor4fv(hexColor(0x00, 0x99, 0x33, 1.0f));

	glBegin(GL_QUADS);
		
		GLfloat a[] = {-width, height, -length};
		GLfloat c[] = {-width, height,  length};
		GLfloat b[] = { width, height,  length};
		GLfloat *v1 = vSubtract(a, c);
		GLfloat *v2 = vSubtract(b, c);
		
		GLfloat *v3 = vToUnitVector(vCrossProduct(v1, v2));
		glNormal3fv(v3);
		//printf("%f %f %f\n", v3[0], v3[1], v3[2]);
		GLdouble nRepeatTexureWidth = width/100;
		GLdouble nRepeatTexureLength = length/100;
		glTexCoord2d(nRepeatTexureWidth,0); 
		glVertex3f(-width, height, -length);
		
		glTexCoord2d(nRepeatTexureWidth,nRepeatTexureLength);
		glVertex3f(-width, height,  length);
		
		glTexCoord2d(0,nRepeatTexureLength);
		glVertex3f( width, height,  length);
		
		glTexCoord2d(0,0);
		glVertex3f( width, height, -length);
	glEnd();

}

void drawRoad() {
	
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D,roadTexture);
	GLfloat width = 2000, length = 100, height = e[1]-0.4;

	glColor4fv(hexColor(0x00, 0x99, 0x33, 1.0f));

	glBegin(GL_QUADS);
		
		GLfloat a[] = {-width, height, -length};
		GLfloat c[] = {-width, height,  length};
		GLfloat b[] = { width, height,  length};
		GLfloat *v1 = vSubtract(a, c);
		GLfloat *v2 = vSubtract(b, c);
		
		GLfloat *v3 = vToUnitVector(vCrossProduct(v1, v2));
		glNormal3fv(v3);
		//printf("%f %f %f\n", v3[0], v3[1], v3[2]);
		GLdouble nRepeatTexureWidth = width/100;
		GLdouble nRepeatTexureLength = length/100;
		glTexCoord2d(nRepeatTexureWidth,0); 
		glVertex3f(-width, height, -length);
		
		glTexCoord2d(nRepeatTexureWidth,nRepeatTexureLength);
		glVertex3f(-width, height,  length);
		
		glTexCoord2d(0,nRepeatTexureLength);
		glVertex3f( width, height,  length);
		
		glTexCoord2d(0,0);
		glVertex3f( width, height, -length);
	glEnd();

}

void drawSky() {
	GLfloat width = 2000, length = 500, height = 500;
	
	glBegin(GL_QUADS);
		glColor4fv(hexColor(0xCC,0xFF,0xFF,1.0));
	
		glVertex3f( width, 0.0f, length);
		glVertex3f(-width, 0.0f, length);
	
		glColor4fv(hexColor(0x00,0xFF,0xFF,1.0));
	
		glVertex3f(-width, height,  length);
		glVertex3f( width, height,  length);
	
		glColor4fv(hexColor(0xCC,0xFF,0xFF,1.0));
	
		glVertex3f( width, 0.0f, -length);
		glVertex3f(-width, 0.0f, -length);
	
		glColor4fv(hexColor(0x00,0xFF,0xFF,1.0));
	
		glVertex3f(-width, height,  -length);
		glVertex3f( width, height,  -length);
	
		glColor4fv(hexColor(0xCC,0xFF,0xFF,1.0));
	
		glVertex3f( width, 0.0f, length);
		glVertex3f( width, 0.0f, -length);
	
		glColor4fv(hexColor(0x00,0xFF,0xFF,1.0));
	
		glVertex3f( width, height,  -length);
		glVertex3f( width, height,  length);
	
		glColor4fv(hexColor(0xCC,0xFF,0xFF,1.0));
	
		glVertex3f(-width, 0.0f, length);
		glVertex3f(-width, 0.0f, -length);
	
		glColor4fv(hexColor(0x00,0xFF,0xFF,1.0));
	
		glVertex3f(-width, height,  -length);
		glVertex3f(-width, height,  length);
	
		glColor4fv(hexColor(0x00,0xFF,0xFF,1.0));
	
		glVertex3f(-width, height, -length);
		glVertex3f(-width, height,  length);
		glVertex3f( width, height,  length);
		glVertex3f( width, height, -length);
	glEnd();
}

void drawHill() {

	glColor4fv(hexColor(0x45, 0xaa, 0x31, 1.0f));
	glBegin(GL_POLYGON);
		glVertex3f(-100.0f,  0.0f, -10.0f);
		glVertex3f(-0.0f,  0.0f, 20.0f);
		glVertex3f(-30.0f,  10.0f, 60.0f);
		glVertex3f(-65.0f,  20.0f, 55.0f);
		glVertex3f(-100.0f,  30.0f, 10.0f);
	glEnd();
	
	glColor4fv(hexColor(0x40, 0xa0, 0x33, 1.0f));
	glBegin(GL_POLYGON);
		glVertex3f(-0.0f,  0.0f, 20.0f);
		glVertex3f(-30.0f,  10.0f, 60.0f);
		glVertex3f(-30.0f,  10.0f, 100.0f);
		glVertex3f(10.0f,  0.0f, 100.0f);
	glEnd();
	
	glColor4fv(hexColor(0x50, 0xa9, 0x33, 1.0f));
	glBegin(GL_POLYGON);
		glVertex3f(-30.0f,  10.0f, 60.0f);
		glVertex3f(-65.0f,  20.0f, 55.0f);
		glVertex3f(-30.0f,  10.0f, 100.0f);
	glEnd();
	
	glColor4fv(hexColor(0x45, 0xa8, 0x33, 1.0f));
	glBegin(GL_POLYGON);
		glVertex3f(-65.0f,  20.0f, 55.0f);
		glVertex3f(-30.0f,  10.0f, 100.0f);
		glVertex3f(-60.0f,  30.0f, 100.0f);
		glVertex3f(-60.0f,  40.0f, 80.0f);
	glEnd();
	
	glColor4fv(hexColor(0x50, 0xaa, 0x33, 1.0f));
	glBegin(GL_POLYGON);
		glVertex3f(-60.0f,  30.0f, 100.0f);
		glVertex3f(-60.0f,  40.0f, 80.0f);
		glVertex3f(-100.0f,  50.0f, 100.0f);
	glEnd();
	
	glColor4fv(hexColor(0x40, 0xa5, 0x33, 1.0f));
	glBegin(GL_POLYGON);
		glVertex3f(-60.0f,  40.0f, 80.0f);
		glVertex3f(-65.0f,  20.0f, 55.0f);
		glVertex3f(-100.0f,  30.0f, 10.0f);
		glVertex3f(-100.0f,  50.0f, 100.0f);
	glEnd();
}

void drawPlants() {
	int j = 0;
	for (int i=0; i<40; i++) {
		glTranslatef(i*2, 0.0, i*2);
		//glRotatef(i*20, 0.0,0.0+i/10, 0.0);
		if (i%2 == 0) {
			if (j%2 == 0)
				glTranslatef(-i*7, 0.0, -i*14);
			else glTranslatef(-i*5, 0.0, i*42);
			plant.drawObjectItp (false,
			static_cast<Md2Object::Md2RenderMode>(0));
			j++;
		} else {
			if (j%2 == 0)
				glTranslatef(i*5, 0.0, -i*19);
			else glTranslatef(-i*5, 0.0, i*12);
			//glTranslatef(i*8, 0.0, -i*5);
			plant2.drawObjectItp (false,
			static_cast<Md2Object::Md2RenderMode>(0));
			j++;
		}
	}
}

void drawBuilding() {
	GLfloat size = 10;
	//Quad 1
	glBegin(GL_QUADS);
		glNormal3f(1.0f, 0.0f, 0.0f);   //N1
		glTexCoord2f(0.0f, 3.0f); glVertex3f( size/2, size/2, size/2);   //V2
		glTexCoord2f(0.0f, 0.0f); glVertex3f( size/2,-size/2, size/2);   //V1
		glTexCoord2f(3.0f, 0.0f); glVertex3f( size/2,-size/2,-size/2);   //V3
		glTexCoord2f(3.0f, 3.0f); glVertex3f( size/2, size/2,-size/2);   //V4
		//Quad 2
		glNormal3f(0.0f, 0.0f, -1.0f);  //N2
		glTexCoord2f(0.0f, 3.0f); glVertex3f( size/2, size/2,-size/2);   //V4
		glTexCoord2f(0.0f, 0.0f); glVertex3f( size/2,-size/2,-size/2);   //V3
		glTexCoord2f(3.0f, 0.0f); glVertex3f(-size/2,-size/2,-size/2);   //V5
		glTexCoord2f(3.0f, 3.0f); glVertex3f(-size/2, size/2,-size/2);   //V6
		//Quad 3
		glNormal3f(-3.0f, 0.0f, 0.0f);  //N3
		glTexCoord2f(0.0f, 3.0f); glVertex3f(-size/2, size/2,-size/2);   //V6
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-size/2,-size/2,-size/2);   //V5
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-size/2,-size/2, size/2);   //V7
		glTexCoord2f(1.0f, 3.0f); glVertex3f(-size/2, size/2, size/2);   //V8
		//Quad 4
		glNormal3f(0.0f, 0.0f, 1.0f);   //N4
		glTexCoord2f(0.0f, 3.0f); glVertex3f(-size/2, size/2, size/2);   //V8
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-size/2,-size/2, size/2);   //V7
		glTexCoord2f(3.0f, 0.0f); glVertex3f( size/2,-size/2, size/2);   //V1
		glTexCoord2f(3.0f, 3.0f); glVertex3f( size/2, size/2, size/2);   //V2
		//Quad 5
		glNormal3f(0.0f, 1.0f, 0.0f);   //N5
		glTexCoord2f(0.0f, 3.0f); glVertex3f(-size/2, size/2,-size/2);   //V6
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-size/2, size/2, size/2);   //V8
		glTexCoord2f(3.0f, 0.0f); glVertex3f( size/2, size/2, size/2);   //V2
		glTexCoord2f(3.0f, 3.0f); glVertex3f( size/2, size/2,-size/2);   //V4
		//Quad 6
		glNormal3f(1.0f, -1.0f, 0.0f);  //N6
		glTexCoord2f(0.0f, 3.0f); glVertex3f(-size/2,-size/2, size/2);   //V7
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-size/2,-size/2,-size/2);   //V5
		glTexCoord2f(3.0f, 0.0f); glVertex3f( size/2,-size/2,-size/2);   //V3
		glTexCoord2f(3.0f, 3.0f); glVertex3f( size/2,-size/2, size/2);   //V1
	glEnd();

//		// Draw Roof
//		if (!drawingShadows)glColor4fv(hexColor(0x00, 0x00, 0x33, 1.0f));
//		glVertex3f(-10.0f, 10.0f, 10.0f);
//		glVertex3f( 10.0f, 10.0f, 10.0f);
//		glVertex3f( 5.0f, 15.0f, 15.0f);
//		glVertex3f(-5.0f, 15.0f, 15.0f);
//		
//		if (!drawingShadows)glColor4fv(hexColor(0x00, 0x00, 0x55, 1.0f));
//		glVertex3f(-10.0f, 10.0f, 20.0f);
//		glVertex3f( 10.0f, 10.0f, 20.0f);
//		glVertex3f( 5.0f, 15.0f, 15.0f);
//		glVertex3f(-5.0f, 15.0f, 15.0f);
//	glEnd();
//	
//	glBegin(GL_TRIANGLES);
//		if (!drawingShadows)glColor4fv(hexColor(0x00, 0x00, 0x99, 1.0f));
//		glVertex3f( 10.0f, 10.0f, 20.0f);
//		glVertex3f( 5.0f, 15.0f, 15.0f);
//		glVertex3f( 10.0f, 10.0f, 10.0f);
//		
//		if (!drawingShadows)glColor4fv(hexColor(0x00, 0x00, 0x99, 1.0f));
//		glVertex3f( -10.0f, 10.0f, 20.0f);
//		glVertex3f( -5.0f, 15.0f, 15.0f);
//		glVertex3f( -10.0f, 10.0f, 10.0f);
//	glEnd();
}

GLuint create(void (*ptr2func)()) {
	GLuint list_ID;
	
	list_ID = glGenLists(1);
	glNewList(list_ID,GL_COMPILE);
		(*ptr2func)();
	glEndList();
	return list_ID;
}
treenode ground, axis, sky, building1, road, wall1, wall2, wall3, wall4, wall5, hill, motorcycle, plants;
void initScene() {
	
	GLuint GROUND   = create(&drawGround);
	GLuint AXIS     = create(&drawAxis);
	GLuint SKY      = create(&drawSky);
	GLuint BUILDING = create(&drawBuilding);
	GLuint ROAD     = create(&drawRoad);
	GLuint HILL     = create(&drawHill);
	GLuint MOTOR    = create(&drawMotorcycle);
	GLuint PLANTS   = create(&drawPlants);
	
	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW_MATRIX,root_node.m);
	(root_node.clr)[0] = 0.0;
	(root_node.clr)[1] = 0.0;
	(root_node.clr)[2] = 0.0;
	root_node.sibling = NULL;
	root_node.child   = &axis;
	
	glGetFloatv(GL_MODELVIEW_MATRIX,axis.m);
	(axis.clr)[0] = 0.0;
	(axis.clr)[1] = 0.0;
	(axis.clr)[2] = 0.0;
	axis.display_list_id = AXIS;
	axis.disable[1] = GL_LIGHTING;
	axis.sibling         = &sky;
	axis.child           = NULL;
	
	glGetFloatv(GL_MODELVIEW_MATRIX,ground.m);
	(ground.clr)[0] = 0.0;
	(ground.clr)[1] = 0.0;
	(ground.clr)[2] = 0.0;
	ground.display_list_id = GROUND;
	ground.enable[0] = GL_LIGHTING;
	ground.enable[1] = GL_TEXTURE_2D;
	ground.sibling         = NULL;
	ground.child           = &road;
	
	glPushMatrix();
	glTranslatef(2000, 0.0,-60.0);
	glGetFloatv(GL_MODELVIEW_MATRIX,road.m);
	(road.clr)[0] = 0.0;
	(road.clr)[1] = 0.0;
	(road.clr)[2] = 0.0;
	road.display_list_id = ROAD;
	road.sibling         = &building1;
	road.child           = NULL;
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(-100.0, 150.0, 135);
		glScalef(20.0f, 30.0f, 20.0f);
		
		glGetFloatv(GL_MODELVIEW_MATRIX,building1.m);
		(building1.clr)[0] = 0.0;
		(building1.clr)[1] = 0.0;
		(building1.clr)[2] = 0.0;
		building1.display_list_id = BUILDING;
		building1.sibling         = &wall1;
		building1.child           = NULL;
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-30.0, 50.0, 200);
		glScalef(5.0f, 10.0f, 32.0f);
		glGetFloatv(GL_MODELVIEW_MATRIX,wall1.m);
		(wall1.clr)[0] = 0.0;
		(wall1.clr)[1] = 0.0;
		(wall1.clr)[2] = 0.0;
		wall1.display_list_id = BUILDING;
		wall1.sibling         = &wall2;
		wall1.child           = NULL;
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(-30.0, 50.0, -300);
		glScalef(5.0f, 10.0f, 22.0f);
		glGetFloatv(GL_MODELVIEW_MATRIX,wall2.m);
		(wall2.clr)[0] = 0.0;
		(wall2.clr)[1] = 0.0;
		(wall2.clr)[2] = 0.0;
		wall2.display_list_id = BUILDING;
		wall2.sibling         = &wall3;
		wall2.child           = NULL;
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(-1000.0, 50.0, 0.0);
		glScalef(5.0f, 10.0f, 75.0f);
		glGetFloatv(GL_MODELVIEW_MATRIX,wall3.m);
		(wall3.clr)[0] = 0.0;
		(wall3.clr)[1] = 0.0;
		(wall3.clr)[2] = 0.0;
		wall3.display_list_id = BUILDING;
		wall3.sibling         = &wall4;
		wall3.child           = NULL;
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(-520.0, 50.0, 380.0);
		glScalef(105.0f, 10.0f, 5.0f);
		glGetFloatv(GL_MODELVIEW_MATRIX,wall4.m);
		(wall4.clr)[0] = 0.0;
		(wall4.clr)[1] = 0.0;
		(wall4.clr)[2] = 0.0;
		wall4.display_list_id = BUILDING;
		wall4.sibling         = &wall5;
		wall4.child           = NULL;
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-520.0, 50.0, -380.0);
		glScalef(105.0f, 10.0f, 5.0f);
		glGetFloatv(GL_MODELVIEW_MATRIX,wall5.m);
		(wall5.clr)[0] = 0.0;
		(wall5.clr)[1] = 0.0;
		(wall5.clr)[2] = 0.0;
		wall5.display_list_id = BUILDING;
		wall5.sibling         = &hill;
		wall5.child           = NULL;
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(-1000.0, 0.0, -500.0);
		glScalef(10.0f, 10.0f, 10.0f);
		glGetFloatv(GL_MODELVIEW_MATRIX,hill.m);
		(hill.clr)[0] = 0.0;
		(hill.clr)[1] = 0.0;
		(hill.clr)[2] = 0.0;
		hill.display_list_id = HILL;
		hill.sibling         = &motorcycle;
		hill.child           = NULL;
	glPopMatrix();

	glPushMatrix();
		glTranslatef(100.0, 0.0, 150.0);
		glGetFloatv(GL_MODELVIEW_MATRIX,motorcycle.m);
		(motorcycle.clr)[0] = 0.0;
		(motorcycle.clr)[1] = 0.0;
		(motorcycle.clr)[2] = 0.0;
		motorcycle.display_list_id = MOTOR;
		motorcycle.sibling         = &plants;
		motorcycle.child           = NULL;
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(-100.0, 0.0, -150.0);
		glGetFloatv(GL_MODELVIEW_MATRIX,plants.m);
		(plants.clr)[0] = 0.0;
		(plants.clr)[1] = 0.0;
		(plants.clr)[2] = 0.0;
		plants.display_list_id = PLANTS;
		plants.sibling         = NULL;
		plants.child           = NULL;
	glPopMatrix();

	glGetFloatv(GL_MODELVIEW_MATRIX,sky.m);
	(sky.clr)[0] = 0.0;
	(sky.clr)[1] = 0.0;
	(sky.clr)[2] = 0.0;
	sky.display_list_id = SKY;
	sky.disable[0] = GL_LIGHTING;
	sky.sibling         = &ground;
	sky.child           = NULL;
	
	
}
