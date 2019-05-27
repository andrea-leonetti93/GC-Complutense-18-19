#include "Scene.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

void Scene::init()
{ // OpenGL basic setting
	glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);  // enable Depth test
	glEnable(GL_TEXTURE_2D);
	// COMANDI LUCI
	//glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	//glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb1);
	// A CHE SERVE QUESTO?
	//ojo de la camara
	//glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);
	//DirLight *dirLuz = new DirLight();
	//dirLuz->uploadL();
	// lights
	// textures  
	// meshes

	// LUCE DIREZIONALE SULLA SCENA
	dirLuz = new DirLight();
	dirLuz->setPosDir(fvec3(1, 1, 0));
	dirLuz->setAmb(fvec4(0.2, 0.2, 0.2, 1.0));
	dirLuz->setSpec(fvec4(0.5, 0.5, 0.5, 1.0));
	dirLuz->setDiff(fvec4(1.0, 1.0, 1.0, 1.0));
	//dirLuz->enable();
	//FARO SULLA SFERA
	sptLuz = new SpotLight(fvec3(0, 0, -1));
	sptLuz->setAmb(fvec4(0, 0, 0, 1));
	sptLuz->setDiff(fvec4(0.4, 0.8, 0.0, 1.0));
	sptLuz->setSpec(fvec4(0.5, 0.5, 0.5, 1.0));
	sptLuz->setSpot(fvec3(0, 0, -1), 10.0, 0);

	//dirLuz->enable();
	// Graphics objects (entities) of the scene
	grObjects.push_back(new EjesRGB(800.0));

	// Polispirale (decommentare i valori interessati)
  //grObjects.push_back(new Poliespiral(glm::dvec2( 0.0, 0.0 ), 0.0, 160.0, 1.0, 1.0, 50));
  //grObjects.push_back(new Poliespiral((0, 0), 0, 72, 30, 0.001, 5));
  //grObjects.push_back(new Poliespiral((0, 0), 0, 60, 0.5, 0.5, 100));
  //grObjects.push_back(new Poliespiral((0, 0), 0, 89.5, 0.5, 0.5, 100));
  //grObjects.push_back(new Poliespiral((0, 0), 0, 45, 1, 1, 50));

  // Drago
  //grObjects.push_back(new Dragon(3000));


  //Triangulo
  //grObjects.push_back(new Triangulo(30.0));

  //TrianguloRGB
  //grObjects.push_back(new TrianguloRGB(200.0));

  //TrianguloAnimado
  //grObjects.push_back(new TrianguloAnimado(200.0));

  //RectanguloRGB
  //grObjects.push_back(new RectanguloRGB(800.0,1200.0));

  //RectanguloTexture
  //grObjects.push_back(new RectanguloTexture(800.0, 1200.0,4,8));

  //Estrella3D
  //grObjects.push_back(new Estrella3D(200.0, 4.0, 100.0));

  //Estrella3DTexture
  //grObjects.push_back(new Estrella3DTexture(200.0, 4.0, 100.0));

	//Caja
	//grObjects.push_back(new Caja(200.0));

	//CajaTexture
	//grObjects.push_back(new CajaTexture(200.0));

	//Suelo
	//grObjects.push_back(new Suelo(800.0, 1200.0, 4, 8));

	//Sphera
	//grObjects.push_back(new Sphere(100));
	//Cylinder
	//grObjects.push_back(new Cylinder(10, 10, 200, 50, 50, dvec3(1, 0, 0)));
	//Disk
	//grObjects.push_back(new Disk(100, 150, 50, 50));
	//PartialDisk
	//grObjects.push_back(new PartialDisk(100, 150, 50, 50, 15, 45));

	//noria(8);
	//Rotor
	//grObjects.push_back(new Rotor(150, 150, 50, 50, 50, true, dvec3(0, 0, 0), dvec3(1, 0, 0)));
	//grObjects.push_back(new Rotor(150, 150, 50, 50, 50, false, dvec3(0,0,0), dvec3(0,1,0)));

	//Chassis
	//grObjects.push_back(new Chassis(150, 150));

	//Dron
	//grObjects.push_back(new Dron());
	//Cono per rivoluzione
	//grObjects.push_back(new Cone(100, 50));

	//ESFERA PER RIVOLUZIONE
	//Va modificato il valore del material
	//FALSE non tiene material -> solo per APARTADO 18 e 19
	//TRUE tiene material -> solo per APARTADO 20 e 21
	//grObjects.push_back(new Esfera(200, 200, 100, false));
	//grObjects.push_back(new Esfera(200, 200, 100, true));

	//Cilindro per rivoluzione
	//grObjects.push_back(new Cilindro(100, 50));
	//Anello per rivoluzione
	//grObjects.push_back(new Anello(10, 50));
	//Toro per rivoluzione
	//grObjects.push_back(new Toro(50, 150, 50));
	//Bicchiere per rivoluzione
	//grObjects.push_back(new Bicchiere(50,70,100));
	//TajMahal per rivoluzione
	//grObjects.push_back(new TajMahal(50, 170));
	//Semisfera per rivoluzione
	// MAX 89 perchè l'angolo è 90, altrimenti scazza.
	//grObjects.push_back(new Semisfera(89, 89, 150, false));

	//ESFERAYDRONE
	//grObjects.push_back(new EsferaYDrone());
	//TheBigDrone
	//grObjects.push_back(new TheBigDrone());

	//Rueda
	//grObjects.push_back(new Rueda(150, 150, 50, 50, 50, dvec3(1,0,0)));
	//Coche
	//grObjects.push_back(new Coche());
	//Coche y Strada	
	//grObjects.push_back(new CocheyStrada());
	//Arbor
	//grObjects.push_back(new Arbor());
	//BB8
	//grObjects.push_back(new BB8());
	// Lampada
	grObjects.push_back(new Lampada(true));
	//apartado_18 = true;
	//apartado_19 = true;
	//apartado_20 = true;
	//apartado_21 = true;
	//apartado_22 = true;
	setLuz(true);
}

