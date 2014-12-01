/**
 * @file parser.h
 *
 * @brief
 * C++ Expression parser. See the header file for more detailed explanation
 *
 * @license
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy
 * of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 *
 * Copyright (C) 2007-2011 Jos de Jong, http://www.speqmath.com
 *
 * The parser is based on the example "A mini C++ Interpreter" from the
 * book "The art of C++" by Herbert Schildt.
 *
 * @author 	Jos de Jong, <wjosdejong@gmail.com>
 * @date	2007-12-22, updated 2012-02-06
 */

/*********************************************************
*     *****
*    *~~~~~*   Partial Differential Equations Resource
*     *o o*              (PDER)
*     *  *
*     * *     By: Joseph Dorris, Joey Allen, ALex Kotzman
*    **                   and Wilson Parker
*   *
*********************************************************/

// declarations
#include "expression_parser.h"


using namespace std;



/*
 * constructor.
 * Initializes all data with zeros and empty strings
 */
Parser::Parser()
{
    expr[0] = '\0';
    e = NULL;

    token[0] = '\0';
    token_type = NOTHING;
    temp_var = new Variablelist();
}

/*
 * destructor.
 * need to delete all initialized arrays
 */
Parser::~Parser() {
    delete temp_var;
}

/*
 * setup all the equations to solve
 *
 */
void Parser::set_eqs(char ** equations, int num) {
  eqs = equations;
  num_eqs = num;
}

/*
 * Solve all of the equations once
 *
 */
void Parser::solve(Variablelist* vars) {
  user_var = vars;

  for(int i=0;i<num_eqs;i++) {
    parse(eqs[i]);
  }
}


/**
 * parses and evaluates the given expression
 * On error, an error of type Error is thrown
 */
void Parser::parse(const char new_expr[])
{
    try
    {
        // check the length of expr
        if ((int)strlen(new_expr) > EXPR_LEN_MAX)
        {
            throw Error(row(), col(), 200);
        }

        // initialize all variables
        strncpy(expr, new_expr, EXPR_LEN_MAX - 1);  // copy the given expression to expr
        e = expr;                                  // let e point to the start of the expression
        ans = 0;

        getToken();
        if (token_type == DELIMETER && *token == '\0')
        {
            throw Error(row(), col(), 4);
        }

        parse_level1();
        // check for garbage at the end of the expression
        // an expression ends with a character '\0' and token_type = delimeter
        if (token_type != DELIMETER || *token != '\0')
        {
            if (token_type == DELIMETER)
            {
                // user entered a not existing operator like "//"
                throw Error(row(), col(), 101, token);
            }
            else
            {
                throw Error(row(), col(), 5, token);
            }
        }

        // add the answer to memory as variable "Ans"
        //user_var->add("Ans", ans);

        //snprintf(ans_str, sizeof(ans_str), "Ans = %g", ans_test);
    }
    catch (Error err)
    {
        if (err.get_row() == -1)
        {
            snprintf(ans_str, sizeof(ans_str), "Error: %s (col %i)", err.get_msg(), err.get_col());
        }
        else
        {
            snprintf(ans_str, sizeof(ans_str), "Error: %s (ln %i, col %i)", err.get_msg(), err.get_row(), err.get_col());
        }
    }

    //return ans_str;
}


/*
 * checks if the given char c is a minus
 */
bool isMinus(const char c)
{
    if (c == 0) return 0;
    return c == '-';
}



/*
 * checks if the given char c is whitespace
 * whitespace when space chr(32) or tab chr(9)
 */
bool isWhiteSpace(const char c)
{
    if (c == 0) return 0;
    return c == 32 || c == 9;  // space or tab
}

/*
 * checks if the given char c is a delimeter
 * minus is checked apart, can be unary minus
 */
bool isDelimeter(const char c)
{
    if (c == 0) return 0;
    return strchr("&|<>=+/*%^!", c) != 0;
}

/*
 * checks if the given char c is NO delimeter
 */
bool isNotDelimeter(const char c)
{
    if (c == 0) return 0;
    return strchr("&|<>=+-/*%^!()", c) != 0;
}

