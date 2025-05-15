/*
 * biblioteca.c
 *
 * Implementação das funções da biblioteca usando Árvore Binária de Busca.
 * Este arquivo contém todas as funções declaradas em biblioteca.h.
 */

#include "biblioteca.h"

/*
 * Cria uma nova biblioteca vazia.
 * Aloca memória para a estrutura e inicializa a raiz como NULL.
 */
Biblioteca *criarBiblioteca()
{
  Biblioteca *bib = (Biblioteca *)malloc(sizeof(Biblioteca));
  if (bib != NULL)
  {
    bib->raiz = NULL;
  }
  return bib;
}

/*
 * Função auxiliar para destruir a árvore recursivamente.
 * Percorre a árvore em pós-ordem, liberando a memória de cada nó.
 */
void destruirArvore(Livro *raiz)
{
  if (raiz != NULL)
  {
    destruirArvore(raiz->esq);
    destruirArvore(raiz->dir);
    free(raiz);
  }
}

/*
 * Libera toda a memória alocada para a biblioteca.
 * Primeiro destrói a árvore de livros e depois libera a estrutura da biblioteca.
 */
void destruirBiblioteca(Biblioteca *bib)
{
  if (bib != NULL)
  {
    destruirArvore(bib->raiz);
    free(bib);
  }
}

/*
 * Cria um novo nó de livro.
 * Aloca memória e inicializa todos os campos do livro.
 */
Livro *criarLivro(int id, const char *titulo, const char *autor)
{
  Livro *novo = (Livro *)malloc(sizeof(Livro));
  if (novo != NULL)
  {
    novo->id = id;
    strcpy(novo->titulo, titulo);
    strcpy(novo->autor, autor);
    novo->disponivel = 1;
    novo->esq = novo->dir = NULL;
  }
  return novo;
}

/*
 * Função auxiliar para inserir um livro na árvore.
 * Insere o livro mantendo a propriedade da ABB: IDs menores à esquerda,
 * maiores à direita.
 */
void inserirLivroRecursivo(Livro **raiz, int id, const char *titulo, const char *autor)
{
  if (*raiz == NULL)
  {
    *raiz = criarLivro(id, titulo, autor);
  }
  else if (id < (*raiz)->id)
  {
    inserirLivroRecursivo(&((*raiz)->esq), id, titulo, autor);
  }
  else if (id > (*raiz)->id)
  {
    inserirLivroRecursivo(&((*raiz)->dir), id, titulo, autor);
  }
}

/*
 * Insere um novo livro na biblioteca.
 * Chama a função recursiva para inserir na posição correta.
 */
void inserirLivro(Biblioteca *bib, int id, const char *titulo, const char *autor)
{
  inserirLivroRecursivo(&(bib->raiz), id, titulo, autor);
}

/*
 * Função auxiliar para buscar um livro na árvore.
 * Busca o livro pelo ID, aproveitando a propriedade da ABB.
 */
Livro *buscarLivroRecursivo(Livro *raiz, int id)
{
  if (raiz == NULL || raiz->id == id)
  {
    return raiz;
  }
  if (id < raiz->id)
  {
    return buscarLivroRecursivo(raiz->esq, id);
  }
  return buscarLivroRecursivo(raiz->dir, id);
}

/*
 * Busca um livro na biblioteca pelo ID.
 * Chama a função recursiva para buscar na árvore.
 */
Livro *buscarLivro(Biblioteca *bib, int id)
{
  return buscarLivroRecursivo(bib->raiz, id);
}

/*
 * Encontra o nó com o menor ID em uma subárvore.
 * Usado na remoção de nós com dois filhos.
 */
Livro *encontrarMenor(Livro *raiz)
{
  Livro *atual = raiz;
  while (atual && atual->esq != NULL)
  {
    atual = atual->esq;
  }
  return atual;
}

/*
 * Função auxiliar para remover um livro da árvore.
 * Remove o livro mantendo a propriedade da ABB.
 * Trata três casos: nó sem filhos, com um filho e com dois filhos.
 */
Livro *removerLivroRecursivo(Livro *raiz, int id)
{
  if (raiz == NULL)
    return raiz;

  if (id < raiz->id)
  {
    raiz->esq = removerLivroRecursivo(raiz->esq, id);
  }
  else if (id > raiz->id)
  {
    raiz->dir = removerLivroRecursivo(raiz->dir, id);
  }
  else
  {
    if (raiz->esq == NULL)
    {
      Livro *temp = raiz->dir;
      free(raiz);
      return temp;
    }
    else if (raiz->dir == NULL)
    {
      Livro *temp = raiz->esq;
      free(raiz);
      return temp;
    }

    Livro *temp = encontrarMenor(raiz->dir);
    raiz->id = temp->id;
    strcpy(raiz->titulo, temp->titulo);
    strcpy(raiz->autor, temp->autor);
    raiz->disponivel = temp->disponivel;
    raiz->dir = removerLivroRecursivo(raiz->dir, temp->id);
  }
  return raiz;
}

/*
 * Remove um livro da biblioteca pelo ID.
 * Chama a função recursiva para remover da árvore.
 */
void removerLivro(Biblioteca *bib, int id)
{
  bib->raiz = removerLivroRecursivo(bib->raiz, id);
}

/*
 * Função auxiliar para listar os livros em ordem.
 * Percorre a árvore em ordem (esquerda, raiz, direita).
 */
void listarLivrosRecursivo(Livro *raiz)
{
  if (raiz != NULL)
  {
    listarLivrosRecursivo(raiz->esq);
    printf("ID: %d\n", raiz->id);
    printf("Título: %s\n", raiz->titulo);
    printf("Autor: %s\n", raiz->autor);
    printf("Disponível: %s\n", raiz->disponivel ? "Sim" : "Não");
    printf("------------------------\n");
    listarLivrosRecursivo(raiz->dir);
  }
}

