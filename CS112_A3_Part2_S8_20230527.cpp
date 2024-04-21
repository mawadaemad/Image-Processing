/*
Name: Mawada Emad Abdo Omar
ID:20230527
Section: 8
CS112_A3_Part2_s8_20230527

*/


#include <iostream>
#include "Image_Class.h"
using namespace std;
    //function to rotate
    Image rotate_image_90(Image& image) {
        int new_width = image.height;
        int new_height = image.width;
        Image rotated_image(new_width, new_height);

        for (int i = 0; i < new_width; ++i) {
            for (int j = 0; j < new_height; ++j) {
                rotated_image(i, j, 0) = image(new_height - 1 - j, i, 0);
                rotated_image(i, j, 1) = image(new_height - 1 - j, i, 1);
                rotated_image(i, j, 2) = image(new_height - 1 - j, i, 2);
            }
        }

        return rotated_image;
    }

    Image rotate_image_180(Image& image) {
        int new_width = image.width;
        int new_height = image.height;
        Image rotated_image(new_width, new_height);

        for (int i = 0; i < new_width; ++i) {
            for (int j = 0; j < new_height; ++j) {
                rotated_image(i, j, 0) = image(new_width - 1 - i, new_height - 1 - j, 0);
                rotated_image(i, j, 1) = image(new_width - 1 - i, new_height - 1 - j, 1);
                rotated_image(i, j, 2) = image(new_width - 1 - i, new_height - 1 - j, 2);
            }
        }

        return rotated_image;
    }

    Image rotate_image_270(Image& image) {
        int new_width = image.height;
        int new_height = image.width;
        Image rotated_image(new_width, new_height);

        for (int i = 0; i < new_width; ++i) {
            for (int j = 0; j < new_height; ++j) {
                rotated_image(i, j, 0) = image(j, new_width - 1 - i, 0);
                rotated_image(i, j, 1) = image(j, new_width - 1 - i, 1);
                rotated_image(i, j, 2) = image(j, new_width - 1 - i, 2);
            }
        }

        return rotated_image;
    }



    //function to crop the image
    Image cropImage( Image& image, int startX, int startY, int width, int height) {
        Image croppedImage(width, height);

        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    croppedImage(i, j, k) = image(startX + i, startY + j, k);
                }
            }
        }

        return croppedImage;
    }


    //function to resize the image
    Image resizeImage( Image& image, int newWidth, int newHeight) {
        Image resizedImage(newWidth, newHeight);

        // Calculate scaling factors
        double scaleX = static_cast<double>(image.width) / newWidth;
        double scaleY = static_cast<double>(image.height) / newHeight;

        // Iterate over each pixel in the resized image
        for (int i = 0; i < newWidth; ++i) {
            for (int j = 0; j < newHeight; ++j) {
                // Calculate corresponding pixel position in the original image
                int originalX = static_cast<int>(i * scaleX);
                int originalY = static_cast<int>(j * scaleY);

                // Set the pixel value in the resized image to the corresponding pixel value in the original image
                for (int k = 0; k < 3; ++k) {
                    resizedImage(i, j, k) = image(originalX, originalY, k);
                }
            }
        }

        return resizedImage;
    }


    //function to add more purple
        Image applyPurple_color(Image& image) {
        Image purple_image(image.width, image.height);

        // add purple to each pxle
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {


                purple_image(i, j, 0) = min(255, static_cast<int>(image(i, j, 0)) + 50);
                purple_image(i, j, 1) = min(255, static_cast<int>(image(i, j, 1)));
                purple_image(i, j, 2) = min(255, static_cast<int>(image(i, j, 2)) + 100);
            }
        }



        return purple_image;
    }












