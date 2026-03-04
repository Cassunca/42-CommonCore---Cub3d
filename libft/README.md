# 📚 Libft

> `libft` é uma implementação personalizada de funções essenciais da biblioteca padrão do C,  
> complementada por utilitários adicionais que servem como base para projetos futuros na 42.  
> Este projeto é um excelente exercício para manipulação de memória, strings e operações de baixo nível,  
> além de reforçar conceitos fundamentais de programação em C.

![Banner](https://img.shields.io/badge/Project-libft-blueviolet) ![C](https://img.shields.io/badge/Language-C-red) ![License](https://img.shields.io/badge/License-MIT-green)

---

## 🎯 Objetivo

O objetivo da **libft** é criar, do zero, uma biblioteca em C contendo funções essenciais  
— tanto da **biblioteca padrão** quanto utilitários extras — para servir como  
**base sólida** no desenvolvimento de projetos futuros.  

Este projeto desafia á:
- 🧠 **Aprofundar** o entendimento sobre ponteiros, arrays e alocação dinâmica de memória.  
- 🛠 **Reimplementar** funções da `libc` para compreender seu funcionamento interno.  
- 🚀 **Desenvolver** novas funções utilitárias para manipulação de strings, memória e listas.  
- 📚 Criar um **repertório de código reutilizável** para economizar tempo nos próximos projetos.  

No final, você terá uma biblioteca **própria**, **eficiente** e **pronta para uso.**

## ⚙️ Funcionalidade

A **libft** fornece um conjunto de funções escritas em C que replicam comportamentos  
da biblioteca padrão e adicionam novas ferramentas úteis.  

Ela é dividida em três partes principais:  
1. **Funções da libc** 🏛 — Implementações próprias de funções como `strlen`, `strcpy`, `memset`, etc.  
2. **Funções adicionais** ✨ — Novas funções para manipulação de strings, conversões e memória.  
3. **Bônus (opcional)** 🧩 — Manipulação de listas encadeadas para praticar estruturas de dados.  

Com ela, você poderá:
- 📏 Medir, copiar e modificar strings.
- 🔍 Pesquisar caracteres e substrings.
- 🧮 Converter valores e dados.
- 🗂 Manipular blocos de memória.
- 🪢 Criar e gerenciar listas encadeadas.

Em resumo: a **libft** é uma biblioteca pronta para ser incluída e  
reutilizada em qualquer projeto futuro na 42.


## 🧩 Conceito Trabalhado

O projeto **libft** aprofunda o contato com os fundamentos da linguagem C,  
permitindo ganhar autonomia e domínio do código, com:

- 📦 **Manipulação de memória** — para gerenciar alocações, liberações e cópias de dados.  
- 🧭 **Uso de ponteiros** — para navegar e acessar diretamente posições de memória.  
- ✍ **Tratamento de strings como arrays de caracteres** — para manipulações textuais em baixo nível.  
- 🔄 **Conversão de tipos** — para trabalhar com diferentes formatos de dados.  
- 🔍 **Implementação de algoritmos básicos** — para busca, cópia, comparação e transformação de informações.  
- 🗂 **Organização modular do código** — com cabeçalhos, arquivos `.c` e Makefile bem estruturados.  

## 📂 Arquivos

| Arquivo/Pasta      | Descrição                                                                 |
|--------------------|---------------------------------------------------------------------------|
| `Makefile`         | Script para compilar, recompilar e limpar a biblioteca                    |
| `srcs/part1`       | Funções da primeira parte (reimplementações da `libc`)                    |
| `srcs/part2`       | Funções adicionais para manipulação de strings, memória e conversões      |
| `srcs/bonus`       | Funções bônus para manipulação de listas encadeadas                       |
| `srcs/includes`    | Arquivos de cabeçalho (`.h`) com protótipos e definições necessárias       |


### 🔧 Como Compilar e Usar

Para compilar a **libft** e gerar o arquivo `libft.a`, utilize no terminal:
```bash
make
```
♻️ Comandos Úteis

`make clean`	Remove apenas os arquivos objeto (.o)

`make fclean`	Remove os arquivos objeto e a biblioteca compilada

`make re`	Executa fclean e recompila tudo do zero

### 💻 Como Usar

#### Para usar basta incluir o Header:
Inclua o arquivo de cabeçalho no seu código:
```C
#include "libft.h"
```
E compilar usando a biblioteca:
```bash
make              # Compila a biblioteca e gera libft.a
gcc main.c libft.a -I ./srcs/includes
./a.out
```
> Ou alterar o Makefile para compilar junto com o seu main.c

## 📚 Funções Implementadas na Libft – Descrição e Exemplos

#### 🔗 Parte 1.
| Função       | Parâmetros | Retorno | Descrição curta | Exemplo de uso |
|--------------|-----------|---------|-----------------|----------------|
| `ft_atoi`    | `const char *str` | `int` | Converte string numérica em inteiro | `ft_atoi("42") // 42` |
| `ft_bzero`   | `void *s`, `size_t n` | `void` | Preenche `n` bytes de `s` com `0` | `ft_bzero(buf, 10)` |
| `ft_calloc`  | `size_t nmemb`, `size_t size` | `void *` | Aloca memória e zera | `ft_calloc(5, sizeof(int))` |
| `ft_isalnum` | `int c` | `int` | Verifica se é alfanumérico | `ft_isalnum('A') // 1` |
| `ft_isalpha` | `int c` | `int` | Verifica se é letra | `ft_isalpha('z') // 1` |
| `ft_isascii` | `int c` | `int` | Verifica se é caractere ASCII | `ft_isascii(128) // 0` |
| `ft_isdigit` | `int c` | `int` | Verifica se é dígito | `ft_isdigit('5') // 1` |
| `ft_isprint` | `int c` | `int` | Verifica se é imprimível | `ft_isprint('\n') // 0` |
| `ft_memchr`  | `const void *s`, `int c`, `size_t n` | `void *` | Encontra 1ª ocorrência de `c` em `s` | `ft_memchr("abc", 'b', 3)` |
| `ft_memcmp`  | `const void *s1`, `const void *s2`, `size_t n` | `int` | Compara blocos de memória | `ft_memcmp("abc","abd",3)` |
| `ft_memcpy`  | `void *dest`, `const void *src`, `size_t n` | `void *` | Copia `n` bytes de `src` para `dest` | `ft_memcpy(buf1, buf2, 5)` |
| `ft_memmove` | `void *dest`, `const void *src`, `size_t n` | `void *` | Copia memória com sobreposição segura | `ft_memmove(buf+1, buf, 5)` |
| `ft_memset`  | `void *s`, `int c`, `size_t n` | `void *` | Preenche memória com valor `c` | `ft_memset(buf, 'A', 5)` |
| `ft_strchr`  | `const char *s`, `int c` | `char *` | Encontra 1ª ocorrência de `c` na string | `ft_strchr("hello",'e')` |
| `ft_strdup`  | `const char *s` | `char *` | Duplica string (aloca nova) | `ft_strdup("42")` |
| `ft_strlcat` | `char *dst`, `const char *src`, `size_t size` | `size_t` | Concatena strings com limite de tamanho | `ft_strlcat(buf,"abc",10)` |
| `ft_strlcpy` | `char *dst`, `const char *src`, `size_t size` | `size_t` | Copia string com limite de tamanho | `ft_strlcpy(buf,"abc",10)` |
| `ft_strlen`  | `const char *s` | `size_t` | Retorna tamanho da string | `ft_strlen("42") // 2` |
| `ft_strncmp` | `const char *s1`, `const char *s2`, `size_t n` | `int` | Compara até `n` caracteres | `ft_strncmp("abc","abd",2)` |
| `ft_strnstr` | `const char *haystack`, `const char *needle`, `size_t len` | `char *` | Busca substring em tamanho limitado | `ft_strnstr("abcde","cd",5)` |
| `ft_strrchr` | `const char *s`, `int c` | `char *` | Encontra última ocorrência de `c` | `ft_strrchr("banana",'a')` |
| `ft_tolower` | `int c` | `int` | Converte caractere para minúsculo | `ft_tolower('A') // 'a'` |
| `ft_toupper` | `int c` | `int` | Converte caractere para maiúsculo | `ft_toupper('a') // 'A'` |

#### 🔗 Parte 2.
| Função | Parâmetros | Retorno | Descrição curta | Exemplo de uso |
|--------|-----------|---------|-----------------|----------------|
| `ft_itoa` | `int n` | `char *` | Converte inteiro em string (aloca nova) | `ft_itoa(42); // "42"` |
| `ft_putchar_fd` | `char c`, `int fd` | `void` | Escreve caractere no file descriptor | `ft_putchar_fd('A', 1);` |
| `ft_putendl_fd` | `char *s`, `int fd` | `void` | Escreve string + `\n` no file descriptor | `ft_putendl_fd("Hello", 1);` |
| `ft_putnbr_fd` | `int n`, `int fd` | `void` | Escreve número no file descriptor | `ft_putnbr_fd(42, 1);` |
| `ft_putstr_fd` | `char *s`, `int fd` | `void` | Escreve string no file descriptor | `ft_putstr_fd("Hello", 1);` |
| `ft_split` | `const char *s`, `char c` | `char **` | Divide string em substrings usando `c` como delimitador | `ft_split("a,b,c", ',');` |
| `ft_striteri` | `char *s`, `void (*f)(unsigned int, char*)` | `void` | Aplica função `f` a cada caractere, passando índice | `ft_striteri(str, f);` |
| `ft_strjoin` | `char const *s1`, `char const *s2` | `char *` | Junta duas strings em uma nova (alocada) | `ft_strjoin("Hello", "World");` |
| `ft_strmapi` | `char const *s`, `char (*f)(unsigned int, char)` | `char *` | Aplica `f` a cada caractere e retorna nova string | `ft_strmapi("abc", f);` |
| `ft_strtrim` | `char const *s1`, `char const *set` | `char *` | Remove do início/fim caracteres de `set` | `ft_strtrim(" 42 ", " ");` |
| `ft_strrstr` | `const char *haystack`, `const char *needle` | `char *` | **(não faz parte padrão, mas parece busca reversa)** | *(depende da implementação)* |
| `ft_substr` | `char const *s`, `unsigned int start`, `size_t len` | `char *` | Retorna substring a partir de `start` com tamanho `len` | `ft_substr("Hello", 1, 3); // "ell"` |


#### 🔗 Bônus – Manipulação de Listas Ligadas (t_list)
| Função | Parâmetros | Retorno | Descrição curta | Exemplo de uso |
|--------|-----------|---------|-----------------|----------------|
| `ft_lstnew` | `void *content` | `t_list *` | Cria novo nó com `content` e `next = NULL` | `t_list *n = ft_lstnew("Oi");` |
| `ft_lstadd_front` | `t_list **lst`, `t_list *new` | `void` | Adiciona nó `new` no início da lista | `ft_lstadd_front(&lst, new);` |
| `ft_lstadd_back` | `t_list **lst`, `t_list *new` | `void` | Adiciona nó `new` no final da lista | `ft_lstadd_back(&lst, new);` |
| `ft_lstsize` | `t_list *lst` | `int` | Retorna quantidade de nós na lista | `ft_lstsize(lst);` |
| `ft_lstlast` | `t_list *lst` | `t_list *` | Retorna último nó da lista | `ft_lstlast(lst);` |
| `ft_lstdelone` | `t_list *lst`, `void (*del)(void *)` | `void` | Libera nó usando função `del` no conteúdo | `ft_lstdelone(node, free);` |
| `ft_lstclear` | `t_list **lst`, `void (*del)(void *)` | `void` | Remove e libera todos os nós | `ft_lstclear(&lst, free);` |
| `ft_lstiter` | `t_list *lst`, `void (*f)(void *)` | `void` | Aplica função `f` em cada conteúdo da lista | `ft_lstiter(lst, print);` |
| `ft_lstmap` | `t_list *lst`, `void *(*f)(void *)`, `void (*del)(void *)` | `t_list *` | Cria nova lista aplicando `f` a cada conteúdo | `ft_lstmap(lst, dup, free);` |

##### 📌 Observações:

Todas essas funções usam a estrutura t_list definida no cabeçalho da libft, geralmente assim:
```c
typedef struct s_list {
    void            *content;
    struct s_list   *next;
} t_list;
```
Os exemplos são apenas ilustrativos e assumem que lst já foi criada corretamente.

---

## 👩‍💻 Autoria

**✨ Amy Rodrigues ✨** 

🎓 Estudante de C e desenvolvimento de baixo nível na [42 São Paulo](https://www.42sp.org.br/)

🐧 Usuária de Linux | 💻 Fã de terminal | 🎯 Apaixonada por entender como tudo funciona por trás dos bastidores

---

## 📎 Licença

Este projeto foi desenvolvido como parte do currículo educacional da 42 São Paulo.

📘 **Uso permitido**:
- Pode ser utilizado como referência para estudos e aprendizado individual
- Pode servir de inspiração para seus próprios projetos

🚫 **Proibido**:
- Submeter cópias deste projeto como se fossem de sua autoria em avaliações da 42 ou outras instituições

Seja ético e contribua para uma comunidade de desenvolvedores mais honesta e colaborativa 🤝
