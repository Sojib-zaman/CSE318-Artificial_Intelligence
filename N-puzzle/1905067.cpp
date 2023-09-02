#include<bits/stdc++.h>
#include<string>
using namespace std ;
 fstream outputFile,inputFile, testfile;
 int dhora = 0 ;
 int expanded = 0 ;
 int explored = 0 ;
class node
{
    int dim ;
    vector<int>v ;
    vector<int>s ;
    vector<node*>adj;
    mutable int M_Distance = 0 ;
    mutable int H_Distance = 0;
    int zero_pos ;
    node* parent ;
    int moves = 0 ;
    int priority = 0 ;
    public :
    node()
    {
        dim = 0 ;

    }
    node(int a)
    {
        dim = a ;
    }
    node(vector<int>s)
    {
        dim = sqrt(s.size()) ;
        for(int i = 0 ; i<s.size() ; i++)
        {

            int a = s[i] ;
            v.push_back(a) ;

        }
        M_Distance = Manhattan_distance();
        H_Distance = Hamming_distance() ;

    }
    void add(int a)
    {
        v.push_back(a) ;
    }
    void show()
    {
        for(int i = 1 ; i<=dim*dim ; i++)
        {
            outputFile<<v[i-1]<<" "  ;
            if(i%dim == 0) outputFile<<endl ;
        }
    }
      void showtest()
    {
        for(int i = 1 ; i<=dim*dim ; i++)
        {
            testfile<<v[i-1]<<" "  ;
            if(i%dim == 0) testfile<<endl ;
        }
    }
    int Hamming_distance()const
    {
        int count = 0 ;
        for(int i = 1 ; i<=dim*dim ; i++)
        {
            if(i!=v[i-1] && v[i-1]!=0)
                count++ ;
        }
        H_Distance = count ;

        return count ;
    }
    int Manhattan_distance()const
    {
        int dr , dc , cr , cc ;
        int count = 0 ;
        for(int i = 1 ; i<=dim*dim ; i++)
        {
            if(v[i-1]!=0)
            {

                dr = v[i-1]/dim ; if(v[i-1]%dim !=0)dr++ ;
                if(v[i-1]%dim !=0 )dc = v[i-1]%dim ;
                else
                    dc = dim-(v[i-1]%dim) ;

                cr = (i/dim) ; if(i%dim !=0 ) cr++;
                cc = (i%dim) ; if(cc==0)cc=dim ;

                count+= abs(dr-cr) ;
                count+= abs(dc-cc) ;

            }
        }
        M_Distance = count ;
        return count ;
    }
    int inversion_count()
    {

        int count = 0 ;
        for(int i = 0 ; i<(dim*dim)-1; i++)
        {
            for(int j=i+1 ; j<dim*dim ; j++ )
            {
                if(v[i]>v[j] && v[j]!=0) count++ ;
            }
        }

        return count ;
    }
    int blank_row_count()
    {

        for(int i = 1 ; i<=dim*dim ; i++)
        {
            if(v[i-1] == 0)
            {

               int row = i/dim ;
               if(i%dim!=0)row++ ;
                return row;
            }
        }


        return 0 ;
    }
    int find_zero_pos()
    {
        int zero_pos ;
        for(int i = 1 ; i<=dim*dim ; i++)
        {
            if(v[i-1] == 0)
            {
                zero_pos = i ;
            }
        }
        return zero_pos;
    }
    void AdjNodes()
    {

        //depending on the position of 0 , we may need 2/3/4 moves
        zero_pos = find_zero_pos();
        s=v;

        if(zero_pos%dim==0 || zero_pos%dim==1 ) // this means it's in last row or first row
        {
            if(zero_pos%dim==0) // this is the last row
               {
                    left_swap() ;
                    if(zero_pos/dim == 1)
                        down_swap() ;
                    else if( zero_pos/dim == dim)
                        up_swap() ;
                    else
                    {
                        up_swap() ;
                        down_swap() ;
                    }

               }
            else //this means first row
            {
                 right_swap() ;
                if(zero_pos==1) down_swap() ;
                else if(zero_pos+dim > dim*dim) up_swap() ;
                else
                    {
                        up_swap() ;
                        down_swap() ;
                    }

            }
        }
        else  // in middle part , we need to make 4 moves
        {
            left_swap() ;
            right_swap() ;
            //don't do it if 1st or last column
            if(zero_pos<dim && zero_pos+dim < dim*dim) down_swap() ; //1st row
            else if(zero_pos>dim && zero_pos+dim > dim*dim) up_swap() ; //last
            else
            {
                up_swap() ;
            down_swap() ;
            }

        }
    }
    void left_swap()
    {

        swap(s[zero_pos-1] , s[zero_pos-2]) ;
        node* n = new node(s);
        adj.push_back(new node(s)) ;
        s=v ;


    }
    void right_swap()
    {
        swap(s[zero_pos-1] , s[zero_pos]) ;
          adj.push_back(new node(s)) ;
        s=v ;

    }
    void up_swap()
    {
         swap(s[zero_pos-1] , s[zero_pos-dim-1]) ;
          adj.push_back(new node(s)) ;
        s=v ;


    }
    void down_swap()
    {
        swap(s[zero_pos-1] , s[zero_pos+dim-1]) ;
          adj.push_back(new node(s)) ;
        s=v ;

    }
    void show_adj_nodes()
    {

       int count = 1;
     for (const auto& x : adj) {
         outputFile<<count++<<"..."<<endl ;
            x->show() ;
    }
    }
    vector<node*> getAdjNodes()
    {
        return adj ;
    }



