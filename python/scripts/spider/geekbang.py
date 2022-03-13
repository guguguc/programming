from concurrent.futures import ThreadPoolExecutor, thread
import random
import time
import requests as req
import os
import zipfile
import glob

from pprint import pprint


class Extractor:
    def __init__(self) -> None:
        self.files = []
        self.size = 4

    def add_file(self, file):
        self.files.append(file)
        if len(self.files) >= self.size:
            self.run()

    def extract(self, fn):
        pt = fn.split('.')[0]
        zf = zipfile.ZipFile(fn)
        zf.extractall(path=pt)
        f = glob.glob(f'{pt}/*.mp3')
        if f:
            for n in f:
                os.remove(n)
        zf.close()
        os.remove(fn)

    def run(self):
        with ThreadPoolExecutor() as executor:
            executor.map(self.extract, self.files)


class Converter:
    def __init__(self) -> None:
        pass

    def convert(self):
        pass


def unzip(fn):
    pt = fn.split('.')[0]
    zf = zipfile.ZipFile(fn)
    zf.extractall(path=pt)
    f = glob.glob(f'{pt}/*.mp3')
    if f:
        for n in f:
            os.remove(n)
    zf.close()
    os.remove(fn)


def get_valid_dir(path):
    blacklist = {'/', ':', '?', '\"', '<', '>', '|', '*'}
    for char in blacklist:
        path = path.replace(char, '-')
    return path


class HttpConfig:
    def __init__(self) -> None:
        self.agent = 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/99.0.4844.51 Safari/537.36'
        self.cookies = {
            'GCID':
            '3a0192e-9dd2436-fb094fe-ba66a5a',
            'GCESS':
            'BgcEeqqVwQgBAwUEAAAAAAIEOTIrYgwBAQkBAQYEyPBBgQ'
            'oEAAAAAA0BAQEIW9ssAAAAAAALAgYABAQALw0AAwQ5Miti',
        }

    def get_headers(self, use_json=False):
        header = {
            'User-Agent': self.agent + str(random.choice(range(100))),
            'Referer': 'https://time.geekbang.org',
        }
        if use_json:
            header['Content-Type'] = 'application/json'
        return header

    def get_cookies(self):
        return self.cookies


class Article:
    def __init__(self, aid, **kwargs) -> None:
        self.pid = aid
        self.title = kwargs.get('article_title')
        self.author = kwargs.get('author_name')
        self.summary = kwargs.get('article_summary')
        self.cpt_id = kwargs.get('chapter_id')
        self.zip_info = {}

    def set_zip_info(self, zip_info: dict):
        self.zip_info = zip_info

    def save(self, path):
        url = self.zip_info.get('url')
        raw = req.get(url, stream=True)
        fn = os.path.join(path, f'{self.pid}.zip')
        if os.path.exists(fn):
            print(f'skip {fn}')
            return
        with open(file=fn, mode='wb') as fp:
            for chunk in raw.iter_content(chunk_size=4096):
                if chunk:
                    fp.write(chunk)
        print(f'succeed to save to {fn}')
        unzip(fn)

    def __str__(self) -> str:
        msg = f'\tname:{self.title}\n' \
                '\tauthor:{self.author}\n' \
                '\tsummary:{self.summary}'
        return '{\n' + msg + '\n}'


class Chapter:
    def __init__(self, cpid, **kargs) -> None:
        self.cpid = cpid
        self.title = get_valid_dir(kargs.get('title'))
        self.article_cnt = kargs.get('article_count')
        self.articles = []

    def add_article(self, article: Article):
        if isinstance(article, Article):
            article = [article]
        self.articles.extend(article)

    def save(self, path=None):
        if not os.path.exists(path):
            os.mkdir(path)
        path = os.path.join(path, self.title)
        if not os.path.exists(path):
            os.mkdir(path)
        for article in self.articles:
            article.save(path)

    def id(self):
        return self.cpid


class Column:
    def __init__(self, cid, cpts, **kwargs) -> None:
        self.id = cid
        self.chapters = cpts
        self.title = get_valid_dir(kwargs.get('title'))
        self.summary = kwargs.get('summary')

    def extend_chapter(self, chapter):
        if isinstance(chapter, Chapter):
            chapter = [chapter]
        self.articles.extend(chapter)

    def save(self, path=None):
        assert self.title
        if path is None:
            path = os.path.dirname(os.path.abspath(__file__))
            path = os.path.join(path, 'data')
        if not os.path.exists(path):
            os.mkdir(path)
        path = os.path.join(path, self.title)
        for chapter in self.chapters:
            chapter.save(path)

    def __str__(self) -> str:
        msg = f'\tname:{self.name}\n\tcnt:{self.cnt}\n\tsummary:{self.summary}'
        return '{\n' + msg + '\n}'