/*
 * checks if the given char c is a letter or undersquare
 */
bool isAlpha(const char c)
{
    if (c == 0) return 0;
    return strchr("ABCDEFGHIJKLMNOPQRSTUVWXYZ_", toupper(c)) != 0;
}

/*
 * checks if the given char c is a digit or dot
 */
bool isDigitDot(const char c)
{
    if (c == 0) return 0;
    return strchr("0123456789.", c) != 0;
}

/*
 * checks if the given char c is a digit
 */
bool isDigit(const char c)
{
    if (c == 0) return 0;
    return strchr("0123456789", c) != 0;
}


/**
 * Get next token in the current string expr.
 * Uses the Parser data expr, e, token, t, token_type and err
 */
void Parser::getToken()
{
    token_type = NOTHING;
    char* t;           // points to a character in token
    t = token;         // let t point to the first character in token
    *t = '\0';         // set token empty

    //printf("\tgetToken e:{%c}, ascii=%i, col=%i\n", *e, *e, e-expr);

    // skip over whitespaces
    while (*e == ' ' || *e == '\t')     // space or tab
    {
        e++;
    }

    // check for end of expression
    if (*e == '\0')
    {
        // token is still empty
        token_type = DELIMETER;
        return;
    }

    // check for minus
    if (*e == '-')
    {
        token_type = DELIMETER;
        *t = *e;
        e++;
        t++;
        *t = '\0';  // add a null character at the end of token
        return;
    }

    // check for parentheses
    if (*e == '(' || *e == ')')
    {
        token_type = DELIMETER;
        *t = *e;
        e++;
        t++;
        *t = '\0';
        return;
    }

    // check for operators (delimeters)
    if (isDelimeter(*e))
    {
        token_type = DELIMETER;
        while (isDelimeter(*e))
        {
            *t = *e;
            e++;
            t++;
        }
        *t = '\0';  // add a null character at the end of token
        return;
    }

    // check for a value
    if (isDigitDot(*e))
    {
        token_type = NUMBER;
        while (isDigitDot(*e))
        {
            *t = *e;
            e++;
            t++;
        }

        // check for scientific notation like "2.3e-4" or "1.23e50"
        if (toupper(*e) == 'E')
        {
            *t = *e;
            e++;
            t++;

            if (*e == '+' || *e == '-')
            {
                *t = *e;
                e++;
                t++;
            }

            while (isDigit(*e))
            {
                *t = *e;
                e++;
                t++;
            }
        }

        *t = '\0';
        return;
    }

    // check for variables or functions
    if (isAlpha(*e))
    {
        while (isAlpha(*e) || isDigit(*e))
        //while (isNotDelimeter(*e))
        {
            *t = *e;
            e++;
            t++;
        }
        *t = '\0';  // add a null character at the end of token

        // check if this is a variable or a function.
        // a function has a parentesis '(' open after the name
        char* e2 = NULL;
        e2 = e;

        // skip whitespaces
        while (*e2 == ' ' || *e2 == '\t')     // space or tab
        {
            e2++;
        }

        if (*e2 == '(')
        {
            token_type = FUNCTION;
        }
        else
        {
            token_type = VARIABLE;
        }
        return;
    }

    // something unknown is found, wrong characters -> a syntax error
    token_type = UNKNOWN;
    while (*e != '\0')
    {
        *t = *e;
        e++;
        t++;
    }
    *t = '\0';
    throw Error(row(), col(), 1, token);

    return;
}


/*
 * assignment of variable or function
 */
void Parser::parse_level1()
{
    if (token_type == VARIABLE)
    {
        // copy current token
        char* e_now = e;
        TOKENTYPE token_type_now = token_type;
        char token_now[NAME_LEN_MAX+1];
        strcpy(token_now, token);

        getToken();
        if (strcmp(token, "=") == 0)
        {

            // assignment
            VAR* ans;
            getToken();
            ans = parse_level2();
            
            if(user_var->exist(token_now)) {
              //user_var->print();
              user_var->add(token_now,ans);
            }
            else if (temp_var->add(token_now, ans) == false)
            {
                throw Error(row(), col(), 300);
            }
        }
        else
        {
            // go back to previous token
            e = e_now;
            token_type = token_type_now;
            strcpy(token, token_now);
        }
    }
}


