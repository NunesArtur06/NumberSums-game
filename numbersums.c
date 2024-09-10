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

void limpaTela() {
    system(CLEAR);
}
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
    printf(GREEN"*** ESCOLHA O MODO DE JOGO ***\n\n"GREEN);
    printf("1 - Iniciante\n");
    printf("2 - Intermediario\n");
    printf("3 - Avancado\n");
    printf("4 - Retornar\n\n");
    printf("Digite a opcao desejada: ");
}

void config(){
    printf(GREEN"*** CONFIGURACOES ***\n\n"RESET);
    printf("1 - Zerar Ranking\n");
    printf("2 - Modo de Dificuldade\n");
    printf("3 - Voltar ao menu principal\n\n");
    printf("Digite a opcao desejada: ");
}

void vocePerdeu(){
    limpaTela();
    printf(RED" _    ______  ____________   ____  __________  ____  ________  __             __\n"RESET);
    printf(RED"| |  / / __ \\/ ____/ ____/  / __ \\/ ____/ __ \\/ __ \\/ ____/ / / /      _    _/_/\n"RESET);
    printf(RED"| | / / / / / /   / __/    / /_/ / __/ / /_/ / / / / __/ / / / /      (_)  / /  \n"RESET);
    printf(RED"| |/ / /_/ / /___/ /___   / ____/ /___/ _, _/ /_/ / /___/ /_/ /      _    / /   \n"RESET);
    printf(RED"|___/\\____/\\____/_____/  /_/   /_____/_/ |_/_____/_____/\\____/      (_)  / /    \n"RESET);
    printf(RED"                                                                         |_|    \n"RESET);
}
void jogodassomas(){
    printf(GREEN"      _  ____   _____  ____    _____           _____    _____  ____  __  __           _____ \n"RESET);
    printf(GREEN"     | |/ __ \\ / ____|/ __ \\  |  __ \\   /\\    / ____|  / ____|/ __ \\|  \\/  |   /\\    / ____|\n"RESET);
    printf(GREEN"     | | |  | | |  __| |  | | | |  | | /  \\  | (___   | (___ | |  | | \\  / |  /  \\  | (___  \n"RESET);
    printf(GREEN" _   | | |  | | | |_ | |  | | | |  | |/ /\\ \\  \\___ \\   \\___ \\| |  | | |\\/| | / /\\ \\  \\___ \\ \n"RESET);
    printf(GREEN"| |__| | |__| | |__| | |__| | | |__| / ____ \\ ____) |  ____) | |__| | |  | |/ ____ \\ ____) |\n"RESET);
    printf(GREEN" \\____/ \\____/ \\_____|\\____/  |_____/_/    \\_\\_____/  |_____/ \\____/|_|  |_/_/    \\_\\_____/\n\n\n\n"RESET);;
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

int leRanking() {
    FILE *fp = fopen("ranking.bin", "rb");
    if (fp == NULL) {
        printf("Erro ao abrir arquivo\n");
        return 0;
    }

    int index = 0;
    struct dados {
        int pontuacao;
        char nome[20];
    };
    struct dados jogador;
    
    while (fread(&jogador, sizeof(jogador), 1, fp)) {
        strcpy(nomes[index], jogador.nome); // Copia o nome para o array de nomes
        pts[index] = jogador.pontuacao;     // Copia a pontuação para o array de pontuações
        index++;
    }
    
    fclose(fp);
    return index; // Retorna o tamanho do ranking
}

// Função para escrever o ranking atualizado no arquivo binário
void escreveRanking(int index) {
    FILE *fp = fopen("ranking.bin", "wb");
    if (fp == NULL) {
        printf("Erro ao abrir arquivo\n");
        return;
    }

    struct dados {
        int pontuacao;
        char nome[20];
    };
    struct dados jogador;
    
    for (int i = 0; i < index; i++) {
        jogador.pontuacao = pts[i];
        strcpy(jogador.nome, nomes[i]);
        fwrite(&jogador, sizeof(jogador), 1, fp); // Escreve o jogador no arquivo
    }
    
    fclose(fp);
}

// Função para adicionar um novo jogador ao ranking
void adicionaJogador(int *index, char *novoNome, int novaPontuacao) {
    strcpy(nomes[*index], novoNome); // Adiciona o nome no array de nomes
    pts[*index] = novaPontuacao;     // Adiciona a pontuação no array de pontuações
    (*index)++;                      // Incrementa o tamanho do ranking
}

// Função para ordenar o ranking por pontuação (Bubble Sort)
void ordenaRanking(int index) {
    for (int i = 0; i < index - 1; i++) {
        for (int j = 0; j < index - i - 1; j++) {
            if (pts[j] < pts[j + 1]) { // Ordena em ordem decrescente
                // Troca pontuação
                int tempPts = pts[j];
                pts[j] = pts[j + 1];
                pts[j + 1] = tempPts;
                
                // Troca nomes
                char tempNome[20];
                strcpy(tempNome, nomes[j]);
                strcpy(nomes[j], nomes[j + 1]);
                strcpy(nomes[j + 1], tempNome);
            }
        }
    }
}

void AlteraRanking(char* nickname, int pontos) {
    char linha[50 + 1 + 3];   // 50 do nickname, 1 do ":", 3 da pontuação
    char nickRanking[50];     // Guarda um nick retirado do ranking
    int pontosRanking;        // Guarda a pontuação do nick retirado do ranking
    int encontrou = 0;

    // Abrir o arquivo ranking.txt para leitura
    FILE *ranking = fopen("ranking.txt", "rb");
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
    temp = fopen("temp.bin", "rb");
    ranking = fopen("ranking.bin", "wb");

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
    remove("temp.bin");
}

void printRanking(int index) {
    if (index == 0) {
        printf(GREEN"*** RANKING ***\n\n\n\n\n\n\n"RESET);
        printf("Nenhum jogador no ranking.\n");
        return;
    }

    printf(GREEN"\n*** RANKING ***\n"RESET);
    for (int i = 0; i < index; i++) {
        printf("%d. %s - %d pontos\n", i + 1, nomes[i], pts[i]);
    }
}

void LimpaRanking() {
    FILE *ranking = fopen("ranking.bin", "w");  // Abre o arquivo em modo "wb", o que limpa o conteúdo

    // Se o arquivo não puder ser aberto, imprime uma mensagem de erro
    if (ranking == NULL) {
        perror("Impossível limpar o arquivo de ranking");
        return;
    }

    // Fecha o arquivo após limpar (escrever nada nele)
    fclose(ranking);

    printf(GREEN"Ranking limpo com sucesso!\n"RESET);
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
void verificaLinha(int linha, int somas_linhas[], int *linhaFechada) {
    int i, soma = 0;
    char ch;
    FILE* arquivo = fopen("copia.txt", "r");
    int posicaoLinha = (linha * tamanho + linha + tamanho * tamanho); // Cálculo da posição da linha no arquivo
    for (i = 0; i < posicaoLinha; i++)
        getc(arquivo);

    for (i = 0; i < tamanho; i++) {
        ch = getc(arquivo);
        if (ch != ' ' && ch >= '0' && ch <= '9') {
            soma += ch - '0'; // Converte caractere para inteiro
        }
    }
    fclose(arquivo);

    if (soma == somas_linhas[linha - 1] && !(*linhaFechada)) {
        *linhaFechada = 1; // Marca a linha como fechada
    }
}

void verificaColuna(int coluna, int somas_colunas[], int *colunaFechada) {
    int i, soma = 0;
    char ch;
    FILE* arquivo = fopen("copia.txt", "r");
    int posicaoColuna = (tamanho + 1) * tamanho + coluna; // Cálculo da posição da coluna no arquivo

    for (i = 0; i < posicaoColuna; i++)
        getc(arquivo);

    for (i = 0; i < tamanho; i++) {
        ch = getc(arquivo);
        if (ch != ' ' && ch >= '0' && ch <= '9') {
            soma += ch - '0'; // Converte caractere para inteiro
        }
    }
    fclose(arquivo);

    // Verificar se a coluna foi fechada
    if (soma == somas_colunas[coluna] && !(*colunaFechada)) {
        *colunaFechada = 1; // Marca a coluna como fechada
    }
}

int calculaSomaColuna(int coluna) {
    FILE* arquivo = fopen("copia.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    int soma = 0;
    char valor;

    // Ler a matriz e somar os valores da coluna desejada
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            valor = fgetc(arquivo);
            if (j == coluna && valor != ' ') {
                soma += valor - '0';  // Converte caractere para inteiro
            }
        }
        fgetc(arquivo);  // Pular o caractere de nova linha
    }

    fclose(arquivo);
    return soma;
}

int calculaSomaLinha(int linha) {
    FILE* arquivo = fopen("copia.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    int soma = 0;
    char valor;
    
    // Pular as linhas anteriores à linha desejada
    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < tamanho; j++) {
            fgetc(arquivo);
        }
        fgetc(arquivo);  // Pular o caractere de nova linha
    }

    // Ler e somar os valores da linha desejada
    for (int j = 0; j < tamanho; j++) {
        valor = fgetc(arquivo);
        if (valor != ' ') {
            soma += valor - '0';  // Converte caractere para inteiro
        }
    }

    fclose(arquivo);
    return soma;
}


