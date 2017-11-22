////////////////////////////////////////////////////////////////
//Inventory.js
//CS300 Group E
//This file contains the javascript involving the inventory list
////////////////////////////////////////////////////////////////

const LIST_MAX = 10;

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
function displayInventory(listContents) {
	document.getElementById("myDropdown").classList.toggle("show");
	var j = 0;
	var k = 1;
	for(var i = 1; i <= LIST_MAX; ++i){
		switch(parseInt(listContents[j])){
			case 0:
				document.getElementById("slot" + i).innerHTML = i + "--> Empty";
				break;
			case 1:
				document.getElementById("slot" + i).innerHTML = i + "--> Hatchet" + " (" + k + ") Removes Trees for 8 energy points";
				break;
			case 2:
				document.getElementById("slot" + i).innerHTML = i + "--> Axe" + " (" + k + ") Removes Trees for 6 energy points";
				break;
			case 3:
				document.getElementById("slot" + i).innerHTML = i + "--> Chainsaw" + " (" + k + ") Removes Trees for 2 energy points";
				break;
			case 4:
				document.getElementById("slot" + i).innerHTML = i + "--> Chisel" + " (" + k + ") Removes Boulders for 15 energy points";
				break;
			case 5:
				document.getElementById("slot" + i).innerHTML = i + "--> Sledgehammer" + " (" + k + ") Removes Boulders for 12 energy points";
				break;
			case 6:
				document.getElementById("slot" + i).innerHTML = i + "--> Jackhammer" + " (" + k + ") Removes Boulders for 4 energy points";
				break;
			case 7:
				document.getElementById("slot" + i).innerHTML = i + "--> Machete" + " (" + k + ") Removes Blackberry Bushes for 2 energy points";
				break;
			case 8:
				document.getElementById("slot" + i).innerHTML = i + "--> Shears" + " (" + k + ") Removes Blackberry Bushes for 2 energy points";
				break;
			default:
				document.getElementById("slot" + i).innerHTML = i + "--> Empty";
				break;
		}
		j += 2;
		k += 2;
	}  


	
}

//This function will launch the appropriate action when an inventory item is clicked on, will check if the action
//is valid, and will update the status of the inventory item on the back-end
function useItem(){
	
}

