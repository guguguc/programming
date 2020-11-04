'''
@Author: grehex
@Date: 2020-03-21 20:22:09
@LastEditTime: 2020-03-29 17:24:33
@Description: 
'''
import socket
import time

buffer_size = 1024
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(('192.168.43.108', 8888))
for _ in range(3):
    msg = input('please input the message:')
    client.send(bytes(msg + '\n', encoding='utf8'))
    response_msg = str(client.recv(buffer_size), encoding='utf8')
    print('recived msg:', response_msg)
client.close()



