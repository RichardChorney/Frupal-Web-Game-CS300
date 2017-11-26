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
//Terrains
var grass = new Image();
var bog = new Image();
var water = new Image();
var forest = new Image();
var wall = new Image();
var mist = new Image();
//Types
var chest = new Image();
var explosiveChest = new Image();
var royalDiamonds = new Image();
var powerBar = new Image();
var tree = new Image();
var boulder = new Image();
var clue = new Image();
var binoculars = new Image();
//Tools
var hatchet = new Image();
var axe = new Image();
var chainsaw = new Image();
var chisel = new Image();
var hammer = new Image();
var jackhammer = new Image();
var machete = new Image();
var shears = new Image();
//Hero
var hero = new Image();

/* Map arrays */
var terrains = new Array(mapSize); //2D map array of terrains to dsiplay
var types = new Array(mapSize);    //2D map array of types to be displayed over terrains
var mists = new Array(mapSize);

//Once the last image has been loaded, display the map
//TODO: Make sure to update this to the last image!!!
powerBar.onload = function() {
    displayMap();
}

//Gets called while the window is being loaded
//Do all initializations here.
window.onload = function() {
    initImages();
    initMap();
    update();
    displayMap();
}

//This function should be called after
//anything has changed on the backend
//and needs to be updated on the Web.
function update() {
    loadTerrainFromString();
    loadTypesFromString();
    loadMistsFromString();
    loadStatusFromString();
    displayMap();
}

//Launch cgi
//Takes an action code to tell the back end what function to launch, such as move, change inventory etc.
//The action1 will be what parameter to send to the appropriate back end function, will expand to an "action2"
//if more parameters are needed.   
//ACTION CODES  --->   move (action1 is our 1,2,3,4 code for movement), loadDefault (loads default map, no args), 
//loadFile (action1 is file name to load), buyItem (action1 is the type being purchased), useItem (action1 is the slot in the inventory bag)
function launchCGI(actionCode, action1, action2) {
    
    arguments = actionCode + "|" + action1 + "|" + action2 + "*";
    var xhttp = new XMLHttpRequest();
    URL = "http://web.cecs.pdx.edu/~aasquier/CS300_project/frupalCGI.cgi?" + arguments;
    xhttp.open("GET", URL, true);
    xhttp.send();
    xhttp.onreadystatechange = afterResponse;

	function afterResponse() {
			if(xhttp.readyState === XMLHttpRequest.DONE){
				if(xhttp.status === 200){
					//TODO We can put a switch statement here to respond accordingly to different actions and remove the TEST
					alert(xhttp.responseText); //TEST
				}
			} 
	}
}

//Move North
function move(direction) {
    //This is where we would send the movement to c++ land
    launchCGI("move", direction, "empty");
}

//Initialize the images
function initImages() {
    //Terrain
    grass.src = "Sprites/grass.png";
    bog.src = "Sprites/dirt.png";
    water.src = "Sprites/water.png";
    mist.src = "Sprites/mist.png";
    wall.src = "Sprites/wall.png";
    forest.src = "Sprites/forest.png";
    //Types
    chest.src = "Sprites/chest.png";
    explosiveChest.src = "Sprites/explosiveChest.png";
    royalDiamonds.src = "Sprites/royalDiamonds.png";
    powerBar.src = "Sprites/powerBar.png";
    tree.src = "Sprites/tree.png";
    boulder.src = "Sprites/boulder.png";
    clue.src = "Sprites/clue.png";
    binoculars.src = "Sprites/binoculars.png";
    //Tools
    hatchet.src = "Sprites/hatchet.png";
    axe.src = "Sprites/axe.png";
    chainsaw.src = "Sprites/chainsaw.png";
    chisel.src = "Sprites/chisel.png";
    hammer.src = "Sprites/hammer.png";
    jackhammer.src = "Sprites/jackhammer.png";
    machete.src = "Sprites/machete.png";
    shears.src = "Sprites/shears.png";
    //Hero
    hero.src = "Sprites/hero.png";
}

