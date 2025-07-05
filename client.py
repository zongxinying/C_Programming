import socket
import sys

def login(client_socket, username, password):
    client_socket.send(f'LOGIN:{username}:{password}'.encode('utf-8'))
    response = client_socket.recv(1024).decode('utf-8')
    if response == 'LOGIN_SUCCESS':
        print(f"{username} logged in successfully.")
    else:
        print("Login failed.")
        return False
    return True

def send_message(client_socket, receiver, content):
    client_socket.send(f'MSG:{username}:{receiver}:{content}'.encode('utf-8'))

def receive_message(client_socket):
    while True:
        message = client_socket.recv(1024).decode('utf-8')
        if message.startswith('MSG:'):
            sender, content = message[4:].split(':')
            print(f"Message from {sender}: {content}")
        else:
            print(message)

if __name__ == '__main__':
    host = 'localhost'
    port = 12345

    if len(sys.argv) != 3:
        print("Usage: python client.py <username> <password>")
        sys.exit(1)

    username = sys.argv[1]
    password = sys.argv[2]

    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect((host, port))

    if login(client_socket, username, password):
        try:
            while True:
                content = input("Enter message (type 'exit' to quit): ")
                if content.lower() == 'exit':
                    break
                receiver = input("Enter receiver's username: ")
                send_message(client_socket, receiver, content)
                receive_message(client_socket)
        finally:
            client_socket.close()
