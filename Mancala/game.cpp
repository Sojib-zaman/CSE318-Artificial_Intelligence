#include<bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include "player.h"
using namespace std;
void show_prompt()
{
    cout<<"Pick a playing option" <<endl ; 
    cout<<"1. Human vs Human"<<endl ; 
    cout<<"2. Human vs AI"<<endl ; 
    cout<<"3. AI vs AI"<<endl ; 
}
bool unfinished_game(board b)
{
    return b.winner()==INT_MIN? true : false ; 
}
int take_user_input()
{
    int pit ; 
    cout<<"choose pit no to move"<<endl ; 
    cin>>pit;
    return pit ;  

}

int main()
{


    show_prompt() ; 
    int game_mode ; 
    cin>>game_mode ; 
   // cout<<"Current game mode is "<<game_mode<<endl ; 
    int pit_no ; 


    int current_player = 0 ; 
    int err_player=-1 ; 
    int move  ; 



    player p1(0,5,3) ; 
    player p2(1,8,4) ; 


    board board ; 
    
    board.show_board() ; 


    
    

    while (!board.endgame())
    {
       cout<<"Current player : "<<current_player<<endl ; 
       if(current_player==INT_MIN || current_player==-1)
       {
            cout<<"please choose right input"<<endl ; 
            current_player = err_player ; 
            
       }
       if(current_player!=-1)
            err_player=current_player ;
       
       if(game_mode==1) //HUMAN VS HUMAN 
            pit_no = take_user_input()  ; 
       else if(game_mode==3)
       {

        if(current_player==0)
            pit_no = p1.callminmax(board) ;
        else if(current_player==1)
            pit_no = p2.callminmax(board) ;
        else {
			cout << "No such player: " << current_player << endl;
		}

        //cout<<"Pit No. : "<<pit_no<<endl ;
       }
       else if(game_mode==2)
       {
            if(current_player==0)pit_no=take_user_input() ; 
            else pit_no = p1.callminmax(board) ; 
       }
       cout<<"Moving pit no : "<<pit_no<<endl ; 
       current_player = board.move(current_player, pit_no) ; 
       board.show_board()  ; 
       
    }
    


    if(board.winner()==-1)cout<<"Draw"<<endl ; 
    else cout<<"\033[35mPlayer "<<board.winner()+1<<" won\033[0m"<<endl ; 
    cout<<"\033[36mPlayer 1\033[0m : "<<board.p1_lane_total_stone()+board.storage[0]<<"----"<<board.p2_lane_total_stone()+board.storage[1]<<" :\033[33m Player 2\033[0m"<<endl ; 
 



    

    
}