from time import strftime, localtime, sleep
import requests
import random
import json
import re

def hello():
    pass

class FakeIdentityGen():
    def __init__(self):
        self.name = self._gen_user_name()
        self.email = self._gen_user_email()
        self.passwd = self._gen_user_pass() 
        self.wechat = self._gen_contact()
        
    def get_user_info(self):
        user_info = dict(
            name=self.name, email=self.email,
            passwd=self.passwd, wechat=self.wechat)
            
        return user_info

    def _gen_user_name(self):
        names_file = 'names.txt' 
        length = 8000
        name = None
        with open(names_file) as fp:
            names = list(map(lambda x: x.strip().lower(), fp.readlines()))
            random_idx = random.randint(0, length)
            name = names[random_idx]
        return name

    def _gen_user_pass(self):
        passwords_file = 'passwords.txt'
        length = 1000
        passwd = None
        with open(passwords_file) as fp:
            passwords = list(map(lambda x: x.strip(), fp.readlines()))
            random_idx = random.randint(0, length)
            passwd = passwords[random_idx]
        return passwd

    def _gen_user_email(self):
        emails_file = 'emails.txt'
        length = 1
        email = None
        with open(emails_file) as fp:
            emails = list(map(lambda x: x.strip(), fp.readlines()))     
            random_idx = random.randint(0, length-1)
            email = emails[random_idx]
        return email

    def _gen_contact(self):
        wechat = ''
        for num in range(9):
            wechat += str(random.randint(1, 9))
        return wechat

    def save_file(self):
        filename = 'user_info.txt'
        with open(filename, mode='a+') as fp:
            time = strftime('%Y-%m-%d-%H:%M', localtime())
            fp.writelines(time + '\t' + self.email + '\t' + self.passwd + '\n')

    def get_validation_code(self):
        proxies = {
            'http': 'http://127.0.0.1:10809',
            'https': 'https://127.0.0.1:10809'
        }
        api = f'https://www.snapmail.cc/emailList/{self.email}'
        req = requests.get(api, proxies=proxies, timeout=10)
        code = None
        if req.status_code == 200:
            email_text = json.loads(req.text)[0]['html']
            code = re.search(r'([0-9]{6})', email_text)
        if code:
            code = code.group(1)
            print(f'[*] succeed to get code {code}')
            return code
        else:
            raise ValueError('failed to get code') 

url_reg = 'https://sakura.aoaomoe.club/auth/register'
url_send = 'https://sakura.aoaomoe.club/auth/send'
user_agent = r'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/81.0.4044.122 Safari/537.36'
headers={'user-agent': user_agent}
generator = FakeIdentityGen()
payload = generator.get_user_info()
# post data
payload.update(dict(
    repasswd=payload['passwd'], imtype=1,
    code=0, emailcode=None))
print(f'[*] {payload=}')
resp = requests.post(url_send, data=dict(email=payload['email']), headers=headers, timeout=20)
msg = json.loads(resp.text)
send_success = resp.status_code == 200
emailcode_send_success = msg.get('ret', 0) == 1
if send_success and emailcode_send_success:
    print('[*] succeed to send emial code')
    sleep(20)
    email_code = generator.get_validation_code()
    payload.update(emailcode=email_code)
    print(f'[*] ready to send {payload=}')
    rep = requests.post(url_reg, headers=headers, data=payload, timeout=20)
    msg = json.loads(rep.text)
    send_success = rep.status_code == 200
    reg_success = msg.get('ret', 0) == 1
    if send_success and reg_success:
        generator.save_file()
        print('[*] succeed to get user')
    else:
        print('[*] failed to get user')
        print(f'[*] error: code = {rep.status_code}, msg = {msg.get("msg")}')
else:
    print('[*] failed to send email code')
    print(f'[*] error: code = {resp.status_code}, msg = {msg.get("msg")}')
b = (1, 2, 3)
c = {ds}
a = 1 + 2