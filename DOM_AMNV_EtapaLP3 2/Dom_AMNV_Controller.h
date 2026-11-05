//Dom_AMNV_Controller.h
//21/09/2026
//Anderson Silva, Marcella Alarcon, Nathalia Pedraca Pinho e Vitor Piccoli
//Projeto Domino LP2026 (Grupo AMNV) - Etapa LP3

#ifndef DOM_AMNV_CONTROLLER_H
#define DOM_AMNV_CONTROLLER_H

void embaralharPecas();
void prepararJogo();
int primeiroLance();
int comprarPeca(int jogador);
int encontrarIndicePecaPorLetra(int jogador, char letra);
int validarEfetuarJogada(int jogador, char letraPeca, char ladoMesa);
int jogadaAutomatica(int jogador);
void turnoComputador(int jogador);
void jogarPartida();
void iniciarPartida(int jogadores);
void retomarPartida();
void mostrarTodasAsPecas();
int gravarJogo();
int recuperarJogo();
void iniciarJogo();

#endif
