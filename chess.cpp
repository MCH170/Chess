/*
Chess by MCH170

Shared under European Union Public License 1.1


Each player types the coordinates of the piece he wants to move and the coordinates of the destination separated by space: eg. "e2 e4"

Checks are pointed out by the code but checkmates and stalemates are up to the players to figure out.

The move "en passant" is not implemented.
*/


#include<iostream>
#include<cmath>
#include<string>
using namespace std;

char board[8][8]={ {'r', 'k', 'b', 'q', '&', 'b', 'k', 'r'}, {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'}, {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'}, {'R', 'K', 'B', 'Q', '@', 'B', 'K', 'R'} };
bool rookhasmoved[4], kinghasmoved[2];
int wking[2]={7,4}, bking[2]={0,4};

void print(){
    cout<<endl<<endl;
    for(int i=0; i<8; i++){
        cout<<" "<<8-i<<" |";
        for(int j=0; j<8; j++){
            cout<<" "<<board[i][j]<<" |";
        }
        cout<<endl<<"   ---------------------------------"<<endl;;
    }
    cout<<"     a   b   c   d   e   f   g   h"<<endl;
}

void translate(int &frow, int &trow){
    frow=8-frow;
    trow=8-trow;
}

bool checkcheck(char colour, int row, int col){
    bool check=false;
    bool leave;
    int updiff, downdiff, rightdiff, leftdiff, urdiff, uldiff, drdiff, dldiff, i;

    updiff=row;
    downdiff=7-row;
    rightdiff=7-col;
    leftdiff=col;

    if(updiff>=rightdiff)//upright
        urdiff=rightdiff;
    else
        urdiff=updiff;

    if(downdiff>=rightdiff)//downright
        drdiff=rightdiff;
    else
        drdiff=downdiff;

    if(updiff>=leftdiff)//upleft
        uldiff=leftdiff;
    else
        uldiff=updiff;

    if(downdiff>=leftdiff)//downleft
        dldiff=leftdiff;
    else
        dldiff=downdiff;

    if(colour=='w'){
        if(board[row-1][col+1]=='p')//pawn upright
            return true;
        if(board[row-1][col-1]=='p')//pawn upleft
            return true;
        if(board[row-2][col+1]=='k')//knight upright
            return true;
        if(board[row-1][col+2]=='k')//knight upright
            return true;
        if(board[row-2][col-1]=='k')//knight upleft
            return true;
        if(board[row-1][col-2]=='k')//knight upleft
            return true;
        if(board[row+2][col+1]=='k')//knight downright
            return true;
        if(board[row+1][col+2]=='k')//knight downright
            return true;
        if(board[row+2][col-1]=='k')//knight downleft
            return true;
        if(board[row+1][col-2]=='k')//knight downleft
            return true;

        for(i=row-1; i<row+2; i++){
            for(int j=col-1; j<col+2; j++){
                if(board[i][j]=='&')
                    return true;
            }
        }

        i=1;//--------up
        leave=false;
        while((i<=updiff)&&(!leave)){
            if((board[row-i][col]=='r')||(board[row-i][col]=='q')){
                return true;
                leave=true;
            }else{
                if((board[row-i][col]=='R')||(board[row-i][col]=='K')||(board[row-i][col]=='B')||(board[row-i][col]=='Q')||(board[row-i][col]=='P')||(board[row-i][col]=='b')||(board[row-i][col]=='k')||(board[row-i][col]=='p')||(board[row-i][col]=='&')){
                    leave=true;
                }
            }
            i++;
        }

        i=1;//---------down
        leave=false;
        while((i<=downdiff)&&(!leave)){
            if((board[row+i][col]=='r')||(board[row+i][col]=='q')){
                return true;
                leave=true;
            }else{
                if((board[row+i][col]=='R')||(board[row+i][col]=='K')||(board[row+i][col]=='B')||(board[row+i][col]=='Q')||(board[row+i][col]=='P')||(board[row+i][col]=='b')||(board[row+i][col]=='k')||(board[row+i][col]=='p')||(board[row+i][col]=='&')){
                    leave=true;
                }
            }
            i++;
        }

        i=1;//---------right
        leave=false;
        while((i<=rightdiff)&&(!leave)){
            if((board[row][col+i]=='r')||(board[row][col+i]=='q')){
                return true;
                leave=true;
            }else{
                if((board[row][col+i]=='R')||(board[row][col+i]=='K')||(board[row][col+i]=='B')||(board[row][col+i]=='Q')||(board[row][col+i]=='P')||(board[row][col+i]=='b')||(board[row][col+i]=='k')||(board[row][col+i]=='p')||(board[row][col+i]=='&')){
                    leave=true;
                }
            }
            i++;
        }

        i=1;//---------left
        leave=false;
        while((i<=leftdiff)&&(!leave)){
            if((board[row][col-i]=='r')||(board[row][col-i]=='q')){
                return true;
                leave=true;
            }else{
                if((board[row][col-i]=='R')||(board[row][col-i]=='K')||(board[row][col-i]=='B')||(board[row][col-i]=='Q')||(board[row][col-i]=='P')||(board[row][col-i]=='b')||(board[row][col-i]=='k')||(board[row][col-i]=='p')||(board[row][col-i]=='&')){
                    leave=true;
                }
            }
            i++;
        }

        i=1;//--------upright
        leave=false;
        while((i<=urdiff)&&(!leave)){
            if((board[row-i][col+i]=='b')||(board[row-i][col+i]=='q')){
                return true;
                leave=true;
            }else{
                if((board[row-i][col+i]=='R')||(board[row-i][col+i]=='K')||(board[row-i][col+i]=='B')||(board[row-i][col+i]=='Q')||(board[row-i][col+i]=='P')||(board[row-i][col+i]=='r')||(board[row-i][col+i]=='k')||(board[row-i][col+i]=='p')||(board[row-i][col+i]=='&')){
                    leave=true;
                }
            }
            i++;
        }

        i=1;//--------upleft
        leave=false;
        while((i<=uldiff)&&(!leave)){
            if((board[row-i][col-i]=='b')||(board[row-i][col-i]=='q')){
                return true;
                leave=true;
            }else{
                if((board[row-i][col-i]=='R')||(board[row-i][col-i]=='K')||(board[row-i][col-i]=='B')||(board[row-i][col-i]=='Q')||(board[row-i][col-i]=='P')||(board[row-i][col-i]=='r')||(board[row-i][col-i]=='k')||(board[row-i][col-i]=='p')||(board[row-i][col-i]=='&')){
                    leave=true;
                }
            }
            i++;
        }

        i=1;//--------downright
        leave=false;
        while((i<=drdiff)&&(!leave)){
            if((board[row+i][col+i]=='b')||(board[row+i][col+i]=='q')){
                return true;
                leave=true;
            }else{
                if((board[row+i][col+i]=='R')||(board[row+i][col+i]=='K')||(board[row+i][col+i]=='B')||(board[row+i][col+i]=='Q')||(board[row+i][col+i]=='P')||(board[row+i][col+i]=='r')||(board[row+i][col+i]=='k')||(board[row+i][col+i]=='p')||(board[row+i][col+i]=='&')){
                    leave=true;
                }
            }
            i++;
        }

        i=1;//--------downleft
        leave=false;
        while((i<=dldiff)&&(!leave)){
            if((board[row+i][col-i]=='b')||(board[row+i][col-i]=='q')){
                return true;
                leave=true;
            }else{
                if((board[row+i][col-i]=='R')||(board[row+i][col-i]=='K')||(board[row+i][col-i]=='B')||(board[row+i][col-i]=='Q')||(board[row+i][col-i]=='P')||(board[row+i][col-i]=='r')||(board[row+i][col-i]=='k')||(board[row+i][col-i]=='p')||(board[row+i][col-i]=='&')){
                    leave=true;
                }
            }
            i++;
        }
            //--------------------------------------END WHITE
    }else{
        if(board[row+1][col+1]=='P')//pawn upright
            return true;
        if(board[row+1][col-1]=='P')//pawn upleft
            return true;
        if(board[row-2][col+1]=='K')//knight upright
            return true;
        if(board[row-1][col+2]=='K')//knight upright
            return true;
        if(board[row-2][col-1]=='K')//knight upleft
            return true;
        if(board[row-1][col-2]=='K')//knight upleft
            return true;
        if(board[row+2][col+1]=='K')//knight downright
            return true;
        if(board[row+1][col+2]=='K')//knight downright
            return true;
        if(board[row+2][col-1]=='K')//knight downleft
            return true;
        if(board[row+1][col-2]=='K')//knight downleft
            return true;

        for(i=row-1; i<row+2; i++){
            for(int j=col-1; j<col+2; j++){
                if(board[i][j]=='@')
                    return true;
            }
        }

        i=1;//--------up
        leave=false;
        while((i<=updiff)&&(!leave)){
            if((board[row-i][col]=='R')||(board[row-i][col]=='Q')){
                return true;
                leave=true;
            }else{
                if((board[row-i][col]=='r')||(board[row-i][col]=='k')||(board[row-i][col]=='b')||(board[row-i][col]=='q')||(board[row-i][col]=='p')||(board[row-i][col]=='B')||(board[row-i][col]=='K')||(board[row-i][col]=='P')||(board[row-i][col]=='@')){
                    leave=true;
                }
            }
            i++;
        }

        i=1;//---------down
        leave=false;
        while((i<=downdiff)&&(!leave)){
            if((board[row+i][col]=='R')||(board[row+i][col]=='Q')){
                return true;
                leave=true;
            }else{
                if((board[row+i][col]=='r')||(board[row+i][col]=='k')||(board[row+i][col]=='b')||(board[row+i][col]=='q')||(board[row+i][col]=='p')||(board[row+i][col]=='B')||(board[row+i][col]=='K')||(board[row+i][col]=='P')||(board[row+i][col]=='@')){
                    leave=true;
                }
            }
            i++;
        }

        i=1;//---------right
        leave=false;
        while((i<=rightdiff)&&(!leave)){
            if((board[row][col+i]=='R')||(board[row][col+i]=='Q')){
                return true;
                leave=true;
            }else{
                if((board[row][col+i]=='r')||(board[row][col+i]=='k')||(board[row][col+i]=='b')||(board[row][col+i]=='q')||(board[row][col+i]=='p')||(board[row][col+i]=='B')||(board[row][col+i]=='K')||(board[row][col+i]=='P')||(board[row][col+i]=='@')){
                    leave=true;
                }
            }
            i++;
        }

        i=1;//---------left
        leave=false;
        while((i<=leftdiff)&&(!leave)){
            if((board[row][col-i]=='R')||(board[row][col-i]=='Q')){
                return true;
                leave=true;
            }else{
                if((board[row][col-i]=='r')||(board[row][col-i]=='k')||(board[row][col-i]=='b')||(board[row][col-i]=='q')||(board[row][col-i]=='p')||(board[row][col-i]=='B')||(board[row][col-i]=='K')||(board[row][col-i]=='P')||(board[row][col-i]=='@')){
                    leave=true;
                }
            }
            i++;
        }

        i=1;//--------upright
        leave=false;
        while((i<=urdiff)&&(!leave)){
            if((board[row-i][col+i]=='B')||(board[row-i][col+i]=='Q')){
                return true;
                leave=true;
            }else{
                if((board[row-i][col+i]=='r')||(board[row-i][col+i]=='k')||(board[row-i][col+i]=='b')||(board[row-i][col+i]=='q')||(board[row-i][col+i]=='p')||(board[row-i][col+i]=='R')||(board[row-i][col+i]=='K')||(board[row-i][col+i]=='P')||(board[row-i][col+i]=='@')){
                    leave=true;
                }
            }
            i++;
        }

        i=1;//--------upleft
        leave=false;
        while((i<=uldiff)&&(!leave)){
            if((board[row-i][col-i]=='B')||(board[row-i][col-i]=='Q')){
                return true;
                leave=true;
            }else{
                if((board[row-i][col-i]=='r')||(board[row-i][col-i]=='k')||(board[row-i][col-i]=='b')||(board[row-i][col-i]=='q')||(board[row-i][col-i]=='p')||(board[row-i][col-i]=='R')||(board[row-i][col-i]=='K')||(board[row-i][col-i]=='P')||(board[row-i][col-i]=='@')){
                    leave=true;
                }
            }
            i++;
        }

        i=1;//--------downright
        leave=false;
        while((i<=drdiff)&&(!leave)){
            if((board[row+i][col+i]=='B')||(board[row+i][col+i]=='Q')){
                return true;
                leave=true;
            }else{
                if((board[row+i][col+i]=='r')||(board[row+i][col+i]=='k')||(board[row+i][col+i]=='b')||(board[row+i][col+i]=='q')||(board[row+i][col+i]=='p')||(board[row+i][col+i]=='R')||(board[row+i][col+i]=='K')||(board[row+i][col+i]=='P')||(board[row+i][col+i]=='@')){
                    leave=true;
                }
            }
            i++;
        }

        i=1;//--------downleft
        leave=false;
        while((i<=dldiff)&&(!leave)){
            if((board[row+i][col-i]=='B')||(board[row+i][col-i]=='Q')){
                return true;
                leave=true;
            }else{
                if((board[row+i][col-i]=='r')||(board[row+i][col-i]=='k')||(board[row+i][col-i]=='b')||(board[row+i][col-i]=='q')||(board[row+i][col-i]=='p')||(board[row+i][col-i]=='R')||(board[row+i][col-i]=='K')||(board[row+i][col-i]=='P')||(board[row+i][col-i]=='@')){
                    leave=true;
                }
            }
            i++;
        }
            //----------------END BLACK
    }
    return false;
}

