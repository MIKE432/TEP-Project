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
#include "MatrixHelper.h"
#include "Problem.h"
#include <float.h>

class CMscnProblem: public CProblem {
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
    
    int ValidateSolution(double* pSolution, size_t sizeSolution);
    double GetBottleNeck();
    
public:
    CMscnProblem();
    
    void GenerateInstance(int nInstanceSeed);
    
//---setters---
    
    void SetSizeD(int sizeD);
    void SetSizeF(int sizeF);
    void SetSizeM(int sizeM);
    void SetSizeS(int sizeS);
    
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
    
    double GetKT(CMatrixHelper& xd, CMatrixHelper& xf, CMatrixHelper& xm);
    double GetKU(CMatrixHelper& xd, CMatrixHelper& xf, CMatrixHelper& xm);
    double GetP(CMatrixHelper& xm);
    CRange& GetSolutionConstraint(int i);
    
    int GetSizeD() { return m_nSizeD; }
    int GetSizeF() { return m_nSizeF; }
    int GetSizeM() { return m_nSizeM; }
    int GetSizeS() { return m_nSizeS; }
    
    CTable<CDouble> GetTableSD() { return m_tableSD; }
    CTable<CDouble> GetTableSF() { return m_tableSF; }
    CTable<CDouble> GetTableSM() { return m_tableSM; }
    CTable<CDouble> GetTableSS() { return m_tableSS; }
    
//---required methods---
    
    double GetQuality(double* pSolution, size_t sizeSolution, int& error);
    bool ConstraintsSatisfied(double* pSolution, size_t sizeSolution, int& error);
    
    bool Randomize(CRandom& random);
    size_t GetSolutionSize();
    
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
