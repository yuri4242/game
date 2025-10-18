#include <stdio.h>
#include <time.h>
#include <stdlib.h>

const int MAX_NUM = 99;

int main(void){
    srand((unsigned)time(NULL));
    int r = rand() & MAX_NUM + 1;
    int num, count;

    printf("私が思い浮かべている数字を当ててください。\n");
    printf("その数字は1~%dまでのどれかです。\n", MAX_NUM);
    printf("さて、その数字は？\n");
    scanf("%d", &num);

    while(num != r){
        if(num > r){
            printf("それより小さい値です。");
            printf("その数字は？");
            scanf("%d", &num);
            count++;
        }else{
            printf("それより大きな値です。");
            printf("その数字は？");
            scanf("%d", &num);
            count++;
        }
    }

    if(num == r) printf("大正解!!\n"); printf("あなたは%d回で正解しました。\n", count);

}