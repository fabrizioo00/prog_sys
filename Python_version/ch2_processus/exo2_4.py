import os

for i in range(1, 6):
    if os.fork() == 0:
        print(f"je suis le fils {i}")
        break
else:
    for _ in range(5): os.wait()
