# Soma

Un'implementazione da zero di una Rete Neurale Artificiale (ANN) scritta interamente in C puro, senza l'ausilio di librerie di machine learning esterne. Il progetto esplora i fondamenti del Deep Learning, implementando manualmente l'architettura Multi-Layer Perceptron (MLP), l'algoritmo di backpropagation e la discesa del gradiente per l'ottimizzazione dei pesi.

## ✨ Caratteristiche
* 🚀 **Performance:** Scritto in C puro per la massima velocità.
* 🛠️ **Modularità:** Separazione netta tra logica di interfaccia (`.h`) e implementazione (`.c`).
* 📦 **Facile da integrare:** Include un Makefile pronto all'uso.

## 📋 Prerequisiti
Prima di iniziare, assicurati di avere installato:
* **GCC**
* **Make**

## ⚙️ Installazione e Compilazione
Clona il repository e compila il progetto:

```bash
git clone https://github.com/Koda971/Soma.git
cd Soma
make
```

## 📂 Struttura del Progetto
La disposizione dei file segue gli standard dei progetti in C per mantenere separati i sorgenti, le intestazioni e i dati:

```text
.
├── src/        # File sorgente (.c) - Contiene la logica e l'implementazione
├── include/    # File header (.h) - Definizioni delle strutture e prototipi
├── resources/  # Dataset - File di input per il training
├── bin/        # Eseguibile finale - File compilati pronti all'uso
└── Makefile    # Script per l'automazione della compilazione
