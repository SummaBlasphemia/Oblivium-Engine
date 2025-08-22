#ifndef ENGINE_H       // Evita múltiplas inclusões
#define ENGINE_H

#include <glad/glad.h>   // Deve vir antes do GLFW para carregar funções OpenGL modernas
#include <GLFW/glfw3.h>  // Gerenciamento de janela e input com GLFW
#include <stdbool.h>     // Suporte a tipo bool no C

// Inicializa a engine (janela, renderizador, etc)
bool engine_init(void);

// Processa o input do usuário (teclado, mouse, etc)
void engine_handle_input(void);

// Atualiza a lógica interna da engine/jogo
void engine_update(void);

// Renderiza a cena atual
void engine_render(void);

// Retorna true enquanto a engine deve continuar rodando (janela aberta)
bool engine_should_run(void);

// Encerra a engine, libera recursos
void engine_shutdown(void);

#endif // ENGINE_H
