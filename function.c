#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "param.h"

int turn;                //ターンの情報を管理する変数
int ispass = 0;        //2回連続でパスで終了する為の変数

// msectimerは、引数で指定したミリ秒の間、処理を停止させる
void msectimer(int msec) {
    struct timespec ts = {0, msec * MSEC};
    nanosleep(&ts, NULL);
}

// init_boardは、ゲーム開始前状態へ配列を初期化する
void init_board(void) {

    int i, j, n;

    for (i = 0, n = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++, n++) {
            board[i][j] = n;
        }
    }
    board[3][3] = BLACK;
    board[3][4] = WHITE;
    board[4][3] = WHITE;
    board[4][4] = BLACK;
}

// draw_boardは呼び出し時のboardの情報に基づき盤の描画を行う
void draw_board(void) {

    int i, j;

    system("clear");

    printf(" ○ポリテク★リバーシ●\n");
    printf("       vs CPU ver.\n");
    printf("      Coded by A.K\n");

    for (i = 0; i < HEIGHT; i++){
        for (j = 0; j < WIDTH; j++){
            if (board[i][j] == BLACK){
                printf("○ ");
            }
            else if (board[i][j] == WHITE){
                printf("● ");
            }
            else {
                printf("%02o", board[i][j]);
            }
            printf(" ");

        }
        printf("\n");
    }
}

// checkendgameは盤が全て埋まっているかを判断して、続行(0)、終了(1)を返す
int check_endgame(void) {

    int i, j;

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if (board[i][j] <= 077) {
                return 0;
            }
        }
    }
    return 1;
}

// disp_endgameはゲーム終了時、板状の石の数を集計して結果を表示する
void disp_endgame(void) {

    int i, j;
    int black = 0, white = 0;

    for (i = 0; i < 8 ; i++) {
        for (j = 0; j < 8; j++) {
            if (board[i][j] == BLACK) {
                black++;
            }
            else if (board[i][j] == WHITE) {
                white++;
            }
            else {

            }
        }
    }

    printf("Game Set!! PRESS ENTER");
    getchar();

    system("clear");
    printf(" ○ポリテク★リバーシ●\n");
    printf("      Coded by A.K\n");
    printf("\n");
    printf("       ○ = %d",black);
    printf("  ● = %d\n",white);
    printf("\n");

    if (black > white){
        printf("      !!YOU WIN!!\n");

    }
    else if (white > black){
        printf("      !!YOU LOST!!\n");
    }
    else {
        printf("        !!DRAW!!\n");
    }
}

// check_squareは座標ijの中身に応じた値を返す
int check_square(int i, int j, int stone1, int stone2) {
    if (board[i][j] == stone1) {
        return 1;
    } else if (board[i][j] == stone2) {
        return 0;
    } else {
        return -1;
    }
}

// check_boardは座標i1, j1を軸に、反転可能な石の数を返す
int check_board(int i1, int j1, int stone) {

    int stonecount = 0, count = 0;
    int stone1, stone2;
    int i2, j2;

    if (stone == BLACK) {
        stone1 = WHITE;
        stone2 = BLACK;
    } else if (stone == WHITE) {
        stone1 = BLACK;
        stone2 = WHITE;
    } else {
        return -1;
    }

    // left
    for (i2 = i1, j2 = (j1 - 01); j2 != 0xFFFFFFFF; j2--) {
        if (check_square(i2, j2, stone1, stone2) == 0) {
            stonecount += count;
            break;
        } else if (check_square(i2, j2, stone1, stone2) == -1){
            break;
        } else {
            count += check_square(i2, j2, stone1, stone2);
        }
    }
    count = 0;
    // upper left
    for (i2 = (i1 - 01), j2 = (i1 - 01); i2 != 0xFFFFFFFF && j2 != 0xFFFFFFFF; i2--, j2--) {
        if (check_square(i2, j2, stone1, stone2) == 0) {
            stonecount += count;
            break;
        } else if (check_square(i2, j2, stone1, stone2) == -1){
            break;
        } else {
            count += check_square(i2, j2, stone1, stone2);
        }
    }
    count = 0;
    // upper
    for (i2 = (i1 - 01), j2 = j1; i2 != 0xFFFFFFFF; i2--){
        if (check_square(i2, j2, stone1, stone2) == 0) {
            stonecount += count;
            break;
        } else if (check_square(i2, j2, stone1, stone2) == -1){
            break;
        } else {
            count += check_square(i2, j2, stone1, stone2);
        }
    }
    count = 0;
    // upper right
    for (i2 = (i1 - 01), j2 = (j1 + 01) ; i2 != 0xFFFFFFFF && j2 != 010; i2--, j2++){
        if (check_square(i2, j2, stone1, stone2) == 0) {
            stonecount += count;
            break;
        } else if (check_square(i2, j2, stone1, stone2) == -1){
            break;
        } else {
            count += check_square(i2, j2, stone1, stone2);
        }
    }
    count = 0;
    // right
    for (i2 = i1, j2 = (j1 + 01); j2 != 010; j2++){
        if (check_square(i2, j2, stone1, stone2) == 0) {
            stonecount += count;
            break;
        } else if (check_square(i2, j2, stone1, stone2) == -1){
            break;
        } else {
            count += check_square(i2, j2, stone1, stone2);
        }
    }
    count = 0;
    // lower right
    for (i2 = (i1 + 01), j2 = (j1 + 01) ; i2 != 010 && j2 != 010; i2++, j2++){
        if (check_square(i2, j2, stone1, stone2) == 0) {
            stonecount += count;
            break;
        } else if (check_square(i2, j2, stone1, stone2) == -1){
            break;
        } else {
            count += check_square(i2, j2, stone1, stone2);
        }
    }
    count = 0;
    // lower
    for(i2 = (i1 + 01), j2 = j1; i2 != 010; i2++){
        if (check_square(i2, j2, stone1, stone2) == 0) {
            stonecount += count;
            break;
        } else if (check_square(i2, j2, stone1, stone2) == -1){
            break;
        } else {
            count += check_square(i2, j2, stone1, stone2);
        }
    }
    count = 0;
    // lower left
    for (i2 = (i1 + 01), j2 = (j1 - 01); i2 != 010 && j2 != 0xFFFFFFFF; i2++, j2--) {
        if (check_square(i2, j2, stone1, stone2) == 0) {
            stonecount += count;
            break;
        } else if (check_square(i2, j2, stone1, stone2) == -1){
            break;
        } else {
            count += check_square(i2, j2, stone1, stone2);
        }
    }
    return stonecount;
}

