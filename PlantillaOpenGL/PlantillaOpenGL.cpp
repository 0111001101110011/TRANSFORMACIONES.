#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

using namespace std;
float posicionXTriangulo = 0.0f;
float posicionYTriangulo = 0.0f;
float angulo = 0.0f;

enum Direccion { Izquierda, Derecha, Arriba, Abajo };
Direccion direccionTriangulo = Izquierda;
Direccion direccionTrianguloVertical = Arriba;


void dibujarTriangulos() {

	//Utilizar matriz identidad
	glPushMatrix();

		//Rotar
	/* glRotatef(180.0f, 0.0f, 0.0f, 1.0f); */

	//Transformaciones
	glTranslatef(posicionXTriangulo, posicionYTriangulo, 0.0f);
	glRotatef(angulo, 0.0f, 1.0f, 5.0f );
	


	//Escalado
	/* glScalef(0.2f, 0.2f, 0.2f); */


	//Dibujar los vertices
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.8f, 0);
	glVertex3f(-0.2f, -0.2f, 0);
	glVertex3f(0.2f, -0.2f, 0);
	glVertex3f(0.0f, 0.2f, 0);
	glEnd();

	glPopMatrix();
}


void dibujar() {
	dibujarTriangulos();

}


void actualizar() {

	if (angulo >= 360) {
		angulo = 0.0f;
	}
	angulo += 0.01f;


	if (direccionTriangulo == Direccion::Izquierda) {

		if (posicionXTriangulo > -0.8f) {

			posicionXTriangulo -= 0.001f;
		
		} else {
			direccionTriangulo = Direccion::Derecha;
		}

	}

	if(direccionTriangulo == Direccion::Derecha) {
		if (posicionXTriangulo < 0.8f) {
			posicionXTriangulo += 0.001f;
		}
		else 
		{
			direccionTriangulo = Direccion::Izquierda;
		}
	}

	//Arriba y Abajo

	if (direccionTrianguloVertical == Direccion::Abajo) {
		if (posicionYTriangulo > - 0.8f) {
			posicionYTriangulo -= 0.002f;
		}
		else
		{
			direccionTrianguloVertical = Direccion::Arriba;
		}
	}

	if (direccionTrianguloVertical == Direccion::Arriba) {
		if (posicionYTriangulo < 0.8f) {
			posicionYTriangulo += 0.002f;
		}
		else
		{
			direccionTrianguloVertical = Direccion::Abajo;
		}
	}

} 

int main()
{
	//Creamos una ventana
	GLFWwindow *window;

	//Si no se puede inicializar glfw
	//Iniciamos ejecucion
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	//Si se pudo iniciar GLFW
	//entonces inicializamosla ventana
	window = glfwCreateWindow(1024, 768, "Ventana", NULL, NULL);
	//Si nopodemos iniciar la ventana
	//Entonces terminamos ejecucion
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	//Establecemos el contexto
	glfwMakeContextCurrent(window);

	//Una vez establecido el contexto activamos funciones modernas
	glewExperimental = true;
	GLenum errorGlew = glewInit();
	if (errorGlew != GLEW_OK) {
		cout << glewGetErrorString(errorGlew);
	}

	const GLubyte *versionGL = glGetString(GL_VERSION);
	cout << "Version OpenGL: " << versionGL;

	//ciclode dibujo (Draw loop)
	while (!glfwWindowShouldClose(window)) {
		//Establecer region de dibujo
		glViewport(0, 0, 1024, 768);
		//Establece el color de borrado
		glClearColor(0, 181, 252, 0);
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