import socket 
import time


class Client:
	def __init__(self):
		self.client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		self.client.connect(('127.0.0.1', 8000))
		print('Connected!')

	def go_back(self):
		finalData = []		
		windowSize = int(self.client.recv(1).decode())
		print('windowSize : '+str(windowSize))

		while(True):
			tempData = []
			dataCorrupted = False

			for i in range(windowSize):
				currentData = self.client.recv(1).decode()
				print('Received Frame :',currentData)
				tempData.append(currentData)


			for i in range(windowSize):
				#Send Acknowledgement
				if dataCorrupted == True:
					self.client.send(' '.encode())
					time.sleep(.1)
				
				else:
					self.client.send(tempData[i].encode())
					if tempData[i] != ' ':
						finalData.append(tempData[i]) 
						print('Sending Ack: ', tempData[i])

					else:
						dataCorrupted=True
						print('Data Corrupted')

					time.sleep(.1)


obj = Client()
obj.go_back()