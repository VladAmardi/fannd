//
//  ann.cpp
//  fann_test
//
//  Created by Влад on 24.11.13.
//  Copyright (c) 2013 Влад. All rights reserved.
//

#include "ann.h"
#include "../lib/log.h"

ann::ann() {
    this->port = 9100;
    this->host = "127.0.0.1";
    this->error_id = 0;
    this->changed = false;
}

ann::~ann() {
    
}

void ann::parse_path(char * data_path) {
    this->path = std::string(::dirname(data_path));
    this->dirname = std::string(::basename(data_path));
    this->full_path.append(this->path.c_str()).append("/").append(this->dirname.c_str());
    this->ini_file.append(this->full_path.c_str()).append("/config.ini");
    this->ann_file.append(full_path.c_str()).append("/ann.dat");
}

bool ann::create(char * data_path, unsigned int num_layers, unsigned int num_input, unsigned int num_neurons_hidden, unsigned int num_output) {
    this->parse_path(data_path);
    
    Log::instance().message(std::string("Checking parent:").append(this->path));
    if(!FS::isDir(this->path)) {
        std::string message = "Path ";
        message.append(this->path);
        message.append(" is not exist.\n");
        Log::instance().important(message);
        return false;
    }
    
    Log::instance().message(std::string("Checking object:").append(this->full_path));
    if(FS::exists(this->full_path)) {
        std::string message = "Object ";
        message.append(this->full_path);
        message.append(" is now exist.\n");
        Log::instance().important(message);
        return false;
    }
    
    Log::instance().message("Creating dir...");
    if(!FS::mkdir(this->full_path)) {
        Log::instance().important(std::string("Creating dir failed:").append(this->full_path));
        return false;
    }
    Log::instance().message("Dir created.");
    
    Log::instance().message("Creating config.ini...");
    CSimpleIniA ini;
    ini.SetValue("Server", "Host", this->host.c_str());
    ini.SetValue("Server", "Port", std::to_string(this->port).c_str());
    if(ini.SaveFile(this->ini_file.c_str()) != SI_OK) {
        Log::instance().important("Error creating config.ini!");
        return false;
    }
    Log::instance().message("config.ini created");
    
    Log::instance().message("Creating ann.dat...");
    struct fann *ann = fann_create_standard(num_layers, num_input, num_neurons_hidden, num_output);
    if(fann_save(ann, this->ann_file.c_str()) == -1) {
        Log::instance().important("Error creating ann.dat!");
        return false;
    }
    Log::instance().message("ann.dat created");
    
    return true;
}

bool ann::save() {
    bool result = false;
    this->mtx.lock();
    if(fann_save(this->ann_object, this->ann_file.c_str()) == 0) {
        result = true;
        this->changed = false;
    }
    this->mtx.unlock();
    return result;
}

bool ann::load(char *data_path) {
    this->parse_path(data_path);
    
    Log::instance().message("Reading config.ini...");
    CSimpleIniA ini;
    if(ini.LoadFile(this->ini_file.c_str()) != SI_OK) {
        Log::instance().important("Error loading config.ini!");
        return false;
    }
    this->host = ini.GetValue("Server", "Host");
    this->port = atoi(ini.GetValue("Server", "Port"));
    Log::instance().message(std::string("Host:").append(host));
    Log::instance().message(std::string("Port:").append(std::to_string(port)));
    
    Log::instance().message("Loading ann...");
    this->ann_object = fann_create_from_file(this->ann_file.c_str());
    
    fann_set_activation_function_hidden(this->ann_object, FANN_SIGMOID_SYMMETRIC);
    fann_set_activation_function_output(this->ann_object, FANN_SIGMOID_SYMMETRIC);
    
    Log::instance().message("Ann loaded.");
    
    return true;
}

int ann::getPort() {
    return this->port;
}

std::string ann::getHost() {
    return this->host;
}

bool ann::train(float * input, float * output) {
    this->mtx.lock();
    fann_train(this->ann_object, input, output);
    this->changed = true;
    return this->ann_result();
}

std::string ann::getErrorString() {
    return this->error_str;
}

bool ann::trainOnData() {
    //struct fann_train_data *data = fann_create_train(4, this->ann_object->num_input, this->ann_object->num_output);
    
    
    
    //fann_train_on_data(this->ann_object, <#struct fann_train_data *data#>, <#unsigned int max_epochs#>, <#unsigned int epochs_between_reports#>, <#float desired_error#>)
    return true;
}

bool ann::run(float * input, float ** output) {
    this->mtx.lock();
    (*output) = fann_run(this->ann_object, input);
    return this->ann_result();
}

int ann::getErrorId() {
    return this->error_id;
}

bool ann::ann_result() {
    bool result = true;
    this->error_id = fann_get_errno((struct fann_error *) (this->ann_object));
    if(this->error_id != FANN_E_NO_ERROR) {
        this->error_str = fann_get_errstr((struct fann_error *) (this->ann_object));
        result = false;
    }
    this->mtx.unlock();
    return result;
}

int ann::getNumOutput() {
    return this->ann_object->num_output;
}

int ann::getNumInput() {
    return this->ann_object->num_input;
}

bool ann::hasChanges() {
    return this->changed;
}
