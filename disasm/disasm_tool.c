//
// tool to generate P2 disassembler table
//

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "instr.h"

Instruction
instr_p2[] = {
    { "nop",    0x00000000, NO_OPERANDS,  OPC_NOP, 0 },
    { "ror",    0x00000000, TWO_OPERANDS, OPC_ROR, FLAG_P2_STD },
    { "rol",    0x00200000, TWO_OPERANDS, OPC_ROL, FLAG_P2_STD },
    { "shr",    0x00400000, TWO_OPERANDS, OPC_SHR, FLAG_P2_STD },
    { "shl",    0x00600000, TWO_OPERANDS, OPC_SHL, FLAG_P2_STD },
    { "rcr",    0x00800000, TWO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },
    { "rcl",    0x00a00000, TWO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },
    { "sar",    0x00c00000, TWO_OPERANDS, OPC_SAR, FLAG_P2_STD },
    { "sal",    0x00e00000, TWO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },
    { "add",    0x01000000, TWO_OPERANDS, OPC_ADD, FLAG_P2_STD },
    { "addx",   0x01200000, TWO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },
    { "adds",   0x01400000, TWO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },
    { "addsx",  0x01600000, TWO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },
    { "sub",    0x01800000, TWO_OPERANDS, OPC_SUB, FLAG_P2_STD },
    { "subx",   0x01a00000, TWO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },
    { "subs",   0x01c00000, TWO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },
    { "subsx",  0x01e00000, TWO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },

    { "cmp",    0x02000000, TWO_OPERANDS, OPC_CMP, FLAG_P2_STD | FLAG_WARN_NOTUSED },
    { "cmpx",   0x02200000, TWO_OPERANDS, OPC_GENERIC, FLAG_P2_STD | FLAG_WARN_NOTUSED },
    { "cmps",   0x02400000, TWO_OPERANDS, OPC_CMPS, FLAG_P2_STD | FLAG_WARN_NOTUSED },
    { "cmpsx",  0x02600000, TWO_OPERANDS, OPC_GENERIC, FLAG_P2_STD | FLAG_WARN_NOTUSED },
    { "cmpr",   0x02800000, TWO_OPERANDS, OPC_GENERIC, FLAG_P2_STD | FLAG_WARN_NOTUSED },
    { "cmpm",   0x02a00000, TWO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },
    { "subr",   0x02c00000, TWO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },
    { "cmpsub", 0x02e00000, TWO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },

    { "fge",    0x03000000, TWO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },
    { "fle",    0x03200000, TWO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },
    { "fges",   0x03400000, TWO_OPERANDS, OPC_MINS, FLAG_P2_STD },
    { "fles",   0x03600000, TWO_OPERANDS, OPC_MAXS, FLAG_P2_STD },

    { "sumc",   0x03800000, TWO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },
    { "sumnc",  0x03a00000, TWO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },
    { "sumz",   0x03c00000, TWO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },
    { "sumnz",  0x03e00000, TWO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },

    { "testb",   0x04000000, TWO_OPERANDS, OPC_GENERIC, FLAG_P2_CZTEST },
    { "testbn",  0x04200000, TWO_OPERANDS, OPC_GENERIC, FLAG_P2_CZTEST },

    { "bitl",   0x04000000, TWO_OPERANDS, OPC_GENERIC, FLAG_WCZ },
    { "bith",   0x04200000, TWO_OPERANDS, OPC_GENERIC, FLAG_WCZ },
    { "bitc",   0x04400000, TWO_OPERANDS, OPC_GENERIC, FLAG_WCZ },
    { "bitnc",  0x04600000, TWO_OPERANDS, OPC_GENERIC, FLAG_WCZ },
    { "bitz",   0x04800000, TWO_OPERANDS, OPC_GENERIC, FLAG_WCZ },
    { "bitnz",  0x04a00000, TWO_OPERANDS, OPC_GENERIC, FLAG_WCZ },
    { "bitrnd", 0x04c00000, TWO_OPERANDS, OPC_GENERIC, FLAG_WCZ },
    { "bitnot", 0x04e00000, TWO_OPERANDS, OPC_GENERIC, FLAG_WCZ },

    { "and",    0x05000000, TWO_OPERANDS, OPC_AND, FLAG_P2_STD },
    { "andn",   0x05200000, TWO_OPERANDS, OPC_ANDN, FLAG_P2_STD },
    { "or",     0x05400000, TWO_OPERANDS, OPC_OR, FLAG_P2_STD },
    { "xor",    0x05600000, TWO_OPERANDS, OPC_XOR, FLAG_P2_STD },
    { "muxc",   0x05800000, TWO_OPERANDS, OPC_MUXC, FLAG_P2_STD },
    { "muxnc",  0x05a00000, TWO_OPERANDS, OPC_MUXNC, FLAG_P2_STD },
    { "muxz",   0x05c00000, TWO_OPERANDS, OPC_MUXZ, FLAG_P2_STD },
    { "muxnz",  0x05e00000, TWO_OPERANDS, OPC_MUXNZ, FLAG_P2_STD },

    { "mov",    0x06000000, TWO_OPERANDS, OPC_MOV, FLAG_P2_STD },
    { "not",    0x06200000, TWO_OPERANDS_OPTIONAL, OPC_NOT, FLAG_P2_STD },
    { "abs",    0x06400000, TWO_OPERANDS_OPTIONAL, OPC_ABS, FLAG_P2_STD },
    { "neg",    0x06600000, TWO_OPERANDS_OPTIONAL, OPC_NEG, FLAG_P2_STD },
    { "negc",   0x06800000, TWO_OPERANDS_OPTIONAL, OPC_GENERIC, FLAG_P2_STD },
    { "negnc",  0x06a00000, TWO_OPERANDS_OPTIONAL, OPC_GENERIC, FLAG_P2_STD },
    { "negz",   0x06c00000, TWO_OPERANDS_OPTIONAL, OPC_GENERIC, FLAG_P2_STD },
    { "negnz",  0x06e00000, TWO_OPERANDS_OPTIONAL, OPC_GENERIC, FLAG_P2_STD },

    { "incmod", 0x07000000, TWO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },
    { "decmod", 0x07200000, TWO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },
    { "zerox",  0x07400000, TWO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },
    { "signx",  0x07600000, TWO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },

    { "encod",  0x07800000, TWO_OPERANDS_OPTIONAL, OPC_ENCOD, FLAG_P2_STD },
    { "ones",   0x07a00000, TWO_OPERANDS_OPTIONAL, OPC_GENERIC, FLAG_P2_STD },

    { "test",   0x07c00000, TWO_OPERANDS_OPTIONAL, OPC_TEST, FLAG_P2_STD|FLAG_WARN_NOTUSED },
    { "testn",  0x07e00000, TWO_OPERANDS, OPC_GENERIC_NR, FLAG_P2_STD|FLAG_WARN_NOTUSED },

    { "setnib", 0x08000000, THREE_OPERANDS_NIBBLE, OPC_GENERIC, 0 },
    { "getnib", 0x08400000, THREE_OPERANDS_NIBBLE, OPC_GENERIC, 0 },
    { "rolnib", 0x08800000, THREE_OPERANDS_NIBBLE, OPC_GENERIC, 0 },
    { "setbyte", 0x08c00000, THREE_OPERANDS_BYTE, OPC_GENERIC, 0 },
    { "getbyte", 0x08e00000, THREE_OPERANDS_BYTE, OPC_GENERIC, 0 },
    { "rolbyte", 0x09000000, THREE_OPERANDS_BYTE, OPC_GENERIC, 0 },
    { "setword", 0x09200000, THREE_OPERANDS_WORD, OPC_GENERIC, 0 },
    { "getword", 0x09300000, THREE_OPERANDS_WORD, OPC_GENERIC, 0 },
    { "rolword", 0x09400000, THREE_OPERANDS_WORD, OPC_GENERIC, 0 },

    { "altsn",  0x09500000, TWO_OPERANDS_DEFZ, OPC_GENERIC, 0 },
    { "altgn",  0x09580000, TWO_OPERANDS_DEFZ, OPC_GENERIC, 0 },
    { "altsb",  0x09600000, TWO_OPERANDS_DEFZ, OPC_GENERIC, 0 },
    { "altgb",  0x09680000, TWO_OPERANDS_DEFZ, OPC_GENERIC, 0 },
    { "altsw",  0x09700000, TWO_OPERANDS_DEFZ, OPC_GENERIC, 0 },
    { "altgw",  0x09780000, TWO_OPERANDS_DEFZ, OPC_GENERIC, 0 },
    { "altr",   0x09800000, TWO_OPERANDS_DEFZ, OPC_GENERIC, 0 },
    { "altd",   0x09880000, TWO_OPERANDS_DEFZ, OPC_ALTD, 0 },
    { "alts",   0x09900000, TWO_OPERANDS_DEFZ, OPC_ALTS, 0 },
    { "altb",   0x09980000, TWO_OPERANDS_DEFZ, OPC_GENERIC, 0 },
    { "alti",   0x09a00000, TWO_OPERANDS_DEFZ, OPC_GENERIC, 0 },
    { "setr",   0x09a80000, TWO_OPERANDS, OPC_GENERIC, 0 },
    { "setd",   0x09b00000, TWO_OPERANDS, OPC_GENERIC, 0 },
    { "sets",   0x09b80000, TWO_OPERANDS, OPC_GENERIC, 0 },

    { "decod",  0x09c00000, TWO_OPERANDS_OPTIONAL, OPC_DECOD, 0 },
    { "bmask",  0x09c80000, TWO_OPERANDS_OPTIONAL, OPC_GENERIC, 0 },
    
    { "crcbit", 0x09d00000, TWO_OPERANDS, OPC_GENERIC, 0 },
    { "crcnib", 0x09d80000, TWO_OPERANDS, OPC_GENERIC, 0 },
    
    { "muxnits", 0x09e00000, TWO_OPERANDS, OPC_GENERIC, 0 },
    { "muxnibs", 0x09e80000, TWO_OPERANDS, OPC_GENERIC, 0 },
    { "muxq",   0x09f00000, TWO_OPERANDS, OPC_GENERIC, 0 },
    { "movbyts", 0x09f80000, TWO_OPERANDS, OPC_GENERIC, 0 },

    { "mul",    0x0a000000, TWO_OPERANDS, OPC_GENERIC, FLAG_WZ },
    { "muls",   0x0a100000, TWO_OPERANDS, OPC_GENERIC, FLAG_WZ },
    { "sca",    0x0a200000, TWO_OPERANDS, OPC_GENERIC, FLAG_WZ },
    { "scas",   0x0a300000, TWO_OPERANDS, OPC_GENERIC, FLAG_WZ },

    { "addpix", 0x0a400000, TWO_OPERANDS, OPC_GENERIC, 0 },
    { "mulpix", 0x0a480000, TWO_OPERANDS, OPC_GENERIC, 0 },
    { "blnpix", 0x0a500000, TWO_OPERANDS, OPC_GENERIC, 0 },
    { "mixpix", 0x0a580000, TWO_OPERANDS, OPC_GENERIC, 0 },

    { "addct1", 0x0a600000, TWO_OPERANDS, OPC_ADDCT1, 0 },
    { "addct2", 0x0a680000, TWO_OPERANDS, OPC_GENERIC, 0 },
    { "addct3", 0x0a700000, TWO_OPERANDS, OPC_GENERIC, 0 },
    { "wmlong", 0x0a780000, P2_RDWR_OPERANDS, OPC_GENERIC, 0 },

    { "rqpin",  0x0a800000, TWO_OPERANDS, OPC_GENERIC, FLAG_WC },
    { "rdpin",  0x0a880000, TWO_OPERANDS, OPC_GENERIC, FLAG_WC },
    { "rdlut",  0x0aa00000, TWO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },
  
    { "rdbyte", 0x0ac00000, P2_RDWR_OPERANDS, OPC_RDBYTE, FLAG_P2_STD },
    { "rdword", 0x0ae00000, P2_RDWR_OPERANDS, OPC_RDWORD, FLAG_P2_STD },
    { "rdlong", 0x0b000000, P2_RDWR_OPERANDS, OPC_RDLONG, FLAG_P2_STD },

    { "calld",  0x0b200000, P2_TJZ_OPERANDS, OPC_GENERIC_BRANCH, FLAG_P2_STD },
    { "reti0",  0x0b3bffff, NO_OPERANDS, OPC_GENERIC_BRANCH, FLAG_P2_STD },
    { "reti1",  0x0b3bfff5, NO_OPERANDS, OPC_GENERIC_BRANCH, FLAG_P2_STD },
    { "reti2",  0x0b3bfff3, NO_OPERANDS, OPC_GENERIC_BRANCH, FLAG_P2_STD },
    { "reti3",  0x0b3bfff1, NO_OPERANDS, OPC_GENERIC_BRANCH, FLAG_P2_STD },
    { "resi0",  0x0b3bfdff, NO_OPERANDS, OPC_GENERIC_BRANCH, FLAG_P2_STD },
    { "resi1",  0x0b3be9f5, NO_OPERANDS, OPC_GENERIC_BRANCH, FLAG_P2_STD },
    { "resi2",  0x0b3be5f3, NO_OPERANDS, OPC_GENERIC_BRANCH, FLAG_P2_STD },
    { "resi3",  0x0b3be1f1, NO_OPERANDS, OPC_GENERIC_BRANCH, FLAG_P2_STD },

    { "callpa", 0x0b400000, P2_TJZ_OPERANDS, OPC_GENERIC_BRANCH, 0 },
    { "callpb", 0x0b500000, P2_TJZ_OPERANDS, OPC_GENERIC_BRANCH, 0 },

    { "djz",    0x0b600000, P2_TJZ_OPERANDS, OPC_GENERIC_BRANCH, 0 },
    { "djnz",   0x0b680000, P2_TJZ_OPERANDS, OPC_DJNZ, 0 },
    { "djf",    0x0b700000, P2_TJZ_OPERANDS, OPC_GENERIC_BRANCH, 0 },
    { "djnf",   0x0b780000, P2_TJZ_OPERANDS, OPC_GENERIC_BRANCH, 0 },
    { "ijz",    0x0b800000, P2_TJZ_OPERANDS, OPC_GENERIC_BRANCH, 0 },
    { "ijnz",   0x0b880000, P2_TJZ_OPERANDS, OPC_GENERIC_BRANCH, 0 },
    { "tjz",    0x0b900000, P2_TJZ_OPERANDS, OPC_GENERIC_BRANCH, 0 },
    { "tjnz",   0x0b980000, P2_TJZ_OPERANDS, OPC_GENERIC_BRANCH, 0 },
    { "tjf",    0x0ba00000, P2_TJZ_OPERANDS, OPC_GENERIC_BRANCH, 0 },
    { "tjnf",   0x0ba80000, P2_TJZ_OPERANDS, OPC_GENERIC_BRANCH, 0 },
    { "tjs",    0x0bb00000, P2_TJZ_OPERANDS, OPC_GENERIC_BRANCH, 0 },
    { "tjns",   0x0bb80000, P2_TJZ_OPERANDS, OPC_GENERIC_BRANCH, 0 },
    { "tjv",    0x0bc00000, P2_TJZ_OPERANDS, OPC_GENERIC_BRANCH, 0 },

//  { "jp",     0x0ba00000, P2_TJZ_OPERANDS, OPC_GENERIC_BRANCH },
//  { "jnp",    0x0bb00000, P2_TJZ_OPERANDS, OPC_GENERIC_BRANCH },
    

    { "jint",   0x0bc80000, P2_JINT_OPERANDS, OPC_GENERIC_BRANCH, 0 },
    { "jct1",   0x0bc80200, P2_JINT_OPERANDS, OPC_GENERIC_BRANCH, 0 },
    { "jct2",   0x0bc80400, P2_JINT_OPERANDS, OPC_GENERIC_BRANCH, 0 },
    { "jct3",   0x0bc80600, P2_JINT_OPERANDS, OPC_GENERIC_BRANCH, 0 },
    { "jse1",   0x0bc80800, P2_JINT_OPERANDS, OPC_GENERIC_BRANCH, 0 },
    { "jse2",   0x0bc80a00, P2_JINT_OPERANDS, OPC_GENERIC_BRANCH, 0 },
    { "jse3",   0x0bc80c00, P2_JINT_OPERANDS, OPC_GENERIC_BRANCH, 0 },
    { "jse4",   0x0bc80e00, P2_JINT_OPERANDS, OPC_GENERIC_BRANCH, 0 },
    { "jpat",   0x0bc81000, P2_JINT_OPERANDS, OPC_GENERIC_BRANCH, 0 },
    { "jfbw",   0x0bc81200, P2_JINT_OPERANDS, OPC_GENERIC_BRANCH, 0 },
    { "jxmt",   0x0bc81400, P2_JINT_OPERANDS, OPC_GENERIC_BRANCH, 0 },
    { "jxfi",   0x0bc81600, P2_JINT_OPERANDS, OPC_GENERIC_BRANCH, 0 },
    { "jxro",   0x0bc81800, P2_JINT_OPERANDS, OPC_GENERIC_BRANCH, 0 },
    { "jxrl",   0x0bc81a00, P2_JINT_OPERANDS, OPC_GENERIC_BRANCH, 0 },
    { "jatn",   0x0bc81c00, P2_JINT_OPERANDS, OPC_GENERIC_BRANCH, 0 },
    { "jqmt",   0x0bc81e00, P2_JINT_OPERANDS, OPC_GENERIC_BRANCH, 0 },

    { "jnint",  0x0bc82000, P2_JINT_OPERANDS, OPC_GENERIC_BRANCH, 0 },
    { "jnct1",  0x0bc82200, P2_JINT_OPERANDS, OPC_GENERIC_BRANCH, 0 },
    { "jnct2",  0x0bc82400, P2_JINT_OPERANDS, OPC_GENERIC_BRANCH, 0 },
    { "jnct3",  0x0bc82600, P2_JINT_OPERANDS, OPC_GENERIC_BRANCH, 0 },
    { "jnse1",  0x0bc82800, P2_JINT_OPERANDS, OPC_GENERIC_BRANCH, 0 },
    { "jnse2",  0x0bc82a00, P2_JINT_OPERANDS, OPC_GENERIC_BRANCH, 0 },
    { "jnse3",  0x0bc82c00, P2_JINT_OPERANDS, OPC_GENERIC_BRANCH, 0 },
    { "jnse4",  0x0bc82e00, P2_JINT_OPERANDS, OPC_GENERIC_BRANCH, 0 },
    { "jnpat",  0x0bc83000, P2_JINT_OPERANDS, OPC_GENERIC_BRANCH, 0 },
    { "jnfbw",  0x0bc83200, P2_JINT_OPERANDS, OPC_GENERIC_BRANCH, 0 },
    { "jnxmt",  0x0bc83400, P2_JINT_OPERANDS, OPC_GENERIC_BRANCH, 0 },
    { "jnxfi",  0x0bc83600, P2_JINT_OPERANDS, OPC_GENERIC_BRANCH, 0 },
    { "jnxro",  0x0bc83800, P2_JINT_OPERANDS, OPC_GENERIC_BRANCH, 0 },
    { "jnxrl",  0x0bc83a00, P2_JINT_OPERANDS, OPC_GENERIC_BRANCH, 0 },
    { "jnatn",  0x0bc83c00, P2_JINT_OPERANDS, OPC_GENERIC_BRANCH, 0 },
    { "jnqmt",  0x0bc83e00, P2_JINT_OPERANDS, OPC_GENERIC_BRANCH, 0 },

    { "setpat", 0x0bf00000, P2_TWO_OPERANDS, OPC_GENERIC, 0 },
    { "wrpin",  0x0c000000, P2_TWO_OPERANDS, OPC_GENERIC, 0 },
    { "akpin",  0x0c080200, SRC_OPERAND_ONLY, OPC_GENERIC, 0 },
    { "wxpin",  0x0c100000, P2_TWO_OPERANDS, OPC_GENERIC, 0 },
    { "wypin",  0x0c200000, P2_TWO_OPERANDS, OPC_GENERIC, 0 },
    { "wrlut",  0x0c300000, P2_TWO_OPERANDS, OPC_GENERIC, 0 },

    { "wrbyte", 0x0c400000, P2_RDWR_OPERANDS, OPC_WRBYTE, 0 },
    { "wrword", 0x0c500000, P2_RDWR_OPERANDS, OPC_WRWORD, 0 },
    { "wrlong", 0x0c600000, P2_RDWR_OPERANDS, OPC_WRLONG, 0 },

    // some aliases for wrlong x, ptra++ etc.
    { "pusha",  0x0c600161, TWO_OPERANDS_DEFZ, OPC_GENERIC, 0 },
    { "pushb",  0x0c6001e1, TWO_OPERANDS_DEFZ, OPC_GENERIC, 0 },

    { "rdfast", 0x0c700000, P2_TWO_OPERANDS, OPC_GENERIC, 0 },
    { "wrfast", 0x0c800000, P2_TWO_OPERANDS, OPC_GENERIC, 0 },
    { "fblock", 0x0c900000, P2_TWO_OPERANDS, OPC_GENERIC, 0 },

    { "xinit",  0x0ca00000, P2_TWO_OPERANDS, OPC_GENERIC, 0 },
    { "xstop",  0x0cac0000, NO_OPERANDS, OPC_GENERIC, 0 },
    { "xzero",  0x0cb00000, P2_TWO_OPERANDS, OPC_GENERIC, 0 },
    { "xcont",  0x0cc00000, P2_TWO_OPERANDS, OPC_GENERIC, 0 },

    { "rep",    0x0cd00000, P2_TWO_OPERANDS, OPC_REPEAT, 0 },
  
    { "coginit",0x0ce00000, P2_TWO_OPERANDS, OPC_GENERIC, FLAG_WC },
    { "qmul",   0x0d000000, P2_TWO_OPERANDS, OPC_GENERIC, 0 },
    { "qdiv",   0x0d100000, P2_TWO_OPERANDS, OPC_GENERIC, 0 },
    { "qfrac",  0x0d200000, P2_TWO_OPERANDS, OPC_GENERIC, 0 },
    { "qsqrt",  0x0d300000, P2_TWO_OPERANDS, OPC_GENERIC, 0 },
    { "qrotate",0x0d400000, P2_TWO_OPERANDS, OPC_GENERIC, 0 },
    { "qvector",0x0d500000, P2_TWO_OPERANDS, OPC_GENERIC, 0 },

    { "hubset", 0x0d600000, P2_DST_CONST_OK,  OPC_HUBSET, 0 },
    { "cogid",  0x0d600001, P2_DST_CONST_OK,  OPC_COGID, FLAG_WC },
    { "cogstop",0x0d600003, P2_DST_CONST_OK,  OPC_COGSTOP, 0 },
    { "locknew",0x0d600004, DST_OPERAND_ONLY, OPC_GENERIC, FLAG_WC },
    { "lockret",0x0d600005, P2_DST_CONST_OK, OPC_GENERIC_NR, 0 },
    { "locktry",0x0d600006, P2_DST_CONST_OK, OPC_GENERIC_NR, FLAG_WC },
    { "lockrel",0x0d600007, P2_DST_CONST_OK, OPC_GENERIC_NR, FLAG_WC },

    { "qlog",   0x0d60000e, P2_DST_CONST_OK, OPC_GENERIC, 0 },
    { "qexp",   0x0d60000f, P2_DST_CONST_OK, OPC_GENERIC, 0 },
  
    { "rfbyte", 0x0d600010, DST_OPERAND_ONLY, OPC_GENERIC, FLAG_P2_STD },
    { "rfword", 0x0d600011, DST_OPERAND_ONLY, OPC_GENERIC, FLAG_P2_STD },
    { "rflong", 0x0d600012, DST_OPERAND_ONLY, OPC_GENERIC, FLAG_P2_STD },
    { "rfvar",  0x0d600013, DST_OPERAND_ONLY, OPC_GENERIC, FLAG_P2_STD },
    { "rfvars", 0x0d600014, DST_OPERAND_ONLY, OPC_GENERIC, FLAG_P2_STD },
    
    { "wfbyte", 0x0d600015, P2_DST_CONST_OK, OPC_GENERIC, 0 },
    { "wfword", 0x0d600016, P2_DST_CONST_OK, OPC_GENERIC, 0 },
    { "wflong", 0x0d600017, P2_DST_CONST_OK, OPC_GENERIC, 0 },

    { "getqx",  0x0d600018, DST_OPERAND_ONLY, OPC_GENERIC, FLAG_P2_STD },
    { "getqy",  0x0d600019, DST_OPERAND_ONLY, OPC_GENERIC, FLAG_P2_STD },
    { "getct",  0x0d60001a, DST_OPERAND_ONLY, OPC_GENERIC, 0 },
    { "getrnd", 0x0d60001b, DST_OPERAND_ONLY, OPC_GENERIC, FLAG_P2_STD },

    { "setdacs",0x0d60001c, P2_DST_CONST_OK, OPC_GENERIC, 0 },
    { "setxfrq",0x0d60001d, P2_DST_CONST_OK, OPC_GENERIC, 0 },
    { "getxacc",0x0d60001e, DST_OPERAND_ONLY, OPC_GENERIC, 0 },
    { "waitx",  0x0d60001f, P2_DST_CONST_OK, OPC_GENERIC, FLAG_P2_STD },
  
    { "setse1", 0x0d600020, P2_DST_CONST_OK, OPC_GENERIC, 0 },
    { "setse2", 0x0d600021, P2_DST_CONST_OK, OPC_GENERIC, 0 },
    { "setse3", 0x0d600022, P2_DST_CONST_OK, OPC_GENERIC, 0 },
    { "setse4", 0x0d600023, P2_DST_CONST_OK, OPC_GENERIC, 0 },
  
    { "pollint",0x0d600024, NO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },
    { "pollct1",0x0d600224, NO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },
    { "pollct2",0x0d600424, NO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },
    { "pollct3",0x0d600624, NO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },
    { "pollse1",0x0d600824, NO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },
    { "pollse2",0x0d600a24, NO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },
    { "pollse3",0x0d600c24, NO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },
    { "pollse4",0x0d600e24, NO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },
    { "pollpat",0x0d601024, NO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },
    { "pollfbw",0x0d601224, NO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },
    { "pollxmt",0x0d601424, NO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },
    { "pollxfi",0x0d601624, NO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },
    { "pollxro",0x0d601824, NO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },
    { "pollxrl",0x0d601a24, NO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },
    { "pollatn",0x0d601c24, NO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },
    { "pollqmt",0x0d601e24, NO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },
  
    { "waitint",0x0d602024, NO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },
    { "waitct1",0x0d602224, NO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },
    { "waitct2",0x0d602424, NO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },
    { "waitct3",0x0d602624, NO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },
    { "waitse1",0x0d602824, NO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },
    { "waitse2",0x0d602a24, NO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },
    { "waitse3",0x0d602c24, NO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },
    { "waitse4",0x0d602e24, NO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },
    { "waitpat",0x0d603024, NO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },
    { "waitfbw",0x0d603224, NO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },
    { "waitxmt",0x0d603424, NO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },
    { "waitxfi",0x0d603624, NO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },
    { "waitxro",0x0d603824, NO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },
    { "waitxrl",0x0d603a24, NO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },
    { "waitatn",0x0d603c24, NO_OPERANDS, OPC_GENERIC, FLAG_P2_STD },

    { "allowi", 0x0d604024, NO_OPERANDS, OPC_GENERIC, 0 },
    { "stalli", 0x0d604224, NO_OPERANDS, OPC_GENERIC, 0 },
    { "trgint1",0x0d604424, NO_OPERANDS, OPC_GENERIC, 0 },
    { "trgint2",0x0d604624, NO_OPERANDS, OPC_GENERIC, 0 },
    { "trgint3",0x0d604824, NO_OPERANDS, OPC_GENERIC, 0 },

    { "nixint1",0x0d604a24, NO_OPERANDS, OPC_GENERIC, 0 },
    { "nixint2",0x0d604c24, NO_OPERANDS, OPC_GENERIC, 0 },
    { "nixint3",0x0d604e24, NO_OPERANDS, OPC_GENERIC, 0 },
  
    { "setint1",0x0d600025, P2_DST_CONST_OK, OPC_GENERIC, 0 },
    { "setint2",0x0d600026, P2_DST_CONST_OK, OPC_GENERIC, 0 },
    { "setint3",0x0d600027, P2_DST_CONST_OK, OPC_GENERIC, 0 },

    { "setq",   0x0d600028, P2_DST_CONST_OK, OPC_GENERIC_NR, 0 },
    { "setq2",  0x0d600029, P2_DST_CONST_OK, OPC_GENERIC_NR, 0 },

    { "push",   0x0d60002a, P2_DST_CONST_OK, OPC_GENERIC, 0 },
    { "pop",    0x0d60002b, DST_OPERAND_ONLY, OPC_GENERIC, FLAG_P2_STD },

  // indirect jumps via register
  // normally the user will write "jmp x" and the assembler will
  // recognize if x is a register and rewrite it as "jmp.ind x"
    { "jmp.ind", 0x0d60002c, DST_OPERAND_ONLY, OPC_GENERIC_BRANCH, FLAG_P2_STD },
    { "call.ind",0x0d60002d, DST_OPERAND_ONLY, OPC_GENERIC_BRANCH, FLAG_P2_STD },
    { "ret",    0x0d64002d, NO_OPERANDS, OPC_GENERIC_BRANCH, FLAG_P2_STD },
    { "calla.ind",0x0d60002e, DST_OPERAND_ONLY, OPC_GENERIC_BRANCH, FLAG_P2_STD },
    { "reta",   0x0d64002e, NO_OPERANDS, OPC_RET, FLAG_P2_STD },
    { "callb.ind",0x0d60002f, DST_OPERAND_ONLY, OPC_GENERIC_BRANCH, FLAG_P2_STD },
    { "retb",   0x0d64002f, NO_OPERANDS, OPC_GENERIC_BRANCH, FLAG_P2_STD },

    { "jmprel", 0x0d600030, P2_DST_CONST_OK, OPC_GENERIC_BRANCH, 0 },
  
    { "skip",   0x0d600031, P2_DST_CONST_OK, OPC_GENERIC, 0 },
    { "skipf",  0x0d600032, P2_DST_CONST_OK, OPC_GENERIC, 0 },
    { "execf",  0x0d600033, P2_DST_CONST_OK, OPC_GENERIC, 0 },

    { "getptr", 0x0d600034, DST_OPERAND_ONLY, OPC_GENERIC, 0 },
    { "getbrk", 0x0d600035, DST_OPERAND_ONLY, OPC_GENERIC, FLAG_P2_STD },
    { "brk",    0x0d600036, P2_DST_CONST_OK, OPC_GENERIC, 0 },
    { "setluts",0x0d600037, P2_DST_CONST_OK, OPC_GENERIC, 0 },
    { "lutsoff",0x0d640037, NO_OPERANDS, OPC_GENERIC, 0 },
    { "lutson", 0x0d640237, NO_OPERANDS, OPC_GENERIC, 0 },
  
    { "setcy",  0x0d600038, P2_DST_CONST_OK, OPC_GENERIC, 0 },
    { "setci",  0x0d600039, P2_DST_CONST_OK, OPC_GENERIC, 0 },
    { "setcq",  0x0d60003a, P2_DST_CONST_OK, OPC_GENERIC, 0 },
    { "setcfrq",0x0d60003b, P2_DST_CONST_OK, OPC_GENERIC, 0 },
    { "setcmod",0x0d60003c, P2_DST_CONST_OK, OPC_GENERIC, 0 },
    { "setpiv", 0x0d60003d, P2_DST_CONST_OK, OPC_GENERIC, 0 },
    { "setpix", 0x0d60003e, P2_DST_CONST_OK, OPC_GENERIC, 0 },
    { "cogatn", 0x0d60003f, P2_DST_CONST_OK, OPC_GENERIC, 0 },

    { "testp",  0x0d600040, P2_DST_CONST_OK, OPC_GENERIC, FLAG_P2_CZTEST },
    { "testpn", 0x0d600041, P2_DST_CONST_OK, OPC_GENERIC, FLAG_P2_CZTEST },

    { "dirl",   0x0d600040, P2_DST_CONST_OK, OPC_GENERIC, FLAG_WCZ },
    { "dirh",   0x0d600041, P2_DST_CONST_OK, OPC_GENERIC, FLAG_WCZ },
    { "dirc",   0x0d600042, P2_DST_CONST_OK, OPC_GENERIC, FLAG_WCZ },
    { "dirnc",  0x0d600043, P2_DST_CONST_OK, OPC_GENERIC, FLAG_WCZ },
    { "dirz",   0x0d600044, P2_DST_CONST_OK, OPC_GENERIC, FLAG_WCZ },
    { "dirnz",  0x0d600045, P2_DST_CONST_OK, OPC_GENERIC, FLAG_WCZ },
    { "dirrnd", 0x0d600046, P2_DST_CONST_OK, OPC_GENERIC, FLAG_WCZ },
    { "dirnot", 0x0d600047, P2_DST_CONST_OK, OPC_GENERIC, FLAG_WCZ },
  
    { "outl",   0x0d600048, P2_DST_CONST_OK, OPC_GENERIC, FLAG_WCZ },
    { "outh",   0x0d600049, P2_DST_CONST_OK, OPC_GENERIC, FLAG_WCZ },
    { "outc",   0x0d60004a, P2_DST_CONST_OK, OPC_GENERIC, FLAG_WCZ },
    { "outnc",  0x0d60004b, P2_DST_CONST_OK, OPC_GENERIC, FLAG_WCZ },
    { "outz",   0x0d60004c, P2_DST_CONST_OK, OPC_GENERIC, FLAG_WCZ },
    { "outnz",  0x0d60004d, P2_DST_CONST_OK, OPC_GENERIC, FLAG_WCZ },
    { "outrnd", 0x0d60004e, P2_DST_CONST_OK, OPC_GENERIC, FLAG_WCZ },
    { "outnot", 0x0d60004f, P2_DST_CONST_OK, OPC_GENERIC, FLAG_WCZ },

    { "fltl",   0x0d600050, P2_DST_CONST_OK, OPC_GENERIC, FLAG_WCZ },
    { "flth",   0x0d600051, P2_DST_CONST_OK, OPC_GENERIC, FLAG_WCZ },
    { "fltc",   0x0d600052, P2_DST_CONST_OK, OPC_GENERIC, FLAG_WCZ },
    { "fltnc",  0x0d600053, P2_DST_CONST_OK, OPC_GENERIC, FLAG_WCZ },
    { "fltz",   0x0d600054, P2_DST_CONST_OK, OPC_GENERIC, FLAG_WCZ },
    { "fltnz",  0x0d600055, P2_DST_CONST_OK, OPC_GENERIC, FLAG_WCZ },
    { "fltrnd", 0x0d600056, P2_DST_CONST_OK, OPC_GENERIC, FLAG_WCZ },
    { "fltnot", 0x0d600057, P2_DST_CONST_OK, OPC_GENERIC, FLAG_WCZ },
  
    { "drvl",   0x0d600058, P2_DST_CONST_OK, OPC_GENERIC, FLAG_WCZ },
    { "drvh",   0x0d600059, P2_DST_CONST_OK, OPC_GENERIC, FLAG_WCZ },
    { "drvc",   0x0d60005a, P2_DST_CONST_OK, OPC_GENERIC, FLAG_WCZ },
    { "drvnc",  0x0d60005b, P2_DST_CONST_OK, OPC_GENERIC, FLAG_WCZ },
    { "drvz",   0x0d60005c, P2_DST_CONST_OK, OPC_GENERIC, FLAG_WCZ },
    { "drvnz",  0x0d60005d, P2_DST_CONST_OK, OPC_GENERIC, FLAG_WCZ },
    { "drvrnd", 0x0d60005e, P2_DST_CONST_OK, OPC_GENERIC, FLAG_WCZ },
    { "drvnot", 0x0d60005f, P2_DST_CONST_OK, OPC_GENERIC, FLAG_WCZ },

    { "splitb", 0x0d600060, DST_OPERAND_ONLY, OPC_GENERIC, 0 },
    { "mergeb", 0x0d600061, DST_OPERAND_ONLY, OPC_GENERIC, 0 },
    { "splitw", 0x0d600062, DST_OPERAND_ONLY, OPC_GENERIC, 0 },
    { "mergew", 0x0d600063, DST_OPERAND_ONLY, OPC_GENERIC, 0 },
    { "seussf", 0x0d600064, DST_OPERAND_ONLY, OPC_GENERIC, 0 },
    { "seussr", 0x0d600065, DST_OPERAND_ONLY, OPC_GENERIC, 0 },
    { "rgbsqz", 0x0d600066, DST_OPERAND_ONLY, OPC_GENERIC, 0 },
    { "rgbexp", 0x0d600067, DST_OPERAND_ONLY, OPC_GENERIC, 0 },
    { "xoro32", 0x0d600068, DST_OPERAND_ONLY, OPC_GENERIC, 0 },
    { "rev",    0x0d600069, DST_OPERAND_ONLY, OPC_REV_P2, 0 },
    
    { "rczr",   0x0d60006a, DST_OPERAND_ONLY, OPC_GENERIC, FLAG_P2_STD },
    { "rczl",   0x0d60006b, DST_OPERAND_ONLY, OPC_GENERIC, FLAG_P2_STD },
    { "wrc",    0x0d60006c, DST_OPERAND_ONLY, OPC_GENERIC, 0 },
    { "wrnc",   0x0d60006d, DST_OPERAND_ONLY, OPC_GENERIC, 0 },
    { "wrz",    0x0d60006e, DST_OPERAND_ONLY, OPC_GENERIC, 0 },
    { "wrnz",   0x0d60006f, DST_OPERAND_ONLY, OPC_GENERIC, 0 },
    { "modcz",  0x0d64006f, P2_MODCZ, OPC_GENERIC, FLAG_P2_STD | FLAG_WARN_NOTUSED },
    { "modc",   0x0d64006f, P2_MODCZ, OPC_GENERIC, FLAG_WC | FLAG_WARN_NOTUSED },
    { "modz",   0x0d64006f, P2_MODCZ, OPC_GENERIC, FLAG_WZ | FLAG_WARN_NOTUSED },
    { "rfvar",  0x0d600070, DST_OPERAND_ONLY, OPC_GENERIC, FLAG_P2_STD },
    { "rfvars", 0x0d600071, DST_OPERAND_ONLY, OPC_GENERIC, FLAG_P2_STD },
    
  // long jumps
    { "jmp" ,   0x0d800000, P2_JUMP, OPC_JUMP, 0 },
    { "call",   0x0da00000, P2_JUMP, OPC_GENERIC_BRANCH, 0 },
    { "calla",  0x0dc00000, P2_JUMP, OPC_CALL, 0 },
    { "callb",  0x0de00000, P2_JUMP, OPC_GENERIC_BRANCH, 0 },

    { "calld",  0x0e000000, P2_LOC, OPC_GENERIC_BRANCH, 0 },
    { "loc",    0x0e800000, P2_LOC, OPC_GENERIC, 0 },

    { "augs",   0x0f000000, P2_AUG, OPC_GENERIC, 0 },
    { "augd",   0x0f800000, P2_AUG, OPC_GENERIC, 0 },

    { NULL, 0, NO_OPERANDS, OPC_GENERIC},
};

