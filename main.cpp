#include <iostream>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <cstring>
#include <fstream>

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
    void exportarHTMLRecursivo(ofstream& out, const Node* node, int nivel = 0){
        for(int i = 0; i < nivel; i++) out << "&nbsp;&nbsp;&nbsp;&nbsp;";
        out << (node->serPasta ? "[Pasta]" : "[Arquivo]") << node->nome;
        out << " (" << node->tamanho << "bytes)";
        if (node->serPasta) out << " [" << node->filhos.size() << "filhos]";
        out << "<br>\n";

        for (const auto& filho : node->filhos) {
            exportarHTMLRecursivo(out, filho, nivel + 1);
        }
        }

    void exportarParaHTML(const Node* raiz){
        ofstream out("arvore.html");
        if (!out) {
            cerr << "Erro ao criar arquivo HTML.\n";
            return;
        }
        out << "<html><body><pre>\n";
        exportarHTMLRecursivo(out, raiz);
        out << "</pre></body></html>\n";
        out.close();
        cout << "Estrutura exportada para 'arvore.html'\n";
        }

    void buscarMaiorArquivoRecursivo(const Node* node, const Node*& maior){
        if (!node) return;

        if (!node->serPasta){
            if(!maior || node->tamanho >maior->tamanho){
                maior = node;
            }
        }

        for (const auto& filho : node->filhos){
            buscarMaiorArquivoRecursivo(filho, maior);
        }
    }

    void buscarMaiorArquivo(const Node* raiz){
        const Node* maior = nullptr;
        buscarMaiorArquivoRecursivo(raiz, maior);

        if(maior){
            cout << "Maior arquivo encontrado \n";
            cout << "Nome: " << maior->nome << endl;
            cout << "Caminho: " << maior->caminho << endl;
            cout << "Tamanho: " << maior->tamanho << " bytes\n";
        }else{
            cout << "Nenhum arquivo encontrado.\n";
        }

    }
    void buscarArquivosMaioresQueRecursivo(const Node* node, long long n){
        if(!node) return;

        if(!node->serPasta && node->tamanho > n){
            cout << "Arquivo: " << node->nome << endl;
            cout << "Caminho: " << node->caminho << endl;
            cout << "Tamanho: " << node->tamanho << " bytes.\n\n";
        }
        for (const auto& filho : node->filhos){
            buscarArquivosMaioresQueRecursivo(filho, n);
        }
    }
    void buscarArquivosMaioresQue(const Node* raiz){
        long long n;
        cout << "Digite o valor N (bytes): " << endl;
        cin >> n;
        cin.ignore();

        cout << "\nArquivos maiores que " << n << " bytes:\n";
        cout << "---------------------------------\n";
        buscarArquivosMaioresQueRecursivo(raiz,n);
    }
    void buscarPastaMaisArquivosRecursivo(const Node* node, const Node*& melhor, size_t& maxFilhos){
        if (!node || !node->serPasta) return;

        if (node->filhos.size() > maxFilhos){
            maxFilhos = node->filhos.size();
            melhor = node;
        }

        for (const auto& filho : node->filhos){
            buscarPastaMaisArquivosRecursivo(filho, melhor, maxFilhos);
        }
    }
    void buscarPastaMaisArquivos(const Node* raiz){
        const Node* melhor = nullptr;
        size_t maxFilhos = 0;

        buscarPastaMaisArquivosRecursivo(raiz, melhor, maxFilhos);

        if(melhor){
            cout << "Pasta com mais arquivos diretos: \n";
            cout << "Nome: " << melhor->nome << endl;
            cout << "Caminho: " << melhor->caminho << endl;
            cout << "Quantidade de filhos diretos: " << maxFilhos << endl;
        }else{
            cout << "Nenhuma pasta encontrada.\n";
        }

    }
    bool temExtensao(const string& nome, const string& extensao){
        if (extensao.size() > nome.size()) return false;
        return nome.substr(nome.size() - extensao.size()) == extensao;
    }
    void buscarArquivosPorExtensaoRecursivo(const Node* node, const string& extensao){
        if (!node) return;

        if(!node->serPasta && temExtensao(node->nome, extensao)){
            cout << "Arquivo: " << node->nome << " - Caminho: " << node->caminho << endl;
        }

        for(const auto& filho : node->filhos){
            buscarArquivosPorExtensaoRecursivo(filho, extensao);
        }
    }
    void buscarArquivosPorExtensao(const Node* raiz){
        string entrada;
        cout << "Digite a extensão (ex:txt, ou .txt): ";
        getline(cin, entrada);

        //Certificando que haverá um "." antes da extensão
        string extensao = (entrada[0] == '.') ? entrada : "." + entrada;

        cout << "Arquivos com extensão '" << extensao << "':\n";
        buscarArquivosPorExtensaoRecursivo(raiz,extensao);

    }void listarPastasVaziasRecursivo(const Node* node){
        if (!node) return;

        if(node->serPasta && node->filhos.empty()){
            cout << "Pasta vazia: " << node->nome << " - Caminho: " << node->caminho << endl;
        }

        for(const auto& filho : node->filhos){
            listarPastasVaziasRecursivo(filho);
        }
    }
    void listarPastasVazias(const Node* raiz){
        cout << "Pastas vazias encontradas:\n";
        listarPastasVaziasRecursivo(raiz);
    }

    void menuInterativo(Node* raiz){
        int opcao;
        do {
            cout << "\n---Menu---\n";
            cout << "1. Exibir árvore completa\n";
            cout << "2. Exportar a árvore para HTML\n";
            cout << "3. Buscar o maior arquivo\n";
            cout << "4. Arquivos maiores que N bytes\n";
            cout << "5. Pasta com mais arquivos diretos\n";
            cout << "6. Buscar arquivos por extensão \n";
            cout << "7. Listar pastas vazias \n";
            cout << "0. Sair \n";
            cin >> opcao;
            cin.ignore();

            switch (opcao){
                case 1: exibirSimples(raiz); break;
                case 2: exportarParaHTML(raiz); break;
                case 3: buscarMaiorArquivo(raiz); break;
                case 4: buscarArquivosMaioresQue(raiz); break;
                case 5: buscarPastaMaisArquivos(raiz); break;
                case 6: buscarArquivosPorExtensao(raiz); break;
                case 7: listarPastasVazias(raiz); break;
                case 0: cout << "Encerrando. \n"; break;
                default: cout << "Opção inválida! \n";
            }
        } while(opcao!=0);

    }

}

int main(int argc, char* argv[]){
    string diretorioInicial = (argc > 1) ? argv[1] : ".";

    cout << "Diretório inicial: " << diretorioInicial << endl;

    using namespace Arvore;

    Node* raiz = construirArvore(diretorioInicial);
    if(raiz){
        menuInterativo(raiz);
        liberarMemoria(raiz);
    }
    return 0;
}
