#include<stdio.h>
#include<GL/glut.h>
float h=0.0,k=0.0,theta;
int choice;
void myInit();
void rotate_origin();
void rotate_fixed_point();
void draw_triangle();
void display_about_origin();
void display_about_fixed_point();
void rotate_origin()
{
	glRotatef(theta,0,0,1);
}
void rotate_fixed_point()
{
	glTranslatef(h,k,0);
	glRotatef(theta,0,0,1);
	glTranslatef(-h,-k,1);
}
void draw_triangle()
{
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(100,100);
	glVertex2f(400,100);
	glVertex2f(250,350);
	glEnd();
}
void display_about_origin()
{
	draw_triangle();
	rotate_origin();
	draw_triangle();
	glLoadIdentity();
	glFlush();
}
void display_about_fixed_point()
{
	draw_triangle();
	rotate_fixed_point();
	draw_triangle();
	glLoadIdentity();
	glFlush();
}
void myInit()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-500.0,500.0,-500.0,500.0);
	glMatrixMode(GL_MODELVIEW);
}
void main(int argc,char *argv[])
{
	printf("enter your choice:1->rotation about origin\n");
	printf("enter your choice:2->rotation about fixed point\n");
	scanf("%d",&choice);
	printf("enter the rotation angle\n");
	scanf("%f",&theta);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	if(choice==1)
	{
		glutCreateWindow("rotation of triangle w.r.t origin(4MT19CS162)\n");
		glutDisplayFunc(display_about_origin);
		
	}
	else if(choice==2)
	{
		printf("enter the pivot(x,y) point\n");
		scanf("%f%f",&h,&k);
		glutCreateWindow("rotation of a triange w.r.t fixed point(4MT19CS162)");
		glutDisplayFunc(display_about_fixed_point);
	}
	else{
		printf("wrong choice\n");
	}
	myInit();
	glutMainLoop();
}
		


	
