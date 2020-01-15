//
//  Archive.hpp
//  TEP Project
//
//  Created by Michał Raszczuk on 01/01/2020.
//  Copyright © 2020 Michał Raszczuk. All rights reserved.
//

#ifndef Archive_h
#define Archive_h

#include <stdio.h>
#include <string>
#include "Consts.h"

using namespace std;

class CArchive {
private:
    FILE* m_fFile;
    bool m_bIsLoadable;
    
public:
    CArchive();
    ~CArchive();
    
    bool Load(string strFileName);
    bool Store(string strFileName);
    
    bool IsLoadable() { return m_bIsLoadable; }
    
    FILE GetFile();
    int SetFile(string fileName);
    
    CArchive& operator << (CArchive& (* fn)(CArchive&));
    CArchive& operator << (const char* pchText);
    CArchive& operator << (char chValue);
    CArchive& operator << (size_t sizeValue);
//    CArchive& operator >> (size_t sizeValue);
    CArchive& operator << (int nValue);
    CArchive& operator << (double dValue);
    CArchive& operator >> (CArchive& (* fn)(CArchive&));
    CArchive& operator >> (char& chValue);
    CArchive& operator >> (int& nValue);
    CArchive& operator >> (double& dValue);
    
    bool IsValidText(const char* pch);
};

inline CArchive& endln(CArchive& archive) {
    
    if(archive.IsLoadable()) {
        char ch;
        archive >> ch;
    } else
        archive << '\n';
    
    return archive;
}

inline CArchive& space(CArchive& archive) {
    
    if(archive.IsLoadable()) {
        char ch;
        archive >> ch;
    } else
        archive << ' ';
    
    return archive;
}

struct ValidText {
    
    const char* pchText;
};

inline ValidText IsValidText(const char* pchText) {
    
    return { pchText };
}

inline CArchive& operator >> (CArchive& archive, ValidText ct) {
    
    if( !archive.IsValidText(ct.pchText) )
        ;
    
    return archive;
}


#endif /* Archive_hpp */
