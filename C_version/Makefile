CC=gcc
CFLAGS=-Wall -g
LDPTHREAD=-lpthread
LDMATH=-lm

# Chapter 2
CH2=ch2_processus
CH2_BIN=$(CH2)/ex2_1 $(CH2)/ex2_2 $(CH2)/ex2_3 $(CH2)/ex2_4 $(CH2)/ex2_5

# Chapter 3
CH3=ch3_exec
CH3_BIN=$(CH3)/ex3_1 $(CH3)/ex3_2 $(CH3)/ex3_3 $(CH3)/ex3_4 $(CH3)/ex3_5 $(CH3)/ex3_6

# Chapter 4
CH4=ch4_pipes
CH4_BIN=$(CH4)/ex4_1 $(CH4)/ex4_2 $(CH4)/ex4_3 $(CH4)/ex4_3_fils $(CH4)/ex4_4 $(CH4)/ex4_4_fils

# Chapter 5
CH5=ch5_threads
CH5_BIN=$(CH5)/ex5_1 $(CH5)/ex5_2 $(CH5)/ex5_3 $(CH5)/ex5_4 $(CH5)/ex5_5 \
        $(CH5)/ex5_6 $(CH5)/ex5_7 $(CH5)/ex5_8 $(CH5)/ex5_9 $(CH5)/ex5_10 $(CH5)/ex5_11

# Chapter 6
CH6=ch6_fichiers
CH6_BIN=$(CH6)/ex6_1 $(CH6)/ex6_2 $(CH6)/ex6_3

# Chapter 7
CH7=ch7_signaux
CH7_BIN=$(CH7)/ex7_1 $(CH7)/ex7_2_saisit $(CH7)/ex7_2_affiche $(CH7)/ex7_3 $(CH7)/ex7_4

# Chapter 8
CH8=ch8_sockets
CH8_BIN=$(CH8)/ex8_1_serveur $(CH8)/ex8_2_serveur $(CH8)/ex8_3_client $(CH8)/ex8_3_serveur \
        $(CH8)/ex8_4_client $(CH8)/ex8_4_serveur $(CH8)/ex8_5_serveur $(CH8)/ex8_6_serveur

ALL=$(CH2_BIN) $(CH3_BIN) $(CH4_BIN) $(CH5_BIN) $(CH6_BIN) $(CH7_BIN) $(CH8_BIN)

all: $(ALL)

# Ch2: simple
$(CH2)/%: $(CH2)/%.c
	$(CC) $(CFLAGS) $< -o $@

# Ch3: simple
$(CH3)/%: $(CH3)/%.c
	$(CC) $(CFLAGS) $< -o $@

# Ch4: simple
$(CH4)/%: $(CH4)/%.c
	$(CC) $(CFLAGS) $< -o $@

# Ch5: pthread
$(CH5)/%: $(CH5)/%.c
	$(CC) $(CFLAGS) $< -o $@ $(LDPTHREAD)

# Ch6: simple
$(CH6)/%: $(CH6)/%.c
	$(CC) $(CFLAGS) $< -o $@

# Ch7: simple
$(CH7)/%: $(CH7)/%.c
	$(CC) $(CFLAGS) $< -o $@

# Ch8: pthread for ex8_6
$(CH8)/ex8_6_serveur: $(CH8)/ex8_6_serveur.c
	$(CC) $(CFLAGS) $< -o $@ $(LDPTHREAD)

$(CH8)/%: $(CH8)/%.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(ALL)

.PHONY: all clean
