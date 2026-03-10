let i = 1

//match is a smarter version of switch
match(i){
    0 -> println("i equals to zero")
    1 -> println("i = 1")
    else -> {} //empty body for default, but it's required to have
}

// also match can be smart chain of if..else statements
match {
    i < 0 -> println("i is less than zero")
    i == 0 -> println("i == 0")
    i > 0 -> println("i is greater than zero")
    else -> {} // here else is optional
}
