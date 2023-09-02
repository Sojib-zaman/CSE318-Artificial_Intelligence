#include<bits/stdc++.h> 
#include <windows.h>
#include <conio.h>
using namespace std; 
class board
{
    public:
    // storage 
    int storage[2] ;



    // default stone 
    int stones = 4; 
    int pits = 6 ;
    int total_stones; 



    // individual boxes 
    int lane[2][6] ; 


 
    // total stone count 
    int p1_lane_total_stone() ; 
    int p2_lane_total_stone() ;

    //total stones in each storage 
    int total_captured() ; 

    // heuristics 
    int heuristic_one(int cp) ; 
    int heuristic_two(int cp,int W1 , int W2) ; 
    int heuristic_three(int cp,int W1 , int W2 , int W3 , int additional_moves) ; 
    int heuristic_four(int cp,int W1 , int W2 , int W3  , int W4 , int additional_moves) ; 

    // choose heuristic 
    int call_heuristic(int count,int cpr,int W1 , int W2 , int W3  , int W4,int add) ;

    //functionalities 
    board(); 
    void show_board() ; 
    bool isempty(int pid , int sid) ; 
    void copy_board(board board) ;
    bool isvalid() ; 
    int send_noempty(int player) ; 
    int move(int player , int pit_no) ; 
    void take_all_of_opp(int player , int pit_no) ; 
    int winner() ; 
    bool endgame() ; 


};


board::board()
{
    total_stones = stones*pits*2 ;
   
   //setup the storage 
   storage[0] = 0  ;
   storage[1] = 0 ; 
   
   //setting up the lane 
    for(int i=0 ; i<2 ; i++)
    {
        for(int j=0 ; j< pits ; j++)
        {
          lane[i][j] = stones ; 
        }
        
    } 
    
}
bool board::isempty(int pid , int sid)
{
    if(lane[pid][sid]==0)return true ; 
    return false ; 
}
void board::copy_board(board board)
{
    storage[0] = board.storage[0] ; 
    storage[1] = board.storage[1] ; 
    for(int i=0 ; i<2 ; i++)
    {
        for(int j=0 ; j< pits ; j++)
        {
          lane[i][j] = board.lane[i][j] ; 
        }
        
    } 
    
    
}
int board::send_noempty(int player)
{
    return player;
        
}
bool board::isvalid()
{
    if(p1_lane_total_stone()+p2_lane_total_stone()+total_captured() == total_stones )
        return true;
    return false; 
}
int board::move(int playerid , int pit_no)
{
    int stones_on_pit_no ; 
    stones_on_pit_no = lane[playerid][pit_no] ;  
    if ((pit_no<0)||(pit_no>pits)||(stones_on_pit_no==0))
       { 
        return 1-playerid;
       }
    lane[playerid][pit_no] = 0 ; 


   
    
   // int per_pit = floor(stones_on_pit_no / pits) ; 
   // int extra_stone = stones_on_pit_no%pits ; 

    int opponent = 1-playerid ; 



    // for(int i=0 ; i<pits ; i++)
    // {
    //     lane[playerid][i] += per_pit ; 
    //     lane[opponent][i] += per_pit ; 
    // }
    //storage[playerid]+=per_pit ; 
   // storage[playerid]+= floor(stones_on_pit_no / pits) ;  


    int next_player = opponent ; 
    // if I land on a empty pit (note that my pit no is going to be empty)
    if(stones_on_pit_no==2*pits+1)
        take_all_of_opp(playerid,pit_no) ; 
    

    // if per pit is 0 , then we only distribute one by one
    // when giving stones to me is done 
    // we give the rest of them to enemy 
    int extra_stone = stones_on_pit_no ; 
    int nextbox = pit_no+1 ;
    for(int i=nextbox; i<pits ; i++)
    {
        
        if(extra_stone>0)
        {
            lane[playerid][i]+=1 ; 
          
            extra_stone-- ; 
            // again the last stone(that's the first check) may drop in some empty slot , then take all of opponent 
            if(extra_stone==0 && lane[playerid][i]==1) // checking one because extra stone (just landed)
                take_all_of_opp(playerid,i) ;
            
        }
    }

   
    if(extra_stone>0)
    {
       
        storage[playerid]+=1 ; 
        extra_stone-- ; 
        if(extra_stone==0) next_player = playerid ; 
    }

    for(int i=0 ; i<pits ; i++)
    {
        if(extra_stone!=0)
        {
            lane[opponent][i]+=1 ; 
            extra_stone-- ; 
        }
    }
    // now if the stones come back to my lane again 
    for(int i=0; i<pits ; i++)
    {
        if(extra_stone>0)
        {
            lane[playerid][i]+=1 ; 
            extra_stone-- ; 
            // again the last stone(that's the first check) may drop in some empty slot , then take all of opponent 
            if(extra_stone==0 && lane[playerid][i]==1) // checking one because extra stone (just landed)
                take_all_of_opp(playerid,i) ;
            
        }
    }
    return next_player ; 


    
}

