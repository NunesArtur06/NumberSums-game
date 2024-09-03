#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define CLEAR "cls"

        //Cores//
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"
//Use as cores no formato "printf(COR "texto" RESET);"/

//Cria a variável de arquivo "ranking"
FILE* ranking;

void instructions(){
    printf(GREEN"INSTRUCOES SOBRE O JOGO DAS SOMAS: \n\n"RESET);
    printf("ESCREVER NESSE ESPAÇO AS INSTRUCOES SOBRE COMO JOGAR O JOGO.\n");
}
void modo_dificuldade(){
    printf("* ESCOLHA O MODO DE JOGO *\n\n");
    printf(CYAN"1 - Iniciante\n"RESET);
    printf(YELLOW"2 - Intermediario\n"RESET);
    printf(RED"3 - Avancado\n"RESET);
    printf("4 - Retornar\n\n");
    printf("Digite a opcao desejada: ");
}

void config(){
    printf("* CONFIGURACOES *\n\n");
    printf("1 - Zerar Ranking\n");
    printf("2 - Modo de Dificuldade\n");
    printf("3 - Voltar ao menu principal\n\n");
    printf("Digite a opcao desejada: ");
}

void menu(){
    printf(GREEN"* JOGO DAS SOMAS *\n\n"RESET);
    printf("1 - Jogar\n");
    printf("2 - Instrucoes\n");
    printf("3 - Configuracoes\n");
    printf("4 - Ranking\n");
    printf("5 - Sair\n\n");
    printf("Digite a opcao desejada: ");
}

void limpaTela() {
    system(CLEAR);
}

void AlteraRanking(char* nickname, int pontos) {
    char linha[50 + 1 + 3];   // 50 do nickname, 1 do ":", 3 da pontuação
    char nickRanking[50];     // Guarda um nick retirado do ranking
    int pontosRanking;        // Guarda a pontuação do nick retirado do ranking
    int encontrou = 0;

    // Abrir o arquivo ranking.txt para leitura
    FILE *ranking = fopen("ranking.txt", "r");
    FILE *temp = fopen("temp.txt", "w");  // Arquivo temporário para armazenar o ranking atualizado

    // Se o arquivo não for encontrado, printa uma mensagem de erro
    if (ranking == NULL || temp == NULL) {
        perror("Impossível encontrar arquivo");
        return;
    }

    while (fgets(linha, sizeof(linha), ranking)) {
        sscanf(linha, "%[^:]:%d", nickRanking, &pontosRanking);

        if (strcmp(nickname, nickRanking) == 0) {
            pontosRanking += pontos;  // Atualiza a pontuação do jogador existente
            encontrou = 1;
        }

        // Escreve no arquivo temporário
        fprintf(temp, "%s:%d\n", nickRanking, pontosRanking);
    }

    if (!encontrou) {
        // Se o nickname não foi encontrado no ranking, adiciona a nova entrada
        fprintf(temp, "%s:%d\n", nickname, pontos);
    }

    fclose(ranking);
    fclose(temp);

    // Reabrir o arquivo temporário para leitura e o ranking.txt para escrita
    temp = fopen("temp.txt", "r");
    ranking = fopen("ranking.txt", "w");

    if (ranking == NULL || temp == NULL) {
        perror("Impossível encontrar arquivo");
        return;
    }

    // Agora reescrevemos o ranking no arquivo original, em ordem decrescente de pontuação
    struct {
        char nick[50];
        int pontos;
    } jogadores[100];  // Supondo que não há mais de 100 jogadores no ranking

    int i = 0;

    while (fgets(linha, sizeof(linha), temp)) {
        sscanf(linha, "%[^:]:%d", jogadores[i].nick, &jogadores[i].pontos);
        i++;
    }

    // Ordena os jogadores em ordem decrescente de pontuação
    for (int j = 0; j < i - 1; j++) {
        for (int k = j + 1; k < i; k++) {
            if (jogadores[j].pontos < jogadores[k].pontos) {
                // Troca os jogadores
                int tempPontos = jogadores[j].pontos;
                jogadores[j].pontos = jogadores[k].pontos;
                jogadores[k].pontos = tempPontos;

                char tempNick[50];
                strcpy(tempNick, jogadores[j].nick);
                strcpy(jogadores[j].nick, jogadores[k].nick);
                strcpy(jogadores[k].nick, tempNick);
            }
        }
    }

    // Escreve o ranking ordenado no arquivo
    for (int j = 0; j < i; j++) {
        fprintf(ranking, "%s:%d\n", jogadores[j].nick, jogadores[j].pontos);
    }

    fclose(ranking);
    fclose(temp);

    // Remove o arquivo temporário
    remove("temp.txt");
}