void calculaSomas(int* valores_somas_linhas, int* valores_somas_colunas) {
    FILE* arquivo = fopen("copia.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char linha[50];
    
    // Pular a matriz (as primeiras linhas do arquivo) e chegar até as somas
    for (int i = 0; i < tamanho; i++) {
        fgets(linha, sizeof(linha), arquivo);  // Ler cada linha da matriz
    }

    for (int i = 0; i < tamanho; i++) {
        valores_somas_colunas[i] = (fgetc(arquivo) - '0') * 10 + (fgetc(arquivo) - '0');  // Lê duas colunas por vez
    }

    fgetc(arquivo);  

    for (int i = 0; i < tamanho; i++) {
        valores_somas_linhas[i] = (fgetc(arquivo) - '0') * 10 + (fgetc(arquivo) - '0');  // Lê duas colunas por vez
    }


    fclose(arquivo);
}

void alteraMatriz(int linha, int coluna, int *vida)
{
    int i,k=0;
    FILE* matriz = fopen("copia.txt","r");
    int coord = coluna+(linha-1)*(tamanho+1);
    char errou, ch;
    for (i=0;i<(tamanho*(tamanho+5)+2);i++) // O cálculo é a forma simplificada de (tamanho+1)*tamanho+tamanho*2*2+2
        getc(matriz);
    for(i=0;i<coord;i++)
        errou = getc(matriz);
    fclose(matriz);

    if (errou == '1') {
        *vida -= 1;
        printf("Que pena, voce " RED "ERROU" RESET "! Tecle <enter> para tentar novamente.");
        getchar(); // Aguarda novo <enter> do usuário
        return;
    } else {
        FILE* velhaMatriz = fopen("copia.txt", "r");
        FILE* novaMatriz = fopen("copianova.txt", "w");

        while ((ch = fgetc(velhaMatriz)) != EOF) {
            if (k == (coord - 1)) {
                fputc(' ', novaMatriz);
            } else {
                fputc(ch, novaMatriz);
            }
            k++;
        }
        fclose(velhaMatriz);
        fclose(novaMatriz);

        velhaMatriz = fopen("copia.txt", "w");
        novaMatriz = fopen("copianova.txt", "r");

        while ((ch = fgetc(novaMatriz)) != EOF) {
            fputc(ch, velhaMatriz);
        }
        fclose(velhaMatriz);
        fclose(novaMatriz);

        // Exibir mensagem de acerto e esperar <enter>
        printf("Parabens, voce " GREEN "ACERTOU" RESET "! Tecle <enter> para continuar.\n");
        getchar(); // Captura a tecla enter


    }
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
    int index = leRanking();
    limpaTela();
    char nome[50];
    int num, opcao, modo=1, ponto, vida=5; // Modo inicia automaticamente no Iniciante
    int valores_somas_linhas[tamanho], valores_somas_colunas[tamanho];

    int linha=0, coluna=0;
    copiaMatriz(modo);
    limpaTela();
    jogodassomas();
    printf("Bem vindo(a) ao Jogo das Somas de APC!!!!\n\n");
    printf("Informe seu nickname: ");
    scanf("%s", nome); 
    printf("teste p/ ranking. pts: ");
    scanf("%d", &ponto);

    adicionaJogador(&index, nome, ponto); // Adiciona o novo jogador
    ordenaRanking(index); // Ordena o ranking por pontuação
    escreveRanking(index); // Escreve o ranking atualizado no arquivo binário

    limpaTela();


    while (1) {
        menu();
        scanf("%d", &num);
        getchar();  // Consumir o newline residual
        limpaTela();

    if (num == 1) { // JOGAR
        limpaTela();//limpa a tela
        matriz(modo);
        while (vida > 0) { // Loop de jogadas
                printf(GREEN"\n\n*** VOCE TEM "RED"%d"GREEN" VIDAS ***\n"RESET, vida);
                printf("Digite a linha e coluna do elemento a ser apagado: ");
                scanf("%d %d", &linha, &coluna);

                // Chama a função para alterar a matriz e atualiza as vidas
                int vidas_anteriores = vida;
                alteraMatriz(linha, coluna, &vida);
                getchar();

                    if (vidas_anteriores == vida) {
                        calculaSomas(valores_somas_linhas, valores_somas_colunas);

                        // Verifica se a linha foi fechada
                        int soma_linha = calculaSomaLinha(linha - 1);
                        if (soma_linha == valores_somas_linhas[linha - 1]) {
                            printf(GREEN "Muito bem, voce " GREEN "fechou a linha %d! " RESET "Pressione <enter> para continuar.", linha);
                            getchar(); // Captura a tecla enter
                        }

                        // Verifica se a coluna foi fechada
                        int soma_coluna = calculaSomaColuna(coluna - 1);
                        if (soma_coluna == valores_somas_colunas[coluna - 1]) {
                            printf("Muito bem, voce " GREEN "fechou a coluna %d! " RESET "Pressione <enter> para continuar.", coluna);
                            getchar(); // Captura a tecla enter
                        }
                    }
                // Reimprime a matriz após a jogada
                limpaTela();
                matriz(modo); // Reimprimir a matriz atualizada

                if (vida == 0) { // Se o jogador perder todas as vidas
                vocePerdeu();
                printf(RED "\n\n\n\nFim de jogo! Voce perdeu todas as vidas.\n" RESET);
                printf("Pressione <enter> para tentar novamente!\n");
                getchar();
                limpaTela();
                
                // Reseta as vidas e recarrega a matriz original
                vida = 5;
                copiaMatriz(modo); // Restaura a matriz original
                break; // Sai do loop de jogadas, permitindo ao jogador tentar novamente
            }
            }
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
                printf(GREEN"*** RANKING ***\n\n\n\n\n"RESET);
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
                    printf(GREEN"MODO INICIANTE SELECIONADO\n"RESET);
                    copiaMatriz(modo);
                    printf("\n\n\n\n\nPressione <enter> para voltar: ");
                } else if (modo == 2) { // MODO INTERMEDIÁRIO
                    limpaTela();
                    printf(GREEN"MODO INTERMEDIARIO SELECIONADO\n"RESET);
                    copiaMatriz(modo);
                    printf("\n\n\n\n\nPressione <enter> para voltar: ");
                } else if (modo == 3) { // MODO AVANÇADO
                    limpaTela();
                    printf(GREEN"MODO AVANCADO SELECIONADO\n"RESET);
                    copiaMatriz(modo);
                    printf("\n\n\n\n\nPressione <enter> para voltar: ");
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
        index = leRanking();
        printRanking(index);
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
