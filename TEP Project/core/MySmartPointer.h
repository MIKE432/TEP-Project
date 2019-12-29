//
//  CMySmartPointer.h
//  labolatoria7
//
//  Created by Michał Raszczuk on 26/11/2019.
//  Copyright © 2019 Michał Raszczuk. All rights reserved.
//

#ifndef MySmartPointer_h
#define MySmartPointer_h

template<typename TYPE> class CMySmartPointer {
 
protected:
    
    struct CData {
        
        int m_nRef;
        TYPE* m_pPointer;
        
        CData(TYPE* pPointer);
        ~CData();
    };
    
    CData* m_pData;
    
public:
    
    CMySmartPointer(TYPE* pPointer);
    CMySmartPointer(const CMySmartPointer& oPointer);
    ~CMySmartPointer();
    
    
    void operator = (CMySmartPointer& cOtherSmartPointer);
    void operator = (TYPE* pcOtherPointer);
    TYPE* operator -> ();
    TYPE& operator * ();
};

template<typename TYPE> CMySmartPointer<TYPE>::CData::CData(TYPE* pPointer)
: m_nRef(1), m_pPointer(pPointer) {

}

template<typename TYPE> CMySmartPointer<TYPE>::CData::~CData() {
    delete m_pPointer;
}

template<typename TYPE> CMySmartPointer<TYPE>::CMySmartPointer(TYPE* pPointer)
: m_pData(NULL) {
    m_pData = new CData( pPointer );
}

template<typename TYPE> CMySmartPointer<TYPE>::CMySmartPointer(const CMySmartPointer& rPointer)
: m_pData(NULL) {
    
    if(rPointer.m_pData) {
        
        m_pData = rPointer.m_pData;
        m_pData->m_nRef++;
    }
}

template<typename TYPE> CMySmartPointer<TYPE>::~CMySmartPointer() {
   
    if( m_pData && --m_pData->m_nRef == 0 )
       delete m_pData;
}


template<typename TYPE> void CMySmartPointer<TYPE>::operator = (CMySmartPointer& cOtherSmartPointer) {
    
    if( m_pData && --m_pData->m_nRef == 0 )
       delete m_pData;
    
    m_pData = cOtherSmartPointer.m_pData;
    m_pData->m_nRef++;
}

template<typename TYPE> void CMySmartPointer<TYPE>::operator = (TYPE* pcOtherPointer) {
    
    if( m_pData && --m_pData->m_nRef == 0 )
       delete m_pData;
    
    m_pData = new CData(pcOtherPointer);
}

template<typename TYPE> TYPE* CMySmartPointer<TYPE>::operator -> () {
    
    return m_pData->m_pPointer;
}

template<class TYPE> TYPE& CMySmartPointer<TYPE>::operator * () {
    
    return *m_pData->m_pPointer;
}


#endif /* CMySmartPointer_h */
