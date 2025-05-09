# Trabalho_ED2
Trabalho de estrutura de dados II do Mestre Jedi Dr. Brusso

# Como rodar o programa:
## Compilação
- Abra o terminal e execute o seguinte comando (considerando que estamos usando gcc):
`
 g++ main.cpp arvore/*.cpp utils/*.cpp -o programa.o
`

# Casos de teste
- Listando alguns casos de teste do programa, separando-os por categoria.
- Lógica da apresentação dos pontos:
    - **Checkbox desmarcada:** não testado;
    - **Checkbox marcada:** testado e aprovado;
    - **Checkbox desmarcada + warning após header:** testado com erro -> correção necessária.

## 📦 Carregamento Inicial

- [x] Rodar sem argumento → carregar diretório atual
- [x] Rodar com diretório existente → carregar e exibir corretamente
- [x] Rodar com diretório inexistente → mostrar erro e não travar
- [x] Rodar em diretório com links/dispositivos/sockets → ignorar corretamente
- [x] Tentar abrir em arquivo -> retornar erro?

---

## 🌳 Exibir Árvore Completa
> :warning: **Ponto de melhora: ordenar melhor os itens e pastas, fazendo por ordem alfabética.**

- [x] Exibir arquivos com nome e tamanho corretos
- [x] Exibir pastas com nome, número de filhos diretos e tamanho acumulado corretos
- [x] Exibir subpastas com indentação adequada
- [x] Exibir pastas vazias corretamente (0 filhos)

---

## 🌐 Exportar Árvore para HTML

- [x] Exportar árvore pequena → HTML com indentação correta
- [x] Exportar árvore grande → HTML mantendo estrutura correta
- [x] Exportar árvore com pastas vazias → HTML mostra as pastas vazias

---

## 🔍 Pesquisas

### 3.1 Maior Arquivo
> ~~:warning: **Erro encontrado quando dois arquivos tem o mesmo tamanho (apenas o último é listado)**~~
> ✔ Resolvido

- [x] Encontrar e exibir o maior arquivo corretamente
- [x] Empate entre dois ou mais arquivos → listar todos

### 3.2 Arquivos com mais do que N bytes
> ~~:warning: Ponto de melhora: podemos colocar uma mensagem personalizada quando N maior que todos~~
> ✔ Resolvido

- [x] N menor que todos → listar todos
- [x] N maior que todos → listar nenhum
- [x] N intermediário → listar arquivos corretos

### 3.3 Pasta com mais arquivos diretos
> ¿: **Será que devemos considerar a pasta buscada/raíz junto nessa operação?**
> ¿: **O que fazer quando temos duas pastas com a mesma quantidade de arquivos/pastas?**

- [x] Identificar a pasta com mais arquivos diretos corretamente
- [x] Empate entre pastas → escolher ou listar qualquer uma de forma estável

### 3.4 Arquivos por extensão
> ~~:warning: **Ponto de melhora: Criar uma saída padrão para quando nenhum arquivo com aquela extensão é encontrado**~~
> ✔ Resolvido
- [x] Buscar por `.txt` → listar arquivos corretos
- [x] Buscar por extensão inexistente → não listar nada
- [x] Buscar com e sem ponto (`txt` e `.txt`) → funcionar em ambos os casos

### 3.5 Pastas vazias

- [x] Pastas sem arquivos e subpastas → listar como vazias
- [x] Pastas com arquivos ocultos → considerar como não vazias
- [x] Pastas com subpastas → listar vazias corretamente se aplicável

---

## 🚨 Robustez
> ⚠️ **Erro ao inserir um valor não numérico no menu! Ao invés de entrada inválida, o programa encerra.**
>:warning: **Erro ao inserir ponto flutuante no menu! Pode entrar em alguma opção até utilizar o valor após a vírgula.**
- [ ] Pastas/arquivos com espaços e caracteres especiais → funcionar normalmente
- [ ] Arquivos grandes → mostrar tamanho corretamente
- [ ] Muitas subpastas e profundidade → manter performance e indentação
- [ ] Pastas com permissões restritas → não travar o programa

---

## 📌 Observação Final

- [ ] Cobertura completa de todos os itens pedidos no enunciado
- [ ] Pronto para entrega e apresentação
