import mmap
import time
import os

def write():
    open("output.txt", 'w').close()
    with open("output.txt", "wb") as f:
        f.write("Hi from server!".encode("Ascii"))
        f.close()
def read():
    while(os.stat("input.txt").st_size==0):
        time.sleep(0.0001)
    with open("input.txt", "r+") as f:
        # memory-map the file, size 0 means whole file
        mm = mmap.mmap(f.fileno(), 0)
        # read content via standard file methods
        print(mm.readline().decode("Ascii"))
        # close the map
        f.flush()
        mm.close()
        f.close()
        open("input.txt", 'w').close()
write()
time.sleep(5)
read()

