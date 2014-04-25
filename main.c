//Aditya Ponukumati
//April 25, 2014
//N-Body Problem 
//
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
//
#define N  7
#define DT 0.00001
#define G  3
//
   typedef struct
   {
      double vx , vy , vz ;
      double  x ,  y ,  z ;
      double r ;
      double m ;
   } Body;
//
   Body nbody[N];
//
//
   double rho,phi,theta,up=1.0;
   double xc,yc,zc,xe,ye,ze;
   double max = 0;
//
    void look()
   {
      xe=xc+rho*sin(theta)*cos(phi);
      ye=zc+rho*cos(theta);
      ze=yc+rho*sin(theta)*sin(phi);
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      gluLookAt(xe,ye,ze, xc,yc,zc, 0.0,up,0.0);
   }
    void display(void)
   {
      int j;
   //
      glMatrixMode(GL_MODELVIEW);
      glClear(GL_COLOR_BUFFER_BIT);
      glColor3f(0.0,0.0,0.0);
      for(j=0;j<N;j++)
      { 
         glPushMatrix();
         glTranslated(nbody[j].x,nbody[j].y,nbody[j].z);
         glRotated(90.0,1.0,0.0,0.0);
         glutWireSphere(nbody[j].r, 24, 12);
         glPopMatrix();
      }
      glutSwapBuffers();
   }
    void idle(void)
   {
      int i,k;
      double dx,dy,dz,dmag,fmag;
      double ax[N],ay[N],az[N];
   
      for(i = 0; i < N; ++i)
      {
         for(k = 0; k < N; ++k)
         {
            if(i == k)
            {
               continue;
            }
            dx = nbody[k].x - nbody[i].x;
            dy = nbody[k].y - nbody[i].y;
            dz = nbody[k].z - nbody[i].z;
         
            dmag = sqrt(pow(dx, 2) + pow(dy, 2) + pow(dz, 2));
         
            fmag = -(G*nbody[i].m*nbody[k].m)/pow(dmag, 2);
         
            double fx = fmag*(dx/dmag);
            double fy = fmag*(dy/dmag);
            double fz = fmag*(dz/dmag);
         
            ax[k] = fx/nbody[k].m;
            ay[k] = fy/nbody[k].m;
            az[k] = fz/nbody[k].m;
         
            nbody[k].vx = nbody[k].vx + ax[k]*DT;
            nbody[k].vy = nbody[k].vy + ay[k]*DT;
            nbody[k].vz = nbody[k].vz + az[k]*DT;
         }
      }
      
   
      for(k = 0; k < N; ++k)
      {
         nbody[k].x = nbody[k].x + nbody[k].vx*DT;
         nbody[k].y = nbody[k].y + nbody[k].vy*DT;
         nbody[k].z = nbody[k].z + nbody[k].vz*DT;
      }
   
      look();
      glutPostRedisplay();
   }
    void mouse(int button,int state,int xscr,int yscr)
   {
      if(button == 3)
      {
         rho -= 0.05;
      }
      if(button == 4)
      {
         rho += 0.05;
      }
      look();
      glutPostRedisplay();
   }
    void motion(int xscr,int yscr)
   {
   //
   // change phi ... or theta and up
   //
      phi = 2*M_PI*(xscr/320.0);
      theta = 2*M_PI*(yscr/240.0);
      if((int)(theta / M_PI) % 2 == 1)
      {
         up = -1;
      }
      else
      {
         up = 1;
      }
   
      printf("%f\n", theta);
      look();
      glutPostRedisplay();
   }
    void mouse_wheel(int wheel,int direction,int xscr,int yscr)
   {
      look();
      glutPostRedisplay();
   }
    void keyfunc(unsigned char key,int xscr,int yscr)
   {
      if(key=='q')
      {
         exit(0);
      }
   }
    void specialfunc(int key,int xscr,int yscr)
   {
      if( key == GLUT_KEY_UP )
      {
         xe++;
         ye++;
         ze++;
      }
      if( key == GLUT_KEY_DOWN )
      {
         xe--;
         ye--;
         ze--;
      }
      look();
      glutPostRedisplay();
   }
    void reshape(int wscr,int hscr)
   {
      GLfloat aspect_ratio;
      aspect_ratio=(GLfloat)wscr/(GLfloat)hscr;
      glViewport(0,0,(GLsizei)wscr,(GLsizei)hscr);
   //
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluPerspective(60.0,aspect_ratio,0.1,500.0);
   //
      look();
   }
    int main(int argc,char* argv[])
   {  
      rho=1.0;
      phi=0.5*M_PI;
      theta=0.5*M_PI;
      xc=yc=zc=0.0;
   //
      nbody[0].m=10000.0; // sun
      nbody[0].r=0.2;
      nbody[0].x=0.0;
      nbody[0].y=0.0;
      nbody[0].z=0.0;
      nbody[0].vx=0.0;
      nbody[0].vy=0.0;
      nbody[0].vz=0.0;
   //
      nbody[1].m=100.0; // earth
      nbody[1].r=0.01;
      nbody[1].x=0.45;
      nbody[1].y=0.0;
      nbody[1].z=0.0;
      nbody[1].vx=0.0;
      nbody[1].vy=150;
      nbody[1].vz=0.0;
   //
      nbody[2].m=100.0;
      nbody[2].r=0.01;
      nbody[2].x=0.0;
      nbody[2].y=0.0;
      nbody[2].z=0.45;
      nbody[2].vx=150;
      nbody[2].vy=0.0;
      nbody[2].vz=0.0;
   //
      nbody[3].m=100.0;
      nbody[3].r=0.01;
      nbody[3].x=0.0;
      nbody[3].y=0.45;
      nbody[3].z=0.0;
      nbody[3].vx=0.0;
      nbody[3].vy=0.0;
      nbody[3].vz=150;
   //
      nbody[4].m=100.0;
      nbody[4].r=0.01;
      nbody[4].x=-0.45;
      nbody[4].y=0.0;
      nbody[4].z=0.0;
      nbody[4].vx=0.0;
      nbody[4].vy=-150;
      nbody[4].vz=0.0;
   //
      nbody[5].m=100.0;
      nbody[5].r=0.01;
      nbody[5].x=0.0;
      nbody[5].y=0.0;
      nbody[5].z=-0.45;
      nbody[5].vx=-150;
      nbody[5].vy=0.0;
      nbody[5].vz=0.0;
   //
      nbody[6].m=100.0;
      nbody[6].r=0.01;
      nbody[6].x=0.0;
      nbody[6].y=-0.45;
      nbody[6].z=0.0;
      nbody[6].vx=0.0;
      nbody[6].vy=0.0;
      nbody[6].vz=-150;
   //
      glutInit(&argc,argv);
      glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
      glutInitWindowSize(640,480);
      glutInitWindowPosition(100,50);
      glutCreateWindow("Foxes");
   //
      glClearColor(1.0,1.0,1.0,0.0);
      glShadeModel(GL_SMOOTH);
   //
      glutDisplayFunc(display);
      glutIdleFunc(idle);
      glutMouseFunc(mouse);
      glutMotionFunc(motion);
      glutMouseWheelFunc(mouse_wheel);
      glutKeyboardFunc(keyfunc);
      glutSpecialFunc(specialfunc);
      glutReshapeFunc(reshape);
   //
      glutMainLoop();
   //
      return 0;
   }
//
// end of file
//
