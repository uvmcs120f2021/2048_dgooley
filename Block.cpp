//
// Created by goole on 12/11/2021.
//

#include "Block.h"

Block::Block(int value, int pos_x, int pos_y){
    this->value = value;
    this->pos_x = pos_x;
    this->pos_y = pos_y;
}

bool operator == (const Block &left, const Block& right) {
    return left.value == right.value;
}
