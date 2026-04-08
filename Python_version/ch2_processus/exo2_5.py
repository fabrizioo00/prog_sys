import os, time, random

start = time.time()
if os.fork() == 0:
    time.sleep(random.randint(1, 10))
elif os.fork() == 0:
    time.sleep(random.randint(1, 10))
else:
    os.wait(); os.wait()
    print(f"Durée totale: {time.time() - start:.2f} s")
