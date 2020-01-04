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

using namespace std;


SSolution::SSolution(CMatrix<CDouble> xd, CMatrix<CDouble> xf, CMatrix<CDouble> xm) {
    
    m_xd = xd;
    m_xf = xf;
    m_xm = xm;
}

CMscnProblem::CMscnProblem()
: m_nSizeD( DEFAULT_MSCN_PROBLEM_D_COUNT )
, m_nSizeF( DEFAULT_MSCN_PROBLEM_F_COUNT )
, m_nSizeM( DEFAULT_MSCN_PROBLEM_M_COUNT )
, m_nSizeS( DEFAULT_MSCN_PROBLEM_S_COUNT ) {

    Init();
}

void CMscnProblem::Init() {
    
    m_tableSD.Resize(m_nSizeD);
    m_tableSF.Resize(m_nSizeF);
    m_tableSS.Resize(m_nSizeS);
    m_tableSM.Resize(m_nSizeM);
    
    m_tableUD.Resize(m_nSizeD);
    m_tableUF.Resize(m_nSizeF);
    m_tableUM.Resize(m_nSizeM);
    m_tablePS.Resize(m_nSizeS);
    
    m_matrixCD.Resize(m_nSizeD, m_nSizeF);
    m_matrixCF.Resize(m_nSizeF, m_nSizeM);
    m_matrixCM.Resize(m_nSizeM, m_nSizeS);
    
    m_matrixMinMaxXD.Resize(m_nSizeD, m_nSizeF);
    m_matrixMinMaxXF.Resize(m_nSizeF, m_nSizeM);
    m_matrixMinMaxXM.Resize(m_nSizeM, m_nSizeS);
}

bool CMscnProblem::Randomize(CRandom& random) {
    
    m_tableSD.Randomize(random.SetRange(DEFAULT_MSCN_S_RANDOM_MIN_VALUE, DEFAULT_MSCN_S_RANDOM_MAX_VALUE));
    m_tableSF.Randomize(random.SetRange(DEFAULT_MSCN_S_RANDOM_MIN_VALUE, DEFAULT_MSCN_S_RANDOM_MAX_VALUE));
    m_tableSS.Randomize(random.SetRange(DEFAULT_MSCN_S_RANDOM_MIN_VALUE, DEFAULT_MSCN_S_RANDOM_MAX_VALUE));
    m_tableSM.Randomize(random.SetRange(DEFAULT_MSCN_S_RANDOM_MIN_VALUE, DEFAULT_MSCN_S_RANDOM_MAX_VALUE));
    
    m_tableUD.Randomize(random.SetRange(DEFAULT_MSCN_U_RANDOM_MIN_VALUE, DEFAULT_MSCN_U_RANDOM_MAX_VALUE));
    m_tableUF.Randomize(random.SetRange(DEFAULT_MSCN_U_RANDOM_MIN_VALUE, DEFAULT_MSCN_U_RANDOM_MAX_VALUE));
    m_tableUM.Randomize(random.SetRange(DEFAULT_MSCN_U_RANDOM_MIN_VALUE, DEFAULT_MSCN_U_RANDOM_MAX_VALUE));
    m_tablePS.Randomize(random.SetRange(DEFAULT_MSCN_P_RANDOM_MIN_VALUE, DEFAULT_MSCN_P_RANDOM_MAX_VALUE));
    
    m_matrixCD.Randomize(random.SetRange(DEFAULT_MSCN_C_RANDOM_MIN_VALUE, DEFAULT_MSCN_C_RANDOM_MAX_VALUE));
    m_matrixCF.Randomize(random.SetRange(DEFAULT_MSCN_C_RANDOM_MIN_VALUE, DEFAULT_MSCN_C_RANDOM_MAX_VALUE));
    m_matrixCM.Randomize(random.SetRange(DEFAULT_MSCN_C_RANDOM_MIN_VALUE, DEFAULT_MSCN_C_RANDOM_MAX_VALUE));
    
    m_matrixMinMaxXD.Randomize(random.SetRange(0, 50));
    m_matrixMinMaxXF.Randomize(random.SetRange(0, 50));
    m_matrixMinMaxXM.Randomize(random.SetRange(0, 50));

    return true;
}

void CMscnProblem::SetSizeD(int sizeD) {
    
    m_nSizeD = sizeD;
    
    m_tableSD.Resize(sizeD);
    m_matrixCD.Resize(sizeD, m_nSizeF);
    m_tableUD.Resize(sizeD);
    m_matrixMinMaxXD.Resize(sizeD, m_nSizeF);
}

