// 函数测试

// 函数声明
function multiply(a, b) {
    return a * b;
}

// 函数表达式
var divide = function(a, b) {
    return a / b;
};

// 箭头函数
var add = (a, b) => a + b;
var square = x => x * x;
var greet = () => "Hello";

// 箭头函数（带块）
var process = (data) => {
    var result = data * 2;
    return result;
};

// 嵌套函数
function outer() {
    var x = 10;
    function inner() {
        return x * 2;
    }
    return inner();
}

// 递归函数
function factorial(n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