void MostraRanking()
{
    printf("* RANKING *\n\n");
    char letra; //Armazena um caractere do ranking

    ranking = fopen("ranking.txt","r"); //Abre o arquivo como "r", para ser lido
    if (ranking == NULL)
        perror("Impossivel encontrar arquivo");
    
    while((letra=fgetc(ranking))!=EOF) //Pega um caractere do ranking enquanto o arquivo não acabar
                                       //Automaticamente passa para o próximo caractere
        putchar(letra); //Printa o caractere

    fclose(ranking);
}

void LimpaRanking() {
    FILE *ranking = fopen("ranking.txt", "w");  // Abre o arquivo em modo "w", o que limpa o conteúdo

    // Se o arquivo não puder ser aberto, imprime uma mensagem de erro
    if (ranking == NULL) {
        perror("Impossível limpar o arquivo de ranking");
        return;
    }

    // Fecha o arquivo após limpar (escrever nada nele)
    fclose(ranking);

    printf("Ranking limpo com sucesso!\n");
    printf("\nTecle <enter> para voltar.");
}

void matriz(int dificuldade)
{
    FILE* matriz;

    switch (dificuldade)
    {
        case 1: matriz= fopen("iniciante.txt","r"); break;
        case 2: matriz= fopen("intermediario.txt","r"); break;
        case 3: matriz= fopen("avancado.txt","r"); break;
        default: printf(RED"Dificuldade nao selecionada"RESET); return;
    }
    while (1)
    {
        for(int x=5;x<7;x++)
        {
            for(int y=0;y<9;y++)
                putchar(fgetc(matriz));
        }
        for(int x=0;x<4;x++)
        {
            for(int y=0;y<5;y++)
                putchar(fgetc(matriz));
        }
    }
}
/*void printMatrix(int matrix[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void printArray(int array[SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}*/


int main() {
    char nickname[50];
    int num, opcao, modo = 1; // Modo inicia automaticamente no Iniciante

    printf(GREEN"Bem vindo(a) ao Jogo das Somas de APC!!!!\n\n"RESET);
    printf("Informe seu nickname: ");
    scanf("%s", nickname); 

    limpaTela();


    while (1) {
    menu();
    scanf("%d", &num);
    getchar();  // Consumir o newline residual
    limpaTela();

    if (num == 1) { // JOGAR
        matriz(modo);
    } else if (num == 2) { // INSTRUÇÕES
        instructions();
        printf("\nTecle <enter> para voltar ao menu principal: ");
        getchar();  // Esperar pelo Enter para voltar ao menu principal
        limpaTela();
    } else if (num == 3) { // CONFIGURAÇÕES
        int voltar = 0; // Flag para voltar ao menu principal
        while (!voltar) {
            config();
            scanf("%d", &opcao);
            getchar();  // Consumir o newline residual

            if (opcao == 1) { // ZERAR RANKING
                limpaTela();
                printf("* RANKING *\n\n\n\n\n");
                LimpaRanking();
                getchar();  // Esperar pelo Enter para voltar ao submenu de configurações
                limpaTela();
            } else if (opcao == 2) { // MODO DE DIFICULDADE
                limpaTela();
                modo_dificuldade();
                scanf("%d", &modo);
                getchar();

                if (modo == 1) { // MODO INICIANTE
                    limpaTela();
                    printf(CYAN"MODO INICIANTE SELECIONADO\n"RESET);
                    printf("\n\n\nPressione <enter> para voltar: ");
                } else if (modo == 2) { // MODO INTERMEDIÁRIO
                    limpaTela();
                    printf(YELLOW"MODO INTERMEDIARIO SELECIONADO\n"RESET);
                    printf("\n\n\nPressione <enter> para voltar: ");
                } else if (modo == 3) { // MODO AVANÇADO
                    limpaTela();
                    printf(RED"MODO AVANCADO SELECIONADO\n"RESET);
                    printf("\n\n\nPressione <enter> para voltar: ");
                } else {
                    limpaTela();
                    continue; // Voltar ao submenu de configurações
                }

                //voltando para o submenu de config
                getchar();  // Esperar pelo Enter para voltar ao submenu de configurações
                limpaTela();
            } else if (opcao == 3) { // VOLTAR PARA O MENU
                limpaTela();
                voltar = 1;  // Sair do submenu de configuracoes e voltar ao menu principal
            }
        }
    } else if (num == 4) { // RANKING
        MostraRanking();
        printf("\nTecle <enter> para voltar ao menu principal: ");
        getchar();  // Esperar pelo Enter para voltar ao menu principal
        limpaTela();
    } else if (num == 5) {
        printf("Saindo...\n");
        break;  // Sair do loop e terminar o programa
    } else {
        printf("Opção inválida!\n");
    }
}

return 0;
}