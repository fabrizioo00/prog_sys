import os

r, w = os.pipe()
if os.fork() == 0:
    os.close(w)
    print("Trouvé" if os.read(r, 1) == b'1' else "Non trouvé")
else:
    os.close(r)
    mot = input("Mot à chercher: ")
    with open("fichier.txt", "a+") as f:
        f.seek(0)
        os.write(w, b'1' if mot in f.read().split() else b'0')
    os.wait()
