#include <stdlib.h>
#include<Windows.h>
#ifdef __APPLE__
#else
#include <GL/glut.h>
#endif
#include<math.h>
#include<stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/GLAUX.h>
#include <string.h>

int arr[] = {7,4,9,3,5,1,2};
float pos[] = {-15.0,-10.0,-5.0,0.0,5.0,10.0,15.0};
float shift[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float posI = -15.0, posJ = 15.0, posP = -15.0;
int state = 0, ishift=0;
int complete[] = {0,0,0,0,0,0,0};
float delayIter = 0.0;
int run=1;
float spin = 0.0;
double camX=0.0, camY=10.0, camZ=50.0;
double objX=0.0, objY=10.0, objZ=-50.0;
double lookSpeed=1.0, movingSpeed=1.0, iterSpeed=0.05;

void renderBitmapString(float x, float y, float z, void *font,const char *string){
    const char *c;
    glRasterPos3f(x, y, z);
    for (c=string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void quickSort (void){
    if(run==1)
        spin+=1;
    glutPostRedisplay();
    if(state==1){
        if(posI<-10.0){
            posI+=iterSpeed;
            glutPostRedisplay();
        }
        else if(posI<-5.0){
            posI+=iterSpeed;
            glutPostRedisplay();
        }
        else if(shift[2]<5.0 && ishift==0){
            shift[2]+=iterSpeed;
            shift[6]+=iterSpeed;
            glutPostRedisplay();
        }
        else if(pos[2]<15.0){
            pos[2]+=iterSpeed;
            pos[6]-=iterSpeed;
            glutPostRedisplay();
        }
        else if(shift[2]>0.0){
            ishift=1;
            shift[2]-=iterSpeed;
            shift[6]-=iterSpeed;
            glutPostRedisplay();
        }
        else{
            arr[2]=2, arr[6]=9;
            pos[2]=-5.0, pos[6]=15.0;
            posI = -5.0, posJ = 15.0, posP = -15.0;
            state++;
            ishift=0;
            glutPostRedisplay();
        }
    }

    if(state==2){
        if(posI<15.0){
            posI+=iterSpeed;
            glutPostRedisplay();
        }
        else if(posJ>10.0){
            posJ-=iterSpeed;
            glutPostRedisplay();
        }
        else if(shift[0]<5.0 && ishift==0){
            shift[0]+=iterSpeed;
            shift[5]+=iterSpeed;
            glutPostRedisplay();
        }
        else if(pos[0]<10.0){
            pos[0]+=iterSpeed;
            pos[5]-=iterSpeed;
            glutPostRedisplay();
        }
        else if(shift[0]>0.0){
            ishift=1;
            shift[0]-=iterSpeed;
            shift[5]-=iterSpeed;
            glutPostRedisplay();
        }
        else{
            complete[5]=1;
            arr[0]=1, arr[5]=7;
            pos[0]=-15.0, pos[5]=10.0;
            posI = -15.0, posJ = 5.0, posP = -15.0;
            state++;
            ishift=0;
            glutPostRedisplay();
        }
    }

    if(state==3){
        if(posI<-10.0){
            posI+=iterSpeed;
            glutPostRedisplay();
        }
        else if(posJ>-15.0){
            posJ-=iterSpeed;
            glutPostRedisplay();
        }
        else if(shift[0]<5.0 && ishift==0){
            shift[0]+=iterSpeed;
            glutPostRedisplay();
        }
        else if(shift[0]>0.0){
            ishift=1;
            shift[0]-=iterSpeed;
            glutPostRedisplay();
        }
        else{
            complete[0]=1;
            posI = -10.0, posJ = 5.0, posP = -10.0;
            state++;
            ishift=0;
            glutPostRedisplay();
        }
    }

    if(state==4){
        if(posI<5.0){
            posI+=iterSpeed;
            glutPostRedisplay();
        }
        else if(posJ>0.0){
            posJ-=iterSpeed;
            glutPostRedisplay();
        }
        else if(shift[1]<5.0 && ishift==0){
            shift[1]+=iterSpeed;
            shift[3]+=iterSpeed;
            glutPostRedisplay();
        }
        else if(pos[1]<0.0){
            pos[1]+=iterSpeed;
            pos[3]-=iterSpeed;
            glutPostRedisplay();
        }
        else if(shift[1]>0.0){
            ishift=1;
            shift[1]-=iterSpeed;
            shift[3]-=iterSpeed;
            glutPostRedisplay();
        }
        else{
            complete[3]=1;
            arr[1]=3, arr[3]=4;
            pos[1]=-10.0, pos[3]=0.0;
            posI = -10.0, posJ = -5.0, posP = -10.0;
            state++;
            ishift=0;
            glutPostRedisplay();
        }
    }

    if(state==5){
        if(posI<0.0){
            posI+=iterSpeed;
            glutPostRedisplay();
        }
        else if(shift[1]<5.0 && ishift==0){
            shift[1]+=iterSpeed;
            shift[2]+=iterSpeed;
            glutPostRedisplay();
        }
        else if(pos[1]<-5.0){
            pos[1]+=iterSpeed;
            pos[2]-=iterSpeed;
            glutPostRedisplay();
        }
        else if(shift[1]>0.0){
            ishift=1;
            shift[1]-=iterSpeed;
            shift[2]-=iterSpeed;
            glutPostRedisplay();
        }
        else{
            complete[2]=1;
            complete[1]=1;
            complete[4]=1;
            complete[6]=1;
            arr[1]=2, arr[2]=3;
            pos[1]=-10.0, pos[2]=-5.0;
            posI = -15.0, posJ = 15.0, posP = -15.0;
            state=0;
            ishift=0;
            glutPostRedisplay();
        }
    }
}

void wall(float x, float y, float z){
    glBegin(GL_QUADS);
        glColor3f(198.0/255.0, 190.0/255.0, 189.0/255.0);
        glVertex3f(x/2,y/2,z/2);					    // Top front Of The Quad (right)
        glVertex3f(x/2,y/2,-z/2);					    // Top back Of The Quad (right)
        glVertex3f(x/2,-y/2,-z/2);    					// Bottom back Of The Quad (right)
        glVertex3f(x/2,-y/2,z/2);	    				// Bottom front Of The Quad (right)

        glColor3f(198.0/255.0, 190.0/255.0, 189.0/255.0);
        glVertex3f(-x/2,y/2,z/2);					// Top front Of The Quad (left)
        glVertex3f(-x/2,y/2,-z/2);					// Top back Of The Quad (left)
        glVertex3f(-x/2,-y/2,-z/2);					// Bottom back Of The Quad (left)
        glVertex3f(-x/2,-y/2,z/2);					// Bottom front Of The Quad (left)

        glColor3f(224.0/255.0, 221.0/255.0, 213.0/255.0);
        glVertex3f(x/2,y/2,z/2);				    // Right front Of The Quad (top)
        glVertex3f(x/2,y/2,-z/2);				    // Right back Of The Quad (top)
        glVertex3f(-x/2,y/2,-z/2);				    // Left back Of The Quad (top)
        glVertex3f(-x/2,y/2,z/2);				    // Left front Of The Quad (top)

        glColor3f(255.0/255.0, 233.0/255.0, 183.0/255.0);
        glVertex3f(x/2,-y/2,z/2);					// Right front Of The Quad (bottom)
        glVertex3f(x/2,-y/2,-z/2);					// Right back Of The Quad (bottom)
        glVertex3f(-x/2,-y/2,-z/2);				    // Left back Of The Quad (bottom)
        glVertex3f(-x/2,-y/2,z/2);				    // Left front Of The Quad (bottom)


        glColor3f(200.0/255.0, 200.0/255.0, 200.0/255.0);
        glVertex3f(x/2,y/2,-z/2);					 // Top Right Of The Quad (Back)
        glVertex3f(-x/2,y/2,-z/2);					// Top Left Of The Quad (Back)
        glVertex3f(-x/2,-y/2,-z/2);					// Bottom Left Of The Quad (Back)
        glVertex3f(x/2,-y/2,-z/2);					// Bottom Right Of The Quad (Back)


        glColor3f(216.0/255.0, 214.0/255.0, 201.0/255.0);
        glVertex3f(x/2,y/2,z/2);					    // Top Right Of The Quad (Front)
        glVertex3f(-x/2,y/2,z/2);					// Top Left Of The Quad (Front)
        glVertex3f(-x/2,-y/2,z/2);					// Bottom Left Of The Quad (Front)
        glVertex3f(x/2,-y/2,z/2);					// Bottom Right Of The Quad (Front)

    glEnd();
}

void stand(float x, float y, float z){
    glBegin(GL_QUADS);
        glVertex3f(x/2,y/2,z/2);					    // Top front Of The Quad (right)
        glVertex3f(x/2,y/2,-z/2);					    // Top back Of The Quad (right)
        glVertex3f(x/2,-y/2,-z/2);    					// Bottom back Of The Quad (right)
        glVertex3f(x/2,-y/2,z/2);	    				// Bottom front Of The Quad (right)

        glVertex3f(-x/2,y/2,z/2);					// Top front Of The Quad (left)
        glVertex3f(-x/2,y/2,-z/2);					// Top back Of The Quad (left)
        glVertex3f(-x/2,-y/2,-z/2);					// Bottom back Of The Quad (left)
        glVertex3f(-x/2,-y/2,z/2);					// Bottom front Of The Quad (left)

        glVertex3f(x/2,y/2,z/2);				    // Right front Of The Quad (top)
        glVertex3f(x/2,y/2,-z/2);				    // Right back Of The Quad (top)
        glVertex3f(-x/2,y/2,-z/2);				    // Left back Of The Quad (top)
        glVertex3f(-x/2,y/2,z/2);				    // Left front Of The Quad (top)

        glVertex3f(x/2,-y/2,z/2);					// Right front Of The Quad (bottom)
        glVertex3f(x/2,-y/2,-z/2);					// Right back Of The Quad (bottom)
        glVertex3f(-x/2,-y/2,-z/2);				    // Left back Of The Quad (bottom)
        glVertex3f(-x/2,-y/2,z/2);				    // Left front Of The Quad (bottom)


        glVertex3f(x/2,y/2,-z/2);					 // Top Right Of The Quad (Back)
        glVertex3f(-x/2,y/2,-z/2);					// Top Left Of The Quad (Back)
        glVertex3f(-x/2,-y/2,-z/2);					// Bottom Left Of The Quad (Back)
        glVertex3f(x/2,-y/2,-z/2);					// Bottom Right Of The Quad (Back)


        glVertex3f(x/2,y/2,z/2);					    // Top Right Of The Quad (Front)
        glVertex3f(-x/2,y/2,z/2);					// Top Left Of The Quad (Front)
        glVertex3f(-x/2,-y/2,z/2);					// Bottom Left Of The Quad (Front)
        glVertex3f(x/2,-y/2,z/2);					// Bottom Right Of The Quad (Front)

    glEnd();
}

void cpu(float x, float y, float z){
    glBegin(GL_QUADS);
        glColor3f(10.0/255.0, 10.0/255.0, 10.0/255.0);
        glVertex3f(x/2,y/2,z/2);					    // Top front Of The Quad (right)
        glVertex3f(x/2,y/2,-z/2);					    // Top back Of The Quad (right)
        glVertex3f(x/2,-y/2,-z/2);    					// Bottom back Of The Quad (right)
        glVertex3f(x/2,-y/2,z/2);	    				// Bottom front Of The Quad (right)

        glVertex3f(-x/2,y/2,z/2);					// Top front Of The Quad (left)
        glVertex3f(-x/2,y/2,-z/2);					// Top back Of The Quad (left)
        glVertex3f(-x/2,-y/2,-z/2);					// Bottom back Of The Quad (left)
        glVertex3f(-x/2,-y/2,z/2);					// Bottom front Of The Quad (left)

        glVertex3f(x/2,y/2,z/2);				    // Right front Of The Quad (top)
        glVertex3f(x/2,y/2,-z/2);				    // Right back Of The Quad (top)
        glVertex3f(-x/2,y/2,-z/2);				    // Left back Of The Quad (top)
        glVertex3f(-x/2,y/2,z/2);				    // Left front Of The Quad (top)

        glVertex3f(x/2,-y/2,z/2);					// Right front Of The Quad (bottom)
        glVertex3f(x/2,-y/2,-z/2);					// Right back Of The Quad (bottom)
        glVertex3f(-x/2,-y/2,-z/2);				    // Left back Of The Quad (bottom)
        glVertex3f(-x/2,-y/2,z/2);				    // Left front Of The Quad (bottom)

        glVertex3f(x/2,y/2,-z/2);					 // Top Right Of The Quad (Back)
        glVertex3f(-x/2,y/2,-z/2);					// Top Left Of The Quad (Back)
        glVertex3f(-x/2,-y/2,-z/2);					// Bottom Left Of The Quad (Back)
        glVertex3f(x/2,-y/2,-z/2);					// Bottom Right Of The Quad (Back)

        glVertex3f(x/2,y/2,z/2);					    // Top Right Of The Quad (Front)
        glVertex3f(-x/2,y/2,z/2);					// Top Left Of The Quad (Front)
        glVertex3f(-x/2,-y/2,z/2);					// Bottom Left Of The Quad (Front)
        glVertex3f(x/2,-y/2,z/2);					// Bottom Right Of The Quad (Front)
    glEnd();

    glPushMatrix();
        glTranslatef(0,0.3,0.01);
        glScalef(0.7,0.1,1);
        glBegin(GL_QUADS);
            glColor3f(83.0/255.0, 85.0/255.0, 89.0/255.0);
            glVertex3f(x/2,y/2,z/2);					    // Top Right Of The Quad (Front)
            glVertex3f(-x/2,y/2,z/2);					// Top Left Of The Quad (Front)
            glVertex3f(-x/2,-y/2,z/2);					// Bottom Left Of The Quad (Front)
            glVertex3f(x/2,-y/2,z/2);					// Bottom Right Of The Quad (Front)
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-0.4,1.3,0.01);
        glScalef(0.05,0.03,1);
        glBegin(GL_QUADS);
            glColor3f(83.0/255.0, 85.0/255.0, 89.0/255.0);
            glVertex3f(x/2,y/2,z/2);					    // Top Right Of The Quad (Front)
            glVertex3f(-x/2,y/2,z/2);					// Top Left Of The Quad (Front)
            glVertex3f(-x/2,-y/2,z/2);					// Bottom Left Of The Quad (Front)
            glVertex3f(x/2,-y/2,z/2);					// Bottom Right Of The Quad (Front)
        glEnd();
    glPopMatrix();
}

void monitor(float x, float y, float z){
    //monitor body
    glPushMatrix();
        glRotatef(-4,1,0,0);
        glBegin(GL_QUADS);
            glColor3f(10.0/255.0, 10.0/255.0, 10.0/255.0);
            glVertex3f(x/2,y/2,z/2);					// Top front Of The Quad (right)
            glVertex3f(x/2,y/2,-z/2);					// Top back Of The Quad (right)
            glVertex3f(x/2,-y/2,-z/2);    				// Bottom back Of The Quad (right)
            glVertex3f(x/2,-y/2,z/2);	    			// Bottom front Of The Quad (right)

            glVertex3f(-x/2,y/2,z/2);					// Top front Of The Quad (left)
            glVertex3f(-x/2,y/2,-z/2);					// Top back Of The Quad (left)
            glVertex3f(-x/2,-y/2,-z/2);					// Bottom back Of The Quad (left)
            glVertex3f(-x/2,-y/2,z/2);					// Bottom front Of The Quad (left)

            glVertex3f(x/2,y/2,z/2);				    // Right front Of The Quad (top)
            glVertex3f(x/2,y/2,-z/2);				    // Right back Of The Quad (top)
            glVertex3f(-x/2,y/2,-z/2);				    // Left back Of The Quad (top)
            glVertex3f(-x/2,y/2,z/2);				    // Left front Of The Quad (top)

            glVertex3f(x/2,-y/2,z/2);					// Right front Of The Quad (bottom)
            glVertex3f(x/2,-y/2,-z/2);					// Right back Of The Quad (bottom)
            glVertex3f(-x/2,-y/2,-z/2);				    // Left back Of The Quad (bottom)
            glVertex3f(-x/2,-y/2,z/2);				    // Left front Of The Quad (bottom)

            glVertex3f(x/2,y/2,-z/2);					// Top Right Of The Quad (Back)
            glVertex3f(-x/2,y/2,-z/2);					// Top Left Of The Quad (Back)
            glVertex3f(-x/2,-y/2,-z/2);					// Bottom Left Of The Quad (Back)
            glVertex3f(x/2,-y/2,-z/2);					// Bottom Right Of The Quad (Back)

            glVertex3f(x/2,y/2,z/2);					// Top Right Of The Quad (Front)
            glVertex3f(-x/2,y/2,z/2);					// Top Left Of The Quad (Front)
            glVertex3f(-x/2,-y/2,z/2);					// Bottom Left Of The Quad (Front)
            glVertex3f(x/2,-y/2,z/2);					// Bottom Right Of The Quad (Front)
        glEnd();
    glPopMatrix();

    //screen
    glPushMatrix();
        glTranslatef(0,0.0,0.009);
        glRotatef(-4,1,0,0);
        glScalef(0.92,0.9,1);
        glBegin(GL_QUADS);
            glColor3f(100.0/255.0, 106.0/255.0, 117.0/255.0);
            glVertex3f(x/2,y/2,z/2);					    // Top Right Of The Quad (Front)
            glVertex3f(-x/2,y/2,z/2);					// Top Left Of The Quad (Front)
            glVertex3f(-x/2,-y/2,z/2);					// Bottom Left Of The Quad (Front)
            glVertex3f(x/2,-y/2,z/2);					// Bottom Right Of The Quad (Front)
        glEnd();
    glPopMatrix();

    //stand
    glPushMatrix();
        glTranslatef(0.0,-1.49,0.05);
        glColor3f(10.0/255.0, 10.0/255.0, 10.0/255.0);
        stand(.2,1,.1);
    glPopMatrix();

    //base
    glPushMatrix();
        glTranslatef(0.0,-1.99,0.05);
        glColor3f(10.0/255.0, 10.0/255.0, 10.0/255.0);
        stand(0.7,0.01,0.7);
    glPopMatrix();
}

void keyboard(float x, float y, float z){
    glPushMatrix();
        glBegin(GL_QUADS);
            glColor3f(10.0/255.0, 10.0/255.0, 10.0/255.0);
            glVertex3f(x/2,y/2,z/2);					    // Top front Of The Quad (right)
            glVertex3f(x/2,y/2,-z/2);					    // Top back Of The Quad (right)
            glVertex3f(x/2,-y/2,-z/2);    					// Bottom back Of The Quad (right)
            glVertex3f(x/2,-y/2,z/2);	    				// Bottom front Of The Quad (right)

            glVertex3f(-x/2,y/2,z/2);					// Top front Of The Quad (left)
            glVertex3f(-x/2,y/2,-z/2);					// Top back Of The Quad (left)
            glVertex3f(-x/2,-y/2,-z/2);					// Bottom back Of The Quad (left)
            glVertex3f(-x/2,-y/2,z/2);					// Bottom front Of The Quad (left)

            glVertex3f(x/2,y/2,z/2);				    // Right front Of The Quad (top)
            glVertex3f(x/2,y/2,-z/2);				    // Right back Of The Quad (top)
            glVertex3f(-x/2,y/2,-z/2);				    // Left back Of The Quad (top)
            glVertex3f(-x/2,y/2,z/2);				    // Left front Of The Quad (top)

            glVertex3f(x/2,-y/2,z/2);					// Right front Of The Quad (bottom)
            glVertex3f(x/2,-y/2,-z/2);					// Right back Of The Quad (bottom)
            glVertex3f(-x/2,-y/2,-z/2);				    // Left back Of The Quad (bottom)
            glVertex3f(-x/2,-y/2,z/2);				    // Left front Of The Quad (bottom)

            glVertex3f(x/2,y/2,-z/2);					 // Top Right Of The Quad (Back)
            glVertex3f(-x/2,y/2,-z/2);					// Top Left Of The Quad (Back)
            glVertex3f(-x/2,-y/2,-z/2);					// Bottom Left Of The Quad (Back)
            glVertex3f(x/2,-y/2,-z/2);					// Bottom Right Of The Quad (Back)

            glVertex3f(x/2,y/2,z/2);					    // Top Right Of The Quad (Front)
            glVertex3f(-x/2,y/2,z/2);					// Top Left Of The Quad (Front)
            glVertex3f(-x/2,-y/2,z/2);					// Bottom Left Of The Quad (Front)
            glVertex3f(x/2,-y/2,z/2);					// Bottom Right Of The Quad (Front)
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,0.0,0.005);
        glScalef(0.92,0.9,1);
        glBegin(GL_QUADS);
            glColor3f(100.0/255.0, 106.0/255.0, 117.0/255.0);
            glVertex3f(x/2,y/2,z/2);					    // Top Right Of The Quad (Front)
            glVertex3f(-x/2,y/2,z/2);					// Top Left Of The Quad (Front)
            glVertex3f(-x/2,-y/2,z/2);					// Bottom Left Of The Quad (Front)
            glVertex3f(x/2,-y/2,z/2);					// Bottom Right Of The Quad (Front)
        glEnd();
    glPopMatrix();
}

void mouse(float x, float y, float z){
    glPushMatrix();
        glBegin(GL_QUADS);
            glColor3f(10.0/255.0, 10.0/255.0, 10.0/255.0);
            glVertex3f(x/2,y/2,z/2);					    // Top front Of The Quad (right)
            glVertex3f(x/2,y/2,-z/2);					    // Top back Of The Quad (right)
            glVertex3f(x/2,-y/2,-z/2);    					// Bottom back Of The Quad (right)
            glVertex3f(x/2,-y/2,z/2);	    				// Bottom front Of The Quad (right)

            glVertex3f(-x/2,y/2,z/2);					// Top front Of The Quad (left)
            glVertex3f(-x/2,y/2,-z/2);					// Top back Of The Quad (left)
            glVertex3f(-x/2,-y/2,-z/2);					// Bottom back Of The Quad (left)
            glVertex3f(-x/2,-y/2,z/2);					// Bottom front Of The Quad (left)

            glVertex3f(x/2,y/2,z/2);				    // Right front Of The Quad (top)
            glVertex3f(x/2,y/2,-z/2);				    // Right back Of The Quad (top)
            glVertex3f(-x/2,y/2,-z/2);				    // Left back Of The Quad (top)
            glVertex3f(-x/2,y/2,z/2);				    // Left front Of The Quad (top)

            glVertex3f(x/2,-y/2,z/2);					// Right front Of The Quad (bottom)
            glVertex3f(x/2,-y/2,-z/2);					// Right back Of The Quad (bottom)
            glVertex3f(-x/2,-y/2,-z/2);				    // Left back Of The Quad (bottom)
            glVertex3f(-x/2,-y/2,z/2);				    // Left front Of The Quad (bottom)

            glVertex3f(x/2,y/2,-z/2);					 // Top Right Of The Quad (Back)
            glVertex3f(-x/2,y/2,-z/2);					// Top Left Of The Quad (Back)
            glVertex3f(-x/2,-y/2,-z/2);					// Bottom Left Of The Quad (Back)
            glVertex3f(x/2,-y/2,-z/2);					// Bottom Right Of The Quad (Back)

            glVertex3f(x/2,y/2,z/2);					    // Top Right Of The Quad (Front)
            glVertex3f(-x/2,y/2,z/2);					// Top Left Of The Quad (Front)
            glVertex3f(-x/2,-y/2,z/2);					// Bottom Left Of The Quad (Front)
            glVertex3f(x/2,-y/2,z/2);					// Bottom Right Of The Quad (Front)
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,0.0,0.005);
        glScalef(0.92,0.9,1);
        glBegin(GL_QUADS);
            glColor3f(100.0/255.0, 106.0/255.0, 117.0/255.0);
            glVertex3f(x/2,y/2,z/2);					    // Top Right Of The Quad (Front)
            glVertex3f(-x/2,y/2,z/2);					// Top Left Of The Quad (Front)
            glVertex3f(-x/2,-y/2,z/2);					// Bottom Left Of The Quad (Front)
            glVertex3f(x/2,-y/2,z/2);					// Bottom Right Of The Quad (Front)
        glEnd();
    glPopMatrix();
}

