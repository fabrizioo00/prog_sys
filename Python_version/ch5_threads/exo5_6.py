import threading
import random
import time
import sys

t = [0] + [random.uniform(0, 100) for _ in range(98)] + [0]
lock = threading.Lock()
running = True

def t1():
    while running:
        with lock:
            for i in range(1, 99):
                t[i] = (t[i-1] + t[i] + t[i+1]) / 3
        time.sleep(random.randint(1, 3))

def t2():
    iterations = 0
    while running and iterations < 10:
        with lock:
            print(f"Iteration {iterations}: {t[:5]} ...")
        time.sleep(4)
        iterations += 1

th1 = threading.Thread(target=t1, daemon=True)
th2 = threading.Thread(target=t2)
th1.start()
th2.start()

try:
    th2.join()
except KeyboardInterrupt:
    running = False
    print("\nArret des threads")

running = False
th1.join(timeout=2)
