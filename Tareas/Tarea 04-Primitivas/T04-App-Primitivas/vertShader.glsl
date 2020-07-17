#version 410 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

uniform float u_time;
uniform vec2 u_resolution;

out vec4 the_color;

void main(void) {
    gl_Position =  vec4(position, 1.0);
    the_color = vec4(color, 1.0);
}
