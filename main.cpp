//
//  main.cpp
//  search
//
//  Created by WU,MENG-TING on 2020/7/19.
//  Revised by WU,MENG-TING on 2020/8/17.
//  Copyright © 2020 WU,MENG-TING. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <string>
#include "execute.hpp"

using namespace std;

void prompt(const int Algo,const int runs,const int iterations);

int main(int argc, const char * argv[]) {
    const string algo = argv[1];
    const int runs = stoi(argv[2]);
    const int iterations = stoi(argv[3]);
    
    string filename= argv[4];
    cout<<"filename: "<<filename<<endl;
    
    const int population = stoi(argv[5]);
    const double Pm = stod(argv[6]);
    const double Pc = stod(argv[7]);
    
    if (algo=="ga"){
        prompt(1, runs, iterations);
        execute(1, runs, iterations, filename, population, Pm, Pc);
    }
    else{
        cerr<<"No such algorithm!"<<endl;
    }
    return 0;
}


void prompt(const int Algo,const int runs,const int iterations){
    cout<<"Problem: Data Clustering"<<endl;
    cout<<"Data set: Iris"<<endl;
    cout<<"----------------------------------------"<<endl;
    switch (Algo) {
        case 1:
            cout<<"Genetic Algorithm:"<<endl;
            break;
        default:
            break;
    }
    cout<<"Runs: "<<runs<<endl;
    cout<<"Generations: "<<iterations<<endl;
    cout<<"----------------------------------------"<<endl;
}
