////////////////////////////////////////////////////////////////
//Inventory.js
//CS300 Group E
//This file contains the javascript involving the inventory list
////////////////////////////////////////////////////////////////

const LIST_MAX = 10;

var listContents = "11223142516273810000";


//Gets called while the window is being loaded
//Do all initializations here.


/* When the user clicks on the button, 
toggle between hiding and showing the dropdown content */
function displayInventory() {
    document.getElementById("myDropdown").classList.toggle("show");
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
