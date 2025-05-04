#include "arvore/arvore.hpp"
#include <unistd.h>
#include <limits.h>
#include <iostream>
#include <string>

// Retorna o caminho absoluto de um diretório ou arquivo
std::string obterCaminhoAbsoluto(const std::string& caminho) {
    char resolved_path[PATH_MAX];
    
    // Usa realpath para resolver "." e ".." e obter o caminho completo
    if (realpath(caminho.c_str(), resolved_path) != nullptr) {
        return std::string(resolved_path);
    } else {
        // Se não conseguir resolver (por exemplo, se o caminho não existir), retorna o caminho original
        // tratamento de erros para caso onde temos uma pasta inexistente já é feito em arvore.cpp
        return caminho;
    }
}

int main(int argc, char* argv[]) {
    std::string diretorioInicial = (argc > 1) ? argv[1] : ".";

    // Garante que o caminho é absoluto para evitar confusões na exibição
    diretorioInicial = obterCaminhoAbsoluto(diretorioInicial);

    std::cout << "Diretório inicial: " << diretorioInicial << std::endl;

    using namespace Arvore;

    // Constrói a árvore de arquivos e pastas a partir do diretório inicial
    Node* raiz = construirArvore(diretorioInicial);
    
    if (raiz) {
        // Exibe o menu para o usuário interagir com as opções disponíveis
        menuInterativo(raiz);
        
        // Libera toda a memória alocada pela árvore
        liberarMemoria(raiz);
    }

    return 0;
}
