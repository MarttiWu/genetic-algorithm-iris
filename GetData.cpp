//
//  Ackley.cpp
//
//  Created by WU,MENG-TING on 2020/8/14.
//  Copyright © 2020 WU,MENG-TING. All rights reserved.
//

#include "GetData.hpp"


vector<vector<double> > GetIrisData(){
    ifstream fin;
    fin.open("iris.data");
    vector<vector<double> > dataset;
    while(!fin.eof()){
        vector<double> data(5);
        fin>>data[0];
        fin.ignore(2,',');
        fin>>data[1];
        fin.ignore(2,',');
        fin>>data[2];
        fin.ignore(2,',');
        fin>>data[3];
        fin.ignore(2,',');
        string name;
        fin>>name;
        double target;
        if (name=="Iris-setosa")
            target=1;
        else if (name=="Iris-versicolor")
            target=2;
        else if (name=="Iris-virginica")
            target=3;
        else{
            //unknown data
            target=-1;
        }
        data[4]=target;
        dataset.push_back(data);
    }
    return dataset;
}
