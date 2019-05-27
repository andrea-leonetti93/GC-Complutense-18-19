//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Camera.h"
#include "Texture.h"
#include "Mesh.h"
#include "Light.h"
#include <vector>

//-------------------------------------------------------------------------

class Entity 
{
public:
	Entity() : modelMat(1.0) { }; 
	virtual ~Entity() { };
	double incrAng = 0.0;
	//virtual void render(Camera const& cam) = 0;
	virtual void render(glm::dmat4 const& modelViewMat) = 0;
	Texture texture; // w, h, id
	

	// modeling matrix
	glm::dmat4 const& getModelMat() const { return modelMat; };

	void setModelMat(glm::dmat4 const& aMat) { modelMat = aMat; }
	virtual void update();
	virtual void update(GLuint);
	virtual void move(GLuint);

protected:
	Mesh* mesh = nullptr;						// surface mesh
	glm::dmat4 modelMat;						// modeling matrix
	glm::fvec3 color = { -1.0, -1.0, -1.0 };	//attributo per decidere colore con luce
	// transfers modelViewMat to the GPU
	virtual void uploadMvM(glm::dmat4 const& modelViewMat) const;
	
};

//-------------------------------------------------------------------------
class CompoundEntity : public Entity
{
public:

	std::vector<Entity*> grObjects;

	Entity* getEntity(int i) { return grObjects[i]; }

	CompoundEntity() {}
	~CompoundEntity() {
		for (Entity* it : grObjects)
			delete it;
	}
	void render(glm::dmat4 const& modelViewMat);
	void update();
	void update(GLuint timeElapsed);
};

//-------------------------------------------------------------------------

class EntityMaterial : public Entity {
public:
	EntityMaterial() : Entity() { };
	virtual ~EntityMaterial() { };
	void setTexture(Texture* tex) { texture = tex; };
	void setMaterial(Material matl) { material = matl; };
protected:
	Texture* texture = nullptr;
	Material material;
};

//-------------------------------------------------------------------------

class EjesRGB : public Entity 
{
public:
	EjesRGB(GLdouble l);
	~EjesRGB();
	virtual void render(glm::dmat4 const& modelViewMat);
};

//-------------------------------------------------------------------------

class Poliespiral : public Entity
{
public:
	Poliespiral(glm::dvec2 verIni,
		GLdouble angIni,
		GLdouble incrAng,
		GLdouble ladoIni,
		GLdouble incrLado,
		GLuint numVert);
	~Poliespiral();
	virtual void render(glm::dmat4 const& modelViewMat);
};
//-------------------------------------------------------------------------

class Dragon : public Entity
{
public:
	Dragon(GLuint numVert);
	~Dragon();
	virtual void render(glm::dmat4 const& modelViewMat);
};
//-------------------------------------------------------------------------
class TrianguloRGB : public Entity
{
public:
	TrianguloRGB(GLdouble r);
	~TrianguloRGB();
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update();
};
//-------------------------------------------------------------------------
class TrianguloAnimado : public Entity
{
public:
	TrianguloAnimado(GLdouble);
	~TrianguloAnimado();
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update();
	virtual void update(GLuint);
protected:
	double incrExtAng = 0;
	double raggio_int = 0;
	double const r_ext = 300;
	double new_x = 0, new_y = 0;
	double const centre_x = 0, centre_y = r_ext;
};
//-------------------------------------------------------------------------
class Rectangulo : public Entity
{
public:
	Rectangulo(GLdouble h, GLdouble w, glm::dvec3 c);
	~Rectangulo();
	virtual void render(glm::dmat4 const& modelViewMat);
protected:
	char c;
};

class RectanguloRGB : public Entity
{
public:
	RectanguloRGB(GLdouble h,GLdouble w);
	~RectanguloRGB();
	virtual void render(glm::dmat4 const& modelViewMat);
};

