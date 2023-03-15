//Criando funções de numpy em c++

//Importando bibliotecas
#include <iostream>

//Criando funcao de potencia(pow)
int pow(int base, int exp){
    int result = 1;
    for(int i = 0; i < exp; i++){
        result *= base;
    }
    return result;
}

//Criando classe matrix
class matrix{
private:
    int *data; //vetor de dados
    int n_rows; //numero de linhas
    int n_cols; //numero de colunas
    int stride_rows; // valor de "pulo" para a proxima linha
    int stride_cols; // valor de "pulo" para a proxima coluna
    int offset; // inicio de contagem para acesso
public:
    int* get_data(){return data;}
    int get_nrows(){return n_rows;}
    int get_ncols(){return n_cols;}
    int get_stride_rows(){return stride_rows;}
    int get_stride_cols(){return stride_cols;}
    int get_offset(){return offset;}

    void set_data(int *data){this->data = data;}
    void set_nrows(int n_rows){this->n_rows = n_rows;}
    void set_ncols(int n_cols){this->n_cols = n_cols;}
    void set_stride_rows(int stride_rows){this->stride_rows = stride_rows;}
    void set_stride_cols(int stride_cols){this->stride_cols = stride_cols;}
    void set_offset(int offset){this->offset = offset;}
    
    //montador
    matrix(int n_rows, int n_cols, int offset, int *data): n_rows(n_rows), n_cols(n_cols), stride_rows(n_cols), stride_cols(1), offset(offset), data(data) {} ;
    matrix(int n_rows, int n_cols, int stride_rows, int stride_cols, int offset, int *data): n_rows(n_rows), n_cols(n_cols), stride_rows(stride_rows), stride_cols(stride_cols), offset(offset), data(data) {} ;
    //destrutor
    ~matrix();
    //função para acessar elemento) 
    int get_element(int i, int j);
    void set_element(int i, int j, int value);
    //função para imprimir matriz
    void print_matrix();

    //rotinas de criação de matrizes
    matrix zeros(int n_rows, int n_cols);
    matrix ones(int n_rows, int n_cols);
    matrix identity(int n_rows, int n_cols);
    matrix full(int n_rows, int n_cols, int values);
    matrix tile(int rep);

    //Rotinas de manipulação de matrizes
    matrix transpose();
    void transpose_view();
    matrix reshape(int n_rows, int n_cols);
    matrix flatten();
    matrix concatenate(matrix B, int axis);
    matrix slice(int start, int end, int step);
    matrix slice(int start, int end);
    matrix slice(int start);

    //Rotinas de operações matemáticas
    matrix operator+(matrix A);
    matrix operator-(matrix A);
    matrix operator*(matrix A);
    matrix operator/(matrix A);
    matrix operator%(matrix A);
    matrix operator^(matrix A);
    
    matrix operator+=(int value);
    matrix operator-=(int value);
    matrix operator*=(int value);
    matrix operator/=(int value);
    matrix operator%=(int value);
    matrix operator^=(int value);
};

