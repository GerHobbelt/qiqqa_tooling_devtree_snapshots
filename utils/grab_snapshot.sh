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
# abseil-cpp
# adaptiveqf
# ADE-graph-management
# AFLplusplus
# agg
# aho-corasick
# aho_corasick
# amd-fftw
# annoy
# ApprovalTestsCpp
# arangodb
# ArborX
# archive-hocr-tools

argparse
armadillo

# arrayfire
# arrow

asio

# asyncplusplus
# asynqro
# AudioFile
# autodiff
# avro
# awesome-c
# Awesome-Document-Image-Rectification
# Awesome-Image-Quality-Assessment
# b2xtranslator
# backward-cpp
# baobzi

BaseMatrixOps

# basez
# BayerToRGB

bbe

# BBHash
# BCF-cuckoo-index
# bebop
# BehaviorTree.CPP
# better-enums

bhtsne--Barnes-Hut-t-SNE

# Bi-Sent2Vec
# bibtex-robust-decoder
# bibtool

bibutils
bin2cpp

# binary2strings
# binary_bakery
# binary_search
# binlog
# BitFunnel
# bitrush-index

bitsery
BLAKE3

# blaze
# blazingmq
# BlingFire
# blis
# blitsort
# bloom
# bolt

boost

# boost-url
# boringssl
# BoxFort
# bplustree
# breakpad

brotli

# brown-cluster
# brunsli
# bustache
# butteraugli
# c-blosc2
# CacheLib
# cachelot
# caches
# caffe
# cairo
# cairo-demos
# calibre
# capnproto
# capture-thread
# Capture2Text
# catboost
# cctz
# ccv-nnc
# cdc-file-transfer
# cef-pdf
# cel-cpp
# cel-spec
# cereal
# ceres-solver
# cfgpath
# chewing_text_cud
# chibi-scheme
# CHM-lib
# chromium-snss-parse
# cilantro
# CImg
# circlehash

# citation-abbreviations
# citation-journals
# citation-styles
# citeproc-js
# civetweb
# cjose
# clBLAS
# CLBlast
# CLBlast-database
# cld1-language-detect
# cld2-language-detect
# cld3-language-detect

cli11
clipp

# Clipper2
# clp
# CLTune
# Cmathtuts

cmph-hasher

# CNTK
# colm
# color-util
# colorm
# ColorMagic
# colormap-shaders
# ColorPaletteCodable
# ColorSpace
# comdb2-bdb
# compact_enc_det
# completesearch
# concat
# concurrencpp
# concurrentqueue
# config-cpp
# continuable
# coost
# cpp-btree
# cpp-httplib
# cpp-ipc
# cpp-netlib

cpp-terminal

# cppdap
# cppflow
# cppjieba
# cpplocate
# CppNumericalSolvers
# cppsimhash
cpptoml
# cppzmq
# cpp_rest_sdk

cpuinfo

# cpu_features
# cpython
# cqf
# cr
# crc32c
# createprocess-windows
# CRFpp
# crfsuite
# CRFsuite-extended
# Criterion
# CRoaring

crow

# crumsort

cryptopp

# CryptSync
# csv-parser
# csvquote
# csync2
# CTCWordBeamSearch
# CTPL-Thread-Pool
# ctsa
# cuckoo-index
# cuckoofilter
curl-impersonate
# curl-www
# CurvatureFilter
# cv-VanishingPoint
# cvmatio
# CxImage
# cxxopts
# cxxtest

cxxtest_catch_2_gtest

# Cysboard
# darknet
# dashing
# datamash
# date
# datetimepp
# dateutils
# DBoW2
# DBow3
# dbscan
# DCF-cuckoo-index

debugbreak

# decision-tree
# deepdetect

delegate

# density
# densityxx
# design-patterns-cpp
# detect-character-encoding
# DGM-CRF
# diffutils
# Digital-Halftoning
# directorywatcher

dirent

# DiskANN

djvulibre

# dkm

dlfcn-win32

# dlib
# DocLayNet
# doctest
# docxBox
# doh
doxa
# doxygen-awesome-css
# DP_means
# drogon
# dr_libs
# dtl-diff-template-library
# dtoa-benchmark
# duckdb
# duktape
# dynet
# easyexif
# easyloggingpp
# EasyOCR
# EasyOCR-cpp
# ecal
# ECMA262

edit-distance

