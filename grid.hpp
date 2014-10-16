//
//  grid.hpp
//  sudoku
//
//  Created by aaron67 on 14-10-16.
//  Copyright (c) 2014年 aaron67. All rights reserved.
//

#ifndef sudoku_grid_hpp
#define sudoku_grid_hpp

#include <vector>
#include <iostream>
using std::vector;
using std::ostream;
using std::cout;
using std::endl;

// N行N列表格
class Grid {
public:
    Grid() {}
    
    /*
     * rowColumnSize 表格的行列数
     * val 表格每个元素的初始值
     */
    explicit Grid(int rowColumnSize, int val = 0) : m_rowColumnSize(rowColumnSize) {
        resizeGrid(val);
    }
    
    int rowColumnSize() const { return m_rowColumnSize; }
    void setRowColumnSize(int size) {
        m_rowColumnSize = size;
        resizeGrid();
    }
    
    vector<vector<int> > &grid() { return m_grid; }
    const vector<vector<int> > &grid() const { return m_grid; }
    
    /*
     * 友好的输出表格内容
     * seperatedElementsCount 每隔几个字符输出一个空白字符（换行或者空格）
     * os ostream对象，默认输出到屏幕
     */
    void output(int seperatedElementsCount, ostream &os = cout) const {
        for (int i = 0; i < m_rowColumnSize; ++i) {
            if (i % seperatedElementsCount == 0) {
                os << endl;
            }
            for (int j = 0; j < m_rowColumnSize; ++j) {
                if (j % seperatedElementsCount == 0) {
                    os << ' ';
                }
                os << m_grid[i][j];
            }
            os << endl;
        }
    }
    
private:
    void resizeGrid(int val = 0) {
        m_grid.resize(m_rowColumnSize);
        for (int i = 0; i < m_rowColumnSize; ++i) {
            vector<int> row(m_rowColumnSize, val);
            m_grid[i] = row;
        }
    }
    
private:
    int m_rowColumnSize; // 表格行列数
    vector<vector<int> > m_grid; // 表格内容
};

#endif
