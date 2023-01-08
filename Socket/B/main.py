import socket


class Client:

    def __init__(self, host, port):
        self.host = host
        self.port = port

    def connect(self):
        client_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        client_sock.connect((self.host, self.port))

        message = client_sock.recv(1024)
        print(message.decode("ascii"))
        message = "Hi from client!"
        client_sock.send(message.encode("ascii"))
        client_sock.close()

def main():
    client = Client("127.0.0.1", 9999)
    client.connect()


if __name__ == "__main__":
    main()
