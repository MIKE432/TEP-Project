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
#include "Optimizer.h"

class CDiffEvol: public COptimizer {
private:
    CProblem* m_pProblem;
    CRandomSearch* m_RandomSearch;
    CTable<CSolution*> m_tablePSolutions;
    
    bool InitPopulation(CRandom& random, CRandomSearch& randomSearch, int populationLength);
    CSolution* GetRandomInd(CRandom& random);
    bool AreIndividualsDifferent(CSolution* ind, CSolution* baseInd, CSolution* addInd0, CSolution* addInd1);
    void CorrectGenotype(CRandom& random);

public:
    CDiffEvol();
    CDiffEvol(CProblem* problem, CRandomSearch* randomSearch);
    CDiffEvol(CProblem* problem, CRandomSearch* randomSearch, int tableSolutionSize);
    ~CDiffEvol();

    CSolution* GetSolution(CRandom& random);
    
    
    
};


#endif /* DiffEvol_hpp */
