#include "Entity.h"
#include "Texture.h"
#include "Mesh.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------
//ENTITY
void Entity::uploadMvM(dmat4 const& modelViewMat) const
{
	dmat4 aMat = modelViewMat * modelMat;
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(aMat));
}

void Entity::update()
{
}

void Entity::update(GLuint)
{

}

void Entity::move(GLuint)
{
}
//-------------------------------------------------------------------------
void CompoundEntity::render(dmat4 const& modelViewMat) {
	glMatrixMode(GL_MODELVIEW);
	dmat4 aMat = modelViewMat * modelMat;
	glLoadMatrixd(value_ptr(aMat));

	for (Entity* it : grObjects) {
		it->render(aMat);
	}
}

void CompoundEntity::update() {
	for (Entity* it : grObjects) {
		it->update();
	}
}

void CompoundEntity::update(GLuint timeElapsed) {
	for (Entity* entity : grObjects) {
		entity->update(timeElapsed);
	}
}
//-------------------------------------------------------------------------
// EjesRGB
EjesRGB::EjesRGB(GLdouble l) : Entity()
{
	mesh = Mesh::createRGBAxes(l);
}

EjesRGB::~EjesRGB()
{
	delete mesh; mesh = nullptr;
};

void EjesRGB::render(dmat4 const& modelViewMat)
{
	if (mesh != nullptr) {
		uploadMvM(modelViewMat);
		glLineWidth(2);
		mesh->render();
	}
}
//-------------------------------------------------------------------------
//Poliespiral
Poliespiral::Poliespiral(dvec2 verIni,
	GLdouble angIni,
	GLdouble incrAng,
	GLdouble ladoIni,
	GLdouble incrLado,
	GLuint numVert) : Entity()
{
	mesh = Mesh::generaPoliespiral(verIni, angIni, incrAng, ladoIni, incrLado, numVert);
}

Poliespiral::~Poliespiral()
{
	delete mesh; mesh = nullptr;
};

void Poliespiral::render(dmat4 const& modelViewMat)
{
	if (mesh != nullptr) {
		uploadMvM(modelViewMat);
		glLineWidth(2);
		glColor3d(1.0, 0.0, 0.0);
		mesh->render();
	}
}
//-------------------------------------------------------------------------
//Dragon
Dragon::Dragon(GLuint numVert) : Entity()
{
	mesh = Mesh::generaDragon(numVert);
}

Dragon::~Dragon()
{
	delete mesh; mesh = nullptr;
};

void Dragon::render(dmat4 const& modelViewMat)
{
	if (mesh != nullptr) {
		dmat4 matAux = modelViewMat;
		matAux = translate(matAux, glm::dvec3(-40.0, -170.0, 0.0));
		matAux = scale(matAux, glm::dvec3(40.0, 40.0, 0.0));
		uploadMvM(matAux);
		glColor3d(0.4, 0.5, 0.1);
		glPointSize(2);
		mesh->render();
	}
}
//-------------------------------------------------------------------------
//TrianguloRGB
TrianguloRGB::TrianguloRGB(GLdouble r) : Entity()
{
	mesh = Mesh::generaTrianguloRGB(r);
}

TrianguloRGB::~TrianguloRGB()
{
	delete mesh; mesh = nullptr;
};

void TrianguloRGB::render(dmat4 const& modelViewMat)
{
	if (mesh != nullptr) {
		uploadMvM(modelViewMat);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		modelMat = rotate(modelMat, glm::radians(incrAng), glm::dvec3(0, 0, 1.0));
		modelMat = translate(dmat4(1), dvec3(0, 0, 200.0));
		mesh->render();
	}
}

void TrianguloRGB::update()
{
	incrAng++;
}
//-------------------------------------------------------------------------
//Triangulo Animado
TrianguloAnimado::TrianguloAnimado(GLdouble r) : Entity()
{
	mesh = Mesh::generaTrianguloRGB(r);
	raggio_int = r;
}

TrianguloAnimado::~TrianguloAnimado()
{
	delete mesh; mesh = nullptr;
};

void TrianguloAnimado::render(dmat4 const& modelViewMat)
{
	if (mesh != nullptr) {
		dmat4 auxMat = modelMat;
		dmat4 matTranslate = translate(auxMat, dvec3(new_x, new_y, 0));
		dmat4 matRotated = rotate(modelMat, radians((double)incrAng), dvec3(0.0, 0.0, 1.0));
		modelMat = auxMat * matTranslate * matRotated;
		uploadMvM(modelViewMat);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mesh->render();
		modelMat = auxMat;
	}
}

void TrianguloAnimado::update()
{
	incrAng += 1;
	incrExtAng += 5;
	new_x = centre_x + r_ext * cos(radians(incrExtAng));
	new_y = centre_y + r_ext * sin(radians(incrExtAng));
}
void TrianguloAnimado::update(GLuint a)
{
	incrAng += a / 10;
	incrExtAng += a / 10;
	new_x = centre_x + r_ext * cos(radians(incrExtAng));
	new_y = centre_y + r_ext * sin(radians(incrExtAng));
}
//-------------------------------------------------------------------------
//Rectangulo
Rectangulo::Rectangulo(GLdouble h, GLdouble w, dvec3 c)
{
	//c = color;
	mesh = Mesh::generaRectangulo(h, w);
	glm::dmat4 model = glm::mat4(1.0f);
	color = c;
}

Rectangulo::~Rectangulo()
{
	delete mesh; mesh = nullptr;
};

void Rectangulo::render(dmat4 const& modelViewMat)
{
	if (mesh != nullptr) {
		uploadMvM(modelViewMat);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		if (color != fvec3(-1.0, -1.0, -1.0)) glColor3f(color[0], color[1], color[2]);
		else glColor3f(0.2, 0.4, 0.6);
		/*if (c == 'a') {
			glColor3d(0.0, 0.0, 1.0);
		}
		else if (c == 'n') {
			glColor3d(0.0, 0.0, 0.0);
		}*/
		mesh->render();
	}
}
//-------------------------------------------------------------------------
//RectanguloRGB
RectanguloRGB::RectanguloRGB(GLdouble h, GLdouble w) : Entity()
{
	mesh = Mesh::generaRectanguloRGB(h, w);
	glm::dmat4 model = glm::mat4(1.0f);
}

RectanguloRGB::~RectanguloRGB()
{
	delete mesh; mesh = nullptr;
};

void RectanguloRGB::render(dmat4 const& modelViewMat)
{
	if (mesh != nullptr) {
		uploadMvM(modelViewMat);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mesh->render();
	}
}
//-------------------------------------------------------------------------
//RectanguloTexture
RectanguloTexture::RectanguloTexture(GLdouble w, GLdouble h, GLuint x, GLuint y) : Entity()
{
	mesh = Mesh::generaRectanguloTexCor(w, h, x, y);
	glm::dmat4 model = glm::mat4(1.0f);
	texture.load("..\\Bmps\\baldosaC.bmp");
	modelMat = glm::rotate(model, glm::radians(90.0), glm::dvec3(1.0, 0, 0));
}

RectanguloTexture::~RectanguloTexture()
{
	delete mesh; mesh = nullptr;
};

void RectanguloTexture::render(dmat4 const& modelViewMat)
{
	dmat4 auxMat = modelMat;
	modelMat = glm::rotate(modelMat, glm::radians(180.0), glm::dvec3(1.0, 0, 0));
	uploadMvM(modelViewMat);
	texture.bind();
	mesh->render();
	texture.unbind();
	modelMat = auxMat;
}

//-------------------------------------------------------------------------
//Estrella3D
Estrella3D::Estrella3D(GLdouble er, GLdouble np, GLdouble h) : Entity()
{
	mesh = Mesh::generaEstrella3D(er, np, h);
}

Estrella3D::~Estrella3D()
{
	delete mesh; mesh = nullptr;
};

void Estrella3D::render(dmat4 const& modelViewMat)
{
	if (mesh != nullptr) {
		dmat4 auxMat = modelMat;
		dmat4 matAnimation1 = glm::rotate(dmat4(1), radians(incrAngY), dvec3(0.0, 1.0, 0.0));
		dmat4 matAnimation2 = glm::rotate(dmat4(1), radians(incrAngZ), dvec3(0.0, 0.0, 1.0));
		dmat4 translate1 = translate(modelMat, glm::dvec3(0.0, 50, 0.0));
		modelMat = auxMat * translate1 *matAnimation1 * matAnimation2;
		uploadMvM(modelViewMat);
		glColor3d(0.0, 0.0, 0.0);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mesh->render();
		dmat4 rotate2 = glm::rotate(auxMat, radians(180.0), dvec3(0.0, 1.0, 0.0));
		dmat4 translate2 = translate(auxMat, glm::dvec3(0.0, 50.0, 0.0));
		modelMat = auxMat * translate2 * rotate2 * matAnimation1 * matAnimation2;
		uploadMvM(modelViewMat);
		mesh->render();
		modelMat = auxMat;
	}
}

void Estrella3D::update()
{
	incrAngY++;
	incrAngZ++;
}

