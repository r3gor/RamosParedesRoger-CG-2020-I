/*
 * main.cpp
 *
 *  Created on: 02 jul. 2020
 *      Author: rogrp
 */

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <vector>
#include <math.h>
#include <iostream>
#include "Utils.h"

using namespace std;

#define PUSH_COORD(P) vertices.insert(vertices.end(), {(P).x, (P).y}); 
#define PUSH_COLOR(C) vertices.insert(vertices.end(), {(C).x, (C).y, (C).z}); 


/* --------------------------------------------------------------------
 *                  constantes globales (EDITE AQUI) :)
 * -------------------------------------------------------------------- */
   
// TRIANGULO RECTO
const float CATETO1 = 5.0f;
const float CATETO2 = 7.0f;
const float R1 = 1, G1 = 0, B1 = 0; // COLOR

// TRIANGULO ESCALENO - OBS: procure LADO1 != LADO2 != LADO3
const float LADO1 = 4.0f;
const float LADO2 = 5.5f;
const float LADO3 = 7.5f;
const float R2 = 0, G2 = 1, B2 = 0; // COLOR

// TRIANGULO ISOCELES
const float LADO = 6.0f;
const float R3 = 0, G3 = 0, B3 = 1; // COLOR

// RECTANGULO
const float ALTO = 4.0f;
const float ANCHO = 7.0f; 
const float R4 = 1, G4 = 1, B4 = 0; // COLOR

/* -------------------------------------------------------------------- */

// variables globales
GLuint VBO, VAO;
GLuint shader_program;
GLFWwindow* window;

// vector que contendrá los vertices de las figuras generadas
vector<float> vertices(0); // (5 triangulos <> 15 vertices * dimension = 30 elementos)

// puntos generadores
glm::vec2 P0 = glm::vec2( 4.0f,  8.0f);
glm::vec2 P1 = glm::vec2(-8.0f,  8.2f);
glm::vec2 P2 = glm::vec2(-6.0f, -1.0f);
glm::vec2 P3 = glm::vec2( 2.0f, -1.0f);

// funciones que generan las figuras
void GEN_TRIANGULO_RECTO(glm::vec2 P, float CATETO1, float CATETO2, glm::vec3 color);
void GEN_TRIANG_ESCALENO(glm::vec2 P, float LADO1, float LADO2, float LADO3, glm::vec3 color);
void GEN_TRIANG_ISOCELES(glm::vec2 P, float LADO , glm::vec3 color);
void GEN_RECTANGULO(glm::vec2 P, float ANCHO, float ALTO, glm::vec3 color);
void coord_to_gl(float space);

void init(){
    
    GEN_TRIANGULO_RECTO(P1, CATETO1, CATETO2, glm::vec3(R1,G1,B1));
    GEN_TRIANG_ESCALENO(P0, LADO1, LADO2, LADO3, glm::vec3(R2,G2,B2));
    GEN_TRIANG_ISOCELES(P2, LADO, glm::vec3(R3,G3,B3));
    GEN_RECTANGULO(P3, ANCHO, ALTO, glm::vec3(R4,G4,B4));
    
    // normalizado de coordenadas
    coord_to_gl(0.1000f + 0.0099999); // 0.1111f es el espacio entre cada coordenada

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    shader_program = Utils::createShaderProgram("vertShader.glsl", "fragShader.glsl");
    glUseProgram(shader_program);
}

void display(double currentTime) {
    double slow = 5;
    double osc1 = abs(sin(currentTime/slow));
    double osc2 = abs(cos(currentTime/slow));
    double osc3 = abs(sin(-currentTime/slow));

    double c = 1.9;

	glClearColor(
        osc1*c, 
        osc2*c, 
        osc3*c, 
        0.0f);

	glClear(GL_COLOR_BUFFER_BIT);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT)*5, (void *) 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT)*5, (void *) 8);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    // envio de uniformes
    glUniform1f(glGetUniformLocation(shader_program, "u_time"), (float) currentTime);
    glUniform2f(glGetUniformLocation(shader_program, "u_resolution"), (float) width, (float) height);

	glDrawArrays(GL_TRIANGLES, 0, 15); 
	glDisableVertexAttribArray(0);
}


int main( void ){
	if (!glfwInit()) exit(EXIT_FAILURE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); 	// Resizable option.
	window = glfwCreateWindow(800, 800, "Ramos Paredes Roger Anthony", NULL, NULL);
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) exit(EXIT_FAILURE);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    glfwSwapInterval(1);
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