bool checkmove(char colour, int frow, int fcol, int trow, int tcol){
    char tempf=board[frow][fcol];
    char tempt=board[trow][tcol];

    if(colour=='w'){//white
        board[trow][tcol]=board[frow][fcol];
        board[frow][fcol]=' ';

        if(checkcheck(colour, wking[0], wking[1])){
            board[trow][tcol]=tempt;
            board[frow][fcol]=tempf;
            return false;
        }else{
            board[trow][tcol]=tempt;
            board[frow][fcol]=tempf;
            return true;
        }
    }else{//black
        board[trow][tcol]=board[frow][fcol];
        board[frow][fcol]=' ';

        if(checkcheck(colour, bking[0], bking[1])){
            board[trow][tcol]=tempt;
            board[frow][fcol]=tempf;
            return false;
        }else{
            board[trow][tcol]=tempt;
            board[frow][fcol]=tempf;
            return true;
        }
    }//end
}

bool truepos(char colour, int r, int c){
    if(colour=='w'){
        if((board[r][c]=='R')||(board[r][c]=='K')||(board[r][c]=='B')||(board[r][c]=='Q')||(board[r][c]=='@')||(board[r][c]=='P'))
            return false;
        else{
            cout<<"Invalid position"<<endl;
            return true;
        }
    }else{
        if((board[r][c]=='r')||(board[r][c]=='k')||(board[r][c]=='b')||(board[r][c]=='q')||(board[r][c]=='&')||(board[r][c]=='p'))
            return false;
        else{
            cout<<"Invalid position"<<endl;
            return true;
        }
    }
}

bool truetogo(int row, int col){
    if((row>=0)&&(row<=7)&&(col>=0)&&(col<=7))
        return true;
    else{
        cout<<"Invalid move"<<endl;
        return false;
    }
}

