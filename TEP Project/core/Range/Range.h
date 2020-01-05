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

class CRandom;

class CRange {
private:
    CDouble m_dMin;
    CDouble m_dMax;
    
public:
    CRange();
    CRange(CDouble min, CDouble max);
    CRange(const CRange& otherCRange);
    
    CDouble& GetMin();
    CDouble& GetMax();
    void SetMax(const CDouble& otherDouble);
    void SetMin(const CDouble& otherDouble);
    
    void Store(CArchive& archive);
    void Load(CArchive& archive);
    
    CDouble operator [] (int minOrMax);
    CRange& operator = (const CRange& otherCRange);
    
    bool Randomize(CRandom& random);
    string ToString();
};

inline CArchive& operator >> (CArchive& archive, CRange& range) {
    
    range.Load(archive);
    return archive;
}

inline CArchive& operator << (CArchive& archive, CRange& range) {
    
    range.Store(archive);
    return archive;
}

#endif /* CRange_hpp */
