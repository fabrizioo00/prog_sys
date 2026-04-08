import os
print("Fils a reçu:", os.read(int(os.environ["TUBE_R"]), 100).decode())
