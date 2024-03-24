#! /bin/bash
#
# Assumes a git-on-windows with robocopy, bash, etc. dev env available
#

pushd $( dirname $0 )      > /dev/null
cd ..
#pwd

mkdir -p Qiqqa/MuPDF

cat > utils/tmp.lst  <<EOF

# 1D-RGB-color-gradient
# 2D-color-gradient-or-Procedural-texture
# A-MNS_TemplateMatching
# ADE-graph-management
# AFLplusplus
# ApprovalTestsCpp
# ArborX
# BBHash
# BCF-cuckoo-index
# BaseMatrixOps
# Bi-Sent2Vec
# BitFunnel
# BlingFire
# BoxFort
# CHM-lib
# CImg
# CLBlast
# CLBlast-database
# CLTune
# CRFpp
# CRFsuite-extended
# CRoaring
# CTCWordBeamSearch
# CTPL-Thread-Pool
# CacheLib
# Capture2Text
# Clipper2
# ColorSpace
# CppNumericalSolvers
# Criterion
# CryptSync
# CurvatureFilter
# CxImage
# Cysboard
# DBoW2
# DCF-cuckoo-index
# DGM-CRF
# DiskANN
# ECMA262
# EigenRand
# EtwExplorer
# Extensible-Storage-Engine
# FFmpeg
# FIt-SNE
# FastGlobbing
# FreeFileSync
# GMM-HMM-kMeans
# GMMreg
# GQ-gumbo-css-selectors
# GSL
# GoldFish-CBOR
# GraphicsMagick
# HDiffPatch
# ITK
# IconFontCppHeaders
# IdGenerator
# ImageMagick
# Imath
# Ipopt
# JabRef-Browser-Extension
# JabRef-abbreviations
# JamSpell
# LBFGS-Lite
# LDCF-hash
# LLhttp-parser
# LSWMS
# LeptonicaDocsSite
# LightGBM
# LightLDA
# Lightning.NET
# MITIE-nlp
# MNN
# MariGold.OpenXHTML
# MicroPather
# NSIS-OBSInstallerUtils
# NSISDotNetChecker
# NSISFileCheck
# NSISMultiUser
# NanoLog
# NiuTrans.NMT
# OfficeIMO
# Open-XML-SDK
# OpenBLAS
# OpenCL-CTS
OpenCL-Headers
# OpenCL-SDK
# OpenColorIO
# OpenEXR
# OpenFST
# OpenFST-utils
# OptimizationTemplateLibrary
# PEGTL
# PGM-index
# Paddle-Lite
# PaddleClas
# PaddleDetection
# PaddleNLP
# PaddleOCR
# PaddlePaddle
# PhotonLibOS
# Pillow
# PlatformFolders
# QCBOR
# RE-flex
# RNGSobol
# RRD
# RRPN
# RapidFuzz
# RuntimeCompiledCPlusPlus
# RxCpp
# SQLiteCpp
# SQLiteHistograms
# ScriptX
# Sealighter
# ShapeCrawler
# Sherwood
# Signals
# SilkETW
# SipHash
# Sophus
# StarSpace
# SymSpell
# TelemetrySourcerer
# ThreadPool
# TraceETW
# UIforETW
# URI-Encode-C
# URL-Detector
# UnofficialLeptDocs
# VQMT
# VSNASM
# VTK
# Verify
# VisualScriptEngine
# Win32_read_directory_changes
# Win32_read_directory_changes_IOCP
# WinHttpPAL
# Windows10EtwEvents
# XMP-Toolkit-SDK
# Xoshiro-cpp
# YACLib
# ZLMediaKit
# abseil-cpp
# adaptiveqf
# agg
# aho-corasick
# aho_corasick
# annoy
# arangodb
# archive-hocr-tools
# armadillo
# arrayfire
# asyncplusplus
# asynqro
# autodiff
# avro
# awesome-c
# b2xtranslator
# basez
bbe
# bebop
bhtsne--Barnes-Hut-t-SNE
# bibtex-robust-decoder
# bibtool
# binary_search
# binlog
bitsery
# blaze
# blitsort
# bolt
# boost-url
# boringssl
# breakpad
# c-blosc2
# cachelot
# caches
# caffe
# cairo
# cairo-demos
# calibre
# capnproto
# capture-thread
# catboost
# cctz
# ccv-nnc
# cdc-file-transfer
# cef-pdf
# cereal
# ceres-solver
# cfgpath
# chibi-scheme
# chromium-snss-parse
# citation-abbreviations
# citation-journals
# citation-styles
# citeproc-js
# civetweb
# cjose
# clBLAS
# cld1-language-detect
# cld2-language-detect
# cld3-language-detect
# cmph-hasher
# color-util
# colormap-shaders
# comdb2-bdb
# compact_enc_det
# completesearch
# concurrencpp
# concurrentqueue
# coost
# cpp-btree
# cpp-httplib
# cpp-ipc
# cpp-netlib
cpp-terminal
# cpp_rest_sdk
# cppdap
# cppflow
# cppjieba
# cpplocate
# cpptoml
# cppzmq
cpuinfo
# cpython
# cqf
# cr
# crc32c
# createprocess-windows
# crfsuite
# crumsort
# csv-parser
# csvquote
# csync2
# ctsa
# cuckoo-index
# cuckoofilter
# curl-impersonate
# curl-www
# cvmatio
# cxxopts
# cxxtest
cxxtest_catch_2_gtest
# datamash
# date
# datetimepp
# dateutils
# dbscan
debugbreak
# decision-tree
delegate
# density
# densityxx
# detect-character-encoding
# diffutils
djvulibre
# dlib
# doctest
# docxBox
# doh
# doxa
# doxygen-awesome-css
# drogon
# dtl-diff-template-library
# dtoa-benchmark
# duckdb
# dynet
# easyexif
# easyloggingpp
# ecal
# edit-distance
# efsw
# emphf-hash
# enca
# enkiTS-TaskScheduler
# ensmallen
# eventpp
# everything-curl
# ex-leptonica-freetype-harfbuzz
# exiv2
# expected-lite
exprtk
# eytzinger
# faiss
# falconn
# farmhash
# farver-OKlab
# fast-lzma2
# fastBPE
# fastPRNG
# fastText
# fast_float
# fast_pfor
# fastapprox
# fastfilter_cpp
# fastgron
# fatal
# faup
# ffht
# fftw3
# fifo_map
# figtree
file
# filecopyex3
filesystem
# flat.hpp
# flat_hash_map
# flinng
# flip
# fluent-bit
# fluxsort
# fmem
# fmemopen_windows
# fmtlog
fnmatch
# folly
fontconfig
# fontview
# fpng
# fribidi
# friso
# frozen
# fswatch
# fxt
# g3log
gcem
# gdbm
# gegl
# gencolormap
# genieclust
getopt
# gettext
gibbs-lda
glfw
# glib2
# glyph_name
# gmic
# gmic-community
# gmt
# gnuplot
# gnuplot-palettes
# gnuplot_i
# google-diff-match-patch
# google-marl
# gram_savitzky_golay
# graph-coloring
# graphit
# grok-jpeg2000
# groonga
# gtn
# guetzli
# guile
# gumbo-libxml
gumbo-query
# h2o-server
# h5cpp
# harbour-core
# hdbscan
# hdbscan-cpp
# hedley
# highwayhash
# hikyuu
# hmm-scalable
# hmm-stoch
# hnswlib
# hocr-fileformat
# hocr-spec
# hocr-tools
# honggfuzz
# hopscotch-map
# horsejs
# hsluv-c
# hsluv-color-gradient
# html2openxml
# htmlstreamparser
# http-parser
# hunspell
# hunspell-dictionaries
# hunspell-hyphen
# hyperscan
# hypertextcpp
# iODBC
# iceberghashtable
# iceoryx
id3-tagparser
# ifopt
imagedistance
# indicators
# infoware
# ion-c
# ipa-dict
# iresearch
# itcl
# itpp
# ivf-hnsw
# jasper
# javascript-serialization-benchmark
# jbig2enc
# jemalloc
# jerryscript
# jimtcl
# jq
# json
# json-jansson
# jsoncons
# jsoncpp
# jtc
# kahypar
# kalman-cpp
# kann
# kfr
# kgraph
# kiwi
# klib
# koan
# krabsETW
# lapack
# lda
# lda-3-variants
# lda-Familia
# lda-bigartm
# leptonica-hillshade
# lerc
# lexbor
# libCRCpp
# libCZMQ
# libaco
# libahocorasick
# libalg
# libaom
libassert
# libavif
# libbloom
# libbloomfilters
# libcbor
# libchaos
# libchardet
# libchopshop
# libclip
# libclipboard
# libcmime
# libcnl
# libconfig
# libcopp
# libcppjieba
# libcpuid
# libcsp
libcsv2
# libcuckoo
# libcyaml
# libde265
# libdeflate
# libdi-dependency-injection
libdiagnostics
# libdip
# libdist
# libdivide
# libdivsufsort
# libdtm
libeigen
# libevent
# libevt
libexpat
# libfann
# libffi
# libfolia
# libfort
# libfyaml
# libgateY
# libgd
# libgnurx
# libgrape-lite
# libharry
# libheif
# libheif-alt
libhog
# libicns
# libics
# libidn2
# libimagequant
# libinsane
# libirwls
# libkra
# liblbfgs
# liblinear
# libmdbx
# libmetalink
# libmio
# libmlpp
# libmobi
# libmodbus
# libngt-ann
# libnop
# liboauth2
# libocca
libparameters
libpathutils
# libpillowfight
# libpinyin
# libpipeline
# libpmemobj-cpp
# libpopcnt
# libprecog
# libprecog-data
# libprecog-manuals
# libpsd
# libpsl
# libq
# libquill
# libraqm
# librs232
# librsync
# libscanf
# libserialport
# libshmcache
# libsigcplusplus
# libsiridb
# libsl3
# libsmile
# libsptag
# libsql
# libsqlfs
# libstb
# libstemmer
# libsvm
# libtextcat
# libtuv
# libucl
# libunibreak
# libunifex
# libusb
# libuv
# libvips
# libvrb
libwarc
# libwebsocketpp
# libwebsockets
# libwil
libwildmatch
# libxcam
# libxo
libyaml
# libyaml-examples
# libzip
# libzmq
# ligra-graph
# line_detector
# linecook
# lizard
# lmdb
# lmdb-safe
# lmdb-store
# lmdb.spreads.net
# lmdbxx
# lnav
# localmemcache
# loguru
# loki
# lol
# lolremez
# lru_cache
# lrucache11
# lshbox
# lzbench
# lzham_codec
# mace
# magic_enum
# magsac
# mammut
# manticore-columnar
# manticore-plugins
# manticoresearch
# many-stop-words
# marian
# math-atlas
# mathtoolbox
# matplotplusplus
# mcmc
# mecab
# memory
# merror
# mesh-allocator
# messagebox-windows
# metalink-cli
# metalink-mini-downloader
# mht-rip
# microsoft-performance-toolkit-sdk
# midas
# mimalloc
# mime-mega
# mimetic
# minifb
# miniscript
# minizip-ng
# mipp
# mitlm
# mlpack
# mmc
# mmkv
# modbus-esp8266
# monolith
# morton_filter
# mosquitto
# mozjpeg
# mrpt
# ms_cpp_client_telemetry
# multiverso
# mxnet
# mydumper
# mysql-connector-cpp
# n2-kNN
# nameof
# nano-signal-slot
# nanodbc
# nanoflann
# nanomsg-nng
# nativefiledialog-extended
# ncnn
# netdata
# netpbm
# neutralinoJS
# neutralinoJS-CLI
# newlisp
# nghttp3
# ngrams-weighted
# ngtcp2
# nlopt
# nmslib
# notcurses
# npoi
# nsis
# nsis-nscurl
# nsis-stdutils
# nsync
# numero
# nuspell
# ocreval
# ogdf
# oidn-OpenImageDenoise
# oiio
# olena
# omaha
# oneTBB
# online-hnsw
# onnxruntime
opencv
opencv_contrib
# opencv_extra
# openlibm
# openpbs
# openssl
# opentelemetry-cpp
# opentelemetry-cpp-contrib
# openvino
# oppat
# optim
# osqp
# osqp-cpp
# osqp-eigen
# osquery
# otl
# owl
# p7zip
# pHash
# pagerank
# palanteer
# palmtree
# pango
# papis-zotero
# parallel-hashmap
# paramonte
# pcg-c-random
# pcg-cpp-random
# pcm
# pdf2htmlEX
# pdfgrep
# pdfium
# pdiff
# pecos
# pelikan
# pevents
# pg_similarity
# phash-gpl
# phf-hash
# photino.native
# picoc
# picohttpparser
# pikchr
# pinyin
# pipes
# pisa
# pisa_formatter
# pixman
# pmdk
# pmdk-tests
# pmemkv
# pmemkv-bench
# poco
# podofo
# poisson_blend
# polatory
# poppler
# portable-memory-mapping
# portable-snippets
# portable_concurrency-std-future
# preprocess-corpuses
# prio_queue
# probminhash
# promise-cpp
# promise-hpp
# protobuf
# proxygen
# prvhash
# psd_sdk
# pthreadpool
# pybind11
# pyclustering
# pyglass
# pylene
# pytorch
# pytorch_cpp_demo
# qlever
# qoi
# qpdf
# qs_parse
# quadsort
# quill-logging
# radamsa
# radon-tf
# randen
# random
# random-forest
# rapidJSON
# rapidxml
# rapidyaml
# rclone
re2
# reckless
# recycle
# refl-cpp
# restc-cpp
# result-cpp
# resumable-assert
# rgf
# robin-hood-hashing
# robin-map
# rotate_detection
# rsync
# safeclib
# safestringlib
# salieri
# sbcl
# scantailor
# scilab
# scintilla
# scws-chinese-word-segmentation
# sdhash
# sdsl-lite
# semimap
# sent2vec
# sentence-tokenizer
# sentencepiece
# sequential-line-search
# shadesmar
# sharedhashfile
# shmdata
# shoco
# sile-typesetter
# simd-imgproc
# simdjson
# sioyek
# siridb-server
# sist2
# slot_map
# smhasher
# snap
# snappy
# snmalloc
# snowball
# somoclu
# sparsehash
spdlog
# spdlog_setup
# spdlog_sqlite_sink
# spdmon
# spline
# splinter
# spookyhash
# spy-build-sysinfo
# sqawk
# sqlcipher
# sqlean
# sqleet
# sqlite-fts5-snowball
# sqlite-stats
# sqlite3-compression-encryption-vfs
# sqlite3pp
# sqlite_fts_tokenizer_chinese_simple
# sqlite_wrapper
# sqlite_zstd_vfs
# sqliteodbc
# sqlplot-tools
# sqlpp11
# squash
# ssdeep
# ssimulacra2
# stan
# stan-math
# stateline
# statsite
# stdext-path
# stlcache
# stopwords
# stringi
# strtk
# stx-error-handling
# subprocess
# subprocess-cpp
# subprocess_h
# sumatrapdf
# swig
# sync-module.sh
# tabulate
# tao-json
# taolog
# taskflow
# tclap
# tclclockmod
# tcp_pubsub
# tcpshm
# tee-win32
# telegram-bot-api
# telegram-td
# tempo
# tensorflow
# tensorflow-docs
# tensorflow-io
# tensorflow-text
# tensorstore
# termcolor
# tesseract-gImgRdrGui
text-wrangler
# textflowcpp
# thread-pool
# thread-pool-c
# thread-pool-cpp
# thrift
# thunderSVM
# ticpp
# tink
# tinn
# tiny-process-library
# tinycbor
# tinycolormap
# tinydir
# tinygettext
# tlx
# tlx-btree
# tmap
# toml11
# tomlpp
# tracelogging-for-ETW
# transwarp
# tray
tre
# treelite
# tsf
# twain_library
# txiki.js
# typesense
u8_to_std_string
# uberlog
uchardet
# ucto
# uctodata
# ucx
# ugrep
# unblending
# unicode-cldr
# unicode-cldr-data
unicode-icu
# unicode-icu-data
# unicode-icu-demos
# universal-numbers
# unixODBC
# uno-solver
# unpaper
# unqlite
# upscaledb
# url
# url-parser
# userver
utf8proc
utfcpp
# variadic_table
# vcpkg
# velocypack
# visible-url-detector
# vizzu
# vmaf
# vmem
# vmemcache
# vtm
# vxl
# waifu2x-ncnn-vulkan
# warc2text
# warp-ctc
# warpLDA
wcwidth9
# websocket-sharp
# webview
# wget
# wget2
# wil-Win32-Interface-Library
# win-iconv
# win32-dpi
# winflexbison
# word2vec
# word2vec-GloVe
# wordfreq
# wordfrequency
# wxCurl
# wxDatabase
# wxExamples
# wxMEdit
# wxPDFView
# wxPdfDocument
# wxSQLite3
# wxVisualScriptEngine
# wxWebViewChromium
# wyhash
# xgboost
# xlnt
xml-pugixml
# xnnpack
# xor-and-binary-fuse-filter
# xpdf
# xsg
xsimd
# xsldbg
# xtensor
# xtensor-blas
# xtensor-io
# xtl
# xxHash
# yaml-cpp
# yaml-test-suite
# yara-pattern-matcher
# yasl
# yggdrasil-decision-forests
# you-token-to-me
# yyjson
# zfp-compressed-arrays
# zotero
# zotero-better-bibtex
# zotero-bib
# zotero-build
# zotero-connectors
# zotero-google-docs-integration
# zotero-libreoffice-integration
# zotero-scholar-citations
# zotero-shortdoi
# zotero-standalone-build
# zotero-translate
# zotero-translation-server
# zotero-translators
# zotero-web-library
# zotero-word-for-windows-integration
# zotero-zotfile
# zpp_bits
# zsv
# zsync2
# zxing-cpp
BLAKE3
QuickJS
QuickJS-C++-Wrapper
QuickJS-C++-Wrapper2
argparse
asio
bibutils
boost
brotli
cli11
clipp
crow
cryptopp
dirent
dlfcn-win32
fmt
gbenchmark
gflags
glob
glog
googletest
gperf-hash
highway
jpeg-xl
lib_nas_lockfile
libarchive
libbf
libcpr
libeternaltimestamp
libgif
libiconv
libjpeg-turbo
libjxl
libqrencode
libwebp
libxml2
libxslt
libzopfli
linenoise
lz4
nanosvg
pcre
plf_nanotimer
pmt-png-tools
pthread-win32
replxx
splitmerge
sqlite
sqlite-amalgamation
svg-charter
taglib
tesslinesplit
tidy-html5
tinyexpr
tvision
uint128_t
upskirt-markdown
vcopy
wxCharts
wxFormBuilder
wxWidgets
zstd

