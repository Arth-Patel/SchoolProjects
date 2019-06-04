
import binascii
import socket as syssock
import threading
from struct import *
import sys

# these functions are global to the class and
# define the UDP ports all messages are sent
# and received from

def init(UDPportTx,UDPportRx):   # initialize your UDP socket here 
	global transmitPort
	global recievePort
	transmitPort=int(UDPportTx)
	recievePort=int(UDPportRx)
    
class socket:
    
	def __init__(self):  # fill in your code here 
		self.sock=syssock.socket(syssock.AF_INET, syssock.SOCK_DGRAM)
		self.sock.bind(('',recievePort))
		self.sendfinish=False
		return
    
	def bind(self,address):
		return 

	def connect(self,address):
		self.sock.connect((address[0], transmitPort))
        # Client Connection
        # Send SYN 
		packA=Packet(1,0,0,0,'')
		
		self.sock.send(pack("iiiiiiiiiiii",packA.version,packA.flags,packA.opt_ptr,packA.protocol,packA.header_len,packA.checksum,packA.source_port,packA.dest_port,packA.sequence_no,packA.ack_no,packA.window,packA.payload_len))#Flag(1st number) is 1 for SYN
		#print("send")#recieve SYN and ACK
		packedData = self.sock.recv(48)# Empty besides header
        # Send ACK 
		original_data=unpack('iiiiiiiiiiii',packedData)
		packC=Packet(4,0,original_data[8]+1,1,'')
		
		self.sock.send(pack("iiiiiiiiiiii",packC.version,packC.flags,packC.opt_ptr,packC.protocol,packC.header_len,packC.checksum,packC.source_port,packC.dest_port,packC.sequence_no,packC.ack_no,packC.window,packC.payload_len))#Flag(1st number) is 1 for SYN
		return

	def listen(self,backlog):
		return

	def accept(self):
		#Recieve SYN
		packedData=self.sock.recv(48)#header file only to start 
		original_data=unpack('iiiiiiiiiiii',packedData)
		self.sendfinish=True
        # Server Side connection
		self.sock.connect(("localhost", transmitPort))
        # Send SYN/ACK
		packB=Packet(5,0,original_data[9]+1,0,'')
		
		self.sock.send(pack("iiiiiiiiiiii",packB.version,packB.flags,packB.opt_ptr,packB.protocol,packB.header_len,packB.checksum,packB.source_port,packB.dest_port,packB.sequence_no,packB.ack_no,packB.window,packB.payload_len))#Flag(1st number) is 1 for SYN
		#  Receive ACK
		packet = self.sock.recv(48)
	
		return (self, "localhost")
    
	def close(self):# fill in your code here 
		if(self.sendfinish):
			self.sock.close()
			
		return 

	def send(self,buffer):#65536 is the max bytes need to remove 48 for the header
		max=65536-48
		counter=0
		currentlyon=0
		self.bytessent=0
		self.verified=0
		self.amount=((len(buffer)/max)+1)
		order=0
		self.brokenOrder=False
	#	print("donk"+str(len(buffer)))
		self.sendfinish=False
		
		while(True):
			if(self.brokenOrder):
				counter=self.verified
				self.brokenOrder=False
			if (counter<self.amount):
				end=min(counter*max+max-100, len(buffer))
				packB=Packet(0,counter,0,0,buffer[counter*max:end])
			#	print("DONKEY= "+str(len(packB.data)))
				self.sock.send(pack("iiiiiiiiiiii",packB.version,packB.flags,packB.opt_ptr,packB.protocol,packB.header_len,packB.checksum,packB.source_port,packB.dest_port,packB.sequence_no,packB.ack_no,packB.window,packB.payload_len)+packB.data)#Flag(1st number) is 1 for SYN
				t=threading.Thread(target=self.sendHelp,args=(counter,end))#not how to start a thread but shrug
				t.daemon=True
				t.start()
			counter=+1
			if(self.sendfinish):
				break
		return self.bytessent 
	
	def sendHelp(self,counter,end):
		try:
			msg = self.sock.recv(48)
			original_data=unpack('iiiiiiiiiiii',msg)
			if(counter==original_data[9] and counter==self.verified):
				self.verified+=1
				#print("here")
				self.bytessent+=end
				if(counter==(self.amount-1)):
					self.sendfinish=True
				return
			self.brokenOrder=True
			return
		except syssock.error, e:
			self.brokenOrder=True
			return
	
	def recv(self,nbytes):
		answer=""
	#	
		maxchar=65536-48
		amountRec=((nbytes/maxchar)+1)
		answerOrder=0
		while(answerOrder<amountRec):
			msg=self.sock.recv(65536)
			original_data=unpack('iiiiiiiiiiii',msg[:48])
			packA=Packet(0,0,answerOrder,original_data[8],'')
			self.sock.send(pack("iiiiiiiiiiii",packA.version,packA.flags,packA.opt_ptr,packA.protocol,packA.header_len,packA.checksum,packA.source_port,packA.dest_port,packA.sequence_no,packA.ack_no,packA.window,packA.payload_len))#Flag(1st number) is 1 for SYN
			print(str(original_data[8]))
			if(original_data[8]==answerOrder):
				answerOrder+=1
				answer+=msg[48:]
					
		return answer

class Packet:
	def __init__(self,flags,sequence_no,ack_no,payload_len,data):
		self.version=1
		self.flags=flags
		self.opt_ptr=0
		self.protocol=0
		self.header_len=48#12*4=48 12 ints included in the header
		self.checksum=0
		self.source_port=0
		self.dest_port=0
		self.sequence_no=sequence_no
		self.ack_no=ack_no
		self.window=0
		self.payload_len=payload_len
		self.data=data
	
    


