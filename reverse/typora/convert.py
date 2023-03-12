from PIL import Image

logo = Image.open("icon.png")
logo.save("icon.ico", format='ICO', sizes=[(16, 16), (32,32), (64,64), (128,128), (256,256)])