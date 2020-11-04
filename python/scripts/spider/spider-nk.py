'''
@Author: grehex
@Date: 2020-02-16 10:03:30
@LastEditTime: 2020-02-18 00:33:54
@Description: 爬取牛客面经
'''
import requests
import json
from bs4 import BeautifulSoup

url = 'https://www.nowcoder.com/discuss/167046'
params = {
    'type': 0,
    'order': 4,
    'pos': 6,
    'page': 1
}
# resp = requests.get(url, params=params)
# with open('mianjing.html', mode='w', encoding='utf8') as fp:
    # fp.write(resp.text)
soup = BeautifulSoup(open('mianjing.html', encoding='utf8'), 'html.parser')
tags = soup.find(id='c').next_sibling.next_sibling
url_generater = tags.find_all('a')
urls =[url.string for url in url_generater]
s = requests.Session()

post_titles = []
post_contents = []
post_info = {}
for count, url in enumerate(urls):
    resp = s.get(url, timeout=5)
    soup = BeautifulSoup(resp.text, 'html.parser')
    title = soup.find_all('span', 'js-post-title')
    contents = soup.find_all('div', 'nc-post-content')
    # 遍历段落子节点, 添加到content
    if title and contents:
        title = title[0].string
        if not title:
            continue
        content = ''
        # 遍历post-content div下的所有p节点, 并拼接字符串
        for children in contents:
            if children.text:
                content += (children.text + '\n')
        if content:      
            post_info[title] = content
            print('ok')
        print(f'{count}th: --> {title}')

path = './experience/'
count = 0
for title, content in post_info.items():
    filename = path + str(count) + '.txt'
    with open(filename, mode='w+', encoding='utf8') as f:
        text = title + '\n' + content 
        f.write(text)
    count += 1