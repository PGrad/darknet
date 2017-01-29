from os import walk, remove
from sys import argv
from shutil import copyfile


def match_files(anno_dir, anno_num_dir, image_dir, image_num_dir, label):
    anno_set = set()
    count = 1
    for _,_,files in walk(anno_dir):
        for anno in files:
            anno_set.add(anno.split(".")[0])
    for _,_,files in walk(image_dir):
        for img in files:
            name = img.split(".")[0]
            if(name in anno_set):
                copyfile(anno_dir + "/" + name + ".xml", anno_num_dir + "/" + label + str(count) + ".xml")
                copyfile(image_dir + "/" + img, image_num_dir + "/" + label + str(count) + ".JPEG")
                count += 1
if __name__=="__main__":
    match_files(*argv[1:])
