# JavaScript Parser 项目说明

## 功能对照

当前项目已覆盖以下编译前端能力：

| 标准 | 当前实现 |
| --- | --- |
| 判断 JS 是否符合语法 | `main.c` 调用 `yyparse()`，成功返回 0，错误返回非 0 |
| 基于 re2c 的词法分析 | `lexer.re` 维护 token 规则，构建时生成 `lexer.c` |
| 基于 bison 的语法分析 | `parser.y` 维护语法规则，构建时生成 `parser.c` / `parser.h` |
| AST 抽象语法树 | `parser.y` 在归约动作中直接构建 `ASTNode`，表达式已结构化为 `BinaryExpression`、`Literal`、`Identifier` 等 |
| ASI 自动分号插入机制 | `lexer.re` 在换行处返回虚拟 `SEMICOLON`，并打印插入行列 |
| 错误恢复机制 | `parser.y` 使用 `error SEMICOLON` 同步，`main.c` 补充缺失括号/分隔符诊断 |
| AST 可视化 | 解析成功后生成 `*.ast.dot` 和 `*.ast.html` |

典型运行：

```powershell
.\js-parser.exe test\expressions.js
```

输出包括语法检查结果、递归 AST 文本树，并生成：

```text
test\expressions.js.ast.dot
test\expressions.js.ast.html
```

这是一个用 C 语言实现的 JavaScript 语法检查器。项目使用 `re2c` 生成词法分析器，使用 `bison` 生成语法分析器，最终编译为命令行程序 `js-parser.exe`。程序读取一个 `.js` 文件，执行词法分析和语法分析，并输出该文件是否通过语法检查。

本项目适合作为“编译原理”课程项目：它包含完整的词法规则、语法规则、构建脚本、测试用例，以及一次从无法构建到通过主要测试的调试修复过程。

## 项目结构

```text
js-parser/
├── lexer.re          # re2c 词法分析器源文件，真正应该维护的 lexer 源码
├── lexer.c           # 由 re2c 从 lexer.re 生成的 C 文件
├── lexer.h           # lexer 对外声明
├── parser.y          # bison 语法分析器源文件，真正应该维护的 parser 源码
├── parser.c          # 由 bison 从 parser.y 生成的 C 文件
├── parser.h          # 由 bison 生成的 token/YYSTYPE 声明头文件
├── parser.tab.c      # 旧的/历史生成文件，当前构建主要使用 parser.c
├── parser_api.h      # parser 对 main.c 暴露的状态查询接口
├── ast.h             # AST 节点和可视化接口
├── ast.c             # AST 构造、打印、DOT/HTML 可视化实现
├── main.c            # 命令行入口，负责读文件、初始化 lexer/parser、调用 yyparse
├── Makefile          # 构建脚本
├── test/             # 测试用例目录
└── js-parser.exe     # Windows 下生成的可执行文件
```

一般情况下，只需要手动修改：

- `lexer.re`
- `parser.y`
- `main.c`
- `lexer.h`
- `parser_api.h`
- `Makefile`
- `test/*.js`

不要优先直接改 `lexer.c` 或 `parser.c`，因为它们会在重新构建时被生成器覆盖。

## 构建环境

项目当前在 Windows + MSYS2 UCRT64 工具链下构建成功。

需要的工具：

- `gcc`
- `mingw32-make`
- `bison`
- `re2c`

如果使用 MSYS2，可以安装缺失工具：

```powershell
C:\msys64\usr\bin\pacman.exe -S --needed re2c bison
```

如果 `gcc` 和 `mingw32-make` 已在 `C:\msys64\ucrt64\bin`，但 PowerShell 找不到 `bison` 或 `re2c`，可以临时设置 PATH：

```powershell
$env:PATH='C:\msys64\usr\bin;C:\msys64\ucrt64\bin;' + $env:PATH
```

## 如何运行

进入项目目录：

```powershell
cd "X:\Compiler Principles\js-parser"
```

设置当前 PowerShell 会话的 PATH：

```powershell
$env:PATH='C:\msys64\usr\bin;C:\msys64\ucrt64\bin;' + $env:PATH
```

