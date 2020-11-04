'''
@Author: grehex
@Date: 2020-03-30 14:06:20
@LastEditTime: 2020-03-30 21:46:42
@Description: 
'''
import socket
import argparse
from struct import pack
import time

addr = ('192.168.16.138', 8888)
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
# client.settimeout(4)
client.connect(addr)
print(f'[*] succeed to connect {addr}')

filename = 'hp.txt'
chunk_size = 4096
with open(filename, mode='rb') as fp:
    name = bytes(filename, encoding='utf8')
    raw = []
    length = 0
    while chunk := fp.read(chunk_size):
        raw.append(chunk)
        length += len(chunk)
    header = pack(f'<32sI', name, length)
    client.send(header)
    print(f'[*] succeed to send header: {header}')
    time.sleep(5)
    
    start_time = time.time()
    for index, chunk in enumerate(raw):
        # payload = pack(f'<{len(chunk)}s', chunk)
        client.send(chunk)
        print(f'[*] succeed to send chunk {index}')
    send_end_time = time.time()
    print('[*] success to send file!')
    msg = str(client.recv(8), encoding='utf8')
    if (msg == 'OK'):
        print('[*] server has saved the file successfully') 
        client.close()
    saved_end_time = time.time()
    send_time = send_end_time - start_time
    save_time = saved_end_time - start_time
    print(f'[*]send time: {send_time:.2}s, save time: {save_time:.2}s')
    
# if __name__ == '__main__':
#     parser = argparse.ArgumentParser(description='upload file')
#     parser.add_argument('ip', type=str)
#     parser.add_argument('port', type=int)