void CMscnProblem::SetSizeF(int sizeF) {
    
    m_nSizeF = sizeF;
    
    m_tableSF.Resize(sizeF);
    m_matrixCD.Resize(m_nSizeD, sizeF);
    m_matrixCF.Resize(sizeF, m_nSizeM);
    m_tableUF.Resize(sizeF);
    m_matrixMinMaxXD.Resize(m_nSizeD, sizeF);
    m_matrixMinMaxXF.Resize(sizeF, m_nSizeM);
}

void CMscnProblem::SetSizeM(int sizeM) {
    
    m_nSizeM = sizeM;
    
    m_tableSM.Resize(sizeM);
    m_matrixCF.Resize(m_nSizeF, sizeM);
    m_matrixCM.Resize(sizeM, m_nSizeS);
    m_tableUM.Resize(sizeM);
    m_matrixMinMaxXF.Resize(m_nSizeF, sizeM);
    m_matrixMinMaxXM.Resize(sizeM, m_nSizeS);
}

void CMscnProblem::SetSizeS(int sizeS) {
    
    m_nSizeS = sizeS;
    
    m_tableSS.Resize(sizeS);
    m_matrixCM.Resize(m_nSizeM, sizeS);
    m_tablePS.Resize(sizeS);
    m_matrixMinMaxXM.Resize(m_nSizeM, sizeS);
}

void CMscnProblem::SetInSD(CDouble value, int offset) {
    
    m_tableSD[offset] = value;
}

void CMscnProblem::SetInSF(CDouble value, int offset) {
    
    m_tableSF[offset] = value;
}

void CMscnProblem::SetInSM(CDouble value, int offset) {
    
    m_tableSM[offset] = value;
}

void CMscnProblem::SetInSS(CDouble value, int offset) {
    
    m_tableSS[offset] = value;
}

void CMscnProblem::SetInUD(CDouble value, int offset) {
    
    m_tableUD[offset] = value;
}

void CMscnProblem::SetInUF(CDouble value, int offset) {
    
    m_tableUF[offset] = value;
}

void CMscnProblem::SetInUM(CDouble value, int offset) {
    
    m_tableUM[offset] = value;
}

void CMscnProblem::SetInPS(CDouble value, int offset) {
    
    m_tablePS[offset] = value;
}

void CMscnProblem::SetInMinMaxXD(CDouble value, int offsetX, int offsetY, int minOrMax) {
    
    m_matrixMinMaxXD[offsetX][offsetY][minOrMax] = value;
}

void CMscnProblem::SetInMinMaxXF(CDouble value, int offsetX, int offsetY, int minOrMax) {
    
    m_matrixMinMaxXF[offsetX][offsetY][minOrMax] = value;
}

void CMscnProblem::SetInMinMaxXM(CDouble value, int offsetX, int offsetY, int minOrMax) {
    
    m_matrixMinMaxXM[offsetX][offsetY][minOrMax] = value;
}

double CMscnProblem::GetP(CMatrix<CDouble>& xm) {
    
    double result = 0;
    
    for(int m = 0; m < m_nSizeM; m++) {
        
        for(int s = 0; s < m_nSizeS; s++) {
            
            result += m_tablePS[s].Get() * xm[m][s].Get();
        }
    }
    return result;
}

double CMscnProblem::GetKU(CMatrix<CDouble>& xd, CMatrix<CDouble>& xf, CMatrix<CDouble>& xm) {
    
    double result = 0;
    
    for(int d = 0; d < m_nSizeD; d++) {
        
        for(int f = 0; f < m_nSizeF; f++) {
            
            result += m_matrixCD[d][f].Get() * xd[d][f].Get();
        }
    }
    
    for(int f = 0; f < m_nSizeF; f++) {
        
        for(int m = 0; m < m_nSizeM; m++) {
            
            result += m_matrixCF[f][m].Get() * xf[f][m].Get();
        }
    }
    
    for(int m = 0; m < m_nSizeD; m++) {
        
        for(int s = 0; s < m_nSizeF; s++) {
            
            result += m_matrixCM[m][s].Get() * xm[m][s].Get();
        }
    }
    
    return result;
}

double CMscnProblem::GetKT(CMatrix<CDouble>& xd, CMatrix<CDouble>& xf, CMatrix<CDouble>& xm) {
    
    double result = 0;
    
    for(int d = 0; d < m_nSizeD; d++) {
        if(xd.rowSumHigherThanZero(d))
            result += m_tableUD[d].Get();
    }
    
    
    for(int f = 0; f < m_nSizeF; f++) {
        if(xf.rowSumHigherThanZero(f))
            result += m_tableUF[f].Get();
    }
    
    
    for(int m = 0; m < m_nSizeM; m++) {
        if(xm.rowSumHigherThanZero(m))
            result += m_tableUM[m].Get();
    }
    
    return result;
}

