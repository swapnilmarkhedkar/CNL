import time
import socket


class Server:
	def __init__(self):
		self.serv = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		self.serv.setsockopt(socket.SOL_SOCKET , socket.SO_REUSEADDR, 1)
		self.serv.bind(('127.0.0.1',8000))
		self.serv.listen(5)
		print('Waiting for Client...')

	def calculate_window_size(self,m):
		return (2**m)-1

	def go_back(self,data):
		currIndex = 0
		lossIndex = 0
		tempData = ''
		mySocket, addr = self.serv.accept()
		print("Successfully Connected to Client")

		m = int(input("Enter the value of m : "))
		windowSize = self.calculate_window_size(m)
		print('Window Size : '+ str(windowSize))
		mySocket.send(str(windowSize).encode())

		while(True):
			slideBy = 0
			dataCorrupted = False

			chLoss = input('Do you wish to Loss a packet?(Y/N) ')
			if chLoss == 'Y' or chLoss == 'y':
				lossIndex = int(input('Choose Index from Range ('+ str(currIndex) + '-' + str(currIndex+windowSize-1) + ')'))
				#send
				for i in range(currIndex, currIndex + windowSize):
					print('Sending :',data[i])
					if lossIndex == i:
						mySocket.send(' '.encode())
					else:
						mySocket.send(data[i].encode())
					time.sleep(1)

			else:
				#send
				for i in range(currIndex, currIndex + windowSize):
					print('Sending :',data[i])
					mySocket.send(data[i].encode())
					time.sleep(1)


			for i in range(windowSize):
				#Receive Ack
				tempData = mySocket.recv(1).decode()
				print('Checking', tempData,'with',data[i+currIndex])
				if dataCorrupted == False:
					if tempData == data[i+currIndex]:
						#Acknowledgement Correctly Received
						slideBy = slideBy + 1
					else:
						#Ack is wrong, Dont slide Window
						dataCorrupted = True

				else:
					#Data is corrupted, Need to Go-Back-N
					pass

			if dataCorrupted == False:
				print('Acks Received properly')
				currIndex = currIndex + windowSize
			else:
				print('Data Corrupted, Going-Back-N')
				currIndex = currIndex + slideBy


file = open('data.txt', 'r')
data = file.read()

obj = Server()
obj.go_back(data)
