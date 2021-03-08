package main

import "fmt"
import "strings"

func add(x, y int) int {
	return x + y
}

func echo(x, y string) (string, string) {
	return y, x
}

func split(str string) []string {
	return strings.Split(str, "/")
}

func fibonacci() func() int {
	a, b := 1, 0
	return func() int {
		a, b = b, a+b
		return a
	}
}

func demo() {
	fmt.Println("1 + 2 =", add(1, 2))
	fmt.Println(echo("hello", "world"))
	fmt.Println(split("/usr/share/bison"))
	f := fibonacci()
	for i := 0; i < 10; i++ {
		fmt.Println(f())
	}
}