void Scene::init2()
{ // OpenGL basic setting
	glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);  // enable Depth test
	glEnable(GL_TEXTURE_2D);
	// Graphics objects (entities) of the scene
	grObjects.push_back(new EjesRGB(800.0));
	//TheBigDrone
	grObjects.push_back(new TheBigDrone());
}
//-------------------------------------------------------------------------
void Scene::escena2D()
{

	grObjects.clear();
	//Poliespiral
	grObjects.push_back(new Poliespiral(glm::dvec2(0.0, 0.0), 0.0, 160.0, 1.0, 1.0, 50));

	//Drago
	grObjects.push_back(new Dragon(3000));

	//TrianguloAnimado
	grObjects.push_back(new TrianguloAnimado(200.0));

	//RectanguloRGB
	grObjects.push_back(new RectanguloRGB(800.0, 1200.0));

}

//-------------------------------------------------------------------------
void Scene::escena3D()
{
	grObjects.clear();

	//EjesRGB
	grObjects.push_back(new EjesRGB(800.0));

	//RectanguloTexture
	//grObjects.push_back(new RectanguloTexture(800.0, 1200.0,4,8));

	//Suelo
	grObjects.push_back(new Suelo(800.0, 1200.0, 4, 8));

	//Estrella3DTexture
	grObjects.push_back(new Estrella3DTexture(200.0, 4.0, 100.0));

	//CajaTexture
	grObjects.push_back(new CajaTexture(200.0));


	//Foto Escena
	grObjects.push_back(new Foto(300.0, 150.0));
}

//-------------------------------------------------------------------------
void Scene::setLuz(bool luz)
{
	if (apartado_18) {
		if (luz) {
			//glEnable(GL_COLOR_MATERIAL);
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb1);
		}
		else {
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb2);
		}
	}
	if (apartado_19) {
		if (luz) {
			//glEnable(GL_COLOR_MATERIAL);
			dirLuz->enable();
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb1);
		}
		else {
			dirLuz->disable();
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb2);
		}
	}
	if (apartado_20) {
		//APARTADO 20 e 21
		//Si disattiva il COLOR_MATERIAL
		//Si elimina il colore della sfera
		//Si aggiunge un attributo Material alla classe Sfera
		//con i metodi setCooper(), setSilver(), setGold() imposto il materiale
		glDisable(GL_COLOR_MATERIAL);
		if (luz) {
			dirLuz->enable();
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb1);
		}
		else {
			dirLuz->disable();
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb2);
		}
	}
	if (apartado_21) {
		glDisable(GL_COLOR_MATERIAL);
		if (luz) {
			dirLuz->enable();
			sptLuz->disable();
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb1);
		}
		else {
			dirLuz->disable();
			sptLuz->enable();
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb2);
		}
	}
	if (apartado_22) {
		if (luz) {
			dirLuz->enable();
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb1);
		}
		else {
			dirLuz->disable();
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb2);
		}
	}
	if (luz) {
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb1);
	}
	else {
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb2);

	}
}

