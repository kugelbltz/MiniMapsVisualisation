/* QUADTREE CLASSES */
class Node {
    constructor(id, lat, lon) {
        this.id = id;
        this.lat = lat;
        this.lon = lon;
    }
}

class Region {
    constructor(lat, lon, halfDimension) {
        this.lat = lat;
        this.lon = lon;
        this.halfDimension = halfDimension;
    }


    contains(node) {
        let isVerticallyBound = Math.abs(node.lat - this.lat) <= this.halfDimension;
        let isHorizontallyBound = Math.abs(node.lon - this.lon) <= this.halfDimension;

        return isHorizontallyBound && isVerticallyBound;
    }


    get left() {
        return this.lon - this.halfDimension;
    }

    get right() {
        return this.lon + this.halfDimension;
    }

    get top() {
        return this.lat + this.halfDimension;
    }

    get bottom() {
        return this.lat - this.halfDimension;
    }

    intersects(other) {

        let overlaps1 = this.left <= other.right;
        let overlaps2 = this.right >= other.left;
        let overlaps3 = this.top >= other.bottom;
        let overlaps4 = this.bottom <= other.top;

        return overlaps1 && overlaps2 && overlaps3 && overlaps4;
    }
}

class QuadTree {
    constructor(boundary) {
        this.boundary = boundary;
        this.nodes = [];
        this.capacity = 4;
        this.divided = false;
    }

    insert(node) {
        if (!this.boundary.contains(node)) {
            return;
        }

        if (this.nodes.length < this.capacity && !this.divided) {
            this.nodes.push(node);
        } else {
            if (!this.divided) {
                this.subdivide();
                this.divided = true;
            }

            this.ne.insert(node);
            this.nw.insert(node);
            this.se.insert(node);
            this.sw.insert(node);
        }
    }

    subdivide() {

        let halfDimension = this.boundary.halfDimension / 2;

        let leftLon = this.boundary.lon - halfDimension;
        let rightLon = this.boundary.lon + halfDimension;
        let topLat = this.boundary.lat + halfDimension;
        let bottomLat = this.boundary.lat - halfDimension;

        let nwBoundary = new Region(topLat, leftLon, halfDimension);
        this.nw = new QuadTree(nwBoundary);

        let neBoundary = new Region(topLat, rightLon, halfDimension);
        this.ne = new QuadTree(neBoundary);

        let swBoundary = new Region(bottomLat, leftLon, halfDimension);
        this.sw = new QuadTree(swBoundary);

        let seBoundary = new Region(bottomLat, rightLon, halfDimension);
        this.se = new QuadTree(seBoundary);

        for (let i = 0; i < this.nodes.length; i++) {
            let n = this.nodes[i];
            this.ne.insert(n);
            this.nw.insert(n);
            this.se.insert(n);
            this.sw.insert(n);
        }
        this.nodes = [];
    }

    queryRange(range) {
        var nodesInRange = [];

        if (!this.boundary.intersects(range))
            return nodesInRange;


        if (this.divided) {
            nodesInRange = nodesInRange.concat(this.ne.queryRange(range));
            nodesInRange = nodesInRange.concat(this.nw.queryRange(range));
            nodesInRange = nodesInRange.concat(this.se.queryRange(range));
            nodesInRange = nodesInRange.concat(this.sw.queryRange(range));

        } else {
            for (let i = 0; i < this.nodes.length; i++) {
                if (range.contains(this.nodes[i]))
                    nodesInRange.push(this.nodes[i]);
            }
        }
        return nodesInRange;
    }

    findNearest(lat, lon) {
        let range = new Region(lat, lon, 0.001);
        let pool = this.queryRange(range);

        let dist = -1;
        let nearest;

        for (let n of pool) {
            let currentDistance = distance(n.lat, n.lon, lat, lon);
            if (currentDistance < dist || dist === -1) {
                nearest = n;
                dist = currentDistance;
            }
        }
        return nearest["id"];
    }
}

