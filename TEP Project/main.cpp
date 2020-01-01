//
//  main.cpp
//  TEP Project
//
//  Created by Michał Raszczuk on 27/12/2019.
//  Copyright © 2019 Michał Raszczuk. All rights reserved.
//

#include <iostream>
#include "core/Table.h"
#include "core/Matrix.h"
#include "MSCN Problem/MscnProblem.h"
#include "Double.h"
#include <random>

using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    
    CMscnProblem problem;
//    CDouble o1 = 1;
//    CDouble o2 = 2;
//    CDouble o3 = 3;
//    CDouble o4 = 4;
//    CDouble o5 = 5;
//
//    o2 = o1;
//    o3 = o4 + o5;
//    o3 += o4;
    
    CRandom random(10);
    
    cout << random.nextNumber() << endl;
    cout << random.nextNumber() << endl;
    cout << random.nextNumber() << endl;
    cout << random.nextNumber() << endl;
    cout << random.nextNumber() << endl;
    cout << random.nextNumber() << endl;
    
    return 0;
}
