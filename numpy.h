/**
 * @file numpy.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-01-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */

struct matrix{
    int *data; //vetor de dados
    int n_rows; //numero de linhas
    int n_cols; //numero de colunas
    int stride_rows; // valor de "pulo" para a proxima linha
    int stride_cols; // valor de "pulo" para a proxima coluna
    int offset; // inicio de contagem para acesso
};

//-- Rotinas de criação
struct matrix create(int *data, int n_rows, int n_cols);
struct matrix create_zeros(int n_rows, int n_cols);
struct matrix create_ones(int n_rows, int n_cols);
struct matrix create_id(int n_rows, int n_cols);
struct matrix create_range(int n_rows, int n_cols, int start, int step);
struct matrix create_full(int n_rows, int n_cols, int value);
struct matrix create_tile(int *data, int rep);
struct matrix create_multiply(int *data, int value);


int get(struct matrix m, int i, int j);

void set(struct matrix m, int i, int j, int value);

void print(struct matrix m);

