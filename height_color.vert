varying vec4 pos;
varying vec3 color;
void main()
{
    vec4 vert_pos = gl_Vertex;
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    pos = gl_Position;

    float scaling = 255 * 3;

    if (vert_pos.y < scaling * 0.55) {   //deep sea
        color = vec3(0.0, 0.0, 0.5);
    }
    else if (vert_pos.y < scaling * 0.57) {
        color = vec3(0.0, 0.0, 0.88);
    }
    else if (vert_pos.y < scaling * 0.59) {
        color = vec3(0.94, 1.0, 0.55);
    }
    else if (vert_pos.y < scaling * 0.8) {
        color = vec3(0.0, 0.67, 0.0);
    }
    else if (vert_pos.y < scaling * 0.9) {
        color = vec3(0.0, 0.56, 0.0);
    }
    else if (vert_pos.y < scaling * 0.9999) {
        color = vec3(0.55, 0.55, 0.55);
    }
    else {
        color = vec3(1.0, 1.0, 1.0);
    }

    // = vec4(color, 1.0);
}