//Called when the window first loads
function displayMap() {

    /* Draw the terrains */
    for (var i = 0; i < mapSize; ++i) {
        for (var j = 0; j < mapSize; ++j) {

            /* Display Terrain */
            if (terrains[i][j] == 'G') { displayImg(grass, i, j); } //Change this to back to grass
            else if (terrains[i][j] == 'S') { displayImg(bog, i, j); }
            else if (terrains[i][j] == 'B') { displayImg(bog, i, j); }
            else if (terrains[i][j] == 'W') { displayImg(water, i, j); }
            else if (terrains[i][j] == '|') { displayImg(wall, i, j); }
            else if (terrains[i][j] == 'F') { displayImg(forest, i, j); }

            /* Display Type */
            if (types[i][j] == 'A') { displayImg(hatchet, i, j); }
            else if (types[i][j] == 'X') { displayImg(axe, i, j); }
            else if (types[i][j] == 'E') { displayImg(chainsaw, i, j); }
            else if (types[i][j] == 'J') { displayImg(chisel, i, j); }
            else if (types[i][j] == 'L') { displayImg(hammer, i, j); }
            else if (types[i][j] == 'Y') { displayImg(jackhammer, i, j); }
            else if (types[i][j] == 'M') { displayImg(machete, i, j); }
            else if (types[i][j] == 'Q') { displayImg(shears, i, j); }
            else if (types[i][j] == '$') { displayImg(chest, i, j); }
            else if (types[i][j] == '$') { displayImg(explosiveChest, i, j); }
            else if (types[i][j] == 'R') { displayImg(royalDiamonds, i, j); }
            else if (types[i][j] == 'P') { displayImg(powerBar, i, j); }
            else if (types[i][j] == '^') { displayImg(tree, i, j); }
            else if (types[i][j] == 'B') { displayImg(boulder, i, j); }
            else if (types[i][j] == 'C') { displayImg(clue, i, j); }
            else if (types[i][j] == '8') { displayImg(binoculars, i, j); }

            /* Display Mist & Hero */
            if (mists[i][j] == 'H') { displayImg(hero, i, j); }
            else if (mists[i][j] == 'X' && SHOW_MIST == true) { displayImg(mist, i, j); }


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

//Reads status string from Web/status.html
function loadStatusFromString()
{
    var httpRequest;
    httpRequest = new XMLHttpRequest();
    httpRequest.onreadystatechange = parseStatusString;
    httpRequest.open('GET', 'http://web.cecs.pdx.edu/~lwarden/CS300_project/Web/status.html', true);
    httpRequest.send();


    function parseStatusString() {

        //Makes sure the server has responded
        if(httpRequest.readyState === XMLHttpRequest.DONE) {

            //Checks for the all clear code from the server
            if(httpRequest.status === 200) {

                //Takes the server response as a text string
                var statusString = httpRequest.responseText;
                updateMessageWindow(statusString);

            } else {
                alert('Status: There was a problem with the request');
            }
        }
    }
}

function updateMessageWindow(statStr)
{
    var statArr = statStr.split('|'); //splits the string into an array, separating on '|'

    document.getElementById("messageWindow").innerHTML =
             "Whiffles: " + statArr[0] + "<br>" +
             "Energy: " + statArr[1] + "<br>" + 
             "Location: (" + statArr[2] + ", " + statArr[3] + ")<br>" +
             "Terrain: " + statArr[4] + "<br><br>" +
             statArr[5];
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

//Loads the Mist and Hero from a file,
//puts it into a string,
//and then loads it into the mists
//array
function loadMistsFromString()
{
    var httpRequest;
    httpRequest = new XMLHttpRequest();
    httpRequest.onreadystatechange = parseMistsString;
    httpRequest.open('GET', 'http://web.cecs.pdx.edu/~cofer2/CS300_project/Web/webMists.html', true);
    httpRequest.send();


    function parseMistsString() {

        //Makes sure the server has responded
        if(httpRequest.readyState === XMLHttpRequest.DONE) {

            //Checks for the all clear code from the server
            if(httpRequest.status === 200) {

                //Takes the server response as a text string
                var  listContents = httpRequest.responseText;
                fillMists(listContents);

            } else {
                alert('Mists: There was a problem with the request');
            }
        }
    }
}

//Fills in the mists array
//with the values passed in by 'mi'
function fillMists(mi) {
    var strIndex = 0;
    for (var i = 0; i < mapSize; ++i) {
        for (var j = 0; j < mapSize; ++j) {
            mists[i][j] = mi[strIndex];
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