void desk(float x, float y, float z){
    //table
    glBegin(GL_QUADS);
        glColor3f(170.0/255.0, 139.0/255.0, 77.0/255.0);
        glVertex3f(x/2,y/2,z/2);					    // Top front Of The Quad (right)
        glVertex3f(x/2,y/2,-z/2);					    // Top back Of The Quad (right)
        glVertex3f(x/2,-y/2,-z/2);    					// Bottom back Of The Quad (right)
        glVertex3f(x/2,-y/2,z/2);	    				// Bottom front Of The Quad (right)

        glColor3f(170.0/255.0, 139.0/255.0, 77.0/255.0);
        glVertex3f(-x/2,y/2,z/2);					// Top front Of The Quad (left)
        glVertex3f(-x/2,y/2,-z/2);					// Top back Of The Quad (left)
        glVertex3f(-x/2,-y/2,-z/2);					// Bottom back Of The Quad (left)
        glVertex3f(-x/2,-y/2,z/2);					// Bottom front Of The Quad (left)

        glColor3f(150.0/255.0, 119.0/255.0, 60.0/255.0);
        glVertex3f(x/2,y/2,z/2);				    // Right front Of The Quad (top)
        glVertex3f(x/2,y/2,-z/2);				    // Right back Of The Quad (top)
        glVertex3f(-x/2,y/2,-z/2);				    // Left back Of The Quad (top)
        glVertex3f(-x/2,y/2,z/2);				    // Left front Of The Quad (top)


        glColor3f(150.0/255.0, 119.0/255.0, 60.0/255.0);
        glVertex3f(x/2,-y/2,z/2);					// Right front Of The Quad (bottom)
        glVertex3f(x/2,-y/2,-z/2);					// Right back Of The Quad (bottom)
        glVertex3f(-x/2,-y/2,-z/2);				    // Left back Of The Quad (bottom)
        glVertex3f(-x/2,-y/2,z/2);				    // Left front Of The Quad (bottom)

        glVertex3f(x/2,y/2,-z/2);					 // Top Right Of The Quad (Back)
        glVertex3f(-x/2,y/2,-z/2);					// Top Left Of The Quad (Back)
        glVertex3f(-x/2,-y/2,-z/2);					// Bottom Left Of The Quad (Back)
        glVertex3f(x/2,-y/2,-z/2);					// Bottom Right Of The Quad (Back)
    glEnd();

    //cpu
    glPushMatrix();
        glTranslatef(0.5,-0.5,0);
        cpu(1,3,1);
    glPopMatrix();

    //monitor
    glPushMatrix();
        glTranslatef(0.0,4.0,-0.5);
        monitor(2,2,0.1);
    glPopMatrix();

    //keyboard
    glPushMatrix();
        glTranslatef(-0.3,2.03,0.5);
        keyboard(2,0.05,0.6);
    glPopMatrix();

    //mouse
    glPushMatrix();
        glTranslatef(1.15,2.08,0.5);
        mouse(0.5,0.15,0.3);
    glPopMatrix();
}

