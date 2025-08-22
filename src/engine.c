#include <../include/glad/glad.h>
#include <GLFW/glfw3.h>         // GLFW continua para janela e input
#include <stdio.h>
#include "../include/engine.h"
#include "../include/window.h"
#include "../include/renderer.h"
#include "../include/input.h"

// Inicializa a engine: cria janela e inicializa o renderer
bool engine_init(void) {
    if (!window_init(800, 600, "Minha Engine 3D")) return false;

    // ⚠️ Importante: carregar as funções modernas do OpenGL com GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Erro ao carregar funções OpenGL com GLAD\n");
        return false;
    }

    if (!renderer_init()) return false;

    return true;
}

// Trata o input do usuário
void engine_handle_input(void) {
    input_poll_events();
}

// Atualiza lógica da engine (por enquanto vazio)
void engine_update(void) {
    // Lógica geral aqui
}

// Desenha na tela
void engine_render(void) {
    renderer_draw();
    window_swap_buffers();
}

// Verifica se a engine ainda deve rodar
bool engine_should_run(void) {
    return !window_should_close();
}

// Encerra e limpa tudo
void engine_shutdown(void) {
    renderer_shutdown();
    window_shutdown();
}
