import os, signal, time
def handler(s, f):
    with open("/tmp/entier.txt") as file: print("Lu:", file.read())
signal.signal(signal.SIGUSR1, handler)
print("PID:", os.getpid())
while True: time.sleep(1)
