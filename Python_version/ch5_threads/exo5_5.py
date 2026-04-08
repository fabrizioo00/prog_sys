import threading, random, time, sys

compt, mutex = 0, threading.Lock()
limit = int(sys.argv[1]) if len(sys.argv) > 1 else 10

def t1():
    global compt
    while compt < limit:
        with mutex: compt += 1
        time.sleep(random.randint(1, 5))

def t2():
    while compt < limit:
        with mutex: print(compt)
        time.sleep(2)

th1, th2 = threading.Thread(target=t1), threading.Thread(target=t2)
th1.start(); th2.start(); th1.join(); th2.join()
