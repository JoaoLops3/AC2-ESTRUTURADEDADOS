/*
 * gerar_livros.c
 *
 * Este arquivo gera dados de teste para o sistema de biblioteca.
 * Cria um arquivo com livros aleatórios, incluindo IDs, títulos e autores.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
 * Estrutura que representa um livro.
 * Usada para armazenar os dados dos livros gerados.
 */
typedef struct
{
  int id;           // ID único do livro
  char titulo[500]; // Título do livro
  char autor[500];  // Nome do autor
  int disponivel;   // 1 se disponível, 0 se emprestado
} Livro;

// Arrays de prefixos e sufixos para gerar títulos aleatórios
const char *prefixos_titulo[] = {
    "O", "A", "Os", "As", "Um", "Uma", "O Grande", "A Grande", "O Pequeno", "A Pequena",
    "O Último", "A Última", "O Primeiro", "A Primeira", "O Segredo", "O Mistério",
    "A História", "O Caminho", "A Jornada", "O Destino"};

const char *sufixos_titulo[] = {
    "do Tempo", "da Vida", "do Amor", "da Esperança", "do Destino", "da Fortuna",
    "do Deserto", "da Floresta", "do Mar", "da Montanha", "do Céu", "da Terra",
    "do Sol", "da Lua", "das Estrelas", "do Vento", "da Chuva", "do Fogo",
    "da Água", "do Ar"};

// Arrays de nomes e prenomes para gerar autores aleatórios
const char *nomes[] = {
    "Silva", "Santos", "Oliveira", "Souza", "Rodrigues", "Ferreira", "Almeida",
    "Pereira", "Costa", "Carvalho", "Gomes", "Martins", "Lima", "Araújo",
    "Fernandes", "Ribeiro", "Barbosa", "Mendes", "Lopes", "Nascimento"};

const char *prenomes[] = {
    "João", "Maria", "José", "Ana", "Antônio", "Francisco", "Carlos", "Paulo",
    "Pedro", "Lucas", "Luiz", "Marcos", "Luis", "Gabriel", "Rafael", "Daniel",
    "Marcelo", "Bruno", "Eduardo", "Felipe"};

/*
 * Gera um título aleatório combinando um prefixo e um sufixo.
 * O título é armazenado no buffer fornecido.
 */
void gerar_titulo_aleatorio(char *titulo)
{
  int prefixo_idx = rand() % (sizeof(prefixos_titulo) / sizeof(prefixos_titulo[0]));
  int sufixo_idx = rand() % (sizeof(sufixos_titulo) / sizeof(sufixos_titulo[0]));
  sprintf(titulo, "%s %s", prefixos_titulo[prefixo_idx], sufixos_titulo[sufixo_idx]);
}

/*
 * Gera um nome de autor aleatório combinando um prenome e um sobrenome.
 * O nome é armazenado no buffer fornecido.
 */
void gerar_autor_aleatorio(char *autor)
{
  int nome_idx = rand() % (sizeof(nomes) / sizeof(nomes[0]));
  int prenome_idx = rand() % (sizeof(prenomes) / sizeof(prenomes[0]));
  sprintf(autor, "%s %s", prenomes[prenome_idx], nomes[nome_idx]);
}

/*
 * Lista de livros pré-definidos.
 * Contém 100 livros clássicos da literatura.
 */