//
// generate a disassembler table
// this has the following fields:
//
// uint32_t: instruction pattern
// uint32_t: instruction mask
// uint32_t: flags
// uint32_t: pointer to instruction name
//
// if pattern & mask == pattern then we can print the instruction
// this is controlled via "flags":
//    0x01: print src
//    0x02: print dst
//    0x04: print wcz
//    0x08: print condition
//    0x10: check for immediate on src
//    0x20: print augmented src
//    0x40: print loc src
//    0x80: print loc dst
//    0x100: accept extended RDWR syntax like ptra++
//
#define PRINT_SRC  0x01
#define PRINT_DST  0x02
#define PRINT_WCZ  0x04
#define PRINT_COND 0x08
#define PRINT_IMMSRC 0x10
#define PRINT_AUGSRC 0x20
#define PRINT_LOCSRC  0x40
#define PRINT_LOCDST  0x80
#define PRINT_RDWR    0x100

int main()
{
    int i;
    Instruction *instr;
    uint32_t pattern;
    uint32_t mask;
    uint32_t flags;
    FILE *f = stdout;
    
    i = 0;
    for (instr = &instr_p2[0]; instr->name; instr++, i++) {
        flags = PRINT_COND; // normally print condition
        pattern = instr->binary;
        switch(instr->ops) {
        case NO_OPERANDS:
            if (!strcmp(instr->name, "nop")) {
                mask = 0xffffffff;
                flags = 0;
            } else {
                mask = 0x0fffffff;
            }
            break;
        case TWO_OPERANDS_DEFZ:
        case P2_RDWR_OPERANDS:
            mask = 0x0fe00000;
            flags |= PRINT_SRC|PRINT_DST|PRINT_IMMSRC|PRINT_RDWR|PRINT_WCZ;
            break;
        case P2_TJZ_OPERANDS:
            flags |= PRINT_DST|PRINT_SRC|PRINT_IMMSRC;
            mask = 0x0ff80000;
            break;
        case DST_OPERAND_ONLY:
        case P2_DST_CONST_OK:
            flags |= PRINT_DST|PRINT_WCZ|PRINT_IMMSRC;
            mask = 0x0fe001ff;
            break;
        case SRC_OPERAND_ONLY:
            mask = 0x0ff80000;
            flags |= PRINT_SRC|PRINT_IMMSRC;
            break;
        case P2_JUMP:
            mask = 0x0fe00000;
            flags |= PRINT_LOCSRC;
            break;
        case P2_LOC:
            mask = 0x0f800000;
            flags |= PRINT_LOCSRC|PRINT_LOCDST;
            break;
        case P2_AUG:
            mask = 0x0f800000;
            flags |= PRINT_AUGSRC;
            break;
        default:
            mask = 0x0fe00000;
            flags |= PRINT_DST|PRINT_SRC|PRINT_IMMSRC|PRINT_WCZ;
            break;
        }
        fprintf(f, "\tlong\t$%08x, $%08x, $%08x, @@@name_%03d\n",
               pattern, mask, flags, i);
    }
    // now go back and print labels for the names
    fprintf(f, "\n");
    i = 0;
    for (instr = &instr_p2[0]; instr->name; instr++, i++) {
        fprintf(f, "name_%03d\tbyte\t\"%-7s\", 0\n", i, instr->name);
    }
    return 0;
}
