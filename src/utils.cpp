#include "utils.h"

unsigned long timeMillisecond()
{
    using namespace chrono;
    unsigned long t = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    return t;
}

float sumSquare(float a, float b, float c)
{
    float re = (a * a) + (b * b) + (c * c);
    return re;
}

string f2s(float x, int precision = 3) 
{
    return number2string<float>(x, precision);
}

string f2s(float x) 
{
    int precision = 3;
    return number2string<float>(x, precision);
}

template <typename T> string number2string(T x, int precision)
{
    stringstream re;
    re << fixed << setprecision(precision) << setw(8) << x;
    return re.str();
}

vector<string> vF2vS(vector<float> x) 
{
    int precision = 3;
    return vector2vecString<float>(x, precision);
}


vector<string> vF2vS(vector<float> x, int precision = 3) 
{
    return vector2vecString<float>(x, precision);
}

template <typename T> vector<string> vector2vecString(vector<T> x, int precision)
{
    vector<string> re;
    for (int i=0; i<x.size(); i++) {
        re.push_back(number2string<T>(x[i],precision));
    }
    return re;
}

int writeToPDB(set<vector<string>> totPoints, string fname = "sphere_test_out.pdb")
{
    ofstream fo;
    fo.open(fname);
    fo << "REMARK this is a sphere\n";
    int i_ctrl = 0;
    for (set<vector<string>>::iterator p = totPoints.begin(); 
         p!= totPoints.end(); p++) 
    {
        int resid = i_ctrl+1;
        if (resid > 9999) {
            resid = resid % 10000;
        }
        string chain = "A";
        if ((*p).size() < 4) {
            chain = "A";
        } else {
            chain = (*p)[3];
        }

        fo << "ATOM " 
           << setw(6) <<  i_ctrl+1 
           << " C    DUM " << chain 
           << setw(4) << resid 
           << "    " 
           << (*p)[0]
           << (*p)[1] 
           << (*p)[2]
           << "  1.00  0.00  " << endl;
        i_ctrl += 1;
    }
    fo << "TER\n" ;
    fo.close();
    return 0;
}