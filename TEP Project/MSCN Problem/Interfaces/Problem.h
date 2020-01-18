//
//  Problem.h
//  TEP Project
//
//  Created by Michał Raszczuk on 15/01/2020.
//  Copyright © 2020 Michał Raszczuk. All rights reserved.
//

#ifndef Problem_h
#define Problem_h

#include "Table.h"

class CProblem {
protected:
    CTable<size_t> m_tableSizes;
public:    
    virtual bool ConstraintsSatisfied(double* pSolution, size_t sizeSolution, int& error) = 0;
    virtual double GetQuality(double* pSolution, size_t sizeSolution, int& error) =  0;
    virtual CRange& GetSolutionConstraint(int i) = 0;
    virtual size_t GetSolutionSize() = 0;
    
    CTable<size_t> GetSizes() {
        return m_tableSizes;
    }
    
};


#endif /* Problem_h */