# efftw
# efsw
# EigenRand
# emphf-hash
# enca
# enkiTS-TaskScheduler
# ensmallen
# epeg
# EtwExplorer
# eventpp
everything-curl
# EWAHBoolArray
# ex-leptonica-freetype-harfbuzz
# exiv2
expected
# expected-lite

exprtk

# Extensible-Storage-Engine
# eytzinger
# faiss
# falconn
# farmhash
# farver-OKlab
# fast-hex
# fast-kmeans
# fast-lzma2
# fastapprox
# fastBPE
# fastfilter_cpp
# FastGlobbing
# fastgron
# fasthashing
# fastops
# fastPRNG
# fastrange
# FastString
# fastText
# fast_double_parser
# fast_float
# fast_pfor
# fatal
# faup
# fbow
# fCWT
# ffht
# FFME
# FFmpeg
# ffts
# fftw3
# FiberTaskingLib
# fifo_map
# figcone
# figtree

file

# filecopyex3

filesystem

# FIt-SNE
# fityk
# flac
# flann
# flare-floss
# flashlight
# flat.hpp
# flatton-offline
# flat_hash_map
# flinng
# flip
# fluent-bit
# fluxsort
# FM-fast-match
# fmath
# fmem
# fmemopen_windows

fmt

# fmtlog

fnmatch

# folly
# fontbm

fontconfig

# fontview
fph-table
# fpng
# FreeFileSync
# fribidi
# friso
# frozen
# fsst
# fswatch
# fuzzy-match
# fxt
# g2o
# g3log

gbenchmark
gcem

# gdbm
# gegl
# gencolormap
# genieclust

getopt

# gettext

gflags
gibbs-lda

giflib-turbo
# glaze

glfw

# glib2
# glm

glob
glog

# glyph_name
# gmic
# gmic-community
# GMM-HMM-kMeans
# GMMreg
# gmt
# gnuplot
# gnuplot-palettes
# gnuplot_i
# GoldFish-CBOR
# google-diff-match-patch
# google-marl

googletest
gperf-hash

# GQ-gumbo-css-selectors
# gram_savitzky_golay
# graph-coloring
# GraphBLAS
# GraphicsMagick
# graphit
# grok-jpeg2000
# groonga
# GSL
# gtn
# gtsam
# guetzli
# guile
gumbo-libxml

gumbo-query

# gumbo_pp
# h2o-server
# h5cpp
# Hackers-Delight
# half
# harbour-core
# harry
# HashMap
# hdbscan
# hdbscan-cpp
# HDiffPatch
# hedley
# hescape

highway

# highwayhash
# hikyuu
# hilbert_curves
# hilbert_hpp
# hmm-scalable
# hmm-stoch
# hnswlib
# hocr-fileformat
# hocr-spec
# hocr-tools
# honggfuzz
# hopscotch-map
# horsejs
# houdini
# hsluv-c
# hsluv-color-gradient
# html2openxml
# html5lib-tests
# htmlstreamparser
# http-parser
# hunspell
# hunspell-dictionaries
# hunspell-hyphen
# hydraquill
# hyperscan
# hypertextcpp
# iceberghashtable
# iceoryx
# icer_compression
# IconFontCppHeaders

id3-tagparser

# IdGenerator
# ifopt
# ikd-Tree

imagedistance

# imagehash
# ImageMagick
# Imath
# IMGUR5K-Handwriting-Dataset
# indicators
# InferenceHelper
# infoware
# InversePerspectiveMapping
# iODBC
# ion-c
# ipa-dict
# Ipopt
# iresearch
# itcl
# ITK
# itpp
# ivf-hnsw
# JabRef-abbreviations
# JabRef-Browser-Extension
# JamSpell
# jasper
# javascript-serialization-benchmark
jbig2dec
jbig2enc
# jemalloc
# jerryscript
# jimtcl

jpeg-xl

# jpeg2dct
# jpegview
# jq
# json
# json-jansson
# jsoncons
# jsoncpp
# jtc
# K-Medoids-Clustering
# kahypar
# kalman-cpp
# kann
# KDSPDSetup
# kfr
# kgraph
# kissfft
# kiwi
# klib
# knusperli
# koan
# krabsETW
# krita
# L1Flattening
# lapack
# LBFGS-Lite
# lda
# lda-3-variants
# lda-bigartm
# lda-Familia
# LDCF-hash
# learnopencv
# leptonica-hillshade
# LeptonicaDocsSite
# lerc
# lexbor
# libaco
# libahocorasick
# libalg
# libaom

