'''
@Author: grehex
@Date: 2020-02-19 21:50:28
@LastEditTime: 2020-02-19 22:00:53
@Description: 
'''
import json
with open('post.json', encoding='utf-8') as fp:
    di = json.load(fp)
    print(type(di))
    with open('post2.json', mode='w+', encoding='utf-8') as fp2:
        json.dump(di, fp2, ensure_ascii=False, indent=4)