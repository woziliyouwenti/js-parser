// ASI edge cases

var counter = 0
counter++
counter--

function getValue() {
    return counter
}

var record = {
    name: "counter",
    value: counter
}

var afterObject = record.value

