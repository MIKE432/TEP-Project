//
//  RandomSearch.cpp
//  TEP Project
//
//  Created by Michał Raszczuk on 03/01/2020.
//  Copyright © 2020 Michał Raszczuk. All rights reserved.
//

#include "RandomSearch.h"

CRandomSearch::CRandomSearch()
: m_pProblem(NULL), COptimizer(NULL) {
    
}

CRandomSearch::CRandomSearch(CProblem* problem)
: m_pProblem(problem), COptimizer(problem) {
    
}

CSolution* CRandomSearch::GenerateSolution(CRandom& random) {


    size_t sizeSolution = m_pProblem->GetSolutionSize();
    CSolution* pSolution = new CSolution(sizeSolution, m_pProblem->GetSizes()[0], m_pProblem->GetSizes()[1], m_pProblem->GetSizes()[2], m_pProblem->GetSizes()[3]);

    int i = 0;
    double* pe = pSolution->GetEndPtr();
    
    for(double* p = pSolution->GetBeginPtr(); p < pe; ++p, ++i) {
        
        CRange& range = m_pProblem->GetSolutionConstraint( i );
        *p = random.SetRange(range.GetMin().Get(), range.GetMax().Get()).Generate();
    }

    return pSolution;
}

double MinDouble(double d1, double d2) {
    if(d1 > d2)
        return d2;
    
    return d1;
}

CSolution* CRandomSearch::GetSolution(CRandom& random) {
    
    size_t sizeSolution = m_pProblem->GetSolutionSize();
    CSolution* pSolution = new CSolution(sizeSolution, m_pProblem->GetSizes()[0], m_pProblem->GetSizes()[1], m_pProblem->GetSizes()[2], m_pProblem->GetSizes()[3]);
        
    double* p = pSolution->GetBeginPtr();
    
    CTable<CDouble> sd = ((CMscnProblem*)m_pProblem)->GetTableSD();
    CTable<CDouble> sf = ((CMscnProblem*)m_pProblem)->GetTableSF();
    CTable<CDouble> sm = ((CMscnProblem*)m_pProblem)->GetTableSM();
    CTable<CDouble> ss = ((CMscnProblem*)m_pProblem)->GetTableSS();
    
    CMatrixHelper xd;
    CMatrixHelper xf;
    CMatrixHelper xm;
    
    xd.Attach(p, m_pProblem->GetSizes()[0], m_pProblem->GetSizes()[1]);
    
    for(int i = 0; i < m_pProblem->GetSizes()[0]; ++i) {
        
        for(int j = 0; j < m_pProblem->GetSizes()[1]; j++, ++p) {
            
            *p = random.SetRange(ZERO, sd[i].Get()).Generate();
            sd[i] = sd[i] - *p;
        }
    }
    
    xf.Attach(p, m_pProblem->GetSizes()[1], m_pProblem->GetSizes()[2]);
    
    for(int i = 0; i < m_pProblem->GetSizes()[1]; ++i) {
        
        for(int j = 0; j < m_pProblem->GetSizes()[2]; j++, ++p) {
            
            *p = random.SetRange(ZERO, sf[i].Get()).Generate();
            sf[i] = sf[i] - *p;
        }
    }
    
    xm.Attach(p, m_pProblem->GetSizes()[2], m_pProblem->GetSizes()[3]);
    
    for(int i = 0; i < m_pProblem->GetSizes()[2]; ++i) {
        
        for(int j = 0; j < m_pProblem->GetSizes()[3]; j++, ++p) {
            
            *p = random.SetRange(ZERO, MinDouble(sm[i].Get(), ss[j].Get())).Generate();
            sm[i] = sm[i] - *p;
            ss[j] = ss[j] - *p;
        }
    }
    
    
    int error;
    m_pProblem->ConstraintsSatisfied(pSolution->GetBeginPtr(), m_pProblem->GetSolutionSize(), error);
    return pSolution;
}
