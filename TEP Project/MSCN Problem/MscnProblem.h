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
#include "Archive.h"

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
    
    CTable<CDouble> m_tableSD;
    CTable<CDouble> m_tableSF;
    CTable<CDouble> m_tableSM;
    CTable<CDouble> m_tableSS;
    
    CTable<CDouble> m_tableUD;
    CTable<CDouble> m_tableUF;
    CTable<CDouble> m_tableUM;
    CTable<CDouble> m_tablePS;
    
    CMatrix<CDouble> m_matrixCD;
    CMatrix<CDouble> m_matrixCF;
    CMatrix<CDouble> m_matrixCM;
    
    CMatrix<CRange> m_matrixMinMaxXD;
    CMatrix<CRange> m_matrixMinMaxXF;
    CMatrix<CRange> m_matrixMinMaxXM;
    
    void Init();
    
    int Check(double* pSolution, int solutionSize);
    SSolution ParseSolution(double* pSolution);
    
public:
    CMscnProblem();
    
//---setters---
    void SetSizeD(int dCount);
    void SetSizeF(int fCount);
    void SetSizeM(int mCount);
    void SetSizeS(int sCount);
    
    void SetInSD(CDouble value, int offset);
    void SetInSF(CDouble value, int offset);
    void SetInSM(CDouble value, int offset);
    void SetInSS(CDouble value, int offset);
    void SetInUD(CDouble value, int offset);
    void SetInUF(CDouble value, int offset);
    void SetInUM(CDouble value, int offset);
    void SetInPS(CDouble value, int offset);
    
    void SetInMinMaxXD(CDouble value, int offsetX, int offsetY, int minOrMax);
    void SetInMinMaxXF(CDouble value, int offsetX, int offsetY, int minOrMax);
    void SetInMinMaxXM(CDouble value, int offsetX, int offsetY, int minOrMax);
    
//---getters---
    double GetKT(CMatrix<CDouble>& xd, CMatrix<CDouble>& xf, CMatrix<CDouble>& xm);
    double GetKU(CMatrix<CDouble>& xd, CMatrix<CDouble>& xf, CMatrix<CDouble>& xm);
    double GetP(CMatrix<CDouble>& xm);
    CTable<CRange> GetMinMaxSolutionTable();
    
//---required methods---
    
    double GetQuality(double* pSolution, int& error, int solutionSize);
    bool ConstraintsSatisfied(double* pSolution, int& error, int solutionSize);
    
    bool Randomize(CRandom& random);
    int GetSolutionSize();

//---files handler methods (read, write)---
    
    bool Store(CArchive& archive);
    bool Load(CArchive& archive);
};

inline CArchive& operator >> (CArchive& archive, CMscnProblem& problem) {
    
    problem.Load(archive);
    return archive;
}

inline CArchive& operator << (CArchive& archive, CMscnProblem& problem) {
    
    problem.Store(archive);
    return archive;
}
#endif /* MscnProblem_h */
