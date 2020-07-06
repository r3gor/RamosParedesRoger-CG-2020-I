# T03-Puntos

## Descripción
### Coordenadas
1. Primero representamos las coordenadas deseadas en un sistema de coordenadas sencillo de simbolizar (sin tantos decimales), para ello en lugar de usar el sistema de OpenGL (___-1<X,Y<1___) usamos uno extendido (___-6<X,Y<6___):

    ```C++
    GLfloat puntos[] = {
        -5,3,  -5,1,  -3,1, // Puntos en NorEste
        0,0, // Punto en Centro
        3,1,   3,3,   4,2,  5,1,  5,3, // Puntos en NorOeste
        -4,-2, // Punto en SurEste
        3.5,-2.5,  4,-2,  4.5,-1.5 // Puntos en SurOeste
    };
    ```
  
2. Luego la función coord_to_gl transforma las coordenadas anteriores a coordenadas compatibles con OpenGL (___-1<X,Y<1___), para ello la función multiplica cada valor por 1/6 = 1.16666 que es la proporción entre ambos sistemas de coordenadas.

### Color de fondo
 Para que el color de fondo varie se hace uso de la variable currentTime a la cual se le aplica una función periodica como el seno y coseno para que los colores siempre se encuentren cambiantes.

### Resultado
![GitHub Logo](https://github.com/r3gor/RamosParedesRoger-CG-2020-I/blob/master/Tareas/T03-Puntos/T03-App-Puntos.jpg)
