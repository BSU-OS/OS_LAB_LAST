import socket


class Server:

    def __init__(self, host, port):
        self.host = host
        self.port = port

    def start(self):
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.bind((self.host, self.port))
        sock.listen()
        print("Server started on port %d" % self.port)

        while True:
            client, address = sock.accept()
            print("connection established to client: {} on port {}".format(client, address))
            message = "Hi from server!"
            client.send(message.encode("ascii"))
            message = client.recv(1024)
            print(message.decode("ascii"))
            client.close()


def main():
    server = Server("127.0.0.1", 9999)
    server.start()


if __name__ == "__main__":
    main()