libarchive
libascii

# libase
# libass

libassert

# libatlas
# libavif

libbf

# libbloom
# libbloomfilters
# libblosc
# libbtree
# libcbor

libchaos

# libchardet

libchiaroscuramente

# libCHM

libchopshop

# libclip
# libclipboard
# libcluster
# libcmime
# libcnl
# libconfig
# libcopp
# libcppjieba

libcpr

# libcpuid
# libCRCpp
# libCSD
# libcsp

libcsv2

# libcuckoo
# libcyaml
# libCZMQ
# libde265
# libdeflate
# libdi-dependency-injection

libdiagnostics

# libdip
# libdist
# libdivide
# libdivsufsort
# libdjvu
# libdtm

libeigen

# libenkiTaskScheduler

libeternaltimestamp

# libevent
# libevt

libexpat

# libfamilia
# libfann
# libffi
# libfolia
# libfort
# libfyaml
# libgateY
# libgd

libgif

# libgnurx
# libgrape-lite
# libharry
# libhashmapbtree
# libheif
# libheif-alt
# libhilbert

libhog

# libicns

libiconv

# libics
# libicu
# libidn2
# libimagequant
# libinsane
# libInterpolate
# libintrinsics
# libirwls
# libjansson

libjpeg-turbo

# libjpegqs

libjxl

# libkdtree
# libkra
# liblbfgs
# liblinear
# libmarl
# libmdbx
# libmegamime
# libmetalink
# libmio
# libmlpp
# libmobi
# libmodbus
# libngt-ann
# libnop
# liboauth2
# libocca
# libpano13

libparameters
libpathutils

# libpillowfight
# libpinyin
# libpipeline
# libpmemobj-cpp
# libpng
# libpopcnt
# libpostal

libprecog

# libprecog-data
# libprecog-manuals
# libpromise
# libpsd
# libpsl
# libq

libqrencode

# libquill
# libraqm
# librobust-bibtex
# librs232
# librsync
# libscanf
# libserialport
# libshmcache

libsigcplusplus

# libsiridb
# libsl3
# libsmile
# libsndfile
# libsptag
# libsql
# libsqlfs
# libstb
# libstemmer
# libsvgcharter
# libsvm
# libtbb
# libtextcat
# libtidyhtml

libtiff

# libtoml
# libtorch
# libtuv
# libucl
# libunibreak
# libunifex
# libusb
# libuv
# libvips
# libvrb

libwarc
libwebp

# libwebsocketpp
# libwebsockets
# libwil

libwildmatch

# libxbr-standalone
# libxcam

libxml2

# libXMP-Toolkit
# libxo

libxslt
libyaml

# libyaml-examples
# libzint
# libzip
# libzmq

libzopfli
lib_nas_lockfile

# LightGBM
# LightLDA
# Lightning.NET
# ligra-graph
# linecook

linenoise

# line_detector
# lizard
# LLhttp-parser
# lmdb
# lmdb-safe
# lmdb-store
# lmdb.spreads.net
# lmdbxx
# lmfit
# LMW-tree
# lnav
# localmemcache
# local_adaptive_binarization
# lockfree
# loguru
# loki
# lol
# lolremez
# lrucache11
# lru_cache
# lshbox
# LSHBOX
# LSWMS
# lterpalettefinder
# luple

lz4

# lzbench
# lzham_codec
# LZMA-Vizualizer
# mace
# magic_enum
# magsac
# mammut
# manticore
# manticore-columnar
# manticore-plugins
# manticoresearch
# many-stop-words
# mapreduce
# marian
# MariGold.OpenXHTML
# math-atlas
# mathtoolbox
# matplotplusplus

mcmc

# mcmc-jags
# mcmd
# mecab
# mechascribe
# MegEngine
# memory
# merror
# mesh-allocator
# messagebox-windows
# metalink-cli
# metalink-mini-downloader
# MetBrewer
# mht-rip
# MicroPather
# microsoft-performance-toolkit-sdk
# midas
# mimalloc
# mime-mega
# mimetic
# minhash_clustering
# minifb
# minimp3
# miniscript
# minizip-ng
# mipp
# MITIE-nlp
# mitlm
# mlinterp
# mlpack
# mmc
# mmkv
# MNN
# modbus-esp8266
# ModernCppStarter
# monolith
# morton_filter
# mosquitto
# mozjpeg
# MPMCQueue
# mrpt
# ms_cpp_client_telemetry
# Multicore-TSNE
# MultipartEncoder
# multiverso
# mutable_rank_select
# mxnet
# mydumper
# mysql-connector-cpp
# n2-kNN
# nameof
# nano-signal-slot
# nanodbc
# nanoflann
# nanoflann_dbscan
# nanogui
# NanoLog
# nanomsg-nng

