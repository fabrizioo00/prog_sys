import threading
import random

tab = []

def init_tab(n):
    global tab
    tab = [random.randint(0, 99) for _ in range(n)]

def search_x(x, res):
    res.append(1 if x in tab else 0)

t1 = threading.Thread(target=init_tab, args=(10,))
t1.start()
t1.join()

x = int(input("x ?: "))
res = []
t2 = threading.Thread(target=search_x, args=(x, res))
t2.start()
t2.join()
print("Trouvé" if res[0] else "Non")
