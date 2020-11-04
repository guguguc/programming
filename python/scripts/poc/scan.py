import requests

ip = 'http://218.29.223.%s:8080'

for i in range(256):
    try:
        res = requests.get(ip % i, timeout=2)
        print(res.status_code)
        print(f'[+]connect to {ip % i} success!')
    except requests.exceptions.ConnectTimeout as e:
        print(f'[-]connect to {ip % i} failed!')