void Scene::setColorDrone(bool a)
{
	if (apartado_22) {
		if (a) {
			//glEnable(GL_COLOR_MATERIAL);
			//glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
			////setLuzGlobal(0.5, 0.5, 0.5, 1.0);
			////((Esfera*)getEntity(1))->setMaterial(nullptr);
			//((Esfera*)getEntity(1))->setColor(0.75164, 0.60648, 0.22648);
			//if (dirLuz != nullptr)
			//	dirLuz->enable();
			((Dron*)getEntity(1))->luzOnOff(true);
		}
		else {
			//glDisable(GL_COLOR_MATERIAL);
			//Material *m = new Material();
			//m->setGold();
			////m->upload();
			//((Esfera*)getEntity(1))->setMaterial(m);
			//((Esfera*)getEntity(1))->setColor(-1.0, -1.0, -1.0);
			//if (dirLuz != nullptr) {
			//	dirLuz->disable();
			//}
			((Dron*)getEntity(1))->luzOnOff(false);
		}
	}
}

//-------------------------------------------------------------------------

void Scene::render(glm::dmat4 const& modelMat)
{
	if (dirLuz != nullptr)
		dirLuz->upload(modelMat);
	if (sptLuz != nullptr)
		sptLuz->upload(dmat4(1.0));
	//if (foco != nullptr)
	//	foco->upload(modelMat);
	CompoundEntity::render(modelMat);
}
//-------------------------------------------------------------------------

void Scene::setMaterial(char c)
{
	Material *m = new Material();
	switch (c) {
	case 'g':
		m->setGold();
		break;
	case 'c':
		m->setCooper();
		break;
	case 's':
		m->setSilver();
		break;
	}
	m->upload();
	for (Entity* el : grObjects) {
		((Esfera*)el)->setMaterial(m);
	}
}
void Scene::luzOnOff(bool luz) {
	if (luz) {
		//dirLuz->enable();
		//posLuz->enable();
		sptLuz->enable();
		//glEnable(GL_LIGHT0);
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb1);
	}
	else {
		//dirLuz->disable();
		//posLuz->disable();
		sptLuz->disable();
		//glDisable(GL_LIGHT0);
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb2);
	}

}

//-------------------------------------------------------------------------
Scene::~Scene()
{ // free memory and resources   

	for (Entity* el : grObjects)
	{
		delete el;  el = nullptr;
	}
}
/*
void Scene::render(glm::dmat4 const& modelViewMat)
{
	dirLuz->upload(modelViewMat);
	for (Entity* el : grObjects)
	{
		el->render(modelViewMat);
	}
	//sptLuz->upload(dmat4(1.0));
}*/

//-------------------------------------------------------------------------
// RENDER, UPDATE commentati perché ora sono ereditati da CompoundEntity
/*
void Scene::render(glm::dmat4 const& modelViewMat)
{
	for (Entity* el: grObjects)
	{
		el->render(modelViewMat);
	}
}

//-------------------------------------------------------------------------

void Scene::update()
{
	for (Entity* el : grObjects)
	{
		el->update();
	}
}

//-------------------------------------------------------------------------
void Scene::update(GLuint delta)
{
	for (Entity* el : grObjects)
	{
		el->update(delta);
	}
}
*/
//-------------------------------------------------------------------------
void Scene::move(GLuint num)
{
	for (Entity* el : grObjects)
	{
		el->move(num);
	}
}
//-------------------------------------------------------------------------
void Scene::aspaNoria() {
	grObjects.clear();
	Entity* e = new EjesRGB(200.0);
	e->render(e->getModelMat());
	//Entity* c = new Cangilon(200.0);
	//dmat4 m(1.0);
	//m = translate(dmat4(1), glm::dvec3(500.0, 0.0, 0.0));
	//c->setModelMat(m);
	//c->render(c->getModelMat());
	//Entity* t1 = new Tablero1(50.0);
	//dmat4 mm(1.0);
	//t1->render(t1->getModelMat());
	//Entity* t2 = new Tablero2(50.0);
	//dmat4 mmm(1.0);
	//t2->render(t2->getModelMat());
	//grObjects.push_back(new Cangilon(200.0));
	//grObjects.push_back(new Tablero1(50.0));
	//grObjects.push_back(new Tablero2(50.0));
}
//-------------------------------------------------------------------------

void Scene::noria(GLint n)
{
	grObjects.clear();
	grObjects.push_back(new EjesRGB(800.0));
	grObjects.push_back(new Cangilon(200.0, n));
	grObjects.push_back(new Tablero1(50.0, n));
	grObjects.push_back(new Tablero2(50.0, n));
}