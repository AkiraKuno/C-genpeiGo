#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "defineparam.h"

int turn;                //ターンの情報を管理する変数
int ispass = 0;        //2回連続でパスで終了する為の変数

void init_board(void);
void draw_board(void);
int ins_and_check(int, int);
int cpu_turn(void);
int check_endgame(void);
void disp_endgame(void);

// msectimerは、引数で指定したミリ秒の間、処理を停止させる
void msectimer(int msec) {
    struct timespec ts = {0, msec * MSEC};
    nanosleep(&ts, NULL);
}

// init_boardは、ゲーム開始前状態へ配列を初期化する
void init_board(void) {

    int i, j, k;

    for (i = 0, k = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++, k++) {
            base[i][j] = k;
        }
    }
    base[3][3] = BLACK;
    base[3][4] = WHITE;
    base[4][3] = WHITE;
    base[4][4] = BLACK;
}

// draw_boardは呼び出し時のbaseの情報に基づき盤の描画を行う
void draw_board(void) {

    int i, j;

    system("clear");

    printf(" ○ポリテク★リバーシ●\n");
    printf("       vs CPU ver.\n");
    printf("      Coded by A.K\n");

    for (i = 0; i < HEIGHT; i++){
        for (j = 0; j < WIDTH; j++){
            if (base[i][j] == BLACK){
                printf("○ ");
            }
            else if (base[i][j] == WHITE){
                printf("● ");
            }
            else {
                printf("%02o", base[i][j]);
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
            if (base[i][j] <= 077) {
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
            if (base[i][j] == BLACK) {
                black++;
            }
            else if (base[i][j] == WHITE) {
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
        printf("      !!YOU WIN!!");

    }
    else if (white > black){
        printf("      !!YOU LOST!!");
    }
    else {
        printf("        !!DRAW!!");
    }
}

// 反転可否情報と返せる個数をCPUへ返す
int just_check(int k,int l) {

    int i,j;
    int goturn1 = 0;
    int goturn2 = 0;
    int toback = 0;       // toback=0であれば反転不可
    int stonenum = 0;     // 反転可能な石の数(仮)
    int sumstonenum = 0;  // 反転可能な石の数(実)

    //////////////////////////////*左向きに検査*/////////////////////////////////////
    for (i = k, j = (l - 01); j != 0xFFFFFFFF; j--) {
        if (base[i][j] == BLACK){            //逆の石を読んだらループ続行して数を数えておく
            goturn1 = 1;
            stonenum++;
        }
        else if (base[i][j] == WHITE){    //同じ石を読んだら反転情報を保持してbreak
            goturn2 = 1;
            break;
        }
        else {
            break;                        //石以外を読んだらbreak
        }
    }

    if (goturn1 + goturn2 == 2) {
        toback = 1;
        sumstonenum += stonenum;
    }
    goturn1 = 0;
    goturn2 = 0;
    stonenum = 0;
    ///////////////////////////////*左上向きに検査*//////////////////////////////////////
    for (i = k-01, j = l-01; i != 0xFFFFFFFF && j != 0xFFFFFFFF; i--, j--) {
        if (base[i][j] == BLACK){            //逆の石を読んだらループ続行して数を数えておく
            goturn1 = 1;
            stonenum++;
        }
        else if (base[i][j] == WHITE) {    //同じ石を読んだら反転情報を保持してbreak
            goturn2 = 1;
            break;
        }
        else {
            break;                        //石以外を読んだらbreak
        }
    }

    if(goturn1 + goturn2 == 2) {
        toback = 1;
        sumstonenum += stonenum;
    }
    goturn1=0;
    goturn2=0;
    stonenum=0;
    ///////////////////////////////*上向きに検査*/////////////////////////////////////
    for(i=k-01,j=l;i!=0xFFFFFFFF;i--){
        if(base[i][j]==BLACK){            //逆の石を読んだらループ続行して数を数えておく
            goturn1=1;
            stonenum++;
        }
        else if(base[i][j]==WHITE){    //同じ石を読んだら反転情報を保持してbreak
            goturn2=1;
            break;
        }
        else{
            break;                        //石以外を読んだらbreak
        }
    }

    if(goturn1+goturn2==2){
                toback=1;
        sumstonenum+=stonenum;
    }
    goturn1=0;
    goturn2=0;
    stonenum=0;
    ////////////////////////////////*右上向きに検査*////////////////////////////////////
    for(i=k-01,j=l+01 ;i!=0xFFFFFFFF&&j!=010; i--,j++){
        if(base[i][j]==BLACK){            //逆の石を読んだらループ続行して数を数えておく
            goturn1=1;
            stonenum++;
        }
        else if(base[i][j]==WHITE){    //同じ石を読んだら反転情報を保持してbreak
            goturn2=1;
            break;
        }
        else{
            break;                        //石以外を読んだらbreak
        }
    }

    if(goturn1+goturn2==2){
        toback=1;
        sumstonenum+=stonenum;
    }
    goturn1=0;
    goturn2=0;
    stonenum=0;
    ///////////////////////////////*右向きに検査*////////////////////////////////////
    for(i=k,j=l+01;j!=010;j++){
        if(base[i][j]==BLACK){            //逆の石を読んだらループ続行して数を数えておく
            goturn1=1;
            stonenum++;
        }
        else if(base[i][j]==WHITE){    //同じ石を読んだら反転情報を保持してbreak
            goturn2=1;
            break;
        }
        else{
            break;                        //石以外を読んだらbreak
        }
    }

    if(goturn1+goturn2==2){
        toback=1;
        sumstonenum+=stonenum;
    }

    goturn1=0;
    goturn2=0;
    stonenum=0;
    ///////////////////////////////*右下向きに検査*//////////////////////////////////////
    for(i=k+01,j=l+01 ;i!=010&&j!=010; i++,j++){
        if(base[i][j]==BLACK){            //逆の石を読んだらループ続行して数を数えておく
            goturn1=1;
            stonenum++;
        }
        else if(base[i][j]==WHITE){    //同じ石を読んだら反転情報を保持してbreak
            goturn2=1;
            break;
        }
        else{
            break;                        //石以外を読んだらbreak
        }
    }

    if(goturn1+goturn2==2){
        toback=1;
        sumstonenum+=stonenum;
    }
    goturn1=0;
    goturn2=0;
    stonenum=0;
    ///////////////////////////////*下向きに検査*////////////////////////////////////////
    for(i=k+01,j=l;i!=010;i++){
        if(base[i][j]==BLACK){            //逆の石を読んだらループ続行して数を数えておく
            goturn1=1;
            stonenum++;
        }
        else if(base[i][j]==WHITE){    //同じ石を読んだら反転情報を保持してbreak
            goturn2=1;
            break;
        }
        else{
            break;                        //石以外を読んだらbreak
        }
    }

    if(goturn1+goturn2==2){
        toback=1;
        sumstonenum+=stonenum;
    }
    goturn1=0;
    goturn2=0;
    stonenum=0;
    /////////////////////////////////*左下向きに検査*///////////////////////////////////
    for(i=k+01,j=l-01 ;i!=010&&j!=0xFFFFFFFF; i++,j--){
        if(base[i][j]==BLACK){            //逆の石を読んだらループ続行して数を数えておく
            goturn1=1;
            stonenum++;
        }
        else if(base[i][j]==WHITE){    //同じ石を読んだら反転情報を保持してbreak
            goturn2=1;
            break;
        }
        else{
            break;                        //石以外を読んだらbreak
        }
    }

    if(goturn1+goturn2==2){
        toback=1;
        sumstonenum+=stonenum;
    }

    if(toback==1){
        return(sumstonenum);                //反転できるならその数を返す
    }
    else{
        return(0);                        //反転できなければ0を返す
    }
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

    for(k=0;k<HEIGHT;k++){            //打てる手とその返せる数をchoiced[][]に格納する
        for(l=0;l<WIDTH;l++){
            if(base[k][l]!=BLACK&&base[k][l]!=WHITE){    //埋まっている場を除外する
                para=just_check(k,l);
                if(para>0){                    //just_checkで打てる手とその返せる数を格納する
                    choiced[0][m]=para;
                    choiced[1][m]=k*010+l;
                    val++;
                    m++;
                }
            }
        }
    }

    if(val==0){                                //返せる手が無ければパス
        printf("CPU PASS");
        msectimer(750);
        ispass++;
        return (0);
        }
    else{
        ispass=0;
    }

    for(k=0;k<val-1;k++){                    //最も多く返せる手を出す為にchoiced[][]を降順ソートする->[1][0]に格納
        for(i=0,j=1;j<val-k;i++,j++){        //後々の拡張の為に他の手も降順で残しておく
            if(choiced[0][i]<choiced[0][j]){
                temp=choiced[0][j];
                choiced[0][j]=choiced[0][i];
                choiced[0][i]=temp;
                temp=choiced[1][j];
                choiced[1][j]=choiced[1][i];
                choiced[1][i]=temp;
            }
        }
    }

    ////////////反転処理へ///////////////

    k = choiced[1][0] / 010;
    l = choiced[1][0] % 010;

    // draw_board();
    printf("<白(CPU)のターン>:");
    msectimer(1500);
    printf("%o", k);
    msectimer(250);
    printf("%o", l);
    msectimer(500);
    base[k][l] = WHITE;
    draw_board();
    msectimer(750);

    //////////////////////////////*左向き反転*/////////////////////////////////////
    goturn=0;
    for(i=k,j=l-01;j!=0xFFFFFFFF;j--){
        if(base[i][j]==BLACK){            //逆の石を読んだらループ続行
        }
        else if(base[i][j]==WHITE){    //同じ石を読んだら反転情報を保持してbreak
            goturn=1;
            break;
        }
        else{
            break;                        //石以外を読んだらbreak
        }
    }
    if(goturn==1){            //反転処理
        for(j+=01;j<l;j++){
            if(base[i][j]==BLACK){
                msectimer(250);
                base[i][j]=WHITE;
                draw_board();
            }
        }
    }
    ///////////////////////////////*左上向きに検査*//////////////////////////////////////
    goturn=0;
    for(i=k-01,j=l-01;i!=0xFFFFFFFF&&j!=0xFFFFFFFF;i--,j--){
        if(base[i][j]==BLACK){            //逆の石を読んだらループ続行
        }
        else if(base[i][j]==WHITE){    //同じ石を読んだら反転情報を保持してbreak
            goturn=1;
            break;
        }
        else{
            break;                        //石以外を読んだらbreak
        }
    }
    if(goturn==1){            //反転処理
        for(i+=01,j+=01;i<k;i++,j++){
            if(base[i][j]==BLACK){
                msectimer(250);
                base[i][j]=WHITE;
                draw_board();
            }
        }
    }

    ///////////////////////////////*上向きに検査*/////////////////////////////////////
        goturn=0;
    for(i=k-01,j=l;i!=0xFFFFFFFF;i--){
        if(base[i][j]==BLACK){            //逆の石を読んだらループ続行
        }
        else if(base[i][j]==WHITE){    //同じ石を読んだら反転情報を保持してbreak
            goturn=1;
            break;
        }
        else{
            break;                        //石以外を読んだらbreak
        }
    }

    if(goturn==1){            //反転処理
        for(i+=01;i<k;i++){
            if(base[i][j]==BLACK){
                msectimer(250);
                base[i][j]=WHITE;
                draw_board();
            }
        }
    }

    ////////////////////////////////*右上向きに検査*////////////////////////////////////
        goturn=0;
    for(i=k-01,j=l+01 ;i!=0xFFFFFFFF&&j!=010; i--,j++){
        if(base[i][j]==BLACK){            //逆の石を読んだらループ続行
        }
        else if(base[i][j]==WHITE){    //同じ石を読んだら反転情報を保持してbreak
            goturn=1;
            break;
        }
        else{
            break;                        //石以外を読んだらbreak
        }
    }
    if(goturn==1){            //反転処理
        for(i+=01,j-=01;i<k;i++,j--){
            if(base[i][j]==BLACK){
                msectimer(250);
                base[i][j]=WHITE;
                draw_board();
            }
        }
    }

    ///////////////////////////////*右向きに検査*////////////////////////////////////
        goturn=0;
    for(i=k,j=l+01;j!=010;j++){
        if(base[i][j]==BLACK){            //逆の石を読んだらループ続行
        }
        else if(base[i][j]==WHITE){    //同じ石を読んだら反転情報を保持してbreak
            goturn=1;
            break;
        }
        else{
            break;                        //石以外を読んだらbreak
        }
    }
    if(goturn==1){            //反転処理
        for(j-=01;j>l;j--){
            if(base[i][j]==BLACK){
                msectimer(250);
                base[i][j]=WHITE;
                draw_board();
            }
        }
    }

    ///////////////////////////////*右下向きに検査*//////////////////////////////////////
        goturn=0;
    for(i=k+01,j=l+01 ;i!=010&&j!=010; i++,j++){
        if(base[i][j]==BLACK){            //逆の石を読んだらループ続行
        }
        else if(base[i][j]==WHITE){    //同じ石を読んだら反転情報を保持してbreak
            goturn=1;
            break;
        }
        else{
            break;                        //石以外を読んだらbreak
        }
    }
    if(goturn==1){            //反転処理
        for(i-=01,j-=01;i>k;i--,j--){
            if(base[i][j]==BLACK){
                msectimer(250);
                base[i][j]=WHITE;
                draw_board();
            }
        }
    }

    ///////////////////////////////*下向きに検査*////////////////////////////////////////
        goturn=0;
    for(i=k+01,j=l;i!=010;i++){
        if(base[i][j]==BLACK){            //逆の石を読んだらループ続行
        }
        else if(base[i][j]==WHITE){    //同じ石を読んだら反転情報を保持してbreak
            goturn=1;
            break;
        }
        else{
            break;                        //石以外を読んだらbreak
        }
    }
    if(goturn==1){            //反転処理
        for(i-=01;i>k;i--){
            if(base[i][j]==BLACK){
                msectimer(250);
                base[i][j]=WHITE;
                draw_board();
            }
        }
    }

    /////////////////////////////////*左下向きに検査*///////////////////////////////////
        goturn=0;
    for(i=k+01,j=l-01 ;i!=010&&j!=0xFFFFFFFF; i++,j--){
        if(base[i][j]==BLACK){            //逆の石を読んだらループ続行
        }
        else if(base[i][j]==WHITE){    //同じ石を読んだら反転情報を保持してbreak
            goturn=1;
            break;
        }
        else{
            break;                        //石以外を読んだらbreak
        }
    }
    if(goturn==1){            //反転処理
        for(i-=01,j+=01;i>k;i--,j++){
            if(base[i][j]==BLACK){
                msectimer(250);
                base[i][j]=WHITE;
                draw_board();
            }
        }
    }

    msectimer(500);

    return(1);
}



    //PLAYER側処理->入力と検査と反転//
int ins_and_check(int color1,int color2){        //color1=使用する駒color2=反転される駒

    int i,j,k,l;

    int num;        //入力した数字を一時的に格納する変数
    int goturn;        //反転を許可する変数
    int didturn;    //どれか一方向でも反転できたか判断する変数
    int scnchk;        //不正な文字を入力した時にscanfから0を受け取る変数

    do{
        if(color1==BLACK){
            printf("<黒:置き場を選んで下さい>\n    :");
        }
        else{
            printf("<白:置き場を選んで下さい>\n    :");
        }
            scnchk=scanf("%o[89a-zA-Z\n]",&num);    //不正な文字を入力すればscnchkに0が返る
            getchar();                                //バッファクリア
            k=num/010;l=num%010;
            if(base[k][l]==BLACK||base[k][l]==WHITE){        //既に石のある場を除外する処理
            scnchk=0;
            draw_board();
            }
        }while(num<00||num>100||scnchk==0);            //全て問題なければ反転検査へ

        base[k][l]=color1;
        draw_board();

        didturn=0;
        //////////////////////////////*左向きに検査*/////////////////////////////////////
        goturn=0;
        for(i=k,j=l-01;j!=0xFFFFFFFF;j--){
            if(base[i][j]==color2){            //逆の石を読んだらループ続行
            }
            else if(base[i][j]==color1){    //同じ石を読んだら反転情報を保持してbreak
                goturn=1;
                break;
            }
            else{
                break;                        //石以外を読んだらbreak
            }
        }

        if(goturn==1&&num!=PASS){            //反転処理
            for(j+=01;j<l;j++){
                if(base[i][j]==color2){
                    msectimer(250);
                    base[i][j]=color1;
                    draw_board();
                    didturn=1;
                }
            }
        }

        ///////////////////////////////*左上向きに検査*//////////////////////////////////////
        goturn=0;
        for(i=k-01,j=l-01;i!=0xFFFFFFFF&&j!=0xFFFFFFFF;i--,j--){
            if(base[i][j]==color2){            //逆の石を読んだらループ続行
            }
            else if(base[i][j]==color1){    //同じ石を読んだら反転情報を保持してbreak
                goturn=1;
                break;
            }
            else{
                break;                        //石以外を読んだらbreak
            }
        }

        if(goturn==1&&num!=PASS){            //反転処理
            for(i+=01,j+=01;i<k;i++,j++){
                if(base[i][j]==color2){
                    msectimer(250);
                    base[i][j]=color1;
                    draw_board();
                    didturn=1;
                }
            }
        }

        ///////////////////////////////*上向きに検査*/////////////////////////////////////
        goturn=0;
        for(i=k-01,j=l;i!=0xFFFFFFFF;i--){
            if(base[i][j]==color2){            //逆の石を読んだらループ続行
            }
            else if(base[i][j]==color1){    //同じ石を読んだら反転情報を保持してbreak
                goturn=1;
                break;
            }
            else{
                break;                        //石以外を読んだらbreak
            }
        }

        if(goturn==1&&num!=PASS){            //反転処理
            for(i+=01;i<k;i++){
                if(base[i][j]==color2){
                    msectimer(250);
                    base[i][j]=color1;
                    draw_board();
                    didturn=1;
                }
            }
        }

        ////////////////////////////////*右上向きに検査*////////////////////////////////////
        goturn=0;
        for(i=k-01,j=l+01 ;i!=0xFFFFFFFF&&j!=010; i--,j++){
            if(base[i][j]==color2){            //逆の石を読んだらループ続行
            }
            else if(base[i][j]==color1){    //同じ石を読んだら反転情報を保持してbreak
                goturn=1;
                break;
            }
            else{
                break;                        //石以外を読んだらbreak
            }
        }

        if(goturn==1&&num!=PASS){            //反転処理
            for(i+=01,j-=01;i<k;i++,j--){
                if(base[i][j]==color2){
                    msectimer(250);
                    base[i][j]=color1;
                    draw_board();
                    didturn=1;
                }
            }
        }


        ///////////////////////////////*右向きに検査*////////////////////////////////////
        goturn=0;
        for(i=k,j=l+01;j!=010;j++){
            if(base[i][j]==color2){            //逆の石を読んだらループ続行
            }
            else if(base[i][j]==color1){    //同じ石を読んだら反転情報を保持してbreak
                goturn=1;
                break;
            }
            else{
                break;                        //石以外を読んだらbreak
            }
        }

        if(goturn==1&&num!=PASS){            //反転処理
            for(j-=01;j>l;j--){
                if(base[i][j]==color2){
                    msectimer(250);
                    base[i][j]=color1;
                    draw_board();
                    didturn=1;
                }
            }
        }

        ///////////////////////////////*右下向きに検査*//////////////////////////////////////
        goturn=0;
        for(i=k+01,j=l+01 ;i!=010&&j!=010; i++,j++){
            if(base[i][j]==color2){            //逆の石を読んだらループ続行
            }
            else if(base[i][j]==color1){    //同じ石を読んだら反転情報を保持してbreak
                goturn=1;
                break;
            }
            else{
                break;                        //石以外を読んだらbreak
            }
        }

        if(goturn==1&&num!=PASS){            //反転処理
            for(i-=01,j-=01;i>k;i--,j--){
                if(base[i][j]==color2){
                    msectimer(250);
                    base[i][j]=color1;
                    draw_board();
                    didturn=1;
                }
            }
        }

        ///////////////////////////////*下向きに検査*////////////////////////////////////////
        goturn=0;
        for(i=k+01,j=l;i!=010;i++){
            if(base[i][j]==color2){            //逆の石を読んだらループ続行
            }
            else if(base[i][j]==color1){    //同じ石を読んだら反転情報を保持してbreak
                goturn=1;
                break;
            }
            else{
                break;                        //石以外を読んだらbreak
            }
        }

        if(goturn==1&&num!=PASS){            //反転処理
            for(i-=01;i>k;i--){
                if(base[i][j]==color2){
                    msectimer(250);
                    base[i][j]=color1;
                    draw_board();
                    didturn=1;
                }
            }
        }


        /////////////////////////////////*左下向きに検査*///////////////////////////////////
        goturn=0;
        for(i=k+01,j=l-01 ;i!=010&&j!=0xFFFFFFFF; i++,j--){
            if(base[i][j]==color2){            //逆の石を読んだらループ続行
            }
            else if(base[i][j]==color1){    //同じ石を読んだら反転情報を保持してbreak
                goturn=1;
                break;
            }
            else{
                break;                        //石以外を読んだらbreak
            }
        }

        if(goturn==1&&num!=PASS){            //反転処理
            for(i-=01,j+=01;i>k;i--,j++){
                if(base[i][j]==color2){
                    msectimer(250);
                    base[i][j]=color1;
                    draw_board();
                    didturn=1;
                }
            }
        }

        if(num==PASS){                        //PASS=0100を入力したらパス、両者がパスすればispass=2でゲーム終了
            didturn=1;
            ispass++;
        }
        else{
            ispass=0;
        }

        if(didturn==0){                        //反転不可の時に再入力へ戻す
            base[k][l]=k*010+l;
            draw_board();
            do{
                scnchk=ins_and_check(BLACK,WHITE);
            }while(scnchk!=1);
        }

        return(1);
}
