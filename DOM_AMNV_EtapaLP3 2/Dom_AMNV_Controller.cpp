//Dom_AMNV_Controller
//21/09/2026
//Anderson Silva, Marcella Alarcon, Nathalia Pedraca Pinho e Vitor Piccoli
//Projeto Domino LP2026 (Grupo AMNV) - Etapa LP3

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Dom_AMNV_Model.h"
#include "Dom_AMNV_Controller.h"
#include "Dom_AMNV_View.cpp"

void embaralharPecas() {
    for (int i = 0; i < 28; i++) {
        int sorteado = rand() % 28; 
        pecaaux = peca[i];
        peca[i] = peca[sorteado];
        peca[sorteado] = pecaaux;
    }
}

void prepararJogo() {
    criarPecas();
    embaralharPecas();
    
    for(int i = 0; i < 28; i++) {
        peca[i].status = '\0';
    }
    
    // Distribui 7 peças para o Jogador 1 (índices 0 a 6) e 7 para o Jogador 2 (índices 7 a 13)
    for(int i = 0; i < 14; i++) {
        if(i < 7) {
            peca[i].status = '1';
        } else {
            peca[i].status = '2';
        }
    }
    qtmesa = 0;
}

int primeiroLance() {
    int maiorBucha = -1, idxBucha = -1;
    int maiorSoma = -1, idxSoma = -1;
    
    // Analisa apenas as 14 peças distribuídas aos jogadores (0 a 13)
    for(int i = 0; i < 14; i++) {
        if(peca[i].lado1 == peca[i].lado2) {
            if(peca[i].lado1 > maiorBucha) {
                maiorBucha = peca[i].lado1;
                idxBucha = i;
            }
        } else {
            int soma = peca[i].lado1 + peca[i].lado2;
            if(soma > maiorSoma) {
                maiorSoma = soma;
                idxSoma = i;
            }
        }
    }
    
    int escolhida = (idxBucha != -1) ? idxBucha : idxSoma;

    mesaInicio = MESA_MEIO;
    mesaFim = MESA_MEIO;
    mesaSequencia[MESA_MEIO] = escolhida;
    peca[escolhida].status = 'M'; // Marcada como Mesa
    qtmesa = 1;

    mesaE = peca[escolhida].lado1;
    mesaD = peca[escolhida].lado2;
    
    // Retorna qual jogador tem a peça escolhida (1 se < 7, senão 2)
    return (escolhida < 7) ? 1 : 2;
}

int comprarPeca(int jogador) {
    // Procura no monte (peças com status '\0' a partir do índice 14)
    for(int i = 14; i < 28; i++) {
        if(peca[i].status == '\0') {
            peca[i].status = (jogador == 1) ? '1' : '2';
            return i;
        }
    }
    return -1;
}

// Converte a letra escolhida pelo usuário (a, b, c...) para o índice real da peça do jogador
int encontrarIndicePecaPorLetra(int jogador, char letra) {
    char statusBusca = (jogador == 1) ? '1' : '2';
    int contador = 0;
    int letraAlvo = letra - 'a'; // 'a' vira 0, 'b' vira 1, etc.
    
    for(int i = 0; i < 28; i++) {
        if(peca[i].status == statusBusca) {
            if(contador == letraAlvo) {
                return i;
            }
            contador++;
        }
    }
    return -1;
}

int validarEfetuarJogada(int jogador, char letraPeca, char ladoMesa) {
    int idx = encontrarIndicePecaPorLetra(jogador, letraPeca);
    if(idx == -1) return 0; // Peça não encontrada
    
    int l1 = peca[idx].lado1;
    int l2 = peca[idx].lado2;
    
    if(ladoMesa == 'E' || ladoMesa == 'e') {
        // Tenta encaixar na esquerda: o lado que bate fica "para dentro"
        // (encostando na peca vizinha), o outro fica exposto
        if(l2 == mesaE) {
            // ja esta na orientacao certa: [exposto|tocando]
        }
        else if(l1 == mesaE) {
            peca[idx].lado1 = l2;
            peca[idx].lado2 = l1;
        }
        else {
            return 0;
        }
        mesaE = peca[idx].lado1; // nova extremidade exposta
        mesaInicio--;            // so anda o ponteiro, sem deslocar nada
        mesaSequencia[mesaInicio] = idx;
        peca[idx].status = 'M';
        qtmesa++;
        return 1;
    }
    else if(ladoMesa == 'D' || ladoMesa == 'd') {
        // Tenta encaixar na direita
        if(l1 == mesaD) {
            // ja esta na orientacao certa: [tocando|exposto]
        }
        else if(l2 == mesaD) {
            peca[idx].lado1 = l2;
            peca[idx].lado2 = l1;
        }
        else {
            return 0;
        }
        mesaD = peca[idx].lado2; // nova extremidade exposta
        mesaFim++;
        mesaSequencia[mesaFim] = idx;
        peca[idx].status = 'M';
        qtmesa++;
        return 1;
    }
    
    return 0; // Jogada inválida (não bate com a extremidade)
}

