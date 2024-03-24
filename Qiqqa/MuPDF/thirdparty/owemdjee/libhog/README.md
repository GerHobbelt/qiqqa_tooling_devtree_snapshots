# `hog` a.k.a. `hound` - fetch the (PDF,EPUB,HTML) document you seek using maximum effort

`hog` (a.k.a. `(news)hound`)[^1] = a tool for fetching *files* from the internet, specifically PDFs. Intended to be used where you browse the 'Net and decide you want to download a given PDF from any site: this can be done through the browser itself, but is sometimes convoluted or neigh impossible (ftp links require another tool, PDFs stored at servers which report as having their SSL certificates *expired* are a hassle to get through for the user-in-a-hurry, etc. etc.) and `hog` is meant to cope with all these by providing:
  - ability to detect the listed PDF url and *download* it, i.e. has knowledge about several approaches used by various sites (publishers, etc.) which offer on-line PDFs for viewing & downloading,
  - *possibly* (= future feature) allow scripting these seek&fetch behaviours so users can create their own, custom, procedures re DOM parsing, cookies, etc. as the sites change or other sites' access is desired, when not yet part of the "how to download" knowledge base of `hog` out of the box,
  - fundamentally a tool that sits somewhere between `cUrl` and `wget`, with some `cUrl-impersonation` abilities thrown in as well. This includes:
    - desirable behaviour with minimal commandline arguments, i.e. "good defaults",
    - auto-naming the local filename when downloading,
    - auto-sanitizing the local filename when downloading (255 max length, only ASCII or letter/number Unicode chars in the filename, etc.),
    - create a *second* local file describing the metadata thus far, in particular the source URL, for it will be loaded by Qiqqa as part of the file's metadata later on,
    - ability to detect and follow HTTP 301, 302 responses, *but also* HTTP pages which come back as 200, yet have "timers" (sourceforge, f.e.) or other wait-before-you-get-it or go-here-instead "redirection" embedded in their HTML output,
    - `hog` being able to either fetch a *file* (PDF, image, ...) or a *full HTML page*: some whitepapers are published as blog articles or other HTML-only formats, and we want those too *as local files*. This implies that we should be able to tell `hog` to grab the page itself (auto-detect such a scenario?), plus all its relevant assets (CSS, images, ...) and bundle that into a HTMLZ or similar "HTML file archive".
      > I'm not too enthousiastic about the classical MHTML (Mime-HTML) format as it expands images using Base64, while we have *zero* need to raw-copy this into email or would otherwise benefit from the convoluted MIME encoding in our storage format — better would be having it all in an accessible single file, e.g. a ZIP-style wrapper, hence my preference for [HTMLZ](https://wiki.mobileread.com/wiki/HTMLZ) (or the more modern [WARC](https://en.wikipedia.org/wiki/Web_ARChive) format, which seems to be preferred by internet libraries out there, e.g. archive.org)


[^1]: name inspired by the line "*news-hound sniffs the air...*" (Roger Waters: Amused To Death)
