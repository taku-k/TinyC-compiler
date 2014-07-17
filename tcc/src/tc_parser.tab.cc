// A Bison parser, made by GNU Bison 3.0.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2013 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


// First part of user declarations.

#line 37 "tc_parser.tab.cc" // lalr1.cc:398

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

#include "tc_parser.tab.hh"

// User implementation prologue.

#line 51 "tc_parser.tab.cc" // lalr1.cc:406
// Unqualified %code blocks.
#line 21 "tc_parser.yy" // lalr1.cc:407

  #include <fstream>
  #include <cstdlib>
  #include <iostream>
  #include <string>
  #include "tc_driver.h"

#undef yylex
#define yylex scanner.yylex


#line 65 "tc_parser.tab.cc" // lalr1.cc:407


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif



// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyempty = true)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 4 "tc_parser.yy" // lalr1.cc:473
namespace TC {
#line 132 "tc_parser.tab.cc" // lalr1.cc:473

  /// Build a parser object.
  TC_Parser::TC_Parser (TC_Scanner &scanner_yyarg, TC_Driver &driver_yyarg, NodeList &nl_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      scanner (scanner_yyarg),
      driver (driver_yyarg),
      nl (nl_yyarg)
  {}

  TC_Parser::~TC_Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
  TC_Parser::syntax_error::syntax_error (const std::string& m)
    : std::runtime_error (m)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  TC_Parser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  TC_Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
  {
    value = other.value;
  }


  template <typename Base>
  inline
  TC_Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v)
    : Base (t)
    , value (v)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  inline
  TC_Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t)
    : Base (t)
    , value ()
  {}

  template <typename Base>
  inline
  TC_Parser::basic_symbol<Base>::~basic_symbol ()
  {
  }

  template <typename Base>
  inline
  void
  TC_Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
    value = s.value;
  }

  // by_type.
  inline
  TC_Parser::by_type::by_type ()
     : type (empty)
  {}

  inline
  TC_Parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  TC_Parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  TC_Parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.type = empty;
  }

  inline
  int
  TC_Parser::by_type::type_get () const
  {
    return type;
  }


  // by_state.
  inline
  TC_Parser::by_state::by_state ()
    : state (empty)
  {}

  inline
  TC_Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  TC_Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.state = empty;
  }

  inline
  TC_Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  TC_Parser::symbol_number_type
  TC_Parser::by_state::type_get () const
  {
    return state == empty ? 0 : yystos_[state];
  }

  inline
  TC_Parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  TC_Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s)
  {
    value = that.value;
    // that is emptied.
    that.type = empty;
  }

  inline
  TC_Parser::stack_symbol_type&
  TC_Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    return *this;
  }


  template <typename Base>
  inline
  void
  TC_Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    switch (yysym.type_get ())
    {
            case 11: // Id

#line 93 "tc_parser.yy" // lalr1.cc:598
        { if ((yysym.value.id))  { delete ((yysym.value.id)); ((yysym.value.id)) = NULL; } }
#line 309 "tc_parser.tab.cc" // lalr1.cc:598
        break;

      case 41: // external_declaration

#line 94 "tc_parser.yy" // lalr1.cc:598
        { if ((yysym.value.node))  { delete ((yysym.value.node)); ((yysym.value.node)) = NULL; } }
#line 316 "tc_parser.tab.cc" // lalr1.cc:598
        break;

      case 42: // declaration

#line 94 "tc_parser.yy" // lalr1.cc:598
        { if ((yysym.value.node))  { delete ((yysym.value.node)); ((yysym.value.node)) = NULL; } }
#line 323 "tc_parser.tab.cc" // lalr1.cc:598
        break;

      case 43: // declarator_list

#line 95 "tc_parser.yy" // lalr1.cc:598
        { if ((yysym.value.list))  { delete ((yysym.value.list)); ((yysym.value.list)) = NULL; } }
#line 330 "tc_parser.tab.cc" // lalr1.cc:598
        break;

      case 44: // declarator

#line 94 "tc_parser.yy" // lalr1.cc:598
        { if ((yysym.value.node))  { delete ((yysym.value.node)); ((yysym.value.node)) = NULL; } }
#line 337 "tc_parser.tab.cc" // lalr1.cc:598
        break;

      case 45: // function_definition

#line 94 "tc_parser.yy" // lalr1.cc:598
        { if ((yysym.value.node))  { delete ((yysym.value.node)); ((yysym.value.node)) = NULL; } }
#line 344 "tc_parser.tab.cc" // lalr1.cc:598
        break;

      case 46: // func_def_declarator

#line 94 "tc_parser.yy" // lalr1.cc:598
        { if ((yysym.value.node))  { delete ((yysym.value.node)); ((yysym.value.node)) = NULL; } }
#line 351 "tc_parser.tab.cc" // lalr1.cc:598
        break;

      case 47: // parameter_type_list

#line 95 "tc_parser.yy" // lalr1.cc:598
        { if ((yysym.value.list))  { delete ((yysym.value.list)); ((yysym.value.list)) = NULL; } }
#line 358 "tc_parser.tab.cc" // lalr1.cc:598
        break;

      case 48: // parameter_declaration

#line 94 "tc_parser.yy" // lalr1.cc:598
        { if ((yysym.value.node))  { delete ((yysym.value.node)); ((yysym.value.node)) = NULL; } }
#line 365 "tc_parser.tab.cc" // lalr1.cc:598
        break;

      case 49: // statement

#line 94 "tc_parser.yy" // lalr1.cc:598
        { if ((yysym.value.node))  { delete ((yysym.value.node)); ((yysym.value.node)) = NULL; } }
#line 372 "tc_parser.tab.cc" // lalr1.cc:598
        break;

      case 50: // compound_statement

#line 94 "tc_parser.yy" // lalr1.cc:598
        { if ((yysym.value.node))  { delete ((yysym.value.node)); ((yysym.value.node)) = NULL; } }
#line 379 "tc_parser.tab.cc" // lalr1.cc:598
        break;

      case 53: // declaration_list

#line 95 "tc_parser.yy" // lalr1.cc:598
        { if ((yysym.value.list))  { delete ((yysym.value.list)); ((yysym.value.list)) = NULL; } }
#line 386 "tc_parser.tab.cc" // lalr1.cc:598
        break;

      case 54: // statement_list

#line 95 "tc_parser.yy" // lalr1.cc:598
        { if ((yysym.value.list))  { delete ((yysym.value.list)); ((yysym.value.list)) = NULL; } }
#line 393 "tc_parser.tab.cc" // lalr1.cc:598
        break;

      case 55: // expression

#line 94 "tc_parser.yy" // lalr1.cc:598
        { if ((yysym.value.node))  { delete ((yysym.value.node)); ((yysym.value.node)) = NULL; } }
#line 400 "tc_parser.tab.cc" // lalr1.cc:598
        break;

      case 56: // assign_expr

#line 94 "tc_parser.yy" // lalr1.cc:598
        { if ((yysym.value.node))  { delete ((yysym.value.node)); ((yysym.value.node)) = NULL; } }
#line 407 "tc_parser.tab.cc" // lalr1.cc:598
        break;

      case 57: // logical_OR_expr

#line 94 "tc_parser.yy" // lalr1.cc:598
        { if ((yysym.value.node))  { delete ((yysym.value.node)); ((yysym.value.node)) = NULL; } }
#line 414 "tc_parser.tab.cc" // lalr1.cc:598
        break;

      case 58: // logical_AND_expr

#line 94 "tc_parser.yy" // lalr1.cc:598
        { if ((yysym.value.node))  { delete ((yysym.value.node)); ((yysym.value.node)) = NULL; } }
#line 421 "tc_parser.tab.cc" // lalr1.cc:598
        break;

      case 59: // bit_or_expr

#line 94 "tc_parser.yy" // lalr1.cc:598
        { if ((yysym.value.node))  { delete ((yysym.value.node)); ((yysym.value.node)) = NULL; } }
#line 428 "tc_parser.tab.cc" // lalr1.cc:598
        break;

      case 60: // bit_xor_expr

#line 94 "tc_parser.yy" // lalr1.cc:598
        { if ((yysym.value.node))  { delete ((yysym.value.node)); ((yysym.value.node)) = NULL; } }
#line 435 "tc_parser.tab.cc" // lalr1.cc:598
        break;

      case 61: // bit_and_expr

#line 94 "tc_parser.yy" // lalr1.cc:598
        { if ((yysym.value.node))  { delete ((yysym.value.node)); ((yysym.value.node)) = NULL; } }
#line 442 "tc_parser.tab.cc" // lalr1.cc:598
        break;

      case 62: // equality_expr

#line 94 "tc_parser.yy" // lalr1.cc:598
        { if ((yysym.value.node))  { delete ((yysym.value.node)); ((yysym.value.node)) = NULL; } }
#line 449 "tc_parser.tab.cc" // lalr1.cc:598
        break;

      case 63: // relational_expr

#line 94 "tc_parser.yy" // lalr1.cc:598
        { if ((yysym.value.node))  { delete ((yysym.value.node)); ((yysym.value.node)) = NULL; } }
#line 456 "tc_parser.tab.cc" // lalr1.cc:598
        break;

      case 64: // add_expr

#line 94 "tc_parser.yy" // lalr1.cc:598
        { if ((yysym.value.node))  { delete ((yysym.value.node)); ((yysym.value.node)) = NULL; } }
#line 463 "tc_parser.tab.cc" // lalr1.cc:598
        break;

      case 65: // mult_expr

#line 94 "tc_parser.yy" // lalr1.cc:598
        { if ((yysym.value.node))  { delete ((yysym.value.node)); ((yysym.value.node)) = NULL; } }
#line 470 "tc_parser.tab.cc" // lalr1.cc:598
        break;

      case 66: // unary_expr

#line 94 "tc_parser.yy" // lalr1.cc:598
        { if ((yysym.value.node))  { delete ((yysym.value.node)); ((yysym.value.node)) = NULL; } }
#line 477 "tc_parser.tab.cc" // lalr1.cc:598
        break;

      case 67: // postfix_expr

#line 94 "tc_parser.yy" // lalr1.cc:598
        { if ((yysym.value.node))  { delete ((yysym.value.node)); ((yysym.value.node)) = NULL; } }
#line 484 "tc_parser.tab.cc" // lalr1.cc:598
        break;

      case 68: // func_call_identifier

#line 94 "tc_parser.yy" // lalr1.cc:598
        { if ((yysym.value.node))  { delete ((yysym.value.node)); ((yysym.value.node)) = NULL; } }
#line 491 "tc_parser.tab.cc" // lalr1.cc:598
        break;

      case 69: // primary_expr

#line 94 "tc_parser.yy" // lalr1.cc:598
        { if ((yysym.value.node))  { delete ((yysym.value.node)); ((yysym.value.node)) = NULL; } }
#line 498 "tc_parser.tab.cc" // lalr1.cc:598
        break;

      case 70: // argument_expression_list

#line 95 "tc_parser.yy" // lalr1.cc:598
        { if ((yysym.value.list))  { delete ((yysym.value.list)); ((yysym.value.list)) = NULL; } }
#line 505 "tc_parser.tab.cc" // lalr1.cc:598
        break;

      case 71: // constant

#line 94 "tc_parser.yy" // lalr1.cc:598
        { if ((yysym.value.node))  { delete ((yysym.value.node)); ((yysym.value.node)) = NULL; } }
#line 512 "tc_parser.tab.cc" // lalr1.cc:598
        break;

      case 72: // Identifier

#line 94 "tc_parser.yy" // lalr1.cc:598
        { if ((yysym.value.node))  { delete ((yysym.value.node)); ((yysym.value.node)) = NULL; } }
#line 519 "tc_parser.tab.cc" // lalr1.cc:598
        break;


      default:
        break;
    }
  }

