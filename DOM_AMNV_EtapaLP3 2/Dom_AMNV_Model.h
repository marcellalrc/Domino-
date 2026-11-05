//Dom_AMNV_Model.h
//21/09/2026
//Anderson Silva, Marcella Alarcon, Nathalia Pedraca Pinho e Vitor Piccoli
//Projeto Domino LP2026 (Grupo AMNV) - Etapa LP3

#ifndef DOM_AMNV_MODEL_H
#define DOM_AMNV_MODEL_H

#include <time.h>

typedef struct stpeca {
    int lado1;
    int lado2;
    char status; // '1' = Jogador 1, '2' = Jogador 2, 'M' = Mesa, '\0' = Disponivel
} tipoPeca;

// Variaveis globais declaradas como extern
extern tipoPeca peca[28];
extern tipoPeca pecaaux;

// Sequencia visual da mesa: guarda o INDICE (em peca[]) de cada posicao.
// O array tem folga pros dois lados (28 posicoes livres de cada lado do
// meio) para a mesa poder crescer tanto pela esquerda quanto pela direita
// sem precisar deslocar nada - so anda o ponteiro do lado que foi jogado.
#define MESA_MEIO 28
extern int mesaSequencia[57];
extern int mesaInicio; // posicao (em mesaSequencia) da peca mais a esquerda
extern int mesaFim;    // posicao (em mesaSequencia) da peca mais a direita

extern int mesaE, mesaD;
extern int qtmesa;
extern int jogatual;
extern int qtdJogadores;
extern int partidaEmAndamento;

// Situacao da partida, agrupada para ser gravada de uma vez
typedef struct stjogo {
    int qtmesaJogo;         // quantas pecas na mesa
    int jogadorJogo;        // de quem e a vez
    int qtdJogadoresJogo;   // 2 = dois humanos, 1 = contra a maquina
    int mesaEJogo;          // extremidade esquerda
    int mesaDJogo;          // extremidade direita
    int mesaInicioJogo;     // marcador de inicio em mesaSequencia
    int mesaFimJogo;        // marcador de fim em mesaSequencia
} tipoJogo;

extern tipoJogo sitJogo;

// Adicionar este prototipo para o Controller enxergar a funcao
void criarPecas();

// Fim de jogo
int contarPecasJogador(int jogador);
int somarPontosJogador(int jogador);
int monteVazio();
int pecaEncaixa(int indice);
int pecaEncaixaNoLado(int indice, char lado);
int existeJogadaValida(int jogador);
int verificarFimDeJogo(int *vencedor);

#endif
