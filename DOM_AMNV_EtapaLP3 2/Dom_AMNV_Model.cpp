//Dom_AMNV_Model
//21/09/2026
//Anderson Silva, Marcella Alarcon, Nathalia Pedraca Pinho e Vitor Piccoli
//Projeto Domino LP2026 (Grupo AMNV) - Etapa LP3

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Dom_AMNV_Model.h"

// Instanciação das variáveis globais
tipoPeca peca[28];
tipoPeca pecaaux;
int mesaSequencia[57];
int mesaInicio;
int mesaFim;
int mesaE, mesaD;
int qtmesa;
int jogatual;
int qtdJogadores;
int partidaEmAndamento;
tipoJogo sitJogo;

// Criação automática das 28 peças do dominó
void criarPecas() {
    int indice = 0; 
    for (int i = 0; i <= 6; i++) {
        for (int j = i; j <= 6; j++) {
            peca[indice].lado1 = i;
            peca[indice].lado2 = j;
            peca[indice].status = '\0'; 
            indice++; 
        }
    }
}

// Quantidade de pecas que o jogador ainda tem na mao
int contarPecasJogador(int jogador) {
    char alvo = (jogador == 1) ? '1' : '2';
    int total = 0;
    for (int i = 0; i < 28; i++)
        if (peca[i].status == alvo) total++;
    return total;
}

// Soma dos pontos das pecas que restaram na mao do jogador
int somarPontosJogador(int jogador) {
    char alvo = (jogador == 1) ? '1' : '2';
    int total = 0;
    for (int i = 0; i < 28; i++)
        if (peca[i].status == alvo) total += peca[i].lado1 + peca[i].lado2;
    return total;
}

// Indica se ainda ha pecas disponiveis para compra
int monteVazio() {
    for (int i = 0; i < 28; i++)
        if (peca[i].status == '\0') return 0;
    return 1;
}

// Verifica se a peca serve na extremidade indicada ('E' ou 'D')
int pecaEncaixaNoLado(int indice, char lado) {
    if (qtmesa == 0) return 1;

    if (lado == 'E')
        return (peca[indice].lado1 == mesaE || peca[indice].lado2 == mesaE);
    else
        return (peca[indice].lado1 == mesaD || peca[indice].lado2 == mesaD);
}

// Verifica se a peca serve em alguma das extremidades da mesa
int pecaEncaixa(int indice) {
    return pecaEncaixaNoLado(indice, 'E') || pecaEncaixaNoLado(indice, 'D');
}

// Verifica se o jogador possui alguma peca jogavel
int existeJogadaValida(int jogador) {
    char alvo = (jogador == 1) ? '1' : '2';
    for (int i = 0; i < 28; i++)
        if (peca[i].status == alvo && pecaEncaixa(i)) return 1;
    return 0;
}

// Encerra a partida por batida ou por travamento.
// Retorna 1 quando acabou e devolve o vencedor (0 = empate)
int verificarFimDeJogo(int *vencedor) {
    if (contarPecasJogador(1) == 0) { *vencedor = 1; return 1; }
    if (contarPecasJogador(2) == 0) { *vencedor = 2; return 1; }

    if (!existeJogadaValida(1) && !existeJogadaValida(2) && monteVazio()) {
        int qtd1 = contarPecasJogador(1);
        int qtd2 = contarPecasJogador(2);
        if (qtd1 < qtd2) { *vencedor = 1; return 1; }
        if (qtd2 < qtd1) { *vencedor = 2; return 1; }

        int pts1 = somarPontosJogador(1);
        int pts2 = somarPontosJogador(2);
        if (pts1 < pts2)      *vencedor = 1;
        else if (pts2 < pts1) *vencedor = 2;
        else                  *vencedor = 0;
        return 1;
    }
    return 0;
}
