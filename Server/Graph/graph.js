class Cost {
    constructor(distance, heightDifference) {
        this.distance = distance;
        this.heightDifference = heightDifference;
    }
}

class ArcInfo {
    constructor(transportType, cost) {
        this.transportType = transportType;
        this.cost = cost;
    }
}


function getArcInfo(node1, node2) {
    let endsId = getEndsId(node1, node2);

    if (graph.has(endsId)) {
        return graph.get(endsId);
    } else {
        return undefined;
    }    
}

function hashCode(s) {
    for(var i = 0, h = 0; i < s.length; i++)
        h = Math.imul(31, h) + s.charCodeAt(i) | 0;
    return h;
}

function getEndsId(node1, node2) {
    let str = node1.toString() + " " + node2.toString();
    return hashCode(str);
}


const transportTypeEnum = Object.freeze({walking: 1, biking: 2, driving: 3});
const nbArcs = 15;
const graph = new Map();
/*
for (let i = 0; i < nbArcs; i++) {
    var node1 = Math.round(rand(1,100));
    var node2 = Math.round(rand(1,100));
    var endsId = getEndsId(node1, node2);

    let transportType = transportTypeEnum.tram;
    let cost = new Cost(Infinity, node1 + node2);
    let arcInfo = new ArcInfo(transportType, cost);

    graph.set(endsId, arcInfo);
}

console.log(node1, node2);
console.log(getArcInfo(node1, node2));
*/


function initGraph(lines) {
    for (line of lines) {
        if (line[0] === 'a') {
            let arcData = line.split(" ");
            let costData = arcData[3].substring(1,arcData[3].length - 2).split(',');

            let node1 = Number(arcData[1]);
            let node2 = Number(arcData[2]);
            let endsId = getEndsId(node1, node2);

            let transportType = transportTypeEnum.walking;
            let cost = new Cost(costData[0], costData[1]);
            let arcInfo = new ArcInfo(transportType, cost);

            graph.set(endsId, arcInfo);
        }
        
    }
}


const fs = require("fs");
const filesToUpload = ["graphWalk.txt", "ok.txt"];
var nbOks = 0;




const uploadTasks = filesToUpload.map((file) => new Promise((resolve, reject) => {
    var reader = fs.createReadStream(file);
    reader.on('error', function(err) {reject(file); throw "Error with file " + file;})
    reader.on('data', function(chunk) {
        let lines = chunk.toString().split('\n');
        if (file === "graphWalk.txt") {
            initGraph(lines);
        }

        if (file === "ok.txt") {
            nbOks += lines.length;
        }
    });
    reader.on('end', function() {resolve(file); console.log(file + " is finished");});
}));

Promise.all(uploadTasks)
  .then(() => { console.log('All uploads completed.', nbOks, graph); })
  .catch(() => {});
