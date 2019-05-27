//#include <Windows.h>
//#include <gl/GL.h>    // OpenGL
//#include <gl/GLU.h>   // OpenGL Utility Library
//#include <GL/glut.h>  // OpenGL Utility Toolkit

#include <GL/freeglut.h>  // Free OpenGL Utility Toolkit for creating windows, initializing OpenGL contexts, and handling input events
#include <glm.hpp>  // OpenGL Mathematics. A C++ mathematics library for graphics programming 

#include "Viewport.h"
#include "Camera.h"
#include "Scene.h"

#include <iostream>

using namespace std;

//---------- Global variables -------------------------------------------------------------

// Viewport position and size
//Viewport viewPort(800, 600);
Viewport* vp1 = new Viewport(800, 600);
Viewport* vp2 = new Viewport(800, 600);
// Camera position, view volume and projection
//Camera camera(&viewPort);
Camera* cam1 = new Camera(vp1);
Camera* cam2 = new Camera(vp2);
// Graphics objects of the scene
Scene scene;
Scene scene2;

GLuint last_updated_tick = 0;

bool auto_update = true;
bool baldosas = false;
bool twoPorts = false;
bool coloDrone = false;

//Dichiarare due variabili per vedere le coordinate del mouse
glm::dvec2 mCoord;
int mBot = 0;

int CLIENT_WIDTH = 800;
int CLIENT_HEIGHT = 600;
//----------- Callbacks ----------------------------------------------------

void display();
void resize(int newWidth, int newHeight);
void key(unsigned char key, int x, int y);
void specialKey(int key, int x, int y);
void update();
void embaldosar(int nCol);

//Callbacks della diapositiva 17 della camera, si generano quando si spinge o si lascia
//il bottone del mouse e raccoglie nelle coordinate della finestra (x,y) il momento in cui lo stato del 
//bottone è cambiato dallo stare da spinto a rilasciato.
void mouse(int button, int state, int x, int y);
//Si genera quando un bottone del mouse è spinto o rilasciato per le coordinatee della finestra (x,y).
void motion(int x, int y);

void mouseWheel(int n, int d, int x, int y);
//-------------------------------------------------------------------------

int main(int argc, char *argv[])
{
	cout << "Starting console..." << '\n';

	// Initialization
	glutInit(&argc, argv);

	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);			// GLUT_CORE_PROFILE
	glutInitContextFlags(GLUT_DEBUG);							// GLUT_FORWARD_COMPATIBLE

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutInitWindowSize(CLIENT_WIDTH, CLIENT_HEIGHT);
	//glutInitWindowSize(800, 600);								// Window Size
	//glutInitWindowPosition (140, 140);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH	/*| GLUT_STENCIL*/); 
																// RGBA colors, double buffer, depth buffer and stencil buffer   
	int win = glutCreateWindow("IG1App");						// Window's Identifier

	// Callback registration
	glutReshapeFunc(resize);
	glutKeyboardFunc(key);
	glutSpecialFunc(specialKey);
	glutDisplayFunc(display);
	glutIdleFunc(update);
	//Nuovi eventi del mouse (diapositiva 18 camera)
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutMouseWheelFunc(mouseWheel);

	cout << glGetString(GL_VERSION) << '\n';
	cout << glGetString(GL_VENDOR) << '\n';

	// After creating the context
	cam1->set3D();
	scene.init();
	//scene.practica2_22();
	//scene2.init2();
	//cam2->set3D();

	glutMainLoop();

	//cin.ignore(INT_MAX, '\n');  cin.get();  
	glutDestroyWindow(win);										 // Destroy the context 

	return 0;
}
//-------------------------------------------------------------------------

void display()													 // double buffering
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Se la variabile booleana twoPorts è true, implementa due ViewPort
	if (twoPorts) {
		// Ricava la larghezza della finestra
		GLdouble ancho = glutGet(GLUT_WINDOW_WIDTH);

		GLdouble SVAratio = (cam1->getxRight() - cam1->getxLeft()) / (cam1->getyTop() - cam1->getyBot());
		GLdouble w = (GLdouble)ancho / (GLdouble)2;
		GLdouble h = w / SVAratio;
		// Prima ViewPort
		Viewport *vp1 = new Viewport(w, h);
		// Parte da 0
		vp1->uploadPos((GLint)0, (GLint)h / 2);
		vp1->upload();
		cam1->setVP(vp1);
		cam1->uploadPM();
		scene.render(cam1->getViewMat());
		// Seconda ViewPort
		Viewport * vp2 = new Viewport(w, h);
		// Parte da w che è GLUT_WINDOW_WIDTH/2
		vp2->uploadPos((GLint)w, (GLint)h / 2);
		vp2->upload();
		cam2->setVP(vp2);
		cam2->uploadPM();
		scene2.render(cam2->getViewMat());

		/*
		Viewport * vp1 = new Viewport(CLIENT_WIDTH, CLIENT_HEIGHT);
		vp1->uploadPos((GLint)-CLIENT_WIDTH / 4, (GLint)0);
		vp1->upload();
		camera->setVP(vp1);
		scene.render(camera->getViewMat());

		Viewport * vp2 = new Viewport(CLIENT_WIDTH, CLIENT_HEIGHT);
		vp2->uploadPos((GLint)CLIENT_WIDTH / 4, (GLint)0);
		vp2->upload();
		camera2->setVP(vp2);
		scene2.render(camera2->getViewMat());
		*/

	}
	else {
		//Se viene richiesto l'impiastrellamento, baldosas è true e fa vedere la scena 1 per 4 volte
		if (baldosas) {
			embaldosar(2);											// 2 = nCol
		}
		else {
		// Se non viene richiesto né twoPorts né baldosas, 
		// crea una sola viewPort di grandezza standard new Viewport(CLIENT_WIDTH, CLIENT_HEIGHT);
			Viewport* vp = new Viewport(CLIENT_WIDTH, CLIENT_HEIGHT);
			vp->upload();
			cam1->setVP(vp);
			scene.render(cam1->getViewMat());
		}
	}

	glutSwapBuffers();
}
//-------------------------------------------------------------------------

