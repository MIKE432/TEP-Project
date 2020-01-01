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

CRandom::CRandom(int seed)
: m_seed(seed) {
    m_dre = std::default_random_engine(m_rd());
    m_dre.seed(seed);
}

double CRandom::nextNumber() {
    std::uniform_real_distribution<double> dist(10, 15);
    return dist(m_dre);
}

double CRandom::nextNumber(double leftEdge, double rightEdge) {
    std::uniform_real_distribution<double> dist(leftEdge, rightEdge);
    return dist(m_dre);
}

void CRandom::setSeed(int seed) {
    
    m_seed = seed;
    m_dre.seed(seed);
    
}
void CRandom::deleteSeed() {
    m_dre = std::default_random_engine(m_rd());
    m_seed = NULL;
}
