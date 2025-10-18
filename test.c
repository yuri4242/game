#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <wctype.h>
#include <fcntl.h>  // ← _O_U16TEXT の定義
#include <io.h>     // ← _setmode, _fileno の定義


#define QUIZ_NUM 1

int main(void) {
    setlocale(LC_ALL, "");         // ロケール設定（日本語対応）
    _setmode(_fileno(stdout), 0x00020000); // UTF-16出力（Windows専用）
    _setmode(_fileno(stdin), 0x00020000);  // UTF-16入力（Windows専用）

    wchar_t ans[256];
    wchar_t correct[] = L"あつまれ";

    wprintf(L"日本語で回答してください：\n");
    fgetws(ans, 256, stdin);
    ans[wcscspn(ans, L"\n")] = L'\0';  // 改行除去

    wprintf(L"[DEBUG] ans = \"%ls\", 正解 = \"%ls\"\n", ans, correct);

    if (wcscmp(ans, correct) == 0) {
        wprintf(L"正解です！\n");
    } else {
        wprintf(L"不正解です。\n");
    }

    return 0;
}
