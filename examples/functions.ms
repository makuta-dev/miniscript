func power(a,b){
    let value = a
    while(b > 1){
        value *= a
        b--
    }
    ret value
}

func main(){
    println("3^4 = {power(3,4)}")
}