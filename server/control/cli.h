//
//  cli.h
//  fann_test
//
//  Created by Влад on 30.11.13.
//  Copyright (c) 2013 Влад. All rights reserved.
//

#ifndef __fann_test__cli__
#define __fann_test__cli__

#include <iostream>
#include "../lib/control.h"
#include "../lib/helper.h"
#include "../lib/log.h"
#include "../model/ann.h"
#include "api.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>
#include <chrono>

class CliControl : public Control<CliControl> {
public:
    bool OpenAction(char *data);
    bool CreateAction(char *data);
    ann * getAnnModel();
    static void saverThread();
    static void listenerThread();
protected:
    ann ann_model;
};

#endif /* defined(__fann_test__cli__) */
