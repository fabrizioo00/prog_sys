import threading, time, random

N, M = int(input("N lecteurs: ")), int(input("M rédacteurs: "))
db = [0] * 15
readers, lock, write_lock = 0, threading.Lock(), threading.Lock()

def reader(i):
    global readers
    while True:
        time.sleep(random.randint(1, 3))
        with lock:
            readers += 1
            if readers == 1: write_lock.acquire()
        print(f"L{i} lit {db[random.randint(0, 14)]}")
        with lock:
            readers -= 1
            if readers == 0: write_lock.release()

def writer(i):
    while True:
        time.sleep(random.randint(1, 10))
        with write_lock:
            db[random.randint(0, 14)] = random.randint(1, 99)
            print(f"E{i} écrit")

for i in range(N): threading.Thread(target=reader, args=(i,), daemon=True).start()
for i in range(M): threading.Thread(target=writer, args=(i,), daemon=True).start()
time.sleep(15)
