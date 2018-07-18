##############################
#       convertOGIntoSquare.py
##############################

from PIL import Image

import imageSetting
import getSquare
import math
import reduceImageSize
import resizeSquare

#
#   converts original image into a square of 100x100
#
#       imgName:    name of image that is being changed
#       inDir:      where photo is located
#       outDir:     where photo is being stored
#       imgNum:     img number (used for naming saved image)
#       imageSize:  desired img size (in this case 100)
#
def convertOGIntoSquare(imgName, inDir, outDir, imgNum, imageSize):

        # load the image
        img = imageSetting.load_img(imgName, inDir)

        # get square image (array of pixels)
        squareArray = getSquare.squareImage(img)[0]
        sizeOfSquare = getSquare.squareImage(img)[1]

        # get ratio between width and desired imageSize (100)
        widthRatio = sizeOfSquare / imageSize

        # if it's not evenly divisable by imageSize, make it the next closest
        #   multiple of that number and then reduce
        if not widthRatio.is_integer():

            newSize = math.floor(widthRatio) * math.floor(imageSize)
            squareArray = resizeSquare.resizeSquare(squareArray, newSize, sizeOfSquare)
            sizeOfSquare = newSize

        ratio = sizeOfSquare // math.floor(imageSize)

        # new name for the new image
        newImgName = outDir + "IM_" + format(imgNum, '04d') + "_REDUCED.jpg"

        newImg = reduceImageSize.reduceImageSize(squareArray, ratio, sizeOfSquare)

        # save reduced image
        imageSetting.save_img(newImg, newImgName)

        return newImgName
