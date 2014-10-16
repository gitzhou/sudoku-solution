//
//  main.cpp
//  sudoku
//
//  Created by aaron67 on 14-10-16.
//  Copyright (c) 2014年 aaron67. All rights reserved.
//

#include "app.hpp"

int main(int argc, const char * argv[]) {
    if (argc != 2) {
        cout << "使用说明：可执行文件 [空格] 数据目录路径 [回车]" << endl;
        return 1;
    }
    App(argv[1]).run();
    return 0;
}
