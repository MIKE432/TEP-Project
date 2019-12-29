//
//  main.cpp
//  TEP Project
//
//  Created by Michał Raszczuk on 27/12/2019.
//  Copyright © 2019 Michał Raszczuk. All rights reserved.
//

#include <iostream>
#include "Matrix.h"
#include "Table.h"
using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    
    CMatrix<int> matrix(5 , 5);
    
    matrix.set(99, 0, 0);
    matrix.set(1, 1, 0);
    matrix.set(2, 2, 0);
    matrix.set(3, 3, 0);
    matrix.set(4, 4, 0);
    
    matrix.set(5, 0, 1);
    matrix.set(6, 1, 1);
    matrix.set(7, 2, 1);
    matrix.set(8, 3, 1);
    matrix.set(9, 4, 1);
    
    matrix.set(10, 0, 2);
    matrix.set(11, 1, 2);
    matrix.set(12, 2, 2);
    matrix.set(13, 3, 2);
    matrix.set(14, 4, 2);
    
    matrix.set(15, 0, 3);
    matrix.set(16, 1, 3);
    matrix.set(17, 2, 3);
    matrix.set(18, 3, 3);
    matrix.set(19, 4, 3);
    
    matrix.set(20, 0, 4);
    matrix.set(21, 1, 4);
    matrix.set(22, 2, 4);
    matrix.set(23, 3, 4);
    matrix.set(24, 4, 4);
    matrix[4][4] = 100;
    cout << matrix[4][4] << endl;

    
    return 0;
}
