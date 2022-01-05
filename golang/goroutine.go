package main

import (
	"fmt"
	"time"
)

const n = 100

var fibN [n]float64

type FuncMetric struct {
	file_name   string
	func_sig    string
	line_number int
	line_cnt    int
}

func spinner(delay time.Duration) {
	s := `-\|/`
	for i := 0; ; i = (i + 1) % 4 {
		fmt.Printf("\r%c", s[i])
		time.Sleep(delay)
	}
}

func fib(x int) float64 {
	if x < 2 {
		fibN[x] = 1
		return 1
	}
	if fibN[x-1] == 0 {
		fibN[x-1] = fib(x - 1)
	}
	if fibN[x-2] == 0 {
		fibN[x-2] = fib(x - 2)
	}
	return fibN[x-1] + fibN[x-2]
}

func fib2(x int) int {
	if x < 2 {
		return x
	}
	var l = fib2(x - 1)
	var r = fib2(x - 2)
	return l + r
}

func adder() func(int) int {
	sum := 0
	return func(x int) int {
		sum += x
		return sum
	}
}

func main() {
	// go spinner(100 * time.Millisecond)
	// for i := 0; i < n - 1; i++ {
	// 	ans := fib(i)
	// 	fmt.Printf("\rFibonacci(%d) = %f\n", i, ans)
	// }
	// fmt.Printf("\rFib %d is %d", 60, fib2(60))
	fun := adder()
	for i := 0; i < 10; i++ {
		fmt.Println(fun(i))
	}
}
