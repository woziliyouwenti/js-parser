// 控制流语句测试

// if-else语句
if (x > 0) {
    console.log("positive");
} else {
    console.log("negative");
}

// while循环
var i = 0;
while (i < 10) {
    i++;
}

// for循环
for (var j = 0; j < 10; j++) {
    console.log(j);
}

// do-while循环
var k = 0;
do {
    k++;
} while (k < 10);

// switch语句
switch (x) {
    case 1:
        console.log("one");
        break;
    case 2:
        console.log("two");
        break;
    default:
        console.log("other");
}

// try-catch-finally
try {
    riskyOperation();
} catch (e) {
    console.error(e);
} finally {
    cleanup();
}

