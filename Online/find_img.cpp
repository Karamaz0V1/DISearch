

#include <stdlib.h>
#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>
#include "find_img.h"



// Fonction qui trouve l'image associée à un descripteur a partir de 
/*
	
	le fichier des descripteurs
	le fichier des images
	l'indice du descripteur dans la matrice (= indice dans le fichier)

*/

int idesc_to_iimg(std::istream & file_desc,int i_desc)
{
			///////////////////////////////////////////////////////////
			//RECHERCHE DE L'INDICE DE L'IMAGE ASSOCIEE AU DESCRIPTEUR
			//////////////////////////////////////////////////////////

		  std::vector<std::string>   result;
		  std::string                line;
		  int i=0;
		  bool next = false ;
		  while(!next)
		  {
				if(i <= i_desc)
				{
					//lire une ligne
					std::getline(file_desc,line);
					i++;
				}
				else{next = true;}
			}
			

			//extraire dans le vecteur result les 2 composantes [id_img,descripteur]
		  std::stringstream          lineStream(line);
		  std::string                ligne;

		  while(std::getline(lineStream,ligne,';'))
		  {
		      result.push_back(ligne);
		  }
		  
			const char * i_image_ = result[0].c_str();	  		
		  int i_image = atoi(i_image_); 	
		  
			/////////////////////////////
		  // INDICE DE L'IMAGE RECUPERE
			/////////////////////////////
			file_desc.clear();
			file_desc.seekg(0,std::ios::beg);
		  return i_image ;
		  
}		  
		  
std::string iimg_to_imgname(std::istream & file_img,int i_image)
{		//////////////////////////////////////
		  //RECHERCHE DU NOM DE L'IMAGE ASSOCIEE
			//////////////////////////////////////

		 	std::string l;

			//lire la ligne correspondant à l'image cherchée
  		int i=0;
		  bool next = false ;
		  while(!next)
		  {
				if(i <= i_image)
				{
					std::getline(file_img,l);
					i++;
				}
				else{next = true;}
			}				
			file_img.clear();
			file_img.seekg(0,std::ios::beg);
			return l;

}
/*
int main(int argc,char* argv[] )
{ 
	std::istream str1("/private/student/8/58/14009558/ESIR3/Vo/moteur_de_recherche/DISearch/Online/tmp/test_file_desc.txt");
	std::istream str2("/private/student/8/58/14009558/ESIR3/Vo/moteur_de_recherche/DISearch/Online/tmp/test_file_img.txt");
	int i_image = idesc_to_iimg(str1,4);
	std::cout << "id image " << i_image << std::endl;
	std::string s = iimg_to_imgname(str2,i_image);
	std::cout << "nom de l'image " << s << std::endl;
}*/


