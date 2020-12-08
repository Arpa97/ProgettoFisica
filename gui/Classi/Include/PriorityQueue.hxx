# include <queue>

struct PriorityQueue : public std::priority_queue<double, std::vector<double>, std::greater<double>>
{
    void deleteValue(double x);
};