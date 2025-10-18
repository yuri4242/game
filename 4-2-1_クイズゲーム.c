#include <stdio.h>
#include <string.h>

#define QUIZ_NUM 5

int main(void){
    char QUIZ[QUIZ_NUM][256] = {
        "2020年に発売され、ヒットしたNintendo Switchのゲーム「○○○○ どうぶつの森」。○○○○に入る言葉は？",
        "2010年代にスマートフォンでヒットしたソーシャルゲーム「パズドラ」の正式名称は？",
        "2000年代にガラケーでヒットした、自転車に乗った棒人間を操作して遊ぶゲームの名称は？",
        "1990年代にゲームセンターに設置され、ブームとなった写真シール機「プリクラ」の正式名称は？",
        "1980年代に大ヒットした家庭用ゲーム機「ファミコン」の正式名称は？"
    };
    char ANS[QUIZ_NUM][256] = {
        "あつまれ",
        "パズル＆ドラゴンズ",
        "チャリ走",
        "プリント倶楽部",
        "ファミリーコンピュータ"
    };

    char ans[256];
    int i, count = 0;

    printf("今から%d問、クイズを出題します。日本語で回答してください。\n", QUIZ_NUM);
    for(i=0; i<QUIZ_NUM; i++){
        printf("第%d問!\n", i+1);
        printf("%s\n", QUIZ[i]);
        //scanf("%s", ans);
        fgets(ans, sizeof(ans), stdin);
        ans[strcspn(ans, "\n")] = '\0';
        if(strcmp(ans, ANS[i])==0){
            printf("正解です。\n");
            count++;
        }else{
            printf("[DEBUG] ans = \"%s\", 正解 = \"%s\"\n", ans, ANS[i]);
            FILE* f = fopen("debug.txt", "w");
            fprintf(f, "ans = %s\n", ans);
            fclose(f);
            //printf("不正解です。正しい回答は%sです。\n", ANS[i]);
        }
    }

    

    printf("あなたの正解数は%d問です!\n", count);


}