void Estrella3D::update(GLuint a)
{
	incrAngY += a / 10;
	incrAngZ += a / 10;
}
//-------------------------------------------------------------------------
//Estrella3DTexture
Estrella3DTexture::Estrella3DTexture(GLdouble r, GLdouble nL, GLdouble h) : Entity()
{
	mesh = Mesh::generaEstrellaTexCor(r, nL, h);
	texture.load("..\\Bmps\\baldosaP.bmp");
}

Estrella3DTexture::~Estrella3DTexture()
{
	delete mesh; mesh = nullptr;
};

void Estrella3DTexture::render(dmat4 const& modelViewMat)
{
	if (mesh != nullptr) {
		dmat4 auxMat = modelMat;
		uploadMvM(modelViewMat);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		dmat4 translate1 = translate(dmat4(1), glm::dvec3(100.00, 100.0, 0.0));
		dmat4 matAnimation1 = glm::rotate(dmat4(1), radians(incrAngY), dvec3(0.0, 1.0, 0.0));
		dmat4 matAnimation2 = glm::rotate(dmat4(1), radians(incrAngZ), dvec3(0.0, 0.0, 1.0));
		modelMat = auxMat * translate1 *matAnimation1 * matAnimation2;
		uploadMvM(modelViewMat);
		texture.bind();
		mesh->render();
		texture.unbind();
		//Dobbiamo cambiare la matrice e l'attributo che si chiama modelMat
		dmat4 translate2 = translate(dmat4(1), glm::dvec3(100.00, 100.0, 0.0));
		dmat4 rotate2 = glm::rotate(dmat4(1), radians(180.0), dvec3(0.0, 1.0, 0.0));
		modelMat = auxMat * translate2 * rotate2 * matAnimation1 * matAnimation2;
		uploadMvM(modelViewMat);
		texture.bind();
		mesh->render();
		texture.unbind();
		//Successivamente dobbiamo riportarla alla posizione originale
		modelMat = auxMat;
	}
}

void Estrella3DTexture::update()
{
	incrAngY++;
	incrAngZ++;
}

void Estrella3DTexture::update(GLuint a)
{
	incrAngY += a / 10;
	incrAngZ += a / 10;
}
//-------------------------------------------------------------------------
// Caja
Caja::Caja(GLdouble l) : Entity()
{
	mesh = Mesh::generaContCubo(l);
	glm::dmat4 model = glm::mat4(1.0f);
	modelMat = translate(dmat4(1), dvec3(-l / 2, 0, -l / 2));
}

Caja::~Caja()
{
	delete mesh; mesh = nullptr;
};

void Caja::render(dmat4 const& modelViewMat)
{
	if (mesh != nullptr) {
		uploadMvM(modelViewMat);
		glColor3d(0.0, 0.0, 0.0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		mesh->render();
	}
}

//-------------------------------------------------------------------------
// CajaTexture
CajaTexture::CajaTexture(GLdouble l) : Entity()
{
	mesh = Mesh::generaCajaTexCor(l);
	glm::dmat4 model = glm::mat4(1.0f);
	texture.load("..\\Bmps\\container.bmp");
	texture2.load("..\\Bmps\\papelE.bmp");

	modelMat = translate(dmat4(1), dvec3(0, l / 2, 0));
}

CajaTexture::~CajaTexture()
{
	delete mesh; mesh = nullptr;
};

void CajaTexture::render(dmat4 const& modelViewMat)
{
	if (mesh != nullptr) {
		uploadMvM(modelViewMat);
		glLineWidth(2);
		glColor3d(0.0, 0.0, 0.0);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		texture.bind();
		mesh->render();
		texture.unbind();
		glDisable(GL_CULL_FACE);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);

		texture2.bind();
		mesh->render();
		texture2.unbind();
		glDisable(GL_CULL_FACE);
	}
}
//-------------------------------------------------------------------------
//Suelo
Suelo::Suelo(GLdouble h, GLdouble w, GLuint rh, GLuint rw) : Entity()
{
	mesh = Mesh::generaSuelo(h, w, rh, rw);
	//texture.load("..\\Bmps\\baldosaC.bmp");
}

Suelo::~Suelo()
{
	delete mesh; mesh = nullptr;
};

void Suelo::render(dmat4 const& modelViewMat)
{
	if (mesh != nullptr) {
		dmat4 auxMat = modelMat;
		modelMat = glm::rotate(modelMat, glm::radians(90.0), glm::dvec3(1.0, 0, 0));
		uploadMvM(modelViewMat);
		texture.bind();
		mesh->render();
		texture.unbind();
		//Successivamente dobbiamo riportarla alla posizione originale
		modelMat = auxMat;
	}
}
void Suelo::update()
{
}

void Suelo::update(GLuint)
{
}
//-------------------------------------------------------------------------
// Foto
Foto::Foto(GLdouble w, GLdouble h) : Entity()
{
	mesh = Mesh::generaFoto(w, h);
	texture.loadColorBuffer();
}

Foto::~Foto()
{
	delete mesh; mesh = nullptr;
};

void Foto::render(dmat4 const& modelViewMat)
{
	if (mesh != nullptr) {
		uploadMvM(modelViewMat);
		modelMat = translate(dmat4(1), dvec3(500.0, 1.0, 0));
		modelMat = glm::rotate(modelMat, glm::radians(90.0), glm::dvec3(1.0, 0, 0));
		texture.bind();
		mesh->render();
		texture.unbind();
	}
}
void Foto::update()
{
}

void Foto::update(GLuint)
{
}

//-------------------------------------------------------------------------
// Tablero1
Tablero1::Tablero1(GLdouble l, GLuint n) : Entity()
{
	mesh = Mesh::generaTablero(l);
	glm::dmat4 model = glm::mat4(1.0f);
	numTablero1 = n;
}

Tablero1::~Tablero1()
{
	delete mesh; mesh = nullptr;
};

