import os
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# Diretório onde os arquivos CSV estão localizados
diretorio_dados = './datas'

# Lista dos arquivos CSV que queremos processar
arquivos_csv = [
    'tempos_fatorial_iterativo.csv',
    'tempos_fatorial_recursivo.csv',
    'tempos_fatorial_recursivo_intensivo.csv',
    'tempos_fibonacci_iterativo.csv',
    'tempos_fibonacci_recursivo.csv',
    'tempos_fibonacci_recursivo_intensivo.csv'
]

# Loop para ler cada arquivo e gerar um gráfico
for arquivo in arquivos_csv:
    caminho_arquivo = os.path.join(diretorio_dados, arquivo)

    try:
        # Lê o arquivo CSV
        df = pd.read_csv(caminho_arquivo)
        
        # Identifica a coluna de tempo automaticamente
        col_tempo = [col for col in df.columns if 'tempo' in col]
        
        if not col_tempo:
            print(f"Coluna de tempo não encontrada no arquivo {arquivo}")
            continue
        
        col_tempo = col_tempo[0]  # Seleciona a primeira coluna de tempo encontrada

        # Dados para o gráfico
        x = df['num']
        y = df[col_tempo]

        # Gera o gráfico da função
        plt.figure()
        plt.plot(x, y, marker='o', label='Tempo de execução')
        
        # Calcula e plota a linha de tendência (regressão linear)
        coef = np.polyfit(x, y, 1)  # Ajuste linear
        poly1d_fn = np.poly1d(coef)  # Função de linha de tendência
        plt.plot(x, poly1d_fn(x), '--r', label='Linha de Tendência')

        # Configurações do gráfico
        plt.xlabel('Número')
        plt.ylabel('Tempo (segundos)')
        plt.title(f'Tempo de execução - {arquivo}')
        plt.legend()
        plt.grid(True)

        # Salva o gráfico como imagem
        nome_grafico = os.path.splitext(arquivo)[0] + '.png'
        caminho_grafico = os.path.join(diretorio_dados, nome_grafico)
        plt.savefig(caminho_grafico)
        plt.close()
        
        print(f"Gráfico com linha de tendência salvo como {caminho_grafico}")
        
    except FileNotFoundError:
        print(f"Arquivo {caminho_arquivo} não encontrado.")
    except Exception as e:
        print(f"Ocorreu um erro ao processar {caminho_arquivo}: {e}")
