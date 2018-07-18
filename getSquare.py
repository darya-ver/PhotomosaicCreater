####################
#       getSquare.py
####################

from PIL import Image
import math

#
#   converts the image into a square
#
#       returns:    [array of pixels of square image, size of new image]
#
#       im:         image that is being converted into sqaure
#
def squareImage(im):

    # load the pixel data from im.
    pixels = im.getdata()

    # get the width and height of the current image
    width, height = im.size

    # will be set to the shortest dimension later on
    newSize = 0

    # create a list to hold the new image pixel data.
    new_pixels = []

    # if image is horizontal
    if(width > height):

        newSize = height
        dif = (width - height) // 2

        row = 0
        while (row * width) < len(pixels):
            rowIndex = row * width

            for col in range(height):
                i = row * width + dif + col
                new_pixels.append(pixels[i])

            row += 1

    # if image is vertical
    else:

        newSize = width
        dif = (height - width)//2

        # moves past the first dif rows
        i = width * dif

        # copies over the next width rows
        widthSqaured = width * width
        for j in range(widthSqaured):
            new_pixels.append(pixels[i])
            i += 1

    return [new_pixels, newSize]
