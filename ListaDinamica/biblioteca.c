/*
 * biblioteca.c
 *
 * Este arquivo implementa as funções da biblioteca usando Lista Dinâmica.
 * Cada função manipula a lista de livros de forma a manter a ordem por ID
 * e garantir a integridade dos dados.
 */

#include "biblioteca.h"

/*
 * Cria uma nova biblioteca vazia.
 * Aloca memória para a estrutura da biblioteca e inicializa o início da lista como NULL.
 */
Biblioteca *criarBiblioteca()
{
  Biblioteca *bib = (Biblioteca *)malloc(sizeof(Biblioteca));
  if (bib != NULL)
  {
    bib->inicio = NULL;
  }
  return bib;
}

/*
 * Libera toda a memória alocada para a biblioteca.
 * Percorre a lista do início ao fim, liberando cada livro.
 * Por fim, libera a estrutura da biblioteca.
 */
void destruirBiblioteca(Biblioteca *bib)
{
  if (bib != NULL)
  {
    Livro *atual = bib->inicio;
    while (atual != NULL)
    {
      Livro *prox = atual->prox;
      free(atual);
      atual = prox;
    }
    free(bib);
  }
}

/*
 * Cria um novo livro com os dados fornecidos.
 * Aloca memória para o livro e inicializa seus campos.
 * O livro é criado como disponível e sem próximo livro.
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
    novo->prox = NULL;
  }
  return novo;
}

/*
 * Insere um novo livro na biblioteca.
 * O livro é inserido mantendo a lista ordenada por ID.
 * Se a lista estiver vazia ou o novo livro tiver ID menor que o primeiro,
 * ele é inserido no início. Caso contrário, é inserido na posição correta.
 */
void inserirLivro(Biblioteca *bib, int id, const char *titulo, const char *autor)
{
  Livro *novo = criarLivro(id, titulo, autor);
  if (novo == NULL)
    return;

  // Se a lista estiver vazia ou o novo livro tiver ID menor que o primeiro
  if (bib->inicio == NULL || id < bib->inicio->id)
  {
    novo->prox = bib->inicio;
    bib->inicio = novo;
    return;
  }

  // Encontrar a posição correta para inserir
  Livro *atual = bib->inicio;
  while (atual->prox != NULL && atual->prox->id < id)
  {
    atual = atual->prox;
  }

  novo->prox = atual->prox;
  atual->prox = novo;
}

/*
 * Busca um livro pelo ID.
 * Percorre a lista do início ao fim até encontrar o livro.
 * Retorna um ponteiro para o livro encontrado ou NULL se não encontrar.
 */
Livro *buscarLivro(Biblioteca *bib, int id)
{
  Livro *atual = bib->inicio;
  while (atual != NULL)
  {
    if (atual->id == id)
    {
      return atual;
    }
    atual = atual->prox;
  }
  return NULL;
}

/*
 * Remove um livro da biblioteca pelo ID.
 * Se o livro for o primeiro da lista, atualiza o início.
 * Caso contrário, procura o livro e o remove, mantendo a lista ligada.
 */
void removerLivro(Biblioteca *bib, int id)
{
  if (bib->inicio == NULL)
    return;

  // Se o livro a ser removido é o primeiro
  if (bib->inicio->id == id)
  {
    Livro *temp = bib->inicio;
    bib->inicio = bib->inicio->prox;
    free(temp);
    return;
  }

  // Procurar o livro na lista
  Livro *atual = bib->inicio;
  while (atual->prox != NULL && atual->prox->id != id)
  {
    atual = atual->prox;
  }

  // Se encontrou o livro
  if (atual->prox != NULL)
  {
    Livro *temp = atual->prox;
    atual->prox = temp->prox;
    free(temp);
  }
}

/*
 * Lista todos os livros da biblioteca.
 * Percorre a lista do início ao fim, imprimindo os dados de cada livro.
 * Se a biblioteca estiver vazia, exibe uma mensagem.
 */
void listarLivros(Biblioteca *bib)
{
  if (bib->inicio == NULL)
  {
    printf("Biblioteca vazia!\n");
    return;
  }

  Livro *atual = bib->inicio;
  while (atual != NULL)
  {
    printf("ID: %d\n", atual->id);
    printf("Título: %s\n", atual->titulo);
    printf("Autor: %s\n", atual->autor);
    printf("Disponível: %s\n", atual->disponivel ? "Sim" : "Não");
    printf("------------------------\n");
    atual = atual->prox;
  }
}

/*
 * Marca um livro como emprestado.
 * Busca o livro pelo ID e, se encontrar e estiver disponível,
 * marca como emprestado.
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
 * Busca o livro pelo ID e, se encontrar e estiver emprestado,
 * marca como disponível.
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
 * Salva todos os livros em um arquivo.
 * Percorre a lista do início ao fim, salvando os dados de cada livro
 * em formato texto, separados por '|'.
 */
void salvarLivros(Biblioteca *bib, FILE *arquivo)
{
  if (arquivo == NULL)
    return;

  Livro *atual = bib->inicio;
  while (atual != NULL)
  {
    fprintf(arquivo, "%d|%s|%s|%d\n",
            atual->id,
            atual->titulo,
            atual->autor,
            atual->disponivel);
    atual = atual->prox;
  }
  printf("Livros salvos com sucesso!\n");
}

/*
 * Carrega livros de um arquivo para a biblioteca.
 * Lê o arquivo linha por linha, criando um novo livro para cada linha.
 * Os dados são lidos no formato: id|titulo|autor|disponivel
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
  char linha[1024];

  while (fgets(linha, sizeof(linha), arquivo))
  {
    char *token = strtok(linha, "|");
    id = atoi(token);

    token = strtok(NULL, "|");
    strcpy(titulo, token);

    token = strtok(NULL, "|");
    strcpy(autor, token);

    token = strtok(NULL, "|");
    disponivel = atoi(token);

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