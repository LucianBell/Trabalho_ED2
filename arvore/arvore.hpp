#ifndef ARVORE_HPP
#define ARVORE_HPP

#include <iostream>
#include <string>
#include <vector>

namespace Arvore {

struct Node {
    std::string nome;
    std::string caminho;
    bool serPasta;
    long long tamanho = 0;
    std::vector<Node*> filhos;
};

// Funções principais da árvore
Node* construirArvore(const std::string& caminho);
void liberarMemoria(Node* node);
void exibirSimples(const Node* node, int nivel = 0);

// Exportação (vai delegar para o HtmlExporter)
void exportarParaHTML(const Node* raiz);

// Busca e análise de arquivos e pastas
void buscarMaiorArquivo(const Node* raiz);
void buscarArquivosMaioresQue(const Node* raiz);
void buscarPastaMaisArquivos(const Node* raiz);
void buscarArquivosPorExtensao(const Node* raiz);
void listarPastasVazias(const Node* raiz);

// Menu interativo
void menuInterativo(Node* raiz);

} // namespace Arvore

#endif // ARVORE_HPP
