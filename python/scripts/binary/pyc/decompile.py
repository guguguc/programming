#!/bin/python3
# https://stackoverflow.com/questions/11141387/given-a-python-pyc-file-is-there-a-tool-that-let-me-view-the-bytecode
import sys
import importlib
import time
import struct
import marshal
import dis
from typing import Callable


header_sizes = [
    # (size, first version this applies to)
    # pyc files were introduced in 0.9.2 way, way back in June 1991.
    (8,  (0, 9, 2)),  # 2 bytes magic number, \r\n, 4 bytes UNIX timestamp
    (12, (3, 6)),     # added 4 bytes file size
    # bytes 4-8 are flags, meaning of 9-16 depends on what flags are set
    # bit 0 not set: 9-12 timestamp, 13-16 file size
    # bit 0 set: 9-16 file hash (SipHash-2-4, k0 = 4 bytes of the file, k1 = 0)
    (16, (3, 7)),     # inserted 4 bytes bit flag field at 4-8
    # future version may add more bytes still, at which point we can extend
    # this table. It is correct for Python versions up to 3.9
]
header_size = next(s for s, v in reversed(header_sizes)
                   if sys.version_info > v)


def disassemble(fn, log: Callable = print):
    fp = open(fn, 'rb')
    metadata = fp.read(header_size)
    bit_field = int.from_bytes(metadata[4:8], byteorder=sys.byteorder)
    log(sys.version, 'magic:', importlib.util.MAGIC_NUMBER.hex())
    log(fn, 'magic:', metadata[:4].hex())
    if 1 & bit_field:
        file_hash = metadata[8:16].hex()
        log('hash', file_hash.hex())
    else:
        tm = metadata[8:12]
        tm = time.ctime(struct.unpack('I', tm)[0])
        size = struct.unpack('I', metadata[12:16])[0]
        log('timestamp', tm, 'size:', size)
    code_obj = marshal.load(fp)
    dis.disassemble(code_obj)
    log('names', code_obj.co_names)
    log('filename', code_obj.co_filename)


if __name__ == '__main__':
    import sys
    sys.stdout = open('log.txt', 'w')
    disassemble("./config.cpython-39.pyc")
