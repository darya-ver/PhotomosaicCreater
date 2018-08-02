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
#
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
def convertIntoFinalImage(arrayOfImages, height, width, sizeOfSquare):

    # convert into double array
    doubleArray = convertIntoDoubleArray(arrayOfImages, height, width)

    # where final image pixels will be stored
    finalImage = []

    finalPixelSize = height * width * sizeOfSquare * sizeOfSquare
    currentPixelNum = 0

    print("\t0%")


    # go throug each row in
    for rowList in doubleArray:

        # start of with the first pixel and the first row
        imgIndx = 0
        row = 0

        # go through width of images (goes through width number of images)
        for i in range(len(rowList)):

            while row * sizeOfSquare < sizeOfSquare * sizeOfSquare:

                # goes through each list in the row
                for pixelList in rowList:
                    imgIndx = row * sizeOfSquare

                    for i in range(sizeOfSquare):
                        finalImage.append(pixelList[imgIndx])
                        imgIndx += 1
                        currentPixelNum += 1

                        # print percentage of pixels program has gone through
                        if (currentPixelNum / finalPixelSize) == 0.1:
                                print("\t10%")
                        elif (currentPixelNum / finalPixelSize) == 0.2:
                            print("\t20%")
                        elif (currentPixelNum / finalPixelSize) == 0.3:
                            print("\t30%")
                        elif (currentPixelNum / finalPixelSize) == 0.4:
                            print("\t40%")
                        elif (currentPixelNum / finalPixelSize) == 0.5:
                            print("\t50%")
                        elif (currentPixelNum / finalPixelSize) == 0.6:
                            print("\t60%")
                        elif (currentPixelNum / finalPixelSize) == 0.7:
                            print("\t70%")
                        elif (currentPixelNum / finalPixelSize) == 0.8:
                            print("\t80%")
                        elif (currentPixelNum / finalPixelSize) == 0.9:
                            print("\t90%")
                        elif (currentPixelNum / finalPixelSize) == 1:
                            print("\t100%")
                row += 1

    return finalImage
