// Copyright 2015 Kevin B. Hendricks, Stratford, Ontario,  All Rights Reserved.
// loosely based on a greatly simplified version of BeautifulSoup4 decode() routine
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Author: Kevin Hendricks
//
// Prettyprint back to html / xhtml

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <cstring>

#include "gumbo.h"

static std::string nonbreaking_inline  = "|a|abbr|acronym|b|bdo|big|cite|code|dfn|em|font|i|img|kbd|nobr|s|small|span|strike|strong|sub|sup|tt|";
static std::string empty_tags          = "|area|base|basefont|bgsound|br|command|col|embed|event-source|frame|hr|image|img|input|keygen|link|menuitem|meta|param|source|spacer|track|wbr|";
static std::string preserve_whitespace = "|pre|textarea|script|style|";
static std::string special_handling    = "|html|body|";
static std::string no_entity_sub       = "|script|style|";
static std::string treat_like_inline   = "|p|";

static void replace_all(std::string &s, const char * s1, const char * s2)
{
  std::string t1(s1);
  size_t len = t1.length();
  size_t pos = s.find(t1);
  while (pos != std::string::npos) {
    s.replace(pos, len, s2);
    pos = s.find(t1, pos + len);
  }
}


static std::string substitute_xml_entities_into_text(const std::string &text)
{
  std::string result = text;
  // replacing & must come first 
  replace_all(result, "&", "&amp;");
  replace_all(result, "<", "&lt;");
  replace_all(result, ">", "&gt;");
  return result;
}


static std::string substitute_xml_entities_into_attributes(char quote, const std::string &text)
{
  std::string result = substitute_xml_entities_into_text(text);
  if (quote == '"') {
    replace_all(result,"\"","&quot;");
  }    
  else if (quote == '\'') {
    replace_all(result,"'","&apos;");
  }
 return result;
}


static std::string handle_unknown_tag(GumboStringPiece *text)
{
  std::string tagname = "";
  if (text->data == NULL) {
    return tagname;
  }
  // work with copy GumboStringPiece to prevent asserts 
  // if try to read same unknown tag name more than once
  GumboStringPiece gsp = *text;
  gumbo_tag_from_original_text(&gsp);
  tagname = std::string(gsp.data, gsp.length);
  return tagname; 
}


static std::string get_tag_name(GumboNode *node)
{
  std::string tagname;
  // work around lack of proper name for document node
  if (node->type == GUMBO_NODE_DOCUMENT) {
    tagname = "document";
  } else {
    tagname = gumbo_normalized_tagname(node->v.element.tag);
  }
  if (tagname.empty()) {
    tagname = handle_unknown_tag(&node->v.element.original_tag);
  }
  return tagname;
}


static std::string build_doctype(GumboNode *node)
{
  std::string results = "";
  if (node->v.document.has_doctype) {
    results.append("<!DOCTYPE ");
    results.append(node->v.document.name);
    std::string pi(node->v.document.public_identifier);
    if ((node->v.document.public_identifier != NULL) && !pi.empty() ) {
        results.append(" PUBLIC \"");
        results.append(node->v.document.public_identifier);
        results.append("\" \"");
        results.append(node->v.document.system_identifier);
        results.append("\"");
    }
    results.append(">");
  }
  return results;
}


static std::string build_attributes(GumboAttribute * at, bool no_entities)
{
  std::string atts = "";
  atts.append(" ");
  atts.append(at->name);

  // how do we want to handle attributes with empty values
  // <input type="checkbox" checked />  or <input type="checkbox" checked="" /> 

  if ( (!std::string(at->value).empty())   || 
       (at->original_value.data[0] == '"') || 
       (at->original_value.data[0] == '\'') ) {

    // determine original quote character used if it exists
    char quote = at->original_value.data[0];
    std::string qs = "";
    if (quote == '\'') qs = std::string("'");
    if (quote == '"') qs = std::string("\"");

    atts.append("=");

    atts.append(qs);

    if (no_entities) {
      atts.append(at->value);
    } else {
      atts.append(substitute_xml_entities_into_attributes(quote, std::string(at->value)));
    }

    atts.append(qs);
  }
  return atts;
}


