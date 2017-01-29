from os import walk, remove
from sys import argv

def match_files(anno_dir, image_dir):
    anno_set = set()
    for _,_,files in walk(anno_dir):
        for anno in files:
            anno_set.add(anno.split(".")[0])
    for _,_,files in walk(image_dir):
        for img in files:
            if(img.split(".")[0] not in anno_set):
                remove(image_dir + "/" + img)

if __name__=="__main__":
    match_files(argv[1], argv[2])
