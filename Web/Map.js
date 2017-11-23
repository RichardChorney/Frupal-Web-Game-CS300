/////////////////////////////////////////////////////
//Map.js
//CS300 Group E
//This file contains the javascript involving the map
/////////////////////////////////////////////////////

const SIZE = 50; //Width and Height of all Grovnicks
const mapSize = 10; //One dimension of the map size
var terrainMap = "1222221111111222111111112211111111121111111111111111111111111111111111111111133311111113331111111111";
var typeMap = "0000000000001000000000000000010000000000000002000000000000000003000000000000000000000000000000000000";

//Get the canvas details
var canvas = document.getElementById("frupalCanvas");
var context = canvas.getContext("2d");

/* Images */
var grass = new Image();
var dirt = new Image();
var water = new Image();
var hatchet = new Image();
var chest = new Image();
var explosiveChest = new Image();

/* Map arrays */
var terrains = new Array(mapSize); //2D map array of terrains to dsiplay
var types = new Array(mapSize);    //2D map array of types to be displayed over terrains

//Gets called while the window is being loaded
//Do all initializations here.
window.onload = function() {
    initImages();
    initMap();
    loadMapFromString();
}

//Launch cgi
//This funciton sends a single string to the
//backend of Frupal by concatenating all of the
//parameters together.
//moveDirection -> Direction the Hero attempted to step
//decision -> Yes or No decision if he was prompted for something.
function launchCGI(moveDirection, decision) {
    /*
    arguments = moveDirection + "|" + decision;
    var xhttp = new XMLHttpRequest();
    URL = "frupalCGI.cgi?" + arguments;
    xhttp.open("GET", URL, false);
    xhttp.send();
    alert(xhttp.responseText); //TEST
    */
}

//Move North
function move(direction) {
    //This is where we would send the movement to c++ land
    launchCGI(direction, "none");
}

//Once the last image has been loaded, display the map
//TODO: Make sure to update this to the last image!!!
explosiveChest.onload = function() {
    displayMap();
}

//Initialize the images
function initImages() {
    grass.src = "Sprites/grass.png";
    dirt.src = "Sprites/dirt.png";
    water.src = "Sprites/water.png";
    hatchet.src = "Sprites/hatchet.png";
    chest.src = "Sprites/chest.png";
    explosiveChest.src = "Sprites/explosiveChest.png";
}

//Called when the window first loads
function displayMap() {
    /* Draw the terrains */
    for (var i = 0; i < mapSize; ++i) {
        for (var j = 0; j < mapSize; ++j) {
            if (terrains[i][j] == 1) {
                displayImg(grass, i, j);
            } else if (terrains[i][j] == 2) {
                displayImg(dirt, i, j);
            } else if (terrains[i][j] == 3) {
                displayImg(water, i, j);
            }
        }
    }

    //TODO There is no point in iterating twice here,
    //just add the logic into one of the nested for loops

    /* Draw the objects / types */
    for (var i = 0; i < mapSize; ++i) {
        for (var j = 0; j < mapSize; ++j) {
            if (types[i][j] == 1) {
                displayImg(hatchet, i, j);
            } else if (types[i][j] == 2) {
                displayImg(chest, i, j);
            } else if (types[i][j] == 3) {
                displayImg(explosiveChest, i, j);
            }
        }
    }
}

//Initialize maps
function initMap() {

    //Allocate memory for terrain and types arrays
    for (var i = 0; i < mapSize; ++i) {
        terrains[i] = new Array(mapSize);
        types[i] = new Array(mapSize);
    }
}

//Initializes the map array's from a string
//This string will be sent through ajax eventually
function loadMapFromString() {

    /* HTTP REQUEST MAJESTICNESS */
    var httpRequest;
    httpRequest = new XMLHttpRequest();
    httpRequest.onreadystatechange = parseMapString();
    httpRequest.open('GET', 'http://web.cecs.pdx.edu/~cofer2/CS300_project/Web/webTerrain.html', true);
    httpRequest.send();

    //Parses the string and turns it into a beautiful map
    function parseMapString() {
        //Makes sure the server has responded
        if(httpRequest.readyState === XMLHttpRequest.DONE) {
            //Checks for the all clear code from the server
            if(httpRequest.status === 200) {

                //Takes the server response as a text string
                var contents = httpRequest.responseText;
                alert(contents);
            } else {
                alert("HttpRequest is not ready!");
            }
        } else {
            alert("Status != 200");
        }
    }


    /* Load in Terrain from terrainMap string */
    var strIndex = 0;
    for (var i = 0; i < mapSize; ++i) {
        for (var j = 0; j < mapSize; ++j) {
            terrains[i][j] = terrainMap[strIndex];
            ++strIndex;
        }
    }

    /* Load in Types from typeMap string */
    var typeIndex = 0;
    for (var i = 0; i < mapSize; ++i) {
        for (var j = 0; j < mapSize; ++j) {
            types[i][j] = typeMap[typeIndex];
            ++typeIndex;
        }
    }

}

//Test function that updates the graphics on the canvas
//Triggered with a button click
function changeMap() {
    //Change some grass into dirt
    terrains[5][2] = 2;
    terrains[4][3] = 2;
    terrains[4][4] = 2;
    terrains[4][2] = 2;
    terrains[4][5] = 2;
    types[9][9] = 3; //Add a chest
    displayMap(); //Redraw
}

//Clears the canvas for redraw
function clearMap() {
    context.clearRect(0, 0, canvas.width, canvas.height);
}

//Displays an image on the canvas at the
//coordinates specified by the params
function displayImg(img, x, y) {
    context.drawImage(img, x * SIZE, y * SIZE);
}

//Sample function to change text
//Could add a parameter for the Id
//Instead of using "demo"
function changeText() {
    document.getElementById("demo").innerHTML = "Hello there";
}
