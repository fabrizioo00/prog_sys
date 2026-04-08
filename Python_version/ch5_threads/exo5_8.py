import threading, random, time, sys

N = int(sys.argv[1]) if len(sys.argv) > 1 else 3
barrier = threading.Barrier(N)

def task(tid):
    for _ in range(10):
        time.sleep(random.randint(1, 5))
        print(f"Thread {tid} à la barrière")
        barrier.wait()

for i in range(N): threading.Thread(target=task, args=(i,)).start()
