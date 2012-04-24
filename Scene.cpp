#include <stdio.h>
#include <GL/glut.h>

#define N_ENABLE 10

bool drawingShadows = false;

float l[] = { 0.0,  380.0, -380.0, 1.0 }; // Coordinates of the light source
float n[] = { 0.0,  -1.0, 0.0 }; // Normal vector for the plane
float e[] = { 0.0, 0.0, 0.0 }; // Point of the plane


void glShadowProjection(float * l, float * e, float * n) {
	float d, c;
	float mat[16];

	// These are c and d (corresponding to the tutorial)
	
	d = n[0]*l[0] + n[1]*l[1] + n[2]*l[2];
	c = e[0]*n[0] + e[1]*n[1] + e[2]*n[2] - d;

	// Create the matrix. OpenGL uses column by column
	// ordering

	mat[0]	= l[0]*n[0]+c; 
	mat[4]	= n[1]*l[0]; 
	mat[8]	= n[2]*l[0]; 
	mat[12] = -l[0]*c-l[0]*d;
	
	mat[1]	= n[0]*l[1];				
	mat[5]	= l[1]*n[1]+c;
	mat[9]	= n[2]*l[1]; 
	mat[13] = -l[1]*c-l[1]*d;
	
	mat[2]	= n[0]*l[2];				
	mat[6]	= n[1]*l[2]; 
	mat[10] = l[2]*n[2]+c; 
	mat[14] = -l[2]*c-l[2]*d;
	
	mat[3]	= n[0];				
	mat[7]	= n[1]; 
	mat[11] = n[2]; 
	mat[15] = -d;

	// Finally multiply the matrices together *plonk*
	glMultMatrixf(mat);
}

typedef struct treenode{
	// treenode structure from Lecture 13
	GLfloat m[16];
	GLfloat clr[3];
	int display_list_id;
	GLint enable[N_ENABLE];
	GLint disable[N_ENABLE];
	bool drawShadow;
	struct treenode *child;
	struct treenode *sibling;
} treenode;

void traverse(treenode* node){
	// Directly based off the function in the Lecture 13
	if (node==NULL) return;
	
	
	
	glPushMatrix();
		bool wasEnabled[N_ENABLE];
		bool wasDisabled[N_ENABLE];
		for (int i = 0; i<N_ENABLE; i++) {
			if (node->enable[i]) {
				if (!glIsEnabled(node->enable[i])) wasDisabled[i] = true;
				glEnable(node->enable[i]);
			}
			if (node->disable[i]) {
				if (glIsEnabled(node->disable[i])) wasEnabled[i] = true;
				glDisable(node->disable[i]);
			}
		}
		
		glMultMatrixf(node->m);
		glColor3f((node->clr)[0],(node->clr)[1],(node->clr)[2]);
		if (node->display_list_id) glCallList(node->display_list_id);
		if(node->child != NULL) traverse(node->child);
		glColor3f(0.0,0.0,0.0);
		
		for (int i = 0; i<N_ENABLE; i++) {
			if (node->enable[i]) {
				if (wasDisabled[i]) glDisable(node->enable[i]);
			}
			if (node->disable[i]) {
				if (wasEnabled[i]) glEnable(node->disable[i]);
				
			}
		}
	glPopMatrix();
	
	if (node->drawShadow) {
		drawingShadows = true;
		glPushMatrix();
			glShadowProjection(l,e,n);	
			glDisable(GL_LIGHTING);
			glDisable (GL_TEXTURE_2D);
			glColor4f(0.1,0.1,0.1,1.0);
			//glDisable(GL_COLOR_MATERIAL);
			glMultMatrixf(node->m);
	//		glColor3f((node->clr)[0],(node->clr)[1],(node->clr)[2]);
			glCallList(node->display_list_id);
	//		if(node->child != NULL) traverse(node->child);
			//glEnable(GL_COLOR_MATERIAL) ;
		glPopMatrix();
		drawingShadows = false;
	}

	if(node->sibling != NULL) traverse(node->sibling);
}


