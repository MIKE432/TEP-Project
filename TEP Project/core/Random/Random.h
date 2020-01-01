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
    std::random_device m_rd;
    std::default_random_engine m_dre;
    
public:
    CRandom();
    CRandom(int seed);
    double nextNumber();
    double nextNumber(double leftEdge, double rightEdge);
    void setSeed(int seed);
    void deleteSeed();
};

#endif /* Random_h */
