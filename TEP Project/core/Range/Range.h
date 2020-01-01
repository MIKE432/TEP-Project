//
//  CRange.hpp
//  TEP Project
//
//  Created by Michał Raszczuk on 31/12/2019.
//  Copyright © 2019 Michał Raszczuk. All rights reserved.
//

#ifndef CRange_h
#define CRange_h

#include <stdio.h>

#include "Random.h"
#include "Double.h"

class CRange {
private:
    CDouble m_dMin;
    CDouble m_dMax;
    
public:
    CRange();
    CRange(CDouble min, CDouble max);
    CRange(const CRange& otherCRange);
    
    CDouble& getMin();
    CDouble& getMax();
    void setMax(const CDouble& otherDouble);
    void setMin(const CDouble& otherDouble);
    
    CDouble operator [] (int minOrMax);
    CRange& operator = (const CRange& otherCRange);
    
    bool random(CRandom& random);
};

#endif /* CRange_hpp */
