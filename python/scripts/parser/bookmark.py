#!/usr/bin/python3
import requests
from html.parser import HTMLParser

RED = '\033[31;1;1m'
GREEN = '\033[32;1;1m'
RESET = '\033[0m'

class BookMarkParser(HTMLParser):
    def __init__(self):
        """parse chromium exported bookmark
        <h3>category 1</h3>
            <dl>
            <a href="url1"></a>
            <a href="url2"></a>
            <h3>sub category 1</h3>
                <dl>
                    <a href="url1"></a>
                    <a href="url1"></a>
                </dl>
            <h3>sub category 2</h3>
                <dl>
                    <a href="url1"></a>
                    <a href="url1"></a>
                </dl>
            </dl>
        <h3>category 2</h3>
        """
        super(BookMarkParser, self).__init__()
        self.info = []
        self.cat_map = dict()
        self._last = ''
        self._stack = []

    def handle_starttag(self, tag, attrs):
        if tag == 'h3':
            self.info.append({})
            self._last = 'bk_name'
        elif tag == 'dl':
            parent = 0 if not self._stack else self._stack[-1][0]
            current = len(self.info) - 1
            self._stack.append((current, parent))
        elif tag == 'a':
            pos = self._stack[-1][0]
            self.info[pos]['url'].append(attrs[0][1])
            self._last = 'url'
        else:
            pass

    def handle_data(self, data):
        data = data.strip()
        if not data:
            return
        if self._last == 'bk_name':
            self.info[-1] = dict(type=data, url=[], title=[],
                                 num=0)
            self.cat_map[data] = len(self.info) - 1
        elif self._last == 'url':
            pos = self._stack[-1][0]
            self.info[pos]['title'].append(data)
            self.info[pos]['num'] += 1

    def handle_endtag(self, tag):
        if tag == 'dl':
            current, parent = self._stack.pop()
            self.info[current]['parent'] = parent
        else:
            pass

    def post_process(self):
        for item in self.info:
            assert(len(item['url']) == item['num'])

    def get(self, key):
        idx = self.cat_map.get(key, -1)
        if idx == -1:
            return None
        else:
            return self.info[idx]

    def show(self):
        for idx, item in enumerate(self.info):
            print(idx, item['type'],
                  len(item['url']), item.get('parent'),
                  item['title'])

def check_one(url):
    rep = requests.get(url, timeout=10)
    return rep.status_code

def check_all(urls):
    from concurrent.futures import ThreadPoolExecutor, as_completed
    err_urls = []
    with ThreadPoolExecutor(max_workers=12) as pool:
        future_to_url = {pool.submit(check_one, url): url for url in urls}
        for future in as_completed(future_to_url):
            url = future_to_url[future]
            try:
                ret = future.result()
            except Exception as e:
                print(f'url {url} generated an Exception {e}')
                err_urls.append((url, -1))
            else:
                print('[*] code', ret, 'url', url)
                if ret >= 400:
                    err_urls.append((url, ret))
    return err_urls



if __name__ == '__main__':
    import time
    import json
    data = '/home/gugugu/Documents/bookmarks.html'
    parser = BookMarkParser()
    parser.feed(open(data, encoding='utf8').read())
    parser.post_process()
    parser.show()
    urls = []
    for item in parser.info:
        urls.extend(item['url'])
    print('[*] start to test %s urls' % len(urls))
    t1 = time.time()
    err_urls = check_all(urls)
    t2 = time.time()
    print(f'[*] err url length {len(err_urls)}', \
          f'check {len(urls)} urls cost {(t2-t1):.2f}s')
    json.dump(err_urls, open('err_urls.json', 'w+'),
              indent=4)