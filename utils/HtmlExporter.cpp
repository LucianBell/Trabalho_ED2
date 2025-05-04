#include "HtmlExporter.hpp"
#include <iostream>

// Função recursiva para exportar a árvore no formato HTML
static void exportarHTMLRecursivo(std::ofstream& out, const Arvore::Node* node, int nivel = 0) {
    // Adiciona indentação no HTML para representar a hierarquia da árvore
    for (int i = 0; i < nivel; ++i) out << "&nbsp;&nbsp;&nbsp;&nbsp;";

    // Escreve as informações do nó atual (pasta ou arquivo)
    out << (node->serPasta ? "[Pasta] " : "[Arquivo] ") << node->nome;
    out << " (" << node->tamanho << " bytes)";
    
    // Se for pasta, também mostra quantos filhos diretos ela possui
    if (node->serPasta) out << " [" << node->filhos.size() << " filhos]";
    
    out << "<br>\n";

    // Chama recursivamente para cada filho
    for (const auto& filho : node->filhos) {
        exportarHTMLRecursivo(out, filho, nivel + 1);
    }
}

// Exporta a árvore completa para um arquivo HTML
void exportarParaHTML(const Arvore::Node* raiz) {
    std::ofstream out("arvore.html");

    // Verifica se o arquivo foi aberto com sucesso
    if (!out) {
        std::cerr << "Erro ao criar o arquivo HTML.\n";
        return;
    }

    // Escreve o cabeçalho básico do HTML
    out << "<html><body><pre>\n";
    
    // Chama a função recursiva para adicionar o conteúdo da árvore
    exportarHTMLRecursivo(out, raiz);
    
    // Finaliza o HTML
    out << "</pre></body></html>\n";
    out.close();

    std::cout << "Estrutura exportada para 'arvore.html'\n";
}
