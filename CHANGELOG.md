# Changelog

## 2.5.5-pre-alpha
- Removed CMakeLists.txt
- Removed the option to build with CMake in README.md
- You can now write 5.0 without an f at the end
- Fixed parserDumpNode to print ```Lexeme: \"%s\"``` instead of ```lexeme: %s```, same for ```line``` & ```col```
- Fixed the compiler treating ```temp_outside``` as ```temp```, ```_```, ```outside```

## 2.5.4-pre-alpha
- Add ```from``` keyword into the parser
- Remove parserIsType because the parser isn't supposed to type-check
- Add support for floats like ```32.5f```
- tokenToNode now copies ```line``` & ```col``` fields from the token into the node
- parserDumpNode is not gonna show the ```line``` & ```col``` fields if they are zero


## 2.5.3-pre-alpha
- Compiler now recognizes 4 UTF-8 characters as 4 instead of 8 characters

- Added a new error message: ```SYNTAX ERROR: Expected expression, got EOF```
    - Fires when a variable is declared like ```var krabba =```

