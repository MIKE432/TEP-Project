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

CSolution* CRandomSearch::GetSolution(CRandom& random) {


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



CSolution* CRandomSearch::GenerateSolution(CRandom& random) {
    
    size_t sizeSolution = m_pProblem->GetSolutionSize();
    CSolution* pSolution = new CSolution(sizeSolution, m_pProblem->GetSizes()[0], m_pProblem->GetSizes()[1], m_pProblem->GetSizes()[2], m_pProblem->GetSizes()[3]);
    
    bool isValid = false;
    int error = 0;
    int trial = DEFAULT_MAX_ITERATE;
    
    while(trial-- && !isValid) {
        
        int i = 0;
        double* pe = pSolution->GetEndPtr();
        
        for(double* p = pSolution->GetBeginPtr(); p < pe; ++p, ++i) {
            
            CRange& range = m_pProblem->GetSolutionConstraint( i );
            *p = random.SetRange(range.GetMin().Get(), range.GetMax().Get()).Generate();
        }
        
        isValid = m_pProblem->ConstraintsSatisfied(pSolution->GetBeginPtr(), sizeSolution, error);
    }
    
    if(isValid)
        return pSolution;
    
    delete pSolution;
    
    return NULL;
}
