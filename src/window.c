#include <glad/glad.h>         // OpenGL moderno
#include <GLFW/glfw3.h>        // GLFW para janela e input

#include "../include/window.h"

static GLFWwindow* window = NULL;

bool window_init(int width, int height, const char* title) {
    if (!glfwInit())
        return false;

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) {
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);  // Necessário para usar OpenGL (e carregar com GLAD)

    return true;
}

void window_swap_buffers() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

bool window_should_close() {
    return glfwWindowShouldClose(window);
}

void window_shutdown() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

// ⚠️ Permite que outros arquivos acessem o ponteiro da janela
GLFWwindow* window_get(void) {
    return window;
}