/*
 * conditional operators and bitshift
 */
VAR* Parser::parse_level2()
{
    int op_id;
    VAR* ans;
    ans = parse_level3();

    op_id = get_operator_id(token);
    while (op_id == AND || op_id == OR || op_id == BITSHIFTLEFT || op_id == BITSHIFTRIGHT)
    {
        getToken();
        ans = eval_operator(op_id, ans, parse_level3());
        op_id = get_operator_id(token);
    }

    return ans;
}

/*
 * conditional operators
 */
VAR* Parser::parse_level3()
{
    int op_id;
    VAR* ans;
    ans = parse_level4();

    op_id = get_operator_id(token);
    while (op_id == EQUAL || op_id == UNEQUAL || op_id == SMALLER || op_id == LARGER || op_id == SMALLEREQ || op_id == LARGEREQ)
    {
        getToken();
        ans = eval_operator(op_id, ans, parse_level4());
        op_id = get_operator_id(token);
    }

    return ans;
}

/*
 * add or subtract
 */
VAR* Parser::parse_level4()
{
    int op_id;
    VAR* ans;
    ans = parse_level5();

    op_id = get_operator_id(token);
    while (op_id == PLUS || op_id == MINUS)
    {
        getToken();
        ans = eval_operator(op_id, ans, parse_level5());
        op_id = get_operator_id(token);
    }

    return ans;
}


/*
 * multiply, divide, modulus, xor
 */
VAR* Parser::parse_level5()
{
    int op_id;
    VAR* ans;
    ans = parse_level6();

    op_id = get_operator_id(token);
    while (op_id == MULTIPLY || op_id == DIVIDE || op_id == MODULUS || op_id == XOR)
    {
        getToken();
        ans = eval_operator(op_id, ans, parse_level6());
        op_id = get_operator_id(token);
    }

    return ans;
}


/*
 * power
 */
VAR* Parser::parse_level6()
{
    int op_id;
    VAR* ans;
    ans = parse_level7();

    op_id = get_operator_id(token);
    while (op_id == POW)
    {
        getToken();
        ans = eval_operator(op_id, ans, parse_level7());
        op_id = get_operator_id(token);
    }

    return ans;
}

/*
 * Factorial
 */
VAR* Parser::parse_level7()
{
    int op_id;
    VAR* ans;
    ans = parse_level8();
    VAR* temp;
    op_id = get_operator_id(token);
    while (op_id == FACTORIAL)
    {
        getToken();
        // factorial does not need a value right from the
        // operator, so zero is filled in.
        ans = eval_operator(op_id, ans, temp);
        op_id = get_operator_id(token);
    }

    return ans;
}

/*
 * Unary minus
 */
VAR* Parser::parse_level8()
{
    VAR* var1;
    VAR* ret_var;

    int op_id = get_operator_id(token);
    if (op_id == MINUS)
    { 
        getToken();
        var1 = parse_level9();
        VAR* temp_minus = new VAR;
        temp_minus->set_type(0);
        temp_minus->val=-1.0;
        ret_var = mult(var1,temp_minus);
    }
    else
    {
        ret_var = parse_level9();
    }

    return ret_var;
}


/*
 * functions
 */
VAR* Parser::parse_level9()
{
    char fn_name[NAME_LEN_MAX+1];
    VAR* ans;

    if (token_type == FUNCTION)
    {
        strcpy(fn_name, token);
        getToken();
        ans = eval_function(fn_name, parse_level10());
    }
    else
    {
        ans = parse_level10();
    }

    return ans;
}


/*
 * parenthesized expression or value
 */
VAR* Parser::parse_level10()
{
    // check if it is a parenthesized expression
    if (token_type == DELIMETER)
    {
        if (token[0] == '(' && token[1] == '\0')
        {
            getToken();
            VAR* ans = parse_level2();
            if (token_type != DELIMETER || token[0] != ')' || token[1] || '\0')
            {
                throw Error(row(), col(), 3);
            }
            getToken();
            return ans;
        }
    }

    // if not parenthesized then the expression is a value
    return parse_number();
}


