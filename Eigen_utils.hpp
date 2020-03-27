#ifndef EIGEN_UTILS_HPP
#define EIGEN_UTILS_HPP

#include <Eigen/Dense>
#include <vector>
#include <fstream>


namespace myUtils {
    // based on user357269's answer at https://stackoverflow.com/questions/34247057/how-to-read-csv-file-and-assign-to-eigen-matrix/

    template <typename Container>
    Container load_csv(const std::string& path, char sep = ',') {
        
        std::ifstream indata(path);
        if (indata.fail())
            throw std::runtime_error(std::string("file: \"") + path + std::string("\" not found"));
        
        std::string line;
        std::vector<typename Container::value_type> values;
        Eigen::Index rows = 0;
        while (std::getline(indata, line)) {
            std::stringstream lineStream(line);
            std::string cell;

            while (std::getline(lineStream, cell, sep)) values.push_back(std::stod(cell));
            
            ++rows;
        }
        indata.close();

        Eigen::Index cols = 0;
        if(rows >0 ) cols = values.size() / rows;

        if (cols > Container::ColsAtCompileTime& Container::ColsAtCompileTime != Eigen::Dynamic)
            throw std::runtime_error(std::string("file \"") + path + std::string("\" has too many columns"));
        if (rows > Container::ColsAtCompileTime& Container::RowsAtCompileTime != Eigen::Dynamic)
            throw std::runtime_error(std::string("file \"") + path + std::string("\" has too many rows"));

        return Eigen::Map<const Eigen::Matrix<typename Container::Scalar, Container::RowsAtCompileTime, 
                                              Container::ColsAtCompileTime, Container::IsRowMajor >>
            (values.data(), rows, cols);
    }


    void test_load_csv(const std::string& path, char sep = ',') {
        std::ifstream indata;
        indata.open(path);
        std::string line;
        while (std::getline(indata, line)) {
            std::cout << line << std::endl;
            //std::stringstream lineStream(line);
            //std::string cell;
            //while (std::getline(lineStream, cell, sep)) {
            //    values.push_back(std::stod(cell));
            //}
            //++rows;
        }
        //Eigen::Index 
        indata.close();
    }

    // based on Robert Dodier's answer at https://stackoverflow.com/questions/24518989/how-to-perform-1-dimensional-valid-convolution
    template<typename T>
    inline Eigen::Vector<T, Eigen::Dynamic> VectorConvolutionValid
    (const Eigen::Vector<T, Eigen::Dynamic>& f, const Eigen::Vector<T, Eigen::Dynamic>& g)
    {
        //static_assert(! (std::is_same<T, float> || std::is_same<T, double> ), "convolution is only defined for floating-point numbers")
        const Eigen::Index nf = f.rows();
        const Eigen::Index ng = g.rows();

        Eigen::Vector<T, Eigen::Dynamic> const& min_v = (nf < ng) ? f : g;
        Eigen::Vector<T, Eigen::Dynamic> const& max_v = (nf < ng) ? g : f;

        const Eigen::Index n = std::max(nf, ng) - std::min(nf, ng) + 1;
        Eigen::Vector<T, Eigen::Dynamic> out{ Eigen::Vector<T, Eigen::Dynamic>::Zero(n) };

        for (size_t i{ 0 }; i < n; ++i) {
            size_t k{ i };
            for (auto j(min_v.size() - 1); j >= 0; --j) {
                //std::cout << out(i) << " += " << min_v(j) << "*" << max_v(k) << std::endl;
                out(i) += min_v(j) * max_v(k);
                ++k;
            }
        }
        return out;
    }
}
#endif //EIGEN_UTILS_HPP