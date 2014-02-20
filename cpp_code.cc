#include <list>
#include <iostream>
#include <cstring>
#define LEN 32
using namespace std;

class minMaxTree
{
    public:
        int heuristic;
        list<list<int> > moves;
        list<minMaxTree*> children;
        
        minMaxTree(list<list<int> >);
};

minMaxTree::minMaxTree(list<list<int> > mov)
{
    moves = mov;
    heuristic = 0;
}

int* applyMove(int* board, list<int> move)
{
    int* temp = malloc(sizeof(int) * LEN);
    memcpy(temp, board, sizeof(int)*LEN);
    auto piece = move.begin();
    for(auto j = move.begin() + 1; j != move.end(); j++ )
    {
        temp[*j] = temp[*piece];
        temp[*piece] = 0;
        //TODO: Piece being jumped over needs to be cleared
    }
    return tmp;
}

list<list<int> > getAllJumps(int* board, int piece);

list<list<int> > jumpHelper(int* board, int piece, int offset)
{
    list<int> move;
    move.push_back(piece);
    move.push_back(piece+offset);
    list<list<int> > temp = getAllJumps(applyMove(board, move),piece+offset);
    for(auto i = temp.begin(); i != temp.end(); ++i){
        (*i).push_front(piece);
    }
    temp.push_back(move);
    return temp;
}


list<list<int> > getAllJumps(int* board, int piece){
    list<list<int> > moves;
    int offset = (piece/4) % 2;
    if(piece < 24)
    {
        if(board[piece + 7] == 0 && board[piece + 4 - offset] < 0 && piece % 4 != 0){
            list<list<int> > temp = jumpHelper(board, piece, 7);
            moves.insert(moves.end(), temp.begin(), temp.end());
        }
        if(board[piece + 9] == 0 && board[piece + 5 - offset] < 0 && piece % 4 != 3){
            list<list<int> > temp = jumpHelper(board, piece, 9);
            moves.insert(moves.end(), temp.begin(), temp.end());
        }
    }
    if(board[piece] == 2 && piece > 7){
        if(board[piece - 7] == 0 && board[piece -3 - offset] < 0 && piece % 4 != 3){
            list<list<int> > temp = jumpHelper(board, piece, -7);
            moves.insert(moves.end(), temp.begin(), temp.end());
        }
        if(board[piece - 9] == 0 && board[piece -4 - offset] < 0 && piece % 4 != 0){
            list<list<int> > temp = jumpHelper(board, piece, -9);
            moves.insert(moves.end(), temp.begin(), temp.end());
        }
    }
    return moves;
}

list<list<int> > possibleMoves(int* board)
{
    list<list<int> > moves;
    for(int i = 0; i < LEN; i++)
    {
        if(board[i] > 0)
        {
            int offset = (i/4) % 2;
            if(i < 28)
            {
                if(board[i + 4 - offset] == 0 && i % 8 != 4)
                {
                    list<int> move;
                    move.push_back(i);
                    move.push_back(i+4-offset);
                    moves.push_back(move);
                }
                if(board[i + 5 - offset] == 0 && i % 8 != 3)
                {
                    list<int> move;
                    move.push_back(i);
                    move.push_back(i+5-offset);
                    moves.push_back(move);
                }
            }
            if (board[i] == 2 && i > 3){
                if(board[i - 4 - offset] == 0 && i % 8 != 4)
                {
                    list<int> move;
                    move.push_back(i);
                    move.push_back(i-4-offset);
                    moves.push_back(move);
                }
                if(board[i - 3 - offset] == 0 && i % 8 != 3)
                {
                   list<int> move;
                   move.push_back(i);
                   move.push_back(i-3-offset);
                   moves.push_back(move);
                }

            }
            list<list<int> > jumps = getAllJumps(board, i);
            moves.insert(moves.end(), jumps.begin(), jumps.end());
        }
    }
    return moves;
}

void printListOfListOfInts(list<list<int> > moves)
{
    for(auto i = moves.begin(); i != moves.end(); i++)
    {
        cout << "[";
        for(auto j = (*i).begin(); j != (*i).end(); j++)
        {
            cout << (*j) << " ";
        }
        cout << "]" << endl;
    }
}



/*
 * This function is called by the Python front end
 * Using ctypes
 * Pass in an array of ints that represent the board
 */
extern "C" int* callAI(int* board)
{    
    printListOfListOfInts(possibleMoves(board));
    return board;
}