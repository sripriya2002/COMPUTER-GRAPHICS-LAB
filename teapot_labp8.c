#include<stdio.h>
#include<GL/glut.h>
void tableLeg(double thick,double len){
	glPushMatrix();
	glTranslated(0,len/2,0);
	glScaled(thick,len,thick);
	glutSolidCube(1.0);
	glPopMatrix();
}
void table(double topWid,double topThick,double legThick,double legLen){
	glPushMatrix();
	glTranslated(0,legLen,0);
	glScaled(topWid,topThick,topWid);
	glutSolidCube(1.0);
	glPopMatrix();
	double dist=0.95*topWid/2.0-legThick/2.0;
	glPushMatrix();
	glTranslated(dist,0,dist);
	tableLeg(legThick,legLen);
	glTranslated(0,0,-2.0*dist);
	tableLeg(legThick,legLen);
	glTranslated(-2.0*dist,0,2.0*dist);
	tableLeg(legThick,legLen);
	glTranslated(0,0,-2.0*dist);
	tableLeg(legThick,legLen);
	glPopMatrix();
}
void display(){
	GLfloat matamb[]={0.7f,0.7f,0.7f,0.7f};
	GLfloat matdif[]={0.5f,0.5f,0.5f,0.5f};
	GLfloat matspec[]={1.0f,1.0f,1.0f,1.0f};
	GLfloat shine[]={50.0f};
	glMaterialfv(GL_FRONT,GL_AMBIENT,matamb);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,matdif);
	glMaterialfv(GL_FRONT,GL_SPECULAR,matspec);
	glMaterialfv(GL_FRONT,GL_SHININESS,shine);
	GLfloat lightPos[]={2.0f,6.0f,3.0f,0.0f};
	GLfloat lightIntensity[]={0.7f,0.7f,0.7f,0.7f};
	glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,lightIntensity);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0,2.0,-1.0,1.0,0.1,100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(2.3,1.3,2.0,0.0,0.25,0.0,0.0,1.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glTranslated(0.53,0.41,0.5);
	glRotated(30,0,1,0);
	glutSolidTeapot(0.08);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.4,0.0,0.4);
	table(0.6,0.02,0.02,0.3);
	glPopMatrix();
	glFlush();
}
void main(int argc,char **argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE|GLUT_DEPTH);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(640,480);
	glutCreateWindow("teapot");
	glutDisplayFunc(display);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	glClearColor(1.0,1.0,1.0,0.0);
	glViewport(0,0,640,480);
	glutMainLoop();
}
	
	
	