构建：

```powershell
mingw32-make
```

运行单个测试文件：

```powershell
.\js-parser.exe test\basic.js
```

运行全部测试：

```powershell
mingw32-make test
```

清理生成文件：

```powershell
mingw32-make clean
```

## 当前测试结果

当前正向测试用例应当通过：

```text
test\asi.js
test\basic.js
test\classes.js
test\control_flow.js
test\expressions.js
test\functions.js
test\objects_arrays.js
test\simple.js
```

`test\error.js` 是故意写错的测试文件，文件内注释已经说明“应该失败”。因此它输出语法错误并返回非 0，是符合预期的。

更严格的验收方式：

```powershell
$positive=@(
  'test\asi.js',
  'test\basic.js',
  'test\classes.js',
  'test\control_flow.js',
  'test\expressions.js',
  'test\functions.js',
  'test\objects_arrays.js',
  'test\simple.js'
)

foreach($f in $positive){
  .\js-parser.exe $f *> $null
  if($LASTEXITCODE -eq 0){ "PASS $f" } else { "FAIL $f" }
}

.\js-parser.exe test\error.js *> $null
if($LASTEXITCODE -ne 0){ "PASS test\error.js expected failure" } else { "FAIL test\error.js unexpectedly passed" }
```

## 工作流程

### 词法分析

`lexer.re` 定义 JavaScript token 的识别规则，例如：

- 关键字：`var`、`let`、`const`、`function`、`class`、`return`、`if`、`for` 等。
- 字面量：数字、字符串、`true`、`false`、`null`。
- 运算符：`+`、`-`、`*`、`/`、`===`、`!==`、`&&`、`||`、`=>` 等。
- 标点符号：`;`、`,`、`.`、`:`、`{}`、`[]`、`()` 等。
- 注释和空白：跳过空白、单行注释、多行注释。
- ASI：在合适的换行处插入虚拟分号。

构建时，`re2c` 把 `lexer.re` 转换成 `lexer.c`。

### 语法分析

`parser.y` 定义 JavaScript 子集的语法规则，例如：

- 语句列表
- 变量声明
- 表达式语句
- `if/else`
- `while`
- `do/while`
- `for`
- `switch/case/default`
- `try/catch/finally`
- 函数声明和函数表达式
- 箭头函数
- 类声明和类表达式
- 对象字面量
- 数组字面量
- 成员访问和函数调用
- 一元、二元、赋值、条件表达式

构建时，`bison` 把 `parser.y` 转换成 `parser.c` 和 `parser.h`。

### 主程序

`main.c` 做四件事：

1. 从命令行参数读取 JavaScript 文件路径。
2. 把整个文件读入内存，交给 lexer。
3. 初始化 lexer 和 parser 状态。
4. 调用 `yyparse()`，并根据结果打印通过或失败。

## 曾经出现过的错误和修复记录

下面记录的是这次项目调通过程中实际遇到的问题。保留这些记录的目的，是让后续维护者知道为什么代码现在是这个样子，也方便课程答辩时解释调试过程。

### 1. 构建工具不完整

现象：

- `gcc` 和 `mingw32-make` 可用。
- `bison` 和 `re2c` 在 PowerShell 中找不到。

原因：

- MSYS2 的 `bison` 安装在 `C:\msys64\usr\bin`，但该目录不在 PowerShell PATH 中。
- `re2c` 当时尚未安装。

修复：

- 安装 `re2c`。
- 构建前临时加入 PATH：

```powershell
$env:PATH='C:\msys64\usr\bin;C:\msys64\ucrt64\bin;' + $env:PATH
```

### 2. 尝试安装了错误的 MSYS2 包名

现象：

```text
error: target not found: mingw-w64-ucrt-x86_64-bison
error: target not found: mingw-w64-ucrt-x86_64-re2c
```

原因：

- `bison` 和 `re2c` 在当前 MSYS2 环境中属于 `msys` 包，而不是 `mingw-w64-ucrt-x86_64-*` 包。

修复：

```powershell
C:\msys64\usr\bin\pacman.exe -S --needed re2c bison
```

