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
	x    int
	y    int
	tail bool
}

func moveNotRequired(x1, y1, x2, y2 float64) bool {
	// Calculate the distance between the two points using the Euclidean distance formula
	d := math.Sqrt(math.Pow(x2-x1, 2) + math.Pow(y2-y1, 2))
	// fmt.Println(d)
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
		// fmt.Println("no action taken for tail")
		return oldTailPos
	}

	// Check for easy moves - up, left, right, down
	if newHeadPos.x == oldTailPos.x || newHeadPos.y == oldTailPos.y {

		// Calculate change for new tail pos
		if newHeadPos.x == oldTailPos.x {
			diff := findLateralDiff(newHeadPos.y, oldTailPos.y)
			return Coordinate{oldTailPos.x, oldTailPos.y + diff, oldTailPos.tail}
		} else if newHeadPos.y == oldTailPos.y {
			diff := findLateralDiff(newHeadPos.x, oldTailPos.x)
			return Coordinate{oldTailPos.x + diff, oldTailPos.y, oldTailPos.tail}
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
		return Coordinate{oldTailPos.x + 1, oldTailPos.y + 1, oldTailPos.tail}
	} else if newHeadPos.x < oldTailPos.x && newHeadPos.y > oldTailPos.y {
		// move tail diagonally to the up left
		return Coordinate{oldTailPos.x - 1, oldTailPos.y + 1, oldTailPos.tail}
	} else if newHeadPos.x < oldTailPos.x && newHeadPos.y < oldTailPos.y {
		// move tail diagonally to the down left
		return Coordinate{oldTailPos.x - 1, oldTailPos.y - 1, oldTailPos.tail}
	} else if newHeadPos.x > oldTailPos.x && newHeadPos.y < oldTailPos.y {
		// move tail diagonally to the down right
		return Coordinate{oldTailPos.x + 1, oldTailPos.y - 1, oldTailPos.tail}
	}

	fmt.Println("no diagonal or lateral move")

	return oldTailPos
}

func main() {
	file, err := os.Open("rope.txt")
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()

	var lines []string
	dict := make(map[Coordinate]bool)
	headPos := Coordinate{0, 0, false}
	knots := make([]Coordinate, 9)
	knots[8].tail = true

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
		fmt.Println(direction + " : " + strconv.Itoa(repeats))
		if err != nil {
			fmt.Println("bad repeat input")
			os.Exit(1)
		}
		for repeats > 0 {
			// move head
			if direction == "R" {
				headPos.x = headPos.x + 1
				repeats = repeats - 1
			} else if direction == "L" {
				headPos.x = headPos.x - 1
				repeats = repeats - 1
			} else if direction == "U" {
				headPos.y = headPos.y + 1
				repeats = repeats - 1
			} else if direction == "D" {
				headPos.y = headPos.y - 1
				repeats = repeats - 1
			} else {
				fmt.Println("bad direction input")
				os.Exit(1)
			}
			// move knots that follow
			for i := 0; i < 9; i++ {
				var currHead Coordinate
				var currTail Coordinate
				if i == 0 {
					currHead = headPos
					currTail = knots[i]
				} else {
					currHead = knots[i-1]
					currTail = knots[i]
				}

				newTail := calculateTail(currTail, currHead)
				if newTail.tail {
					dict[newTail] = true
				}
				knots[i] = newTail
			}

		}
		fmt.Println("Command completed")
		fmt.Printf("H: %d, %d \n", headPos.x, headPos.y)
		for index, coord := range knots {
			fmt.Printf("%d: %d, %d, %t \n", index, coord.x, coord.y, coord.tail)
		}
	}

	fmt.Println("Finished")
	for k, _ := range dict {
		fmt.Printf("coord: %d, %d\n", k.x, k.y)
	}
	fmt.Println(len(dict))
}
