import socket

socket_file = '/tmp/image_transfer_socket'
image_file_path = '/home/mathi/simulations/unix_sockets/unixdomainsockets/Mathivanan.png'

client_socket = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
client_socket.connect(socket_file)

try:
    with open(image_file_path, 'rb') as image_file:
        while True:
            parted_data = image_file.read(4096)
            if not parted_data:
                break
            client_socket.sendall(parted_data)
finally:
    client_socket.close()