// Percorre as pecas do jogador (usado pela maquina) tentando encaixar
// em qualquer extremidade. Retorna 1 se conseguiu jogar, 0 caso contrario.
int jogadaAutomatica(int jogador) {
    char letra = 'a';
    int idx;
    
    while ((idx = encontrarIndicePecaPorLetra(jogador, letra)) != -1) {
        if (validarEfetuarJogada(jogador, letra, 'E')) {
            return idx;
        }
        if (validarEfetuarJogada(jogador, letra, 'D')) {
            return idx;
        }
        letra++;
    }

    return -1; // Nenhuma peca da mao encaixou
}

// Turno automatico da maquina
void turnoComputador(int jogador) {
    int jogada = jogadaAutomatica(jogador);
    int comprado, compras = 0;

    if (jogada != -1) {
        apresentarJogadaComputador(jogada, 0);
        return;
    }

    do {
        comprado = comprarPeca(jogador);
        if (comprado != -1) {
            compras++;
            jogada = jogadaAutomatica(jogador);
            if (jogada != -1) {
                apresentarJogadaComputador(jogada, compras);
                return;
            }
        }
    } while (comprado != -1);

    mostrarMensagem("A maquina nao tem jogada possivel e o monte esta vazio. Passou a vez.");
}

// Conduz a partida em andamento ate o fim ou ate o jogador interromper
void jogarPartida() {
    int jogoRodando = 1;
    int vencedor = 0;
    char opcao, letra, lado;
    int indice, cabeE, cabeD;

    while (jogoRodando) {
        if (verificarFimDeJogo(&vencedor)) {
            limpaTela();
            apresentaMesa();
            apresentarResultado(vencedor);
            partidaEmAndamento = 0;
            jogoRodando = 0;
            continue;
        }

        limpaTela();
        apresentaMesa();

        if (qtdJogadores == 1 && jogatual == 2) {
            turnoComputador(2);
            jogatual = 1;
            pausar();
            continue;
        }

        mostrarPecasJogador(jogatual);
        opcao = menuJogada(mesaE, mesaD);

        if (opcao == 'S' || opcao == 's') {
            mostrarMensagem("Jogo interrompido. Use a opcao 3 do menu para retomar.");
            jogoRodando = 0;
            pausar();
        }
        else if (opcao == 'J' || opcao == 'j') {
            letra = pedirLetraDaPeca();
            indice = encontrarIndicePecaPorLetra(jogatual, letra);

            if (indice == -1) {
                mostrarMensagem("Voce nao tem essa peca.");
            }
            else {
                cabeE = pecaEncaixaNoLado(indice, 'E');
                cabeD = pecaEncaixaNoLado(indice, 'D');

                if (!cabeE && !cabeD) {
                    mostrarMensagem("Essa peca nao encaixa em nenhuma das pontas da mesa.");
                }
                else {
                    // So pergunta o lado quando a peca cabe nos dois
                    if (cabeE && cabeD)
                        lado = pedirLadoDaMesa();
                    else if (cabeE)
                        lado = 'E';
                    else
                        lado = 'D';

                    validarEfetuarJogada(jogatual, letra, lado);
                    mostrarMensagem("Jogada realizada com sucesso!");
                    jogatual = (jogatual == 1) ? 2 : 1;
                }
            }
            pausar();
        }
        else if (opcao == 'C' || opcao == 'c') {
            indice = comprarPeca(jogatual);

            if (indice != -1)
                apresentarPecaComprada(indice);
            else
                mostrarMensagem("O monte esta vazio.");
            pausar();
        }
        else if (opcao == 'P' || opcao == 'p') {
            if (existeJogadaValida(jogatual))
                mostrarMensagem("Voce tem jogada valida - nao pode passar.");
            else if (!monteVazio())
                mostrarMensagem("Ainda ha pecas no monte - compre antes de passar.");
            else {
                mostrarMensagem("Turno passado.");
                jogatual = (jogatual == 1) ? 2 : 1;
            }
            pausar();
        }
        else {
            mostrarMensagem("Opcao invalida.");
            pausar();
        }
    }
}

// Prepara e inicia uma nova partida (2 = dois jogadores, 1 = contra a maquina)
void iniciarPartida(int jogadores) {
    qtdJogadores = jogadores;
    prepararJogo();
    int quemComecou = primeiroLance();
    jogatual = (quemComecou == 1) ? 2 : 1;
    partidaEmAndamento = 1;
    jogarPartida();
}

