/* -------------------------------
      REVERSI PROGRAM for mac
            vsCPU ver.
       2016.7.21-2016.12.30
       Coded by KUNO AKIRA
   ------------------------------- */
/* TODO :change clearwindow method and time method */

int isfull = 0;
int turn   = 1;

extern int ispass;

void init_board(void);
void draw_board(void);
int player_turn(int);
int cpu_turn(void);
int check_endgame(void);
void disp_endgame(void);

int main (void) {

    init_board();
    draw_board();

    while (isfull != 1 && ispass < 2) {
        if (turn == 1) {
            player_turn(0102);
            isfull = check_endgame();
            turn = 0;
        }
        else {
            cpu_turn();
            isfull = check_endgame();
            turn = 1;
        }
    }
    disp_endgame();
    return 0;
}
