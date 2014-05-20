//
//  main.cpp
//  fann_test
//
//  Created by Влад on 24.11.13.
//  Copyright (c) 2013 Влад. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <vector>
#include "lib/simpleini/SimpleIni.h"
#include "model/ann.h"
#include "lib/log.h"
#include "lib/singleton.h"
#include <cstddef>

#include "control/cli.h"

void show_help() {
    printf("Usage:\n");
    printf("-h,--help - show help\n");
    printf("-v,--verbose - enable verbose mode\n");
    printf("-o,--open path\n");
    printf("-c,--create path,num_layers,num_input,num_neurons_hidden,num_output\n");
}

int main(int argc, char **argv)
{
    
    int ch, option_index = 0;
    bool action_selected = false;
    
    static struct option longopts[] = {
        // verbose options
        { "verbose", no_argument, NULL, 'v' },
        { "help",    no_argument, NULL, 'h' },
        
        // actions
        {"create",  required_argument, 0, 'c'},
        {"open",    required_argument, 0, 'o'},
        
        {0, 0, 0, 0}
    };
    
    while ((ch = getopt_long(argc, argv, "hvo:c:", longopts, &option_index)) != -1) {
        switch (ch) {
            case 'h':
                show_help();
                return 0;
                break;
            case 'v':
                Log::instance().set_level(Log::MSG);
                break;
            case 'c':
                action_selected = true;
                Log::instance().message("Create action");
                CliControl::instance().CreateAction(optarg);
                break;
            case 'o':
                action_selected = true;
                Log::instance().important("Open");
                CliControl::instance().OpenAction(optarg);
                printf("%s", optarg);
                break;
        }
    }
    
    if(!action_selected) {
        show_help();
        return 1;
    }
    
    Log::instance().message("OK: That all.");
    return 0;
}
