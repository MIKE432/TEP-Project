//
//  Random.cpp
//  TEP Project
//
//  Created by Michał Raszczuk on 31/12/2019.
//  Copyright © 2019 Michał Raszczuk. All rights reserved.
//

#include <stdio.h>
#include "Random.h"

CRandom::CRandom() {
    
    m_dre = std::default_random_engine(m_rd());
}

CRandom::CRandom(int seed) {
    
    m_dre = std::default_random_engine(m_rd());
    m_dre.seed(seed);
    SetRange(0.0, 1.0);
}

CRandom& CRandom::operator >> (double& dValue) {
    
    dValue = Generate();
    return *this;
}

void CRandom::SetRange(std::uniform_real_distribution<double>& dist) {
    
    m_dist = dist;
}

CRandom& CRandom::SetRange(double dFrom, double dTo) {
    
    m_dist = std::uniform_real_distribution<double>(dFrom, dTo);
    return *this;
}

double CRandom::Generate() {
    
    //std::uniform_real_distribution<double> dist(m_dFrom, m_dTo);
    return m_dist(m_dre);
}


