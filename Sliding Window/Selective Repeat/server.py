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
		return 2**(m-1)

	def selective_repeat(self,data):
		currIndex = 0
		lossIndex = 0
		lossData = ''
		tempData = ''
		chLoss = 'n'
		mySocket, addr = self.serv.accept()
		print("Successfully Connected to Client")

		m = int(input("Enter the value of m : "))
		windowSize = self.calculate_window_size(m)
		print('Window Size : '+ str(windowSize))
		mySocket.send(str(windowSize).encode())

		while(True):
			slideBy = 0
			dataCorrupted = False

			#NOTE :
			#This if-else contains redundant code which could have been combined
			#But this allows clear distinction between whether there was a packet loss in the previous iteration
			if chLoss == 'y' or chLoss =='Y':

				#This part of code is executed when there was a packet loss in previous iteration
				chLoss = input('Do you wish to Loss a packet?(Y/N) ')
								
				#Send What is missing
				print('Selectively Repeating :',lossData)
				mySocket.send(lossData.encode())
				time.sleep(1)

				if chLoss == 'Y' or chLoss == 'y':
					lossIndex = int(input('Choose Index from Range ('+ str(currIndex) + '-' + str(currIndex+windowSize-2) + ')')) #window size is smaller
					#send
					for i in range(currIndex, currIndex + windowSize-1):
						print('Sending :',data[i])
						if lossIndex == i:
							mySocket.send(' '.encode())
							lossData=data[i]
						else:
							mySocket.send(data[i].encode())
						time.sleep(1)

				else:
					#send
					for i in range(currIndex, currIndex + windowSize-1):
						print('Sending :',data[i])
						mySocket.send(data[i].encode())
						time.sleep(1)


				for i in range(windowSize):
					#Receive Ack
					tempData = mySocket.recv(1).decode()
					#Ideally the ack received should be matched and hence it should be found if there is inconsistency
					#Only then this 'Lossed Packet' should be sent in next iteration
					#However, as I already know what Packet I'm Lossing, I haven't bothered to check

			else:
				#This part of code is executed when there was NO packet loss in previous iteration
				chLoss = input('Do you wish to Loss a packet?(Y/N) ')
				if chLoss == 'Y' or chLoss == 'y':
					lossIndex = int(input('Choose Index from Range ('+ str(currIndex) + '-' + str(currIndex+windowSize-1) + ')'))
					#send
					for i in range(currIndex, currIndex + windowSize):
						print('Sending :',data[i])
						if lossIndex == i:
							mySocket.send(' '.encode())
							lossData=data[i]
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
					#Ideally the ack received should be matched and hence it should be found if there is inconsistency
					#Only then this 'Lossed Packet' should be sent in next iteration
					#However, as I already know what Packet I'm Lossing, I haven't bothered to check
				
			currIndex = currIndex + windowSize
			
			#Exit Condition
			if currIndex >= len(data):
				break

file = open('data.txt', 'r')
data = file.read()
file_data = []
file_data[:0] = data

obj = Server()
obj.selective_repeat(data)