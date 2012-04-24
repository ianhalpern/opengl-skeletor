/**************************************
Camera Movement using gluLookAt
based on tutorials found at http://www.codecolony.de/
**************************************/

#include <GL/glut.h>
#include <math.h>
#define PI 3.1415926535897932

float get_angle_between_in_degrees(float ax, float ay, float bx, float by)
{
   float dotproduct, lengtha, lengthb, result;

   dotproduct = (ax * bx) + (ay * by);
   lengtha = sqrt(ax * ax + ay * ay);
   lengthb = sqrt(bx * bx + by * by);

   result = acos( dotproduct / (lengtha * lengthb) );

   if(dotproduct < 0)
   {
      if(result > 0)
         result += M_PI;
      else
         result -= M_PI;
   }
   result *= 180/M_PI; 
   return result;
}

GLfloat vpn[] = {0.0, 0.0,-1.0};
GLfloat u[] = {1.0, 0.0, 0.0};
GLfloat up[] = {0.0, 1.0, 0.0};
GLfloat eye[] = {0.0, 0.0,0.0};


GLfloat* vAdd(GLfloat v1[3], GLfloat v2[3]) {
	// Adds two vectors
	GLfloat *new_v = new GLfloat[3];
	new_v[0] = v1[0] + v2[0];
	new_v[1] = v1[1] + v2[1];
	new_v[2] = v1[2] + v2[2];
	return new_v;
}

GLfloat* vScale(GLfloat v[3], GLfloat scale) {
	// scales a vector size by 'scale' percent
	GLfloat *new_v = new GLfloat[3];
	new_v[0] = v[0] * scale;
	new_v[1] = v[1] * scale;
	new_v[2] = v[2] * scale;
	return new_v;
}

GLfloat* vSubtract(GLfloat v1[3], GLfloat v2[3]) {
	// subtracts two vectors
	return vAdd(v1, vScale(v2, -1.0));
}

GLfloat vLen(GLfloat v[3]) {
	// returns the length of a vector
	return sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
}

GLfloat deg2rad(GLfloat deg) {
	// converts degrees to radians
	return deg * PI / 180;
}

GLfloat* vToUnitVector(GLfloat v[3]) {
	// Converts a vector into a unit vector (a vector with length 1)
	GLfloat *new_v = new GLfloat[3];
	GLfloat len = vLen(v);
	if (len != 0.0) {
		new_v[0] = v[0] / len;
		new_v[1] = v[1] / len;
		new_v[2] = v[2] / len;
	}
	return new_v;
}

GLfloat* vCrossProduct (GLfloat v1[3], GLfloat v2[3]) {
	// returns a vector perpendicular to v1 and v2
	GLfloat *crossProduct = new GLfloat[3];
	crossProduct[0] = v2[1]*v1[2] - v2[2]*v1[1];
	crossProduct[1] = v2[2]*v1[0] - v2[0]*v1[2];
	crossProduct[2] = v2[0]*v1[1] - v2[1]*v1[0];

	return crossProduct;
}

void viewUpdate() {
	// generates the at point by adding the eye point to the view plane normal vector
	GLfloat *at = vAdd(eye, vpn);
	gluLookAt(eye[0], eye[1], eye[2], 
		   at[0],  at[1],  at[2],
		   up[0],  up[1],  up[2]);
}

void viewMoveTo(GLfloat dir[3]) {
	// Moves the eye in a direction vector
	GLfloat *eye_tmp = vAdd(eye, dir);
	eye[0] = eye_tmp[0];
	eye[1] = eye_tmp[1];
	eye[2] = eye_tmp[2];
}

void viewRot (GLfloat rotation, GLfloat v1[3], GLfloat v2[3], GLfloat v3[3], GLfloat dir) {
	// Rotates the camera around x, y, or z axis
	GLfloat *tmp = new GLfloat[3];
	tmp = vToUnitVector(
		vAdd(vScale(v1, cos(deg2rad(rotation))), vScale(vScale(v2, sin(deg2rad(rotation))), dir))
	);
	v1[0] = tmp[0];
	v1[1] = tmp[1];
	v1[2] = tmp[2];
	
	tmp = vScale(vCrossProduct(vpn, v3), -1*dir);
	
	v2[0] = tmp[0];
	v2[1] = tmp[1];
	v2[2] = tmp[2];
}

