#define BSON_MACRO_ARG(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75, _76, _77, _78, _79, _80, _81, _82, _83, _84, _85, _86, _87, _88, _89, _90, _91, _92, _93, _94, _95, _96, _97, _98, _99, _100, _101, _102, _103, _104, _105, _106, _107, _108, _109, _110, _111, _112, _113, _114, _115, _116, _117, _118, _119, _120, _121, _122, _123, _124, _125, _126, _127, _128, _129, _130, _131, _132, _133, _134, _135, _136, _137, _138, _139, _140, _141, _142, _143, _144, _145, _146, _147, _148, _149, _150, _151, _152, _153, _154, _155, _156, _157, _158, _159, _160, _161, _162, _163, _164, _165, _166, _167, _168, _169, _170, _171, _172, _173, _174, _175, _176, _177, _178, _179, _180, _181, _182, _183, _184, _185, _186, _187, _188, _189, _190, _191, _192, _193, _194, _195, _196, _197, _198, _199, _200, _201, _202, _203, _204, _205, _206, _207, _208, _209, _210, _211, _212, _213, _214, _215, _216, _217, _218, _219, _220, _221, _222, _223, _224, _225, _226, _227, _228, _229, _230, _231, _232, _233, _234, _235, _236, _237, _238, _239, _240, _241, _242, _243, _244, _245, _246, _247, _248, _249, _250, _251, _252, _253, _254, _255, _256, ...) _256
#define BSON_MACRO_COUNT(...) BSON_MACRO_ARG(__VA_ARGS__, 255, 254, 253, 252, 251, 250, 249, 248, 247, 246, 245, 244, 243, 242, 241, 240, 239, 238, 237, 236, 235, 234, 233, 232, 231, 230, 229, 228, 227, 226, 225, 224, 223, 222, 221, 220, 219, 218, 217, 216, 215, 214, 213, 212, 211, 210, 209, 208, 207, 206, 205, 204, 203, 202, 201, 200, 199, 198, 197, 196, 195, 194, 193, 192, 191, 190, 189, 188, 187, 186, 185, 184, 183, 182, 181, 180, 179, 178, 177, 176, 175, 174, 173, 172, 171, 170, 169, 168, 167, 166, 165, 164, 163, 162, 161, 160, 159, 158, 157, 156, 155, 154, 153, 152, 151, 150, 149, 148, 147, 146, 145, 144, 143, 142, 141, 140, 139, 138, 137, 136, 135, 134, 133, 132, 131, 130, 129, 128, 127, 126, 125, 124, 123, 122, 121, 120, 119, 118, 117, 116, 115, 114, 113, 112, 111, 110, 109, 108, 107, 106, 105, 104, 103, 102, 101, 100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0) 
#define BSON_MACRO_MAP_2(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_1(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_3(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_2(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_4(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_3(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_5(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_4(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_6(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_5(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_7(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_6(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_8(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_7(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_9(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_8(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_10(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_9(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_11(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_10(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_12(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_11(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_13(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_12(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_14(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_13(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_15(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_14(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_16(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_15(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_17(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_16(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_18(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_17(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_19(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_18(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_20(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_19(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_21(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_20(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_22(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_21(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_23(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_22(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_24(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_23(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_25(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_24(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_26(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_25(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_27(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_26(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_28(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_27(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_29(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_28(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_30(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_29(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_31(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_30(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_32(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_31(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_33(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_32(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_34(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_33(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_35(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_34(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_36(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_35(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_37(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_36(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_38(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_37(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_39(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_38(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_40(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_39(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_41(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_40(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_42(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_41(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_43(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_42(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_44(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_43(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_45(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_44(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_46(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_45(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_47(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_46(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_48(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_47(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_49(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_48(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_50(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_49(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_51(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_50(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_52(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_51(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_53(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_52(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_54(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_53(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_55(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_54(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_56(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_55(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_57(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_56(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_58(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_57(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_59(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_58(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_60(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_59(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_61(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_60(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_62(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_61(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_63(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_62(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_64(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_63(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_65(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_64(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_66(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_65(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_67(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_66(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_68(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_67(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_69(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_68(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_70(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_69(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_71(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_70(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_72(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_71(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_73(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_72(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_74(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_73(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_75(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_74(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_76(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_75(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_77(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_76(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_78(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_77(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_79(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_78(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_80(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_79(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_81(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_80(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_82(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_81(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_83(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_82(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_84(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_83(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_85(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_84(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_86(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_85(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_87(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_86(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_88(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_87(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_89(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_88(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_90(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_89(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_91(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_90(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_92(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_91(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_93(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_92(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_94(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_93(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_95(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_94(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_96(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_95(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_97(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_96(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_98(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_97(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_99(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_98(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_100(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_99(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_101(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_100(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_102(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_101(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_103(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_102(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_104(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_103(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_105(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_104(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_106(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_105(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_107(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_106(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_108(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_107(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_109(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_108(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_110(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_109(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_111(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_110(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_112(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_111(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_113(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_112(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_114(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_113(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_115(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_114(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_116(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_115(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_117(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_116(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_118(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_117(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_119(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_118(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_120(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_119(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_121(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_120(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_122(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_121(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_123(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_122(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_124(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_123(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_125(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_124(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_126(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_125(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_127(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_126(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_128(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_127(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_129(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_128(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_130(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_129(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_131(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_130(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_132(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_131(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_133(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_132(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_134(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_133(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_135(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_134(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_136(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_135(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_137(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_136(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_138(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_137(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_139(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_138(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_140(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_139(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_141(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_140(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_142(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_141(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_143(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_142(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_144(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_143(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_145(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_144(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_146(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_145(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_147(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_146(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_148(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_147(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_149(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_148(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_150(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_149(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_151(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_150(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_152(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_151(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_153(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_152(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_154(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_153(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_155(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_154(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_156(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_155(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_157(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_156(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_158(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_157(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_159(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_158(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_160(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_159(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_161(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_160(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_162(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_161(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_163(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_162(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_164(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_163(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_165(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_164(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_166(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_165(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_167(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_166(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_168(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_167(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_169(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_168(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_170(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_169(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_171(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_170(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_172(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_171(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_173(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_172(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_174(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_173(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_175(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_174(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_176(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_175(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_177(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_176(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_178(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_177(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_179(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_178(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_180(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_179(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_181(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_180(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_182(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_181(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_183(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_182(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_184(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_183(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_185(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_184(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_186(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_185(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_187(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_186(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_188(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_187(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_189(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_188(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_190(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_189(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_191(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_190(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_192(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_191(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_193(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_192(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_194(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_193(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_195(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_194(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_196(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_195(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_197(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_196(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_198(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_197(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_199(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_198(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_200(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_199(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_201(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_200(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_202(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_201(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_203(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_202(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_204(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_203(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_205(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_204(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_206(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_205(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_207(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_206(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_208(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_207(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_209(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_208(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_210(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_209(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_211(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_210(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_212(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_211(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_213(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_212(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_214(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_213(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_215(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_214(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_216(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_215(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_217(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_216(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_218(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_217(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_219(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_218(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_220(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_219(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_221(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_220(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_222(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_221(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_223(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_222(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_224(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_223(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_225(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_224(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_226(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_225(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_227(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_226(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_228(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_227(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_229(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_228(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_230(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_229(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_231(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_230(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_232(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_231(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_233(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_232(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_234(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_233(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_235(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_234(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_236(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_235(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_237(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_236(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_238(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_237(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_239(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_238(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_240(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_239(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_241(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_240(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_242(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_241(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_243(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_242(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_244(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_243(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_245(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_244(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_246(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_245(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_247(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_246(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_248(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_247(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_249(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_248(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_250(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_249(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_251(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_250(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_252(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_251(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_253(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_252(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_254(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_253(m, sep, __VA_ARGS__)
#define BSON_MACRO_MAP_255(m, sep, v, ...) m(v)BSON_MACRO_CONCAT sep BSON_MACRO_MAP_254(m, sep, __VA_ARGS__)
