//
//  RandomSearch.hpp
//  TEP Project
//
//  Created by Michał Raszczuk on 03/01/2020.
//  Copyright © 2020 Michał Raszczuk. All rights reserved.
//

#ifndef RandomSearch_h
#define RandomSearch_h

#include <stdio.h>
#include "MscnProblem.h"
#include "Random.h"
#include "Double.h"
#include "Table.h"
#include "Consts.h"
#include "MscnSolution.h"
#include "Problem.h"
#include "Optimizer.h"

class CRandomSearch: public COptimizer {
private:
    CProblem* m_pProblem;
    
public:
    CRandomSearch();
    CRandomSearch(CProblem* problem);
        
    CSolution* GetSolution(CRandom& random);
    CSolution* GenerateSolution(CRandom& random);
};

#endif /* RandomSearch_hpp */