double CMscnProblem::GetQuality(double* pSolution, int& error, int solutionSize) {
    
    error = Check(pSolution, solutionSize);
    
    if(!error)
        return 0;
    
    SSolution parsedSolution = ParseSolution(pSolution);
    
    CMatrix<CDouble> xd = parsedSolution.m_xd;
    CMatrix<CDouble> xf = parsedSolution.m_xf;
    CMatrix<CDouble> xm = parsedSolution.m_xm;
    
    
    return (GetP(xd) - GetKT(xd, xf, xm) - GetKU(xd, xf, xm));
}

bool CMscnProblem::ConstraintsSatisfied(double* pSolution, int& error, int solutionSize) {
    
    error = Check(pSolution, solutionSize);
    
    if(!error)
        return false;
    
    SSolution parsedSolution = ParseSolution(pSolution);
    
    CMatrix<CDouble> xd = parsedSolution.m_xd;
    CMatrix<CDouble> xf = parsedSolution.m_xf;
    CMatrix<CDouble> xm = parsedSolution.m_xm;
    

    for(int d = 0; d < m_nSizeD; d++) {
        
        if(xd.sumInRowOrColumn('c', d) > m_tableSD[d].Get())
            return false;
    }
    
    for(int f = 0; f < m_nSizeF; f++) {
        
        if(xf.sumInRowOrColumn('c', f) > m_tableSF[f].Get())
            return false;
    }
    
    for(int m = 0; m < m_nSizeM; m++) {
        
        if(xm.sumInRowOrColumn('c', m) > m_tableSM[m].Get())
            return false;
    }
    
    for(int s = 0; s < m_nSizeS; s++) {
        
        if(xm.sumInRowOrColumn('r', s) > m_tableSS[s].Get())
            return false;
    }
    
    for(int f = 0; f < m_nSizeF; f++) {
        
        if(xd.sumInRowOrColumn('r', f) < xf.sumInRowOrColumn('c', f))
            return false;
    }
    
    for(int m = 0; m < m_nSizeM; m++) {
        
        if(xf.sumInRowOrColumn('r', m) > xm.sumInRowOrColumn('c', m))
            return false;
    }
    
    return true;
}

int CMscnProblem::GetSolutionSize() {
    
    return ((m_nSizeS * m_nSizeM) + (m_nSizeF * m_nSizeM) + (m_nSizeD * m_nSizeF));
}

int CMscnProblem::Check(double* pSolution, int solutionSize) {
    
    if(pSolution == nullptr)
        return NULL_SOLUTION_POINTER_ERROR;
    
    if(solutionSize <= 0 || solutionSize > this->GetSolutionSize())
        return WRONG_SOLUTION_SIZE_ERROR;
    
    return NO_ERROR;
}

SSolution CMscnProblem::ParseSolution(double* pSolution) {
    
    CMatrix<CDouble> xd(m_nSizeD, m_nSizeF);
    CMatrix<CDouble> xf(m_nSizeF, m_nSizeM);
    CMatrix<CDouble> xm(m_nSizeM, m_nSizeS);
    
    int counter = 0;
    
    for(int d = 0; d < m_nSizeD; d++) {
        
        for(int f = 0; f < m_nSizeF; f++) {
            
            xd[d][f] = pSolution[counter++];
        }
    }
    
    for(int f = 0; f < m_nSizeF; f++) {
        
        for(int m = 0; m < m_nSizeM; m++) {
            
            xf[f][m] = pSolution[counter++];
        }
    }
    
    for(int m = 0; m < m_nSizeM; m++) {
        
        for(int s = 0; s < m_nSizeS; s++) {
            
            xm[m][s] = pSolution[counter++];
        }
    }
    
    return SSolution(xd, xf, xm);
}

