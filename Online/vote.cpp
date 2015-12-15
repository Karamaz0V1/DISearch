#include <stdlib.h>
#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>
#include "find_img.h"


//Algorithme de vote
//renvoit un vecteur contenant le nom des images (classées de la plus ressemblante a la moins)
 
std::vector<std::string> vote(std::string file_desc,std::string file_img, std::vector<int> ind_desc, int nbImages)
{

	//nombre de descripteurs
	int nbDesc = ind_desc.size();
	
	// recuperer les noms des fichiers
	std::ifstream str1(file_desc.c_str());
	std::ifstream str2(file_img.c_str());

	// creer le vecteur contenant les votes
	std::vector<int> votes(nbImages);

	//on parcours tous les descripteurs retenus
	for(int i_desc=0 ; i_desc< nbDesc;i_desc++)
	{
		std::cout << "le descripteur " << ind_desc[i_desc] << std::endl;
		int i_image = idesc_to_iimg(str1,ind_desc[i_desc]);
		std::cout << "vote l'image " << i_image << std::endl;
		votes[i_image] ++ ;
		
		std::cout << "votes " << votes[0]<< votes[1]<< votes[2]<< votes[3]<< votes[4] << std::endl;
	}


	
	
	std::vector<std::string> v(5);
	return v;

}












int main(int argc,char* argv[] )
{ 
	std::string file_desc = "/private/student/8/58/14009558/ESIR3/Vo/moteur_de_recherche/DISearch/Online/tmp/test_file_desc.txt";
	std::string file_img = "/private/student/8/58/14009558/ESIR3/Vo/moteur_de_recherche/DISearch/Online/tmp/test_file_img.txt";
	
	
	std::vector<int> ind_desc(5);
	ind_desc[0]=1;
	ind_desc[1]=4;
	ind_desc[2]=6;
	ind_desc[3]=8;
	ind_desc[4]=5;
	int nbImages = 10;
	vote(file_desc,file_img,ind_desc,nbImages);
}
