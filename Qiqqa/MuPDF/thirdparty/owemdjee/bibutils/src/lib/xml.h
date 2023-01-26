/*
 * xml.h
 *
 * Copyright (c) Chris Putnam 2004-2021
 *
 * Source code released under the GPL version 2
 *
 */
#ifndef XML_H
#define XML_H

#include "slist.h"
#include "str.h"

typedef struct xml {
	str tag;
	str value;
	slist attributes;
	slist attribute_values;
	struct xml *down;
	struct xml *next;
} xml;

void   xml_init                 ( xml *node );
void   xml_free                 ( xml *node );
int    xml_has_value            ( const xml *node );
str *  xml_value                ( xml *node );
const char * xml_value_cstr     ( const xml *node );
str *  xml_tag                  ( xml *node );
const char * xml_tag_cstr       ( const xml *node );
int    xml_tag_matches          ( const xml *node, const char *tag );
int    xml_tag_matches_has_value( const xml *node, const char *tag );
const str * xml_attribute       ( const xml *node, const char *attribute );
const char * xml_attribute_cstr ( const xml *node, const char *attribute );
const char * xml_find_start     ( const char *buffer, const char *tag );
const char * xml_find_end       ( const char *buffer, const char *tag );
int    xml_tag_has_attribute    ( const xml *node, const char *tag, const char *attribute, const char *attribute_value );
int    xml_has_attribute        ( const xml *node, const char *attribute, const char *attribute_value );
const char * xml_parse          ( const char *p, xml *onode );

extern const char * xml_pns; /* global Namespace */

#endif

