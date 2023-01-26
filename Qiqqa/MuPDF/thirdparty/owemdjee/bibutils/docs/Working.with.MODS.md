# Introduction to MODS version 3 Bibliography Format

Document Version 0.3 November 2 2007  
Chris Putnam

The MODS Schema is defined at the Library of Congress which is the ultimate authority. This document seeks to be an introduction to trying to use MODS and is the sort of document I would have liked to have had when I first started outputting MODS from my conversion tools.

```
1. Self-contained Items
    1.1 modsCollection
    1.2 title
    1.3 names
    1.4 origin
    1.5 type of resource
    1.6 genre
    1.7 citation key 
2. Items within Larger Collections
    2.1 part tag 
3. Thoughts about MODS for Bibliography Conversions
4. Credits
```

# 1\. Self-contained Items

The easiest type of reference is to a self-contained item, such as a book or report. The source I'm showing is bibtex (but I also could find RIS, EndNote, or other examples if it's helpful).

```
 @book(bandj,
 author="T. L. Blundell
 and L. N. Johnson",
 title="Protein Crystallography",
 publisher="Academic Press",
 address="New York",
 year=1976)
```

Converted to MODS, it looks like the following:

```
<mods ID="bandj">
    <titleInfo>
        <title>Protein Crystallography?</title>
    </titleInfo>
    <name type="personal">
            <namePart type="given">T.</namePart>
        <namePart type="given">L.</namePart>
            <namePart type="family">Blundell</namePart>
            <role>
                <roleTerm authority="marcrelator" type="text">author</roleTerm>
            </role>
    </name>
    <name type="personal">
        <namePart type="given">L.</namePart>
        <namePart type="given">N.</namePart>
        <namePart type="family">Johnson</namePart>
        <role>
            <roleTerm authority="marcrelator" type="text">author</roleTerm>
        </role>
    </name>
    <originInfo>
        <dateIssued>1976</dateIssued>
        <publisher>Academic Press</publisher>
        <place>
            <placeTerm type="text">New York</placeTerm>
        </place>
    </originInfo>
    <typeOfResource>text</typeOfResource>
    <genre>book</genre>
    <identifier type="citekey">bandj</identifier>
</mods>
```

## 1.1 modsCollection

First things first. A list of bibliographies is a modsCollection, which is only allowed to have mods (individual items) collection inside.

```
<modsCollection>
    <mods></mods>
    <mods></mods>
</modsCollection>
```

## 1.2 Title

The title of the item goes under the title key. Subtitles are explictly split.

```
 @book(bandj,
 author="T. L. Blundell
 and L. N. Johnson",
 title="Protein Crystallography: with subtitle",
 publisher="Academic Press",
 address="New York",
 year=1976)
```

The title as MODS:

```
<titleInfo>
    <title>Protein Crystallography</title>
    <subTitle>with subtitle</subTitle>
</titleInfo>

@book(bandj,
author="T. L. Blundell
and L. N. Johnson",
title="Protein Crystallography? with subtitle",
publisher="Academic Press",
address="New York",
year=1976)
```

The title as MODS:

```
<titleInfo>
    <title>Protein Crystallography?</title>
    <subTitle>with subtitle</subTitle>
</titleInfo>
```

MODS also supports items with full and abbreviated titles, something that I do not know how to code in BibTeX.

```
<titleInfo>
    <title>Protein Crystallography</title>
    <subTitle>with subtitle</subTitle>
</titleInfo>
<titleInfo type="abbreviated">
    <title>Blundell-and-Johnson we call it</title>
</titleInfo>
```

## 1.3 People

People associated with the work (authors, editors, translators) all fall under the <name> tag, distinguished by their role. All possible roles under the "marcauthority" are defined on the MODS web site. I do have some problems with limitations. For example, "reporter" isn't a valid term, which is problematic both for newspapers and court proceedings; however, the roles under the "marcauthority" do cover a lot of ground.</name>

```
<name type="personal">
    <namePart type="given">T.</namePart>
    <namePart type="given">L.</namePart>
    <namePart type="family">Blundell</namePart>
    <role>
        <roleTerm authority="marcrelator" type="text">author</roleTerm>
    </role>
</name>
```

There are two name 'types', personal and corporate (for things authored by agencies and the like). My converter tools support an external file that lists names that when matched will be automatically listed as "corporate", which also includes government agencies.

## 1.4 Origin

