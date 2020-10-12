package main

import (
	"bufio"
	"fmt"
	"os"
	"io"
	"time"
)

func main() {
	fmt.Printf("hello, world\n")
	bufferWrite(100000, 100000)
	noBufferWrite(100000)
}

func bufferWrite(buffersize int, num int) {
	fp, err := os.Create("bufferwrite.txt")
	if err != nil {
		fmt.Println(err)
		return
	}
	defer fp.Close()

	buffer := bufio.NewWriterSize(fp, buffersize)

	data := []byte("1")

	start := time.Now();

	for i := 0; i < num; i++ {
		buffer.Write(data)
	}

	end := time.Now();
	fmt.Printf("Buff:%f秒\n",(end.Sub(start)).Seconds())
}

func noBufferWrite(num int) {
	fp, err := os.Create("nobufferwrite.txt")
	if err != nil {
		fmt.Println(err)
		return
	}
	defer fp.Close()

	start := time.Now();

	for i := 0; i < num; i++ {
		_, err = io.WriteString(fp, "1")
	}
	end := time.Now();
	fmt.Printf("noBuff:%f秒\n",(end.Sub(start)).Seconds())
}