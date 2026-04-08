import os, sys
print("Fils a reçu:", os.read(int(sys.argv[1]), 100).decode())
