import socket
import threading

users = {
    'habibi': '123456',  
    'labubu': '654321'   
}

clients = {}

def client_handler(client_socket, client_address):
    while True:
        try:
            message = client_socket.recv(1024).decode('utf-8')
            if not message:
                break
            if message.startswith('LOGIN'):
                username, password = message[6:].split(':')
                if username in users and users[username] == password:
                    client_socket.send('LOGIN_SUCCESS'.encode('utf-8'))
                    clients[username] = client_socket
                    print(f"{username} logged in.")
                else:
                    client_socket.send('LOGIN_FAIL'.encode('utf-8'))
                    break
            elif message.startswith('MSG'):
                sender, receiver, content = message[4:].split(':')
                if receiver in clients:
                    clients[receiver].send(f'MSG:{sender}:{content}'.encode('utf-8'))
                else:
                    client_socket.send('MSG_FAIL'.encode('utf-8'))
        except ConnectionResetError:
            break
    client_socket.close()

def start_server(host, port):
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((host, port))
    server_socket.listen(5)
    print(f"Server is running on {host}:{port}")
    while True:
        client_socket, client_address = server_socket.accept()
        print(f"Connection from {client_address}")
        thread = threading.Thread(target=client_handler, args=(client_socket, client_address))
        thread.start()

if __name__ == '__main__':
    start_server('localhost', 12345)
