#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

// Funcao para vizualizar mapa no console
int viewmap(int map[15][15])
{
    int L, C;                // Variaveis LINHA COLUNA
    for (L = 0; L < 15; L++) // For para percorrer as linhas
    {
        for (C = 0; C < 15; C++) // For para percorrer as colunas
        {
            if (map[L][C] == 0 || map[L][C] == 1) // mostrando se o espaco esta preenchido.
            {
                printf("[ ]");
            }
            if (map[L][C] == 2) // mostrando a localizacao do usuario
            {
                printf("[O]");
            }
            if (map[L][C] == 3) // Marcacoes de passagem do usuario
            {
                printf("[-]");
            }
            if (C == 14)
            {
                printf("\n"); // Adicionando espacamento entre as linhas
            }
        }
    }
}
/* Funcao movimento do usuario.

caso direita coluna + 1, caso cima linha - 1, caso baixo linha + 1.  */

int moviment(int map[15][15])
{
    int L_User, C_User, l, c; // variaveis Linha atual(L_User), coluna atual(C_User), linha , coluna para usar no loop
    int walk = 0;             // Variavel comando(Recebe o comando do usuario)
    printf("\nComandos: Direita = 6, Baixo = 5, cima = 4\n\n");
    printf("Digite seu movimento: ");
    scanf("%d", &walk);
    while (walk < 4 || walk > 6) // regra enquanto comando estiver entre 4 e 6 ele funciona senao da comando invalido.
    {
        printf("Ops Comando Invalido!\n");
        printf("\nComandos: Direita = 6, Baixo = 5, cima = 4\n\n");
        printf("Digite seu movimento: ");
        scanf("%d", &walk);
    }
    for (l = 0; l < 15; l++) // For para percorrer as linhas
    {
        for (c = 0; c < 15; c++) // For para percorrer as colunas
        {
            if (map[l][c] == 2)
            {
                C_User = c; // posicao usuario coluna
                L_User = l; // posicao usuario linha
            }
        }
    }
    if (walk == 4) // inicializacao do if para andar pra cima
    {
        if (map[L_User - 1][C_User] == 1)
        {
            map[L_User - 1][C_User] = 5;
            return map;
        }
        if (L_User - 1 < 0) //if para nao passar a area permitida do mapa
        {
            printf("Ops bateu na parede, va para outra direcao!\n");
        }
        else
        {
            map[L_User - 1][C_User] = 2;
            map[L_User][C_User] = 3;
        }
    }
    if (walk == 5) // inicializacao do if para andar pra baixo
    {
        if (map[L_User + 1][C_User] == 1)
        {
            map[L_User + 1][C_User] = 5;
            return map;
        }
        if (L_User + 1 >= 15) // if para nao passar a area permitida do mapa
        {
            printf("Ops bateu na parede, va para outra direcao!\n");
        }
        else
        {
            map[L_User + 1][C_User] = 2;
            map[L_User][C_User] = 3;
        }
    }
    if (walk == 6) // inicializacao do if para andar pra direita
    {
        if (map[L_User][C_User + 1] == 1)
        {
            map[L_User][C_User + 1] = 5;
            return map;
        }

        if (C_User + 1 >= 15)
        {
        }
        else
        {
            map[L_User][C_User + 1] = 2;
            map[L_User][C_User] = 3;
        }
    }
    return map;
}

int main()
{
    // Inicializando aleatoriamente na primeira coluna
    srand(time(NULL));
    // Variaveis
    int map[15][15];               // terreno
    int start = rand() % 15;       // onde voce vai comecar
    int linha = 0, coluna = 0;     // Linha Coluna
    int r_coluna = 0, r_linha = 0; // coluna linha randomicas
    int a = 0;                     // variavel de aleatorio
    int win = 0;                   // vitoria
    int dificuldade = 0;           // dificuldade

    printf("voce comecara na: %d\n", start);

    //dificuldade entre 20% e 70%
    printf("Selecione sua dificuldade entre 45 e 157 bombas: ");
    scanf("%d", &dificuldade);
    while (dificuldade < 45 || dificuldade > 157) // Regra para nao deixar a dificuldade sair de 20% a 70%
    {
        printf("Ops Numero Invalido! Tente Novamente!(45-157)\n");
        printf("Selecione sua dificuldade entre 45 e 157 bombas: ");
        scanf("%d", &dificuldade);
    }
    //* Mapa comfigurando
    for (linha = 0; linha < 15; linha++)
    {
        for (coluna = 0; coluna < 15; coluna++)
        {
            map[linha][coluna] = 0;
        }
    }
    // gerando bombas com o fator de aleatoriedade
    for (a = 0; a < dificuldade; a++)
    {
        r_coluna = rand() % 15;
        r_linha = rand() % 15;
        while (map[r_linha][r_coluna] == 1)
        {
            r_coluna = rand() % 15;
            r_linha = rand() % 15;
        }
        map[r_linha][r_coluna] = 1;
    }
    map[start][0] = 2;
    // Agora criei um while como se fosse a regra do jogo pra ele acabar, com voce perdendo ou vencendo.
    while (win == 0)
    {
        viewmap(map);                        // chamando funcao viewmap
        map[15][15] = moviment(map);         // a função moviment retorna o mapa.
        for (linha = 0; linha < 15; linha++) // For para percorrer as linhas
        {
            for (coluna = 0; coluna < 15; coluna++) // For para percorrer as colunas
            {
                if (map[linha][coluna] == 5) // if para consultar se perdeu
                {
                    printf("Voce perdeu!");
                    return 0;
                }
            }
        }
        for (linha = 0; linha < 15; linha++)
        {
            if (map[linha][14] == 2) // if para consultar se venceu
            {
                printf("Voce Venceu!");
                win = 1;
            }
        }
    }
    return 0;
}