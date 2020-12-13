# include "PriorityQueue.hxx"

void PriorityQueue::deleteValue(double x)
{
    auto first = this->c.cbegin();
    auto last = this->c.cend();

    while (first!=last) 
    {
        if (*first==x)
        {
            this->c.erase(first);
            break;
        }

        ++first;
    }
}