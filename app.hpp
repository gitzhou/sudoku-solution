//
//  app.hpp
//  sudoku
//
//  Created by aaron67 on 14-10-16.
//  Copyright (c) 2014年 aaron67. All rights reserved.
//

#ifndef sudoku_app_hpp
#define sudoku_app_hpp

#include <iostream>
#include <fstream>
#include <sstream>
#include "sudoku.hpp"
using std::fstream;
using std::ios_base;
using std::stringstream;

class App {
public:
    App(const string &path) : m_dataDirPath(path) {}
    
    void run() const {
        // 输入
        fstream inFile(m_dataDirPath + "/in.txt", ios_base::in);
        vector<string> dataInput;
        while(!inFile.eof())
        {
            string line;
            getline(inFile, line);
            dataInput.push_back(line);
        }
        inFile.close();
        // 构建 & 运算
        Sudoku s(dataInput);
        s.cal();
        // 输出
        cout << "找到 " << s.result().size() << " 组解" << endl;
        for (int i = 0; i < s.result().size(); ++i) {
            string fileName = "out" + intToString(i) + ".txt";
            fstream outFile(m_dataDirPath + "/" + fileName, ios_base::out);
            s.result()[i].output(Sudoku::GRID_EACH_ROW_COUNT_SIZE, outFile);
            outFile.close();
        }
    }
    
private:
    string intToString(int i) const {
        stringstream ss;
        ss << i;
        string s;
        ss >> s;
        return s;
    }
    
private:
    string m_dataDirPath; // 数据目录路径
};

#endif