void chair(float x, float y, float z){
    glColor3f(34.0/255.0, 40.0/255.0, 38.0/255.0);
    //back part
    glPushMatrix();
        glTranslatef(0,1,0.7);
        glScalef(0.7,0.6,0.08);
        glBegin(GL_QUADS);
            glVertex3f(x/2,y/2,z/2);					    // Top front Of The Quad (right)
            glVertex3f(x/2,y/2,-z/2);					    // Top back Of The Quad (right)
            glVertex3f(x/2,-y/2,-z/2);    					// Bottom back Of The Quad (right)
            glVertex3f(x/2,-y/2,z/2);	    				// Bottom front Of The Quad (right)

            glVertex3f(-x/2,y/2,z/2);					// Top front Of The Quad (left)
            glVertex3f(-x/2,y/2,-z/2);					// Top back Of The Quad (left)
            glVertex3f(-x/2,-y/2,-z/2);					// Bottom back Of The Quad (left)
            glVertex3f(-x/2,-y/2,z/2);					// Bottom front Of The Quad (left)

            glVertex3f(x/2,y/2,z/2);				    // Right front Of The Quad (top)
            glVertex3f(x/2,y/2,-z/2);				    // Right back Of The Quad (top)
            glVertex3f(-x/2,y/2,-z/2);				    // Left back Of The Quad (top)
            glVertex3f(-x/2,y/2,z/2);				    // Left front Of The Quad (top)

            glVertex3f(x/2,-y/2,z/2);					// Right front Of The Quad (bottom)
            glVertex3f(x/2,-y/2,-z/2);					// Right back Of The Quad (bottom)
            glVertex3f(-x/2,-y/2,-z/2);				    // Left back Of The Quad (bottom)
            glVertex3f(-x/2,-y/2,z/2);				    // Left front Of The Quad (bottom)

            glVertex3f(x/2,y/2,-z/2);					 // Top Right Of The Quad (Back)
            glVertex3f(-x/2,y/2,-z/2);					// Top Left Of The Quad (Back)
            glVertex3f(-x/2,-y/2,-z/2);					// Bottom Left Of The Quad (Back)
            glVertex3f(x/2,-y/2,-z/2);					// Bottom Right Of The Quad (Back)

            glVertex3f(x/2,y/2,z/2);					    // Top Right Of The Quad (Front)
            glVertex3f(-x/2,y/2,z/2);					// Top Left Of The Quad (Front)
            glVertex3f(-x/2,-y/2,z/2);					// Bottom Left Of The Quad (Front)
            glVertex3f(x/2,-y/2,z/2);					// Bottom Right Of The Quad (Front)
        glEnd();
    glPopMatrix();

    //seat
    glPushMatrix();
        glTranslatef(0,0,0);
        glScalef(0.7,0.1,0.7);
        glBegin(GL_QUADS);
            glVertex3f(x/2,y/2,z/2);					    // Top front Of The Quad (right)
            glVertex3f(x/2,y/2,-z/2);					    // Top back Of The Quad (right)
            glVertex3f(x/2,-y/2,-z/2);    					// Bottom back Of The Quad (right)
            glVertex3f(x/2,-y/2,z/2);	    				// Bottom front Of The Quad (right)

            glVertex3f(-x/2,y/2,z/2);					// Top front Of The Quad (left)
            glVertex3f(-x/2,y/2,-z/2);					// Top back Of The Quad (left)
            glVertex3f(-x/2,-y/2,-z/2);					// Bottom back Of The Quad (left)
            glVertex3f(-x/2,-y/2,z/2);					// Bottom front Of The Quad (left)

            glVertex3f(x/2,y/2,z/2);				    // Right front Of The Quad (top)
            glVertex3f(x/2,y/2,-z/2);				    // Right back Of The Quad (top)
            glVertex3f(-x/2,y/2,-z/2);				    // Left back Of The Quad (top)
            glVertex3f(-x/2,y/2,z/2);				    // Left front Of The Quad (top)

            glVertex3f(x/2,-y/2,z/2);					// Right front Of The Quad (bottom)
            glVertex3f(x/2,-y/2,-z/2);					// Right back Of The Quad (bottom)
            glVertex3f(-x/2,-y/2,-z/2);				    // Left back Of The Quad (bottom)
            glVertex3f(-x/2,-y/2,z/2);				    // Left front Of The Quad (bottom)

            glVertex3f(x/2,y/2,-z/2);					 // Top Right Of The Quad (Back)
            glVertex3f(-x/2,y/2,-z/2);					// Top Left Of The Quad (Back)
            glVertex3f(-x/2,-y/2,-z/2);					// Bottom Left Of The Quad (Back)
            glVertex3f(x/2,-y/2,-z/2);					// Bottom Right Of The Quad (Back)

            glVertex3f(x/2,y/2,z/2);					    // Top Right Of The Quad (Front)
            glVertex3f(-x/2,y/2,z/2);					// Top Left Of The Quad (Front)
            glVertex3f(-x/2,-y/2,z/2);					// Bottom Left Of The Quad (Front)
            glVertex3f(x/2,-y/2,z/2);					// Bottom Right Of The Quad (Front)
        glEnd();
    glPopMatrix();

    //legs
    for(float i=0.6; i>=-1.2; i-=1.2){
        //front legs
        glPushMatrix();
            glTranslatef(-0.75,-1.45,i);
            glScalef(0.09,0.7,0.09);
            glBegin(GL_QUADS);
                glVertex3f(x/2,y/2,z/2);					    // Top front Of The Quad (right)
                glVertex3f(x/2,y/2,-z/2);					    // Top back Of The Quad (right)
                glVertex3f(x/2,-y/2,-z/2);    					// Bottom back Of The Quad (right)
                glVertex3f(x/2,-y/2,z/2);	    				// Bottom front Of The Quad (right)

                glVertex3f(-x/2,y/2,z/2);					// Top front Of The Quad (left)
                glVertex3f(-x/2,y/2,-z/2);					// Top back Of The Quad (left)
                glVertex3f(-x/2,-y/2,-z/2);					// Bottom back Of The Quad (left)
                glVertex3f(-x/2,-y/2,z/2);					// Bottom front Of The Quad (left)

                glVertex3f(x/2,y/2,z/2);				    // Right front Of The Quad (top)
                glVertex3f(x/2,y/2,-z/2);				    // Right back Of The Quad (top)
                glVertex3f(-x/2,y/2,-z/2);				    // Left back Of The Quad (top)
                glVertex3f(-x/2,y/2,z/2);				    // Left front Of The Quad (top)

                glVertex3f(x/2,-y/2,z/2);					// Right front Of The Quad (bottom)
                glVertex3f(x/2,-y/2,-z/2);					// Right back Of The Quad (bottom)
                glVertex3f(-x/2,-y/2,-z/2);				    // Left back Of The Quad (bottom)
                glVertex3f(-x/2,-y/2,z/2);				    // Left front Of The Quad (bottom)

                glVertex3f(x/2,y/2,-z/2);					 // Top Right Of The Quad (Back)
                glVertex3f(-x/2,y/2,-z/2);					// Top Left Of The Quad (Back)
                glVertex3f(-x/2,-y/2,-z/2);					// Bottom Left Of The Quad (Back)
                glVertex3f(x/2,-y/2,-z/2);					// Bottom Right Of The Quad (Back)

                glVertex3f(x/2,y/2,z/2);					    // Top Right Of The Quad (Front)
                glVertex3f(-x/2,y/2,z/2);					// Top Left Of The Quad (Front)
                glVertex3f(-x/2,-y/2,z/2);					// Bottom Left Of The Quad (Front)
                glVertex3f(x/2,-y/2,z/2);					// Bottom Right Of The Quad (Front)
            glEnd();
        glPopMatrix();

        //back legs
        glPushMatrix();
            glTranslatef(0.75,-1.45,i);
            glScalef(0.09,0.7,0.09);
            glBegin(GL_QUADS);
                glVertex3f(x/2,y/2,z/2);					    // Top front Of The Quad (right)
                glVertex3f(x/2,y/2,-z/2);					    // Top back Of The Quad (right)
                glVertex3f(x/2,-y/2,-z/2);    					// Bottom back Of The Quad (right)
                glVertex3f(x/2,-y/2,z/2);	    				// Bottom front Of The Quad (right)

                glVertex3f(-x/2,y/2,z/2);					// Top front Of The Quad (left)
                glVertex3f(-x/2,y/2,-z/2);					// Top back Of The Quad (left)
                glVertex3f(-x/2,-y/2,-z/2);					// Bottom back Of The Quad (left)
                glVertex3f(-x/2,-y/2,z/2);					// Bottom front Of The Quad (left)

                glVertex3f(x/2,y/2,z/2);				    // Right front Of The Quad (top)
                glVertex3f(x/2,y/2,-z/2);				    // Right back Of The Quad (top)
                glVertex3f(-x/2,y/2,-z/2);				    // Left back Of The Quad (top)
                glVertex3f(-x/2,y/2,z/2);				    // Left front Of The Quad (top)

                glVertex3f(x/2,-y/2,z/2);					// Right front Of The Quad (bottom)
                glVertex3f(x/2,-y/2,-z/2);					// Right back Of The Quad (bottom)
                glVertex3f(-x/2,-y/2,-z/2);				    // Left back Of The Quad (bottom)
                glVertex3f(-x/2,-y/2,z/2);				    // Left front Of The Quad (bottom)

                glVertex3f(x/2,y/2,-z/2);					 // Top Right Of The Quad (Back)
                glVertex3f(-x/2,y/2,-z/2);					// Top Left Of The Quad (Back)
                glVertex3f(-x/2,-y/2,-z/2);					// Bottom Left Of The Quad (Back)
                glVertex3f(x/2,-y/2,-z/2);					// Bottom Right Of The Quad (Back)

                glVertex3f(x/2,y/2,z/2);					    // Top Right Of The Quad (Front)
                glVertex3f(-x/2,y/2,z/2);					// Top Left Of The Quad (Front)
                glVertex3f(-x/2,-y/2,z/2);					// Bottom Left Of The Quad (Front)
                glVertex3f(x/2,-y/2,z/2);					// Bottom Right Of The Quad (Front)
            glEnd();
        glPopMatrix();
    }
}

