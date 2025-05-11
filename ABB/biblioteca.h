/*
 * biblioteca.h
 *
 * Este arquivo contém as definições para o sistema de biblioteca usando
 * Árvore Binária de Busca. A árvore é usada para organizar os livros por ID,
 * permitindo buscas e inserções eficientes.
 */

#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITULO 500 // Tamanho máximo para o título do livro
#define MAX_AUTOR 500  // Tamanho máximo para o nome do autor

/*
 * Estrutura que representa um livro na árvore.
 * Cada livro tem um ID único, título, autor e status de disponibilidade.
 * Os ponteiros esq e dir apontam para os filhos na árvore.
 */
typedef struct Livro
{
  int id;                  // ID único do livro
  char titulo[MAX_TITULO]; // Título do livro
  char autor[MAX_AUTOR];   // Nome do autor
  int disponivel;          // 1 se disponível, 0 se emprestado
  struct Livro *esq;       // Ponteiro para o filho esquerdo (ID menor)
  struct Livro *dir;       // Ponteiro para o filho direito (ID maior)
} Livro;

/*
 * Estrutura principal da biblioteca.
 * Mantém apenas o ponteiro para a raiz da árvore.
 */
typedef struct
{
  Livro *raiz; // Ponteiro para a raiz da árvore
} Biblioteca;

/*
 * Cria uma nova biblioteca vazia.
 * Retorna um ponteiro para a biblioteca criada ou NULL se houver erro.
 */
Biblioteca *criarBiblioteca();

/*
 * Libera toda a memória alocada para a biblioteca.
 * Primeiro destrói a árvore de livros e depois libera a estrutura da biblioteca.
 */
void destruirBiblioteca(Biblioteca *bib);

/*
 * Insere um novo livro na biblioteca.
 * O livro é inserido mantendo a ordem da árvore (IDs menores à esquerda,
 * maiores à direita).
 */
void inserirLivro(Biblioteca *bib, int id, const char *titulo, const char *autor);

/*
 * Remove um livro da biblioteca pelo ID.
 * A remoção mantém a estrutura da árvore, tratando três casos:
 * 1. Livro sem filhos
 * 2. Livro com um filho
 * 3. Livro com dois filhos
 */
void removerLivro(Biblioteca *bib, int id);

/*
 * Busca um livro pelo ID.
 * Retorna um ponteiro para o livro encontrado ou NULL se não encontrar.
 */
Livro *buscarLivro(Biblioteca *bib, int id);

/*
 * Lista todos os livros da biblioteca em ordem.
 * A listagem é feita percorrendo a árvore em ordem (esquerda, raiz, direita).
 */
void listarLivros(Livro *raiz);

/*
 * Marca um livro como emprestado.
 * Verifica se o livro existe e está disponível antes de emprestar.
 */
void emprestarLivro(Biblioteca *bib, int id);

/*
 * Marca um livro como devolvido.
 * Verifica se o livro existe e está emprestado antes de devolver.
 */
void devolverLivro(Biblioteca *bib, int id);

/*
 * Salva todos os livros em um arquivo.
 * Os livros são salvos em ordem (esquerda, raiz, direita).
 */
void salvarLivros(Livro *raiz, FILE *arquivo);

/*
 * Carrega livros de um arquivo para a biblioteca.
 * Lê o arquivo linha por linha, criando um novo livro para cada linha.
 */
void carregarLivros(Biblioteca *bib, const char *nomeArquivo);

/*
 * Conta o número total de livros na biblioteca.
 * Percorre a árvore contando todos os nós.
 */
int contarLivros(Livro *raiz);

/*
 * Armazena os livros em um vetor em ordem.
 * Usado para salvar os livros de forma balanceada.
 */
void armazenarLivrosEmOrdem(Livro *raiz, Livro **vetor, int *pos);

/*
 * Salva os livros de forma balanceada.
 * Usado para garantir que a árvore fique balanceada quando for recarregada.
 */
void salvarLivrosBalanceado(Livro *raiz, FILE *arquivo);

/*
 * Imprime os livros por níveis da árvore.
 * Usa uma fila para imprimir nível por nível, da raiz até as folhas.
 */
void imprimirPorNiveis(Livro *raiz);

#endif