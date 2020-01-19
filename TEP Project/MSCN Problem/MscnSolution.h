//
//  MscnSolution.hpp
//  TEP Project
//
//  Created by Michał Raszczuk on 05/01/2020.
//  Copyright © 2020 Michał Raszczuk. All rights reserved.
//

#ifndef MscnSolution_h
#define MscnSolution_h

#include <stdio.h>
#include "MatrixHelper.h"
#include "Archive.h"

class CSolution {
private:
    void FillMatrixes();
public:
    double* m_pSolution;
    size_t m_sizeSolution;
    
    size_t m_sizeD;
    size_t m_sizeF;
    size_t m_sizeM;
    size_t m_sizeS;
    
    CMatrixHelper m_matrixXD;
    CMatrixHelper m_matrixXF;
    CMatrixHelper m_matrixXM;
    
    CSolution(size_t sizeSolution, size_t sizeD, size_t sizeF, size_t sizeM, size_t sizeS);
    CSolution(const CSolution& otherSolution);
    ~CSolution();
    
    double* GetEndPtr();
    double* GetBeginPtr();
    
    int Store(CArchive& archive);
};

inline CArchive& operator << (CArchive& archive, CSolution& solution) {
    
    solution.Store(archive);
    return archive;
}

#endif /* MscnSolution_hpp */
