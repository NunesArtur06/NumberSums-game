#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int tamanho;  //tamanho da matriz
char nomes[900][20]; //900 linhas de 20 caracteres cada
int pts[900]; // lista das pontuacoes

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
    printf(GREEN"Objetivo do jogo: \n\n"RESET);
    printf("O jogo sempre comeca com 5 vidas. O objetivo do jogo eh apagar os elementos das linhas e colunas de modo que os elementos restantes na tela, uma vez somando sao exatamente os valores mostrados no topo das colunas e na frente das linhas.\n\n");
    printf(GREEN"COMO APAGAR UM ELEMENTO DA MATRIZ?\n\n"RESET); 
    printf("Para apagar um elemento o jogador deve informar a linha e a coluna do numero a ser apagado. No modo iniciante a matriz do jogo eh 4x4, no modo intermediario a matriz eh 6x6 e no modo avancado a matriz eh 7x7. Para o jogador as linhas e colunas iniciam sempre em 1. \n\n\n\n");
    printf(GREEN"*** EXEMPLO ***\n\n"RESET);
    printf("      06 03 21 19\n");
    printf("     -------------\n");
    printf("  19 | 2  4  8  9 \n");
    printf("  09 | 8  7  6  3 \n");
    printf("  11 | 4  8  1  7 \n");
    printf("  10 | 2  3  7  7 \n\n");
    printf("*** Voce tem 5 vidas ***\n");
    printf("Digite linha e coluna do elemento a ser apagado: 2 3\n");
}
void res(){
    printf(GREEN"*** EXEMPLO ***\n\n"RESET);
    printf("      06 03 21 19\n");
    printf("     -------------\n");
    printf("  19 | 2  4  8  9 \n");
    printf("  09 | 8  7     3 \n");
    printf("  11 | 4  8  1  7 \n");
    printf("  10 | 2  3  7  7 \n\n");
    printf("*** Voce tem 5 vidas ***\n");
    printf("Digite linha e coluna do elemento a ser apagado: 2 3\n");
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
    printf(GREEN"      _  ____   _____  ____    _____           _____    _____  ____  __  __           _____ \n"RESET);
    printf(GREEN"     | |/ __ \\ / ____|/ __ \\  |  __ \\   /\\    / ____|  / ____|/ __ \\|  \\/  |   /\\    / ____|\n"RESET);
    printf(GREEN"     | | |  | | |  __| |  | | | |  | | /  \\  | (___   | (___ | |  | | \\  / |  /  \\  | (___  \n"RESET);
    printf(GREEN" _   | | |  | | | |_ | |  | | | |  | |/ /\\ \\  \\___ \\   \\___ \\| |  | | |\\/| | / /\\ \\  \\___ \\ \n"RESET);
    printf(GREEN"| |__| | |__| | |__| | |__| | | |__| / ____ \\ ____) |  ____) | |__| | |  | |/ ____ \\ ____) |\n"RESET);
    printf(GREEN" \\____/ \\____/ \\_____|\\____/  |_____/_/    \\_\\_____/  |_____/ \\____/|_|  |_/_/    \\_\\_____/\n"RESET);;
    printf("\n\n\n1 - Jogar\n");
    printf("2 - Instrucoes\n");
    printf("3 - Configuracoes\n");
    printf("4 - Ranking\n");
    printf("5 - Sair\n\n");
    printf("Digite a opcao desejada: ");
}

void limpaTela() {
    system(CLEAR);
}
int leRanking(){
    FILE *fp = fopen("ranking.bin", "r");
    int index=0;
    struct batata{
        int pontuacao;
        char nome[20];
    };

    struct batata bat; // variavel
    
    
    while(fread( &bat, sizeof(bat), 1, fp)){
        printf("%d %s\n", bat.pontuacao, bat.nome);
        strcpy(nomes[index], bat.nome);
        pts[index] = bat.pontuacao;
        index++;
        
    }
    fclose (fp);
    return index; // retorna o tamanho do ranking
}