void projector(float x, float y, float z){
    //stand
    glPushMatrix();
        glTranslatef(0.0,1.0,0.0);
        glColor3f(100.0/255.0, 106.0/255.0, 117.0/255.0);
        stand(.2,2,.2);
    glPopMatrix();

    //projector body
    glBegin(GL_QUADS);
        glColor3f(65.0/255.0, 107.0/255.0, 175.0/255.0);
        glVertex3f(x/2,y/2,z/2);					    // Top front Of The Quad (right)
        glVertex3f(x/2,y/2,-z/2);					    // Top back Of The Quad (right)
        glVertex3f(x/2,-y/2,-z/2);    					// Bottom back Of The Quad (right)
        glVertex3f(x/2,-y/2,z/2);	    				// Bottom front Of The Quad (right)

        //glColor3f(110.0/255.0, 117.0/255.0, 130.0/255.0);
        glVertex3f(-x/2,y/2,z/2);					// Top front Of The Quad (left)
        glVertex3f(-x/2,y/2,-z/2);					// Top back Of The Quad (left)
        glVertex3f(-x/2,-y/2,-z/2);					// Bottom back Of The Quad (left)
        glVertex3f(-x/2,-y/2,z/2);					// Bottom front Of The Quad (left)


        //glColor3f(105.0/255.0, 120.0/255.0, 128.0/255.0);
        glVertex3f(x/2,y/2,z/2);				    // Right front Of The Quad (top)
        glVertex3f(x/2,y/2,-z/2);				    // Right back Of The Quad (top)
        glVertex3f(-x/2,y/2,-z/2);				    // Left back Of The Quad (top)
        glVertex3f(-x/2,y/2,z/2);				    // Left front Of The Quad (top)


        //glColor3f(105.0/255.0, 120.0/255.0, 128.0/255.0);
        glVertex3f(x/2,-y/2,z/2);					// Right front Of The Quad (bottom)
        glVertex3f(x/2,-y/2,-z/2);					// Right back Of The Quad (bottom)
        glVertex3f(-x/2,-y/2,-z/2);				    // Left back Of The Quad (bottom)
        glVertex3f(-x/2,-y/2,z/2);				    // Left front Of The Quad (bottom)


        //glColor3f(100.0/255.0, 112.0/255.0, 125.0/255.0);
        glVertex3f(x/2,y/2,-z/2);					 // Top Right Of The Quad (Back)
        glVertex3f(-x/2,y/2,-z/2);					// Top Left Of The Quad (Back)
        glVertex3f(-x/2,-y/2,-z/2);					// Bottom Left Of The Quad (Back)
        glVertex3f(x/2,-y/2,-z/2);					// Bottom Right Of The Quad (Back)


        //glColor3f(100.0/255.0, 112.0/255.0, 125.0/255.0);
        glVertex3f(x/2,y/2,z/2);					    // Top Right Of The Quad (Front)
        glVertex3f(-x/2,y/2,z/2);					// Top Left Of The Quad (Front)
        glVertex3f(-x/2,-y/2,z/2);					// Bottom Left Of The Quad (Front)
        glVertex3f(x/2,-y/2,z/2);					// Bottom Right Of The Quad (Front)
    glEnd();

    //base
    glPushMatrix();
        glTranslatef(0,1.54,0);
        glScalef(.3,1,.3);
        glBegin(GL_QUADS);
            glColor3f(100.0/255.0, 106.0/255.0, 117.0/255.0);
            glVertex3f(x/2,y/2,z/2);				    // Right front Of The Quad (top)
            glVertex3f(x/2,y/2,-z/2);				    // Right back Of The Quad (top)
            glVertex3f(-x/2,y/2,-z/2);				    // Left back Of The Quad (top)
            glVertex3f(-x/2,y/2,z/2);				    // Left front Of The Quad (top)
        glEnd();
    glPopMatrix();

    //lens
    glPushMatrix();
        glTranslatef(0.5,0.0,-0.9);
        glScalef(0.1,0.1,0.1);
        glColor3f(1,1,1);
        glutSolidSphere(2,20,20);
    glPopMatrix();
}

