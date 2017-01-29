from typing import Tuple
import xml.etree.ElementTree as ET
from os import walk
from sys import argv


Coords = Tuple[float]
train_list = "train/images/training_list.txt"
#Following from Guanghan's tutorial on training darknet: 
#https://github.com/Guanghan/darknet/blob/master/scripts/convert.py
def convert(size: Coords, box: Coords) -> Coords:
    dw = 1./size[0]
    dh = 1./size[1]
    x = (box[0] + box[1])/2.0
    y = (box[2] + box[3])/2.0
    w = box[1] - box[0]
    h = box[3] - box[2]
    x = x*dw
    w = w*dw
    y = y*dh
    h = h*dh
    return (x,y,w,h)

#Returns the image size and bbox boundaries to feed into convert.
def get_bounds_from_XML(xml_file: str) -> Coords:
    xml_tree = ET.parse(xml_file)
    root = xml_tree.getroot()
    root_i = 0
    while(root[root_i].tag != 'size'):
        root_i += 1
    size_child = [int(child.text) for child in root[root_i]]
    while(root[root_i].tag != "object"):
        root_i += 1
    obj_child = root[root_i]
    obj_i = 0
    while(obj_child[obj_i].tag != "bndbox"):
        obj_i += 1
    bnd_child = [int(child.text) for child in obj_child[obj_i]]
    return ((size_child[0], size_child[1]), (bnd_child[0], bnd_child[1], bnd_child[2] - bnd_child[0], bnd_child[3] - bnd_child[1]))


def imagenet_to_yolo(inet_anno_dir: str, yolo_anno_dir: str, image_dir: str, class_num: int) -> None:
    inet_bbox_coords = []
    inet_names = []
    for _,_,inet_labels in walk(inet_anno_dir):
        for label in inet_labels:
            inet_bbox_coords.append(convert(*get_bounds_from_XML(inet_anno_dir + "/" + label)))
            inet_names.append(label.split(".")[0])
    num_labels = len(inet_names)
    with open(yolo_anno_dir + "/annotations_" + str(class_num) + ".txt", 'w') as yolo_label_file:
        for i in range(num_labels):
            yolo_label_file.write(str(class_num) + " " + " ".join([str(dim) for dim in inet_bbox_coords[i]]) + "\n")
    with open(train_list, "a") as train_file:
        for name in inet_names:
            train_file.write(image_dir + "/" + name + ".JPEG\n")

if __name__=="__main__":
    imagenet_to_yolo(*argv[1:])
