#include<stdio.h>
#include<stdbool.h>
#include<GL/glut.h>
float xvmin=200,yvmin=200,xvmax=300,yvmax=300;
float x0,y0,x1,y1;
float xmin,ymin,xmax,ymax;
const int LEFT=1;
const int RIGHT=2;
const int TOP=8;
const int BOTTOM=4;
int computecode(float x,float y){
	int code=0;
	if(y>ymax)
		code=code|TOP;
	else if(y<ymin)
		code=code|BOTTOM;
	if(x>xmax)
		code=code|RIGHT;
	else if(x<xmin)
		code=code|LEFT;
	return code;
}
void CSLCAD(float x0,float y0,float x1,float y1){
	bool done=false,accept=false;
	int outcode0,outcode1,outcodeout;
	outcode0=computecode(x0,y0);
	outcode1=computecode(x1,y1);
	do{
		if((outcode0 || outcode1)==0){
			done=true;
			accept=true;
		}
		else if((outcode0 & outcode1) !=0){
			done=true;
		}
		else{
			double x,y;
			outcodeout=outcode0?outcode0:outcode1;
			if(outcodeout & TOP){
				x=x0+(x1-x0)*(ymax-y0)/(y1-y0);
				y=ymax;
			}
			else if(outcodeout & BOTTOM){
				x=x0+(x1-x0)*(ymin-y0)/(y1-y0);
				y=ymin;
			}
			else if(outcodeout & RIGHT){
				y=y0+(y1-y0)*(xmax-x0)/(x1-x0);
				x=xmax;
			}
			else{
				y=y0+(y1-y0)*(xmin-x0)/(x1-x0);
				x=xmin;
			}
			if(outcodeout==outcode0){
				x0=x;
				y0=y;
				outcode0=computecode(x0,y0);
			}
			else{
				x1=x;
				y1=y;
				outcode1=computecode(x1,y1);
			}
		}
	}while(!done);
	if(accept){
		double sx=(xvmax-xvmin)/(xmax-xmin);
		double sy=(yvmax-yvmin)/(ymax-ymin);
		double vx0=xvmin+(x0-xmin)*sx;
		double vy0=yvmin+(y0-xmin)*sy;
		double vx1=xvmin+(x1-xmin)*sx;
		double vy1=yvmin+(y1-xmin)*sx;
		glColor3f(0,0,1);
		glBegin(GL_LINES);
		glVertex2d(vx0,vy0);
		glVertex2d(vx1,vy1);
		glEnd();
	}
	glColor3f(1,0,0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(xvmin,yvmin);
	glVertex2f(xvmax,yvmin);
	glVertex2f(xvmax,yvmax);
	glVertex2f(xvmin,yvmax);
	glEnd();
}
void lines(){
	glBegin(GL_LINES);
	glVertex2f(x0,y0);
	glVertex2f(x1,y1);
	glEnd();
}
void rect(){
	glBegin(GL_LINE_LOOP);
	glVertex2f(xmin,ymin);
	glVertex2f(xmax,ymin);
	glVertex2f(xmax,ymax);
	glVertex2f(xmin,ymax);
	glEnd();
}
void display(){
	glColor3f(1,0,0);
	lines();
	glColor3f(0,0,1);
	rect();
	CSLCAD(x0,y0,x1,y1);
	glFlush();
}
void myInit(){
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1,0,0);
	glPointSize(1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,499,0,499);
}
void main(int argc,char **argv){
	printf("enter the clipping cordinated\n");
	scanf("%f%f%f%f",&xmin,&ymin,&xmax,&ymax);
	printf("enter the line endpoints\n");
	scanf("%f%f%f%f",&x0,&y0,&x1,&y1);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(600,600);
	glutCreateWindow("line");
	glutDisplayFunc(display);
	myInit();
	glutMainLoop();
}
