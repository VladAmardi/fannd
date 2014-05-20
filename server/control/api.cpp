//
//  api.cpp
//  fann_test
//
//  Created by Влад on 30.11.13.
//  Copyright (c) 2013 Влад. All rights reserved.
//

#include "api.h"

ApiControl::fann_query ApiControl::parseData(std::string data) {
    std::vector<std::string> request = helper::split(data, "#");
    std::vector<std::string> tmp;
    fann_query result;
    
    for(int i = 0; i < request.size(); i++) {
        tmp = helper::split(request[i], ",");
        
        //float * array = (float*) malloc(sizeof(float) * tmp.size());
        float * array = new float[tmp.size()]();
        for(int j = 0; j < tmp.size(); j++) {
            array[j] = ::atof(tmp[j].c_str());
        }
        
        result.push_back( std::make_pair(array, tmp.size()) );
    }
    
    return result;
}

void ApiControl::setAnn(ann * model) {
    this->ann_model = model;
}

int ApiControl::getArgSize(fann_query * query, int i) {
    if(query->size() > i) {
        return (*query)[i].second;
    }
    return 0;
}

std::string ApiControl::execute(std::string data) {
    std::string output = "";
    unsigned int result = RESULT_FAIL;
    int action_id = 0;
    // command, input data
    
    fann_query query = this->parseData(data);
    if(this->getArgSize(&query, 0) > 0) {
        action_id = query[0].first[0];
    }
    
    switch (action_id) {
        case ACTION_TRAIN:
            result = this->trainAction(query, &output);
            break;
        case ACTION_RUN:
            result = this->runAction(query, &output);
            break;
        case ACTION_TRAIN_DATA:
            result = RESULT_FAIL;
            output = "TODO: do it.";
            break;
        default:
            result = RESULT_FAIL;
            output = "Undefined action.";
            break;
    }
    
    for(int i = 0; i < query.size(); i++) {
        delete [] (query[i].first);
        //free(query[i]);
    }
    
    query.clear();
    
    return this->result(result, output);
}

unsigned int ApiControl::trainAction(fann_query query, std::string *output) {
    if(this->getArgSize(&query, 1) != this->ann_model->getNumInput()) {
        *output = "Incorrect input list";
        Log::instance().message(*output);
        return RESULT_FAIL;
    }
    if(this->getArgSize(&query, 2) != this->ann_model->getNumOutput()) {
        *output = "Incorrect output list";
        Log::instance().message(*output);
        return RESULT_FAIL;
    }
    this->ann_model->train(query[1].first, query[2].first);
    return RESULT_OK;
}

unsigned int ApiControl::runAction(fann_query query, std::string *output) {
    if(this->getArgSize(&query, 1) != this->ann_model->getNumInput()) {
        *output = "Incorrect input list";
        Log::instance().message(*output);
        return RESULT_FAIL;
    }
    float * out;
    if(!this->ann_model->run(query[1].first, &out)) {
        return false;
    }
    
    output->clear();
    for(int i = 0; i < this->ann_model->getNumOutput(); i++) {
        if(i > 0) {
            output->append(",");
        }
        output->append(std::to_string(out[i]));
    }
    
    return true;
}

std::string ApiControl::result(unsigned int status, std::string result) {
    return std::string(std::to_string(status)).append("#").append(result);
}

std::string ApiControl::result(unsigned int status) {
    if(status != RESULT_FAIL) {
        return this->result(status, "");
    }
    return this->result(status, this->ann_model->getErrorString());
}
