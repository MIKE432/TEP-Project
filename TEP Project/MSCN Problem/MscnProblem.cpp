//
//  MscnProblem.cpp
//  TEP Project
//
//  Created by Michał Raszczuk on 30/12/2019.
//  Copyright © 2019 Michał Raszczuk. All rights reserved.
//

#include <stdio.h>

#include "MscnProblem.h"
#include "Matrix.h"
#include "Table.h"
#include "Consts.h"


SSolution::SSolution(CMatrix<double> xd, CMatrix<double> xf, CMatrix<double> xm) {
    
    m_xd = xd;
    m_xf = xf;
    m_xm = xm;
}

CMscnProblem::CMscnProblem() {
    
    setDCount(DEFAULT_MSCN_PROBLEM_D_COUNT);
    setFCount(DEFAULT_MSCN_PROBLEM_F_COUNT);
    setMCount(DEFAULT_MSCN_PROBLEM_M_COUNT);
    setSCount(DEFAULT_MSCN_PROBLEM_S_COUNT);
}

void CMscnProblem::setDCount(int dCount) {
    
    m_sd.resize(dCount);
    m_cd.resize(dCount, m_fCount);
    m_ud.resize(dCount);
    m_xdMinMax.resize(dCount, m_fCount);
}

void CMscnProblem::setFCount(int fCount) {
    
    m_sf.resize(fCount);
    m_cd.resize(m_dCount, fCount);
    m_cf.resize(fCount, m_mCount);
    m_uf.resize(fCount);
    m_xdMinMax.resize(m_dCount, fCount);
    m_xfMinMax.resize(fCount, m_mCount);
}

void CMscnProblem::setMCount(int mCount) {
    
    m_sm.resize(mCount);
    m_cf.resize(m_fCount, mCount);
    m_cm.resize(mCount, m_sCount);
    m_um.resize(mCount);
    m_xfMinMax.resize(m_fCount, mCount);
    m_xmMinMax.resize(mCount, m_sCount);
}

void CMscnProblem::setSCount(int sCount) {
    
    m_ss.resize(sCount);
    m_cm.resize(m_mCount, sCount);
    m_ps.resize(sCount);
    m_xmMinMax.resize(m_mCount, sCount);
}

void CMscnProblem::setInSd(double value, int offSet) {
    
    m_sd[offSet] = value;
}

void CMscnProblem::setInSf(double value, int offSet) {
    
    m_sf[offSet] = value;
}

void CMscnProblem::setInSm(double value, int offSet) {
    
    m_sm[offSet] = value;
}

void CMscnProblem::setInSs(double value, int offSet) {
    
    m_ss[offSet] = value;
}

void CMscnProblem::setInUd(double value, int offSet) {
    
    m_ud[offSet] = value;
}

void CMscnProblem::setInUf(double value, int offSet) {
    
    m_uf[offSet] = value;
}

void CMscnProblem::setInUm(double value, int offSet) {
    
    m_um[offSet] = value;
}

void CMscnProblem::setInPs(double value, int offSet) {
    
    m_ps[offSet] = value;
}

void CMscnProblem::setInXdMinMax(double value, int offSetX, int offSetY, int minOrMax) {
    
    m_xdMinMax[offSetX][offSetY][minOrMax] = value;
}

void CMscnProblem::setInXfMinMax(double value, int offSetX, int offSetY, int minOrMax) {
    
    m_xfMinMax[offSetX][offSetY][minOrMax] = value;
}

void CMscnProblem::setInXmMinMax(double value, int offSetX, int offSetY, int minOrMax) {
    
    m_xmMinMax[offSetX][offSetY][minOrMax] = value;
}

double CMscnProblem::getP(CMatrix<double>& xm) {
    
    double result = 0;
    
    for(int m = 0; m < m_mCount; m++) {
        
        for(int s = 0; s < m_sCount; s++) {
            
            result += m_ps[s] * xm[m][s];
        }
    }
    return result;
}

double CMscnProblem::getKu(CMatrix<double>& xd, CMatrix<double>& xf, CMatrix<double>& xm) {
    
    double result = 0;
    
    for(int d = 0; d < m_dCount; d++) {
        
        for(int f = 0; f < m_fCount; f++) {
            
            result += m_cd[d][f] * xd[d][f];
        }
    }
    
    for(int f = 0; f < m_fCount; f++) {
        
        for(int m = 0; m < m_mCount; m++) {
            
            result += m_cf[f][m] * xf[f][m];
        }
    }
    
    for(int m = 0; m < m_dCount; m++) {
        
        for(int s = 0; s < m_fCount; s++) {
            
            result += m_cm[m][s] * xm[m][s];
        }
    }
    
    return result;
}