/* GLOBAL VARIABLES */
const express = require("express");
const app = express();
const fs = require("fs");
const reader = fs.createReadStream(process.cwd() + '\\..\\Interface\\Data\\nodes.co');

const maxLat = 44.903;
const minLat = 44.776;
const maxLon = -0.481;
const minLon = -0.687;

let deltaLat = maxLat - minLat;
let deltaLon = maxLon - minLon;
let midLat = (minLat + maxLat) / 2.0;
let midLon = (minLon + maxLon) / 2.0;
const halfDimension = ((deltaLat > deltaLon) ? deltaLat : deltaLon);
const rootRegion = new Region(midLat, midLon, halfDimension);
const quadTree = new QuadTree(rootRegion);

const nodesData = new Map();
var failed = 0;

const invalidNode = {
    latitude: -91.0,
    longitude: 189.0
}

/* FUNCTIONS */
function getName(nodeInfo) {
    let name = nodeInfo[5];
    for (let i = 6; i < nodeInfo.length; i++) {
        name += " " + nodeInfo[i];
    }
    return name;
}

function distance(lat1, lon1, lat2, lon2) {
    lat1 *= Math.PI / 180;
    lat2 *= Math.PI / 180;
    lon1 *= Math.PI / 180;
    lon2 *= Math.PI / 180;


    let deltaLat = Math.abs(lat1 - lat2);
    let deltaLon = Math.abs(lon1 - lon2);



    let a1 = Math.sin(deltaLat / 2) * Math.sin(deltaLat / 2);
    let a2 = Math.cos(lat1) * Math.cos(lat2);
    let a3 = Math.sin(deltaLon / 2) * Math.sin(deltaLon / 2);
    let a = a1 + a2 * a3;

    let c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1 - a));
    return 6371 * c;
}


/* READING NODES.CO FILE : SETTING UP MAP AND QUAD OF NODES */
console.time("Setting up data structures");
console.log("Reading nodes.co");
reader.on('data', function (line) {
    if (nodesData.size > 1000000) {
        return;
    }

    let data = line.toString().split('\n');
    for (i = 0; i < data.length; i++) {
        let nodeInfo = data[i].split(' ');

        let info;

        let id = parseInt(nodeInfo[1]);
        let lat = parseFloat(nodeInfo[2]);
        let lon = parseFloat(nodeInfo[3]);


        if (isNaN(lat) || isNaN(lon) || isNaN(id)) {
            failed += 1;
            continue;
        }


        if (nodeInfo[5] === "undefined") {
            info = {
                latitude: lat,
                longitude: lon
            }
        } else {
            info = {
                latitude: lat,
                longitude: lon,
                name: getName(nodeInfo)
            }
        }

        nodesData.set(id, info);
        let node = new Node(id, lat, lon);
        quadTree.insert(node);
    }
});

reader.on('error', function() {console.log("error"); reader.close();})

reader.on('end', function () {
    console.timeEnd("Setting up data structures");

    let lossRate = failed / nodesData.size * 100.0;
    console.log(failed + " nodes lost out of " + nodesData.size + " => " + lossRate + "%");

    var server = app.listen(8000, () => {
        console.log("Waiting for requests ...");
    })

    app.get('/coord/:id', (req, res) => {

        console.time("getNodeInfo");
        if (nodesData.has(parseInt(req.params.id))) {
            res.send(nodesData.get(parseInt(req.params.id)));
        } else {
            res.send(invalidNode);
        }
        console.timeEnd("getNodeInfo");
    });

    app.get('/near/:lat/:lon', (req, res) => {
        // si les coordonnés ne sont pas dans le carré
        console.time("findNearest");
        let id = quadTree.findNearest(parseFloat(req.params.lat), parseFloat(req.params.lon));
        console.timeEnd("findNearest");

        let closestNodeId = {
            id: id
        };
        res.send(closestNodeId);
    });

    app.get('/stop', (req, res) => {
        res.send("Bye bitch !")
        server.close();
    })
})