/***************************************************************************
 *
 * TODO: Project Title
 *
 * Author: Florent Guiotte <guiotte.florent@gmail.com>
 *
 **************************************************************************/

#include "DIIndex.h"
#include <iostream>
#include <fstream>
#include <dirent.h>

using namespace std;
using namespace cv;

DIIndex::DIIndex(const std::vector<cv::Mat> & idb) : _idb(idb) {}

void DIIndex::loadDB(const string & url) {
//    DIR * dir;
//    struct dirent * ent;
//    if ((dir = opendir(url.c_str()) != NULL) {
//        while ((ent = readdir(dir)) != NULL) {
//            cout << ent->d_name << endl;
//        }
//        closedir (dir);
//    }
}

void DIIndex::indexDB(const string & detector, const string & extractor) {
    FeatureDetector * fd = FeatureDetector::create(detector);
    cout << "Extract " << detector << " keypoints from images..." << endl;
    fd->detect(_idb, _kdb);

    DescriptorExtractor * de = DescriptorExtractor::create(extractor);
    cout << "Create " << extractor << " descriptors..." << endl;
    de->compute(_idb, _kdb, _ddb);

    delete fd, de;
}

void DIIndex::writeDB(const string & url) const {
    ofstream idImages;
    idImages.open((url + ID_IMAGE_FILE).c_str());

    idImages.close();

}
