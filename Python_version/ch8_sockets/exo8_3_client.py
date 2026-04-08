import socket, sys

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect(('127.0.0.1', 8082))
    with open(sys.argv[1], "rb") as f:
        s.sendall(f.read())
