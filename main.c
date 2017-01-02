/* -------------------------------
      REVERSI PROGRAM for mac
            vsCPU ver.
       2016.7.21-2016.12.30
       Coded by KUNO AKIRA
   ------------------------------- */
/* TODO :change clearwindow method and time method */

int isfull = 0;

extern int turn;
extern int ispass;

void init_board(void);
void draw_board(void);
int ins_and_check(int, int);
int cpu_turn(void);
int check_endgame(void);
void disp_endgame(void);

int main (void) {

    turn=1;

    init_board();        //盤を初期化して描画
    draw_board();

    while (isfull < 1 && ispass < 2) {
        if (turn == 1) {
            /*黒(PLAYER)のターン*/
            ins_and_check(0102, 0101);
            isfull = check_endgame();
            turn = 0;
        }
        else {
            cpu_turn();        //////////*白(CPU)のターン*///////////
            isfull = check_endgame();
            turn = 1;
        }
    }
    disp_endgame();
    return 0;
}

