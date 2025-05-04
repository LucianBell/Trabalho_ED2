# Trabalho_ED2
Trabalho de estrutura de dados II do Mestre Jedi Dr. Brusso

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

- [ ] Exibir arquivos com nome e tamanho corretos
- [ ] Exibir pastas com nome, número de filhos diretos e tamanho acumulado corretos
- [ ] Exibir subpastas com indentação adequada
- [ ] Exibir pastas vazias corretamente (0 filhos)

---

## 🌐 Exportar Árvore para HTML

- [ ] Exportar árvore pequena → HTML com indentação correta
- [ ] Exportar árvore grande → HTML mantendo estrutura correta
- [ ] Exportar árvore com pastas vazias → HTML mostra as pastas vazias

---

## 🔍 Pesquisas

### 3.1 Maior Arquivo
> :warning: **Erro encontrado quando dois arquivos tem o mesmo tamanho (apenas o último é listado)**

- [ ] Encontrar e exibir o maior arquivo corretamente
- [ ] Empate entre dois ou mais arquivos → listar todos

### 3.2 Arquivos com mais do que N bytes

- [ ] N menor que todos → listar todos
- [ ] N maior que todos → listar nenhum
- [ ] N intermediário → listar arquivos corretos

### 3.3 Pasta com mais arquivos diretos

- [ ] Identificar a pasta com mais arquivos diretos corretamente
- [ ] Empate entre pastas → escolher ou listar qualquer uma de forma estável

### 3.4 Arquivos por extensão

- [ ] Buscar por `.txt` → listar arquivos corretos
- [ ] Buscar por extensão inexistente → não listar nada
- [ ] Buscar com e sem ponto (`txt` e `.txt`) → funcionar em ambos os casos

### 3.5 Pastas vazias

- [ ] Pastas sem arquivos e subpastas → listar como vazias
- [ ] Pastas com arquivos ocultos → considerar como não vazias
- [ ] Pastas com subpastas → listar vazias corretamente se aplicável

---

## 🚨 Robustez

- [ ] Pastas/arquivos com espaços e caracteres especiais → funcionar normalmente
- [ ] Arquivos grandes → mostrar tamanho corretamente
- [ ] Muitas subpastas e profundidade → manter performance e indentação
- [ ] Pastas com permissões restritas → não travar o programa

---

## 📌 Observação Final

- [ ] Cobertura completa de todos os itens pedidos no enunciado
- [ ] Pronto para entrega e apresentação
