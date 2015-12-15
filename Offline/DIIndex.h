/***************************************************************************
 *
 * TODO: Project Title
 *
 * Author: Florent Guiotte <guiotte.florent@gmail.com>
 *
 **************************************************************************/

#ifndef __DIINDEX_H__
#define __DIINDEX_H__
#include <opencv2/opencv.hpp>
#include <vector>

class DIIndex {
    public:
        DIIndex(const std::vector<cv::Mat> & idb);
        ~DIIndex();
        void indexDB(const std::string & detector = "SIFT", const std::string & extractor = "SIFT");
        void push(const std::string & url, const cv::Mat);

    private:
        std::vector<std::string> _pidb;
        std::vector<cv::Mat> _idb;
        std::vector<std::vector<cv::KeyPoint> > _kdb;
        std::vector<cv::Mat> _ddb;
};

#endif /* __DIINDEX_H__ */
