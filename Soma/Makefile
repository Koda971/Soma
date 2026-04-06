# 1. Variabili di Configurazione
CC       := gcc
CFLAGS   := -Wall -Wextra -Iinclude -g
LDFLAGS  := 
TARGET   := bin/programma

# 2. Individuazione automatica dei file
SRCS     := $(wildcard src/*.c)
OBJS     := $(patsubst src/%.c, build/%.o, $(SRCS))

# 3. Regola principale (Default)
all: $(TARGET)

# 4. Linking dell'eseguibile
$(TARGET): $(OBJS) | bin
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# 5. Compilazione dei file oggetto (Pattern Rule)
build/%.o: src/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

# 6. Creazione delle cartelle se non esistono
bin build:
	mkdir -p $@

# 7. Pulizia
.PHONY: all clean

clean:
	rm -rf build bin