void print_data(int* data, int len){
    for(int i = 0; i < len; i++){
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}

matrix::~matrix(){
    if(data !=NULL)
        std::cout << "deleting data..." << data[0] << std::endl;
        delete data;
}

int matrix::get_element(int i, int j){
    return data[get_offset() + i*get_stride_rows() + j*get_stride_cols()];
}

void matrix::set_element(int i, int j, int value){
    data[get_offset() + i*get_stride_rows() + j*get_stride_cols()] = value;
}

void matrix::print_matrix(){
    for(int i = 0; i < n_rows; i++){
        for(int j = 0; j < n_cols; j++){
            std::cout << get_element(i, j) << " ";
        }
        std::cout << std::endl;
    }
}

//----- ROTINAS DE CRIAÇÃO DE MATRIZES -----
matrix matrix::zeros(int n_rows, int n_cols){
    int *data = new int[n_rows*n_cols];
    for(int i = 0; i < n_rows*n_cols; i++){
        data[i] = 0;
    }
    return matrix(n_rows, n_cols, 1, n_rows, 0, data);
}

matrix matrix::ones(int n_rows, int n_cols){
    int *data = new int[n_rows*n_cols];
    for(int i = 0; i < n_rows*n_cols; i++){
        data[i] = 1;
    }
    return matrix(n_rows, n_cols, 1, n_rows, 0, data);
}

matrix matrix::identity(int n_rows, int n_cols){
    int *data = new int[n_rows*n_cols];
    for(int i = 0; i < n_rows; i++){
        for(int j = 0; j < n_cols; j++){
            if(i == j){
                data[i*n_rows + j] = 1;
            }
            else{
                data[i*n_rows + j] = 0;
            }
        }
    }
    return matrix(n_rows, n_cols, 1, n_rows, 0, data);
}

matrix matrix::full(int n_rows, int n_cols, int value){
    int *data = new int[n_rows*n_cols];
    for(int i = 0; i < n_rows*n_cols; i++){
        data[i] = value;
    }
    return matrix(n_rows, n_cols, 1, n_rows, 0, data);
}

matrix matrix::tile(int rep){
    int *data = new int[get_nrows()*get_ncols()*rep];
    for(int i = 0; i < rep; i++){
        for(int j = 0; j < get_nrows()*get_ncols(); j++){
            data[i*get_nrows()*get_ncols() + j] = data[j];
        }
    }
}

//----- ROTINAS DE MANIPULAÇÃO DE MATRIZES -----
matrix matrix::transpose(){
    int *data = new int[n_rows*n_cols];
    for(int i = 0; i < n_cols; i++){
        for(int j = 0; j < n_cols; j++){
            data[j*n_rows + i] = get_element(i, j);
        }
    }
    return matrix(n_cols, n_rows, 1, n_cols, 0, data);
}

void matrix::transpose_view(){
    matrix m = transpose();
    m.print_matrix();
}

matrix matrix::reshape(int n_rows, int n_cols){
    if(n_rows*n_cols == get_nrows()*get_ncols()){
        return matrix(n_rows, n_cols, 1, n_rows, 0, get_data());
    }
}

matrix matrix::flatten(){
    return matrix(get_nrows()*get_ncols(), 1, 1, get_nrows()*get_ncols(), 0, get_data());
}

matrix matrix::concatenate(matrix B, int axis){
    if(axis){
        if(get_nrows() == B.get_nrows()){
            int *data = new int[get_nrows()*(get_ncols() + B.get_ncols())];
            for(int i = 0; i < get_nrows(); i++){
                for(int j = 0; j < get_ncols(); j++){
                    data[i*get_nrows() + j] = get_element(i, j);
                }
                for(int j = 0; j < B.get_ncols(); j++){
                    data[i*get_nrows() + j + get_ncols()] = B.get_element(i, j);
                }
            }
        }
        else{
            std::cout << "ERRO: As matrizes não possuem o mesmo número de linhas" << std::endl;
            return matrix(0, 0, 0, 0, 0, NULL);
            }
    }
    else{
        if(get_ncols() == B.get_ncols()){
            int *data = new int[(get_nrows() + B.get_nrows())*get_ncols()];
            for(int i = 0; i < get_nrows(); i++){
                for(int j = 0; j < get_ncols(); j++){
                    data[i*get_nrows() + j] = get_element(i, j);
                }
            }
            for(int i = 0; i < B.get_nrows(); i++){
                for(int j = 0; j < B.get_ncols(); j++){
                    data[(i + get_nrows())*get_nrows() + j] = B.get_element(i, j);
                }
            }
        }
        else{
            std::cout << "ERRO: As matrizes não possuem o mesmo número de colunas" << std::endl;
            return matrix(0, 0, 0, 0, 0, NULL);
            }
    }
}

matrix matrix::slice(int start, int end, int step){
    if(n_rows > 1){
        std::cout << "ERRO: A matriz não é um vetor" << std::endl;
        return matrix(0, 0, 0, 0, 0, NULL);
    }
    else{
        int *data = new int[(end - start)/step];
        for(int i = start; i < end; i += step){
            data[i] = get_element(0, i);
        }
        return matrix((end - start)/step, 1, 1, (end - start)/step, 0, data);
    }
}

matrix matrix::slice(int start, int end){
    return slice(start, end, 1);
}

matrix matrix::slice(int start){
    return slice(start, get_ncols(), 1);
}

matrix matrix::operator+(matrix A){
    if(get_nrows() == A.get_nrows() && get_ncols() == A.get_ncols()){
        int *data = new int[get_nrows()*get_ncols()];
        for(int i = 0; i < get_nrows(); i++){
            for(int j = 0; j < get_ncols(); j++){
                data[i*get_nrows() + j] = get_element(i, j) + A.get_element(i, j);
            }
        }
        return matrix(get_nrows(), get_ncols(), 1, get_nrows(), 0, data);
    }
    else{
        std::cout << "ERRO: As matrizes não possuem as mesmas dimensões" << std::endl;
        return matrix(0, 0, 0, 0, 0, NULL);
    }
}

matrix matrix::operator-(matrix A){
    if(get_nrows() == A.get_nrows() && get_ncols() == A.get_ncols()){
        int *data = new int[get_nrows()*get_ncols()];
        for(int i = 0; i < get_nrows(); i++){
            for(int j = 0; j < get_ncols(); j++){
                data[i*get_nrows() + j] = get_element(i, j) - A.get_element(i, j);
            }
        }
        return matrix(get_nrows(), get_ncols(), 1, get_nrows(), 0, data);
    }
    else{
        std::cout << "ERRO: As matrizes não possuem as mesmas dimensões" << std::endl;
        return matrix(0, 0, 0, 0, 0, NULL);
    }
}

matrix matrix::operator*(matrix A){
    if(get_ncols() == A.get_nrows()){
        int *data = new int[get_nrows()*A.get_ncols()];
        for(int i = 0; i < get_nrows(); i++){
            for(int j = 0; j < A.get_ncols(); j++){
                data[i*get_nrows() + j] = 0;
                for(int k = 0; k < get_ncols(); k++){
                    data[i*get_nrows() + j] += get_element(i, k)*A.get_element(k, j);
                }
            }
        }
        return matrix(get_nrows(), A.get_ncols(), 1, get_nrows(), 0, data);
    }
    else{
        std::cout << "ERRO: As matrizes não possuem as dimensões corretas para a multiplicação" << std::endl;
        return matrix(0, 0, 0, 0, 0, NULL);
    }
}

matrix matrix::operator/(matrix A){
    if(get_nrows() == A.get_nrows() && get_ncols() == A.get_ncols()){
        int *data = new int[get_nrows()*get_ncols()];
        for(int i = 0; i < get_nrows(); i++){
            for(int j = 0; j < get_ncols(); j++){
                data[i*get_nrows() + j] = get_element(i, j)/A.get_element(i, j);
            }
        }
        return matrix(get_nrows(), get_ncols(), 1, get_nrows(), 0, data);
    }
    else{
        std::cout << "ERRO: As matrizes não possuem as mesmas dimensões" << std::endl;
        return matrix(0, 0, 0, 0, 0, NULL);
    }
}
matrix matrix::operator%(matrix A){
    if(get_nrows() == A.get_nrows() && get_ncols() == A.get_ncols()){
        int *data = new int[get_nrows()*get_ncols()];
        for(int i = 0; i < get_nrows(); i++){
            for(int j = 0; j < get_ncols(); j++){
                data[i*get_nrows() + j] = get_element(i, j)%A.get_element(i, j);
            }
        }
        return matrix(get_nrows(), get_ncols(), 1, get_nrows(), 0, data);
    }
    else{
        std::cout << "ERRO: As matrizes não possuem as mesmas dimensões" << std::endl;
        return matrix(0, 0, 0, 0, 0, NULL);
    }
}
matrix matrix::operator^(matrix A){
    if(get_nrows() == A.get_nrows() && get_ncols() == A.get_ncols()){
        int *data = new int[get_nrows()*get_ncols()];
        for(int i = 0; i < get_nrows(); i++){
            for(int j = 0; j < get_ncols(); j++){
                data[i*get_nrows() + j] = pow(get_element(i, j), A.get_element(i, j));
            }
        }
        return matrix(get_nrows(), get_ncols(), 1, get_nrows(), 0, data);
    }
    else{
        std::cout << "ERRO: As matrizes não possuem as mesmas dimensões" << std::endl;
        return matrix(0, 0, 0, 0, 0, NULL);
    }
}

matrix matrix::operator+=(int value){
    int *data = new int[get_nrows()*get_ncols()];
    for(int i = 0; i < get_nrows(); i++){
        for(int j = 0; j < get_ncols(); j++){
            data[i*get_nrows() + j] = get_element(i, j) + value;
        }
    }
    return matrix(get_nrows(), get_ncols(), 1, get_nrows(), 0, data);
}

matrix matrix::operator-=(int value){
    int *data = new int[get_nrows()*get_ncols()];
    for(int i = 0; i < get_nrows(); i++){
        for(int j = 0; j < get_ncols(); j++){
            data[i*get_nrows() + j] = get_element(i, j) - value;
        }
    }
    return matrix(get_nrows(), get_ncols(), 1, get_nrows(), 0, data);
}
matrix matrix::operator*=(int value){
    int *data = new int[get_nrows()*get_ncols()];
    for(int i = 0; i < get_nrows(); i++){
        for(int j = 0; j < get_ncols(); j++){
            data[i*get_nrows() + j] = get_element(i, j)*value;
        }
    }
    return matrix(get_nrows(), get_ncols(), 1, get_nrows(), 0, data);
}
matrix matrix::operator/=(int value){
    int *data = new int[get_nrows()*get_ncols()];
    for(int i = 0; i < get_nrows(); i++){
        for(int j = 0; j < get_ncols(); j++){
            data[i*get_nrows() + j] = get_element(i, j)/value;
        }
    }
    return matrix(get_nrows(), get_ncols(), 1, get_nrows(), 0, data);
}
matrix matrix::operator%=(int value){
    int *data = new int[get_nrows()*get_ncols()];
    for(int i = 0; i < get_nrows(); i++){
        for(int j = 0; j < get_ncols(); j++){
            data[i*get_nrows() + j] = get_element(i, j)%value;
        }
    }
    return matrix(get_nrows(), get_ncols(), 1, get_nrows(), 0, data);
}
matrix matrix::operator^=(int value){
    int *data = new int[get_nrows()*get_ncols()];
    for(int i = 0; i < get_nrows(); i++){
        for(int j = 0; j < get_ncols(); j++){
            data[i*get_nrows() + j] = pow(get_element(i, j), value);
        }
    }
    return matrix(get_nrows(), get_ncols(), 1, get_nrows(), 0, data);
}

int main(){
    int *aa = new int[9];
    int *bb = new int[9];
    for(int i = 0; i < 9; i++){
        aa[i] = i;
        bb[i] = 9-i;
    }

    matrix AA(3, 3, 0, aa);
    std::cout << "A = " << std::endl;
    matrix BB(3, 3, 0, bb);
    std::cout << "B = " << std::endl;
    matrix CC = AA.concatenate(BB, 1);
    std::cout << "C = A + B = " << std::endl;
    CC.print_matrix();
    return 0;
}

