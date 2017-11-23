/////////////////////////////////////////////////////
//Map.js
//CS300 Group E
//This file contains the javascript involving the map
/////////////////////////////////////////////////////

const SHOW_MIST = false; //Set true to show mist
const SIZE = 50; //Width and Height of all Grovnicks
const mapSize = 10; //One dimension of the map size

//Get the canvas details
var canvas = document.getElementById("frupalCanvas");
var context = canvas.getContext("2d");

/* Images */
var grass = new Image();
var bog = new Image();
var water = new Image();
var hatchet = new Image();
var chest = new Image();
var explosiveChest = new Image();
var mist = new Image();
var hero = new Image();

/* Map arrays */
var terrains = new Array(mapSize); //2D map array of terrains to dsiplay
var types = new Array(mapSize);    //2D map array of types to be displayed over terrains
var mists = new Array(mapSize);

//Once the last image has been loaded, display the map
//TODO: Make sure to update this to the last image!!!
hero.onload = function() {
    displayMap();
}

//Gets called while the window is being loaded
//Do all initializations here.
window.onload = function() {
    initImages();
    initMap();
    update();
}

//This function should be called after
//anything has changed on the backend
//and needs to be updated on the Web.
function update() {
    loadTerrainFromString();
    loadTypesFromString();
    loadMistsFromString();
}

//Launch cgi
//This funciton sends a single string to the
//backend of Frupal by concatenating all of the
//parameters together.
//moveDirection -> Direction the Hero attempted to step
//decision -> Yes or No decision if he was prompted for something.
function launchCGI(moveDirection) {
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


//Initialize the images
function initImages() {
    grass.src = "Sprites/grass.png";
    bog.src = "Sprites/dirt.png";
    water.src = "Sprites/water.png";
    hatchet.src = "Sprites/hatchet.png";
    chest.src = "Sprites/chest.png";
    explosiveChest.src = "Sprites/explosiveChest.png";
    mist.src = "Sprites/mist.png";
    hero.src = "Sprites/hero.png";
}

//Called when the window first loads
function displayMap() {
    /* Draw the terrains */
    for (var i = 0; i < mapSize; ++i) {
        for (var j = 0; j < mapSize; ++j) {

            /* Display Terrain */
            if (terrains[i][j] == 'G') { displayImg(grass, i, j); }
            else if (terrains[i][j] == 'S') { displayImg(bog, i, j); }
            else if (terrains[i][j] == 'W') { displayImg(water, i, j); }

            /* Display Type */
            if (types[i][j] == 1) { displayImg(hatchet, i, j); }
            else if (types[i][j] == 2) { displayImg(chest, i, j); }
            else if (types[i][j] == 3) { displayImg(explosiveChest, i, j); }

            /* Display Mist & Hero */
            if (mists[i][j] == 0 && SHOW_MIST == true) {
                displayImg(mist, i, j);
            } else if (mists[i][j] == 2) { displayImg(hero, i, j); }

        }
    }
}

//Initialize maps
function initMap() {

    //Allocate memory for terrain and types arrays
    for (var i = 0; i < mapSize; ++i) {
        terrains[i] = new Array(mapSize);
        types[i] = new Array(mapSize);
        mists[i] = new Array(mapSize);
    }
}

//Initializes the map array's from a string
//This string will be sent through ajax eventually
function loadTerrainFromString()
{
    var httpRequest;
    httpRequest = new XMLHttpRequest();
    httpRequest.onreadystatechange = parseTerrainString;
    httpRequest.open('GET', 'http://web.cecs.pdx.edu/~cofer2/CS300_project/Web/webTerrain.html', true);
    httpRequest.send();


    function parseTerrainString() {

        //Makes sure the server has responded
        if(httpRequest.readyState === XMLHttpRequest.DONE) {

            //Checks for the all clear code from the server
            if(httpRequest.status === 200) {

                //Takes the server response as a text string
                var  listContents = httpRequest.responseText;
                fillTerrain(listContents);

            } else {
                alert('Terrain: There was a problem with the request');
            }
        }
    }
}

//Fills in the terrain array
//with contents in terr
function fillTerrain(terr) {
    /* Load in Terrain from terrainMap string */
    var strIndex = 0;
    for (var i = 0; i < mapSize; ++i) {
        for (var j = 0; j < mapSize; ++j) {
            terrains[i][j] = terr[strIndex];
            ++strIndex;
        }
    }

    displayMap();
}

//Loads the Types from a file,
//puts it into a string,
//and then loads it into the type
//array
function loadTypesFromString()
{
    var httpRequest;
    httpRequest = new XMLHttpRequest();
    httpRequest.onreadystatechange = parseTypesString;
    httpRequest.open('GET', 'http://web.cecs.pdx.edu/~cofer2/CS300_project/Web/webTypes.html', true);
    httpRequest.send();


    function parseTypesString() {

        //Makes sure the server has responded
        if(httpRequest.readyState === XMLHttpRequest.DONE) {

            //Checks for the all clear code from the server
            if(httpRequest.status === 200) {

                //Takes the server response as a text string
                var  listContents = httpRequest.responseText;
                fillTypes(listContents);

            } else {
                alert('Types: There was a problem with the request');
            }
        }
    }
}

//Fills in the types array
//with the values passed in by 'ty'
function fillTypes(ty) {
    var strIndex = 0;
    for (var i = 0; i < mapSize; ++i) {
        for (var j = 0; j < mapSize; ++j) {
            types[i][j] = ty[strIndex];
            ++strIndex;
        }
    }

    displayMap();
}

//Loads in from file the grovnicks
//that should be covered in mist.
function loadMistsFromString() {
    var httpRequest;
    httpRequest = new XMLHttpRequest();
    httpRequest.onreadystatechange = parseMistString;
    httpRequest.open('GET', 'http://web.cecs.pdx.edu/~cofer2/CS300_project/Web/webMists.html', true);
    httpRequest.send();


    function parseMistString() {

        //Makes sure the server has responded
        if(httpRequest.readyState === XMLHttpRequest.DONE) {

            //Checks for the all clear code from the server
            if(httpRequest.status === 200) {

                //Takes the server response as a text string
                var  listContents = httpRequest.responseText;
                fillMists(listContents);

            } else {
                alert('Types: There was a problem with the request');
            }
        }
    }
}

//Fills in the mists array
//with the values passed in
function fillMists(mis) {
    var strIndex = 0;
    for (var i = 0; i < mapSize; ++i) {
        for (var j = 0; j < mapSize; ++j) {
            mists[i][j] = mis[strIndex];
            ++strIndex;
        }
    }

    displayMap();
}

//Test function that updates the graphics on the canvas
//Triggered with a button click
function changeMap() {
    //Change some grass into bog
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
