#include "arvore.hpp"
#include <fstream>
#include <sstream>
//Começo da implementação da função exportarComoHTML
namespace Arvore {

// Função auxiliar para gerar HTML recursivamente
void gerarHTML(const Node* node, std::ostream& out) {
    if (!node) return;

    out << "<li>";
    
    // Indica se é pasta ou arquivo
    if (node->serPasta) {
        out << "[PASTA] ";
    } else {
        out << "[ARQUIVO] ";
    }

    out << node->nome;

    // Se for pasta e tiver filhos, começa uma nova lista
    if (node->serPasta && !node->filhos.empty()) {
        out << "\n<ul>\n";
        for (const Node* filho : node->filhos) {
            gerarHTML(filho, out);  // Recursão
        }
        out << "</ul>\n";
    }

    out << "</li>\n";
}

void exportarComoHTML(const Node* raiz) {
    if (!raiz) return;

    std::ofstream arquivo("estrutura.html");
    if (!arquivo) {
        std::cerr << "Erro ao criar o arquivo HTML.\n";
        return;
    }

    arquivo << "<!DOCTYPE html>\n<html>\n<head>\n<meta charset=\"UTF-8\">\n";
    arquivo << "<title>Estrutura de Diretórios</title>\n";
    arquivo << "<style>\n";
    arquivo << "ul { list-style-type: none; }\n";
    arquivo << "li { margin: 4px 0; }\n";
    arquivo << "</style>\n";
    arquivo << "</head>\n<body>\n";
    arquivo << "<h1>Estrutura de Diretórios</h1>\n";
    arquivo << "<ul>\n";

    gerarHTML(raiz, arquivo);

    arquivo << "</ul>\n</body>\n</html>\n";
    arquivo.close();

    std::cout << "Exportação concluída. Arquivo gerado: estrutura.html\n";
}

} // namespace Arvore