void viewRotAround (GLfloat rotation, GLfloat v1[3], GLfloat v2[3], GLfloat v3[3], GLfloat dir, GLfloat *around) {
	GLfloat *at_v1 = vScale(v1,-1);
	GLfloat *at_v2 = vScale(v2,-1);
	GLfloat *at_v3 = vScale(v3, 1);
	GLfloat *tmp  = new GLfloat[3];
	
	viewRot(rotation, at_v1, at_v2, at_v3, dir);
	tmp = vScale(at_v1,-1);
	v1[0] = tmp[0];
	v1[1] = tmp[1];
	v1[2] = tmp[2];
	
	tmp = vScale(  at_v2,-1);
	v2[0] = tmp[0];
	v2[1] = tmp[1];
	v2[2] = tmp[2];
	
	tmp = vScale( at_v3, 1);
	v3[0] = tmp[0];
	v3[1] = tmp[1];
	v3[2] = tmp[2];
	//printf("%f\n", vLen(vSubtract(around, eye)));
	
	tmp = vAdd(around, vScale(at_v1, vLen(vSubtract(around, eye))));
	eye[0] = tmp[0];
	eye[1] = tmp[1];
	eye[2] = tmp[2];
}

void viewPitch(GLfloat rotation) {
	// rotates the view around the X axis
	viewRot(rotation, vpn, up, u, 1.0);
}

void viewYaw(GLfloat rotation) {
	// rotates the view around the Y axis
	viewRot(rotation, vpn, u, up, -1.0);
}

void viewRoll(GLfloat rotation) {
	// rotates teh view around the Z axis
	viewRot(rotation, u, up, u, 1.0);
}

void viewLevelOut() {
	// Levels out the view to look forward along the xz plane
	up[0] = 0.0;
	up[1] = 1.0;
	up[2] = 0.0;
	
	vpn[1] = 0.0;
	
	float *u_tmp = vCrossProduct(vpn, up);
	u[0] = u_tmp[0];
	u[1] = u_tmp[1];
	u[2] = u_tmp[2];
}

void viewSlidePerpendicular( GLfloat d ) {
	// Slides the view forward or backward by scaling the vpn to 'd' distance, then adding that
	// vector the the current eye vector
	GLfloat *eye_tmp = vAdd(eye,  vScale(vpn,-d));
	eye[0] = eye_tmp[0];
	eye[1] = eye_tmp[1];
	eye[2] = eye_tmp[2];
}

void viewSlideHorizonally( GLfloat d ) {
	// Slides the view left or right by scaling the u vector to 'd' distance, then adding that
	// vector the the current eye vector
	GLfloat *eye_tmp = vAdd(eye,  vScale(u,d));
	eye[0] = eye_tmp[0];
	eye[1] = eye_tmp[1];
	eye[2] = eye_tmp[2];
}

void viewSlideUp( GLfloat d ) {
	// Slides the view up or down by scaling the up vector to 'd' distance, then adding that
	// vector the the current eye vector
	GLfloat *eye_tmp = vAdd(eye,  vScale(up,d));
	eye[0] = eye_tmp[0];
	eye[1] = eye_tmp[1];
	eye[2] = eye_tmp[2];
}

void viewYawAround( GLfloat *at, GLfloat rotation ) {
	viewRotAround(rotation, vpn, u, up, 1.0, at);
}

void viewPitchAround( GLfloat *at, GLfloat rotation ) {
	viewRotAround(rotation, vpn, up, u, -1.0, at);
}

void viewRollAround( GLfloat *at, GLfloat rotation ) {
	//viewRotAround(rotation, u, up, u, 1.0, at);
	// this doesn't really work
}
