// This is a synchronous method for reading a local text file,
// which means that it will block the execution of the rest of

const { exit } = require("process");

// the program until the file is fully read.
  function readTextFile(filePath) {
    const fs = require("fs");
    return fs.readFileSync(filePath, "utf8");
  }
  
  function isEdge(i, j){
    if(i == 0 || j == 0 || i == array.length - 1 || j == array[0].length - 1){
        return true;
    }
  }
  

  function isVisible(array, i, j){
    const currValue = array[i][j];
    var isVisibleTop = false;
    var isVisibleRight = false;
    var isVisibleLeft = false;
    var isVisibleBot = false;

    // is literal edge case?
    if(isEdge(i, j)){
        console.log("edge : ( " + i +", "+j+") : "+currValue);
        return 1;
    }

    // check column from top
    for( let index = 0; index < j; index++){
        if(array[i][index] < currValue) {
            isVisibleTop = true;
        }
        else {
            isVisibleTop = false;
            break;
        }
    }

    // check column from bottom
    for( let index = array[0].length - 1; index > j; index--){
        if(array[i][index] < currValue) {
            isVisibleBot = true;
        }
        else {
            isVisibleBot = false;
            break;
        }
    }
    
    // check row from left
    for( let index = 0; index < i; index++){
        if(array[index][j] < currValue) {
            isVisibleLeft = true;
        }
        else {
            isVisibleLeft = false;
            break;
        }
    }

    // check row from right
    for( let index = array.length - 1; index > i; index--){
        if(array[index][j] < currValue) {
            isVisibleRight = true;
        }
        else {
            isVisibleRight = false;
            break;
        }
    }

    if( isVisibleBot || isVisibleLeft || isVisibleRight || isVisibleTop) {
        console.log("visible : ( " + i +", "+j+") : "+currValue);
        return 1;
    }
    return 0;
  }

  function scenicScore(array, i, j){
    const currValue = array[i][j];

    var topVal = 0;
    var rightVal = 0;
    var leftVal = 0;
    var botVal = 0;

    // check column from top
    for( let index = j - 1; index >= 0; index--){
        if(array[i][index] < currValue) {
            topVal = topVal + 1;
        }
        else {
            topVal = topVal + 1;
            break;
        }
    }
    // i = 2, j = 1

    // check column from bottom
    for( let index = j + 1; index < array[0].length; index++){
        if(array[i][index] < currValue) {
            botVal = botVal + 1;
        }
        else {
            botVal = botVal + 1;
            break;
        }
    }
    // i = 2, j = 1

    // check row from left
    for( let index = i - 1; index >= 0; index--){
        if(array[index][j] < currValue) {
           leftVal = leftVal + 1;
        }
        else {
            leftVal = leftVal + 1;
            break;
        }
    }

    // i = 2, j = 1
    // check row from right
    for( let index = i + 1; index < array.length; index++){
        if(array[index][j] < currValue) {
            rightVal = rightVal + 1;
        }
        else {
            rightVal = rightVal + 1;
            break;
        }
    }
    // if (i == 2 && j == 3){
    //     console.log(array.length);
    //     console.log("(" + i + ", " + j + ")");
    //     console.log(array[i][j]);
    //     console.log("top:" + topVal);
    //     console.log("bot:" + botVal);
    //     console.log("right:" + rightVal);
    //     console.log("left:" + leftVal);
    //     console.log("----")
    //     exit(0);
    // }
    return topVal * botVal * rightVal * leftVal;
  }
  
  
  // This function takes a string of text and returns a 2D array
  // where each element is a character from the original string.
  function populateArray(text) {
    text = text.replace(/[\r]/g, '');
    // Split the string into an array of individual lines
    const lines = text.split("\n");
  
    // Create an empty 2D array with the same number of rows as
    // there are lines in the text file, and the same number of
    // columns as the length of the longest line.
    const array = Array.from(Array(lines.length), () =>
      Array(Math.max(...lines.map((line) => line.length)))
    );
  
    // Iterate over the lines and characters in the text, and
    // populate the 2D array with the characters from the text.
    for (let i = 0; i < lines.length; i++) {
      const line = lines[i];
      for (let j = 0; j < line.length; j++) {
        array[i][j] = parseInt(line[j]);
      }
    }
  
    return array;
  }
  
  // Use the above functions to read from a local text file and
  // populate a 2D array with the characters from that file.
  const filePath = "./trees.txt";
  const text = readTextFile(filePath);
  const array = populateArray(text);
  var sumOfVisible = 0;

  var bestView = 0;

  for ( let i = 0; i < array.length; i++) {
    for ( let j = 0; j < array[0].length; j++) {
        var returnVal = isVisible(array, i, j);
        sumOfVisible += returnVal;
        var currScore = scenicScore(array, i, j);
        if( currScore > bestView) {
            bestView = currScore;
        }
    }
  }

  
  console.log(array);
  console.log(sumOfVisible);
  console.log(bestView);