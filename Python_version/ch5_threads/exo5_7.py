import threading
import time
import sys
import random

compteur = 0
u = 1.0
lock = threading.Lock()
running = True

def worker(f, name):
    global compteur, u
    iterations = 0
    while running and iterations < 20:
        with lock:
            compteur += 1
            u = f(u)
            print(f"[{name}] u={u:.4f}, iter={compteur}")
        time.sleep(random.randint(1, 5))
        iterations += 1

threading.Thread(target=worker, args=(lambda x: (x-1)**2/4, "T1"), daemon=True).start()
threading.Thread(target=worker, args=(lambda x: (x-2)**2/6, "T2"), daemon=True).start()

try:
    time.sleep(15)
except KeyboardInterrupt:
    pass
finally:
    running = False
    print("\nArret des threads")
