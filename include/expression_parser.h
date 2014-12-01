/**
 * @file parser.h
 *
 * @brief
 * C++ Expression parser
 *
 * Features:
 *     Operators:
 *         & | << >>
 *         = <> < > <= >=
 *         + -
 *         * / % ||
 *         ^
 *         !
 *
 *     Functions:
 *         Abs, Exp, Sign, Sqrt, Log, Log10
 *         Sin, Cos, Tan, ASin, ACos, ATan
 *         Factorial
 *
 *     Variables:
 *         Pi, e
 *         you can define your own variables
 *
 *     Other:
 *        Scientific notation supported
 *         Error handling supported
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

#ifndef EXPRESSION_PARSER_H
#define EXPRESSION_PARSER_H

// declarations
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>

#include "constants.h"
#include "error.h"
//#include "functions.h"
#include "variablelist.h"
#include "variable.h"
#include "operators.h"

using namespace std;

class Parser
{
    // public functions
    public:
        Parser();
	~Parser();
        void parse(const char expr[]);
	void set_eqs(char ** eqs, int num_eqs);
        void solve(Variablelist* vars);

    // enumerations
    private:

        enum TOKENTYPE {NOTHING = -1, DELIMETER, NUMBER, VARIABLE, FUNCTION, UNKNOWN};

        enum OPERATOR_ID {AND, OR, BITSHIFTLEFT, BITSHIFTRIGHT,                 // level 2
                       EQUAL, UNEQUAL, SMALLER, LARGER, SMALLEREQ, LARGEREQ,    // level 3
                       PLUS, MINUS,                     // level 4
                       MULTIPLY, DIVIDE, MODULUS, XOR,  // level 5
                       POW,                             // level 6
                       FACTORIAL};                      // level 7

    // data
    private:
	char ** eqs;
        int num_eqs;

        char expr[EXPR_LEN_MAX+1];    // holds the expression
        char* e;                      // points to a character in expr

        char token[NAME_LEN_MAX+1];   // holds the token
        TOKENTYPE token_type;         // type of the token

        VAR* ans;                   // holds the result of the expression
        char ans_str[255];            // holds a string containing the result
                                      // of the expression

        Variablelist* user_var;        // list with variables defined by user
        Variablelist* temp_var;        // temporary vars

    // private functions
    private:
        void getToken();

        void parse_level1();
        VAR* parse_level2();
        VAR* parse_level3();
        VAR* parse_level4();
        VAR* parse_level5();
        VAR* parse_level6();
        VAR* parse_level7();
        VAR* parse_level8();
        VAR* parse_level9();
        VAR* parse_level10();
        VAR* parse_number();

        int get_operator_id(const char op_name[]);
        VAR* eval_operator(const int op_id, VAR* lhs, VAR* rhs);
        VAR* eval_function(const char fn_name[], VAR* value);
        VAR* eval_variable(const char var_name[]);

        int row();
        int col();
};

#endif
