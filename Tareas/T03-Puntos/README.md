# T03-Puntos

### Descripción
1. Primero representamos las coordenadas deseadas en un sistema de coordenadas sencillo de simbolizar (sin tantos decimales), para ello en lugar de usar el sistema de OpenGL (-1<X,Y<1) usamos uno extendido: -6<X,Y<6:

    ```C++
    GLfloat puntos[] = {
        -5,3,  -5,1,  -3,1, // Puntos en NorEste
        0,0, // Punto en Centro
        3,1,   3,3,   4,2,  5,1,  5,3, // Puntos en NorOeste
        -4,-2, // Punto en SurEste
        3.5,-2.5,  4,-2,  4.5,-1.5 // Puntos en SurOeste
    };
    ```
  
2. Luego la función coord_to_gl transforma las coordenadas anteriores a coordenadas compatibles con OpenGL (-1<X,Y<1), para ello la función multiplica cada valor por 1/6 = 1.16666.