void fan(float x, float y, float z){
    //stand
    glPushMatrix();
        glTranslatef(0.0,1.0,0.0);
        glColor3f(100.0/255.0, 106.0/255.0, 117.0/255.0);
        stand(.2,2,.2);
    glPopMatrix();

    //base
    glPushMatrix();
        glTranslatef(0,1.99,0);
        glScalef(.8,1,.1);
        glBegin(GL_QUADS);
            glColor3f(100.0/255.0, 106.0/255.0, 117.0/255.0);
            glVertex3f(x/2,y/2,z/2);				    // Right front Of The Quad (top)
            glVertex3f(x/2,y/2,-z/2);				    // Right back Of The Quad (top)
            glVertex3f(-x/2,y/2,-z/2);				    // Left back Of The Quad (top)
            glVertex3f(-x/2,y/2,z/2);				    // Left front Of The Quad (top)
        glEnd();
    glPopMatrix();

    //fan hands
    glPushMatrix();
        glRotatef(spin,0,1,0);
        glPushMatrix();
            glRotatef(90,0,1,0);
            glBegin(GL_QUADS);
                glColor3f(105.0/255.0, 120.0/255.0, 128.0/255.0);
                glVertex3f(x/2,-y/2,z/2);					// Right front Of The Quad (bottom)
                glVertex3f(x/2,-y/2,-z/2);					// Right back Of The Quad (bottom)
                glVertex3f(-x/2,-y/2,-z/2);				    // Left back Of The Quad (bottom)
                glVertex3f(-x/2,-y/2,z/2);				    // Left front Of The Quad (bottom)
            glEnd();
        glPopMatrix();

        glPushMatrix();
            glBegin(GL_QUADS);
                glColor3f(105.0/255.0, 120.0/255.0, 128.0/255.0);
                glVertex3f(x/2,-y/2,z/2);					// Right front Of The Quad (bottom)
                glVertex3f(x/2,-y/2,-z/2);					// Right back Of The Quad (bottom)
                glVertex3f(-x/2,-y/2,-z/2);				    // Left back Of The Quad (bottom)
                glVertex3f(-x/2,-y/2,z/2);				    // Left front Of The Quad (bottom)
            glEnd();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.0,0.0,0.0);
            glScalef(0.15,0.15,0.15);
            glColor3f(1,1,1);
            glutSolidSphere(2,20,20);
        glPopMatrix();
    glPopMatrix();
}