// forward declaration

static std::string print(GumboNode*);


// print children of a node
// may be invoked recursively

static std::string print_contents(GumboNode* node) {

  std::string contents        = "";
  std::string tagname         = get_tag_name(node);
  std::string key             = "|" + tagname + "|";
  bool no_entity_substitution = no_entity_sub.find(key) != std::string::npos;
  bool keep_whitespace        = preserve_whitespace.find(key) != std::string::npos;
  bool is_inline              = nonbreaking_inline.find(key) != std::string::npos;
  bool pp_okay                = !is_inline && !keep_whitespace;

  GumboVector* children = &node->v.element.children;

  for (unsigned int i = 0; i < children->length; ++i) {
    GumboNode* child = static_cast<GumboNode*> (children->data[i]);

    if (child->type == GUMBO_NODE_TEXT) {

      std::string val;

      val = std::string(child->v.text.text);

      contents.append(val);


    } else if ((child->type == GUMBO_NODE_ELEMENT) || (child->type == GUMBO_NODE_TEMPLATE)) {

      std::string val = print(child);

      contents.append(val);

    } else if (child->type == GUMBO_NODE_WHITESPACE) {

      contents.append(std::string(child->v.text.text));

    } else if (child->type != GUMBO_NODE_COMMENT) {

      // Does this actually exist: (child->type == GUMBO_NODE_CDATA)
      fprintf(stderr, "unknown element of type: %d\n", child->type); 

    }

  }

  return contents;
}


// print a GumboNode back to html/xhtml
// may be invoked recursively

static std::string print(GumboNode* node) {

  // special case the document node
  if (node->type == GUMBO_NODE_DOCUMENT) {
    std::string results = build_doctype(node);
    results.append(print_contents(node));
    return results;
  }

  std::string close              = "";
  std::string closeTag           = "";
  std::string atts               = "";
  std::string tagname            = get_tag_name(node);
  std::string key                = "|" + tagname + "|";
  bool need_special_handling     =  special_handling.find(key) != std::string::npos;
  bool is_empty_tag              = empty_tags.find(key) != std::string::npos;
  bool no_entity_substitution    = no_entity_sub.find(key) != std::string::npos;
  bool keep_whitespace           = preserve_whitespace.find(key) != std::string::npos;
  bool is_inline                 = nonbreaking_inline.find(key) != std::string::npos;
  bool inline_like               = treat_like_inline.find(key) != std::string::npos;
  bool pp_okay                   = !is_inline && !keep_whitespace;

  // build attr string
  const GumboVector * attribs = &node->v.element.attributes;
  for (int i=0; i< attribs->length; ++i) {
    GumboAttribute* at = static_cast<GumboAttribute*>(attribs->data[i]);
    atts.append(build_attributes(at, no_entity_substitution));
  }

  // determine closing tag type
  if (is_empty_tag) {
      close = "/";
  } else {
      closeTag = "</" + tagname + ">";
  }

  // print your contents 
  std::string contents = print_contents(node);

  // build results
  std::string results;
  results.append("<"+tagname+atts+close+">");
  results.append(contents);
  results.append(closeTag);

  return results;
}


#if defined(BUILD_MONOLITHIC)
#define main		gumbo_print_main
#endif

int main(int argc, const char** argv) {
  char buffer[4096];
  std::string contents;
  while (!feof(stdin)) {
      fgets(buffer, 4096, stdin);
      contents.append(buffer);
      memset(buffer, 0, sizeof buffer);
  }
 
  GumboOptions options = kGumboDefaultOptions;

  GumboOutput* output = gumbo_parse_with_options(&options, contents.data(), contents.length());
  std::cout << print(output->document);
  gumbo_destroy_output(&kGumboDefaultOptions, output);
  return 0;
}
