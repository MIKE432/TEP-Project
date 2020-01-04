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

CDouble& CRange::GetMin() {

    return m_dMin;
}

CDouble& CRange::GetMax() {

    return m_dMax;
}

void CRange::SetMax(const CDouble& otherDouble) {
    
    m_dMax = otherDouble;
}

void CRange::SetMin(const CDouble& otherDouble) {
    
    m_dMin = otherDouble;
}

bool CRange::Randomize(CRandom &random) {
    
    double d1 = random.Generate();
    double d2 = random.Generate();
    
    if(d1 > d2) {
        m_dMax = d1;
        m_dMin = d2;
    } else {
        m_dMax = d2;
        m_dMin = d1;
    }
    
    return true;
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

void CRange::Store(CArchive& archive) {
    
    m_dMin.Store(archive);
    archive<<space_w;
    m_dMax.Store(archive);
}

void CRange::Load(CArchive& archive) {
    
    m_dMin.Load(archive);
    archive>>space_r;
    m_dMax.Load(archive);
}




