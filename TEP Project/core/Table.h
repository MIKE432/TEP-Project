//
//  Table.h
//  TEP Project
//
//  Created by Michał Raszczuk on 28/12/2019.
//  Copyright © 2019 Michał Raszczuk. All rights reserved.
//

#ifndef Table_h
#define Table_h

#include "Consts.h"
#include "Random.h"
#include "Double.h"
#include "Archive.h"
#include <iostream>

template<typename TYPE>
class CTable {
private:
    TYPE* m_pTable;
    int m_nTableSize;
    
public:
    CTable();
    CTable(int size);
    CTable(const CTable& otherTable);
    ~CTable();
    
    bool Resize(int size);
    int GetSize();
    TYPE& operator [] (int offset);
    
    void operator = (const CTable& otherTable);
    bool Randomize(CRandom& random);
    
    int Store(CArchive& archive);
    int Load(CArchive& archive);
};

//---constructors---
template<typename TYPE> CTable<TYPE>::CTable(int size)
: m_pTable(NULL), m_nTableSize(size) {
    
    if(m_nTableSize > 0)
        m_pTable = new TYPE[m_nTableSize];
}

template<typename TYPE> CTable<TYPE>::CTable()
: m_pTable(NULL), m_nTableSize(DEFAULT_TABLE_SIZE) {
    
    if(m_nTableSize > 0)
        m_pTable = new TYPE[m_nTableSize];
}

template<typename TYPE> CTable<TYPE>::CTable(const CTable& otherTable)
: m_pTable(NULL), m_nTableSize(otherTable.m_nTableSize) {
    
    m_pTable = new TYPE[m_nTableSize];
    
    for(int i = 0; i < m_nTableSize; i++) {
        m_pTable[i] = otherTable.m_pTable[i];
    }
}

template<typename TYPE> void CTable<TYPE>::operator = (const CTable<TYPE>& otherTable) {
    
    if(m_pTable != NULL)
        delete[] m_pTable;
    
    m_pTable = new TYPE[m_nTableSize];
    
    for(int i = 0; i < m_nTableSize; i++) {
        m_pTable[i] = otherTable.m_pTable[i];
    }
}

template<typename TYPE> CTable<TYPE>::~CTable() {
    
    if(m_pTable != NULL)
        delete[] m_pTable;

}

//---methods---
template<typename TYPE> bool CTable<TYPE>::Resize(int size) {
    
    if(m_pTable != NULL)
        delete [] m_pTable;
    
    m_nTableSize = size;
    
    if(m_nTableSize > 0)
        m_pTable = new TYPE[m_nTableSize];
    else
        m_pTable = NULL;

    return true;
}

template<typename TYPE> int CTable<TYPE>::GetSize() {
    
    return m_nTableSize;
}

template<typename TYPE> TYPE& CTable<TYPE>::operator[] (int offset) {
    
    return m_pTable[offset];
}

template<typename TYPE> bool CTable<TYPE>::Randomize(CRandom& random) {
    
    for(int i = 0; i < m_nTableSize; i++) {
        
        m_pTable[i].Randomize(random);
    }
    
    return true;
}

template<typename TYPE> int CTable<TYPE>::Store(CArchive &archive) {
    
    for(int i = 0; i < m_nTableSize; i++) {
        
        m_pTable[i].Store(archive);
        archive >> space;
    }
    
    archive << endln << endln;
    
    return NO_ERROR;
}

template<typename TYPE> int CTable<TYPE>::Load(CArchive &archive) {

    for(int i = 0; i < m_nTableSize; i++) {
        
        m_pTable[i].Load(archive);
        archive << space;
    }
    
    archive >> endln >> endln;
    
    return NO_ERROR;
}

template <typename TYPE>
inline CArchive& operator << (CArchive& archive, CTable<TYPE>& table) {
    
    table.Store(archive);
    return archive;
}
template <typename TYPE>
inline CArchive& operator >> (CArchive& archive, CTable<TYPE>& table) {
    
    table.Load(archive);
    return archive;
}

inline double* ConvertToSolutionTable(CTable<CDouble> tableToConvert) {
    
    double* pDoubleTable = new double[tableToConvert.GetSize()];
    
    for(int i = 0; i < tableToConvert.GetSize(); i++) {
        pDoubleTable[i] = tableToConvert[i].Get();
    }
    
    return pDoubleTable;
}
#endif /* Table_h */
