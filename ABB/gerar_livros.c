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
 */
void salvarBalanceado(int inicio, int fim, FILE *arquivo)
{
  if (inicio <= fim)
  {
    int meio = (inicio + fim) / 2;
    int id = meio + 1; // IDs de 1 a NUM_LIVROS
    char *titulo = gerarTituloAleatorio();
    char *autor = gerarAutorAleatorio();

    if (titulo != NULL && autor != NULL)
    {
      fprintf(arquivo, "%d|%s|%s|%d\n", id, titulo, autor, 1);
      free(titulo);
      free(autor);
    }

    // Salva subárvores esquerda e direita
    salvarBalanceado(inicio, meio - 1, arquivo);
    salvarBalanceado(meio + 1, fim, arquivo);
  }
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