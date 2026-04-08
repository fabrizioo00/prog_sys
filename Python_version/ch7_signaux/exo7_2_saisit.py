import os, signal
with open("/tmp/entier.txt", "w") as f: f.write(input("Entier: "))
os.kill(int(input("PID affiche.py: ")), signal.SIGUSR1)
