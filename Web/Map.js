/////////////////////////////////////////////////////
//Map.js
//CS300 Group E
//Authors: CC, AS, MK, CD, RC, EB
//This file contains the javascript involving the map
/////////////////////////////////////////////////////

const SHOW_MIST = true; //Set true to show mist
const SIZE = 45; //Width and Height of all Grovnicks
const mapSize = 16; //One dimension of the map size
const USER_NAME = "cofer2";  //TODO PUT YOUR USERNAME HERE FOR PATH INFORMATION
const LIST_MAX = 10;	//Max size of the inventory bag


//Get the canvas details
var canvas = document.getElementById("frupalCanvas");
var context = canvas.getContext("2d");
document.onkeydown = move_key; //Kep press

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
var boat = new Image();
var heroInBoat = new Image();
var bush = new Image();
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
/* file name passed from login screen */
var fileParam;

//Once the last image has been loaded, display the map
//TODO: Make sure to update this to the last image!!!
powerBar.onload = function() {
    displayMap();
}

//Gets called while the window is being loaded
//Do all initializations here.
window.onload = function() {
	// alert("begin here.");
    launchCGI("loadDefault", " ", " ");
    initImages();
    initMap();
    update();
    displayMap();
    // alertFileParam();
}

function getParam() {
	alert("here.");
	return window.location.search.substring(1);
}

function alertFileParam() {
	fileParam = getParam();
	alert("fileParam = " + fileParam);
}

//Restarts the game state if the hero dies, is just a clone of the onload function
function restart() {
	launchCGI("restart", " ", " ");
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
    URL = "http://web.cecs.pdx.edu/~" + USER_NAME + "/CS300_project/frupalCGI.cgi?" + arguments;
    xhttp.open("GET", URL, true);
    xhttp.send();
    xhttp.onreadystatechange = afterResponse;
	function afterResponse() {
			update();
			if(xhttp.readyState === XMLHttpRequest.DONE){
				if(xhttp.status === 200){
					if(xhttp.responseText[0] == '*'){ 		//This will trigger for chests and death since there cout begins with an (*)
						alert(xhttp.responseText.slice(4));
					}
					else if(xhttp.responseText[0] == '!'){	//This will restart the game state if the hero dies triggered when cout begins with (!)
						restart();
						alert(xhttp.responseText.slice(4));
					}
					else if(xhttp.responseText[0] == '?' && xhttp.responseText[1] == '!'){ //This case happens if the royal diamonds were stepped on.
						restart();
						alert(xhttp.responseText.slice(4));
					}
					else if(xhttp.responseText[0] == '>'){ //This will trigger a prompt from the user on purchases of tools
						if(xhttp.responseText[1] == '>'){
								if(confirm(xhttp.responseText.slice(4)) == true){
										launchCGI("buyItem", " ", " ");
										update();
									} else {
										alert("Oh well, I guess you are too cheap for this fine frupal tool...");
									}
						}
						else if(xhttp.responseText[1] == '<'){		//This will trigger a prompt from the user for a powerbar
							if(confirm(xhttp.responseText.slice(3)) == true){
								launchCGI("powerBar", " ", " ");
							} else {
								alert("Oh well, I guess not everyone likes power bars...");
							}
						}
					    else if(xhttp.responseText[1] == 'v'){ //Trigger a prompt to buy a boat
                            if(confirm(xhttp.responseText.slice(3)) == true){
                                launchCGI("boat", " ", " ");
                            } else {
                                alert("Boats are too expensive anyway...");
                            }
          				}
					}
					else if(xhttp.responseText[1] == '@'){  //This will ask a user to use a tool on an obstacle
						if(confirm(xhttp.responseText.slice(4)) == true){
							displayInventory();
							update();
            			} else{
							alert("Oh well, I guess you will have to do it the hard way...");
							launchCGI("adjustEnergy", " ", " ");
						}
          			}
					else if(xhttp.responseText[0] == 'o'){		//This will trigger a prompt from the user for Binoculars
							if(confirm(xhttp.responseText.slice(3)) == true){
								launchCGI("Binoculars", " ", " ");
							} else {
								alert("Oh well, I guess you didn't want those binoculars anyways...");
							}
					}
			}
		}
	}
}

//Move North
function move(direction) {
    //This is where we would send the movement to c++ land
    launchCGI("move", direction, "empty");
}

