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

class CRandomSearch {
private:
    CMscnProblem* m_pProblem;
    
public:
    CRandomSearch();
    CRandomSearch(CMscnProblem* problem);
    
    bool SetProblem(CMscnProblem* problem);
    CMscnProblem GetProblem();
    
    CTable<CDouble> GenerateValidSolution(CRandom& random);
    CTable<CDouble> GenerateSolution(CRandom& random);
    CTable<CDouble> GetBestSolution(int maxIterationCount, CRandom &random);
};

#endif /* RandomSearch_hpp */
