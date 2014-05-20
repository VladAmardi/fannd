//
//  cli.cpp
//  fann_test
//
//  Created by Влад on 30.11.13.
//  Copyright (c) 2013 Влад. All rights reserved.
//

#include "cli.h"

ann * CliControl::getAnnModel() {
    return &ann_model;
}

void CliControl::saverThread() {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    if(CliControl::instance().getAnnModel()->hasChanges()) {
        Log::instance().message("Has changes, saving...");
        if(CliControl::instance().getAnnModel()->save()) {
            Log::instance().message("Saved");
        } else {
            Log::instance().message("Error saving");
        }
    }
    CliControl::saverThread();
}

void CliControl::listenerThread() {
    ann * ann_model = CliControl::instance().getAnnModel();
    Log::instance().message(std::string("inputs:").append(std::to_string(ann_model->getNumInput())));
    Log::instance().message(std::string("outputs:").append(std::to_string(ann_model->getNumOutput())));
    
    ApiControl::instance().setAnn(ann_model);
    
    int sockfd, newsockfd;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    std::string client_data;
    
    bzero(buffer,sizeof(buffer));
    
    /* First call to socket() function */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        Log::instance().important("ERROR opening socket");
        return;
    }
    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(ann_model->getHost().c_str());
    serv_addr.sin_port = htons(ann_model->getPort());
    
    /* Now bind the host address using bind() call.*/
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        Log::instance().important("ERROR on binding");
        return;
    }
    
    /* Now start listening for the clients, here
     * process will go in sleep mode and will wait
     * for the incoming connection
     */
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    while (1) {
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        Log::instance().message("Client was accepted.");
        while (read(newsockfd, buffer, sizeof(buffer))) {
            client_data.append(buffer);
            bzero(buffer,sizeof(buffer));
            if( ((int) client_data.find_last_of("\n")) != -1 ) {
                break;
            }
        }
        
        Log::instance().message("Received message, processing...");
        std::string reply = ApiControl::instance().execute(client_data);
        Log::instance().message("Done, sending reply...");
        write(newsockfd, reply.c_str(), reply.length());
        close(newsockfd);
        Log::instance().message("Client was disconnected.");
        client_data.clear();
    }
}

bool CliControl::OpenAction(char *data) {
    ann_model.load(data);
    std::thread saver(CliControl::saverThread);
    std::thread listener(CliControl::listenerThread);
    saver.join();
    listener.join();
    return true;
}

bool CliControl::CreateAction(char *data) {
    std::vector<std::string> params = helper::split(data, ",");
    //path,num_layers,num_input,num_neurons_hidden,num_output
    
    unsigned int num_layers = atoi(params[1].c_str());
    unsigned int num_input = atoi(params[2].c_str());
    unsigned int num_neurons_hidden = atoi(params[3].c_str());
    unsigned int num_output = atoi(params[4].c_str());
    
    Log::instance().message(std::string("path:").append(params[0]));
    Log::instance().message(std::string("num_layers:").append(std::to_string(num_layers)));
    Log::instance().message(std::string("num_input:").append(std::to_string(num_input)));
    Log::instance().message(std::string("num_neurons_hidden:").append(std::to_string(num_neurons_hidden)));
    Log::instance().message(std::string("num_output:").append(std::to_string(num_output)));
    
    if(!num_layers || !num_layers || !num_neurons_hidden || !num_output) {
        Log::instance().important("Numeric params of ANN need positive values.");
        return false;
    }
    
    ann ann_model;
    char *path = new char[params[0].length() + 1];
    strcpy(path, params[0].c_str());
    bool result = ann_model.create(path,num_layers,num_input,num_neurons_hidden,num_output);
    delete [] path;
    
    if(result) {
        Log::instance().important("OK");
    } else {
        Log::instance().important("Fail");
    }
    
    return result;
}

