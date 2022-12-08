package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
)

func isContained(sections []string) bool {
	firstLow, err1 := strconv.Atoi(sections[0])
	firstHigh, err2 := strconv.Atoi(sections[1])
	secondLow, err3 := strconv.Atoi(sections[2])
	secondHigh, err4 := strconv.Atoi(sections[3])

	if err1 != nil || err2 != nil || err3 != nil || err4 != nil {
		fmt.Println("Error")
		os.Exit(1)
	}

	if firstLow <= secondLow && firstHigh >= secondHigh {
		// fmt.Println(sections[0] + ", " + sections[1] + ", " + sections[2] + ", " + sections[3] + " were contained!")
		return true
	} else if firstLow >= secondLow && firstHigh <= secondHigh {
		// fmt.Println(sections[0] + ", " + sections[1] + ", " + sections[2] + ", " + sections[3] + " were contained!")
		return true
	} else {
		// fmt.Println(sections[0] + ", " + sections[1] + ", " + sections[2] + ", " + sections[3] + " were not contained ")
		return false
	}
}

func isOverlapping(sections []string) bool {
	firstLow, err1 := strconv.Atoi(sections[0])
	firstHigh, err2 := strconv.Atoi(sections[1])
	secondLow, err3 := strconv.Atoi(sections[2])
	secondHigh, err4 := strconv.Atoi(sections[3])

	if err1 != nil || err2 != nil || err3 != nil || err4 != nil {
		fmt.Println("Error")
		os.Exit(1)
	}

	if firstLow <= secondHigh && firstHigh >= secondLow {
		// fmt.Println(sections[0] + ", " + sections[1] + ", " + sections[2] + ", " + sections[3] + " were contained!")
		return true
	} else {
		return false
	}
}

func main() {
	file, err := os.Open("sections.txt")
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()

	var lines []string
	var totalContainments int = 0
	var totalOverlaps int = 0

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		lines = append(lines, scanner.Text())
	}

	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}

	file.Close()

	for _, line := range lines {
		line = strings.ReplaceAll(line, "-", ",")
		var decoupled []string = strings.Split(line, ",")
		if isContained(decoupled) {
			totalContainments += 1
		}
		if isOverlapping(decoupled) {
			totalOverlaps += 1
		}
	}

	fmt.Println("Total number of containments :" + strconv.Itoa(totalContainments))
	fmt.Println("Total number of overlaps :" + strconv.Itoa(totalOverlaps))

}
