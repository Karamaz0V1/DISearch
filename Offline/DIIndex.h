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
#define ID_IMAGE_FILE "id_image"
#define ID_DESC_FILE "id_desc"

class DIIndex {
    public:
        DIIndex();
        DIIndex(const std::vector<cv::Mat> & idb);
        ~DIIndex();
        void push(const std::string & url, const cv::Mat);
        void loadDB(const std::string & url);
        void indexDB(const std::string & detector = "SIFT", const std::string & extractor = "SIFT");
        void writeDB(const std::string & url = "./") const;

    private:
        std::vector<std::string> _pidb;                 // Picture url DB
        std::vector<cv::Mat> _idb;                      // Picture DB
        std::vector<std::vector<cv::KeyPoint> > _kdb;   // Keypoints BD
        std::vector<cv::Mat> _ddb;                      // Descriptors DB
        std::vector<std::string> _extFilter;             // File extension filter
};

#endif /* __DIINDEX_H__ */