// Retoma a partida interrompida pela opcao S
void retomarPartida() {
    if (!partidaEmAndamento) {
        mostrarMensagem("Nao ha partida interrompida para retomar.");
        pausar();
        return;
    }
    jogarPartida();
}

// Exibe as 28 pecas em ordem e depois embaralhadas
void mostrarTodasAsPecas() {
    if (partidaEmAndamento) {
        mostrarMensagem("Encerre a partida em andamento antes de reembaralhar as pecas.");
        pausar();
        return;
    }

    limpaTela();
    criarPecas();
    apresentarTodasAsPecas("Pecas em ordem");
    embaralharPecas();
    apresentarTodasAsPecas("Pecas embaralhadas");
    pausar();
}

// Grava a situacao da partida em tres arquivos
int gravarJogo() {
    FILE *fp, *fpm, *fps;

    fp  = fopen("CAD_DOMINO", "wb");
    fpm = fopen("CAD_MESA",   "wb");
    fps = fopen("CAD_JOGO",   "wb");

    if (fp == NULL || fpm == NULL || fps == NULL) {
        if (fp  != NULL) fclose(fp);
        if (fpm != NULL) fclose(fpm);
        if (fps != NULL) fclose(fps);
        return 0;
    }

    fwrite(peca, sizeof(tipoPeca), 28, fp);
    fwrite(mesaSequencia, sizeof(int), 57, fpm);

    sitJogo.qtmesaJogo       = qtmesa;
    sitJogo.jogadorJogo      = jogatual;
    sitJogo.qtdJogadoresJogo = qtdJogadores;
    sitJogo.mesaEJogo        = mesaE;
    sitJogo.mesaDJogo        = mesaD;
    sitJogo.mesaInicioJogo   = mesaInicio;
    sitJogo.mesaFimJogo      = mesaFim;
    fwrite(&sitJogo, sizeof(tipoJogo), 1, fps);

    fclose(fp);
    fclose(fpm);
    fclose(fps);
    return 1;
}

// Le os tres arquivos e recoloca tudo nas variaveis do jogo
int recuperarJogo() {
    FILE *fp, *fpm, *fps;

    fp  = fopen("CAD_DOMINO", "rb");
    fpm = fopen("CAD_MESA",   "rb");
    fps = fopen("CAD_JOGO",   "rb");

    if (fp == NULL || fpm == NULL || fps == NULL) {
        if (fp  != NULL) fclose(fp);
        if (fpm != NULL) fclose(fpm);
        if (fps != NULL) fclose(fps);
        return 0;
    }

    fread(peca, sizeof(tipoPeca), 28, fp);
    fread(mesaSequencia, sizeof(int), 57, fpm);
    fread(&sitJogo, sizeof(tipoJogo), 1, fps);

    qtmesa       = sitJogo.qtmesaJogo;
    jogatual     = sitJogo.jogadorJogo;
    qtdJogadores = sitJogo.qtdJogadoresJogo;
    mesaE        = sitJogo.mesaEJogo;
    mesaD        = sitJogo.mesaDJogo;
    mesaInicio   = sitJogo.mesaInicioJogo;
    mesaFim      = sitJogo.mesaFimJogo;

    partidaEmAndamento = 1;

    fclose(fp);
    fclose(fpm);
    fclose(fps);
    return 1;
}

void iniciarJogo() {
    int opcao;
    do {
        opcao = menuPrincipal();
        switch(opcao) {
            case 1:
                iniciarPartida(2);
                break;
            case 2:
                iniciarPartida(1);
                break;
            case 3:
                retomarPartida();
                break;
            case 4:
                exibirRegras();
                break;
            case 5:
                if (!partidaEmAndamento)
                    mostrarMensagem("Nao ha partida para salvar.");
                else if (gravarJogo())
                    mostrarMensagem("Jogo salvo em CAD_DOMINO, CAD_MESA e CAD_JOGO.");
                else
                    mostrarMensagem("Nao foi possivel gravar os arquivos.");
                pausar();
                break;
            case 6:
                if (recuperarJogo()) {
                    mostrarMensagem("Jogo recuperado. Use a opcao 3 para continuar jogando.");
                } else {
                    mostrarMensagem("Nao ha jogo salvo para recuperar.");
                }
                pausar();
                break;
            case 7:
                mostrarTodasAsPecas();
                break;
            case 0:
                mostrarMensagem("Encerrando o programa...");
                break;
            default:
                mostrarMensagem("Opcao invalida.");
                pausar();
        }
    } while(opcao != 0);
}
