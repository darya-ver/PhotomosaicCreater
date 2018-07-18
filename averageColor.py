#######################
#       averageColor.py
#######################

from PIL import Image
import math

def averageColor(im):

    # load the pixel data from im.
    pixels = im.getdata()

    # create a list to hold the new image pixel data.
    new_pixels = []

    totalRed = 0
    totalGreen = 0
    totalBlue = 0
    for p in pixels:
        totalRed += p[0]
        totalGreen += p[1]
        totalBlue += p[2]

    finalRed = totalRed // len(pixels)
    finalGreen = totalGreen // len(pixels)
    finalBlue = totalBlue // len(pixels)

    finalColor = (finalRed, finalGreen, finalBlue)

    # for i in range(100 * 100):
    #     new_pixels.append(finalColor)

    #newim = Image.new("RGB", (100, 100))
    #newim.putdata(new_pixels)
    return finalColor