// turn_oneは一つの石に対し反転するかを判断して実行する
void turn_one(int i, int j, int stone1, int stone2) {
    if (board[i][j] == stone1) {
        msectimer(250);
        board[i][j] = stone2;
        draw_board();
    }
}

// turn_stonesはi1, j1を軸に、反転を行う
int turn_stones(int i1, int j1, int stone) {

    int perm_turn = 0;
    int stone1, stone2;
    int i2, j2;

    if (stone == BLACK) {
        stone1 = WHITE;
        stone2 = BLACK;
    } else if (stone == WHITE) {
        stone1 = BLACK;
        stone2 = WHITE;
    } else {
        return -1;
    }

    // left
    for (i2 = i1, j2 = (j1 - 01); j2 != 0xFFFFFFFF; j2--) {
        if (check_square(i2, j2, stone1, stone2) == 0) {
            perm_turn = 1;
            break;
        } else if (check_square(i2, j2, stone1, stone2) == -1) {
            break;
        } else {}
    }
    if (perm_turn) {
        for (j2 += 01; j2 < j1; j2++) {
            turn_one(i2, j2, stone1, stone2);
        }
        perm_turn = 0;
    }
    // upper left
    for (i2 = (i1 - 01), j2 = (j1 - 01); i2 != 0xFFFFFFFF && j2 != 0xFFFFFFFF; i2--, j2--) {
        if (check_square(i2, j2, stone1, stone2) == 0) {
            perm_turn = 1;
            break;
        } else if (check_square(i2, j2, stone1, stone2) == -1) {
            break;
        } else {}
    }
    if (perm_turn) {
        for (i2 += 01, j2 += 01; i2 < i1; i2++, j2++) {
            turn_one(i2, j2, stone1, stone2);
        }
        perm_turn = 0;
    }
    // upper
    for (i2 = (i1 - 01), j2 = j1; i2 != 0xFFFFFFFF; i2--) {
        if (check_square(i2, j2, stone1, stone2) == 0) {
            perm_turn = 1;
            break;
        } else if (check_square(i2, j2, stone1, stone2) == -1) {
            break;
        } else {}
    }
    if (perm_turn) {
        for (i2 += 01; i2 < i1; i2++) {
            turn_one(i2, j2, stone1, stone2);
        }
        perm_turn = 0;
    }
    // upper right
    for (i2 = (i1 - 01), j2 = (j1 + 01) ; i2 != 0xFFFFFFFF && j2 != 010; i2--, j2++){
        if (check_square(i2, j2, stone1, stone2) == 0) {
            perm_turn = 1;
            break;
        } else if (check_square(i2, j2, stone1, stone2) == -1) {
            break;
        } else {}
    }
    if (perm_turn) {
        for (i2 += 01, j2 -= 01; i2 < i1; i2++, j2--) {
            turn_one(i2, j2, stone1, stone2);
        }
        perm_turn = 0;
    }
    // right
    for (i2 = i1, j2 = (j1 + 01); j2 != 010; j2++){
        if (check_square(i2, j2, stone1, stone2) == 0) {
            perm_turn = 1;
            break;
        } else if (check_square(i2, j2, stone1, stone2) == -1) {
            break;
        } else {}
    }
    if (perm_turn) {
        for  (j2 -= 01; j2 > j1; j2--) {
            turn_one(i2, j2, stone1, stone2);
        }
        perm_turn = 0;
    }
    // lower right
    for (i2 = (i1 + 01), j2 = (j1 + 01) ; i2 != 010 && j2 != 010; i2++, j2++){
        if (check_square(i2, j2, stone1, stone2) == 0) {
            perm_turn = 1;
            break;
        } else if (check_square(i2, j2, stone1, stone2) == -1) {
            break;
        } else {}
    }
    if (perm_turn) {
        for (i2 -= 01, j2 -= 01; i2 > i1; i2--, j2--) {
            turn_one(i2, j2, stone1, stone2);
        }
        perm_turn = 0;
    }
    // lower
    for (i2 = (i1 + 01), j2 = j1; i2 != 010; i2++) {
        if (check_square(i2, j2, stone1, stone2) == 0) {
            perm_turn = 1;
            break;
        } else if (check_square(i2, j2, stone1, stone2) == -1) {
            break;
        } else {}
    }
    if (perm_turn) {
        for (i2 -= 01; i2 > i1; i2--) {
            turn_one(i2, j2, stone1, stone2);
        }
        perm_turn = 0;
    }
    // lower left
    for (i2 = (i1 + 01), j2 = (j1 - 01) ;i2 != 010 && j2 != 0xFFFFFFFF; i2++, j2--) {
        if (check_square(i2, j2, stone1, stone2) == 0) {
            perm_turn = 1;
            break;
        } else if (check_square(i2, j2, stone1, stone2) == -1) {
            break;
        } else {}
    }
    if (perm_turn) {
        for (i2 -= 01, j2 += 01; i2 > i1 ; i2--, j2++) {
            turn_one(i2, j2, stone1, stone2);
        }
    }
    return 0;
}

