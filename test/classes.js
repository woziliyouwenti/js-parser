// 类测试

// 类声明
class Person {
    constructor(name, age) {
        this.name = name;
        this.age = age;
    }
    
    greet() {
        return "Hello, I'm " + this.name;
    }
    
    getAge() {
        return this.age;
    }
}

// 类继承
class Student extends Person {
    constructor(name, age, school) {
        super(name, age);
        this.school = school;
    }
    
    study() {
        return "Studying at " + this.school;
    }
}

// 类表达式
var Animal = class {
    constructor(name) {
        this.name = name;
    }
    
    speak() {
        return this.name + " makes a sound";
    }
};

