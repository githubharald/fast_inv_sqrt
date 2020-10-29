#include <cstdint>
#include <cstddef>
#include <cmath>
#include <limits>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>


// log x values and computed approximations, write to csv file at the end
class Logger
{
public:
    Logger(const std::string filename) : m_filename(filename) {}
    ~Logger()
    {
        std::ofstream f(m_filename);
        for (size_t i = 0; i < m_xvals.size(); ++i)
        {
            f << m_xvals[i] << ",";
            for (size_t j = 0; j < m_guesses[i].size(); ++j)
            {
                f << m_guesses[i][j];
                if (j + 1 < m_guesses[i].size())
                {
                    f << ",";
                }
            }
            f << "\n";
        }
    }

    // add the current x value
    void add_curr_xval(float x)
    {
        m_xvals.push_back(x);
        m_guesses.push_back(std::vector<float>());
    }

    // for the current x value, add an approximation for the inverse square root
    void add_curr_guess(float guess)
    {
        m_guesses.back().push_back(guess);
    }

private:
    std::string m_filename;
    std::vector<float> m_xvals;
    std::vector<std::vector<float>> m_guesses;
};


// compute inverse square root
float fast_inv_sqrt(float x, Logger &logger)
{
    logger.add_curr_xval(x);

    float y = x; // current guess y = sqrt(x)
    uint32_t *i = reinterpret_cast<uint32_t *>(&y); // i points to current guess y, interpreted as uint32

    const uint32_t exp_mask = 0x7F800000; // 0xFF<<23
    const uint32_t magic_number = 0x5f000000; // 190<<23

    // initial guess using magic number
    *i = magic_number - ((*i >> 1) & exp_mask);
    logger.add_curr_guess(y);

    // refine guess using some Newton iterations
    const size_t num_newton_iter = 2;
    for (size_t i = 0; i < num_newton_iter; ++i)
    {
        y = (x * y * y + 1) / (2 * x * y);
        logger.add_curr_guess(y);
    }

    return y;
}


int main()
{
    Logger logger("dump.csv");

    float min_val = 1;
    float max_val = 16;
    float step = 0.1;

    for (float f = min_val; f <= max_val; f += step)
    {
        fast_inv_sqrt(f, logger);
    }

    return 0;
}