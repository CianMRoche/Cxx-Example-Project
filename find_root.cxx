# include <iostream>
# include <cmath>
# include <functional>
# include <string>
# include "function_input.h"
# include "root_finding.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

// Function to print out the parameters we input for root finding in the main function below
void printMethodParameters(const boost::property_tree::ptree& pt, const std::string& method) {
    try {
        const auto& methodNode = pt.get_child(method);
        std::cout << method << " Parameters:" << std::endl;
        for (const auto& param : methodNode) {
            const auto& paramName = param.first;
            try {
                const auto& paramValue = param.second.get<double>("value");
                const auto& paramDesc = param.second.get<std::string>("description");
                const auto& paramType = param.second.get<std::string>("type");
                std::cout << paramDesc << " (" << paramType << "): " << paramValue << std::endl;
            } catch (const std::exception& ex) {
                std::cerr << "Error reading value for parameter '" << paramName << "': " << ex.what() << std::endl;
            }
        }
    } catch (const std::exception& ex) {
        std::cerr << "Error reading JSON file in printMethodParameters: " << ex.what() << std::endl;
    }
}


/*
Description:
---------
Main function to find the root of a function using the chosen method.
The method is chosen by passing the method name as an argument to the program, e.g.:
./find_root bisection
./find_root newton_raphson
./find_root secant
The function to find the root of (f) is found in function_input.h and implemented in function_input.cxx.
The parameters for the root finding methods are loaded from a JSON file, config.json, using the boost library.
The config file can be changed without recompiling, but changing the function itself necessitates recompilation.

Compilation:
-----------
To compile the program, use the following commands, where cmake is called from the build folder
to create the makefile using the "out of source" method, which keeps the source directory clean.
If recompiling, run `make clean` (in build folder) first and no need to recreate the build folder
mkdir build
cd build
cmake ..
make all
./find_root <method choice>
*/

int main(int argc, char* argv[]) {
    // Check if the method is passed as an argument
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <method>" << std::endl;
        return 1;
    }

    std::string method = argv[1]; // Convert char* to std::string so it can be compared easily
    std::cout << "Chosen method: " << method << std::endl;


    // ----------- Import root finding parameters from JSON file -----------

    // Create a property tree to hold the JSON data
    boost::property_tree::ptree pt;
    
    // Load the JSON file into the property tree
    try {boost::property_tree::json_parser::read_json("../config.json", pt);

    } catch (const std::exception& ex) {
        std::cerr << "Error reading JSON file: " << ex.what() << std::endl;
        return 1;
    }

    std::cout << "Root finding parameters loaded from JSON file." << std::endl;

    // ----------- Get rootfinding params and find the root -----------
    double root;

    if (method=="bisection"){
        // Access variables for bisection
        double left_limit = pt.get<double>("bisection.left_limit.value");
        double right_limit = pt.get<double>("bisection.right_limit.value");
        double tol = pt.get<double>("bisection.tol.value");
        int max_iter = pt.get<int>("bisection.max_iter.value");
        // Print out the variables
        printMethodParameters(pt, method);
        // find the root
        root = bisection(f, left_limit, right_limit, tol, max_iter);

    } else if (method=="newton_raphson"){
        // Access variables for newton_raphson
        double x0 = pt.get<double>("newton_raphson.x0.value");
        double tol = pt.get<double>("newton_raphson.tol.value");
        int max_iter = pt.get<int>("newton_raphson.max_iter.value");
        // Print out the variables
        printMethodParameters(pt, method);
        // find the root
        root = newton_raphson(f, df, x0, tol, max_iter);

    } else if (method=="secant"){
        // Access variables for secant
        double x0 = pt.get<double>("secant.x0.value");
        double x1 = pt.get<double>("secant.x1.value");
        double tol = pt.get<double>("secant.tol.value");
        int max_iter = pt.get<int>("secant.max_iter.value");
        // Print out the variables
        printMethodParameters(pt, method);
        // find the root
        root = secant(f, x0, x1, tol, max_iter);
        
    } else {
        std::cout << "Invalid method." << std::endl;
        return 1;
    }

    //  ----------- Print out the root -----------
    std::cout << "Root: " << root << std::endl;

    return 0;
}