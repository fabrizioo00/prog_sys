import socket, sys, shutil
shutil.make_archive('/tmp/archive', 'tar', sys.argv[1])
with socket.socket() as s:
    s.connect(('127.0.0.1', 8084))
    s.sendall(open('/tmp/archive.tar', 'rb').read())
