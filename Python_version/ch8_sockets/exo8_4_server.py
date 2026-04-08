import socket, time
with socket.socket() as s:
    s.bind(('', 8084)); s.listen(1)
    conn, addr = s.accept()
    with open(f"/home/save/archive_{addr[0]}_{time.time()}.tar", "wb") as f:
        while (d:=conn.recv(4096)): f.write(d)
