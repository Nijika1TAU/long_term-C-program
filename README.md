# long_term-C-program
Why seldom people didn't know this~


## C語言巨集（Macro）是編譯器預處理

單井號（#）和雙井號（##）的功能

（#）: 將其後面的巨集引數進行字串化操作（Stringfication）：

#define WARN_IF(EXP) /
 do{ if (EXP) /
 fprintf(stderr, "Warning: " #EXP "/n"); } /
 while(0)

實際使用會出現下面的替換過程：  WARN_IF (divider == 0);
被替換為
do {
 if (divider == 0)
 fprintf(stderr, "Warning" "divider == 0" "/n");
} while(0);

定義單行巨集：主要有以下三種用法。

1) 前加##或後加##，將標記作為一個合法的識別字的一部分，例如：

#define A(x) T_##x // int A(1) = 10; 等效於 int T_1 = 10;
#define A(x) Tx##__ // int A(1) = 10; 等效於 int T1__ = 10;

2) 前加#，將標記轉換為字串。

#define C(x) #x  // C(1+1) 等效於 "1+1"


## （##）連接子（concatenator）
           
在帶參數的巨集定義中將兩個Token聯接起來，從而形成一個新的Token。
但它不可以是第一個或者最後一個子串。

譬如做一個功能表項目命令名稱和函數指標組成的結構陣列，並在函數名和功能表項目命令名之間有直接名字上的關係：

struct command{
  char * name;
  void (*function) (void);
};

#define COMMAND(NAME) { NAME, NAME ## _command }

struct command commands[] = {
  COMMAND(quit),
  COMMAND(help),
  ...
}

COMMAND在這裡充當一個代碼生成器的作用，這樣可以在一定程度上減少代碼密度，
間接地也可以減少不留心所造成的錯誤。
我們還可以n個##符號連接 n+1個Token，這個特性也是#符號所不具備的。譬如：

#define LINK_MULTIPLE(a,b,c,d) a##_##b##_##c##_##d

typedef struct _record_type LINK_MULTIPLE(name,company,position,salary);

// 這裡這個語句將展開為：
// typedef struct _record_type name_company_position_salary;

MSDN上的一個例子：

#define paster( n ) printf( "token" #n " = %d", token##n )
int token9 = 9;

// Main中調用 paster( 9 ); 這個語句將展開為：
// printf( "token" "9" " = %d", token9 );

注意到在這個例子中，paster(9); 中的這個”9”被原封不動的當成了一個字串，
與”token”連接在了一起，從而成為了token9。
而 #n 也被”9”所替代。可想而知，上面程式運行的結果就是在螢幕上列印出token9=9
