// Latitude : y axis ranging from +90° (NORTH) to -90° (SOUTH)
// Longitude : x axis ranging from -180° (WEST) to +180° (EAST)

/* CLASSES FOR THE QUADTREE */
class Node {
    constructor(id, lat, lon) {
        this.id = id;
        this.lat = lat;
        this.lon = lon;
    }
    
    toString() {
        console.log(`${this.id} : (${this.lat}, ${this.lon})`);
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
    
    findNearest(lat, lon, range) {
        let pool = this.queryRange(range);
        console.log(pool.length);
        let dist = -1;
        let nearest;
        
        for (let n of pool) {
            let currentDistance = distance(n.lat, n.lon, lat, lon);
            if (currentDistance < dist || dist === -1) {
                nearest = n;
                dist = currentDistance;
            } 
        }
        return nearest;
    }
}


/* FUNCTIONS THAT ARE REQUIRED FOR SOME REASONS */
// TBH ONLY DISTANCE IS ACTUALLY USEFULL
function rand(min, max) {
    return Math.random() * (max - min) + min; 
}

function distance(lat1, lon1, lat2, lon2) {
    return Math.sqrt(Math.pow(lat1 - lat2, 2) + Math.pow(lon1 - lon2, 2))
}


/* SPEEDTEST BETWEEN FINDING NEAREST WITH A MAP OR WITH A QUADTREE */
const scale = 16;
const rootRegion = new Region(0,0,scale);
const smallRegion = new Region(0, 0, 0.1); // Search area should be about 0.001 degrees around the center point
const quadTree = new QuadTree(rootRegion);


console.time("Creation of quad tree");
for (let i = 0; i < 1000000; i++) {
    let node = new Node(i,rand(-scale, scale), rand(-scale, scale));
    quadTree.insert(node);
}
console.timeEnd("Creation of quad tree");

console.time("findNearest quad");
quadTree.findNearest(0, 0, smallRegion);
console.timeEnd("findNearest quad");

