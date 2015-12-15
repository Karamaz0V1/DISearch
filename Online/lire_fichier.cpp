#include <stdlib.h>
#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>

// Fonction pour lire les descripteurs et les images et les stocker dans une matrice
/*

	filename : nom du fichier a lire
	nbDesc   : nombre de descripteurs (lignes) dans le fichier
	dim 		 : taille d'un descripteur
	
*/
cv::Mat readFileToMatrix(std::istream& filename, int nbDesc, int dim)
{
		cv::Mat m(nbDesc,dim,CV_64F);
		
		for(int i_ligne=0;i_ligne<nbDesc;i_ligne++)
		{
		  std::vector<std::string>   result;
		  std::string                line;
		  
		  
			//lire une ligne
		  std::getline(filename,line);
				
			//extraire dans le vecteur result les 2 composantes [id_img,descripteur]
		  std::stringstream          lineStream(line);
		  std::string                ligne;

		  while(std::getline(lineStream,ligne,';'))
		  {
		      result.push_back(ligne);
		  }
		  
		  //récuperer les composantes du descripteur dans un vecteur 
		  std::stringstream descString(result[1]); 

			int d =0;
			std::vector<double> vec(dim) ;
			std::string         comp;

			while(std::getline(descString,comp,' ' ))
			{
					if(d<dim)
					{
						const char * comp_ = comp.c_str();	  		
					  vec[d] = atoi(comp_); 
						d++;
					}
					else{break;}  
			}

			//ajouter le descripteur à la matrice
			for(int i =0;i<dim;i++)
			{
				m.at<double>(i_ligne,i) = vec[i]; 
			}
		}		
		
    return m;
}
/*
int main(int argc,char* argv[] )
{ 
	std::ifstream str("/private/student/8/58/14009558/ESIR3/Vo/moteur_de_recherche/DISearch/Online/tmp/test_file.txt");
	cv::Mat m = readFileToMatrix(str,8,4);
	std::cout << "mat " << m << std::endl;
}
*/


