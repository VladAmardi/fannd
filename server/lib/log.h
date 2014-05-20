//
//  log.h
//  fann_test
//
//  Created by Влад on 24.11.13.
//  Copyright (c) 2013 Влад. All rights reserved.
//

#ifndef __fann_test__log__
#define __fann_test__log__

#include <iostream>
#include "singleton.h"
#include <mutex>

class Log : public Singleton<Log> {
public:
    Log();
    static const unsigned int MSG = 0;
    static const unsigned int IMPORTANT = 1;
    void message(char *message);
    void message(const char *message);
    void message(const std::string& message);
    void message(float * array);
    void important(char *message);
    void important(const char *message);
    void important(const std::string& message);
    void set_level(unsigned int level);
protected:
    unsigned int level;
    std::mutex mtx;
    void write(const char * message, unsigned int level);
};

#endif /* defined(__fann_test__log__) */
