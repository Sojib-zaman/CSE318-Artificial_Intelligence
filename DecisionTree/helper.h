#include<bits/stdc++.h>
#include "extraHelp.h"
#include<chrono>
using namespace std ;
#include "param.h"
class examples 
{
    public:
    int r_u ; 
    int r_a ; 
    int r_g ;
    int r_v ; 
    vector<string>carlist ; 
    vector<string>datalist ;
    int verdict ; 
    examples()
    {
        verdict = 0 ; 
        r_a=r_g=r_u=r_v= 0 ; 
    }
    void show()
    {
        //cout<<" unacc : "<<r_u<<" acc : "<<r_a<<" good : "<<r_g<<" vgood : "<<r_v<<endl ; 
        //cout<<"Dataset:"<<endl ; 
        //printVector(datalist) ; 
    
    }
    bool isempty()
    {
        //cout<<"cal empty "<<(r_a+r_g+r_v+r_u)<<endl ; 
        if(r_a+r_g+r_v+r_u==0)return true  ; 
        return false ; 
      
    }
    int sameClassificaiton()
    {
        if(r_a+r_g+r_v==0 && r_u!=0)return result_unacc ; 
        if(r_a+r_g+r_u==0 && r_v!=0)return result_vgood ; 
        if(r_a+r_u+r_v==0 && r_g!=0)return result_good ; 
        if(r_u+r_g+r_v==0 && r_a!=0)return result_acc ; 
        return 0 ; 
    }

};

void make_init(examples &e , vector<string>v)
{
    
    for(int i=6 ; i<v.size() ; i+=7)
    {
        ////cout<<v[i]<<endl ; 
        if(v[i]=="unacc") e.r_u++ ;
        else if(v[i]=="acc") e.r_a++; 
        else if(v[i]=="good") e.r_g++;
        else if(v[i]=="vgood") e.r_v++ ;  
        else break;
    }
    e.carlist = v ; 
}


struct TreeNode {
    int attribute;
    std::map<int, TreeNode*> branches;
    int outcome;

    TreeNode() {
        attribute=-1;
        outcome=0 ; 
    }
};

class DecisionTree
{
    private: 
        TreeNode* root ; 
    public:
        void buildTree(examples initial,vector<vector<int>>&attributes,set<int>used) ; 
        int prediction(string line ) ;
        void showTree() ; 

        
    private: 
        TreeNode* decisionTreeLearning(examples initial_example ,vector<vector<int>>&attributes, examples parent_example,set<int>used) ; 
        int traverse_tree(TreeNode* node ,vector<string>tokens ) ; 
        double test_accuracy(vector<string>tokens) ;
        void printTree(TreeNode* node, int depth);
};


void DecisionTree::printTree(TreeNode* node, int depth = 6) {
    if (node == nullptr) {
        return;
    }

    for (int i = 0; i < depth; i++) {
        cout << "  ";
    }

    if (node->attribute != -1) {
        cout << "Attribute: " << node->attribute << endl;
    } else {
        cout << "Outcome: " << node->outcome << endl;
    }

    for (const auto& entry : node->branches) {
        for (int i = 0; i < depth + 1; i++) {
            cout << "  ";
        }
        cout << "Value: " << entry.first << " -> ";
        printTree(entry.second, depth + 1);
    }
}

void DecisionTree::showTree()
{
    printTree(root) ; 
}

int DecisionTree::prediction(string line)
{
    vector<string>tokens=line_spliter(line) ; 
    if(getStringFromValue(tokens[6])==traverse_tree(root,tokens)) return 1; 
    return 0 ; 
}
int DecisionTree::traverse_tree(TreeNode* node ,vector<string>tokens)
{
       //cout<<"Node attribute : "<<node->attribute<<endl ; 
    if(node->branches.empty())
    {
        //cout<<"Found value"<<endl ; 
        return node->outcome ; 
    }
    //cout<<"value to be checked " <<tokens[node->attribute]<<endl ; 
    int attr_value = converter(tokens[node->attribute],node->attribute)  ;
   //cout<<"converted value : "<<attr_value<<endl ; 
    if(node->branches[attr_value]!=nullptr)
    {
       //cout<<"Going to next level"<<endl ; 
        return traverse_tree(node->branches[attr_value] , tokens)  ;
    }

    return result_good; //default 
}


double DecisionTree::test_accuracy(vector<string>tokens)
{
    
    ifstream inputfile; 
    inputfile.open("test_data.txt") ;
    string line ;
    return 0.0 ;  

    
    
}


void DecisionTree::buildTree(examples initial,vector<vector<int>>&attributes , set<int>used)
{
    
    root=decisionTreeLearning(initial ,attributes,initial,used) ;
}

int plurality_value(examples e)
{
    e.show() ; 
    int max_value = std::max({e.r_a, e.r_u, e.r_g, e.r_v});
    string result;



    if (max_value == e.r_g) {
        result = "good";
    } else if (max_value == e.r_v) {
        result = "vgood";
    }
    else if (max_value == e.r_a) {
        result = "acc";
    } else if (max_value ==e.r_u) {
        result = "unacc";
    }


  
    return getStringFromValue(result); 
}

