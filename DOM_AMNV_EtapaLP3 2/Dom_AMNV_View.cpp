//Dom_AMNV_View
//21/09/2026
//Anderson Silva, Marcella Alarcon, Nathalia Pedraca Pinho e Vitor Piccoli
//Projeto Domino LP2026 (Grupo AMNV) - Etapa LP3

#include <stdio.h>
#include <stdlib.h>
#include "Dom_AMNV_Model.h"
#include "Dom_AMNV_View.h"

// Descarta o que restou digitado ate o fim da linha
void fclear() {
    int carac;
    while ((carac = fgetc(stdin)) != EOF && carac != '\n') { }
}

// Exibe uma mensagem ao usuario
void mostrarMensagem(const char* msg) {
    printf("\n%s\n", msg);
}

// Aguarda o usuario pressionar Enter
void pausar() {
    printf("\nPressione Enter para continuar...");
    getchar();
}

void limpaTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Tela de encerramento da partida
void apresentarResultado(int vencedor) {
    int q1 = contarPecasJogador(1);
    int q2 = contarPecasJogador(2);

    printf("\n========================================\n");
    printf("            FIM DA PARTIDA\n");
    printf("========================================\n");

    if (vencedor == 0) {
        printf("\nPARTIDA EMPATADA!\n");
        printf("Os dois terminaram com a mesma quantidade\n");
        printf("de pecas e a mesma pontuacao.\n");
    } else if ((vencedor == 1 && q1 == 0) || (vencedor == 2 && q2 == 0)) {
        printf("\nO JOGADOR %d BATEU E VENCEU A PARTIDA!\n", vencedor);
    } else {
        printf("\nPARTIDA FECHADA: ninguem consegue jogar e\n");
        printf("o monte esta vazio.\n");
        printf("\nO JOGADOR %d VENCEU A PARTIDA!\n", vencedor);
    }

    printf("\n----------------------------------------\n");
    printf("Jogador 1: %d peca(s) na mao, %d ponto(s)\n", q1, somarPontosJogador(1));
    printf("Jogador 2: %d peca(s) na mao, %d ponto(s)\n", q2, somarPontosJogador(2));
    printf("----------------------------------------\n");

    printf("\nPressione Enter para voltar ao menu...");
    getchar();   // um so: aqui o teclado ja esta vazio
}

void apresentaMesa() {
    printf("\n========================================\n");
    printf("MESA: ");
    for(int i = mesaInicio; i <= mesaFim; i++) {
        printf("[%d|%d] ", peca[mesaSequencia[i]].lado1, peca[mesaSequencia[i]].lado2);
    }
    printf("\nExtremidades abertas -> Esquerda: %d | Direita: %d\n", mesaE, mesaD);
    printf("========================================\n");
}

void mostrarPecasJogador(int jogador) {
    char statusBusca = (jogador == 1) ? '1' : '2';
    printf("Jogador %d Pecas: ", jogador);
    int letra = 'a';
    for(int i = 0; i < 28; i++) {
        if(peca[i].status == statusBusca) {
            printf("%c.[%d|%d] ", letra, peca[i].lado1, peca[i].lado2);
            letra++;
        }
    }
    printf("\n");
}

