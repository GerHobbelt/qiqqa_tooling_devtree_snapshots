#!/bin/python3
# -*- coding: utf-8 -*-

# ##### BEGIN LICENSE BLOCK #####
# Version: MPL 1.1/GPL 2.0/LGPL 2.1
#
# The contents of this file are subject to the Mozilla Public License Version
# 1.1 (the "License"); you may not use this file except in compliance with
# the License. You may obtain a copy of the License at
# http://www.mozilla.org/MPL/
#
# Software distributed under the License is distributed on an "AS IS" basis,
# WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
# for the specific language governing rights and limitations under the
# License.
#
# The Original Code is Mozilla Universal charset detector code.
#
# The Initial Developer of the Original Code is
# Netscape Communications Corporation.
# Portions created by the Initial Developer are Copyright (C) 2001
# the Initial Developer. All Rights Reserved.
#
# Contributor(s):
#          Jehan <jehan@girinstud.io>
#
# Alternatively, the contents of this file may be used under the terms of
# either the GNU General Public License Version 2 or later (the "GPL"), or
# the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
# in which case the provisions of the GPL or the LGPL are applicable instead
# of those above. If you wish to allow use of your version of this file only
# under the terms of either the GPL or the LGPL, and not to allow others to
# use your version of this file under the terms of the MPL, indicate your
# decision by deleting the provisions above and replace them with the notice
# and other provisions required by the GPL or the LGPL. If you do not delete
# the provisions above, a recipient may use your version of this file under
# the terms of any one of the MPL, the GPL or the LGPL.
#
# ##### END LICENSE BLOCK #####

# Third party modules.
import unicodedata
import subprocess
import wikipedia
import importlib
import math
import optparse
import datetime
import operator
import requests
import sys
import re
import os
import random
import string
import hmac
import hashlib
import base64
import yaml
import bisect


# Custom modules.
import charsets.db
from charsets.codepoints import *

# set to `True` when you want to see verbose (debugging) output while running this script:
debug = False

# fix error as per https://bobbyhadz.com/blog/python-unicodeencodeerror-charmap-codec-cant-encode-characters-in-position
sys.stdin.reconfigure(encoding='utf-8')
sys.stdout.reconfigure(encoding='utf-8')
sys.stderr.reconfigure(encoding='utf-8')

# Command line processing.
usage = 'Usage: {} <LANG-CODE>\n' \
        '\nEx: `{} fr`'.format(__file__, __file__)

description = "Internal tool for uchardet to generate language data."
cmdline = optparse.OptionParser(usage, description = description)
cmdline.add_option('--max-page',
                   help = 'Maximum number of Wikipedia pages to parse (useful for debugging).',
                   action = 'store', type = 'int', dest = 'max_page', default = None)
cmdline.add_option('--max-chars',
                   help = 'Maximum number of characters to process. (default: 4000000)',
                   action = 'store', type = 'int', dest = 'max_chars', default = 4000000)
cmdline.add_option('--max-depth',
                   help = 'Maximum depth when following links from start page (default: 4).',
                   action = 'store', type = 'int',
                   dest = 'max_depth', default = 4)
(options, langs) = cmdline.parse_args()
if len(langs) < 1:
  sys.stderr.write("Please select at least one language code. ")
  sys.stderr.write("You may also choose 'all' or 'none'.\n")
  exit(1)

current_dir = os.path.dirname(os.path.realpath(__file__))

with open(os.path.join(current_dir, "support.txt"), mode='r', encoding='utf-8') as f:
    all_langs = f.readlines()
all_langs = [ l.strip() for l in all_langs if l.strip() != '' ]

if len(langs) == 1:
  if langs[0].lower() == 'none':
    langs = []
  elif langs[0].lower() == 'all':
    langs = all_langs

abort = False
for lang in langs:
  if lang not in all_langs:
    abort = True
    sys.stderr.write("Error: unsupported lang: {}\n".format(lang))
if abort:
  sys.stderr.write("Info: new langs must be added in 'script/support.txt'.\n")
  exit(1)

generated_files = []

