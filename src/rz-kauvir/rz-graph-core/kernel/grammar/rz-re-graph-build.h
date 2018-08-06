
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_RE_GRAPH_BUILD__H
#define RZ_RE_GRAPH_BUILD__H

#include "rz-re-parser.h"

#include "flags.h"

#include "accessors.h"

#include "rz-re-parse-context.h"

#include "kernel/graph/rz-re-markup-position.h"


#include "tuple/rz-re-tuple-info.h"

#include "code/rz-re-function-def-kinds.h"

#include <QStack>
#include <QSet>

#include "rzns.h"



RZNS_(RECore)

class RE_Document;
class RE_Parser;
class RE_Graph;
class RE_Tag_Command;
class RE_Annotation_Tile;

class RE_Token;
class RE_Tile;
class RE_Node;
class RE_Sentence;
class RE_Sentence_Part;
class RE_Paralexeme;
class RE_Call_Entry;
class RE_Function_Def_Entry;
class RZ_String_Plex_Builder;

class RE_Graph_Build
{
 flags_(1)
  bool inside_text_map:1;
  bool ghost_in_closes_expression:1;
  bool next_token_closes_expression:1;
  bool inside_array_with_formation:1;
  bool pending_convert_to_type_symbol:1;
//?  bool pending_symbol_modify_to_method:1;
//?  bool arrow_pending_symbol_modify_to_method:1;
 _flags

 RE_Document* document_;
 RE_Parser& parser_;
 RE_Graph& graph_;

 enum class Quoting_Formations {
  N_A, Single,
  Double_Single, Backtick, Double_Backtick
 };

 Quoting_Formations get_quoting_formation(QString s)
 {
  static QMap<QString, Quoting_Formations> static_map
  {{
    { "'", Quoting_Formations::Single },
    { "''", Quoting_Formations::Double_Single },
    { "`", Quoting_Formations::Backtick },
    { "``", Quoting_Formations::Double_Backtick },
  }};

  return static_map.value(s, Quoting_Formations::N_A);
 }


 caon_ptr<RE_Node> root_node_;
 caon_ptr<RE_Node> active_run_node_;
 caon_ptr<RE_Token> active_chief_token_;

 caon_ptr<RZ_String_Plex_Builder> current_string_plex_builder_;

 RE_Parse_Context parse_context_;


 int current_line_;
 int current_run_comment_left_;
 int current_run_comment_right_;

 QStack<caon_ptr<RE_Node>> parent_command_nodes_;

 QString expected_token_end_;

 RE_Frame& fr_;

 RE_Markup_Position markup_position_;

 QSet<QString> automatic_statement_closing_tokens_;

 QString string_literal_acc_;

 QString raw_lisp_acc_;

 int call_entry_count_;
 int block_entry_count_;
 int tuple_entry_count_;

 void set_expected_token_end(QString text);
 void check_line_increment(QString text);


 QString held_suffix_;


public:


 enum class Token_Formations {
  N_A, Normal, Cpp_Scoped, Do_Plus_Block, Strong_Do_Plus_Block
 };

 ACCESSORS(RE_Document* ,document)

 ACCESSORS(caon_ptr<RE_Node> ,root_node)
 ACCESSORS(caon_ptr<RE_Node> ,active_run_node)
 ACCESSORS(caon_ptr<RE_Token>  ,active_chief_token)
 ACCESSORS__GET(RE_Graph& ,graph)

 ACCESSORS__RGET(RE_Parse_Context ,parse_context)


 RE_Graph_Build(RE_Document* d,
  RE_Parser& p, RE_Graph& g);

 void complete_function_declaration();


 void init();

 void string_plex_switch(QString key);
 void string_plex_acc(QString text);

 void enter_tuple(QString name, QString prefix, QString entry, QString suffix);

 void add_equalizer_to_type(QString raw_text);

 caon_ptr<RE_Node> new_run_call_entry_node(bool is_statement_entry,
   QString prefix = QString(), caon_ptr<RE_Call_Entry> parent_entry = nullptr);

 caon_ptr<RE_Node> new_run_block_entry_node();

 caon_ptr<RE_Node> new_autogenerated_token_node(QString raw_text);

 caon_ptr<RE_Node> close_string_plex();

 void add_to_string_literal(QString str)
 {
  string_literal_acc_ += str;
 }

 void string_literal_start();

 void raw_lisp_start();

 void add_to_raw_lisp(QString str);

 void finalize_take_a_space();

 void process_string_literal();
 void process_raw_lisp();

 void add_run_token(RE_Token& token);
 void add_raw_lisp_token(RE_Token& token);


 void add_type_indicator(QString raw_text);


 caon_ptr<RE_Node> create_tuple(RE_Tuple_Info::Tuple_Formations tf,
  RE_Tuple_Info::Tuple_Indicators ti, RE_Tuple_Info::Tuple_Formations sf, bool increment_id = true);

 caon_ptr<RE_Node> make_new_empty_tuple_node(caon_ptr<RE_Tuple_Info> rti);

 void check_hold_tuple_suffix(RE_Tuple_Info::Tuple_Indicators ti, QString& suffix);

 inline caon_ptr<RE_Node> current_node()
 {
  return markup_position_.current_node();
 }

 caon_ptr<RE_Node> make_re_node(caon_ptr<RE_Token> token);

 void check_run_comment_begin(int left, int right);
 void check_run_comment_end(int left, int right);

 void line_increment();

 void add_run_token(QString raw_text);

 void add_run_token(QString prefix, QString raw_text,
  QString suffix, Token_Formations tf, QString space_to_end_of_line = QString());

 void check_run_acc(QString raw_text);
 void finalize_run_acc();

 caon_ptr<RE_Node> new_function_def_entry_node(RE_Node& prior_node,
   RE_Function_Def_Kinds kind, caon_ptr<RE_Node> label_node = nullptr);

 void terminate_read();
 void terminate_parse();

 caon_ptr<RE_Node> make_new_node(caon_ptr<RE_Token>  token);
 caon_ptr<RE_Node> make_new_node(caon_ptr<RE_Call_Entry> rce);
 caon_ptr<RE_Node> make_new_node(caon_ptr<RE_Block_Entry> rbe);
 caon_ptr<RE_Node> make_new_node(caon_ptr<RE_Function_Def_Entry> fdef);
 caon_ptr<RE_Node> make_new_node(caon_ptr<RZ_String_Plex_Builder> rzspb);


 void absorb_whitespace();

 void add_token_plus_block(QString token, QString block_entry);

 void add_semis(QString raw_text, QString space_to_end_of_line);
 void add_run_token(QString raw_text, QString space_to_end_of_line);

 void acc(QString s);

};

_RZNS(RECore)

#endif //RZ_RE_GRAPH_BUILD__H
