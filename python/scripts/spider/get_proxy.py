import requests
import json
from bs4 import BeautifulSoup
from termcolor import colored
from time import sleep

def log(msg):
    print(colored(f'[*] {msg}', 'green'))

def hint(msg):
    print(colored(f'[*] {msg}', 'blue'))

def error(msg):
    print(colored(f'[*] {msg}', 'red'))

def read_userinfo(file):
    users = []
    with open(file) as fp:
        info_lines = [line.strip() for line in fp.readlines()]
        print(info_lines)
        for info in info_lines:
            info_list = info.split()
            email = info_list[1]
            passwd = info_list[2]
            users.append(dict(email=email, pwd=passwd))
    return users

def save(filename, urls: list):
    with open(filename, 'a+') as fp:
        urls = [url + '\n' for url in urls]
        fp.writelines(urls)
    log(f'succeed to write {len(urls)} urls to file {filename}')

url_login = 'https://sakura.aoaomoe.club/auth/login'
url_home = "https://sakura.aoaomoe.club/user"
user_agent = r'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/81.0.4044.122 Safari/537.36'
headers={'user-agent': user_agent}
file = 'user_info.txt'

users = read_userinfo(file)
subscribe_urls = []
for user in users:
    email, pwd = user.values()
    payload = dict(email=email, passwd=pwd, code=None)
    log(f'[*] payload: {payload}')
    log(f'[*] start to send payload')
    resp = requests.post(url_login, headers=headers, data=payload, timeout=10)
    send_success = resp.status_code == 200
    msg = json.loads(resp.text)
    login_success = msg.get('ret', 0) == 1
    if send_success and login_success:
        log('[*] succeed to login')
        log(f'msg {msg.get("msg")}')
        cookies = resp.cookies
        resp = requests.get(url_home, headers=headers, cookies=cookies, timeout=10)
        html = resp.text
        soup = BeautifulSoup(html, 'html.parser')
        subscribe_url = soup.find('a', class_="copy-text btn-dl")['data-clipboard-text']
        hint(subscribe_url)        
        subscribe_urls.append(subscribe_url)
    else:
        error('failed to login')
        error(f'ret code {resp.status_code}, msg {msg.get("msg")}')
    sleep(5)

save('urls.txt', subscribe_urls)