void board::take_all_of_opp(int player , int pit_no)
{
    if(lane[1-player][pits-1-pit_no]!=0)
    {
    storage[player] += lane[1-player][pits-1-pit_no]+1 ; // last +1 because the last stone on my pit will also go to storage 
    lane[1-player][pits-1-pit_no] = 0 ; 
    lane[player][pit_no]  = 0 ; 
    }
   
}
bool board::endgame()
{
    if(p1_lane_total_stone()==0 || p2_lane_total_stone()==0 || total_captured()==total_stones)
        return true ; 
    return false ; 
}
int board::winner()
{  // cout<<p1_lane_total_stone()<<" "<< p2_lane_total_stone() <<" "<<total_captured()<<" "<<total_stones<<endl ; 
    if(endgame())
    { 
        if(p1_lane_total_stone()+storage[0] > p2_lane_total_stone()+storage[1])
            return 0 ; 
        else if(p1_lane_total_stone()+storage[0] < p2_lane_total_stone()+storage[1])return 1 ; 
        else return -1 ;
    }
    else{
        return INT_MIN ;
    }
}

int board:: p1_lane_total_stone()
{
    int count=0 ; 
    for(int i=0 ; i<pits ; i++)
        count+=lane[0][i] ; 
    return count;
}
int board:: p2_lane_total_stone()
{
    int count=0 ; 
    for(int i=0 ; i<6 ; i++)
        count+=lane[1][i] ; 
    return count;
}
int board::total_captured()
{
    return storage[0]+storage[1] ; 
}

int board:: heuristic_one(int cp)
{
   
    return (storage[cp]-storage[1-cp]) ; 
}

int board:: heuristic_two(int cp,int W1 , int W2)
{
    int str_diff = storage[cp]-storage[cp] ; 
    int lane_diff = 0 ;
    if(cp==0)
     lane_diff = p1_lane_total_stone() - p2_lane_total_stone() ; 
    else lane_diff = p2_lane_total_stone() - p1_lane_total_stone() ; 
    return W1*str_diff+W2*lane_diff ; 
}
int board:: heuristic_three(int cp,int W1 , int W2, int W3 , int additional_moves)
{

    return heuristic_two(cp,W1,W2)+W3*additional_moves; 
}
int board:: heuristic_four(int cp , int W1 , int W2, int W3 , int W4 , int additional_moves)
{  
    return heuristic_three( cp, W1 ,  W2,  W3 , additional_moves)+ W4*total_captured() ; 
}

int board::call_heuristic(int count,int cpr,int add=0,int W1=1,int W2=2,int W3=3,int W4=4)
{
    if(count==1)return heuristic_one(cpr);
    else if(count==2)return heuristic_two(cpr,W1, W2) ; 
    else if(count==3)return heuristic_three(cpr,W1,W2,W3,add) ; 
    else if(count==4)return heuristic_four(cpr,W1,W2,W3,W4,add) ; 
    return 0 ; 
}

void board::show_board()
{
    
    int rows = 7;
    int cols = 8;
   //cout<<"Printing"<<endl ; 
    for (int i = 0; i < rows; i++)
     {
        for (int j = 0; j < cols; j++)
         {
            if (i == 0 || i == rows - 1 || i==2 || i==4) 
            {
              
                cout << "\033[35m.....\033[0m";
                if(j==cols-1)cout<<"\033[35m......\033[0m";
                
            } 
            else if(i==3)
            {
                
                
                if(j==0)
                {
                    if(storage[1]>=10)
                        cout<<": \033[1;31m"<<storage[1]<<"\033[0m :" ; 
                    else 
                        cout<<": \033[1;31m0"<<storage[1]<<"\033[0m :" ; 
                }
                else if(j==cols-1)
                {
                    if(storage[0]>=10)
                    cout<<": \033[1;32m"<<storage[0]<<" \033[0m:" ; 
                    else
                    cout<<": \033[1;32m0"<<storage[0]<<" \033[0m:" ;
                }
                else if(j==cols-2)cout<<"     ";
                else if(j==1)cout<<"     ";
                else 
                { 
                    cout<<"      ";
                }
            }
            else if(i==1)
            {
                if(j==0 )cout<<":    " ; 
                else if( j==cols-1)cout<<"    :" ; 
                else 
                {
                    if(lane[1][6-j]>=10)
                        cout<<":\033[1;33m "<<lane[1][6-j]<<"\033[0m :";
                    else
                        cout<<":\033[1;33m 0"<<lane[1][6-j]<<"\033[0m :";
                }
                    
            }
             else if(i==5)
            {
                if(j==0 )cout<<":    " ; 
                else if( j==cols-1)cout<<"    :" ; 
                else 
                {
                    if(lane[0][j-1]>=10)
                        cout<<":\033[1;36m "<<lane[0][j-1]<<"\033[0m :";
                    else
                        cout<<":\033[1;36m 0"<<lane[0][j-1]<<"\033[0m :";
                }
            }
        
            
         }
         cout<<endl ; 
    }
}








