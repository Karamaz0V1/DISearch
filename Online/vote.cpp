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
//renvoit un vecteur contenant le nom des images (classées de la plus ressemblante a la moins, celles qui n'ont eu aucun vote ne sont pas ajoutées)
 
std::vector<std::string> vote(std::string file_desc,std::string file_img, std::vector<int> ind_desc, int nbImages)
{
	////////////////////////////////////////////
	// CALCUL DES VOTES 
	////////////////////////////////////////////

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
		int i_image = idesc_to_iimg(str1,ind_desc[i_desc]);
		votes[i_image] ++ ;
	}


	////////////////////////////////////////////
	// Le vecteur de votes est complet /////////
	////////////////////////////////////////////

	////////////////////////////////////////////
	// CLASSEMENT DES IMAGES
	////////////////////////////////////////////

	std::vector<std::string> classement ;
	
	int max = 0;
	int i_max =0;
	
	//calcul de la norme
	double norme = 0;
	for(int i=0;i<votes.size();i++)
	{
		norme += votes[i]*votes[i];
	}
	norme = sqrt(norme);
	
	while(norme > 0)
	{
	
		for(int i=0;i<votes.size();i++)
		{
			//parcours du vecteur pour trouver l'indice de valeur maximale
			if(votes[i] > max)
			{
				i_max = i;
				max = votes[i];
			}
		}
	
		if(max != 0)
		{
		std::string img_name = iimg_to_imgname(str2,i_max);
		
		classement.push_back(img_name);
		votes[i_max] = 0;
		i_max = 0;
		max = 0;
	
	  norme = 0;
		for(int i=0;i<votes.size();i++)
		{
			norme += votes[i]*votes[i];
		}
		norme = sqrt(norme);
	
	
		}
		else{break;}
	
	
	}
	
	if(classement.size() == 0)
	{std::cout << "pas d'image trouvée" << std::endl;}
	else
	{
		std::cout << "classement " << std::endl ;
		for(int i=0;i<classement.size();i++)
		{std::cout << classement[i] << std::endl;}
	}
	

	return classement;

}












int main(int argc,char* argv[] )
{ 
	std::string file_desc = "/private/student/8/58/14009558/ESIR3/Vo/moteur_de_recherche/DISearch/Online/tmp/test_file_desc.txt";
	std::string file_img = "/private/student/8/58/14009558/ESIR3/Vo/moteur_de_recherche/DISearch/Online/tmp/test_file_img.txt";
	
	
	std::vector<int> ind_desc(10);
	ind_desc[0]=0;
	ind_desc[1]=1;
	ind_desc[2]=2;
	ind_desc[3]=3;
	ind_desc[4]=4;
	ind_desc[5]=5;
	ind_desc[6]=6;
	ind_desc[7]=7;
	ind_desc[8]=8;
	ind_desc[9]=9;
	int nbImages = 10;
	vote(file_desc,file_img,ind_desc,nbImages);
}
