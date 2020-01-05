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
    
    CRandom random;
    int error = 0;
    {
//        problem.GenerateInstance(200);
//
//        CArchive archive;
//        archive.Store("testfile2.txt");
//        archive << problem;
    }
    CMscnProblem problem;
    {
        CArchive archive;
        archive.Load("testfile2.txt");
        archive >> problem;
    }

    CRandomSearch randomSearch(&problem);
    {
        CSolution* pSolution = randomSearch.GenerateValidSolution(random);
        
        if(pSolution != NULL) {
            CArchive archive;
            archive.Store("testSolution.txt");

            archive << *pSolution;
            
            
            delete pSolution;
        }
    }
    
    return 0;
}
