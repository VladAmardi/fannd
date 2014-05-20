//
//  api.h
//  fann_test
//
//  Created by Влад on 30.11.13.
//  Copyright (c) 2013 Влад. All rights reserved.
//

#ifndef __fann_test__api__
#define __fann_test__api__

#include <iostream>
#include "../lib/control.h"
#include "../model/ann.h"
#include "../lib/helper.h"

class ApiControl : public Control<ApiControl> {
public:
    static const unsigned int RESULT_OK = 1;
    static const unsigned int RESULT_FAIL = 0;
    
    static const unsigned int ACTION_TRAIN = 1;
    static const unsigned int ACTION_TRAIN_DATA = 2;
    static const unsigned int ACTION_RUN = 3;
    
    typedef std::vector< std::pair<float *, int> > fann_query;
    
    std::string execute(std::string data);
    
    unsigned int trainAction(fann_query query, std::string *output);
    unsigned int runAction(fann_query query, std::string *output);
    
    void setAnn(ann * model);
protected:
    int getArgSize(fann_query * query, int i);
    ann * ann_model;
    std::string result(unsigned int status);
    std::string result(unsigned int status, std::string result);
    fann_query parseData(std::string data);
};


#endif /* defined(__fann_test__api__) */