CTable<CRange> CMscnProblem::GetMinMaxSolutionTable() {
    
    int solutionSize = GetSolutionSize();
    int counter = 0;
    CTable<CRange> minMaxTable(solutionSize);
    
    for(int d = 0; d < m_nSizeD; d++) {
        
        for(int f = 0; f < m_nSizeF; f++) {
            
            minMaxTable[counter][MIN_VALUE_MSCN_MIN_MAX_TABLE] = m_matrixMinMaxXD[d][f][MIN_VALUE_MSCN_MIN_MAX_TABLE];
            minMaxTable[counter++][MAX_VALUE_MSCN_MIN_MAX_TABLE] = m_matrixMinMaxXD[d][f][MAX_VALUE_MSCN_MIN_MAX_TABLE];
        }
    }
    
    for(int f = 0; f < m_nSizeF; f++) {
        
        for(int m = 0; m < m_nSizeM; m++) {
            
            minMaxTable[counter][MIN_VALUE_MSCN_MIN_MAX_TABLE] = m_matrixMinMaxXF[f][m][MIN_VALUE_MSCN_MIN_MAX_TABLE];
            minMaxTable[counter++][MAX_VALUE_MSCN_MIN_MAX_TABLE] = m_matrixMinMaxXF[f][m][MAX_VALUE_MSCN_MIN_MAX_TABLE];
        }
    }
    
    for(int m = 0; m < m_nSizeM; m++) {
        
        for(int s = 0; s < m_nSizeS; s++) {
            
            minMaxTable[counter][MIN_VALUE_MSCN_MIN_MAX_TABLE] = m_matrixMinMaxXM[m][s][MIN_VALUE_MSCN_MIN_MAX_TABLE];
            minMaxTable[counter++][MAX_VALUE_MSCN_MIN_MAX_TABLE] = m_matrixMinMaxXM[m][s][MAX_VALUE_MSCN_MIN_MAX_TABLE];
        }
    }
    
    return minMaxTable;
}

bool CMscnProblem::Store(CArchive& archive) {
    
    archive << 'D' << space << m_nSizeD << endln << endln;
    archive << 'F' << space << m_nSizeF << endln << endln;
    archive << 'M' << space << m_nSizeM << endln << endln;
    archive << 'S' << space << m_nSizeS << endln << endln;

    archive << 's' << 'd' << endln << endln << m_tableSD;
    archive << 's' << 'f' << endln << endln << m_tableSF;
    archive << 's' << 'm' << endln << endln << m_tableSM;
    archive << 's' << 's' << endln << endln << m_tableSS;
    archive << 'c' << 'd' << endln << endln << m_matrixCD;
    archive << 'c' << 'f' << endln << endln << m_matrixCF;
    archive << 'c' << 'm' << endln << endln << m_matrixCM;
    archive << 'u' << 'd' << endln << endln << m_tableUD;
    archive << 'u' << 'f' << endln << endln << m_tableUF;
    archive << 'u' << 'm' << endln << endln << m_tableUM;
    archive << 'p' << endln << endln << m_tablePS;
    archive << 'x' << 'd' << 'm' << 'i' << 'n' << 'm' << 'a' << 'x' << endln << endln << m_matrixMinMaxXD;
    //archive << "xdminmax" << endln << endln << m_matrixMinMaxXD;
    archive << 'x' << 'f' << 'm' << 'i' << 'n' << 'm' << 'a' << 'x' << endln << endln << m_matrixMinMaxXF;
    archive << 'x' << 'm' << 'm' << 'i' << 'n' << 'm' << 'a' << 'x' << endln << endln << m_matrixMinMaxXM;
 
    return true;
}

bool CMscnProblem::Load(CArchive& archive) {
    
    archive >> Validate("D") >> space >> m_nSizeD >> endln >> endln;
    archive >> Validate("F") >> space >> m_nSizeF >> endln >> endln;
    archive >> Validate("M") >> space >> m_nSizeM >> endln >> endln;
    archive >> Validate("S") >> space >> m_nSizeS >> endln >> endln;
    
    Init();

    archive >> Validate("sd") >> endln >> endln >> m_tableSD;
    archive >> Validate("sf") >> endln >> endln >> m_tableSF;
    archive >> Validate("sm") >> endln >> endln >> m_tableSM;
    archive >> Validate("ss") >> endln >> endln >> m_tableSS;
    archive >> Validate("cd") >> endln >> endln >> m_matrixCD;
    archive >> Validate("cf") >> endln >> endln >> m_matrixCF;
    archive >> Validate("cm") >> endln >> endln >> m_matrixCM;
    archive >> Validate("ud") >> endln >> endln >> m_tableUD;
    archive >> Validate("uf") >> endln >> endln >> m_tableUF;
    archive >> Validate("um") >> endln >> endln >> m_tableUM;
    archive >> Validate("p") >> endln >> endln >> m_tablePS;
    archive >> Validate("xdminmax") >> endln >> endln >> m_matrixMinMaxXD;
    archive >> Validate("xfminmax") >> endln >> endln >> m_matrixMinMaxXF;
    archive >> Validate("xmminmax") >> endln >> endln >> m_matrixMinMaxXM;

    return true;
}