VAR* Parser::parse_number()
{
double ans = 0;
VAR* ret_var = new VAR;

    switch (token_type)
    {
        case NUMBER:
            // this is a number
            ans = strtod(token, NULL);
            ret_var->set_type(0);
            ret_var->val=ans;
            getToken();
            break;

        case VARIABLE:
            // this is a variable
            ret_var = eval_variable(token);
            getToken();
            break;

        default:
            // syntax error or unexpected end of expression
            if (token[0] == '\0')
            {
                throw Error(row(), col(), 6);
            }
            else
            {
                throw Error(row(), col(), 7);
            }
            break;
    }

    return ret_var;
}


/*
 * returns the id of the given operator
 * treturns -1 if the operator is not recognized
 */
int Parser::get_operator_id(const char op_name[])
{
    // level 2
    if (!strcmp(op_name, "&")) {return AND;}
    if (!strcmp(op_name, "|")) {return OR;}
    if (!strcmp(op_name, "<<")) {return BITSHIFTLEFT;}
    if (!strcmp(op_name, ">>")) {return BITSHIFTRIGHT;}

    // level 3
    if (!strcmp(op_name, "=")) {return EQUAL;}
    if (!strcmp(op_name, "<>")) {return UNEQUAL;}
    if (!strcmp(op_name, "<")) {return SMALLER;}
    if (!strcmp(op_name, ">")) {return LARGER;}
    if (!strcmp(op_name, "<=")) {return SMALLEREQ;}
    if (!strcmp(op_name, ">=")) {return LARGEREQ;}

    // level 4
    if (!strcmp(op_name, "+")) {return PLUS;}
    if (!strcmp(op_name, "-")) {return MINUS;}

    // level 5
    if (!strcmp(op_name, "*")) {return MULTIPLY;}
    if (!strcmp(op_name, "/")) {return DIVIDE;}
    if (!strcmp(op_name, "%")) {return MODULUS;}
    if (!strcmp(op_name, "||")) {return XOR;}

    // level 6
    if (!strcmp(op_name, "^")) {return POW;}

    // level 7
    if (!strcmp(op_name, "!")) {return FACTORIAL;}

    return -1;
}


/*
 * evaluate an operator for given valuess
 */
VAR* Parser::eval_operator(const int op_id, VAR* lhs, VAR* rhs)
{
    VAR* ret_var;
    switch (op_id)
    {   /*
        // level 2
        case AND:           return static_cast<int>(lhs) & static_cast<int>(rhs);
        case OR:            return static_cast<int>(lhs) | static_cast<int>(rhs);
        case BITSHIFTLEFT:  return static_cast<int>(lhs) << static_cast<int>(rhs);
        case BITSHIFTRIGHT: return static_cast<int>(lhs) >> static_cast<int>(rhs);

        // level 3
        case EQUAL:     return lhs == rhs;
        case UNEQUAL:   return lhs != rhs;
        case SMALLER:   return lhs < rhs;
        case LARGER:    return lhs > rhs;
        case SMALLEREQ: return lhs <= rhs;
        case LARGEREQ:  return lhs >= rhs;
        */

        // level 4
        case PLUS:  return add(lhs,rhs);    
        case MINUS:     return sub(lhs,rhs);

        // level 5
        case MULTIPLY:  return mult(lhs,rhs);
        case DIVIDE:    return divide(lhs,rhs);
 
       
       case MODULUS:   return vmod(lhs,rhs); // todo: give a warning if the values are not integer?
       /* case XOR:       return static_cast<int>(lhs) ^ static_cast<int>(rhs);

        // level 6
        case POW:       return pow(lhs, rhs);

        // level 7
        case FACTORIAL: return factorial(lhs);
        */
    }

    throw Error(row(), col(), 104, op_id);
    ret_var = new VAR;
    ret_var->set_type(-1);
    return ret_var;
}


/*
 * evaluate a function
 */
