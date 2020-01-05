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

class CRange;

class CRandom {
private:
    std::random_device m_rd;
    std::default_random_engine m_dre;
    std::uniform_real_distribution<double> m_dist;
    
    double m_dFrom;
    double m_dTo;
    
public:
    CRandom();
    CRandom(int seed);
    
    void SetRange(std::uniform_real_distribution<double>& dist);
    
    //CRandom& SetRange(CRange& range);
    CRandom& SetRange(double dFrom, double dTo );
    double Generate();

    CRandom& operator >> (double& dValue);
};

inline std::uniform_real_distribution<double> SetRange( double dFrom, double dTo) {
    
    return std::uniform_real_distribution<double>(dFrom, dTo);
}

inline CRandom& operator >> (CRandom& random, std::uniform_real_distribution<double> dist ) {
    
    random.SetRange( dist );
    return random;
}
// random >> SetRange( 0.0, 1000.0 ) >> m

#endif /* Random_h */
