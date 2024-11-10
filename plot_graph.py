import matplotlib.pyplot as plt
import numpy as np

# Inicializa listas para armazenar os valores de n e os tempos de execução
n_values = []
execution_times = []
#arquivo = 'fatorial_iterative.csv'
#arquivo = 'fatorial_recursive.csv'
#arquivo = 'fatorial_recursive_heavy.csv'
#arquivo = 'fibonacci_iterative.csv'
arquivo = 'fibonacci_recursive.csv'

#title_graph = 'Fatorial Iterativo'
#title_graph = 'Fatorial Recursivo'
#title_graph = 'Fatorial Recursivo Pesado'
#title_graph = 'Fibonacci Iterativo'
title_graph = 'Fibonacci Recursivo'

# Lê o arquivo CSV e extrai os dados
with open(arquivo, 'r') as file:
    next(file)  # Ignora o cabeçalho
    for line in file:
        n, time = line.strip().split(',')
        n_values.append(int(n))
        # Remove " segundos" e converte para float
        execution_times.append(float(time.replace(" segundos", "")))

# Converte as listas para arrays do numpy para facilitar a manipulação
n_values_np = np.array(n_values)
execution_times_np = np.array(execution_times)

# Ajuste de uma curva de regressão polinomial (exponencial pode ser uma escolha melhor para fatorial)
# Aqui, tentaremos um ajuste de segundo grau como exemplo
coefficients = np.polyfit(n_values_np, execution_times_np, 2)  # Ajuste polinomial de grau 2
polynomial = np.poly1d(coefficients)

# Calcula os valores ajustados
regression_values = polynomial(n_values_np)

# Plota os dados originais e a curva de regressão
plt.figure(figsize=(10, 6))
plt.plot(n_values, execution_times, 'o', label='Dados Medidos', markersize=4)
plt.plot(n_values, regression_values, '-', label='Curva de Regressão', color='red')
plt.xlabel('n (Valor de Entrada)')
plt.ylabel('Tempo de Execução (segundos)')
plt.title(title_graph)
plt.legend()
plt.grid(visible=True, linestyle='--', alpha=0.5)
plt.show()
