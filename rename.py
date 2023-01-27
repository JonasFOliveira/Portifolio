#Criando um script para renomear os arquivos do diretorio de datasets

import os

datas = os.listdir('datasets')
# Verificando todos os diretorios do datasets
for data in datas:
    files = os.listdir('datasets/' + data)
    # Verificando todos os arquivos do diretorio de dataset
    for file in files:
        print(file)
        if file.startswith(data):
            break
        os.rename('datasets/'+data+'/'+file, 'datasets/'+data+'/'+data+'_'+file)
        # Renomeando os arquivos do diretorio de dataset
        # Nome do arquivo = Nome do diretorio_Nome do arquivo

