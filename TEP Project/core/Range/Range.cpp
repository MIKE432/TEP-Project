//
//  CRange.cpp
//  TEP Project
//
//  Created by Michał Raszczuk on 31/12/2019.
//  Copyright © 2019 Michał Raszczuk. All rights reserved.
//

#include "Range.h"
#include "Consts.h"

CRange::CRange()
: m_dMin(DEFAULT_MIN_RANGE_VALUE), m_dMax(DEFAULT_MAX_RANGE_VALUE) {
    
}

CRange::CRange(CDouble min, CDouble max)
: m_dMin(min), m_dMax(max) {
    
}

CRange::CRange(const CRange& otherCRange)
: m_dMin(otherCRange.m_dMin), m_dMax(otherCRange.m_dMax) {
    
}

CDouble& CRange::getMin() {

    return m_dMin;
}

CDouble& CRange::getMax() {

    return m_dMax;
}

void CRange::setMax(const CDouble& otherDouble) {
    
    m_dMax = otherDouble;
}

void CRange::setMin(const CDouble& otherDouble) {
    
    m_dMin = otherDouble;
}

CDouble CRange::operator [] (int minOrMax) {
    
    if(minOrMax > 0 && minOrMax <= 1 ) {
        return (minOrMax == 0 ? m_dMin : m_dMax);
    }
    
    return NULL;
}

CRange& CRange::operator = (const CRange& otherCRange) {
    m_dMin = otherCRange.m_dMin;
    m_dMax = otherCRange.m_dMax;
    
    return *this;
}





