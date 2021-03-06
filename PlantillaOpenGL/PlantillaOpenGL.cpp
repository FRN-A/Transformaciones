// PlantillaOpenGL.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

using namespace std;

float angulo = 0;

float posicionXTriangulo = 0;
float posicionYTriangulo = 0;

enum Direccion {Izquierda, Derecha, Arriba, Abajo};
Direccion direccionTrianguloX = Direccion::Izquierda;
Direccion direccionTrianguloY = Direccion::Arriba;

void dibujarTrangulo() {
	//utilizar matriz identidad
	glPushMatrix();
	//transformaciones
	glTranslatef(posicionXTriangulo, posicionYTriangulo, 0);
	glRotatef(angulo, 1, 0, 0);

	//dibujar los vertices
	glBegin(GL_TRIANGLES);
	glColor3f(0.4, 0,0);
	glVertex3f(-0.4,- 0.4, 0);
	glVertex3f(0.4, -0.4, 0);
	glVertex3f(0, 0.4, 0);
	glEnd();

	//soltar la matriz
	glPopMatrix();
}

void dibujar() {
	dibujarTrangulo();
}

void actualizar() {
	if (angulo >= 360) {
		angulo = 0;
	}

	angulo += 0.1;

	if (direccionTrianguloX == Direccion::Izquierda) {
		if (posicionXTriangulo > -0.6)
			posicionXTriangulo -= 0.0005;
		else
			direccionTrianguloX = Direccion::Derecha;
	}
	if (direccionTrianguloX == Direccion::Derecha) {
		if (posicionXTriangulo < 0.6)
			posicionXTriangulo += 0.0005;
		else
			direccionTrianguloX = Direccion::Izquierda;
	}
	if (direccionTrianguloY == Direccion::Arriba) {
		if (posicionYTriangulo > -0.6)
			posicionYTriangulo -= 0.0002;
		else
			direccionTrianguloY = Direccion::Abajo;
	}
	if (direccionTrianguloY == Direccion::Abajo) {
		if (posicionYTriangulo < 0.6)
			posicionYTriangulo += 0.0002;
		else
			direccionTrianguloY = Direccion::Arriba;
	}
	
	

}

int main()
{
	//Declaramos apuntador de ventana
	GLFWwindow *window;

	//si no se pudo inicializar glfw terminamos ejecución
	if (!glfwInit())
		exit(EXIT_FAILURE);

	//si se pudo iniciar GLFW entonces inicializamos la ventana
	window = glfwCreateWindow(1024, 768, "Ventana", NULL, NULL);

	//si no podemos iniciar la ventana entonces terminamos la ejecución
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	//establecemos el contexto
	glfwMakeContextCurrent(window);

	//UNa vez establecido el contexto activamos funciones modernas (CPU/GPU)
	glewExperimental = true;
	GLenum errorGlew = glewInit();

	if (errorGlew != GLEW_OK) {
		cout << glewGetErrorString(errorGlew);
	}

	const GLubyte *versionGL = glGetString(GL_VERSION);
	cout << "Version OpenGL: " << versionGL;


	//Cilco de dibijo (Draw loop)
	while (!glfwWindowShouldClose(window)) {
		//Establecer region de dibujo
		glViewport(0, 0, 1024, 768);
		//Esctablece el color de borrado
		glClearColor(0.25, 0, 0.3, 1);
		//Borramos
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Rutina de dibujo
		actualizar();
		dibujar();
		

		//Cambiar los buffers
		glfwSwapBuffers(window);
		//Reconocer si hay entradas
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

    return 0;
}

