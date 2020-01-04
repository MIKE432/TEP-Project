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

//class WC {
//public:
//    static WC CRLF( '\n' );
//    static WC SP( ' ' );
//
//    char m_ch;
//    WC( char ch )
//    : m_ch( ch ) {
//
//    }
//};

class CArchive {
private:
    FILE* m_fFile;
    
public:
    CArchive();
    CArchive(string fileName, string flags);
    ~CArchive();
    
    FILE GetFile();
    int SetFile(string fileName);
    
    int Store(string line);
    int Load();
    
    CArchive& operator << (CArchive& (* fn)(CArchive&));
    CArchive& operator << (char chValue);
    CArchive& operator << (int nValue);
    CArchive& operator << (double dValue);
    CArchive& operator >> (CArchive& (* fn)(CArchive&));
    CArchive& operator >> (char& chValue);
    CArchive& operator >> (int& nValue);
    CArchive& operator >> (double& dValue);
    
};

inline CArchive& endln_r(CArchive& archive) {
    char ch;
    archive >> ch;
    return archive;
}
inline CArchive& endln_w(CArchive& ar) {
    ar<<'\n';
    return ar;
}
inline CArchive& space_r(CArchive& ar) {
    char ch;
    ar>>ch;
    return ar;
}
inline CArchive& space_w(CArchive& ar) {
    ar<<' ';
    return ar;
}

#endif /* Archive_hpp */