Provides the information about date, publisher, and the like. The date really ought to be output in a much cleaner way using nice XML standards (whose names I don't have right here). I've been dragging my feet just a little bit--mostly it's due to the range of things I've seen used as date information in different bibliography sources (that claim to be the same formats)....They're easy for humans to parse, but much more difficult to do correctly using a program. This is mostly me being lazy coupled with a lack of people really pushing it.

## 1.5 Type of Resource

The options here are fully enumerated by the MODS standard:

```
text
cartographic
notated music
sound recording-musical
sound recording-nonmusical
sound recording
still image
moving image
three dimensional object
software, multimedia (note error on MODS web page)
mixed material
```

Almost all references are going to be <typeofresource>text</typeofresource>, which makes the field not so useful for determining reference "types" in the bibliography software world.

## 1.6 Genre

The <genre> tag is more helpful for actually dterming reference "types" in the more traditional sense of software. Allowed types under are defined at the MODS web site.</genre>

## 1.7 CiteKey

There was a question as to where the citekey "bandj" should go. Two possibilities were discussed and both were used to make the MODS output more generally useful for different XML parsings...the first is the ID attribute for the main <mods> tag, the second is the citekey type of identifier.</mods>

# 2\. Items within Larger Collections

These types of scenarios were more difficult for me to initially understand, but once I appreciated them, it shows how MODS really shines. Every MODS reference can also include a <relatedItem>, which is another MODS reference and potentially other <relatedItem>s. The <relatedItem type="host"> and <relatedItem type="series"> refer to a larger collection that contains the reference. Thus it's possible to nest a chapter of a book in a series thusly:

```
<mods>
...chapter details...
<relatedItem type="host">
    ...book details...
    <relatedItem type="series">
        ...series details...
    </relatedItem>
</relatedItem>
</mods>
```

For a journal (or newspaper) article, the article is considered as part of the journal as a larger collection:

```
<mods>
...article details...
<relatedItem type="host">
    ...journal details...
</relatedItem>
</mods>
```

For example, here's a bibtex journal article:

```
 @ARTICLE(C003,
 AUTHOR="B. Kramer
 and W. Kramer
 and H. J. Fritz",
 TITLE="Different base/base mismatches are corrected with
 different efficiencies by the methyl-directed {DNA} mismatch-repair
 system of {{\it E. coli}}",
 JOURNAL="Cell",
 VOLUME=38,
 YEAR=1984,
 PAGES="879--887")
```

As MODS:

```
<mods ID="C003">
    <titleInfo>
        <title>Different base/base mismatches are corrected with 
        different efficiencies by the methyl-directed DNA mismatch-repair 
        system of E. coli</title>
    </titleInfo>
    <name type="personal">
        <namePart type="given">B.</namePart>
        <namePart type="family">Kramer</namePart>
        <role>
            <roleTerm authority="marcrelator" type="text">author</roleTerm>
        </role>
    </name>
    <name type="personal">
        <namePart type="given">W.</namePart>
        <namePart type="family">Kramer</namePart>
        <role>
            <roleTerm authority="marcrelator" type="text">author</roleTerm>
        </role>
    </name>
    <name type="personal">
        <namePart type="given">H.</namePart>
        <namePart type="given">J.</namePart>
        <namePart type="family">Fritz</namePart>
        <role>
            <roleTerm authority="marcrelator" type="text">author</roleTerm>
        </role>
    </name>
    <typeOfResource>text</typeOfResource>
    <relatedItem type="host">
        <titleInfo>
            <title>Cell</title>
        </titleInfo>
        <originInfo>
            <issuance>continuing</issuance>
        </originInfo>
        <genre authority="marc">periodical</genre>
        <genre>academic journal</genre>
        <part>
           <date>1984</date>
           <detail type="volume"><number>38</number></detail>
           <extent unit="page">
               <start>879</start>
               <end>887</end>
           </extent>
        </part>
    </relatedItem>
    <identifier type="citekey">C003</identifier>
</mods>
```

## 2.1 Part tag

The part tag is the only new tag defined in the <relateditem> that isn't defined in the main mods level. For a <relateditem type="host">, it describes where the object is in terms of volume, issue, pages, and the like. From the above example:</relateditem></relateditem>

```
    <part>
       <date>1984</date>
       <detail type="volume"><number>38</number></detail>
       <extent unit="page">
           <start>879</start>
           <end>887</end>
       </extent>
    </part>
```

The detail is used to describe single item locators, such as volume, issue, number, section, and session.

The extent is used to describe ranges. The only extent element that I current output is the page range; however, I've been told that to use extent for a reference of only a single page is wrong. So:

```
<part>
    <extent unit="page">
        <start>879</start>
    </extent>
</part>
```

and

```
<part>
    <extent unit="page">
        <start>879</start>
        <end>879</end>
    </extent>
</part>
```

and should be handled by a detail element

```
<part>
    <detail type="page"><number>879</number></detail>
</part>
```

# 3\. Thoughts about MODS for Bibliography Conversions

The biggest problem for using MODS as an intermediate XML format for converting between different bibliographies may be one of scope. MODS appears to have been defined for people who want to extensively characterize their references, and it lacks a field with a simple 1:1 relationship to typical bibliographic reference types used in bibliography programs. Instead the information appears to be scattered across a number of different fields which have to be looked up to sort out what sort of reference type a particular reference is (which is the most basic sort of information programs like BibTeX and EndNote require).

Thus far, I've resisted introducing my own custom "authorities" and types to my MODS output (and input) as I want the conversion tools to happily take MODS files from anywhere, rather than only handling MODS files that my programs have generated.

# 4\. Credits

As a final thought, this entire document stems simply from my experience in trying to use MODS as a format. Bruce D'Arcus [http://netapps.muohio.edu/movabletype/archives/darcusb/darcusb/](http://netapps.muohio.edu/movabletype/archives/darcusb/darcusb/)) has been really helpful in getting me started in working with the format and has patiently looked for bugs even in really raw alpha versions of my converter programs. What's right about the software is substantially due to his help. What's wrong about the software (and this document) are fully my responsibility.
