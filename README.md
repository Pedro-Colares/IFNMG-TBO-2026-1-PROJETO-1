# 🎬 Sistema de Consulta de Filmes e Cinemas

## 📌 Introdução

Este projeto é o **Primeiro Projeto da disciplina de Técnicas de Busca e Ordenação**.

O objetivo é aplicar conceitos de **estruturas de dados**, **busca** e **ordenação** em um cenário prático: um sistema de consulta de filmes e cinemas.

A aplicação permite ao usuário realizar buscas complexas combinando filtros com operadores lógicos (`"&"` e `"|"`), simulando um mecanismo de consulta eficiente sobre grandes bases de dados.

---

## ⚙️ Funcionalidades

### 🔎 Consulta de Filmes

O usuário pode filtrar filmes por:

* Tipo (`titleType`)
* Gênero (`genres`)
* Intervalo de duração
* Intervalo de anos

📌 Exemplo:

```
(Comedy | Drama) & ano:2000-2010 & duracao:90-120
```

---

### 🏢 Consulta de Cinemas

O usuário pode buscar cinemas com base em:

* Filmes exibidos
* Gênero dos filmes
* Tipo dos filmes
* Ano de lançamento dos filmes
* Duração dos filmes
* Preço máximo
* Distância máxima de um ponto

📌 Exemplo:

```
(genero:Drama | genero:Comedy) & tipo:tvMovie & ano:2000-2010 & dist:20019,510301,500000 & preco:20
```

---

## 🧠 Estruturas de Dados Utilizadas

### 🔹 Tabela Hash (implementação própria)

Utilizada para:

* Buscar filmes por título
* Mapear filmes → cinemas
* Mapear gêneros → cinemas
* Mapear tipos → cinemas

📌 Vantagens:

* Acesso médio em **O(1)**
* Evita percorrer toda a base

📌 Tratamento de colisão:

* Encadeamento (listas)

---

### 🔹 HashSet

Utilizado para:

* Evitar duplicatas nos resultados
* Operações de união e interseção

---

### 🔹 Vetores + Ordenação

Utilizados para:

* Ordenar filmes por ano e duração
* Ordenar cinemas por preço

📌 Algoritmo:

* MergeSort

---

### 🔹 Busca Binária

Aplicada em:

* Filtros por ano
* Filtros por duração
* Filtros por preço

📌 Complexidade:

* **O(log n)**

---

### 🔹 Grid Espacial (Hash de coordenadas)

Utilizado para busca por distância.

📌 Ideia:

* Divide o espaço em células (blocos)
* Cada cinema pertence a uma célula
* Apenas células próximas são analisadas

📌 Vantagem:

* Evita verificar todos os cinemas
* Reduz drasticamente o custo

---

## 📍 Filtro por Distância

### Funcionamento:

1. O usuário informa:

   * Coordenada `(x, y)`
   * Distância máxima

2. O sistema:

   * Identifica a célula do usuário
   * Calcula o raio de blocos:

     ```
     raio = distMax / TAM + 1
     ```
   * Percorre as células dentro desse raio
   * Calcula a distância euclidiana:

     ```
     dist = sqrt(dx² + dy²)
     ```
   * Filtra apenas os cinemas dentro da distância

---

## 🔗 Sistema de Consulta

As consultas são processadas com:

* Tokenização
* Pilhas
* Operadores lógicos

### Operadores:

* `&` → interseção
* `|` → união
* `()` → prioridade

📌 Exemplo:

```
(Drama | Comedy) & preco:20
```

---

## ⏱️ Desempenho

* O carregamento pode ser mais pesado (pré-processamento)
* As consultas são rápidas devido ao uso de:

  * Hash
  * Índices
  * Busca binária
  * Grid espacial

---

## 📂 Estrutura do Projeto

* `Filmes.*` → Gerencia filmes
* `Cinemas.*` → Gerencia cinemas
* `Hash.*` → Implementação de tabela hash
* `HashSet.*` → Conjunto baseado em hash
* `MergeSort.*` → Ordenação
* `Controller.*` → Interface com o usuário
* `main.cpp` → Execução do programa

---

## 🚀 Como Rodar o Projeto

### 1. Clonar ou baixar o projeto

Você pode baixar o repositório ou copiar os arquivos para sua máquina.

---

### 2. Compilar o código

No terminal, dentro da pasta do projeto:

#### 🔹 Linux / Mac:

```
g++ src/*.cpp -Iinclude -o programa
```

#### 🔹 Windows:

```
g++ src/*.cpp -Iinclude -o programa.exe
```

---

### 3. Executar

#### 🔹 Linux / Mac:

```
./programa
```

#### 🔹 Windows:

```
programa.exe
```

---

### 4. Uso

O sistema exibirá um menu:

```
1. Consultar Filmes
2. Consultar Cinemas
0. Sair
```

* Escolha uma opção
* Digite a consulta desejada
* O sistema retornará:

  * Resultados
  * Quantidade
  * Tempo de execução

---

## 💡 Destaques do Projeto

* Implementação própria de Hash (sem STL)
* Sistema de consultas com operadores lógicos
* Otimização com múltiplas estruturas de dados
* Uso de grid espacial para busca por proximidade

---

## 📊 Complexidade (Resumo)

| Operação              | Complexidade |
| --------------------- | ------------ |
| Busca em hash         | O(1) médio   |
| Busca binária         | O(log n)     |
| Ordenação (MergeSort) | O(n log n)   |
| Filtro por distância  | O(b + c)     |

---

## 🧩 Conclusão

O projeto demonstra como combinar diferentes estruturas de dados para construir um sistema eficiente de busca, equilibrando:

* Tempo de carregamento
* Tempo de consulta
* Uso de memória

A principal ideia é:
👉 **pré-processar bem os dados para consultas rápidas.**

---
