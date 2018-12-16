//
//  main.cpp
//  CSE524
//
//  Created by Anand Kulkarni on 11/3/18.
//  Copyright © 2018 Anand Kulkarni. All rights reserved.
//
#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <zip.h>

#include <boost/range/irange.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filtering_stream.hpp>



#include <fstream>
#include <iostream>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>


#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/bzip2.hpp>



using namespace std;
using namespace boost;

#include <map>


std::map<std::pair<string, string>, std::list<double>> matrixMap;

void read_quants_bin(string path){
    boost::iostreams::filtering_istream countMatrixStream;
    countMatrixStream.push(boost::iostreams::gzip_decompressor());
    
    std::list<string> columns;
    std::list<string> rows;
    cout << path << "\n";
//    path = path + "/alevin";
    string quant_file = path + "/quants_mat.gz";
    string cb_file = path +  "/quants_mat_rows.txt";
    string gene_file = path + "/quants_mat_cols.txt";
    cout << "base_location : " << path << "\n";
    cout << "quant_file : " << quant_file << "\n";
    cout << "cb_file : " << cb_file << "\n";
    cout << "gene_file : " << gene_file << "\n";
    
    
    string line;
    ifstream columnFile (gene_file);
    if (columnFile.is_open())
    {
        while ( getline (columnFile,line) )
        {
            columns.push_back(line);
            //cout << line << '\n';
        }
        cout << "Columns size : " << columns.size() << "\n";
        columnFile.close();
    }
    
    ifstream rowFile (cb_file);
    if (rowFile.is_open())
    {
        while ( getline (rowFile,line) )
        {
            rows.push_back(line);
            //cout << line << '\n';
        }
        cout << "Rows size : " << rows.size() << "\n";
        rowFile.close();
    }
    
    
    
    std::ifstream file1;
    file1.exceptions(std::ios::failbit | std::ios::badbit);
    file1.open(path + "/quants_mat.gz", std::ios_base::in | std::ios_base::binary);
    
    boost::iostreams::filtering_stream<boost::iostreams::input> decompressor;
    decompressor.push(boost::iostreams::gzip_decompressor());
    decompressor.push(file1);
    
    long columnSize = columns.size();
    
    const int buffSize= 8;
    char buffer[buffSize * columnSize];
    char tempBuffer[buffSize];
    
    
    int index1 = 0;
    int index2 = 0;
    
    for (auto const& row : rows) {
            decompressor.get(buffer, buffSize * columnSize);
            index1 = 0;
            for (auto const& column : columns){
                index2 = 0;
                for(int i = 0; i < 8;i++){
                    tempBuffer[index2++] = buffer[index1++];
                }
            double n = 1;
            n = atof (tempBuffer);
            cout << tempBuffer;
            
//                        if(matrixMap.count(std::make_pair(row, column)) == 0) {
//                            std::list<double> values;
//                            values.push_back(n);
//                            matrixMap[std::make_pair(row, column)] = values;
//                        }
//                        else {
//                            std::list<double> values = matrixMap[std::pair<string,string>(row, column)];
//                            values.push_back(n);
//                            matrixMap[std::make_pair(row, column)] = values;
//                        }
        }
    }
}


 double getValue(string row, string column, int number){
     list<double> emptyList;
    if(matrixMap.count(std::make_pair(row, column)) == 0){
        return 0.0;
    }
    else{
        list<double> values = matrixMap[std::pair<string,string>(row, column)];
        list<double>::iterator it = values.begin();
        for(int i=0; i<number; i++){
            ++it;
        }
        return *it;
    }
}



int main(int argc, const char * argv[]) {
    // insert code here...
    cout << "Hello, World!\n";
    read_quants_bin("/Users/anand/Downloads/alevin/mouse_1");
    read_quants_bin("/Users/anand/Downloads/alevin/mouse_2");
    return 0;
}
