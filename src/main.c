#include <stdio.h>
#include <stdlib.h>
#include <string.h>       // Para strcmp

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cglm/cglm.h>    // Matriz e vetor

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void checkCompileErrors(unsigned int shader, const char* type) {
    int success;
    char infoLog[1024];
    if (strcmp(type, "PROGRAM") != 0) {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            fprintf(stderr, "ERRO SHADER COMPILACAO (%s): %s\n", type, infoLog);
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            fprintf(stderr, "ERRO LINKAGEM PROGRAMA (%s): %s\n", type, infoLog);
        }
    }
}

int main() {
    // Inicializa GLFW
    if (!glfwInit()) {
        fprintf(stderr, "Falha ao inicializar GLFW\n");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Piramide 3D com Luz Direcional", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Falha ao criar janela GLFW\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Falha ao inicializar GLAD\n");
        return -1;
    }
    glViewport(0, 0, 800, 600);

    // Vertices da pirâmide: posição (x,y,z) + normal (nx, ny, nz)
    // Normais calculadas manualmente para cada face
    float vertices[] = {
        // Base (2 triângulos) - Normais para baixo (0,-1,0)
        -0.5f, 0.0f, -0.5f,    0.0f, -1.0f, 0.0f,
         0.5f, 0.0f, -0.5f,    0.0f, -1.0f, 0.0f,
         0.5f, 0.0f,  0.5f,    0.0f, -1.0f, 0.0f,

        -0.5f, 0.0f, -0.5f,    0.0f, -1.0f, 0.0f,
         0.5f, 0.0f,  0.5f,    0.0f, -1.0f, 0.0f,
        -0.5f, 0.0f,  0.5f,    0.0f, -1.0f, 0.0f,

        // Face 1 (frontal)
        -0.5f, 0.0f,  0.5f,    0.0f, 0.707f, 0.707f,
         0.5f, 0.0f,  0.5f,    0.0f, 0.707f, 0.707f,
         0.0f, 0.8f,  0.0f,    0.0f, 0.707f, 0.707f,

        // Face 2 (direita)
         0.5f, 0.0f,  0.5f,    0.707f, 0.707f, 0.0f,
         0.5f, 0.0f, -0.5f,    0.707f, 0.707f, 0.0f,
         0.0f, 0.8f,  0.0f,    0.707f, 0.707f, 0.0f,

        // Face 3 (traseira)
         0.5f, 0.0f, -0.5f,    0.0f, 0.707f, -0.707f,
        -0.5f, 0.0f, -0.5f,    0.0f, 0.707f, -0.707f,
         0.0f, 0.8f,  0.0f,    0.0f, 0.707f, -0.707f,

        // Face 4 (esquerda)
        -0.5f, 0.0f, -0.5f,   -0.707f, 0.707f, 0.0f,
        -0.5f, 0.0f,  0.5f,   -0.707f, 0.707f, 0.0f,
         0.0f, 0.8f,  0.0f,   -0.707f, 0.707f, 0.0f,
    };

    const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec3 aNormal;\n"
        "out vec3 FragPos;\n"
        "out vec3 Normal;\n"
        "uniform mat4 model;\n"
        "uniform mat4 view;\n"
        "uniform mat4 projection;\n"
        "void main()\n"
        "{\n"
        "   FragPos = vec3(model * vec4(aPos, 1.0));\n"
        "   Normal = mat3(transpose(inverse(model))) * aNormal;\n"
        "   gl_Position = projection * view * vec4(FragPos, 1.0);\n"
        "}\0";

    const char* fragmentShaderSource = "#version 330 core\n"
        "in vec3 FragPos;\n"
        "in vec3 Normal;\n"
        "out vec4 FragColor;\n"
        "uniform vec3 lightDir;\n"
        "uniform vec3 lightColor;\n"
        "uniform vec3 objectColor;\n"
        "void main()\n"
        "{\n"
        "   vec3 norm = normalize(Normal);\n"
        "   float diff = max(dot(norm, -lightDir), 0.0);\n"
        "   vec3 result = diff * lightColor * objectColor;\n"
        "   FragColor = vec4(result, 1.0);\n"
        "}\0";

    // Compilação dos shaders
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    checkCompileErrors(vertexShader, "VERTEX");

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    checkCompileErrors(fragmentShader, "FRAGMENT");

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    checkCompileErrors(shaderProgram, "PROGRAM");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // VBO e VAO
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // posição (location 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal (location 1)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Luz e cor
    vec3 lightDir = { -0.2f, -1.0f, -0.3f };
    glm_vec3_normalize(lightDir);

    vec3 lightColor = { 1.0f, 1.0f, 1.0f };
    vec3 objectColor = { 1.0f, 0.5f, 0.31f };

    // Matrizes
    mat4 model;
    glm_mat4_identity(model);

    mat4 projection;
    glm_perspective(glm_rad(45.0f), 800.0f/600.0f, 0.1f, 100.0f, projection);

    float angle = 0.0f;

    glEnable(GL_DEPTH_TEST);

    // Loop
    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0.1f,0.1f,0.1f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Calcula posição da câmera girando ao redor da pirâmide
        float radius = 3.0f;
        float camX = sinf(angle) * radius;
        float camZ = cosf(angle) * radius;

        vec3 camPos = { camX, 1.5f, camZ };  // Câmera um pouco acima para melhor visão
        vec3 target = { 0.0f, 0.3f, 0.0f };  // Olhando levemente acima da base
        vec3 up = { 0.0f, 1.0f, 0.0f };

        mat4 view;
        glm_lookat(camPos, target, up, view);

        glUseProgram(shaderProgram);

        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, (float*)model);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, (float*)view);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, (float*)projection);

        glUniform3fv(glGetUniformLocation(shaderProgram, "lightDir"), 1, lightDir);
        glUniform3fv(glGetUniformLocation(shaderProgram, "lightColor"), 1, lightColor);
        glUniform3fv(glGetUniformLocation(shaderProgram, "objectColor"), 1, objectColor);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 18);  // 6 (base) + 4*3 (faces laterais)

        glfwSwapBuffers(window);

        angle += 0.01f;
        if(angle > 2.0f * M_PI)
            angle -= 2.0f * M_PI;
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