void door(float x, float y, float z){
    glBegin(GL_QUADS);
        glVertex3f(x/2,y/2,z/2);					    // Top front Of The Quad (right)
        glVertex3f(x/2,y/2,-z/2);					    // Top back Of The Quad (right)
        glVertex3f(x/2,-y/2,-z/2);    					// Bottom back Of The Quad (right)
        glVertex3f(x/2,-y/2,z/2);	    				// Bottom front Of The Quad (right)
    glEnd();
}

void plane(float x, float y, float z){
    glBegin(GL_QUADS);
        glVertex3f(x/2,-y/2,z/2);					// Right front Of The Quad (bottom)
        glVertex3f(x/2,-y/2,-z/2);					// Right back Of The Quad (bottom)
        glVertex3f(-x/2,-y/2,-z/2);				    // Left back Of The Quad (bottom)
        glVertex3f(-x/2,-y/2,z/2);				    // Left front Of The Quad (bottom)
    glEnd();
}

void whiteBoard(){
    glBegin(GL_QUADS);
        glColor3f(218.0/255.0, 224.0/255.0, 234.0/255.0);
        glVertex3f(13/2,4/2,0.0f);					    // Top Right Of The Quad (Front)
        glVertex3f(-13/2,4/2,0.0f);					// Top Left Of The Quad (Front)
        glVertex3f(-13/2,-4/2,0.0f);					// Bottom Left Of The Quad (Front)
        glVertex3f(13/2,-4/2,0.0f);					// Bottom Right Of The Quad (Front)
    glEnd();
}

void roof(){
    glBegin(GL_QUADS);

            glColor3f(26.0/255.0f, 49.0/255.0f, 119.0/255.0f);
            glVertex3f(5.0f,5.0f,20.0f);					    // Top front Of The Quad (right)
            glVertex3f(5.0f,5.0f,1.0f);					    // Top back Of The Quad (right)
            glVertex3f(0.5f,-5.0f,3.0f);					// Bottom back Of The Quad (right)
            glVertex3f(0.5f,-5.0f,18.0f);					// Bottom front Of The Quad (right)

            glColor3f(26.0/255.0f, 49.0/255.0f, 119.0/255.0f);
            glVertex3f(-5.0f,5.0f,20.0f);					// Top front Of The Quad (left)
            glVertex3f(-5.0f,5.0f,1.0f);					// Top back Of The Quad (left)
            glVertex3f(-0.5f,-5.0f,3.0f);					// Bottom back Of The Quad (left)
            glVertex3f(-0.5f,-5.0f,18.0f);					// Bottom front Of The Quad (left)


            glColor3f(242.0/255.0f, 198.0/255.0f, 164.0/255.0f);
            glVertex3f(5.0f,5.0f,20.0f);					    // Right front Of The Quad (top)
            glVertex3f(5.0f,5.0f,1.0f);					    // Right back Of The Quad (top)
            glVertex3f(-5.0f,5.0f,1.0f);				    // Left back Of The Quad (top)
            glVertex3f(-5.0f,5.0f,20.0f);				    // Left front Of The Quad (top)


            glColor3f(119.0/255.0f, 87.0/255.0f, 62.0/255.0f);
            glVertex3f(0.5f,-5.0f,18.0f);					// Right front Of The Quad (bottom)
            glVertex3f(0.5f,-5.0f,3.0f);					// Right back Of The Quad (bottom)
            glVertex3f(-0.5f,-5.0f,3.0f);				    // Left back Of The Quad (bottom)
            glVertex3f(-0.5f,-5.0f,18.0f);				    // Left front Of The Quad (bottom)


            glColor3f(74.0/255.0f, 109.0/255.0f, 214.0/255.0f);
            glVertex3f(5.0f,5.0f,1.0f);					 // Top Right Of The Quad (Back)
            glVertex3f(-5.0f,5.0f,1.0f);					// Top Left Of The Quad (Back)
            glVertex3f(-0.5f,-5.0f,3.0f);					// Bottom Left Of The Quad (Back)
            glVertex3f(0.5f,-5.0f,3.0f);					// Bottom Right Of The Quad (Back)

            glColor3f(74.0/255.0f, 109.0/255.0f, 214.0/255.0f);
            glVertex3f(5.0f,5.0f,20.0f);					    // Top Right Of The Quad (Front)
            glVertex3f(-5.0f,5.0f,20.0f);					// Top Left Of The Quad (Front)
            glVertex3f(-0.5f,-5.0f,18.0f);					// Bottom Left Of The Quad (Front)
            glVertex3f(0.5f,-5.0f,18.0f);					// Bottom Right Of The Quad (Front)

        glEnd();
}

