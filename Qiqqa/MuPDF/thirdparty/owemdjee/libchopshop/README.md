# libchopshop

- NLP/text processing with automated stop word detection and stemmer-based filtering
- **input** is international language plain text (UTF-8)
- **output** is n-gram / k-mer output vectors`<uint16_t>`/`<uint32_t>`/`<uint64_t>` with optional weight vector`<float>`/`<double>`/`<int>`
  + support variable length n-grams, q-grams, skip-grams, *elasti*-grams, k-grams for arbitrary k
  + character / symbol / codepoint and word + phrase[^1] level tokens (grams)
  + attributed / augmented n-grams (POS encoding as part of the n-gram; ditto for whole-word/part-of-word/start- & end-of-word markers)
  + support weights / ranking -based filtering of the token stream ("*primus inter pares*", only the "*upper crust*" are allowed through into the output vectors)
- also available as CLI tool, suitable for UNIX-style piped workflows, such as `my_extractor | chopshop | my_fts_db_feeder` command lines. Can be easily called from arbritary language scripts ("external invocation" a.k.a. "execv/system call")

[^1]: "words" are discovered in the input text stream by fast, redefinable NLP tokenizers; may be dictionary-assisted or aided otherwise.

This library / toolkit is engineered to be able to provide **both** of the (often more or less disparate) n-gram token streams / vectors required for (1) initializing / training FTS databases, neural nets, etc. and (2) executing effective queries / matches on these engines.



## Notable characteristics

In FTS, you won't be able to find references to the Shakespearian quote "To be or not to be" when using *any* stop word list as it's all stop words and thus producing utter ... *silence*, at both indexing and searching time. Not so with `chopshop`.
 
With FTS databases, for example, it might be highly desirable to keep the database/search index relatively small -- and thus potentially much faster for large document collections, particularly with limited hardware resources available! -- which is why everyone and their granny are into stop-word lists, which is a rather blunt hammer to solve token-count-per-document reduction ("optimization") requirements. `chopshop` enables this approach, among others, but allows run-time dynamic discovery of the stop-words-list that's applicable to the given session and/or *input document*. Meanwhile the very same tokenizer can be used at the search query tokenization side, where it's advisable to NOT filter stop-words that way but let it all hit the index to find matches.[^2]

`chopshop` has been engineered to support both major language groups: the Indo-european form which uses whitespace + punctuation for word separation, and the (east-)asian languages (plus old Egyptian, etc.etc.) which are ideogram-based languages which do not have easily machine-readable word separators that way.
As a bonus, `chopshop` is able to apply the word-recognition mechanisms you often see with the latter to the former, among other word-extraction subtools: this means `chopshop` can cope quite well with euro/american language where the whitespace has been lost for whatever reason (e.g. because your document extractor failed to produce them or you are processing text media, such as old telegram messages where character expenditure came at significant cost and thus had its whitespace removed to save (tranmit + encryption) time and coin.





[^2]: of course, the note about not filtering stop-words at the query/probe site of the process only has merit when any *run-time dynamic* form of stop-ord like filtering at index/training time has been applied, as *only then* will there be *potential amtches* for such words available/recognized in your engine. When you apply old skool brute force stop word filtering, there's no good argument to not just do the very same at query/probe time as well.



  
