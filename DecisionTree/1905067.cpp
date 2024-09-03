#include<iostream>
#include<bits/stdc++.h>
#include<sstream>
#include "param.h"
#include "helper.h"
using namespace std ; 



int main(int argc, char* argv[]) 
{

int size = 80 ;     
ofstream final_result("final_result.txt") ; 
vector<double>test_accuracy ; 
vector<double>train_accuracy ;
   for(int iter = 1 ; iter<=100 ; iter++)
   {
       
        //size++ ; 
        cout<<"Running iteration no : "<<iter<<endl ; 
        double train_data_size = size*1.0/100 ;
        //final_result<<"For training data size "<<train_data_size<<endl ; 
        ifstream datafile , inputfile ; 
        ofstream train_file, test_file ; 

        int test_count = 0 , train_count = 0 ; 
        datafile.open("car evaluation dataset/car.data") ; 
        train_file.open("training_data.txt") ; 
        test_file.open("test_data.txt") ; 
        examples initial_example ; 
        string line ; 
        vector<string>values ; 
    

        
        while (getline(datafile,line))
        {
        if(help_rand()>=train_data_size){
                test_file<<line<<endl  ; 
                test_count++ ; 
            }
        else{
                train_file<<line<<endl  ;
                initial_example.datalist.push_back(line); 
                train_count++ ; 
        }
        

        }

        vector<string>train_tokens ; 
        vector<string>test_tokens ; 
        // Using mod 7 , you will get each entry 
        // 0--buying   2-Doors 3-Persons 
        // 1--maint    4-lug_boot  5-safety 6-outcome



        vector<int>attr_buying ; 
        attr_buying.push_back(buying_vhigh) ; 
        attr_buying.push_back(buying_high) ; 
        attr_buying.push_back(buying_med) ; 
        attr_buying.push_back(buying_low) ;



        vector<int>attr_maint ; 
        attr_maint.push_back(maint_vhigh) ; 
        attr_maint.push_back(maint_high) ; 
        attr_maint.push_back(maint_med) ; 
        attr_maint.push_back(maint_low) ;
        
        vector<int>attr_doors ; 
        attr_doors.push_back(doors_2) ; 
        attr_doors.push_back(doors_3) ; 
        attr_doors.push_back(doors_4) ; 
        attr_doors.push_back(doors_5more) ;

        vector<int>attr_persons ; 
        attr_persons.push_back(persons_2) ; 
        attr_persons.push_back(persons_4) ; 
        attr_persons.push_back(persons_more) ; 


        vector<int>attr_lug_boot ; 
        attr_lug_boot.push_back(lug_boot_small) ; 
        attr_lug_boot.push_back(lug_boot_med) ; 
        attr_lug_boot.push_back(lug_boot_big) ; 


        vector<int>attr_safety ; 
        attr_safety.push_back(safety_low) ; 
        attr_safety.push_back(safety_med) ; 
        attr_safety.push_back(safety_high) ; 


        vector<vector<int>>attributes;  
        attributes.push_back(attr_buying) ;    
        attributes.push_back(attr_maint) ;
        attributes.push_back(attr_doors) ; 
        attributes.push_back(attr_persons) ; 
        attributes.push_back(attr_lug_boot) ; 
        attributes.push_back(attr_safety) ; 



        train_file.close() ;
        test_file.close() ;


        inputfile.open("training_data.txt") ; 
        spliter(inputfile , train_tokens) ; 
        inputfile.close() ;
        inputfile.open("test_data.txt") ; 
        spliter(inputfile , test_tokens) ;  
        inputfile.close() ; 

        
        make_init(initial_example , train_tokens) ; 
        //initial_example.show() ; 

        std::set<int> used;
        DecisionTree tree  ; 
        tree.buildTree(initial_example,attributes,used) ; 
        //tree.showTree();



        
        //vector<string>temp_tokens={"vhigh","low","2","more","big","high","vgood"} ; 
    
        inputfile.open("test_data.txt") ; 
        int result ; 
        ofstream outfile ; 
        outfile.open("GraphTest.txt")  ; 
        int correct = 0 , count =0  ; 
        while (getline(inputfile,line))
        {
            result = tree.prediction(line) ; 
            correct+=result ;
            count+=1 ; 
        
        }
        double acc = 100.0*correct/count ; 
        outfile<<acc<<endl ;
        test_accuracy.push_back(acc) ; 
        final_result<<"Accuracy on test file : "<<acc<<endl ; 
        //cout<<size<<" "<<acc<<endl ; 
        inputfile.close() ; 
        outfile.close() ; 



        outfile.open("GraphTrain.txt") ; 
        inputfile.open("training_data.txt") ; 
        correct = 0 ;
        count =0  ; 
        while (getline(inputfile,line))
        {
            result = tree.prediction(line) ; 
            correct+=result ;
            count+=1 ; 
        
        }
        acc = 100.0*correct/count ; 
        train_accuracy.push_back(acc) ; 
        outfile<<acc<<endl ;
        final_result<<"Accuracy on training file : "<<acc<<endl ; 
        final_result<<"--------------------------------------------"<<endl ;
    

   }
    double mean_acc = calc_mean(test_accuracy)  ; 
    final_result<<"Average test accuracy : "<<mean_acc<<endl ; 
    final_result<<"Standard deviation of accuracy : "<<SD(test_accuracy)<<endl ; 
    
    return 0 ; 

}