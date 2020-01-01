//
//  Random.h
//  TEP Project
//
//  Created by Michał Raszczuk on 31/12/2019.
//  Copyright © 2019 Michał Raszczuk. All rights reserved.
//

#ifndef Random_h
#define Random_h

#include <random>

class CRandom {
private:
    int m_seed;
    double m_dFrom;
    double m_dTo;
    std::random_device m_rd;
    std::default_random_engine m_dre;
    
public:
    CRandom();
    CRandom(int seed);
    
    CRandom& SetRange(double dFrom, double dTo );
    double Generate();
};

#endif /* Random_h */