void crown(){
    //crown body
    glBegin(GL_QUADS);
        glColor3f(209.0/255.0f, 162.0/255.0f, 35.0/255.0f);
        glVertex3f(1.0f,1.0f,3.0f);
        glVertex3f(1.0f,6.0f,3.0f);
        glVertex3f(1.0f,1.0f,1.0f);
        glVertex3f(1.0f,6.0f,1.0f);

        glColor3f(181.0/255.0f, 141.0/255.0f, 36.0/255.0f);
        glVertex3f(3.0f,1.0f,3.0f);
        glVertex3f(3.0f,6.0f,3.0f);
        glVertex3f(3.0f,1.0f,1.0f);
        glVertex3f(3.0f,6.0f,1.0f);

        glColor3f(188.0/255.0f, 151.0/255.0f, 38.0/255.0f);
        glVertex3f(1.0f,1.0f,3.0f);
        glVertex3f(1.0f,6.0f,3.0f);
        glVertex3f(3.0f,1.0f,3.0f);
        glVertex3f(3.0f,6.0f,3.0f);

        glColor3f(191.0/255.0f, 145.0/255.0f, 37.0/255.0f);
        glVertex3f(1.0f,1.0f,1.0f);
        glVertex3f(1.0f,6.0f,1.0f);
        glVertex3f(3.0f,1.0f,1.0f);
        glVertex3f(3.0f,6.0f,1.0f);

        glColor3f(165.0/255.0f, 200.0/255.0f, 35.0/255.0f);
        glVertex3f(0.8f,6.0f,3.2f);
        glVertex3f(0.8f,5.0f,3.2f);
        glVertex3f(0.8f,6.0f,0.8f);
        glVertex3f(0.8f,5.0f,0.8f);

        glColor3f(170.0/255.0f, 200.0/255.0f, 36.0/255.0f);
        glVertex3f(3.2f,6.0f,3.2f);
        glVertex3f(3.2f,5.0f,3.2f);
        glVertex3f(3.2f,6.0f,0.8f);
        glVertex3f(3.2f,5.0f,0.8f);

        glColor3f(160.0/255.0f, 200.0/255.0f, 38.0/255.0f);
        glVertex3f(0.8f,6.0f,3.2f);
        glVertex3f(0.8f,5.0f,3.2f);
        glVertex3f(3.2f,6.0f,3.2f);
        glVertex3f(3.2f,5.0f,3.2f);

        glColor3f(150.0/255.0f, 200.0/255.0f, 37.0/255.0f);
        glVertex3f(0.8f,6.0f,0.8f);
        glVertex3f(0.8f,5.0f,0.8f);
        glVertex3f(3.2f,6.0f,0.8f);
        glVertex3f(3.2f,5.0f,0.8f);
    glEnd();

    //ball
    glPushMatrix();
        glTranslatef(2.0f,-0.4f,2.0f);
        glScalef(1.0f,1.0f,1.0f);
        glColor3f(110.0/255.0f, 190.0/255.0f, 235.0/255.0f);
        glutSolidSphere(2,300,300);
    glPopMatrix();
}

void room(){

    //projector
    glPushMatrix();
        glTranslatef(0,8.5,0.0);
        glScalef(.5,.5,.5);
        projector(2,0.9,1.8);
    glPopMatrix();

    //whiteboard
    glPushMatrix();
        glTranslatef(0.0,5.0,-14.9);
        glScalef(1,1.5,1);
        whiteBoard();
    glPopMatrix();

    //desks
    for(float i=-1.0; i<=11.0; i+=5.0){
        //desk1
        glPushMatrix();
            glTranslatef(-7.0,1.0,i);
            glScalef(.7,.7,1);
            desk(3,4,2.0);
        glPopMatrix();

        //desk2
        glPushMatrix();
            glTranslatef(-3.0,1.0,i);
            glScalef(.7,.7,1);
            desk(3,4,2.0);
        glPopMatrix();

        //desk3
        glPushMatrix();
            glTranslatef(3.0,1.0,i);
            glScalef(.7,.7,1);
            desk(3,4,2.0);
        glPopMatrix();

        //desk4
        glPushMatrix();
            glTranslatef(7.0,1.0,i);
            glScalef(.7,.7,1);
            desk(3,4,2.0);
        glPopMatrix();
    }

    //chairs
    for(float i=1.0; i<=14.0; i+=5.0){
        //chair1
        glPushMatrix();
            glTranslatef(-7.0,1.5,i);
            glScalef(.7,.7,0.7);
            chair(3,4,2.0);
        glPopMatrix();

        //chair2
        glPushMatrix();
            glTranslatef(-3.0,1.5,i);
            glScalef(.7,.7,0.7);
            chair(3,4,2.0);
        glPopMatrix();

        //chair3
        glPushMatrix();
            glTranslatef(3.0,1.5,i);
            glScalef(.7,.7,0.7);
            chair(3,4,2.0);
        glPopMatrix();

        //chair4
        glPushMatrix();
            glTranslatef(7.0,1.5,i);
            glScalef(.7,.7,0.7);
            chair(3,4,2.0);
        glPopMatrix();
    }

    //roof
    glPushMatrix();
        glTranslatef(0.0,14.55,-18.5);
        glRotatef(180,0,0,1);
        glScalef(2.1,1,1.7);
        glColor3f(40.0/255.0, 127.0/255.0, 62.0/255.0);
        roof();
    glPopMatrix();

    //wall
    glPushMatrix();
        glTranslatef(0.0,4.5,0.0);
        glColor3f(216.0/255.0, 214.0/255.0, 201.0/255.0);
        wall(20,10,30);
    glPopMatrix();

    //door1
    glPushMatrix();
        glTranslatef(9.49,3,-12.0);
        glColor3f(135.0/255.0, 103.0/255.0, 28.0/255.0);
        door(1,7,3.5);
    glPopMatrix();

    //door2
    glPushMatrix();
        glTranslatef(9.6,3,-12.0);
        glColor3f(135.0/255.0, 103.0/255.0, 28.0/255.0);
        door(1,7,3.5);
    glPopMatrix();

    for(int i=0; i<=10; i+=5){
        //fan1
        glPushMatrix();
            glTranslatef(-5.0,8.5,i);
            glScalef(.5,.5,.5);
            fan(0.6,0,6);
        glPopMatrix();

        //fan2
        glPushMatrix();
            glTranslatef(5.0,8.5,i);
            glScalef(.5,.5,.5);
            fan(0.6,0,6);
        glPopMatrix();
    }

    //crown
    glPushMatrix();
        glTranslatef(-8.0f,2.5f,-15.0f);
        glScalef(0.3f,0.5f,0.3f);
        glRotatef(180,0.0f,0.0f,1.0f);
        crown();
    glPopMatrix();

    //plane
    glPushMatrix();
        glTranslatef(0.0,-0.01,0.0);
        glColor3f(40.0/255.0, 127.0/255.0, 62.0/255.0);
        plane(30,1,40);
    glPopMatrix();
}


