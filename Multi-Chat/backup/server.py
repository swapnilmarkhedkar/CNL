import socket
# import time
import threading

class Server:
	clients = []
	def __init__(self):
		self.serv = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
		self.serv.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

		self.serv.bind(('127.0.0.1',8000))
		self.serv.listen(5)
		print('Waiting for Client')

		self.client_socket, self.address = self.serv.accept()
		print('Connected to Client')
		# self.client_socket.send("Hello".encode())

	def sender(self):
		while True:
			self.data = input()
			for i in self.clients:
				self.client_socket.send(self.data)

	def receiver(self):
		while True:
			msg, self.addr = self.client_socket.recv(5).decode()

			if self.addr not in self.clients:
				self.clients.append(self.addr)
			else:
				print('Message from',str(self.addr),':',msg)
				for i in self.clients:
					if i!=self.addr:
						client_socket.send(msg.encode())


	def chatWindow(self):
		threadS = threading.Thread(target = self.sender)
		threadR = threading.Thread(target = self.receiver)

		threadS.start()
		threadR.start()

server = Server()
server.chatWindow()