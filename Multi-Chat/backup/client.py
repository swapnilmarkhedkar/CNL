import socket
# import time
import threading

class Client:
	def __init__(self):
		self.client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		self.client.connect(('127.0.0.1', 8000))

	def chatWindow(self):
		# self.data = self.client.recv(10).decode()
		# time.sleep(1)
		# print('Server :',self.data)
		threadS = threading.Thread(target = self.sender)
		threadR = threading.Thread(target = self.receiver)

		threadS.start()
		threadR.start()

	def sender(self):
		while True:
			msg = input()
			self.client.send(msg.encode())

	def receiver(self):
		while True:
			msg, self.addr = self.client.recv(5).decode()

			print(str(self.addr),' says :',str(msg))


cl = Client()
cl.chatWindow()

# client.send('Hello, I am Client'.encode())


