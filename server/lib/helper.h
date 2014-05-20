//
//  helper.h
//  fann_test
//
//  Created by Влад on 28.11.13.
//  Copyright (c) 2013 Влад. All rights reserved.
//

#ifndef __fann_test__helper__
#define __fann_test__helper__

#include <iostream>
#include <vector>

class helper {
public:
    static std::vector<std::string> split(std::string str,std::string sep);
    static std::vector<std::string> split(char * str, char * sep);
    static std::vector<std::string> split(char * str, const char * sep);
};

#endif /* defined(__fann_test__helper__) */
