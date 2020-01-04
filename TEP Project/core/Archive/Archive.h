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
    CArchive& operator << (char chValue);
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

struct ValidateText {
    string str;
};

inline ValidateText Validate(string str) {
    
    return { str };
}

inline CArchive& operator >> (CArchive& archive, ValidateText vt) {
    
    string str = archive.ReadString( vt.str.length() );
    //archive.SetError( 12323, "Invalid input %s. Expected %s", str.c_str(), vt.str.c_str() );
    return archive;
}

#endif /* Archive_hpp */