__docs
__docs_src

jpeg-xl\third_party\lodepng
jpeg-xl\third_party\highway

taglib\3rdparty\utf8-cpp

../../../thirdparty/DirScanner

../../../docs-src/Notes

EOF

cat > utils/tmp.bat  <<EOF
@echo on

robocopy Z:\lib\tooling\qiqqa\MuPDF Qiqqa/MuPDF * /LOG:snapshot.log /LEV:8 /S /COPY:DAT /DCOPY:DAT /IM /XJF /W:1 /R:3 /PURGE /XD .vs obj bin b tmp research node_modules packages owemdjee downloads ~ .circleci  /XF *.obj *.user *.psd cef_binary* files *.tags *.exe *.dll *.gz *.zip *.idb *.pdb *fuzz* *.dump *-files .git .gitmodules

robocopy Z:\lib\tooling\qiqqa\MuPDF\thirdparty\owemdjee Qiqqa/MuPDF/thirdparty/owemdjee * /LOG+:snapshot.log /LEV:1    /COPY:DAT /DCOPY:DAT /IM /XJF /W:1 /R:3 /PURGE    /XF *.obj *.user *.psd cef_binary* files *.tags *.exe *.dll *.gz *.zip *.idb *.pdb *fuzz* .git .gitmodules

EOF

