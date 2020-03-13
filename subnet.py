
def find_class(ele):
	ele = int(ele)
	if ele<127:
		return 'A'
	elif ele>127 and ele<=191:
		return 'B'
	elif ele>191 and ele<=223:
		return 'C'
	elif ele>224 and ele<=239:
		return 'D'
	else:
		return 'E'

def find_default_subnet(ip_class):

	if ip_class == 'A':
		return '255.0.0.0'
	elif ip_class == 'B':
		return '255.255.0.0'
	elif ip_class == 'C':
		return '255.255.255.0'	

def find_subnet_binary(cidr):
	subnet_bin = 0
	for i in range(cidr):
		subnet_bin*=10
		subnet_bin+=1

	for i in range(cidr,32):
		subnet_bin*=10

	return subnet_bin
	
def find_subnet_mask(cidr):
	a = str(find_subnet_binary(cidr))

	a1 = 0
	a2 = 0
	a3 = 0
	a4 = 0

	for i in range(0,8):
		a1*=10
		a1+= int(a[i])

	for i in range(8,16):
		a2*=10
		a2+= int(a[i])

	for i in range(16,24):
		a3*=10
		a3+= int(a[i])

	for i in range(24,32):
		a4*=10
		a4+= int(a[i])

	a1 = str(binary_to_decimal(a1))
	a2 = str(binary_to_decimal(a2))
	a3 = str(binary_to_decimal(a3))
	a4 = str(binary_to_decimal(a4))

	a5 = []
	a5.append(a1)
	a5.append(a2)
	a5.append(a3)
	a5.append(a4)

	dot = "."
	return dot.join(a5)

def find_net_id(subnet,ip):
	subnet = subnet.split('.')
	ip = ip.split('.')
	n = []

	for i in range(4):
		n.append(str(int(subnet[i]) & int(ip[i])))

	dot = '.'
	return dot.join(n)

def find_bid(nid,bits):
	nid = nid.split('.')
	div = int(256 / (2**bits))
	nid[3] = str(int(nid[3]) + div-1)
	dot='.'
	return dot.join(nid)

def binary_to_decimal(bin):
	base=1
	num=0
	while(bin):
		rem=bin%10
		bin=int(bin/10)
		num+=base*rem
		base=base*2	
	return num

ip = input("Enter IP Address :")
cidr = int(input("Enter CIDR(Classless Inter-Domain Routing) : "))

ip_elements = ip.split('.')

ip_class = find_class(ip_elements[0])
print('Class :', ip_class)

default_subnet = find_default_subnet(ip_class)
print('Default Subnet :',default_subnet)

subnet_mask = find_subnet_mask(cidr)
print('Subnet Mask :',subnet_mask)

net_id = find_net_id(subnet_mask,ip)
print("Network ID :", net_id)

bid = find_bid(net_id,cidr-24)
print("Directed Broadcast Address :",bid)