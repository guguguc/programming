'''
@Author: grehex
@Date: 2020-02-12 13:43:39
@LastEditTime: 2020-02-19 22:28:52
@Description: 爬取极客时间专栏
'''
import requests
import json
import time
import random
from collections import OrderedDict

url = [
    "https://time.geekbang.org/serv/v1/article",
]

headers = {
    'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/80.0.3987.106 Safari/537.36',
    'origin': 'https://time.geekbang.org',
}

cookies = {
  	'GCID': '16a0140-80827a7-d9723a9-c6c1f84',
	'GCESS': 'BAYEXSmY6AoEAAAAAAwBAQEEQIMPAAUEAAAAAAQEAC8NAAkBAQMEILxDXggBAwcEpBk1fgsCBAACBCC8Q14-',
}
payload = {"id": "183", "include_neighbors": 'true', "is_freelyread": 'true'}

post_info = OrderedDict()
title = '183'
while True:
	try:
		req = requests.post(url[-1], headers=headers, cookies=cookies, json=payload)
		time.sleep(random.random() * 3)
		print(req.status_code)
		content = req.json()['data']
		post = content['article_content']
		post_info[title] = post
		next_index = content['neighbors']['right']['id']
		next_title = content['neighbors']['right']['article_title']
		payload['id'] = next_index
		title = next_title
		print(title)
	except json.decoder.JSONDecodeError:
		print('wrong', payload['id'], title)
		print(req.content)

	except:
		print("complete!")
		break
	
with open('post.json', mode='w+') as fp:
	json.dump(post_info, fp, indent=4, ensure_ascii=False)