class RectanguloTexture : public Entity
{
public:
	RectanguloTexture(GLdouble w, GLdouble h, GLuint x, GLuint y);
	~RectanguloTexture();
	virtual void render(glm::dmat4 const& modelViewMat);
};//-------------------------------------------------------------------------
class Estrella3D : public Entity
{
public:
	Estrella3D(GLdouble re, GLdouble np, GLdouble h);
	~Estrella3D();
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update();
	virtual void update(GLuint);
protected:
	double incrAngY = 0; 
	double incrAngZ = 0; 
};
//-------------------------------------------------------------------------
class Estrella3DTexture : public Entity
{
public:
	Estrella3DTexture(GLdouble r, GLdouble nL, GLdouble h);
	~Estrella3DTexture();
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update();
	virtual void update(GLuint);
protected:
	double incrAngY = 0;
	double incrAngZ = 0;
};
//-------------------------------------------------------------------------
class Caja : public Entity
{
public:
	Caja(GLdouble l);
	~Caja();
	virtual void render(glm::dmat4 const& modelViewMat);
	Mesh * fondo;
};
//-------------------------------------------------------------------------
class CajaTexture : public Entity
{
public:
	CajaTexture(GLdouble l);
	~CajaTexture();
	virtual void render(glm::dmat4 const& modelViewMat);
	Mesh * fondo;
	Texture texture2; 
};
//-------------------------------------------------------------------------
class Suelo : public Entity
{
public:
	Suelo(GLdouble h, GLdouble w, GLuint rh, GLuint rw);
	~Suelo();
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update();
	virtual void update(GLuint);
};
//-------------------------------------------------------------------------
class Foto : public Entity
{
public:
	Foto(GLdouble w, GLdouble h);
	~Foto();
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update();
	virtual void update(GLuint);
};
//-------------------------------------------------------------------------
class Tablero1 : public Entity
{
public:
	Tablero1(GLdouble l, GLuint n);
	~Tablero1();
	virtual void render(glm::dmat4 const& modelViewMat);
	Mesh * fondo;
	virtual void update();
protected:
	double incrExtAng = 0.0;
	double raggio_int = 0;
	double const r_ext = 50;
	double const centre_x = 0, centre_y = 0;
	double incrAngX = 0.0;
	double incrAngY = 0.0;
	int numTablero1 = 0;
};
//-------------------------------------------------------------------------
class Tablero2 : public Entity
{
public:
	Tablero2(GLdouble l, GLuint n);
	~Tablero2();
	virtual void render(glm::dmat4 const& modelViewMat);
	Mesh * fondo;
	virtual void update();
protected:
	double incrExtAng = 0.0;
	double raggio_int = 0;
	double const r_ext = 50;
	double const centre_x = 0, centre_y = 0;
	double incrAngX = 0.0;
	double incrAngY = 0.0;
	double incrAngZ = 0.0;
	int numTablero2 = 0;
};
//-------------------------------------------------------------------------
class Cangilon : public Entity
{
public:
	Cangilon(GLdouble l, GLuint n);
	~Cangilon();
	virtual void render(glm::dmat4 const& modelViewMat);
	Mesh * fondo;
	virtual void update();
protected:
	double incrExtAng = 0.0;
	double raggio_int = 0;
	double const r_ext = 500;
	double const centre_x = 0, centre_y = 0;
	double incrAngX = 0.0;
	double incrAngY = 0.0;
	double incrAngZ = 0.0;
	double x = 500.0;
	double y = 0.0;
	int numCangilon = 0;
};
//-------------------------------------------------------------------------
class AspaNoria : public Entity
{
public:
	AspaNoria(GLdouble l);
	~AspaNoria();
	virtual void render(glm::dmat4 const& modelViewMat);
	Mesh * fondo;
	virtual void update();
protected:
	double incrExtAng = 0.0;
	double raggio_int = 0;
	double const r_ext = 500;
	double const centre_x = 0, centre_y = 0;
	double incrAngX = 500.0;
	double incrAngY = 0.0;
	double incrAngZ = 0.0;
};

class QuadricEntity : public Entity
{
public:
	QuadricEntity();
	~QuadricEntity() { gluDeleteQuadric(q); };
protected:
	GLUquadricObj* q;
	glm::fvec3 color = glm::dvec3(-1.0, -1.0, -1.0);
};


class Sphere : public QuadricEntity
{
public:
	Sphere(GLdouble r, glm::dvec3 c);
	void render(glm::dmat4 const& modelViewMat);
private:
	GLdouble r;
};

