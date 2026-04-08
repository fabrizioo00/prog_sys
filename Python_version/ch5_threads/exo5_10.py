import threading, queue, random, time

N, M = int(input("N producteurs: ")), int(input("M consommateurs: "))
q = queue.LifoQueue(maxsize=10)

def prod(i):
    while True:
        time.sleep(random.randint(1, 3))
        q.put("O"); print(f"P{i} produit")
def cons(i):
    while True:
        q.get(); print(f"C{i} consomme")
        time.sleep(random.randint(1, 3))

for i in range(N): threading.Thread(target=prod, args=(i,), daemon=True).start()
for i in range(M): threading.Thread(target=cons, args=(i,), daemon=True).start()
time.sleep(10)
