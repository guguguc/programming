import requests as req

ip = '125.219.64.177'
mask = '255.255.254.0'
headers = {
    'User-Agent':
    'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/96.0.4664.110 Safari/537.36'
}


def gen_ip(ip, mask):
    ip = ''.join([bin(int(i))[2:].rjust(8, '0') for i in ip.split('.')])
    mask = ''.join([bin(int(i))[2:].rjust(8, '0') for i in mask.split('.')])
    mk_cnt = mask.count('1')
    var_len = len(ip) - mk_cnt
    cnt = 2**var_len
    ip_prefix = ip[:mk_cnt]
    for i in range(cnt):
        sip = ip_prefix + bin(i)[2:].rjust(var_len, '0')
        yield '.'.join(str(int(sip[8 * i:8 * (i + 1)], 2)) for i in range(4))


def get_head(ip):
    try:
        resp = req.get(f'http://{ip}:8080', headers=headers)
    except Exception:
        return ip, 'not found'
    else:
        return ip, resp.status_code


def main(logger=print):
    from concurrent.futures import ThreadPoolExecutor
    with ThreadPoolExecutor() as executor:
        fs = executor.map(get_head, gen_ip(ip, mask))
        for res in fs:
            logger(res)


if __name__ == '__main__':
    main()