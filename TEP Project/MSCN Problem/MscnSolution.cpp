//
//  MscnSolution.cpp
//  TEP Project
//
//  Created by Michał Raszczuk on 05/01/2020.
//  Copyright © 2020 Michał Raszczuk. All rights reserved.
//

#include "MscnSolution.h"


CSolution::CSolution(size_t sizeSolution, size_t sizeD, size_t sizeF, size_t sizeM, size_t sizeS)
: m_pSolution(NULL), m_sizeSolution(sizeSolution), m_sizeD(sizeD), m_sizeF(sizeF), m_sizeM(sizeM), m_sizeS(sizeS) {
    
    m_pSolution = new double[m_sizeSolution];

    double* p = m_pSolution;
    m_matrixXD.Attach(p , m_sizeD, m_sizeF);
    
    p += m_sizeD*m_sizeF;
    m_matrixXF.Attach(p, m_sizeF, m_sizeM);
    
    p += m_sizeF*m_sizeM;
    m_matrixXM.Attach(p, m_sizeM, m_sizeS);
}

CSolution::CSolution(const CSolution& otherSolution) {
    
}

CSolution::~CSolution() {
    
    if(m_pSolution != NULL)
        delete[] m_pSolution;
}

double* CSolution::GetEndPtr() {
    
    return m_pSolution + m_sizeSolution;
}

double* CSolution::GetBeginPtr() {
    
    return m_pSolution;
}

int CSolution::Store(CArchive& archive) {
    
    archive << MN_D << space << m_sizeD << endln << endln;
    archive << MN_F << space << m_sizeF << endln << endln;
    archive << MN_M << space << m_sizeM << endln << endln;
    archive << MN_S << space << m_sizeS << endln << endln;
    
    archive << MN_XD << endln << endln << m_matrixXD;
    archive << MN_XF << endln << endln << m_matrixXF;
    archive << MN_XM << endln << endln << m_matrixXM;
    
    return NO_ERROR;
}
