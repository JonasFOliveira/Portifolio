/* Criando algumas funcoes do numpy em C
*/

#include "numpy.h"

struct matrix create(int *data, int n_rows, int n_cols){
    struct matrix m;
    m.data = data;
    m.n_rows = n_rows;
    m.n_cols = n_cols;
    m.stride_cols = 1; //Para mudar de coluna basta andar o vetor uma posicao
    m.stride_rows = n_cols; //para mudar de linha basta você andar o vetor por todas as colunas posicoes
    m.offset = 0; //O offset é a posicao inicial do vetor
    return m;
}

//Para acessar o elemento na linha i e coluna j em um vetor de 1D, temos que 
//realizar um calculo com i e j(i - linha, j- coluna)
//i*m.stride_rows + j*m.stride_cols

int get(struct matrix m, int i, int j){
    return m.data[i*m.stride_rows + j*m.stride_cols]; 
}

void set(struct matrix m, int i, int j, int value){
    m.data[i*m.stride_rows + j*m.stride_cols] = value;
}

void print_matrix(struct matrix m){
    for(int i = 0; i < m.n_rows; i++){
        for(int j = 0; j < m.n_cols; j++){
            printf("%d ", get(m, i, j));
        }
        printf("\n");
    }
}


