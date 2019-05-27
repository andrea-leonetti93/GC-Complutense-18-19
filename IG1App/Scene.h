//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Camera.h"
#include "Entity.h"
//#include "Mesh.h"

#include <vector>

//-------------------------------------------------------------------------
// Scene prima di Compound Entity
/*
class Scene	
{ 
public:
    Scene() { };
	~Scene();
    void init(); 
    void init2(); 

    void render(glm::dmat4 const& modelViewMat);
	void escena2D();
	void escena3D();
	void update();
	void update(GLuint);
	void move(GLuint);
	void aspaNoria();
	void noria(GLint aspas);

	  
protected:

	  std::vector<Entity*> grObjects;  // Entities (graphics objects) of the scene
	  //glm::dmat4 const& modelViewMat;
};
*/
//-------------------------------------------------------------------------
// Scene dopo Compound Entity

class Scene : public CompoundEntity
{
public:
	Scene() { };
	~Scene();
	void init();
	void init2();
	void escena2D();
	void escena3D();
	void luzOnOff(bool luz);
	void move(GLuint);
	void aspaNoria();
	void noria(GLint aspas);
	void render(glm::dmat4 const& modelViewMat);
	void setLuz(bool luz);
	void setColorDrone(bool);
	void setMaterial(char);

protected:
	//std::vector<Light*> grLights;
	//EsferaYDrone * esferaYDrone = new EsferaYDrone();
	DirLight *dirLuz;
	//PosLight *posLuz;
	SpotLight *sptLuz;
	SpotLight *foco;
	GLfloat amb1[4] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat amb2[4] = { 0.0, 0.0, 0.0, 1.0 };
	bool apartado_18 = false;
	bool apartado_19 = false;
	bool apartado_20 = false;
	bool apartado_21 = false;
	bool apartado_22 = false;
};

#endif //_H_Scene_H_

