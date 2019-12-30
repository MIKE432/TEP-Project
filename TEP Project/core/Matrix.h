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
#include "MySmartPointer.h"
#include "Consts.h"

using namespace std;

template<typename TYPE>
class CMatrix {
private:
    TYPE** m_matrix;
    int m_offSetX;
    int m_offSetY;
    
public:
    CMatrix();
    CMatrix(int offSetX, int dimY);
    ~CMatrix();
    
    bool set(const TYPE& element, int offSetX, int offSetY);
    bool resize(int offSetX, int offSetY);
    TYPE& get(int offSetX, int offSetY);
//    void print() {
//        for(int j = 0; j < m_offSetY; j++) {
//            for(int i = 0; i < m_offSetX; i++) {
//
//                cout << m_matrix[i][j];
//            }
//            cout << endl;
//        }
//    }
//
    bool rowSumHigherThanZero(int row);
    double getXSize() { return m_offSetX; }
    double getYSize() { return m_offSetY; }
    TYPE* operator [] (int offSetX);
};

//---constructors---
template<typename TYPE> CMatrix<TYPE>::CMatrix()
: m_matrix(nullptr), m_offSetX(DEFAULT_DIM_X), m_offSetY(DEFAULT_DIM_Y) {

}

template<typename TYPE> CMatrix<TYPE>::CMatrix(int offSetX, int offSetY)
: m_matrix(nullptr), m_offSetX(offSetX), m_offSetY(offSetY) {
    
    m_matrix = new TYPE*[m_offSetX];
    
    for(int i = 0; i < m_offSetX; i++) {
        m_matrix[i] = new TYPE[m_offSetY];
    }
    
}

template<typename TYPE> CMatrix<TYPE>::~CMatrix() {
    
    if(m_matrix != nullptr) {
        
        for(int i = 0; i < m_offSetX; i++) {
            delete[] m_matrix[i];
        }
        
        delete[] m_matrix;
    }
}

//---methods---
template<typename TYPE> bool CMatrix<TYPE>::resize(int sizeX, int sizeY) {
    
    if(sizeX < 0 || sizeY < 0 || m_matrix == nullptr || sizeY == m_offSetY || sizeX == m_offSetX)
        return false;
    
    m_offSetX = sizeX;
    m_offSetY = sizeY;
    
    for(int i = 0; i < m_offSetX; i++) {
        delete[] m_matrix[i];
    }
    
    delete[] m_matrix;
    
    m_matrix = new TYPE*[m_offSetX];
    
    for(int i = 0; i < m_offSetX; i++) {
        m_matrix[i] = new TYPE[m_offSetY];
    }
    
    return true;
}

template<typename TYPE> bool CMatrix<TYPE>::set(const TYPE& element, int offSetX, int offSetY) {
    
    if(offSetX > m_offSetX || offSetY > m_offSetY)
        return false;
    
    m_matrix[offSetX][offSetY] = element;
    
    return true;
}

template<typename TYPE> TYPE& CMatrix<TYPE>::get(int offSetX, int offSetY) {
    
    if(offSetX > m_offSetX || offSetY > m_offSetY)
        return NULL;
    
    return m_matrix[offSetX][offSetY];
}


template<typename TYPE> TYPE* CMatrix<TYPE>::operator [](int offSetX) {
    
    return m_matrix[offSetX];
}

template<typename TYPE> bool CMatrix<TYPE>::rowSumHigherThanZero(int row) {
    
    for(int i = 0; i < m_offSetY; i++) {
        
        if(m_matrix[row][i] > 0)
            return true;
    }
    
    return false;
}

#endif /* Matrix_hpp */
