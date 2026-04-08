import os

f = input("Nom de fichier: ")
os.execvp("emacs", ["emacs", f])
