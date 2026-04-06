
La Struttura Ideale del Progetto
Immaginiamo questa gerarchia di cartelle:

src/: i file .c

include/: i file .h

build/: i file oggetto .o (per non sporcare i sorgenti)

bin/: l'eseguibile finale



Perché questo Makefile è "Best Practice"?
Variabili (CC, CFLAGS): Se domani decidi di usare clang invece di gcc, devi cambiare solo una riga.

Funzioni (wildcard, patsubst): Non devi elencare ogni file .c a mano. Se aggiungi player.c nella cartella src, il Makefile lo troverà da solo.

Target "Phony": .PHONY impedisce a make di confondersi nel caso esistesse davvero un file chiamato "clean" o "all" nella tua cartella.

Automatic Variables ($<, $@): * $@: Rappresenta il nome del target (quello a sinistra di :).

$<: Rappresenta la prima dipendenza (il file sorgente).

Order-only dependencies (|): La sintassi | build dice a Make: "Crea la cartella se non c'è, ma non ricompilare tutto ogni volta che la data della cartella cambia".

Come usarlo
Salva il codice sopra in un file chiamato esattamente Makefile.

Apri il terminale e digita make.

Per ricominciare da zero, digita make clean.