//Allows the user to move using the arrow keys,
//or using w,a,s,d
function move_key(e){
	if(e.keyCode == 39 || e.keyCode == 68) { //right
		launchCGI("move", 2, "empty");
	}
	else if(e.keyCode == 37 || e.keyCode == 65) {	//left
		launchCGI("move", 4, "empty");
	}
	else if(e.keyCode == 38 || e.keyCode == 87) {	//up
		launchCGI("move", 1, "empty");
	}
	else if(e.keyCode == 40 || e.keyCode == 83) {	//down
		launchCGI("move", 3, "empty");
	}
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
    boat.src = "Sprites/boat.png";
    heroInBoat.src = "Sprites/heroInBoat.png";
    bush.src = "Sprites/bush.png";
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
            else if (types[i][j] == 'V') { displayImg(boat, i, j); }
            else if (types[i][j] == '@') { displayImg(bush, i, j); }


            /* Display Mist & Hero */
            if (mists[i][j] == 'H') { displayImg(hero, i, j); }
            else if (mists[i][j] == 'X' && SHOW_MIST == true) { displayImg(mist, i, j); }
            else if (mists[i][j] == '4') { displayImg(heroInBoat, i, j); }


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
    httpRequest.open('GET', 'http://web.cecs.pdx.edu/~' + USER_NAME + '/CS300_project/Web/status.html', true);
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
    httpRequest.open('GET', 'http://web.cecs.pdx.edu/~' + USER_NAME + '/CS300_project/Web/webTerrain.html', true);
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
    httpRequest.open('GET', 'http://web.cecs.pdx.edu/~' + USER_NAME + '/CS300_project/Web/webTypes.html', true);
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
    httpRequest.open('GET', 'http://web.cecs.pdx.edu/~' + USER_NAME + '/CS300_project/Web/webMists.html', true);
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
    httpRequest.open('GET', 'http://web.cecs.pdx.edu/~' + USER_NAME + '/CS300_project/Web/webMists.html', true);
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

// Close the dropdown if the user clicks outside of it
window.onclick = function(event) {
  if (!event.target.matches('.dropbtn')) {

    var dropdowns = document.getElementsByClassName("dropdown-content");
    var i;
    for (i = 0; i < dropdowns.length; i++) {
      var openDropdown = dropdowns[i];
      if (openDropdown.classList.contains('show')) {
        openDropdown.classList.remove('show');
      }
    }
  }
}

//When the user clicks on the button, toggle between hiding and showing the dropdown content, also
//takes a string as an argument and parses it to populate the inventory with. The string will be in the form of
//pairs of integers, first element of the pair is inventory slot number, second element of the pair is the quantity
//of that item, i.e. 12 would be axe, quantity 2
function displayInventory() {

	//These are the necessary variable to create a "request variable" and then opens a request to my working directory, we will need to create a
	//global constant for the right directory to GET from.
	var httpRequest;
	httpRequest = new XMLHttpRequest();

	//This tells the program what function to handle the request when the request has been answered
	httpRequest.onreadystatechange = parseInventory;
    //	httpRequest.open('GET', 'http://web.cecs.pdx.edu/~aasquier/CS300_project/inventory.html', true); //The true arg indicates a text response
    httpRequest.open('GET', 'http://web.cecs.pdx.edu/~' + USER_NAME + '/CS300_project/inventory.html', true); //The true arg indicates a text response
	httpRequest.send();

	//Parses the servers response into the inventory list
	function parseInventory() {

			//Makes sure the server has responded
			if(httpRequest.readyState === XMLHttpRequest.DONE){

				//Checks for the all clear code from the server
				if(httpRequest.status === 200){

					//Index variables
					var j = 0;
					var k = 1;

					//Takes the server response as a text string
					var listContents = httpRequest.responseText;

					//Toggles the dropdown menu
					document.getElementById("myDropdown").classList.toggle("show");

					//Populates the inventory list with the string from the back end
					for(var i = 1; i <= LIST_MAX; ++i){
						switch(parseInt(listContents[j])){
							case 0:
                                document.getElementById("slot" + i).innerHTML = i + "--> Boat" + " (" + listContents[k] + ") Allows water traversal";
								break;
							case 1:
								document.getElementById("slot" + i).innerHTML = i + "--> Hatchet" + " (" + listContents[k] + ") Removes Trees for 8 energy points";
								break;
							case 2:
								document.getElementById("slot" + i).innerHTML = i + "--> Axe" + " (" + listContents[k] + ") Removes Trees for 6 energy points";
								break;
							case 3:
								document.getElementById("slot" + i).innerHTML = i + "--> Chainsaw" + " (" + listContents[k] + ") Removes Trees for 2 energy points";
								break;
							case 4:
								document.getElementById("slot" + i).innerHTML = i + "--> Chisel" + " (" + listContents[k] + ") Removes Boulders for 15 energy points";
								break;
							case 5:
								document.getElementById("slot" + i).innerHTML = i + "--> Sledgehammer" + " (" + listContents[k] + ") Removes Boulders for 12 energy points";
								break;
							case 6:
								document.getElementById("slot" + i).innerHTML = i + "--> Jackhammer" + " (" + listContents[k] + ") Removes Boulders for 4 energy points";
								break;
							case 7:
								document.getElementById("slot" + i).innerHTML = i + "--> Machete" + " (" + listContents[k] + ") Removes Blackberry Bushes for 2 energy points";
								break;
							case 8:
								document.getElementById("slot" + i).innerHTML = i + "--> Shears" + " (" + listContents[k] + ") Removes Blackberry Bushes for 2 energy points";
								break;
							case 9:
								document.getElementById("slot" + i).innerHTML = i + "--> Binoculars" + " (" + listContents[k] + ") Doubles visibility range";
								break;

							default:
								document.getElementById("slot" + i).innerHTML = i + "--> Empty";
								break;
						}
						j += 2;
						k += 2;
					}
				} else{
					alert('There was a problem with the request');
				}
			}
		}
}


//This function will launch the appropriate action when an inventory item is clicked on, will check if the action
//is valid, and will update the status of the inventory item on the back-end
function useItem(slot){
	launchCGI("useItem", slot, " ");
}

//this function will prevent user from moving and spit out an alert if the user is dead
//does nothing currently
function deadUser(isDead){
	if(isDead==1)
	{
		alert('Player out of energy');
	}
	return;
}
