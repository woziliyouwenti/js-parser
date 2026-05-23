# js-parser

A JavaScript syntax checker built with **re2c** (lexer) and **bison** (parser) — a compiler principles course project.

## Features

- Lexical analysis via re2c with ASI (Automatic Semicolon Insertion)
- Syntax parsing via bison covering a broad JS subset
- AST construction and visualization (DOT/HTML output)
- Error recovery and detailed error reporting

## Quick Start

```powershell
mingw32-make
.\js-parser.exe test\basic.js
```

## Documentation

See [PROJECT.md](./PROJECT.md) for full project documentation, build instructions, and debugging history.

## Author

woziliyouwenti
