#include <stdio.h>
int main() {
   int c = 0;
   for(c = 10; c >= 0; c--){
     printf("%d ", c);
   }
   return 0;
}
/*
間違いはfor文のセミコロンとunsignedである。
for文だけでぐるぐる回してしまうので何も起きない。
アンサインドは最上位ビットを符号ビットとして使わない方法なので、C>=0を満たすのが　かなり大きい数字になってからになるから変な結果が出る
*/