    bool operator<(const node& n2) const {
        return priority < n2.priority;
    }
      bool operator>(const node& n2) const {
        return priority > n2.priority;
    }
    void setparent(node* n)
    {
        parent = n;
    }
    int dijkstra(int choice)
    {
        int md;
        if(choice==2)
             md = Manhattan_distance() ;
        else
             md = Hamming_distance() ;


        priority_queue< pair<int , node*> , vector< pair<int , node*> > , greater< pair<int , node*> > > pq ;
        this->setparent(NULL);
         if(choice==2)
            pq.push(make_pair(M_Distance,this)) ;
        else
             pq.push(make_pair(H_Distance,this)) ;


        set<vector<int>>closedlist ;

        while(!pq.empty())
        {
            md = pq.top().first ;
            node* current = pq.top().second ;
            pq.pop() ;
            explored++ ;
           if(closedlist.count(current->v)) continue;
           closedlist.insert(current->v);

           int cmd ;
           if(choice==2) cmd=current->Manhattan_distance() ;
           else cmd=current->Hamming_distance() ;
            if(cmd==0)
            {
                outputFile<<"Minimum number of moves = "<<current->moves<<endl ;
                node* dummy = current;
                stack<node*>tree;
                int count = 1 ;
                while (dummy != NULL)
                {
                    tree.push(dummy);
                    dummy = dummy->parent;
                }
                while (tree.size()!=0)
                {
                    tree.top()->show() ; outputFile<<endl ;
                    tree.pop();
                }




                break ;
            }
            current->AdjNodes() ;
            for(auto x : current->getAdjNodes())
            {
                x->moves = current->moves+1 ;
                if(choice==2)
                x->priority = x->moves + x->Manhattan_distance() ;
                else
                     x->priority = x->moves + x->Hamming_distance();
                x->setparent(current) ;

                if(closedlist.count(x->v)) {

                        continue;
                }
                x->showtest();
                pq.push(make_pair(x->priority,x)) ;
                expanded++ ;
            }
        }
        return 1 ;
    }

};


int main()
{
    int a ;
    cout<<"INPUT FUNCTION : 1 FOR HAMMING AND 2 FOR MANHATTAN "<<endl ;
    int choice ;
    cin>>choice ;
    inputFile.open("318_offline_1\\input.txt",ios::in);
    outputFile.open("output\\output.txt", ios::out);
    testfile.open("test\\tesy06.txt", ios::out);
    inputFile>>a ;

    node* p = new node(a) ;
    for(int i=0 ; i<a*a ; i++)
    {
        int x ;
        inputFile>>x ;
        p->add(x) ;

    }

    if(a%2==1 && p->inversion_count()%2==1)
       outputFile<<"Unsolvable puzzle"<<endl  ;
    else if(a%2==0)
    {

        if( (p->inversion_count()+p->blank_row_count()) %2==1)
            outputFile<<"Unsolvable puzzle"<<endl ;
        else {
                p->dijkstra(choice) ;
                outputFile<<"Total expanded nodes : "<<expanded<<endl ;
                   outputFile<<"Total explored nodes : "<<explored<<endl ;
             }

    }
    else
    {


           p->dijkstra(choice) ;
           outputFile<<"Total expanded nodes : "<<expanded<<endl ;
             outputFile<<"Total explored nodes : "<<explored<<endl ;
    }

}