for f in   langdata_LSTM tessconfigs tessdata tessdata_best tessdata_contrib tessdata_fast tessdoc tesseract_docs tesseract_langdata tesseract_ocr_test tesstrain \
            curl extract freeglut freetype gumbo-parser harfbuzz jbig2dec jpeginfo lcms2 leptonica libjpeg libpng libtiff monolithic_tmplt mujs openjpeg          \
            tesseract tesseract_api_docs tesseract_docs zlib                                                                                                      \
; do

    echo "$f..."
    echo "set F=$f" >> utils/tmp.bat
    cat >> utils/tmp.bat  <<EOF

robocopy Z:\lib\tooling\qiqqa\MuPDF\thirdparty\%F%  Qiqqa/MuPDF\thirdparty\%F%  * /LOG+:snapshot.log /LEV:8 /S /COPY:DAT /DCOPY:DAT /IM /XJF /W:1 /R:3 /PURGE /XD .vs obj b tmp research node_modules packages .circleci 3rd thirdparty third_party 3rdparty 3rd_party  /XF  *.obj *.user *.psd cef_binary* files *.tags *.exe *.dll *.gz *.zip *.idb *.pdb *fuzz* .git .gitmodules

EOF
done

cat >> utils/tmp.bat  <<EOF

robocopy Z:\lib\tooling\qiqqa\MuPDF\thirdparty\owemdjee\boost Qiqqa/MuPDF\thirdparty\owemdjee\boost * /LOG+:snapshot.log /LEV:20 /S /COPY:DAT /DCOPY:DAT /IM      /W:1 /R:3 /PURGE /XD .vs obj b tmp research node_modules packages owemdjee downloads ~ .circleci 3rd thirdparty third_party 3rdparty 3rd_party  /XF *.obj *.user *.psd cef_binary* files *.tags *.exe *.dll *.gz *.zip *.idb *.pdb *fuzz* .git .gitmodules

