#############################################################################
# Name:        build/cmake/lib/stc/CMakeLists.txt
# Purpose:     CMake file for stc library
# Author:      Tobias Taschner
# Created:     2016-10-04
# Copyright:   (c) 2016 wxWidgets development team
# Licence:     wxWindows licence
#############################################################################

wx_append_sources(STC_FILES STC_CMN)

if(WXOSX_COCOA)
    wx_append_sources(STC_FILES STC_OSX_COCOA)
endif()

wx_add_builtin_library(wxscintilla
    src/stc/scintilla/lexers/LexA68k.cxx
    src/stc/scintilla/lexers/LexAbaqus.cxx
    src/stc/scintilla/lexers/LexAda.cxx
    src/stc/scintilla/lexers/LexAPDL.cxx
    src/stc/scintilla/lexers/LexAsm.cxx
    src/stc/scintilla/lexers/LexAsn1.cxx
    src/stc/scintilla/lexers/LexASY.cxx
    src/stc/scintilla/lexers/LexAU3.cxx
    src/stc/scintilla/lexers/LexAVE.cxx
    src/stc/scintilla/lexers/LexAVS.cxx
    src/stc/scintilla/lexers/LexBaan.cxx
    src/stc/scintilla/lexers/LexBash.cxx
    src/stc/scintilla/lexers/LexBasic.cxx
    src/stc/scintilla/lexers/LexBatch.cxx
    src/stc/scintilla/lexers/LexBibTeX.cxx
    src/stc/scintilla/lexers/LexBullant.cxx
    src/stc/scintilla/lexers/LexCaml.cxx
    src/stc/scintilla/lexers/LexCIL.cxx
    src/stc/scintilla/lexers/LexCLW.cxx
    src/stc/scintilla/lexers/LexCmake.cxx
    src/stc/scintilla/lexers/LexCOBOL.cxx
    src/stc/scintilla/lexers/LexCoffeeScript.cxx
    src/stc/scintilla/lexers/LexConf.cxx
    src/stc/scintilla/lexers/LexCPP.cxx
    src/stc/scintilla/lexers/LexCrontab.cxx
    src/stc/scintilla/lexers/LexCsound.cxx
    src/stc/scintilla/lexers/LexCSS.cxx
    src/stc/scintilla/lexers/LexD.cxx
    src/stc/scintilla/lexers/LexDataflex.cxx
    src/stc/scintilla/lexers/LexDiff.cxx
    src/stc/scintilla/lexers/LexDMAP.cxx
    src/stc/scintilla/lexers/LexDMIS.cxx
    src/stc/scintilla/lexers/LexECL.cxx
    src/stc/scintilla/lexers/LexEDIFACT.cxx
    src/stc/scintilla/lexers/LexEiffel.cxx
    src/stc/scintilla/lexers/LexErlang.cxx
    src/stc/scintilla/lexers/LexErrorList.cxx
    src/stc/scintilla/lexers/LexEScript.cxx
    src/stc/scintilla/lexers/LexFlagship.cxx
    src/stc/scintilla/lexers/LexForth.cxx
    src/stc/scintilla/lexers/LexFortran.cxx
    src/stc/scintilla/lexers/LexGAP.cxx
    src/stc/scintilla/lexers/LexGui4Cli.cxx
    src/stc/scintilla/lexers/LexHaskell.cxx
    src/stc/scintilla/lexers/LexHollywood.cxx
    src/stc/scintilla/lexers/LexHex.cxx
    src/stc/scintilla/lexers/LexHollywood.cxx
    src/stc/scintilla/lexers/LexHTML.cxx
    src/stc/scintilla/lexers/LexIndent.cxx
    src/stc/scintilla/lexers/LexInno.cxx
    src/stc/scintilla/lexers/LexJSON.cxx
    src/stc/scintilla/lexers/LexKix.cxx
    src/stc/scintilla/lexers/LexKVIrc.cxx
    src/stc/scintilla/lexers/LexLaTeX.cxx
    src/stc/scintilla/lexers/LexLisp.cxx
    src/stc/scintilla/lexers/LexLout.cxx
    src/stc/scintilla/lexers/LexLPeg.cxx
    src/stc/scintilla/lexers/LexLua.cxx
    src/stc/scintilla/lexers/LexMagik.cxx
    src/stc/scintilla/lexers/LexMake.cxx
    src/stc/scintilla/lexers/LexMarkdown.cxx
    src/stc/scintilla/lexers/LexMatlab.cxx
    src/stc/scintilla/lexers/LexMaxima.cxx
    src/stc/scintilla/lexers/LexMetapost.cxx
    src/stc/scintilla/lexers/LexMMIXAL.cxx
    src/stc/scintilla/lexers/LexModula.cxx
    src/stc/scintilla/lexers/LexMPT.cxx
    src/stc/scintilla/lexers/LexMSSQL.cxx
    src/stc/scintilla/lexers/LexMySQL.cxx
    src/stc/scintilla/lexers/LexNim.cxx
    src/stc/scintilla/lexers/LexNimrod.cxx
    src/stc/scintilla/lexers/LexNsis.cxx
    src/stc/scintilla/lexers/LexNull.cxx
    src/stc/scintilla/lexers/LexOpal.cxx
    src/stc/scintilla/lexers/LexOScript.cxx
    src/stc/scintilla/lexers/LexPascal.cxx
    src/stc/scintilla/lexers/LexPB.cxx
    src/stc/scintilla/lexers/LexPerl.cxx
    src/stc/scintilla/lexers/LexPLM.cxx
    src/stc/scintilla/lexers/LexPO.cxx
    src/stc/scintilla/lexers/LexPOV.cxx
    src/stc/scintilla/lexers/LexPowerPro.cxx
    src/stc/scintilla/lexers/LexPowerShell.cxx
    src/stc/scintilla/lexers/LexProgress.cxx
    src/stc/scintilla/lexers/LexProps.cxx
    src/stc/scintilla/lexers/LexPS.cxx
    src/stc/scintilla/lexers/LexPython.cxx
    src/stc/scintilla/lexers/LexR.cxx
    src/stc/scintilla/lexers/LexRaku.cxx
    src/stc/scintilla/lexers/LexRebol.cxx
    src/stc/scintilla/lexers/LexRegistry.cxx
    src/stc/scintilla/lexers/LexRuby.cxx
    src/stc/scintilla/lexers/LexRust.cxx
    src/stc/scintilla/lexers/LexSAS.cxx
    src/stc/scintilla/lexers/LexScriptol.cxx
    src/stc/scintilla/lexers/LexSmalltalk.cxx
    src/stc/scintilla/lexers/LexSML.cxx
    src/stc/scintilla/lexers/LexSorcus.cxx
    src/stc/scintilla/lexers/LexSpecman.cxx
    src/stc/scintilla/lexers/LexSpice.cxx
    src/stc/scintilla/lexers/LexSQL.cxx
    src/stc/scintilla/lexers/LexStata.cxx
    src/stc/scintilla/lexers/LexSTTXT.cxx
    src/stc/scintilla/lexers/LexTACL.cxx
    src/stc/scintilla/lexers/LexTADS3.cxx
    src/stc/scintilla/lexers/LexTAL.cxx
    src/stc/scintilla/lexers/LexTCL.cxx
    src/stc/scintilla/lexers/LexTCMD.cxx
    src/stc/scintilla/lexers/LexTeX.cxx
    src/stc/scintilla/lexers/LexTxt2tags.cxx
    src/stc/scintilla/lexers/LexVB.cxx
    src/stc/scintilla/lexers/LexVerilog.cxx
    src/stc/scintilla/lexers/LexVHDL.cxx
    src/stc/scintilla/lexers/LexVisualProlog.cxx
    src/stc/scintilla/lexers/LexX12.cxx
    src/stc/scintilla/lexers/LexYAML.cxx
    src/stc/scintilla/lexlib/Accessor.cxx
    src/stc/scintilla/lexlib/CharacterCategory.cxx
    src/stc/scintilla/lexlib/CharacterSet.cxx
    src/stc/scintilla/lexlib/DefaultLexer.cxx
    src/stc/scintilla/lexlib/LexerBase.cxx
    src/stc/scintilla/lexlib/LexerModule.cxx
    src/stc/scintilla/lexlib/LexerNoExceptions.cxx
    src/stc/scintilla/lexlib/LexerSimple.cxx
    src/stc/scintilla/lexlib/PropSetSimple.cxx
    src/stc/scintilla/lexlib/StyleContext.cxx
    src/stc/scintilla/lexlib/WordList.cxx
    src/stc/scintilla/src/AutoComplete.cxx
    src/stc/scintilla/src/CallTip.cxx
    src/stc/scintilla/src/CaseConvert.cxx
    src/stc/scintilla/src/CaseFolder.cxx
    src/stc/scintilla/src/Catalogue.cxx
    src/stc/scintilla/src/CellBuffer.cxx
    src/stc/scintilla/src/CharClassify.cxx
    src/stc/scintilla/src/ContractionState.cxx
    src/stc/scintilla/src/DBCS.cxx
    src/stc/scintilla/src/Decoration.cxx
    src/stc/scintilla/src/Document.cxx
    src/stc/scintilla/src/EditModel.cxx
    src/stc/scintilla/src/Editor.cxx
    src/stc/scintilla/src/EditView.cxx
    src/stc/scintilla/src/ExternalLexer.cxx
    src/stc/scintilla/src/Indicator.cxx
    src/stc/scintilla/src/KeyMap.cxx
    src/stc/scintilla/src/LineMarker.cxx
    src/stc/scintilla/src/MarginView.cxx
    src/stc/scintilla/src/PerLine.cxx
    src/stc/scintilla/src/PositionCache.cxx
    src/stc/scintilla/src/RESearch.cxx
    src/stc/scintilla/src/RunStyles.cxx
    src/stc/scintilla/src/ScintillaBase.cxx
    src/stc/scintilla/src/Selection.cxx
    src/stc/scintilla/src/Style.cxx
    src/stc/scintilla/src/UniConversion.cxx
    src/stc/scintilla/src/UniqueString.cxx
    src/stc/scintilla/src/ViewStyle.cxx
    src/stc/scintilla/src/XPM.cxx
)
target_include_directories(wxscintilla PRIVATE
    ${wxSOURCE_DIR}/src/stc/scintilla/include
    ${wxSOURCE_DIR}/src/stc/scintilla/lexlib
    ${wxSOURCE_DIR}/src/stc/scintilla/src
)
target_compile_definitions(wxscintilla PRIVATE
    __WX__
    SCI_LEXER
    LINK_LEXERS
    LPEG_LEXER=0
)

wx_target_enable_precomp(wxscintilla "${wxSOURCE_DIR}/src/stc/scintilla/include/Scintilla.h")
wx_add_library(wxstc ${STC_FILES})
wx_lib_include_directories(wxstc
    ${wxSOURCE_DIR}/src/stc/scintilla/include
    ${wxSOURCE_DIR}/src/stc/scintilla/lexlib
    ${wxSOURCE_DIR}/src/stc/scintilla/src
)
wx_lib_compile_definitions(wxstc
    __WX__
    SCI_LEXER
    LINK_LEXERS
)
wx_lib_link_libraries(wxstc PRIVATE wxscintilla)
if(WXMSW)
    wx_lib_link_libraries(wxstc PRIVATE imm32)
endif()

if(WXUWP)
    wx_lib_link_libraries(wxstc PRIVATE imm32)
endif()

