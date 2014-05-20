//
//  helper.cpp
//  fann_test
//
//  Created by Влад on 28.11.13.
//  Copyright (c) 2013 Влад. All rights reserved.
//

#include "helper.h"

std::vector<std::string> helper::split(std::string str,std::string sep){
    char* cstr=const_cast<char*>(str.c_str());
    std::vector<std::string> arr;
    
    char* current;
    current=strtok(cstr,sep.c_str());
    while(current!=NULL){
        arr.push_back(std::string(current));
        current=strtok(NULL,sep.c_str());
    }
    
    delete [] current;
    
    return arr;
}

std::vector<std::string> helper::split(char * str, char * sep) {
    return helper::split(std::string(str), std::string(sep));
}

std::vector<std::string> helper::split(char * str, const char * sep) {
    return helper::split(std::string(str), std::string(sep));
}