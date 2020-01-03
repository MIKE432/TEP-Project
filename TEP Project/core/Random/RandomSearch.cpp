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

CRandomSearch::CRandomSearch(CMscnProblem* problem) {
    
    m_pProblem = problem;
}

bool CRandomSearch::SetProblem(CMscnProblem* problem) {
    
    m_pProblem = problem;
    return true;
}

CMscnProblem CRandomSearch::GetProblem() {
    
    return *m_pProblem;
}

CTable<CDouble> CRandomSearch::GenerateSolution(CRandom& random) {
    
//    if(m_pProblem == NULL)
//        return NULL;
    
    CTable<CDouble> solution(m_pProblem->GetSolutionSize());
    
    
    for(int i = 0; i < m_pProblem->GetSolutionSize(); i++) {
        solution[i].Randomize(random.SetRange(m_pProblem->GetMinMaxSolutionTable()[i].GetMin().Get(), m_pProblem->GetMinMaxSolutionTable()[i].GetMax().Get()));
    }
    
    return solution;
}

double* ConvertToSolutionTable(CTable<CDouble> tableToConvert) {
    
    double* pDoubleTable = new double[tableToConvert.GetSize()];
    
    for(int i = 0; i < tableToConvert.GetSize(); i++) {
        pDoubleTable[i] = tableToConvert[i].Get();
    }
    
    return pDoubleTable;
}

CTable<CDouble> CRandomSearch::GenerateValidSolution(CRandom& random) {
    
    CTable<CDouble> potentialValidResult;
    
    bool isValid = false;
    int error = 0;
    
    while(!isValid) {
        
        potentialValidResult = GenerateSolution(random);
        isValid = m_pProblem->ConstraintsSatisfied(ConvertToSolutionTable(potentialValidResult), error, m_pProblem->GetSolutionSize());
    }
    
    return potentialValidResult;
}

CTable<CDouble> CRandomSearch::GetBestSolution(int maxIterationCount, CRandom &random) {
    
    CTable<CDouble> bestSolution;
    CDouble bestQuality = 0;
    int error = 0;
    
    while(maxIterationCount--) {
        
        CTable<CDouble> potentialBestSolution = GenerateValidSolution(random);
        CDouble potentialBestQuality = m_pProblem->GetQuality(ConvertToSolutionTable(potentialBestSolution), error, m_pProblem->GetSolutionSize());
        
        if((bestQuality < potentialBestQuality) && error == NO_ERROR) {
            bestQuality = potentialBestQuality;
            bestSolution = potentialBestSolution;
        }
    }
    
    return bestSolution;
}
