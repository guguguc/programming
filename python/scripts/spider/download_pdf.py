from bs4 import BeautifulSoup
import requests

url = 'http://pages.cs.wisc.edu/~remzi/OSTEP/'
html = requests.get(url)
with open('tmp.html', mode='w') as fp:
    fp.write(html.content)
print('[*]succeed to write!')
    
# soup = BeautifulSoup(html, 'html.parse')
# for link in soup.find_all('i'):
    # print(link)