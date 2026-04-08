import os

if os.fork() == 0:
    print("je suis le fils 1")
elif os.fork() == 0:
    print("je suis le fils 2")
else:
    print("je suis le père")
    os.wait(); os.wait()