bool truemove(int frow, int fcol, int trow, int tcol){
    char piece= board[frow][fcol];

    switch (piece){
        case 'P':{

            if(!checkmove('w', frow, fcol, trow, tcol))
                cout<<endl<<"Check - ";

            if((tcol==fcol)&&(trow==frow-1)&&(board[trow][tcol]==' ')&&checkmove('w', frow, fcol, trow, tcol))// pawn move 1
                return true;
            if((trow==frow-1)&&(tcol==fcol+1)&&((board[trow][tcol]=='r')&&checkmove('w', frow, fcol, trow, tcol)||(board[trow][tcol]=='k')||(board[trow][tcol]=='b')||(board[trow][tcol]=='q')||(board[trow][tcol]=='&')||(board[trow][tcol]=='p')))//pawn attack right
                return true;
            if((trow==frow-1)&&(tcol==fcol-1)&&((board[trow][tcol]=='r')&&checkmove('w', frow, fcol, trow, tcol)||(board[trow][tcol]=='k')||(board[trow][tcol]=='b')||(board[trow][tcol]=='q')||(board[trow][tcol]=='&')||(board[trow][tcol]=='p')))//pawn attack left
                return true;
            if((tcol==fcol)&&(trow==frow-2)&&(board[trow][tcol]==' ')&&(board[trow+1][tcol]==' ')&&(frow==6)&&checkmove('w', frow, fcol, trow, tcol))// pawn move 2
                return true;
        }break;

        case 'p':{

            if(!checkmove('b', frow, fcol, trow, tcol))
                cout<<endl<<"Check - ";

            if((tcol==fcol)&&(trow==frow+1)&&(board[trow][tcol]==' ')&&checkmove('b', frow, fcol, trow, tcol))// pawn move 1
                return true;
            if((trow==frow+1)&&(tcol==fcol+1)&&((board[trow][tcol]=='R')&&checkmove('b', frow, fcol, trow, tcol)||(board[trow][tcol]=='K')||(board[trow][tcol]=='B')||(board[trow][tcol]=='Q')||(board[trow][tcol]=='@')||(board[trow][tcol]=='P')))//pawn attack right
                return true;
            if((trow==frow+1)&&(tcol==fcol-1)&&((board[trow][tcol]=='R')&&checkmove('b', frow, fcol, trow, tcol)||(board[trow][tcol]=='K')||(board[trow][tcol]=='B')||(board[trow][tcol]=='Q')||(board[trow][tcol]=='@')||(board[trow][tcol]=='P')))//pawn attack left
                return true;
            if((tcol==fcol)&&(trow==frow+2)&&(board[trow][tcol]==' ')&&(board[trow-1][tcol]==' ')&&(frow==1)&&checkmove('b', frow, fcol, trow, tcol))// pawn move 2
                return true;
        }break;

        case 'R':{
            bool clean=true;

            if(!checkmove('w', frow, fcol, trow, tcol))
                cout<<endl<<"Check - ";

            if((tcol==fcol)&&(trow>frow)){//--------------------rook move down
                    int diff=trow-frow;
                    for(int i=1; i<diff; i++){
                        clean&=(board[frow+i][fcol]==' ');
                    }
                    if((board[trow][tcol]=='r')||(board[trow][tcol]=='k')||(board[trow][tcol]=='b')||(board[trow][tcol]=='q')||(board[trow][tcol]=='&')||(board[trow][tcol]=='p')||(board[trow][tcol]==' '))
                        clean&=true;
                    else
                        clean&=false;
                    if((clean)&&checkmove('w', frow, fcol, trow, tcol)){
                        if((fcol==0)&&(frow==7))
                            rookhasmoved[2]==true;
                        if((fcol==7)&&(frow==7))
                            rookhasmoved[3]==true;
                        return true;
                    }else{
                        cout<<"Invalid move"<<endl;
                        return false;
                    }
            }

            if((tcol==fcol)&&(trow<frow)){//--------------------rook move up
                    int diff=trow-frow;
                    diff=abs(diff);
                    for(int i=1; i<abs(diff); i++){
                        clean&=(board[frow-i][fcol]==' ');
                    }
                    if((board[trow][tcol]=='r')||(board[trow][tcol]=='k')||(board[trow][tcol]=='b')||(board[trow][tcol]=='q')||(board[trow][tcol]=='&')||(board[trow][tcol]=='p')||(board[trow][tcol]==' '))
                        clean&=true;
                    else
                        clean&=false;
                    if((clean)&&checkmove('w', frow, fcol, trow, tcol)){
                        if((fcol==0)&&(frow==7))
                            rookhasmoved[2]==true;
                        if((fcol==7)&&(frow==7))
                            rookhasmoved[3]==true;
                        return true;
                    }else{
                        cout<<"Invalid move"<<endl;
                        return false;
                    }
            }

            if((trow==frow)&&(tcol>fcol)){//--------------------rook move right
                    int diff=tcol-fcol;
                    for(int i=1; i<abs(diff); i++){
                        clean&=(board[frow][fcol+i]==' ');
                    }
                    if((board[trow][tcol]=='r')||(board[trow][tcol]=='k')||(board[trow][tcol]=='b')||(board[trow][tcol]=='q')||(board[trow][tcol]=='&')||(board[trow][tcol]=='p')||(board[trow][tcol]==' '))
                        clean&=true;
                    else
                        clean&=false;
                    if((clean)&&checkmove('w', frow, fcol, trow, tcol)){
                        if((fcol==0)&&(frow==7))
                            rookhasmoved[2]==true;
                        if((fcol==7)&&(frow==7))
                            rookhasmoved[3]==true;
                        return true;
                    }else{
                        cout<<"Invalid move"<<endl;
                        return false;
                    }
            }

            if((trow==frow)&&(tcol<fcol)){//--------------------rook move left
                    int diff=tcol-fcol;
                    for(int i=1; i<abs(diff); i++){
                        clean&=(board[frow][fcol-i]==' ');
                    }
                    if((board[trow][tcol]=='r')||(board[trow][tcol]=='k')||(board[trow][tcol]=='b')||(board[trow][tcol]=='q')||(board[trow][tcol]=='&')||(board[trow][tcol]=='p')||(board[trow][tcol]==' '))
                        clean&=true;
                    else
                        clean&=false;
                    if((clean)&&checkmove('w', frow, fcol, trow, tcol)){
                        if((fcol==0)&&(frow==7))
                            rookhasmoved[2]==true;
                        if((fcol==7)&&(frow==7))
                            rookhasmoved[3]==true;
                        return true;
                    }else{
                        cout<<"Invalid move"<<endl;
                        return false;
                    }
            }

        }break;

        case 'r':{
            bool clean=true;

            if(!checkmove('b', frow, fcol, trow, tcol))
                cout<<endl<<"Check - ";

            if((tcol==fcol)&&(trow>frow)){//--------------------rook move down
                    int diff=trow-frow;
                    for(int i=1; i<diff; i++){
                        clean&=(board[frow+i][fcol]==' ');
                    }
                    if((board[trow][tcol]=='R')||(board[trow][tcol]=='K')||(board[trow][tcol]=='B')||(board[trow][tcol]=='Q')||(board[trow][tcol]=='@')||(board[trow][tcol]=='P')||(board[trow][tcol]==' '))
                        clean&=true;
                    else
                        clean&=false;
                    if((clean)&&checkmove('b', frow, fcol, trow, tcol)){
                        if((fcol==0)&&(frow==0))
                            rookhasmoved[0]==true;
                        if((fcol==7)&&(frow==0))
                            rookhasmoved[1]==true;
                        return true;
                    }else{
                        cout<<"Invalid move"<<endl;
                        return false;
                    }
            }

            if((tcol==fcol)&&(trow<frow)){//--------------------rook move up
                    int diff=trow-frow;
                    diff=abs(diff);
                    for(int i=1; i<abs(diff); i++){
                        clean&=(board[frow-i][fcol]==' ');
                    }
                    if((board[trow][tcol]=='R')||(board[trow][tcol]=='K')||(board[trow][tcol]=='B')||(board[trow][tcol]=='Q')||(board[trow][tcol]=='@')||(board[trow][tcol]=='P')||(board[trow][tcol]==' '))
                        clean&=true;
                    else
                        clean&=false;
                    if((clean)&&checkmove('b', frow, fcol, trow, tcol)){
                        if((fcol==0)&&(frow==0))
                            rookhasmoved[0]==true;
                        if((fcol==7)&&(frow==0))
                            rookhasmoved[1]==true;
                        return true;
                    }else{
                        cout<<"Invalid move"<<endl;
                        return false;
                    }
            }

            if((trow==frow)&&(tcol>fcol)){//--------------------rook move right
                    int diff=tcol-fcol;
                    for(int i=1; i<abs(diff); i++){
                        clean&=(board[frow][fcol+i]==' ');
                    }
                    if((board[trow][tcol]=='R')||(board[trow][tcol]=='K')||(board[trow][tcol]=='B')||(board[trow][tcol]=='Q')||(board[trow][tcol]=='@')||(board[trow][tcol]=='P')||(board[trow][tcol]==' '))
                        clean&=true;
                    else
                        clean&=false;
                    if((clean)&&checkmove('b', frow, fcol, trow, tcol)){
                        if((fcol==0)&&(frow==0))
                            rookhasmoved[0]==true;
                        if((fcol==7)&&(frow==0))
                            rookhasmoved[1]==true;
                        return true;
                    }else{
                        cout<<"Invalid move"<<endl;
                        return false;
                    }
            }

            if((trow==frow)&&(tcol<fcol)){//--------------------rook move left
                    int diff=tcol-fcol;
                    for(int i=1; i<abs(diff); i++){
                        clean&=(board[frow][fcol-i]==' ');
                    }
                    if((board[trow][tcol]=='R')||(board[trow][tcol]=='K')||(board[trow][tcol]=='B')||(board[trow][tcol]=='Q')||(board[trow][tcol]=='@')||(board[trow][tcol]=='P')||(board[trow][tcol]==' '))
                        clean&=true;
                    else
                        clean&=false;
                    if((clean)&&checkmove('b', frow, fcol, trow, tcol)){
                        if((fcol==0)&&(frow==0))
                            rookhasmoved[0]==true;
                        if((fcol==7)&&(frow==0))
                            rookhasmoved[1]==true;
                        return true;
                    }else{
                        cout<<"Invalid move"<<endl;
                        return false;
                    }
            }

        }break;

        case 'B':{
            bool clean=true;

            if(!checkmove('w', frow, fcol, trow, tcol))
                cout<<endl<<"Check - ";

            if((trow<frow)&&(tcol>fcol)){//----------------bishop move upright
                int diff=tcol-fcol;
                for(int i=1; i<diff; i++){
                    clean&=(board[frow-i][fcol+i]==' ');
                }
                if((board[trow][tcol]=='r')||(board[trow][tcol]=='k')||(board[trow][tcol]=='b')||(board[trow][tcol]=='q')||(board[trow][tcol]=='&')||(board[trow][tcol]=='p')||(board[trow][tcol]==' '))
                        clean&=true;
                    else
                        clean&=false;
                if((clean)&&(frow-trow==tcol-fcol)&&checkmove('w', frow, fcol, trow, tcol))
                        return true;
                    else{
                        cout<<"Invalid move"<<endl;
                        return false;
                }
            }//d

            if((trow<frow)&&(tcol<fcol)){//----------------bishop move upleft
                int diff=fcol-tcol;//+
                for(int i=1; i<diff; i++){
                    clean&=(board[frow-i][fcol-i]==' ');
                }
                if((board[trow][tcol]=='r')||(board[trow][tcol]=='k')||(board[trow][tcol]=='b')||(board[trow][tcol]=='q')||(board[trow][tcol]=='&')||(board[trow][tcol]=='p')||(board[trow][tcol]==' '))
                        clean&=true;
                    else
                        clean&=false;
                if((clean)&&(frow-trow==fcol-tcol)&&checkmove('w', frow, fcol, trow, tcol))
                        return true;
                    else{
                        cout<<"Invalid move"<<endl;
                        return false;
                }
            }//d

            if((trow>frow)&&(tcol>fcol)){//----------------bishop move downright
                int diff=tcol-fcol;
                for(int i=1; i<diff; i++){
                    clean&=(board[frow+i][fcol+i]==' ');
                }
                if((board[trow][tcol]=='r')||(board[trow][tcol]=='k')||(board[trow][tcol]=='b')||(board[trow][tcol]=='q')||(board[trow][tcol]=='&')||(board[trow][tcol]=='p')||(board[trow][tcol]==' '))
                        clean&=true;
                    else
                        clean&=false;
                if((clean)&&(trow-frow==tcol-fcol)&&checkmove('w', frow, fcol, trow, tcol))
                        return true;
                    else{
                        cout<<"Invalid move"<<endl;
                        return false;
                }
            }//d

            if((trow>frow)&&(tcol<fcol)){//----------------bishop move downleft
                int diff=fcol-tcol;//+
                for(int i=1; i<diff; i++){
                    clean&=(board[frow+i][fcol-i]==' ');
                }
                if((board[trow][tcol]=='r')||(board[trow][tcol]=='k')||(board[trow][tcol]=='b')||(board[trow][tcol]=='q')||(board[trow][tcol]=='&')||(board[trow][tcol]=='p')||(board[trow][tcol]==' '))
                        clean&=true;
                    else
                        clean&=false;
                if((clean)&&(trow-frow==fcol-tcol)&&checkmove('w', frow, fcol, trow, tcol))
                        return true;
                    else{
                        cout<<"Invalid move"<<endl;
                        return false;
                }
            }//d

        }break;

        case 'b':{
            bool clean=true;

            if(!checkmove('b', frow, fcol, trow, tcol))
                cout<<endl<<"Check - ";

            if((trow<frow)&&(tcol>fcol)){//----------------bishop move upright
                int diff=tcol-fcol;
                for(int i=1; i<diff; i++){
                    clean&=(board[frow-i][fcol+i]==' ');
                }
                if((board[trow][tcol]=='R')||(board[trow][tcol]=='K')||(board[trow][tcol]=='B')||(board[trow][tcol]=='Q')||(board[trow][tcol]=='@')||(board[trow][tcol]=='P')||(board[trow][tcol]==' '))
                        clean&=true;
                    else
                        clean&=false;
                if((clean)&&(frow-trow==tcol-fcol)&&checkmove('b', frow, fcol, trow, tcol))
                        return true;
                    else{
                        cout<<"Invalid move"<<endl;
                        return false;
                }
            }//d

            if((trow<frow)&&(tcol<fcol)){//----------------bishop move upleft
                int diff=fcol-tcol;//+
                for(int i=1; i<diff; i++){
                    clean&=(board[frow-i][fcol-i]==' ');
                }
                if((board[trow][tcol]=='R')||(board[trow][tcol]=='K')||(board[trow][tcol]=='B')||(board[trow][tcol]=='Q')||(board[trow][tcol]=='@')||(board[trow][tcol]=='P')||(board[trow][tcol]==' '))
                        clean&=true;
                    else
                        clean&=false;
                if((clean)&&(frow-trow==fcol-tcol)&&checkmove('b', frow, fcol, trow, tcol))
                        return true;
                    else{
                        cout<<"Invalid move"<<endl;
                        return false;
                }
            }//d

            if((trow>frow)&&(tcol>fcol)){//----------------bishop move downright
                int diff=tcol-fcol;
                for(int i=1; i<diff; i++){
                    clean&=(board[frow+i][fcol+i]==' ');
                }
                if((board[trow][tcol]=='R')||(board[trow][tcol]=='K')||(board[trow][tcol]=='B')||(board[trow][tcol]=='Q')||(board[trow][tcol]=='@')||(board[trow][tcol]=='P')||(board[trow][tcol]==' '))
                        clean&=true;
                    else
                        clean&=false;
                if((clean)&&(trow-frow==tcol-fcol)&&checkmove('b', frow, fcol, trow, tcol))
                        return true;
                    else{
                        cout<<"Invalid move"<<endl;
                        return false;
                }
            }//d

            if((trow>frow)&&(tcol<fcol)){//----------------bishop move downleft
                int diff=fcol-tcol;//+
                for(int i=1; i<diff; i++){
                    clean&=(board[frow+i][fcol-i]==' ');
                }
                if((board[trow][tcol]=='R')||(board[trow][tcol]=='K')||(board[trow][tcol]=='B')||(board[trow][tcol]=='Q')||(board[trow][tcol]=='@')||(board[trow][tcol]=='P')||(board[trow][tcol]==' '))
                        clean&=true;
                    else
                        clean&=false;
                if((clean)&&(trow-frow==fcol-tcol)&&checkmove('b', frow, fcol, trow, tcol))
                        return true;
                    else{
                        cout<<"Invalid move"<<endl;
                        return false;
                }
            }//d

        }break;

        case 'Q':{
            bool clean=true;

            if(!checkmove('w', frow, fcol, trow, tcol))
                cout<<endl<<"Check - ";

            if((tcol==fcol)&&(trow<frow)){//--------------------queen move up
                    int diff=trow-frow;
                    diff=abs(diff);
                    for(int i=1; i<abs(diff); i++){
                        clean&=(board[frow-i][fcol]==' ');
                    }
                    if((board[trow][tcol]=='r')||(board[trow][tcol]=='k')||(board[trow][tcol]=='b')||(board[trow][tcol]=='q')||(board[trow][tcol]=='&')||(board[trow][tcol]=='p')||(board[trow][tcol]==' '))
                        clean&=true;
                    else
                        clean&=false;
                    if((clean)&&checkmove('w', frow, fcol, trow, tcol))
                        return true;
                    else{
                        cout<<"Invalid move"<<endl;
                        return false;
                }
            }

            if((tcol==fcol)&&(trow>frow)){//--------------------queen move down
                    int diff=trow-frow;
                    for(int i=1; i<diff; i++){
                        clean&=(board[frow+i][fcol]==' ');
                    }
                    if((board[trow][tcol]=='r')||(board[trow][tcol]=='k')||(board[trow][tcol]=='b')||(board[trow][tcol]=='q')||(board[trow][tcol]=='&')||(board[trow][tcol]=='p')||(board[trow][tcol]==' '))
                        clean&=true;
                    else
                        clean&=false;
                    if((clean)&&checkmove('w', frow, fcol, trow, tcol))
                        return true;
                    else{
                        cout<<"Invalid move"<<endl;
                        return false;
                }
            }

            if((trow==frow)&&(tcol>fcol)){//--------------------queen move right
                    int diff=tcol-fcol;
                    for(int i=1; i<abs(diff); i++){
                        clean&=(board[frow][fcol+i]==' ');
                    }
                    if((board[trow][tcol]=='r')||(board[trow][tcol]=='k')||(board[trow][tcol]=='b')||(board[trow][tcol]=='q')||(board[trow][tcol]=='&')||(board[trow][tcol]=='p')||(board[trow][tcol]==' '))
                        clean&=true;
                    else
                        clean&=false;
                    if((clean)&&checkmove('w', frow, fcol, trow, tcol))
                        return true;
                    else{
                        cout<<"Invalid move"<<endl;
                        return false;
                }
            }

            if((trow==frow)&&(tcol<fcol)){//--------------------queen move left
                    int diff=tcol-fcol;
                    for(int i=1; i<abs(diff); i++){
                        clean&=(board[frow][fcol-i]==' ');
                    }
                    if((board[trow][tcol]=='r')||(board[trow][tcol]=='k')||(board[trow][tcol]=='b')||(board[trow][tcol]=='q')||(board[trow][tcol]=='&')||(board[trow][tcol]=='p')||(board[trow][tcol]==' '))
                        clean&=true;
                    else
                        clean&=false;
                    if((clean)&&checkmove('w', frow, fcol, trow, tcol))
                        return true;
                    else{
                        cout<<"Invalid move"<<endl;
                        return false;
                }
            }

            if((trow<frow)&&(tcol>fcol)){//----------------queen move upright
                int diff=tcol-fcol;
                for(int i=1; i<diff; i++){
                    clean&=(board[frow-i][fcol+i]==' ');
                }
                if((board[trow][tcol]=='r')||(board[trow][tcol]=='k')||(board[trow][tcol]=='b')||(board[trow][tcol]=='q')||(board[trow][tcol]=='&')||(board[trow][tcol]=='p')||(board[trow][tcol]==' '))
                        clean&=true;
                    else
                        clean&=false;
                if((clean)&&(frow-trow==tcol-fcol)&&checkmove('w', frow, fcol, trow, tcol))
                        return true;
                    else{
                        cout<<"Invalid move"<<endl;
                        return false;
                }
            }//d

            if((trow<frow)&&(tcol<fcol)){//----------------queen move upleft
                int diff=fcol-tcol;//+
                for(int i=1; i<diff; i++){
                    clean&=(board[frow-i][fcol-i]==' ');
                }
                if((board[trow][tcol]=='r')||(board[trow][tcol]=='k')||(board[trow][tcol]=='b')||(board[trow][tcol]=='q')||(board[trow][tcol]=='&')||(board[trow][tcol]=='p')||(board[trow][tcol]==' '))
                        clean&=true;
                    else
                        clean&=false;
                if((clean)&&(frow-trow==fcol-tcol)&&checkmove('w', frow, fcol, trow, tcol))
                        return true;
                    else{
                        cout<<"Invalid move"<<endl;
                        return false;
                }
            }//d

            if((trow>frow)&&(tcol>fcol)){//----------------queen move downright
                int diff=tcol-fcol;
                for(int i=1; i<diff; i++){
                    clean&=(board[frow+i][fcol+i]==' ');
                }
                if((board[trow][tcol]=='r')||(board[trow][tcol]=='k')||(board[trow][tcol]=='b')||(board[trow][tcol]=='q')||(board[trow][tcol]=='&')||(board[trow][tcol]=='p')||(board[trow][tcol]==' '))
                        clean&=true;
                    else
                        clean&=false;
                if((clean)&&(trow-frow==tcol-fcol)&&checkmove('w', frow, fcol, trow, tcol))
                        return true;
                    else{
                        cout<<"Invalid move"<<endl;
                        return false;
                }
            }//d

            if((trow>frow)&&(tcol<fcol)){//----------------queen move downleft
                int diff=fcol-tcol;//+
                for(int i=1; i<diff; i++){
                    clean&=(board[frow+i][fcol-i]==' ');
                }
                if((board[trow][tcol]=='r')||(board[trow][tcol]=='k')||(board[trow][tcol]=='b')||(board[trow][tcol]=='q')||(board[trow][tcol]=='&')||(board[trow][tcol]=='p')||(board[trow][tcol]==' '))
                        clean&=true;
                    else
                        clean&=false;
                if((clean)&&(trow-frow==fcol-tcol)&&checkmove('w', frow, fcol, trow, tcol))
                        return true;
                    else{
                        cout<<"Invalid move"<<endl;
                        return false;
                }
            }//d

        }break;

        case 'q':{
            bool clean=true;

            if(!checkmove('b', frow, fcol, trow, tcol))
                cout<<endl<<"Check - ";

            if((tcol==fcol)&&(trow<frow)){//--------------------queen move up
                    int diff=trow-frow;
                    diff=abs(diff);
                    for(int i=1; i<abs(diff); i++){
                        clean&=(board[frow-i][fcol]==' ');
                    }
                    if((board[trow][tcol]=='R')||(board[trow][tcol]=='K')||(board[trow][tcol]=='B')||(board[trow][tcol]=='Q')||(board[trow][tcol]=='@')||(board[trow][tcol]=='P')||(board[trow][tcol]==' '))
                        clean&=true;
                    else
                        clean&=false;
                    if((clean)&&checkmove('b', frow, fcol, trow, tcol))
                        return true;
                    else{
                        cout<<"Invalid move"<<endl;
                        return false;
                }
            }

            if((tcol==fcol)&&(trow>frow)){//--------------------queen move down
                    int diff=trow-frow;
                    for(int i=1; i<diff; i++){
                        clean&=(board[frow+i][fcol]==' ');
                    }
                    if((board[trow][tcol]=='R')||(board[trow][tcol]=='K')||(board[trow][tcol]=='B')||(board[trow][tcol]=='Q')||(board[trow][tcol]=='@')||(board[trow][tcol]=='P')||(board[trow][tcol]==' '))
                        clean&=true;
                    else
                        clean&=false;
                    if((clean)&&checkmove('b', frow, fcol, trow, tcol))
                        return true;
                    else{
                        cout<<"Invalid move"<<endl;
                        return false;
                }
            }

            if((trow==frow)&&(tcol>fcol)){//--------------------queen move right
                    int diff=tcol-fcol;
                    for(int i=1; i<abs(diff); i++){
                        clean&=(board[frow][fcol+i]==' ');
                    }
                    if((board[trow][tcol]=='R')||(board[trow][tcol]=='K')||(board[trow][tcol]=='B')||(board[trow][tcol]=='Q')||(board[trow][tcol]=='@')||(board[trow][tcol]=='P')||(board[trow][tcol]==' '))
                        clean&=true;
                    else
                        clean&=false;
                    if((clean)&&checkmove('b', frow, fcol, trow, tcol))
                        return true;
                    else{
                        cout<<"Invalid move"<<endl;
                        return false;
                }
            }

            if((trow==frow)&&(tcol<fcol)){//--------------------queen move left
                    int diff=tcol-fcol;
                    for(int i=1; i<abs(diff); i++){
                        clean&=(board[frow][fcol-i]==' ');
                    }
                    if((board[trow][tcol]=='R')||(board[trow][tcol]=='K')||(board[trow][tcol]=='B')||(board[trow][tcol]=='Q')||(board[trow][tcol]=='@')||(board[trow][tcol]=='P')||(board[trow][tcol]==' '))
                        clean&=true;
                    else
                        clean&=false;
                    if((clean)&&checkmove('b', frow, fcol, trow, tcol))
                        return true;
                    else{
                        cout<<"Invalid move"<<endl;
                        return false;
                }
            }

            if((trow<frow)&&(tcol>fcol)){//----------------queen move upright
                int diff=tcol-fcol;
                for(int i=1; i<diff; i++){
                    clean&=(board[frow-i][fcol+i]==' ');
                }
                if((board[trow][tcol]=='R')||(board[trow][tcol]=='K')||(board[trow][tcol]=='B')||(board[trow][tcol]=='Q')||(board[trow][tcol]=='@')||(board[trow][tcol]=='P')||(board[trow][tcol]==' '))
                        clean&=true;
                    else
                        clean&=false;
                if((clean)&&(frow-trow==tcol-fcol)&&checkmove('b', frow, fcol, trow, tcol))
                        return true;
                    else{
                        cout<<"Invalid move"<<endl;
                        return false;
                }
            }//d

            if((trow<frow)&&(tcol<fcol)){//----------------queen move upleft
                int diff=fcol-tcol;//+
                for(int i=1; i<diff; i++){
                    clean&=(board[frow-i][fcol-i]==' ');
                }
                if((board[trow][tcol]=='R')||(board[trow][tcol]=='K')||(board[trow][tcol]=='B')||(board[trow][tcol]=='Q')||(board[trow][tcol]=='@')||(board[trow][tcol]=='P')||(board[trow][tcol]==' '))
                        clean&=true;
                    else
                        clean&=false;
                if((clean)&&(frow-trow==fcol-tcol)&&checkmove('b', frow, fcol, trow, tcol))//good
                        return true;
                    else{
                        cout<<"Invalid move"<<endl;
                        return false;
                }
            }//d

            if((trow>frow)&&(tcol>fcol)){//----------------queen move downright
                int diff=tcol-fcol;
                for(int i=1; i<diff; i++){
                    clean&=(board[frow+i][fcol+i]==' ');
                }
                if((board[trow][tcol]=='R')||(board[trow][tcol]=='K')||(board[trow][tcol]=='B')||(board[trow][tcol]=='Q')||(board[trow][tcol]=='@')||(board[trow][tcol]=='P')||(board[trow][tcol]==' '))
                        clean&=true;
                    else
                        clean&=false;
                if((clean)&&(trow-frow==tcol-fcol)&&checkmove('b', frow, fcol, trow, tcol))
                        return true;
                    else{
                        cout<<"Invalid move"<<endl;
                        return false;
                }
            }//d

            if((trow>frow)&&(tcol<fcol)){//----------------queen move downleft
                int diff=fcol-tcol;//+
                for(int i=1; i<diff; i++){
                    clean&=(board[frow+i][fcol-i]==' ');
                }
                if((board[trow][tcol]=='R')||(board[trow][tcol]=='K')||(board[trow][tcol]=='B')||(board[trow][tcol]=='Q')||(board[trow][tcol]=='@')||(board[trow][tcol]=='P')||(board[trow][tcol]==' '))
                        clean&=true;
                    else
                        clean&=false;
                if((clean)&&(trow-frow==fcol-tcol)&&checkmove('b', frow, fcol, trow, tcol))
                        return true;
                    else{
                        cout<<"Invalid move"<<endl;
                        return false;
                }
            }//d

        }break;

        case 'K':{

            if(!checkmove('w', frow, fcol, trow, tcol))
                cout<<endl<<"Check - ";

            if((trow<frow)&&(tcol>fcol)){//----------------knight move upright
                if((trow==frow-2)&&(tcol==fcol+1)&&checkmove('w', frow, fcol, trow, tcol)){
                    if((board[trow][tcol]=='r')||(board[trow][tcol]=='k')||(board[trow][tcol]=='b')||(board[trow][tcol]=='q')||(board[trow][tcol]=='&')||(board[trow][tcol]=='p')||(board[trow][tcol]==' '))
                        return true;
                    else{
                        cout<<"Invalid move"<<endl;
                        return false;
                    }
                }
                if((trow==frow-1)&&(tcol==fcol+2)&&checkmove('w', frow, fcol, trow, tcol)){
                    if((board[trow][tcol]=='r')||(board[trow][tcol]=='k')||(board[trow][tcol]=='b')||(board[trow][tcol]=='q')||(board[trow][tcol]=='&')||(board[trow][tcol]=='p')||(board[trow][tcol]==' '))
                        return true;
                    else{
                        cout<<"Invalid move"<<endl;
                        return false;
                    }
                }
            }

            if((trow<frow)&&(tcol<fcol)){//----------------knight move upleft
                if((trow==frow-2)&&(tcol==fcol-1)&&checkmove('w', frow, fcol, trow, tcol)){
                    if((board[trow][tcol]=='r')||(board[trow][tcol]=='k')||(board[trow][tcol]=='b')||(board[trow][tcol]=='q')||(board[trow][tcol]=='&')||(board[trow][tcol]=='p')||(board[trow][tcol]==' '))
                        return true;
                    else{
                        cout<<"Invalid move"<<endl;
                        return false;
                    }
                }
                if((trow==frow-1)&&(tcol==fcol-2)&&checkmove('w', frow, fcol, trow, tcol)){
                    if((board[trow][tcol]=='r')||(board[trow][tcol]=='k')||(board[trow][tcol]=='b')||(board[trow][tcol]=='q')||(board[trow][tcol]=='&')||(board[trow][tcol]=='p')||(board[trow][tcol]==' '))
                        return true;
                    else{
                        cout<<"Invalid move"<<endl;
                        return false;
                    }
                }
            }

            if((trow>frow)&&(tcol>fcol)){//----------------knight move downright
                if((trow==frow+2)&&(tcol==fcol+1)&&checkmove('w', frow, fcol, trow, tcol)){
                    if((board[trow][tcol]=='r')||(board[trow][tcol]=='k')||(board[trow][tcol]=='b')||(board[trow][tcol]=='q')||(board[trow][tcol]=='&')||(board[trow][tcol]=='p')||(board[trow][tcol]==' '))
                        return true;
                    else{
                        cout<<"Invalid move"<<endl;
                        return false;
                    }
                }
                if((trow==frow+1)&&(tcol==fcol+2)&&checkmove('w', frow, fcol, trow, tcol)){
                    if((board[trow][tcol]=='r')||(board[trow][tcol]=='k')||(board[trow][tcol]=='b')||(board[trow][tcol]=='q')||(board[trow][tcol]=='&')||(board[trow][tcol]=='p')||(board[trow][tcol]==' '))
                        return true;
                    else{
                        cout<<"Invalid move"<<endl;
                        return false;
                    }
                }
            }

            if((trow>frow)&&(tcol<fcol)){//----------------knight move downleft
                if((trow==frow+2)&&(tcol==fcol-1)&&checkmove('w', frow, fcol, trow, tcol)){
                    if((board[trow][tcol]=='r')||(board[trow][tcol]=='k')||(board[trow][tcol]=='b')||(board[trow][tcol]=='q')||(board[trow][tcol]=='&')||(board[trow][tcol]=='p')||(board[trow][tcol]==' '))
                        return true;
                    else{
                        cout<<"Invalid move"<<endl;
                        return false;
                    }
                }
                if((trow==frow+1)&&(tcol==fcol-2)&&checkmove('w', frow, fcol, trow, tcol)){
                    if((board[trow][tcol]=='r')||(board[trow][tcol]=='k')||(board[trow][tcol]=='b')||(board[trow][tcol]=='q')||(board[trow][tcol]=='&')||(board[trow][tcol]=='p')||(board[trow][tcol]==' '))
                        return true;
                    else{
                        cout<<"Invalid move"<<endl;
                        return false;
                    }
                }
            }

        }break;

        case 'k':{

            if(!checkmove('b', frow, fcol, trow, tcol))
                cout<<endl<<"Check - ";

            if((trow<frow)&&(tcol>fcol)){//----------------knight move upright
                if((trow==frow-2)&&(tcol==fcol+1)&&checkmove('b', frow, fcol, trow, tcol)){
                    if((board[trow][tcol]=='R')||(board[trow][tcol]=='K')||(board[trow][tcol]=='B')||(board[trow][tcol]=='Q')||(board[trow][tcol]=='@')||(board[trow][tcol]=='P')||(board[trow][tcol]==' '))
                        return true;
                    else{
                        cout<<"Invalid move"<<endl;
                        return false;
                    }
                }
                if((trow==frow-1)&&(tcol==fcol+2)&&checkmove('b', frow, fcol, trow, tcol)){
                    if((board[trow][tcol]=='R')||(board[trow][tcol]=='K')||(board[trow][tcol]=='B')||(board[trow][tcol]=='Q')||(board[trow][tcol]=='@')||(board[trow][tcol]=='P')||(board[trow][tcol]==' '))
                        return true;
                    else{
                        cout<<"Invalid move"<<endl;
                        return false;
                    }
                }
            }

            if((trow<frow)&&(tcol<fcol)){//----------------knight move upleft
                if((trow==frow-2)&&(tcol==fcol-1)&&checkmove('b', frow, fcol, trow, tcol)){
                    if((board[trow][tcol]=='R')||(board[trow][tcol]=='K')||(board[trow][tcol]=='B')||(board[trow][tcol]=='Q')||(board[trow][tcol]=='@')||(board[trow][tcol]=='P')||(board[trow][tcol]==' '))
                        return true;
                    else{
                        cout<<"Invalid move"<<endl;
                        return false;
                    }
                }
                if((trow==frow-1)&&(tcol==fcol-2)&&checkmove('b', frow, fcol, trow, tcol)){
                    if((board[trow][tcol]=='R')||(board[trow][tcol]=='K')||(board[trow][tcol]=='B')||(board[trow][tcol]=='Q')||(board[trow][tcol]=='@')||(board[trow][tcol]=='P')||(board[trow][tcol]==' '))
                        return true;
                    else{
                        cout<<"Invalid move"<<endl;
                        return false;
                    }
                }
            }

            if((trow>frow)&&(tcol>fcol)){//----------------knight move downright
                if((trow==frow+2)&&(tcol==fcol+1)&&checkmove('b', frow, fcol, trow, tcol)){
                    if((board[trow][tcol]=='R')||(board[trow][tcol]=='K')||(board[trow][tcol]=='B')||(board[trow][tcol]=='Q')||(board[trow][tcol]=='@')||(board[trow][tcol]=='P')||(board[trow][tcol]==' '))
                        return true;
                    else{
                        cout<<"Invalid move"<<endl;
                        return false;
                    }
                }
                if((trow==frow+1)&&(tcol==fcol+2)&&checkmove('b', frow, fcol, trow, tcol)){
                    if((board[trow][tcol]=='R')||(board[trow][tcol]=='K')||(board[trow][tcol]=='B')||(board[trow][tcol]=='Q')||(board[trow][tcol]=='@')||(board[trow][tcol]=='P')||(board[trow][tcol]==' '))
                        return true;
                    else{
                        cout<<"Invalid move"<<endl;
                        return false;
                    }
                }
            }

            if((trow>frow)&&(tcol<fcol)){//----------------knight move downleft
                if((trow==frow+2)&&(tcol==fcol-1)&&checkmove('b', frow, fcol, trow, tcol)){
                    if((board[trow][tcol]=='R')||(board[trow][tcol]=='K')||(board[trow][tcol]=='B')||(board[trow][tcol]=='Q')||(board[trow][tcol]=='@')||(board[trow][tcol]=='P')||(board[trow][tcol]==' '))
                        return true;
                    else{
                        cout<<"Invalid move"<<endl;
                        return false;
                    }
                }
                if((trow==frow+1)&&(tcol==fcol-2)&&checkmove('b', frow, fcol, trow, tcol)){
                    if((board[trow][tcol]=='R')||(board[trow][tcol]=='K')||(board[trow][tcol]=='B')||(board[trow][tcol]=='Q')||(board[trow][tcol]=='@')||(board[trow][tcol]=='P')||(board[trow][tcol]==' '))
                        return true;
                    else{
                        cout<<"Invalid move"<<endl;
                        return false;
                    }
                }
            }

        }break;

        case '@':{
            bool clean=false;
            cout<<"a";

            if((trow==7)&&(tcol==6)&&(!kinghasmoved[1])&&(!rookhasmoved[3])&&(!checkcheck('w', 7, 5))&&(!checkcheck('w', 7, 6))&&(!checkcheck('w', 7, 4))&&(board[7][5]==' ')&&(board[7][6]==' ')&&(board[7][7]=='R')){//short castle
                kinghasmoved[1]=true;
                rookhasmoved[3]=true;
                board[7][5]='R';
                board[7][7]=' ';
                wking[0]=7;
                wking[1]=6;
                return true;
            }

            if((trow==7)&&(tcol==2)&&(!kinghasmoved[1])&&(!rookhasmoved[2])&&(!checkcheck('w', 7, 2))&&(!checkcheck('w', 7, 3))&&(!checkcheck('w', 7, 4))&&(board[7][3]==' ')&&(board[7][2]==' ')&&(board[7][1]==' ')&&(board[7][0]=='R')){//long castle
                kinghasmoved[1]=true;
                rookhasmoved[2]=true;
                board[7][3]='R';
                board[7][0]=' ';
                wking[0]=7;
                wking[1]=2;
                return true;
            }

           if((fcol==tcol)&&(trow==frow-1)){//-----up
                clean=true;
                if((board[trow][tcol]=='r')||(board[trow][tcol]=='k')||(board[trow][tcol]=='b')||(board[trow][tcol]=='q')||(board[trow][tcol]=='&')||(board[trow][tcol]=='p')||(board[trow][tcol]==' ')){
                    clean&=true;
                }else{
                    clean&=false;
                }
                if(!checkcheck('w', trow, tcol))
                    clean&=true;
                else
                    clean&=false;
           }

           if((fcol+1==tcol)&&(trow==frow)){//-----right
                clean=true;
                if((board[trow][tcol]=='r')||(board[trow][tcol]=='k')||(board[trow][tcol]=='b')||(board[trow][tcol]=='q')||(board[trow][tcol]=='&')||(board[trow][tcol]=='p')||(board[trow][tcol]==' ')){
                    clean&=true;
                }else{
                    clean&=false;
                }
                if(!checkcheck('w', trow, tcol))
                    clean&=true;
                else
                    clean&=false;
           }

           if((fcol==tcol)&&(trow==frow+1)){//-----down
                clean=true;
                if((board[trow][tcol]=='r')||(board[trow][tcol]=='k')||(board[trow][tcol]=='b')||(board[trow][tcol]=='q')||(board[trow][tcol]=='&')||(board[trow][tcol]=='p')||(board[trow][tcol]==' ')){
                    clean&=true;
                }else{
                    clean&=false;
                }
                if(!checkcheck('w', trow, tcol))
                    clean&=true;
                else
                    clean&=false;
           }

           if((fcol-1==tcol)&&(trow==frow)){//-----left
                clean=true;
                if((board[trow][tcol]=='r')||(board[trow][tcol]=='k')||(board[trow][tcol]=='b')||(board[trow][tcol]=='q')||(board[trow][tcol]=='&')||(board[trow][tcol]=='p')||(board[trow][tcol]==' ')){
                    clean&=true;
                }else{
                    clean&=false;
                }
                if(!checkcheck('w', trow, tcol))
                    clean&=true;
                else
                    clean&=false;
           }

           if((tcol==fcol+1)&&(trow==frow-1)){//-----upright
                clean=true;
                if((board[trow][tcol]=='r')||(board[trow][tcol]=='k')||(board[trow][tcol]=='b')||(board[trow][tcol]=='q')||(board[trow][tcol]=='&')||(board[trow][tcol]=='p')||(board[trow][tcol]==' ')){
                    clean&=true;
                }else{
                    clean&=false;
                }
                if(!checkcheck('w', trow, tcol))
                    clean&=true;
                else
                    clean&=false;
           }

           if((tcol==fcol+1)&&(trow==frow+1)){//-----downright
                clean=true;
                if((board[trow][tcol]=='r')||(board[trow][tcol]=='k')||(board[trow][tcol]=='b')||(board[trow][tcol]=='q')||(board[trow][tcol]=='&')||(board[trow][tcol]=='p')||(board[trow][tcol]==' ')){
                    clean&=true;
                }else{
                    clean&=false;
                }
                if(!checkcheck('w', trow, tcol))
                    clean&=true;
                else
                    clean&=false;
           }

           if((tcol==fcol-1)&&(trow==frow-1)){//-----upleft
                clean=true;
                if((board[trow][tcol]=='r')||(board[trow][tcol]=='k')||(board[trow][tcol]=='b')||(board[trow][tcol]=='q')||(board[trow][tcol]=='&')||(board[trow][tcol]=='p')||(board[trow][tcol]==' ')){
                    clean&=true;
                }else{
                    clean&=false;
                }
                if(!checkcheck('w', trow, tcol))
                    clean&=true;
                else
                    clean&=false;
           }

           if((tcol==fcol-1)&&(trow==frow+1)){//-----downleft
                clean=true;
                if((board[trow][tcol]=='r')||(board[trow][tcol]=='k')||(board[trow][tcol]=='b')||(board[trow][tcol]=='q')||(board[trow][tcol]=='&')||(board[trow][tcol]=='p')||(board[trow][tcol]==' ')){
                    clean&=true;
                }else{
                    clean&=false;
                }
                if(!checkcheck('w', trow, tcol))
                    clean&=true;
                else
                    clean&=false;
           }

           if(clean){
                kinghasmoved[1]==true;
                wking[0]=trow;
                wking[1]=tcol;
                return true;
           }else{
                cout<<"Invalid move"<<endl;
                return false;
           }//---------------------ENND WHITE

        }break;

        case '&':{
            bool clean=false;

            if((trow==0)&&(tcol==6)&&(!kinghasmoved[0])&&(!rookhasmoved[1])&&(!checkcheck('b', 0, 5))&&(!checkcheck('b', 0, 6))&&(!checkcheck('b', 0, 4))&&(board[0][5]==' ')&&(board[0][6]==' ')&&(board[0][7]=='r')){//short castle
                kinghasmoved[0]=true;
                rookhasmoved[1]=true;
                board[0][5]='r';
                board[0][7]=' ';
                bking[0]=0;
                bking[1]=6;
                return true;
            }

            if((trow==0)&&(tcol==2)&&(!kinghasmoved[0])&&(!rookhasmoved[0])&&(!checkcheck('b', 0, 2))&&(!checkcheck('b', 0, 3))&&(!checkcheck('b', 0, 4))&&(board[0][3]==' ')&&(board[0][2]==' ')&&(board[0][1]==' ')&&(board[0][0]=='r')){//long castle
                kinghasmoved[0]=true;
                rookhasmoved[0]=true;
                board[0][3]='r';
                board[0][0]=' ';
                bking[0]=0;
                bking[1]=2;
                return true;
            }

           if((fcol==tcol)&&(trow==frow-1)){//-----up
                clean=true;
                if((board[trow][tcol]=='R')||(board[trow][tcol]=='K')||(board[trow][tcol]=='B')||(board[trow][tcol]=='Q')||(board[trow][tcol]=='@')||(board[trow][tcol]=='P')||(board[trow][tcol]==' ')){
                    clean&=true;
                }else{
                    clean&=false;
                }
                if(!checkcheck('b', trow, tcol))
                    clean&=true;
                else
                    clean&=false;
           }

           if((fcol+1==tcol)&&(trow==frow)){//-----right
                clean=true;
                if((board[trow][tcol]=='R')||(board[trow][tcol]=='K')||(board[trow][tcol]=='B')||(board[trow][tcol]=='Q')||(board[trow][tcol]=='@')||(board[trow][tcol]=='P')||(board[trow][tcol]==' ')){
                    clean&=true;
                }else{
                    clean&=false;
                }
                if(!checkcheck('b', trow, tcol))
                    clean&=true;
                else
                    clean&=false;
           }

           if((fcol==tcol)&&(trow==frow+1)){//-----down
                clean=true;
                if((board[trow][tcol]=='R')||(board[trow][tcol]=='K')||(board[trow][tcol]=='B')||(board[trow][tcol]=='Q')||(board[trow][tcol]=='@')||(board[trow][tcol]=='P')||(board[trow][tcol]==' ')){
                    clean&=true;
                }else{
                    clean&=false;
                }
                if(!checkcheck('b', trow, tcol))
                    clean&=true;
                else
                    clean&=false;
           }

           if((fcol-1==tcol)&&(trow==frow)){//-----left
                clean=true;
                if((board[trow][tcol]=='R')||(board[trow][tcol]=='K')||(board[trow][tcol]=='B')||(board[trow][tcol]=='Q')||(board[trow][tcol]=='@')||(board[trow][tcol]=='P')||(board[trow][tcol]==' ')){
                    clean&=true;
                }else{
                    clean&=false;
                }
                if(!checkcheck('b', trow, tcol))
                    clean&=true;
                else
                    clean&=false;
           }

           if((tcol==fcol+1)&&(trow==frow-1)){//-----upright
                clean=true;
                if((board[trow][tcol]=='R')||(board[trow][tcol]=='K')||(board[trow][tcol]=='B')||(board[trow][tcol]=='Q')||(board[trow][tcol]=='@')||(board[trow][tcol]=='P')||(board[trow][tcol]==' ')){
                    clean&=true;
                }else{
                    clean&=false;
                }
                if(!checkcheck('b', trow, tcol))
                    clean&=true;
                else
                    clean&=false;
           }

           if((tcol==fcol+1)&&(trow==frow+1)){//-----downright
                clean=true;
                if((board[trow][tcol]=='R')||(board[trow][tcol]=='K')||(board[trow][tcol]=='B')||(board[trow][tcol]=='Q')||(board[trow][tcol]=='@')||(board[trow][tcol]=='P')||(board[trow][tcol]==' ')){
                    clean&=true;
                }else{
                    clean&=false;
                }
                if(!checkcheck('b', trow, tcol))
                    clean&=true;
                else
                    clean&=false;
           }

           if((tcol==fcol-1)&&(trow==frow-1)){//-----upleft
                clean=true;
                if((board[trow][tcol]=='R')||(board[trow][tcol]=='K')||(board[trow][tcol]=='B')||(board[trow][tcol]=='Q')||(board[trow][tcol]=='@')||(board[trow][tcol]=='P')||(board[trow][tcol]==' ')){
                    clean&=true;
                }else{
                    clean&=false;
                }
                if(!checkcheck('b', trow, tcol))
                    clean&=true;
                else
                    clean&=false;
           }

           if((tcol==fcol-1)&&(trow==frow+1)){//-----downleft
                clean=true;
                if((board[trow][tcol]=='R')||(board[trow][tcol]=='K')||(board[trow][tcol]=='B')||(board[trow][tcol]=='Q')||(board[trow][tcol]=='@')||(board[trow][tcol]=='P')||(board[trow][tcol]==' ')){
                    clean&=true;
                }else{
                    clean&=false;
                }
                if(!checkcheck('b', trow, tcol))
                    clean&=true;
                else
                    clean&=false;
           }

           if(clean){
                kinghasmoved[0]==true;
                bking[0]=trow;
                bking[1]=tcol;
                return true;
           }else{
                cout<<"Invalid move"<<endl;
                return false;
           }//---------------------END BLACK

        }break;

    }
    cout<<"Invalid move"<<endl;
    return false;
}

