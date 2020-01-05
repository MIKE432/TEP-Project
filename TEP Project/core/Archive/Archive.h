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
    bool m_bIsLoadable;
public:
    CArchive();
    ~CArchive();
    
    bool Load(string strFileName);
    bool Store(string strFileName);
    
    bool IsLoadable() {
        
        return m_bIsLoadable;
    }
    
    FILE GetFile();
    int SetFile(string fileName);
    
    CArchive& operator << (CArchive& (* fn)(CArchive&));
    CArchive& operator << (const char* pchText);
    CArchive& operator << (char chValue);
    CArchive& operator << (size_t sizeValue);
    CArchive& operator << (int nValue);
    CArchive& operator << (double dValue);
    CArchive& operator >> (CArchive& (* fn)(CArchive&));
    CArchive& operator >> (char& chValue);
    CArchive& operator >> (int& nValue);
    CArchive& operator >> (double& dValue);
    
    string ReadString( size_t len ) {
        string str;
        
        while( len-- )
            str += fgetc( m_fFile );
        
        return str;
    }
    
    bool IsValidText(const char* pch) {
        
        while(*pch!='\0') {
            
            if( *pch!=(char)fgetc(m_fFile))
                return false;
            ++pch;
        }
        
        return true;
    }
};

inline CArchive& endln(CArchive& ar) {
    
    if(ar.IsLoadable()) {
        char ch;
        ar >> ch;
    } else
        ar<<'\n';
    
    return ar;
}

inline CArchive& space(CArchive& ar) {
    
    if(ar.IsLoadable()) {
        char ch;
        ar >> ch;
    } else
        ar<<' ';
    
    return ar;
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
    //archive.SetError( 12323, "Invalid input %s. Expected %s", str.c_str(), vt.str.c_str() );
    return archive;
}


#endif /* Archive_hpp */
