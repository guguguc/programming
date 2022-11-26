#!/bin/python3
import cv2
from pyzbar.pyzbar import decode

file = '1.png'
img = cv2.imread(file)
ans = decode(img)
for item in ans:
    print(item)