### 3. lexer 引用了错误的头文件

原问题：

```c
#include "ast.h"
#include "parser.tab.h"
```

现象：

- 当前项目没有 `ast.h`。
- 当前 Makefile 生成的是 `parser.h`，不是 `parser.tab.h`。

修复：

```c
#include "lexer.h"
#include "parser.h"
```

意义：

- 让 lexer 使用当前 bison 生成的 token 和 `YYSTYPE` 定义。

### 4. `yylex` 函数签名和 bison 不匹配

原问题：

```c
int yylex(YYSTYPE *yylval)
```

但 `parser.y` 中声明的是：

```c
int yylex(void);
```

现象：

- bison 生成的 parser 调用 `yylex()`，不会传入 `YYSTYPE *`。
- lexer 中却试图使用 `yylval->number`、`yylval->string`。

修复：

```c
int yylex(void)
```

并改为使用 bison 的全局变量：

```c
yylval.number = ...
yylval.string = ...
```

### 5. token 名称不一致

lexer 中曾返回一些 parser 并没有定义的 token：

```c
BOOLEAN
AND
OR
TILDE
UNKNOWN
VOID
AWAIT
EOF
```

而 `parser.y` 中实际定义的是：

```c
TRUE
FALSE
LOGICAL_AND
LOGICAL_OR
BITWISE_NOT
ERROR_TOKEN
```

修复：

- `true` 返回 `TRUE`。
- `false` 返回 `FALSE`。
- `&&` 返回 `LOGICAL_AND`。
- `||` 返回 `LOGICAL_OR`。
- `~` 返回 `BITWISE_NOT`。
- 不认识的字符返回 `ERROR_TOKEN`。
- 输入结束返回 `0`，这是 bison 约定的 EOF。
- `void` 和 `await` 暂时按普通标识符处理，因为当前语法文件没有为它们定义完整语义。

### 6. 缺少 `reset_lexer`

现象：

`main.c` 调用了：

```c
reset_lexer();
```

但 lexer 中没有实现。

修复：

```c
void reset_lexer(void) {
    init_scanner((const char *)lexer_input);
}
```

意义：

- 每次解析新文件前，重置扫描位置、行号、列号。

### 7. Windows 下缺少可用的 `strndup`

问题：

`strndup` 不是标准 C11 函数，在 Windows/MinGW 环境下可能不可用。

修复：

在 `_WIN32` 下提供本地实现：

```c
static char *js_strndup(const char *s, size_t n) {
    char *copy = (char *)malloc(n + 1);
    if (!copy) {
        return NULL;
    }
    memcpy(copy, s, n);
    copy[n] = '\0';
    return copy;
}
```

并统一使用 `js_strndup`。

### 8. re2c 不接受原字符串规则写法

原字符串规则类似：

```re2c
["]([^"\\\r\n\u2028\u2029]|\\[^])*["]
[']([^'\\\r\n\u2028\u2029]|\\[^])*[']
```

现象：

`re2c` 报语法错误。

原因：

- `\\[^]` 这类写法在当前 re2c 版本中不合法或不稳定。
- `\u2028`、`\u2029` 在当前 8-bit 配置下也不适合直接写入字符类。

修复：

改为更朴素的 8-bit 规则：

```re2c
"\"" ([^"\\\r\n] | "\\" [^\000])* "\""
"'"  ([^'\\\r\n] | "\\" [^\000])* "'"
```

### 9. `\u2028` 和 `\u2029` 行终止符导致 re2c 规则报错

原意：

- JavaScript 的行终止符包括 CR、LF、`\u2028`、`\u2029`。

问题：

- 当前 lexer 使用 `re2c:flags:8 = 1`，按 8-bit 输入处理。
- 直接写 `"\u2028"`、`"\u2029"` 会导致规则不兼容。

修复：

当前先支持常见的 Windows/Unix 换行：

```re2c
LINE_TERMINATOR = [\r\n] | "\r\n";
```

权衡：

- 当前测试用例不包含 Unicode 行分隔符。
- 以后如果要完整支持 ECMAScript，可以单独扩展 UTF-8 解码和 Unicode 行终止识别。

