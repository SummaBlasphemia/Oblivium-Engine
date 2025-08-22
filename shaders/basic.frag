#version 330 core

in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform vec3 lightDir;   // direção da luz (normalizada)
uniform vec3 lightColor; // cor da luz
uniform vec3 objectColor; // cor do objeto

void main()
{
    // Normaliza a normal
    vec3 norm = normalize(Normal);

    // Calcula a intensidade da luz (difusa)
    float diff = max(dot(norm, -lightDir), 0.0);

    // Calcula a cor final
    vec3 result = diff * lightColor * objectColor;

    FragColor = vec4(result, 1.0);
}
