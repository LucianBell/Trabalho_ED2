#include <iostream>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <cstring>

using namespace std;

namespace Arvore { //Namespace para organizar o código relacionado à árvore
    
    struct Node { //Representação do nó da árvore
        string nome; //Do arquivo ou pasta
        string caminho; // (ex: "/home/usuario/arquivo.txt")
        bool serPasta; //true para pasta e false para arquivo
        long long tamanho = 0; // tamanho do arquivo ou soma do tamanho dos filhos
        vector<Node*> filhos; //Vários filhos implicam em um vetor de filhos
    };

    // Função para liberar a memória alocada 
    void liberarMemoria(Node* node) {
        for (auto filho : node->filhos) {
            liberarMemoria(filho);  //chama a função de forma recursiva para o filho
        }
        delete node; //Depois de passar pelos filhos deleta o nodo
    }
    // Função para exibir a estrutura da árvore com nome e tamanho
    void exibirSimples(const Node* node, int nivel = 0) {
        // Imprime a indentação de acordo com o nível da árvore
        for (int i = 0; i < nivel; ++i) cout << "  ";

        // Exibe nome, tipo e tamanho
        if (node->serPasta) {
            cout << "[Pasta] " << node->nome 
                << " (" << node->filhos.size() << " filhos, "
                << node->tamanho << " bytes)" << endl;
        } else {
            cout << "[Arquivo] " << node->nome 
                << " (" << node->tamanho << " bytes)" << endl;
        }

        // Exibe os filhos (subpastas ou arquivos dentro da pasta)
        for (const auto& filho : node->filhos) {
            exibirSimples(filho, nivel + 1);
        }
    }

    Node* construirArvore(const string& caminho){
        Node* node = new Node;
        node->caminho = caminho;

        struct stat info;
        if(stat(caminho.c_str(), &info) == -1){
            perror(("Erro ao acessar: " + caminho).c_str());
            delete node;
            return nullptr;
        }
        node->serPasta = S_ISDIR(info.st_mode);
        node->nome = caminho.substr(caminho.find_last_of("/")+1);

        if(!node->serPasta){
            node->tamanho = info.st_size;
            return node;
    }
        DIR* dir = opendir(caminho.c_str());
        if(!dir){
            perror(("Erro ao abrir diretório: " + caminho).c_str());
            delete node;
            return nullptr;
        }
        struct dirent* entry;
        while ((entry = readdir(dir)) != nullptr){
            string nome = entry->d_name;
            if (nome == "." || nome == "..") continue;

            string novoCaminho = caminho + "/" + nome;

            if (entry->d_type != DT_REG && entry->d_type != DT_DIR) continue;

            Node* filho = construirArvore(novoCaminho);
            if(filho){
                node->filhos.push_back(filho);
                node->tamanho += filho->tamanho;
            }
        }
        closedir(dir);
        return node;

    }
}

int main(int argc, char* argv[]){
    string diretorioInicial = (argc > 1) ? argv[1] : ".";

    cout << "Diretório inicial: " << diretorioInicial << endl;

    using namespace Arvore;

    Node* raiz = construirArvore(diretorioInicial);
    if(raiz){
        exibirSimples(raiz);
        liberarMemoria(raiz);
    }
    return 0;
}
