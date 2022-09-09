// RP_Greedy.hh
#ifndef _RP_GREEDY_HH_
#define _RP_GREEDY_HH_
#include "Router_placement_data.hh"

point MaxDegreeRouter (const RP_Input& in, RP_Output& out);
bool IsFeasibleRouter (const RP_Input& in, RP_Output& out, point r);
point MakeRandomMove(point p);
unsigned SelectRouter(const RP_Input& in, RP_Output& out);
void ConnectRouterWithBackbone(RP_Output& out, const RP_Input& in, point router);
void GreedyRP(const RP_Input& in, RP_Output& out);

bool PointIsInVec (point pt, vector<point> vec);
void PrintVec (vector<point> vec);

#endif