void update()
{

	bool need_redisplay = true;
	//GLuint tiempo = glutGet(GLUT_ELAPSED_TIME) - last_updated_tick;
	//if (auto_update == true && tiempo > 50) {
	if (auto_update) {

		if (twoPorts) {
			scene2.update(glutGet(GLUT_ELAPSED_TIME) - last_updated_tick);
		}
		scene.update(glutGet(GLUT_ELAPSED_TIME) - last_updated_tick);
		last_updated_tick = glutGet(GLUT_ELAPSED_TIME);
	}

	if (need_redisplay)
		glutPostRedisplay();

}

void embaldosar(int nCol)
{
	GLdouble SVAratio = (cam1->getxRight() - cam1->getxLeft()) / (cam1->getyTop() - cam1->getyBot());
	GLdouble w = (GLdouble)CLIENT_WIDTH / (GLdouble)nCol;
	GLdouble h = w / SVAratio;

	for (GLint c = 0; c < nCol; c++) {
		GLdouble currentH = 0;
		while ((currentH + h) <= CLIENT_HEIGHT) {
			Viewport* vp = new Viewport((GLint)w, (GLint)h);
			vp->uploadPos((GLint)(c*w), (GLint)currentH);
			vp->upload();
			cam1->setVP(vp);
			scene.render(cam1->getViewMat());
			currentH += h;
		} //del while
	} // del for
}

void resize(int newWidth, int newHeight)
{
	// Resize Viewport 
	vp1->uploadSize(newWidth, newHeight);
	if (twoPorts) {
		vp2->uploadSize(newWidth, newHeight);
	}
	// Resize Scene Visible Area 
	cam1->uploadSize(vp1->getW(), vp1->getH());    // scale unchanged
	if (twoPorts) {
		cam2->uploadSize(vp2->getW(), vp2->getH());
	}

}
//-------------------------------------------------------------------------

void key(unsigned char key, int x, int y)
{
	bool need_redisplay = true;

	switch (key) {
	case 27:  // Escape key 
		glutLeaveMainLoop();  // Freeglut's sentence for stopping glut's main loop 
		break;
	case '+':
		if (twoPorts) {
			cam2->uploadScale(+0.01);   // zoom in  (increases the scale)
		}
		cam1->uploadScale(+0.01);   // zoom in  (increases the scale)
		break;
	case '-':
		if (twoPorts) {
			cam2->uploadScale(-0.01);
		}
		cam1->uploadScale(-0.01);   // zoom out (decreases the scale)
		break;
	case 'l':
		if (twoPorts) {
			cam2->set3D();
		}
		cam1->set3D();
		break;
	case 'o':
		if (twoPorts) {
			cam2->set2D();
		}
		cam1->set2D();
		break;
	case 'u':
		if (twoPorts) {
			scene2.update();
		}
		scene.update();
		scene.render(cam1->getViewMat());
		break;
	case 'U':
		auto_update = !(auto_update);
		break;
	case 'c':
		if (twoPorts) {
			cam2->setCenital();
		}
		cam1->setCenital();
		break;
	case 'h':
		baldosas = !baldosas;
		break;
	case 'j':
		twoPorts = !twoPorts;
		break;
	case 'k':
		if (twoPorts) {
			cam2->yaw(1);
		}
	case 'p': {
		if (twoPorts) {
			if (cam2->getOrto() == true) {
				cam2->setOrto(false);
			}
			else {
				cam2->setOrto(true);
			}
			cam2->uploadPM();
		}
		if (cam1->getOrto() == true) {
			cam1->setOrto(false);
		}
		else {
			cam1->setOrto(true);
		}
		cam1->uploadPM();
		break;
	}
	case '2':
		scene.escena2D();
		break;
	case '3':
		scene.escena3D();
		break;
	case 'n':
		//scene.setLuzGlobal(0, 0, 0, 1);
		scene.setLuz(false);
		//scene.luzOnOff(false);
		break;
	case 'm':
		//scene.setLuzGlobal(0.5, 0.5, 0.5, 1);
		scene.setLuz(true);
		//scene.luzOnOff(true);
		break;
	case 's':
		scene.setMaterial('s');
		break;
	case 'b':
		coloDrone = !coloDrone;
		scene.setColorDrone(coloDrone);
	default:
		need_redisplay = false;
		break;
	} //switch

	if (need_redisplay)
		glutPostRedisplay();
}
//-------------------------------------------------------------------------

