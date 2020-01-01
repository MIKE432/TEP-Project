//
//  MscnProblem.h
//  TEP Project
//
//  Created by Michał Raszczuk on 29/12/2019.
//  Copyright © 2019 Michał Raszczuk. All rights reserved.
//

#ifndef MscnProblem_h
#define MscnProblem_h

#include "Matrix.h"
#include "Table.h"
#include "Consts.h"
#include "Double.h"
#include "Range.h"

struct SSolution {
    CMatrix<CDouble> m_xf;
    CMatrix<CDouble> m_xd;
    CMatrix<CDouble> m_xm;
    
    SSolution(CMatrix<CDouble> xf, CMatrix<CDouble> xd, CMatrix<CDouble> xm);
};

class CMscnProblem {
private:
    int m_nSizeD;
    int m_nSizeF;
    int m_nSizeM;
    int m_nSizeS;
    
    int m_dCount;
    int m_fCount;
    int m_mCount;
    int m_sCount;
    
    CTable<CDouble> m_sd;
    CTable<CDouble> m_sf;
    CTable<CDouble> m_sm;
    CTable<CDouble> m_ss;
    
    CTable<CDouble> m_ud;
    CTable<CDouble> m_uf;
    CTable<CDouble> m_um;
    CTable<CDouble> m_ps; //m_tablePS;
    
    CMatrix<CDouble> m_cd; //m_matrixCD
    CMatrix<CDouble> m_cf;
    CMatrix<CDouble> m_cm;
    
    CMatrix<CRange> m_xdMinMax;
    CMatrix<CRange> m_xfMinMax;
    CMatrix<CRange> m_xmMinMax;
    
    void Init();
    
    int check(double* pSolution, int solutionSize);
    SSolution parseSolution(double* pSolution);
    int getSolutionSize();
    
public:
    CMscnProblem();
    
//---setters---
    void SetSizeD( int nSizeD );
    void SetSizeF( int nSizeF );
    void SetSizeM( int nSizeM );
    
    void setDCount(int dCount);
    void setFCount(int fCount);
    void setMCount(int mCount);
    void setSCount(int sCount);
    
    void setInSd(CDouble value, int offSet);
    void setInSf(CDouble value, int offSet);
    void setInSm(CDouble value, int offSet);
    void setInSs(CDouble value, int offSet);
    void setInUd(CDouble value, int offSet);
    void setInUf(CDouble value, int offSet);
    void setInUm(CDouble value, int offSet);
    void setInPs(CDouble value, int offSet);
    
    void setInXdMinMax(CDouble value, int offSetX, int offSetY, int minOrMax);
    void setInXfMinMax(CDouble value, int offSetX, int offSetY, int minOrMax);
    void setInXmMinMax(CDouble value, int offSetX, int offSetY, int minOrMax);
    
//---getters---
    double getKt(CMatrix<CDouble>& xd, CMatrix<CDouble>& xf, CMatrix<CDouble>& xm);
    double getKu(CMatrix<CDouble>& xd, CMatrix<CDouble>& xf, CMatrix<CDouble>& xm);
    double getP(CMatrix<CDouble>& xm);
    CTable<CRange> getMinMaxSolutionTable();
    
//---required methods---
    
    double getQuality(double* pSolution, int& error, int solutionSize);
    bool constraintsSatisfied(double* pSolution, int& error, int solutionSize);
    
    bool randomize(CRandom& random);

//---files handler methods (read, write)---
    
    bool readFromFile(FILE* file);
    bool writeToFile(FILE* file);
};

#endif /* MscnProblem_h */
