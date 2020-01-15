//
//  DiffEvol.cpp
//  TEP Project
//
//  Created by Michał Raszczuk on 13/01/2020.
//  Copyright © 2020 Michał Raszczuk. All rights reserved.
//

#include "DiffEvol.h"

bool CDiffEvol::InitPopulation(CRandom& random, CRandomSearch& randomSearch, int populationLength) {
    
    if(populationLength <= 0)
        return false;
    
    for(int i = 0; i < m_tablePSolutions.GetSize(); i++) {
        
        if(m_tablePSolutions[i] != NULL)
            delete m_tablePSolutions[i];
        
        m_tablePSolutions[i] = randomSearch.GenerateSolution(random);
    }
    
    return true;
}

CSolution* CDiffEvol::GetRandomInd(CRandom& random) {
    
    return m_tablePSolutions[(int)random.SetRange(ZERO, m_tablePSolutions.GetSize()).Generate()];
}

bool CDiffEvol::AreIndividualsDifferent(CSolution* ind, CSolution* baseInd, CSolution* addInd0, CSolution* addInd1) {
    
    int similarity = 0;
    
    double dIndActualNumber = 0.0;
    double dBaseIndActualNumber = 0.0;
    double dAddInd0ActualNumber = 0.0;
    double dAddInd1ActualNumber = 0.0;
    
    for(int i = 0; i < ind->m_sizeSolution; i++) {
        dIndActualNumber = ind->GetBeginPtr()[0];
        dBaseIndActualNumber = baseInd->GetBeginPtr()[0];
        dAddInd0ActualNumber = addInd0->GetBeginPtr()[0];
        dAddInd1ActualNumber = addInd1->GetBeginPtr()[0];
        
        if((dIndActualNumber == dBaseIndActualNumber) && (dIndActualNumber == dAddInd0ActualNumber) && (dIndActualNumber == dAddInd1ActualNumber) && (dBaseIndActualNumber == dAddInd0ActualNumber) && (dBaseIndActualNumber == dAddInd1ActualNumber) && (dAddInd0ActualNumber == dAddInd1ActualNumber))
            similarity++;
    }
    
    return similarity != (ind->m_sizeSolution);
}

CDiffEvol::CDiffEvol() {
    
}

CDiffEvol::CDiffEvol(CMscnProblem* problem)
:m_pProblem(problem) {
    
    m_tablePSolutions = CTable<CSolution*>(DEFAULT_POPULATION_LENGTH);
    
    for(int i = 0; i < m_tablePSolutions.GetSize(); i++) {
        m_tablePSolutions[i] = NULL;
    }
    
}

CDiffEvol::CDiffEvol(CMscnProblem* problem, int tableSolutionSize)
: m_pProblem(problem) {
    
    m_tablePSolutions = CTable<CSolution*>(tableSolutionSize);
    
    for(int i = 0; i < m_tablePSolutions.GetSize(); i++) {
        m_tablePSolutions[i] = NULL;
    }
}

CDiffEvol::~CDiffEvol() {
    
}

void CDiffEvol::CorrectGenotype(CRandom& random, CRandomSearch& randomSearch) {
    
    InitPopulation(random, randomSearch, DEFAULT_POPULATION_LENGTH);
    
    CSolution* pInd = NULL;
    CSolution* pBaseInd = NULL;
    CSolution* pAddInd0 = NULL;
    CSolution* pAddInd1 = NULL;
    CSolution* pNewInd = NULL;
    
    double dValue = 0.0;
    int error = 0;
    
    for(int i = 0; i < DEFAULT_CORRECTION_TRIES; i++) {
        
        for(int j = 0; j < m_tablePSolutions.GetSize(); j++) {
            
            pInd = m_tablePSolutions[j];
            pBaseInd = GetRandomInd(random);
            pAddInd0 = GetRandomInd(random);
            pAddInd1 = GetRandomInd(random);
            
            if(AreIndividualsDifferent(pInd, pBaseInd, pAddInd0, pAddInd1)) {
                
                pNewInd = new CSolution(m_pProblem->GetSolutionSize(), m_pProblem->GetSizeD(), m_pProblem->GetSizeF(), m_pProblem->GetSizeM(), m_pProblem->GetSizeS());
                
                for(int genOffset = 0; genOffset < pInd->m_sizeSolution; genOffset++) {
                    
                    if(random.SetRange(0, 1).Generate() < DEFAULT_CROSS_PROPABILITY) {
                        
                       dValue = pBaseInd->GetBeginPtr()[genOffset] + (DEFAULT_DIFF_WEIGHT * (pAddInd0->GetBeginPtr()[genOffset] - pAddInd1->GetBeginPtr()[genOffset]));
                        
                        CRange range = m_pProblem->GetSolutionConstraint(genOffset);
                        
                        if(dValue < range.GetMin().Get())
                            dValue = range.GetMin().Get();
                        else if(dValue > range.GetMax().Get())
                            dValue = range.GetMax().Get();
                        
                        pNewInd->GetBeginPtr()[genOffset] = dValue;
                        
                    } else
                        pNewInd->GetBeginPtr()[genOffset] = pInd->GetBeginPtr()[genOffset];
                }
                
                double dNewQuality = m_pProblem->GetQuality(pNewInd->GetBeginPtr(), pNewInd->m_sizeSolution, error);
                
                double dQuality = m_pProblem->GetQuality(pInd->GetBeginPtr(), pInd->m_sizeSolution, error);
                
                if(dNewQuality >= dQuality && m_pProblem->ConstraintsSatisfied(pNewInd->GetBeginPtr(), pNewInd->m_sizeSolution, error)) {
                    
                    delete pInd;
                    m_tablePSolutions[j] = pNewInd;
                    
                } else
                    delete pNewInd;
            }
        }
    }
}

CSolution* CDiffEvol::GetBestSolution(CRandom& random, CRandomSearch& randomSearch)  {
    
    CorrectGenotype(random, randomSearch);
    CSolution* bestSolution = m_tablePSolutions[0];
    
    int error = 0;
    double dCurrentValue = 0.0;
    double dBestValue = m_pProblem->ConstraintsSatisfied(bestSolution->GetBeginPtr(), bestSolution->m_sizeSolution, error);

    for(int i = 1; i < m_tablePSolutions.GetSize(); i++) {
        
        dCurrentValue = m_pProblem->ConstraintsSatisfied(m_tablePSolutions[i]->GetBeginPtr(), m_tablePSolutions[i]->m_sizeSolution, error);
        
        if(dBestValue < dCurrentValue) {
            bestSolution = m_tablePSolutions[i];
            dBestValue = dCurrentValue;
        }
    }
    
    
    return bestSolution;
}
