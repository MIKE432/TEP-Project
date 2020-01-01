//
//  Double.hpp
//  TEP Project
//
//  Created by Michał Raszczuk on 01/01/2020.
//  Copyright © 2020 Michał Raszczuk. All rights reserved.
//

#ifndef Double_h
#define Double_h

#include <stdio.h>
#include <string>
#include "Random.h"

using namespace std;

class CDouble {
private:
    double m_dValue;
    
  
public:
    CDouble();
    CDouble(double num);
    
    void set(double num);
    double get() const;
    
    string ToString();
    bool Parse(string s, string::size_type* pRead = NULL);
    
    bool randomize(CRandom& random);
    
    CDouble& operator = (const CDouble& otherDouble);
    CDouble& operator = (double double1);
    CDouble& operator += (const CDouble& otherDouble);
    CDouble operator + (const CDouble& otherDouble);
    CDouble operator - (const CDouble& otherDouble);
    CDouble operator * (const CDouble& otherDouble);
    CDouble operator / (const CDouble& otherDouble);
    
    bool operator > (const CDouble& otherDouble);
    bool operator > (double double1);
    bool operator < (const CDouble& otherDouble);
    bool operator < (double double1);
    
    bool operator == (const CDouble& otherDouble);
    bool operator == (double double1);
    bool operator != (const CDouble& otherDouble);
    bool operator != (double double1);
    
//    operatory == !=
    
};

#endif /* Double_h */
