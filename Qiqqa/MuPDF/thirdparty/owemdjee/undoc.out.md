
- **OpenImageIO** [🌐](https://github.com/OpenImageIO/oiio)

























- **SWIG** [🌐](https://swig.readthedocs.io/en/latest/Manual/SWIG.html)

























- **hsluv-c** [📁](./hsluv-c) [🌐](https://github.com/GerHobbelt/hsluv-c)

[![Build Status](https://travis-ci.org/hsluv/hsluv-c.svg?branch=master)](https://travis-ci.org/hsluv/hsluv-c)

# HSLuv-C: Human-friendly HSL

## Introduction

This is C implementation of [HSLuv](https://www.hsluv.org/) (revision 4).


## Using HSLuv-C with your own project

Just copy `src/hsluv.h` and `src/hsluv.c` into your project.

Refer to `src/hsluv.h` for API description.


## Building from a Git clone

```console
$ mkdir build
$ cd build
$ cmake ..
$ make
$ make test
```


## Reporting Bugs

If you encounter any bug, please be so kind and report it. Unheard bugs cannot
get fixed. You can submit bug reports here:

* https://github.com/hsluv/hsluv-c/issues


## License

HSLuv-C is covered with MIT license, see the file `LICENSE.md`.


































- **jpeg-xl** [📁](./jpeg-xl) [🌐](https://github.com/GerHobbelt/jpeg-xl)

# JPEG XL reference implementation

[![Build/Test](https://github.com/libjxl/libjxl/actions/workflows/build_test.yml/badge.svg)](
https://github.com/libjxl/libjxl/actions/workflows/build_test.yml)
[![Build/Test Cross](https://github.com/libjxl/libjxl/actions/workflows/build_test_cross.yml/badge.svg)](
https://github.com/libjxl/libjxl/actions/workflows/build_test_cross.yml)
[![Conformance](https://github.com/libjxl/libjxl/actions/workflows/conformance.yml/badge.svg)](
https://github.com/libjxl/libjxl/actions/workflows/conformance.yml)
[![CIFuzz](https://github.com/libjxl/libjxl/actions/workflows/fuzz.yml/badge.svg)](
https://github.com/libjxl/libjxl/actions/workflows/fuzz.yml)
[![Releases](https://github.com/libjxl/libjxl/actions/workflows/release.yaml/badge.svg)](
https://github.com/libjxl/libjxl/actions/workflows/release.yaml)
[![Doc](https://readthedocs.org/projects/libjxl/badge/?version=latest)](
https://libjxl.readthedocs.io/en/latest/?badge=latest)
[![codecov](https://codecov.io/gh/libjxl/libjxl/branch/main/graph/badge.svg)](
https://codecov.io/gh/libjxl/libjxl)

<img src="doc/jxl.svg" width="100" align="right" alt="JXL logo">

This repository contains a reference implementation of JPEG XL (encoder and
decoder), called `libjxl`. This software library is
[used by many applications that support JPEG XL](doc/software_support.md).

JPEG XL was standardized in 2022 as [ISO/IEC 18181](https://jpeg.org/jpegxl/workplan.html).
The [core codestream](doc/format_overview.md#codestream-features) is specified in 18181-1,
the [file format](doc/format_overview.md#file-format-features) in 18181-2.
[Decoder conformance](https://github.com/libjxl/conformance) is defined in 18181-3,
and 18181-4 is the [reference software](https://github.com/libjxl/libjxl).

The library API, command line options, and tools in this repository are subject
to change, however files encoded with `cjxl` conform to the JPEG XL specification
and can be decoded with current and future `djxl` decoders or the `libjxl` decoding library.

## Installation

In most Linux distributions, installing `libjxl` is just a matter of using the package management system.
For example in Debian-based distributions: `apt install libjxl-tools` will install `cjxl` and `djxl`
and other tools like `benchmark_xl` are available in the package `libjxl-devtools`.
On MacOS, you can use [Homebrew](https://brew.sh/): `brew install jpeg-xl`.

[![libjxl packaging status](https://repology.org/badge/vertical-allrepos/libjxl.svg?exclude_unsupported=1&columns=3&exclude_sources=modules,site&header=libjxl%20packaging%20status)](https://repology.org/project/libjxl/versions)


For Windows, binaries can be downloaded from the [releases page](https://github.com/libjxl/libjxl/releases/).

Of course you can also [build libjxl from sources](BUILDING.md).


## Usage

To encode a source image to JPEG XL with default settings:

```bash
cjxl input.png output.jxl
```

The desired visual fidelity can be selected using the `--distance` parameter
(in units of just-noticeable difference, where 0 is lossless and the most useful lossy range is 0.5 .. 3.0),
or using `--quality` (on a scale from 0 to 100, roughly matching libjpeg).
The [encode effort](doc/encode_effort.md) can be selected using the `--effort` parameter.

For more settings run `cjxl --help` or for a full list of options
run `cjxl -v -v --help`.

To decode a JPEG XL file run:

```bash
djxl input.jxl output.png
```

When possible `cjxl`/`djxl` are able to read/write the following
image formats: .exr, .gif, .jpeg/.jpg, .pfm, .pgm/.ppm, .pgx, .png.
Specifically for JPEG files, the default `cjxl` behavior is to apply lossless
recompression and the default `djxl` behavior is to reconstruct the original
JPEG file (when the extension of the output file is .jpg).

### Benchmarking

For speed benchmarks on single images in single or multi-threaded decoding
`djxl` can print decoding speed information. See `djxl --help` for details
on the decoding options and note that the output image is optional for
benchmarking purposes.

For more comprehensive benchmarking options, see the
[benchmarking guide](doc/benchmarking.md).

### Library API

Besides the `libjxl` library [API documentation](https://libjxl.readthedocs.io/en/latest/),
there are [example applications](examples/) and [plugins](plugins/) that can be used as a reference or
starting point for developers who wish to integrate `libjxl` in their project.


## License

This software is available under a 3-clause BSD license which can be found in
the [LICENSE](LICENSE) file, with an "Additional IP Rights Grant" as outlined in
the [PATENTS](PATENTS) file.

Please note that the PATENTS file only mentions Google since Google is the legal
entity receiving the Contributor License Agreements (CLA) from all contributors
to the JPEG XL Project, including the initial main contributors to the JPEG XL
format: Cloudinary and Google.

## Additional documentation

### Codec description

*   [JPEG XL Format Overview](doc/format_overview.md)
*   [Introductory paper](https://www.spiedigitallibrary.org/proceedings/Download?fullDOI=10.1117%2F12.2529237) (open-access)
*   [XL Overview](doc/xl_overview.md) - a brief introduction to the source code modules
*   [JPEG XL white paper](https://ds.jpeg.org/whitepapers/jpeg-xl-whitepaper.pdf)
*   [JPEG XL official website](https://jpeg.org/jpegxl)
*   [JPEG XL community website](https://jpegxl.info)

### Development process

*   [More information on testing/build options](doc/building_and_testing.md)
*   [Git guide for JPEG XL](doc/developing_in_github.md) - for developers
*   [Fuzzing](doc/fuzzing.md) - for developers
*   [Building Web Assembly artifacts](doc/building_wasm.md)
*   [Test coverage on Codecov.io](https://app.codecov.io/gh/libjxl/libjxl) - for
    developers
*   [libjxl documentation on readthedocs.io](https://libjxl.readthedocs.io/)

### Contact

If you encounter a bug or other issue with the software, please open an Issue here.

There is a [subreddit about JPEG XL](https://www.reddit.com/r/jpegxl/), and
informal chatting with developers and early adopters of `libjxl` can be done on the
[JPEG XL Discord server](https://discord.gg/DqkQgDRTFu).


































- **jpeginfo** [📁](../../thirdparty/jpeginfo) [🌐](https://github.com/GerHobbelt/jpeginfo)


Jpeginfo v1.7.0beta  Copyright (c) 1995-2023, Timo Kokkonen.


REQUIREMENTS
	jpeglib, Independent JPEG Group's jpeg library version 6a or
        version 7 (or later version)

TESTED PLATFORMS
	Linux
	MacOS
	Solaris
        IRIX
	HP-UX

INSTALLATION
	Installation should be very straightforward, just unpack the
	tar file, run configure script, and then compile the program. 
	You may wanna do something like this:

		gunzip -c jpeginfo-1.7.0.tar.gz | tar xf -
		cd jpeginfo-1.7.0
		./configure
		make
		make strip
		make install

	NOTE! if 'configure' cannot find libjpeg.a or jpeglib.h, then
	you must use the --with-jpeglib option when running configure,
	see 'configure --help'.


HISTORY
        v1.7.0 - add support for reading input file stdin,
	         other minor fixes.
	v1.6.2 - add SHA256 digest support (--sha256 or -2),
	         improved Win32 support thanks to tumagonx,
		 other minor fixes.
	v1.6.1 - support for new libjpeg v7 thanks to Guido Vollbeding,
		 fix to display of 8bit characters by Pierre Jarillon
	v1.6.0 - added support for printing out Comments (from COM
	         markers), Exif format images are now also recognized
	         (no Exif marker decoding functionality, though).
	v1.5   - configuration is now done with GNU autoconf, 
		 program now uses free MD5 algorithm,
		 added file size as new field on reports,
		 program now returns exit code 1 if one or more of the jpegs
		 had any errors, useful for testing if particular jpeg is
	         ok from shell scripts, 
	         also if you specify -q (--quiet) option twice on
		 command line, then program won't produce any output.
	v1.4   - added support for calculating MD5 checksums.
	v1.3   - alternative listing format (-l switch) added.
	         new column on reports displaying whether jpeg is 
		 progressive or normal (P/N).
		 new switch -i for printing out even more information
	         about pictures: coding, density, CCIR601 sampling.
	         new switch -f for passing filenames to program from
	         file or stdin.
	v1.2   - improved support for other platforms, minor fixes
        v1.1.2 - small fixes, improvements to Makefile
	v1.1   - modified to use Independent JPEG Group's new v.6a library,
		 minor fixes.
	v1.0   - first public release


LATEST VERSION

	Latest version is always available from:
		http://www.iki.fi/tjko/projects.html


ACKNOWLEDGEMENT

	- MD5 message-digest allgorithm used is public domain implementation
	  written by Colin Plumb.
	- SHA-256 message-digest algorithm used is public domain implementation
	  by D. J. Bernstein (from NaCl library).



Timo <tjko@iki.fi>
07-Jan-2023


































- **lda-Familia** [📁](./lda-Familia) [🌐](https://github.com/GerHobbelt/Familia)

<a href="http://github.com/baidu/Familia">
	<img style="vertical-align: top;" src="https://raw.githubusercontent.com/wiki/baidu/Familia/img/logo.png?raw=true" alt="logo" height="140px">
</a>

[![Build Status][image-1]][1]
[![License][image-2]]()

**Familia** 开源项目包含文档主题推断工具、语义匹配计算工具以及基于工业级语料训练的三种主题模型：Latent Dirichlet Allocation(LDA)、SentenceLDA 和Topical Word Embedding(TWE)。 支持用户以“拿来即用”的方式进行文本分类、文本聚类、个性化推荐等多种场景的调研和应用。考虑到主题模型训练成本较高以及开源主题模型资源有限的现状，我们会陆续开放基于工业级语料训练的多个垂直领域的主题模型，以及这些模型在工业界的典型应用方式，助力主题模型技术的科研和落地。([**English**][10])

## News!!!

近期，我们在[PaddleHub](https://github.com/PaddlePaddle/PaddleHub) 1.8版本中上线了**Familia**中的LDA模型，根据数据集的不同，区分为lda_news、lda_novel和lda_webpage。

PaddleHub使用起来非常便捷，我们以lda_news的使用来进行例子介绍。

1. 首先，在使用PaddleHub之前，需要先安装PaddlePaddle深度学习框架，更多安装说明请查阅[飞桨快速安装](https://www.paddlepaddle.org.cn/install/quick)。

2. 安装Paddlehub: `pip install paddlehub`

3. lda_news模型安装：`hub install lda_news`

4. 具体使用：
``` python
import paddlehub as hub

lda_news = hub.Module(name="lda_news")
jsd, hd = lda_news.cal_doc_distance(doc_text1="今天的天气如何，适合出去游玩吗", doc_text2="感觉今天的天气不错，可以出去玩一玩了")
# jsd = 0.003109, hd = 0.0573171

lda_sim = lda_news.cal_query_doc_similarity(query='百度搜索引擎', document='百度是全球最大的中文搜索引擎、致力于让网民更便捷地获取信息，找到所求。百度超过千亿的中文网页数据库，可以瞬间找到相关的搜索结果。')
# LDA similarity = 0.06826

results = lda_news.cal_doc_keywords_similarity('百度是全球最大的中文搜索引擎、致力于让网民更便捷地获取信息，找到所求。百度超过千亿的中文网页数据库，可以瞬间找到相关的搜索结果。')
# [{'word': '百度', 'similarity': 0.12943492762349573}, 
#  {'word': '信息', 'similarity': 0.06139783578769882}, 
#  {'word': '找到', 'similarity': 0.055296603463188265}, 
#  {'word': '搜索', 'similarity': 0.04270794098349327}, 
#  {'word': '全球', 'similarity': 0.03773627056367886}, 
#  {'word': '超过', 'similarity': 0.03478658388202199}, 
#  {'word': '相关', 'similarity': 0.026295857219683725}, 
#  {'word': '获取', 'similarity': 0.021313585287833996}, 
#  {'word': '中文', 'similarity': 0.020187103312009513}, 
#  {'word': '搜索引擎', 'similarity': 0.007092890537169911}]
```

更加具体的介绍和使用方法可以看这里：https://www.paddlepaddle.org.cn/hublist?filter=en_category&value=SemanticModel 


## 应用介绍
**Familia**目前包含的主题模型的对应论文介绍可以参考[相关论文][3]。

主题模型在工业界的应用范式可以抽象为两大类: 语义表示和语义匹配。

- **语义表示 (Semantic Representation)**
    对文档进行主题降维，获得文档的语义表示，这些语义表示可以应用于文本分类、文本内容分析、CTR预估等下游应用。

- **语义匹配 (Semantic Matching)**

	计算文本间的语义匹配度，我们提供两种文本类型的相似度计算方式:

	- 短文本-长文本相似度计算，使用场景包括文档关键词抽取、计算搜索引擎查询和网页的相似度等等。
	- 长文本-长文本相似度计算，使用场景包括计算两篇文档的相似度、计算用户画像和新闻的相似度等等。

更详细的内容及工业界应用案例可以参考[**Familia Wiki**][4] ，
如果想要对上述应用范式进行基于Web的可视化展示，可以参考[**Familia-Visualization**][12]。

## 代码编译
第三方依赖包括`gflags-2.0`，`glogs-0.3.4`，`protobuf-2.5.0`, 同时要求编译器支持C++11, `g++ >= 4.8`, 兼容Linux和Mac操作系统。
默认情况下执行以下脚本会自动获取依赖并安装。

	$ sh build.sh # 包含获取并安装第三方依赖的过程

## 模型下载

	$ cd model
	$ sh download_model.sh

* 关于模型的详细配置说明可以参考[模型说明][5]

我们会陆续开放不同领域的多种主题模型，来满足更多不同的场景需求。

## Demo
**Familia**自带的Demo包含以下功能：
-  **语义表示计算**
   利用主题模型对输入文档进行主题推断，以得到文档的主题降维表示。

-  **语义匹配计算**
   计算文本之间的相似度，包括短文本-长文本、长文本-长文本间的相似度计算。

-  **模型内容展现**
    对模型的主题词，近邻词进行展现，方便用户对模型的主题有直观的理解。

具体的Demo使用说明可以参考[使用文档][6]

## 注意事项

* 若出现找不到libglog.so, libgflags.so等动态库错误，请添加third\_party至环境变量的`LD_LIBRARY_PATH`中。

	`export LD_LIBRARY_PATH=./third_party/lib:$LD_LIBRARY_PATH`

* 代码中内置简易的FMM分词工具，只针对主题模型中出现的词表进行正向匹配。若对分词和语义准确度有更高要求，建议使用商用分词工具，并使用自定义词表的功能导入主题模型中的词表。

## 问题咨询

欢迎提交任何问题和Bug Report至[Github Issues][7]。
或者发送咨询邮件至{ familia } at baidu.com

## Docker

```
docker run -d \
    --name familia \
    -e MODEL_NAME=news \
    -p 5000:5000 \
    orctom/familia
```
MODEL_NAME can be one of `news`/`novel`/`webpage`/`webo`

### API

```
http://localhost:5000/swagger/
```

## Citation

The following article describes the Familia project and industrial cases powered by topic modeling. It bundles and translates the Chinese documentation of the website. We recommend citing this article as default.

Di Jiang, Yuanfeng Song, Rongzhong Lian, Siqi Bao, Jinhua Peng, Huang He, Hua Wu. 2018. [Familia: A Configurable Topic Modeling Framework for Industrial Text Engineering][8]. arXiv preprint arXiv:1808.03733.
	
	@article{jiang2018familia,
	  author = {Di Jiang and Yuanfeng Song and Rongzhong Lian and Siqi Bao and Jinhua Peng and Huang He and Hua Wu},
	  title = {{Familia: A Configurable Topic Modeling Framework for Industrial Text Engineering}},
	  journal = {arXiv preprint arXiv:1808.03733},
	  year = {2018}
	}
	
Further Reading: [Federated Topic Modeling][11]


## Copyright and License

Familia is provided under the [BSD-3-Clause License][9].

[1]:	http://travis-ci.org/baidu/Familia
[3]:	https://github.com/baidu/Familia/wiki/%E5%8F%82%E8%80%83%E6%96%87%E7%8C%AE
[4]:	https://github.com/baidu/Familia/wiki
[5]:	https://github.com/baidu/Familia/blob/master/model/README.md
[6]:	https://github.com/baidu/Familia/wiki/Demo%E4%BD%BF%E7%94%A8%E6%96%87%E6%A1%A3
[7]:	https://github.com/baidu/Familia/issues
[8]:	https://arxiv.org/abs/1808.03733v2
[9]:	LICENSE
[10]:   https://github.com/baidu/Familia/blob/master/README.EN.md
[11]:   https://github.com/baidu/Familia/blob/master/papers/FTM.pdf
[12]:   https://github.com/gmission/Familia-Visualization

[image-1]:	https://travis-ci.org/baidu/Familia.svg?branch=master
[image-2]:	https://img.shields.io/pypi/l/Django.svg


































- **libdivide** [📁](./libdivide) [🌐](https://github.com/GerHobbelt/libdivide)

# libdivide
[![Build Status](https://ci.appveyor.com/api/projects/status/github/ridiculousfish/libdivide?branch=master&svg=true)](https://ci.appveyor.com/project/kimwalisch/libdivide)
[![Github Releases](https://img.shields.io/github/release/ridiculousfish/libdivide.svg)](https://github.com/ridiculousfish/libdivide/releases)

```libdivide.h```  is a header-only C/C++ library for optimizing integer division.
Integer division is one of the slowest instructions on most CPUs e.g. on
current x64 CPUs a 64-bit integer division has a latency of up to 90 clock
cycles whereas a multiplication has a latency of only 3 clock cycles.
libdivide allows you to replace expensive integer divsion instructions by
a sequence of shift, add and multiply instructions that will calculate
the integer division much faster.

On current CPUs you can get a **speedup of up to 10x** for 64-bit integer division
and a speedup of up to to 5x for 32-bit integer division when using libdivide.
libdivide also supports [SSE2](https://en.wikipedia.org/wiki/SSE2),
[AVX2](https://en.wikipedia.org/wiki/Advanced_Vector_Extensions) and
[AVX512](https://en.wikipedia.org/wiki/Advanced_Vector_Extensions)
vector division which provides an even larger speedup. You can test how much
speedup you can achieve on your CPU using the [benchmark](#benchmark-program)
program.

libdivide is compatible with 8-bit microcontrollers, such as the AVR series: [the CI build includes a AtMega2560 target](test/avr/readme.md). Since low end hardware such as this often do not include a hardware divider, libdivide is particulary useful. In addition to the runtime [C](https://github.com/ridiculousfish/libdivide/blob/master/doc/C-API.md) & [C++](https://github.com/ridiculousfish/libdivide/blob/master/doc/CPP-API.md) APIs, a set of [predefined macros](constant_fast_div.h) and [templates](constant_fast_div.hpp) is included to speed up division by 16-bit constants: division by a 16-bit constant is [not optimized by avr-gcc on 8-bit systems](https://stackoverflow.com/questions/47994933/why-doesnt-gcc-or-clang-on-arm-use-division-by-invariant-integers-using-multip). 

See https://libdivide.com for more information on libdivide.

# C++ example

The first code snippet divides all integers in a vector using integer division.
This is slow as integer division is at least one order of magnitude slower than
any other integer arithmetic operation on current CPUs.

```C++
void divide(std::vector<int64_t>& vect, int64_t divisor)
{
    // Slow, uses integer division
    for (auto& n : vect)
        n /= divisor;
}
```

The second code snippet runs much faster, it uses libdivide to compute the
integer division using a sequence of shift, add and multiply instructions hence
avoiding the slow integer divison operation.

```C++
#include "libdivide.h"

void divide(std::vector<int64_t>& vect, int64_t divisor)
{
    libdivide::divider<int64_t> fast_d(divisor);

    // Fast, computes division using libdivide
    for (auto& n : vect)
        n /= fast_d;
}
```

Generally libdivide will give at significant speedup if:

* The divisor is only known at runtime
* The divisor is reused multiple times e.g. in a loop

# C example

You first need to generate a libdivide divider using one of the ```libdivide_*_gen``` functions (```*```:&nbsp;```s32```,&nbsp;```u32```,&nbsp;```s64```,&nbsp;```u64```)
which can then be used to compute the actual integer division using the
corresponding ```libdivide_*_do``` function.

```C
#include "libdivide.h"

void divide(int64_t *array, size_t size, int64_t divisor)
{
    struct libdivide_s64_t fast_d = libdivide_s64_gen(divisor);

    // Fast, computes division using libdivide
    for (size_t i = 0; i < size; i++)
        array[i] = libdivide_s64_do(array[i], &fast_d);
}
```

# API reference

* [C API](https://github.com/ridiculousfish/libdivide/blob/master/doc/C-API.md)
* [C++ API](https://github.com/ridiculousfish/libdivide/blob/master/doc/CPP-API.md)
* [Macro Invariant Division](constant_fast_div.h)
* [Template Based Invariant Division](constant_fast_div.hpp)

# Branchfull vs branchfree

The default libdivide divider makes use of
[branches](https://en.wikipedia.org/wiki/Branch_(computer_science)) to compute the integer
division. When the same divider is used inside a hot loop as in the C++ example section the
CPU will accurately predict the branches and there will be no performance slowdown. Often
the compiler is even able to move the branches outside the body of the loop hence
completely eliminating the branches, this is called loop-invariant code motion.

libdivide also has a branchfree divider type which computes the integer division without
using any branch instructions. The branchfree divider generally uses a few more instructions
than the default branchfull divider. The main use case for the branchfree divider is when
you have an array of different divisors and you need to iterate over the divisors. In this
case the default branchfull divider would exhibit poor performance as the CPU won't be
able to correctly predict the branches.

```C++
#include "libdivide.h"

// 64-bit branchfree divider type
using branchfree_t = libdivide::branchfree_divider<uint64_t>;

uint64_t divide(uint64_t x, std::vector<branchfree_t>& vect)
{
    uint64_t sum = 0;

    for (auto& fast_d : vect)
        sum += x / fast_d;

    return sum;
}
```

Caveats of branchfree divider:

* Unsigned branchfree divider cannot be ```1```
* Faster for unsigned types than for signed types

# Vector division

libdivide supports [SSE2](https://en.wikipedia.org/wiki/SSE2),
[AVX2](https://en.wikipedia.org/wiki/Advanced_Vector_Extensions) and
[AVX512](https://en.wikipedia.org/wiki/Advanced_Vector_Extensions)
vector division on x86 and x64 CPUs. In the example below we divide the packed 32-bit
integers inside an AVX512 vector using libdivide. libdivide supports 32-bit and 64-bit
vector division for both signed and unsigned integers.

```C++
#include "libdivide.h"

void divide(std::vector<__m512i>& vect, uint32_t divisor)
{
    libdivide::divider<uint32_t> fast_d(divisor);

    // AVX512 vector division
    for (auto& n : vect)
        n /= fast_d;
}
```

Note that you need to define one of macros below to enable vector division:

* ```LIBDIVIDE_SSE2```
* ```LIBDIVIDE_AVX2```
* ```LIBDIVIDE_AVX512```
* ```LIBDIVIDE_NEON```

# Performance tips

* If possible use unsigned integer types because libdivide's unsigned division is measurably
  faster than its signed division. This is especially true for the branchfree divider.
* Try both the default branchfull divider and the branchfree divider in your program and
  choose the one that performs best. The branchfree divider is more likely to get auto
  vectorized by the compiler (if you compile with e.g. ```-march=native```). But don't forget
  that the unsigned branchfree divider cannot be 1.
* Vector division is much faster for 32-bit than for 64-bit. This is because there are
  currently no vector multiplication instructions on x86 to efficiently calculate
  64-bit * 64-bit to 128-bit. 

# Build instructions

libdivide has one test program and two benchmark programs which can be built using cmake and
a recent C++ compiler that supports C++11 or later. Optionally ```libdivide.h``` can also be
installed to ```/usr/local/include```.

```bash
cmake .
make -j
sudo make install
```

# Tester program

You can pass the **tester** program one or more of the following arguments: ```u32```,
```s32```, ```u64```, ```s64``` to test the four cases (signed, unsigned, 32-bit, or 64-bit), or
run it with no arguments to test all four. The tester will verify the correctness of libdivide
via a set of randomly chosen numerators and denominators, by comparing the result of libdivide's
division to hardware division. It will stop with an error message as soon as it finds a
discrepancy.

# Benchmark program

You can pass the **benchmark** program one or more of the following arguments: ```u16```, ```s16```, ```u32```,
```s32```, ```u64```, ```s64``` to compare libdivide's speed against hardware division.
**benchmark** tests a simple function that inputs an array of random numerators and a single
divisor, and returns the sum of their quotients. It tests this using both hardware division, and
the various division approaches supported by libdivide, including vector division.

It will output data like this:

```bash
 #   system  scalar  scl_bf  vector  vec_bf   gener   algo
 1   9.684   0.792   0.783   0.426   0.426    1.346   0
 2   9.078   0.781   1.609   0.426   1.529    1.346   0
 3   9.078   1.355   1.609   1.334   1.531   29.045   1
 4   9.076   0.787   1.609   0.426   1.529    1.346   0
 5   9.074   1.349   1.609   1.334   1.531   29.045   1
 6   9.078   1.349   1.609   1.334   1.531   29.045   1
...
```

It will keep going as long as you let it, so it's best to stop it when you are happy with the
denominators tested. These columns have the following significance. All times are in
nanoseconds, lower is better.

```
     #:  The divisor that is tested
system:  Hardware divide time
scalar:  libdivide time, using scalar division
scl_bf:  libdivide time, using scalar branchfree division
vector:  libdivide time, using vector division
vec_bf:  libdivide time, using vector branchfree division
 gener:  Time taken to generate the divider struct
  algo:  The algorithm used.
```

The **benchmark** program will also verify that each function returns the same value,
so benchmark is valuable for its verification as well.

# Contributing

Although there are no individual unit tests, the supplied ```cmake``` builds do include several safety nets:

* They compile with:
  * All warnings on and;
  * Warnings as errors
* The CI build will build and run with sanitizers on ; these are available as part of the cmake build: ```-DCMAKE_BUILD_TYPE=Sanitize```
* The ```cmake``` and CI builds will compile and run both ```C``` and ```C++``` test programs.

Before sending in patches, build and run at least the ```tester``` and ```benchmark``` using the supplied ```cmake``` scripts on at least ```MSVC``` and ```GCC``` (or ```Clang```).

### Happy hacking!


































- **libpng** [📁](../../thirdparty/libpng) [🌐](https://github.com/GerHobbelt/libpng)

README for libpng version 1.6.40.git
====================================

See the note about version numbers near the top of `png.h`.
See `INSTALL` for instructions on how to install libpng.

Libpng comes in several distribution formats.  Get `libpng-*.tar.gz`
or `libpng-*.tar.xz` if you want UNIX-style line endings in the text
files, or `lpng*.7z` or `lpng*.zip` if you want DOS-style line endings.

For a detailed description on using libpng, read `libpng-manual.txt`.
For examples of libpng in a program, see `example.c` and `pngtest.c`.
For usage information and restrictions (what little they are) on libpng,
see `png.h`.  For a description on using zlib (the compression library
used by libpng) and zlib's restrictions, see `zlib.h`.

You should use zlib 1.0.4 or later to run this, but it _may_ work with
versions as old as zlib 0.95.  Even so, there are bugs in older zlib
versions which can cause the output of invalid compression streams for
some images.

You should also note that zlib is a compression library that is useful
for more things than just PNG files.  You can use zlib as a drop-in
replacement for `fread()` and `fwrite()`, if you are so inclined.

zlib should be available at the same place that libpng is, or at
https://zlib.net .

You may also want a copy of the PNG specification.  It is available
as an RFC, a W3C Recommendation, and an ISO/IEC Standard.  You can find
these at http://www.libpng.org/pub/png/pngdocs.html .

This code is currently being archived at https://libpng.sourceforge.io
in the download area, and at http://libpng.download/src .

This release, based in a large way on Glenn's, Guy's and Andreas'
earlier work, was created and will be supported by myself and the PNG
development group.

Send comments, corrections and commendations to `png-mng-implement`
at `lists.sourceforge.net`.  (Subscription is required; visit
https://lists.sourceforge.net/lists/listinfo/png-mng-implement
to subscribe.)

Send general questions about the PNG specification to `png-mng-misc`
at `lists.sourceforge.net`.  (Subscription is required; visit
https://lists.sourceforge.net/lists/listinfo/png-mng-misc
to subscribe.)

Historical notes
----------------

The libpng library has been in extensive use and testing since mid-1995.
Version 0.89, published a year later, was the first official release.
By late 1997, it had finally gotten to the stage where there hadn't
been significant changes to the API in some time, and people have a bad
feeling about libraries with versions below 1.0.  Version 1.0.0 was
released in March 1998.

Note that some of the changes to the `png_info` structure render this
version of the library binary incompatible with libpng-0.89 or
earlier versions if you are using a shared library.  The type of the
`filler` parameter for `png_set_filler()` has changed from `png_byte`
to `png_uint_32`, which will affect shared-library applications that
use this function.

To avoid problems with changes to the internals of the `info_struct`,
new APIs have been made available in 0.95 to avoid direct application
access to `info_ptr`.  These functions are the `png_set_<chunk>` and
`png_get_<chunk>` functions.  These functions should be used when
accessing/storing the `info_struct` data, rather than manipulating it
directly, to avoid such problems in the future.

It is important to note that the APIs did not make current programs
that access the info struct directly incompatible with the new
library, through libpng-1.2.x.  In libpng-1.4.x, which was meant to
be a transitional release, members of the `png_struct` and the
`info_struct` can still be accessed, but the compiler will issue a
warning about deprecated usage.  Since libpng-1.5.0, direct access
to these structs is not allowed, and the definitions of the structs
reside in private `pngstruct.h` and `pnginfo.h` header files that are
not accessible to applications.  It is strongly suggested that new
programs use the new APIs (as shown in `example.c` and `pngtest.c`),
and older programs be converted to the new format, to facilitate
upgrades in the future.

The additions since 0.89 include the ability to read from a PNG stream
which has had some (or all) of the signature bytes read by the calling
application.  This also allows the reading of embedded PNG streams that
do not have the PNG file signature.  As well, it is now possible to set
the library action on the detection of chunk CRC errors.  It is possible
to set different actions based on whether the CRC error occurred in a
critical or an ancillary chunk.

The additions since 0.90 include the ability to compile libpng as a
Windows DLL, and new APIs for accessing data in the `info_struct`.
Experimental functions included the ability to set weighting and cost
factors for row filter selection, direct reads of integers from buffers
on big-endian processors that support misaligned data access, faster
methods of doing alpha composition, and more accurate 16-to-8 bit color
conversion.  Some of these experimental functions, such as the weighted
filter heuristics, have since been removed.

Files included in this distribution
-----------------------------------

    ANNOUNCE      =>  Announcement of this version, with recent changes
    AUTHORS       =>  List of contributing authors
    CHANGES       =>  Description of changes between libpng versions
    INSTALL       =>  Instructions to install libpng
    LICENSE       =>  License to use and redistribute libpng
    README        =>  This file
    TODO          =>  Things not implemented in the current library
    TRADEMARK     =>  Trademark information
    example.c     =>  Example code for using libpng functions
    libpng.3      =>  Manual page for libpng (includes libpng-manual.txt)
    libpng-manual.txt  =>  Description of libpng and its functions
    libpngpf.3    =>  Manual page for libpng's private functions (deprecated)
    png.5         =>  Manual page for the PNG format
    png.c         =>  Basic interface functions common to library
    png.h         =>  Library function and interface declarations (public)
    pngpriv.h     =>  Library function and interface declarations (private)
    pngconf.h     =>  System specific library configuration (public)
    pngstruct.h   =>  png_struct declaration (private)
    pnginfo.h     =>  png_info struct declaration (private)
    pngdebug.h    =>  debugging macros (private)
    pngerror.c    =>  Error/warning message I/O functions
    pngget.c      =>  Functions for retrieving info from struct
    pngmem.c      =>  Memory handling functions
    pngbar.png    =>  PNG logo, 88x31
    pngnow.png    =>  PNG logo, 98x31
    pngpread.c    =>  Progressive reading functions
    pngread.c     =>  Read data/helper high-level functions
    pngrio.c      =>  Lowest-level data read I/O functions
    pngrtran.c    =>  Read data transformation functions
    pngrutil.c    =>  Read data utility functions
    pngset.c      =>  Functions for storing data into the info_struct
    pngtest.c     =>  Library test program
    pngtest.png   =>  Library test sample image
    pngtrans.c    =>  Common data transformation functions
    pngwio.c      =>  Lowest-level write I/O functions
    pngwrite.c    =>  High-level write functions
    pngwtran.c    =>  Write data transformations
    pngwutil.c    =>  Write utility functions
    arm/          =>  Optimized code for the ARM platform
    intel/        =>  Optimized code for the INTEL-SSE2 platform
    mips/         =>  Optimized code for the MIPS platform
    powerpc/      =>  Optimized code for the PowerPC platform
    ci/           =>  Scripts for continuous integration
    contrib/      =>  External contributions
        arm-neon/     =>  Optimized code for the ARM-NEON platform
        mips-msa/     =>  Optimized code for the MIPS-MSA platform
        powerpc-vsx/  =>  Optimized code for the POWERPC-VSX platform
        examples/     =>  Examples of libpng usage
        gregbook/     =>  Source code for PNG reading and writing, from
                          "PNG: The Definitive Guide" by Greg Roelofs,
                          O'Reilly, 1999
        libtests/     =>  Test programs
        oss-fuzz/     =>  Files used by the OSS-Fuzz project for fuzz-testing
                          libpng
        pngminim/     =>  Minimal decoder, encoder, and progressive decoder
                          programs demonstrating the use of pngusr.dfa
        pngminus/     =>  Simple pnm2png and png2pnm programs
        pngsuite/     =>  Test images
        testpngs/     =>  Test images
        tools/        =>  Various tools
        visupng/      =>  VisualPng, a Windows viewer for PNG images
    projects/     =>  Project files and workspaces for various IDEs
        owatcom/      =>  OpenWatcom project
        visualc71/    =>  Microsoft Visual C++ 7.1 workspace
        vstudio/      =>  Microsoft Visual Studio workspace
    scripts/      =>  Scripts and makefiles for building libpng
                      (see scripts/README.txt for the complete list)
    tests/        =>  Test scripts

Good luck, and happy coding!

 * Cosmin Truta (current maintainer, since 2018)
 * Glenn Randers-Pehrson (former maintainer, 1998-2018)
 * Andreas Eric Dilger (former maintainer, 1996-1997)
 * Guy Eric Schalnat (original author and former maintainer, 1995-1996)
   (formerly of Group 42, Inc.)


































- **pmt-png-tools** [📁](./pmt-png-tools) [🌐](https://github.com/GerHobbelt/pmt)

/*
  This is the master branch of the "pmt" tree.
  Individual projects are in separate branches,
  e.g., pngcrush is in the "pngcrush" branch,
        pngmeta is in the "pngmeta" branch, and
        pnguri is in the "pnguri" branch.
*/


































- **sqlite_fts_tokenizer_chinese_simple** [📁](./sqlite_fts_tokenizer_chinese_simple) [🌐](https://github.com/GerHobbelt/simple)

[![Downloads](https://img.shields.io/github/downloads/wangfenjin/simple/total)](https://img.shields.io/github/downloads/wangfenjin/simple/total)
[![build](https://github.com/wangfenjin/simple/workflows/CI/badge.svg)](https://github.com/wangfenjin/simple/actions?query=workflow%3ACI)
[![codecov](https://codecov.io/gh/wangfenjin/simple/branch/master/graph/badge.svg?token=8SHLFZ3RB4)](https://codecov.io/gh/wangfenjin/simple)
[![CodeFactor](https://www.codefactor.io/repository/github/wangfenjin/simple/badge)](https://www.codefactor.io/repository/github/wangfenjin/simple)
[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://github.com/wangfenjin/simple/blob/master/LICENSE)

# Simple tokenizer

simple 是一个支持中文和拼音的 [sqlite3 fts5](https://www.sqlite.org/fts5.html) 拓展。它完整提供了 [微信移动端的全文检索多音字问题解决方案](https://cloud.tencent.com/developer/article/1198371) 一文中的方案四，非常简单和高效地支持中文及拼音的搜索。

实现相关介绍：https://www.wangfenjin.com/posts/simple-tokenizer/

在此基础上，我们还支持通过 [cppjieba](https://github.com/yanyiwu/cppjieba) 实现更精准的词组匹配，介绍文章见 https://www.wangfenjin.com/posts/simple-jieba-tokenizer/

## 用法

### 代码使用


* 下载已经编译好的插件：https://github.com/wangfenjin/simple/releases 参考 examples 目录，目前已经有 c++, python, go 和 node-sqlite3 的例子。
* iOS 可以参考这个例子 https://github.com/wangfenjin/simple/pull/73 和 [@hxicoder](https://github.com/hxicoder) 提供的 [demo](https://github.com/hxicoder/DBDemo) .
* 在 Rust 中使用的例子 https://github.com/wangfenjin/simple/issues/89 https://github.com/fundon/tiny-docs-se

### 命令行使用

首先需要确认你用到的 sqlite 版本支持 fts5 拓展，确认方法是：
```sql
select fts5(?1);
```
然后就可以使用了，具体的例子可以参考 [example.sql](./example.sql) 和 [cpp](https://github.com/wangfenjin/simple/blob/master/examples/cpp/main.cc) 

```
$ ./sqlite3
SQLite version 3.32.3 2020-06-18 14:00:33
Enter ".help" for usage hints.
Connected to a transient in-memory database.
Use ".open FILENAME" to reopen on a persistent database.
sqlite> .load libsimple
sqlite> CREATE VIRTUAL TABLE t1 USING fts5(text, tokenize = 'simple');
sqlite> INSERT INTO t1 VALUES ('中华人民共和国国歌');
sqlite> select simple_highlight(t1, 0, '[', ']') as text from t1 where text match simple_query('中华国歌');
[中华]人民共和[国国歌]
sqlite> select simple_highlight(t1, 0, '[', ']') as text from t1 where text match jieba_query('中华国歌');
[中华]人民共和国[国歌]
sqlite> select simple_highlight(t1, 0, '[', ']') as text from t1 where text match simple_query('中华人民共和国');
[中华人民共和国国]歌
sqlite> select simple_highlight(t1, 0, '[', ']') as text from t1 where text match jieba_query('中华人民共和国');
[中华人民共和国]国歌
```

## 功能

1. simple tokenizer 支持中文和拼音的分词，并且可通过开关控制是否需要支持拼音
2. simple_query() 函数实现自动组装 match query 的功能，用户不用学习 fts5 query 的语法
3. simple_highlight() 实现连续高亮 match 的词汇，与 sqlite 自带的 highlight 类似，但是 simple_highlight 实现了连续 match 的词汇分到同一组的逻辑，理论上用户更需要这样
4. simple_highlight_pos() 实现返回 match 的词汇位置，用户可以自行决定怎么使用
5. simple_snippet() 实现截取 match 片段的功能，与 sqlite 自带的 snippet 功能类似，同样是增强连续 match 的词汇分到同一组的逻辑
6. jieba_query() 实现jieba分词的效果，在索引不变的情况下，可以实现更精准的匹配。可以通过 `-DSIMPLE_WITH_JIEBA=OFF ` 关掉结巴分词的功能 [#35](https://github.com/wangfenjin/simple/pull/35)
7. jieba_dict() 指定 dict 的目录，只需要调用一次，需要在调用 jieba_query() 之前指定。

## 开发

### 编译相关

使用支持 c++14 以上的编译器编译，直接在根目录 ./build-and-run 就会编译所有需要的文件并运行测试。编译输出见 output 目录

也可以手动 cmake:
```shell
mkdir build; cd build
cmake ..
make -j 12
make install
```

支持 iOS 编译：
```
./build-ios.sh
```

### 代码
- `src/entry` 入口文件，注册 sqlite tokenizer 和函数
- `src/simple_tokenizer` 分词器实现
- `src/simple_highlight` 高亮函数，基于内置的高亮函数改的，让命中的相邻单词连续高亮
- `src/pinyin` 中文转拼音以及拼音拆 query 的实现

## TODO

- [x] 添加 CI/CD 
- [x] 添加使用的例子，参见 [cpp](https://github.com/wangfenjin/simple/blob/master/examples/cpp/main.cc) [python3](https://github.com/wangfenjin/simple/blob/master/examples/python3/db_connector.py)
- [x] 部分参数可配，比如拼音文件的路径(已经把文件打包到 so 中)
- [x] 减少依赖，减小 so 的大小
- [x] 给出性能数据：加载扩展时间2ms内；第一次使用拼音功能需要加载拼音文件，大概 500ms；第一次使用结巴分词功能需要加载结巴分词文件，大概 4s。

## Star History

[![Star History Chart](https://api.star-history.com/svg?repos=wangfenjin/simple&type=Date)](https://star-history.com/#wangfenjin/simple&Date)



































- **XMP-Toolkit-SDK** [📁](./XMP-Toolkit-SDK) [🌐](https://github.com/GerHobbelt/XMP-Toolkit-SDK)

# XMP-Toolkit-SDK fork used by [Diffractor](https://diffractor.com/)

Few changes from the original:
- added vcxproj file 
- POPM (rating) and TPE2 (albumArtist) reconciliations for MP3
- windows tag support and other fixes from chebum
- tweaks for C++ 17
- WEBP support from [Exempi](https://libopenraw.freedesktop.org/exempi/)

# XMP-Toolkit-SDK

The XMP Toolkit allows you to integrate XMP functionality into your product or solution. It supports Macintosh, Windows, as well as UNIX and comes with samples, documentation, source code and scripts to generate project files. The XMP Toolkit is available under the BSD license. The specification is provided under the [XMP Specification Public Patent License](https://wwwimages2.adobe.com/content/dam/acom/en/devnet/xmp/pdfs/cs6/xmp_public_patent_license.pdf)


## SDK components

The XMP Toolkit SDK contains two libraries, XMPCore and XMPFiles. XMPCore and XMPFiles are provided as C++ implementations.


### XMPCore

This library supplies an API for parsing, manipulating, and serializing metadata, according to the XMP data model and regardless of the file format of the data it describes.


### XMPFiles

This library supplies an API for locating, adding, or updating the XMP metadata in a file. The API allows you to retrieve the entire XMP Packet, which you can then pass to the XMPCore component in order to manipulate the individual XMP properties.

*It also includes a plug-in SDK that allows you to create an XMPFiles Plug-in that handles metadata for additional file formats, or replaces built-in format handlers with custom ones.*


## XMP Toolkit SDK Contents

This git repo contains the following folders under the root folder:

Directory | Details 
------------ | -------------
/ 				| At the root level, the license agreement (BSD_License.txt) and this overview (XMP-Toolkit-SDK-Overview.pdf).
build/ 			| Contains Batch file, shell scripts, Makefile and CMake scripts to be used to create XMP Toolkit SDK project files on the supported platforms. Follow the instructions in README.txt to create the projects.
docs/ 			| The three-part XMP Specification, the XMP Toolkit SDK Programmer’s Guide, the API reference documentation (API/index.html) and the XMPFiles plug-in SDK documentation.
public/include/ | The header files and glue code that clients of the XMP Toolkit SDK must include.
samples/ 		| Sample source code and CMake scripts for building sample projects, with the necessary resources to run the sample code. See ‘‘Sample code and tools’’ below.
source/ 		| The common source code that is used by both components of the XMP Toolkit SDK.
XMPCore/ 		| The source code for XMPCore library.
XMPFiles/ 		| The source code for XMPFiles library.
third-party/ <br>&nbsp;&nbsp;&nbsp;expat/<br>&nbsp;&nbsp;&nbsp;zlib/<br>&nbsp;&nbsp;&nbsp;zuid/	| Placeholders for third party source files which are needed for the XMP Toolkit SDK, including ReadMe.txt files with information on how to obtain and install the tools. MD5 source code, needed by both components for MD5 hash computation, is included.
tools/ 			| Placeholder for downloading and placing CMake tool
XMPFilesPlugins/| The header files and glue code of the XMPFiles plug-in SDK and a sample plug-in.


## How to Build and Use

XMP Toolkit SDK provides build script to ease the process. This repository contains everything needed to build SDK libraries on Mac OS®, Windows®, UNIX®/Linux®, iOS and Android. For detailed build steps , refer the [Programmer's Guide](https://github.com/adobe/XMP-Toolkit-SDK/blob/master/docs/XMPProgrammersGuide.pdf)


## Documentation

See extensive [API documentation](https://github.com/adobe/XMP-Toolkit-SDK/blob/master/docs/XMPProgrammersGuide.pdf) where a complete API Reference is available.

The XMP Specification, available from [Adobe Developer Center (XMP)](http://adobe.com/devnet/xmp/), provides a complete formal
specification for XMP. Before working with the XMP Toolkit SDK, you must be familiar with, at a minimum,
the XMP Data Model.

The specification has three parts:
- Part 1, Data Model, Serialization, and Core Properties covers the basic metadata representation model
that is the foundation of the XMP standard format. The Data Model prescribes how XMP metadata can
be organized; it is independent of file format or specific usage. The Serialization Model prescribes how
the Data Model is represented in XML, specifically RDF.
This document provides all the details a programmer would need to implement a metadata
manipulation system such as the XMP Toolkit SDK (which is available from Adobe).

- Part 2, Additional Properties, provides detailed property lists and descriptions for standard XMP
metadata schemas; these include general-purpose schemas such as Dublin Core, and special-purpose
schemas for Adobe applications such as Photoshop®. It also provides information on extending
existing schemas and creating new schemas.

- Part 3, Storage in Files, provides information about how serialized XMP metadata is packaged into XMP
Packets and embedded in different file formats. It includes information about how XMP relates to and
incorporates other metadata formats, and how to reconcile values that are represented in multiple
metadata formats.


## Contributing

Contributions are welcomed! Read the [Contributing Guide](https://github.com/adobe/XMP-Toolkit-SDK/blob/master/CONTRIBUTING.md) for more information.


## Licensing

This project is BSD licensed. See [LICENSE](https://github.com/adobe/XMP-Toolkit-SDK/blob/main/LICENSE) for more information.


## Report Issues/Bugs

You can report the issues in the issues section of the github repo.


































- **zotero** [📁](./zotero) [🌐](https://github.com/GerHobbelt/zotero)

Zotero
======
[![CI](https://github.com/zotero/zotero/actions/workflows/ci.yml/badge.svg)](https://github.com/zotero/zotero/actions/workflows/ci.yml)

[Zotero](https://www.zotero.org/) is a free, easy-to-use tool to help you collect, organize, cite, and share your research sources.

Please post feature requests or bug reports to the [Zotero Forums](https://forums.zotero.org/). If you're having trouble with Zotero, see [Getting Help](https://www.zotero.org/support/getting_help).

For more information on how to use this source code, see the [Zotero wiki](https://www.zotero.org/support/dev/source_code).
































