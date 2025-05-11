/*
 * main.c
 *
 * Este arquivo implementa a interface do usuário para o sistema de biblioteca.
 * Apresenta um menu interativo com as operações disponíveis e mede o tempo
 * de execução de cada operação.
 */

#include "biblioteca.h"
#include <time.h>

/*
 * Limpa o buffer de entrada.
 * Remove caracteres residuais após operações de leitura.
 */
void limparBuffer()
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

/*
 * Exibe o menu principal do sistema.
 * Mostra todas as opções disponíveis para o usuário.
 */
void menu()
{
  printf("\n=== Biblioteca ===\n");
  printf("1. Inserir livro\n");
  printf("2. Remover livro\n");
  printf("3. Buscar livro\n");
  printf("4. Listar todos os livros\n");
  printf("5. Emprestar livro\n");
  printf("6. Devolver livro\n");
  printf("7. Salvar livros\n");
  printf("8. Carregar livros\n");
  printf("0. Sair\n");
  printf("Escolha uma opção: ");
}

/*
 * Função principal do programa.
 * Implementa o loop principal que processa as opções do usuário.
 * Para cada operação, mede e exibe o tempo de execução.
 */
int main()
{
  Biblioteca *bib = criarBiblioteca();
  int opcao;
  int id;
  char titulo[MAX_TITULO];
  char autor[MAX_AUTOR];
  FILE *arquivo;
  clock_t inicio, fim;
  double tempo_gasto;

  do
  {
    menu();
    scanf("%d", &opcao);
    limparBuffer();

    switch (opcao)
    {
    case 1: // Inserir livro
      inicio = clock();
      printf("Digite o ID do livro: ");
      scanf("%d", &id);
      limparBuffer();
      printf("Digite o título do livro: ");
      fgets(titulo, MAX_TITULO, stdin);
      titulo[strcspn(titulo, "\n")] = 0;
      printf("Digite o autor do livro: ");
      fgets(autor, MAX_AUTOR, stdin);
      autor[strcspn(autor, "\n")] = 0;
      inserirLivro(bib, id, titulo, autor);
      fim = clock();
      tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
      printf("\nTempo gasto para inserir o livro: %.3f segundos\n", tempo_gasto);
      break;

    case 2: // Remover livro
      inicio = clock();
      printf("Digite o ID do livro a ser removido: ");
      scanf("%d", &id);
      removerLivro(bib, id);
      fim = clock();
      tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
      printf("\nTempo gasto para remover o livro: %.3f segundos\n", tempo_gasto);
      break;

    case 3: // Buscar livro
      inicio = clock();
      printf("Digite o ID do livro a ser buscado: ");
      scanf("%d", &id);
      Livro *livro = buscarLivro(bib, id);
      if (livro != NULL)
      {
        printf("\nLivro encontrado:\n");
        printf("ID: %d\n", livro->id);
        printf("Título: %s\n", livro->titulo);
        printf("Autor: %s\n", livro->autor);
        printf("Disponível: %s\n", livro->disponivel ? "Sim" : "Não");
      }
      else
      {
        printf("Livro não encontrado.\n");
      }
      fim = clock();
      tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
      printf("\nTempo gasto para buscar o livro: %.3f segundos\n", tempo_gasto);
      break;

    case 4: // Listar livros
      inicio = clock();
      listarLivros(bib);
      fim = clock();
      tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
      printf("\nTempo gasto para listar todos os livros: %.3f segundos\n", tempo_gasto);
      break;

    case 5: // Emprestar livro
      inicio = clock();
      printf("Digite o ID do livro a ser emprestado: ");
      scanf("%d", &id);
      emprestarLivro(bib, id);
      fim = clock();
      tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
      printf("\nTempo gasto para emprestar o livro: %.3f segundos\n", tempo_gasto);
      break;

    case 6: // Devolver livro
      inicio = clock();
      printf("Digite o ID do livro a ser devolvido: ");
      scanf("%d", &id);
      devolverLivro(bib, id);
      fim = clock();
      tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
      printf("\nTempo gasto para devolver o livro: %.3f segundos\n", tempo_gasto);
      break;

    case 7: // Salvar livros
      inicio = clock();
      arquivo = fopen("livros.dat", "w");
      if (arquivo != NULL)
      {
        salvarLivros(bib, arquivo);
        fclose(arquivo);
      }
      else
      {
        printf("Erro ao abrir arquivo para escrita.\n");
      }
      fim = clock();
      tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
      printf("\nTempo gasto para salvar os livros: %.3f segundos\n", tempo_gasto);
      break;

    case 8: // Carregar livros
      inicio = clock();
      carregarLivros(bib, "livros.dat");
      fim = clock();
      tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
      printf("\nTempo gasto para carregar os livros: %.3f segundos\n", tempo_gasto);
      break;

    case 0: // Sair
      printf("Saindo...\n");
      break;

    default:
      printf("Opção inválida!\n");
    }
  } while (opcao != 0);

  destruirBiblioteca(bib);
  return 0;
}