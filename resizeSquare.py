#######################
#       resizeSquare.py
#######################

from PIL import Image
import math

#
#   changes image to newSize x newSize pixels strickly
#
#       returns:    new image that is newSize x newSize pixels
#
#       im:         array of pixels from image function is getting new size from
#       newsize:    new size of photo
#       size:       old size of image
#
def resizeSquare(im, newSize, size):

    # set pixels array to incoming array of pixels
    pixels = im

    # get the width and height of the current image
    width = size
    height = size

    # create a list to hold the new image pixel data.
    new_pixels = []

    # the difference on either side of newSize x newSize square that is getting
    #   cut by center of current image
    dif = (width - newSize) // 2

    # keeps track of the row of the photo that the pixels are from
    row = dif + 1

    while row < (height - dif):

        rowIndex = row * width

        for col in range(newSize):
            i = row * width + dif + col
            new_pixels.append(pixels[i])

        row += 1

    return new_pixels
