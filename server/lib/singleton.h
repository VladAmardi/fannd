//
//  singleton.h
//  fann_test
//
//  Created by Влад on 27.11.13.
//  Copyright (c) 2013 Влад. All rights reserved.
//

#ifndef __fann_test__singleton__
#define __fann_test__singleton__

#include <iostream>

template< bool val, class TrueT, class FlaseT >
struct If {
    typedef TrueT type;
};
template< class TrueT, class FalseT >
struct If< false, TrueT, FalseT > {
    typedef FalseT type;
};
template< class DerivedT = void >
class Singleton {
public:
    typedef typename If<std::is_same<DerivedT, void>::value,
    Singleton<DerivedT>, DerivedT>::type this_type;
    static this_type& instance() {
        static this_type me;
        return me;
    }
};

#endif /* defined(__fann_test__singleton__) */
