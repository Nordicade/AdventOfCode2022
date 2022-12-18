package main

import (
	"bufio"
	"fmt"
	"log"
	"math"
	"os"
	"strconv"
	"strings"
)

type Coordinate struct {
	x       int
	y       int
	visited bool
}

func printOut(direction string, repeats int, headPos Coordinate, tailPos Coordinate) {
	fmt.Println(direction + " : " + strconv.Itoa(repeats))
	fmt.Printf("H: (%d, %d) Value: %v\n", headPos.x, headPos.y, headPos.visited)
	fmt.Printf("T: (%d, %d) Value: %v\n", tailPos.x, tailPos.y, tailPos.visited)
	fmt.Println("- - -")
}

func moveNotRequired(x1, y1, x2, y2 float64) bool {
	// Calculate the distance between the two points using the Euclidean distance formula
	d := math.Sqrt(math.Pow(x2-x1, 2) + math.Pow(y2-y1, 2))
	fmt.Println(d)
	// Return true if the distance is less than or equal to 1, and false otherwise
	return d <= 1.42
}

func findLateralDiff(head, tail int) int {
	//newHeadPos.x > oldTailPos.x ? 1 : -1
	if head > tail {
		return 1
	}
	return -1
}

func calculateTail(oldTailPos Coordinate, newHeadPos Coordinate) Coordinate {

	if moveNotRequired(float64(newHeadPos.x), float64(newHeadPos.y), float64(oldTailPos.x), float64(oldTailPos.y)) {
		fmt.Println("no action taken for tail")
		return oldTailPos
	}

	// Check for easy moves - up, left, right, down
	if newHeadPos.x == oldTailPos.x || newHeadPos.y == oldTailPos.y {

		// Calculate change for new tail pos
		if newHeadPos.x == oldTailPos.x {
			diff := findLateralDiff(newHeadPos.y, oldTailPos.y)
			return Coordinate{oldTailPos.x, oldTailPos.y + diff, true}
		} else if newHeadPos.y == oldTailPos.y {
			diff := findLateralDiff(newHeadPos.x, oldTailPos.x)
			return Coordinate{oldTailPos.x + diff, oldTailPos.y, true}
		} else {
			fmt.Println("Invalid calculate trail state")
			os.Exit(1)
		}
	}

	// Handle diagonal changes
	// we can split this into 4 possibilities
	// treat tail as origin, and the head as a quadrant
	if newHeadPos.x > oldTailPos.x && newHeadPos.y > oldTailPos.y {
		// move tail diagonally to the up right
		return Coordinate{oldTailPos.x + 1, oldTailPos.y + 1, true}
	} else if newHeadPos.x < oldTailPos.x && newHeadPos.y > oldTailPos.y {
		// move tail diagonally to the up left
		return Coordinate{oldTailPos.x - 1, oldTailPos.y + 1, true}
	} else if newHeadPos.x < oldTailPos.x && newHeadPos.y < oldTailPos.y {
		// move tail diagonally to the down left
		return Coordinate{oldTailPos.x - 1, oldTailPos.y - 1, true}
	} else if newHeadPos.x > oldTailPos.x && newHeadPos.y < oldTailPos.y {
		// move tail diagonally to the down right
		return Coordinate{oldTailPos.x + 1, oldTailPos.y - 1, true}
	}

	fmt.Println("no diagonal or lateral move")

	return oldTailPos
}

func main() {
	file, err := os.Open("ropeHardTest.txt")
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()

	var lines []string
	dict := make(map[Coordinate]bool)
	headPos := Coordinate{0, 0, false}
	tailPos := Coordinate{0, 0, true}
	dict[tailPos] = true
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		lines = append(lines, scanner.Text())
	}

	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}

	file.Close()

	for _, line := range lines {
		parts := strings.Split(line, " ")
		direction := parts[0]
		repeats, err := strconv.Atoi(parts[1])
		if err != nil {
			fmt.Println("bad repeat input")
			os.Exit(1)
		}
		for repeats > 0 {
			if direction == "R" {
				oldTailPos := tailPos
				headPos.x = headPos.x + 1
				repeats = repeats - 1
				newTailPos := calculateTail(oldTailPos, headPos)
				dict[newTailPos] = true
				tailPos = newTailPos
				printOut(direction, repeats, headPos, tailPos)
			} else if direction == "L" {
				oldTailPos := tailPos
				headPos.x = headPos.x - 1
				repeats = repeats - 1
				newTailPos := calculateTail(oldTailPos, headPos)
				dict[newTailPos] = true
				tailPos = newTailPos
				printOut(direction, repeats, headPos, tailPos)
			} else if direction == "U" {
				oldTailPos := tailPos
				headPos.y = headPos.y + 1
				repeats = repeats - 1
				newTailPos := calculateTail(oldTailPos, headPos)
				dict[newTailPos] = true
				tailPos = newTailPos
				printOut(direction, repeats, headPos, tailPos)
			} else if direction == "D" {
				oldTailPos := tailPos
				headPos.y = headPos.y - 1
				repeats = repeats - 1
				newTailPos := calculateTail(oldTailPos, headPos)
				dict[newTailPos] = true
				tailPos = newTailPos
				printOut(direction, repeats, headPos, tailPos)
			} else {
				fmt.Println("bad direction input")
				os.Exit(1)
			}
		}
		fmt.Println("Command completed")
		// for k, _ := range dict {
		// 	fmt.Printf("coord: %d, %d\n", k.x, k.y)
		// }
	}

	fmt.Println("Finished")
	for k, _ := range dict {
		fmt.Printf("coord: %d, %d\n", k.x, k.y)
	}
	fmt.Println(len(dict))
}