void Tablero1::render(dmat4 const& modelViewMat)
{
	if (mesh != nullptr) {
		dmat4 auxMat = modelMat;
		//uploadMvM(modelViewMat);
		glLineWidth(2);
		glColor3d(0.0, 0.0, 0.0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		double angolo = 360 / numTablero1;
		double start = 0;
		for (int i = 0; i < numTablero1; i++) {
			//incrAngX = centre_x + r_ext * cos(radians(start));
			//incrAngY = centre_y + r_ext * sin(radians(start));
			dmat4 matAnimation1 = translate(dmat4(1), glm::dvec3(incrAngX, incrAngY, 102.0));
			dmat4 rotate2 = glm::rotate(dmat4(1), radians(start), dvec3(0.0f, 0.0f, 1.0f));
			modelMat = auxMat * matAnimation1 * rotate2;
			uploadMvM(modelViewMat);
			mesh->render();
			start = start + angolo;
			//modelMat = translate(dmat4(1), dvec3(incrAngX, incrAngY, 102.0));
			//mesh->render();
		}
		modelMat = auxMat;
	}
}

void Tablero1::update()
{
	//incrAngY++;
	//incrAngZ++;
	incrExtAng += 5;
	incrAngX = centre_x + r_ext * cos(radians(incrExtAng));
	incrAngY = centre_y + r_ext * sin(radians(incrExtAng));
}
//-------------------------------------------------------------------------
// Tablero2
Tablero2::Tablero2(GLdouble l, GLuint n) : Entity()
{
	mesh = Mesh::generaTablero(l);
	glm::dmat4 model = glm::mat4(1.0f);
	numTablero2 = n;
}


Tablero2::~Tablero2()
{
	delete mesh; mesh = nullptr;
};

void Tablero2::render(dmat4 const& modelViewMat)
{
	if (mesh != nullptr) {
		dmat4 auxMat = modelMat;
		//uploadMvM(cam.getViewMat());
		glLineWidth(2);
		glColor3d(0.0, 0.0, 0.0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		double angolo = 360 / numTablero2;
		double start = 0.0;
		for (int i = 0; i < numTablero2; i++) {
			//incrAngX = centre_x + r_ext * cos(radians(start));
			//incrAngY = centre_y + r_ext * sin(radians(start));
			//dmat4 translate1 = translate(dmat4(1), glm::dvec3(0.0, 0.0, -102.0));
			dmat4 matAnimation1 = translate(dmat4(1), glm::dvec3(incrAngX, incrAngY, -102.0));
			dmat4 rotate2 = glm::rotate(dmat4(1), radians(start), dvec3(0.0f, 0.0f, 1.0f));
			//glRotatef(start, 0.0, 0.0, 1.0);
			modelMat = auxMat * matAnimation1 * rotate2;
			uploadMvM(modelViewMat);
			mesh->render();
			start = start + angolo;
		}
		modelMat = auxMat;
	}
}

void Tablero2::update()
{
	//incrAngY++;
	//incrAngZ++;
	//incrAng += 1;
	incrExtAng += 5;
	incrAngX = centre_x + r_ext * cos(radians(incrExtAng));
	incrAngY = centre_y + r_ext * sin(radians(incrExtAng));
	incrAngZ++;
}
//-------------------------------------------------------------------------
// Cangilon
Cangilon::Cangilon(GLdouble l, GLuint n) : Entity()
{
	mesh = Mesh::generaCajaTexCor(l);
	numCangilon = n;
	glm::dmat4 model = glm::mat4(1.0f);
	texture.load("..\\Bmps\\container.bmp");
}

Cangilon::~Cangilon()
{
	delete mesh; mesh = nullptr;
};

void Cangilon::render(dmat4 const& modelViewMat)
{
	if (mesh != nullptr) {
		dmat4 auxMat = modelMat;
		glLineWidth(2);
		glColor3d(0.0, 0.0, 0.0);
		//glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		float angolo = 360 / numCangilon;
		float start = 0;
		for (int i = 0; i < numCangilon; i++) {
			x = centre_x + r_ext * cos(radians(start));
			y = centre_y + r_ext * sin(radians(start));
			dmat4 matAnimation1 = translate(dmat4(1), glm::dvec3(x, y, 0.0));
			dmat4 matAnimation2 = translate(dmat4(1), glm::dvec3(incrAngX, incrAngY, 0.0));
			//dmat4 matAnimation3 = glm::rotate(dmat4(1), radians(incrAngZ), dvec3(0.0, 0.0, 1.0));
			modelMat = auxMat * matAnimation1 * matAnimation2;
			uploadMvM(modelViewMat);
			texture.bind();
			mesh->render();
			texture.unbind();
			start = start + angolo;
			//modelMat = auxMat;
		}
		//modelMat = translate(dmat4(1), dvec3(500.0, 0, 0));

		//dmat4 translate1 = translate(dmat4(1), glm::dvec3(500.0, 0.0, 0.0));
		modelMat = auxMat;
	}
}

void Cangilon::update()
{
	incrExtAng += 5;
	incrAngX = centre_x + r_ext * cos(radians(incrExtAng));
	incrAngY = centre_y + r_ext * sin(radians(incrExtAng));
	//incrAngZ++;
}
//-------------------------------------------------------------------------
// Aspanoria
AspaNoria::AspaNoria(GLdouble l) : Entity()
{
	mesh = Mesh::generaCajaTexCor(l);
	//mesh1 = Mesh::generaTablero(l);
	//mesh2 = Mesh::generaTablero(l);
	glm::dmat4 model = glm::mat4(1.0f);
	texture.load("..\\Bmps\\container.bmp");
}

AspaNoria::~AspaNoria()
{
	delete mesh; mesh = nullptr;
};

void AspaNoria::render(dmat4 const& modelViewMat)
{
	if (mesh != nullptr) {
		dmat4 auxMat = modelMat;
		//		uploadMvM(cam.getViewMat());
		glLineWidth(2);
		glColor3d(0.0, 0.0, 0.0);
		//glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		//texture.bind();
		//mesh->render();
		//texture.unbind();
		//glDisable(GL_CULL_FACE);
		//modelMat = translate(dmat4(1), dvec3(500.0, 0, 0));
		//dmat4 matAnimation1 = glm::rotate(dmat4(1), radians(incrAngZ), dvec3(0.0, 0.0, 1.0));
		//dmat4 translate1 = translate(dmat4(1), glm::dvec3(500.0, 0.0, 0.0));
		dmat4 matAnimation1 = translate(dmat4(1), glm::dvec3(incrAngX, incrAngY, 0.0));
		//dmat4 matAnimation2 = glm::rotate(dmat4(1), radians(incrAngZ), dvec3(0.0, 0.0, 1.0));
		modelMat = auxMat * matAnimation1;
		uploadMvM(modelViewMat);
		texture.bind();
		mesh->render();
		texture.unbind();
		modelMat = auxMat;
	}
}
void AspaNoria::update()
{
	//if (incrAngX <= 500.0 && incrAngX > 0) {
	//	incrAngY++;
	//	incrAngX--;
	//}
	//if (incrAngX <= 0 && incrAngX > -500.0) {
	//	incrAngX--;
	//	incrAngY--;
	//}
	//if (incrAngX >= -500.0 && incrAngX < 0.0) {
	//	incrAngX++;
	//	incrAngY--;
	//}
	//if (incrAngX <= 0.0 && incrAngX < 500.0) {
	//	incrAngX++;
	//	incrAngY++;
	//}
	incrAng += 1;
	incrExtAng += 5;
	incrAngX = centre_x + r_ext * cos(radians(incrExtAng));
	incrAngY = centre_y + r_ext * sin(radians(incrExtAng));
	incrAngZ++;
}

//-------------------------------------------------------------------------
//QuadricEntity
QuadricEntity::QuadricEntity() {
	q = gluNewQuadric();
}
//-------------------------------------------------------------------------
//Sphere
Sphere::Sphere(GLdouble rr, dvec3 c) {
	r = rr;
	color = c;
}

void Sphere::render(glm::dmat4 const& modelViewMat) {
	uploadMvM(modelViewMat);
	// Fijar el color con glColor3f(...);
	// Fijar el modo en que se dibuja la entidad con
	if (color != fvec3(-1.0, -1.0, -1.0)) glColor3f(color[0], color[1], color[2]);
	gluQuadricDrawStyle(q, GLU_FILL);
	gluSphere(q, r, 50, 50);
}
//-------------------------------------------------------------------------
//Cylinder
Cylinder::Cylinder(GLdouble baseRadio, GLdouble topRadio, GLdouble altura, int lados, int rodajas, dvec3 c)
{
	br = baseRadio;
	tr = topRadio;
	h = altura;
	l = lados;
	r = rodajas;
	color = c;
}

void Cylinder::render(glm::dmat4 const& modelViewMat) {
	uploadMvM(modelViewMat);
	if (color != fvec3(-1.0, -1.0, -1.0)) glColor3f(color[0], color[1], color[2]);
	//else glColor3f(0.2, 0.4, 0.6);
	/*if (c) {
		glColor3f(1, 0, 0);
	}
	else {
		glColor3f(0, 1, 0);
	}*/
	gluQuadricDrawStyle(q, GLU_FILL);
	gluCylinder(q, br, tr, h, l, r);

}
//-------------------------------------------------------------------------
//Disk
Disk::Disk(GLdouble intRadio, GLdouble extRadio, int lados, int anillos) : QuadricEntity() {
	ir = intRadio;
	er = extRadio;
	l = lados;
	r = anillos;

}

void Disk::render(glm::dmat4 const& modelViewMat) {

	gluQuadricDrawStyle(q, GLU_FILL);
	gluDisk(q, ir, er, l, r);

}
//-------------------------------------------------------------------------
//PartialDisk
PartialDisk::PartialDisk(GLdouble intRadio, GLdouble extRadio, int lados, int anillos, GLdouble startAngle, GLdouble sweepAngle) : QuadricEntity() {
	ir = intRadio;
	er = extRadio;
	l = lados;
	r = anillos;
	sta = startAngle;
	swa = sweepAngle;

}

void PartialDisk::render(glm::dmat4 const& modelViewMat) {

	gluQuadricDrawStyle(q, GLU_FILL);
	gluPartialDisk(q, ir, er, l, r, sta, swa);
}

//-------------------------------------------------------------------------
// Chassis
Chassis::Chassis(GLdouble h, GLdouble w) : Entity()
{
	// generaChassis e un cubo con il fattore di scala
	fs = 3;
	height = h;
	width = w;
	mesh = Mesh::generaChassis(h, fs);
	tapa1 = new Rectangulo(height*fs, width*fs, dvec3(0,0,1));
	tapa2 = new Rectangulo(height*fs, width*fs, dvec3(0, 0, 1));
}

Chassis::~Chassis()
{
	delete mesh; mesh = nullptr;
};

void Chassis::render(dmat4 const& modelViewMat)
{

	dmat4 auxMat1 = dmat4(1.0);
	dmat4 auxMat2 = dmat4(1.0);
	auxMat1 = translate(auxMat1, dvec3(0, height / (fs * 2), 0));
	auxMat1 = rotate(auxMat1, radians(angulo), dvec3(1, 0, 0));
	auxMat2 = translate(auxMat2, dvec3(0, -height / (fs * 2), 0));
	auxMat2 = rotate(auxMat2, radians(angulo), dvec3(1, 0, 0));
	tapa1->setModelMat(auxMat1);
	tapa2->setModelMat(auxMat2);
	glColor3d(0.0, 0.0, 1.0);
	uploadMvM(modelViewMat);
	tapa1->render(modelViewMat);
	uploadMvM(modelViewMat);
	glColor3d(0.0, 0.0, 1.0);
	tapa2->render(modelViewMat);
	glColor3d(0.0, 0.0, 1.0);
	uploadMvM(modelViewMat);
	mesh->render();
}
void Chassis::update()
{
}
//-------------------------------------------------------------------------
// ROTORE NORMALE
// Commento perche ora Rotor eredita da CompoundEntity
/*
Rotor::Rotor(GLdouble baseRadio, GLdouble topRadio, GLdouble altura, int lados, int rodajas, bool direccion, bool color)
{
	br = baseRadio;
	tr = topRadio;
	h = altura;
	l = lados;
	r = rodajas;
	d = direccion;
	c = color;
	length = br * 2 - 2;
	width = altura;
	paleta = new Rectangulo(length - 10, width);
	cylinder = new Cylinder(br, tr, h, l, r);
}

Rotor::~Rotor()
{
	delete mesh; mesh = nullptr;
};

void Rotor::render(dmat4 const& modelViewMat)
{
	dmat4 auxMat = dmat4(1.0);
	auxMat = translate(auxMat, dvec3(0, 0, width / 2));
	auxMat = rotate(auxMat, radians((double)90), dvec3(0, 1, 0));
	auxMat = rotate(auxMat, radians(anguloPaleta), dvec3(1, 0, 0));
	paleta->setModelMat(auxMat);
	glColor3d(0.0, 0.0, 0.0);
	uploadMvM(modelViewMat);
	paleta->render(modelViewMat);
	if (c) {
		glColor3d(1.0, 0.0, 0.0);
	}
	else {
		glColor3d(0.0, 1.0, 0.0);
	}
	uploadMvM(modelViewMat);
	cylinder->render(modelViewMat);
}
*/
// ROTORE COMPOUNDENTITY
Rotor::Rotor(GLdouble baseRadio, GLdouble topRadio, GLdouble altura, int lados, int rodajas, bool direccion, dvec3 colPal, dvec3 colCyl) : CompoundEntity()
{
	br = baseRadio;
	tr = topRadio;
	h = altura;
	l = lados;
	r = rodajas;
	d = direccion;
	length = br * 2 - 2;
	width = altura;
	paleta = new Rectangulo(length - 10, width, colPal);
	cylinder = new Cylinder(br, tr, h, l, r, colCyl);
	dmat4 auxMat = dmat4(1.0);
	auxMat = translate(auxMat, dvec3(0, 0, width / 2));
	auxMat = rotate(auxMat, radians((double)90), dvec3(0, 1, 0));
	paleta->setModelMat(auxMat);
	this->grObjects.push_back(cylinder);
	this->grObjects.push_back(paleta);
}

void Rotor::update()
{
	dmat4 auxMat = dmat4(1.0);
	anguloPaleta += 1;

	if (d) {
		auxMat = rotate(auxMat, radians(anguloPaleta), dvec3(0, 0, 1));
	}
	else {
		auxMat = rotate(auxMat, radians(-anguloPaleta), dvec3(0, 0, 1));
	}
	auxMat = translate(auxMat, dvec3(0, 0, width / 2));
	auxMat = rotate(auxMat, radians(90.0), dvec3(0, 1, 0));
	paleta->setModelMat(auxMat);
}

void Rotor::update(GLuint timeElapsed) {  }

//-------------------------------------------------------------------------
// DRONE NORMALE
// Commento perche ora Dron eredita da CompoundEntity
/*
Dron::Dron()
{
	chassis = new Chassis(150, 150);
	rotorF1 = new Rotor(150, 150, 50, 50, 50, true, true);
	rotorF2 = new Rotor(150, 150, 50, 50, 50, true, true);
	rotorB3 = new Rotor(150, 150, 50, 50, 50, false, false);
	rotorB4 = new Rotor(150, 150, 50, 50, 50, false, false);
}
Dron::~Dron()
{
	delete mesh; mesh = nullptr;
};

void Dron::render(dmat4 const& modelViewMat)
{

	//Rotor Front 1
	dmat4 auxMat1 = dmat4(1.0);
	auxMat1 = translate(auxMat1, dvec3(0, (150 / 4) + 10, 0));
	auxMat1 = translate(auxMat1, dvec3(-200, 0, 0));
	auxMat1 = translate(auxMat1, dvec3(0, 0, 200));
	auxMat1 = rotate(auxMat1, radians((double)90), dvec3(1, 0, 0));
	auxMat1 = scale(auxMat1, dvec3(0.5, 0.5, 0.5));
	rotorF1->setModelMat(auxMat1);
	rotorF1->render(modelViewMat*auxMat1);
	//Rotor Front 2
	dmat4 auxMat2 = dmat4(1.0);
	auxMat2 = translate(auxMat2, dvec3(0, (150 / 4) + 10, 0));
	auxMat2 = translate(auxMat2, dvec3(200, 0, 0));
	auxMat2 = translate(auxMat2, dvec3(0, 0, 200));
	auxMat2 = rotate(auxMat2, radians((double)90), dvec3(1, 0, 0));
	auxMat2 = scale(auxMat2, dvec3(0.5, 0.5, 0.5));
	rotorF2->setModelMat(auxMat2);
	rotorF2->render(modelViewMat*auxMat2);
	//Rotor Back 1
	dmat4 auxMat3 = dmat4(1.0);
	auxMat3 = translate(auxMat3, dvec3(0, (150 / 4) + 10, 0));
	auxMat3 = translate(auxMat3, dvec3(200, 0, 0));
	auxMat3 = translate(auxMat3, dvec3(0, 0, -200));
	auxMat3 = rotate(auxMat3, radians((double)90), dvec3(1, 0, 0));
	auxMat3 = scale(auxMat3, dvec3(0.5, 0.5, 0.5));
	rotorB3->setModelMat(auxMat3);
	rotorB3->render(modelViewMat*auxMat3);
	//Rotor Back 2
	dmat4 auxMat4 = dmat4(1.0);
	auxMat4 = translate(auxMat4, dvec3(0, (150 / 4) + 10, 0));
	auxMat4 = translate(auxMat4, dvec3(-200, 0, 0));
	auxMat4 = translate(auxMat4, dvec3(0, 0, -200));
	auxMat4 = rotate(auxMat4, radians((double)90), dvec3(1, 0, 0));
	auxMat4 = scale(auxMat4, dvec3(0.5, 0.5, 0.5));
	rotorB4->setModelMat(auxMat4);
	rotorB4->render(modelViewMat*auxMat4);
	chassis->render(modelViewMat);
	uploadMvM(modelViewMat);
	//modelMat = auxMat;
	//rotorF1->setModelMat(translate(rotorF1->getModelMat(), dvec3(0, 100, 0)));
	//rotorF1->setModelMat(translate(rotorF1->getModelMat(), dvec3(-200, 0, 0)));
	//rotorF1->setModelMat(translate(rotorF1->getModelMat(), dvec3(0, 0, -200)));
	//tapa2->setModelMat(translate(tapa2->getModelMat(), dvec3(0, -height / (fs * 2), 0)));
	//rotorF1->setModelMat(rotate(rotorF1->getModelMat(), radians(anguloPaleta), dvec3(1, 0, 0)));
	//tapa2->setModelMat(rotate(tapa2->getModelMat(), radians(anguloPaleta), dvec3(1, 0, 0)));
}
*/
// DRONE COMPOUNDENTITY
Dron::Dron() : CompoundEntity()
{
	Chassis *chassis = new Chassis(150, 150);
	rotorF1 = new Rotor(150, 150, 50, 50, 50, true, dvec3(0,0,0), dvec3(1,0,0));
	rotorF2 = new Rotor(150, 150, 50, 50, 50, true, dvec3(0,0,0), dvec3(1,0,0));
	rotorB3 = new Rotor(150, 150, 50, 50, 50, false, dvec3(0, 0, 0), dvec3(0, 1, 0));
	rotorB4 = new Rotor(150, 150, 50, 50, 50, false, dvec3(0, 0, 0), dvec3(0, 1, 0));
	
	//Rotor Front 1
	dmat4 auxMat1 = dmat4(1.0);
	auxMat1 = translate(auxMat1, dvec3(0, (150 / 4) + 10, 0));
	auxMat1 = translate(auxMat1, dvec3(-200, 0, 0));
	auxMat1 = translate(auxMat1, dvec3(0, 0, 200));
	auxMat1 = rotate(auxMat1, radians((double)90), dvec3(1, 0, 0));
	auxMat1 = scale(auxMat1, dvec3(0.5, 0.5, 0.5));
	rotorF1->setModelMat(auxMat1);
	//rotorF1->render(modelViewMat*auxMat1);
	//Rotor Front 2
	dmat4 auxMat2 = dmat4(1.0);
	auxMat2 = translate(auxMat2, dvec3(0, (150 / 4) + 10, 0));
	auxMat2 = translate(auxMat2, dvec3(200, 0, 0));
	auxMat2 = translate(auxMat2, dvec3(0, 0, 200));
	auxMat2 = rotate(auxMat2, radians((double)90), dvec3(1, 0, 0));
	auxMat2 = scale(auxMat2, dvec3(0.5, 0.5, 0.5));
	rotorF2->setModelMat(auxMat2);
	//rotorF2->render(modelViewMat*auxMat2);
	//Rotor Back 1
	dmat4 auxMat3 = dmat4(1.0);
	auxMat3 = translate(auxMat3, dvec3(0, (150 / 4) + 10, 0));
	auxMat3 = translate(auxMat3, dvec3(200, 0, 0));
	auxMat3 = translate(auxMat3, dvec3(0, 0, -200));
	auxMat3 = rotate(auxMat3, radians((double)90), dvec3(1, 0, 0));
	auxMat3 = scale(auxMat3, dvec3(0.5, 0.5, 0.5));
	rotorB3->setModelMat(auxMat3);
	//rotorB3->render(modelViewMat*auxMat3);
	//Rotor Back 2
	dmat4 auxMat4 = dmat4(1.0);
	auxMat4 = translate(auxMat4, dvec3(0, (150 / 4) + 10, 0));
	auxMat4 = translate(auxMat4, dvec3(-200, 0, 0));
	auxMat4 = translate(auxMat4, dvec3(0, 0, -200));
	auxMat4 = rotate(auxMat4, radians((double)90), dvec3(1, 0, 0));
	auxMat4 = scale(auxMat4, dvec3(0.5, 0.5, 0.5));
	rotorB4->setModelMat(auxMat4);
	//rotorB4->render(modelViewMat*auxMat4);
	//chassis->render(modelViewMat);
	//uploadMvM(modelViewMat);
	//FOCO
	foco = new SpotLight(fvec3(0, 0, 0));
	foco->setPosDir(dvec3(0, 0, 0));
	foco->setAmb(fvec4(0, 0, 0, 1));
	foco->setDiff(fvec4(1.0, 1.0, 1.0, 1.0));
	foco->setSpec(fvec4(0.5, 0.5, 0.5, 1.0));
	foco->setSpot(fvec3(0, -1, 0), 80.0, 0);
	foco->enable();
	this->grObjects.push_back(chassis);
	this->grObjects.push_back(rotorF1);
	this->grObjects.push_back(rotorF2);
	this->grObjects.push_back(rotorB3);
	this->grObjects.push_back(rotorB4);
	

}

void Dron::render(glm::dmat4 const& modelViewMat) {
	if (foco != nullptr) {
		foco->upload(modelViewMat*modelMat);
	}
	CompoundEntity::render(modelViewMat);
}
/*
void Dron::render(dmat4 const& modelViewMat)
{
	sptLuz->upload(modelViewMat);
}*/

void Dron::update()
{
	rotorF1->update();
	rotorF2->update();
	rotorB3->update();
	rotorB4->update();
}

void Dron::update(GLuint timeElapsed) { }

void Dron::luzOnOff(bool luz)
{
	if (luz) {
		foco->enable();
	}
	else {
		foco->disable();
	}
}

//-------------------------------------------------------------------------
//CONO PER RIVOLUZIONE
Cone::Cone(GLdouble h, GLdouble r)
{
	//h altura de cono, r radio de la base
	int m = 3; //m = numero puntos perfil
	dvec3* perfil = new dvec3[m];
	perfil[0] = dvec3(0.0, 0.0, 0.0);
	perfil[1] = dvec3(r, 0.0, 0.0);
	perfil[2] = dvec3(0.0, h, 0.0);
	this->mesh = new MBR(m, 50, perfil);
}

void Cone::render(glm::dmat4 const & modelViewMat)
{
	//luceFaro->upload(modelViewMat*modelMat);
	uploadMvM(modelViewMat*modelMat);
	mesh->render();

}

void Cone::update()
{
}

void Cone::update(GLuint timeElapsed)
{
}
//-------------------------------------------------------------------------
//SFERA PER RIVOLUZIONE
Esfera::Esfera(GLint p, GLint m, GLdouble r, bool ma) : Entity()
{
	material = ma;
	paralelos = p;
	meridianos = m;
	radio = r;
	GLdouble x = 0;
	GLdouble y = -r;
	GLdouble ang = -90.0;
	GLdouble incr = 180.0 / m;
	dvec3* perfil = new dvec3[meridianos];
	//color = glm::fvec3(0.8, 0.4, 0.2);

	for (int i = 0; i < m - 1; i++) {

		perfil[i] = dvec3(x, y, 0.0);
		ang = ang - incr;
		x = r * cos(radians(ang));
		y = r * sin(radians(ang));

	}
	perfil[m - 1] = dvec3(0, r, 0.0);
	color = dvec3(0.8, 0.4, 0.2);
	if (material) {
		mat = new Material();
	}
	this->mesh = new MBR(paralelos, meridianos, perfil);
}

void Esfera::render(glm::dmat4 const & modelViewMat)
{
	uploadMvM(modelViewMat*modelMat);
	//if (color != fvec3(-1.0, -1.0, -1.0)) glColor3f(color[0], color[1], color[2]);
	//else glColor3f(0.2, 0.4, 0.6);
	//glColor3f(0.0, 0.0, 1.0);
	//glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	
	// APARTADO 20 e 21
	// Elimino il colore della sfera 
	// Aggiungo attributo Material alla classe sfera
	// Imposto o setGold(), setSilver() o setCooper() e faccio upload()
	if (material) {
		mat->setGold();
		mat->upload();
	}
	// COLORE SFERA APARTADO 18 e 19
	//glColor3f(0.8, 0.4, 0.2);
	// COLORE SFERA APARTADO 22
	glColor3f(0.75164, 0.60648, 0.22648);

	/*
	if (mat == nullptr) {
		if (colorEsfera[0] == -1.0) {
			glColor3f(0.8, 0.4, 0.2);
		}
		else {
			glColor3f(0.75164, 0.60648, 0.22648);
		}
	}
	*/
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	mesh->render();
}

void Esfera::setMaterial(Material *m)
{
	mat = m;
}

void Esfera::setColor(GLdouble a, GLdouble b, GLdouble c)
{
	colorEsfera = glm::fvec3(a, b, c);
}

void Esfera::update()
{
}

void Esfera::update(GLuint timeElapsed)
{
}
//-------------------------------------------------------------------------
//CILINDRO PER RIVOLUZIONE
Cilindro::Cilindro(GLdouble h, GLdouble r)
{
	//h altura del cilindro, r radio de la base
	int m = 4; //m = numero puntos perfil
	dvec3* perfil = new dvec3[m];
	perfil[0] = dvec3(0.0, 0.0, 0.0);
	perfil[1] = dvec3(r, 0.0, 0.0);
	perfil[2] = dvec3(r, h, 0.0);
	perfil[3] = dvec3(0.0, h, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	this->mesh = new MBR(m, 50, perfil);
}

void Cilindro::render(glm::dmat4 const & modelViewMat)
{
	uploadMvM(modelViewMat*modelMat);
	mesh->render();
}

void Cilindro::update()
{
}

void Cilindro::update(GLuint timeElapsed)
{
}
//-------------------------------------------------------------------------
//ANELLO PER RIVOLUZIONE
Anello::Anello(GLdouble h, GLdouble r)
{
	//h altezza anello
	int m = 2; //m = numero puntos perfil
	dvec3* perfil = new dvec3[m];
	perfil[0] = dvec3(r, 0.0, 0.0);
	perfil[1] = dvec3(r, h, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	this->mesh = new MBR(m, 50, perfil);
}

void Anello::render(glm::dmat4 const & modelViewMat)
{
	uploadMvM(modelViewMat*modelMat);
	mesh->render();
}

void Anello::update()
{
}

void Anello::update(GLuint timeElapsed)
{
}
//-------------------------------------------------------------------------
//TORO PER RIVOLUZIONE
Toro::Toro(GLdouble r, GLdouble dFromZero, GLint nPerfil)
{
	GLdouble x = 0;
	GLdouble y = -r;
	GLdouble ang = -90.0;
	GLdouble incr = 360.0 / nPerfil;
	dvec3* perfil = new dvec3[nPerfil];
	for (int i = 0; i < nPerfil - 1; i++) {

		perfil[i] = dvec3(x + dFromZero, y, 0.0);
		ang = ang - incr;
		x = r * cos(radians(ang));
		y = r * sin(radians(ang));

	}
	perfil[nPerfil - 1] = dvec3(dFromZero, -r, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	//mat = new Material();
	//mat->setGold();
	//mat->upload();
	this->mesh = new MBR(nPerfil, 100, perfil);
}

void Toro::render(glm::dmat4 const & modelViewMat)
{
	uploadMvM(modelViewMat*modelMat);
	dmat4 auxMat = modelMat;
	modelMat = glm::rotate(modelMat, glm::radians(90.0), glm::dvec3(1.0, 0.0, 0));
	uploadMvM(modelViewMat);
	mesh->render();
	modelMat = auxMat;
}

void Toro::update()
{
}

void Toro::update(GLuint timeElapsed)
{
}
//-------------------------------------------------------------------------
//BICCHIERE PER RIVOLUZIONE

Bicchiere::Bicchiere(GLdouble baseRadio, GLdouble topRadio, GLdouble h) {
	int m = 11;										//m = numero puntos perfil
	dvec3* perfil = new dvec3[m];
	perfil[0] = dvec3(baseRadio, 0.0, 0.0);
	perfil[1] = dvec3(baseRadio - 10, 5.0, 0.0);
	perfil[2] = dvec3(baseRadio - 30, 6.0, 0.0);
	perfil[3] = dvec3(baseRadio - 33, 10.0, 0.0);
	perfil[4] = dvec3(baseRadio - 45, 15.0, 0.0);
	perfil[5] = dvec3(baseRadio - 45, 70.0, 0.0);
	perfil[6] = dvec3(baseRadio, 85.0, 0.0);
	perfil[7] = dvec3(topRadio, h, 0.0);
	perfil[8] = dvec3(topRadio - 5, h, 0.0);
	perfil[9] = dvec3(topRadio - 30, 85.0, 0.0);
	perfil[10] = dvec3(0.0, 75.0, 0.0);
	glColor3f(1.0, 0.0, 1.0);
	this->mesh = new MBR(m, 50, perfil);
}

void Bicchiere::render(glm::dmat4 const & modelViewMat)
{
	uploadMvM(modelViewMat*modelMat);
	mesh->render();
}

void Bicchiere::update()
{
}

void Bicchiere::update(GLuint timeElapsed)
{
}

//-------------------------------------------------------------------------
//TAJ MAHAL PER RIVOLUZIONE

TajMahal::TajMahal(GLdouble baseRadio, GLdouble h) {
	int m = 18;										//m = numero puntos perfil
	dvec3* perfil = new dvec3[m];
	perfil[0] = dvec3(baseRadio, 0.0, 0.0);
	perfil[1] = dvec3(baseRadio, 40.0, 0.0);
	perfil[2] = dvec3(baseRadio + 5, 45.0, 0.0);
	perfil[3] = dvec3(baseRadio, baseRadio, 0.0);
	perfil[4] = dvec3(baseRadio, 60.0, 0.0);
	perfil[5] = dvec3(baseRadio + 3, 65.0, 0.0);
	perfil[6] = dvec3(baseRadio + 7, 70.0, 0.0);
	perfil[7] = dvec3(baseRadio + 10, 80.0, 0.0);
	perfil[8] = dvec3(baseRadio + 5, 85.0, 0.0);
	perfil[8] = dvec3(baseRadio - 15, 95.0, 0.0);
	perfil[9] = dvec3(baseRadio - 20, 105.0, 0.0);
	perfil[10] = dvec3(baseRadio - 15, 110.0, 0.0);
	perfil[11] = dvec3(baseRadio - 35, 120.0, 0.0);
	perfil[12] = dvec3(0, 130.0, 0.0);
	perfil[13] = dvec3(6, 135.0, 0.0);
	perfil[14] = dvec3(3, 140.0, 0.0);
	perfil[15] = dvec3(0, 145.0, 0.0);
	perfil[16] = dvec3(1.5, 150.0, 0.0);
	perfil[17] = dvec3(0, 155.0, 0.0);

	glColor3f(0.0, 0.0, 0.0);
	this->mesh = new MBR(m, 100, perfil);
}

void TajMahal::render(glm::dmat4 const & modelViewMat)
{
	uploadMvM(modelViewMat*modelMat);
	mesh->render();
}

void TajMahal::update()
{
}

void TajMahal::update(GLuint timeElapsed)
{
}
//SEMISFERA PER RIVOLUZIONE
Semisfera::Semisfera(GLint p, GLint m, GLdouble r, bool ma) : Entity()
{
	material = ma;
	paralelos = p;
	meridianos = m;
	radio = r;
	GLdouble x = r;
	GLdouble y = 0;
	GLdouble ang = 0;
	GLdouble incr = 90 / m;
	dvec3* perfil = new dvec3[meridianos];
	perfil[0] = dvec3(0.0, 0.0, 0.0);

	for (int i = 1; i < m - 1; i++) {

		perfil[i] = dvec3(x, y, 0.0);
		ang = ang + incr;
		x = r * cos(radians(ang));
		y = r * sin(radians(ang));

	}
	perfil[m - 1] = dvec3(0, r, 0.0);
	if (material) {
		mat = new Material();
	}
	this->mesh = new MBR(paralelos, meridianos, perfil);
}

void Semisfera::render(glm::dmat4 const & modelViewMat)
{
	uploadMvM(modelViewMat*modelMat);
	//if (color != fvec3(-1.0, -1.0, -1.0)) glColor3f(color[0], color[1], color[2]);
	//else glColor3f(0.2, 0.4, 0.6);
	//glColor3f(0.0, 0.0, 1.0);
	//glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	if (material) {
		mat->setGold();
		mat->upload();
	}
	/*if (mat == nullptr) {
		if (colorEsfera[0] == -1.0) {
			glColor3f(0.8, 0.4, 0.2);
		}
		else {
			glColor3f(0.75164, 0.60648, 0.22648);
		}
	}*/
	glColor3f(0.75164, 0.60648, 0.22648);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	mesh->render();
}

void Semisfera::setMaterial(Material *m)
{
	mat = m;
}

void Semisfera::setColor(GLdouble a, GLdouble b, GLdouble c)
{
	colorEsfera = glm::fvec3(a, b, c);
}

void Semisfera::update() {}

void Semisfera::update(GLuint timeElapsed){}

//LAMPADA
Lampada::Lampada(bool ma) : Entity()
{
	material = ma;
	lampadina = new SpotLight();
	esfera = new Esfera(200, 200, 100, true);
	int m = 8;															//m = numero puntos perfil
	dvec3* perfil = new dvec3[m];
	perfil[0] = dvec3(30.0, 0.0, 0.0);
	perfil[1] = dvec3(20.0, 10.0, 0.0);
	perfil[2] = dvec3(10.0, 10.0, 0.0);
	perfil[3] = dvec3(10.0, 90.0, 0.0);
	perfil[4] = dvec3(20.0, 90.0, 0.0);
	perfil[5] = dvec3(40.0, 40.0, 0.0);
	perfil[6] = dvec3(41.0, 40.0, 0.0);
	perfil[7] = dvec3(20.0, 110.0, 0.0);
	if (material) {
		mat = new Material();
	}
	// Lampadina
	lampadina->setPosDir(fvec3(0, 100, 0));
	lampadina->setAmb(fvec4(0, 0, 0, 1));
	lampadina->setDiff(fvec4(1.0, 1.0, 1.0, 1.0));
	lampadina->setSpec(fvec4(0.5, 0.5, 0.5, 1.0));
	lampadina->setSpot(fvec3(0, 1, 0), 100.0, 0);
	lampadina->enable();
	this->mesh = new MBR(m, 500, perfil);
}

void Lampada::render(glm::dmat4 const & modelViewMat)
{
	uploadMvM(modelViewMat*modelMat);
	// MATERIALE SI O NO
	if (material) {
		mat->setCooper();
		mat->upload();
	}
	glColor3f(0.75164, 0.60648, 0.22648);
	// Lampadina
	lampadina->upload(modelViewMat);
	mesh->render();

	//Esfera 
	dmat4 auxMat1 = dmat4(1.0);
	auxMat1 = translate(auxMat1, dvec3(0, 150, 0));
	esfera->setModelMat(auxMat1);
	esfera->render(modelViewMat);

}

void Lampada::update() {}

void Lampada::update(GLuint timeElapsed) {}

//-------------------------------------------------------------------------
//EsferaYDrone
EsferaYDrone::EsferaYDrone()
{
	dron = new Dron();
	esfera = new Esfera(300, 300, 200, false);
}
//-------------------------------------------------------------------------
EsferaYDrone::~EsferaYDrone()
{
	delete mesh; mesh = nullptr;
};
//-------------------------------------------------------------------------
void EsferaYDrone::render(glm::dmat4 const & modelViewMat)
{
	uploadMvM(modelViewMat);
	dmat4 auxMat1 = dmat4(1.0);
	auxMat1 = rotate(auxMat1, radians(parallelo), dvec3(0, 1, 0));
	auxMat1 = rotate(auxMat1, radians(meridiano), dvec3(0, 0, 1));
	auxMat1 = translate(auxMat1, dvec3(0, 210, 0));
	//	auxMat1 = rotate(auxMat1, radians(parallelo), dvec3(0, 1, 0));
	auxMat1 = scale(auxMat1, dvec3(0.05, 0.05, 0.05));
	dron->setModelMat(auxMat1);
	//dron->sptLuz->upload(modelViewMat);
	esfera->render(modelViewMat);
	uploadMvM(modelViewMat);
	dron->render(modelViewMat);
}

void EsferaYDrone::update()
{
	dron->update();
	meridiano = meridiano + 5;
}

void EsferaYDrone::update(GLuint timeElapsed)
{
}

void EsferaYDrone::move(GLuint num)
{
	dron->update();
	if (num == 1) {
		meridiano = meridiano + 5;
	}
	else if (num == 2) {
		meridiano = meridiano - 5;
	}
	else if (num == 3) {
		parallelo = parallelo + 5;
	}
	else {
		parallelo = parallelo - 5;
	}
}
//-------------------------------------------------------------------------
//TheBigDrone
TheBigDrone::TheBigDrone()
{
	dron = new Dron();
	dron1 = new Dron();
	dron2 = new Dron();
	dron3 = new Dron();
	dron4 = new Dron();
}

TheBigDrone::~TheBigDrone()
{
	delete mesh; mesh = nullptr;
};

void TheBigDrone::render(glm::dmat4 const & modelViewMat)
{
	//Drone grande
	dron->render(modelViewMat);
	//Primo drone piccolo
	dmat4 auxMat1 = dmat4(1.0);
	auxMat1 = translate(auxMat1, dvec3(0, (150 / 4) + 50, 0));
	auxMat1 = translate(auxMat1, dvec3(-200, 0, 0));
	auxMat1 = translate(auxMat1, dvec3(0, 0, -200));
	auxMat1 = scale(auxMat1, dvec3(0.2, 0.2, 0.2));
	dron1->setModelMat(auxMat1);
	dron1->render(modelViewMat);
	// render prima di compound entity
	//dron1->render(modelViewMat*auxMat1);
	uploadMvM(modelViewMat);
	//Secondo drone piccolo
	dmat4 auxMat2 = dmat4(1.0);
	auxMat2 = translate(auxMat2, dvec3(0, (150 / 4) + 50, 0));
	auxMat2 = translate(auxMat2, dvec3(200, 0, 0));
	auxMat2 = translate(auxMat2, dvec3(0, 0, -200));
	auxMat2 = scale(auxMat2, dvec3(0.2, 0.2, 0.2));
	dron2->setModelMat(auxMat2);
	dron2->render(modelViewMat);
	//dron2->render(modelViewMat*auxMat2);
	uploadMvM(modelViewMat);
	//Terzo drone piccolo
	dmat4 auxMat3 = dmat4(1.0);
	auxMat3 = translate(auxMat3, dvec3(0, (150 / 4) + 50, 0));
	auxMat3 = translate(auxMat3, dvec3(200, 0, 0));
	auxMat3 = translate(auxMat3, dvec3(0, 0, 200));
	auxMat3 = scale(auxMat3, dvec3(0.2, 0.2, 0.2));
	dron3->setModelMat(auxMat3);
	dron3->render(modelViewMat);
	//dron3->render(modelViewMat*auxMat3);
	uploadMvM(modelViewMat);
	//Quarto drone piccolo
	dmat4 auxMat4 = dmat4(1.0);
	auxMat4 = translate(auxMat4, dvec3(0, (150 / 4) + 50, 0));
	auxMat4 = translate(auxMat4, dvec3(-200, 0, 0));
	auxMat4 = translate(auxMat4, dvec3(0, 0, 200));
	auxMat4 = scale(auxMat4, dvec3(0.2, 0.2, 0.2));
	dron4->setModelMat(auxMat4);
	dron4->render(modelViewMat);
	//dron4->render(modelViewMat*auxMat4);
	uploadMvM(modelViewMat);
}

void TheBigDrone::update()
{
	dron->update();
	dron1->update();
	dron2->update();
	dron3->update();
	dron4->update();

}

void TheBigDrone::update(GLuint timeElapsed){}

// Rueda
Rueda::Rueda(GLdouble baseRadio, GLdouble topRadio, GLdouble altura, int lados, int rodajas, dvec3 color) : CompoundEntity()
{
	br = baseRadio;
	tr = topRadio;
	h = altura;
	l = lados;
	r = rodajas;
	length = br * 2 - 2;
	width = altura;
	paleta1 = new Rectangulo(length - 10, width, dvec3(0, 0, 0));
	paleta2 = new Rectangulo(length - 10, width, dvec3(0, 0, 0));
	cylinder = new Cylinder(br, tr, h, l, r, color);

	dmat4 auxMat = dmat4(1.0);
	auxMat = translate(auxMat, dvec3(0, 0, width / 2));
	auxMat = rotate(auxMat, radians((double)90), dvec3(0, 1, 0));
	//auxMat = rotate(auxMat, radians(anguloPaleta), dvec3(1, 0, 0));
	paleta1->setModelMat(auxMat);

	dmat4 auxMat2 = dmat4(1.0);
	auxMat2 = translate(auxMat2, dvec3(0, 0, width / 2));
	auxMat2 = rotate(auxMat2, radians((double)90), dvec3(0, 1, 0));
	auxMat2 = rotate(auxMat2, radians((double)90), dvec3(1, 0, 0));
	//auxMat2 = rotate(auxMat2, radians(anguloPaleta), dvec3(1, 0, 0));
	paleta2->setModelMat(auxMat2);

	this->grObjects.push_back(cylinder);
	this->grObjects.push_back(paleta1);
	this->grObjects.push_back(paleta2);
}

Rueda::~Rueda()
{
	delete mesh; mesh = nullptr;
};

void Rueda::update(){ }

void Rueda::move(GLuint num)
{
	dmat4 auxMat1 = dmat4(1.0);
	dmat4 auxMat2 = dmat4(1.0);
	anguloPaleta += 5;
	
	if (num == 1) {
		auxMat1 = rotate(auxMat1, radians(-anguloPaleta), dvec3(0, 0, 1));
		auxMat2 = rotate(auxMat2, radians(-anguloPaleta), dvec3(0, 0, 1));
	}
	else if(num == 2) {
		auxMat1 = rotate(auxMat1, radians(anguloPaleta), dvec3(0, 0, 1));
		auxMat2 = rotate(auxMat2, radians(anguloPaleta), dvec3(0, 0, 1));
	}

	auxMat1 = translate(auxMat1, dvec3(0, 0, width / 2));
	auxMat1 = rotate(auxMat1, radians(90.0), dvec3(0, 1, 0));

	auxMat2 = translate(auxMat2, dvec3(0, 0, width / 2));
	auxMat2 = rotate(auxMat2, radians(90.0), dvec3(0, 1, 0));
	auxMat2 = rotate(auxMat2, radians(90.0), dvec3(1, 0, 0));

	paleta1->setModelMat(auxMat1);
	paleta2->setModelMat(auxMat2);
}
//-------------------------------------------------------------------------
// Coche
Coche::Coche() : CompoundEntity()
{
	Chassis *chasisCoche = new Chassis(50, 50);
	rueda1 = new Rueda(50, 50, 50, 50, 50, dvec3(1,0,0));
	rueda2 = new Rueda(50, 50, 50, 50, 50, dvec3(1, 0, 0));
	rueda3 = new Rueda(50, 50, 50, 50, 50, dvec3(0, 1, 0));
	rueda4 = new Rueda(50, 50, 50, 50, 50, dvec3(0, 1, 0));
	faroS = new Cone(100, 50);
	faroD = new Cone(100, 50);
	luceFaroS = new SpotLight();
	luceFaroD = new SpotLight();
	
	//Ruota Anteriore Sinistra
	dmat4 auxMat1 = dmat4(1.0);
	auxMat1 = translate(auxMat1, dvec3(75, 0, 0));
	auxMat1 = translate(auxMat1, dvec3(0, 0, -100));
	auxMat1 = scale(auxMat1, dvec3(0.5, 0.5, 0.5));
	rueda1->setModelMat(auxMat1);
	//Ruota Anteriore Destra
	dmat4 auxMat2 = dmat4(1.0);
	auxMat2 = translate(auxMat2, dvec3(75, 0, 0));
	auxMat2 = translate(auxMat2, dvec3(0, 0, 75));
	auxMat2 = scale(auxMat2, dvec3(0.5, 0.5, 0.5));
	rueda2->setModelMat(auxMat2);
	//Ruota Posteriore Sinistra
	dmat4 auxMat3 = dmat4(1.0);
	auxMat3 = translate(auxMat3, dvec3(-75, 0, 0));
	auxMat3 = translate(auxMat3, dvec3(0, 0, -100));
	auxMat3 = scale(auxMat3, dvec3(0.5, 0.5, 0.5));
	rueda3->setModelMat(auxMat3);
	//Ruota Posteriore Destra
	dmat4 auxMat4 = dmat4(1.0);
	auxMat4 = translate(auxMat4, dvec3(-75, 0, 0));
	auxMat4 = translate(auxMat4, dvec3(0, 0, 75));
	auxMat4 = scale(auxMat4, dvec3(0.5, 0.5, 0.5));
	rueda4->setModelMat(auxMat4);
	//Faro Sinistro
	dmat4 auxMat5 = dmat4(1.0);
	auxMat5 = translate(auxMat5, dvec3(65, 0, 0));
	auxMat5 = translate(auxMat5, dvec3(0, 0, -30));
	auxMat5 = translate(auxMat5, dvec3(0, -10, 0));
	auxMat5 = rotate(auxMat5, radians(45.0), dvec3(0, 0, 1));
	auxMat5 = scale(auxMat5, dvec3(0.5, 0.5, 0.5));
	faroS->setModelMat(auxMat5);
	//Faro Destro
	dmat4 auxMat6 = dmat4(1.0);
	auxMat6 = translate(auxMat6, dvec3(65, 0, 0));
	auxMat6 = translate(auxMat6, dvec3(0, 0, 30));
	auxMat6 = translate(auxMat6, dvec3(0, -10, 0));
	auxMat6 = rotate(auxMat6, radians(45.0), dvec3(0, 0, 1));
	auxMat6 = scale(auxMat6, dvec3(0.5, 0.5, 0.5));
	faroD->setModelMat(auxMat6);
	// LUCE FARO SINISTRO
	luceFaroS->setPosDir(fvec3(65, -10, -30));
	luceFaroS->setAmb(fvec4(0, 0, 0, 1));
	luceFaroS->setDiff(fvec4(1.0, 1.0, 1.0, 1.0));
	luceFaroS->setSpec(fvec4(0.5, 0.5, 0.5, 1.0));
	luceFaroS->setSpot(fvec3(1, 0, 0), 15.0, 0);
	luceFaroS->enable();
	// LUCE FARO DESTRO
	luceFaroD->setPosDir(fvec3(65, -10, 30));
	luceFaroD->setAmb(fvec4(0, 0, 0, 1));
	luceFaroD->setDiff(fvec4(1.0, 1.0, 1.0, 1.0));
	luceFaroD->setSpec(fvec4(0.5, 0.5, 0.5, 1.0));
	luceFaroD->setSpot(fvec3(1, 0, 0), 15.0, 0);
	luceFaroD->enable();

	this->grObjects.push_back(chasisCoche);
	this->grObjects.push_back(rueda1);
	this->grObjects.push_back(rueda2);
	this->grObjects.push_back(rueda3);
	this->grObjects.push_back(rueda4);
	this->grObjects.push_back(faroD);
	this->grObjects.push_back(faroS);

}
void Coche::render(glm::dmat4 const& modelViewMat) {
	if (luceFaroS != nullptr) {
		luceFaroS->upload(modelViewMat*modelMat);
	}
	if (luceFaroD != nullptr) {
		luceFaroD->upload(modelViewMat*modelMat);
	}
	CompoundEntity::render(modelViewMat);
	
}
Coche::~Coche()
{
	delete mesh; mesh = nullptr;
};
/*
void Coche::render(dmat4 const& modelViewMat)
{
	//Ruota Anteriore Sinistra
	dmat4 auxMat1 = dmat4(1.0);
	auxMat1 = translate(auxMat1, dvec3(75, 0, 0));
	auxMat1 = translate(auxMat1, dvec3(0, 0, -100));
	auxMat1 = scale(auxMat1, dvec3(0.5, 0.5, 0.5));
	rueda1->setModelMat(auxMat1);
	rueda1->render(modelViewMat*auxMat1);
	//Ruota Anteriore Destra
	dmat4 auxMat2 = dmat4(1.0);
	auxMat2 = translate(auxMat2, dvec3(75, 0, 0));
	auxMat2 = translate(auxMat2, dvec3(0, 0, 75));
	auxMat2 = scale(auxMat2, dvec3(0.5, 0.5, 0.5));
	rueda2->setModelMat(auxMat2);
	rueda2->render(modelViewMat*auxMat2);
	//Ruota Posteriore Sinistra
	dmat4 auxMat3 = dmat4(1.0);
	auxMat3 = translate(auxMat3, dvec3(-75, 0, 0));
	auxMat3 = translate(auxMat3, dvec3(0, 0, -100));
	auxMat3 = scale(auxMat3, dvec3(0.5, 0.5, 0.5));
	rueda3->setModelMat(auxMat3);
	rueda3->render(modelViewMat*auxMat3);
	//Ruota Posteriore Destra
	dmat4 auxMat4 = dmat4(1.0);
	auxMat4 = translate(auxMat4, dvec3(-75, 0, 0));
	auxMat4 = translate(auxMat4, dvec3(0, 0, 75));
	auxMat4 = scale(auxMat4, dvec3(0.5, 0.5, 0.5));
	rueda4->setModelMat(auxMat4);
	rueda4->render(modelViewMat*auxMat4);
	chasisCoche->render(modelViewMat);
	uploadMvM(modelViewMat);
	//Muro
	dmat4 auxMat5 = dmat4(1.0);
	auxMat5 = translate(auxMat5, dvec3(0, -200, 0));
	auxMat5 = rotate(auxMat5, radians((double)90), dvec3(1, 0, 0));
	muro->setModelMat(auxMat5);
	muro->render(modelViewMat);
	uploadMvM(modelViewMat);

	//Faro Sinistro
	faroS = new SpotLight(fvec3(0, 0, 0));
	faroS->setAmb(fvec4(0, 0, 0, 1));
	faroS->setDiff(fvec4(1.0, 1.0, 1.0, 1.0));
	faroS->setSpec(fvec4(0.5, 0.5, 0.5, 1.0));
	faroS->setSpot(fvec3(0, -1, 0), 80.0, 1);
	if (faroS != nullptr) {
		faroS->upload(modelViewMat);
		faroS->enable();
		uploadMvM(modelViewMat);

	}
	//Faro Destro
	//faroD->setAmb(fvec4(0, 0, 0, 1));
	//faroD->setDiff(fvec4(1.0, 1.0, 1.0, 1.0));
	//faroD->setSpec(fvec4(0.5, 0.5, 0.5, 1.0));
	//faroD->setSpot(fvec3(1, 0, 0), 80.0, 1);
	//if (faroD != nullptr) {
	//	faroD->upload(modelViewMat);
	//	faroD->enable();
	//}
}*/

void Coche::update(){}

void Coche::update(GLuint timeElapsed){}

void Coche::move(GLuint num)
{
	rueda1->move(num);
	rueda2->move(num);
	rueda3->move(num);
	rueda4->move(num);

}

//ARBOR
Arbor::Arbor()
{
	// BASE RADIO, TOP RADIO; ALTEZZA, LADOS, RODAJAS, COLORE
	tronco = new Cylinder(20, 20, 200, 50, 50, dvec3(1, 0, 0));
	chioma1 = new Cylinder(70, 1, 130, 50, 50, dvec3(0, 1, 0));
	tronco2 = new Cylinder(20, 20, 200, 50, 50, dvec3(1, 0, 0));
	chioma2 = new Sphere(70, dvec3(0, 1, 0));
}

Arbor::~Arbor()
{
	delete mesh; mesh = nullptr;
};

void Arbor::render(glm::dmat4 const & modelViewMat)
{
	uploadMvM(modelViewMat);
	//Tronco
	dmat4 auxMat1 = dmat4(1.0);
	auxMat1 = translate(auxMat1, dvec3(0, 100, 0));
	auxMat1 = rotate(auxMat1, radians(90.0), dvec3(1, 0, 0));
	tronco->setModelMat(auxMat1);
	tronco->render(modelViewMat);
	//Chioma 1
	dmat4 auxMat2 = dmat4(1.0);
	auxMat2 = translate(auxMat2, dvec3(0, 50, 0));
	auxMat2 = rotate(auxMat2, radians(90.0), dvec3(-1, 0, 0));
	chioma1->setModelMat(auxMat2);
	chioma1->render(modelViewMat);
	uploadMvM(modelViewMat);
	//Tronco 2
	dmat4 auxMat3 = dmat4(1.0);
	auxMat3 = translate(auxMat3, dvec3(200, 100, 0));
	auxMat3 = rotate(auxMat3, radians(90.0), dvec3(1, 0, 0));
	tronco2->setModelMat(auxMat3);
	tronco2->render(modelViewMat);
	//Chioma 2
	dmat4 auxMat4 = dmat4(1.0);
	auxMat4 = translate(auxMat4, dvec3(200, 50, 0));
	auxMat4 = rotate(auxMat4, radians(90.0), dvec3(-1, 0, 0));
	chioma2->setModelMat(auxMat4);
	chioma2->render(modelViewMat);
	uploadMvM(modelViewMat);
}

void Arbor::update() { }

void Arbor::update(GLuint timeElapsed) {}

// COCHE E STRADA
//-------------------------------------------------------------------------
//CocheyStrada
CocheyStrada::CocheyStrada()
{
	coche = new Coche();
	sfera = new Esfera(200, 200, 150, false);
	arbor = new Arbor();
}
//-------------------------------------------------------------------------
CocheyStrada::~CocheyStrada()
{
	delete mesh; mesh = nullptr;
};
//-------------------------------------------------------------------------
void CocheyStrada::render(glm::dmat4 const & modelViewMat)
{
	// COCHE
	coche->render(modelViewMat);
	// SFERA
	dmat4 auxMat1 = dmat4(1.0);
	auxMat1 = translate(auxMat1, dvec3(600, 0, 0));
	auxMat1 = scale(auxMat1, dvec3(2, 2, 2));
	sfera->setModelMat(auxMat1);
	sfera->render(modelViewMat);
	uploadMvM(modelViewMat);
	// ARBOR
	dmat4 auxMat2 = dmat4(1.0);
	auxMat2 = translate(auxMat2, dvec3(400, 0, 0));
	auxMat2 = rotate(auxMat2, radians(90.0), dvec3(0, 1, 0));
	arbor->setModelMat(auxMat2);
	arbor->render(modelViewMat*auxMat2);
	uploadMvM(modelViewMat);
}

void CocheyStrada::update(){}

void CocheyStrada::update(GLuint timeElapsed){}

void CocheyStrada::move(GLuint num){
	dmat4 auxMat = dmat4(1.0);
	if (num == 1) {
		movimentoLineare += 5;
		auxMat = translate(auxMat, dvec3(movimentoLineare, 0, movimentoLaterale));
		coche->move(num);
	}
	else if(num == 2){
		movimentoLineare -= 5;
		auxMat = translate(auxMat, dvec3(movimentoLineare, 0, movimentoLaterale));
		coche->move(num);

	}
	else if (num == 3) {
		movimentoLaterale += 5;
		auxMat = translate(auxMat, dvec3(movimentoLineare, 0, movimentoLaterale));
	}
	else if (num == 4) {
		movimentoLaterale -= 5;
		auxMat = translate(auxMat, dvec3(movimentoLineare, 0, movimentoLaterale));
	}
	coche->setModelMat(auxMat);
}

// BB8 COMPOUND ENTITY

BB8::BB8() : CompoundEntity()
{
	head = new Semisfera(89, 89, 150, false);
	body = new Esfera(150, 150, 150, false);
	//Head
	dmat4 auxMat1 = dmat4(1.0);
	auxMat1 = translate(auxMat1, dvec3(0, 75, 0));
	head->setModelMat(auxMat1);
	//Body
	this->grObjects.push_back(head);
	this->grObjects.push_back(body);
}

void BB8::render(glm::dmat4 const& modelViewMat) {
	CompoundEntity::render(modelViewMat);
}

void BB8::update(){}

void BB8::update(GLuint timeElapsed) { }

void BB8::luzOnOff(bool luz) {}

