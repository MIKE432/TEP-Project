//
//  MatrixHelper.h
//  TEP Project
//
//  Created by Michał Raszczuk on 05/01/2020.
//  Copyright © 2020 Michał Raszczuk. All rights reserved.
//

#ifndef MatrixHelper_h
#define MatrixHelper_h
#include "Archive.h"

class CMatrixHelper {
public:
    double* m_pData;
    size_t m_row;
    size_t m_col;
    
    
    CMatrixHelper()
    : m_pData(NULL), m_row(0), m_col(0) {
        
    }
    
    CMatrixHelper(double* pData, size_t row, size_t col)
    : m_pData(pData), m_row(row), m_col(col) {
        
    }
    
    void Attach(double* pData, size_t row, size_t col) {
        
        m_pData = pData;
        m_row = row;
        m_col = col;
    }
    
    double Get(size_t r, size_t c) {
        
        return *(m_pData+(r* m_col + c));
    }
    
    double sumInRow(int col) {
        
        double sum = 0;
        
        for(int row = 0; row < m_row; row++) {
            
            sum += Get(row, col);
        }
        
        return sum;
    }
    
    double sumInColumn(int row) {
        
        double sum = 0;
        
        for(int col = 0; col < m_col; col++) {
            
            sum += Get(row, col);
        }
        
        return sum;
    }
    
    int Store(CArchive& archive) {
        
        for(int x = 0; x < m_row; x++) {
            
            for(int y = 0; y < m_col; y++) {
                
                archive << Get(x, y) << space;
            }
            
            archive << endln;
        }
        
        archive << endln;
        
        return NO_ERROR;
    }
    
};

inline CArchive& operator << (CArchive& archive, CMatrixHelper& matrix) {
    
    matrix.Store(archive);
    return archive;
}

#endif /* MatrixHelper_h */
