//
// Created by goole on 12/13/2021.
//

#include "Testing.h"

bool test_check_loss(){
    bool passed = true;
    for (int i=0; i<16; i++){
        int hold = all_blocks[i];
        all_blocks[i] = 0;
        if (check_loss(all_blocks)){
            passed = false;
        }
        all_blocks[i] = hold;
    }

    int hold = all_blocks[4];
    int hold_two = all_blocks[3];
    all_blocks[3] = 2048;
    all_blocks[4] = 2048;
    if (check_loss(all_blocks)){
        passed = false;
    }
    all_blocks[3] = hold;
    all_blocks[4] = hold_two;

    return passed;
    int hold = all_blocks[14];
    int hold_two = all_blocks[15];
    all_blocks[14] = 2;
    all_blocks[15] = 2;
    if (check_loss(all_blocks)){
        passed = false;
    }
    all_blocks[14] = hold;
    all_blocks[15] = hold_two;

    int hold = all_blocks[0];
    int hold_two = all_blocks[4];
    all_blocks[0] = 4;
    all_blocks[4] = 4;
    if (check_loss(all_blocks)){
        passed = false;
    }
    all_blocks[0] = hold;
    all_blocks[4] = hold_two;

    return passed;
}

int main(int argc, char** argv) {
    cout << test_check_loss;
    return 0;
}