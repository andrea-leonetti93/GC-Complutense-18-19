//#pragma once
#ifndef _H_Camera_H_
#define _H_Camera_H_

#include <GL/freeglut.h>
#include <glm.hpp>
#include <gtc/matrix_access.hpp>

#include "Viewport.h"
//-------------------------------------------------------------------------

class Camera {
public:
	Camera(Viewport* avp) : vp(avp), viewMat(1.0), projMat(1.0),
		xRight(avp->getW() / 2.0), xLeft(-xRight),
		yTop(avp->getH() / 2.0), yBot(-yTop) {	};
	~Camera() {};
	Viewport* getVP() { return vp; }

	// view matrix (the inverse of modeling matrix)
	glm::dmat4 const& getViewMat() const { return viewMat; };
	void uploadVM() const; // transfers viewMat to the GPU

	void set2D();  // eye(0,0,500), look(0,0,0), up(0, 1, 0)

	//se va a modificar set3D para situar el ojo en el punto 
	// (frente, frente, frente) y mira el origen y pone la capara derecha,
	// donde frente = radio*cos(ang) y angulo = -45º
	void set3D();  // eye(500,500,500), look(0,10,0), up(0, 1, 0)

	//AÑADIMOS setCenital() que muestra una vista cenital de la escena,
	//situando el ojo a una altura igual a radio, mirando al origen y
	//orientando la cámara dirección (Z, -Z). El método actualiza ang a -90ª,
	//por ejemplo, para que, al recuperarse de este movimiento se vuelva a ver la imagen derecha
	void setCenital();

	//Movimiento de la cámara a izquierda o derecha, sobre el eje U,
	//una distancia cs. Cambia pues eye y de acuerdo con ello look
	void moveLR(GLdouble cs);

	//EJE N
	void moveFB(GLdouble cs);

	//EJE V
	void moveUD(GLdouble cs);

	//Movimientos análogos sobre los ejes U y V respectivamente, pero sin
	//cambiar eye, solo look
	void lookLR(GLdouble cs);

	void lookUD(GLdouble cs);

	//Orbita la cámara alrededor de look, haciendo que eye describa
	//el paralelo que se encuentra a altura eye.y, en sentido antihorario
	void orbit(GLdouble ax);

	//Método similar al anterior, pero se deja que la cámara cambie su
	//altura a una catidad ay. Obsérvese que ax es un double que se refiere 
	//a radianes mientras que ay es una longitud
	void orbit(GLdouble ax, GLdouble ay);

	void pitch(GLdouble a); // rotates a degrees on the X axis
	void yaw(GLdouble a);   // rotates a degrees on the Y axis
	void roll(GLdouble a);  // rotates a degrees on the Z axis

	// projection matrix
	glm::dmat4 const& getProjMat() const { return projMat; };
	void uploadPM();  // transfers projMat to the GPU

	// set scene visible area size and transfers projMat to the GPU
	void uploadSize(GLdouble aw, GLdouble ah);

	// update scale factor and transfers projMat to GPU
	void uploadScale(GLdouble s);

	bool getOrto();

	void setOrto(bool boolean);

	GLdouble getxRight();
	GLdouble getxLeft();
	GLdouble getyTop();
	GLdouble getyBot();

	void setVP(Viewport* viewport);


protected:

	glm::dmat4 viewMat;    // view matrix = inverse of modeling matrix

	glm::dmat4 projMat;     // projection matrix

	GLdouble xRight, xLeft, yTop, yBot;    // size of scene visible area
	GLdouble nearVal = 500, farVal = 10000;  // view volume
	GLdouble factScale = 1;

	Viewport* vp;

	//ATRIBUTOS AÑADIDOS COMO INDICA LA TRANSPARECIA 11 DE LAS DIAPOSITIVAS DE CAMARA
	glm::dvec3 eye = { 1000.0, 1000.0, 1000.0 };
	glm::dvec3 look = { 0.0, 0.0, 0.0 };
	glm::dvec3 up = { 0.0, 1.0, 0.0 };
	glm::dvec3 front = { 0.0, 0.0, -1.0 }; // Observa que es -n
	glm::dvec3 u = { 1.0, 0.0, 0.0 };
	glm::dvec3 v = { 0.0, 1.0, 0.0 };

	GLdouble radio = 1000.0;
	GLdouble ang = 0.0;
	bool orto = true;


	//METODOS PROTEGIDOS DE LA TRANSPARENCIA 14

	//Da valor a u, v, front a partir de las filas de la matriz de vista.
	// RECORDEMOS QUE FRONT ES -N (USAMOS ROW())
	void setAxes();

	//Invoca a lookAt() con los valores de eye, look, up para dar valor a la 
	//matriz de vista, y actualiza después los ejes con el método anterior
	void setVM();

};

//-------------------------------------------------------------------------

#endif //_H_Camera_H_