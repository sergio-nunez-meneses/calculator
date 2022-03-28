# [The shunting-yard algorithm](https://en.wikipedia.org/wiki/Shunting-yard_algorithm)

Parses an arithmetical expression in [infix notation](https://en.wikipedia.org/wiki/Infix_notation), and returns it in 
postfix notation or [Reverse Polish notation](https://en.wikipedia.org/wiki/Reverse_Polish_notation). The result 
of the infix expression is also returned.

Example:

```
Enter an arithmetical expression, separating with whitespaces operands, operators and parentheses:

3 + 4 * ( 2 - 1 )

Reverse Polish Notation: 3.000000 4.000000 2.000000 1.000000 - * + 
Expression result: 7.000000
```

Supported arithmetic operations are exponentiation, multiplication, division, addition, and subtraction.

Built to learn the basis of the C++ language.

# [The shunting-yard algorithm in detail](https://en.wikipedia.org/wiki/Shunting-yard_algorithm#The_algorithm_in_detail)

```
/* This implementation does not implement composite functions, functions with variable number of arguments, and unary operators. */

while there are tokens to be read:
    read a token

    if the token is:
    - a number:
        put it into the output queue

    - a function:
        push it onto the operator stack

    - an operator o1:
        while (
            there is an operator o2 other than the left parenthesis at the top of the operator stack,
            and (o2 has greater precedence than o1 or they have the same precedence and o1 is left-associative)
        ):
            pop o2 from the operator stack into the output queue

        push o1 onto the operator stack

    - a left parenthesis (i.e. "("):
        push it onto the operator stack

    - a right parenthesis (i.e. ")"):
        while the operator at the top of the operator stack is not a left parenthesis:
            {assert the operator stack is not empty}

            /* If the stack runs out without finding a left parenthesis, then there are mismatched parentheses. */

            pop the operator from the operator stack into the output queue
        
        {assert there is a left parenthesis at the top of the operator stack}
        pop the left parenthesis from the operator stack and discard it
        
        if there is a function token at the top of the operator stack, then:
            pop the function from the operator stack into the output queue
            
/* After the while loop, pop the remaining items from the operator stack into the output queue. */
while there are tokens on the operator stack:
    /* If the operator token on the top of the stack is a parenthesis, then there are mismatched parentheses. */

    {assert the operator on top of the stack is not a (left) parenthesis}
    pop the operator from the operator stack onto the output queue
```

# TODO

- Implement a [stack version](https://www.cplusplus.com/reference/stack/stack/)
- Implement an object-oriented version