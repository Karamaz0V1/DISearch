/***************************************************************************
 *
 * TODO: Project Title
 *
 * Author: Florent Guiotte <guiotte.florent@gmail.com>
 *
 **************************************************************************/

#include "DIIndex.h"

using namespace std;
using namespace cv;

DIIndex::DIIndex(const std::vector<cv::Mat> & idb) : _idb(idb) {}

void DIIndex::indexDB(const string & detector, const string & extractor) {
    FeatureDetector * fd = FeatureDetector::create(detector);
    cout << "Extract " << detector << " keypoints from images..." << endl;
    fd->detect(_idb, _kdb);

    DescriptorExtractor * de = DescriptorExtractor::create(extractor);
    cout << "Create " << extractor << " descriptors..." << endl;
    de->compute(_idb, _kdb, _ddb);

    delete fd, de;
}

