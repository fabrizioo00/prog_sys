"""exo5_4_fixed.py - Fixed os._exit usage"""
import threading
import random
import sys

T1, T2 = [], []

def gen(T, size):
    T.extend([random.randint(0, 99) for _ in range(size)])

def user_input():
    if input() == 'A':
        print("Annulé")
        sys.exit(0)

threading.Thread(target=user_input, daemon=True).start()

t1 = threading.Thread(target=gen, args=(T1, 5))
t2 = threading.Thread(target=gen, args=(T2, 10))
t1.start()
t2.start()
t1.join()
t2.join()

res = []
tc = threading.Thread(target=lambda: res.append(all(x in T2 for x in T1)))
tc.start()
tc.join()
print("T1 dans T2" if res[0] else "T1 pas dans T2")