nanosvg

# nanovg-qjs
# nativefiledialog-extended
# ncnn
# nedtries
# netdata
# netpbm
# neutralinoJS
# neutralinoJS-CLI
# newlisp
# nfft
# nghttp3
# ngrams-weighted
# ngtcp2
# NiuTrans.NMT
# nlopt
# nlopt-util
# nmslib
# nodesoup
# notcurses
# npoi
# nsis
# nsis-nscurl
# NSIS-OBSInstallerUtils
# nsis-stdutils
# NSISDotNetChecker
# NSISFileCheck
# NSISMultiUser
# nsync
# numero
# nuspell
# Nuvoton-N76E003-material
ocreval
# ocr_eval_tools
# OfficeIMO
# ogdf
# oidn-OpenImageDenoise
# oiio
# olena
# omaha
# oneDNN
# oneTBB
# online-hnsw
# onnxruntime
# onnxruntime-extensions
# onnxruntime-genai
# oof
# open-vcdiff
# Open-XML-SDK
# openalpr
# OpenBLAS
# OpenCL-CTS

OpenCL-Headers

# OpenCL-SDK
# OpenColorIO
# OpenCP

opencv
opencv_contrib

# opencv_extra
# OpenEXR
# openexr-images
# OpenFST
# OpenFST-utils
# OpenImageIO
# openjpeg
# openlibm
# OpenNN
# openpbs
# openssl
# opentelemetry-cpp
# opentelemetry-cpp-contrib
# openvino
# oppat
# optim
# OptimizationTemplateLibrary
# opus
# or-tools
# ormpp
# osqp
# osqp-cpp
# osqp-eigen
# osquery
# OTB
# otl
# otl-ml
# owl
# OZBCBitmap
# p7zip
# Paddle-Lite
# PaddleClas
# PaddleDetection
# PaddleNLP
# PaddleOCR
# PaddlePaddle
# pagerank
# paintingReorganize
# palanteer
# palmtree
# pango
# papis-zotero
# parallel-hashmap
# paramonte
# pcg-c-random
# pcg-cpp-random
# pcl
# pcm

pcre

# pdf2htmlEX
# PDFGen
# pdfgrep
# pdfium
# pdiff
# pecos
# PEGTL
# pelikan
# pevents
# pfp-cst
# PGM-index
# pg_similarity
# pHash
# phash-gpl
# phf-hash
# photino.native
# PhotonLibOS
# picoc
# picohttpparser
# pico_tree
# pikchr
# Pillow
# pillow-resize
# pinyin
# pipes
# piposort
# pisa
# pisa_formatter
# pixman
# pke
# PlatformFolders

plf_nanotimer

# pmdk
# pmdk-tests
# pmemkv
# pmemkv-bench

pmt-png-tools

# PNWColors
# poco
# podofo
# poisson_blend
# polatory
# poplar-trie
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

pthread-win32

# pthreadpool
# puffinn
# pybind11
# pyclustering
# pyglass
# pylene
# pytorch
# pytorch_cluster
# pytorch_cpp_demo
# QALSH
# QALSH_Mem
# QCBOR
# qHilbert
# qjs-ffi
# qjs-modules
# qjs-opencv
# qjs-sqlite3
# qlever
# qoa
# qoi
# qpdf
# qs_parse
# quadsort
# Quant
# QuantLib
# quantum

QuickJS
QuickJS-C++-Wrapper
QuickJS-C++-Wrapper2

# quickjs-ffi
# quill-logging
# quirc
# r8brain-free-src
# radamsa
# radon-tf
# ragel
# RAKE
# randen
# random
# random-forest
# RandomizedRedundantDCTDenoising
# RapidFuzz
# rapidJSON
# rapidxml
# rapidyaml
# rclone
# RE-flex

re2

# re2c
# readerwriterqueue
# reckless
# RectangleBinPack
# recycle
# refl-cpp
# remake

replxx