double get_ratio(int des, examples esc)
{
    //cout<<"cal ratio"<<endl ; 
    double x = des*1.0 ; 
    if(!esc.isempty())
    {
        //cout<<"Happy ratio"<<endl ; 
       return x/((esc.r_a+esc.r_g+esc.r_u+esc.r_v)*1.0) ;
    }

    //cout<<"bro wtf"<<endl ; 
    return -1;
}
double calc(double x,examples esc)
{
    if(x!=0)
        return get_ratio(x,esc)*log(get_ratio(x,esc))/log(2.0) ; 
    return 0.0 ; 
}

double entropy(examples esc)
{
   
    return -1*(calc(esc.r_a,esc)+calc(esc.r_u,esc)+calc(esc.r_g,esc)+calc(esc.r_v,esc));
}

examples splitByAttribute(int attr_number ,  examples esc , int attr_value)
{
    //attr_number = 2(doors er jnne gain calculate korbo)
    //esc has datalist which is entire line 
    //esc carlist has the line splitted in datas
    //attr_value is like 4 persons (emne sob value er jnne entropy niye add korbo)

    examples new_ex ; 
    //cout<<"This will be checked for "<<attr_value<<endl ; 
    for(int i=attr_number ; i<esc.carlist.size() ; i+=7)
    {
       // //cout<<"data : "<<esc.carlist[i]<<" "<<converter(esc.carlist[i],attr_number)<<endl ; 
        if(converter(esc.carlist[i],attr_number)==attr_value)
        {
            new_ex.datalist.push_back(esc.datalist[i/7]) ; 
        }
    }
    new_ex.carlist=spliter_by_vector(new_ex.datalist) ; 
    make_init(new_ex,new_ex.carlist) ; 
    return new_ex; 
}



double gain(int attr_number , vector<int>one_attr,  examples esc)
{
    //attribute number is needed to find the order 
    //this one attribute contains some values ; 

   //cout<<"Checking the gain for attribute : "<<attr_number<<endl ; //buying , maint 


    int values_of_attribute = one_attr.size() ; 
    //cout<<"This attribute has total "<<values_of_attribute<<" values "<<endl ; 
    double parent_entropy = entropy(esc) ; 
    //cout<<"Parent entropy : "<<parent_entropy<<endl ; 
    double entropy_after_split = 0.0 ; 
    for(int i=0 ; i<values_of_attribute; i++)
    {
        //here one_attr[i] can be like 52 (lug_boot_med)
        //cout<<"Going to splitbyattr for "<<one_attr[i]<<endl ; 
        examples demo = splitByAttribute(attr_number,esc,one_attr[i]);
        demo.show();
        entropy_after_split+=(demo.datalist.size()*1.0/esc.datalist.size())*entropy(demo) ;

    }
    //cout<<" Entropy after split is : "<<entropy_after_split<<endl ; 
    return parent_entropy-entropy_after_split ; 
}

int BestAttribute(vector<vector<int>>attributes,  examples esc,set<int>used)
{
    double max_gain =  0 ; 
    int best_attribute = 0  ;
    for(int i=0 ; i<attributes.size() ; i++)
    {  
        //sending buying OR maint OR safety 
        if(used.find(i) == used.end())
        {
            double gained = gain(i,attributes[i],esc) ; 
            //cout<<"Gain : "<<gained<<endl ; 
            if(gained>max_gain)
            {
                best_attribute = i ;   
                max_gain=gained ;
            }

        }
        
    }
    return best_attribute ; 
}


TreeNode* DecisionTree::decisionTreeLearning(examples example,vector<vector<int>>&attributes,  examples parent_example,set<int>used)
{
    
    //cout<<"Inside decision tree"<<endl ; 
    TreeNode* node = new TreeNode() ; 
    if(example.isempty())
    {
       
        node->outcome = plurality_value(parent_example) ;
         //cout<<"Empty example "<<node->outcome<<endl ; 
        return node ; 
    }
    else if(example.sameClassificaiton()!=0)
    {
        
        node->outcome=example.sameClassificaiton() ; 
        //cout<<"Same classificaiton "<<node->outcome<<endl ; 
        return node ; 
    }
    else if(used.size()==6)
    {
    
        node->outcome=plurality_value(parent_example) ; 
        //cout<<"Empty Attribute "<<node->outcome<<endl ; 
     
        return node ; 
    }
    else 
    {
       int current_attribute_number = BestAttribute(attributes,example,used) ; 
       //cout<<"best : "<<current_attribute_number<<endl ; 
       node->attribute=current_attribute_number ; 
       used.insert(current_attribute_number) ; 
       for(int i=0 ; i<attributes[current_attribute_number].size() ; i++)
       {    

        int attribute_value = attributes[current_attribute_number][i] ; 
        examples value_example = splitByAttribute(current_attribute_number,example,attribute_value) ; 
        TreeNode* branch = decisionTreeLearning(value_example ,attributes ,example,used);
        //cout<<attribute_value<<endl ;
        node->branches[attribute_value] = branch;
       }
    }
    
    
    return node ; 

}



