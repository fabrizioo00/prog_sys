import socket, time, os

def load_db():
    try: return {k: float(v) for k, v in (line.split() for line in open("db.txt"))}
    except: return {"pomme": 2.5, "poire": 3.0}

db = load_db()

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind(('', 8080)); s.listen(1)
    print("Serveur 8080")
    conn, addr = s.accept()
    with conn:
        conn.sendall(b"Nom: "); nom = conn.recv(1024).decode().strip()
        conn.sendall(b"Produits (nom:qty nom:qty): "); prods = conn.recv(1024).decode().strip()
        try: total = sum(db.get(p, 0) * int(q) for p, q in (x.split(':') for x in prods.split()))
        except: total = 0
        conn.sendall(f"Total: {total}\n".encode())
        with open(f"cmd_{time.strftime('%Y%m%d%H%M%S')}.txt", "w") as f:
            f.write(f"{nom} a commande {prods} pour {total}")