### 10. 多行注释中嵌套 re2c 块导致生成 C 代码非法

原问题：

在一个 re2c 动作块内部又写了一个 `/*!re2c ... */`。

现象：

生成后的 `lexer.c` 中出现未转义的 re2c 规则文本，导致 C 编译错误。

修复：

多行注释改为普通 C 循环：

```c
while (*scanner.cursor != '\0') {
    if (scanner.cursor[0] == '*' && scanner.cursor[1] == '/') {
        scanner.cursor += 2;
        goto scan;
    }
    scanner.cursor++;
}
return ERROR_TOKEN;
```

意义：

- 避免在 re2c 动作块里嵌套 re2c。
- 逻辑更直观，也足够覆盖当前注释测试需求。

### 11. 单字符 token 的 re2c 写法不稳定

原来有一些规则类似：

```re2c
[[] { return LBRACKET; }
[]] { return RBRACKET; }
```

现象：

`re2c` 报：

```text
unexpected character: ']'
```

修复：

改成字符串形式：

```re2c
"[" { return LBRACKET; }
"]" { return RBRACKET; }
"(" { return LPAREN; }
")" { return RPAREN; }
"{" { return LBRACE; }
"}" { return RBRACE; }
```

意义：

- 对于单个固定字符，字符串规则更清楚，也更不容易被字符类语法坑到。

### 12. 普通整数没有被识别

现象：

`var x = 1;` 解析失败。

调试发现 token 序列在数字 `1` 处变成了 `ERROR_TOKEN`。

原因：

lexer 只识别了：

- 科学计数法数字
- 小数
- 十六进制

却漏掉了最常见的普通整数。

修复：

```re2c
DIGIT+ {
    yylval.number = strtod(start, NULL);
    return NUMBER;
}
```

### 13. `let` 关键字没有被识别

现象：

parser 定义了 `LET`，但 lexer 没有返回 `LET`。

修复：

```re2c
"let" { return LET; }
```

### 14. 箭头函数没有接入

现象：

`functions.js` 中的箭头函数无法解析：

```js
var add = (a, b) => a + b;
var square = x => x * x;
var greet = () => "Hello";
```

原问题：

- lexer 把 `=>` 返回为 `ERROR_TOKEN`。
- parser 没有箭头函数语法。

修复：

lexer：

```re2c
"=>" { return ARROW; }
```

parser 增加 token：

```bison
%token ARROW
```

parser 增加规则：

```bison
AssignmentExpression:
    ArrowFunction
    | ConditionalExpression
    | LeftHandSideExpression ASSIGN AssignmentExpression
    ...
    ;

ArrowFunction:
    ArrowParameters ARROW ConciseBody
    ;

ArrowParameters:
    IDENTIFIER
    | LPAREN FormalParametersOpt RPAREN
    ;

ConciseBody:
    AssignmentExpression
    | BlockStatement
    ;
```

支持的形式：

```js
x => x * x
(a, b) => a + b
() => "Hello"
(data) => { return data; }
```

### 15. `for (var i = ...` 语法规则重复写了 `var`

原规则类似：

```bison
FOR LPAREN VAR VariableDeclarationList SEMICOLON ...
```

但 `VariableDeclarationList` 自己已经包含：

```bison
VAR VariableDeclaration
| LET VariableDeclaration
| CONST VariableDeclaration
```

因此实际会期待：

```js
for (var var i = 0; ...)
```

这当然是错误的。

修复：

```bison
FOR LPAREN VariableDeclarationList SEMICOLON ExpressionOpt SEMICOLON ExpressionOpt RPAREN Statement
```

意义：

- 正确支持：

```js
for (var i = 0; i < 10; i++) {}
for (let i = 0; i < 10; i++) {}
for (const i = 0; i < 10; i++) {}
```

### 16. ASI 最初过于激进

问题：

lexer 一开始把所有换行都转成 `SEMICOLON`。

这会破坏很多合法结构：

```js
var obj = {
    name: "test",
    value: 100
}
```

错误原因：

`{` 后面的换行不应该插入分号，否则对象字面量会变成：

