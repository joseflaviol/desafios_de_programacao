#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

int linhas, colunas;
char **entrada;

bool busca_horizontal(char *busca, int t_busca, int x, int y);
bool busca_vertical(char *busca, int t_busca, int x, int y);
bool busca_diagonal(char *busca, int t_busca, int x, int y);

int main() {

    int casos;
    int buscas;
    int a, b, i, j;
    char *busca;
    bool achou;

    scanf("%d", &casos);

    for (a = 0; a < casos; a++) {

        scanf("%d %d", &linhas, &colunas);
      
        entrada = malloc(sizeof(char *) * linhas);
        
        for (i = 0; i < linhas; i++) {
            entrada[i] = malloc(sizeof(char) * colunas);    
        }

        getchar();
        
        for (i = 0; i < linhas; i++, getchar()) {
            fgets(entrada[i], colunas + 1, stdin);
            entrada[i][colunas] = '\0';
        }
  
        scanf("%d", &buscas);

        busca = malloc(sizeof(char) * 51);

        getchar();
      
        for (b = 0; b < buscas; b++) {
            fgets(busca, 51, stdin);
            busca[strlen(busca) - 1] = '\0';
            
            achou = false;
            
            for (i = 0; i < linhas; i++) {
                for (j = 0; j < colunas; j++) {
                    if (tolower(entrada[i][j]) == tolower(busca[0])) {
                        if (busca_horizontal(busca, strlen(busca), i, j) || busca_vertical(busca, strlen(busca), i, j) || busca_diagonal(busca, strlen(busca), i, j)) {
                            printf("%d %d\n", i + 1, j + 1);
                            achou = true;
                            break;
                        }    
                    }
                }
                if (achou) break;
            }
        }

        free(entrada);
        free(busca);
    
    }
  
    return 0;
}

bool busca_horizontal(char *busca, int t_busca, int x, int y) {
    int i;
    bool esquerda = true;
    bool direita = true;
  
    for (i = 0; i < t_busca; i++) {
        if (!esquerda && !direita) break;
        if (esquerda && y - i > -1 && tolower(busca[i]) == tolower(entrada[x][y - i])) {
            continue;
        } else {
            esquerda = false;
        }
        if (direita && y + i < colunas && tolower(busca[i]) == tolower(entrada[x][y + i])) {
            continue;
        } else {
            direita = false;
        }
    }

    return esquerda || direita;
}

bool busca_vertical(char *busca, int t_busca, int x, int y) {
    int i;
    bool cima = true;
    bool baixo = true;
  
    for (i = 0; i < t_busca; i++) {
        if (!cima && !baixo) break;
        if (cima && x - i > -1 && tolower(busca[i]) == tolower(entrada[x - i][y])) {
            continue;
        } else {
            cima = false;
        }
        if (baixo && x + i < linhas && tolower(busca[i]) == tolower(entrada[x + i][y])) {
            continue;
        } else {
            baixo = false;
        }
    }

    return cima || baixo;  
}

bool busca_diagonal(char *busca, int t_busca, int x, int y) {
    int i;
    bool esquerda_cima = true;
    bool esquerda_baixo = true;
    bool direita_cima = true;
    bool direita_baixo = true;
  
    for (i = 0; i < t_busca; i++) {
        if (!esquerda_cima && !esquerda_baixo && !direita_cima && !direita_baixo) break;
        if (esquerda_cima && x - i > -1 && y - i > -1 && tolower(busca[i]) == tolower(entrada[x - i][y - i])) {
            continue;
        } else {
            esquerda_cima = false;
        }
        if (esquerda_baixo && x + i < linhas && y - i > -1 && tolower(busca[i]) == tolower(entrada[x + i][y - i])) {
            continue;
        } else {
            esquerda_baixo = false;
        }
        if (direita_cima && x - i > -1 && y + i < colunas && tolower(busca[i]) == tolower(entrada[x - i][y + i])) {
            continue;
        } else {
            direita_cima = false;
        }
        if (direita_baixo && x + i < linhas && y + i < colunas && tolower(busca[i]) == tolower(entrada[x + i][y + i])) {
            continue;
        } else {
            direita_baixo = false;
        }
    }

    return esquerda_cima || esquerda_baixo || direita_cima || direita_baixo; 
}