for lang_arg in langs:
  lang_arg = lang_arg.lower()

  # Load the language data.
  sys_path_backup = sys.path
  sys.path = [current_dir + '/langs']
  try:
      lang = importlib.import_module(lang_arg)
  except ImportError:
      sys.stderr.write('Unknown language code "{}": '
                       'file "langs/{}.py" does not exist.\n'.format(lang_arg, lang_arg))
      exit(1)
  sys.path = sys_path_backup

  print("Processing language data for {} (lang/{}.py):\n".format(lang_arg, lang_arg))

  lang_charsets = charsets.db.load(lang.charsets)

  if not hasattr(lang, 'start_pages') or lang.start_pages is None or \
     lang.start_pages == []:
      # Let's start with the main page, assuming it should have links
      # to relevant pages. In locale wikipedia, this page is usually redirected
      # to a relevant page.
      sys.stderr.write("Warning: no `start_pages` set for '{}'. Using ['Main_Page'].\n"
                       "         If you don't get good data, it is advised to set a "
                       "start_pages` variable yourself.\n".format(lang.code))
      lang.start_pages = ['Main_Page']
  lang.start_pages += ['Phonetics', 'Linguistics', 'Alphabet', 'Language', 'Spelling', 'Pratchett', 'Satire', 'Grammar', 'History', 'Folklore', 'Biology', 'Flower', 'Plant', 'Animal', 'Human', 'computer', 'Robot', 'Technology', 'Communication', 'Writing', 'Video Game', 'Music', 'Glass', 'Bread', 'Food', 'Politics', 'Earth', 'Ocean', 'Amazon', 'Chaplin', 'Aguilera', 'Morse Code', 'Streptococcus', 'Virus', 'Bacteria', 'Bird', 'Submarine', 'Steel', 'Chemistry', 'Military', 'Weather', 'Scholar', 'Supernova', 'Olympiad', 'Rogyapas', 'Agincourt', 'Caesar', 'Ada Lovelace', 'Ip Man', 'Marie Louise of Bourbon-Parma', 'Sumeria', 'Botai', 'Calendar', 'Clytemnestra', 'Baba Yaga', 'transistor', 'diode']

  if not hasattr(lang, 'wikipedia_code') or lang.wikipedia_code is None:
      lang.wikipedia_code = lang.code
  if not hasattr(lang, 'clean_wikipedia_content') or lang.clean_wikipedia_content is None:
      lang.clean_wikipedia_content = None
  if hasattr(lang, 'case_mapping'):
      lang.case_mapping = bool(lang.case_mapping)
  else:
      lang.case_mapping = False
  if not hasattr(lang, 'custom_case_mapping'):
      lang.custom_case_mapping = None
  if not hasattr(lang, 'alphabet') or lang.alphabet is None:
      lang.alphabet = None
  if not hasattr(lang, 'alphabet_mapping') or lang.alphabet_mapping is None:
      lang.alphabet_mapping = None
  if not hasattr(lang, 'unicode_ranges') or lang.unicode_ranges is None:
      lang.unicode_ranges = None
  if not hasattr(lang, 'frequent_ranges') or lang.frequent_ranges is None:
      if lang.unicode_ranges is not None:
        lang.frequent_ranges = lang.unicode_ranges
      else:
        lang.frequent_ranges = None

  def local_lowercase(text, lang):
      lowercased = ''
      for l in text:
          if lang.custom_case_mapping is not None and \
             l in lang.custom_case_mapping:
              lowercased += lang.custom_case_mapping[l]
          elif l.isupper() and \
               lang.case_mapping and \
               len(unicodedata.normalize('NFC', l.lower())) == 1:
              lowercased += l.lower()
          else:
              lowercased += l
      return lowercased

  if lang.use_ascii:
      if lang.alphabet is None:
          lang.alphabet = [chr(l) for l in range(65, 91)] + [chr(l) for l in range(97, 123)]
      else:
          # Allowing to provide an alphabet in string format rather than list.
          lang.alphabet = list(lang.alphabet)
          lang.alphabet += [chr(l) for l in range(65, 91)] + [chr(l) for l in range(97, 123)]
  if lang.alphabet is not None:
      # Allowing to provide an alphabet in string format rather than list.
      lang.alphabet = list(lang.alphabet)
      if lang.case_mapping or lang.custom_case_mapping is not None:
          lang.alphabet = [local_lowercase(l, lang) for l in lang.alphabet]
          #alphabet = []
          #for l in lang.alphabet:
              #if l.isupper() and \
                 #lang.custom_case_mapping is not None and \
                 #l in lang.custom_case_mapping:
                  #alphabet.append(lang.custom_case_mapping[l])
              #elif l.isupper() and \
                   #lang.case_mapping and \
                   #len(unicodedata.normalize('NFC', l.lower())) == 1:
                  #alphabet.append(l.lower())
              #else:
                  #alphabet.append(l)
      lang.alphabet = list(set(lang.alphabet))

  if lang.alphabet_mapping is not None:
      alphabet_mapping = {}
      for char in lang.alphabet_mapping:
        # Allowing to provide an alphabet in string format rather than list.
        for alt_char in list(lang.alphabet_mapping[char]):
          # While it's easier to write from main character to
          # equivalencies in the language file, we reverse the mapping
          # for simpler usage.
          if lang.case_mapping or lang.custom_case_mapping is not None:
            alphabet_mapping[alt_char] = local_lowercase(char, lang)
          else:
            alphabet_mapping[alt_char] = char
      lang.alphabet_mapping = alphabet_mapping

  def normalize_codepoint_ranges(input_range):
    output_range = []
    if input_range is not None:
        for start, end in input_range:
          # Allow to write down characters rather than unicode values.
          if isinstance(start, str):
            start = ord(start)
          if isinstance(end, str):
            end = ord(end)
          if not isinstance(start, int) or not isinstance(end, int):
            sys.stderr.write("Expected unicode range in char or int: {}-{}.\n".format(start, end))
          if start > end:
            sys.stderr.write("Wrong unicode range: {}-{}.\n".format(start, end))
          else:
            output_range += [(start, end)]
    if len(output_range) == 0:
      output_range = None
    return output_range

  lang.unicode_ranges = normalize_codepoint_ranges(lang.unicode_ranges)
  lang.frequent_ranges = normalize_codepoint_ranges(lang.frequent_ranges)

  # Starting processing.
  wikipedia.set_lang(lang.wikipedia_code)

  visited_pages = []
  discarded_pages = []
  discarded_delta_pages = []
  marked_pages = []             # a SORTED array   , used to help speed up deduplication searches
  marked_delta_pages = []       # an UNSORTED array, used to help speed up deduplication searches
  processed_pages_count = 0

  # The full list of letter characters.
  # The key is the unicode codepoint,
  # and the value is the occurrence count.
  characters = {}
  # Sequence of letters.
  # The key is the couple (char1, char2) in unicode codepoint,
  # the value is the occurrence count.
  sequences = {}
  prev_char = None

  def process_text(content, lang):
      global lang_charsets
      global characters
      global sequences
      global prev_char

      content = unicodedata.normalize('NFC', content)

      if lang.clean_wikipedia_content is not None:
          content = lang.clean_wikipedia_content(content)
      # Clean out the Wikipedia syntax for titles.
      content = re.sub(r'(=+) *([^=]+) *\1',
                       r'\2', content)
      # Clean multiple spaces. Newlines and such are normalized to spaces,
      # since they have basically a similar role in the purpose of uchardet.
      content = re.sub(r'\s+', ' ', content)

      if lang.case_mapping or lang.custom_case_mapping is not None:
          content = local_lowercase(content, lang)

      # In python 3, strings are UTF-8.
      # Looping through them return expected characters.
      for char in content:
          # Map to main equivalent character.
          if lang.alphabet_mapping is not None and \
             char in lang.alphabet_mapping:
            char = lang.alphabet_mapping[char]

          unicode_value = ord(char)
          is_letter = False
          if unicode_value in characters:
              characters[unicode_value] += 1
              is_letter = True
          elif lang.use_ascii and \
               (unicode_value >= 32 and unicode_value < 127):
              if ((unicode_value >= 65 and unicode_value <= 90) or \
                  (unicode_value >= 97 and unicode_value <= 122)):
                  characters[unicode_value] = 1
                  is_letter = True
          elif lang.unicode_ranges is not None:
              for start, end in lang.unicode_ranges:
                if unicode_value >= start and unicode_value <= end:
                  characters[unicode_value] = 1
                  is_letter = True
                  break
          else:
              # We save the character if it is at least in one of the
              # language encodings and its not a special character.
              for charset in lang_charsets:
                  # Does the character exist in the charset?
                  try:
                      codepoint = char.encode(charset, 'ignore')
                  except LookupError:
                      # unknown encoding. Check the ASCII base range first to prevent executing a costly iconv call whenever we can:
                      if (unicode_value >= 32 and unicode_value < 127):
                          if ((unicode_value >= 65 and unicode_value <= 90) or \
                              (unicode_value >= 97 and unicode_value <= 122)):
                              characters[unicode_value] = 1
                              is_letter = True
                          break
                      else:
                          # unknown encoding. Use iconv from command line instead.
                          if debug: sys.stderr.write("ICONV::CHAR: {}, {}, [{}], {}\n".format(char, ord(char), charset, lang.name))
                          try:
                              call = subprocess.Popen(['iconv', '-f', 'UTF-8', '-t', charset],
                                                      stdin=subprocess.PIPE, stdout=subprocess.PIPE,
                                                      stderr=subprocess.DEVNULL)
                              if call.poll() is not None:
                                  (_, error) = call.communicate(input='')
                                  sys.stderr.write('Error: `iconv` ended with error "{}".\n'.format(error))
                                  exit(1)
                              (codepoint, _) = call.communicate(input=char.encode('UTF-8'))
                              if debug: sys.stderr.write('iconv :: lang.use_ascii = [{}], [{}], "{}", {}, charset = {} ==> codepoint = [{}]\n'.format(lang.use_ascii, char.encode('UTF-8'), char, ord(char), charset, codepoint))
                          except FileNotFoundError:
                              sys.stderr.write('Error: "{}" is not a supported charset by python and `iconv` is not installed.\n')
                              exit(1)

                  if codepoint == b'':
                      continue
                  # ord() is said to return the unicode codepoint.
                  # But it turns out it also gives the codepoint for other
                  # charsets if I turn the string to encoded bytes first.
                  # Not sure if that is a bug or expected.
                  codepoint = ord(codepoint)
                  if lang_charsets[charset].charmap[codepoint] == LET:
                      characters[unicode_value] = 1
                      is_letter = True
                      break
          if is_letter:
              if prev_char is not None:
                  if (prev_char, unicode_value) in sequences:
                      sequences[(prev_char, unicode_value)] += 1
                  else:
                      sequences[(prev_char, unicode_value)] = 1
              prev_char = unicode_value
          else:
              prev_char = None

  def visit_pages(cache_dir, titles, depth, lang, logfd):
      global visited_pages
      global discarded_pages
      global discarded_delta_pages
      global marked_pages
      global marked_delta_pages
      global processed_pages_count
      global options
      global characters
      global debug

      occurrences = sum(characters.values())
      sys.stderr.write('\nPreloaded {} from cache: {}/{} chars = {:0.1f}% (by processing {} cached pages)\n'.format(lang.name, occurrences, options.max_chars, occurrences * 100.0 / options.max_chars, processed_pages_count))

      # append the titles from cache before we start:
      titles = load_links_from_cache(cache_dir, titles)

      if len(titles) < 30:
          if debug: sys.stderr.write("Adding 30 random Wikipedia pages to the start pages...\n")
          try:
              rndlist = wikipedia.random(pages=30)
              titles += rndlist
          except Exception as error:
              sys.stderr.write("Skipped adding 30 random Wikipedia articles: {}\n".format(error))
              pass

      if debug: sys.stderr.write("Start pages: {}\n".format(titles))

      discarded_pages = load_discards_from_cache(cache_dir, discarded_pages)

      marked_delta_pages += visited_pages
      marked_delta_pages += discarded_pages

      next_titles = []

      while len(titles) > 0:
          # update our sorted marker cache table, which is used by the is_already_marked() API
          # to give use O(log(N)) performance for our inner deduplication scans...
          update_marked_pages_search_index()

          extra_titles = []

          if options.max_page is not None:
              max_titles = int(options.max_page/(options.max_depth * options.max_depth))
          else:
              max_titles = sys.maxsize

          store_links_in_cache(cache_dir, titles)

          # speed optimization: work with batches of about 100 pages/titles:
          remaining_titles = titles[100:]
          # ^^^^^^^^^^^^^^^^^^^^^^^^^ this is potentially *huge* list, which we DO NOT check
          # in the inner deduplication scans in order to speed up the outer loop to O(N log(N))
          # instead of the naive O(N^2) we had before.
          titles = titles[:100]                # one batch of 100 titles

          for title in titles:
              #if title in visited_pages:
              #    continue
              #if title in discarded_pages:
              #    continue
              if is_already_marked(title):
                  continue

              occurrences = sum(characters.values())
              if occurrences / 1.02 > options.max_chars:    # HACKY: heuristically compensate for overlapping wikipages producing a single cache page for content that is counted double/triple/... in this function
                  if debug: sys.stderr.write('Stop criterium: occurrences > options.max_chars: {} > {}\n'.format(occurrences, options.max_chars))
                  return

              if debug: sys.stderr.write('Max occurrences check: {} vs. {} ==> continue consuming pages until we\'ve consumed enough characters. ({}/{} + {} + {} more titles to fetch at depth {})\n'.format(occurrences, options.max_chars, len(titles) - titles.index(title), len(titles), len(extra_titles), (0 if (depth >= options.max_depth) else len(next_titles)), depth))

              if options.max_page is not None and \
                 processed_pages_count > options.max_page:
                  if debug: sys.stderr.write('Stop criterium: processed_pages_count > options.max_page: {} > {}\n'.format(processed_pages_count, options.max_page))
                  return

              # Ugly hack skipping internal pages
              if 'wiki' in title or 'Wiki' in title or 'extlinks' in title:
                  sys.stderr.write('Skipping internal page: {}\n'.format(title))
                  continue

              store_discards_in_cache(cache_dir, discarded_delta_pages)
              discarded_delta_pages = []

              sys.stderr.write('.')
              sys.stderr.flush()

              visited_pages.append(title)
              marked_delta_pages.append(title)
              try:
                  page = wikipedia.page(title, auto_suggest=True, preload=True)
              except (wikipedia.exceptions.PageError,
                      wikipedia.exceptions.DisambiguationError) as error:
                  sys.stderr.write('(E)')
                  sys.stderr.flush()

                  # extract the suggestions from the error message, iff any:
                  sl = []
                  error_msg = "{}".format(error)
                  if 'may refer to:' in error_msg:
                      sl = error_msg.strip().splitlines()
                      # ditch the initial error line:
                      if not debug:
                          error_msg = sl.pop(0) + ' [...]'
                      else:
                          sl.pop(0)

                  # also query wikipedia for (additional) suggestions:
                  try:
                      suggestions = wikipedia.search(title)
                  except Exception as error:
                      discarded_delta_pages.append(title)
                      marked_delta_pages.append(title)
                      sys.stderr.write("\n(P1) Discarding page {} and failed to obtain suggestions: {}\n".format(title, error))
                      continue

                  sys.stderr.write('(S)')
                  sys.stderr.flush()

                  suggestions = [] + suggestions + sl
                  if not suggestions:
                      # Let's just discard a page when I get an exception.
                      discarded_delta_pages.append(title)
                      marked_delta_pages.append(title)
                      sys.stderr.write("\n(P2) Discarding page {}; no new suggestions: {}\n".format(title, error_msg))
                  else:
                      # filter the suggestions list so we don't inject duplicates
                      sl = []
                      for suggestion in suggestions:
                          if len(suggestion) == 0:
                              continue
                          if len(suggestion) <= 4:      # SPECIAL OPTIMIZATION: ignore (links to) pages with (very) short titles.
                              continue
                          if is_already_marked(suggestion):
                              continue
                          if suggestion in sl or \
                             suggestion in extra_titles:
                              continue
                          #if suggestion in visited_pages or \
                          #   suggestion in discarded_pages:
                          #    continue
                          if suggestion in titles:
                              continue
                          sl.append(suggestion)
                      suggestions = sl
                      if not suggestions:
                          # Let's just discard a page when I get an exception.
                          discarded_delta_pages.append(title)
                          marked_delta_pages.append(title)
                          sys.stderr.write("\n(P3) Discarding page {}: {}\n".format(title, error_msg))
                      else:
                          #random.shuffle(suggestions)
                          if len(suggestions) > max_titles:
                              suggestions = suggestions[:max_titles]
                          discarded_delta_pages.append(title)
                          marked_delta_pages.append(title)
                          sys.stderr.write("\n(P4) Discarding page {}: {}\n     ==> adding these suggestions instead: {}\n".format(title, error_msg, suggestions))
                          extra_titles += suggestions
                          store_links_in_cache(cache_dir, suggestions)
                  continue
              except Exception as error:
                  discarded_delta_pages.append(title)
                  marked_delta_pages.append(title)
                  sys.stderr.write("\n(P5) Discarding page {}: {}\n".format(title, error))
                  continue

              sys.stderr.write(':')
              sys.stderr.flush()

              logfd.write("\n{} (revision {})".format(title, page.revision_id))
              logfd.flush()

              if debug: sys.stderr.write("\n{} (revision {}) -> {}\n".format(title, page.revision_id, page.url))

              content = page.content.strip()

              # Nuke LaTeX math lines as best we can.
              #
              # those come out as, for example:
              #   {\displaystyle {\tfrac {p+q}{2}}=50{\tfrac {1}{2}}}
              content = re.sub(r'\{\s*\\displaystyle[^\n]*\}', ' ', content)

              # only count (and cache) non-empty pages against the configured page count maximum:
              if (len(content) != 0):
                  process_text(content, lang)
                  processed_pages_count += 1
                  store_content_in_cache(cache_dir, page.url, content, title, page.revision_id)

              if debug: sys.stderr.write('processing links [{}]\n'.format(page.links))
              try:
                  links = page.links
                  # filter the links[] list so we don't inject duplicates
                  ll = []
                  for link in links:
                      if len(link) == 0:
                          continue
                      if len(link) <= 4:      # SPECIAL OPTIMIZATION: ignore (links to) pages with (very) short titles.
                          continue
                      #if link in visited_pages or \
                      #   link in discarded_pages:
                      #    continue
                      if is_already_marked(link):
                          continue
                      if link in ll or \
                         link in extra_titles:
                          continue
                      if link in titles:
                          continue
                      ll.append(link)
                  links = ll
                  #random.shuffle(links)
                  if len(links) > max_titles:
                      links = links[:max_titles]
                  next_titles += links
                  store_links_in_cache(cache_dir, links)
              except KeyError as error:
                  if debug: sys.stderr.write('links append error: {}\n'.format(error))
                  pass

          # all titles in the batch have been consumed. Now check if here's any remaining and/or extras, and if not not, then descend into the next depth level of links:

          #remaining_titles.sort()
          #remaining_titles = sort_and_append_nonduplicate_titles(remaining_titles, extra_titles)
          #
          # ^^^^^^^^^^^^^^^ instead of these costly lines do this:
          # VVVVVVVVVVvvvvv is faster, yet suffers from carrying duplicates after a while.
          #                 Alas.
          #                 Those will be filtered out quickly using O(log(N)) binary search in the end via `is_already_marked()`
          remaining_titles += extra_titles

          # ??? don't shuffle here: it's costly on a large array. And it's not strictly necessary anyway.
          random.shuffle(remaining_titles)

          titles = remaining_titles
          if len(titles) > 0:
              continue

          if depth >= options.max_depth:
              if debug: sys.stderr.write('Stop criterium: depth >= options.max_depth: {} > {}\n'.format(depth, options.max_depth))
              return

          random.shuffle(next_titles)
          depth += 1
          titles = next_titles

          if len(titles) < 30:
              if debug: sys.stderr.write("Adding 30 random Wikipedia pages to the start pages at depth {}...\n".format(depth))
              try:
                  rndlist = wikipedia.random(pages=30)
                  titles += rndlist
              except Exception as error:
                  sys.stderr.write("Skipped adding 30 random Wikipedia articles: {}\n".format(error))
                  pass

          next_titles = []

      store_discards_in_cache(cache_dir, discarded_delta_pages)

  def sort_and_append_nonduplicate_titles(alist, titles):
      global debug

      titles.sort()

      # We assume alist[] is already sorted!
      #
      # Also note that this code uses the for/else a.k.a. while/else construct explicitly.
      # Finally something I *like* about Python! :-) [GHo]
      #
      # https://stackoverflow.com/questions/9979970/why-does-python-use-else-after-for-and-while-loops
      rv = alist[:]
      i = 0
      j = 0
      while i < len(alist):
          if j >= len(titles):
              break   # done
          title = titles[j]
          t0 = alist[i]
          while t0 < title:
              i += 1
              if i >= len(alist):
                  break
              t0 = alist[i]

          # when we get here, we're guaranteed to have t0 >= title or reached end of marked_pages[] hence *fictive* t0 > title
          while t0 == title:
              # skip/discard incoming duplicate(s) in titles[]:
              j += 1
              if j >= len(titles):
                  break   # done
              title = titles[j]
          else:
              # when we get here, we're guaranteed to NOT have run out of titles[] to add, i.e. we still have a title pending:
              rv.append(title)
              j += 1
      else:
          # when we get here, we're guaranteed to NOT have run out of titles[] to add, i.e. we still have title(s) pending:
          while j < len(titles):
              title = titles[j]
              rv.append(title)
              j += 1

      rv.sort()
      return rv

  def update_marked_pages_search_index():
      global marked_pages
      global marked_delta_pages
      global debug

      marked_pages = sort_and_append_nonduplicate_titles(marked_pages, marked_delta_pages)
      marked_delta_pages = []

  def is_already_marked(item):
      global marked_pages
      global marked_delta_pages

      # Locate the leftmost value exactly equal to item
      i = bisect.bisect_left(marked_pages, item)
      if i != len(marked_pages) and marked_pages[i] == item:
          return True

      return item in marked_delta_pages

  def store_content_in_cache(cache_dir, url, content, title, revision_id):
      global debug

      # create **probably globally unique** hash for the given url:
      dig = hmac.new(b'1234567890', msg=url.encode('utf8'), digestmod=hashlib.sha256).digest()
      hashstr = base64.b64encode(dig).decode()      # py3k-mode
      unique_fname = hashstr.replace('=', '')
      unique_fname = re.sub(r'[^a-zA-Z0-9_-]+', '', unique_fname)
      unique_fname = unique_fname[-50:] + '.content.txt'

      fpath = os.path.join(cache_dir, unique_fname)
      if (len(content) > 0):
          if debug: sys.stderr.write('Cache content (size: {}) for URL {} -> filename: {}\n'.format(len(content), url, fpath))
          with open(fpath, mode='w', encoding='utf-8') as c_fd:
              header = dict(
                  title = title,
                  url = url,
                  revision = revision_id
              )
              c_fd.write(yaml.dump(header))
              c_fd.write('\n\n---\n\n')

              c_fd.write(content)

              sys.stderr.write('_')
              sys.stderr.flush()

  def store_links_in_cache(cache_dir, links):
      global debug

      if (len(links) > 0):
          cached_set = []              # load_links_from_cache(cache_dir, [])
          links = links[:]
          links.sort()

          prev_title = ''
          for title in links:
              title = title.strip()
              if len(title) == 0:
                  continue
              if len(title) <= 4:      # SPECIAL OPTIMIZATION: ignore (links to) pages with (very) short titles.
                  continue
              if title == prev_title:
                  continue
              cached_set.append(title)
              prev_title = title

          fpath = os.path.join(cache_dir, 'links.txt')
          with open(fpath, mode='a', encoding='utf-8') as c_fd:
              c_fd.write("\n")
              c_fd.write("\n".join(cached_set))
              c_fd.write("\n")

  def dedup_links_in_cache(cache_dir, links):
      global debug

      #links = load_links_from_cache(cache_dir, [])
      # ^^^^ this loads the links cache **deduplicated**!
      #
      # all we have to do now is rewrite the cache file:

      fpath = os.path.join(cache_dir, 'links.txt')
      with open(fpath, mode='w', encoding='utf-8') as c_fd:
          c_fd.write("\n")
          c_fd.write("\n".join(links))
          c_fd.write("\n")

  def load_links_from_cache(cache_dir, titles):
      global debug

      fpath = os.path.join(cache_dir, 'links.txt')
      if os.path.isfile(fpath):
          with open(fpath, mode='r', encoding='utf-8') as c_fd:
              content = c_fd.read()

          lines = content.strip().splitlines()
          lines.sort()

          prev_title = ''
          for title in lines:
              if len(title) == 0:
                  continue
              if len(title) <= 4:      # SPECIAL OPTIMIZATION: ignore (links to) pages with (very) short titles.
                  continue
              if title == prev_title:
                  continue
              titles.append(title)
              prev_title = title

      # rewrite the cache DEDUPLICATED:
      dedup_links_in_cache(cache_dir, titles)

      return titles

  def store_discards_in_cache(cache_dir, discarded_pages):
      global debug

      if (len(discarded_pages) > 0):
          cached_set = []      # load_discards_from_cache(cache_dir, [])
          discarded_pages = discarded_pages[:]
          discarded_pages.sort()

          prev_title = ''
          for title in discarded_pages:
              title = title.strip()
              if len(title) == 0:
                  continue
              if title == prev_title:
                  continue
              cached_set.append(title)
              prev_title = title

          fpath = os.path.join(cache_dir, 'discards.txt')
          with open(fpath, mode='a', encoding='utf-8') as c_fd:
              c_fd.write("\n")
              c_fd.write("\n".join(cached_set))
              c_fd.write("\n")

  def dedup_discards_in_cache(cache_dir, discarded_pages):
      global debug

      #discarded_pages = load_discards_from_cache(cache_dir, [])
      # ^^^^ this loads the discards cache **deduplicated**!
      #
      # all we have to do now is rewrite the cache file:

      fpath = os.path.join(cache_dir, 'discards.txt')
      with open(fpath, mode='w', encoding='utf-8') as c_fd:
          c_fd.write("\n")
          c_fd.write("\n".join(discarded_pages))
          c_fd.write("\n")

  def load_discards_from_cache(cache_dir, titles):
      global debug

      fpath = os.path.join(cache_dir, 'discards.txt')
      if os.path.isfile(fpath):
          with open(fpath, mode='r', encoding='utf-8') as c_fd:
              content = c_fd.read()

          lines = content.strip().splitlines()
          lines.sort()

          prev_title = ''
          for title in lines:
              if len(title) == 0:
                  continue
              if title == prev_title:
                  continue
              titles.append(title)
              prev_title = title

      # rewrite the cache DEDUPLICATED:
      dedup_discards_in_cache(cache_dir, titles)

      return titles

  def visit_pages_cache(cache_dir, lang, logfd):
      global visited_pages
      global discarded_pages
      global marked_pages
      global marked_delta_pages
      global processed_pages_count
      global options
      global characters
      global debug

      if debug: sys.stderr.write('Cache file dir for lang {}: {}\n'.format(lang.name, cache_dir))
      try:
          cachefiles = [f for f in os.listdir(cache_dir) if os.path.isfile(os.path.join(cache_dir, f)) and ('.content.txt' in f)]
          # sys.stderr.write('Cache file list: {}\n'.format(cachefiles))

          for title in cachefiles:
              occurrences = sum(characters.values())
              #if occurrences > options.max_chars:
              #    if debug: sys.stderr.write('Stop criterium: occurrences > options.max_chars: {} > {}\n'.format(occurrences, options.max_chars))
              #    return

              if debug: sys.stderr.write('Max occurrences check: {} vs. {} ==> continue comsuming cached pages until we\'ve consumed enough characters. ({}/{})\n'.format(occurrences, options.max_chars, len(cachefiles) - cachefiles.index(title), len(cachefiles)))

              #if options.max_page is not None and \
              #   processed_pages_count > options.max_page:
              #    if debug: sys.stderr.write('Stop criterium: processed_pages_count > options.max_page: {} > {}\n'.format(processed_pages_count, options.max_page))
              #    return

              sys.stderr.write('+')
              sys.stderr.flush()

              fpath = os.path.join(cache_dir, title)
              with open(fpath, mode='r', encoding='utf-8') as cache_fd:
                  content = cache_fd.read()

              # decode cache file header:
              ch = content.split('\n---\n\n', maxsplit=1)
              cheader = ch[0]
              content = ch[1].strip()
              dct = yaml.safe_load(cheader)

              page_title = dct['title']
              page_url = dct['url']
              page_revision = dct['revision']

              # mark page as visited:
              #if page_title in visited_pages:
              #    continue
              visited_pages.append(page_title)
              marked_delta_pages.append(page_title)

              logfd.write("\n{} (revision {}; CACHED)".format(page_title, page_revision))
              logfd.flush()

              if debug: sys.stderr.write("\n{} (revision {}) -> {}; cached file: {}; content size: {}\n".format(page_title, page_revision, page_url, title, len(content)))

              # only count (and cache) non-empty pages against the configured page count maximum:
              if (len(content) != 0):
                  process_text(content, lang)
                  processed_pages_count += 1

      except FileNotFoundError as error:
          sys.stderr.write('\nWARNING: No cached content files at {}?\n    {}\n'.format(cache_dir, error))
          pass

  language_c = lang.name.replace('-', '_').title()
  build_log = current_dir + '/BuildLangModelLogs/Lang{}Model.log'.format(language_c)
  logfd = open(build_log, mode='w', encoding='utf-8')
  logfd.write('= Logs of language model for {} ({}) =\n'.format(lang.name, lang.code))
  logfd.write('\n- Generated by {}'.format(os.path.basename(__file__)))
  logfd.write('\n- Started: {}'.format(str(datetime.datetime.now())))
  logfd.write('\n- Maximum depth: {}'.format(options.max_depth))
  if options.max_page is not None:
      logfd.write('\n- Max number of pages: {}'.format(options.max_page))
  if options.max_chars is not None:
      logfd.write('\n- Max number of characters: {}'.format(options.max_chars))
  logfd.write('\n\n== Parsed pages ==\n')
  logfd.flush()
  sys.stderr.write('\n>')
  sys.stderr.flush()
  try:
      cache_dir = current_dir + '/langs-content-cache/'+ lang_arg
      os.makedirs(cache_dir, exist_ok=True)

      visit_pages_cache(cache_dir, lang, logfd)
      visit_pages(cache_dir, lang.start_pages, 0, lang, logfd)
  except requests.exceptions.ConnectionError:
      sys.stderr.write('Error: connection to Wikipedia failed. Aborting\n')
      exit(1)
  logfd.write('\n\n== End of Parsed pages ==')
  logfd.write('\n\n- Number of pages processed: {}'.format(len(visited_pages)))
  logfd.write('\n- Number of characters consumed: {}'.format(sum(characters.values())))
  logfd.write('\n\n- Wikipedia parsing ended at: {}\n'.format(str(datetime.datetime.now())))
  logfd.flush()

  sys.stderr.write('\nFinished consuming {} web pages; processing the statistics now...\n'.format(len(visited_pages)))

  ########### CHARACTERS ###########

  # Character ratios.
  ratios = {}
  n_char = len(characters)
  occurrences = sum(characters.values())

  logfd.write("\n{} characters appeared {} times.\n\n".format(n_char, occurrences))
  for char in characters:
      ratios[char] = characters[char] / occurrences

  sorted_ratios = sorted(ratios.items(), key=operator.itemgetter(1),
                         reverse=True)

  for order, (char, ratio) in enumerate(sorted_ratios):
      logfd.write("[{:2}] Character '{}' usage: {} ({:.9f} %)\n".format(order, chr(char),
                                                             characters[char],
                                                             ratios[char] * 100))

  # Accumulated ratios of the frequent chars.
  accumulated_ratios = 0

  # If there is no alphabet defined, we just use the first `freq_count_limit` letters, which was
  # the original default.
  # If there is an alphabet, we make sure all the alphabet characters are in the
  # frequent list, and we stop then. There may therefore be more or less than
  # 64 frequent characters depending on the language.
  logfd.write('\nMost Frequent characters:')
  # sys.stderr.write('\nAlphabet: {}, frequent_ranges: {}, lang: {}\n'.format(lang.alphabet, lang.frequent_ranges, lang.name))
  very_freq_count = 0
  very_freq_ratio = 0
  freq_count_limit = 128
  if lang.alphabet is None and lang.frequent_ranges is None:
      freq_count = min(255, min(freq_count_limit, len(sorted_ratios)))
      for order, (char, ratio) in enumerate(sorted_ratios):
          if order >= freq_count:
              break
          logfd.write("\n[{:2}] Char {}: {:.9f} %".format(order, chr(char), ratio * 100))
          accumulated_ratios += ratio
          if very_freq_ratio < 0.4:
            very_freq_count += 1
            very_freq_ratio += ratio
  elif lang.alphabet is not None:
      freq_count = 0
      for order, (char, ratio) in enumerate(sorted_ratios):
          if freq_count >= 255:
              break
          if len(lang.alphabet) == 0:
              break
          if chr(char) in lang.alphabet:
              lang.alphabet.remove(chr(char))
          logfd.write("\n[{:2}] Char {}: {:.9f} %".format(order, chr(char), ratio * 100))
          accumulated_ratios += ratio
          freq_count += 1
          if very_freq_ratio < 0.4:
            very_freq_count += 1
            very_freq_ratio += ratio
      if len(lang.alphabet) > 0:
          sys.stderr.write("Error: alphabet characters are absent from data collection"
                           "\n       Please check the configuration or the data."
                           "\n       Missing characters: [{}]"
                           "\n       Tip: you may want to increase your corpus size (max-chars)."
                           "\n".format(", ".join(lang.alphabet)))
          exit(1)
  elif lang.frequent_ranges is not None:
      # How many characters in the frequent range?
      frequent_ranges_size = 0
      for start, end in lang.frequent_ranges:
        frequent_ranges_size += end - start + 1

      # Keep ratio for at least all the characters inside the frequent
      # ranges.
      freq_count = 0
      for order, (char, ratio) in enumerate(sorted_ratios):
        if order >= freq_count_limit and ratio < 0.0005:
          break
        if freq_count >= 255:
          break
        for start, end in lang.frequent_ranges:
          if char >= start and char <= end:
            freq_count += 1
            accumulated_ratios += ratio
            logfd.write("\n[{:2}] Char {}: {:.9f} %".format(order, chr(char), ratio * 100))
            frequent_ranges_size -= 1
            break
        else:
          # A frequent character in the non-frequent range.
          logfd.write("\n[{:2}] Char {}: {:.9f} %".format(order, chr(char), ratio * 100))
          freq_count += 1
          accumulated_ratios += ratio

        if very_freq_ratio < 0.4:
          very_freq_count += 1
          very_freq_ratio += ratio

        if frequent_ranges_size <= 0:
          break

  low_freq_order = freq_count - 1
  low_freq_ratio = 0
  for back_order, (char, ratio) in enumerate(reversed(sorted_ratios[:freq_count])):
    if low_freq_ratio < 0.03:
      low_freq_ratio += ratio
      low_freq_order -= 1
    else:
      break

  # Keep the freq_count more frequent characters.
  sorted_chars = [(char, freq, order) for order, (char, freq) in
                  enumerate(sorted_ratios)][:freq_count]
  max_order = len(sorted_chars)

  # Add equivalency characters.
  equivalent = []
  if lang.case_mapping:
      for char, ratio, order in sorted_chars:
          uppercased = chr(char).upper()
          try:
            if char != ord(uppercased):
                equivalent += [(ord(uppercased), ratio, order)]
          except TypeError:
            # This happens for some case such as 'SS' as uppercase of 'ß'.
            # Just ignore such cases.
            sys.stderr.write("Ignoring '{}' as uppercase equivalent of '{}'.\n".format(uppercased, char))

  if lang.alphabet_mapping is not None:
    for alt_c in lang.alphabet_mapping:
      for char, ratio, order in sorted_chars:
        if alt_c == chr(char):
          sys.stderr.write("ALREADY {}\n".format(alt_c))
          exit(1)
        elif char == ord(lang.alphabet_mapping[alt_c]):
          equivalent += [(ord(alt_c), ratio, order)]
          break
      else:
        sys.stderr.write("Base equivalent for {} not found in frequent characters!\n".format(alt_c))
        exit(1)

  sorted_chars += equivalent

  # Order by code point.
  sorted_chars = sorted(sorted_chars, key=operator.itemgetter(0))
  max_order = len(sorted_chars)

  lo_c = sorted_chars[0][0]
  hi_c = sorted_chars[max_order -  1][0]

  logfd.write("\n\nThe first {} characters have an accumulated ratio of {}.\n".format(freq_count, accumulated_ratios))
  logfd.write("The first {} characters have an accumulated ratio of {}.\n".format(very_freq_count, very_freq_ratio))
  logfd.write("All characters whose order is over {} have an accumulated ratio of {}.\n".format(low_freq_order, low_freq_ratio))
  
  sys.stderr.write('\nGenerating language model CHARACTER MAP file...\n')

  with open(current_dir + '/header-template.cpp', mode='r', encoding='utf-8') as header_fd:
      c_code = header_fd.read()

  c_code += '\n#include "../nsSBCharSetProber.h"'
  c_code += '\n#include "../nsSBCharSetProber-generated.h"'
  c_code += '\n#include "../nsLanguageDetector.h"\n'
  c_code += '\n#include "../nsLanguageDetector-generated.h"\n'
  c_code += '\n/********* Language model for: {} *********/\n\n'.format(lang.name)
  c_code += '/**\n * Generated by {}\n'.format(os.path.basename(__file__))
  c_code += ' * On: {}\n'.format(str(datetime.datetime.now()))
  c_code += ' **/\n'

  c_code += \
