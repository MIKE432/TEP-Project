//
//  Double.cpp
//  TEP Project
//
//  Created by Michał Raszczuk on 01/01/2020.
//  Copyright © 2020 Michał Raszczuk. All rights reserved.
//

#include "Double.h"
#include "Consts.h"

CDouble::CDouble()
: m_dValue(DEFAULT_DOUBLE_NUMBER) {
    
}

CDouble::CDouble(double num)
: m_dValue(num) {
    
}

CDouble::CDouble(const CDouble& otherDouble)
: m_dValue(otherDouble.m_dValue) {
    
}

void CDouble::Set(double num) {
    
    m_dValue = num;
}

double CDouble::Get() {
    
    return m_dValue;
}

bool CDouble::Randomize(CRandom &random) {
    
    random >> m_dValue;

    return true;
}

//---operators---

CDouble& CDouble::operator = (const CDouble& otherDouble) {
    
    m_dValue = otherDouble.m_dValue;
    
    return *this;
}

CDouble CDouble::operator + (const CDouble& otherDouble) {
    
    return CDouble(m_dValue + otherDouble.m_dValue);
}

CDouble CDouble::operator - (const CDouble& otherDouble) {
    
    return CDouble(m_dValue - otherDouble.m_dValue);
}

CDouble& CDouble::operator += (const CDouble& otherDouble) {
    
    m_dValue += otherDouble.m_dValue;
    
    return *this;
}

CDouble CDouble::operator * (const CDouble& otherDouble) {
    
    return CDouble(m_dValue * otherDouble.m_dValue);
}

CDouble CDouble::operator / (const CDouble& otherDouble) {
    
    return CDouble(m_dValue / otherDouble.m_dValue);
}

bool CDouble::operator < (const CDouble& otherDouble) {
    
    return m_dValue < otherDouble.m_dValue;
}

bool CDouble::operator < (double double1) {
    
    return m_dValue < double1;
}

bool CDouble::operator > (const CDouble& otherDouble) {
    
    return m_dValue > otherDouble.m_dValue;
}

bool CDouble::operator > (double double1) {
    
    return m_dValue > double1;
}

CDouble& CDouble::operator = (double double1) {
    
    m_dValue = double1;
    return *this;
}

bool CDouble::operator == (const CDouble& otherDouble) {
    
       return m_dValue == otherDouble.m_dValue;
}

bool CDouble::operator == (double double1) {
    
       return m_dValue == double1;
}

bool CDouble::operator != (const CDouble& otherDouble) {
    
    return m_dValue != otherDouble.m_dValue;
}

bool CDouble::operator != (double double1) {
    
    return m_dValue != double1;
}

void CDouble::Store(CArchive& archive) {
    
    archive << m_dValue;
}

void CDouble::Load(CArchive& archive) {

    archive >> m_dValue;
}
