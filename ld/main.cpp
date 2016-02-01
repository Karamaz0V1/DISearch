//============================================================================
// Name        : images_search_motor.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
#include <string>

#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/nonfree/nonfree.hpp"
using namespace std;
using namespace cv;


void save_imgsInList(string LIST_DIR, string IMG_DIR, vector<Mat>&imgs, vector<string>&names, string img_type) {
	string line, img_name;
	ifstream myfile(LIST_DIR.c_str());
	while(getline(myfile, line)) {
		img_name = IMG_DIR + line + "." + img_type;
		cout << img_name << endl;
		Mat img = imread(img_name, CV_LOAD_IMAGE_COLOR);
		imgs.push_back(img);
		names.push_back(line);
	}
}


void write_descriptorsInFile(string base, string type, int minHessian, int nbFeatures, vector<Mat>&imgs, vector<string>&names) {
	/*----Compute keypoints of all images----*/
	initModule_nonfree();
	Ptr<FeatureDetector> fd = FeatureDetector::create(type);
	vector<string> fd_params;
	fd->getParams(fd_params);
	if(type == "SURF") {
		cout<<"SURF minHessian  = "<<minHessian<<endl;
		fd->set(fd_params[1], minHessian);
	}
	if(type == "SIFT") {
		cout<<"SIFT nbFeatures  = "<<nbFeatures<<endl;
		fd->set(fd_params[2], nbFeatures);
	}
	if(type == "HARRIS") {
		cout<<"HARRIS nbFeatures = "<<nbFeatures<<endl;
		fd->set(fd_params[2], nbFeatures);
	}

	cout<<"Get all "<<type<<" keypoints..."<<endl;
	vector<vector<KeyPoint> > keypoints; // keypoints of all images
	fd->detect(imgs, keypoints);
	cout<<"OK"<<endl;

	/*----Compute descriptors of all images----*/
	cout<<"Save all "<<type<<" descriptors..."<<endl;
	vector<Mat> descriptors;
	Ptr<DescriptorExtractor> de = DescriptorExtractor::create(type);
	de->compute(imgs, keypoints, descriptors);

	string myfile = base+type+"_descriptors.xml";
	FileStorage fs(myfile, FileStorage::WRITE);
	for(int i = 0; i < (int)names.size(); i++) {
		fs<<type+"_"+names[i]<<descriptors[i];
	}
	cout<<"OK"<<endl;

}

void read_descriptorsOutFile(string base, string type, vector<Mat>&descriptors, vector<string>&names) {
	string myfile = base+type+"_descriptors.xml";
	FileStorage fs(myfile, FileStorage::READ);
	for(int i = 0; i < (int)names.size(); i++) {
		Mat des;
		fs[type+"_"+names[i] ]>>des;
		descriptors.push_back(des);
	}
}

void image_request(Mat img, string type, int minHessian, int nbFeatures, Mat&request) {
	initModule_nonfree();
	/*----Compute keypoints of all images----*/
	Ptr<FeatureDetector> fd = FeatureDetector::create(type);
	vector<string> fd_params;
	fd->getParams(fd_params);
	if(type == "SURF") {
		cout<<"SURF minHessian param  = "<<minHessian<<endl;
		fd->set(fd_params[1], minHessian);
	}
	if(type == "SIFT") {
		cout<<"SIFT nbFeatures param  = "<<nbFeatures<<endl;
		fd->set(fd_params[2], nbFeatures);
	}
	vector<KeyPoint> keypoint; // keypoints of all images
	fd->detect(img, keypoint);

	/*----Compute descriptor of test image----*/
	Ptr<DescriptorExtractor> de = DescriptorExtractor::create(type);
	de->compute(img, keypoint, request);

}

void descriptors_index(vector<vector<DMatch> >&matches, vector<int>&nb_goodFeatures, vector<int>&indices) {

	cout<<matches.size()<<endl;
	for(int i = 0; i < (int)matches.size(); i++) {
		double max_dist = 0;
		for(int j = 0; j < (int)matches[i].size(); j++) {
			double dist = matches[i][j].distance;
			if(dist > max_dist) {
				max_dist = dist;
			}
		}
		cout<<max_dist<<endl;
		int num = 0;
		for(int j = 0; j < (int)matches[i].size(); j++) {
			if(matches[i][j].distance < max_dist/2) {
				num++;
			}
		}
		nb_goodFeatures.push_back(num);
		indices.push_back(i);
	}
}

void view_vec(Vector<int> vec) {
	int i = 0;
	for(; i < (int)vec.size()-1; i++) {
		cout<<vec[i]<<", ";
	}
	cout<<vec[i]<<endl;
}

Mat mat2row(Mat des) {
	int h = des.rows;
	Mat myline = des.row(0);
	for(int i = 1; i < h; i++) {
		hconcat(myline, des.row(i), myline);
	}
	return myline;
}

Mat vecmats2mat(vector<Mat> vec_des, int nbd) {
	int nb_des = vec_des.size();
	int max_nbd = 0;
//  int min_nbd = 1000;
//	for(int i = 0; i < nb_des; i++) {
//		int nbd = vec_des[i].rows;
//		if(nbd > max_nbd) {
//			max_nbd = nbd;
//		}
//
//		if(nbd < min_nbd) {
//			min_nbd = nbd;
//		}
//	}

	max_nbd= nbd;

	int w = vec_des[0].cols;
	int l = max_nbd*w;

	Mat mat_des(nb_des, l, vec_des[0].type());

	for(int i = 0; i < nb_des; i++) {

		Mat m;
		int m_cols;
		if(vec_des[i].empty()) {
			m_cols = 0;
		}
		else {
			m = mat2row(vec_des[i]);
			m_cols = m.cols;
		}

		for(int j = 0; j < l; j++) {
			if(j < m_cols) {
				mat_des.at<float>(i, j) = m.at<float>(j);
			}
			else {
				mat_des.at<float>(i, j) = (float)0;
			}
		}

	}

	return mat_des;
}


