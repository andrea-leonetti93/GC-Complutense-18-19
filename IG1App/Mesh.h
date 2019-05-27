//#pragma once
#ifndef _H_Mesh_H_
#define _H_Mesh_H_

#include <GL/freeglut.h>
#include <glm.hpp>

//-------------------------------------------------------------------------

class Mesh 
{
public:
	static Mesh* createRGBAxes(GLdouble l); // creates a new 3D RGB axes mesh
	static Mesh* generaPoliespiral(glm::dvec2 verIni, GLdouble angIni, GLdouble
		incrAng, GLdouble ladoIni, GLdouble incrLado, GLuint numVert); // creates a new poliespiral
	static Mesh* generaDragon(GLuint numVert);	//create a new dragon
	static Mesh* generaTriangulo(GLdouble r);	//create a triangle
	static Mesh* generaTrianguloRGB(GLdouble r);	//create a RGB triangle
	static Mesh* generaRectangulo(GLdouble h, GLdouble w);	//create a rectangle
	static Mesh* generaRectanguloRGB(GLdouble h, GLdouble w);	//create a RGB rectangle
	static Mesh* generaRectanguloTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh); //create a rectangle with texture
	static Mesh* generaEstrella3D(GLdouble re, GLdouble np, GLdouble h);	//create a estrella
	static Mesh* generaEstrellaTexCor(GLdouble r, GLdouble nL, GLdouble h); //create a estrella with texture
	static Mesh* generaContCubo(GLdouble l);	//create a caja
	static Mesh* generaCajaTexCor(GLdouble l); // create a caja with texture
	static Mesh* generaSuelo(GLdouble h, GLdouble w, GLuint rh, GLuint rw); // Create a suelo
	static Mesh* generaFoto(GLdouble w, GLdouble h); // Create a photo
	static Mesh* generaTablero(GLdouble l); // Create a tablero
	static Mesh* generaChassis(GLdouble l, GLfloat fs); // Create a Chasis
	static Mesh* generaChasisCoche(GLdouble l, GLfloat fs); // Create a Chasis Coche
	

	Mesh(void) { };
	~Mesh(void);
	virtual void render();

	glm::dvec3* getVertices() { return vertices; };  // vertex array
	glm::dvec4* getColors() { return colors; };      // color array
   
protected:

	GLuint numVertices = 0;   // arrays size (number of elements)
	GLuint primitive = GL_TRIANGLES;  // graphic primitive: GL_POINTS, GL_LINES, GL_TRIANGLES, ...

	glm::dvec3* vertices = nullptr;  // vertex array
	glm::dvec4* colors = nullptr;    // color array
	glm::dvec2* texCoords = nullptr; // texture array
};

//-------------------------------------------------------------------------
class MBR : public Mesh 
{
public: 
	MBR(GLuint p, GLuint r, glm::dvec3* perfilOriginal);

	void vertexBuilding();
	void normalize();
	virtual void render();

protected:
	GLuint m;
	GLuint n;
	glm::dvec3 *perfil;
	double PI = 3.14;
	glm::dvec3 *normals = nullptr;
};

#endif //_H_Scene_H_