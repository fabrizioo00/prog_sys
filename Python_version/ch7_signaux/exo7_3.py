import os, signal, time, sys

def child(i):
    signal.signal(signal.SIGTERM, lambda s, f: (print(f"Fils {i} tué"), sys.exit(0)))
    while True: time.sleep(1)

signal.signal(signal.SIGTERM, lambda s, f: (print("Père tué"), sys.exit(0)))

pids = []
for i in range(5):
    if (pid := os.fork()) == 0: child(i)
    else: pids.append(pid)

while True:
    try:
        cmd, idx = input("Menu (s,r,t i): ").split()
        idx = int(idx)
        if cmd == 's': os.kill(pids[idx], signal.SIGSTOP)
        elif cmd == 'r': os.kill(pids[idx], signal.SIGCONT)
        elif cmd == 't': os.kill(pids[idx], signal.SIGTERM)
    except Exception: pass
