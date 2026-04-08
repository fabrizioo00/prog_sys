import os

while (f := input("Fichier (q pour quitter): ")) != 'q':
    if os.fork() == 0:
        os.execvp("emacs", ["emacs", f])
    os.wait()