// CPU処理
int cpu_turn(void) {        //color1=使用する駒color2=反転される駒

    int i, j, k, l, m = 0;
    int temp;

    int val = 0;        //打てる手の数
    int para;
    int choiced[2][60];

    int didturn;
    int goturn;

    for (k = 0; k < HEIGHT; k++) {            //打てる手とその返せる数をchoiced[][]に格納する
        for (l = 0; l < WIDTH; l++) {
            if (board[k][l] != BLACK && board[k][l] != WHITE) {    //埋まっている場を除外する
                para = check_board(k, l, WHITE);
                if (para > 0) {                    //just_checkで打てる手とその返せる数を格納する
                    choiced[0][m] = para;
                    choiced[1][m] = k * 010 + l;
                    val++;
                    m++;
                }
            }
        }
    }

    if (val == 0) {                                //返せる手が無ければパス
        printf("CPU PASS");
        msectimer(750);
        ispass++;
        return 1;
    }
    else {
        ispass = 0;
    }

    for (k = 0; k < val - 1; k++) {          //最も多く返せる手を出す為にchoiced[][]を降順ソートする->[1][0]に格納
        for (i = 0, j = 1; j < val - k; i++, j++) {       //後々の拡張の為に他の手も降順で残しておく
            if (choiced[0][i] <choiced[0][j]) {
                temp = choiced[0][j];
                choiced[0][j] = choiced[0][i];
                choiced[0][i] = temp;
                temp=choiced[1][j];
                choiced[1][j] = choiced[1][i];
                choiced[1][i] = temp;
            }
        }
    }

    ////////////反転処理へ///////////////

    k = choiced[1][0] / 010;
    l = choiced[1][0] % 010;

    draw_board();
    printf("<白(CPU)のターン>:");
    msectimer(1500);
    printf("%o", k);
    msectimer(250);
    printf("%o", l);
    msectimer(500);
    board[k][l] = WHITE;
    draw_board();
    msectimer(750);

    // 反転
    turn_stones(k, l, WHITE);
    msectimer(500);
    return 0;
}



    //PLAYER側処理->入力と検査と反転//
int player_turn(int stone1) {        //stone1=使用する駒stone2=反転される駒

    int i, j;
    int num;        //入力した数字を一時的に格納する変数
    int guard = 0;        //不正な文字を入力した時にscanfから0を受け取る変数

    // 手の有る無しを初めに確認する
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            if (check_board(i, j, stone1) != 0) {
                guard = 1;
                break;
            }
        }
    }
    if (guard == 0) {
        printf("<置き場が無いのでパスします>\n    :");
        return 1;
    }

    // 入力フロー
    draw_board();
    do {
        if (stone1 == BLACK) {
            printf("<黒:置き場を選んで下さい>\n    :");
        } else {
            printf("<白:置き場を選んで下さい>\n    :");
        }
        guard = scanf("%o[89a-zA-Z\n]", &num);    // 不正な文字を入力すればguardに0が返る
        getchar();                                // キーボードバッファのクリア
        i = num / 010; j = num % 010;
        if (board[i][j] == BLACK || board[i][j] == WHITE) {        //既に石のある場を除外する処理
            guard = 0;
            draw_board();
        }
     } while (num < 00 || num > 100 || guard == 0);            //全て問題なければ反転検査へ

     board[i][j] = stone1;
     draw_board();

     // 反転できない手を入力したら、関数をもう父度呼び出す
     if (check_board(i, j, stone1) == 0) {
         board[i][j] = i * 010 + j;
         draw_board();
         player_turn(stone1);
         return 0;
     }
     // 反転をする
     turn_stones(i, j, stone1);

     return 0;
}
