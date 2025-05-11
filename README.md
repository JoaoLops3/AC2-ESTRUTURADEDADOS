# Biblioteca - Implementação em ABB e Lista Dinâmica

Este projeto implementa um sistema de biblioteca utilizando duas estruturas de dados diferentes:

1. Árvore Binária de Busca (ABB)
2. Lista Dinâmica

## Divisão do Código

O projeto está organizado em duas implementações independentes, cada uma com sua própria estrutura de dados. Vamos detalhar a organização de cada uma:

### Implementação ABB (Árvore Binária de Busca)

#### Estrutura de Dados

- `biblioteca.h`: Define as estruturas principais:
  - `struct Livro`: Nó da árvore com campos para id, título, autor, disponibilidade e ponteiros para filhos esquerdo e direito
  - `struct Biblioteca`: Estrutura principal que mantém o ponteiro para a raiz da árvore

#### Organização do Código

- `biblioteca.c`: Implementa as operações da ABB:
  - Funções de gerenciamento: `criarBiblioteca()`, `destruirBiblioteca()`
  - Operações básicas: `inserirLivro()`, `removerLivro()`, `buscarLivro()`
  - Funções auxiliares: `encontrarMenor()`, `contarLivros()`
  - Funções de persistência: `salvarLivros()`, `carregarLivros()`
  - Funções de balanceamento: `salvarLivrosBalanceado()`

### Implementação Lista Dinâmica

#### Estrutura de Dados

- `biblioteca.h`: Define as estruturas principais:
  - `struct Livro`: Nó da lista com campos para id, título, autor, disponibilidade e ponteiro para próximo
  - `struct Biblioteca`: Estrutura principal que mantém o ponteiro para o início da lista

#### Organização do Código

- `biblioteca.c`: Implementa as operações da Lista:
  - Funções de gerenciamento: `criarBiblioteca()`, `destruirBiblioteca()`
  - Operações básicas: `inserirLivro()`, `removerLivro()`, `buscarLivro()`
  - Funções de persistência: `salvarLivros()`, `carregarLivros()`

### Interface do Usuário

Ambas as implementações compartilham a mesma interface de usuário através do `main.c`, que oferece:

- Menu interativo com todas as operações disponíveis
- Medição de tempo para cada operação
- Tratamento de entrada/saída de dados
- Persistência de dados em arquivo

### Gerador de Testes

O arquivo `gerar_livros.c` é comum às duas implementações e serve para:

- Gerar dados de teste aleatórios
- Criar o arquivo inicial `livros.dat`
- Facilitar a comparação de desempenho entre as implementações

## Funcionalidades

Ambas as implementações oferecem as seguintes funcionalidades:

- Inserção de livros
- Remoção de livros
- Busca de livros
- Listagem de todos os livros
- Empréstimo de livros
- Devolução de livros
- Salvamento em arquivo
- Carregamento de arquivo

## Compilação

### Compilando a versão ABB

```bash
cd ABB
gcc -o biblioteca_abb main.c biblioteca.c
```

### Compilando a versão Lista Dinâmica

```bash
cd ListaDinamica
gcc -o biblioteca_lista main.c biblioteca.c
```

## Execução

### Executando a versão ABB

```bash
cd ABB
./biblioteca_abb
```

### Executando a versão Lista Dinâmica

```bash
cd ListaDinamica
./biblioteca_lista
```

## Geração de Dados para Teste

Para gerar dados de teste, você pode usar o programa `gerar_livros`:

### Compilando o gerador

```bash
gcc -o gerar_livros gerar_livros.c
```

### Executando o gerador

```bash
./gerar_livros
```

## Formato dos Dados

Os livros são salvos em um arquivo `livros.dat` com o seguinte formato:

```
id|titulo|autor|disponivel
```

## Observações

- A implementação em ABB mantém os livros organizados em uma árvore binária de busca
- A implementação em Lista Dinâmica mantém os livros ordenados por ID
- Ambas as implementações medem o tempo de execução das operações
- Os dados são persistidos em arquivo para manter o estado entre execuções
