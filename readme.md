
# miniscript

A fast, declarative, and dynamic programming language implemented in modern C++23.

## 🚀 Overview
**miniscript** is designed to be an embeddable or standalone scripting language that blends the readability of Rust/Swift with the flexibility of dynamic typing. It features a high-performance linear lexer, string interpolation, and powerful pattern matching.

### Key Features
* **Modern C++23 Core**: Leveraging `std::string_view`, `std::variant`, and `std::from_chars` for zero-allocation performance.
* **Declarative Syntax**: Focus on "what" to do, not just "how."
* **Smart String Interpolation**: Handles nested expressions and function calls inside strings natively.
* **Fast Lexing**: Zero-copy tokenization using `std::string_view`.
* **Pattern Matching**: Robust `match` statements for clean conditional logic.

## 🛠 Syntax Example

```swift
const USER = "Developer"

let items = [1, 2, 3]

for(let x in items) {
    println("Item value is {x}")
}

match(USER) {
    "Admin" -> println("Access Granted")
    "Guest" -> println("Limited Access")
    else -> println("Hello, {USER}!")
}

```

## 🔨 Building

Miniscript requires a C++23 compliant compiler (GCC 13+, Clang 16+, or MSVC 19.34+).

```bash
mkdir build && cd build
cmake ..
make -j$(nproc)

```

## 📜 License

Available under the [MIT License](LICENSE).