VAR* Parser::eval_function(const char fn_name[], VAR* value)
{
    VAR * ret_var;
    try
    {
        // first make the function name upper case
        char fnU[NAME_LEN_MAX+1];
        toupper(fnU, fn_name);
        /*
        // arithmetic
        if (!strcmp(fnU, "ABS")) {
          ret_var = vabs(value);
          delete value;
          return ret_var;
        }
        if (!strcmp(fnU, "EXP")) {
          ret_var = vexp(value);
          delete value;
          return ret_var;
        }
        if (!strcmp(fnU, "SIGN")) {
          ret_var = vsign(value);
          delete value;
          return ret_var;
        }
        if (!strcmp(fnU, "SQRT")) {
          ret_var = vsqrt(value);
          delete value;
          return ret_var;
        }
        if (!strcmp(fnU, "LOG")) {
          ret_var = vlog(value);
          delete value;
          return ret_var;
        }
        if (!strcmp(fnU, "LOG10")) {
          ret_var = vlog10(value);
          delete value;
          return ret_var;
        }

        // trigonometric
        if (!strcmp(fnU, "SIN")) {
          ret_var = vsin(value);
          delete value;
          return ret_var;
        }
        if (!strcmp(fnU, "COS")) {
          ret_var = vcos(value);
          delete value;
          return ret_var;
        }
        if (!strcmp(fnU, "TAN")) {
          ret_var = vtan(value);
          delete value;
          return ret_var;
        }
        if (!strcmp(fnU, "ASIN")) {
          ret_var = vasin(value);
          delete value;
          return ret_var;
        }
        if (!strcmp(fnU, "ACOS")) {
          ret_var = vacos(value);
          delete value;
          return ret_var;
        }
        if (!strcmp(fnU, "ATAN")) {
          return vatan(value);
        }

        // probability
        if (!strcmp(fnU, "FACTORIAL")) {return factorial(value);}*/
      
        if (!strcmp(fnU, "GRAD")) {
          return grad(value);
        }
        if (!strcmp(fnU, "USTP")) {
          return ustp(value);
        }
        if (!strcmp(fnU, "RAND")) {
          return rand(value);
        }
        if (!strcmp(fnU, "CURL")) {
          return curl(value);
        }
        if (!strcmp(fnU, "DIVERG")) {
          return diverg(value);
        }
        if (!strcmp(fnU, "MAG")) {
          return mag(value);
        }
        if (!strcmp(fnU, "LAPLAC")) {
          return laplac(value);
        }
        if (!strcmp(fnU, "RAND")) {
          return rand(value);
        }
    }
    catch (Error err)
    {
        // retrow error, add information about column and row of occurance
        // TODO: doesnt work yet
        throw Error(col(), row(), err.get_id(), err.get_msg());
    }

    // unknown function
    throw Error(row(), col(), 102, fn_name);
    ret_var = new VAR;
    ret_var->set_type(-1);
    return ret_var;
}


/*
 * evaluate a variable
 */
VAR* Parser::eval_variable(const char var_name[])
{
    VAR * ret_var = new VAR;
    // first make the variable name uppercase
    char varU[NAME_LEN_MAX+1];
    toupper(varU, var_name);
    // check for built-in variables
    if(!strcmp(varU, "E")) {
      ret_var->set_type(0);
      ret_var->val=2.7182818284590452353602874713527;
      return ret_var;
    }
    if(!strcmp(varU, "PI")) {
      ret_var->set_type(0);
      ret_var->val=3.1415926535897932384626433832795;
      return ret_var;
    }

    // check for user defined variables
    if (user_var->get_variable(var_name, ret_var))
    {
        return ret_var;
    }


    // check for new defined variables
    if (temp_var->get_variable(var_name, ret_var))
    {
        return ret_var;
    }

    // unknown variable
    throw Error(row(), col(), 103, var_name);
    ret_var->set_type(-1);
    return ret_var;
}



/*
 * Shortcut for getting the current row value (one based)
 * Returns the line of the currently handled expression
 */
int Parser::row()
{
    return -1;
}

/*
 * Shortcut for getting the current col value (one based)
 * Returns the column (position) where the last token starts
 */
int Parser::col()
{
    return e-expr-strlen(token)+1;
}
