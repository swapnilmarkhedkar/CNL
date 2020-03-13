import socket
# import time
import threading

class Server:
	clients = []
	def __init__(self):
		self.serv = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

		self.serv.bind(('127.0.0.1',8000))
		print('Socket Binded to :', str(8000))

	def sender(self):
		while True:
			self.data = input()
			for i in self.clients:
				self.serv.sendto(self.data.encode(),i)

	def receiver(self):
		while True:
			msg, self.addr = self.serv.recvfrom(50)

			if self.addr not in self.clients:
				self.clients.append(self.addr)
			else:
				msg = msg.decode()
				print('Message from',str(self.addr),':',msg)
				msg = msg + "|||" + str(self.addr)
				for i in self.clients:
					if(i != self.addr):
						self.serv.sendto(msg.encode("utf-8"), i)


	def chatWindow(self):
		threadS = threading.Thread(target = self.sender)
		threadR = threading.Thread(target = self.receiver)

		threadS.start()
		threadR.start()

server = Server()
server.chatWindow()