"""
/* Character Mapping Table:
 * ILL: illegal character.
 * CTR: control character specific to the charset.
 * RET: carriage/return.
 * SYM: symbol (punctuation) that does not belong to word.
 * NUM: 0 - 9.
 * IRR: irrelevant character (which does belong to a word)
 *
 * Other characters are ordered by probabilities
 * (0 is the most common character in the language).
 *
 * Orders are generic to a language. So the codepoint with order X in
 * CHARSET1 maps to the same character as the codepoint with the same
 * order X in CHARSET2 for the same language.
 * As such, it is possible to get missing order. For instance the
 * ligature of 'o' and 'e' exists in ISO-8859-15 but not in ISO-8859-1
 * even though they are both used for French. Same for the euro sign.
 */
"""

  c_code += '\n\n\n#define IRR                     (-1)\n\n'
  c_code += '#define {}OrderWidth        {}\n\n\n'.format(language_c, freq_count)

  for charset in lang_charsets:
      charset_c = charset.replace('-', '_').title()
      CTOM_str = 'static const unsigned char {}_CharToOrderMap[]'.format(charset_c)
      CTOM_str += ' =\n{'
      for line in range(0, 16):
          CTOM_str += '\n  '
          for column in range(0, 16):
              cp = line * 16 + column
              cp_type = lang_charsets[charset].charmap[cp]
              if cp_type == ILL:
                  CTOM_str += 'ILL,'
              elif cp_type == RET:
                  CTOM_str += 'RET,'
              elif cp_type == CTR:
                  CTOM_str += 'CTR,'
              elif cp_type == SYM:
                  CTOM_str += 'SYM,'
              elif cp_type == NUM:
                  CTOM_str += 'NUM,'
              else: # LET
                  try:
                      uchar = bytes([cp]).decode(charset)
                  except UnicodeDecodeError:
                      sys.stderr.write('Unknown character 0X{:X} in {}.'.format(cp, charset))
                      sys.stderr.write('Please verify your charset specification.\n')
                      exit(1)
                  except LookupError:
                      # Unknown encoding. Use iconv instead.
                      try:
                          call = subprocess.Popen(['iconv', '-t', 'UTF-8', '-f', charset],
                                                  stdin=subprocess.PIPE,
                                                  stdout=subprocess.PIPE,
                                                  stderr=subprocess.PIPE)
                          if call.poll() is not None:
                              (_, error) = call.communicate(input='')
                              sys.stderr.write('Error: `iconv` ended with error "{}".\n'.format(error))
                              exit(1)
                          (uchar, _) = call.communicate(input=bytes([cp]))
                          uchar = uchar.decode('UTF-8')
                      except FileNotFoundError:
                          sys.stderr.write('Error: "{}" is not a supported charset by python and `iconv` is not installed.\n')
                          exit(1)
                      if len(uchar) == 0:
                          sys.stderr.write('TypeError: iconv failed to return a unicode character for codepoint "{}" in charset {}.\n'.format(hex(cp), charset))
                          exit(1)
                  #if lang.case_mapping and uchar.isupper() and \
                     #len(unicodedata.normalize('NFC', uchar.lower())) == 1:
                     # Unless we encounter special cases of characters with no
                     # composed lowercase, we lowercase it.
                  if lang.case_mapping or lang.custom_case_mapping is not None:
                      uchar = local_lowercase(uchar, lang)
                  if lang.alphabet_mapping is not None and uchar in lang.alphabet_mapping:
                      uchar = lang.alphabet_mapping[uchar]
                  for char, ratio, order in sorted_chars:
                      if char == ord(uchar):
                          CTOM_str += '{:3},'.format(min(249, order))
                          break
                  else:
                      # XXX: we must make sure the character order does not go
                      # over the special characters (250 currently). This may
                      # actually happen when building a model for a language
                      # writable with many different encodings. So let's just
                      # ceil the order value at 249 max.
                      # It may be an interesting alternative to add another
                      # constant for any character with an order > freqCharCount.
                      # Maybe IRR (irrelevant character) or simply CHR.
                      CTOM_str += '{:3},'.format(249)    # min(249, freq_count)
          CTOM_str += ' /* {:X}X */'.format(line)
      CTOM_str += '\n};\n/* '
      CTOM_str += 'X0  X1  X2  X3  X4  X5  X6  X7  X8  X9  XA  XB  XC  XD  XE  XF'
      CTOM_str += ' */\n\n'
      c_code += CTOM_str

  ## UNICODE frequency.

  # Since we can't map the full character table from encoding to order,
  # just create a list from the most common characters from the language.
  # The list is ordered by unicode code points (hence can be used
  # generically for various encoding schemes as it is not encoding
  # specific) allowing to search from code points efficiently by a divide
  # and conquer search algorithm.
  # Each code point is immediately followed by its order.

  CTOM_str = '#define Unicode_Char_size    {}\n\n'.format(max_order)
  
  CTOM_str += 'static const PRUint32 Unicode_CharOrder[]'
  CTOM_str += ' =\n{'
  column = 0

  if len(sorted_chars) == 0:
    sys.stderr.write('##########################################################\n')
    sys.stderr.write('ERROR: collected character set (model) is empty for language: {}!\n'.format(lang.name))
    sys.stderr.write('##########################################################\n')
    model_is_empty = 1
    max_char_width = 2
    max_order_width = 2
  else:
    model_is_empty = 0
    max_char_width = math.floor(math.log10(sorted_chars[max_order - 1][0])) + 1
    max_order_width = math.floor(math.log10(max_order)) + 1

  sorted_order = []
  for char, ratio, order in sorted_chars:
      if column % 8 == 0:
          CTOM_str += '\n  '
      else:
          CTOM_str += ' '
      column += 1
      CTOM_str += '{:>{width}}, '.format(char, width=max_char_width)
      CTOM_str += '{:>{width}},'.format(order, width=max_order_width)

      sorted_order.append((order, ratio))

  CTOM_str += '\n};\n\n'
  c_code += CTOM_str

  if not model_is_empty:
      sorted_order = sorted(sorted_order, key=operator.itemgetter(0))

      CTOM_str = 'static const float OrderToRatio[]'
      CTOM_str += ' =\n{'
      column = 0
      prev_order = -1

      for order, ratio in sorted_order:
          if order == prev_order:
              continue
          prev_order = order

          if column % 8 == 0:
              CTOM_str += '\n  '
          else:
              CTOM_str += ' '
          column += 1
          CTOM_str += '{:0.9f}f, '.format(ratio)

      CTOM_str += '\n  0    /* value slot for out-of-bounds index values; range: 0..freq_count({}) */'.format(freq_count)
      CTOM_str += '\n};\n\n'
      c_code += CTOM_str

  invalid_order_nr = 1000000
  char_order_lookup = [invalid_order_nr] * (hi_c + 1)
  for char, ratio, order in sorted_chars:
      char_order_lookup[char] = order

  ########### SEQUENCES ###########

  sys.stderr.write('\nGenerating language model CHARACTER SEQUENCES file...\n')

  ratios = {}
  occurrences = sum(sequences.values())

  accumulated_seq_count = 0
  order_3 = -1
  order_2 = -1
  ratio_3 = -1
  ratio_2 = -1
  count_512 = -1
  count_1024 = -1
  sorted_seqs = sorted(sequences.items(), key=operator.itemgetter(1),
                       reverse=True)
  for order, ((c1, c2), count) in enumerate(sorted_seqs):
    accumulated_seq_count += count
    if order_3 == -1 and accumulated_seq_count / occurrences >= 0.995:
      order_3 = order
      ratio_3 = accumulated_seq_count / occurrences
    elif order_2 == -1 and accumulated_seq_count / occurrences >= 0.999:
      order_2 = order
      ratio_2 = accumulated_seq_count / occurrences
    if order < 512:
      count_512 += count
    elif order < 1024:
      count_1024 += count

    if order_3 != -1 and order_2 != -1:
      break

  if order_3 == -1 or order_2 == -1:
    # This would probably never happen. It would require a language with
    # very few possible sequences and each of the sequences are widely
    # used. Just add this code for completion, but it won't likely ever be
    # run.
    order_2 = 512
    order_3 = 1024
    if not model_is_empty:
      ratio_2 = count_512 / occurrences
      ratio_3 = count_1024 / occurrences
    else:
      ratio_2 = 0
      ratio_3 = 0

  logfd.write("\n{} sequences found.\n".format(len(sorted_seqs)))

  c_code += """
/* Model Table:
 * Number of web pages processed for this model: {}
 * Number of characters consumed for this model: {}
 * Total considered sequences: {} / {}
 *
 * - Positive sequences: first {} ({})
 * - Probable sequences: next {} ({}-{}) ({})
 * - Neutral sequences: last {} ({})
 * - Negative sequences: {} (off-ratio, TODO)
 */
""".format(len(visited_pages),
            sum(characters.values()),
            len(sorted_seqs),
            freq_count * freq_count,
            order_3, ratio_3,
            order_2 - order_3,
            order_2, order_3,
            ratio_2 - ratio_3,
            freq_count * freq_count - order_2,
            1 - ratio_2,
            freq_count * freq_count - len(sorted_seqs))

  logfd.write("\nFirst {} (typical positive ratio): {}".format(order_3, ratio_3))
  logfd.write("\nNext {} ({}-{}): {}".format(order_2 - order_3,
                                             order_2, order_3,
                                             ratio_2 - ratio_3))
  logfd.write("\nRest: {}".format(1 - ratio_2))

  line_count = math.ceil(freq_count / 40)
  line_width = math.ceil(freq_count / line_count)

  alphabet_width = len(sorted_chars)

  # prep for speedup: filter/reduce sorted_seqs to sequences matching the reduced cmap[] charset:
  sorted_seqs_hf = {}
  for order, (seq, _) in enumerate(sorted_seqs):
      first_char = seq[0]
      second_char = seq[1]
      if first_char <= hi_c and second_char <= hi_c and \
         char_order_lookup[first_char] < freq_count and char_order_lookup[second_char] < freq_count \
      :
          index = first_char + (hi_c + 1) * second_char
          sorted_seqs_hf[index] = order

  if freq_count_limit < alphabet_width:
      frequent_cmap_prefix = 'Frequent'
  else:
      frequent_cmap_prefix = ''

  c_code += '#define {}UnicodeCharToOrderIsReduced  {}\n'.format(language_c, 1 if freq_count_limit < alphabet_width else 0)
      
  c_code += '\n\n#define {}FCMLowerBound  {}\n'.format(language_c, lo_c)
  c_code += '#define {}FCMUpperBound  {}\n\n\n'.format(language_c, hi_c)

  FC_str = 'static const PRInt16 {}{}UnicodeCharToOrder[]'.format(language_c, frequent_cmap_prefix)
  FC_str += ' =\n{'

  longest_irr_run_start = -1
  longest_irr_run_length = 0
  current_irr_run_start = -1
  current_irr_run_length = 0
  for char in range(lo_c, hi_c + 1):
      order = char_order_lookup[char]
      if order < freq_count:
          if current_irr_run_length > longest_irr_run_length:
              longest_irr_run_start = current_irr_run_start
              longest_irr_run_length = current_irr_run_length
          current_irr_run_start = -1
          current_irr_run_length = 0
      else:                                 # invalid_order_nr
          if current_irr_run_start < 0:
              current_irr_run_start = char
              current_irr_run_length = 0
          current_irr_run_length += 1
  if current_irr_run_length > longest_irr_run_length:
      longest_irr_run_start = current_irr_run_start
      longest_irr_run_length = current_irr_run_length
  # heuristic:
  if longest_irr_run_length < 40:
      longest_irr_run_start = -1
      longest_irr_run_length = 0

  count = 0
  for char in range(lo_c, hi_c + 1):
      if longest_irr_run_length > 0 and char == longest_irr_run_start:
          pass # break

      if count % 20 == 0:
          FC_str += '\n  '
      count += 1

      order = char_order_lookup[char]
      if order < freq_count:
          FC_str += "{},".format(order)
      else:
          FC_str += "{},".format('IRR')     # invalid_order_nr

  FC_str += '\n};\n\n'
  c_code += FC_str

  if longest_irr_run_length > 0:
      sys.stderr.write('@@@ OrderMap largest gap: {}\n'.format(longest_irr_run_length))

      SM_str = '\n'
      SM_str += '\n#define {}{}UnicodeCharToOrderFirstTableChunkSize    {}'.format(language_c, frequent_cmap_prefix, longest_irr_run_start - lo_c)
      SM_str += '\n#define {}{}UnicodeCharToOrderSecondTableChunkOffset {}'.format(language_c, frequent_cmap_prefix, longest_irr_run_start + longest_irr_run_length - lo_c)
      SM_str += '\n#define {}{}UnicodeCharToOrderSecondTableChunkSize   {}'.format(language_c, frequent_cmap_prefix, hi_c + 1 - (longest_irr_run_start + longest_irr_run_length))
      SM_str += '\n\n\n'
      c_code += SM_str
  
      FC_str = 'static const PRInt16 {}{}UnicodeCharToOrder2[]'.format(language_c, frequent_cmap_prefix)
      FC_str += ' =\n{'

      count = 0
      for char in range(longest_irr_run_start + longest_irr_run_length, hi_c + 1):
          if count % 20 == 0:
              FC_str += '\n  '
          count += 1

          order = char_order_lookup[char]
          if order < freq_count:
              FC_str += "{},".format(order)
          else:
              FC_str += "{},".format('IRR')     # invalid_order_nr

      FC_str += '\n};\n\n'
      c_code += FC_str

  LM_str = 'static const PRUint8 {}CompactedLangModel[]'.format(language_c)
  LM_str += ' =\n{'

  omap = [0] * freq_count
  for char, ratio, order in sorted_chars:
      if order < freq_count:
          omap[order] = char

  count = 0
  for first_order in range(0, freq_count):
      first_char = omap[first_order]

      if debug:
          sys.stderr.write('first_order: {}, first_char: {}, lo_c: {}, hi_c: {}, freq_count_limit: {}\n'.format(first_order, first_char, lo_c, hi_c, freq_count_limit))
      else:
          sys.stderr.write('#')
          sys.stderr.flush()

      for second_order in range(0, freq_count):
          second_char = omap[second_order]

          # Let's not make too long lines.
          if count % line_width == 0:
              LM_str += '\n  '

          index = first_char + (hi_c + 1) * second_char
          if (index in sorted_seqs_hf):
              order = sorted_seqs_hf[index]
              if order < order_3:
                  LM_str += '3,'
              elif order < order_2:
                  LM_str += '2,'
              else:
                  LM_str += '1,'
          else:
              LM_str += '0,'

          count += 1

  LM_str += '\n};\n'
  c_code += LM_str

  for charset in lang_charsets:
      charset_c = charset.replace('-', '_').title()
      SM_str = '\n\nconst SequenceModel {}{}Model ='.format(charset_c, language_c)
      SM_str += '\n{\n  '
      SM_str += '{}_CharToOrderMap,'.format(charset_c)
      SM_str += '\n  {}CompactedLangModel,'.format(language_c)
      SM_str += '\n  {}OrderWidth,'.format(language_c)
      SM_str += '\n  {}f,'.format(ratio_2)
      SM_str += '\n  {},'.format('PR_TRUE' if lang.use_ascii else 'PR_FALSE')
      SM_str += '\n  "{}",'.format(charset)
      SM_str += '\n  "{}"'.format(lang.code)
      SM_str += '\n};'
      c_code += SM_str

  SM_str = '\n\nconst LanguageModel {}Model ='.format(language_c)
  SM_str += '\n{'
  SM_str += '\n  "{}",'.format(lang.code)
  SM_str += '\n  Unicode_CharOrder,'
  SM_str += '\n  Unicode_Char_size,\n'
  SM_str += '\n  {}FCMLowerBound,'.format(language_c)
  SM_str += '\n  {}FCMUpperBound,'.format(language_c)
  SM_str += '\n  {}UnicodeCharToOrderIsReduced,'.format(language_c)
  SM_str += '\n  {}{}UnicodeCharToOrder,'.format(language_c, frequent_cmap_prefix)
  if longest_irr_run_length > 0:
      SM_str += '\n  {}{}UnicodeCharToOrderFirstTableChunkSize,'.format(language_c, frequent_cmap_prefix)
      SM_str += '\n  {}{}UnicodeCharToOrderSecondTableChunkOffset,'.format(language_c, frequent_cmap_prefix)
      SM_str += '\n  {}{}UnicodeCharToOrderSecondTableChunkSize,'.format(language_c, frequent_cmap_prefix)
      SM_str += '\n  {}{}UnicodeCharToOrder2,'.format(language_c, frequent_cmap_prefix)
  else:
      SM_str += '\n  {}FCMUpperBound + 1 - {}FCMLowerBound,'.format(language_c, language_c)
      SM_str += '\n  0,'
      SM_str += '\n  0,'
      SM_str += '\n  nullptr,'
  SM_str += '\n  OrderToRatio,'
  SM_str += '\n  {}CompactedLangModel,'.format(language_c)
  SM_str += '\n  {}OrderWidth,'.format(language_c)
  SM_str += '\n  {},'.format(very_freq_count)
  SM_str += '\n  {}f,'.format(very_freq_ratio)
  SM_str += '\n  {},'.format(low_freq_order)
  SM_str += '\n  {}f,'.format(low_freq_ratio)
  SM_str += '\n  {}f,'.format(accumulated_ratios)
  SM_str += '\n};'
  c_code += SM_str

  c_code += '\n'

  lang_model_file = current_dir + '/../src/LangModels/Lang{}Model.cpp'.format(language_c)
  with open(lang_model_file, mode='w', encoding='utf-8') as cpp_fd:
      cpp_fd.write(c_code)

  logfd.write('\n\n- Processing end: {}\n'.format(str(datetime.datetime.now())))
  logfd.close()

  generated_files += [ (lang_model_file, build_log) ]

