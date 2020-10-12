#include <stdio.h>
#include <unistd.h>

/* n 回出力する関数 f */
void f(int n){
  for(int i=0; i<n; i++){
    write(1," ",1);
  }
}

/* f を m 回呼び出す関数 g */
void g(int m, int n){
  for(int j=0; j<m; j++){
    f(n);
  }
}

int main(int argc, char**argv){
  int n = atoi(argv[1]);
  int m = atoi(argv[2]);
  g(m,n);
}
