#include "stdafx.h"

#include "SPOJ_PALIN.h"                        // 001
#include "UVa100.h"                            // 002
#include "UVa272.h"                            // 003
#include "UVa394.h"                            // 004
#include "UVa483.h"                            // 005
#include "UVa573.h"                            // 006
#include "UVa661.h"                            // 007
#include "UVa739.h"                            // 008
#include "UVa837.h"                            // 009
#include "UVa941.h"                            // 010
#include "UVa10082.h"                          // 011
#include "UVa10141.h"                          // 012
#include "UVa10281.h"                          // 013
#include "UVa10363.h"                          // 014
#include "UVa10420.h"                          // 015
#include "UVa482.h"                            // 016
#include "UVa146.h"                            // 017
#include "UVa299.h"                            // 018
#include "UVa11462.h"                          // 019
#include "UVa127.h"                            // 020
#include "UVa336.h"                            // 021
#include "UVa10226.h"                          // 022
#include "UVa908.h"                            // 023
#include "UVa291.h"                            // 024
#include "UVa459.h"                            // 025
#include "UVa11235.h"                          // 026
#include "UVa912.h"                            // 027
#include "UVa11297.h"                          // 028
#include "UVa10505.h"                          // 029
#include "UVa11503.h"                          // 030
#include "UVa10928.h"                          // 031
#include "UVa725.h"                            // 032
#include "UVa750.h"                            // 033
#include "UVa10360.h"                          // 034
#include "UVa524.h"                            // 035
#include "UVa628.h"                            // 036
#include "UVa639.h"                            // 037
#include "UVa193.h"                            // 038
#include "UVa10158.h"                          // 039
#include "UVa11242.h"                          // 040
#include "UVa679.h"                            // 041
#include "UVa714.h"                            // 042
#include "SPOJ_TEST.h"                         // 043
#include "UVa957.h"                            // 044
#include "SPOJ_LITE_1.h"                       // 045
#include "SPOJ_LITE_2.h"                       // 045
#include "UVa10341.h"                          // 046
#include "UVa10077.h"                          // 047
#include "SPOJ_HORRIBLE.h"                     // 048
#include "LEET_LONGEST_CONSECUTIVE_SEQUENCE.h" // 049
#include "LEET_SUM_ROOT_TO_LEAF_NUMBER.h"      // 050
#include "UVa410.h"                            // 051
#include "UVa10020.h"                          // 052
#include "UVa10340.h"                          // 052
#include "UVa10440.h"                          // 053
#include "UVa10670.h"                          // 054
#include "UVa10763.h"                          // 055
#include "UVa11054.h"                          // 056
#include "UVa11292.h"                          // 057
#include "UVa11369.h"                          // 058
#include "UVa11450.h"                          // 059
#include "UVa103.h"                            // 060
#include "UVa111.h"                            // 061
#include "UVa10003.h"                          // 062
#include "UVa10911.h"                          // 063
#include "SPOJ_FISHER.h"                       // 064
#include "UVa231.h"                            // 065
#include "UVa481.h"                            // 066
#include "UVa147.h"                            // 067
#include "UVa166.h"                            // 068
#include "UVa357.h"                            // 069
#include "UVa674.h"                            // 070
#include "UVa108.h"                            // 071
#include "UVa836.h"                            // 072
#include "UVa562.h"                            // 073
#include "UVa990.h"                            // 074
#include "UVa116.h"                            // 075
#include "UVa473.h"                            // 076
#include "UVa607.h"                            // 077
#include "UVa10364.h"                          // 078
#include "UVa10651.h"                          // 079
#include "UVa590.h"                            // 080
#include "UVa10243.h"                          // 081
#include "UVa10891.h"                          // 082
#include "UVa910.h"                            // 083
#include "UVa260.h"                            // 084
#include "UVa352.h"                            // 085
#include "UVa315.h"                            // 086
#include "UVa610.h"                            // 087
#include "UVa10731.h"                          // 088
#include "UVa11504.h"                          // 089
#include "UVa124.h"                            // 090
#include "UVa200.h"                            // 091
#include "UVa383.h"                            // 092
#include "UVa10034.h"                          // 093
#include "UVa417.h"                            // 094
#include "UVa469.h"                            // 095
#include "UVa10307.h"                          // 096
#include "UVa10004.h"                          // 097
#include "UVa11228.h"                          // 098
#include "UVa341.h"                            // 099
#include "UVa929.h"                            // 100
#include "UVa10278.h"                          // 101
#include "UVa10603.h"                          // 102
#include "UVa10147.h"                          // 103
#include "UVa10369.h"                          // 104
#include "UVa558.h"                            // 105
#include "UVa10557.h"                          // 106

