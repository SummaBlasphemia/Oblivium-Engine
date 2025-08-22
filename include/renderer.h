#ifndef RENDERER_H      // Proteção contra múltipla inclusão
#define RENDERER_H

#include <stdbool.h>   // Para usar o tipo bool com true/false

// Inicializa o sistema de renderização
// Retorna true se a inicialização for bem-sucedida, false caso contrário
bool renderer_init(void);

// Desenha o frame atual (renderiza a cena)
void renderer_draw(void);

// Encerra o sistema de renderização, liberando recursos
void renderer_shutdown(void);

#endif // RENDERER_H