class Spider:
    auth_url = 'https://account.geekbang.org/serv/v1'
    base_url = 'https://time.geekbang.org/serv/v1'
    base_v3_url = 'https://time.geekbang.org/serv/v3'
    try_cnt = 0

    def __init__(self, log_func=print) -> None:
        self.http_config = HttpConfig()
        assert (self.auth())
        self.log = log_func
        self.columns_id = self.get_cid_lst()
        self.log(f'succed to fetch {len(self.columns_id)} columns')
        self.extractor = Extractor

    def auth(self) -> bool:
        url = self.auth_url + '/user/auth?t={}'
        rep = req.get(url.format(int(time.time())),
                      headers=self.http_config.get_headers(),
                      cookies=self.http_config.get_cookies())
        if rep.json().get('data'):
            return True
        return False

    def get_cid_lst(self) -> list[str]:
        url = self.base_url + '/column/label_skus'
        payload = {"label_id": 0, "type": 0}
        rep = req.get(url,
                      data=payload,
                      headers=self.http_config.get_headers(),
                      cookies=self.http_config.get_cookies())
        dt = rep.json().get('data')
        assert dt, rep.json()
        lst = [item.get('column_sku') for item in dt.get('list')]
        return lst

    def get_col_info(self, cid) -> dict:
        url = self.base_v3_url + '/column/info'
        payload = f'{{"product_id":{cid},"with_recommend_article":true}}'
        cfg = self.http_config
        headers = cfg.get_headers(use_json=True)
        headers[
            'Referer'] = f'https://time.geekbang.org/column/intro/{cid}&page=B'
        rep = req.post(url, data=payload, headers=headers)
        dt = rep.json().get('data')
        assert dt, rep.json()
        return {
            'id': cid,
            'title': dt.get('title'),
            'summary': dt.get('subtitle'),
            'author': dt.get('author')
        }

    def get_chapters(self, col_id: str) -> list[Chapter]:
        url = self.base_url + '/chapters'
        payload = {'cid': col_id}
        cfg = self.http_config
        headers = cfg.get_headers(use_json=True)
        headers[
            'Referer'] = f'https://time.geekbang.org/column/intro/{col_id}?tab=catalog&page=B'
        rep = req.get(url,
                      json=payload,
                      headers=headers,
                      cookies=cfg.get_cookies())
        dt = rep.json().get('data')
        assert dt, rep.json()
        return [Chapter(item['id'], **item) for item in dt]

    def get_article(self, aid) -> dict:
        '''
        @param aid: article id
        @return {'size': <size>, 'url': <download_url>, 'filename': <filename> }
        '''
        url = self.base_url + '/article'
        payload = {"id": aid, "include_neighbors": 'true', "reverse": 'false'}
        rep = req.get(url,
                      json=payload,
                      headers=self.http_config.get_headers(),
                      cookies=self.http_config.get_cookies())
        dt = rep.json().get('data')
        assert dt, rep.json()
        dt = dt.get('offline')
        url = dt.pop('download_url')
        dt['url'] = url
        return dt

    def get_articles(self, col_id: str, cpts: list[Chapter]) -> list[Article]:
        url = self.base_url + '/column/articles'
        payload = {
            'chapter_ids': [cp.id() for cp in cpts],
            'cid': col_id,
            'order': 'earliest',
            'prev': 0,
            'sample': 'false',
            'size': 500
        }
        rep = req.get(url,
                      json=payload,
                      headers=self.http_config.get_headers(),
                      cookies=self.http_config.get_cookies())
        dt = rep.json().get('data')
        assert dt, rep.json()
        articles = [
            Article(article['id'], **article) for article in dt.get('list')
        ]
        for article in articles:
            self.try_cnt += 1
            article.set_zip_info(self.get_article(article.pid))
            print(f'succed to get article {article.title} info')
            if self.try_cnt % 10 == 0:
                time.sleep(random.random() * 2)
        return articles

    def get_column(self, col_id: str) -> Column:
        self.log(f'prepare to get column : {col_id}')
        self.log(f'prepare to get column info : {col_id}')
        cinfo = self.get_col_info(col_id)
        self.log(f'succeed to get column info -> {cinfo.get("summary")}')
        cpts = self.get_chapters(col_id)
        cpts_tb = {cpt.id(): cpt for cpt in cpts}
        self.log(f'succeed to get chapters : {len(cpts)}')
        articles = self.get_articles(col_id, cpts)
        for article in articles:
            cpts_tb[article.cpt_id].add_article(article)
        self.log(f'aleady fetched {len(articles)} article')
        column = Column(col_id, cpts, **cinfo)
        return column

    def get_random_cid(self):
        return random.choice(self.columns_id)

    def save(self):
        st = None
        if os.path.exists('error.txt'):
            with open('error.txt') as fp:
                st = fp.read().strip()
        if st:
            print(f'resume from {st}')
            idx = self.columns_id.index(int(st))
            self.columns_id = self.columns_id[idx:]
        cnt = len(self.columns_id)
        try:
            for cid in self.columns_id:
                try:
                    col = self.get_column(cid)
                except AssertionError:
                    print(f'unable {st}')
                    with open('unable.txt', 'a') as f:
                        f.write(str(cid) + '\n')
                else:
                    col.save()
                    remain = cnt - self.columns_id.index(cid) - 1
                    print(f'remain {remain} columns')
        except Exception:
            with open('error.txt', 'w') as f:
                f.write(str(cid))
            raise


if __name__ == '__main__':
    spider = Spider()
    spider.save()
    # for chapter in column.chapters:
    #     print(f'chapter: {chapter.title}')
    #     print(f'cnt : {chapter.article_cnt}')
    #     for article in chapter.articles:
    #         print(f'article: {article.title}')
    #         print(f'zip info: {article.zip_info}')