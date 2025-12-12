#!/bin/bash
echo "=== 详细崩溃分析 ==="

cd ~/MallSystem

# 分析所有崩溃
for crash in fuzz_output/master/crashes/id:*; do
    echo -e "\n 分析崩溃: $(basename "$crash")"
    echo "文件大小: $(stat -c%s "$crash") 字节"
    
    # 查看文件类型
    echo "文件类型:"
    file "$crash"
    
    # 查看文件内容
    echo -e "\n文件内容（前100字节）:"
    head -c 100 "$crash" | hexdump -C
    
    echo -e "\n文件内容（文本）:"
    cat "$crash" 2>/dev/null | head -c 200
    echo -e "\n"
    
    # 尝试运行看看是否真的崩溃
    echo "运行测试..."
    timeout 2 fuzz_build/fuzzer "$crash" 2>&1 | head -20
    echo "退出码: $?"
    echo "---"
done