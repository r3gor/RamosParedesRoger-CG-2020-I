# Bezier Teapot
Modificaciones:
1. Las rutas de los shader eran erroneas:

    ```program = Utils::createShaderProgram("src/teapot.v.glsl", "src/teapot.f.glsl");```
 
    se reemplazó por:
  
    ```program = Utils::createShaderProgram("teapot.v.glsl", "teapot.f.glsl");```
2. La aplicación usa el perfil GLFW_OPENGL_CORE_PROFILE, por lo que es obligatorio la creación explícita del VAO, lo cual no sucede, para corregir esto:
    
    ```GLuint vao; // creamos la variable global para el vao ```
    
    y antes de generar los buffer generamos el VAO y lo activamos con bind:
    
    ```int init_resources()
      {
        build_teapot();
        glGenVertexArrays(1,&vao); // genera VAO
        glBindVertexArray(vao); // activa VAO
        glGenBuffers(1, &vbo_teapot_vertices);
        ...
        ...```
    
