/***************************************************************************
 *
 * TODO: Project Title
 *
 * Author: Florent Guiotte <guiotte.florent@gmail.com>
 *
 **************************************************************************/

#include "utils.h"
#include <dirent.h>
#include <iostream>
#include <stdlib.h>
using namespace std;

vector<string> listDir(const string & url) {
    vector<string> list;
    DIR * dir;
    struct dirent * ent;
    if ((dir = opendir(url.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            list.push_back(ent->d_name);
        }
        closedir (dir);
    } else {
        cerr << "ERROR: Could not open directory " << url << endl;
        exit(EXIT_FAILURE);
    }
    return list;
}

bool isExt(const string & url, const string & ext) {
    return url.substr(url.find_last_of(".") + 1) == ext;
}
