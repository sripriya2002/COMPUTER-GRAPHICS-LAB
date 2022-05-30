#include<stdio.h>
#include<GL/glut.h>
void myInit(){
	glClearColor(0.0,0.0,0.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0,200.0,0.0,200.0);
}
void lines(){
	glLineWidth(10.0);
	glBegin(GL_LINES);
		glVertex2i(20,60);
		glVertex2i(180,45);
	glEnd();	
	glBegin(GL_LINE_STRIP);
		glVertex2i(10,30);
		glVertex2i(30,50);
		glVertex2i(40,20);
		glVertex2i(40,90);
	glEnd();
	
	glFlush();
}
void main(int argc,char* argv[]){
	printf("Name is sripriya and usn is 4MT19CS161\n");
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(0,0);
	glutCreateWindow("lines primitive");
	glutInitWindowSize(500,500);
	myInit();
	glutDisplayFunc(lines);
	glutMainLoop();
}

	
