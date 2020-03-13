import socket
import threading

class Client:
	def __init__(self):
		self.client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
		print('Binded Successfully')

		self.client.sendto(''.encode(), ('127.0.0.1', 8000))


	def chatWindow(self):
		threadS = threading.Thread(target = self.sender)
		threadR = threading.Thread(target = self.receiver)

		threadS.start()
		threadR.start()

	def sender(self):
		while True:
			msg = input()
			self.client.sendto(msg.encode(), ('127.0.0.1', 8000))

	def receiver(self):
		while True:
			msg, addr = self.client.recvfrom(50)
			msg = msg.decode()
			print(msg)
			if "|||" in msg:
				msg = msg.split("|||")
				print(msg)
			print(str(addr),' says :',str(msg[0]))

cl = Client()
cl.chatWindow()



