#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <sys/resource.h>
#include "algorithms.hpp" // Assumindo que todas as funções estão implementadas nesse arquivo.

struct ResourceUsage {
    double user_time;
    double system_time;
};

ResourceUsage measure_resources() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);

    double user_time = usage.ru_utime.tv_sec + usage.ru_utime.tv_usec / 1e6;
    double system_time = usage.ru_stime.tv_sec + usage.ru_stime.tv_usec / 1e6;

    return {user_time, system_time};
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <numero_maximo>" << std::endl;
        return 1;
    }

    int max_num = std::stoi(argv[1]);

    if (max_num < 1) {
        std::cerr << "O valor de numero_maximo deve ser um inteiro positivo." << std::endl;
        return 1;
    }

    // Cria arquivos CSV separados para cada função
    std::ofstream file_iter_factorial("./datas/tempos_fatorial_iterativo.csv");
    std::ofstream file_rec_factorial("./datas/tempos_fatorial_recursivo.csv");
    std::ofstream file_rec_heavy_factorial("./datas/tempos_fatorial_recursivo_intensivo.csv");
    std::ofstream file_iter_fibonacci("./datas/tempos_fibonacci_iterativo.csv");
    std::ofstream file_rec_fibonacci("./datas/tempos_fibonacci_recursivo.csv");
    std::ofstream file_rec_heavy_fibonacci("./datas/tempos_fibonacci_recursivo_intensivo.csv");

    // Escreve cabeçalhos em cada arquivo
    file_iter_factorial << "num,tempo_funcao,tempo_usuario,tempo_sistema\n";
    file_rec_factorial << "num,tempo_funcao,tempo_usuario,tempo_sistema\n";
    file_rec_heavy_factorial << "num,tempo_funcao,tempo_usuario,tempo_sistema\n";
    file_iter_fibonacci << "num,tempo_funcao,tempo_usuario,tempo_sistema\n";
    file_rec_fibonacci << "num,tempo_funcao,tempo_usuario,tempo_sistema\n";
    file_rec_heavy_fibonacci << "num,tempo_funcao,tempo_usuario,tempo_sistema\n";

    for (int num = 1; num <= max_num; ++num) {
        unsigned long long result = 0;
        ResourceUsage res_usage;

        // Fatorial iterativo
        auto start = std::chrono::high_resolution_clock::now();
        result = factorial_iterative(num);
        auto end = std::chrono::high_resolution_clock::now();
        double duration_iter_factorial = std::chrono::duration<double>(end - start).count();
        res_usage = measure_resources();
        file_iter_factorial << num << "," << duration_iter_factorial << "," << res_usage.user_time << "," << res_usage.system_time << "\n";

        // Fatorial recursivo
        start = std::chrono::high_resolution_clock::now();
        result = factorial_recursive(num);
        end = std::chrono::high_resolution_clock::now();
        double duration_rec_factorial = std::chrono::duration<double>(end - start).count();
        res_usage = measure_resources();
        file_rec_factorial << num << "," << duration_rec_factorial << "," << res_usage.user_time << "," << res_usage.system_time << "\n";

        // Fatorial recursivo intensivo
        start = std::chrono::high_resolution_clock::now();
        result = factorial_recursive_heavy(num);
        end = std::chrono::high_resolution_clock::now();
        double duration_rec_heavy_factorial = std::chrono::duration<double>(end - start).count();
        res_usage = measure_resources();
        file_rec_heavy_factorial << num << "," << duration_rec_heavy_factorial << "," << res_usage.user_time << "," << res_usage.system_time << "\n";

        // Fibonacci iterativo
        start = std::chrono::high_resolution_clock::now();
        result = fibonacci_iterative(num);
        end = std::chrono::high_resolution_clock::now();
        double duration_iter_fibonacci = std::chrono::duration<double>(end - start).count();
        res_usage = measure_resources();
        file_iter_fibonacci << num << "," << duration_iter_fibonacci << "," << res_usage.user_time << "," << res_usage.system_time << "\n";

        // Fibonacci recursivo
        start = std::chrono::high_resolution_clock::now();
        result = fibonacci_recursive(num);
        end = std::chrono::high_resolution_clock::now();
        double duration_rec_fibonacci = std::chrono::duration<double>(end - start).count();
        res_usage = measure_resources();
        file_rec_fibonacci << num << "," << duration_rec_fibonacci << "," << res_usage.user_time << "," << res_usage.system_time << "\n";

        // Fibonacci recursivo intensivo
        start = std::chrono::high_resolution_clock::now();
        result = fibonacci_recursive_heavy(num);
        end = std::chrono::high_resolution_clock::now();
        double duration_rec_heavy_fibonacci = std::chrono::duration<double>(end - start).count();
        res_usage = measure_resources();
        file_rec_heavy_fibonacci << num << "," << duration_rec_heavy_fibonacci << "," << res_usage.user_time << "," << res_usage.system_time << "\n";
    }

    // Fecha todos os arquivos
    file_iter_factorial.close();
    file_rec_factorial.close();
    file_rec_heavy_factorial.close();
    file_iter_fibonacci.close();
    file_rec_fibonacci.close();
    file_rec_heavy_fibonacci.close();

    std::cout << "Resultados gravados em arquivos CSV separados.\n";

    return 0;
}
