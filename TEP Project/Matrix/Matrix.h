//
//  Matrix.hpp
//  TEP Project
//
//  Created by Michał Raszczuk on 27/12/2019.
//  Copyright © 2019 Michał Raszczuk. All rights reserved.
//

#ifndef Matrix_h
#define Matrix_h

#include <stdio.h>

class CMatrix {
private:
    int** m_matrix;
    
public:
    CMatrix();
    CMatrix(int dimX, int dimY);
    ~CMatrix();
    
    CMatrix& make(int dimX, int dimY);
    void fill(FILE file);
};

#endif /* Matrix_hpp */
