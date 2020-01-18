//
//  Optimizer.h
//  TEP Project
//
//  Created by Michał Raszczuk on 15/01/2020.
//  Copyright © 2020 Michał Raszczuk. All rights reserved.
//

#ifndef Optimizer_h
#define Optimizer_h
#include "Problem.h"

#include "MscnSolution.h"

class COptimizer {
protected:
    CProblem* m_pProblem;
    
public:
    
    COptimizer(CProblem* problem)
    : m_pProblem(problem) {
        
    }
    
    virtual CSolution* GetSolution(CRandom& random) = 0;
    
};


#endif /* Optimizer_h */