void specialKey(int key, int x, int y)
{
	bool need_redisplay = true;

	switch (key) {
	case GLUT_KEY_RIGHT:
		//camera.pitch(1);   // rotate 1 on the X axis
		scene.move(3);
		break;
	case GLUT_KEY_LEFT:
		//camera.yaw(1);     // rotate 1 on the Y axis 
		scene.move(4);
		break;
	case GLUT_KEY_UP:
		//camera.roll(1);    // rotate 1 on the Z axis
		scene.move(1); //true arriba
		break;
	case GLUT_KEY_DOWN:
		//camera.roll(-1);   // rotate -1 on the Z axis
		scene.move(2); // false abajo
		break;
	default:
		need_redisplay = false;
		break;
	}//switch

	if (need_redisplay)
		glutPostRedisplay();
}
//-------------------------------------------------------------------------

void mouse(int button, int state, int x, int y) {
	mBot = button;
	mCoord = glm::dvec2(x, y);

	//La variable y si riferisce alle coordinata della finestra e questa tiene
	//l'origine nell'angolo superiore sinistra, mentre nel puerto di vista l'origine 
	//sta nell'angolo inferiore sinistro. Per passare da una all'altra si usa
	// y(viewPort) = glutGet(GLUT_WINDOW_HEIGHT) - y ;
}

void motion(int x, int y) {
	// GLUT_LEFT_BUTTON / GLUT_RIGHT_BUTTON sono i bottoni sinistro e destro del mouse
	// GLUT_UP / GLUT_DOWN sono gli stati del bottone (non premuto o premuto)
	// Guardiamo mCoord quando si è cliccato un tasto
	glm::dvec2 mp = mCoord;
	mCoord = glm::dvec2(x, y);

	if (twoPorts) {

		bool leftWindow = false;
		mp = mCoord - mp;

		if (mCoord.x < CLIENT_WIDTH / 2) {
			leftWindow = true;
		}
		else {
			leftWindow = false;
		}
		if (mBot == GLUT_LEFT_BUTTON) {
			if (leftWindow) cam1->orbit(mp.x * 0.5, mp.y);
			else cam2->orbit(mp.x * 0.5, mp.y);
		}
		else if (mBot == GLUT_RIGHT_BUTTON) {
			if (leftWindow) {
				cam1->moveUD(mp.y);
				cam1->moveLR(-mp.x);
			}
			else {
				cam2->moveUD(mp.y);
				cam2->moveLR(-mp.x);
			}

		}
		glutPostRedisplay();

	}
	else {
	// Se TwoPorts è false si lavora solo con un ViewPort
		// Calcular el desplazamiento habido
		mp = mCoord - mp;

		if (mBot == GLUT_LEFT_BUTTON)
		{
			//Recuerda que mp.x son radianes. Reducelos a tu gusto
			cam1->orbit(mp.x*0.5, mp.y);
		}
		else if (mBot == GLUT_RIGHT_BUTTON)
		{
			cam1->moveUD(mp.y);
			cam1->moveLR(-mp.x);
		}

		glutPostRedisplay();
	}


}

void mouseWheel(int n, int d, int x, int y)
{
	//Si usa quando sono spinti GLUT_ACTIVE_CTRL/ALT/_SHIFT 
	int m = glutGetModifiers();
	//Se nessun tasto è premuto
	if (m == 0) 
	{
		//Spostarsi nella direzione di vista "d"

		if (d == 1)
		{
			cam1->moveFB(10);
			if (twoPorts) cam2->moveFB(10);
		}
		else
		{
			cam1->moveFB(-10);
			if (twoPorts) cam2->moveFB(-10);
		}
	}
	else if (m == GLUT_ACTIVE_CTRL)
	{
		glm::dvec2 mp = mCoord;
		mCoord = glm::dvec2(x, y);

		bool leftWindow = false;

		if (mCoord.x < CLIENT_WIDTH / 2) {
			leftWindow = true;
		}
		else {
			leftWindow = false;
		}

		if (d == 1)
		{
			if (twoPorts) {
				if (leftWindow) cam1->uploadScale(0.1);
				else cam2->uploadScale(0.1);
			}
			else {
				cam1->uploadScale(0.1);
			}

		}
		else
		{
			if (twoPorts) {
				if (leftWindow) cam1->uploadScale(-0.1);
				else cam2->uploadScale(-0.1);
			}
			else
			{
				cam1->uploadScale(-0.1);
			}
		}

		glutPostRedisplay();
	}
}