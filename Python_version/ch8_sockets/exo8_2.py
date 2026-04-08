import socket

def load_auth():
    try: return dict(line.split() for line in open("add_autoris.txt"))
    except: return {"127.0.0.1": "Fabrizio"}

auth = load_auth()

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind(('', 8081)); s.listen(1)
    print("Serveur 8081")
    while True:
        conn, addr = s.accept()
        ip = addr[0]
        if ip in auth: conn.sendall(f"Bienvenue {auth[ip]}\n".encode())
        else: conn.sendall(b"Acces refuse\n")
        conn.close()
