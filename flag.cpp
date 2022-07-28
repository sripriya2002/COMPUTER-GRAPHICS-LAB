#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
#define PI 3.1428
int flag;
GLsizei winWidth=600,winHeight=600;
GLfloat xmin=0,ymin=0,xmax=130,ymax=130;

struct wcpt3d{
	GLfloat x,y,z;
};
void bino(GLint n,GLint *c){
	GLint k,j;
	for(k=0;k<=n;k++){
		c[k]=1;
		for(j=n;j>=k+1;j--)
			c[k]*=j;
		for(j=n-k;j>=2;j--)
			c[k]/=j;
	}
}
void compute(GLfloat u,struct wcpt3d *bezpt,GLint nctrlpt,struct wcpt3d *ctrlpt,GLint *c){
	GLint k,n=nctrlpt-1;
	bezpt->x=bezpt->y=bezpt->z=0;
	GLfloat Bezblend;
	for(k=0;k<nctrlpt;k++){
		Bezblend=c[k]*pow(u,k)*pow(1-u,n-k);
		bezpt->x+=ctrlpt[k].x*Bezblend;
		bezpt->y+=ctrlpt[k].y*Bezblend;
		bezpt->z+=ctrlpt[k].z*Bezblend;
	}
}
void bezier(struct wcpt3d *ctrlpt,GLint nctrlpt,GLint bezcurvept){
	struct wcpt3d bezcurve;
	GLint k,c[nctrlpt];
	bino(nctrlpt-1,c);
	
	glBegin(GL_LINE_STRIP);
	for(k=0;k<=bezcurvept;k++){
		GLfloat u=GLfloat(k)/GLfloat(bezcurvept);
		compute(u,&bezcurve,nctrlpt,ctrlpt,c);
		glVertex2f(bezcurve.x,bezcurve.y);
	}
	glEnd();
}
void display(){
	GLint nctrlpt=4,nbezpt=20;
	static float theta=0;
	GLint i;
	struct wcpt3d ctrlpt[4]={{20,100,0},{30,110,0},{50,90,0},{60,100,0}};
	if(flag==0)
		glClear(GL_COLOR_BUFFER_BIT);
	else{
		ctrlpt[1].x+=10*sin(theta*PI/180);
		ctrlpt[1].y+=5*sin(theta*PI/180);
		ctrlpt[2].x-=10*sin((theta+30)*PI/180);
		ctrlpt[2].y-=10*sin((theta+30)*PI/180);
		ctrlpt[3].x-=4*sin(theta*PI/180);
		ctrlpt[3].y-=sin((theta-30)*PI/180);
		theta+=0.5;
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1,1,1);
		glPointSize(5);
		glPushMatrix();
		glLineWidth(5);
		glColor3f(1,0.5,0);
		for(i=0;i<8;i++){
			glTranslatef(0,-0.8,0);
			bezier(ctrlpt,nctrlpt,nbezpt);
		}
		glColor3f(1,1,1);
		for(i=0;i<8;i++){
			glTranslatef(0,-0.8,0);
			bezier(ctrlpt,nctrlpt,nbezpt);
		}
		glColor3f(0,1,0);
		for(i=0;i<8;i++){
			glTranslatef(0,-0.8,0);
			bezier(ctrlpt,nctrlpt,nbezpt);
		}
		glPopMatrix();
		glColor3f(1,0,0.5);
		glLineWidth(5);
		glBegin(GL_LINES);
		glVertex2f(20,100);
		glVertex2f(20,40);
		glEnd();
		glFlush();
		glutPostRedisplay();
		glutSwapBuffers();
	}
}
void disp(){
	display();
}
void winReshapeFunc(GLint newWidth,GLint newHeight){
	glViewport(0,0,newWidth,newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(xmin,xmax,ymin,ymax);
}
void menu(int c){
	switch(c){
		case 1:flag=1;
			break;
		case 2:exit(0);
	}
}

int main(int argc,char **argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(winWidth,winHeight);
	glutCreateWindow("indian flag");
	glutDisplayFunc(disp);
	glutReshapeFunc(winReshapeFunc);
	glutCreateMenu(menu);
	glutAddMenuEntry("draw",1);

	glutAddMenuEntry("exit",2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}