int main() {
    int choice;
    cout << "Enter Your Choice by Number:\n";
    cout << "Filter 1: Gray scale Conversion. " << endl;
    cout << "Filter 2: Black and White." << endl;
    cout << "Filter 3: Invert Image." << endl;
    cout << "Filter 4: Flip Image." << endl;
    cout << "Filter 5: Darken and Lighten Image." << endl;
    cout << "Filter 6: Rotate Image." << endl;
    cout << "Filter 7: Cropped Image." << endl;
    cout << "Filter 8: Resize Image." << endl;
    cout << "Filter 9: Make it more Purple" << endl;
    cout << "Filter 10: infrared" << endl;


    cin >> choice;

    if (choice == 1) { // converting to gray scale
        string filename;
        cout << "Please enter the name of the colored image to turn to grayscale" << endl;
        cin >> filename;

        Image image(filename);

        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                unsigned int avg = 0; //initialize average value
                for (int k = 0; k < 3; ++k) {
                    avg += image(i, j, k); // getting the average value
                }
                avg /= 3; //calculate average

                //set all channels to the average value
                image(i, j, 0) = avg;
                image(i, j, 1) = avg;
                image(i, j, 2) = avg;
            }
        }

        cout << "Please enter the filename to store the new image and specify extension (.jpg, .bmp, .png, .tga): ";
        cin >> filename;

        image.saveImage(filename);
        system(filename.c_str());
    } else if (choice == 2) { // converting to black and white
        string filename;
        cout << "Please enter the name of the colored image to turn to black and white:\n";
        cin >> filename;

        Image image(filename);

        unsigned int threshold = 128;

        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                // calculate brightness from rgb values
                unsigned int brightness = 0.2126 * image(i, j, 0) + 0.7152 * image(i, j, 1) + 0.0722 * image(i, j, 2);

                // set pixel to black or white based on threshold
                if (brightness >= threshold) {
                    image(i, j, 0) = 255; // set red channel to white
                    image(i, j, 1) = 255; // set green channel to white
                    image(i, j, 2) = 255; // set blue channel to white
                } else {
                    image(i, j, 0) = 0; // set red channel to black
                    image(i, j, 1) = 0; // set green channel to black
                    image(i, j, 2) = 0; // set blue channel to black
                }
            }
        }

        cout << "Please enter the filename to store the new image and specify extension (.jpg, .bmp, .png, .tga): ";
        cin >> filename;

        image.saveImage(filename);
        system(filename.c_str());
    } else if (choice == 3) { // inverting the image
        string filename;
        cout << "Please enter the name of the colored image to invert:";
        cin >> filename;

        Image image(filename);

        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                // Invert pixel intensity
                image(i, j, 0) = 255 - image(i, j, 0); // invert red
                image(i, j, 1) = 255 - image(i, j, 1); // invert green
                image(i, j, 2) = 255 - image(i, j, 2); // invert blue
            }
        }

        cout << "Please enter the filename to store the new image and specify extension (.jpg, .bmp, .png, .tga): ";
        cin >> filename;

        image.saveImage(filename);
        system(filename.c_str());
    } else if (choice == 4) { // flipping the image
        char cho;
        cout << "Press H or V to choose if you want to flip your image horizontally or vertically \n";
        cin >> cho;

        if (cho == 'H') {
            string filename;
            cout << "Please enter the name of the colored image to flip  Horizontally: \n";
            cin >> filename;

            Image image(filename);
            Image flippedImage(image.width, image.height); // create new image with the same dimensions as the original

            for (int i = 0; i < image.width; ++i) {
                for (int j = 0; j < image.height; ++j) {
                    // copy pixels from the original image in reverse to the flipped image
                    flippedImage(i, j, 0) = image(image.width - 1 - i, j, 0); // Red
                    flippedImage(i, j, 1) = image(image.width - 1 - i, j, 1); // green
                    flippedImage(i, j, 2) = image(image.width - 1 - i, j, 2); // blue
                }
            }

            cout << "Please enter the filename to store the horizontally flipped image and specify extension (.jpg, .bmp, .png, .tga): ";
            cin >> filename;

            flippedImage.saveImage(filename);
            system(filename.c_str());

        } else if (cho == 'V') {
            string filename;
            cout << "Please enter the name of the colored image to flip  Vertically: \n";
            cin >> filename;

            Image image(filename);
            Image flippedImage(image.width, image.height); // create new image with the same dimensions as the original

            for (int i = 0; i < image.width; ++i) {
                for (int j = 0; j < image.height; ++j) {
                    flippedImage(i, j, 0) = image(i, image.height - 1 - j, 0);
                    flippedImage(i, j, 1) = image(i, image.height - 1 - j, 1);
                    flippedImage(i, j, 2) = image(i, image.height - 1 - j, 2);
                }
            }

            cout << "Please enter the filename to store the Vertically flipped image and specify extension (.jpg, .bmp, .png, .tga): ";
            cin >> filename;

            flippedImage.saveImage(filename);
            system(filename.c_str());
        }
    } else if (choice == 5) { // Darken and Lighten Image
        char ch;
        cout << "Choose D to Darken or L to Lighten \n";
        cin >> ch;
        if (ch == 'D') {
            string filename;
            cout << "Please enter the name of the image to Darken: \n";
            cin >> filename;

            Image image(filename);
            for (int i = 0; i < image.width; ++i) {
                for (int j = 0; j < image.height; ++j) {
                    image(i, j, 0) = max(0, static_cast<int>(image(i, j, 0)) - 70); // decrease red
                    image(i, j, 1) = max(0, static_cast<int>(image(i, j, 1)) - 70); // decrease green
                    image(i, j, 2) = max(0, static_cast<int>(image(i, j, 2)) - 70); // decrease blue
                }
            }

            cout << "Please enter the filename to store the darkened image and specify extension (.jpg, .bmp, .png, .tga): ";
            cin >> filename;

            image.saveImage(filename);
            system(filename.c_str());
        } else if (ch == 'L') {
            string filename;
            cout << "Please enter the name of the image to Lighten: \n";
            cin >> filename;

            Image image(filename);
            for (int i = 0; i < image.width; ++i) {
                for (int j = 0; j < image.height; ++j) {
                    image(i, j, 0) = min(255, static_cast<int>(image(i, j, 0)) + 70); // increase red
                    image(i, j, 1) = min(255, static_cast<int>(image(i, j, 1)) + 70); // increase green
                    image(i, j, 2) = min(255, static_cast<int>(image(i, j, 2)) + 70); // increase blue
                }
            }

            cout << "Please enter the filename to store the lightened image and specify extension (.jpg, .bmp, .png, .tga): ";
            cin >> filename;

            image.saveImage(filename);
            system(filename.c_str());
        }



        else {
            cout << "Invalid choice. Please choose D to Darken or L to Lighten.\n";
        }

    }
     else if (choice ==6){ //rotate
          int degree ;
         cout<<"choose 90 ,180 or 270 to rotate \n";
         cin>>degree;
         if(degree ==270){

                    string filename;
                    cout << "Please enter the name of the image to Rotate: \n";
                    cin >> filename;

                    Image image(filename);

                    Image rotatedImage(image.height, image.width); // Rotated dimensions

                    for (int i = 0; i < image.width; ++i) {
                        for (int j = 0; j < image.height; ++j) {
                            rotatedImage(j, image.width - 1 - i, 0) = image(i, j, 0);
                            rotatedImage(j, image.width - 1 - i, 1) = image(i, j, 1);
                            rotatedImage(j, image.width - 1 - i, 2) = image(i, j, 2);
                        }
                    }

                    cout << "Please enter the filename to store the rotated image and specify extension (.jpg, .bmp, .png, .tga): ";
                    cin >> filename;

                    rotatedImage.saveImage(filename);
                    system(filename.c_str());

                    cout << "Image successfully rotated and saved as " << filename << endl;
                    }
            else if(degree==180){
                string filename;
                cout << "Please enter the name of the image to Rotate: \n";
                cin >> filename;

                Image image(filename);

                Image rotatedImage(image.width, image.height); // Rotated dimensions

                for (int i = 0; i < image.width; ++i) {
                    for (int j = 0; j < image.height; ++j) {
                        rotatedImage(image.width - 1 - i, image.height - 1 - j, 0) = image(i, j, 0);
                        rotatedImage(image.width - 1 - i, image.height - 1 - j, 1) = image(i, j, 1);
                        rotatedImage(image.width - 1 - i, image.height - 1 - j, 2) = image(i, j, 2);
                    }
                }

                cout << "Please enter the filename to store the rotated image and specify extension (.jpg, .bmp, .png, .tga): ";
                cin >> filename;

                rotatedImage.saveImage(filename);
                system(filename.c_str());

                cout << "Image successfully rotated and saved as " << filename << endl;


            }

            else if(degree == 90){

                string filename;
            cout << "Please enter the name of the image to Rotate: \n";
            cin >> filename;

            Image image(filename);

            Image rotatedImage(image.height, image.width); // Rotated dimensions

            for (int i = 0; i < image.width; ++i) {
                for (int j = 0; j < image.height; ++j) {
                    rotatedImage(j, image.width - 1 - i, 0) = image(i, j, 0);
                    rotatedImage(j, image.width - 1 - i, 1) = image(i, j, 1);
                    rotatedImage(j, image.width - 1 - i, 2) = image(i, j, 2);
                }
            }

            cout << "Please enter the filename to store the rotated image and specify extension (.jpg, .bmp, .png, .tga): ";
            cin >> filename;

            rotatedImage.saveImage(filename);
            system(filename.c_str());

            cout << "Image successfully rotated and saved as " << filename << endl;

            }
    }
    else if (choice ==7){ //crop image

            string filename;
        cout << "Please enter the name of the image to crop: \n";
        cin >> filename;

        Image image(filename);

        int startX, startY, width, height;
        cout << "Enter the starting point (x, y) of the area to keep: ";
        cin >> startX >> startY;
        cout << "Enter the width and height of the area to cut: ";
        cin >> width >> height;

        // Check if the specified dimensions are within the bounds of the image
        if (startX >= 0 && startY >= 0 && startX + width <= image.width && startY + height <= image.height) {
            // Crop the image using the cropImage function
            Image croppedImage = cropImage(image, startX, startY, width, height);

            cout << "Please enter the filename to store the cropped image and specify extension (.jpg, .bmp, .png, .tga): ";
            cin >> filename;

            croppedImage.saveImage(filename);
            system(filename.c_str());

            cout << "Image successfully cropped and saved as " << filename << endl;
        } else {
            cout << "Invalid cropping dimensions. Please ensure the specified area is within the bounds of the image." << endl;
        }



    }

    else if(choice == 8){ //resize




    string filename;
    cout << "Please enter the name of the image to resize: \n";
    cin >> filename;

    Image image(filename);

    int newWidth, newHeight;
    cout << "Enter the new width and height for the resized image: ";
    cin >> newWidth >> newHeight;

    // Resize the image using the resizeImage function
    Image resizedImage = resizeImage(image, newWidth, newHeight);

    cout << "Please enter the filename to store the resized image and specify extension (.jpg, .bmp, .png, .tga): ";
    cin >> filename;

    resizedImage.saveImage(filename);
    system(filename.c_str());

    cout << "Image successfully resized and saved as " << filename << endl;


    }




        //Bonus Filters
    else if(choice ==9){
    string filename;
        cout << "Enter the Image that You want to make more purple: \n";
        cin >> filename;

        Image image(filename);

        Image purpleImage = applyPurple_color(image);

        cout << "Please enter the filename to store the new image and specify extension (.jpg, .bmp, .png, .tga): ";
        cin >> filename;

        purpleImage.saveImage(filename);
        system(filename.c_str());

        cout << "Image with purple tint saved as '" << filename << "'\n";





    }



    else if(choice==10){
        string filename;
        cout << "Please enter the name of the colored image to invert:";
        cin >> filename;

        Image image(filename);

        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {

                image(i, j, 0) = 255;
                image(i, j, 1) = 255 - image(i, j, 1); // invert green
                image(i, j, 2) = 255 - image(i, j, 2); // invert blue
            }
        }

        cout << "Please enter the filename to store the new image and specify extension (.jpg, .bmp, .png, .tga): ";
        cin >> filename;

        image.saveImage(filename);
        system(filename.c_str());

    }



    else {
        cout << "Please Choose one of The Previous Filters by Number \n ";
    }

    return 0;
}










