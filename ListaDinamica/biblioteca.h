/*
 * biblioteca.h
 *
 * Este arquivo contém as definições para o sistema de biblioteca usando
 * Lista Dinâmica. A lista é usada para organizar os livros por ID,
 * permitindo operações de busca, inserção e remoção.
 */

#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITULO 500 // Tamanho máximo para o título do livro
#define MAX_AUTOR 500  // Tamanho máximo para o nome do autor

/*
 * Estrutura que representa um livro na lista.
 * Cada livro tem um ID único, título, autor e status de disponibilidade.
 * O ponteiro prox aponta para o próximo livro na lista.
 */
typedef struct Livro
{
  int id;                  // ID único do livro
  char titulo[MAX_TITULO]; // Título do livro
  char autor[MAX_AUTOR];   // Nome do autor
  int disponivel;          // 1 se disponível, 0 se emprestado
  struct Livro *prox;      // Ponteiro para o próximo livro
} Livro;

/*
 * Estrutura principal da biblioteca.
 * Mantém apenas o ponteiro para o início da lista.
 */
typedef struct
{
  Livro *inicio; // Ponteiro para o primeiro livro da lista
} Biblioteca;

/*
 * Cria uma nova biblioteca vazia.
 * Retorna um ponteiro para a biblioteca criada ou NULL se houver erro.
 */
Biblioteca *criarBiblioteca();

/*
 * Libera toda a memória alocada para a biblioteca.
 * Percorre a lista liberando cada livro e depois libera a estrutura da biblioteca.
 */
void destruirBiblioteca(Biblioteca *bib);

/*
 * Insere um novo livro na biblioteca.
 * O livro é inserido mantendo a lista ordenada por ID.
 */
void inserirLivro(Biblioteca *bib, int id, const char *titulo, const char *autor);

/*
 * Remove um livro da biblioteca pelo ID.
 * Mantém a lista ordenada após a remoção.
 */
void removerLivro(Biblioteca *bib, int id);

/*
 * Busca um livro pelo ID.
 * Retorna um ponteiro para o livro encontrado ou NULL se não encontrar.
 */
Livro *buscarLivro(Biblioteca *bib, int id);

/*
 * Lista todos os livros da biblioteca em ordem.
 * A listagem é feita percorrendo a lista do início ao fim.
 */
void listarLivros(Biblioteca *bib);

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
 * Os livros são salvos em ordem, do início ao fim da lista.
 */
void salvarLivros(Biblioteca *bib, FILE *arquivo);

/*
 * Carrega livros de um arquivo para a biblioteca.
 * Lê o arquivo linha por linha, criando um novo livro para cada linha.
 */
void carregarLivros(Biblioteca *bib, const char *nomeArquivo);

#endif