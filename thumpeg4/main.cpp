#include "highgui.h"	// for loading images
#include "Feature.h"	// to use the feature extraction library

#include <iostream>

int main( int argc, char* argv[] )
{
        // load an image
        IplImage* image = cvLoadImage("motor.jpg");

        ///-- extract global image descriptors --

        // create a Frame object (see include/Frame.h)
        // allocate memory for 3-channel color and 1-channel gray image and mask
        Frame* frame = new Frame( image->width, image->height, true, true, true);

        // set the image of the frame
        frame->setImage(image);

        // compute Color Structure descriptor
        XM::ColorStructureDescriptor* csd = Feature::getColorStructureD(frame, 32);

        // write to screen
        for(unsigned int i = 0; i < csd->GetSize(); i++)
                std::cout << (int)csd->GetElement(i) << " " ;
        std::cout << std::endl;

        // release descriptor
        delete csd;

        // release the images..
        delete frame;
        cvReleaseImage(&image);

        return 0;
}
