/***************************************************************************
 *
 * TODO: Project Title
 *
 * Author: Florent Guiotte <guiotte.florent@gmail.com>
 *
 **************************************************************************/

#ifndef __UTILS_H__
#define __UTILS_H__
#include <vector>
#include <string>

std::vector<std::string> listDir(const std::string & url = "./");
bool isExt(const std::string & url, const std::string & ext);


#endif /* __UTILS_H__ */



