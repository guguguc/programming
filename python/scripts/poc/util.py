from hashlib import md5

def calc_md5(filename) -> str:
    return md5(open(filename, mode='rb').read()).hexdigest()

if __name__ == "__main__":
    print(calc_md5(__file__))
