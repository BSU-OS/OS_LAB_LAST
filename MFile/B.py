import mmap
import os
import time


def write():
    open("input.txt", 'w').close()
    with open("input.txt", "wb") as f:
        f.write("Hi from client!".encode("Ascii"))
        f.close()
def read():
    while (os.stat("output.txt").st_size == 0):
        time.sleep(0.0001)
    with open("output.txt", "r+") as f:
        # memory-map the file, size 0 means whole file
        mm = mmap.mmap(f.fileno(), 0)
        # read content via standard file methods
        print(mm.readline().decode("Ascii"))
        # close the map
        f.flush()
        mm.close()
        f.close()
        open("output.txt", 'w').close()
read()
write()
