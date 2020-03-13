import socket 
import time


class Client:
	def __init__(self):
		self.client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		self.client.connect(('127.0.0.1', 8000))
		print('Connected!')

	def selective_repeat(self):
		finalData = []
		windowSize = int(self.client.recv(1).decode())
		print('windowSize : '+str(windowSize))

		while(True):
			tempData = []
			dataCorrupted = False	

			for i in range(windowSize):
				#Receive Packet in this Iteration
				currentData = self.client.recv(1).decode()
				print('Received Frame :',currentData)
				tempData.append(currentData)

			for i in range(windowSize):
				#Send Ack in this iteration
				if tempData[i] == ' ':
					dataCorrupted=True

				else:
					finalData.append(tempData[i])

				print('Sending Ack:', tempData[i])
				self.client.send(tempData[i].encode())
				time.sleep(.1)

			if dataCorrupted == True:
				print('Data Corrupted')

			#Just sorting them instead of explicitly keeping a buffer, which is more timetaking
			finalData.sort()

			str1=''
			print('Data Received :',str1.join(finalData))


obj = Client()
obj.selective_repeat()