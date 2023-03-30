#include <iostream>
#include <random>
#include <cmath>
using namespace std;
void test1(bool bits[])
{
    double sum = 0;
    for (size_t i = 0; i < 128; ++i)
    {
        if (bits[i])sum += 1;
        else sum += -1;
    }
    sum /= sqrt(128);
    cout << erfc(sum / sqrt(2)) << endl;
}
void test2(bool bits[])
{
    double psi = 0;
    for (int i = 0; i < 128; i++) if (bits[i]) psi++;
    psi /= 128;
    if (fabs(psi - 0.5) >= 2 / sqrt(128))
    {
        cout << "0" << endl;
    }
    else
    {
        double V = 0;
        for (size_t i = 0; i < 127; ++i)
        {
            if (bits[i] != bits[i + 1]) V += 1;
        }
        cout << erfc(fabs(V - 256 * psi * (1 - psi)) / (32 * psi * (1 - psi))) << endl;
    }
}
void test3(bool bits[])
{
    double pi[4] = { 0.2148, 0.3672, 0.2305, 0.1875 };
    double V[4] = { 0,0,0,0 };
    double xi = 0;
    for (size_t i = 0; i < 16; ++i)
    {
        size_t v_c = 0;
        size_t v_a = 0;
        for (size_t j = 8 * i; j < 8 * (i + 1); ++j)
        {
            if (v_c == 0 && bits[j])
            {
                v_c = 1;
            }
            if (bits[j] && bits[j] == bits[j + 1])
            {
                v_c += 1;
            }
            if (!bits[j])
            {
                if (v_c > v_a)
                {
                    v_a = v_c;
                }
                v_c = 0;
            }
        }
        if (v_a <= 1)
        {
            V[0] += 1;
        }
        else if (v_a == 2)
        {
            V[1] += 1;
        }
        else if (v_a == 3)
        {
            V[2] += 1;
        }
        else if (v_a >= 4)
        {
            V[3] += 1;
        }
        v_c = 0;
        v_a = 0;
    }
    for (size_t i = 0; i < 4; ++i)
    {
        xi += pow((V[i] - 16 * pi[i]), 2) / (16 * pi[i]);
    }
    cout << xi << endl;
}
int main()
{
    bool bits[128];
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, 1);
    for (size_t i = 0; i < 128; ++i)
    {
        bits[i] = dist(gen);
    }
    for (size_t i = 0; i < 128; ++i)
    {
        cout << bits[i];
    }
    cout << endl;
    test1(bits);
    test2(bits);
    test3(bits);
    return 0;
}
