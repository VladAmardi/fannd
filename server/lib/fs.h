//
//  fs.h
//  fann_test
//
//  Created by Влад on 28.11.13.
//  Copyright (c) 2013 Влад. All rights reserved.
//

#ifndef __fann_test__fs__
#define __fann_test__fs__

#include <iostream>
#include <fstream>
#include <dirent.h>
#include <libgen.h>
#include <sys/stat.h>
#include <unistd.h>

class FS {
public:
    static bool isDir(const std::string& pathname);
    static bool access(const std::string &s, int m);
    static bool exists(const std::string& file);
    static bool mkdir(const std::string& pathname);
};

#endif /* defined(__fann_test__fs__) */
