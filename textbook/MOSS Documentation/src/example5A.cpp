#include <iostream>
#include <vector>
#include <sstream>

using namespace std;


Matrix3x3::Matrix3x3()
{
    matrix = {{0}};
}

Matrix3x3::Matrix3x3(const double m[ROWS][COLUMNS])
{
    set_matrix(const double m[ROWS][COLUMNS]));
}
void Matrix3x3::set_matrix(const double m[ROWS][COLUMNS])
{
    for(int i = 0; i < ROWS; i++)
    {
        for(int x = 0; x < COLUMNS; x++)
        {
            matrix[i][j] = m[i][j];
        }
    }
}
const  Matrix3x3::double get_elem(unsigned i, unsigned j) const
{
    if(i >= ROWS || j >= COLUMNS)
    {
        return 0.0;
    }
    else
    {
        return matrix[i][j];
    }
}
string int_to_string(int n)
{
    ostringstream ss;
    ss << n;
    return ss.str();
}
int count_vector(vector<int> foo)
{
    int total = 0;
    for(int x = 0; x < x.size(); x++)
    {
        total += foo.at(x);
    }
    return
}
int main()
{
    int n = 1234567890;
    cout << int_to_string(n);
    return 0;
}