Livro livros[] = {
    {1, "Dom Casmurro", "Machado de Assis", 1},
    {2, "O Senhor dos Anéis", "J.R.R. Tolkien", 1},
    {3, "1984", "George Orwell", 1},
    {4, "O Pequeno Príncipe", "Antoine de Saint-Exupéry", 1},
    {5, "Cem Anos de Solidão", "Gabriel García Márquez", 1},
    {6, "O Alquimista", "Paulo Coelho", 1},
    {7, "Harry Potter e a Pedra Filosofal", "J.K. Rowling", 1},
    {8, "Crime e Castigo", "Fiódor Dostoiévski", 1},
    {9, "O Grande Gatsby", "F. Scott Fitzgerald", 1},
    {10, "Memórias Póstumas de Brás Cubas", "Machado de Assis", 1},
    {11, "A Divina Comédia", "Dante Alighieri", 1},
    {12, "O Retrato de Dorian Gray", "Oscar Wilde", 1},
    {13, "Os Miseráveis", "Victor Hugo", 1},
    {14, "O Conde de Monte Cristo", "Alexandre Dumas", 1},
    {15, "Orgulho e Preconceito", "Jane Austen", 1},
    {16, "O Processo", "Franz Kafka", 1},
    {17, "A Metamorfose", "Franz Kafka", 1},
    {18, "O Apanhador no Campo de Centeio", "J.D. Salinger", 1},
    {19, "O Hobbit", "J.R.R. Tolkien", 1},
    {20, "A Revolução dos Bichos", "George Orwell", 1},
    {21, "O Nome da Rosa", "Umberto Eco", 1},
    {22, "O Estrangeiro", "Albert Camus", 1},
    {23, "O Mito de Sísifo", "Albert Camus", 1},
    {24, "A Hora da Estrela", "Clarice Lispector", 1},
    {25, "Grande Sertão: Veredas", "João Guimarães Rosa", 1},
    {26, "Vidas Secas", "Graciliano Ramos", 1},
    {27, "O Guarani", "José de Alencar", 1},
    {28, "Iracema", "José de Alencar", 1},
    {29, "O Cortiço", "Aluísio Azevedo", 1},
    {30, "Macunaíma", "Mário de Andrade", 1},
    {31, "Memórias de um Sargento de Milícias", "Manuel Antônio de Almeida", 1},
    {32, "O Tempo e o Vento", "Érico Veríssimo", 1},
    {33, "Olhai os Lírios do Campo", "Érico Veríssimo", 1},
    {34, "A Moreninha", "Joaquim Manuel de Macedo", 1},
    {35, "O Ateneu", "Raul Pompéia", 1},
    {36, "Dom Quixote", "Miguel de Cervantes", 1},
    {37, "A Ilíada", "Homero", 1},
    {38, "A Odisseia", "Homero", 1},
    {39, "Hamlet", "William Shakespeare", 1},
    {40, "Romeu e Julieta", "William Shakespeare", 1},
    {41, "A Comédia dos Erros", "William Shakespeare", 1},
    {42, "O Mercador de Veneza", "William Shakespeare", 1},
    {43, "O Rei Lear", "William Shakespeare", 1},
    {44, "Macbeth", "William Shakespeare", 1},
    {45, "Otelo", "William Shakespeare", 1},
    {46, "A Tempestade", "William Shakespeare", 1},
    {47, "A Morte de Ivan Ilitch", "Liev Tolstói", 1},
    {48, "Guerra e Paz", "Liev Tolstói", 1},
    {49, "Anna Kariênina", "Liev Tolstói", 1},
    {50, "O Idiota", "Fiódor Dostoiévski", 1},
    {51, "Os Irmãos Karamázov", "Fiódor Dostoiévski", 1},
    {52, "O Mestre e Margarida", "Mikhail Bulgákov", 1},
    {53, "Lolita", "Vladimir Nabokov", 1},
    {54, "O Sol é para Todos", "Harper Lee", 1},
    {55, "O Apanhador no Campo de Centeio", "J.D. Salinger", 1},
    {56, "O Velho e o Mar", "Ernest Hemingway", 1},
    {57, "Por Quem os Sinos Dobram", "Ernest Hemingway", 1},
    {58, "O Som e a Fúria", "William Faulkner", 1},
    {59, "O Morro dos Ventos Uivantes", "Emily Brontë", 1},
    {60, "Jane Eyre", "Charlotte Brontë", 1},
    {61, "As Vinhas da Ira", "John Steinbeck", 1},
    {62, "Ratos e Homens", "John Steinbeck", 1},
    {63, "A Laranja Mecânica", "Anthony Burgess", 1},
    {64, "O Iluminado", "Stephen King", 1},
    {65, "O Cemitério", "Stephen King", 1},
    {66, "It - A Coisa", "Stephen King", 1},
    {67, "O Silmarillion", "J.R.R. Tolkien", 1},
    {68, "O Silêncio dos Inocentes", "Thomas Harris", 1},
    {69, "O Código Da Vinci", "Dan Brown", 1},
    {70, "Anjos e Demônios", "Dan Brown", 1},
    {71, "O Poderoso Chefão", "Mario Puzo", 1},
    {72, "O Exorcista", "William Peter Blatty", 1},
    {73, "O Caçador de Pipas", "Khaled Hosseini", 1},
    {74, "A Menina que Roubava Livros", "Markus Zusak", 1},
    {75, "O Diário de Anne Frank", "Anne Frank", 1},
    {76, "O Menino do Pijama Listrado", "John Boyne", 1},
    {77, "A Culpa é das Estrelas", "John Green", 1},
    {78, "O Perfume", "Patrick Süskind", 1},
    {79, "O Mundo de Sofia", "Jostein Gaarder", 1},
    {80, "O Nome do Vento", "Patrick Rothfuss", 1},
    {81, "O Temor do Sábio", "Patrick Rothfuss", 1},
    {82, "O Senhor das Moscas", "William Golding", 1},
    {83, "O Lobo da Estepe", "Hermann Hesse", 1},
    {84, "Sidarta", "Hermann Hesse", 1},
    {85, "O Demônio e a Srta. Prym", "Paulo Coelho", 1},
    {86, "Veronika Decide Morrer", "Paulo Coelho", 1},
    {87, "Onze Minutos", "Paulo Coelho", 1},
    {88, "O Zahir", "Paulo Coelho", 1},
    {89, "A Bruxa de Portobello", "Paulo Coelho", 1},
    {90, "O Vencedor Está Só", "Paulo Coelho", 1},
    {91, "O Aleph", "Paulo Coelho", 1},
    {92, "Manuscrito Encontrado em Accra", "Paulo Coelho", 1},
    {93, "Adulterio", "Paulo Coelho", 1},
    {94, "Hippie", "Paulo Coelho", 1},
    {95, "O Caminho do Arco", "Paulo Coelho", 1},
    {96, "O Diário de um Mago", "Paulo Coelho", 1},
    {97, "As Valkírias", "Paulo Coelho", 1},
    {98, "Na Margem do Rio Piedra eu Sentei e Chorei", "Paulo Coelho", 1},
    {99, "Maktub", "Paulo Coelho", 1},
    {100, "O Monte Cinco", "Paulo Coelho", 1}};

/*
 * Função principal do programa.
 * Gera 10000 livros aleatórios e os salva em um arquivo.
 * Cada livro tem um ID único, título e autor gerados aleatoriamente.
 */
int main()
{
  srand(time(NULL)); // Inicializa o gerador de números aleatórios
  FILE *arquivo = fopen("livros.dat", "w");
  if (arquivo == NULL)
  {
    printf("Erro ao abrir arquivo para escrita.\n");
    return 1;
  }

  for (int i = 0; i < 10000; i++) // Gera 10000 livros aleatórios
  {
    Livro livro;
    livro.id = i + 1;
    gerar_titulo_aleatorio(livro.titulo);
    gerar_autor_aleatorio(livro.autor);
    livro.disponivel = 1;

    fprintf(arquivo, "%d|%s|%s|%d\n",
            livro.id,
            livro.titulo,
            livro.autor,
            livro.disponivel);
  }

  fclose(arquivo);
  printf("Arquivo livros.dat criado com sucesso com 100000 livros!\n");
  return 0;
}