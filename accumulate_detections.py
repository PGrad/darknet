######################################################################
#This script executes the darknet binary on each of the images within#
#the directory provided as a command line argument, and then prints  #
#the execution time.                                                 #
######################################################################

# import the necessary packages
from __future__ import print_function
import asyncio
from os import walk
import argparse
from subprocess import Popen,PIPE,call
from timeit import timeit
from time import sleep
BUFFER_SIZE = 3

def callDarknet(cmd, d, imagePath):
    return Popen(cmd + [d + '/' + imagePath])
def test(): 
    # construct the argument parse and parse the arguments
    ap = argparse.ArgumentParser()
    ap.add_argument("-i", "--images", required=True, help="path to images directory")
    args = vars(ap.parse_args())
    detect_cmd = ["./darknet", "detector", "test", "cfg/voc.data", "cfg/tiny-yolo-voc.cfg", "tiny-yolo-voc.weights"] 
    running_procs = []
    image_pool = []
    root_dir = []
    count = BUFFER_SIZE
    #loop over the image paths
    for root,_,files in walk(args["images"]):
        root_dir = root
        image_pool = files
    num_files = len(image_pool)
    for image in range(BUFFER_SIZE):
        running_procs.append(callDarknet(detect_cmd,root,image_pool[image]))
    while running_procs:
        for proc in running_procs:
            retcode = proc.poll()
            if retcode is not None: # Process finished.
                running_procs.remove(proc)
                if count <= num_files:
                    count += 1
                    running_procs.append(callDarknet(detect_cmd,root,image_pool[image]))
                break
            else: # No process is done, wait a bit and check again.
                sleep(.1)
                continue
if __name__=="__main__":
    print(timeit("test()", setup="from __main__ import test", number=1))
