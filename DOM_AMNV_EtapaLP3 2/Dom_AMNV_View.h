//Dom_AMNV_View.h
//21/09/2026
//Anderson Silva, Marcella Alarcon, Nathalia Pedraca Pinho e Vitor Piccoli
//Projeto Domino LP2026 (Grupo AMNV) - Etapa LP3

#ifndef DOM_AMNV_VIEW_H
#define DOM_AMNV_VIEW_H

void limpaTela();
void fclear();
void apresentaMesa();
void mostrarPecasJogador(int jogador);
void exibirRegras();
int menuPrincipal();
char menuJogada(int extremidadeE, int extremidadeD); // Novo sub-menu interativo
void apresentarResultado(int vencedor);
void mostrarMensagem(const char* msg);
void pausar();
void apresentarTodasAsPecas(const char* titulo);
void apresentarPecaComprada(int indice);
void apresentarJogadaComputador(int indice, int compras);
char pedirLetraDaPeca();
char pedirLadoDaMesa();

#endif
