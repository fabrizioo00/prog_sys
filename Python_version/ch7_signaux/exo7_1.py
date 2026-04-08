import os, signal, sys

if (pid := os.fork()) == 0:
    while True: pass
else:
    while True:
        c = input("s/r/q: ")
        if c == 's': os.kill(pid, signal.SIGSTOP)
        elif c == 'r': os.kill(pid, signal.SIGCONT)
        elif c == 'q':
            os.kill(pid, signal.SIGKILL); sys.exit(0)
