/***************************************************************************
 *
 * TODO: Project Title
 *
 * Author: Florent Guiotte <guiotte.florent@gmail.com>
 *
 **************************************************************************/

#include <iostream>
#include "DIIndex.h"

using namespace std;
using namespace cv;

int main( int argc, char* argv[] )
{
    DIIndex di;
    // TODO: test nb args, disp usage
    di.loadDB(argv[1]);
    di.indexDB();
    di.writeDB();
    cout << argv[1] << endl;

    cout << "Offline search" << endl;
    return 0;
}


