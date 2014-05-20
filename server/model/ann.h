//
//  ann.h
//  fann_test
//
//  Created by Влад on 24.11.13.
//  Copyright (c) 2013 Влад. All rights reserved.
//

#ifndef __fann_test__ann__
#define __fann_test__ann__

#include <iostream>
#include <fann.h>
#include <mutex>
#include "../lib/fs.h"
#include "../lib/log.h"
#include "../lib/simpleini/SimpleIni.h"

class ann {
public:
    ann();
    ~ann();
    bool create(char * data_path, unsigned int num_layers, unsigned int num_input, unsigned int num_neurons_hidden, unsigned int num_output);
    bool load(char * data_path);
    bool save();
    int getPort();
    std::string getHost();
    
    bool train(float * input, float * output);
    bool trainOnData();
    bool run(float * input, float ** output);
    
    int getErrorId();
    std::string getErrorString();
    
    int getNumOutput();
    int getNumInput();
    
    bool hasChanges();
    
protected:
    std::mutex mtx;
    std::string path;
    std::string dirname;
    std::string full_path;
    std::string ini_file;
    std::string ann_file;
    int port;
    std::string host;
    
    struct fann *ann_object;
    void parse_path(char * data_path);
    int error_id;
    std::string error_str;
    bool ann_result();
    bool changed;
};

#endif /* defined(__fann_test__ann__) */
