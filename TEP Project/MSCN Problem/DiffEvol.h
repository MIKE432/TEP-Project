//
//  DiffEvol.hpp
//  TEP Project
//
//  Created by Michał Raszczuk on 13/01/2020.
//  Copyright © 2020 Michał Raszczuk. All rights reserved.
//

#ifndef DiffEvol_h
#define DiffEvol_h

#include <stdio.h>

#include "MscnSolution.h"
#include "MscnProblem.h"
#include "Table.h"
#include "Random.h"
#include "RandomSearch.h"
#include "Consts.h"

class CDiffEvol {
private:
    CMscnProblem* m_pProblem;
    CTable<CSolution*> m_tablePSolutions;
    bool InitPopulation(CRandom& random, CRandomSearch& randomSearch, int populationLength);
    CSolution* GetRandomInd(CRandom& random);
    bool AreIndividualsDifferent(CSolution* ind, CSolution* baseInd, CSolution* addInd0, CSolution* addInd1);
    void CorrectGenotype(CRandom& random, CRandomSearch& randomSearch);

public:
    CDiffEvol();
    CDiffEvol(CMscnProblem* problem);
    CDiffEvol(CMscnProblem* problem, int tableSolutionSize);
    ~CDiffEvol();

    CSolution* GetBestSolution(CRandom& random, CRandomSearch& randomSearch);
    
    
    
};


#endif /* DiffEvol_hpp */
