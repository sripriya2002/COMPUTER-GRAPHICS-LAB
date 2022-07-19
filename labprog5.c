#include<stdio.h>
#include<GL/glut.h>
typedef float point[3];
int n;
point v[4][3]={{0.0,0.0,1.0},{0.0,1.0,0.0},{-1.0,-0.5,0.0},{1.0,-0.5,0.0}};
void triangle(point a,point b,point c){
	glBegin(GL_TRIANGLES);
		glVertex3fv(a);
		glVertex3fv(b);
		glVertex3fv(c);
	glEnd();
}
void divide_tetra(point a,point b,point c,int m){
	point v1,v2,v3;
	int i;
	if(m>0){
		for(i=0;i<3;i++){
			v1[i]=(a[i]+b[i])/2;
			v2[i]=(a[i]+c[i])/2;
			v3[i]=(b[i]+c[i])/2;
		}
		divide_tetra(a,v1,v2,m-1);
		divide_tetra(c,v2,v3,m-1);
		divide_tetra(b,v3,v1,m-1);
	}
	else
		triangle(a,b,c);
}
void tetrahedron(int m){
	glColor3f(1.0,0.0,0.0);
	divide_tetra(v[0],v[1],v[2],m);
	glColor3f(0.0,1.0,0.0);
	divide_tetra(v[3],v[2],v[1],m);
	glColor3f(0.0,0.0,1.0);
	divide_tetra(v[0],v[3],v[1],m);
	glColor3f(0.0,0.0,0.0);
	divide_tetra(v[0],v[2],v[3],m);
}
void display(){
	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	tetrahedron(n);
	glFlush();
}
void myReshape(int w,int h){
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<=h){
		glOrtho(-2.0,2.0,-2.0*(float)h/(float)w,2.0*(float)h/(float)w,-10.0,10.0);
	}
	else{
		glOrtho(-2.0*(float)w/(float)h,2.0*(float)w/(float)h,-2.0,2.0,-10.0,10.0);
	}
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}
void main(int argc,char *argv[]){
	printf("enter the no of divivsions\n");
	scanf("%d",&n);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE|GLUT_DEPTH);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(700,700);
	glutCreateWindow("tetrahedron");
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}
	
