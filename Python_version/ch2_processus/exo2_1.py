import os

if os.fork() == 0:
    print("je suis le fils")
else:
    print("je suis le père")
    os.wait()
