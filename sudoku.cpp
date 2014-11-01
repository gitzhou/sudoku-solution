//
//  sudoku.cpp
//  sudoku
//
//  Created by aaron67 on 14-10-16.
//  Copyright (c) 2014年 aaron67. All rights reserved.
//

#include "sudoku.hpp"
#include <stack>
using std::stack;

Sudoku::Sudoku(const vector<string> &input) : m_input(GRID_TOTAL_ROW_COUNT_SIZE) {
    for (int i = 0; i < input.size(); ++i) {
        for (int j = 0; j < input[i].length(); ++j) {
            m_input.grid()[i][j] = input[i][j] - '0';
        }
    }
}

// 回溯法求解
void Sudoku::cal() {
    // 从一维角度搜索
    // i的范围为[0, GRID_TOTAL_ROW_COUNT_SIZE * GRID_TOTAL_ROW_COUNT_SIZE - 1)
    int i = 0;
    // 在搜索过程中，记录直至当前，0~i位置可以填哪些可选值
    vector<queue<int> > optionalVal(GRID_TOTAL_ROW_COUNT_SIZE * GRID_TOTAL_ROW_COUNT_SIZE);
    // 在搜索过程中，记录直至当前，哪些i位置的值，已被修改过
    stack<int> iset;
    // 搜索
    while (true) {
        // 将一维下标转换成二维下标
        int row = i / GRID_TOTAL_ROW_COUNT_SIZE, col = i % GRID_TOTAL_ROW_COUNT_SIZE;
        bool valid = true;
        if (i < GRID_TOTAL_ROW_COUNT_SIZE * GRID_TOTAL_ROW_COUNT_SIZE) {
            if (m_input.grid()[row][col] != 0) { // 当前位置的值是初始给定的，跳过本次
                ++i;
                continue;
            }
            // 计算当前位置的所有可选值
            if ((optionalVal[i] = updateOptionalVal(row, col)).size() == 0) {
                valid = false;
            } else {
                // 设置当前位置的值
                m_input.grid()[row][col] = optionalVal[i].front();
                optionalVal[i].pop();
                // i位置的值修改过，更新
                iset.push(i);
            }
        }
        if (valid && i >= GRID_TOTAL_ROW_COUNT_SIZE * GRID_TOTAL_ROW_COUNT_SIZE - 1) {
            // 找到一组解
            m_result.push_back(m_input);
        }
        if (valid && i < GRID_TOTAL_ROW_COUNT_SIZE * GRID_TOTAL_ROW_COUNT_SIZE - 1) {
            ++i; // 下一步
            continue;
        }
        // 回溯
        while (i >= GRID_TOTAL_ROW_COUNT_SIZE * GRID_TOTAL_ROW_COUNT_SIZE ||
               (i >= 0 && optionalVal[i].size() == 0)) {
            if (iset.size() != 0 && iset.top() == i) { // 如果i位置的值被修改过
                m_input.grid()[row][col] = 0;
                iset.pop();
            }
            --i;
            row = i / GRID_TOTAL_ROW_COUNT_SIZE;
            col = i % GRID_TOTAL_ROW_COUNT_SIZE;
        }
        if (i == -1) {
            break; // 已试探全部可能
        } else {
            // 设置当前位置的值为下一个可选值
            m_input.grid()[row][col] = optionalVal[i].front();
            optionalVal[i].pop();
        }
    }
}

// 计算表格row行col列位置，在当前情况下，可以填入的值
// row从0开始计数
// col从0开始计数
queue<int> Sudoku::updateOptionalVal(int row, int col) {
    queue<int> optionalVal;
    for (int i = 1; i <= GRID_TOTAL_ROW_COUNT_SIZE; ++i) {
        if (!valueIsShownInRow(i, row) &&
            !valueIsShownInColumn(i, col) &&
            !valueIsShownInOwn33Grid(i, row, col)) {
            optionalVal.push(i);
        }
    }
    return optionalVal;
}

// 判断表格row行，是否出现过值val
// row从0开始计数
bool Sudoku::valueIsShownInRow(int val, int row) const {
    for (int i = 0; i < GRID_TOTAL_ROW_COUNT_SIZE; ++i) {
        if (m_input.grid()[row][i] == val) {
            return true;
        }
    }
    return false;
}

// 判断表格col列，是否出现过值val
// col从0开始计数
bool Sudoku::valueIsShownInColumn(int val, int col) const {
    for (int i = 0; i < GRID_TOTAL_ROW_COUNT_SIZE; ++i) {
        if (m_input.grid()[i][col] == val) {
            return true;
        }
    }
    return false;
}

// 判断表格row行col列位置所在的宫，是否出现过值val
// row从0开始计数
// col从0开始计数
bool Sudoku::valueIsShownInOwn33Grid(int val, int row, int col) const {
    for (int i = row / GRID_EACH_ROW_COUNT_SIZE * GRID_EACH_ROW_COUNT_SIZE;
         i < row / GRID_EACH_ROW_COUNT_SIZE * GRID_EACH_ROW_COUNT_SIZE + GRID_EACH_ROW_COUNT_SIZE;
         ++i) {
        for (int j = col / GRID_EACH_ROW_COUNT_SIZE * GRID_EACH_ROW_COUNT_SIZE;
             j < col / GRID_EACH_ROW_COUNT_SIZE * GRID_EACH_ROW_COUNT_SIZE + GRID_EACH_ROW_COUNT_SIZE;
             ++j) {
            if (m_input.grid()[i][j] == val) {
                return true;
            }
        }
    }
    return false;
}