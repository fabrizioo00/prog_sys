import sys, os

for d in sys.argv[1:]:
    for f in os.listdir(d):
        p = os.path.join(d, f)
        if os.path.isfile(p) and (st := os.stat(p)).st_size > 10**6:
            print(f"{p}: UID {st.st_uid}")
