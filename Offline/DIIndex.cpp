/***************************************************************************
 *
 * TODO: Project Title
 *
 * Author: Florent Guiotte <guiotte.florent@gmail.com>
 *
 **************************************************************************/

#include "DIIndex.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <opencv2/nonfree/features2d.hpp>

using namespace std;
using namespace cv;

DIIndex::DIIndex() {}
DIIndex::DIIndex(const std::vector<cv::Mat> & idb) : _idb(idb) {}
DIIndex::~DIIndex() {}

void DIIndex::loadDB(const string & url) {
    // TODO: filter dir
    // TODO: edit filter
    _extFilter = {"jpg"};
    vector<string> dl = listDir(url);
    for (vector<string>::const_iterator it = dl.begin(); it != dl.end(); it++)
        for (vector<string>::const_iterator itf = _extFilter.begin(); itf != _extFilter.end(); itf++)
            if(isExt(*it, *itf)) {
                cout << "load: " << url << '/' << *it << endl;
                _pidb.push_back(*it);
                _idb.push_back(imread(url + '/' + *it));
                //imshow("LOAD DB", _idb.back());
                //waitKey(0);
            }
    cout << _idb.size() << " images in DB." << endl;
}

void DIIndex::indexDB(const string & detector, const string & extractor) {
    //FeatureDetector * fd = FeatureDetector::create(detector);
    FeatureDetector * fd = new SiftFeatureDetector();
    cout << "Extract " << detector << " keypoints from images..." << endl;
    fd->detect(_idb, _kdb); // plz opencv :'(
    //for (vector<Mat>::const_iterator it = _idb.begin(); it != _idb.end(); it++) {
    //    fd->detect(*it, 

    //DescriptorExtractor * de = DescriptorExtractor::create(extractor);
    DescriptorExtractor * de = new SiftDescriptorExtractor();
    cout << "Create " << extractor << " descriptors..." << endl;
    de->compute(_idb, _kdb, _ddb);

    delete fd, de;
}

void DIIndex::writeDB(const string & url) const {
    ofstream idImages, idDesc;
    cout << "Write " << ID_IMAGE_FILE << "..." << endl;
    idImages.open((url + ID_IMAGE_FILE).c_str());
    for (int i = 0; i < _pidb.size(); i++)
        idImages << i << ';' << _pidb[i] << endl;
    idImages.close();

    cout << "Write " << ID_DESC_FILE << "..." << endl;
    idDesc.open((url + ID_DESC_FILE).c_str());
    for (int i = 0; i < _idb.size(); i++) {
        Mat tmp = _ddb[i];
        for (int j = 0; j < tmp.rows; j++) 
        idDesc << i << ';' << tmp.row(j) << endl;
    }
    idDesc.close();
            

}
