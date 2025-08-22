#include "../include/input.h"
#include <GLFW/glfw3.h>
#include "../include/window.h"  // Para acessar o ponteiro da janela, se necessário

void input_update() {
 int input_is_key_down(int key);
 int input_was_key_pressed(int key);
 int input_is_mouse_button_down(int button);
 float input_get_mouse_x();
 float input_get_mouse_y();

}
void input_poll_events(void) {
    glfwPollEvents();  // Atualiza os eventos do GLFW

    // Exemplo: fecha a janela se apertar ESC
    if (glfwGetKey(window_get(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window_get(), GLFW_TRUE);
    }

    // Aqui você pode adicionar checagens para outras teclas
    // Exemplo: mover personagem, iniciar ações, etc.
}
