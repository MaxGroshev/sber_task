# Compiler

Required programs:

- Cmake version  3.21
- Flex
- Bison

# Install and run
```
> git clone git@github.com:MaxGroshev/sber_task.git
> mkdir build
> cd build

```
#### How to run ParaCL?

```
> cmake ..
> make
> ./compiler ../name_of_file

```


# Tests

## As there is only lexer realisation automate testing is not available so far...

Required programs:

- Python
- Google tests


### How to run end to end tests?
Run this command from directory with ```compiler``` binary
```
> python tests/e2e/e2e_tests.py

```


---
<h1 align="center">What Compiler can parse</a></h1>


### Fun progs
```c++
String my_str = "This icode will be parsed!"
/* WHOO
    MULTY
        LINES
            COMMENTS
                ARE AVAILABLE*/

-- YES BUT YOU CAN COMMENT THIS WAY AS WELL

```
### Serious programs too
```c++
Int    x = 10;
String z = ?;
z = "Complicated line\n";

if (x == 5) {
    print 1;
} else if (x == 10) {
    print 2;
    if (x == true)
        print 1212;
    else
        while (x > 9) {
            if (x > 10) {z = 800;}
                else
                    print 4;
            x = x - 1;
        }
    print z;
}
```

<h2 align="center">Error notification</a></h2>

### if you made a lexic mistake compiler will notice you and will continue parse
#### input:
```c++
/* FAILED INPUT.TXT */

if (x < 5)
    print `;
else if (x > 12) {
    x = 8 * (23 - 4);
}
./;

}
```
#### output:

```
---------------------------------------------------------------
| Unknown symbol|
| in line: 4
| lexem_type : ERROR
|     print `;
             ^
---------------------------------------------------------------
---------------------------------------------------------------
| Unknown symbol|
| in line: 9
| lexem_type : ERROR
| ./;
   ^
---------------------------------------------------------------

```

### Main legal lexems:

#### type ident:  ```String``` ```Char``` ```Int```
#### condition operator:  ```if``` ```then``` ```else``` ```while``` ```loop``` (independent to upper and lower case) ...

#### arith operators ```+```  ```-``` ```*``` ```\``` ```%``` ...
#### caompre operator ```>```  ```<``` ```>=``` ```<=``` ```==``` ```!=```

#### iostream ```print```  ```println``` ```?```

#### logic val ```true```  ```false``` ```&&```  ```||``` ...

#### etc (watch ./include/frontend/lixic.l)

---
