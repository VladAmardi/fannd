//
//  log.cpp
//  fann_test
//
//  Created by Влад on 24.11.13.
//  Copyright (c) 2013 Влад. All rights reserved.
//

#include "log.h"

void Log::write(const char * message, unsigned int level) {
    if(level >= this->level) {
        this->mtx.lock();
        printf("%s\n", message);
        this->mtx.unlock();
    }
}

void Log::message(char *message) {
    this->write( (const char*) message, MSG);
}

void Log::message(const char *message) {
    this->write(message, MSG);
}

void Log::message(const std::string& message) {
    this->write(message.c_str(), MSG);
}

void Log::important(char *message) {
    this->write( (const char*) message, IMPORTANT);
}

void Log::important(const char *message) {
    this->write(message, IMPORTANT);
}

void Log::important(const std::string& message) {
    this->write(message.c_str(), IMPORTANT);
}

void Log::set_level(unsigned int level) {
    this->level = level;
}

void Log::message(float * array) {
    std::string msg;
    for(int i = 0; i < (sizeof(array) / sizeof(float)); i ++) {
        if(i > 0) {
            msg.append(",");
        }
        msg.append(std::to_string(array[i]));
    }
    this->message(msg);
}

Log::Log() {
    this->level = 1;
}

