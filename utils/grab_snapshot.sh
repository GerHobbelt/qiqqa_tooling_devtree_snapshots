#! /bin/bash
#
# Assumes a git-on-windows with robocopy, bash, etc. dev env available
#

pushd $( dirname $0 )      > /dev/null
cd ..
#pwd

mkdir -p Qiqqa/MuPDF

cat > utils/tmp.lst  <<EOF

# A-MNS_TemplateMatching
# abseil-cpp
# annoy
# ApprovalTestsCpp
# arangodb
argparse
# arrayfire
asio
# asyncplusplus
# asynqro
# b2xtranslator
# basez
# BBHash
# BCF-cuckoo-index
# bebop
# bhtsne--Barnes-Hut-t-SNE
# bibtex-robust-decoder
# bibtool
bibutils
# binlog
# bitsery
BLAKE3
# BlingFire
# bolt
boost
# boost-url
# boringssl
# BoxFort
# breakpad
brotli
# c-blosc2
# CacheLib
# caches
# caffe
# cairo
# cairo-demos
# calibre
# catboost
# cctz
# ccv-nnc
# cef-pdf
# cereal
# ceres-solver
# CHM-lib
# CImg
# circlehash
# citation-abbreviations
# citation-journals
# citation-styles
# citeproc-js
# civetweb
# clBLAS
# CLBlast
# CLBlast-database
# cld2-language-detect
cli11
clipp
# CLTune
# cmph-hasher
# ColorSpace
# comdb2-bdb
# compact_enc_det
# completesearch
# concurrencpp
# concurrentqueue
# coost
# cpp-btree
# cpp-ipc
# cppflow
# cppjieba
# cpptoml
# cppzmq
# cpp_rest_sdk
# cpuinfo
# cpython
# cr
# createprocess-windows
# CRFpp
# crfsuite
# CRFsuite-extended
# Criterion
# CRoaring
crow
cryptopp
# CryptSync
# csv-parser
# csync2
# CTCWordBeamSearch
# CTPL-Thread-Pool
# ctsa
# cuckoo-index
# cuckoofilter
# curl-impersonate
# curl-www
# CxImage
# cxxopts
# cxxtest
# cxxtest_catch_2_gtest
# Cysboard
# date
# datetimepp
# dateutils
# DBoW2
# DCF-cuckoo-index
# debugbreak
# delegate
# DGM-CRF
# diffutils
dirent
# djvulibre
dlfcn-win32
# dlib
# docxBox
# doh
# drogon
# dtl-diff-template-library
# dtoa-benchmark
# dynet
# ecal
# ECMA262
# efsw
# emphf-hash
# enkiTS-TaskScheduler
# EOT
# EtwExplorer
# eventpp
# everything-curl
# exiv2
# expected-lite
# Extensible-Storage-Engine
# faiss
# fastBPE
# fastPRNG
# fastText
# fast_float
# fast_pfor
# fatal
# fftw3
# file
# filesystem
# flat_hash_map
# fluent-bit
fmt
# fmtlog
# folly
# fribidi
# friso
# frozen
gbenchmark
# gdbm
# gettext
gflags
# gibbs-lda
# glib2
glob
glog
# GMM-HMM-kMeans
# GMMreg
# GoldFish-CBOR
# google-diff-match-patch
# google-marl
googletest
gperf-hash
# GraphicsMagick
# graphit
# gtn
# gumbo-libxml
# gumbo-query
# h2o-server
# harbour-core
# HDiffPatch
# hedley
highway
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
# html2openxml
# htmlstreamparser
# http-parser
# hunspell
# hunspell-dictionaries
# hunspell-hyphen
# hyperscan
# hypertextcpp
# iceoryx
# id3-tagparser
# ImageMagick
# indicators
# infoware
# iODBC
# ion-c
# ipa-dict
# iresearch
# JabRef-abbreviations
# JabRef-Browser-Extension
# JamSpell
# jasper
# jemalloc
# jerryscript
jpeg-xl
# jq
# json
# json-jansson
# jsoncons
# kahypar
# kfr
# kgraph
# koan
# krabsETW
# lapack
# lda
# lda-3-variants
# lda-bigartm
# lda-Familia
# LDCF-hash
# lerc
# libaco
# libalg
# libaom
libarchive
# libassert
# libavif
libbf
# libbloom
# libcbor
# libchaos
# libchardet
# libclip
# libclipboard
# libcmime
# libcnl
# libconfig
# libcopp
# libcppjieba
libcpr
# libcpuid
# libCRCpp
# libcsp
# libcsv2
# libcyaml
# libCZMQ
# libde265
# libdeflate
# libdi-dependency-injection
# libdist
# libdivsufsort
# libdtm
# libeigen
libeternaltimestamp
# libevent
# libevt
# libexpat
# libffi
# libfolia
# libfort
# libfyaml
# libgateY
# libgd
libgif
# libgrape-lite
# libharry
# libheif
# libheif-alt
# libicns
libiconv
# libidn2
# libimagequant
libjpeg-turbo
libjxl
# liblinear
# libmdbx
# libmio
# libmlpp
# libmobi
# libngt-ann
# libocca
# libpinyin
# libpopcnt
# libpsl
# libq
libqrencode
# libquill
# libraqm
# librs232
# librsync
# libscanf
# libshmcache
# libsigcplusplus
# libsmile
# libsptag
# libsqlfs
# libstb
# libstemmer
# libsvm
# libtextcat
# libtuv
# libucl
# libunifex
# libuv
# libvips
# libvrb
# libwarc
libwebp
# libwebsocketpp
# libwebsockets
# libwil
# libwildmatch
libxml2
libxslt
# libyaml
# libyaml-examples
# libzip
# libzmq
libzopfli
lib_nas_lockfile
# LightGBM
# LightLDA
# Lightning.NET
# ligra-graph
linenoise
# line_detector
# lmdb
# lmdb-safe
# lmdb-store
# lmdb.spreads.net
# lmdbxx
# localmemcache
# lrucache11
lz4
# mace
# magic_enum
# mammut
# manticore-columnar
# manticore-plugins
# manticoresearch
# many-stop-words
# marian
# MariGold.OpenXHTML
# math-atlas
# mcmc
# memory
# merror
# mesh-allocator
# messagebox-windows
# mht-rip
# microsoft-performance-toolkit-sdk
# midas
# mimalloc
# mime-mega
# mimetic
# mipp
# MITIE-nlp
# mlpack
# mmc
# mmkv
# MNN
# monolith
# morton_filter
# ms_cpp_client_telemetry
# multiverso
# mxnet
# mydumper
# mysql-connector-cpp
# nameof
# nanodbc
# nanoflann
# NanoLog
# nanomsg-nng
nanosvg
# nativefiledialog-extended
# ncnn
# neutralinoJS
# neutralinoJS-CLI
# nghttp3
# ngtcp2
# NiuTrans.NMT
# nmslib
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
# nuspell
# ocreval
# OfficeIMO
# oiio
# olena
# oneTBB
# onnxruntime
# Open-XML-SDK
# OpenBLAS
# OpenCL-CTS
# OpenCL-Headers
# OpenCL-SDK
# opencv
# opencv_contrib
# OpenFST
# OpenFST-utils
# openpbs
# openssl
# opentelemetry-cpp
# oppat
# OptimizationTemplateLibrary
# osquery
# otl
# PaddlePaddle
# pagerank
# palanteer
# palmtree
# pango
# papis-zotero
# parallel-hashmap
# pcg-c-random
# pcg-cpp-random
# pcm
pcre
# pdf2htmlEX
# pdfgrep
# pdfium
# pelikan
# percona-server
# pevents
# PGM-index
# pHash
# phash-gpl
# phf-hash
# photino.native
# PhotonLibOS
# picoc
# picohttpparser
# pinyin
# pipes
# pisa
# pixman
# PlatformFolders
plf_nanotimer
pmt-png-tools
# podofo
# poppler
# portable-memory-mapping
# portable-snippets
# portable_concurrency-std-future
# preprocess-corpuses
# prio_queue
# probminhash
# promise-cpp
# promise-hpp
# proxygen
# prvhash
pthread-win32
# pthreadpool
# pybind11
# pyclustering
# pytorch
# pytorch_cpp_demo
# QCBOR
# qlever
QuickJS
QuickJS-C++-Wrapper
QuickJS-C++-Wrapper2
# randen
# random
# rapidJSON
# rapidyaml
# rclone
# re2
# recycle
# refl-cpp
replxx
# research
# restc-cpp
# result-cpp
# resumable-assert
# robin-hood-hashing
# robin-map
# rsync
# RuntimeCompiledCPlusPlus
# RxCpp
# safestringlib
# salieri
# scantailor
# scintilla
# ScriptX
# sdhash
# Sealighter
# sentence-tokenizer
# sentencepiece
# shadesmar
# ShapeCrawler
# sharedhashfile
# shmdata
# shoco
# Signals
# SilkETW
# simd-imgproc
# sioyek
# smhasher
# snap
# snmalloc
# snowball
# sparsehash
# spdlog
# spdlog_setup
splitmerge
# spy-build-sysinfo
# sqlcipher
# sqlean
# sqleet
sqlite
sqlite-amalgamation
# sqlite-fts5-snowball
# sqlite-stats
# sqlite3-compression-encryption-vfs
# sqlite3pp
# SQLiteCpp
# SQLiteHistograms
# sqliteodbc
# sqlite_fts_tokenizer_chinese_simple
# sqlite_wrapper
# sqlite_zstd_vfs
# sqlpp11
# ssdeep
# ssimulacra2
# stan
# stan-math
# StarSpace
# stateline
# statsite
# stdext-path
# stopwords
# stringi
# stx-error-handling
# subprocess
# subprocess-cpp
# subprocess_h
# sumatrapdf
svg-charter
# swig
# SymSpell
# tabulate
taglib
# taolog
# taskflow
# tcpshm
# tcp_pubsub
# tensorflow
# tensorflow-docs
# tensorflow-io
# tensorflow-text
# tesseract-gImgRdrGui
tesslinesplit
# textflowcpp
# thread-pool
# thread-pool-c
# thread-pool-cpp
# ThreadPool
# thunderSVM
# ticpp
tidy-html5
# tink
# tinn
# tiny-process-library
# tinycbor
# tinycolormap
tinyexpr
# tinygettext
# tlx
# tlx-btree
# toml11
# tomlpp
# TraceETW
# tracelogging-for-ETW
# transwarp
# tre
# tsf
tvision
# txiki.js
# typesense
# uberlog
# uchardet
# ucto
# uctodata
# ucx
# UIforETW
uint128_t
# unicode-cldr
# unicode-icu
# universal-numbers
# unixODBC
# unpaper
# upscaledb
upskirt-markdown
# url
# userver
# utfcpp
# variadic_table
# velocypack
# Verify
# VisualScriptEngine
# VQMT
# VSNASM
# vxl
# warc2text
# warp-ctc
# warpLDA
# websocket-sharp
# webview
# wget
# wil-Win32-Interface-Library
# win32-dpi
# Win32_read_directory_changes
# Win32_read_directory_changes_IOCP
# Windows10EtwEvents
# winflexbison
# WinHttpPAL
# word2vec
# word2vec-GloVe
# wordfreq
# wordfrequency
wxCharts
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
# xgboost
# xlnt
# xml-pugixml
# XMP-Toolkit-SDK
# xnnpack
# Xoshiro-cpp
# xpdf
# xsimd
# xsldbg
# xtensor
# xtensor-blas
# xtensor-io
# xtl
# xxHash
# YACLib
# yaml-cpp
# yaml-test-suite
# yara-pattern-matcher
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
zstd
# zsv
# zsync2
# zxing-cpp
__docs
__docs_src

