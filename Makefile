# Compilador
CXX = g++
# Flags de compilação
CXXFLAGS = -std=c++11 -pg -Iinclude  # Adiciona -pg para profiling

# Pastas
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INCLUDE_DIR = include

# Arquivos
SRC_FILES = $(SRC_DIR)/main.cpp $(SRC_DIR)/algorithms.cpp
OBJ_FILES = $(OBJ_DIR)/main.o $(OBJ_DIR)/algorithms.o
EXECUTABLE = $(BIN_DIR)/main

# Regra padrão
all: $(EXECUTABLE)

# Regra para criar o executável
$(EXECUTABLE): $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJ_FILES) -o $(EXECUTABLE)
	@echo "Executável criado em $(BIN_DIR)"

# Regras para criar os arquivos de objeto
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp $(INCLUDE_DIR)/algorithms.hpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/main.cpp -o $(OBJ_DIR)/main.o

$(OBJ_DIR)/algorithms.o: $(SRC_DIR)/algorithms.cpp $(INCLUDE_DIR)/algorithms.hpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/algorithms.cpp -o $(OBJ_DIR)/algorithms.o

# Regra para gerar os tempos de execução com gprof para uma entrada grande
profile: $(EXECUTABLE)
	@echo "Executando com entrada grande (20)..."
	./$(EXECUTABLE) 20 > /dev/null
	@echo "Gerando relatório do gprof..."
	gprof $(EXECUTABLE) gmon.out > gprof_output.txt
	@echo "Relatório gerado em gprof_output.txt"

# Limpeza
clean:
	rm -rf $(OBJ_DIR)/*.o $(BIN_DIR)/main gmon.out gprof_output.txt
	@echo "Arquivos de objeto, executável e dados removidos"

.PHONY: all clean profile
