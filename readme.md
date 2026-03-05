# 📜 Miniscript

**Miniscript** is a high-performance, lightweight interpreted programming language. It is designed to bridge the gap between high-level scriptability and low-level predictability by blending the best of **JavaScript**, **Lua**, and **C++**.

Built from the ground up using **C++23**, the interpreter leverages modern systems programming patterns to stay fast, safe, and "mini."

---

## ✨ Features at a Glance

* **Modern C++23 Core:** Utilizes `std::expected`, `std::variant`, and `std::string_view` for a zero-copy, branch-optimized execution engine.
* **Hybrid Syntax:**
  * **JS-inspired:** Dynamic typing and intuitive Object/Array literals.
  * **Lua-inspired:** Minimalist keywords (like `ret`) and lightweight footprint.
  * **C++-inspired:** Block scoping, explicit operators (`--`, `*=`), and familiar control flow.
* **Expression-Bodied Functions:** Concise single-line function definitions using `=`.
* **Native Interpolation:** Evaluate logic directly inside strings using `{expression}`.

---

## 💻 Language Showcase

### 1. Variables & Data Structures

Miniscript supports rich, nested data structures with a simple `let` syntax.

```
let is_active = true
let count = 42
let message = "Hello, Miniscript"
let list = [1, 2, 3]
let user = {
    "id": 101,
    "active": is_active,
    "roles": ["admin", "editor"],
    "message": message
}

```

### 2. Functions & Control Flow

Familiar C-style logic meets streamlined returns.

```
# Traditional block function
func power(a, b) {
    let value = a
    while(b > 1) {
        value *= a
        b--
    }
    ret value
}

# Expression-bodied function
func square(n) = n * n

func main() {
    // String interpolation support
    println("3^4 = {power(3, 4)}")
    println("Square of 5 is {square(5)}")
}

```

See files in examples folder to know more

---

## 📊 How It Compares

| Feature           | **Miniscript** | JavaScript        | C++           | Lua                |
|-------------------|----------------|-------------------|---------------|--------------------|
| **Declaration**   | `let x = 5`    | `let x = 5`       | `int x = 5;`  | `local x = 5`      |
| **Return**        | `ret x`        | `return x;`       | `return x;`   | `return x`         |
| **Function**      | `func f() {}`  | `function f() {}` | `void f() {}` | `function f() end` |
| **Decrement**     | `x--`          | `x--`             | `x--`         | `x = x - 1`        |
| **Interpolation** | `"{x}"`        | ``${x}``          | `std::format` | `".." .. x`        |

---

## 🛠 Technical Internals (C++23)

Miniscript isn't just a script; it’s a showcase of modern C++ capabilities:

* **Zero-Copy Lexing:** Uses `std::string_view` to tokenize without unnecessary allocations.
* **Type-Safe Values:** The internal `Value` system is powered by `std::variant`, providing speed without the dangers of raw pointers or unions.
* **Functional Error Handling:** Uses `std::expected` to propagate parser and runtime errors without the overhead of exceptions.

---

## 🚀 Getting Started

### Prerequisites

* **Compiler:** GCC 13+, Clang 16+, or MSVC 19.35+
* **Build Tool:** CMake 4.0+

### Installation

```bash
# Clone the repo
git clone https://github.com/makuta-dev/miniscript.git
cd miniscript

# Build
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build

```

### Running Scripts

```bash
./build/miniscript your_script.ms

```

---

## 📄 License

Distributed under the MIT License. See `LICENSE` for more information.