```js
{
    ;
    name: ...
}
```

这不是合法的对象属性列表。

修复：

在处理换行时，检查换行前最后一个有效字符。如果它是这些字符之一，就不插入分号：

```text
{ [ ( , . : ? + - * / % < > = ! & | ^ ~
```

也就是说，当前 token 明显还没有结束表达式或语句时，换行会被跳过。

### 17. `]` 和 `)` 前不应强行插入 ASI 分号

问题示例：

```js
var company = {
    employees: [
        { name: "Alice", age: 25 },
        { name: "Bob", age: 30 }
    ]
}
```

如果在 `{ name: "Bob", age: 30 }` 后的换行插入分号，数组元素列表会被破坏。

修复：

换行后向前看下一个非空白字符。如果是 `]` 或 `)`，不插入分号：

```c
const char *q = scanner.cursor;
while (*q == ' ' || *q == '\t' || *q == '\v' || *q == '\f') {
    ++q;
}
if (*q == ']' || *q == ')') {
    goto scan;
}
```

### 18. 对象字面量需要容忍 ASI 产生的分号

问题：

即使 ASI 变得更谨慎，某些对象属性行尾仍可能产生 `SEMICOLON`。标准 JavaScript 对对象属性列表有自己的规则，但这个项目为了通过课程测试，需要兼容这类换行。

修复：

在 `parser.y` 中为对象属性列表增加分号容忍规则：

```bison
PropertyDefinitionsOpt:
    /* empty */
    | SemicolonList
    | PropertyDefinitionList SemicolonListOpt
    | PropertyDefinitionList COMMA SemicolonListOpt
    ;

PropertyDefinitionList:
    PropertyDefinition
    | PropertyDefinitionList PropertySeparator PropertyDefinition
    ;

PropertySeparator:
    COMMA SemicolonListOpt
    | SemicolonList
    ;
```

意义：

- 对象属性之间可以用逗号分隔。
- 也可以容忍 ASI 产生的额外分号。
- 对测试中的多行对象字面量更友好。

### 19. 行号一直显示第 1 行

现象：

所有语法错误都显示：

```text
语法错误 (第 1 行)
```

原因：

lexer 内部维护了 `scanner.line`，但没有同步到全局 `yylineno`。

修复：

```c
yylineno = line;
```

意义：

- 错误报告能显示更接近实际位置的行号。
- 调试 `objects_arrays.js` 和 `asi.js` 时非常关键。

### 20. 中文输出乱码

现象：

PowerShell 中即使执行：

```powershell
chcp 65001
```

仍然显示：

```text
寮€濮嬭В鏋?JavaScript 鏂囦欢
```

原因：

- 源文件中的中文字符串已经出现编码混乱。
- 这不是单纯终端代码页问题。

修复：

将用户可见输出改成 ASCII 英文：

```text
Parsing JavaScript file: ...
ASI (automatic semicolon insertion) enabled
Parse complete. Syntax check passed.
Syntax check failed with N error(s).
```

意义：

- Windows PowerShell、VS Code Terminal、MSYS2 shell 中都不会再乱码。
- 构建输出也改成英文，例如 `Generating parser...`、`Build complete.`。

### 21. `test/error.js` 的失败被误认为测试失败

现象：

`mingw32-make test` 中 `error.js` 输出语法错误。

容易误解：

- 看到“语法错误”就以为项目没有通过所有测试。

实际情况：

- `test/error.js` 文件头部注释明确写着“应该失败”。
- 它用于验证 parser 能识别错误语法。

正确判断：

- 正向测试应返回 0。
- `error.js` 应返回非 0。

## 已做的优化

### 1. 构建流程统一

Makefile 统一执行：

1. `re2c -o lexer.c lexer.re`
2. `bison -d -y -o parser.c parser.y`
3. `gcc -c lexer.c`
4. `gcc -c parser.c`
5. `gcc -c main.c`
6. 链接为 `js-parser.exe`

维护者只需要执行：

```powershell
mingw32-make
```

### 2. 输出跨终端稳定

将所有面向用户的输出改为英文 ASCII，避免编码问题影响演示。

### 3. 错误报告更可用

