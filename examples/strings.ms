// minilang support string interpolation
// that means you can write

println("Hello, from {input("Your name: ")}")

// when run it looks:
// Your name: user
// Hello, from user

// interpreter should run inner statements 1 by 1
// so if you write
println("Hello, from {input("Your name: ")}, to {input("Guest name: ")}")

// it should looks:
// Your name: user
// Guest name: user1
// Hello, from user, to user1

// also string is simple type, but it have some inner methods
// len() - return length of string
// find(c) - return position of first character that same as c, or -1 if cannot find any
// substr(range/from,to) - return substring of current string within a range
// also strings supports +, += operators for concatenation
// and can be used in for loops as iterable

let str = "word"
for(let c in str){
    println(c) // prints number, for printing string make temp string using 'string(c)' function
}