#if YYDEBUG
  template <typename Base>
  void
  TC_Parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " (";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  TC_Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  TC_Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  TC_Parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  TC_Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  TC_Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  TC_Parser::debug_level_type
  TC_Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  TC_Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline TC_Parser::state_type
  TC_Parser::yy_lr_goto_state_ (state_type yystate, int yylhs)
  {
    int yyr = yypgoto_[yylhs - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yylhs - yyntokens_];
  }

  inline bool
  TC_Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  TC_Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  TC_Parser::parse ()
  {
    /// Whether yyla contains a lookahead.
    bool yyempty = true;

    // State.
    int yyn;
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// $$ and @$.
    stack_symbol_type yylhs;

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULL, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyempty)
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            yyla.type = yytranslate_ (yylex (&yyla.value));
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
        yyempty = false;
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Discard the token being shifted.
    yyempty = true;

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
    /* If YYLEN is nonzero, implement the default value of the action:
       '$$ = $1'.  Otherwise, use the top of the stack.

       Otherwise, the following line sets YYLHS.VALUE to garbage.
       This behavior is undocumented and Bison
       users should not rely upon it.  */
    if (yylen)
      yylhs.value = yystack_[yylen - 1].value;
    else
      yylhs.value = yystack_[0].value;


    // Perform the reduction.
    YY_REDUCE_PRINT (yyn);
    try
      {
        switch (yyn)
          {
  case 2:
#line 100 "tc_parser.yy" // lalr1.cc:846
    {
                                set_tc_driver(&driver);
                                set_tc_scanner(&scanner);
                                set_token_driver(driver.getTokenDriver());
                              }
#line 756 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 4:
#line 108 "tc_parser.yy" // lalr1.cc:846
    { nl.add((yystack_[0].value.node)); }
#line 762 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 5:
#line 109 "tc_parser.yy" // lalr1.cc:846
    { nl.add((yystack_[0].value.node)); }
#line 768 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 6:
#line 112 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 774 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 7:
#line 113 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 780 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 8:
#line 120 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = new DeclTypeNode(OP::INT, (yystack_[1].value.list), &driver); }
#line 786 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 9:
#line 123 "tc_parser.yy" // lalr1.cc:846
    { ((yylhs.value.list) = new DeclList())->append((yystack_[0].value.node)); }
#line 792 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 10:
#line 124 "tc_parser.yy" // lalr1.cc:846
    { ((yylhs.value.list) = (yystack_[2].value.list))->append((yystack_[0].value.node)); }
#line 798 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 11:
#line 128 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 804 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 12:
#line 134 "tc_parser.yy" // lalr1.cc:846
    {
                                                                                                                    (yylhs.value.node) = new FuncNode(new RetNode(OP::INT), (yystack_[5].value.node), new ParamDeclList(), (yystack_[1].value.node)); 
                                                                                                                  }
#line 812 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 13:
#line 137 "tc_parser.yy" // lalr1.cc:846
    {
                                                                                                                                        (yylhs.value.node) = new FuncNode(new RetNode(OP::INT), (yystack_[6].value.node), (yystack_[3].value.list), (yystack_[1].value.node)); 
                                                                                                                                     }
#line 820 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 14:
#line 142 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = make_func_def((yystack_[0].value.node)); }
#line 826 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 15:
#line 145 "tc_parser.yy" // lalr1.cc:846
    { ((yylhs.value.list) = new ParamDeclList())->append((yystack_[0].value.node)); }
#line 832 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 16:
#line 146 "tc_parser.yy" // lalr1.cc:846
    { ((yylhs.value.list) = (yystack_[2].value.list))->append((yystack_[0].value.node)); }
#line 838 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 17:
#line 149 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = new ParamDeclNode(OP::INT, (yystack_[0].value.node)); }
#line 844 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 18:
#line 152 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = new StatNode(NULL); }
#line 850 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 19:
#line 153 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = new StatNode((yystack_[1].value.node)); }
#line 856 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 20:
#line 154 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 862 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 21:
#line 155 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = new IFStatNode((yystack_[2].value.node), (yystack_[0].value.node)); }
#line 868 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 22:
#line 156 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = new IFStatNode((yystack_[4].value.node), (yystack_[2].value.node), (yystack_[0].value.node)); }
#line 874 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 23:
#line 157 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = new WHILEStatNode((yystack_[2].value.node), (yystack_[0].value.node)); }
#line 880 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 24:
#line 158 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = new RETURNStatNode((yystack_[1].value.node)); }
#line 886 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 25:
#line 159 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = new FORStatNode((yystack_[6].value.node), (yystack_[4].value.node), (yystack_[2].value.node), (yystack_[0].value.node)); }
#line 892 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 26:
#line 162 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = new ComStatNode((yystack_[2].value.list), new StatList()); }
#line 898 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 27:
#line 163 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = new ComStatNode((yystack_[3].value.list), (yystack_[2].value.list)); }
#line 904 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 28:
#line 164 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = new ComStatNode(new DeclarationList(), (yystack_[2].value.list)); }
#line 910 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 29:
#line 165 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = new ComStatNode(new DeclarationList(), new StatList()); }
#line 916 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 30:
#line 168 "tc_parser.yy" // lalr1.cc:846
    { (driver.getTokenDriver())->level_up(); }
#line 922 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 31:
#line 171 "tc_parser.yy" // lalr1.cc:846
    {
                                                                            (driver.getTokenDriver())->Pop(driver.getTokenDriver()->get_cur_level());
                                                                            (driver.getTokenDriver())->level_down();
                                                                          }
#line 931 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 32:
#line 177 "tc_parser.yy" // lalr1.cc:846
    { ((yylhs.value.list) = new DeclarationList())->append((yystack_[0].value.node)); }
#line 937 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 33:
#line 178 "tc_parser.yy" // lalr1.cc:846
    { ((yylhs.value.list) = (yystack_[1].value.list))->append((yystack_[0].value.node)); }
#line 943 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 34:
#line 181 "tc_parser.yy" // lalr1.cc:846
    { ((yylhs.value.list) = new StatList())->append((yystack_[0].value.node)); }
#line 949 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 35:
#line 182 "tc_parser.yy" // lalr1.cc:846
    { ((yylhs.value.list) = (yystack_[1].value.list))->append((yystack_[0].value.node)); }
#line 955 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 36:
#line 185 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = new ExpressionList((yystack_[0].value.node), NULL); }
#line 961 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 37:
#line 186 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = new ExpressionList((yystack_[0].value.node), (yystack_[2].value.node)); }
#line 967 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 38:
#line 189 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = new AssignExprNode((yystack_[0].value.node)); }
#line 973 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 39:
#line 190 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = new AssignExprNode(OP::ASSIGN, ref_var((yystack_[2].value.node)), (yystack_[0].value.node)); }
#line 979 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 40:
#line 191 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = new AssignExprNode(OP::ADDASSIGN, ref_var((yystack_[2].value.node)), (yystack_[0].value.node)); }
#line 985 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 41:
#line 192 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = new AssignExprNode(OP::SUBASSIGN, ref_var((yystack_[2].value.node)), (yystack_[0].value.node)); }
#line 991 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 42:
#line 195 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 997 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 43:
#line 196 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = new ExprNode((yystack_[1].value.op), (yystack_[2].value.node), (yystack_[0].value.node)); }
#line 1003 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 44:
#line 199 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1009 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 45:
#line 200 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = new ExprNode((yystack_[1].value.op), (yystack_[2].value.node), (yystack_[0].value.node)); }
#line 1015 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 46:
#line 203 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1021 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 47:
#line 204 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = new ExprNode(OP::BITOR, (yystack_[2].value.node), (yystack_[0].value.node)); }
#line 1027 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 48:
#line 207 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1033 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 49:
#line 208 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = new ExprNode(OP::BITXOR, (yystack_[2].value.node), (yystack_[0].value.node)); }
#line 1039 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 50:
#line 211 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1045 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 51:
#line 212 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = new ExprNode(OP::BITAND, (yystack_[2].value.node), (yystack_[0].value.node)); }
#line 1051 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 52:
#line 215 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1057 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 53:
#line 216 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = new ExprNode((yystack_[1].value.op), (yystack_[2].value.node), (yystack_[0].value.node)); }
#line 1063 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 54:
#line 217 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = new ExprNode((yystack_[1].value.op), (yystack_[2].value.node), (yystack_[0].value.node)); }
#line 1069 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 55:
#line 220 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1075 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 56:
#line 221 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = new ExprNode(OP::LESS, (yystack_[2].value.node), (yystack_[0].value.node)); }
#line 1081 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 57:
#line 222 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = new ExprNode(OP::GREATER, (yystack_[2].value.node), (yystack_[0].value.node)); }
#line 1087 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 58:
#line 223 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = new ExprNode(OP::GREATEREQUAL, (yystack_[2].value.node), (yystack_[0].value.node)); }
#line 1093 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 59:
#line 224 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = new ExprNode(OP::LESSEQUAL, (yystack_[2].value.node), (yystack_[0].value.node)); }
#line 1099 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 60:
#line 227 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1105 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 61:
#line 228 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = new ExprNode(OP::ADD, (yystack_[2].value.node), (yystack_[0].value.node)); }
#line 1111 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 62:
#line 229 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = new ExprNode(OP::SUB, (yystack_[2].value.node), (yystack_[0].value.node)); }
#line 1117 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 63:
#line 232 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1123 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 64:
#line 233 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = new ExprNode(OP::MUL, (yystack_[2].value.node), (yystack_[0].value.node)); }
#line 1129 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 65:
#line 234 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = new ExprNode(OP::DIV, (yystack_[2].value.node), (yystack_[0].value.node)); }
#line 1135 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 66:
#line 237 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1141 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 67:
#line 238 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = new UnaryNode(OP::MINUS, (yystack_[0].value.node)); }
#line 1147 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 68:
#line 241 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1153 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 69:
#line 242 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = new FuncCallNode((yystack_[3].value.node), (yystack_[1].value.list)); }
#line 1159 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 70:
#line 243 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = new FuncCallNode((yystack_[2].value.node), new FuncArgsList());}
#line 1165 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 71:
#line 246 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = ref_func((yystack_[0].value.node)); }
#line 1171 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 72:
#line 249 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = ref_var((yystack_[0].value.node)); }
#line 1177 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 73:
#line 250 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1183 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 74:
#line 251 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = (yystack_[1].value.node); }
#line 1189 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 75:
#line 254 "tc_parser.yy" // lalr1.cc:846
    { ((yylhs.value.list) = new FuncArgsList())->append((yystack_[0].value.node)); }
#line 1195 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 76:
#line 255 "tc_parser.yy" // lalr1.cc:846
    { ((yylhs.value.list) = (yystack_[2].value.list))->append((yystack_[0].value.node)); }
#line 1201 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 77:
#line 258 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = new IntegerNode((yystack_[0].value.val)); }
#line 1207 "tc_parser.tab.cc" // lalr1.cc:846
    break;

  case 78:
#line 261 "tc_parser.yy" // lalr1.cc:846
    { (yylhs.value.node) = make_identifier(*(yystack_[0].value.id)); }
#line 1213 "tc_parser.tab.cc" // lalr1.cc:846
    break;


#line 1217 "tc_parser.tab.cc" // lalr1.cc:846
          default:
            break;
          }
      }
    catch (const syntax_error& yyexc)
      {
        error (yyexc);
        YYERROR;
      }
    YY_SYMBOL_PRINT ("-> $$ =", yylhs);
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();

    // Shift the result of the reduction.
    yypush_ (YY_NULL, yylhs);
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yysyntax_error_ (yystack_[0].state,
                                           yyempty ? yyempty_ : yyla.type_get ()));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyempty)
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyempty = true;
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }


      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyempty)
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyempty)
          yy_destroy_ (YY_NULL, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULL, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  TC_Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what());
  }

  // Generate an error message.
  std::string
  TC_Parser::yysyntax_error_ (state_type, symbol_number_type) const
  {
    return YY_("syntax error");
  }


  const signed char TC_Parser::yypact_ninf_ = -80;

  const signed char TC_Parser::yytable_ninf_ = -72;

  const short int
  TC_Parser::yypact_[] =
  {
     -80,    14,    22,   -80,    27,    22,   -80,   -80,   -80,   -80,
      21,    26,   -80,   -80,   -80,   -80,    27,    31,   -80,     0,
      27,   -80,    24,   -80,   -80,   -80,    34,    78,   -80,   -80,
      62,   -80,   -80,    27,   101,   118,    41,   120,   -80,   -80,
      41,   -80,    41,   -80,   -80,   -80,   119,   140,    50,   -80,
      80,    86,   106,   110,   132,    17,    19,    29,    42,   -80,
     -80,   135,   -80,   -80,   109,   -80,   -80,    41,    41,    83,
      41,    33,   -80,   -80,   141,   -80,   -80,   161,   -80,   -80,
     -80,    41,    41,    41,    41,    41,    41,    41,    41,    41,
      41,    41,    41,    41,    41,    41,    41,    68,    41,    41,
      41,    60,    71,   -80,   116,   -80,   -80,   -80,   -80,   -80,
      86,   106,   110,   132,    17,    19,    19,    29,    29,    29,
      29,    42,    42,   -80,   -80,   -80,   -80,    76,   -80,   -80,
     -80,     5,     5,    41,   -80,    41,   -80,   165,   -80,   128,
     -80,     5,    41,   -80,   111,     5,   -80
  };

  const unsigned char
  TC_Parser::yydefact_[] =
  {
       2,     0,     0,     1,     0,     3,     4,     6,     7,    78,
       0,     9,    30,    11,     5,     8,     0,     0,    10,     0,
       0,    30,     0,    15,    17,    31,     0,     0,    30,    12,
      30,    16,    31,     0,     0,     0,     0,     0,    77,    18,
       0,    31,     0,    32,    34,    20,    30,    30,     0,    36,
      38,    42,    44,    46,    48,    50,    52,    55,    60,    63,
      66,     0,    68,    73,    72,    13,     9,     0,     0,     0,
       0,     0,    29,    67,    72,    31,    33,    30,    31,    35,
      19,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    24,     0,    74,    26,    31,    28,    37,
      43,    45,    47,    49,    51,    53,    54,    59,    58,    56,
      57,    61,    62,    64,    65,    70,    75,     0,    40,    41,
      39,    30,    30,     0,    27,     0,    69,    21,    23,     0,
      76,    30,     0,    22,     0,    30,    25
  };

  const short int
  TC_Parser::yypgoto_[] =
  {
     -80,   -80,   -80,   -80,   166,   -24,   -80,     7,   -80,   -80,
     -80,   148,   -42,   -13,   164,   -31,   -80,   131,   -36,   -79,
     -80,    96,    97,    95,    98,    99,    -1,    65,    66,   -35,
     -80,   -80,   -80,   -80,   -80,    25
  };

  const signed char
  TC_Parser::yydefgoto_[] =
  {
      -1,     1,     2,     5,     6,     7,    10,    11,     8,    12,
      22,    23,    44,    45,    26,    29,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,   127,    63,    64
  };

  const short int
  TC_Parser::yytable_[] =
  {
      69,    65,   109,    20,    71,    79,    43,    73,    25,    34,
      72,    35,    36,    37,     3,    32,     9,    38,   126,   128,
     129,   130,    76,    18,    21,     4,    39,    24,    40,    13,
      87,   101,   102,    88,   104,    79,    89,    90,     9,    42,
      66,    13,    15,    16,   106,    13,    27,   108,    28,   -14,
      91,    92,     9,    38,    19,    81,   140,   105,    13,    30,
     123,   124,    93,    94,    40,    33,    34,    74,    35,    36,
      37,    80,    81,     9,    38,    42,   134,    95,    96,     9,
      38,    20,    81,    39,   131,    40,   115,   116,    41,   137,
     138,    40,   125,    81,    82,   132,    42,   139,   135,   143,
     136,    83,    42,   146,   103,    81,   144,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    33,    34,    67,    35,    36,    37,    98,    99,
       9,    38,   -71,    81,    84,   145,   100,   133,    81,    85,
      39,    68,    40,    70,    34,    75,    35,    36,    37,   142,
      81,     9,    38,    42,   117,   118,   119,   120,    97,   121,
     122,    39,    86,    40,   -71,    34,    78,    35,    36,    37,
     141,    14,     9,    38,    42,    31,    17,    77,   110,   112,
     111,     0,    39,   113,    40,   114,     0,   107,     0,     0,
       0,     0,     0,     0,     0,    42
  };

  const short int
  TC_Parser::yycheck_[] =
  {
      36,    32,    81,     3,    40,    47,    30,    42,    21,     4,
      41,     6,     7,     8,     0,    28,    11,    12,    97,    98,
      99,   100,    46,    16,    24,     3,    21,    20,    23,     4,
      13,    67,    68,    16,    70,    77,    17,    18,    11,    34,
      33,    16,    21,    22,    75,    20,    22,    78,    24,    23,
      31,    32,    11,    12,    23,    22,   135,    24,    33,    25,
      95,    96,    33,    34,    23,     3,     4,    42,     6,     7,
       8,    21,    22,    11,    12,    34,   107,    35,    36,    11,
      12,     3,    22,    21,    24,    23,    87,    88,    26,   131,
     132,    23,    24,    22,    14,    24,    34,   133,    22,   141,
      24,    15,    34,   145,    21,    22,   142,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,     3,     4,    23,     6,     7,     8,    19,    20,
      11,    12,    23,    22,    28,    24,    27,    21,    22,    29,
      21,    23,    23,    23,     4,    26,     6,     7,     8,    21,
      22,    11,    12,    34,    89,    90,    91,    92,    23,    93,
      94,    21,    30,    23,    23,     4,    26,     6,     7,     8,
       5,     5,    11,    12,    34,    27,    12,    46,    82,    84,
      83,    -1,    21,    85,    23,    86,    -1,    26,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    34
  };

  const unsigned char
  TC_Parser::yystos_[] =
  {
       0,    38,    39,     0,     3,    40,    41,    42,    45,    11,
      43,    44,    46,    72,    41,    21,    22,    51,    44,    23,
       3,    24,    47,    48,    44,    50,    51,    22,    24,    52,
      25,    48,    50,     3,     4,     6,     7,     8,    12,    21,
      23,    26,    34,    42,    49,    50,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    71,    72,    52,    44,    23,    23,    55,
      23,    55,    52,    66,    72,    26,    42,    54,    26,    49,
      21,    22,    14,    15,    28,    29,    30,    13,    16,    17,
      18,    31,    32,    33,    34,    35,    36,    23,    19,    20,
      27,    55,    55,    21,    55,    24,    52,    26,    52,    56,
      58,    59,    60,    61,    62,    63,    63,    64,    64,    64,
      64,    65,    65,    66,    66,    24,    56,    70,    56,    56,
      56,    24,    24,    21,    52,    22,    24,    49,    49,    55,
      56,     5,    21,    49,    55,    24,    49
  };

  const unsigned char
  TC_Parser::yyr1_[] =
  {
       0,    37,    39,    38,    40,    40,    41,    41,    42,    43,
      43,    44,    45,    45,    46,    47,    47,    48,    49,    49,
      49,    49,    49,    49,    49,    49,    50,    50,    50,    50,
      51,    52,    53,    53,    54,    54,    55,    55,    56,    56,
      56,    56,    57,    57,    58,    58,    59,    59,    60,    60,
      61,    61,    62,    62,    62,    63,    63,    63,    63,    63,
      64,    64,    64,    65,    65,    65,    66,    66,    67,    67,
      67,    68,    69,    69,    69,    70,    70,    71,    72
  };

  const unsigned char
  TC_Parser::yyr2_[] =
  {
       0,     2,     0,     2,     1,     2,     1,     1,     3,     1,
       3,     1,     7,     8,     1,     1,     3,     2,     1,     2,
       1,     5,     7,     5,     3,     9,     5,     6,     5,     4,
       0,     0,     1,     2,     1,     2,     1,     3,     1,     3,
       3,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     3,     1,     3,     3,     3,     3,
       1,     3,     3,     1,     3,     3,     1,     2,     1,     4,
       3,     1,     1,     1,     3,     1,     3,     1,     1
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const TC_Parser::yytname_[] =
  {
  "$end", "error", "$undefined", "T_Int", "T_If", "T_Else", "T_While",
  "T_Return", "T_For", "T_Inc", "T_Dec", "Id", "Integer", "T_Equal",
  "T_Or", "T_And", "T_NotEqual", "T_LessEqual", "T_GreaterEqual",
  "T_AddAssign", "T_SubAssign", "';'", "','", "'('", "')'", "'{'", "'}'",
  "'='", "'|'", "'^'", "'&'", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'",
  "$accept", "main", "$@1", "program", "external_declaration",
  "declaration", "declarator_list", "declarator", "function_definition",
  "func_def_declarator", "parameter_type_list", "parameter_declaration",
  "statement", "compound_statement", "subroutien_up", "subroutien_down",
  "declaration_list", "statement_list", "expression", "assign_expr",
  "logical_OR_expr", "logical_AND_expr", "bit_or_expr", "bit_xor_expr",
  "bit_and_expr", "equality_expr", "relational_expr", "add_expr",
  "mult_expr", "unary_expr", "postfix_expr", "func_call_identifier",
  "primary_expr", "argument_expression_list", "constant", "Identifier", YY_NULL
  };


  const unsigned short int
  TC_Parser::yyrline_[] =
  {
       0,   100,   100,   100,   108,   109,   112,   113,   120,   123,
     124,   128,   134,   137,   142,   145,   146,   149,   152,   153,
     154,   155,   156,   157,   158,   159,   162,   163,   164,   165,
     168,   171,   177,   178,   181,   182,   185,   186,   189,   190,
     191,   192,   195,   196,   199,   200,   203,   204,   207,   208,
     211,   212,   215,   216,   217,   220,   221,   222,   223,   224,
     227,   228,   229,   232,   233,   234,   237,   238,   241,   242,
     243,   246,   249,   250,   251,   254,   255,   258,   261
  };

  // Print the state stack on the debug stream.
  void
  TC_Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  TC_Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  // Symbol number corresponding to token number t.
  inline
  TC_Parser::token_number_type
  TC_Parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    30,     2,
      23,    24,    35,    33,    22,    34,     2,    36,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    21,
      31,    27,    32,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    29,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    25,    28,    26,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20
    };
    const unsigned int user_token_number_max_ = 275;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

#line 4 "tc_parser.yy" // lalr1.cc:1156
} // TC
#line 1653 "tc_parser.tab.cc" // lalr1.cc:1156
#line 265 "tc_parser.yy" // lalr1.cc:1157

void TC::TC_Parser::error(const std::string &m) {
  std::cerr << "Parser Error: " << m << std::endl;
}
