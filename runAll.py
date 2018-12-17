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
import sys
from PIL import Image
import argparse

#
#   runs all the methods together
#
def main():

    # parse the arguments given in the command line
    parser = argparse.ArgumentParser()
    req_grp = parser.add_argument_group(title='required arguments')
    req_grp.add_argument("-i", "--input", required=True, help="original image that is being converted")
    req_grp.add_argument("-o", "--output", required=True, help="file name for final image to be saved to")
    args = parser.parse_args()

    # set the variables accordingly
    refImgName = args.input
    newFileName = args.output

    # the original reference image
    referenceImg = ""

    # make sure the OG image exists
    try:
        referenceImg = imageSetting.load_img(refImgName, "")

    # if it doesn't exist, print error message
    except:
        print("\nERROR! Your file was not found:\t", refImgName)
        exit()

    # check the newFile doesn't already exist
    for root, dirs, filenames in os.walk("."):
        for f in filenames:
            if newFileName == f:
                print("\nERROR! This image already exists.")
                print("Are you sure you want to override? (y/n)")
                answer = input("\t>> ")
                if answer == "n" or answer == "":
                    exit()

    # the directory where original images are found
    inDir = './originalPhotos/'

    # directory where reduced photos will be saved
    outDir = './reducedPhotos/'

    print("\nThis program will be converting", refImgName + ".")

    # used to name the images
    i = 0

    # resolution of the square images that make up the larger image
    imageSize = 115.0

    ################################
    #       REDUCE IMAGES TO 115x115
    ################################
    print("\n>> Reducing images...\n")

    for root, dirs, filenames in os.walk(inDir):
        for f in filenames:
            if ('.jpg' in f or '.JPG' in f):

                # convert the image into a square 100x100 and save that image
                newImgName = \
                    convertOGIntoSquare.convertOGIntoSquare(f, inDir, outDir, i, imageSize)

                print("\tConverted %s " %(newImgName))

                # increment so that file names are different
                i += 1


    ########################
    #       MAKE FINAL IMAGE
    ########################

    print("\nDone reducing images. \n\n>> Matching pixels with images...")

    # the directory where square 100x100 images are found
    inDir = './reducedPhotos/'

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

    print("Done matching pixels with images.")

    print("\n>> Creating final image...\n")

    # sets the final array of pixels to the array that the function returns
    new_pixels = \
        convertIntoFinalImage.convertIntoFinalImage(phts_order, width, height, int(imageSize))
    print("\nDone creating final image.")

    # creating the image from the pixel array
    print("\n>> Pulling data into jpg photo...")
    newim = Image.new("RGB", (width * int(imageSize), height * int(imageSize)))
    newim.putdata(new_pixels)
    print("Done pulling data.")

    # save image and show it
    print("\n>> Saving image...")
    imageSetting.save_img(newim, newFileName)
    print("Done saving image.")
    imageSetting.show_img(newim)

    print("\n*** Done! Your new image has been created. ")

if __name__ == '__main__':
    main()

























#
