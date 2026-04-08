import os

for _ in range(5):
    if os.fork() == 0:
        break
else:
    for _ in range(5): os.wait()