EOF

for f in $( cat utils/tmp.lst | grep -v '#' ) ; do

    echo "$f..."
    echo "set F=$f" >> utils/tmp.bat
    cat >> utils/tmp.bat  <<EOF

robocopy Z:\lib\tooling\qiqqa\MuPDF\thirdparty\owemdjee\%F%  Qiqqa/MuPDF\thirdparty\owemdjee\%F%  * /LOG+:snapshot.log /LEV:15 /S /COPY:DAT /DCOPY:DAT /IM /XJF /W:1 /R:3 /PURGE /XD .vs obj b tmp research node_modules packages downloads ~ .circleci 3rd thirdparty third_party 3rdparty 3rd_party  /XF *.obj *.user *.psd cef_binary* files *.tags *.exe *.dll *.gz *.zip *.idb *.pdb *fuzz* .git .gitmodules

EOF
done

cat >> utils/tmp.bat  <<EOF

robocopy "Z:\lib\tooling\qiqqa\Technology.Tests\forking cleans up memory leaks" "Qiqqa\Technology.Tests\forking cleans up memory leaks" * /LOG+:snapshot.log /LEV:20 /S /COPY:DAT /DCOPY:DAT /IM      /W:1 /R:3 /PURGE /XD .vs obj b tmp research node_modules packages owemdjee downloads ~ .circleci 3rd thirdparty third_party 3rdparty 3rd_party  /XF *.obj *.user *.psd cef_binary* files *.tags *.exe *.dll *.gz *.zip *.idb *.pdb *fuzz* .git .gitmodules *.tlog *.log *.lastbuildstate *.recipe *.ilk *.pdb *.idb *.vcxproj.FileListAbsolute.txt *.iobj *.ipdb

