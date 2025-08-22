#include "../include/engine.h"    // Cabeçalho principal da engine
#include <glad/glad.h>            // Para chamadas OpenGL modernas
#include <GLFW/glfw3.h>           // GLFW para janela e contexto OpenGL

// Inicializa o sistema de renderização
bool renderer_init() {
    // Configura a cor de fundo (RGBA)
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    return true;
}

// Função que desenha o frame atual
void renderer_draw() {
    // Limpa o framebuffer com a cor definida em glClearColor
    glClear(GL_COLOR_BUFFER_BIT);

    // Aqui você pode desenhar triângulos, modelos, etc com OpenGL
}

// Encerra o sistema de renderização e libera recursos
void renderer_shutdown() {
    // Ainda sem recursos alocados, então não precisa liberar nada
}
