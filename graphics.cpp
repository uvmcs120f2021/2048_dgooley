#include "graphics.h"
#include <ctime>
#include <iostream>
#include <vector>
#include <iomanip>
#include "Block.cpp"
#include <time.h>
using namespace std;

GLdouble width, height;
bool start = false;
bool lost = false;

int wd;
Block zero(0, 0, 0);
Block one(0, 0, 1);
Block two(0, 0, 2);
Block three(0, 0, 3);
Block four(0, 1, 0);
Block five(0, 1, 1);
Block six(0, 1, 2);
Block seven(0, 1, 3);
Block eight(0, 2, 0);
Block nine(0, 2, 1);
Block ten(0, 2, 2);
Block eleven(0, 2, 3);
Block twelve(0, 3, 0);
Block thirteen(0, 3, 1);
Block fourteen(0, 3, 2);
Block fifteen(0, 3, 3);
Block all_blocks[] = {zero, one, two, three, four, five, six, seven,
                      eight, nine, ten, eleven, twelve, thirteen, fourteen, fifteen};

bool check_loss(Block block_array[]);
void start_game(Block block_array[]);
void render_move(Block block_array[]);
void add_rand(Block block_array[]);
void apply_move(Block block_array[], int player_move);
void draw_tile(int x_insert, int y_insert, string num);

void draw_board();

void init() {
    width = 400;
    height = 400;

}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
    // Tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height); // DO NOT CHANGE THIS LINE

    // Do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION); // DO NOT CHANGE THIS LINE
    glLoadIdentity(); // DO NOT CHANGE THIS LINE
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f); // DO NOT CHANGE THIS LINE

    // Clear the color buffer with current clearing color
    glClear(GL_COLOR_BUFFER_BIT); // DO NOT CHANGE THIS LINE

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // DO NOT CHANGE THIS LINE
    draw_board();
    /*
     * Draw here
     */
    if (!start) {
        start_game(all_blocks);
    }

    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            for (int i = 0; i < 16; i++) {
                if (all_blocks[i].pos_x == x and all_blocks[i].pos_y == y) {
                    if (all_blocks[i].value != 0){
                        string send_num = to_string(all_blocks[i].value);
                        draw_tile(x, y, send_num);
                    }
                }
            }
        }
    }
// add new game button
    glColor3f(.8, .7, .2);
    glBegin(GL_POLYGON);
    glVertex2i(130, 20);
    glVertex2i(130, 60);
    glVertex2i(260, 60);
    glVertex2i(260, 20);
    glEnd();

    const char *this_str = "NEW GAME";
    glColor3f (.2, .1, .4);
    glRasterPos2f(145, 46);
    while(*this_str){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *this_str++);
    }

    if (lost){
        glColor3f(1, .1, .1);
        glBegin(GL_POLYGON);
        glVertex2i(100, 105);
        glVertex2i(100, 285);
        glVertex2i(290, 285);
        glVertex2i(290, 105);
        glEnd();
        const char *lost_str = "YOU LOST  :-(";
        glColor3f (1, 1, 1);
        glRasterPos2f(132, 200);
        while(*lost_str){
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *lost_str++);
        }
    }

// add score keeper in box at bottom
    glColor3f(.8, .3, .8);
    glBegin(GL_POLYGON);
    glVertex2i(60, 340);
    glVertex2i(60, 370);
    glVertex2i(330, 370);
    glVertex2i(330, 340);
    glEnd();

    int current_score = 0;
    for (int u=0; u<16; u++){
        current_score += all_blocks[u].value;
    }

    string string_score = "CURRENT SCORE:  " + to_string(current_score);
    const char *string = string_score.c_str();

    glColor3f (0, 1, 1);
    glRasterPos2f(65, 361); //define position on the screen

    while(*string){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *string++);
    }

    glFlush();  // Render now
}

void kbd(unsigned char key, int x, int y) {
    switch(key) {
    }
    //glutPostRedisplay();
}

void kbdUp(unsigned char key, int x, int y) {
    //glutPostRedisplay();
}

void kbdS(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_DOWN:
            apply_move(all_blocks, 1);
            break;
        case GLUT_KEY_LEFT:
            apply_move(all_blocks, 3);
            break;
        case GLUT_KEY_RIGHT:
            apply_move(all_blocks, 2);
            break;
        case GLUT_KEY_UP:
            apply_move(all_blocks, 0);
            break;
    }

    glutPostRedisplay();
}