void escreveRanking(int index){
    FILE *fp = fopen("ranking.bin", "w");
    struct batata{
        int pontuacao;
        char nome[20];
    };

    struct batata bat; // variavel
    
    for( int i = 0; i < index; i++){
        bat.pontuacao = pts[i];
        strcpy(bat.nome, nomes[i]);
        fwrite(&bat, sizeof(bat), 1, fp);
    }
    fclose (fp);
    
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
void copiaMatriz(int dificuldade) //clona o arquivo escolhido
{
    FILE* copia = fopen("copia.txt","w");
    FILE* original;
    char chr;

    switch (dificuldade) //Busca a dificuldade selecionada
    {
        case 1: original= fopen("iniciante.txt","r");
        tamanho = 4; break;
        case 2: original= fopen("intermediario.txt","r");
        tamanho = 6;  break;
        case 3: original= fopen("avancado.txt","r");
        tamanho = 7; break;
        default: printf(RED"Dificuldade nao selecionada"RESET); return;
    }
    while ((chr=fgetc(original))!=EOF)
    {
        fprintf(copia,"%c",chr);
    }
    fclose(copia);
    fclose(original);
}

void matriz() //Gera a matriz
{
    int x=0,y=0; //Variáveis de controle
    int coluna[14]; //Armazena os valores das somas da coluna (maximo de 7x2 = 14 para 7x7)
    FILE* matriz; //Variável de arquivo
    matriz= fopen("copia.txt","r");

    for(x=0;x<(tamanho * tamanho)+tamanho;x++) //pula os números internos da matriz
    {
        fgetc(matriz);
    }

    printf("      ");
    for(x=0;x<tamanho;x++)//Printa os números da linha da soma, de 2 em 2
    {
        putchar(fgetc(matriz));
        putchar(fgetc(matriz));
        printf(" ");
    }
    fgetc(matriz);//Come o <enter>

    for(x=0;x<tamanho * 2;x++)//Armazena as somas da coluna.
    {
        coluna[x]=fgetc(matriz);
    }
    printf("\n     "); 
    for (x = 0; x < tamanho * 3; x++) printf("-"); // A linha divisória é adaptada ao número de colunas
    printf("\n");

    fclose(matriz); //fecha o arquivo
    matriz= fopen("copia.txt","r");

    for (x = 0; x < tamanho; x++) {
        printf("  %c%c | ", coluna[x * 2], coluna[x * 2 + 1]); // Exibe as somas das colunas à esquerda, alinhadas corretamente
        for (y = 0; y < tamanho; y++) {
            putchar(fgetc(matriz)); // Imprime cada valor da matriz com espaços para alinhamento
            printf("  "); // Espaçamento entre os valores da matriz
        }
        printf("\n"); // Passa para a próxima linha da matriz
        fgetc(matriz); // Consome o caractere <enter> ao final de cada linha
    }

    return;
}

int main() {
    int val = leRanking();
    printf("%d\n", val);
    strcpy(nomes[val], "teste");
    pts[val] = 30;
    escreveRanking(val+1);
    leRanking();
    getchar();
    //teste
    char nickname[50];
    int num, opcao, modo = 1; // Modo inicia automaticamente no Iniciante

    int linha=0, coluna=0;

    limpaTela();
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
        limpaTela();//limpa a tela
        copiaMatriz(modo);
        matriz(modo);
        printf(GREEN"\n\n*** VOCE TEM 5 VIDAS ***\n"RESET);
        printf("Digite a linha e coluna do elemento a ser apagado: ");
        scanf("%d %d", &linha, &coluna);
        limpaTela();
    } else if (num == 2) { // INSTRUÇÕES
        instructions();
        printf("\nTecle <enter> para continuar: ");
        getchar();  // Esperar pelo Enter para printar o resultado do exemplo
        limpaTela();
        res();
        printf("\nTecle <enter> para voltar para o menu: ");
        getchar();
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
        limpaTela();
        printf(RED"OPCAO INVALIDA!\n\n\n");
        printf(RED"PRESSIONE <enter> E TENTE NOVAMENTE!\n\n\n"RESET);
        getchar();
        limpaTela();
    }
}

return 0;
}