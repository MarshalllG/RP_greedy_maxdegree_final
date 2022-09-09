// RP_Greedy.cc 

#include "RP_Greedy.hh"

using namespace std;


bool IsFeasibleRouter (const RP_Input& in, RP_Output& out, point r)
{
    return (in.IsDot(r.row, r.col) && (in.RouterPrice() + (ManhattanDistance(r, out.ClosestBackbonePoint(r)) * in.BackbonePrice()) <= out.RemainingBudget()));
}


unsigned SelectRouter(const RP_Input& in, RP_Output& out)
{
    point selected;
    unsigned size;

    selected = MaxDegreeRouter (in, out);
    
    if (IsFeasibleRouter(in, out, selected))
    {
        size = out.FindCoverageArea(selected).size();

        out.InsertRouter(selected.row, selected.col);
        cout << "Covered: " << out.TotalCoveredPoints() << endl;

        out.UpdateUncovered();

        out.ConnectRouterWithBackbone(selected);
        return size;
    }
    else
        return 0;
}


void GreedyRP(const RP_Input& in, RP_Output& out)
{ 
    unsigned new_coverage;

    do
    {    
        if (out.UncoveredSize() == 0)
        {
            cout << "No way to place routers." << endl;
            exit(0);
        }

        if (out.RemainingBudget() >= int(in.RouterPrice()))
            new_coverage = SelectRouter(in, out);
        else
        {
            cout << "No router placed." << endl;
            new_coverage = 0;
        }
    } while(new_coverage > 0);

    cout << out;
    cout << "Final Score: " << out.ComputeTotalScore() << endl;
    cout << "Remaining budget: " << out.RemainingBudget() << endl;
    // cout << "New Backbone:" << endl;
    // PrintVec(out.Backbone());
}


point MaxDegreeRouter (const RP_Input& in, RP_Output& out) 
{
    int max_degree = 0;
    int router_degree;
    point max;

    for (int i = 0; i < out.UncoveredSize(); i++)
    {             
        router_degree = out.RouterScore(out.Uncovered(i));

        if (router_degree > max_degree)
        {
            max_degree = router_degree;
            max.row = out.Uncovered(i).row;
            max.col = out.Uncovered(i).col;
        }
    }
    return max;
}


bool PointIsInVec (point pt, vector<point> vec) 
{
    for (unsigned i = 0; i < vec.size(); i++)
        if (pt.row == vec[i].row && pt.col == vec[i].col)
            return 1;

    return 0;
}


void PrintVec (vector<point> vec) 
{
    for (unsigned i = 0; i < vec.size(); i++)
    {
        cout << vec[i].row << " " << vec[i].col;
        if (i != vec.size()-1)
            cout << " -> ";
    }
        
    cout << endl;
}
