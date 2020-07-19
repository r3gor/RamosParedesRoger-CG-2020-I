#version 410 core

out vec4 color_out;
smooth in vec4 the_color;

uniform float u_time;
uniform vec2 u_resolution;

void main() {
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    // st = st * (1-st); // DOBLE LINEA

    // linea
    float grosor = 0.1 * sin(u_time);

    // float s = smoothstep(abs(sin(u_time)) - grosor,abs(sin(u_time)),st.y) -  // para (EJE X)
    //         smoothstep(abs(sin(u_time)), abs(sin(u_time)) + grosor,st.y);

    float s = smoothstep(abs(sin(u_time)) - grosor,abs(sin(u_time)),st.x) -  // para (EJE Y)
              smoothstep(abs(sin(u_time)), abs(sin(u_time)) + grosor,st.x);

    // color linea
    float slow = 5;
    float c1 = abs(sin(u_time/slow))*1.9;
    float c2 = abs(cos(u_time/slow))*1.9;
    float c3 = abs(sin(-u_time/slow))*1.9;
    
    // linea + color
    vec3 color = (1.0-s) * the_color.xyz + s * vec3(c1,c2,c3);

    color_out = vec4(color,1.0);
}