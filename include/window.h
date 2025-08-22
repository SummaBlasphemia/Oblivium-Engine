#ifndef WINDOW_H         // Proteção contra múltipla inclusão do arquivo
#define WINDOW_H

#include <stdbool.h>    // Para usar o tipo bool com true/false
#include <GLFW/glfw3.h> // Para o tipo GLFWwindow

// Inicializa a janela com as dimensões e título fornecidos.
// Retorna true se a janela foi criada com sucesso, false caso contrário.
bool window_init(int width, int height, const char* title);

// Troca os buffers da janela (mostra o que foi desenhado)
void window_swap_buffers(void);

// Verifica se a janela deve ser fechada (ex: usuário clicou no X)
bool window_should_close(void);

// Encerra a janela e limpa recursos usados pela GLFW
void window_shutdown(void);

// Retorna o ponteiro da janela GLFW (útil para funções de input, contexto OpenGL, etc)
GLFWwindow* window_get(void);

#endif // WINDOW_H