void exibirRegras() {
    limpaTela();
    printf("========================================\n");
    printf("     REGRAS DO JOGO DE DOMINO   (1/2)   \n");
    printf("========================================\n\n");

    printf("AS PECAS\n");
    printf("  Sao 28 pecas, cada uma com dois numeros de 0 a 6,\n");
    printf("  de [0|0] ate [6|6], sem repetir combinacoes.\n");
    printf("  Uma peca com os dois numeros iguais, como [4|4],\n");
    printf("  chama-se carroca (ou bucha).\n\n");

    printf("O INICIO\n");
    printf("  Cada jogador recebe 7 pecas. As 14 restantes formam\n");
    printf("  o monte, de onde se compra durante a partida.\n");
    printf("  Abre o jogo quem tiver a maior carroca: procura-se do\n");
    printf("  [6|6] para baixo. Se ninguem recebeu carroca, abre quem\n");
    printf("  tiver a peca de maior soma. Essa primeira jogada e\n");
    printf("  automatica, e a vez passa ao adversario.\n\n");

    printf("A JOGADA\n");
    printf("  A mesa tem duas pontas abertas. Para jogar, um dos lados\n");
    printf("  da sua peca precisa ser igual ao numero de uma das pontas.\n");
    printf("  A peca e virada automaticamente para encaixar.\n");
    printf("  Se ela couber nas duas pontas, o programa pergunta onde\n");
    printf("  voce quer joga-la.\n\n");

    printf("COMPRAR E PASSAR\n");
    printf("  Voce pode comprar quantas pecas quiser, enquanto houver\n");
    printf("  monte. So e permitido passar a vez em uma unica situacao:\n");
    printf("  quando voce nao tem nenhuma peca que encaixe E o monte\n");
    printf("  ja esta vazio.\n\n");

    printf("Pressione Enter para ver como o jogo termina...");
    getchar();

    limpaTela();
    printf("========================================\n");
    printf("     REGRAS DO JOGO DE DOMINO   (2/2)   \n");
    printf("========================================\n\n");

    printf("O FIM DA PARTIDA\n");
    printf("  Vence quem colocar a ultima peca na mesa: e a batida.\n\n");
    printf("  A partida tambem termina quando trava, ou seja, quando\n");
    printf("  nenhum dos dois jogadores consegue jogar e o monte esta\n");
    printf("  vazio. Nesse caso:\n");
    printf("     1. vence quem tiver menos pecas na mao;\n");
    printf("     2. empatando na quantidade, somam-se os pontos das\n");
    printf("        pecas restantes (lado1 + lado2) e vence quem\n");
    printf("        tiver menos pontos;\n");
    printf("     3. empatando tambem nos pontos, a partida termina\n");
    printf("        empatada. E um caso raro.\n\n");

    printf("COMO OPERAR O JOGO\n");
    printf("  Durante a partida, suas pecas aparecem identificadas por\n");
    printf("  letras: a, b, c... Para agir, digite uma destas opcoes:\n\n");
    printf("     J  jogar uma peca (o programa pede a letra dela)\n");
    printf("     C  comprar uma peca do monte\n");
    printf("     P  passar a vez\n");
    printf("     S  interromper a partida e voltar ao menu\n\n");
    printf("  Depois de cada acao, pressione Enter para continuar.\n");
    printf("  A partida interrompida com S pode ser retomada pela\n");
    printf("  opcao 3 do menu principal, ou salva em arquivo pela\n");
    printf("  opcao 5 para continuar em outro dia.\n\n");

    printf("Pressione Enter para voltar ao menu...");
    getchar();
}

int menuPrincipal() {
    int opcao;
    limpaTela();
    printf("========================================\n");
    printf("         Projeto DOMINO (AMNV)          \n");
    printf("========================================\n");
    printf("1- Iniciar jogo (2 jogadores)\n");
    printf("2- Iniciar jogo (contra o computador)\n");
    printf("3- Retornar ao jogo interrompido\n");
    printf("4- Regras gerais do Jogo\n");
    printf("5- Salvar o jogo em arquivo\n");
    printf("6- Recuperar o jogo salvo\n");
    printf("7- Ver todas as pecas do domino\n");
    printf("0- Sair\n");
    printf("Opcao selecionada: ");

    int c = fgetc(stdin);
    if (c == EOF) return 0; // entrada acabou: sai do programa com seguranca
    if (c != '\n') fclear();

    if (c >= '0' && c <= '9')
        opcao = c - '0';
    else
        opcao = -1;

    return opcao;
}

char menuJogada(int extremidadeE, int extremidadeD) {
    char opcao;
    printf("J- Jogar (possiveis: %d ou %d)\n", extremidadeE, extremidadeD);
    printf("C- Comprar\n");
    printf("P- Passar\n");
    printf("S- Sair (interromper o jogo)\n");
    printf("Opcao: ");
    opcao = fgetc(stdin);
    if (opcao == EOF) return 'S'; // entrada acabou: encerra a partida com seguranca
    if (opcao != '\n') fclear();
    return opcao;
}

// Pergunta qual peca da mao o jogador quer usar
char pedirLetraDaPeca() {
    char letra;
    printf("Escolha a peca (ex: a, b, c...): ");
    letra = fgetc(stdin);
    if (letra != '\n') fclear();
    return letra;
}

// Pergunta em qual extremidade da mesa a peca sera colocada
char pedirLadoDaMesa() {
    char lado;
    printf("Escolha o lado da Mesa (E para Esquerda / D para Direita): ");
    lado = fgetc(stdin);
    if (lado != '\n') fclear();
    return lado;
}

// Mostra ao jogador qual peca ele acabou de comprar
void apresentarPecaComprada(int indice) {
    printf("\nVoce comprou a peca [%d|%d]\n", peca[indice].lado1, peca[indice].lado2);
}

// Mostra o que a maquina fez no turno dela
void apresentarJogadaComputador(int indice, int compras) {
    if (compras > 0)
        printf("\nA maquina comprou %d peca(s) e jogou a [%d|%d]\n",
               compras, peca[indice].lado1, peca[indice].lado2);
    else
        printf("\nA maquina jogou a peca [%d|%d]\n",
               peca[indice].lado1, peca[indice].lado2);
}

// Lista as 28 pecas do domino, sete por linha
void apresentarTodasAsPecas(const char* titulo) {
    printf("\n--- %s ---\n", titulo);
    for (int i = 0; i < 28; i++) {
        printf("[%d|%d] ", peca[i].lado1, peca[i].lado2);
        if ((i + 1) % 7 == 0) printf("\n");
    }
}
