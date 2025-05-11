# Teste com 1.000.000 de livros

Nota: O teste foi realizado apenas uma vez devido à longa duração do processamento.

Os testes foram realizados para comparar o desempenho das operações básicas entre a implementação em Árvore Binária de Busca (ABB) e Lista Dinâmica. Cada operação foi executada e o tempo registrado.

## Tabela 5 - Operações e tempos de execução

| Operação  | ABB (s) | Lista Dinâmica (s) |
| --------- | ------- | ------------------ |
| Carregar  | 0.500   | 950.000            |
| Salvar    | 1.200   | 20.000             |
| Devolver  | 0.0005  | 0.0008             |
| Emprestar | 0.0005  | 0.0008             |
| Listar    | 2.800   | 3.100              |
| Buscar    | 0.0004  | 0.0008             |
| Remover   | 0.0006  | 0.0010             |
| Inserir   | 0.0006  | 0.0010             |
| --------- | ------- | ------------------ |