void coord_to_gl(float space){
    /* transforma coordenadas enteras a coordenadas
     * compatibles con OpenGL (normaliza)
     * */
    for(size_t i=0; i<vertices.size(); i+=5){
        vertices[i]*=space;
        vertices[i+1]*=space;
    }
}

void GEN_TRIANGULO_RECTO(glm::vec2 P, float CATETO1, float CATETO2, glm::vec3 color){
    /* genera vertices de TRIANGULO RECTANGULO - figura 1 */
    
    // 1er vertice
    PUSH_COORD(P);
    PUSH_COLOR(color);
    // 2do vertice
    P = P + glm::vec2(0,-1) * CATETO1; // (0,-1) -> vector director unitario
    PUSH_COORD(P);
    PUSH_COLOR(color);
    // 3er vertice
    P = P + glm::vec2(1,0) * CATETO2; // (1,0) -> vector director unitario
    PUSH_COORD(P);
    PUSH_COLOR(color);

}

void GEN_TRIANG_ESCALENO(glm::vec2 P, float LADO1, float LADO2, float LADO3, glm::vec3 color){
    /* genera vertices de TRIANGULO ESCALENO - figura 2 */

    float s = (LADO1 + LADO2 + LADO3)/2; // semiperimetro
    float altura = (2/LADO3) * sqrt(s*(s-LADO1)*(s-LADO2)*(s-LADO3)); 
    float n = (LADO1*LADO1 - (LADO2*LADO2 + LADO3*LADO3))/(-2*LADO3);

    // 1er vertice
    PUSH_COORD(P);
    PUSH_COLOR(color);
    // 2do vertice
    P = P + glm::vec2( 0,-1) * altura; // (0,-1) = vector director unitario
    P = P + glm::vec2( 1, 0) * n; // (1,0) = vector director unitario
    PUSH_COORD(P);
    PUSH_COLOR(color);
    // 3er vertice
    P = P + glm::vec2(-1, 0) * LADO3; // (-1,0) -> vector director unitario
    PUSH_COORD(P);
    PUSH_COLOR(color);

}

void GEN_TRIANG_ISOCELES(glm::vec2 P, float LADO , glm::vec3 color){
    /* genera vertices de TRIANGULO EQUILATERO - figura 3 */

    float altura = sqrt(3)*LADO/2;

    // 1er vertice
    PUSH_COORD(P);
    PUSH_COLOR(color);
    // 2do vertice
    P = P + glm::vec2(0,-1) * altura; // (0,-1) = vector director unitario (BAJAR)
    P = P + glm::vec2(1, 0) * 3.0f; // (1,0) = vector director unitario (IR A LA DERECHA)
    PUSH_COORD(P);
    PUSH_COLOR(color);
    // 3er vertice
    P = P + glm::vec2(-1,0) * 6.0f; // (-1,0) -> vector director unitario (IR A IZQUIERDA)
    PUSH_COORD(P);
    PUSH_COLOR(color);

}

void GEN_RECTANGULO(glm::vec2 P, float ANCHO, float ALTO, glm::vec3 color){
    /* 
       genera vertices de RECTANGULO - figura 4:
       La fig. 4 se compone de dos triangulos (6 vertices):
       ****          *      
       * *    y    * * 
       *          ****
    
    */

    // PRIMER TRIANGULO
    // 1er vertice
    PUSH_COORD(P);
    PUSH_COLOR(color);
    // 2do vertice
    glm::vec2 P_aux = P + glm::vec2(0,-1) * ALTO; // (0,-1) = vector director unitario (BAJAR)
    PUSH_COORD(P_aux);
    PUSH_COLOR(color);
    // 3er vertice
    P = P + glm::vec2(1,0) * ANCHO; // (1,0) -> vector director unitario (IR A DERECHA)
    PUSH_COORD(P);
    PUSH_COLOR(color);

    // SEGUNDO TRIANGULO
    // 1er vertice
    PUSH_COORD(P);
    PUSH_COLOR(color);
    // 2do vertice
    P = P + glm::vec2(0,-1) * ALTO; // (0,-1) = vector director unitario (BAJAR)
    PUSH_COORD(P);
    PUSH_COLOR(color);
    // 3er vertice
    P = P + glm::vec2(-1,0) * ANCHO; // (-1,0) -> vector director unitario (IR A IZQUIERDA)
    PUSH_COORD(P);
    PUSH_COLOR(color);
}

