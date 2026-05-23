// 表达式测试

// 算术表达式
var sum = 1 + 2 + 3;
var product = 4 * 5 * 6;
var quotient = 10 / 2;
var remainder = 10 % 3;

// 比较表达式
var eq = (1 == 1);
var ne = (1 != 2);
var seq = (1 === 1);
var sne = (1 !== 2);
var lt = (1 < 2);
var gt = (2 > 1);
var le = (1 <= 2);
var ge = (2 >= 1);

// 逻辑表达式
var and = true && false;
var or = true || false;
var not = !true;

// 赋值表达式
var x = 10;
x += 5;
x -= 3;
x *= 2;
x /= 4;

// 条件表达式
var result = (x > 0) ? "positive" : "negative";

// 函数调用
function greet(name) {
    return "Hello, " + name;
}
var message = greet("World");

