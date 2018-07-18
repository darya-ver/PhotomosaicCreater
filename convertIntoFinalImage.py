################################
#       convertIntoFinalImage.py
################################

from PIL import Image
import math

#
#   converts arr into double array of given width and height
#
#       returns:    double array with size width and height
#
#       arr:        arr that is being converted
#       width:      width of double array (number of columns)
#       height:     height of double array (number of rows)
def convertIntoDoubleArray(arr, width, height):
    returnArray = []
    index = 0
    for row in range(height):
        arr2 = []
        for col in range(width):
            arr2.append(arr[index])
            index += 1
        returnArray.append(arr2)

    return returnArray

#
#   takes array of images and creates a single array of pixels
#
#       returns:        single array of pixels representing final image
#
#       arrayOfImages:  array of arrays of pixels in order for final image
#       height:         height of final image (# of photos in height)
#       width:          width of final image (# of photos in width)
#
def convertIntoFinalImage(arrayOfImages, height, width):

    # convert into double array
    doubleArray = convertIntoDoubleArray(arrayOfImages, height, width)

    # where final image pixels will be stored
    finalImage = []

    # go throug each row in
    for rowList in doubleArray:

        # start of with the first pixel and the first row
        imgIndx = 0
        row = 0

        # go through width of images (goes through width number of images)
        for i in range(len(rowList)):

            while row * 100 < 100 * 100:

                # goes through each list in the row
                for pixelList in rowList:
                    imgIndx = row * 100

                    for i in range(100):
                        finalImage.append(pixelList[imgIndx])
                        imgIndx += 1
                row += 1

    return finalImage
