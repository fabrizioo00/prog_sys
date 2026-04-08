import os, struct

tab = [1, 2, 3, 4]
with open("data.bin", "wb") as f:
    f.write(struct.pack(f"{len(tab)}i", *tab))
os.chmod("data.bin", 0o624)

with open("data.bin", "rb") as f:
    d = f.read()
    print(struct.unpack(f"{len(d)//4}i", d))
