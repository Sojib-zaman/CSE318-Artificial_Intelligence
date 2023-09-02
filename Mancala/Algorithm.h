#include "board.h"
#include<fstream>
#include<iostream>




class Algorithm 
{
    int heuristic ; 
    int current_depth ; 
    int max_depth ; 
    ofstream outfile;
    int addt_moves[2] ;
   

    public: 
    void setheuristicfunction(int h) ; 
    void setmaxdepth(int d) ; 
    int MiniMaxAlphaBetaAlgo(board cur_board,int player, bool MaxPrio ,int curr_depth, int Alpha , int Beta) ;  
    void ssb(board b) ; 
};
void Algorithm::setmaxdepth(int d)
{
    outfile.open("output.txt");
    addt_moves[0]=0 ; 
    addt_moves[1]=0 ;
    max_depth=d ; 
}
void Algorithm::setheuristicfunction(int h)
{
    heuristic = h ; 
}
// initially alpha is -inf , beta is +inf
// initial depth = 0 
int Algorithm::MiniMaxAlphaBetaAlgo(board cur_board,int player, bool MaxPrio ,int curr_depth, int Alpha , int Beta)
{
    // cout<<"first : "<<player<<endl ; 
    // outfile<<"Current player "<<player<<endl ; 
    // outfile<<"Current Depth "<<curr_depth<<endl ; 

    // ssb(cur_board) ; 




    
    if(curr_depth==0 || cur_board.endgame()) 
    {
       if(MaxPrio)
         return cur_board.call_heuristic(heuristic,player,addt_moves[player]); // at leaf mode , sending values back 
       else 
         return cur_board.call_heuristic(heuristic,player,addt_moves[1-player]);
    }
    
  
    board demo ; 
    demo.copy_board(cur_board) ; 
        
    if(MaxPrio)
    {
        int best_option = INT_MIN ;
        int next_move = -1 ; // next move only sent for root node 

        // add a choose better options 
        for(int i=0 ; i<6 ; i++)
        { 
             demo.copy_board(cur_board) ; 
            if(!demo.isempty(player,i))
            {
                int curdepth_option ;  
                int nextplayer ; 
                nextplayer = demo.move(player,i) ; 
               
                if(nextplayer==player)
                    {addt_moves[player]++; 
                        curdepth_option = MiniMaxAlphaBetaAlgo(demo , player , true , curr_depth-1 , Alpha , Beta) ;
                        
                    } 
                else 
                    curdepth_option = MiniMaxAlphaBetaAlgo(demo , player , false , curr_depth-1 , Alpha , Beta) ; 

                //cout<<"currdepth option : "<<curdepth_option<<endl ; 
                // now that a node got a value from it's successors , find the best choice for him 
                
                if(best_option<curdepth_option)
                {
                    best_option = curdepth_option ; 
                    next_move = i ; 
                    //cout<<"Next move changes to "<<next_move<<endl ; 
                }
                Alpha = max(Alpha,best_option) ; 
                if(Beta<=Alpha)break;  
               // cur_board.copy_board(demo) ;           
            }
            
        }
        
        if(curr_depth==max_depth)
        {
            //cout<<"sending now "<<next_move<<endl ; 
            return next_move ; // everytime for the root node
        } 
        return best_option ; 
    }
    else 
    {
        int best_option = INT_MAX ;
        
        
        for(int i=0 ; i<6 ; i++)
        {
            if(!cur_board.isempty(1-player,i))
            {
                demo.copy_board(cur_board) ;
                int curdepth_option ;  
                int nextplayer ; 
                nextplayer = demo.move(1-player,i) ; 
                //if next is also me , then I call again for min 
                if(nextplayer==player)
                        curdepth_option = MiniMaxAlphaBetaAlgo(demo , player , true , curr_depth-1 , Alpha , Beta) ; 

                else if(nextplayer==(1-player)) // opponent of min got chance , so calling for max
                    {addt_moves[1-player]++; 
                        curdepth_option = MiniMaxAlphaBetaAlgo(demo , player , false , curr_depth-1 , Alpha , Beta) ; 
                                           
                    }
                // cout<<"currdepth option : "<<curdepth_option<<endl ; 
                // now that a node got a value from it's successors , find the best choice for him 
               
                if(curdepth_option<best_option)
                {
                    best_option = curdepth_option ; 
                }
                Beta = min(Beta,best_option) ; 
                if(Beta<=Alpha)break; 
               // cur_board.copy_board(demo) ; 
            }
           
        }
        return best_option ; 
    }
    
}






void Algorithm :: ssb(board board)
{
    int rows = 5;
    int cols = 8;
    //cout<<"Printing"<<endl ; 
    for (int i = 0; i < rows; i++)
     {
        for (int j = 0; j < cols; j++)
         {
            if (i == 0 || i == rows - 1) 
            {
                outfile<< "....";
            } 
            else if(i==2)
            {
                if(j==0) outfile<<"| "<<board.storage[1]<<" |" ; 
                else if(j==cols-1)outfile<<"|"<<board.storage[0]<<" |" ; 
                else outfile<<"     ";
            }
            else if(i==1)
            {
                if(j==0 || j==cols-1)outfile<<"    " ; 
                else 
                    outfile<<"| "<<board.lane[1][6-j]<<" |";
            }
             else if(i==3)
            {
                if(j==0 || j==cols-1)outfile<<"    " ; 
                else 
                    outfile<<"| "<<board.lane[0][j-1]<<" |";
            }
            
         }
         outfile<<endl ; 
    }
}










