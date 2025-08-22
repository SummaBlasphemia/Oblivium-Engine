#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 FragPos;    // Posição do fragmento no espaço do mundo
out vec3 Normal;     // Normal do vértice para interpolação no fragment shader

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0)); // posição no espaço do mundo
    Normal = mat3(transpose(inverse(model))) * aNormal; // normal transformada

    gl_Position = projection * view * vec4(FragPos, 1.0);
}
