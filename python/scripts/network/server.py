'''
@Author: grehex
@Date: 2020-03-29 16:42:13
@LastEditTime: 2020-03-30 15:33:26
@Description: 
'''
import socket
import time
import struct

addr = ("", 8888)
s = socket.create_server(addr)

print(f'[*] server is listening on {addr[1]}')
while True:
    client, client_addr = s.accept()
    print(client_addr)
    rev_msg = str(client.recv(1024), encoding='utf8')
    print(rev_msg)
    # header = b'\x40\x00\x00\x00hello'
    header = struct.pack('<Is', 0x40, b'A' * 64)
    client.send(header)
    time.sleep(10)
    send_msg = 'AAA'
    while True:
        client.send(bytes(send_msg, encoding='utf8'))
        time.sleep(1)
        print('send success!')
client.close()

    
