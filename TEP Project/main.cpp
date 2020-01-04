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
#include "RandomSearch.h"
#include <random>

using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    
    CMscnProblem problem;

    {
    CArchive archive("testfile2.txt", "w");
    CRandom random(100);
    problem.Randomize(random);
    problem.Store(archive);
    }
    {
    CArchive archive("testfile2.txt", "r");
    problem.Load(archive);
    }
    {
    CArchive archive("testfile3.txt", "w");
    problem.Store(archive);
    }
    return 0;
}
