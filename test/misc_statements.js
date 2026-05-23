// Miscellaneous statements supported by the grammar

debugger;

start:
while (ready) {
    break start;
}

with (config) {
    value = value + 1;
}

for (var key in source) {
    target[key] = source[key];
}

for (let name in registry) {
    console.log(name);
}

