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

template<typename TYPE>
class CTable {
private:
    TYPE* m_pTable;
    int m_tableSize;
    
public:
    CTable();
    CTable(int size);
    ~CTable();
    
    bool resize(int size);
    bool set(TYPE element, int offSet);
    TYPE& get(int offSet);
    TYPE& operator [] (int offSet);
    
    bool randomize(const CRandom& random);
};

//---constructors---
template<typename TYPE> CTable<TYPE>::CTable(int size)
: m_pTable(NULL), m_tableSize(size) {
    
    if(m_tableSize > 0)
        m_pTable = new TYPE[m_tableSize];
}

template<typename TYPE> CTable<TYPE>::CTable()
: m_pTable(NULL), m_tableSize(DEFAULT_TABLE_SIZE) {
    
    if(m_tableSize > 0)
        m_pTable = new TYPE[m_tableSize];
}

template<typename TYPE> CTable<TYPE>::~CTable() {
    
    if(m_pTable != NULL)
        delete[] m_pTable;

}

//---methods---
template<typename TYPE> bool CTable<TYPE>::resize(int size) {
    
    if(m_pTable != NULL)
        delete [] m_pTable;
    
    m_tableSize = size;
    
    if(m_tableSize > 0)
        m_pTable = new TYPE[m_tableSize];
    else
        m_pTable = NULL;

    return true;
}

template<typename TYPE> bool CTable<TYPE>::set(TYPE element, int offSet) {
    
    if(offSet > m_tableSize || m_tableSize != nullptr)
        return false;
    
    m_pTable[offSet] = element;
    
    return true;
}

template<typename TYPE> TYPE& CTable<TYPE>::get(int offSet) {
    
    if(offSet > m_tableSize || m_tableSize != nullptr)
        return NULL;
    
    return m_pTable[offSet];
}

template<typename TYPE> TYPE& CTable<TYPE>::operator[](int offSet) {
    
    return m_pTable[offSet];
}

template<typename TYPE> bool CTable<TYPE>::randomize(const CRandom &random) {
    
    return true;
}


#endif /* Table_h */
