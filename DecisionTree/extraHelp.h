

#include<bits/stdc++.h>
#include<chrono>
using namespace std ;
#include "param.h"

std::unordered_map<std::string, int> constantValueMap = {
    {"buying", 1},
    {"maint", 2},
    {"doors", 3},
    {"persons", 4},
    {"lug_boot", 5},
    {"safety", 6},
    {"vhigh", 11},
    {"high", 12},
    {"med", 13},
    {"low", 14},
    {"doors_2", 31},
    {"doors_3", 32},
    {"doors_4", 33},
    {"doors_5more", 34},
    {"persons_2", 41},
    {"persons_4", 42},
    {"persons_more", 43},
    {"lug_boot_small", 51},
    {"lug_boot_med", 52},
    {"lug_boot_big", 53},
    {"safety_low", 61},
    {"safety_med", 62},
    {"safety_high", 63}
};

int getStringFromValue(const std::string& str) {
    if(str=="good")return result_good ; 
    if(str=="vgood")return result_vgood; 
    if(str=="unacc")return result_unacc ; 
    if(str=="acc")return result_acc ; 

    cout<<"sorry bro , debug harder"<<endl ; 
    return -1; 
}

double help_rand() 
{
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    srand(seed);
    return static_cast<double>(rand()) / RAND_MAX;

   
}

vector<string>  line_spliter(string line)
{
    string v ;
    vector<string>b ;
    istringstream s(line) ; 
    while (getline(s,v,','))
         b.push_back(v) ;
    return b ; 
}
void spliter(ifstream &datafile , vector<string>&values)
{   
    string line ; 
    while (getline(datafile,line))
    {
        
       istringstream s(line) ; 
       string v ; 
       while (getline(s,v,','))
         values.push_back(v) ;  
    }
}

vector<string> spliter_by_vector(vector<string>values)
{   
    vector<string>ret ; 
    for(string line : values)
        {
            istringstream s(line) ; 
            string v ; 
       while (getline(s,v,','))
         ret.push_back(v) ;
        }
    return ret ; 
}

void printVector(vector<string>values)
{
    
    for(int i=0 ; i<values.size() ; i++)
    {
        std::cout<<values[i]<<endl ; 
        //if(i%7==6)std::cout<<endl ;
    }
}

int converter(string& str , int addt = 0) {
    if (str == "buying") return buying;
    if (str == "maint") return maint;
    if (str == "doors") return doors;
    if (str == "persons") return persons;
    if (str == "lug_boot") return lug_boot;
    if (str == "safety") return safety;
    if (str == "vhigh")
    {
        //cout<<"INSIDE VHIGH for "<<addt<<endl ; 
        if(addt==buying)
            return buying_vhigh;
        else if(addt==maint) return maint_vhigh ; 
    }
    if (str == "high")    
    {
        if(addt==buying)
            return buying_high;
        else if(addt==maint) return maint_high ; 
    }
    if (str == "med")   {
        if(addt==buying)
            return buying_med;
        else if(addt==maint) return maint_med ; 
    }
    if (str == "low") {
        if(addt==buying)
            return buying_low;
        else if(addt==maint) return maint_low ; 
    }
    if (str == "2")
    {
        if(addt==doors)
            return doors_2;
        else if(addt==persons) return persons_2 ; 
    }
    if (str == "4")  {
        if(addt==doors)
            return doors_4;
        else if(addt==persons) return persons_4 ; 
    }
    if (str == "3") return doors_3;
    if (str == "5more") return doors_5more;
    if (str == "more") return persons_more;
    if (str == "small") return lug_boot_small;
    if (str == "med") {
        if(addt==safety)
            return safety_med;
        else if(addt==lug_boot) return lug_boot_med ; 
    }
    if (str == "big") return lug_boot_big;
    if (str == "low") return safety_low ;
    if (str == "high") return safety_high;

    cout<<"bruh who tf is : "<<str<<endl ; 
    return -1;
}

double calc_mean(const std::vector<double>& data)
{
    if(data.empty())return 0.0 ; 
    double sum = 0.0; 
    for(double v: data)sum+=v ; 
    return sum/static_cast<double>(data.size());
}
double SD(const std::vector<double>& data)
{
    if(data.empty())return 0.0 ; 
    double mean = calc_mean(data) ; 
    double diff_sq_sum = 0.0 ; 
    for (double value : data)
    {
        double difference = value - mean;
        diff_sq_sum += difference * difference;
    }
    double variance = diff_sq_sum / static_cast<double>(data.size());
    return sqrt(variance);
}



