const readLine = require('readline');
const f = require('fs');

function drawPath(dMap, path) {

    for(var i = 0; i < path.length; i = i + 1) {
        dMap[path[i].y][path[i].x].letter = "*";
    }

    var data = ""
    for(var i = 0; i < lines.length; i = i + 1){
        for(var j = 0; j < lines[0].length; j = j + 1){
            data = data + dMap[i][j].letter
        }
        data = data + "\n"
    }

    console.log(data)

    try {
        f.writeFileSync('output.txt', data);
        // file written successfully
      } catch (err) {
        console.error(err);
      }

}

function findShortestPath(dMap, start, end) {
    // Create a queue to store the cells that need to be processed
    const queue = [start];
  
    // Create a map to store the previous cell for each cell
    const previous = new Map();
  
    // Create a set to store the cells that have been visited
    const visited = new Set();
    visited.add(start);

    // While the queue is not empty
    while (queue.length > 0) {
  
      const cell = queue.shift();

      // If the cell is the end cell, we have found the shortest path
      if (cell.x === end.x && cell.y === end.y) {
        break;
      }
      // Get the neighbors of the current cell
      const neighbors = getNeighbors(dMap, cell);
  
      // For each neighbor
      for (const neighbor of neighbors) {
        // If the neighbor has not been visited
        if (!visited.has(neighbor)) {
          // Mark the neighbor as visited
          visited.add(neighbor);
  
          // Add the neighbor to the queue
          queue.push(neighbor);
  
        //   // Update the previous map for the neighbor
          previous.set(neighbor, cell);
        }
      }
    }
  
    // Create an array to store the shortest path
    const path = [];
  
    // Set the current cell to the end cell
    let currentCell = end;
  
    // While there is a previous cell for the current cell
    while (previous.has(currentCell)) {

      // Add the current cell to the beginning of the path array
      path.unshift(currentCell);
  
      // Set the current cell to the previous cell
      currentCell = previous.get(currentCell);
    }
  
    // Add the start cell to the beginning of the path array
    path.unshift(start);
  
    // Return the path array
    return path;
  }

  // returned cell is not right form
  // A helper function to get the neighbors of a cell in a 2D array
function getNeighbors(grid, cell) {
    const neighbors = [];
    // Get the row and column of the cell
    const row = cell.y;
    const col = cell.x;

    const currLetter = cell.letter == 'S' ? "a" : cell.letter;

    // Check the top cell
    if (row > 0) {
        const compareTopLetter = grid[row - 1][col].letter == 'E' ? "z" : grid[row - 1][col].letter;
        if(currLetter.charCodeAt(0) - compareTopLetter.charCodeAt(0) >= -1){
            neighbors.push(grid[row - 1][col]);
        }
    }
  
    // Check the bottom cell
    if (row < grid.length - 1) {
        const compareBotLetter = grid[row + 1][col].letter == 'E' ? "z" : grid[row + 1][col].letter;
        if(currLetter.charCodeAt(0) - compareBotLetter.charCodeAt(0) >= -1){
            neighbors.push(grid[row + 1][col]);
        }
    }
  
    // Check the left cell
    if (col > 0) {
        const compareLeftLetter = grid[row][col - 1].letter == 'E' ? "z" : grid[row][col - 1].letter;
        if(currLetter.charCodeAt(0) - compareLeftLetter.charCodeAt(0) >= -1 ){
            neighbors.push(grid[row][col - 1]);
        }
    }
  
    // Check the right cell
    if (col < grid[0].length - 1) {
        const compareRightLetter = grid[row][col + 1].letter == 'E' ? "z" : grid[row][col + 1].letter;
        if(currLetter.charCodeAt(0) - compareRightLetter.charCodeAt(0) >= -1){
            neighbors.push(grid[row][col + 1]);
        }
    }
    return neighbors;
}

function buildMap(lines) {
    var dMap = [];
    // Generate letter map in code
    for(var i = 0; i < lines.length; i = i + 1){
        row = []
        for(var j = 0; j < lines[0].length; j = j + 1){
            row.push({letter: lines[i][j], x:j, y:i, path:[]})
        }
        dMap.push(row)
    }
    for(var i = 0; i < lines.length; i = i + 1){
        for(var j = 0; j < lines[0].length; j = j + 1){
            console.log(dMap[i][j])
        }
    }
    // PART 1
    // // Run dijkstra on each square - inspecting the 
    // // dMap[i][j].path = findShortestPath(start, end)
    // for(var i = 0; i < lines.length; i = i + 1){
    //     for(var j = 0; j < lines[0].length; j = j + 1){
    //         var start;
    //         var end;
    //         if (dMap[i][j].letter == 'S'){
    //             start = dMap[i][j]
    //         }
    //         if (dMap[i][j].letter == 'E'){
    //             end = dMap[i][j]
    //         }
    //         if(start && end) {
    //             const path = findShortestPath(dMap, start, end)
    //             console.log(path)
    //             console.log(path.length - 1)
    //             // drawPath(dMap, path)
    //         }
    //     }
    // }
    // return dMap;

    // PART 2
    // Run dijkstra on each square - inspecting the 
    var end;
    for(var i = 0; i < lines.length; i = i + 1){
        for(var j = 0; j < lines[0].length; j = j + 1){
            var end;
            if (dMap[i][j].letter == 'E'){
                end = dMap[i][j]
            }
        }
    }
    var shortestSoFar = 10000000;
    for(var i = 0; i < lines.length; i = i + 1){
        for(var j = 0; j < lines[0].length; j = j + 1){
            if (dMap[i][j].letter == 'a'){
                const path = findShortestPath(dMap, dMap[i][j], end)
                console.log(path)
                console.log(path.length - 1)         
                if(path.length - 1 < shortestSoFar && path.length - 1!= 0) {
                    shortestSoFar = path.length - 1;
                }   
            }
        }
    }
    console.log("Shortest path that starts at a")
    console.log(shortestSoFar)
    return dMap;

}

// the program until the file is fully read.
function readTextFile(filePath) {
    const fs = require("fs");
    return fs.readFileSync(filePath, "utf8");
}

const filePath = "./map.txt";
var text = readTextFile(filePath);
const lines = text.replace(/[\r]/g, '').split("\n");
console.log(lines)
var dMap = buildMap(lines);
throw new Error('This is not an error. This is just to abort javascript');