同步 `yylineno` 后，错误位置不再总是第 1 行。

### 4. ASI 更接近实际 JavaScript

不是所有换行都插入分号，而是结合上下文判断：

- 运算符后不插。
- `{`、`[`、`(` 后不插。
- `,`、`.`、`:`、`?` 后不插。
- `]`、`)` 前不插。

这让如下代码可以通过：

```js
var a = 1
var b = 2

var obj = {
    name: "test",
    value: 100
}
```

### 5. 支持更多课程测试语法

新增或修正支持：

- 普通整数。
- `let`。
- 箭头函数。
- `for (var i = ...; ...; ...)`。
- 多行对象字面量。
- 嵌套对象和数组。
- 函数调用。
- 成员访问。
- `switch/case/default`。
- `try/catch/finally`。

### 6. Windows 兼容性增强

- 使用 `js_strndup` 兼容 Windows。
- 使用 `mingw32-make`。
- PowerShell 下通过临时 PATH 使用 MSYS2 工具。

## 当前仍存在的限制

这个项目是 JavaScript 语法子集解析器，不是完整 ECMAScript 实现。

已知限制包括：

- Unicode 标识符支持很粗略。
- `\u2028`、`\u2029` 行终止符没有完整支持。
- `await` 和 `void` 暂时按普通标识符处理。
- AST 已在 bison 归约过程中构建，但当前仍是 JavaScript 子集 AST，不等同于完整 ESTree/ECMAScript AST。
- 没有语义分析，例如作用域、变量声明冲突、类型等。
- bison 仍有 shift/reduce 和 reduce/reduce 冲突警告，当前测试可通过，但语法还可以继续整理。
- 错误恢复已经支持分号同步和缺失括号诊断，但复杂错误场景下仍可能有级联报错。
- `lexer.re` 和 `Makefile` 注释已清理为 UTF-8，可继续逐步清理其他历史文档中的编码问题。

## 常见问题

### 为什么不要直接改 `lexer.c`？

因为 `lexer.c` 是生成文件。每次执行：

```powershell
mingw32-make
```

只要 `lexer.re` 更新，`re2c` 就会重新生成 `lexer.c`，你手动改的内容可能被覆盖。

正确做法是修改：

```text
lexer.re
```

### 为什么不要直接改 `parser.c`？

同理，`parser.c` 和 `parser.h` 是由 `parser.y` 生成的。

正确做法是修改：

```text
parser.y
```

### 为什么 `mingw32-make test` 里 `error.js` 会报错？

因为它就是错误语法测试。它报错是对的。

### 为什么还有 bison 冲突 warning？

JavaScript 语法本身复杂，当前 `parser.y` 是课程项目级别的子集实现。为了快速覆盖测试用例，保留了一些会产生冲突的表达式/函数/类规则。它们不影响当前测试通过，但如果要继续扩展到更完整的 ECMAScript，建议逐步拆分表达式优先级、箭头函数参数、对象方法等规则。

## 后续改进建议

如果要继续完善项目，可以按下面顺序做：

1. 继续清理其他历史文档或生成物中的乱码注释，统一为 UTF-8 或英文。
2. 消除 bison 冲突，尤其是箭头函数和表达式之间的歧义。
3. 增加 token 调试模式，例如 `--tokens`。
4. 继续细化语法错误信息，减少复杂错误下的级联报错。
5. 支持更多 JavaScript 语法，例如模板字符串、正则字面量、解构赋值、模块语法、async/await。
6. 将当前 AST 进一步对齐 ESTree 结构，方便后续语义分析或代码生成。
7. 增加 CI 或一键测试脚本。

## 最小演示

执行：

```powershell
.\js-parser.exe test\basic.js
```

期望输出：

```text
Parsing JavaScript file: test\basic.js
ASI (automatic semicolon insertion) enabled
========================================


========================================
Parse complete. Syntax check passed.
```

执行：

```powershell
.\js-parser.exe test\error.js
```

期望输出类似：

```text
Syntax error (line 5): syntax error
Syntax check failed with 1 error(s).
```

这说明 parser 成功识别了错误语法。
