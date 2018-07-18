#######################
#       imageSetting.py
#######################
from PIL import Image

#
#   loads the image
#
#       filename:   the name of image that is being loaded
#       dir:        which directory the image is found within curr dir
#
def load_img(filename, dir):
    im = Image.open(dir + filename)
    return im

#
#   displays the image
#
#       im:         the image that is being shown
#
def show_img(im):
    im.show()

#
#   saves the image with given name
#
#       im:         the image that is being shown
#       filename:   the image's new name
#
def save_img(im, filename):
    im.save(filename, "jpeg")
