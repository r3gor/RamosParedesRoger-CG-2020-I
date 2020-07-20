# T06-Transformaciones: "Sharingan"

## Funciones generadoras de curvas
1. all_points_curve: genera todos los puntos de una curva (circular).
2. next_point_curve: genera solo un punto de determinada curva circular.
3. gen_vertices_gotita: genera los vertices de la forma de 'gota' que aparece 3 veces en el sharingan (usa la función n°2).
4. gen_vertices_ojo: genera los vertices de los 3 circulos del ojo (usa la función n°1).

## Movimientos
1. Antihorario de toda la figura.
2. Animacion de alejamiento/acercamiento del iris y las 3 formas de gota del sharingan.

## Fragment Shader
1. Doble 'haz de brillo' que recorre desde el centro hacia las esquinas del sharingan.
2. Inversión de color del sharingan (rojo/negro).
3. Gradiente de oscuridad a los bordes del sharingan.

## Fuentes
1. Para el gradiente de oscuridad (Fragment Shader, punto 3): 
    https://stackoverflow.com/questions/47285778/how-to-create-a-mutli-step-radial-gradient-fragment-shader