void transformm(char colour,int row,int col){
    char tr;
    if(colour=='w'){
        do{
            cout<<endl<<"Transform (Q/B/K/R): ";
            cin>>tr;
        }while(!((tr=='Q')||(tr=='B')||(tr=='K')||(tr=='R')));
        board[row][col]=tr;
    }else{
        do{
            cout<<endl<<"Transform (q/b/k/r): ";
            cin>>tr;
        }while(!((tr=='q')||(tr=='b')||(tr=='k')||(tr=='r')));
        board[row][col]=tr;
    }
}

void chktrans(){
    for(int i=0; i<8; i++){
        if(board[0][i]=='P'){
            transformm('w', 0, i);
        }
    }

    for(int i=0; i<8; i++){
        if(board[7][i]=='P'){
            transformm('b', 7, i);
        }
    }
}

void white(){
    string from, to;
    int fcol, frow, tcol, trow;
    cout<<endl<<"White: ";
    do{
    do{
    cin>>from>>to;
    frow=from[1]-48;
    trow=to[1]-48;
    fcol=((int)from[0])-97;
    tcol=((int)to[0])-97;
    translate(frow, trow);
    }while(truepos('w', frow, fcol)&&truetogo(trow, tcol));
    }while(!truemove(frow, fcol, trow, tcol));
    board[trow][tcol]=board[frow][fcol];
    board[frow][fcol]=' ';
    chktrans();
    if(checkcheck('b', bking[0], bking[1]))
        cout<<endl<<"                                                       Check"<<endl;
    print();
}

void black(){
    string from, to;
    int fcol, frow, tcol, trow;
    cout<<endl<<"Black: ";
    do{
    do{
    cin>>from>>to;
    frow=from[1]-48;
    trow=to[1]-48;
    fcol=((int)from[0])-97;
    tcol=((int)to[0])-97;
    translate(frow, trow);
    }while(truepos('b', frow, fcol)&&truetogo(trow, tcol));
    }while(!truemove(frow, fcol, trow, tcol));
    board[trow][tcol]=board[frow][fcol];
    board[frow][fcol]=' ';
    chktrans();
    if(checkcheck('w', wking[0], wking[1]))
        cout<<endl<<"                                                       Check"<<endl;
    print();
}

int main(){
    int temp=10;
    print();
    while(temp!=0){
    white();
    black();
    }
    cin>>temp;
    return 0;
}

