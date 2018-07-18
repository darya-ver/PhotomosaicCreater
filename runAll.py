#################
#       runAll.py
#################

import convertOGIntoSquare
import averageColor
import findClosestColor
import convertIntoFinalImage

import imageSetting
import os
import math
from PIL import Image

#
#   runs all the methods together
#
def main():

    # the directory where original images are found
    inDir = './originalPhotos/'

    # directory where reduced photos will be saved
    outDir = './reducedPhotos/'


    # used to name the images
    i = 0

    # resolution of the square images that make up the larger image
    imageSize = 100.0

    ################################
    #       REDUCE IMAGES TO 100x100
    ################################
    print("\nReducing images...\n")

    for root, dirs, filenames in os.walk(inDir):
        for f in filenames:
            if ('.jpg' in f or '.JPG' in f) and not ("SQUARE" in f):

                # convert the image into a square 100x100 and save that image
                newImgName = \
                    convertOGIntoSquare.convertOGIntoSquare(f, inDir, outDir, i, imageSize)

                print("\tConverted %s " %(newImgName))

                # increment so that file names are different
                i += 1


    ########################
    #       MAKE FINAL IMAGE
    ########################

    print("\nMatching pixels with images...\n")

    # the directory where square 100x100 images are found
    inDir = './reducedPhotos/'

    # the original reference image
    referenceImg = imageSetting.load_img("jannittaDog.png", "")

    # get the array of pixels for the image and its size
    pixels = referenceImg.getdata()
    width, height = referenceImg.size

    # ARRAYS
    new_pixel_image_arrays = []     # array containing image contents
    phts_order = []                 # photos in order for final image
    avg_colors = []                 # contains average
    new_pixels = []                 # final image array

    # go through each reduced photo and add its average color and pixel array
    #   to 2 separate lists
    for root, dirs, filenames in os.walk(inDir):
        for f in filenames:
            if ('.jpg' in f or '.JPG' in f):

                # load the image
                img = imageSetting.load_img(f, inDir)

                # get the average color and add to list
                avgColor = averageColor.averageColor(img)
                avg_colors.append(avgColor)

                # get the array of pixels for that image and add to list
                pixelArray = img.getdata()
                new_pixel_image_arrays.append(pixelArray)

    # loops through each pixel in the reference image and finds the closest
    #   image for that pixel - adds this pixel array to the arrray of final
    #   images
    for p in pixels:

        colorInd = findClosestColor.findClosestColor(avg_colors, p)
        phts_order.append(new_pixel_image_arrays[colorInd])

    print("\nDone matching pixels with images...\n")

    print("\nCreating final image...\n")

    # sets the final array of pixels to the array that the function returns
    new_pixels = \
        convertIntoFinalImage.convertIntoFinalImage(phts_order, width, height)

    newim = Image.new("RGB", (width * int(imageSize), height * int(imageSize)))
    newim.putdata(new_pixels)
    imageSetting.save_img(newim, "babaColage1.jpg")
    imageSetting.show_img(newim)

if __name__ == '__main__':
    main()

























#
