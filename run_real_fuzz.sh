#!/bin/bash
echo "=== 运行真实 AFL++ 模糊测试 ==="

cd ~/MallSystem

# 设置系统
echo "配置系统..."
echo core | sudo tee /proc/sys/kernel/core_pattern > /dev/null 2>&1 || true
echo performance | sudo tee /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor 2>/dev/null || true

# 创建输入输出目录
echo "创建测试目录..."
rm -rf fuzz_input fuzz_output
mkdir -p fuzz_input
mkdir -p fuzz_output

# 创建更好的种子文件
echo "创建种子文件..."
cat > fuzz_input/seed1.txt << 'EOF'
P001 iPhone 15 2 5999.99
EOF

cat > fuzz_input/seed2.txt << 'EOF'
Hello, I would like to inquire about product availability
EOF

cat > fuzz_input/seed3.txt << 'EOF'
CRASH_ME
EOF

cat > fuzz_input/seed4.txt << 'EOF'
这是一条中文测试消息
EOF

cat > fuzz_input/seed5.txt << 'EOF'
ProductID: P123, Quantity: 5, Price: 99.99
EOF

# 创建一些边界情况
echo -n -e '\x00' > fuzz_input/null.txt
echo "A" > fuzz_input/single.txt
python3 -c "print('B'*100)" > fuzz_input/medium.txt
python3 -c "print('C'*1000)" > fuzz_input/large.txt

echo "种子文件列表:"
ls -la fuzz_input/

# 运行 AFL++
echo -e "\n🚀 启动 AFL++ 模糊测试..."
echo "按 Ctrl+C 停止测试"
echo "监控命令: tail -f fuzz_output/master/fuzzer_stats"

cd fuzz_build
timeout 60 afl-fuzz -i ../fuzz_input -o ../fuzz_output -M master -- ./fuzzer @@

# 显示结果
echo -e "\n=== 模糊测试结果 ==="
if [ -f "../fuzz_output/master/fuzzer_stats" ]; then
    echo "执行统计:"
    grep -E "start_time|last_update|execs_done|execs_per_sec|paths_total|unique_crashes|unique_hangs" ../fuzz_output/master/fuzzer_stats
    
    if [ -d "../fuzz_output/master/crashes" ]; then
        CRASH_COUNT=$(ls -1 ../fuzz_output/master/crashes/ 2>/dev/null | grep -v "README" | wc -l)
        echo -e "\n发现的崩溃: $CRASH_COUNT"
        if [ $CRASH_COUNT -gt 0 ]; then
            echo "崩溃文件:"
            ls -la ../fuzz_output/master/crashes/
            
            # 尝试复现第一个崩溃
            FIRST_CRASH=$(ls ../fuzz_output/master/crashes/id* 2>/dev/null | head -1)
            if [ -n "$FIRST_CRASH" ]; then
                echo -e "\n复现第一个崩溃: $FIRST_CRASH"
                timeout 5 ./fuzzer "$FIRST_CRASH" 2>&1 | head -20
            fi
        fi
    else
        echo "未发现崩溃"
    fi
else
    echo "AFL++ 没有生成统计文件，可能运行失败"
fi