//
//  execute.cpp
//  search
//
//  Created by WU,MENG-TING on 2020/7/1.
//  Copyright © 2020 WU,MENG-TING. All rights reserved.
//

#include "execute.hpp"

void execute(const int Algo,const int runs,const int generations,const string filename,const int population,const double Pm,const double Pc){
    vector<vector<double> > data = GetIrisData();
    int x = data[0].size()-1;
    vector<double> answer(data.size(),0);
    
    for (int i=0;i<data.size();i++){
        answer[i] = data[i][x];
        data[i].pop_back();
    }

    srand((unsigned)time(NULL));
    vector<double> avg(generations/block);

    if (filename==""){
        double avg_acc=0.0;
        for (int i=0;i<runs;i++){
            cout<<"----------------------------------------"<<endl;
            cout<<"run: "<<i<<endl;
            time_t start=0, end=0;
            if (Algo==1){
                GA *r = new GA(generations, population, Pm, Pc, data);
                start = time(NULL);
                r->Cluster();
                for (int j=0;j<generations/block;j++){
                    avg[j] += r->get_record_value(j*block);
                }
                cout<<"Best: "<<r->get_record_value(generations-1)<<endl;
                
                vector<int> index(CLUSTER,0);
                index[0] = 0;
                int last = answer[0];
                int k=0;
                for (int j=0;j<answer.size();j++){
                    if (answer[j]!=last){
                        k++;
                        index[k] = j;
                        last = answer[j];
                    }
                }
                int A[CLUSTER];
                for (int j=1;j<=CLUSTER;j++)
                    A[j-1] = j;
                
                int b=0;
                int size=1;
                for (int j=CLUSTER;j>0;j--)
                    size*=j;
                vector<double> acc(size);
                do{
                    int c=0;
                    for (int j=0;j<answer.size();j++){
                        if (j==index[c]){
                            c++;
                        }
                        answer[j] = A[c-1];
                    }

                    vector<double> predict = r->get_record_str(generations-1);
                    double total=(double)answer.size();
                    for (int j=0;j<answer.size();j++){
                        if (predict[j]==answer[j])
                            acc[b]++;
                    }
                    acc[b]/=total;
                    
                    b++;
                    
                }while(next_permutation(A,A+CLUSTER));
                    
                
                double accuracy=0.0;
                accuracy = acc[0];
                for (int j=0;j<acc.size();j++){
                    if (acc[j]>accuracy)
                        accuracy = acc[j];
                }
                cout<<"accuracy: "<<accuracy<<endl;
                avg_acc+=accuracy;
                
                cout<<endl;
                end = time(NULL);
            }
            
            double diff = difftime(end, start);
            cout<<"Run time: "<<diff<<"s"<<endl;
        }
        cout<<"----------------------------------------"<<endl;
        for (int i=0;i<avg.size();i++){
            avg[i]/=runs;
        }
        for (int i=0;i<avg.size();i++){
             cout<<"Iter "<<i*block<<" SSE average: "<<avg[i]<<endl;
        }
        
        avg_acc/=runs;
        cout<<"average accuracy: "<<avg_acc<<endl;
    }
    else{
        cout<<"random number file"<<endl;
        //left blank
        //complete when needed
    }
}
