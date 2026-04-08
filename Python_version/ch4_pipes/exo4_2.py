import os, sys

r, w = os.pipe()
if os.fork() == 0:
    os.dup2(r, 0)
    os.close(r); os.close(w)
    print("Trouvé" if sys.stdin.read(1) == '1' else "Non trouvé")
else:
    os.dup2(w, 1)
    os.close(r); os.close(w)
    mot = input()
    with open("fichier.txt", "a+") as f:
        f.seek(0)
        print('1' if mot in f.read().split() else '0', end='')
    os.wait()
