##########################
#       reduceImageSize.py
##########################

from PIL import Image
import math

#
#   reduces image of certain size by certain factor
#
#       returns:    new image with changed size
#
#       im:         image that is being changed
#       factor:     factor image is being changed by
#       size:       size of original im
#
def reduceImageSize(im, factor, size):

    # set pixels array to incoming array of pixels
    pixels = im

    # get the width and height of the current image
    width = size
    height = size

    # will be set to the shortest dimension later on
    newSize = 0

    # create a list to hold the new image pixel data.
    new_pixels = []

    # skips over certain factor of pixels depending of factor
    for row in range(height // factor):
        for col in range(width // factor):
            index = factor * row * width + factor * col
            new_pixels.append(pixels[index])

    # convert into an image
    newim = Image.new("RGB", (width // factor, height // factor))
    newim.putdata(new_pixels)
    return newim
