/*
 * main.cpp
 *
 *  Created on: 16 jun. 2020
 *      Author: rogrp
 */

#include <iostream>
#include <math.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
using namespace std;

GLFWwindow* window;
GLuint VAO, VBO;

const int DIMENCION_PUNTO=2;
const int CANT_PUNTOS=13;

void coord_to_gl(GLfloat *m, int size, float space){
    /* transforma coordenadas enteras a coordenadas
     * compatibles con OpenGL
     * */
    for(int i=0; i<size; i++)
        m[i]*=space;
}

void init(){

    //  Representamos los puntos deseados en las coordenadas convencionales (enteras):
    GLfloat puntos[] = {
        -5,3,  -5,1,  -3,1, // Puntos en NorEste
        0,0, // Punto en Centro
        3,1,   3,3,   4,2,  5,1,  5,3, // Puntos en NorOeste
        -4,-2, // Punto en SurEste
        3.5,-2.5,  4,-2,  4.5,-1.5 // Puntos en SurOeste
    };

    const float SPACE = 0.16666f; // Espacio entre cada coordenada

    coord_to_gl(puntos, DIMENCION_PUNTO*CANT_PUNTOS, SPACE); // Adaptamos las cordenadas anteriores al sistema de coord. de OpenGL:


	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(
			GL_ARRAY_BUFFER,
			sizeof(puntos),
			puntos,
			GL_STATIC_DRAW
		);
}

void display(double currentTime) {
    double osc1 = abs(sin(currentTime));
    double osc2 = abs(cos(currentTime));
    double osc3 = abs(sin(currentTime + 10));

    double claridad = 0.7;

	glClearColor(
        osc1*claridad,
        osc2*claridad,
        osc3,
        0.0f);

	glClear(GL_COLOR_BUFFER_BIT);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(
			0,
			DIMENCION_PUNTO,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*) 0
	);
	glPointSize(30.0f);
	glDrawArrays(GL_POINTS, 0, CANT_PUNTOS); // 3 indices starting at 0 -> number of Vertex
	glDisableVertexAttribArray(0);
}

int main( void ){
	if (!glfwInit()) exit(EXIT_FAILURE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); 	// Resizable option.
	window = glfwCreateWindow(800, 800, "Ramos Paredes Roger Anthony", NULL, NULL);
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) exit(EXIT_FAILURE);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    glfwSwapInterval(0.5);
    init();

	while (!glfwWindowShouldClose(window)) {
		display(glfwGetTime());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
    glfwDestroyWindow(window);
	glfwTerminate();

	return 0;

}
