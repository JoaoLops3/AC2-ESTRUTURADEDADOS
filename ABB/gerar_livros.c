/*
 * gerar_livros.c
 *
 * Gerador de dados de teste para o sistema de biblioteca.
 * Cria um arquivo com livros balanceados para testar o sistema.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ============================================================
 * PARA MUDAR A QUANTIDADE DE LIVROS:
 * Altere o valor abaixo de NUM_LIVROS para a quantidade desejada.
 *
 * Quantidades sugeridas:
 * - 100 livros: #define NUM_LIVROS 100
 * - 1.000 livros: #define NUM_LIVROS 1000
 * - 10.000 livros: #define NUM_LIVROS 10000
 * - 100.000 livros: #define NUM_LIVROS 100000
 * - 1.000.000 livros: #define NUM_LIVROS 1000000
 *
 * Observações:
 * - Quantidades maiores gerarão arquivos maiores
 * - O tempo de geração aumenta proporcionalmente
 * - As operações na biblioteca serão mais lentas
 * ============================================================ */

/* ============================================================
 * OPICIONAL: Tamanho máximo dos campos
 * Se desejar, você pode alterar o tamanho máximo dos títulos e autores.
 * Por exemplo:
 * - Para títulos menores: #define MAX_TITULO 100
 * - Para títulos maiores: #define MAX_TITULO 1000
 * - Para autores menores: #define MAX_AUTOR 100
 * - Para autores maiores: #define MAX_AUTOR 1000
 *
 * Observações:
 * - Valores maiores ocupam mais memória
 * - Valores menores podem truncar textos longos
 * - O padrão de 500 caracteres é suficiente para a maioria dos casos
 * ============================================================ */
#define MAX_TITULO 500  // Tamanho máximo para o título do livro
#define MAX_AUTOR 500   // Tamanho máximo para o nome do autor
#define NUM_LIVROS 1000 // Número de livros a serem gerados

/*
 * Gera um número aleatório entre min e max.
 */
int gerarNumeroAleatorio(int min, int max)
{
  return min + rand() % (max - min + 1);
}

/*
 * Gera uma string aleatória com o tamanho especificado.
 * A string contém apenas letras minúsculas.
 */
char *gerarStringAleatoria(int tamanho)
{
  char *str = (char *)malloc(tamanho + 1);
  if (str == NULL)
    return NULL;

  for (int i = 0; i < tamanho; i++)
  {
    str[i] = 'a' + rand() % 26;
  }
  str[tamanho] = '\0';
  return str;
}

/*
 * Gera um título aleatório para um livro.
 * O título é no formato "Livro X" onde X é um número aleatório.
 */
char *gerarTituloAleatorio()
{
  char *titulo = (char *)malloc(MAX_TITULO);
  if (titulo == NULL)
    return NULL;

  int num = gerarNumeroAleatorio(1, 1000);
  sprintf(titulo, "Livro %d", num);
  return titulo;
}

/*
 * Gera um nome de autor aleatório.
 * O nome é no formato "Autor X" onde X é um número aleatório.
 */
char *gerarAutorAleatorio()
{
  char *autor = (char *)malloc(MAX_AUTOR);
  if (autor == NULL)
    return NULL;

  int num = gerarNumeroAleatorio(1, 1000);
  sprintf(autor, "Autor %d", num);
  return autor;
}

/*
 * Salva os livros de forma balanceada.
 * Usa divisão e conquista para garantir árvore balanceada.
 *
 * Parâmetros:
 * - inicio: índice inicial do intervalo
 * - fim: índice final do intervalo
 * - arquivo: arquivo onde os livros serão salvos
 *
 * Como funciona:
 * 1. Usa divisão e conquista para garantir que a árvore fique balanceada
 * 2. Sempre pega o elemento do meio do intervalo como raiz
 * 3. Recursivamente processa a subárvore esquerda (elementos menores)
 * 4. Recursivamente processa a subárvore direita (elementos maiores)
 *
 * Exemplo com 7 livros (IDs 1 a 7):
 * 1. Primeira chamada: salvarBalanceado(0, 6)
 *    - meio = (0 + 6) / 2 = 3
 *    - Salva o livro 4 (meio + 1, será a raiz)
 *    - Chama salvarBalanceado(0, 2) para a esquerda
 *    - Chama salvarBalanceado(4, 6) para a direita
 *
 * 2. Árvore resultante:
 *          4
 *         / \
 *        2   6
 *       / \ / \
 *      1  3 5  7
 *
 * 3. Ordem de salvamento no arquivo:
 *    - Primeiro salva a subárvore esquerda (1,2,3)
 *    - Depois salva a raiz (4)
 *    - Por fim salva a subárvore direita (5,6,7)
 */
void salvarBalanceado(int inicio, int fim, FILE *arquivo)
{
  // Se o intervalo é inválido, retorna
  if (inicio > fim)
    return;

  // Calcula o meio do intervalo (será a raiz da subárvore)
  int meio = (inicio + fim) / 2;

  // Primeiro salva a subárvore esquerda (elementos menores que o meio)
  salvarBalanceado(inicio, meio - 1, arquivo);

  // Depois salva o nó atual (raiz da subárvore)
  char *titulo = gerarTituloAleatorio();
  char *autor = gerarAutorAleatorio();

  if (titulo != NULL && autor != NULL)
  {
    // Salva o livro no arquivo no formato: id|titulo|autor|disponivel
    fprintf(arquivo, "%d|%s|%s|%d\n", meio + 1, titulo, autor, 1);
    free(titulo);
    free(autor);
  }

  // Por fim salva a subárvore direita (elementos maiores que o meio)
  salvarBalanceado(meio + 1, fim, arquivo);
}

/*
 * Função principal do gerador.
 * Cria um arquivo com livros balanceados para teste.
 */
int main()
{
  srand(time(NULL));
  FILE *arquivo = fopen("livros.dat", "w");
  if (arquivo == NULL)
  {
    printf("Erro ao criar arquivo de teste.\n");
    return 1;
  }

  printf("Gerando %d livros balanceados para teste...\n", NUM_LIVROS);

  // Salva os livros de forma balanceada
  salvarBalanceado(0, NUM_LIVROS - 1, arquivo);

  fclose(arquivo);
  printf("Arquivo de teste gerado com sucesso!\n");
  return 0;
}