import shutil, os

while (d := input("Dossier (q pour quitter): ")) != 'q':
    shutil.copytree(os.getcwd(), d, dirs_exist_ok=True)