# reproc
# restc-cpp
# result-cpp
# resumable-assert
# retinex
# rgf
# riegeli
# RNGSobol
# RoaringBitmap
# robin-hood-hashing
# robin-map
# robotstxt
# rollinghashcpp
# rotate
# rotate_detection
# RRD
# RRPN
# rsync
# rtl
# rttr
# RuntimeCompiledCPlusPlus
# ruy
# RxCpp
# sac
# safeclib
# safestringlib
# salieri
# sally
# Sancho.Panza.on.tesseract.OCR
# sbcl
# scantailor
# scilab
# scintilla
# ScriptX
# scws-chinese-word-segmentation
# sdcc
# sdhash
# sdsl-lite
# Sealighter
# see-phit
# semimap
# sent2vec
# sentence-tokenizer
# sentencepiece
# sequential-line-search
# serde-cpp
# serdepp
# shadesmar
# ShapeCrawler
# sharedhashfile
# SheenBidi
# Sherwood
# Shifted-Hamming-Distance
# shmdata
# shoco
# Signals
# sile-typesetter
# silk-codec
# silk-v3-decoder
# SilkETW
# simd-imgproc
# simdcomp
# simdjson
# SIMDString
# simhash-cpp
# sioyek
# SipHash
# siridb-server
# sist2
# slot_map
# smhasher
# snap
# snappy
# snmalloc
# snowball
# Solo
# somoclu
# Sophus

sparsehash

# sparsepp

spdlog

# spdlog_setup
# spdlog_sqlite_sink
# spdmon
# speex
# spherical-k-means
# spline
# splinter

splitmerge

# spookyhash
# SPSCQueue
# spy-build-sysinfo
# sqawk
# sqlcipher
# sqlean
# sqleet

sqlite
sqlite-amalgamation

# sqlite-fts5-snowball
# sqlite-parquet-vtable
# sqlite-stats
# sqlite3-compression-encryption-vfs
# sqlite3pp
# SQLiteCpp
# SQLiteHistograms
# sqliteodbc
# sqlite_fts_tokenizer_chinese_simple
# sqlite_wrapper
# sqlite_zstd_vfs
# sqlplot-tools
# sqlpp11
# squash
# ssdeep
# sse-popcount
# ssimulacra2
# stan
# stan-math
# StarSpace
# state-threads
# stateline
# stats
# statsite
# stdext-path
# stlcache
# stopwords
# stringi
# strings2
# StringZilla
# StronglyUniversalStringHashing
# strtk
# stx-error-handling
# subprocess
# subprocess-cpp
# subprocess_h
# SuiteSparse
# sumatrapdf
# SuperString

svg-charter

# swig
# SymSpell
# SymspellCPP
# sync-module.sh
# SZ
# SZ3
# tab
# tabulate

taglib

# tao-json
# taolog
# tapkee
# taskflow
# tcl
# tclap
# tclclockmod
# tcllib
# tcpshm
# tcp_pubsub
# tee-win32
# telegram-bot-api
# telegram-td
# TelemetrySourcerer
# tempo
# tensorflow
# tensorflow-docs
# tensorflow-io
# tensorflow-text
# tensorstore
# termcolor
# tesseract-dev-mailing-list-archive
# tesseract-gImgRdrGui
# tesseract-ocr-mailing-list-archive

tesslinesplit
text-wrangler

# textflowcpp
# theoretica
# thread-pool
# thread-pool-c
# thread-pool-cpp
# ThreadPool
# thrift
# thunderSVM
# ticpp

tidy-html5

# tink
# tink-cc
# tinn
# tiny-dnn
# tiny-process-library
# tiny-utf8
# tinycbor
# tinycolormap
# tinydir

tinyexpr

# tinyexr
# tinygettext
# tinynurbs
# tinyspline
# tlsh
# tlx
# tlx-btree
# tmap
# TNN
# toml11

tomlpp

# TraceETW
# tracelogging-for-ETW
# transwarp
# tray

tre

# treelite
# trng4
# tsf

tvision

# twain_library
# tweeny
# txiki.js
# typesense
# u8g2

u8_to_std_string

# uberlog

uchardet

# ucto
# uctodata
# ucx
# ugrep
# UIforETW

uint128_t

# unblending
# unicode-cldr
# unicode-cldr-data

unicode-icu

# unicode-icu-data
# unicode-icu-demos
# unilib
# units
# universal-numbers
# unixODBC
# uno-solver
# UnofficialLeptDocs
# unpaper
# unqlite
# unsmear
# upscaledb

upskirt-markdown

# URI-Encode-C
# url
# URL-Detector
# url-parser
# usearch
# userver

utf8proc
utfcpp

# util
# uvw
# variadic_table

