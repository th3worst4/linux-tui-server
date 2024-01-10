uint8_t msg_count = 0;

void initiate(){
    initscr();
    raw();
    keypad(stdscr, true);
    noecho();
    printw("Hi!");
    refresh();
}

void printmsg(char* msg){
    printw(msg);
    msg_count++;
    refresh();
}
