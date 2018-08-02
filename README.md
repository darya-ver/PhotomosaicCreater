# PhotomosaicCreater
This program creates a photomosaic from reference images and a reference photo

## How to download
Click green button at the top that says "Clone or download", then "Download in ZIP". This will download the entire folder in your "Downloads" folder on your computer.

Once that is done, open your terminal (or Windows equivalent) and navigate to your "PhotomosaicCreater" folder that is in your "Downloads" on your computer. (Help: [Linux Help](https://www.digitalocean.com/community/tutorials/basic-linux-navigation-and-file-management))

To make sure you have everything, type "ls" (or "dir" in Windows). This is what should appear (if this doesn't appear, try deleting the folder and re-downloading):

* README.md
* convertOGIntoSquare.py
* imageSetting.py
* reduceImageSize.py
* darAndNicColor.jpg
* jannitta3Colors.jpg
* reducedPhotos (folder)
* averageColor.py
* findClosestColor.py
* jannitta3Colors2.jpg
* resizeSquare.py
* convertIntoFinalImage.py
* getSquare.py
* originalPhotos (folder)
* runAll.py

## Setting up image bank
Copy all your images that you want to use as the database of images into the folder "originalPhotos" located in the "PhotomosaicCreater" folder.

There are already 8 images in the folder, each representing a color from the rainbow. Feel free to get rid of these images if you do not like them.

![Red](/originalPhotos/red.jpg =100)
![orange](/originalPhotos/orange.jpg =100)
![yellow](/originalPhotos/yellow.jpg =100)
![green](/originalPhotos/green.jpg =100)
![blue](/originalPhotos/blue.jpg =100)
![purple](/originalPhotos/purple.jpg =100)
![black](/originalPhotos/black.jpg =100)
![white](/originalPhotos/white.jpg =100)


## Setting up original image
Copy your original image into the main folder "PhotomosaicCreater". Make sure the image is relatively small - the biggest dimension should be no more than 150 pixels. You can make the image bigger, but the program will take an extremely long time to run.

## Running the program
Make sure you are still in the "PhotomosaicCreater" folder in your terminal (or Windows Equivalent).

Make sure you have Python3 ([Python3 download](https://www.python.org/downloads/)).

### Mac
`python3 runAll.py -h`

### Windows
`python runAll.py -h`

This is the help message that will appear:

> usage: runAll.py [-h] -i INPUT -o OUTPUT
>
> optional arguments:
>
>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;-h, --help            show this help message and exit
>
> required arguments:
>
>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;-i INPUT, --input INPUT
>
>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;original image that is being converted
>
>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;-o OUTPUT, --output OUTPUT
>
>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;file name for final image to be saved to

So, to run, provide an input file and an output file. This will run the program. Any other errors that occur will be printed to the screen and you can adjust accordingly.

## Example run

### Mac
`python3 runAll.py -i dogs.jpg -o dogsMosaic.jpg`

### Windows
`python runAll.py -i dogs.jpg -o dogsMosaic.jpg`
