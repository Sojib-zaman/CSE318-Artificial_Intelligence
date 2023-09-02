#include "Algorithm.h"
class player
{
public:
   int depth ; 
   int heuristic_function ; 
   int player_type ; 

    Algorithm algo ;
   
    player(int type , int depth , int heuristic);
    ~player();
    void settype(int type) ; 
    void setdepth(int depth);
    void setfunc(int h) ; 
    int callminmax(board board) ; 
   
};

player::player(int type , int depth , int heuristic)
{
    this->player_type=type;
    setdepth(depth) ; 
    setfunc(heuristic) ; 

     
    algo.setmaxdepth(depth);
    algo.setheuristicfunction(heuristic);
}

player::~player()
{
}
void player :: settype(int type)
{
    this->player_type = type ; 
}
void player::setdepth(int depth){
    this->depth = depth ; 
}
void player:: setfunc(int h){
    heuristic_function = h ; 
}
int player::callminmax(board board)
{
    //cout<<"calling "<<player_type<<" first" <<endl ; 
   return algo.MiniMaxAlphaBetaAlgo(board,player_type,true,this->depth,INT_MIN,INT_MAX) ; 
}