robocopy "Z:\lib\tooling\qiqqa\Technology.Tests\monitor our memory usage and die when passing threshold" "Qiqqa\Technology.Tests\monitor our memory usage and die when passing threshold" * /LOG+:snapshot.log /LEV:20 /S /COPY:DAT /DCOPY:DAT /IM      /W:1 /R:3 /PURGE /XD .vs obj b tmp research node_modules packages owemdjee downloads ~ .circleci 3rd thirdparty third_party 3rdparty 3rd_party  /XF *.obj *.user *.psd cef_binary* files *.tags *.exe *.dll *.gz *.zip *.idb *.pdb *fuzz* .git .gitmodules *.tlog *.log *.lastbuildstate *.recipe *.ilk *.pdb *.idb *.vcxproj.FileListAbsolute.txt *.iobj *.ipdb

robocopy Z:\lib\tooling\qiqqa\MuPDF\platform\win32\bin\Release-Unicode-64bit-x64 utils splitmerge.exe /LOG+:snapshot.log /LEV:8 /S /COPY:DAT /DCOPY:DAT /IM /XJF /W:1 /R:3 /PURGE

EOF

#sed -i -E -e 's/^(robocopy.*)$/echo "\1"\n\1/g' utils/tmp.bat

rm snapshot.log

cat utils/tmp.bat | cmd