class Cylinder : public QuadricEntity
{
public:
	Cylinder(GLdouble baseRadio, GLdouble topRadio, GLdouble altura, int lados, int rodajas, glm::dvec3 c);
	void render(glm::dmat4 const& modelViewMat);
private:
	int l;
	int r;
	GLdouble br;
	GLdouble tr;
	GLdouble h;
};

class Disk : public QuadricEntity
{
public:
	Disk(GLdouble intRadio, GLdouble extRadio, int lados, int anillos);
	void render(glm::dmat4 const& modelViewMat);
private:
	GLdouble ir;
	GLdouble er;
	int l;
	int r;
};

class PartialDisk : public QuadricEntity
{
public:
	PartialDisk(GLdouble intRadio, GLdouble extRadio, int lados, int anillos, GLdouble startAngle, GLdouble sweepAngle);
	void render(glm::dmat4 const& modelViewMat);
private:
	GLdouble ir;
	GLdouble er;
	int l;
	int r;
	GLdouble sta;
	GLdouble swa;
};

class Chassis : public Entity
{
public:
	Chassis(GLdouble h, GLdouble w);
	~Chassis();
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update();
protected:
	int height;
	int width;
	const double angulo = 90;
	GLfloat fs;
	Rectangulo *tapa1;
	Rectangulo *tapa2;
};
/*La classe Rotor eredita Entity, dobbiamo creare una nuova classe che erediti da CompoundEntity*/
//--------------------------------------------------------------------------------------------------
/*
class Rotor : public Entity
{
public:
	Rotor(GLdouble baseRadio, GLdouble topRadio, GLdouble altura, int lados, int rodajas, bool direccion, bool color);
	~Rotor();
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update();
protected:
	int l;
	int r;
	GLdouble br;
	GLdouble tr;
	GLdouble h;
	int length;
	int width;
    double anguloPaleta = 90;
	bool d;
	bool c;
	Rectangulo *paleta;
	Cylinder *cylinder;
};
*/

class Rotor : public CompoundEntity 
{
public:
	Rotor(GLdouble baseRadio, GLdouble topRadio, GLdouble altura, int lados, int rodajas, bool direccion, glm::dvec3 colPal, glm::dvec3 colCyl);
	virtual void update();
	void update(GLuint timeElapsed);
protected:
	int l;
	int r;
	GLdouble br;
	GLdouble tr;
	GLdouble h;
	int length;
	int width;
	double anguloPaleta = 90;
	bool d;
	bool c;
	Rectangulo *paleta;
	Cylinder *cylinder;
};

/*La classe Dron eredita Entity, dobbiamo creare una nuova classe che erediti da Compound Entity*/
//--------------------------------------------------------------------------------------------------
/*
class Dron: public Entity
{
public:
	Dron();
	~Dron();
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update();
protected:
	int height;
	int width;
	double anguloPaleta = 90;
	SpotLight *sptLuz;
	Chassis *chassis;
	Rotor *rotorF1;
	Rotor *rotorF2;
	Rotor *rotorB3;
	Rotor *rotorB4;
};
*/
class Dron : public CompoundEntity
{
public:
	Dron();
	void render(glm::dmat4 const & modelViewMat);
	void update();
	void update(GLuint timeElapsed);
	void luzOnOff(bool luz);
protected:
	int height;
	int width;
	double anguloPaleta = 90;
	Rotor *rotorF1;
	Rotor *rotorF2;
	Rotor *rotorB3;
	Rotor *rotorB4;
	SpotLight *foco;
};

class Cone : public Entity {
public:
	Cone(GLdouble h, GLdouble r);

	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update();
	virtual void update(GLuint timeElapsed);

protected:
	SpotLight *luceFaro;
};

class Esfera : public Entity {
public:
	Esfera(GLint p, GLint m, GLdouble r, bool ma);

	virtual void render(glm::dmat4 const& modelViewMat);
	void setMaterial(Material * m);
	void setColor(GLdouble a, GLdouble b, GLdouble c);
	virtual void update();
	virtual void update(GLuint timeElapsed);

protected:
	GLint paralelos;
	GLint meridianos;
	GLdouble radio;
	Material *mat;
	bool material = false;
	glm::fvec3 colorEsfera = glm::fvec3(-1.0, -1.0, -1.0);
};

