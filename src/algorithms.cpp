#include "algorithms.hpp"
#include <iostream>

// Definição da função consume_resources
void consume_resources() {
    for (int i = 0; i < 1000000; i++) {
        std::sin(123.456); // Calcula o seno de um número várias vezes
    }
}

// Implementação de Fatorial Recursivo
unsigned long long factorial_recursive(int n) {
    if (n <= 1)
        return 1;
    return n * factorial_recursive(n - 1);
}

// Implementação de Fatorial Iterativo
unsigned long long factorial_iterative(int n) {
    unsigned long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

// Implementação de Fatorial Recursivo com Consumo de Recursos
unsigned long long factorial_recursive_heavy(int n) {
    if (n <= 1)
        return 1;
    consume_resources(); // Consome recursos em cada chamada recursiva
    return n * factorial_recursive_heavy(n - 1);
}

// Implementação de Fibonacci Recursivo
unsigned long long fibonacci_recursive(int n) {
    if (n <= 1)
        return n;
    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}

// Implementação de Fibonacci Iterativo
unsigned long long fibonacci_iterative(int n) {
    if (n <= 1)
        return n;

    unsigned long long a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

/* // Implementação de Fibonacci Recursivo com Consumo de Recursos
unsigned long long fibonacci_recursive_heavy(int n) {
    if (n <= 1)
        return n;
    consume_resources(); // Consome recursos em cada chamada recursiva
    return fibonacci_recursive_heavy(n - 1) + fibonacci_recursive_heavy(n - 2);
} */
