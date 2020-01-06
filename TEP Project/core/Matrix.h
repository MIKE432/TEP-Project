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
#include <string>
#include "MySmartPointer.h"
#include "Consts.h"
#include "Table.h"
#include "Double.h"
#include "Random.h"
#include "Archive.h"

using namespace std;

template<typename TYPE>
class CMatrix {
private:
    TYPE** m_ppMatrix;
    int m_nSizeX;
    int m_nSizeY;
    
public:
    CMatrix();
    CMatrix(const CMatrix& otherMatrix);
    CMatrix(int sizeX, int dimY);
    ~CMatrix();
    
    bool set(const TYPE& element, int offsetX, int offsetY);
    bool Resize(int sizeX, int sizeY);
    TYPE& get(int offsetX, int offsetY) const;
    CDouble sumInRowOrColumn(char flag, int rowOrColumnNumber);
    bool rowSumHigherThanZero(int row);
    double getXSize() { return m_nSizeX; }
    double getYSize() { return m_nSizeY; }
    TYPE* operator [] (int offsetX);
    void operator = (const CMatrix& otherMatrix);
    
    bool Randomize(CRandom& random);
    int Store(CArchive& archive);
    int Load(CArchive& archive);
};

//---constructors---
template<typename TYPE> CMatrix<TYPE>::CMatrix()
:m_ppMatrix(NULL), m_nSizeX(DEFAULT_DIM_X), m_nSizeY(DEFAULT_DIM_Y) {
    
    m_ppMatrix = new TYPE*[m_nSizeX];
    
    for(int i = 0; i < m_nSizeX; i++) {
        
        m_ppMatrix[i] = new TYPE[m_nSizeY];
    }
}

template<typename TYPE> CMatrix<TYPE>::CMatrix(const CMatrix& otherMatrix)
: m_ppMatrix(NULL), m_nSizeX(otherMatrix.m_nSizeX), m_nSizeY(otherMatrix.m_nSizeY) {
    
    m_ppMatrix = new TYPE*[m_nSizeX];
    
    for(int i = 0; i < m_nSizeX; i++) {
        
        m_ppMatrix[i] = new TYPE[m_nSizeY];
    }
    
    for(int x = 0; x < m_nSizeX; x++) {
        for(int y = 0; y < m_nSizeY; y++) {
            m_ppMatrix[x][y] = otherMatrix.get(x, y);
        }
    }
}


template<typename TYPE> CMatrix<TYPE>::CMatrix(int sizeX, int sizeY)
: m_ppMatrix(NULL), m_nSizeX(sizeX), m_nSizeY(sizeY) {
    
    m_ppMatrix = new TYPE*[m_nSizeX];
    
    for(int i = 0; i < m_nSizeX; i++) {
        
        m_ppMatrix[i] = new TYPE[m_nSizeY];
    }
}

template<typename TYPE> CMatrix<TYPE>::~CMatrix() {
    
    if(m_ppMatrix != NULL) {
        
        for(int i = 0; i < m_nSizeX; i++) {
            delete[] m_ppMatrix[i];
        }
        
        delete[] m_ppMatrix;
    }
}

//---methods---
template<typename TYPE> bool CMatrix<TYPE>::Resize(int sizeX, int sizeY) {
    
    if(sizeX < 0 || sizeY < 0)
        return false;
    
    TYPE** ppNewMatrix = new TYPE*[ sizeX ];
    for(int i = 0; i < sizeX; i++) {
        ppNewMatrix[i] = new TYPE[ sizeY ];
    }

    if(m_ppMatrix != NULL) {
        
        for(int i = 0; i < m_nSizeX; i++) {
            delete[] m_ppMatrix[i];
        }
        
        delete[] m_ppMatrix;
    }
        
    m_nSizeX = sizeX;
    m_nSizeY = sizeY;
    m_ppMatrix = ppNewMatrix;
    
    return true;
}

template<typename TYPE> bool CMatrix<TYPE>::set(const TYPE& element, int offsetX, int offsetY) {
    
    if(offsetX > m_nSizeX || offsetY > m_nSizeY)
        return false;
    
    m_ppMatrix[offsetX][offsetY] = element;
    
    return true;
}

template<typename TYPE> void CMatrix<TYPE>::operator = (const CMatrix& otherMatrix) {
    
    if(m_ppMatrix == NULL) {
        for(int y = 0; y < m_nSizeY; y++)
            delete[] m_ppMatrix[y];
        
        delete[] m_ppMatrix;
    }
    
    m_nSizeX = otherMatrix.m_nSizeX;
    m_nSizeY = otherMatrix.m_nSizeY;
    
    for(int i = 0; i < m_nSizeX; i++) {
        
        m_ppMatrix[i] = new TYPE[m_nSizeY];
    }
    
    for(int x = 0; x < m_nSizeX; x++) {
        for(int y = 0; y < m_nSizeY; y++) {
            m_ppMatrix[x][y] = otherMatrix.get(x, y);
        }
    }
}

template<typename TYPE> TYPE& CMatrix<TYPE>::get(int offsetX, int offsetY) const {
    
    return m_ppMatrix[offsetX][offsetY];
}


template<typename TYPE> TYPE* CMatrix<TYPE>::operator [](int offsetX) {
    
    return m_ppMatrix[offsetX];
}

template<typename TYPE> bool CMatrix<TYPE>::rowSumHigherThanZero(int row) {
    
    for(int i = 0; i < m_nSizeY; i++) {
        
        if(m_ppMatrix[row][i] > 0)
            return true;
    }
    
    return false;
}

template<typename TYPE> CDouble CMatrix<TYPE>::sumInRowOrColumn(char flag, int rowOrColumnNumber) {
    
    CDouble result = 0;
    
    if(flag == 'c') {
        
        for(int i = 0; i < m_nSizeY; i++) {
            
            result += m_ppMatrix[rowOrColumnNumber][i];
        }
        
        return result;
        
    } else if(flag == 'r') {
        
        for(int i = 0; i < m_nSizeX; i++) {
            
            result += m_ppMatrix[i][rowOrColumnNumber];
        }
        
        return result;
        
    } else
        return WRONG_ARGUMENT_ERROR;
    
}

template<typename TYPE> bool CMatrix<TYPE>::Randomize(CRandom& random) {
    
    for(int x = 0; x < m_nSizeX; x++) {
        
        for(int y = 0; y < m_nSizeY; y++) {
            
            m_ppMatrix[x][y].Randomize(random);
        }
    }
    
    return true;
}

template<typename TYPE> int CMatrix<TYPE>::Store(CArchive &archive) {
    
    for(int x = 0; x < m_nSizeX; x++) {
        
        for(int y = 0; y < m_nSizeY; y++) {
            
            archive << m_ppMatrix[x][y] << space;
        }
        
        archive << endln;
    }
    
    archive << endln;
    return NO_ERROR;
}

template<typename TYPE> int CMatrix<TYPE>::Load(CArchive &archive) {
    
    for(int x = 0; x < m_nSizeX; x++) {
        
        for(int y = 0; y < m_nSizeY; y++) {
            
            archive >> m_ppMatrix[x][y] >> space;
        }
        
        archive >> endln;
    }
    
    archive >> endln;
    return NO_ERROR;
}


template <typename TYPE>
inline CArchive& operator << (CArchive& archive, CMatrix<TYPE>& matrix) {
    
    matrix.Store(archive);
    return archive;
}
template <typename TYPE>
inline CArchive& operator >> (CArchive& archive, CMatrix<TYPE>& matrix) {
    
    matrix.Load(archive);
    return archive;
}

#endif /* Matrix_hpp */
