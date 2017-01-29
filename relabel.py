from sys import argv
from os import walk, rename


def rename_img_dirl(a_dir: str, label: str) -> None:
    count = 1
    for _,_,files in walk(a_dir):
        for f in files:
            rename(a_dir + "/" + f, a_dir + "/" + f + ".JPEG")
            count += 1


def rename_labels(img_dir: str, anno_dir: str) -> None:
    count = 1
    anno_set = set()
    for _,_,files in walk(anno_dir):
        for anno in files:
            anno_set.add(anno)
    for _,_,files in walk(image_dir):
        


if __name__=="__main__":
    rename_all(*argv[1:])
