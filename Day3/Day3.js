const readLine = require('readline');
const f = require('fs');
const { exit } = require('process');

global.prioritySum = 0;
global.lines = [];

var file = './Day3/rucksack.txt';
var rl = readLine.createInterface({
    input : f.createReadStream(file),
    output : process.stdout,
    terminal: false
});

function getOverlap(line) {
    var dict = {};
    const mid = line.length / 2
    const first = line.substring(0,mid);
    const second = line.substring(mid,line.length);

    for (let i = 0; i < first.length; i++) {
        dict[first[i]] = true;
    }
    for (let i = 0; i < second.length; i++) {
        if(dict[second[i]]){
            return second[i];
        }
    }
}

function getPriority(letter) {
    // lowercase
    if(letter.charCodeAt(0) >= 97){
        return (letter.charCodeAt(0)) - 96;
    }
    // uppercase
    else {
        return (letter.charCodeAt(0)) - 38;
    }
}

function getThreeOverlap(one, two, three){
    var dict = [];
    for (var i = 0; i < one.length; i++){
        dict[one[i]] = 1;
    }
    for (var i = 0; i < two.length; i++){
        if(two[i] in dict){
            dict[two[i]] = 2
        }
    }
    for (var i = 0; i < three.length; i++){
        if(three[i] in dict && dict[three[i]] == 2){
            return three[i];
        }
    }
}

function findBadges() {
    console.log("finding badges");
    var groups = [];
    for(var i = 0; i < global.lines.length; i = i + 3){
        var letter = getThreeOverlap(
            global.lines[i],
            global.lines[i+1],
            global.lines[i+2],
            );
        groups.push(letter);
    }

    console.log(groups.length);
    var sum = 0;
    for(var i = 0; i < groups.length; i++){
        sum += getPriority(groups[i]);
    }
    return sum;
}

rl.on('line', function (text) {
  // The following commands were used for Part 1
  // const overlap = getOverlap(text);
  // global.prioritySum += getPriority(overlap);
  global.lines.push(text);
  console.log("read lines");
});

// const result = findBadges();

// console.log(result);

rl.on('close', function () {
    console.log('closing');
    const result = findBadges();

    console.log(result);
});