//
// To avoid create a lot of projects/executables for each competition problem,
// each problem answered as a separate file with an entry function
// The entry function is called in main below.
//
// For competition purpose that file is submitted instead
// And the entry function is renamed to main for submission
// Together we will also remove WIN32 specifics
//
int _tmain(int argc, _TCHAR* argv[])
{
    // return SPOJ_PALIN();                        // Accepted
    // return UVa100();                            // Accepted
    // return UVa272();                            // Accepted
    // return UVa394();                            // Accepted
    // return UVa573();                            // Accepted
    // return UVa661();                            // Accepted
    // return UVa739();                            // Accepted
    // return UVa837();                            // Accepted
    // return UVa941();                            // Accepted
    // return UVa10082();                          // Accepted
    // return UVa10141();                          // Accepted
    // return UVa10281();                          // Accepted
    // return UVa10363();                          // Accepted
    // return UVa10420();                          // Accepted
    // return UVa482();                            // Accepted
    // return UVa146();                            // Accepted
    // return UVa299();                            // Accepted
    // return UVa11462();                          // Accepted
    // return UVa127();                            // Accepted
    // return UVa336();                            // Accepted
    // return UVa10226();                          // Accepted
    // return UVa908();                            // Accepted
    // return UVa291();                            // Accepted
    // return UVa459();                            // Accepted
    // return UVa11235();                          // Accepted
    // return UVa912();                            // Accepted
    // return UVa11297();                          // Accepted
    // return UVa10505();                          // Accepted
    // return UVa11503();                          // Accepted
    // return UVa10928();                          // Accepted
    // return UVa725();                            // Accepted
    // return UVa750();                            // Accepted
    // return UVa10360();                          // Accepted
    // return UVa524();                            // Accepted
    // return UVa628();                            // Accepted
    // return UVa639();                            // Accepted
    // return UVa193();                            // Accepted
    // return UVa10158();                          // Accepted
    // return UVa11242();                          // Accepted
    // return UVa679();                            // Accepted
    // return UVa714();                            // Accepted
    // return SPOJ_TEST();                         // Accepted
    // return UVa957();                            // Accepted
    // return SPOJ_LITE_1();                       // Time limit exceeded - but this algorithm is independent on number of lights - with large constant though
    // return SPOJ_LITE_2();                       // Accepted
    // return UVa10341();                          // Accepted
    // return UVa10077();                          // Accepted
    // return SPOJ_HORRIBLE();                     // Accepted
    // return LEET_LONGEST_CONSECUTIVE_SEQUENCE(); // Accepted
    // return LEET_SUM_ROOT_TO_LEAF_NUMBER();      // Accepted
    // return UVa410();                            // Accepted
    // return UVa10020();                          // Accepted
    // return UVa10340();                          // Accepted
    // return UVa10440();                          // Accepted
    // return UVa10670();                          // Accepted
    // return UVa10763();                          // Accepted
    // return UVa11054();                          // Accepted
    // return UVa11292();                          // Accepted
    // return UVa11369();                          // Accepted
    // return UVa11450();                          // Accepted
    // return UVa103();                            // Accepted
    // return UVa111();                            // Accepted
    // return UVa10003();                          // Accepted
    // return UVa10911();                          // Accepted
    // return SPOJ_FISHER();                       // Accepted
    // return UVa231();                            // Accepted
    // return UVa481();                            // Accepted
    // return UVa147();                            // Accepted
    // return UVa166();                            // Accepted
    // return UVa357();                            // Accepted
    // return UVa674();                            // Accepted
    // return UVa108();                            // Accepted - but we should be able to improve it to O(100^3)
    // return UVa836();                            // Accepted
    // return UVa562();                            // Accepted
    // return UVa990();                            // Accepted
    // return UVa116();                            // Accepted
    // return UVa473();                            // Accepted
    // return UVa607();                            // Accepted
    // return UVa10364();                          // Accepted
    // return UVa10651();                          // Accepted
    // return UVa590();                            // Accepted
    // return UVa10243();                          // Accepted
    // return UVa10891();                          // Accepted
    // return UVa910();                            // Accepted
    // return UVa260();                            // Accepted
    // return UVa352();                            // Accepted
    // return UVa315();                            // Accepted
    // return UVa610();                            // Accepted
    // return UVa10731();                          // Accepted
    // return UVa11504();                          // Accepted
    // return UVa124();                            // Accepted
    // return UVa200();                            // Accepted
    // return UVa383();                            // Accepted
    // return UVa10034();                          // Accepted
    // return UVa417();                            // Accepted
    // return UVa469();                            // Accepted
    // return UVa10307();                          // Accepted
    // return UVa10004();                          // Accepted
    // return UVa11228();                          // Accepted
    // return UVa341();                            // Accepted
    // return UVa929();                            // Accepted
    // return UVa10278();                          // Accepted
    // return UVa10603();                          // Accepted
    // return UVa10147();                          // Accepted
    // return UVa10369();                          // Accepted
    // return UVa558();                            // Accepted
    return UVa10557();                          // 
}