/*
 * Lista todos os livros da biblioteca em ordem.
 * Verifica se a biblioteca está vazia e chama a função recursiva.
 */
void listarLivros(Livro *raiz)
{
  if (raiz == NULL)
  {
    printf("Biblioteca vazia!\n");
    return;
  }
  listarLivrosRecursivo(raiz);
}

/*
 * Marca um livro como emprestado.
 * Busca o livro e verifica se está disponível antes de emprestar.
 */
void emprestarLivro(Biblioteca *bib, int id)
{
  Livro *livro = buscarLivro(bib, id);
  if (livro != NULL)
  {
    if (livro->disponivel)
    {
      livro->disponivel = 0;
      printf("Livro emprestado com sucesso!\n");
    }
    else
    {
      printf("Livro não está disponível para empréstimo.\n");
    }
  }
  else
  {
    printf("Livro não encontrado.\n");
  }
}

/*
 * Marca um livro como devolvido.
 * Busca o livro e verifica se está emprestado antes de devolver.
 */
void devolverLivro(Biblioteca *bib, int id)
{
  Livro *livro = buscarLivro(bib, id);
  if (livro != NULL)
  {
    if (!livro->disponivel)
    {
      livro->disponivel = 1;
      printf("Livro devolvido com sucesso!\n");
    }
    else
    {
      printf("Livro já está disponível.\n");
    }
  }
  else
  {
    printf("Livro não encontrado.\n");
  }
}

/*
 * Função auxiliar para armazenar os livros em um vetor em ordem.
 * Usada para rebalancear a árvore antes de salvar.
 */
void armazenarLivrosEmOrdem(Livro *raiz, Livro **vetor, int *pos)
{
  if (raiz != NULL)
  {
    armazenarLivrosEmOrdem(raiz->esq, vetor, pos);
    vetor[(*pos)++] = raiz;
    armazenarLivrosEmOrdem(raiz->dir, vetor, pos);
  }
}

/*
 * Função auxiliar para salvar os livros de forma balanceada.
 * Usa divisão e conquista para garantir árvore balanceada.
 */
void salvarBalanceadoRecursivo(Livro **vetor, int inicio, int fim, FILE *arquivo)
{
  if (inicio <= fim)
  {
    int meio = (inicio + fim) / 2;
    Livro *livro = vetor[meio];
    fprintf(arquivo, "%d|%s|%s|%d\n", livro->id, livro->titulo, livro->autor, livro->disponivel);
    salvarBalanceadoRecursivo(vetor, inicio, meio - 1, arquivo);
    salvarBalanceadoRecursivo(vetor, meio + 1, fim, arquivo);
  }
}

/*
 * Salva os livros de forma balanceada.
 * Primeiro armazena em um vetor em ordem, depois salva balanceado.
 */
void salvarLivrosBalanceado(Livro *raiz, FILE *arquivo)
{
  int n = contarLivros(raiz);
  Livro **vetor = (Livro **)malloc(n * sizeof(Livro *));
  if (vetor == NULL)
    return;

  int pos = 0;
  armazenarLivrosEmOrdem(raiz, vetor, &pos);
  salvarBalanceadoRecursivo(vetor, 0, n - 1, arquivo);
  free(vetor);
}

/*
 * Salva os livros no arquivo.
 * Usa salvamento balanceado para manter a árvore balanceada.
 */
void salvarLivros(Livro *raiz, FILE *arquivo)
{
  salvarLivrosBalanceado(raiz, arquivo);
}

/*
 * Carrega livros de um arquivo para a biblioteca.
 * Lê o arquivo linha por linha, criando um novo livro para cada linha.
 */
void carregarLivros(Biblioteca *bib, const char *nomeArquivo)
{
  FILE *arquivo = fopen(nomeArquivo, "r");
  if (arquivo == NULL)
  {
    printf("Erro ao abrir arquivo para leitura.\n");
    return;
  }

  int id, disponivel;
  char titulo[MAX_TITULO], autor[MAX_AUTOR];
  char linha[256];

  while (fgets(linha, sizeof(linha), arquivo))
  {
    sscanf(linha, "%d|%[^|]|%[^|]|%d", &id, titulo, autor, &disponivel);
    inserirLivro(bib, id, titulo, autor);
    Livro *livro = buscarLivro(bib, id);
    if (livro != NULL)
    {
      livro->disponivel = disponivel;
    }
  }

  fclose(arquivo);
  printf("Livros carregados com sucesso!\n");
}

/*
 * Conta o número total de livros na biblioteca.
 * Percorre a árvore contando todos os nós.
 */
int contarLivros(Livro *raiz)
{
  if (raiz == NULL)
    return 0;
  return 1 + contarLivros(raiz->esq) + contarLivros(raiz->dir);
}

/*
 * Imprime os livros por níveis da árvore.
 * Usa uma fila para imprimir nível por nível, da raiz até as folhas.
 */
void imprimirPorNiveis(Livro *raiz)
{
  if (raiz == NULL)
    return;

  Livro **fila = (Livro **)malloc(1000 * sizeof(Livro *));
  int inicio = 0, fim = 0;

  fila[fim++] = raiz;

  while (inicio < fim)
  {
    Livro *atual = fila[inicio++];
    printf("ID: %d, Título: %s\n", atual->id, atual->titulo);

    if (atual->esq != NULL)
      fila[fim++] = atual->esq;
    if (atual->dir != NULL)
      fila[fim++] = atual->dir;
  }

  free(fila);
}