void cursor(int x, int y) {
    //glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {
     if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
         if (x>130 and x<260 and y>20 and y< 60){
             for (int l=0; l<16; l++){
                 all_blocks[l].value = 0;
                 start = false;
                 lost = false;
             }
         }
     }

     glutPostRedisplay();
}

void timer(int dummy) {

    //glutPostRedisplay();
    //glutTimerFunc(30, timer, dummy);
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
    srand(time(0));
    init();

    glutInit(&argc, argv);          // Initialize GLUT

    glutInitDisplayMode(GLUT_RGBA);

    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(0, 0); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("2048!" /* title */ );

    // Register callback handler for window re-paint event
    glutDisplayFunc(display);

    // Our own OpenGL initialization
    initGL();

    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);
    glutKeyboardUpFunc(kbdUp);

    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);

    //handles mouse movement
    glutPassiveMotionFunc(cursor);

    // handles mouse click
    glutMouseFunc(mouse);

    // Enter the event-processing loop
    glutMainLoop();


    return 0;
}

void draw_tile(int y_insert, int x_insert, string num){
    int x_value_one = 82+60*x_insert;
    int x_value_two = x_value_one+46;
    int y_value_one = 82+60*y_insert;
    int y_value_two = y_value_one+46;
    glColor3f(0, 0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2i(x_value_two, y_value_two);
    glVertex2i(x_value_two, y_value_one);
    glVertex2i(x_value_one, y_value_one);
    glVertex2i(x_value_one, y_value_two);
    glEnd();

    const char *string = num.c_str();
    int size_qualifier = stoi(num);
    if (size_qualifier<10){
        glColor3f (1, 0.0, 0);
        glRasterPos2f(x_value_one+18, y_value_one+28); //define position on the screen
    }
    else if (size_qualifier<100){
        glColor3f (.8, 0.5, 0);
        glRasterPos2f(x_value_one+13, y_value_one+28); //define position on the screen
    }
    else if (size_qualifier<1000){
        glColor3f (.5, 0.8, 0);
        glRasterPos2f(x_value_one+8, y_value_one+28); //define position on the screen
    }
    else if (size_qualifier<10000){
        glColor3f (0, 1, 0);
        glRasterPos2f(x_value_one+2, y_value_one+28); //define position on the screen
    }
    else{
        glColor3f (0, 1, 1);
        glRasterPos2f(x_value_one, y_value_one+28); //define position on the screen

    }

    while(*string){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *string++);
    }
    //18, 12


}

void draw_board(){
    for (int k=0; k<4; k++){
        int x_value_one = 80+60*k;
        int x_value_two = x_value_one+50;
        for (int i=0; i<4; i++){
            int y_value_one = 80+60*i;
            int y_value_two = y_value_one+50;
            glColor3f(.9, .8, .6);
            glBegin(GL_POLYGON);
            glVertex2i(x_value_two, y_value_two);
            glVertex2i(x_value_two, y_value_one);
            glVertex2i(x_value_one, y_value_one);
            glVertex2i(x_value_one, y_value_two);
            glEnd();
        }
    }
}

void render_move(Block block_array[]) {
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            for (int i = 0; i < 16; i++) {
                if (block_array[i].pos_x == x and block_array[i].pos_y == y) {
                    cout << setw(6) << block_array[i].value;
                }
            }
        }
        cout << endl;
    }
    cout << endl;
}

void add_rand(Block block_array[]){
    bool add = false;

    int new_num = 2;
    int ten_rand = rand()%9;
    if(ten_rand == 0)
        new_num = 4;

    while( add == false){
        int x_rand = rand()%4;
        int y_rand = rand()%4;
        for (int i=0; i<16; i++) {
            if (block_array[i].pos_x == x_rand and block_array[i].pos_y == y_rand) {
                if (block_array[i].value == 0) {
                    block_array[i].value = new_num;
                    string new_num_str = to_string(new_num);
                    draw_tile(x_rand, y_rand, new_num_str);

                    add = true;
                }
            }
        }
    }

}

