import socket
import os

socket_file = '/tmp/unix_socket'

client_socket = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)

client_socket.connect(socket_file)

try:
    while(True):
        data = input()
        if data=='q':
            print("exited")
            exit(0)
        try:
            client_socket.sendall(data.encode('utf-8'))
        except BrokenPipeError:
            print("Connection broken with the client")
        response = client_socket.recv(1024)
        
        print("Received from server:", response.decode())

except Exception as e:
    print(e)

finally:
    client_socket.close()
