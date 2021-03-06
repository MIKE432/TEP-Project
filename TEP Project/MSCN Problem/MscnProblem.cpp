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

CMscnProblem::CMscnProblem()
: CProblem()
, m_nSizeD( DEFAULT_MSCN_PROBLEM_D_COUNT )
, m_nSizeF( DEFAULT_MSCN_PROBLEM_F_COUNT )
, m_nSizeM( DEFAULT_MSCN_PROBLEM_M_COUNT )
, m_nSizeS( DEFAULT_MSCN_PROBLEM_S_COUNT ) {

    Init();
}

void CMscnProblem::Init() {
    
    m_tableSizes = CTable<size_t>(4);
    m_tableSizes[0] = m_nSizeD;
    m_tableSizes[1] = m_nSizeF;
    m_tableSizes[2] = m_nSizeM;
    m_tableSizes[3] = m_nSizeS;
    
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

void CMscnProblem::GenerateInstance(int nInstanceSeed) {
    
    CRandom random(nInstanceSeed);
    Randomize(random);
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
    
    m_matrixMinMaxXD.Randomize(random.SetRange(DEFAULT_MSCN_XF_RANDOM_MIN_VALUE, DEFAULT_MSCN_XD_RANDOM_MAX_VALUE));
    m_matrixMinMaxXF.Randomize(random.SetRange(DEFAULT_MSCN_XF_RANDOM_MIN_VALUE, DEFAULT_MSCN_XF_RANDOM_MAX_VALUE));
    m_matrixMinMaxXM.Randomize(random.SetRange(DEFAULT_MSCN_XM_RANDOM_MIN_VALUE, DEFAULT_MSCN_XM_RANDOM_MAX_VALUE));

    return true;
}

void CMscnProblem::SetSizeD(int sizeD) {
    
    m_nSizeD = sizeD;
    m_tableSizes[0] = m_nSizeD;
    m_tableSD.Resize(m_nSizeD);
    m_matrixCD.Resize(m_nSizeD, m_nSizeF);
    m_tableUD.Resize(m_nSizeD);
    m_matrixMinMaxXD.Resize(m_nSizeD, m_nSizeF);
}

void CMscnProblem::SetSizeF(int sizeF) {
    
    m_nSizeF = sizeF;
    m_tableSizes[1] = m_nSizeF;
    m_tableSF.Resize(m_nSizeF);
    m_matrixCD.Resize(m_nSizeD, m_nSizeF);
    m_matrixCF.Resize(m_nSizeF, m_nSizeM);
    m_tableUF.Resize(m_nSizeF);
    m_matrixMinMaxXD.Resize(m_nSizeD, m_nSizeF);
    m_matrixMinMaxXF.Resize(m_nSizeF, m_nSizeM);
}

void CMscnProblem::SetSizeM(int sizeM) {
    
    m_nSizeM = sizeM;
    m_tableSizes[2] = m_nSizeM;
    m_tableSM.Resize(m_nSizeM);
    m_matrixCF.Resize(m_nSizeF, m_nSizeM);
    m_matrixCM.Resize(m_nSizeM, m_nSizeS);
    m_tableUM.Resize(m_nSizeM);
    m_matrixMinMaxXF.Resize(m_nSizeF, m_nSizeM);
    m_matrixMinMaxXM.Resize(m_nSizeM, m_nSizeS);
}

void CMscnProblem::SetSizeS(int sizeS) {
    
    m_nSizeS = sizeS;
    m_tableSizes[3] = m_nSizeS;
    m_tableSS.Resize(m_nSizeS);
    m_matrixCM.Resize(m_nSizeM, m_nSizeS);
    m_tablePS.Resize(m_nSizeS);
    m_matrixMinMaxXM.Resize(m_nSizeM, m_nSizeS);
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

double CMscnProblem::GetP(CMatrixHelper& xm) {
    
    double result = 0;
    
    for(int m = 0; m < m_nSizeM; m++) {
        
        for(int s = 0; s < m_nSizeS; s++) {
            
            result += m_tablePS[s].Get() * xm.Get(m, s);
        }
    }
    
    return result;
}

double CMscnProblem::GetKT(CMatrixHelper& xd, CMatrixHelper& xf, CMatrixHelper& xm) {
    
    double result = 0;
    
    for(int d = 0; d < m_nSizeD; d++) {
        
        for(int f = 0; f < m_nSizeF; f++) {
            
            result += m_matrixCD[d][f].Get() * xd.Get(d, f);
        }
    }
    
    for(int f = 0; f < m_nSizeF; f++) {
        
        for(int m = 0; m < m_nSizeM; m++) {
            
            result += m_matrixCF[f][m].Get() * xf.Get(f, m);
        }
    }
    
    for(int m = 0; m < m_nSizeM; m++) {
        
        for(int s = 0; s < m_nSizeS; s++) {
            
            result += m_matrixCM[m][s].Get() * xm.Get(m, s);
        }
    }
    
    return result;
}

double CMscnProblem::GetKU(CMatrixHelper& xd, CMatrixHelper& xf, CMatrixHelper& xm) {
    
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

double CMscnProblem::GetBottleNeck() {
    
    double bottleNeck = DBL_MAX;
    
    double potentialBottleNeck = ZERO;
    
    if(bottleNeck > (potentialBottleNeck = SumTable(m_tableSD)))
        bottleNeck = potentialBottleNeck;
    
    if(bottleNeck > (potentialBottleNeck = SumTable(m_tableSF)))
        bottleNeck = potentialBottleNeck;
    
    if(bottleNeck > (potentialBottleNeck = SumTable(m_tableSM)))
        bottleNeck = potentialBottleNeck;
    
    if(bottleNeck > (potentialBottleNeck = SumTable(m_tableSS)))
        bottleNeck = potentialBottleNeck;
        
    
    return bottleNeck;
}

double CMscnProblem::GetQuality(double* pSolution, size_t sizeSolution, int& error) {
    
    if((error = ValidateSolution(pSolution, sizeSolution)) != 0)
        return error;
    
    double* p = pSolution;
    
    CMatrixHelper xd(p, m_nSizeD, m_nSizeF);
    
    p += m_nSizeD * m_nSizeF;
    CMatrixHelper xf(p, m_nSizeF, m_nSizeM);
    
    p += m_nSizeF * m_nSizeM;
    CMatrixHelper xm(p, m_nSizeM, m_nSizeS);
    
    double bottleNeck = GetBottleNeck();
    
    
    
    return (GetP(xd) - GetKT(xd, xf, xm) - GetKU(xd, xf, xm));
}

bool CMscnProblem::ConstraintsSatisfied(double* pSolution, size_t sizeSolution, int& error) {
    
    if((error = ValidateSolution(pSolution, sizeSolution)) != 0)
        return false;
    
    double* p = pSolution;
    
    CMatrixHelper xd(p, m_nSizeD, m_nSizeF );
    
    p += m_nSizeD * m_nSizeF;
    CMatrixHelper xf(p, m_nSizeF, m_nSizeM);
    
    p += m_nSizeF * m_nSizeM;
    CMatrixHelper xm(p, m_nSizeM, m_nSizeS);
    

    for(int d = 0; d < m_nSizeD; d++) {
        
        if(xd.sumInColumn(d) > m_tableSD[d].Get())
            return false;
    }
    
    for(int f = 0; f < m_nSizeF; f++) {
        
        if(xf.sumInColumn(f) > m_tableSF[f].Get())
            return false;
    }
    
    for(int m = 0; m < m_nSizeM; m++) {
        
        if(xm.sumInColumn(m) > m_tableSM[m].Get())
            return false;
    }
    
    for(int s = 0; s < m_nSizeS; s++) {
        
        if(xm.sumInRow(s) > m_tableSS[s].Get())
            return false;
    }
    
    for(int f = 0; f < m_nSizeF; f++) {
        
        if(xd.sumInRow(f) < xf.sumInColumn(f))
            return false;
    }
    
    for(int m = 0; m < m_nSizeM; m++) {
        
        if(xf.sumInRow(m) > xm.sumInColumn(m))
            return false;
    }
    
    return true;
}

size_t CMscnProblem::GetSolutionSize() {
    
    return ((m_nSizeS * m_nSizeM) + (m_nSizeF * m_nSizeM) + (m_nSizeD * m_nSizeF));
}

int CMscnProblem::ValidateSolution(double* pSolution, size_t sizeSolution) {
    
    if(pSolution == nullptr)
        return NULL_SOLUTION_POINTER_ERROR;
    
    if(sizeSolution <= 0 || sizeSolution > this->GetSolutionSize())
        return WRONG_SOLUTION_SIZE_ERROR;
    
    return NO_ERROR;
}

CRange& CMscnProblem::GetSolutionConstraint(int i) {
    
    if(i < (m_nSizeD*m_nSizeF)) {
        
        int d = i/m_nSizeF;
        int f = i%m_nSizeF;

        return m_matrixMinMaxXD[d][f];
    }
    
    i -= m_nSizeD * m_nSizeF;
    
    if(i < (m_nSizeF * m_nSizeM)) {
        
        int f = i / m_nSizeM;
        int m = i % m_nSizeM;
        
        return m_matrixMinMaxXF[f][m];
    }
    
    i -= m_nSizeF * m_nSizeM;
    
    if(i < (m_nSizeM * m_nSizeS)) {
        
        int m = i / m_nSizeS;
        int s = i % m_nSizeS;

        return m_matrixMinMaxXM[m][s];
    }
    
    return m_matrixMinMaxXM[0][0];
}

bool CMscnProblem::Store(CArchive& archive) {
    
    archive << MN_D << space << m_nSizeD << endln << endln;
    archive << MN_F << space << m_nSizeF << endln << endln;
    archive << MN_M << space << m_nSizeM << endln << endln;
    archive << MN_S << space << m_nSizeS << endln << endln;

    archive << MN_SD << endln << endln << m_tableSD;
    archive << MN_SF << endln << endln << m_tableSF;
    archive << MN_SM << endln << endln << m_tableSM;
    archive << MN_SS << endln << endln << m_tableSS;
    archive << MN_CD << endln << endln << m_matrixCD;
    archive << MN_CF << endln << endln << m_matrixCF;
    archive << MN_CM << endln << endln << m_matrixCM;
    archive << MN_UD << endln << endln << m_tableUD;
    archive << MN_UF << endln << endln << m_tableUF;
    archive << MN_UM << endln << endln << m_tableUM;
    archive << MN_PS << endln << endln << m_tablePS;
    archive << MN_MINMAXXD << endln << endln << m_matrixMinMaxXD;
    archive << MN_MINMAXXF << endln << endln << m_matrixMinMaxXF;
    archive << MN_MINMAXXM << endln << endln << m_matrixMinMaxXM;
 
    return true;
}

bool CMscnProblem::Load(CArchive& archive) {
    
    archive >> IsValidText(MN_D) >> space >> m_nSizeD >> endln >> endln;
    archive >> IsValidText(MN_F) >> space >> m_nSizeF >> endln >> endln;
    archive >> IsValidText(MN_M) >> space >> m_nSizeM >> endln >> endln;
    archive >> IsValidText(MN_S) >> space >> m_nSizeS >> endln >> endln;
    
    Init();

    archive >> IsValidText(MN_SD) >> endln >> endln >> m_tableSD;
    archive >> IsValidText(MN_SF) >> endln >> endln >> m_tableSF;
    archive >> IsValidText(MN_SM) >> endln >> endln >> m_tableSM;
    archive >> IsValidText(MN_SS) >> endln >> endln >> m_tableSS;
    archive >> IsValidText(MN_CD) >> endln >> endln >> m_matrixCD;
    archive >> IsValidText(MN_CF) >> endln >> endln >> m_matrixCF;
    archive >> IsValidText(MN_CM) >> endln >> endln >> m_matrixCM;
    archive >> IsValidText(MN_UD) >> endln >> endln >> m_tableUD;
    archive >> IsValidText(MN_UF) >> endln >> endln >> m_tableUF;
    archive >> IsValidText(MN_UM) >> endln >> endln >> m_tableUM;
    archive >> IsValidText(MN_PS) >> endln >> endln >> m_tablePS;
    archive >> IsValidText(MN_MINMAXXD) >> endln >> endln >> m_matrixMinMaxXD;
    archive >> IsValidText(MN_MINMAXXF) >> endln >> endln >> m_matrixMinMaxXF;
    archive >> IsValidText(MN_MINMAXXM) >> endln >> endln >> m_matrixMinMaxXM;

    return true;
}
