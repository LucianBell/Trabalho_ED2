#include "arvore.hpp"
#include "../utils/HtmlExporter.hpp"
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <cstring>
#include <fstream>

namespace Arvore {

// Função recursiva que constrói a árvore a partir do diretório inicial
Node* construirArvore(const std::string& caminho) {
    Node* node = new Node;
    node->caminho = caminho;

    struct stat info;
    // Obtém informações do arquivo/diretório
    if (stat(caminho.c_str(), &info) == -1) {
        perror(("Erro ao acessar: " + caminho).c_str());
        delete node;
        return nullptr;
    }

    node->serPasta = S_ISDIR(info.st_mode);
    node->nome = caminho.substr(caminho.find_last_of("/") + 1);

    // Se for arquivo, salva o tamanho e retorna
    if (!node->serPasta) {
        node->tamanho = info.st_size;
        return node;
    }

    // Caso seja pasta, abre o diretório
    DIR* dir = opendir(caminho.c_str());
    if (!dir) {
        perror(("Erro ao abrir diretório: " + caminho).c_str());
        delete node;
        return nullptr;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        std::string nome = entry->d_name;
        // Ignora as pastas especiais "." e ".."
        if (nome == "." || nome == "..") continue;

        std::string novoCaminho = caminho + "/" + nome;
        // Ignora tipos que não sejam arquivos ou diretórios
        if (entry->d_type != DT_REG && entry->d_type != DT_DIR) continue;

        // Processa o filho e adiciona no vetor de filhos
        Node* filho = construirArvore(novoCaminho);
        if (filho) {
            node->filhos.push_back(filho);
            node->tamanho += filho->tamanho;
        }
    }

    closedir(dir);
    return node;
}

// Libera a memória da árvore de forma recursiva
void liberarMemoria(Node* node) {
    for (auto filho : node->filhos) {
        liberarMemoria(filho);
    }
    delete node;
}

// Exibe a árvore de forma simples e indentada
void exibirSimples(const Node* node, int nivel) {
    for (int i = 0; i < nivel; ++i) std::cout << "  ";

    if (node->serPasta) {
        std::cout << "[Pasta] " << node->nome
                  << " (" << node->filhos.size() << " filhos, "
                  << node->tamanho << " bytes)\n";
    } else {
        std::cout << "[Arquivo] " << node->nome
                  << " (" << node->tamanho << " bytes)\n";
    }

    for (const auto& filho : node->filhos) {
        exibirSimples(filho, nivel + 1);
    }
}

// Função auxiliar para buscar o maior arquivo recursivamente
void buscarMaiorArquivoRecursivo(const Node* node, const Node*& maior) {
    if (!node) return;

    if (!node->serPasta && (!maior || node->tamanho > maior->tamanho)) {
        maior = node;
    }

    for (const auto& filho : node->filhos) {
        buscarMaiorArquivoRecursivo(filho, maior);
    }
}

// Busca e exibe o maior arquivo da árvore
void buscarMaiorArquivo(const Node* raiz) {
    const Node* maior = nullptr;
    buscarMaiorArquivoRecursivo(raiz, maior);

    if (maior) {
        std::cout << "Maior arquivo encontrado\n";
        std::cout << "Nome: " << maior->nome << "\n";
        std::cout << "Caminho: " << maior->caminho << "\n";
        std::cout << "Tamanho: " << maior->tamanho << " bytes\n";
    } else {
        std::cout << "Nenhum arquivo encontrado.\n";
    }
}

// Busca arquivos maiores que um determinado tamanho
void buscarArquivosMaioresQueRecursivo(const Node* node, long long n) {
    if (!node) return;

    if (!node->serPasta && node->tamanho > n) {
        std::cout << "Arquivo: " << node->nome << "\n";
        std::cout << "Caminho: " << node->caminho << "\n";
        std::cout << "Tamanho: " << node->tamanho << " bytes.\n\n";
    }

    for (const auto& filho : node->filhos) {
        buscarArquivosMaioresQueRecursivo(filho, n);
    }
}

void buscarArquivosMaioresQue(const Node* raiz) {
    long long n;
    std::cout << "Digite o valor N (bytes): ";
    std::cin >> n;
    std::cin.ignore();

    std::cout << "\nArquivos maiores que " << n << " bytes:\n";
    buscarArquivosMaioresQueRecursivo(raiz, n);
}

// Função auxiliar para buscar a pasta com mais arquivos diretos
void buscarPastaMaisArquivosRecursivo(const Node* node, const Node*& melhor, size_t& maxFilhos) {
    if (!node || !node->serPasta) return;

    if (node->filhos.size() > maxFilhos) {
        maxFilhos = node->filhos.size();
        melhor = node;
    }

    for (const auto& filho : node->filhos) {
        buscarPastaMaisArquivosRecursivo(filho, melhor, maxFilhos);
    }
}

// Busca e exibe a pasta com mais arquivos diretos
void buscarPastaMaisArquivos(const Node* raiz) {
    const Node* melhor = nullptr;
    size_t maxFilhos = 0;
    buscarPastaMaisArquivosRecursivo(raiz, melhor, maxFilhos);

    if (melhor) {
        std::cout << "Pasta com mais arquivos diretos:\n";
        std::cout << "Nome: " << melhor->nome << "\n";
        std::cout << "Caminho: " << melhor->caminho << "\n";
        std::cout << "Quantidade de filhos diretos: " << maxFilhos << "\n";
    } else {
        std::cout << "Nenhuma pasta encontrada.\n";
    }
}

// Verifica se o nome do arquivo possui a extensão informada
bool temExtensao(const std::string& nome, const std::string& extensao) {
    if (extensao.size() > nome.size()) return false;
    return nome.substr(nome.size() - extensao.size()) == extensao;
}

// Busca arquivos com determinada extensão
void buscarArquivosPorExtensaoRecursivo(const Node* node, const std::string& extensao) {
    if (!node) return;

    if (!node->serPasta && temExtensao(node->nome, extensao)) {
        std::cout << "Arquivo: " << node->nome << " - Caminho: " << node->caminho << "\n";
    }

    for (const auto& filho : node->filhos) {
        buscarArquivosPorExtensaoRecursivo(filho, extensao);
    }
}

void buscarArquivosPorExtensao(const Node* raiz) {
    std::string entrada;
    std::cout << "Digite a extensão (ex: txt ou .txt): ";
    std::getline(std::cin, entrada);

    std::string extensao = (entrada[0] == '.') ? entrada : "." + entrada;

    std::cout << "Arquivos com extensão '" << extensao << "':\n";
    buscarArquivosPorExtensaoRecursivo(raiz, extensao);
}

// Lista todas as pastas vazias na árvore
void listarPastasVaziasRecursivo(const Node* node) {
    if (!node) return;

    if (node->serPasta && node->filhos.empty()) {
        std::cout << "Pasta vazia: " << node->nome << " - Caminho: " << node->caminho << "\n";
    }

    for (const auto& filho : node->filhos) {
        listarPastasVaziasRecursivo(filho);
    }
}

void listarPastasVazias(const Node* raiz) {
    std::cout << "Pastas vazias encontradas:\n";
    listarPastasVaziasRecursivo(raiz);
}

// Menu interativo para escolher as funcionalidades
void menuInterativo(Node* raiz) {
    int opcao;
    do {
        std::cout << "\n--- Menu ---\n";
        std::cout << "1. Exibir árvore completa\n";
        std::cout << "2. Exportar a árvore para HTML\n";
        std::cout << "3. Buscar o maior arquivo\n";
        std::cout << "4. Arquivos maiores que N bytes\n";
        std::cout << "5. Pasta com mais arquivos diretos\n";
        std::cout << "6. Buscar arquivos por extensão\n";
        std::cout << "7. Listar pastas vazias\n";
        std::cout << "0. Sair\n";
        std::cin >> opcao;
        std::cin.ignore();

        // Executa a opção escolhida
        switch (opcao) {
            case 1: exibirSimples(raiz); break;
            case 2: ::exportarParaHTML(raiz); break;
            case 3: buscarMaiorArquivo(raiz); break;
            case 4: buscarArquivosMaioresQue(raiz); break;
            case 5: buscarPastaMaisArquivos(raiz); break;
            case 6: buscarArquivosPorExtensao(raiz); break;
            case 7: listarPastasVazias(raiz); break;
            case 0: std::cout << "Encerrando.\n"; break;
            default: std::cout << "Opção inválida!\n";
        }
    } while (opcao != 0);
}

} // namespace Arvore
