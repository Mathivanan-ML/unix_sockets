import socket
import os

socket_file = '/tmp/image_transfer_socket'
output_file_path = 'received_image.png'

if os.path.exists(socket_file):
    os.remove(socket_file)

server_socket = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
server_socket.bind(socket_file)
server_socket.listen(1)

print("Server is ready to receive image...")

try:
    connection, _ = server_socket.accept()
    with open(output_file_path, 'wb') as output_file:
        while True:
            data = connection.recv(4096)
            if not data:
                break
            output_file.write(data)
    print("Image received and saved to", output_file_path)
finally:
    connection.close()
    server_socket.close()
    os.remove(socket_file)

