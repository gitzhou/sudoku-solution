//
//  sudoku.hpp
//  sudoku
//
//  Created by aaron67 on 14-10-16.
//  Copyright (c) 2014年 aaron67. All rights reserved.
//

#ifndef sudoku_sudoku_hpp
#define sudoku_sudoku_hpp

#include <vector>
#include <string>
#include <queue>
#include "grid.hpp"
using std::vector;
using std::string;
using std::queue;

// 数独核心算法类
class Sudoku {
public:
    Sudoku(const vector<string> &input);
    void cal(); // 回溯法求解
    const vector<Grid> &result() const { return m_result; }
    
public:
    static const int GRID_TOTAL_ROW_COUNT_SIZE = 9; // 数独表格的大小
    static const int GRID_EACH_ROW_COUNT_SIZE = 3; // 数独每一宫的行列数
    
private:
    // 计算表格row行col列位置，在当前情况下，可以填入的值
    // row从0开始计数
    // col从0开始计数
    queue<int> updateOptionalVal(int row, int col);
    
    // 判断表格row行，是否出现过值val
    // row从0开始计数
    bool valueIsShownInRow(int val, int row) const;
    // 判断表格col列，是否出现过值val
    // col从0开始计数
    bool valueIsShownInColumn(int val, int col) const;
    // 判断表格row行col列位置所在的宫，是否出现过值val
    // row从0开始计数
    // col从0开始计数
    bool valueIsShownInOwn33Grid(int val, int row, int col) const;
    
private:
    Grid m_input; // 数独输入
    vector<Grid> m_result; // 解法集合
};

#endif