int main() {

	/*---------------The params-------------------*/
	int minHessian = 400; // SURF param
	int nbFeatures = 500; // SIFT and HARRIS param
	int knn = 30; //
	double radius = 50; //
	string DES_TYPE = "SIFT";
	string IMG_TYPE = "jpg";
	string BASR_NAME = "COREL";
	bool SURF_DES_UPDATE = false;
	bool SIFT_DES_UPDATE = false;
	bool HARRIS_DES_UPDATE = false;


	///////////////////////////////////////////////////////////////
	string PATH_BASE_DIR = "D:\\ImagesData\\"+BASR_NAME+"\\"+IMG_TYPE+"\\";
	string RESULT_DIR = BASR_NAME+"\\"+IMG_TYPE+"\\";
	string LIST_FILE = "_liste_"+BASR_NAME;
	string IMG_DIR = PATH_BASE_DIR;
	string LIST_DIR = "D:\\ImagesData\\"+BASR_NAME+"\\"+LIST_FILE;


	/*----Save images in a list----*/
	vector<Mat> imgs;
	vector<string> names;
	cout<<"Save all images names in a list..."<<endl;
	save_imgsInList(LIST_DIR, IMG_DIR, imgs, names, IMG_TYPE);
	cout<<"OK"<<endl;


	/*----Save descriptors in a file xml----*/
	if(SURF_DES_UPDATE) {
		cout<<"Write SURF descriptors in a file xml"<<endl;
		write_descriptorsInFile(RESULT_DIR, "SURF", minHessian, nbFeatures, imgs, names);
	}
	if(SIFT_DES_UPDATE) {
		cout<<"Write SIFT descriptors in a file xml"<<endl;
		write_descriptorsInFile(RESULT_DIR, "SIFT", minHessian, nbFeatures, imgs, names);
	}
	if(HARRIS_DES_UPDATE) {
		cout<<"Write HARRIS descriptors in a file xml"<<endl;
		write_descriptorsInFile(RESULT_DIR, "HARRIS", minHessian, nbFeatures, imgs, names);
	}

	/*----Read descriptors----*/
	cout<<"Read "<<DES_TYPE<<" descriptors from the file xml..."<<endl;
	vector<Mat> descriptors;
	read_descriptorsOutFile(RESULT_DIR, DES_TYPE, descriptors, names);
	cout<<"OK"<<endl;

	/*----Test image request----*/
	int research = 0;
	while(research < 1) {

		string IMG_NAME;
		cout<<"Give the image query name : "<<endl;
		cin>>IMG_NAME;
		if(IMG_NAME == "z") {
			break;
		}
		string TEST_IMG_PATH = IMG_DIR+IMG_NAME+"."+IMG_TYPE;
		Mat test_img = imread(TEST_IMG_PATH, CV_LOAD_IMAGE_COLOR);
		if(!test_img.data) {

			cerr<<"The test image name error ! please enter again."<<endl;
			continue;
		}

		cout<<"Get image query descriptor : "<<TEST_IMG_PATH<<endl;
		Mat request;
		image_request(test_img, DES_TYPE, minHessian, nbFeatures, request);
		int nbd = request.rows;
		request = mat2row(request);
		cout<<"OK"<<endl;

		/*----Comparison to descriptors base----*/
		//FANNS : Fast Approximate Nearest Neighbor Search
		//http://docs.opencv.org/2.4/modules/flann/doc/flann_fast_approximate_nearest_neighbor_search.html#flann-index
		Mat des_mat = vecmats2mat(descriptors, nbd);
		cout<<des_mat.rows<<" "<<des_mat.cols<<endl;
		flann::Index FANNS(des_mat, flann::KDTreeIndexParams());
		Mat indices;
		Mat dists;
		//FANNS.knnSearch(request, indices, dists, knn);
		FANNS.radiusSearch(request, indices, dists, radius);

		cout<<"Mat indices = "<<indices<<endl;
		cout<<"Mat distances = "<<dists<<endl;

		/*-----------view the result-----------*/
		string path = IMG_DIR+names[indices.at<int>(0)]+"."+IMG_TYPE;
		cout<<path<<endl;
		Mat img = imread(path, CV_LOAD_IMAGE_COLOR);
		Size size(img.cols/4, img.rows/4);
		resize(img, img, size);
		Mat result(img.rows*(knn/5), img.cols*5, img.type());
		img.copyTo(result(Range(0, img.rows), Range(0, img.cols)));
		for(int i = 1; i < knn; i++) {
			path = IMG_DIR+names[indices.at<int>(i)]+"."+IMG_TYPE;
			cout<<path<<endl;
			img = imread(path, CV_LOAD_IMAGE_COLOR);
			resize(img, img, size);
			//putText(img, path, (0,0), FONT_HERSHEY_SIMPLEX, 4,(255,255,255), 2);
			img.copyTo(result(Range(img.rows*(i/5), img.rows*(i/5+1)), Range(img.cols*(i%5), img.cols*(i%5+1))));
		}
		imwrite(IMG_NAME+"_"+BASR_NAME+"_"+DES_TYPE+".jpg", result);
		research++;

	}

	cout << "Operations end !" << endl;
	return 0;
}
