# 42-minishell
Repo para o o projeto Minishell - 42SP
Este projeto é parte do currículo da 42 São Paulo, onde desenvolvemos um interpretador de comandos do tipo *shell*, com suporte a execução de comandos, redirecionamentos, pipes e outras funcionalidades do shell Bash.

## Collab

- Jefferson
- Carol

## Estrutura de Branches

- `main`: branch de produção. Apenas merges vindos de `devops` ou `hotfix`.
- `devops`: branch de desenvolvimento ativo. Origem para `feature` e `release`.
- `feature/*`: desenvolvimento de novas funcionalidades.
- `release/*`: preparação de entregas finais.
- `hotfix/*`: correções urgentes a partir da `main`.

## Build

```bash
make

APAGAR -> COMENTARIOS DIARIOS


27/05
1- Construção da árvore binária de execução com base nos tokens (&&, ||, |, ()).

2- Validação de sintaxe: tratar erros como | ls ou ls || || echo.

3- Expansão de variáveis ($USER, $?).

4- Parsing de redirecionamento (>, <, >>, <<).

5- Execução real com fork/execve, depois que o parser montar a      estrutura.


// ORDEM DE PRECEDENCIA DOS OPERADORES:
// 	||				- menor precedencia  - topo da arvore
// 	&&
// 	|
// 	()
// 	<, >, <<, >>	- maior precedencia

// apartir do no de menor precedencia a arvore e quebrada em dois
// esquerda e direita do no de topo
// e assim por diante sempre procurando operadores