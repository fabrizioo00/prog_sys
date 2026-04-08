import threading, random

class RetThread(threading.Thread):
    def run(self): self.tab = [random.randint(0, 99) for _ in range(10)]

t = RetThread()
t.start(); t.join()
print(t.tab)
