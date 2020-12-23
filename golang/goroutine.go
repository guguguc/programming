package main

import (
	"time"
	"fmt"
	"math"
)

const n = 100
var fibN [n]int

func spinner(delay time.Duration) {
	s := `-\|/`
	for i := 0;; i = (i+1)%4 {
		fmt.Printf("\r%c", s[i])
		time.Sleep(delay)
	}
}

func fib(x int) int {
	if x < 2 {
		fibN[x] = 1
		return 1
	}
	if fibN[x-1] == 0 {
		fibN[x-1] = fib(x-1)
	}
	if fibN[x-2] == 0 {
		fibN[x-2] = fib(x-2)
	}
	return fibN[x-1] + fibN[x-2]
}

func main() {
	go spinner(100 * time.Millisecond)
	for i := 0; i < n - 1; i++ {
		ans := fib(i)
		if ans > math.MaxInt64 >> 1 {
			break
		}
		fmt.Printf("\rFibonacci(%d) = %d\n", i, ans)
	}
}