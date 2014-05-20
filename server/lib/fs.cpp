//
//  fs.cpp
//  fann_test
//
//  Created by Влад on 28.11.13.
//  Copyright (c) 2013 Влад. All rights reserved.
//

#include "fs.h"
#include <dirent.h>

bool FS::isDir(const std::string& pathname) {
	struct stat st;
	if (::stat(pathname.c_str(), &st) == -1) {
		return false;
    }
	return S_ISDIR(st.st_mode);
}

bool FS::access(const std::string &s, int m) {
	return ::access(s.c_str(), m) == 0;
}

bool FS::exists(const std::string& file) {
    return FS::access(file, F_OK);
}

bool FS::mkdir(const std::string& pathname) {
    if (::mkdir(pathname.c_str(),0755) == -1) {
        return false;
    }
    
    return true;
}
