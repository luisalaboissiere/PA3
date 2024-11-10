#include <iostream>
#include <cstring>
#include <ctime>
#include <sys/resource.h>
#include "algorithms.hpp"

void measure_resources() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);

    std::cout << "Tempo de usuário: "
              << usage.ru_utime.tv_sec + usage.ru_utime.tv_usec / 1e6
              << " segundos" << std::endl;

    std::cout << "Tempo de sistema: "
              << usage.ru_stime.tv_sec + usage.ru_stime.tv_usec / 1e6
              << " segundos" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Uso: " << argv[0] << " [fatorial|fibonacci] <n>" << std::endl;
        return 1;
    }

    std::string operation = argv[1];
    int n = std::stoi(argv[2]);

    if (n < 0) {
        std::cerr << "O valor de n deve ser um inteiro não negativo." << std::endl;
        return 1;
    }

    // Mapeia a operação para um código inteiro
    int op_code;
    if (operation == "fatorial") {
        op_code = 1;
    } else if (operation == "fibonacci") {
        op_code = 2;
    } else {
        std::cerr << "Operação desconhecida: " << operation << std::endl;
        return 1;
    }

    // Medição do tempo de relógio
    clock_t start = clock();
    unsigned long long result = 0;

    // Usa switch para selecionar a operação
    switch (op_code) {
        case 1:
            //result = factorial_recursive(n);
            result = factorial_iterative(n);
            // Para medir a versão pesada, descomente a linha abaixo
            // result = factorial_recursive_heavy(n);
            break;
        case 2:
            //result = fibonacci_recursive(n);
            result = fibonacci_iterative(n);
            // Para medir a versão pesada, descomente a linha abaixo
            // result = fibonacci_recursive_heavy(n);
            break;
        default:
            std::cerr << "Erro inesperado." << std::endl;
            return 1;
    }

    clock_t end = clock();
    double time_taken = double(end - start) / CLOCKS_PER_SEC;

    std::cout << "Resultado: " << result << std::endl;
    std::cout << "Tempo de execução (relógio): " << time_taken << " segundos" << std::endl;

    // Medição do uso de recursos (tempo de usuário e sistema)
    measure_resources();

    return 0;
}
