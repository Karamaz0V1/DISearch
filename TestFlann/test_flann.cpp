#include "opencv2/opencv.hpp"
#include "opencv2/opencv_modules.hpp"
#include "opencv2/core/core.hpp"
#include <iostream>
#include "opencv2/flann/flann.hpp"

using namespace cv;

int main()
{
  int dim = 5; //cols
  int card = 5;//rows
  cv::Mat descripteurs(card,dim,CV_32F);
  for(int i=0; i<card; i++) {
  	for(int j=0;j<dim;j++) {
  		descripteurs.at<float>(i,j) = i*j;
  	}
  }
  
  std::cout<<descripteurs <<std::endl;
 
  cv::flann::Index flann_index(descripteurs,cv::flann::KDTreeIndexParams(4));
  flann_index.save("myFirstIndex");
  cv::flann::Index flann;
  flann.load(descripteurs,"myFirstIndex");
  flann.save("mySecondIndex");
  

  cv::Mat query(1,5,CV_32F);
  query.at<float>(0)=0;
  query.at<float>(1)=0;
  query.at<float>(2)=1;
  query.at<float>(3)=0;
  query.at<float>(4)=4;
  
  int knn = 3;
  
  std::vector<int> indices(knn);
  std::vector<float> dists(knn);
  flann_index.knnSearch(query, indices, dists, knn);
  
  std::cout<<indices.at(0)<<std::endl;
  std::cout<<indices.at(1)<<std::endl;
  std::cout<<indices.at(2)<<std::endl;
  
  for(int k=0; k<dim; k++) {
  	std::cout<<'\t'<<descripteurs.at<float>(k,indices.at(0))<<'\t';
  }
  std::cout<<std::endl;

  return 0;
}
