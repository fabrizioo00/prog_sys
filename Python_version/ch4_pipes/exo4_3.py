import os

r, w = os.pipe()
os.set_inheritable(r, True)
if os.fork() == 0:
    os.close(w)
    os.execv("/usr/bin/python3", ["python3", "exo4_3_fils.py", str(r)])
else:
    os.close(r)
    os.write(w, b"Salut depuis le pere")
    os.wait()