# and then some post-orgasmic cleanup bliss:

cat << EOF

-----------------------------------------------



Cleaning cruft that got copied inadvertently...
-----------------------------------------------

(expect some errors reported beyond this line!)


EOF

cd Qiqqa/MuPDF

for f in                            \
    platform/win32/*.pdf            \
    platform/win32/*-files          \
    platform/win32/*.dump           \
    platform/win32/unnamed*         \
    platform/win32/files            \
    platform/win32/text*.xml        \
    ../../Qiqqa/thirdparty/libs     \
    __git_lazy_remotes__            \
; do
    rm "$f"                        2> /dev/null
done

for f in                                                                            \
    thirdparty/libWebP.Net/src/Imazen.WebP/obj/                                     \
    thirdparty/owemdjee/QuickJS/test262/                                            \
    thirdparty/owemdjee/libiconv/build-VS2022/iconv-static/x64/                     \
    platform/win32/lept-tmp/                                                        \
    platform/win32/lept/demo-data/                                                  \
    platform/win32/tess-*/                                                          \
    ../MuPDF/generated/                                                             \
    ../../Qiqqa/docs-src/Notes/.trash                                               \
; do
    rm -rf "$f"                    2> /dev/null
done

for f in $( find ../ -type d -name '.deps' ) ; do
    rm -rf "$f"                    2> /dev/null
