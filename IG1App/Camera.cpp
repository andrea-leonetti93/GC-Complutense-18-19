#include "Camera.h"
#include "Light.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

void Camera::set2D()
{
	eye = dvec3(0, 0, 500);
	look = dvec3(0, 0, 0);
	up = dvec3(0, 1, 0);
	viewMat = lookAt(eye, look, up);
}
//-------------------------------------------------------------------------

void Camera::set3D()
{
	ang = -45.0;
	GLdouble frente = radio * cos(radians(ang));
	eye = dvec3(frente, frente, frente);
	look = dvec3(0, 0, 0);
	up = dvec3(0, 1, 0);
	viewMat = lookAt(eye, look, up);
	SpotLight *sptLuz = new SpotLight();
	fvec4 newColDif = { 0.4, 0.8, 0.0, 1 };
	fvec4 newColAmb = { 0.0, 0.0, 0.0, 1 };
	fvec4 newColSpec = { 0.5, 0.5, 0.5, 1 };
	sptLuz->setDiff(newColDif);
	sptLuz->setAmb(newColAmb);
	sptLuz->setSpec(newColSpec);
	dvec3 dir = dvec3{ 1, 1, 0 };
	sptLuz->setPosDir(dir);
	sptLuz->setSpot((dvec3)(-1, -1, 0), 90, 4);
	sptLuz->uploadL();
}
void Camera::setCenital()
{
	eye = dvec3(0, radio, 0);
	look = dvec3(0, 0, 0);
	up = dvec3(0, 0, -1);
	ang = -90.0;
	viewMat = lookAt(eye, look, up);
}
void Camera::moveLR(GLdouble cs)
{
	eye += u * cs;
	look += u * cs;
	setVM();
}
void Camera::moveFB(GLdouble cs)
{
	eye += -front * cs;
	look += -front * cs;
	setVM();
}
void Camera::moveUD(GLdouble cs)
{
	eye += v * cs;
	look += v * cs;
	setVM();
}
void Camera::lookLR(GLdouble cs)
{
	look += u * cs;
	setVM();
}
void Camera::lookUD(GLdouble cs)
{
	look += v * cs;
	setVM();
}
void Camera::orbit(GLdouble ax)
{
	ang += ax;
	eye.x = look.x + cos(radians(ang)) * radio;
	eye.z = look.z - sin(radians(ang)) * radio;
	setVM();
}

void Camera::orbit(GLdouble ax, GLdouble ay)
{
	ang += ax;
	eye.x = look.x + cos(radians(ang)) * radio;
	eye.z = look.z - sin(radians(ang)) * radio;
	eye.y += ay;
	setVM();
}

//-------------------------------------------------------------------------

void Camera::uploadVM() const
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(viewMat));
}
//-------------------------------------------------------------------------

void Camera::pitch(GLdouble a)
{
	viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(1.0, 0, 0));
}
//-------------------------------------------------------------------------
void Camera::yaw(GLdouble a)
{
	viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(0, 1.0, 0));
}
//-------------------------------------------------------------------------
void Camera::roll(GLdouble a)
{
	viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(0, 0, 1.0));
}
//-------------------------------------------------------------------------

void Camera::uploadSize(GLdouble aw, GLdouble ah)
{
	xRight = aw / 2.0;
	xLeft = -xRight;
	yTop = ah / 2.0;
	yBot = -yTop;
	projMat = ortho(xLeft*factScale, xRight*factScale, yBot*factScale, yTop*factScale, nearVal, farVal);

	uploadPM();
}
//-------------------------------------------------------------------------

void Camera::uploadScale(GLdouble s)
{
	factScale -= s;
	if (factScale < 0) factScale = 0.01;
	projMat = ortho(xLeft*factScale, xRight*factScale, yBot*factScale, yTop*factScale, nearVal, farVal);

	uploadPM();
}

bool Camera::getOrto()
{
	return orto;
}

void Camera::setOrto(bool boolean)
{
	orto = boolean;
}

GLdouble Camera::getxRight()
{
	return xRight;
}

GLdouble Camera::getxLeft()
{
	return xLeft;
}

GLdouble Camera::getyTop()
{
	return yTop;
}

GLdouble Camera::getyBot()
{
	return yBot;
}

void Camera::setVP(Viewport * viewport)
{
	vp = viewport;
}

//Da valor a u, v, front a partir de las filas de la matriz de vista.
// RECORDEMOS QUE FRONT ES -N (USAMOS ROW())
void Camera::setAxes()
{
	u = row(viewMat, 0);
	v = row(viewMat, 1);
	front = -row(viewMat, 2);

}

//Invoca a lookAt() con los valores de eye, look, up para dar valor a la 
//matriz de vista, y actualiza después los ejes con el método anterior
void Camera::setVM()
{
	viewMat = lookAt(eye, look, up);
	setAxes();
}
void Camera::uploadPM()
{
	if (orto)
	{
		nearVal = 1;
		projMat = ortho(xLeft*factScale, xRight*factScale, yBot*factScale, yTop*factScale, nearVal, farVal);
	}
	else
	{
		nearVal = 2 * yTop;
		projMat = frustum(xLeft*factScale, xRight*factScale, yBot*factScale, yTop*factScale, nearVal, farVal);
	}

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(value_ptr(projMat));
	glMatrixMode(GL_MODELVIEW);


}


//-------------------------------------------------------------------------
/*
void Camera::uploadPM() const
{
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(value_ptr(projMat));
	glMatrixMode(GL_MODELVIEW);
}
*/
//-------------------------------------------------------------------------