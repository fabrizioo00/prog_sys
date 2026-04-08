import threading, time, random, queue

q = queue.Queue(maxsize=1)
def emetteur():
    while True:
        time.sleep(random.randint(1, 3))
        q.put("X"); print("Emetteur dépose")
def recepteur():
    while True:
        print("Recepteur lit:", q.get())
        time.sleep(random.randint(1, 3))

threading.Thread(target=emetteur, daemon=True).start()
threading.Thread(target=recepteur, daemon=True).start()
time.sleep(10)