# SymSpell
# wordfreq
# wordfrequency
# libdtm
# prvhash
# vxl
# metalink-cli
# libmetalink
# metalink-mini-downloader
# wget2
# wxCurl

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

for f in   langdata_LSTM tessconfigs tessdata tessdata_best tessdata_contrib tessdata_fast tessdoc tesseract_docs tesseract_langdata tesseract_ocr_test tesstrain    ; do

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

for f in 					\
	platform/win32/*.pdf			\
	platform/win32/*-files			\
	platform/win32/*.dump			\
	platform/win32/unnamed*			\
	platform/win32/files 			\
	platform/win32/text*.xml		\
	__git_lazy_remotes__			\
; do
	rm "$f"                        2> /dev/null
done

for f in 										\
	thirdparty/libWebP.Net/src/Imazen.WebP/obj/					\
	thirdparty/owemdjee/QuickJS/test262/	         				\
	thirdparty/owemdjee/libiconv/build-VS2022/iconv-static/x64/                     \
; do
	rm -rf "$f"                    2> /dev/null
done

find ../.. -name dirlist.txt -delete
find ../.. -name 'db*.sql' -delete
find ../ -name '.gitignore*' -type f -delete
find ../ -name '.gitattr*' -type f -delete

# plus some last-minute compensations, filling up the potholes left by the bulk /XF & /XD rejections:
for f in 									\
	/z/lib/tooling/qiqqa/MuPDF/platform/win32/*fuzz*proj*			\
; do
	DSTFILE="$( echo "$f" | sed -E -e 's/^.*[^q]+qiqqa\//..\/..\/Qiqqa\//' )"
	echo "$f --> $DSTFILE"
	cp "$f" "$DSTFILE"
done

cd ../..
		
popd                       > /dev/null
