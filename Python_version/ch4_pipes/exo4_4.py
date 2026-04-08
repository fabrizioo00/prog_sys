import os

r, w = os.pipe()
os.set_inheritable(r, True)
if os.fork() == 0:
    os.close(w)
    os.environ["TUBE_R"] = str(r)
    os.execv("/usr/bin/python3", ["python3", "exo4_4_fils.py"])
else:
    os.close(r)
    os.write(w, b"Salut depuis le pere (env)")
    os.wait()