double CMscnProblem::getKt(CMatrix<double>& xd, CMatrix<double>& xf, CMatrix<double>& xm) {
    
    double result = 0;
    
    for(int d = 0; d < m_dCount; d++) {
        if(xd.rowSumHigherThanZero(d))
            result += m_ud[d];
    }
    
    
    for(int f = 0; f < m_fCount; f++) {
        if(xf.rowSumHigherThanZero(f))
            result += m_uf[f];
    }
    
    
    for(int m = 0; m < m_mCount; m++) {
        if(xm.rowSumHigherThanZero(m))
            result += m_um[m];
    }
    
    return result;
}

double CMscnProblem::getQuality(double* pSolution, int& error, int solutionSize) {
    
    error = check(pSolution, solutionSize);
    
    if(!error)
        return 0;
    
    SSolution parsedSolution = parseSolution(pSolution);
    
    CMatrix<double> xd = parsedSolution.m_xd;
    CMatrix<double> xf = parsedSolution.m_xf;
    CMatrix<double> xm = parsedSolution.m_xm;
    
    
    return (getP(xd) - getKt(xd, xf, xm) - getKu(xd, xf, xm));
}

bool CMscnProblem::constraintsSatisfied(double* pSolution, int& error, int solutionSize) {
    
    
    
    
    
    
    
    
    return true;
}

int CMscnProblem::getSolutionSize() {
    
    return ((m_sCount * m_mCount) + (m_fCount * m_mCount) + (m_dCount * m_fCount));
}

int CMscnProblem::check(double* pSolution, int solutionSize) {
    
    if(pSolution == nullptr)
        return NULL_SOLUTION_POINTER_ERROR;
    
    if(solutionSize <= 0 || solutionSize > this->getSolutionSize())
        return WRONG_SOLUTION_SIZE_ERROR;
    
    return NO_ERROR;
}

SSolution CMscnProblem::parseSolution(double* pSolution) {
    
    CMatrix<double> xd(m_dCount, m_fCount);
    CMatrix<double> xf(m_fCount, m_mCount);
    CMatrix<double> xm(m_mCount, m_sCount);
    
    int counter = 0;
    
    for(int d = 0; d < m_dCount; d++) {
        
        for(int f = 0; f < m_fCount; f++) {
            
            xd[d][f] = pSolution[counter++];
        }
    }
    
    for(int f = 0; f < m_fCount; f++) {
        
        for(int m = 0; m < m_mCount; m++) {
            
            xf[f][m] = pSolution[counter++];
        }
    }
    
    for(int m = 0; m < m_mCount; m++) {
        
        for(int s = 0; s < m_sCount; s++) {
            
            xm[m][s] = pSolution[counter++];
        }
    }
    
    return SSolution(xd, xf, xm);
}

CTable<CTable<double>> CMscnProblem::getMinMaxSolutionTable() {
    
    int solutionSize = getSolutionSize();
    int counter = 0;
    CTable<CTable<double>> minMaxTable(solutionSize);
    
    for(int i = 0; i < solutionSize; i++) {
        
        minMaxTable[i] = CTable<double>(2);
    }
    
    for(int d = 0; d < m_dCount; d++) {
        
        for(int f = 0; f < m_fCount; f++) {
            
            minMaxTable[counter][MIN_VALUE_MSCN_MIN_MAX_TABLE] = m_xdMinMax[d][f][MIN_VALUE_MSCN_MIN_MAX_TABLE];
            minMaxTable[counter++][MAX_VALUE_MSCN_MIN_MAX_TABLE] = m_xdMinMax[d][f][MAX_VALUE_MSCN_MIN_MAX_TABLE];
        }
    }
    
    for(int f = 0; f < m_fCount; f++) {
        
        for(int m = 0; m < m_mCount; m++) {
            
            minMaxTable[counter][MIN_VALUE_MSCN_MIN_MAX_TABLE] = m_xfMinMax[f][m][MIN_VALUE_MSCN_MIN_MAX_TABLE];
            minMaxTable[counter++][MAX_VALUE_MSCN_MIN_MAX_TABLE] = m_xfMinMax[f][m][MAX_VALUE_MSCN_MIN_MAX_TABLE];
        }
    }
    
    for(int m = 0; m < m_mCount; m++) {
        
        for(int s = 0; s < m_sCount; s++) {
            
            minMaxTable[counter][MIN_VALUE_MSCN_MIN_MAX_TABLE] = m_xmMinMax[m][s][MIN_VALUE_MSCN_MIN_MAX_TABLE];
            minMaxTable[counter++][MAX_VALUE_MSCN_MIN_MAX_TABLE] = m_xmMinMax[m][s][MAX_VALUE_MSCN_MIN_MAX_TABLE];
        }
    }
    
    return minMaxTable;
}
