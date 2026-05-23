// 对象和数组测试

// 对象字面量
var person = {
    name: "John",
    age: 30,
    city: "New York"
};

// 数组字面量
var numbers = [1, 2, 3, 4, 5];
var mixed = [1, "two", 3.0, true];

// 嵌套对象
var company = {
    name: "Tech Corp",
    employees: [
        { name: "Alice", age: 25 },
        { name: "Bob", age: 30 }
    ],
    address: {
        street: "123 Main St",
        city: "San Francisco"
    }
};

// 数组访问
var first = numbers[0];
var last = numbers[numbers.length - 1];

// 对象属性访问
var personName = person.name;
var personAge = person["age"];

