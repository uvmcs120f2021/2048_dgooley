//
// Created by goole on 12/11/2021.
//

#ifndef PROJECT_START_BLOCK_H
#define PROJECT_START_BLOCK_H
using namespace std;
class Block {

private:

public:
    int pos_x, pos_y, value;
    Block(int value, int pos_x, int pos_y);

    friend bool operator == (const Block &left, const Block& right);
};


#endif //GRAPHICS_JEOPARDY_BLOCK_H
