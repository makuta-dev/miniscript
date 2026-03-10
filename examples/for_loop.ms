println("For based loop over range from 0 to 5")
for(let i in 0..5){
    println(i)
}

let items = [2,4,8,6,1,3,7,5,9]

println("For based loop over array")
for(let number in items){
    println(number)
}

println("For based loop over array with indices")
for(let index in 0..items.len()){
    let number = items[index]
    println("items[{index}] = {number}")
}

println("For based loop with decreasing range from 5 to 0")
for(let n in 5..0){
    println(n)
}

println("For loop over floating numbers with custom step")
for(let f in range(0.0,1.0,0.1)){ // range(from, to, step = 1)
    println(f)
}

let dict = {
    "key": "value",
    "number": 3.1415926,
    "boolean": false,
    "nullable": null
}

println("For loop for dict with pair type")
for(let p in dict){
    println("{p.first} - {p.second}")
    // or use index
    // println("{p[0]} - {p[1]}")
}

println("For loop for dict with separate temp vars")
for(let key, value in dict){
    println("{key} - {value}")
}
