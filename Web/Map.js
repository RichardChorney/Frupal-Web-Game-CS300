/////////////////////////////////////////////////////
//Map.js
//CS300 Group E
//This file contains the javascript involving the map
/////////////////////////////////////////////////////

const SIZE = 64; //Width and Height of all Grovnicks
const mapSize = 10; //One dimension of the map size

//Get the canvas details
var canvas = document.getElementById("frupalCanvas");
var context = canvas.getContext("2d");

/* Images */
var grass = new Image();
var dirt = new Image();
var water = new Image();

/* Map arrays */
var terrains = new Array(mapSize); //2D map array of terrains to dsiplay
var types = new Array(mapSize);    //2D map array of types to be displayed over terrains

//Gets called while the window is being loaded
//Do all initializations here.
window.onload = function() {
    initImages();
    initMap();
    displayMap();
}

//Initialize the images
function initImages() {
    grass.src = "Sprites/grass.png";
    dirt.src = "Sprites/dirt.png";
    water.src = "Sprites/water.png";
}

//Called when the window first loads
function displayMap() {
    grass.onload = function() {

        //Will make this more elegant in the future
        for (var i = 0; i < mapSize; ++i) {
            for (var j = 0; j < mapSize; ++j) {
                if (terrains[i][j] == 0) {
                    displayImg(grass, i, j);
                } else if (terrains[i][j] == 1) {
                    displayImg(dirt, i, j);
                } else if (terrains[i][j] == 2) {
                    displayImg(water, i, j);
                }
            }
        }
    };

}

//Initialize maps
function initMap() {

    //Allocate memory for terrain and types arrays
    for (var i = 0; i < mapSize; ++i) {
        terrains[i] = new Array(mapSize);
        types[i] = new Array(mapSize);
    }

    //FIXME
    //Example terrain, this would normally all
    //be read in from a file and set that way.

    //Set all terrain to grass
    for (var i = 0; i < mapSize; ++i) {
        for (var j = 0; j < mapSize; ++j) {
            terrains[i][j] = 0;
        }
    }

    //Dirt
    terrains[0][0] = 1;
    terrains[0][1] = 1;
    terrains[0][2] = 1;
    terrains[1][0] = 1;
    terrains[1][2] = 1;
    terrains[1][3] = 1;
    terrains[2][2] = 1;
    terrains[2][3] = 1;
    terrains[3][2] = 1;

    //Water
    terrains[7][7] = 2;
    terrains[7][8] = 2;
    terrains[8][7] = 2;
    terrains[8][8] = 2;

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
