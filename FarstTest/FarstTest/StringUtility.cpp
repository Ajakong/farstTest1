#include "StringUtility.h"
#include <DxLib.h>
#include <cassert>

std::wstring StringUtility::StringToWString(const std::string& str)
{
    // in : 情報側はstring(あらかじめ分かっている)
    // out : 戻り値はwstring(文字列数もわからない)
    
    // MultiByteToWideCharは、２回呼び出すことを期待されている。
    // １回目の呼び出しは、変換後文字列のサイズを得るため
    // ２回目の呼び出しで、返還後文字列を得る

    std::wstring ret;   // 最終的に返すワイド文字列(最初は何も入っていない)

    // １回目の呼び出し
    int result = MultiByteToWideChar(
        CP_ACP,     // 基の文字列のコードページを書きます(ACPはANSI文字列=ShitfJIS)
        0,          // 変換オプションですが、今回は特に指定なしですので0
        str.data(), // 元の文字列の先頭ポインタ
        str.size(), // 元の文字列の文字列数
        nullptr,    // out, optionalなので、nullptrを渡しておく
        static_cast<int>(0));         // ここでは意味ないので0にしておく

    // 一度目の呼び出しの戻り値が、変換後文字列の文字数になっています。
    assert(result >= 0);

    ret.resize(result); // 受け取れる文字列のバッファを確保する

    result = MultiByteToWideChar(
        CP_ACP,     // 元のコードページ
        0,          // オプション
        str.data(), // 元の文字列へのアドレス
        str.size(), // 元文字列の文字数
        ret.data(), // 変換後文字列のアドレス
        static_cast<int>(ret.size()));// 変換後の文字列数

    return ret;
}
