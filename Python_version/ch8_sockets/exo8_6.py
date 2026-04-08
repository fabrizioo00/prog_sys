import socket, threading

clients = set()
with socket.socket() as s:
    s.bind(('', 8086)); s.listen()
    def handle(c):
        while True:
            try:
                data = c.recv(1024)
                if not data: break
                for x in list(clients):
                    if x != c:
                        try: x.sendall(data)
                        except: clients.discard(x)
            except: break
        clients.discard(c)
    while True:
        c, _ = s.accept(); clients.add(c)
        threading.Thread(target=handle, args=(c,), daemon=True).start()