class Cilindro : public Entity {
public:
	Cilindro(GLdouble h, GLdouble r);

	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update();
	virtual void update(GLuint timeElapsed);
};
class Anello : public Entity {
public:
	Anello(GLdouble h, GLdouble r);

	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update();
	virtual void update(GLuint timeElapsed);
};

class Toro : public Entity {
public:
	Toro(GLdouble r, GLdouble dFromZero, GLint nPerfil);

	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update();
	virtual void update(GLuint timeElapsed);
};
class Bicchiere : public Entity {
public:
	Bicchiere(GLdouble baseRadio, GLdouble topRadio, GLdouble h);

	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update();
	virtual void update(GLuint timeElapsed);
};

class TajMahal : public Entity {
public:
	TajMahal(GLdouble baseRadio, GLdouble h);

	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update();
	virtual void update(GLuint timeElapsed);
};

class Semisfera : public Entity {
public:
	Semisfera(GLint p, GLint m, GLdouble r, bool ma);

	virtual void render(glm::dmat4 const& modelViewMat);
	void setMaterial(Material * m);
	void setColor(GLdouble a, GLdouble b, GLdouble c);
	virtual void update();
	virtual void update(GLuint timeElapsed);

protected:
	GLint paralelos;
	GLint meridianos;
	GLdouble radio;
	Material *mat;
	bool material = false;
	glm::fvec3 colorEsfera = glm::fvec3(-1.0, -1.0, -1.0);
};

class Lampada : public Entity {
public:
	Lampada(bool ma);

	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update();
	virtual void update(GLuint timeElapsed);

protected:
	Material *mat;
	bool material = false;
	SpotLight *lampadina;
	Esfera *esfera;
	glm::fvec3 colorEsfera = glm::fvec3(-1.0, -1.0, -1.0);
};
class EsferaYDrone : public Entity {
public:
	EsferaYDrone();
	~EsferaYDrone();
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update();
	virtual void update(GLuint timeElapsed);
	void move(GLuint num);
protected:
	Dron *dron;
	Esfera *esfera;
	double meridiano = 0;
	double parallelo = 0;
};

class TheBigDrone : public Entity {
public:
	TheBigDrone();
	~TheBigDrone();
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update();
	virtual void update(GLuint timeElapsed);
protected:
	Dron *dron;
	Dron *dron1;
	Dron *dron2;
	Dron *dron3;
	Dron *dron4;
};


// COCHE

class Rueda : public CompoundEntity
{
public:
	Rueda(GLdouble baseRadio, GLdouble topRadio, GLdouble altura, int lados, int rodajas, glm::dvec3 color);
	~Rueda();
	//virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update();
	virtual void move(GLuint);
protected:
	int l;
	int r;
	GLdouble br;
	GLdouble tr;
	GLdouble h;
	int length;
	int width;
	double anguloPaleta = 90;
	Rectangulo *paleta1;
	Rectangulo *paleta2;
	Cylinder *cylinder;
};

class Coche : public CompoundEntity {
public:
	Coche();
	~Coche();
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update();
	virtual void update(GLuint timeElapsed);
	void move(GLuint num);

protected:
	//Chassis *chasisCoche;
	Rueda *rueda1;
	Rueda *rueda2;
	Rueda *rueda3;
	Rueda *rueda4;
	Cone *faroS;
	Cone *faroD;
	SpotLight *luceFaroS;
	SpotLight *luceFaroD;
};

class BB8 : public CompoundEntity
{
public:
	BB8();
	void render(glm::dmat4 const & modelViewMat);
	void update();
	void update(GLuint timeElapsed);
	void luzOnOff(bool luz);
protected:
	Esfera *body;
	Semisfera *head;
};

class Arbor : public Entity {
public:
	Arbor();
	~Arbor();
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update();
	virtual void update(GLuint timeElapsed);
protected:
	Cylinder *tronco;
	Cylinder *tronco2;
	Cylinder *chioma1;
	Sphere *chioma2;
};

class CocheyStrada : public Entity {
public:
	CocheyStrada();
	~CocheyStrada();
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update();
	virtual void update(GLuint timeElapsed);
	void move(GLuint num);
protected:
	Coche *coche;
	Esfera *sfera;
	Arbor *arbor;
	int movimentoLaterale = 0;
	int movimentoLineare = 0;
};


#endif //_H_Entities_H