charset_cpp = os.path.join(current_dir, '../src', 'nsSBCharSetProber-generated.h')
print("\nGenerating {}…".format(charset_cpp))

with open(charset_cpp, mode='w', encoding='utf-8') as cpp_fd:
  with open(current_dir + '/header-template.cpp', mode='r', encoding='utf-8') as header_fd:
    cpp_fd.write(header_fd.read())

  cpp_fd.write('\n#ifndef nsSingleByteCharSetProber_generated_h__')
  cpp_fd.write('\n#define nsSingleByteCharSetProber_generated_h__\n')

  all_extern_declarations = ''
  n_sequence_models = 0
  for l in all_langs:
    l = l.lower()
    # Load the language data.
    sys_path_backup = sys.path
    sys.path = [current_dir + '/langs']
    try:
        lang = importlib.import_module(l)
    except ImportError:
        sys.stderr.write('Unknown language code "{}": '
                         'file "langs/{}.py" does not exist.\n'.format(l, l))
        exit(1)
    sys.path = sys_path_backup

    language_c = lang.name.replace('-', '_').title()
    lang_charsets = charsets.db.load(lang.charsets)
    for charset in lang_charsets:
      charset_c = charset.replace('-', '_').title()
      all_extern_declarations += '\nextern const SequenceModel {}{}Model;'.format(charset_c, language_c)
      n_sequence_models += 1
    all_extern_declarations += '\n'

  cpp_fd.write('\n#define NUM_OF_SEQUENCE_MODELS {}\n'.format(n_sequence_models))
  cpp_fd.write('{}'.format(all_extern_declarations))
  cpp_fd.write('\n#endif /* nsSingleByteCharSetProber_generated_h__ */')