void init(void){

   glClearColor (0, 0, 0, 0);
}

void display(void){

    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT); // GL_COLOR_BUFFER_BIT indicates that the buffer is currently enabled for color writing, GL_DEPTH_BUFFER_BIT indicates that the buffer is currently enabled for depth buffer

    glMatrixMode(GL_PROJECTION);       // Specify which matrix is the current matrix mode
        glLoadIdentity();                  // Replace the current matrix with the identity matrix and essentially resets the matrix back to its default state
        int w=glutGet(GLUT_WINDOW_WIDTH);
        int h=glutGet(GLUT_WINDOW_HEIGHT);
        gluPerspective(60,w/h,0.01,500);    // fovy specifies the field of view angle in degrees in y direction, aspect specifies aspect ratio that determines the field of view in the x direction, znear and zfar specifies the distance from viewer to the near and far clipping plane respectively (always positive)

    glMatrixMode(GL_MODELVIEW);       //  To allow modeling and viewing transformation on 3D object
    glLoadIdentity();
    gluLookAt(                       //  eyex, eyey, eyez specify the position of the eye point, centerx, centery, centerz specify the position of reference point, upx, upy, upz specify the direction of up vector
               camX,camY,camZ,
               objX,objY,objZ,
               0,1,0
             );

    glPushMatrix();
        glTranslatef(0,-5,0.0f);
        glScalef(3.5,3.7,3.7);
        room();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,12,-51.5);
        if(state!=0){
            glPushMatrix();
                glTranslatef(2,5,0);
                char c[12];
                itoa(abs(state),c,10);
                char str[13];
                strcpy(str,"Iteration: ");
                strcat(str,c);
                renderBitmapString(1,1,1,GLUT_BITMAP_TIMES_ROMAN_24,str);
            glPopMatrix();
        }

        glPushMatrix();
            glScalef(0.8,0.6,1);
            char c[2];
            for(int i=0; i<7; i++){
                glPushMatrix();
                    itoa(arr[i],c,10);
                    if(complete[i]==1)
                        glColor3f(36.0/255.0f, 55.0/255.0f, 125.0/255.0f);
                    else
                        glColor3f(255/255.0f, 0/255.0f, 0/255.0f);
                    renderBitmapString(pos[i],shift[i],0.0f,GLUT_BITMAP_TIMES_ROMAN_24,c);
                glPopMatrix();
            }
            glPushMatrix();
                renderBitmapString(-21,10.0f,0.7f,GLUT_BITMAP_TIMES_ROMAN_24,"Quick Sort");
                renderBitmapString(posI,-5.0f,0.0f,GLUT_BITMAP_TIMES_ROMAN_24,"i");
                renderBitmapString(posJ,-5.0f,0.0f,GLUT_BITMAP_TIMES_ROMAN_24,"j");
                renderBitmapString(posP,-10.0f,0.0f,GLUT_BITMAP_TIMES_ROMAN_24,"p");
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
    glutSwapBuffers();
}

void my_keyboard(unsigned char key, int p, int q){
    switch (key) {

        //movement
        case 'w':
            if(camX > objX)
                camX -= movingSpeed;
            else if(camX < objX)
                camX += movingSpeed;

            if(camZ > objZ)
                camZ -= movingSpeed;
            else if(camZ < objZ)
                camZ += movingSpeed;

            glutPostRedisplay();
            break;
        case 'a':
            if(camX > objX){
                camZ += movingSpeed;
                objZ += movingSpeed;
            }
            else if(camX < objX){
                camZ -= movingSpeed;
                objZ -= movingSpeed;
            }

            if(camZ > objZ){
                camX -= movingSpeed;
                objX -= movingSpeed;
            }
            else if(camZ < objZ){
                camX += movingSpeed;
                objX += movingSpeed;
            }
            glutPostRedisplay();
            break;
        case 's':
            if(camX > objX)
                camX += movingSpeed;
            else if(camX < objX)
                camX -= movingSpeed;

            if(camZ > objZ)
                camZ += movingSpeed;
            else if(camZ < objZ)
                camZ -= movingSpeed;

            glutPostRedisplay();
            break;
        case 'd':
            if(camX > objX){
                camZ -= movingSpeed;
                objZ -= movingSpeed;
            }
            else if(camX < objX){
                camZ += movingSpeed;
                objZ += movingSpeed;
            }

            if(camZ > objZ){
                camX += movingSpeed;
                objX += movingSpeed;
            }
            else if(camZ < objZ){
                camX -= movingSpeed;
                objX -= movingSpeed;
            }
            glutPostRedisplay();
            break;

        //up down
        case 32: //space bar
            camY += movingSpeed;
            objY += movingSpeed;
            glutPostRedisplay();
            break;
        case 'c':
            camY -= movingSpeed;
            objY -= movingSpeed;
            glutPostRedisplay();
            break;

        //front view
        case 'i':
            camX=0.0,camY=10.0,camZ=50.0;
            objX=0.0,objY=10.0,objZ=-50.0;
            glutPostRedisplay();
            break;

        //back view
        case 'k':
            camX=0.0,camY=7.0,camZ=-50.0;
            objX=0.0,objY=7.0,objZ=50.0;
            glutPostRedisplay();
            break;

        //right view
        case 'l':
            camX=30.0,camY=7.0,camZ=10.0;
            objX=-50.0,objY=7.0,objZ=10.0;
            glutPostRedisplay();
            break;

        //left view
        case 'j':
            camX=-30.0,camY=7.0,camZ=10.0;
            objX=50.0,objY=7.0,objZ=10.0;
            glutPostRedisplay();
            break;

        //start
        case 13: //Enter
            if(state==0){
                arr[0]=7, arr[1]=4, arr[2]=9, arr[3]=3, arr[4]=5, arr[5]=1, arr[6]=2;
                state=1;
                for(int i=0; i<7; i++)
                    complete[i]=0;
                glutIdleFunc(quickSort);
            } else
                state*=-1;
            break;

        //speed up
        case 'm': //ESC
            iterSpeed*=2;
            break;

        //slow down
        case 'n': //ESC
            iterSpeed/=2;
            break;

        //exit
        case 27: //ESC
            exit(0);

         default:
            break;
    }
}

void specialKeys(int key,int x,int y){
    if(key==GLUT_KEY_RIGHT){
        if(objX >= camX)
            objZ += lookSpeed;
        else
            objZ -= lookSpeed;

        if(objZ >= camZ)
            objX -= lookSpeed;
        else
            objX += lookSpeed;
    }


    else if(key==GLUT_KEY_LEFT){
        if(objX >= camX)
            objZ -= lookSpeed;
        else
            objZ += lookSpeed;

        if(objZ >= camZ)
            objX += lookSpeed;
        else
            objX -= lookSpeed;
    }


    else if(key==GLUT_KEY_UP){
        objY += lookSpeed;
    }
    else if(key==GLUT_KEY_DOWN){
        objY -= lookSpeed;
    }

    glutPostRedisplay();
}

void mouse(int button, int state, int s, int t){
    switch (button)
   {
      case GLUT_LEFT_BUTTON:
         if (state == GLUT_DOWN)
            run*=-1;
            glutPostRedisplay();
         break;
      case GLUT_RIGHT_BUTTON:
         if (state == GLUT_DOWN)
            //glutIdleFunc();
          break;
      case GLUT_MIDDLE_BUTTON:
          if (state == GLUT_DOWN)
            //glutIdleFunc(NULL);
         break;
      default:
         break;
   }
}

int main()
{
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (1920, 1280);
	glutInitWindowPosition (0, 0);
	glutCreateWindow ("Quick Sort");
	init();
	glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(my_keyboard);
    glutMouseFunc(mouse);
    glutIdleFunc(quickSort);
	glutMainLoop();
	return 0;
}
