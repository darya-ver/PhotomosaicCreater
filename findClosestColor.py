###########################
#       findClosestColor.py
###########################

import math

#
#   finds the closet color to a pixel from a list of colors
#
#       returns:        the index where the closest color is in list
#
#       arrayColors:    the array holding the average colors from imgs in order
#       pixelColor:     the pixel from OG image that program is finding img for
#
def findClosestColor(arrayColors, pixelColor):

    # variables used to find min difference and it's index
    minDif = 100000
    minDifIndex = -1

    # go through each color in arrayColors and see if it's closer to pixelColor
    #   than a pixel before it
    for colorInd in range(len(arrayColors)):

        # get the difference in red, green, and blue of 2 pixels
        difRed = abs(arrayColors[colorInd][0] - pixelColor[0])
        difGreen = abs(arrayColors[colorInd][1] - pixelColor[1])
        difBlue = abs(arrayColors[colorInd][2] - pixelColor[2])

        # get the "length" of the difference vector
        num = difRed ** 2 + difGreen ** 2 + difBlue ** 2
        num = math.sqrt(num)

        # update variables if current pixel is smaller
        if num < minDif:
            minDif = num
            minDifIndex = colorInd

    return minDifIndex
