import hashlib

m = hashlib.md5(b'axy_123456').hexdigest()
print(m)