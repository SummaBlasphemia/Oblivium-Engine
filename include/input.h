#ifndef INPUT_H        // Proteção contra múltiplas inclusões
#define INPUT_H

// Processa eventos de entrada do usuário (teclado, mouse, etc)
void input_poll_events(void);

// Retorna 1 se a tecla estiver pressionada
int input_key_pressed(int key);

// Retorna 1 se o botão do mouse estiver pressionado
int input_mouse_button(int button);

// Retorna a posição atual do cursor na janela
void input_get_cursor_pos(double* x, double* y);

#endif // INPUT_H
