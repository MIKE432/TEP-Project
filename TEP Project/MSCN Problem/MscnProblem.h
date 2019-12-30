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

struct SSolution {
    CMatrix<double> m_xf;
    CMatrix<double> m_xd;
    CMatrix<double> m_xm;
    
    SSolution(CMatrix<double> xf, CMatrix<double> xd, CMatrix<double> xm);
};

class CMscnProblem {
private:
    int m_dCount;
    int m_fCount;
    int m_mCount;
    int m_sCount;
    
    CTable<double> m_sd;
    CTable<double> m_sf;
    CTable<double> m_sm;
    CTable<double> m_ss;
    
    CTable<double> m_ud;
    CTable<double> m_uf;
    CTable<double> m_um;
    CTable<double> m_ps;
    
    CMatrix<double> m_cd;
    CMatrix<double> m_cf;
    CMatrix<double> m_cm;
    
    CMatrix<CTable<double>> m_xdMinMax;
    CMatrix<CTable<double>> m_xfMinMax;
    CMatrix<CTable<double>> m_xmMinMax;
    
    int check(double* pSolution, int solutionSize);
    SSolution parseSolution(double* pSolution);
    int getSolutionSize();
    
public:
    CMscnProblem();
    
//---setters---
    void setDCount(int dCount);
    void setFCount(int fCount);
    void setMCount(int mCount);
    void setSCount(int sCount);
    
    void setInSd(double value, int offSet);
    void setInSf(double value, int offSet);
    void setInSm(double value, int offSet);
    void setInSs(double value, int offSet);
    void setInUd(double value, int offSet);
    void setInUf(double value, int offSet);
    void setInUm(double value, int offSet);
    void setInPs(double value, int offSet);
    
    void setInXdMinMax(double value, int offSetX, int offSetY, int minOrMax);
    void setInXfMinMax(double value, int offSetX, int offSetY, int minOrMax);
    void setInXmMinMax(double value, int offSetX, int offSetY, int minOrMax);
    
//---getters---
    double getKt(CMatrix<double>& xd, CMatrix<double>& xf, CMatrix<double>& xm);
    double getKu(CMatrix<double>& xd, CMatrix<double>& xf, CMatrix<double>& xm);
    double getP(CMatrix<double>& xm);
    CTable<CTable<double>> getMinMaxSolutionTable();
    
//---required methods---
    
    double getQuality(double* pSolution, int& error, int solutionSize);
    bool constraintsSatisfied(double* pSolution, int& error, int solutionSize);

//---files handler methods (read, write)---
    
    bool readFromFile(FILE* file);
    bool writeToFile(FILE* file);
};

#endif /* MscnProblem_h */
