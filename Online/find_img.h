#ifndef FIND_IMG_INCLUDED
#define FIND_IMG_INCLUDED


#include <stdlib.h>
#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>



// Fonction qui trouve l'image associée à un descripteur a partir de 
/*
	
	le fichier des descripteurs
	le fichier des images
	l'indice du descripteur dans la matrice (= indice dans le fichier)

*/

int idesc_to_iimg(std::istream & file_desc,int i_desc);
  
std::string iimg_to_imgname(std::istream & file_img,int i_image);


#endif