vcopy

# vcpkg
# velocypack
# Verify
# visible-url-detector
# VisualScriptEngine
# vizzu
# vmaf
# vmem
# vmemcache
# VQMT
# VSNASM
# VTK
# vtm
# vxl
# waifu2x-ncnn-vulkan
# warc2text
# warp-ctc
# warpLDA
# wavelib

wcwidth9

# wdenoise
# we-love-colors
# websocket-sharp
# webview
# WebView2Browser
# WebView2Samples
# wesanderson
# wget
# wget2
# wil-Win32-Interface-Library
# win-iconv
# win32-dpi
# Win32_read_directory_changes
# Win32_read_directory_changes_IOCP
# Windows10EtwEvents
# winflexbison
# WinHttpPAL
# WinToast
# wolfsort
# word2vec
# word2vec-GloVe
# worde_butcher
# wordfreq
# wordfrequency

wxCharts

# wxCurl
# wxDatabase
# wxExamples

wxFormBuilder

# wxMEdit
# wxPdfDocument
# wxPDFView
# wxSQLite3
# wxVisualScriptEngine
# wxWebViewChromium

wxWidgets

# wyhash
# xbrzscale
# xcdat
# xdelta
# xgboost
# xlnt

xml-pugixml

# XMP-Toolkit-SDK
# xmunch
# xnnpack
# xor-and-binary-fuse-filter
# Xoshiro-cpp
# xpdf
# xsg

xsimd

# xsldbg
# xtensor
# xtensor-blas
# xtensor-io
# xtl
# xxHash
# YACLib
# yake
# yaml-cpp
# yaml-test-suite
# yara-pattern-matcher
# yasl
# yggdrasil-decision-forests
# you-token-to-me
# yyjson
# yy_color_convertor
# zfp-compressed-arrays
# zlibxtensor
# ZLMediaKit
# zpp_bits
# ZQCNN

zstd
zsv

# zsync2
# zvec
# zxing-cpp

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
# ZQCNN

zstd

# zsv
# zsync2
# zvec
# zxing-cpp


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

robocopy Z:\lib\tooling\qiqqa\MuPDF\thirdparty\owemdjee\bin2cpp  Qiqqa/MuPDF\thirdparty\owemdjee\bin2cpp  * /LOG+:snapshot.log /LEV:20 /S /COPY:DAT /DCOPY:DAT /IM      /W:1 /R:3 /PURGE /XD .vs obj b tmp research node_modules packages owemdjee downloads ~ .circleci   /XF *.obj *.user *.psd cef_binary* files *.tags *.exe *.dll *.gz *.zip *.idb *.pdb *fuzz* .git .gitmodules

robocopy Z:\lib\tooling\qiqqa\MuPDF\thirdparty\owemdjee\cxxtest_catch_2_gtest  Qiqqa/MuPDF\thirdparty\owemdjee\cxxtest_catch_2_gtest  * /LOG+:snapshot.log /LEV:20 /S /COPY:DAT /DCOPY:DAT /IM      /W:1 /R:3 /PURGE /XD .vs obj b tmp research node_modules packages owemdjee downloads ~ .circleci   /XF *.obj *.user *.psd cef_binary* files *.tags *.exe *.dll *.gz *.zip *.idb *.pdb *fuzz* .git .gitmodules

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
    platform/win32/*.box            \
    platform/win32/*.hocr           \
    platform/win32/*.webp           \
    platform/win32/*.html           \
    platform/win32/*.uzn            \
    platform/win32/*.tsv            \
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
    platform/cmake/.git/				                                            \
	platform/win32/lept/ 															\
	platform/win32/tess-debug*														\
    ../MuPDF/generated/                                                             \
    ../../Qiqqa/docs-src/Notes/.trash                                               \
; do
    rm -rf "$f"                    2> /dev/null
done

# making sure each of the subsequent `find` ops does find at least one entry, so we do not end up with an highly undesirable 'rm -rf' without any path.
mkdir -p Qiqqa/MuPDF/.deps
find ../ -type d -name '.deps' | xargs rm -rf 

mkdir -p Qiqqa/MuPDF/tmp-dummy-dir
find ../ -type d -name 'tmp*'  | xargs rm -rf

mkdir -p Qiqqa/MuPDF/platform/win32/bugger-it-dummy-dir
find Qiqqa/MuPDF/platform/win32/ -mindepth 1 -maxdepth 1 -type d | xargs rm -rf


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