print("Done!")

language_cpp = os.path.join(current_dir, '../src', 'nsLanguageDetector-generated.h')
print("\nGenerating {}…".format(language_cpp))

with open(language_cpp, mode='w', encoding='utf-8') as cpp_fd:
  with open(current_dir + '/header-template.cpp', mode='r', encoding='utf-8') as header_fd:
    cpp_fd.write(header_fd.read())

  cpp_fd.write('\n#ifndef nsLanguageDetector_h_generated_h__')
  cpp_fd.write('\n#define nsLanguageDetector_h_generated_h__\n')

  all_extern_declarations = ''
  n_language_models = 0
  for l in all_langs:
    l = l.lower()
    # Load the language data.
    sys_path_backup = sys.path
    sys.path = [current_dir + '/langs']
    try:
        lang = importlib.import_module(l)
    except ImportError:
        sys.stderr.write('Unknown language code "{}": '
                         'file "langs/{}.py" does not exist.\n'.format(l, l))
        exit(1)
    sys.path = sys_path_backup

    language_c = lang.name.replace('-', '_').title()
    all_extern_declarations += '\nextern const LanguageModel {}Model;'.format(language_c)
    n_language_models += 1

  cpp_fd.write('\n#define NUM_OF_LANGUAGE_MODELS {}\n'.format(n_language_models))
  cpp_fd.write('{}'.format(all_extern_declarations))
  cpp_fd.write('\n\n#endif /* nsLanguageDetector_h_generated_h__ */')

print("Done!")
if len(generated_files) > 0:
  print("\nThe following language files has been generated:")
  for (lang_model_file, build_log) in generated_files:
    print("\n- Language file: {}".format(lang_model_file))
    print("\n  Build log: {}".format(build_log))

print("\nTODO:")
print("- edit nsSBCSGroupProber::nsSBCSGroupProber() in src/nsSBCSGroupProber.cpp manually to test new sequence models;")
print("- edit nsMBCSGroupProber::nsMBCSGroupProber() in src/nsMBCSGroupProber.cpp manually to test new language models;")
print("- add any new language files to src/CMakeLists.txt;")
print("- commit generated files if tests are successful.")