done

for f in $( find ../ -type d -name 'tmp' ) ; do
    rm -rf "$f"                    2> /dev/null
done

find ../.. -name dirlist.txt           -delete
find ../.. -name 'db*.sql'             -delete
find ../   -name '.gitignore*' -type f -delete
find ../   -name '.gitattr*'   -type f -delete
find ../.. -name '*.log'       -type f -a ! -name 'gperf.log' -a ! -name 'run.log' -a ! -name 'size.log' -a ! -name 'change.log' -delete
find       -name '.dirstamp'   -type f -delete

# plus some last-minute compensations, filling up the potholes left by the bulk /XF & /XD rejections:
for f in                                                                                                   \
    /z/lib/tooling/qiqqa/MuPDF/platform/win32/*fuzz*proj*                                                  \
    /z/lib/tooling/qiqqa/MuPDF/thirdparty/owemdjee/libeigen/Eigen/src/Core/Fuzzy*                          \
    /z/lib/tooling/qiqqa/MuPDF/thirdparty/owemdjee/libeigen/Eigen/src/SparseCore/SparseFuzzy*              \
; do
    DSTFILE="$( echo "$f" | sed -E -e 's/^.*[^q]+qiqqa\//..\/..\/Qiqqa\//' )"
    echo "$f --> $DSTFILE"
    cp "$f" "$DSTFILE"
done

find       -name '*.vcxproj.user'     -type f -delete

cd ../..

popd                       > /dev/null
