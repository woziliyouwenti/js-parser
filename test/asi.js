// ASI (自动分号插入) 测试用例

// 测试1: return语句后省略分号
function test1() {
    return 42
}

// 测试2: 变量声明后省略分号
var a = 1
var b = 2

// 测试3: 表达式语句后省略分号
console.log("Hello")
console.log("World")

// 测试4: break语句后省略分号
for (var i = 0; i < 10; i++) {
    if (i === 5) {
        break
    }
}

// 测试5: continue语句后省略分号
for (var i = 0; i < 10; i++) {
    if (i % 2 === 0) {
        continue
    }
}

// 测试6: throw语句后省略分号
function testThrow() {
    throw new Error("Test")
}

// 测试7: 多个语句在同一行（需要分号）
var x = 1; var y = 2; var z = 3

// 测试8: 对象字面量
var obj = {
    name: "test",
    value: 100
}

