import socket, threading

with socket.socket() as s:
    s.bind(('', 8085)); s.listen(2)
    c1, _ = s.accept(); c2, _ = s.accept()
    def relay(a, b):
        while True:
            try: b.sendall(a.recv(1024))
            except: break
    threading.Thread(target=relay, args=(c1, c2), daemon=True).start()
    relay(c2, c1)
