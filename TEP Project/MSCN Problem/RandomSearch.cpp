//
//  RandomSearch.cpp
//  TEP Project
//
//  Created by Michał Raszczuk on 03/01/2020.
//  Copyright © 2020 Michał Raszczuk. All rights reserved.
//

#include "RandomSearch.h"

CRandomSearch::CRandomSearch()
: m_pProblem(NULL) {
    
}

CRandomSearch::CRandomSearch(CMscnProblem* problem)
: m_pProblem(problem) {
    
}

CSolution* CRandomSearch::GenerateValidSolution(CRandom& random, int maxIterate = DEFAULT_MAX_ITERATE) {
    
    size_t sizeSolution = m_pProblem->GetSolutionSize();
    CSolution* pSolution = new CSolution(sizeSolution, m_pProblem->GetSizeD(), m_pProblem->GetSizeF(), m_pProblem->GetSizeM(), m_pProblem->GetSizeS());
    
    bool isValid = false;
    int error = 0;
    int nTrial = maxIterate;
    
    while(nTrial-- && !isValid) {
        
        int i = 0;
        double* pe = pSolution->GetEndPtr();
        
        for(double* p = pSolution->GetBeginPtr(); p<pe; ++p, ++i) {
            
            CRange& range = m_pProblem->GetSolutionConstraint( i );
            *p = random.SetRange(range.GetMin().Get(), range.GetMax().Get()).Generate();
        }
        
        isValid = m_pProblem->ConstraintsSatisfied(pSolution->GetBeginPtr(), sizeSolution, error);
    }
    
    if(!isValid)
        return pSolution;
    
    delete pSolution;
    return NULL;
}