bool check_loss(Block block_array[]){
    lost = true;
    for (int p=0; p<16; p++){
        if (all_blocks[p].value == 0){
            lost = false;
            return lost;
        }
    }
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            for (int a = 0; a < 16; a++) {
                for (int b = 0; b < 16; b++) {
                    if (block_array[a].pos_x == x and block_array[a].pos_y == y) {
                        if ((block_array[b].pos_x == x+1 and block_array[b].pos_y == y) or (block_array[b].pos_x == x and block_array[b].pos_y == y+1)) {
                            if (block_array[a] == block_array[b]){
                                lost = false;
                                return lost;
                            }
                        }
                    }
                }
            }
        }
    }

    return lost;
}

void apply_move(Block block_array[], int player_move){
    bool change_made = false;

    switch (player_move){
        case 0:
            cout << "you moved up" << endl;
            for (int h=0; h<3; h++){
                for (int x = 3; x > -1; x--) {
                    for (int y=3; y>-1;y--){
                        for (int i = 0; i < 16; i++) {
                            if (block_array[i].pos_x == x and block_array[i].pos_y == y) {
                                if (block_array[i].value != 0){
                                    for (int k = 0; k < 16; k++) {
                                        if (block_array[k].pos_x == (x-1) and block_array[k].pos_y == y) {
                                            if (block_array[k].value == 0){
                                                block_array[k].value = block_array[i].value;
                                                block_array[i].value = 0;
                                                change_made = true;
                                            }
                                            if (block_array[k] == block_array[i] and h==0){
                                                block_array[k].value *= 2;
                                                block_array[i].value = 0;
                                                change_made = true;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            break;
        case 1:
            cout << "you moved down" << endl;
            for (int h=0; h<3; h++){
                for (int x = 0; x < 4; x++) {
                    for (int y=3; y>-1;y--){
                        for (int i = 0; i < 16; i++) {
                            if (block_array[i].pos_x == x and block_array[i].pos_y == y) {
                                if (block_array[i].value != 0){
                                    for (int k = 0; k < 16; k++) {
                                        if (block_array[k].pos_x == (x+1) and block_array[k].pos_y == y) {
                                            if (block_array[k].value == 0){
                                                block_array[k].value = block_array[i].value;
                                                block_array[i].value = 0;
                                                change_made = true;
                                            }
                                            if (block_array[k] == block_array[i] and h==0){
                                                block_array[k].value *= 2;
                                                block_array[i].value = 0;
                                                change_made = true;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            break;
        case 2:
            cout << "you moved right" << endl;
            for (int h=0; h<3; h++){
                for (int x = 0; x < 4; x++) {
                    for (int y=0; y<4;y++){
                        for (int i = 0; i < 16; i++) {
                            if (block_array[i].pos_x == x and block_array[i].pos_y == y) {
                                if (block_array[i].value != 0){
                                    for (int k = 0; k < 16; k++) {
                                        if (block_array[k].pos_x == x and block_array[k].pos_y == (y + 1)) {
                                            if (block_array[k].value == 0){
                                                block_array[k].value = block_array[i].value;
                                                block_array[i].value = 0;
                                                change_made = true;
                                            }
                                            if (block_array[k] == block_array[i] and h==0){
                                                block_array[k].value *= 2;
                                                block_array[i].value = 0;
                                                change_made = true;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            break;
        case 3:
            cout << "you moved left" << endl;
            for (int h = 0; h<3; h++){
                for (int x = 0; x < 4; x++) {
                    for (int y=3; y>-1;y--){
                        for (int i = 0; i < 16; i++) {
                            if (block_array[i].pos_x == x and block_array[i].pos_y == y) {
                                if (block_array[i].value != 0){
                                    for (int k = 0; k < 16; k++) {
                                        if (block_array[k].pos_x == x and block_array[k].pos_y == (y - 1)) {
                                            if (block_array[k].value == 0){
                                                block_array[k].value = block_array[i].value;
                                                block_array[i].value = 0;
                                                change_made = true;
                                            }
                                            if (block_array[k] == block_array[i] and h==0){
                                                block_array[k].value *= 2;
                                                block_array[i].value = 0;
                                                change_made = true;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            break;
    }
    if (change_made){
        add_rand(block_array);
    }
    render_move(block_array);

    if(check_loss(block_array)){
        cout << "You lost!" << endl;
    }
}

void start_game(Block block_array[]){
    cout << "Starting a new game of 2048!!!!" << endl;
    add_rand(block_array);
    add_rand(block_array);
    render_move(block_array);
    start = true;
}
