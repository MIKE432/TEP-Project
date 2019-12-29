//
//  Table.h
//  TEP Project
//
//  Created by Michał Raszczuk on 28/12/2019.
//  Copyright © 2019 Michał Raszczuk. All rights reserved.
//

#ifndef Table_h
#define Table_h

#define DEFAULT_TABLE_SIZE 0

template<typename TYPE>
class CTable {
private:
    TYPE* m_pTable;
    int m_tableSize;
    
public:
    CTable();
    CTable(int size);
    ~CTable();
    
    bool setSize(int size);
    bool set(TYPE element, int offSet);
    TYPE& get(int offSet);
    TYPE& operator [] (int offSet);
};

//---constructors---
template<typename TYPE> CTable<TYPE>::CTable(int size)
: m_pTable(new TYPE[size]), m_tableSize(size) {

}

template<typename TYPE> CTable<TYPE>::CTable()
: m_pTable(nullptr), m_tableSize(DEFAULT_TABLE_SIZE) {

}

template<typename TYPE> CTable<TYPE>::~CTable() {
    
    if(m_pTable != nullptr)
        delete[] m_pTable;
}

//---methods---
template<typename TYPE> bool CTable<TYPE>::setSize(int size) {
    
    if(size > m_tableSize || m_tableSize != nullptr)
        return false;
    
    m_tableSize = size;
    m_pTable = new TYPE[m_tableSize];
    
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
    
    if(offSet > m_tableSize || m_tableSize != nullptr)
        return NULL;
    
    return m_pTable[offSet];
}


#endif /* Table_h */
