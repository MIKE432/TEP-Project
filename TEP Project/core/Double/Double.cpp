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

void CDouble::set(double num) {
    
    m_dValue = num;
}

double CDouble::get() const {
    
    return m_dValue;
}

//---operators---

CDouble& CDouble::operator = (const CDouble& otherDouble) {
    
    m_dValue = otherDouble.get();
    
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

bool CDouble::Parse(string s, string::size_type* pRead) {
    
    if(s == "")
        return false;
    
    string::size_type sz;
    m_dValue = stod(s, &sz);
    if( pRead )
        *pRead = sz;
    
    return sz > 0;
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

string CDouble::ToString() {
    return to_string(m_dValue);
}
