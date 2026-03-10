// minilang support types:
// null - no value at all
// bool - true/false
// number - any number in range taken from C double type
// str  - "strings"
// array - [] for empty, or init with some data, like [0,1,2,3]
// dict - {} for empty, or make it look like JSON: { "key": "value", "number": 3.1415926, "boolean": false, "nullable": null }

// str, array, dict - iterable and complex types
// null, bool, number - is simple types

// special types:
// pair - hold 2 objects, used as iterable object when looping over dict, also can be used as iterable object (array with 2 values)
// lambda - hold function, non-iterable type, but can be inserted into array or dict

// variables declared using 'let' keyword, variable name and value, value is required, because miniscript is dynamic typed, so it's deduct types by value
let a = true // bool type

if(a) {
    println("a is True")
} else {
    println("a is False")
}

// for making pair use
let p = pair("key","value")

//lambda
let fn = func(n){
    println("Hello from {n}")
}

//call lambda:
fn("user")