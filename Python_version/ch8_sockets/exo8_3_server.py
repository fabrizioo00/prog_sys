import socket, time, os

os.makedirs("/home/save", exist_ok=True)
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind(('', 8082)); s.listen(1)
    print("Serveur 8082 pour sauvegardes")
    while True:
        conn, addr = s.accept()
        data = conn.recv(4096)
        with open(f"/home/save/file_{addr[0]}_{time.strftime('%Y_%m_%d')}.txt", "wb") as f:
            while data:
                f.write(data)
                data = conn.recv(4096)
        conn.close()
