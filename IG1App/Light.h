#pragma once
#ifndef _H_Lights_H_
#define _H_Lights_H_

#include <GL/freeglut.h>
#include <glm.hpp>

class Light { // Abstract class

// Añade setter’s para cambiar el valor de los atributos lumínicos
public:
	Light();
	virtual ~Light() { disable(); }
	void uploadL();
	virtual void upload(glm::dmat4 const& modelViewMat) = 0;
	//void disable() { glDisable(GL_LIGHTING); };
	void disable() { if (id < GL_LIGHT0 + GL_MAX_LIGHTS) glDisable(id); };
	void enable() { if (id < GL_LIGHT0 + GL_MAX_LIGHTS) glEnable(id); };
	void setAmb(glm::fvec4 amb) { ambient = amb; uploadL(); };
	void setDiff(glm::fvec4 diff) { diffuse = diff; uploadL(); };
	void setSpec(glm::fvec4 spec) { specular = spec; uploadL(); };
	GLuint getId();

protected:
	static GLuint cont; // Para generar un nuevo id cada vez
	GLuint id = GL_LIGHT0 + GL_MAX_LIGHTS; // id no válido
	// Atributos lumínicos y geométrico de la fuente de luz
	glm::fvec4 ambient = { 0.1, 0.1, 0.1, 1 };
	glm::fvec4 diffuse = { 0.5, 0.5, 0.5, 1 };
	glm::fvec4 specular = { 0.5, 0.5, 0.5, 1 };
	glm::fvec4 posDir = { 0, 0, 1, 0 };
};

class DirLight : public Light {
public:
	virtual void upload(glm::dmat4 const& modelViewMat);
	void setPosDir(glm::fvec3 dir);
};

class PosLight : public Light {
public:
	virtual void upload(glm::dmat4 const& modelViewMat);
	void setPosDir(glm::fvec3 dir);
	void setAtte(GLfloat kc, GLfloat kl, GLfloat kq);
protected:
	// Factores de atenuación
	GLfloat kc = 1, kl = 0, kq = 0;
};

class SpotLight : public PosLight {
public:
	SpotLight(glm::fvec3 pos = { 0, 0, 0 })
		: PosLight() {
		posDir = glm::fvec4(pos, 1.0);
	};
	virtual void upload(glm::dmat4 const& modelViewMat);
	void setSpot(glm::fvec3 dir, GLfloat cf, GLfloat e);
protected:
	// Atributos del foco
	glm::fvec4 direction = { 0, 0, -1, 0 };
	GLfloat cutoff = 180;
	GLfloat exp = 0;
};

class Material {
public:
	Material() {};
	virtual ~Material() {};
	virtual void upload();
	void setCooper();
	void setGold();
	void setSilver();
protected:
	// Coeficientes de reflexión
	glm::fvec4 ambient = { 0.2, 0.2, 0.2, 1.0 };
	glm::fvec4 diffuse = { 0.8, 0.8, 0.8, 1.0 };
	glm::fvec4 specular = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat expF = 0; // Exponente para la reflexión especular
	GLuint face = GL_FRONT_AND_BACK;
	GLuint sh = GL_SMOOTH; // Tipo de matizado
};

#endif //_H_Lights_H